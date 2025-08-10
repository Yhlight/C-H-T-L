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
    
    // 精准切割：分离JS和CHTL-JS代码
    std::vector<std::shared_ptr<Segment>> segments = preciseSplit(code);
    
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

std::vector<std::shared_ptr<Segment>> BridgeScanner::preciseSplit(const std::string& code) {
    std::vector<std::shared_ptr<Segment>> segments;
    size_t pos = 0;
    size_t codeStart = 0;
    
    while (pos < code.length()) {
        // 查找下一个CHTL-JS语法的起始位置
        ChtlJsMatch match = findNextChtlJs(code, pos);
        
        if (match.found) {
            // 1. 保存match之前的纯JS代码
            if (match.start > codeStart) {
                std::string jsCode = code.substr(codeStart, match.start - codeStart);
                if (!jsCode.empty() && !isOnlyWhitespace(jsCode)) {
                    segments.push_back(createSegment(SegmentType::JAVASCRIPT, jsCode));
                }
            }
            
            // 2. 提取CHTL-JS特定语法
            std::string chtlJsCode = code.substr(match.start, match.end - match.start);
            segments.push_back(createSegment(SegmentType::CHTL_JAVASCRIPT, chtlJsCode));
            
            // 3. 更新位置
            pos = match.end;
            codeStart = match.end;
        } else {
            // 没有更多CHTL-JS语法，保存剩余的JS代码
            if (codeStart < code.length()) {
                std::string jsCode = code.substr(codeStart);
                if (!jsCode.empty() && !isOnlyWhitespace(jsCode)) {
                    segments.push_back(createSegment(SegmentType::JAVASCRIPT, jsCode));
                }
            }
            break;
        }
    }
    
    return segments;
}

BridgeScanner::ChtlJsMatch BridgeScanner::findNextChtlJs(const std::string& code, size_t startPos) {
    ChtlJsMatch match;
    match.found = false;
    match.start = std::string::npos;
    match.end = std::string::npos;
    
    size_t minPos = std::string::npos;
    
    // 1. 查找CHTL选择器 {{...}}
    size_t selectorPos = findChtlSelector(code, startPos);
    if (selectorPos != std::string::npos && selectorPos < minPos) {
        minPos = selectorPos;
        match.type = ChtlJsType::SELECTOR;
    }
    
    // 2. 查找CHTL方法调用 ->method()
    size_t methodPos = findChtlMethod(code, startPos);
    if (methodPos != std::string::npos && methodPos < minPos) {
        minPos = methodPos;
        match.type = ChtlJsType::METHOD;
    }
    
    // 3. 查找CHTL特殊函数调用 listen(), delegate(), animate()
    size_t specialPos = findChtlSpecialFunction(code, startPos);
    if (specialPos != std::string::npos && specialPos < minPos) {
        minPos = specialPos;
        match.type = ChtlJsType::SPECIAL_FUNCTION;
    }
    
    if (minPos != std::string::npos) {
        match.found = true;
        match.start = minPos;
        
        // 根据类型确定结束位置
        switch (match.type) {
            case ChtlJsType::SELECTOR:
                match.end = findSelectorEnd(code, minPos);
                break;
            case ChtlJsType::METHOD:
                match.end = findMethodEnd(code, minPos);
                break;
            case ChtlJsType::SPECIAL_FUNCTION:
                match.end = findSpecialFunctionEnd(code, minPos);
                break;
        }
    }
    
    return match;
}

size_t BridgeScanner::findChtlSelector(const std::string& code, size_t startPos) {
    size_t pos = startPos;
    
    while (pos < code.length() - 1) {
        // 查找 {{
        pos = code.find("{{", pos);
        if (pos == std::string::npos) {
            return std::string::npos;
        }
        
        // 确保不在字符串或注释中
        if (!isInStringOrComment(code, pos)) {
            return pos;
        }
        
        pos += 2;
    }
    
    return std::string::npos;
}

size_t BridgeScanner::findSelectorEnd(const std::string& code, size_t startPos) {
    // 从 {{ 开始，找到匹配的 }}
    int depth = 0;
    size_t pos = startPos;
    
    while (pos < code.length()) {
        if (pos + 1 < code.length()) {
            if (code[pos] == '{' && code[pos + 1] == '{' && !isInStringOrComment(code, pos)) {
                depth++;
                pos += 2;
                continue;
            }
            if (code[pos] == '}' && code[pos + 1] == '}' && !isInStringOrComment(code, pos)) {
                depth--;
                if (depth == 0) {
                    return pos + 2;
                }
                pos += 2;
                continue;
            }
        }
        pos++;
    }
    
    return code.length();
}

size_t BridgeScanner::findChtlMethod(const std::string& code, size_t startPos) {
    size_t pos = startPos;
    
    while (pos < code.length() - 1) {
        // 查找 ->
        pos = code.find("->", pos);
        if (pos == std::string::npos) {
            return std::string::npos;
        }
        
        // 确保不是箭头函数 =>
        if (pos > 0 && code[pos - 1] == '=') {
            pos += 2;
            continue;
        }
        
        // 确保不在字符串或注释中
        if (!isInStringOrComment(code, pos)) {
            // 确保后面跟着方法名
            size_t methodStart = pos + 2;
            while (methodStart < code.length() && std::isspace(code[methodStart])) {
                methodStart++;
            }
            
            if (methodStart < code.length() && std::isalpha(code[methodStart])) {
                return pos;
            }
        }
        
        pos += 2;
    }
    
    return std::string::npos;
}

size_t BridgeScanner::findMethodEnd(const std::string& code, size_t startPos) {
    // 从 -> 开始，包含方法名和参数列表
    size_t pos = startPos + 2; // 跳过 ->
    
    // 跳过空格
    while (pos < code.length() && std::isspace(code[pos])) {
        pos++;
    }
    
    // 读取方法名
    while (pos < code.length() && (std::isalnum(code[pos]) || code[pos] == '_')) {
        pos++;
    }
    
    // 跳过空格
    while (pos < code.length() && std::isspace(code[pos])) {
        pos++;
    }
    
    // 如果有参数列表，包含整个参数列表
    if (pos < code.length() && code[pos] == '(') {
        int parenDepth = 0;
        while (pos < code.length()) {
            if (code[pos] == '(' && !isInStringOrComment(code, pos)) {
                parenDepth++;
            } else if (code[pos] == ')' && !isInStringOrComment(code, pos)) {
                parenDepth--;
                if (parenDepth == 0) {
                    return pos + 1;
                }
            }
            pos++;
        }
    }
    
    return pos;
}

size_t BridgeScanner::findChtlSpecialFunction(const std::string& code, size_t startPos) {
    // CHTL特殊函数：listen, delegate, animate
    static const std::vector<std::string> specialFunctions = {
        "listen", "delegate", "animate"
    };
    
    size_t minPos = std::string::npos;
    
    for (const auto& func : specialFunctions) {
        size_t pos = startPos;
        while ((pos = code.find(func, pos)) != std::string::npos) {
            // 检查是否是独立的函数调用（不是方法调用）
            bool isStandalone = true;
            
            // 检查前面是否有 . 或 ->
            if (pos > 0) {
                char prevChar = code[pos - 1];
                if (prevChar == '.' || (pos > 1 && code[pos - 2] == '-' && code[pos - 1] == '>')) {
                    isStandalone = false;
                }
            }
            
            // 检查后面是否有 (
            size_t afterFunc = pos + func.length();
            while (afterFunc < code.length() && std::isspace(code[afterFunc])) {
                afterFunc++;
            }
            
            if (isStandalone && afterFunc < code.length() && code[afterFunc] == '(' &&
                !isInStringOrComment(code, pos)) {
                if (pos < minPos) {
                    minPos = pos;
                }
                break;
            }
            
            pos += func.length();
        }
    }
    
    return minPos;
}

size_t BridgeScanner::findSpecialFunctionEnd(const std::string& code, size_t startPos) {
    // 包含函数名和整个参数列表
    size_t pos = startPos;
    
    // 跳过函数名
    while (pos < code.length() && (std::isalpha(code[pos]) || code[pos] == '_')) {
        pos++;
    }
    
    // 跳过空格
    while (pos < code.length() && std::isspace(code[pos])) {
        pos++;
    }
    
    // 包含参数列表
    if (pos < code.length() && code[pos] == '(') {
        int parenDepth = 0;
        while (pos < code.length()) {
            if (code[pos] == '(' && !isInStringOrComment(code, pos)) {
                parenDepth++;
            } else if (code[pos] == ')' && !isInStringOrComment(code, pos)) {
                parenDepth--;
                if (parenDepth == 0) {
                    return pos + 1;
                }
            }
            pos++;
        }
    }
    
    return pos;
}

bool BridgeScanner::isInStringOrComment(const std::string& code, size_t pos) {
    // 简化版本：检查是否在字符串或注释中
    bool inSingleQuote = false;
    bool inDoubleQuote = false;
    bool inTemplate = false;
    bool inSingleLineComment = false;
    bool inMultiLineComment = false;
    
    for (size_t i = 0; i < pos && i < code.length(); i++) {
        char c = code[i];
        char next = (i + 1 < code.length()) ? code[i + 1] : '\0';
        
        // 处理转义字符
        if (i > 0 && code[i - 1] == '\\') {
            continue;
        }
        
        // 处理注释
        if (!inSingleQuote && !inDoubleQuote && !inTemplate) {
            if (c == '/' && next == '/' && !inMultiLineComment) {
                inSingleLineComment = true;
                i++;
                continue;
            }
            if (c == '/' && next == '*' && !inSingleLineComment) {
                inMultiLineComment = true;
                i++;
                continue;
            }
            if (c == '*' && next == '/' && inMultiLineComment) {
                inMultiLineComment = false;
                i++;
                continue;
            }
        }
        
        // 处理换行（结束单行注释）
        if (c == '\n') {
            inSingleLineComment = false;
        }
        
        // 如果在注释中，跳过字符串检测
        if (inSingleLineComment || inMultiLineComment) {
            continue;
        }
        
        // 处理字符串
        if (c == '\'' && !inDoubleQuote && !inTemplate) {
            inSingleQuote = !inSingleQuote;
        } else if (c == '"' && !inSingleQuote && !inTemplate) {
            inDoubleQuote = !inDoubleQuote;
        } else if (c == '`' && !inSingleQuote && !inDoubleQuote) {
            inTemplate = !inTemplate;
        }
    }
    
    return inSingleQuote || inDoubleQuote || inTemplate || 
           inSingleLineComment || inMultiLineComment;
}

bool BridgeScanner::isOnlyWhitespace(const std::string& str) {
    return str.find_first_not_of(" \t\n\r") == std::string::npos;
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
            
        default:
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

std::shared_ptr<Segment> BridgeScanner::createSegment(SegmentType type, const std::string& content) {
    return SegmentFactory::createSegment(type, content);
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::optimizeSegments(
    const std::vector<std::shared_ptr<Segment>>& segments) {
    
    if (!config_.enableOptimization || segments.size() < 2) {
        return segments;
    }
    
    std::vector<std::shared_ptr<Segment>> optimized;
    std::shared_ptr<Segment> currentJs = nullptr;
    
    for (const auto& segment : segments) {
        if (segment->getType() == SegmentType::JAVASCRIPT) {
            if (!currentJs) {
                currentJs = segment;
            } else {
                // 合并相邻的JS段
                std::string combined = currentJs->getContent() + segment->getContent();
                currentJs = createSegment(SegmentType::JAVASCRIPT, combined);
            }
        } else {
            // CHTL-JS段不合并，保持精准
            if (currentJs) {
                optimized.push_back(currentJs);
                currentJs = nullptr;
            }
            optimized.push_back(segment);
        }
    }
    
    if (currentJs) {
        optimized.push_back(currentJs);
    }
    
    return optimized;
}

} // namespace chtl