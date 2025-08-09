#ifndef CHTL_TOKEN_H
#define CHTL_TOKEN_H

#include <string>
#include <iostream>
#include "TokenType.h"

namespace chtl {

// Token类
class Token {
private:
    TokenType type_;
    std::string value_;
    int line_;
    int column_;
    std::string filename_;

public:
    // 构造函数
    Token() : type_(TokenType::UNKNOWN), line_(1), column_(1) {}
    
    Token(TokenType type, const std::string& value, int line, int column, const std::string& filename = "")
        : type_(type), value_(value), line_(line), column_(column), filename_(filename) {}
    
    // Getter方法
    TokenType getType() const { return type_; }
    const std::string& getValue() const { return value_; }
    int getLine() const { return line_; }
    int getColumn() const { return column_; }
    const std::string& getFilename() const { return filename_; }
    
    // Setter方法
    void setType(TokenType type) { type_ = type; }
    void setValue(const std::string& value) { value_ = value; }
    void setLine(int line) { line_ = line; }
    void setColumn(int column) { column_ = column; }
    void setFilename(const std::string& filename) { filename_ = filename; }
    
    // 判断方法
    bool isKeyword() const {
        return type_ >= TokenType::TEXT && type_ <= TokenType::EXCEPT;
    }
    
    bool isSpecialMarker() const {
        return type_ >= TokenType::CUSTOM && type_ <= TokenType::EXPORT_KW;
    }
    
    bool isAtPrefix() const {
        return type_ >= TokenType::AT_STYLE && type_ <= TokenType::AT_CHTL;
    }
    
    bool isOperator() const {
        return type_ >= TokenType::COLON && type_ <= TokenType::AMPERSAND;
    }
    
    bool isBracket() const {
        return type_ >= TokenType::LEFT_BRACE && type_ <= TokenType::RIGHT_BRACKET;
    }
    
    bool isComment() const {
        return type_ >= TokenType::SINGLE_LINE_COMMENT && type_ <= TokenType::HTML_COMMENT;
    }
    
    bool isLiteral() const {
        return type_ >= TokenType::IDENTIFIER && type_ <= TokenType::NUMBER;
    }
    
    bool isEOF() const {
        return type_ == TokenType::EOF_TOKEN;
    }
    
    // 获取Token类型的字符串表示
    std::string getTypeString() const;
    
    // 调试输出
    void print() const {
        std::cout << "Token(" << getTypeString() << ", \"" << value_ << "\", " 
                  << line_ << ":" << column_ << ")" << std::endl;
    }
    
    // 相等比较
    bool operator==(const Token& other) const {
        return type_ == other.type_ && value_ == other.value_;
    }
    
    bool operator!=(const Token& other) const {
        return !(*this == other);
    }
};

} // namespace chtl

#endif // CHTL_TOKEN_H