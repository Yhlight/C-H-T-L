#ifndef CHTL_STANDALONE_LEXER_H
#define CHTL_STANDALONE_LEXER_H

#include "ParserRuntime.h"
#include <unordered_map>
#include <functional>

namespace chtl {
namespace parser {

class CHTLLexer : public Lexer {
public:
    CHTLLexer(const std::string& input) : Lexer(input) {
        initKeywords();
    }
    
protected:
    std::shared_ptr<Token> nextToken() override {
        skipWhitespaceAndComments();
        
        if (pos_ >= input_.size()) {
            return std::make_shared<Token>(TokenType::EOF_TOKEN, "", line_, column_);
        }
        
        int startLine = line_;
        int startColumn = column_;
        
        // 检查注释
        if (peek() == '/' && peekNext() == '/') {
            return scanComment();
        }
        if (peek() == '/' && peekNext() == '*') {
            return scanMultilineComment();
        }
        if (peek() == '-' && peekNext() == '-') {
            return scanHtmlComment();
        }
        
        // 检查字符串字面量
        if (peek() == '"' || peek() == '\'') {
            return scanString();
        }
        
        // 检查数字
        if (std::isdigit(peek())) {
            return scanNumber();
        }
        
        // 检查标识符和关键字
        if (std::isalpha(peek()) || peek() == '_') {
            return scanIdentifierOrKeyword();
        }
        
        // 检查特殊符号
        if (peek() == '[') {
            advance();
            // 检查是否是关键字模式 [Template], [Custom]等
            std::string keyword = scanKeywordInBrackets();
            if (!keyword.empty()) {
                return std::make_shared<Token>(getKeywordType(keyword), 
                    "[" + keyword + "]", startLine, startColumn);
            }
            return std::make_shared<Token>(TokenType::LBRACKET, "[", startLine, startColumn);
        }
        
        if (peek() == '@') {
            advance();
            // 检查@后面的关键字
            std::string keyword = scanIdentifier();
            if (!keyword.empty()) {
                TokenType type = getAtKeywordType(keyword);
                return std::make_shared<Token>(type, "@" + keyword, startLine, startColumn);
            }
            return std::make_shared<Token>(TokenType::AT, "@", startLine, startColumn);
        }
        
        // 单字符符号
        char c = peek();
        advance();
        
        switch (c) {
            case '{': return std::make_shared<Token>(TokenType::LBRACE, "{", startLine, startColumn);
            case '}': return std::make_shared<Token>(TokenType::RBRACE, "}", startLine, startColumn);
            case '(': return std::make_shared<Token>(TokenType::LPAREN, "(", startLine, startColumn);
            case ')': return std::make_shared<Token>(TokenType::RPAREN, ")", startLine, startColumn);
            case ';': return std::make_shared<Token>(TokenType::SEMICOLON, ";", startLine, startColumn);
            case ':': return std::make_shared<Token>(TokenType::COLON, ":", startLine, startColumn);
            case '=': return std::make_shared<Token>(TokenType::EQUALS, "=", startLine, startColumn);
            case ',': return std::make_shared<Token>(TokenType::COMMA, ",", startLine, startColumn);
            case '.': return std::make_shared<Token>(TokenType::DOT, ".", startLine, startColumn);
            case '&': return std::make_shared<Token>(TokenType::AMPERSAND, "&", startLine, startColumn);
            case '#': return std::make_shared<Token>(TokenType::HASH, "#", startLine, startColumn);
            case '+': return std::make_shared<Token>(TokenType::PLUS, "+", startLine, startColumn);
            case '-': return std::make_shared<Token>(TokenType::MINUS, "-", startLine, startColumn);
            case '*': return std::make_shared<Token>(TokenType::STAR, "*", startLine, startColumn);
            case '/': return std::make_shared<Token>(TokenType::SLASH, "/", startLine, startColumn);
            case '%': return std::make_shared<Token>(TokenType::PERCENT, "%", startLine, startColumn);
            case '!': return std::make_shared<Token>(TokenType::EXCLAMATION, "!", startLine, startColumn);
            case '?': return std::make_shared<Token>(TokenType::QUESTION, "?", startLine, startColumn);
            case '>': return std::make_shared<Token>(TokenType::GREATER, ">", startLine, startColumn);
            case '<': return std::make_shared<Token>(TokenType::LESS, "<", startLine, startColumn);
            case '~': return std::make_shared<Token>(TokenType::TILDE, "~", startLine, startColumn);
            case ']': return std::make_shared<Token>(TokenType::RBRACKET, "]", startLine, startColumn);
            default:
                return std::make_shared<Token>(TokenType::INVALID, std::string(1, c), startLine, startColumn);
        }
    }
    
private:
    std::unordered_map<std::string, TokenType> keywords_;
    std::unordered_map<std::string, TokenType> atKeywords_;
    
    void initKeywords() {
        // 普通关键字
        keywords_["text"] = TokenType::KEYWORD_TEXT;
        keywords_["style"] = TokenType::KEYWORD_STYLE;
        keywords_["script"] = TokenType::KEYWORD_SCRIPT;
        keywords_["as"] = TokenType::KEYWORD_AS;
        keywords_["from"] = TokenType::KEYWORD_FROM;
        keywords_["except"] = TokenType::KEYWORD_EXCEPT;
        keywords_["before"] = TokenType::KEYWORD_BEFORE;
        keywords_["after"] = TokenType::KEYWORD_AFTER;
        keywords_["replace"] = TokenType::KEYWORD_REPLACE;
        keywords_["at"] = TokenType::KEYWORD_AT;
        keywords_["top"] = TokenType::KEYWORD_TOP;
        keywords_["bottom"] = TokenType::KEYWORD_BOTTOM;
        keywords_["if"] = TokenType::KEYWORD_IF;
        
        // []关键字
        keywords_["Template"] = TokenType::KEYWORD_TEMPLATE;
        keywords_["Custom"] = TokenType::KEYWORD_CUSTOM;
        keywords_["Import"] = TokenType::KEYWORD_IMPORT;
        keywords_["Namespace"] = TokenType::KEYWORD_NAMESPACE;
        keywords_["Origin"] = TokenType::KEYWORD_ORIGIN;
        
        // @关键字
        atKeywords_["Element"] = TokenType::KEYWORD_ELEMENT;
        atKeywords_["Style"] = TokenType::KEYWORD_STYLE_GROUP;
        atKeywords_["Var"] = TokenType::KEYWORD_VAR_GROUP;
        atKeywords_["Module"] = TokenType::KEYWORD_MODULE;
        atKeywords_["Chtl"] = TokenType::KEYWORD_CHTL;
        atKeywords_["CJmod"] = TokenType::KEYWORD_CJMOD;
        atKeywords_["Html"] = TokenType::KEYWORD_HTML;
        atKeywords_["JavaScript"] = TokenType::KEYWORD_JAVASCRIPT;
        atKeywords_["inherit"] = TokenType::KEYWORD_INHERIT;
        atKeywords_["use"] = TokenType::KEYWORD_USE;
        atKeywords_["delete"] = TokenType::KEYWORD_DELETE;
        atKeywords_["insert"] = TokenType::KEYWORD_INSERT;
    }
    
    char peekNext() {
        if (pos_ + 1 < input_.size()) return input_[pos_ + 1];
        return '\0';
    }
    
    void skipWhitespaceAndComments() {
        while (pos_ < input_.size()) {
            if (std::isspace(peek())) {
                skipWhitespace();
            } else if (peek() == '/' && peekNext() == '/') {
                // 跳过单行注释
                while (pos_ < input_.size() && peek() != '\n') {
                    advance();
                }
            } else if (peek() == '/' && peekNext() == '*') {
                // 跳过多行注释
                advance(); advance();
                while (pos_ < input_.size() - 1) {
                    if (peek() == '*' && peekNext() == '/') {
                        advance(); advance();
                        break;
                    }
                    advance();
                }
            } else {
                break;
            }
        }
    }
    
    std::shared_ptr<Token> scanComment() {
        int startLine = line_;
        int startColumn = column_;
        std::string text;
        
        advance(); advance(); // 跳过 //
        text = "//";
        
        while (pos_ < input_.size() && peek() != '\n') {
            text += advance();
        }
        
        return std::make_shared<Token>(TokenType::COMMENT, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanMultilineComment() {
        int startLine = line_;
        int startColumn = column_;
        std::string text = "/*";
        
        advance(); advance(); // 跳过 /*
        
        while (pos_ < input_.size() - 1) {
            if (peek() == '*' && peekNext() == '/') {
                text += advance();
                text += advance();
                break;
            }
            text += advance();
        }
        
        return std::make_shared<Token>(TokenType::MULTILINE_COMMENT, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanHtmlComment() {
        int startLine = line_;
        int startColumn = column_;
        std::string text = "--";
        
        advance(); advance(); // 跳过 --
        
        while (pos_ < input_.size() && peek() != '\n') {
            text += advance();
        }
        
        return std::make_shared<Token>(TokenType::HTML_COMMENT, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanString() {
        int startLine = line_;
        int startColumn = column_;
        char quote = advance();
        std::string text;
        text += quote;
        
        while (pos_ < input_.size() && peek() != quote) {
            if (peek() == '\\') {
                text += advance();
                if (pos_ < input_.size()) {
                    text += advance();
                }
            } else {
                text += advance();
            }
        }
        
        if (pos_ < input_.size()) {
            text += advance(); // 结束引号
        }
        
        return std::make_shared<Token>(TokenType::STRING_LITERAL, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanNumber() {
        int startLine = line_;
        int startColumn = column_;
        std::string text;
        
        while (pos_ < input_.size() && (std::isdigit(peek()) || peek() == '.')) {
            text += advance();
        }
        
        // 检查单位（px, em, %, 等）
        if (std::isalpha(peek()) || peek() == '%') {
            while (pos_ < input_.size() && (std::isalpha(peek()) || peek() == '%')) {
                text += advance();
            }
        }
        
        return std::make_shared<Token>(TokenType::NUMBER_LITERAL, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanIdentifierOrKeyword() {
        int startLine = line_;
        int startColumn = column_;
        std::string text = scanIdentifier();
        
        // 检查是否是关键字
        auto it = keywords_.find(text);
        if (it != keywords_.end()) {
            return std::make_shared<Token>(it->second, text, startLine, startColumn);
        }
        
        // 检查是否是布尔值
        if (text == "true" || text == "false") {
            return std::make_shared<Token>(TokenType::BOOLEAN_LITERAL, text, startLine, startColumn);
        }
        
        return std::make_shared<Token>(TokenType::IDENTIFIER, text, startLine, startColumn);
    }
    
    std::string scanIdentifier() {
        std::string text;
        
        while (pos_ < input_.size() && 
               (std::isalnum(peek()) || peek() == '_' || peek() == '-')) {
            text += advance();
        }
        
        return text;
    }
    
    std::string scanKeywordInBrackets() {
        int mark = pos_;
        std::string keyword = scanIdentifier();
        
        if (pos_ < input_.size() && peek() == ']') {
            advance(); // consume ]
            auto it = keywords_.find(keyword);
            if (it != keywords_.end()) {
                return keyword;
            }
        }
        
        // 回退
        pos_ = mark;
        return "";
    }
    
    TokenType getKeywordType(const std::string& keyword) {
        auto it = keywords_.find(keyword);
        if (it != keywords_.end()) {
            return it->second;
        }
        return TokenType::IDENTIFIER;
    }
    
    TokenType getAtKeywordType(const std::string& keyword) {
        auto it = atKeywords_.find(keyword);
        if (it != atKeywords_.end()) {
            return it->second;
        }
        return TokenType::IDENTIFIER;
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_LEXER_H