#include "Scanner.h"
#include <algorithm>
#include <regex>

namespace CHTL {

Scanner::Scanner() : currentState_(ScanState::CHTL), currentLine_(1), currentColumn_(1) {}

std::vector<CodeFragment> Scanner::scan(const std::string& content) {
    std::vector<CodeFragment> fragments;
    scanCHTL(content, fragments);
    return fragments;
}

void Scanner::scanCHTL(const std::string& content, std::vector<CodeFragment>& fragments) {
    int pos = 0;
    int startPos = 0;
    int startLine = currentLine_;
    int startColumn = currentColumn_;
    
    while (pos < content.length()) {
        // 查找特殊块的开始
        if (content.substr(pos, 6) == "style{" || 
            (pos + 6 < content.length() && content.substr(pos, 5) == "style" && isWhitespace(content[pos + 5]))) {
            // 保存之前的CHTL代码
            if (pos > startPos) {
                CodeFragment fragment;
                fragment.type = CodeFragmentType::CHTL;
                fragment.content = content.substr(startPos, pos - startPos);
                fragment.startLine = startLine;
                fragment.startColumn = startColumn;
                fragment.endLine = currentLine_;
                fragment.endColumn = currentColumn_;
                fragments.push_back(fragment);
            }
            
            // 找到style块的开始位置
            pos += 5;
            while (pos < content.length() && isWhitespace(content[pos])) {
                updatePosition(content[pos], currentLine_, currentColumn_);
                pos++;
            }
            
            if (pos < content.length() && content[pos] == '{') {
                pos++; // 跳过 '{'
                updatePosition('{', currentLine_, currentColumn_);
                
                int styleStartPos = pos;
                int styleStartLine = currentLine_;
                int styleStartColumn = currentColumn_;
                
                // 找到匹配的 '}'
                int braceEnd = findMatchingBrace(content, pos - 1);
                if (braceEnd != -1) {
                    std::string styleContent = content.substr(styleStartPos, braceEnd - styleStartPos);
                    scanStyleBlock(styleContent, styleStartLine, styleStartColumn, fragments);
                    
                    // 更新位置
                    for (int i = styleStartPos; i <= braceEnd; i++) {
                        updatePosition(content[i], currentLine_, currentColumn_);
                    }
                    pos = braceEnd + 1;
                }
            }
            
            startPos = pos;
            startLine = currentLine_;
            startColumn = currentColumn_;
        }
        else if (content.substr(pos, 7) == "script{" || 
                (pos + 7 < content.length() && content.substr(pos, 6) == "script" && isWhitespace(content[pos + 6]))) {
            // 保存之前的CHTL代码
            if (pos > startPos) {
                CodeFragment fragment;
                fragment.type = CodeFragmentType::CHTL;
                fragment.content = content.substr(startPos, pos - startPos);
                fragment.startLine = startLine;
                fragment.startColumn = startColumn;
                fragment.endLine = currentLine_;
                fragment.endColumn = currentColumn_;
                fragments.push_back(fragment);
            }
            
            // 找到script块的开始位置
            pos += 6;
            while (pos < content.length() && isWhitespace(content[pos])) {
                updatePosition(content[pos], currentLine_, currentColumn_);
                pos++;
            }
            
            if (pos < content.length() && content[pos] == '{') {
                pos++; // 跳过 '{'
                updatePosition('{', currentLine_, currentColumn_);
                
                int scriptStartPos = pos;
                int scriptStartLine = currentLine_;
                int scriptStartColumn = currentColumn_;
                
                // 找到匹配的 '}'
                int braceEnd = findMatchingBrace(content, pos - 1);
                if (braceEnd != -1) {
                    std::string scriptContent = content.substr(scriptStartPos, braceEnd - scriptStartPos);
                    scanScriptBlock(scriptContent, scriptStartLine, scriptStartColumn, fragments);
                    
                    // 更新位置
                    for (int i = scriptStartPos; i <= braceEnd; i++) {
                        updatePosition(content[i], currentLine_, currentColumn_);
                    }
                    pos = braceEnd + 1;
                }
            }
            
            startPos = pos;
            startLine = currentLine_;
            startColumn = currentColumn_;
        }
        else if (content.substr(pos, 8) == "[Origin]") {
            // 处理原始嵌入块
            extractOriginBlock(content, pos, fragments);
            startPos = pos;
            startLine = currentLine_;
            startColumn = currentColumn_;
        }
        else {
            updatePosition(content[pos], currentLine_, currentColumn_);
            pos++;
        }
    }
    
    // 保存最后的CHTL代码片段
    if (startPos < content.length()) {
        CodeFragment fragment;
        fragment.type = CodeFragmentType::CHTL;
        fragment.content = content.substr(startPos);
        fragment.startLine = startLine;
        fragment.startColumn = startColumn;
        fragment.endLine = currentLine_;
        fragment.endColumn = currentColumn_;
        fragments.push_back(fragment);
    }
}

void Scanner::scanStyleBlock(const std::string& content, int startLine, int startColumn, 
                            std::vector<CodeFragment>& fragments) {
    CodeFragment fragment;
    fragment.type = CodeFragmentType::CSS;
    fragment.content = content;
    fragment.startLine = startLine;
    fragment.startColumn = startColumn;
    fragment.context = "style";
    
    // 计算结束位置
    int line = startLine;
    int column = startColumn;
    for (char c : content) {
        updatePosition(c, line, column);
    }
    fragment.endLine = line;
    fragment.endColumn = column;
    
    fragments.push_back(fragment);
}

void Scanner::scanScriptBlock(const std::string& content, int startLine, int startColumn,
                             std::vector<CodeFragment>& fragments) {
    CodeFragment fragment;
    
    // 检测是否包含CHTL JS扩展语法
    if (containsCHTLJSExtensions(content)) {
        fragment.type = CodeFragmentType::CHTL_JAVASCRIPT;
    } else {
        fragment.type = CodeFragmentType::JAVASCRIPT;
    }
    
    fragment.content = content;
    fragment.startLine = startLine;
    fragment.startColumn = startColumn;
    fragment.context = "script";
    
    // 计算结束位置
    int line = startLine;
    int column = startColumn;
    for (char c : content) {
        updatePosition(c, line, column);
    }
    fragment.endLine = line;
    fragment.endColumn = column;
    
    fragments.push_back(fragment);
}

bool Scanner::containsCHTLJSExtensions(const std::string& jsCode) const {
    // 检查CHTL JS特有的语法
    static const std::vector<std::string> chtlJsPatterns = {
        "{{",           // CHTL选择器
        "->",           // CHTL箭头操作符
        "->listen",     // 增强监听器
        "->delegate",   // 事件委托
        "animate("      // 动画函数
    };
    
    for (const auto& pattern : chtlJsPatterns) {
        if (jsCode.find(pattern) != std::string::npos) {
            return true;
        }
    }
    
    return false;
}

void Scanner::extractOriginBlock(const std::string& content, int& pos, 
                                std::vector<CodeFragment>& fragments) {
    // TODO: 实现原始嵌入块的提取
    // 格式: [Origin] @Type { ... }
}

CodeFragmentType Scanner::detectType(const std::string& content, const std::string& context) const {
    if (context == "style") {
        return CodeFragmentType::CSS;
    } else if (context == "script") {
        return containsCHTLJSExtensions(content) ? 
               CodeFragmentType::CHTL_JAVASCRIPT : 
               CodeFragmentType::JAVASCRIPT;
    } else if (context == "origin") {
        return CodeFragmentType::RAW_HTML;
    }
    
    return CodeFragmentType::CHTL;
}

bool Scanner::isWhitespace(char c) const {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

bool Scanner::isNewline(char c) const {
    return c == '\n';
}

void Scanner::updatePosition(char c, int& line, int& column) {
    if (isNewline(c)) {
        line++;
        column = 1;
    } else {
        column++;
    }
}

std::string Scanner::extractUntil(const std::string& content, int& pos, 
                                 const std::string& delimiter) {
    size_t delimPos = content.find(delimiter, pos);
    if (delimPos == std::string::npos) {
        std::string result = content.substr(pos);
        pos = content.length();
        return result;
    }
    
    std::string result = content.substr(pos, delimPos - pos);
    pos = delimPos + delimiter.length();
    return result;
}

int Scanner::findMatchingBrace(const std::string& content, int startPos) const {
    if (startPos >= content.length() || content[startPos] != '{') {
        return -1;
    }
    
    int braceCount = 1;
    int pos = startPos + 1;
    bool inString = false;
    bool inComment = false;
    bool inBlockComment = false;
    char stringChar = 0;
    
    while (pos < content.length() && braceCount > 0) {
        char c = content[pos];
        char nextC = (pos + 1 < content.length()) ? content[pos + 1] : '\0';
        
        // 处理注释
        if (!inString) {
            if (!inComment && !inBlockComment && c == '/' && nextC == '/') {
                inComment = true;
                pos += 2;
                continue;
            }
            if (!inComment && !inBlockComment && c == '/' && nextC == '*') {
                inBlockComment = true;
                pos += 2;
                continue;
            }
            if (inBlockComment && c == '*' && nextC == '/') {
                inBlockComment = false;
                pos += 2;
                continue;
            }
            if (inComment && isNewline(c)) {
                inComment = false;
            }
        }
        
        // 处理字符串
        if (!inComment && !inBlockComment) {
            if (!inString && (c == '"' || c == '\'' || c == '`')) {
                inString = true;
                stringChar = c;
            } else if (inString && c == stringChar && content[pos - 1] != '\\') {
                inString = false;
                stringChar = 0;
            }
        }
        
        // 计算括号
        if (!inString && !inComment && !inBlockComment) {
            if (c == '{') {
                braceCount++;
            } else if (c == '}') {
                braceCount--;
                if (braceCount == 0) {
                    return pos;
                }
            }
        }
        
        pos++;
    }
    
    return -1;
}

} // namespace CHTL