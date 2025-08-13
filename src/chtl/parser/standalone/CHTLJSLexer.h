#ifndef CHTL_STANDALONE_JS_LEXER_H
#define CHTL_STANDALONE_JS_LEXER_H

#include "ParserRuntime.h"
#include <set>

namespace chtl {
namespace parser {

// CHTL JavaScript词法分析器 - 仅处理CHTL在JavaScript中的扩展
// 不处理原生JavaScript语法，原生JS由扫描器直接传递给JS编译器
class CHTLJSLexer : public Lexer {
public:
    CHTLJSLexer(const std::string& input) : Lexer(input) {}
    
protected:
    std::shared_ptr<Token> nextToken() override {
        skipWhitespace();
        
        if (pos_ >= input_.size()) {
            return std::make_shared<Token>(TokenType::EOF_TOKEN, "", line_, column_);
        }
        
        int startLine = line_;
        int startColumn = column_;
        
        // CHTL特有的标记
        
        // @ 指令
        if (peek() == '@') {
            advance();
            
            // 读取指令类型
            std::string directive = readDirective();
            if (directive == "Element") {
                return std::make_shared<Token>(TokenType::AT_ELEMENT, "@Element", startLine, startColumn);
            } else if (directive == "Style") {
                return std::make_shared<Token>(TokenType::AT_STYLE, "@Style", startLine, startColumn);
            } else if (directive == "Var") {
                return std::make_shared<Token>(TokenType::AT_VAR, "@Var", startLine, startColumn);
            } else {
                return std::make_shared<Token>(TokenType::AT, "@" + directive, startLine, startColumn);
            }
        }
        
        // {{ }} 插值
        if (peek() == '{' && peekNext() == '{') {
            advance(); advance();
            return std::make_shared<Token>(TokenType::DOUBLE_LBRACE, "{{", startLine, startColumn);
        }
        
        if (peek() == '}' && peekNext() == '}') {
            advance(); advance();
            return std::make_shared<Token>(TokenType::DOUBLE_RBRACE, "}}", startLine, startColumn);
        }
        
        // var 关键字（仅用于CHTL扩展）
        if (matchKeyword("var")) {
            return std::make_shared<Token>(TokenType::KEYWORD_VAR, "var", startLine, startColumn);
        }
        
        // from 关键字（用于命名空间）
        if (matchKeyword("from")) {
            return std::make_shared<Token>(TokenType::KEYWORD_FROM, "from", startLine, startColumn);
        }
        
        // 标识符
        if (std::isalpha(peek()) || peek() == '_') {
            std::string id = readIdentifier();
            return std::make_shared<Token>(TokenType::IDENTIFIER, id, startLine, startColumn);
        }
        
        // 基本标记
        char c = advance();
        TokenType type = TokenType::INVALID;
        
        switch (c) {
            case '(': type = TokenType::LPAREN; break;
            case ')': type = TokenType::RPAREN; break;
            case '{': type = TokenType::LBRACE; break;
            case '}': type = TokenType::RBRACE; break;
            case ';': type = TokenType::SEMICOLON; break;
            case ',': type = TokenType::COMMA; break;
            case '.': type = TokenType::DOT; break;
            case '=': type = TokenType::EQUALS; break;
        }
        
        return std::make_shared<Token>(type, std::string(1, c), startLine, startColumn);
    }
    
private:
    void skipWhitespace() {
        while (pos_ < input_.size() && std::isspace(peek())) {
            if (peek() == '\n') {
                line_++;
                column_ = 1;
            } else {
                column_++;
            }
            pos_++;
        }
    }
    
    char peek() const {
        return pos_ < input_.size() ? input_[pos_] : '\0';
    }
    
    char peekNext() const {
        return pos_ + 1 < input_.size() ? input_[pos_ + 1] : '\0';
    }
    
    char advance() {
        if (pos_ >= input_.size()) return '\0';
        char c = input_[pos_++];
        column_++;
        return c;
    }
    
    std::string readDirective() {
        std::string result;
        while (pos_ < input_.size() && (std::isalnum(peek()) || peek() == '_')) {
            result += advance();
        }
        return result;
    }
    
    std::string readIdentifier() {
        std::string result;
        while (pos_ < input_.size() && (std::isalnum(peek()) || peek() == '_')) {
            result += advance();
        }
        return result;
    }
    
    bool matchKeyword(const std::string& keyword) {
        size_t savedPos = pos_;
        int savedLine = line_;
        int savedColumn = column_;
        
        for (char c : keyword) {
            if (peek() != c) {
                pos_ = savedPos;
                line_ = savedLine;
                column_ = savedColumn;
                return false;
            }
            advance();
        }
        
        // 确保关键字后面不是字母或数字
        if (std::isalnum(peek()) || peek() == '_') {
            pos_ = savedPos;
            line_ = savedLine;
            column_ = savedColumn;
            return false;
        }
        
        return true;
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_JS_LEXER_H