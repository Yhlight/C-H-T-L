#ifndef CHTL_TOKEN_H
#define CHTL_TOKEN_H

#include <string>
#include <iostream>
#include "TokenType.h"

namespace chtl {

// Token类
class Token {
public:
    TokenType type;
    std::string value;
    int line;
    int column;
    std::string filename;

    // 构造函数
    Token() : type(TokenType::UNKNOWN), line(1), column(1) {}
    
    Token(TokenType t, const std::string& v, int l, int c, const std::string& f = "")
        : type(t), value(v), line(l), column(c), filename(f) {}
    
    // Getter方法（保留以保持兼容性）
    TokenType getType() const { return type; }
    const std::string& getValue() const { return value; }
    int getLine() const { return line; }
    int getColumn() const { return column; }
    const std::string& getFilename() const { return filename; }
    
    // Setter方法（保留以保持兼容性）
    void setType(TokenType t) { type = t; }
    void setValue(const std::string& v) { value = v; }
    void setLine(int l) { line = l; }
    void setColumn(int c) { column = c; }
    void setFilename(const std::string& f) { filename = f; }
    
    // 判断方法
    bool isKeyword() const {
        return type >= TokenType::TEXT && type <= TokenType::EXCEPT;
    }
    
    bool isSpecialMarker() const {
        return type >= TokenType::CUSTOM && type <= TokenType::EXPORT_KW;
    }
    
    bool isAtPrefix() const {
        return type >= TokenType::AT_STYLE && type <= TokenType::AT_CHTL;
    }
    
    bool isOperator() const {
        return type >= TokenType::COLON && type <= TokenType::AMPERSAND;
    }
    
    bool isBracket() const {
        return type >= TokenType::LEFT_BRACE && type <= TokenType::RIGHT_BRACKET;
    }
    
    bool isComment() const {
        return type >= TokenType::SINGLE_LINE_COMMENT && type <= TokenType::HTML_COMMENT;
    }
    
    bool isLiteral() const {
        return type >= TokenType::IDENTIFIER && type <= TokenType::NUMBER;
    }
    
    bool isEOF() const {
        return type == TokenType::EOF_TOKEN;
    }
    
    // 获取Token类型的字符串表示
    std::string getTypeString() const;
    
    // 调试输出
    void print() const {
        std::cout << "Token(" << getTypeString() << ", \"" << value << "\", " 
                  << line << ":" << column << ")" << std::endl;
    }
    
    // 相等比较
    bool operator==(const Token& other) const {
        return type == other.type && value == other.value;
    }
    
    bool operator!=(const Token& other) const {
        return !(*this == other);
    }
};

} // namespace chtl

#endif // CHTL_TOKEN_H