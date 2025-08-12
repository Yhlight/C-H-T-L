#include "BridgeScanner.h"
#include <sstream>
#include <regex>

namespace CHTL {

BridgeScanner::BridgeScanner() 
    : currentLine_(1), currentColumn_(1), debugMode_(false) {
    currentContext_.state = ScanState::CHTL;
    currentContext_.braceCount = 0;
    currentContext_.startLine = 1;
    currentContext_.startColumn = 1;
}

std::vector<SegmentPtr> BridgeScanner::scan(const std::string& content) {
    std::vector<SegmentPtr> segments;
    errors_.clear();
    
    // 重置状态
    currentLine_ = 1;
    currentColumn_ = 1;
    while (!contextStack_.empty()) {
        contextStack_.pop();
    }
    currentContext_.state = ScanState::CHTL;
    currentContext_.braceCount = 0;
    currentContext_.startLine = 1;
    currentContext_.startColumn = 1;
    
    // 开始扫描
    scanCHTL(content, segments);
    
    return segments;
}

void BridgeScanner::scanCHTL(const std::string& content, std::vector<SegmentPtr>& segments) {
    size_t pos = 0;
    size_t lastPos = 0;
    
    while (pos < content.length()) {
        // 检查各种块的开始
        if (isStyleBlock(content, pos)) {
            // 保存之前的CHTL内容
            if (pos > lastPos) {
                std::string chtlContent = content.substr(lastPos, pos - lastPos);
                if (!chtlContent.empty()) {
                    auto segment = createSegment(LanguageType::CHTL, chtlContent,
                                               currentContext_.startLine, currentContext_.startColumn,
                                               currentLine_, currentColumn_);
                    segments.push_back(segment);
                }
            }
            
            // 扫描style块
            scanStyleBlock(content, pos, segments);
            lastPos = pos;
        }
        else if (isScriptBlock(content, pos)) {
            // 保存之前的CHTL内容
            if (pos > lastPos) {
                std::string chtlContent = content.substr(lastPos, pos - lastPos);
                if (!chtlContent.empty()) {
                    auto segment = createSegment(LanguageType::CHTL, chtlContent,
                                               currentContext_.startLine, currentContext_.startColumn,
                                               currentLine_, currentColumn_);
                    segments.push_back(segment);
                }
            }
            
            // 扫描script块
            scanScriptBlock(content, pos, segments);
            lastPos = pos;
        }
        else if (isOriginBlock(content, pos)) {
            // 保存之前的CHTL内容
            if (pos > lastPos) {
                std::string chtlContent = content.substr(lastPos, pos - lastPos);
                if (!chtlContent.empty()) {
                    auto segment = createSegment(LanguageType::CHTL, chtlContent,
                                               currentContext_.startLine, currentContext_.startColumn,
                                               currentLine_, currentColumn_);
                    segments.push_back(segment);
                }
            }
            
            // 扫描origin块
            scanOriginBlock(content, pos, segments);
            lastPos = pos;
        }
        else {
            // 更新位置
            updatePosition(content[pos], currentLine_, currentColumn_);
            pos++;
        }
    }
    
    // 保存最后的CHTL内容
    if (lastPos < content.length()) {
        std::string chtlContent = content.substr(lastPos);
        if (!chtlContent.empty()) {
            auto segment = createSegment(LanguageType::CHTL, chtlContent,
                                       currentContext_.startLine, currentContext_.startColumn,
                                       currentLine_, currentColumn_);
            segments.push_back(segment);
        }
    }
}

void BridgeScanner::scanStyleBlock(const std::string& content, size_t& pos, std::vector<SegmentPtr>& segments) {
    // 记录style块的开始位置
    int startLine = currentLine_;
    int startColumn = currentColumn_;
    
    // 跳过 "style" 关键字
    pos += 5;
    updatePosition(content.substr(pos - 5, 5), currentLine_, currentColumn_);
    
    // 跳过空白
    skipWhitespace(content, pos);
    
    // 期望 '{'
    if (pos >= content.length() || content[pos] != '{') {
        addError("期望 '{' 在 'style' 之后", currentLine_, currentColumn_);
        return;
    }
    
    pos++; // 跳过 '{'
    updatePosition('{', currentLine_, currentColumn_);
    
    // 提取style内容直到找到匹配的 '}'
    int braceCount = 1;
    size_t contentStart = pos;
    
    while (pos < content.length() && braceCount > 0) {
        if (content[pos] == '{') {
            braceCount++;
        } else if (content[pos] == '}') {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        updatePosition(content[pos], currentLine_, currentColumn_);
        pos++;
    }
    
    if (braceCount > 0) {
        addError("未闭合的 style 块", startLine, startColumn);
        return;
    }
    
    // 提取CSS内容
    std::string cssContent = content.substr(contentStart, pos - contentStart);
    
    // 创建CSS段
    auto segment = createSegment(LanguageType::CSS, cssContent,
                                startLine, startColumn, currentLine_, currentColumn_);
    segment->setContext("style");
    segments.push_back(segment);
    
    // 跳过 '}'
    if (pos < content.length()) {
        pos++;
        updatePosition('}', currentLine_, currentColumn_);
    }
}

void BridgeScanner::scanScriptBlock(const std::string& content, size_t& pos, std::vector<SegmentPtr>& segments) {
    // 记录script块的开始位置
    int startLine = currentLine_;
    int startColumn = currentColumn_;
    
    // 跳过 "script" 关键字
    pos += 6;
    updatePosition(content.substr(pos - 6, 6), currentLine_, currentColumn_);
    
    // 跳过空白
    skipWhitespace(content, pos);
    
    // 期望 '{'
    if (pos >= content.length() || content[pos] != '{') {
        addError("期望 '{' 在 'script' 之后", currentLine_, currentColumn_);
        return;
    }
    
    pos++; // 跳过 '{'
    updatePosition('{', currentLine_, currentColumn_);
    
    // 提取script内容直到找到匹配的 '}'
    int braceCount = 1;
    size_t contentStart = pos;
    
    while (pos < content.length() && braceCount > 0) {
        if (content[pos] == '{') {
            braceCount++;
        } else if (content[pos] == '}') {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        updatePosition(content[pos], currentLine_, currentColumn_);
        pos++;
    }
    
    if (braceCount > 0) {
        addError("未闭合的 script 块", startLine, startColumn);
        return;
    }
    
    // 提取JS内容
    std::string jsContent = content.substr(contentStart, pos - contentStart);
    
    // 检查是否包含CHTL JS扩展
    bool isCHTLJS = containsCHTLJSExtensions(jsContent);
    
    // 创建JS或CHTL JS段
    auto segment = createSegment(isCHTLJS ? LanguageType::CHTL_JAVASCRIPT : LanguageType::JAVASCRIPT,
                                jsContent, startLine, startColumn, currentLine_, currentColumn_);
    segment->setContext("script");
    segments.push_back(segment);
    
    // 跳过 '}'
    if (pos < content.length()) {
        pos++;
        updatePosition('}', currentLine_, currentColumn_);
    }
}

void BridgeScanner::scanOriginBlock(const std::string& content, size_t& pos, std::vector<SegmentPtr>& segments) {
    // 记录origin块的开始位置
    int startLine = currentLine_;
    int startColumn = currentColumn_;
    
    // 跳过 "[Origin]" 关键字
    pos += 8;
    updatePosition(content.substr(pos - 8, 8), currentLine_, currentColumn_);
    
    // 跳过空白
    skipWhitespace(content, pos);
    
    // 检查类型 (@Html, @Style, @JavaScript)
    std::string originType;
    if (content.substr(pos, 5) == "@Html") {
        originType = "Html";
        pos += 5;
        updatePosition("@Html", currentLine_, currentColumn_);
    } else if (content.substr(pos, 6) == "@Style") {
        originType = "Style";
        pos += 6;
        updatePosition("@Style", currentLine_, currentColumn_);
    } else if (content.substr(pos, 11) == "@JavaScript") {
        originType = "JavaScript";
        pos += 11;
        updatePosition("@JavaScript", currentLine_, currentColumn_);
    } else {
        addError("期望 @Html, @Style 或 @JavaScript 在 [Origin] 之后", currentLine_, currentColumn_);
        return;
    }
    
    // 跳过空白
    skipWhitespace(content, pos);
    
    // 期望 '{'
    if (pos >= content.length() || content[pos] != '{') {
        addError("期望 '{' 在原始块类型之后", currentLine_, currentColumn_);
        return;
    }
    
    pos++; // 跳过 '{'
    updatePosition('{', currentLine_, currentColumn_);
    
    // 提取原始内容直到找到匹配的 '}'
    int braceCount = 1;
    size_t contentStart = pos;
    
    while (pos < content.length() && braceCount > 0) {
        if (content[pos] == '{') {
            braceCount++;
        } else if (content[pos] == '}') {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        updatePosition(content[pos], currentLine_, currentColumn_);
        pos++;
    }
    
    if (braceCount > 0) {
        addError("未闭合的原始块", startLine, startColumn);
        return;
    }
    
    // 提取原始内容
    std::string rawContent = content.substr(contentStart, pos - contentStart);
    
    // 根据类型创建段
    LanguageType langType;
    if (originType == "Html") {
        langType = LanguageType::HTML;
    } else if (originType == "Style") {
        langType = LanguageType::CSS;
    } else {
        langType = LanguageType::JAVASCRIPT;
    }
    
    auto segment = createSegment(langType, rawContent, startLine, startColumn, currentLine_, currentColumn_);
    segment->setContext("origin:" + originType);
    segments.push_back(segment);
    
    // 跳过 '}'
    if (pos < content.length()) {
        pos++;
        updatePosition('}', currentLine_, currentColumn_);
    }
}

bool BridgeScanner::isStyleBlock(const std::string& content, size_t pos) const {
    if (pos + 5 >= content.length()) return false;
    return content.substr(pos, 5) == "style" && 
           (pos + 5 >= content.length() || isWhitespace(content[pos + 5]) || content[pos + 5] == '{');
}

bool BridgeScanner::isScriptBlock(const std::string& content, size_t pos) const {
    if (pos + 6 >= content.length()) return false;
    return content.substr(pos, 6) == "script" && 
           (pos + 6 >= content.length() || isWhitespace(content[pos + 6]) || content[pos + 6] == '{');
}

bool BridgeScanner::isOriginBlock(const std::string& content, size_t pos) const {
    if (pos + 8 >= content.length()) return false;
    return content.substr(pos, 8) == "[Origin]";
}

bool BridgeScanner::isTemplateDeclaration(const std::string& content, size_t pos) const {
    if (pos + 1 >= content.length()) return false;
    if (content[pos] != '@') return false;
    
    return content.substr(pos, 6) == "@Style" ||
           content.substr(pos, 8) == "@Element" ||
           content.substr(pos, 4) == "@Var";
}

bool BridgeScanner::isCustomDeclaration(const std::string& content, size_t pos) const {
    // Custom声明与Template声明语法相同，但在不同上下文中解释
    return isTemplateDeclaration(content, pos);
}

bool BridgeScanner::containsCHTLJSExtensions(const std::string& jsCode) const {
    // 检查CHTL JS特有的语法
    static const std::regex patterns[] = {
        std::regex(R"(\{\{[^}]+\}\})"),           // {{selector}}
        std::regex(R"(\w+\s*->\s*\w+)"),          // obj->method
        std::regex(R"(->listen\s*\()"),           // ->listen()
        std::regex(R"(->delegate\s*\()"),         // ->delegate()
        std::regex(R"(animate\s*\()"),            // animate()
    };
    
    for (const auto& pattern : patterns) {
        if (std::regex_search(jsCode, pattern)) {
            return true;
        }
    }
    
    return false;
}

bool BridgeScanner::isWhitespace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool BridgeScanner::isNewline(char c) const {
    return c == '\n' || c == '\r';
}

void BridgeScanner::updatePosition(char c, int& line, int& column) {
    if (c == '\n') {
        line++;
        column = 1;
    } else if (c == '\r') {
        // 处理 \r\n 的情况在调用处处理
    } else {
        column++;
    }
}

void BridgeScanner::updatePosition(const std::string& str, int& line, int& column) {
    for (char c : str) {
        updatePosition(c, line, column);
    }
}

void BridgeScanner::skipWhitespace(const std::string& content, size_t& pos) {
    while (pos < content.length() && isWhitespace(content[pos])) {
        updatePosition(content[pos], currentLine_, currentColumn_);
        pos++;
    }
}

std::string BridgeScanner::extractIdentifier(const std::string& content, size_t& pos) {
    size_t start = pos;
    
    // 标识符可以以字母或下划线开头
    if (pos < content.length() && (std::isalpha(content[pos]) || content[pos] == '_')) {
        pos++;
        updatePosition(content[pos - 1], currentLine_, currentColumn_);
        
        // 后续可以是字母、数字或下划线
        while (pos < content.length() && 
               (std::isalnum(content[pos]) || content[pos] == '_')) {
            updatePosition(content[pos], currentLine_, currentColumn_);
            pos++;
        }
    }
    
    return content.substr(start, pos - start);
}

std::string BridgeScanner::extractUntil(const std::string& content, size_t& pos, char delimiter) {
    size_t start = pos;
    
    while (pos < content.length() && content[pos] != delimiter) {
        updatePosition(content[pos], currentLine_, currentColumn_);
        pos++;
    }
    
    return content.substr(start, pos - start);
}

std::string BridgeScanner::extractBlock(const std::string& content, size_t& pos) {
    if (pos >= content.length() || content[pos] != '{') {
        return "";
    }
    
    size_t start = pos;
    pos++; // 跳过 '{'
    updatePosition('{', currentLine_, currentColumn_);
    
    int braceCount = 1;
    
    while (pos < content.length() && braceCount > 0) {
        if (content[pos] == '{') {
            braceCount++;
        } else if (content[pos] == '}') {
            braceCount--;
        }
        
        updatePosition(content[pos], currentLine_, currentColumn_);
        pos++;
    }
    
    return content.substr(start, pos - start);
}

int BridgeScanner::findMatchingBrace(const std::string& content, size_t startPos) const {
    if (startPos >= content.length() || content[startPos] != '{') {
        return -1;
    }
    
    int braceCount = 1;
    size_t pos = startPos + 1;
    
    while (pos < content.length() && braceCount > 0) {
        if (content[pos] == '{') {
            braceCount++;
        } else if (content[pos] == '}') {
            braceCount--;
            if (braceCount == 0) {
                return static_cast<int>(pos);
            }
        }
        pos++;
    }
    
    return -1; // 未找到匹配的括号
}

SegmentPtr BridgeScanner::createSegment(LanguageType type, const std::string& content,
                                       int startLine, int startColumn, int endLine, int endColumn) {
    auto segment = std::make_shared<Segment>(type, content, startLine, startColumn, endLine, endColumn);
    
    if (debugMode_) {
        std::cout << "创建段: " << segment->toString() << std::endl;
    }
    
    return segment;
}

void BridgeScanner::addError(const std::string& error, int line, int column) {
    std::stringstream ss;
    ss << "[" << line << ":" << column << "] " << error;
    errors_.push_back(ss.str());
    
    if (debugMode_) {
        std::cerr << "扫描错误: " << ss.str() << std::endl;
    }
}

} // namespace CHTL