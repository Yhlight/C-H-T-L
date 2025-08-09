#ifndef CHTL_BASIC_STATE_H
#define CHTL_BASIC_STATE_H

#include <string>
#include <memory>
#include <vector>
#include "common/Token.h"

namespace chtl {

// 前向声明
class Lexer;

// 状态类型枚举
enum class StateType {
    CHTL,       // CHTL主状态
    CSS,        // CSS状态
    JS,         // JavaScript状态
    CHTL_JS,    // CHTL扩展的JavaScript状态
    STRING,     // 字符串状态
    COMMENT,    // 注释状态
    ORIGIN      // 原始代码状态
};

// 状态机基类
class BasicState {
protected:
    StateType type_;
    std::string name_;
    Lexer* lexer_;  // 指向词法分析器的指针
    
public:
    // 构造函数
    BasicState(StateType type, const std::string& name, Lexer* lexer)
        : type_(type), name_(name), lexer_(lexer) {}
    
    // 虚析构函数
    virtual ~BasicState() = default;
    
    // 获取状态类型
    StateType getType() const { return type_; }
    
    // 获取状态名称
    const std::string& getName() const { return name_; }
    
    // 处理字符，返回下一个状态（如果需要切换）
    // 返回nullptr表示保持当前状态
    virtual std::shared_ptr<BasicState> handleChar(char ch) = 0;
    
    // 处理字符串（用于预读多个字符的情况）
    virtual std::shared_ptr<BasicState> handleString(const std::string& str) {
        // 默认实现：逐字符处理
        std::shared_ptr<BasicState> newState = nullptr;
        for (char ch : str) {
            newState = handleChar(ch);
            if (newState) {
                return newState;
            }
        }
        return nullptr;
    }
    
    // 进入状态时的处理
    virtual void onEnter() {}
    
    // 离开状态时的处理
    virtual void onExit() {}
    
    // 状态结束时的处理（例如EOF）
    virtual void onEnd() {}
    
    // 创建Token
    virtual Token createToken(TokenType type, const std::string& value, int line, int column) {
        return Token(type, value, line, column);
    }
    
    // 是否接受当前字符
    virtual bool accepts(char ch) const = 0;
    
    // 是否是终止状态
    virtual bool isTerminal() const { return false; }
    
    // 获取当前累积的值（用于构建token）
    virtual std::string getCurrentValue() const { return ""; }
    
    // 重置状态
    virtual void reset() {}
};

} // namespace chtl

#endif // CHTL_BASIC_STATE_H