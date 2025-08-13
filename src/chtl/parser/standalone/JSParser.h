#ifndef CHTL_STANDALONE_JS_PARSER_H
#define CHTL_STANDALONE_JS_PARSER_H

#include "ParserRuntime.h"
#include <regex>
#include <sstream>
#include <set>

namespace chtl {
namespace parser {

// 简化的JavaScript解析器 - 支持原生JS和基本优化
class JSParser {
public:
    struct JSOptions {
        bool minify = false;
        bool removeComments = true;
        bool obfuscateVariables = false;
        bool preserveConsole = true;
    };
    
    JSParser(const std::string& js, const JSOptions& options = {}) 
        : input_(js), pos_(0), options_(options) {}
    
    std::string parse() {
        if (options_.minify) {
            return minifyJS();
        } else {
            return processJS();
        }
    }
    
private:
    std::string input_;
    size_t pos_;
    JSOptions options_;
    
    // 基本的JS处理（保留格式）
    std::string processJS() {
        std::stringstream output;
        
        while (pos_ < input_.size()) {
            if (peek() == '/' && peekNext() == '/') {
                // 单行注释
                if (options_.removeComments) {
                    skipLineComment();
                } else {
                    output << parseLineComment();
                }
            } else if (peek() == '/' && peekNext() == '*') {
                // 多行注释
                if (options_.removeComments) {
                    skipBlockComment();
                } else {
                    output << parseBlockComment();
                }
            } else if (peek() == '"' || peek() == '\'' || peek() == '`') {
                // 字符串
                output << parseString();
            } else if (peek() == '/' && isRegexContext()) {
                // 正则表达式
                output << parseRegex();
            } else {
                output << advance();
            }
        }
        
        return output.str();
    }
    
    // JS压缩
    std::string minifyJS() {
        std::stringstream output;
        bool lastWasWord = false;
        
        while (pos_ < input_.size()) {
            skipWhitespaceAndComments();
            if (pos_ >= input_.size()) break;
            
            char c = peek();
            
            if (c == '"' || c == '\'' || c == '`') {
                // 字符串
                output << parseString();
                lastWasWord = false;
            } else if (c == '/' && isRegexContext()) {
                // 正则表达式
                output << parseRegex();
                lastWasWord = false;
            } else if (std::isalnum(c) || c == '_' || c == '$') {
                // 标识符或关键字
                if (lastWasWord) output << ' ';
                output << parseIdentifier();
                lastWasWord = true;
            } else if (isOperator(c)) {
                // 操作符
                output << c;
                advance();
                lastWasWord = false;
            } else {
                output << advance();
                lastWasWord = false;
            }
        }
        
        return output.str();
    }
    
    char peek() {
        return pos_ < input_.size() ? input_[pos_] : '\0';
    }
    
    char peekNext() {
        return pos_ + 1 < input_.size() ? input_[pos_ + 1] : '\0';
    }
    
    char advance() {
        return pos_ < input_.size() ? input_[pos_++] : '\0';
    }
    
    void skipWhitespace() {
        while (pos_ < input_.size() && std::isspace(input_[pos_])) {
            pos_++;
        }
    }
    
    void skipWhitespaceAndComments() {
        while (pos_ < input_.size()) {
            if (std::isspace(peek())) {
                skipWhitespace();
            } else if (peek() == '/' && peekNext() == '/') {
                skipLineComment();
            } else if (peek() == '/' && peekNext() == '*') {
                skipBlockComment();
            } else {
                break;
            }
        }
    }
    
    void skipLineComment() {
        advance(); advance(); // Skip //
        while (pos_ < input_.size() && peek() != '\n') {
            advance();
        }
        if (peek() == '\n') advance();
    }
    
    void skipBlockComment() {
        advance(); advance(); // Skip /*
        while (pos_ < input_.size() - 1) {
            if (peek() == '*' && peekNext() == '/') {
                advance(); advance();
                break;
            }
            advance();
        }
    }
    
    std::string parseLineComment() {
        std::string comment = "//";
        advance(); advance();
        while (pos_ < input_.size() && peek() != '\n') {
            comment += advance();
        }
        if (peek() == '\n') {
            comment += advance();
        }
        return comment;
    }
    
    std::string parseBlockComment() {
        std::string comment = "/*";
        advance(); advance();
        while (pos_ < input_.size() - 1) {
            if (peek() == '*' && peekNext() == '/') {
                comment += "*/";
                advance(); advance();
                break;
            }
            comment += advance();
        }
        return comment;
    }
    
    std::string parseString() {
        char quote = advance();
        std::string str;
        str += quote;
        
        while (pos_ < input_.size()) {
            char c = peek();
            if (c == quote) {
                str += advance();
                break;
            } else if (c == '\\') {
                str += advance();
                if (pos_ < input_.size()) {
                    str += advance();
                }
            } else if (quote == '`' && c == '$' && peekNext() == '{') {
                // 模板字符串插值
                str += advance(); // $
                str += advance(); // {
                int braceCount = 1;
                while (braceCount > 0 && pos_ < input_.size()) {
                    char nc = advance();
                    str += nc;
                    if (nc == '{') braceCount++;
                    else if (nc == '}') braceCount--;
                }
            } else {
                str += advance();
            }
        }
        
        return str;
    }
    
    std::string parseRegex() {
        std::string regex = "/";
        advance();
        
        bool inClass = false;
        while (pos_ < input_.size()) {
            char c = peek();
            if (c == '[') {
                inClass = true;
            } else if (c == ']') {
                inClass = false;
            } else if (c == '/' && !inClass) {
                regex += advance();
                // 解析标志
                while (pos_ < input_.size() && std::isalpha(peek())) {
                    regex += advance();
                }
                break;
            } else if (c == '\\') {
                regex += advance();
                if (pos_ < input_.size()) {
                    regex += advance();
                }
                continue;
            }
            regex += advance();
        }
        
        return regex;
    }
    
    std::string parseIdentifier() {
        std::string id;
        while (pos_ < input_.size() && 
               (std::isalnum(peek()) || peek() == '_' || peek() == '$')) {
            id += advance();
        }
        return id;
    }
    
    bool isOperator(char c) {
        static const std::set<char> operators = {
            '+', '-', '*', '/', '%', '=', '<', '>', '!', '&', '|', '^', '~',
            '?', ':', ';', ',', '.', '(', ')', '[', ']', '{', '}'
        };
        return operators.count(c) > 0;
    }
    
    // 简单的正则表达式上下文检测
    bool isRegexContext() {
        // 回退查找上一个有意义的token
        size_t savePos = pos_;
        if (pos_ > 0) pos_--;
        
        skipWhitespaceBackward();
        
        // 检查前面是否是可能导致正则表达式的token
        if (pos_ > 0) {
            char c = input_[pos_ - 1];
            pos_ = savePos;
            return c == '=' || c == '(' || c == '[' || c == '!' || 
                   c == ':' || c == ';' || c == ',' || c == '{';
        }
        
        pos_ = savePos;
        return true;
    }
    
    void skipWhitespaceBackward() {
        while (pos_ > 0 && std::isspace(input_[pos_ - 1])) {
            pos_--;
        }
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_JS_PARSER_H