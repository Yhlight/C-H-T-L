#include "Scanner/BridgeScanner.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace chtl {

BridgeScanner::BridgeScanner() 
    : config_() {
    scanState_.currentLine = 1;
    scanState_.currentColumn = 1;
    scanState_.currentMode = ScanMode::AUTO;
    scanState_.inChtlBlock = false;
}

bool BridgeScanner::initialize(std::shared_ptr<BasicLexer> lexer,
                             std::shared_ptr<BasicContext> context) {
    lexer_ = lexer;
    context_ = context;
    
    // 初始化CHTL-JS状态机
    chtlJsState_ = std::make_shared<ChtlJsState>();
    
    return true;
}

BridgeScanner::ScanResult BridgeScanner::scan(const std::string& code, 
                                             const std::string& filename) {
    ScanResult result;
    scanState_.currentFile = filename;
    codeBuffer_ = code;
    
    try {
        // 分割代码
        result.segments = splitCode(code);
        
        // 分发到相应的处理器
        dispatchAll(result.segments);
        
    } catch (const std::exception& e) {
        result.success = false;
        result.errors.push_back("Scanner error: " + std::string(e.what()));
    }
    
    return result;
}

BridgeScanner::ScanResult BridgeScanner::scanFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        ScanResult result;
        result.success = false;
        result.errors.push_back("Failed to open file: " + filename);
        return result;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    return scan(buffer.str(), filename);
}

void BridgeScanner::clearHandlers() {
    jsHandlers_.clear();
    chtlJsHandlers_.clear();
    errorHandler_ = nullptr;
}

void BridgeScanner::dispatch(std::shared_ptr<Segment> segment) {
    if (!segment) return;
    
    switch (segment->getType()) {
        case SegmentType::JavaScript:
            for (auto& handler : jsHandlers_) {
                handler(segment);
            }
            break;
            
        case SegmentType::ChtlJavaScript:
            for (auto& handler : chtlJsHandlers_) {
                handler(segment);
            }
            break;
            
        case SegmentType::Mixed:
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

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitCode(const std::string& code) {
    switch (config_.strategy) {
        case SplitStrategy::SYNTAX_BASED:
            return splitBySyntax(code);
        case SplitStrategy::LINE_BASED:
            return splitByLines(code);
        case SplitStrategy::BLOCK_BASED:
            return splitByBlocks(code);
        case SplitStrategy::HYBRID:
        default:
            return splitHybrid(code);
    }
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitBySyntax(const std::string& code) {
    std::vector<std::shared_ptr<Segment>> segments;
    
    // 使用状态机扫描代码
    chtlJsState_->reset();
    
    size_t start = 0;
    size_t current = 0;
    bool inChtlSyntax = false;
    std::vector<BlockBoundary> boundaries;
    
    // 逐字符扫描
    for (size_t i = 0; i < code.length(); ++i) {
        char c = code[i];
        chtlJsState_->processChar(c);
        
        // 检测CHTL语法边界
        if (!inChtlSyntax && chtlJsState_->isInChtlSelector()) {
            // 进入CHTL选择器
            if (i > start) {
                BlockBoundary boundary;
                boundary.start = start;
                boundary.end = i - 1;  // {{ 之前
                boundary.type = SegmentType::JavaScript;
                boundary.reason = "Before CHTL selector";
                boundaries.push_back(boundary);
            }
            start = i - 1;  // 包含 {{
            inChtlSyntax = true;
        } else if (inChtlSyntax && !chtlJsState_->isInChtlSelector() && 
                   !chtlJsState_->isInChtlMethod()) {
            // 离开CHTL语法
            BlockBoundary boundary;
            boundary.start = start;
            boundary.end = i;
            boundary.type = SegmentType::ChtlJavaScript;
            boundary.reason = "CHTL syntax block";
            boundaries.push_back(boundary);
            start = i + 1;
            inChtlSyntax = false;
        }
        
        // 检测animate调用
        if (i >= 7 && code.substr(i - 7, 7) == "animate" && 
            (i + 1 < code.length() && code[i + 1] == '(')) {
            if (!inChtlSyntax && i - 7 > start) {
                BlockBoundary boundary;
                boundary.start = start;
                boundary.end = i - 8;
                boundary.type = SegmentType::JavaScript;
                boundary.reason = "Before animate call";
                boundaries.push_back(boundary);
            }
            start = i - 7;
            inChtlSyntax = true;
        }
    }
    
    // 处理最后一段
    if (start < code.length()) {
        BlockBoundary boundary;
        boundary.start = start;
        boundary.end = code.length() - 1;
        boundary.type = inChtlSyntax ? SegmentType::ChtlJavaScript : SegmentType::JavaScript;
        boundary.reason = "End of code";
        boundaries.push_back(boundary);
    }
    
    // 创建段
    for (const auto& boundary : boundaries) {
        auto segment = createSegmentFromBoundary(code, boundary);
        if (segment) {
            segments.push_back(segment);
        }
    }
    
    return segments;
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitHybrid(const std::string& code) {
    // 混合策略：结合语法和启发式方法
    auto syntaxSegments = splitBySyntax(code);
    
    // 对每个段进行进一步检查
    std::vector<std::shared_ptr<Segment>> refinedSegments;
    
    for (const auto& segment : syntaxSegments) {
        // 如果段太大，考虑进一步分割
        if (segment->getCode().length() > config_.maxSegmentSize) {
            auto subSegments = splitLargeSegment(segment);
            refinedSegments.insert(refinedSegments.end(), 
                                 subSegments.begin(), 
                                 subSegments.end());
        } else {
            refinedSegments.push_back(segment);
        }
    }
    
    return refinedSegments;
}

bool BridgeScanner::isChtlSyntax(const std::string& code, size_t pos) {
    // 检查CHTL选择器 {{
    if (pos + 1 < code.length() && code[pos] == '{' && code[pos + 1] == '{') {
        return true;
    }
    
    // 检查CHTL箭头 ->
    if (pos > 0 && code[pos - 1] == '-' && code[pos] == '>') {
        // 确保不是箭头函数
        return !isArrowFunction(code, pos);
    }
    
    // 检查animate函数
    if (pos + 7 < code.length() && code.substr(pos, 7) == "animate") {
        return isAnimateCall(code, pos);
    }
    
    return false;
}

SegmentType BridgeScanner::detectSegmentType(const std::string& code) {
    bool hasJavaScript = false;
    bool hasChtlJs = false;
    
    // 快速扫描特征
    if (code.find("{{") != std::string::npos) {
        hasChtlJs = true;
    }
    
    if (code.find("->") != std::string::npos) {
        // 需要更精确的检查
        size_t pos = 0;
        while ((pos = code.find("->", pos)) != std::string::npos) {
            if (!isArrowFunction(code, pos + 1)) {
                hasChtlJs = true;
                break;
            }
            pos += 2;
        }
    }
    
    if (code.find("animate(") != std::string::npos ||
        code.find("animate (") != std::string::npos) {
        hasChtlJs = true;
    }
    
    // 检查标准JavaScript特征
    if (code.find("function") != std::string::npos ||
        code.find("var ") != std::string::npos ||
        code.find("let ") != std::string::npos ||
        code.find("const ") != std::string::npos) {
        hasJavaScript = true;
    }
    
    if (hasChtlJs && hasJavaScript) {
        return SegmentType::Mixed;
    } else if (hasChtlJs) {
        return SegmentType::ChtlJavaScript;
    } else {
        return SegmentType::JavaScript;
    }
}

std::shared_ptr<Segment> BridgeScanner::createSegmentFromBoundary(
    const std::string& code, 
    const BlockBoundary& boundary) {
    
    std::string segmentCode = code.substr(boundary.start, 
                                        boundary.end - boundary.start + 1);
    
    std::shared_ptr<Segment> segment;
    
    switch (boundary.type) {
        case SegmentType::JavaScript:
            segment = std::make_shared<JavaScriptSegment>(segmentCode);
            break;
            
        case SegmentType::ChtlJavaScript:
            segment = std::make_shared<ChtlJavaScriptSegment>(segmentCode);
            break;
            
        case SegmentType::Mixed:
            segment = std::make_shared<MixedSegment>(segmentCode);
            break;
    }
    
    if (segment) {
        // 计算行列信息
        int startLine = 1, startCol = 1;
        int endLine = 1, endCol = 1;
        
        for (size_t i = 0; i < boundary.start; ++i) {
            if (code[i] == '\n') {
                startLine++;
                startCol = 1;
            } else {
                startCol++;
            }
        }
        
        endLine = startLine;
        endCol = startCol;
        
        for (size_t i = boundary.start; i <= boundary.end; ++i) {
            if (code[i] == '\n') {
                endLine++;
                endCol = 1;
            } else {
                endCol++;
            }
        }
        
        updateSourceInfo(segment, startLine, startCol, endLine, endCol);
    }
    
    return segment;
}

void BridgeScanner::updateSourceInfo(std::shared_ptr<Segment> segment,
                                   int startLine, int startCol,
                                   int endLine, int endCol) {
    if (!segment) return;
    
    segment->setSourceInfo(scanState_.currentFile, startLine, startCol, endLine, endCol);
}

void BridgeScanner::reportError(const std::string& error) {
    if (errorHandler_) {
        errorHandler_(error);
    }
}

void BridgeScanner::reportWarning(const std::string& warning) {
    // 可以有单独的警告处理器
    if (errorHandler_) {
        errorHandler_("Warning: " + warning);
    }
}

// CHTL特性检测实现
bool BridgeScanner::hasChtlSelector(const std::string& code) {
    return code.find("{{") != std::string::npos;
}

bool BridgeScanner::hasChtlArrowOperator(const std::string& code) {
    size_t pos = 0;
    while ((pos = code.find("->", pos)) != std::string::npos) {
        if (!isArrowFunction(code, pos + 1)) {
            return true;
        }
        pos += 2;
    }
    return false;
}

bool BridgeScanner::hasChtlListen(const std::string& code) {
    return code.find("->listen") != std::string::npos;
}

bool BridgeScanner::hasChtlDelegate(const std::string& code) {
    return code.find("->delegate") != std::string::npos;
}

bool BridgeScanner::hasChtlAnimate(const std::string& code) {
    return code.find("animate(") != std::string::npos;
}

// 辅助函数
bool BridgeScanner::isArrowFunction(const std::string& code, size_t arrowPos) {
    // 检查是否是箭头函数 =>
    if (arrowPos > 0 && code[arrowPos - 1] == '=' && code[arrowPos] == '>') {
        return true;
    }
    return false;
}

bool BridgeScanner::isAnimateCall(const std::string& code, size_t pos) {
    // animate前面应该没有对象或this
    if (pos > 0) {
        char prev = code[pos - 1];
        if (prev == '.' || prev == '>') {
            return false;  // object.animate 或 ->animate
        }
    }
    
    // 后面应该有括号
    size_t nextPos = pos + 7;
    while (nextPos < code.length() && std::isspace(code[nextPos])) {
        nextPos++;
    }
    
    return nextPos < code.length() && code[nextPos] == '(';
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitMixedSegment(
    std::shared_ptr<MixedSegment> mixed) {
    
    // 对混合段进行更细粒度的分割
    return splitBySyntax(mixed->getCode());
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitLargeSegment(
    std::shared_ptr<Segment> segment) {
    
    // 对大段进行分割
    std::vector<std::shared_ptr<Segment>> result;
    
    // 简单策略：按函数边界分割
    // TODO: 实现更智能的分割策略
    
    result.push_back(segment);
    return result;
}

} // namespace chtl