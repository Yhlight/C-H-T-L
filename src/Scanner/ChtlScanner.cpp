#include "Scanner/ChtlScanner.h"
#include <iostream>
#include <algorithm>
#include <cctype>

namespace chtl {

std::vector<CodeSegment> ChtlScanner::scan(const std::string& source, SegmentType initialType) {
    source_ = source;
    position_ = 0;
    line_ = 1;
    column_ = 1;
    segments_.clear();
    
    switch (initialType) {
        case SegmentType::CHTL:
            scanChtl();
            break;
        case SegmentType::CSS:
            scanCss();
            break;
        case SegmentType::JS:
            scanJs();
            break;
        default:
            break;
    }
    
    return segments_;
}

void ChtlScanner::scanJs() {
    mode_ = ScanMode::LOOSE;
    looseScanJs();
}

void ChtlScanner::looseScanJs() {
    size_t blockStart = position_;
    
    while (!isAtEnd()) {
        // 先检查是否是 CHTL-JS 的开始
        if (currentChar() == '{' && peekChar() == '{' && !isInJsString() && !isInJsComment()) {
            // 保存当前 JS 块
            if (position_ > blockStart) {
                addSegment(createSegment(SegmentType::JS, blockStart, position_));
            }
            
            // 切换到严判模式处理 CHTL-JS
            mode_ = ScanMode::STRICT;
            strictScanForChtlJs();
            mode_ = ScanMode::LOOSE;
            
            // 重置块开始位置
            blockStart = position_;
            continue;
        }
        
        // 更新 JS 上下文
        updateJsContext(currentChar());
        
        // 检查是否应该在此处分割（函数大括号等）
        if (shouldSplitJsHere() && position_ > blockStart) {
            addSegment(createSegment(SegmentType::JS, blockStart, position_ + 1));
            blockStart = position_ + 1;
        }
        
        advance();
    }
    
    // 保存最后的块
    if (position_ > blockStart) {
        addSegment(createSegment(SegmentType::JS, blockStart, position_));
    }
}

bool ChtlScanner::shouldSplitJsHere() {
    // 在函数大括号处分割
    if (currentChar() == '{' || currentChar() == '}') {
        // 但不在字符串或注释中
        if (!isInJsString() && !isInJsComment()) {
            // 检查是否是函数定义
            // 简化版：当大括号深度变化时分割
            return true;
        }
    }
    return false;
}

void ChtlScanner::strictScanForChtlJs() {
    size_t start = position_;
    
    // 验证 {{ 开始
    if (currentChar() != '{' || peekChar() != '{') {
        reportError("Expected '{{' at start of CHTL-JS");
        return;
    }
    
    advance(); // 跳过第一个 {
    advance(); // 跳过第二个 {
    
    // 找到对应的 }}
    size_t end = findChtlJsEnd();
    if (end == std::string::npos) {
        reportError("Unclosed CHTL-JS block");
        return;
    }
    
    // 创建 CHTL-JS 段
    CodeSegment segment = createSegment(SegmentType::CHTL_JS, start, end + 2);
    
    // 提取纯 CHTL-JS 内容（去掉 {{ 和 }}）
    segment.content = source_.substr(start + 2, end - start - 2);
    
    // 记录原始位置信息
    segment.chtlJsInfo.originalStart = start;
    segment.chtlJsInfo.originalEnd = end + 2;
    segment.chtlJsInfo.placeholder = "__CHTL_JS_" + std::to_string(segments_.size()) + "__";
    
    addSegment(segment);
    
    // 移动到 }} 之后
    advanceTo(end + 2);
}

size_t ChtlScanner::findChtlJsEnd() {
    size_t pos = position_;
    int depth = 0;
    bool inString = false;
    char stringChar = 0;
    
    while (pos < source_.length()) {
        char ch = source_[pos];
        
        // 处理字符串
        if (inString) {
            if (ch == stringChar && (pos == 0 || source_[pos - 1] != '\\')) {
                inString = false;
            }
        } else {
            if (ch == '"' || ch == '\'' || ch == '`') {
                inString = true;
                stringChar = ch;
            } else if (ch == '{') {
                depth++;
            } else if (ch == '}') {
                if (pos + 1 < source_.length() && source_[pos + 1] == '}' && depth == 0) {
                    return pos;
                }
                if (depth > 0) depth--;
            }
        }
        
        pos++;
    }
    
    return std::string::npos;
}

void ChtlScanner::updateJsContext(char ch) {
    // 处理字符串状态
    if (jsContext_.inString) {
        if (ch == jsContext_.stringChar && 
            (position_ == 0 || source_[position_ - 1] != '\\')) {
            jsContext_.inString = false;
        }
        return;
    }
    
    // 处理注释
    if (jsContext_.inComment) {
        if (ch == '\n') {
            jsContext_.inComment = false;
        }
        return;
    }
    
    // 检查注释开始
    if (ch == '/' && peekChar() == '/') {
        jsContext_.inComment = true;
        return;
    }
    
    // 检查字符串开始
    if (ch == '"' || ch == '\'' || ch == '`') {
        jsContext_.inString = true;
        jsContext_.stringChar = ch;
        return;
    }
    
    // 更新括号深度
    switch (ch) {
        case '{': jsContext_.braceDepth++; break;
        case '}': jsContext_.braceDepth--; break;
        case '(': jsContext_.parenDepth++; break;
        case ')': jsContext_.parenDepth--; break;
        case '[': jsContext_.bracketDepth++; break;
        case ']': jsContext_.bracketDepth--; break;
    }
}

bool ChtlScanner::isValidChtlJsStart() {
    // 检查 {{ 后面是否是有效的选择器
    size_t pos = position_ + 2;
    while (pos < source_.length() && std::isspace(source_[pos])) {
        pos++;
    }
    
    if (pos >= source_.length()) return false;
    
    // 检查选择器类型
    char ch = source_[pos];
    return ch == '#' || ch == '.' || ch == '&' || std::isalpha(ch);
}

bool ChtlScanner::isValidSelector(const std::string& selector) {
    if (selector.empty()) return false;
    
    char first = selector[0];
    if (first == '#' || first == '.') {
        // ID 或类选择器，后面应该是标识符
        return selector.length() > 1 && std::isalpha(selector[1]);
    } else if (first == '&') {
        // 当前元素引用
        return selector.length() == 1;
    } else if (std::isalpha(first)) {
        // 标签选择器
        return true;
    }
    
    return false;
}

bool ChtlScanner::isValidChtlJsMethod(const std::string& method) {
    static const std::vector<std::string> validMethods = {
        "listen", "animate", "delegate", "create", "update", "remove"
    };
    
    return std::find(validMethods.begin(), validMethods.end(), method) != validMethods.end();
}

char ChtlScanner::currentChar() const {
    return position_ < source_.length() ? source_[position_] : '\0';
}

char ChtlScanner::peekChar(int offset) const {
    size_t pos = position_ + offset;
    return pos < source_.length() ? source_[pos] : '\0';
}

void ChtlScanner::advance() {
    if (position_ < source_.length()) {
        if (source_[position_] == '\n') {
            line_++;
            column_ = 1;
        } else {
            column_++;
        }
        position_++;
    }
}

void ChtlScanner::advanceTo(size_t pos) {
    while (position_ < pos && position_ < source_.length()) {
        advance();
    }
}

bool ChtlScanner::isAtEnd() const {
    return position_ >= source_.length();
}

CodeSegment ChtlScanner::createSegment(SegmentType type, size_t start, size_t end) {
    CodeSegment segment;
    segment.type = type;
    segment.content = source_.substr(start, end - start);
    
    // 计算行列信息（简化版）
    segment.startLine = 1;
    segment.startColumn = 1;
    for (size_t i = 0; i < start; i++) {
        if (source_[i] == '\n') {
            segment.startLine++;
            segment.startColumn = 1;
        } else {
            segment.startColumn++;
        }
    }
    
    segment.endLine = segment.startLine;
    segment.endColumn = segment.startColumn;
    for (size_t i = start; i < end; i++) {
        if (source_[i] == '\n') {
            segment.endLine++;
            segment.endColumn = 1;
        } else {
            segment.endColumn++;
        }
    }
    
    return segment;
}

void ChtlScanner::addSegment(const CodeSegment& segment) {
    segments_.push_back(segment);
}

void ChtlScanner::reportError(const std::string& message) {
    // TODO: 集成到错误处理系统
    std::cerr << "Scanner error at line " << line_ << ", column " << column_ 
              << ": " << message << std::endl;
}

// TODO: 实现 scanChtl() 和 scanCss()
void ChtlScanner::scanChtl() {
    // CHTL 扫描逻辑
    addSegment(createSegment(SegmentType::CHTL, 0, source_.length()));
}

void ChtlScanner::scanCss() {
    // CSS 扫描逻辑
    addSegment(createSegment(SegmentType::CSS, 0, source_.length()));
}

} // namespace chtl