#include "Scanner/BridgeScanner.h"
#include "State/ChtlJsState.h"
#include "Context/ChtlJsContext.h"
#include <sstream>
#include <regex>

namespace chtl {

BridgeScanner::BridgeScanner() 
    : enabled_(true) {
    // 初始化状态和上下文
    chtlJsState_ = std::make_shared<ChtlJsState>(nullptr);
    chtlJsContext_ = std::make_shared<ChtlJsContext>();
    
    // 设置默认配置
    config_.splitStrategy = SplitStrategy::SYNTAX_BASED;
    config_.maxSegmentSize = 1024 * 1024; // 1MB
    config_.enableOptimization = true;
    config_.cacheResults = true;
}

BridgeScanner::~BridgeScanner() = default;

std::vector<std::shared_ptr<Segment>> BridgeScanner::scan(const std::string& code) {
    if (!enabled_ || code.empty()) {
        return {};
    }
    
    // 检查缓存
    if (config_.cacheResults) {
        auto it = cache_.find(code);
        if (it != cache_.end()) {
            return it->second;
        }
    }
    
    std::vector<std::shared_ptr<Segment>> segments;
    
    switch (config_.splitStrategy) {
        case SplitStrategy::SYNTAX_BASED:
            segments = scanSyntaxBased(code);
            break;
        case SplitStrategy::LINE_BASED:
            segments = scanLineBased(code);
            break;
        case SplitStrategy::BLOCK_BASED:
            segments = scanBlockBased(code);
            break;
        case SplitStrategy::HYBRID:
            segments = scanHybrid(code);
            break;
    }
    
    // 优化段
    if (config_.enableOptimization) {
        segments = optimizeSegments(segments);
    }
    
    // 缓存结果
    if (config_.cacheResults) {
        cache_[code] = segments;
    }
    
    return segments;
}

void BridgeScanner::dispatch(std::shared_ptr<Segment> segment) {
    if (!segment) return;
    
    switch (segment->getType()) {
        case SegmentType::JAVASCRIPT:
            for (auto& handler : jsHandlers_) {
                handler(segment);
            }
            break;
            
        case SegmentType::CHTL_JAVASCRIPT:
            for (auto& handler : chtlJsHandlers_) {
                handler(segment);
            }
            break;
            
        case SegmentType::MIXED:
            // 混合段需要进一步分割
            auto mixedSeg = std::dynamic_pointer_cast<MixedSegment>(segment);
            if (mixedSeg) {
                auto subSegments = splitMixedSegment(mixedSeg);
                dispatchAll(subSegments);
            }
            break;
    }
}

void BridgeScanner::dispatchAll(const std::vector<std::shared_ptr<Segment>>& segments) {
    for (const auto& segment : segments) {
        dispatch(segment);
    }
}

void BridgeScanner::registerJavaScriptHandler(SegmentHandler handler) {
    jsHandlers_.push_back(handler);
}

void BridgeScanner::registerChtlJavaScriptHandler(SegmentHandler handler) {
    chtlJsHandlers_.push_back(handler);
}

void BridgeScanner::enable(bool enabled) {
    enabled_ = enabled;
}

void BridgeScanner::reset() {
    if (chtlJsState_) {
        chtlJsState_->reset();
    }
    if (chtlJsContext_) {
        chtlJsContext_->reset();
    }
    clearCache();
}

void BridgeScanner::clearCache() {
    cache_.clear();
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::scanSyntaxBased(const std::string& code) {
    std::vector<std::shared_ptr<Segment>> segments;
    std::vector<BoundaryInfo> boundaries = findBoundaries(code);
    
    if (boundaries.empty()) {
        // 没有边界，整个代码是一个段
        auto type = detectSegmentType(code);
        segments.push_back(createSegment(type, code));
        return segments;
    }
    
    // 根据边界分割代码
    size_t lastPos = 0;
    for (const auto& boundary : boundaries) {
        if (boundary.position > lastPos) {
            // 创建从lastPos到boundary.position的段
            std::string segmentCode = code.substr(lastPos, boundary.position - lastPos);
            segments.push_back(createSegment(boundary.type, segmentCode));
        }
        lastPos = boundary.position;
    }
    
    // 处理最后一段
    if (lastPos < code.length()) {
        std::string segmentCode = code.substr(lastPos);
        auto type = detectSegmentType(segmentCode);
        segments.push_back(createSegment(type, segmentCode));
    }
    
    return segments;
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::scanLineBased(const std::string& code) {
    std::vector<std::shared_ptr<Segment>> segments;
    std::istringstream stream(code);
    std::string line;
    std::string currentSegment;
    SegmentType currentType = SegmentType::UNKNOWN;
    
    while (std::getline(stream, line)) {
        auto lineType = detectLineType(line);
        
        if (lineType != currentType && !currentSegment.empty()) {
            // 类型改变，保存当前段
            segments.push_back(createSegment(currentType, currentSegment));
            currentSegment.clear();
        }
        
        currentType = lineType;
        currentSegment += line + "\n";
    }
    
    // 保存最后一段
    if (!currentSegment.empty()) {
        segments.push_back(createSegment(currentType, currentSegment));
    }
    
    return segments;
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::scanBlockBased(const std::string& code) {
    // 基于块的扫描（如函数、类等）
    std::vector<std::shared_ptr<Segment>> segments;
    
    // 简单实现：寻找大括号平衡的块
    size_t pos = 0;
    while (pos < code.length()) {
        size_t blockStart = pos;
        size_t blockEnd = findBlockEnd(code, pos);
        
        if (blockEnd > blockStart) {
            std::string blockCode = code.substr(blockStart, blockEnd - blockStart);
            auto type = detectSegmentType(blockCode);
            segments.push_back(createSegment(type, blockCode));
            pos = blockEnd;
        } else {
            pos++;
        }
    }
    
    return segments;
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::scanHybrid(const std::string& code) {
    // 混合策略：结合语法和块扫描
    auto syntaxSegments = scanSyntaxBased(code);
    std::vector<std::shared_ptr<Segment>> finalSegments;
    
    for (const auto& segment : syntaxSegments) {
        if (segment->getContent().length() > config_.maxSegmentSize) {
            // 大段进一步分割
            auto subSegments = splitLargeSegment(segment);
            finalSegments.insert(finalSegments.end(), subSegments.begin(), subSegments.end());
        } else {
            finalSegments.push_back(segment);
        }
    }
    
    return finalSegments;
}

std::vector<BridgeScanner::BoundaryInfo> BridgeScanner::findBoundaries(const std::string& code) {
    std::vector<BoundaryInfo> boundaries;
    bool inChtlSyntax = false;
    size_t pos = 0;
    
    while (pos < code.length()) {
        char c = code[pos];
        
        // 使用状态机检测CHTL语法
        if (chtlJsState_) {
            chtlJsState_->handleChar(c);
        }
        
        // 检测CHTL选择器开始 {{
        if (!inChtlSyntax && pos + 1 < code.length() && 
            c == '{' && code[pos + 1] == '{') {
            // 确保不是模板字符串
            if (!isInTemplateString(code, pos)) {
                inChtlSyntax = true;
                BoundaryInfo boundary;
                boundary.position = pos;
                boundary.type = SegmentType::JAVASCRIPT;
                boundary.reason = "CHTL selector start";
                boundaries.push_back(boundary);
                pos += 2;
                continue;
            }
        }
        
        // 检测CHTL选择器结束 }}
        else if (inChtlSyntax && pos + 1 < code.length() && 
                 c == '}' && code[pos + 1] == '}') {
            pos += 2;
            BoundaryInfo boundary;
            boundary.position = pos;
            boundary.type = SegmentType::CHTL_JAVASCRIPT;
            boundary.reason = "CHTL selector end";
            boundaries.push_back(boundary);
            inChtlSyntax = false;
            continue;
        }
        
        // 检测CHTL方法调用 ->
        else if (!inChtlSyntax && pos + 1 < code.length() && 
                 c == '-' && code[pos + 1] == '>') {
            // 确保是CHTL方法调用，不是箭头函数
            if (isChtlMethodCall(code, pos)) {
                BoundaryInfo boundary;
                boundary.position = pos;
                boundary.type = SegmentType::JAVASCRIPT;
                boundary.reason = "CHTL method call";
                boundaries.push_back(boundary);
                
                // 标记方法调用区域
                size_t methodEnd = findMethodCallEnd(code, pos + 2);
                if (methodEnd > pos + 2) {
                    BoundaryInfo endBoundary;
                    endBoundary.position = methodEnd;
                    endBoundary.type = SegmentType::CHTL_JAVASCRIPT;
                    endBoundary.reason = "CHTL method call end";
                    boundaries.push_back(endBoundary);
                }
            }
        }
        
        pos++;
    }
    
    // 确保最后的边界
    if (!boundaries.empty()) {
        auto lastBoundary = boundaries.back();
        if (lastBoundary.position < code.length()) {
            BoundaryInfo finalBoundary;
            finalBoundary.position = code.length();
            finalBoundary.type = inChtlSyntax ? SegmentType::CHTL_JAVASCRIPT : SegmentType::JAVASCRIPT;
            finalBoundary.reason = "End of code";
            boundaries.push_back(finalBoundary);
        }
    }
    
    return boundaries;
}

SegmentType BridgeScanner::detectSegmentType(const std::string& code) {
    // 简单检测：如果包含CHTL特定语法，则为CHTL_JAVASCRIPT
    if (code.find("{{") != std::string::npos && code.find("}}") != std::string::npos) {
        return SegmentType::CHTL_JAVASCRIPT;
    }
    
    if (code.find("->") != std::string::npos) {
        // 需要更精确的检测，避免箭头函数误判
        if (hasChtlMethodCall(code)) {
            return SegmentType::CHTL_JAVASCRIPT;
        }
    }
    
    return SegmentType::JAVASCRIPT;
}

SegmentType BridgeScanner::detectLineType(const std::string& line) {
    // 基于行的类型检测
    std::string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);
    
    if (trimmed.find("{{") != std::string::npos) {
        return SegmentType::MIXED;
    }
    if (trimmed.find("->") != std::string::npos && hasChtlMethodCall(trimmed)) {
        return SegmentType::CHTL_JAVASCRIPT;
    }
    
    return SegmentType::JAVASCRIPT;
}

std::shared_ptr<Segment> BridgeScanner::createSegment(SegmentType type, const std::string& content) {
    return SegmentFactory::create(type, content);
}

bool BridgeScanner::isChtlMethodCall(const std::string& code, size_t pos) {
    if (pos == 0 || pos + 1 >= code.length()) return false;
    
    // 检查前面是否是有效的表达式结束
    size_t prevPos = pos - 1;
    while (prevPos > 0 && std::isspace(code[prevPos])) {
        prevPos--;
    }
    
    char prevChar = code[prevPos];
    // 有效的前导字符：标识符、), ], }
    if (!std::isalnum(prevChar) && prevChar != '_' && prevChar != '$' &&
        prevChar != ')' && prevChar != ']' && prevChar != '}') {
        return false;
    }
    
    // 检查后面是否是方法名
    size_t nextPos = pos + 2;
    while (nextPos < code.length() && std::isspace(code[nextPos])) {
        nextPos++;
    }
    
    if (nextPos >= code.length() || !std::isalpha(code[nextPos])) {
        return false;
    }
    
    return true;
}

bool BridgeScanner::hasChtlMethodCall(const std::string& code) {
    size_t pos = 0;
    while ((pos = code.find("->", pos)) != std::string::npos) {
        if (isChtlMethodCall(code, pos)) {
            return true;
        }
        pos += 2;
    }
    return false;
}

bool BridgeScanner::isInTemplateString(const std::string& code, size_t pos) {
    // 简单检测：计算反引号数量
    int backtickCount = 0;
    for (size_t i = 0; i < pos && i < code.length(); i++) {
        if (code[i] == '`') {
            // 检查是否被转义
            if (i == 0 || code[i-1] != '\\') {
                backtickCount++;
            }
        }
    }
    return backtickCount % 2 == 1;
}

size_t BridgeScanner::findMethodCallEnd(const std::string& code, size_t start) {
    // 找到方法调用的结束位置
    size_t pos = start;
    
    // 跳过方法名
    while (pos < code.length() && (std::isalnum(code[pos]) || code[pos] == '_')) {
        pos++;
    }
    
    // 跳过空格
    while (pos < code.length() && std::isspace(code[pos])) {
        pos++;
    }
    
    // 如果有括号，找到匹配的右括号
    if (pos < code.length() && code[pos] == '(') {
        int parenCount = 1;
        pos++;
        while (pos < code.length() && parenCount > 0) {
            if (code[pos] == '(') parenCount++;
            else if (code[pos] == ')') parenCount--;
            pos++;
        }
    }
    
    return pos;
}

size_t BridgeScanner::findBlockEnd(const std::string& code, size_t start) {
    // 找到代码块的结束位置
    int braceCount = 0;
    bool inString = false;
    bool inComment = false;
    char stringChar = 0;
    
    for (size_t i = start; i < code.length(); i++) {
        char c = code[i];
        char next = (i + 1 < code.length()) ? code[i + 1] : 0;
        
        // 处理注释
        if (!inString && !inComment && c == '/' && next == '/') {
            // 单行注释，跳到行尾
            while (i < code.length() && code[i] != '\n') {
                i++;
            }
            continue;
        }
        if (!inString && !inComment && c == '/' && next == '*') {
            inComment = true;
            i++;
            continue;
        }
        if (inComment && c == '*' && next == '/') {
            inComment = false;
            i++;
            continue;
        }
        
        if (inComment) continue;
        
        // 处理字符串
        if (!inString && (c == '"' || c == '\'' || c == '`')) {
            inString = true;
            stringChar = c;
        } else if (inString && c == stringChar && (i == 0 || code[i-1] != '\\')) {
            inString = false;
            stringChar = 0;
        }
        
        if (inString) continue;
        
        // 计算大括号
        if (c == '{') {
            braceCount++;
        } else if (c == '}') {
            braceCount--;
            if (braceCount == 0 && i > start) {
                return i + 1;
            }
        }
    }
    
    return code.length();
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitMixedSegment(std::shared_ptr<MixedSegment> mixed) {
    if (!mixed) return {};
    
    // 如果已经有子段，直接返回
    if (!mixed->getSubSegments().empty()) {
        return mixed->getSubSegments();
    }
    
    // 否则，分析并分割
    return scanSyntaxBased(mixed->getContent());
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitLargeSegment(std::shared_ptr<Segment> segment) {
    if (!segment) return {};
    
    std::vector<std::shared_ptr<Segment>> result;
    const std::string& content = segment->getContent();
    const size_t maxSize = config_.maxSegmentSize;
    
    if (content.length() <= maxSize) {
        result.push_back(segment);
        return result;
    }
    
    // 按语法边界分割
    size_t start = 0;
    while (start < content.length()) {
        size_t end = std::min(start + maxSize, content.length());
        
        // 尝试在语法边界处分割
        if (end < content.length()) {
            // 寻找最近的语句结束
            size_t boundaryPos = findNearestBoundary(content, end);
            if (boundaryPos > start && boundaryPos < end + maxSize / 4) {
                end = boundaryPos;
            }
        }
        
        std::string subContent = content.substr(start, end - start);
        result.push_back(createSegment(segment->getType(), subContent));
        start = end;
    }
    
    return result;
}

size_t BridgeScanner::findNearestBoundary(const std::string& code, size_t pos) {
    // 向后查找最近的语句边界
    for (size_t i = pos; i < std::min(pos + 1000, code.length()); i++) {
        if (code[i] == ';' || code[i] == '\n') {
            // 确保不在字符串中
            if (!isInString(code, i)) {
                return i + 1;
            }
        }
    }
    
    // 向前查找
    for (size_t i = pos; i > 0 && i > pos - 1000; i--) {
        if (code[i] == ';' || code[i] == '\n') {
            if (!isInString(code, i)) {
                return i + 1;
            }
        }
    }
    
    return pos;
}

bool BridgeScanner::isInString(const std::string& code, size_t pos) {
    // 简单的字符串检测
    bool inSingle = false;
    bool inDouble = false;
    bool inTemplate = false;
    
    for (size_t i = 0; i < pos && i < code.length(); i++) {
        char c = code[i];
        if (i > 0 && code[i-1] == '\\') continue;
        
        if (c == '\'' && !inDouble && !inTemplate) inSingle = !inSingle;
        else if (c == '"' && !inSingle && !inTemplate) inDouble = !inDouble;
        else if (c == '`' && !inSingle && !inDouble) inTemplate = !inTemplate;
    }
    
    return inSingle || inDouble || inTemplate;
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::optimizeSegments(
    const std::vector<std::shared_ptr<Segment>>& segments) {
    
    if (!config_.enableOptimization || segments.size() < 2) {
        return segments;
    }
    
    std::vector<std::shared_ptr<Segment>> optimized;
    std::shared_ptr<Segment> current = nullptr;
    
    for (const auto& segment : segments) {
        if (!current) {
            current = segment;
            continue;
        }
        
        // 尝试合并相同类型的小段
        if (current->getType() == segment->getType() &&
            current->getContent().length() + segment->getContent().length() < config_.maxSegmentSize / 2) {
            // 合并
            std::string combined = current->getContent() + segment->getContent();
            current = createSegment(current->getType(), combined);
        } else {
            optimized.push_back(current);
            current = segment;
        }
    }
    
    if (current) {
        optimized.push_back(current);
    }
    
    return optimized;
}

} // namespace chtl