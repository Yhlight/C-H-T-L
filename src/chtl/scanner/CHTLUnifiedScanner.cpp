#include "CHTLUnifiedScanner.h"
#include <algorithm>
#include <cctype>

namespace chtl {
namespace scanner {

CHTLUnifiedScanner::CHTLUnifiedScanner() 
    : pos_(0), line_(1), column_(1) {
    contextStack_.push(ScannerContext::TOP_LEVEL);
}

CHTLUnifiedScanner::~CHTLUnifiedScanner() = default;

std::vector<CodeFragment> CHTLUnifiedScanner::scan(const std::string& input) {
    input_ = input;
    pos_ = 0;
    line_ = 1;
    column_ = 1;
    errors_.clear();
    
    std::vector<CodeFragment> fragments;
    
    while (contextStack_.size() > 1) {
        contextStack_.pop();
    }
    contextStack_.push(ScannerContext::TOP_LEVEL);
    
    scanTopLevel(fragments);
    
    return fragments;
}

void CHTLUnifiedScanner::setFragmentHandler(FragmentType type, 
                                           std::function<void(const CodeFragment&)> handler) {
    handlers_[type] = handler;
}

void CHTLUnifiedScanner::scanTopLevel(std::vector<CodeFragment>& fragments) {
    while (pos_ < input_.size()) {
        skipWhitespace();
        
        if (pos_ >= input_.size()) break;
        
        size_t startPos = pos_;
        size_t startLine = line_;
        size_t startColumn = column_;
        
        // 检查style块
        if (matchKeyword("style") && (peek() == '{' || std::isspace(peek()))) {
            // 跳过style关键字
            while (pos_ < input_.size() && peek() != '{') advance();
            if (peek() == '{') advance();
            
            pushContext(ScannerContext::STYLE_BLOCK);
            scanStyleBlock(fragments);
            popContext();
            
            if (peek() == '}') advance();
        }
        // 检查script块
        else if (matchKeyword("script") && (peek() == '{' || std::isspace(peek()))) {
            // 跳过script关键字
            while (pos_ < input_.size() && peek() != '{') advance();
            if (peek() == '{') advance();
            
            pushContext(ScannerContext::SCRIPT_BLOCK);
            scanScriptBlock(fragments);
            popContext();
            
            if (peek() == '}') advance();
        }
        // 其他CHTL内容
        else {
            // 收集CHTL片段直到遇到style或script
            std::string chtlContent;
            while (pos_ < input_.size()) {
                if (matchKeyword("style") && (peekAhead(5) == '{' || std::isspace(peekAhead(5)))) {
                    break;
                }
                if (matchKeyword("script") && (peekAhead(6) == '{' || std::isspace(peekAhead(6)))) {
                    break;
                }
                chtlContent += advance();
            }
            
            if (!chtlContent.empty()) {
                addFragment(fragments, FragmentType::CHTL, chtlContent,
                           startLine, startColumn, line_, column_);
            }
        }
    }
}

void CHTLUnifiedScanner::scanStyleBlock(std::vector<CodeFragment>& fragments) {
    size_t startPos = pos_;
    size_t startLine = line_;
    size_t startColumn = column_;
    
    // 收集CSS内容直到遇到对应的 }
    std::string cssContent;
    int braceCount = 1;
    
    while (pos_ < input_.size() && braceCount > 0) {
        char c = peek();
        
        if (c == '{') {
            braceCount++;
        } else if (c == '}') {
            braceCount--;
            if (braceCount == 0) break;
        } else if (c == '/' && peekNext() == '*') {
            // CSS注释
            cssContent += advance(); // /
            cssContent += advance(); // *
            while (pos_ < input_.size() && !(peek() == '*' && peekNext() == '/')) {
                cssContent += advance();
            }
            if (pos_ < input_.size()) {
                cssContent += advance(); // *
                cssContent += advance(); // /
            }
            continue;
        }
        
        cssContent += advance();
    }
    
    if (!cssContent.empty()) {
        addFragment(fragments, FragmentType::CSS, cssContent,
                   startLine, startColumn, line_, column_);
    }
}

void CHTLUnifiedScanner::scanScriptBlock(std::vector<CodeFragment>& fragments) {
    size_t startPos = pos_;
    size_t startLine = line_;
    size_t startColumn = column_;
    
    // 先扫描一遍，检查是否包含CHTL扩展
    size_t scanPos = pos_;
    bool hasCHTLExtensions = false;
    int braceCount = 1;
    
    while (scanPos < input_.size() && braceCount > 0) {
        if (input_[scanPos] == '{') {
            braceCount++;
        } else if (input_[scanPos] == '}') {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        // 检查CHTL扩展标记
        if (scanPos + 1 < input_.size()) {
            // @Element, @Style, @Var
            if (input_[scanPos] == '@' && 
                (matchAt(scanPos + 1, "Element") || 
                 matchAt(scanPos + 1, "Style") || 
                 matchAt(scanPos + 1, "Var"))) {
                hasCHTLExtensions = true;
                break;
            }
            // {{ }}
            if (input_[scanPos] == '{' && input_[scanPos + 1] == '{') {
                hasCHTLExtensions = true;
                break;
            }
            // var x = @...
            if (matchAt(scanPos, "var") && scanPos + 3 < input_.size()) {
                size_t tempPos = scanPos + 3;
                while (tempPos < input_.size() && std::isspace(input_[tempPos])) tempPos++;
                while (tempPos < input_.size() && (std::isalnum(input_[tempPos]) || input_[tempPos] == '_')) tempPos++;
                while (tempPos < input_.size() && std::isspace(input_[tempPos])) tempPos++;
                if (tempPos < input_.size() && input_[tempPos] == '=') {
                    tempPos++;
                    while (tempPos < input_.size() && std::isspace(input_[tempPos])) tempPos++;
                    if (tempPos < input_.size() && input_[tempPos] == '@') {
                        hasCHTLExtensions = true;
                        break;
                    }
                }
            }
        }
        
        scanPos++;
    }
    
    // 根据是否有CHTL扩展决定片段类型
    if (hasCHTLExtensions) {
        scanCHTLJavaScript(fragments);
    } else {
        // 纯JavaScript，收集整个块
        std::string jsContent;
        braceCount = 1;
        
        while (pos_ < input_.size() && braceCount > 0) {
            char c = peek();
            
            if (c == '{') {
                braceCount++;
            } else if (c == '}') {
                braceCount--;
                if (braceCount == 0) break;
            }
            
            jsContent += advance();
        }
        
        if (!jsContent.empty()) {
            addFragment(fragments, FragmentType::JS, jsContent,
                       startLine, startColumn, line_, column_);
        }
    }
}

void CHTLUnifiedScanner::scanCHTLJavaScript(std::vector<CodeFragment>& fragments) {
    size_t startPos = pos_;
    size_t startLine = line_;
    size_t startColumn = column_;
    
    // 收集整个CHTL JS内容
    std::string chtlJsContent;
    int braceCount = 1;
    
    while (pos_ < input_.size() && braceCount > 0) {
        char c = peek();
        
        if (c == '{') {
            braceCount++;
        } else if (c == '}') {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        chtlJsContent += advance();
    }
    
    if (!chtlJsContent.empty()) {
        addFragment(fragments, FragmentType::CHTL_JS, chtlJsContent,
                   startLine, startColumn, line_, column_);
    }
}

// 辅助方法实现
char CHTLUnifiedScanner::peek() const {
    return pos_ < input_.size() ? input_[pos_] : '\0';
}

char CHTLUnifiedScanner::peekNext() const {
    return pos_ + 1 < input_.size() ? input_[pos_ + 1] : '\0';
}

char CHTLUnifiedScanner::peekAhead(size_t n) const {
    return pos_ + n < input_.size() ? input_[pos_ + n] : '\0';
}

char CHTLUnifiedScanner::advance() {
    if (pos_ >= input_.size()) return '\0';
    
    char c = input_[pos_++];
    if (c == '\n') {
        line_++;
        column_ = 1;
    } else {
        column_++;
    }
    
    return c;
}

void CHTLUnifiedScanner::skipWhitespace() {
    while (pos_ < input_.size() && std::isspace(peek())) {
        advance();
    }
}

bool CHTLUnifiedScanner::match(const std::string& text) {
    if (pos_ + text.length() > input_.size()) return false;
    
    for (size_t i = 0; i < text.length(); i++) {
        if (input_[pos_ + i] != text[i]) return false;
    }
    
    pos_ += text.length();
    column_ += text.length();
    return true;
}

bool CHTLUnifiedScanner::matchKeyword(const std::string& keyword) {
    if (pos_ + keyword.length() > input_.size()) return false;
    
    for (size_t i = 0; i < keyword.length(); i++) {
        if (input_[pos_ + i] != keyword[i]) return false;
    }
    
    // 确保关键字后面不是字母或数字
    if (pos_ + keyword.length() < input_.size()) {
        char next = input_[pos_ + keyword.length()];
        if (std::isalnum(next) || next == '_') return false;
    }
    
    return true;
}

bool CHTLUnifiedScanner::matchAt(size_t position, const std::string& text) const {
    if (position + text.length() > input_.size()) return false;
    
    for (size_t i = 0; i < text.length(); i++) {
        if (input_[position + i] != text[i]) return false;
    }
    
    return true;
}

void CHTLUnifiedScanner::pushContext(ScannerContext ctx) {
    contextStack_.push(ctx);
}

void CHTLUnifiedScanner::popContext() {
    if (contextStack_.size() > 1) {
        contextStack_.pop();
    }
}

ScannerContext CHTLUnifiedScanner::currentContext() const {
    return contextStack_.top();
}

void CHTLUnifiedScanner::addFragment(std::vector<CodeFragment>& fragments,
                                    FragmentType type,
                                    const std::string& content,
                                    size_t startLine, size_t startColumn,
                                    size_t endLine, size_t endColumn) {
    fragments.emplace_back(type, content, startLine, startColumn, endLine, endColumn);
    
    // 如果有处理器，立即调用
    if (handlers_.count(type)) {
        handlers_[type](fragments.back());
    }
}

void CHTLUnifiedScanner::reportError(const std::string& message) {
    std::ostringstream oss;
    oss << "Scanner error at line " << line_ << ", column " << column_ << ": " << message;
    errors_.push_back(oss.str());
}

} // namespace scanner
} // namespace chtl