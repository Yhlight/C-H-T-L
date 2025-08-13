#ifndef CHTL_PARSER_RUNTIME_H
#define CHTL_PARSER_RUNTIME_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stack>
#include <exception>
#include <sstream>

namespace chtl {
namespace parser {

// 前向声明
class Token;
class TokenStream;
class ParseTree;
class ParseContext;
class ErrorListener;

// Token类型枚举（根据CHTL语法定义）
enum class TokenType {
    // 特殊Token
    EOF_TOKEN = -1,
    INVALID = 0,
    
    // 字面量
    TEXT_LITERAL,
    STRING_LITERAL,
    NUMBER_LITERAL,
    BOOLEAN_LITERAL,
    
    // 标识符
    IDENTIFIER,
    
    // 关键字 - 根据CHTL语法文档
    KEYWORD_TEXT,       // text
    KEYWORD_STYLE,      // style
    KEYWORD_SCRIPT,     // script
    KEYWORD_TEMPLATE,   // [Template]
    KEYWORD_CUSTOM,     // [Custom]
    KEYWORD_IMPORT,     // [Import]
    KEYWORD_NAMESPACE,  // [Namespace]
    KEYWORD_ORIGIN,     // [Origin]
    KEYWORD_ELEMENT,    // @Element
    KEYWORD_STYLE_GROUP,// @Style
    KEYWORD_VAR_GROUP,  // @Var
    KEYWORD_MODULE,     // @Module
    KEYWORD_CHTL,       // @Chtl
    KEYWORD_CJMOD,      // @CJmod
    KEYWORD_HTML,       // @Html
    KEYWORD_JAVASCRIPT, // @JavaScript
    KEYWORD_CSS,        // @Style (for import)
    KEYWORD_AS,         // as
    KEYWORD_FROM,       // from
    KEYWORD_EXCEPT,     // except
    KEYWORD_INHERIT,    // @inherit
    KEYWORD_USE,        // @use
    KEYWORD_DELETE,     // @delete
    KEYWORD_INSERT,     // @insert
    KEYWORD_BEFORE,     // before
    KEYWORD_AFTER,      // after
    KEYWORD_REPLACE,    // replace
    KEYWORD_AT,         // at
    KEYWORD_TOP,        // top
    KEYWORD_BOTTOM,     // bottom
    KEYWORD_IF,         // if
    
    // 操作符
    LBRACE,             // {
    RBRACE,             // }
    LBRACKET,           // [
    RBRACKET,           // ]
    LPAREN,             // (
    RPAREN,             // )
    SEMICOLON,          // ;
    COLON,              // :
    EQUALS,             // =
    COMMA,              // ,
    DOT,                // .
    AT,                 // @
    AMPERSAND,          // &
    HASH,               // #
    PLUS,               // +
    MINUS,              // -
    STAR,               // *
    SLASH,              // /
    PERCENT,            // %
    EXCLAMATION,        // !
    QUESTION,           // ?
    GREATER,            // >
    LESS,               // <
    TILDE,              // ~
    
    // 注释
    COMMENT,            // //
    MULTILINE_COMMENT,  // /* */
    HTML_COMMENT,       // --
    
    // 空白
    WHITESPACE,
    NEWLINE
};

// Token类
class Token {
public:
    Token(TokenType type, const std::string& text, int line, int column)
        : type_(type), text_(text), line_(line), column_(column) {}
    
    TokenType getType() const { return type_; }
    const std::string& getText() const { return text_; }
    int getLine() const { return line_; }
    int getColumn() const { return column_; }
    
    std::string toString() const {
        std::stringstream ss;
        ss << "Token[" << static_cast<int>(type_) << ":" << text_ 
           << " @" << line_ << ":" << column_ << "]";
        return ss.str();
    }
    
private:
    TokenType type_;
    std::string text_;
    int line_;
    int column_;
};

// Token流
class TokenStream {
public:
    TokenStream(const std::vector<std::shared_ptr<Token>>& tokens)
        : tokens_(tokens), index_(0) {}
    
    std::shared_ptr<Token> LT(int k) {
        int pos = index_ + k - 1;
        if (pos < 0 || pos >= tokens_.size()) {
            return std::make_shared<Token>(TokenType::EOF_TOKEN, "", -1, -1);
        }
        return tokens_[pos];
    }
    
    std::shared_ptr<Token> consume() {
        if (index_ < tokens_.size()) {
            return tokens_[index_++];
        }
        return std::make_shared<Token>(TokenType::EOF_TOKEN, "", -1, -1);
    }
    
    int mark() { return index_; }
    void seek(int index) { index_ = index; }
    
    size_t size() const { return tokens_.size(); }
    size_t index() const { return index_; }
    
private:
    std::vector<std::shared_ptr<Token>> tokens_;
    size_t index_;
};

// 解析树节点
class ParseTree {
public:
    ParseTree(const std::string& name) : name_(name) {}
    virtual ~ParseTree() = default;
    
    const std::string& getName() const { return name_; }
    
    void addChild(std::shared_ptr<ParseTree> child) {
        children_.push_back(child);
    }
    
    const std::vector<std::shared_ptr<ParseTree>>& getChildren() const {
        return children_;
    }
    
    virtual std::string getText() const {
        std::string text;
        for (const auto& child : children_) {
            text += child->getText();
        }
        return text;
    }
    
    virtual bool isTerminal() const { return false; }
    
protected:
    std::string name_;
    std::vector<std::shared_ptr<ParseTree>> children_;
};

// 终端节点
class TerminalNode : public ParseTree {
public:
    TerminalNode(std::shared_ptr<Token> token) 
        : ParseTree("Terminal"), token_(token) {}
    
    std::shared_ptr<Token> getToken() const { return token_; }
    
    std::string getText() const override {
        return token_->getText();
    }
    
    bool isTerminal() const override { return true; }
    
private:
    std::shared_ptr<Token> token_;
};

// 解析上下文
class ParseContext : public ParseTree {
public:
    ParseContext(const std::string& ruleName) : ParseTree(ruleName) {}
    
    void setParent(std::shared_ptr<ParseContext> parent) {
        parent_ = parent;
    }
    
    std::shared_ptr<ParseContext> getParent() const {
        return parent_.lock();
    }
    
private:
    std::weak_ptr<ParseContext> parent_;
};

// 错误监听器
class ErrorListener {
public:
    virtual ~ErrorListener() = default;
    
    virtual void syntaxError(const std::string& msg, int line, int column) {
        errors_.push_back({msg, line, column});
    }
    
    bool hasErrors() const { return !errors_.empty(); }
    
    const std::vector<std::tuple<std::string, int, int>>& getErrors() const {
        return errors_;
    }
    
protected:
    std::vector<std::tuple<std::string, int, int>> errors_;
};

// 基础解析器类
class Parser {
public:
    Parser(std::shared_ptr<TokenStream> tokens) 
        : tokens_(tokens), errorListener_(std::make_shared<ErrorListener>()) {}
    
    void setErrorListener(std::shared_ptr<ErrorListener> listener) {
        errorListener_ = listener;
    }
    
protected:
    std::shared_ptr<TokenStream> tokens_;
    std::shared_ptr<ErrorListener> errorListener_;
    
    // 解析辅助方法
    bool match(TokenType type) {
        auto token = tokens_->LT(1);
        if (token->getType() == type) {
            tokens_->consume();
            return true;
        }
        return false;
    }
    
    std::shared_ptr<Token> consume(TokenType type, const std::string& message) {
        auto token = tokens_->LT(1);
        if (token->getType() == type) {
            return tokens_->consume();
        }
        
        error(message + " Expected " + tokenTypeName(type) + 
              " but found " + token->getText(), token);
        return token;
    }
    
    void error(const std::string& msg, std::shared_ptr<Token> token) {
        errorListener_->syntaxError(msg, token->getLine(), token->getColumn());
    }
    
    std::string tokenTypeName(TokenType type) {
        // 简化的Token类型名称映射
        switch (type) {
            case TokenType::IDENTIFIER: return "identifier";
            case TokenType::LBRACE: return "{";
            case TokenType::RBRACE: return "}";
            case TokenType::SEMICOLON: return ";";
            // ... 添加更多映射
            default: return "token";
        }
    }
};

// 基础词法分析器类
class Lexer {
public:
    Lexer(const std::string& input) : input_(input), pos_(0), line_(1), column_(1) {}
    
    std::vector<std::shared_ptr<Token>> tokenize() {
        std::vector<std::shared_ptr<Token>> tokens;
        
        while (pos_ < input_.size()) {
            skipWhitespace();
            if (pos_ >= input_.size()) break;
            
            auto token = nextToken();
            if (token->getType() != TokenType::WHITESPACE && 
                token->getType() != TokenType::COMMENT &&
                token->getType() != TokenType::MULTILINE_COMMENT) {
                tokens.push_back(token);
            }
        }
        
        tokens.push_back(std::make_shared<Token>(TokenType::EOF_TOKEN, "", line_, column_));
        return tokens;
    }
    
protected:
    std::string input_;
    size_t pos_;
    int line_;
    int column_;
    
    virtual std::shared_ptr<Token> nextToken() = 0;
    
    void skipWhitespace() {
        while (pos_ < input_.size() && std::isspace(input_[pos_])) {
            if (input_[pos_] == '\n') {
                line_++;
                column_ = 1;
            } else {
                column_++;
            }
            pos_++;
        }
    }
    
    char peek() {
        if (pos_ < input_.size()) return input_[pos_];
        return '\0';
    }
    
    char advance() {
        if (pos_ < input_.size()) {
            char c = input_[pos_++];
            if (c == '\n') {
                line_++;
                column_ = 1;
            } else {
                column_++;
            }
            return c;
        }
        return '\0';
    }
    
    std::string consumeWhile(std::function<bool(char)> predicate) {
        std::string result;
        while (pos_ < input_.size() && predicate(input_[pos_])) {
            result += advance();
        }
        return result;
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_PARSER_RUNTIME_H