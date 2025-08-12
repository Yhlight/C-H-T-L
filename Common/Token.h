#ifndef CHTL_COMMON_TOKEN_H
#define CHTL_COMMON_TOKEN_H

#include <string>
#include <memory>
#include "Types.h"

namespace CHTL {

/**
 * Token类 - 表示词法分析器生成的标记
 */
class Token {
public:
    Token(TokenType type, const std::string& value, int line, int column)
        : type_(type), value_(value), line_(line), column_(column) {}
    
    // 获取Token类型
    TokenType getType() const { return type_; }
    
    // 获取Token值
    const std::string& getValue() const { return value_; }
    
    // 获取行号
    int getLine() const { return line_; }
    
    // 获取列号
    int getColumn() const { return column_; }
    
    // 设置下一个Token（用于链表结构）
    void setNext(std::shared_ptr<Token> next) { next_ = next; }
    std::shared_ptr<Token> getNext() const { return next_; }
    
    // 判断是否是特定类型
    bool is(TokenType type) const { return type_ == type; }
    
    // 判断是否是关键字
    bool isKeyword() const {
        return type_ >= TokenType::KEYWORD_START && type_ <= TokenType::KEYWORD_END;
    }
    
    // 判断是否是操作符
    bool isOperator() const {
        return type_ >= TokenType::OPERATOR_START && type_ <= TokenType::OPERATOR_END;
    }
    
    // 转换为字符串（用于调试）
    std::string toString() const;
    
private:
    TokenType type_;
    std::string value_;
    int line_;
    int column_;
    std::shared_ptr<Token> next_;
};

using TokenPtr = std::shared_ptr<Token>;

} // namespace CHTL

#endif // CHTL_COMMON_TOKEN_H