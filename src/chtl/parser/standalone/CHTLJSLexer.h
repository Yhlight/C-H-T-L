#ifndef CHTL_STANDALONE_JS_LEXER_H
#define CHTL_STANDALONE_JS_LEXER_H

#include "CHTLLexer.h"
#include <set>

namespace chtl {
namespace parser {

// CHTL JavaScript词法分析器 - 扩展CHTL词法分析器以支持JS语法
class CHTLJSLexer : public CHTLLexer {
public:
    CHTLJSLexer(const std::string& input) : CHTLLexer(input) {
        initJSKeywords();
    }
    
protected:
    std::shared_ptr<Token> nextToken() override {
        // 首先尝试CHTL特有的token
        if (isInCHTLContext()) {
            auto chtlToken = CHTLLexer::nextToken();
            if (chtlToken->getType() != TokenType::INVALID) {
                return chtlToken;
            }
        }
        
        // 然后处理JavaScript特有的token
        return scanJSToken();
    }
    
private:
    std::unordered_map<std::string, TokenType> jsKeywords_;
    bool inTemplateString_ = false;
    char templateQuote_ = '`';
    
    void initJSKeywords() {
        // JavaScript关键字
        jsKeywords_["var"] = TokenType::KEYWORD_VAR;
        jsKeywords_["let"] = TokenType::IDENTIFIER;  // 作为标识符处理
        jsKeywords_["const"] = TokenType::IDENTIFIER;
        jsKeywords_["function"] = TokenType::IDENTIFIER;
        jsKeywords_["class"] = TokenType::IDENTIFIER;
        jsKeywords_["extends"] = TokenType::IDENTIFIER;
        jsKeywords_["return"] = TokenType::IDENTIFIER;
        jsKeywords_["if"] = TokenType::KEYWORD_IF;
        jsKeywords_["else"] = TokenType::IDENTIFIER;
        jsKeywords_["for"] = TokenType::IDENTIFIER;
        jsKeywords_["while"] = TokenType::IDENTIFIER;
        jsKeywords_["do"] = TokenType::IDENTIFIER;
        jsKeywords_["switch"] = TokenType::IDENTIFIER;
        jsKeywords_["case"] = TokenType::IDENTIFIER;
        jsKeywords_["break"] = TokenType::IDENTIFIER;
        jsKeywords_["continue"] = TokenType::IDENTIFIER;
        jsKeywords_["try"] = TokenType::IDENTIFIER;
        jsKeywords_["catch"] = TokenType::IDENTIFIER;
        jsKeywords_["finally"] = TokenType::IDENTIFIER;
        jsKeywords_["throw"] = TokenType::IDENTIFIER;
        jsKeywords_["new"] = TokenType::IDENTIFIER;
        jsKeywords_["this"] = TokenType::IDENTIFIER;
        jsKeywords_["super"] = TokenType::IDENTIFIER;
        jsKeywords_["import"] = TokenType::IDENTIFIER;
        jsKeywords_["export"] = TokenType::IDENTIFIER;
        jsKeywords_["default"] = TokenType::IDENTIFIER;
        jsKeywords_["async"] = TokenType::IDENTIFIER;
        jsKeywords_["await"] = TokenType::IDENTIFIER;
        jsKeywords_["yield"] = TokenType::IDENTIFIER;
        jsKeywords_["static"] = TokenType::IDENTIFIER;
        jsKeywords_["get"] = TokenType::IDENTIFIER;
        jsKeywords_["set"] = TokenType::IDENTIFIER;
        jsKeywords_["typeof"] = TokenType::IDENTIFIER;
        jsKeywords_["instanceof"] = TokenType::IDENTIFIER;
        jsKeywords_["in"] = TokenType::IDENTIFIER;
        jsKeywords_["of"] = TokenType::IDENTIFIER;
        jsKeywords_["null"] = TokenType::IDENTIFIER;
        jsKeywords_["undefined"] = TokenType::IDENTIFIER;
        jsKeywords_["true"] = TokenType::BOOLEAN_LITERAL;
        jsKeywords_["false"] = TokenType::BOOLEAN_LITERAL;
    }
    
    bool isInCHTLContext() {
        // 检查是否在CHTL特定的上下文中
        // 例如：在{}内但不在script块中
        // 这需要更复杂的状态管理，这里简化处理
        return false;
    }
    
    std::shared_ptr<Token> scanJSToken() {
        skipWhitespaceAndComments();
        
        if (pos_ >= input_.size()) {
            return std::make_shared<Token>(TokenType::EOF_TOKEN, "", line_, column_);
        }
        
        int startLine = line_;
        int startColumn = column_;
        
        // 模板字符串
        if (peek() == '`' || (inTemplateString_ && peek() == '$' && peekNext() == '{')) {
            return scanTemplateString();
        }
        
        // 正则表达式
        if (peek() == '/' && isRegexContext()) {
            return scanRegex();
        }
        
        // 数字（包括二进制、八进制、十六进制）
        if (std::isdigit(peek()) || (peek() == '.' && std::isdigit(peekNext()))) {
            return scanJSNumber();
        }
        
        // 字符串
        if (peek() == '"' || peek() == '\'') {
            return scanString();
        }
        
        // 标识符或关键字
        if (std::isalpha(peek()) || peek() == '_' || peek() == '$') {
            return scanJSIdentifier();
        }
        
        // 操作符
        return scanJSOperator();
    }
    
    std::shared_ptr<Token> scanTemplateString() {
        int startLine = line_;
        int startColumn = column_;
        std::string text;
        
        if (peek() == '`') {
            advance();
            inTemplateString_ = !inTemplateString_;
            text = "`";
            
            if (inTemplateString_) {
                // 开始模板字符串
                while (pos_ < input_.size() && peek() != '`') {
                    if (peek() == '$' && peekNext() == '{') {
                        // 遇到插值表达式
                        break;
                    }
                    if (peek() == '\\') {
                        text += advance();
                        if (pos_ < input_.size()) {
                            text += advance();
                        }
                    } else {
                        text += advance();
                    }
                }
            }
            
            return std::make_shared<Token>(TokenType::STRING_LITERAL, text, startLine, startColumn);
        }
        
        // 处理 ${ ... }
        if (peek() == '$' && peekNext() == '{') {
            advance(); advance();
            return std::make_shared<Token>(TokenType::IDENTIFIER, "${", startLine, startColumn);
        }
        
        return std::make_shared<Token>(TokenType::INVALID, "", startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanRegex() {
        int startLine = line_;
        int startColumn = column_;
        std::string text = "/";
        advance();
        
        bool inClass = false;
        while (pos_ < input_.size()) {
            char c = peek();
            if (c == '[' && !inClass) {
                inClass = true;
            } else if (c == ']' && inClass) {
                inClass = false;
            } else if (c == '/' && !inClass) {
                text += advance();
                // 读取标志
                while (pos_ < input_.size() && std::isalpha(peek())) {
                    text += advance();
                }
                break;
            } else if (c == '\\') {
                text += advance();
                if (pos_ < input_.size()) {
                    text += advance();
                }
                continue;
            }
            text += advance();
        }
        
        return std::make_shared<Token>(TokenType::STRING_LITERAL, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanJSNumber() {
        int startLine = line_;
        int startColumn = column_;
        std::string text;
        
        // 十六进制
        if (peek() == '0' && (peekNext() == 'x' || peekNext() == 'X')) {
            text += advance(); // 0
            text += advance(); // x
            while (pos_ < input_.size() && std::isxdigit(peek())) {
                text += advance();
            }
        }
        // 二进制
        else if (peek() == '0' && (peekNext() == 'b' || peekNext() == 'B')) {
            text += advance(); // 0
            text += advance(); // b
            while (pos_ < input_.size() && (peek() == '0' || peek() == '1')) {
                text += advance();
            }
        }
        // 八进制
        else if (peek() == '0' && (peekNext() == 'o' || peekNext() == 'O')) {
            text += advance(); // 0
            text += advance(); // o
            while (pos_ < input_.size() && peek() >= '0' && peek() <= '7') {
                text += advance();
            }
        }
        // 十进制或浮点数
        else {
            while (pos_ < input_.size() && (std::isdigit(peek()) || peek() == '.')) {
                text += advance();
            }
            
            // 科学计数法
            if (peek() == 'e' || peek() == 'E') {
                text += advance();
                if (peek() == '+' || peek() == '-') {
                    text += advance();
                }
                while (pos_ < input_.size() && std::isdigit(peek())) {
                    text += advance();
                }
            }
            
            // BigInt
            if (peek() == 'n') {
                text += advance();
            }
        }
        
        return std::make_shared<Token>(TokenType::NUMBER_LITERAL, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanJSIdentifier() {
        int startLine = line_;
        int startColumn = column_;
        std::string text;
        
        while (pos_ < input_.size() && 
               (std::isalnum(peek()) || peek() == '_' || peek() == '$')) {
            text += advance();
        }
        
        // 检查是否是JS关键字
        auto it = jsKeywords_.find(text);
        if (it != jsKeywords_.end()) {
            return std::make_shared<Token>(it->second, text, startLine, startColumn);
        }
        
        return std::make_shared<Token>(TokenType::IDENTIFIER, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanJSOperator() {
        int startLine = line_;
        int startColumn = column_;
        char c = peek();
        
        // 三字符操作符
        if (pos_ + 2 < input_.size()) {
            std::string threeChar = std::string(1, c) + peekNext() + input_[pos_ + 2];
            if (threeChar == ">>>" || threeChar == "===" || threeChar == "!==") {
                advance(); advance(); advance();
                return std::make_shared<Token>(TokenType::IDENTIFIER, threeChar, startLine, startColumn);
            }
        }
        
        // 双字符操作符
        if (pos_ + 1 < input_.size()) {
            std::string twoChar = std::string(1, c) + peekNext();
            std::set<std::string> doubleOps = {
                "++", "--", "==", "!=", "<=", ">=", "&&", "||",
                "<<", ">>", "+=", "-=", "*=", "/=", "%=", "&=",
                "|=", "^=", "=>", "?.", "??", "**"
            };
            
            if (doubleOps.count(twoChar)) {
                advance(); advance();
                return std::make_shared<Token>(TokenType::IDENTIFIER, twoChar, startLine, startColumn);
            }
        }
        
        // 单字符操作符 - 使用基类的处理
        return CHTLLexer::nextToken();
    }
    
    bool isRegexContext() {
        // 简化的正则表达式上下文检测
        // 实际实现需要更复杂的上下文分析
        if (pos_ == 0) return true;
        
        size_t i = pos_ - 1;
        while (i > 0 && std::isspace(input_[i])) i--;
        
        if (i > 0) {
            char prev = input_[i];
            return prev == '=' || prev == '(' || prev == '[' || 
                   prev == '!' || prev == ':' || prev == ';' || 
                   prev == ',' || prev == '{';
        }
        
        return true;
    }
    
    char peekNext() {
        return pos_ + 1 < input_.size() ? input_[pos_ + 1] : '\0';
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_JS_LEXER_H