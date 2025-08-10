#ifndef CHTL_JS_LEXER_H
#define CHTL_JS_LEXER_H

#include "Lexer/BasicLexer.h"
#include "State/ChtlJsState.h"
#include "Context/ChtlJsContext.h"
#include <memory>
#include <string>
#include <vector> // Added for tokenBuffer_

namespace chtl {

/**
 * CHTL-JS词法分析器
 * 使用状态机和上下文推导来处理CHTL扩展的JavaScript语法
 */
class ChtlJsLexer : public BasicLexer {
private:
    // CHTL-JS状态管理
    std::shared_ptr<ChtlJsState> chtlJsState_;
    std::shared_ptr<ChtlJsContext> chtlJsContext_;
    
    // Token缓冲
    std::vector<Token> tokenBuffer_;
    
    // 状态标志
    bool inChtlSequence_;
    
    // 输入管理
    std::string input_;
    size_t position_;
    int currentLine_;
    int currentColumn_;
    
    // Token生成辅助
    Token createChtlToken(TokenType type, const std::string& value);
    Token createSelectorToken(const std::string& selector);
    Token createMethodToken(const std::string& method);
    
public:
    ChtlJsLexer();
    virtual ~ChtlJsLexer() = default;
    
    // 初始化
    void initialize(std::shared_ptr<ChtlJsState> state = nullptr,
                   std::shared_ptr<ChtlJsContext> context = nullptr);
    
    // 重写BasicLexer方法
    Token getNextToken() override;
    Token peekNextToken() override;
    void reset();
    
    // CHTL-JS特有方法
    bool isInChtlMode() const;
    std::shared_ptr<ChtlJsContext> getChtlJsContext() const { return chtlJsContext_; }
    
protected:
    // Token识别
    Token recognizeToken();
    
    // CHTL特有token识别
    Token recognizeChtlSelector();      // {{selector}}
    Token recognizeChtlArrow();         // ->
    Token recognizeChtlMethod();        // listen, delegate, animate
    
    // JavaScript token识别（复用标准JS）
    Token recognizeJsIdentifier();
    Token recognizeJsNumber();
    Token recognizeJsString();
    Token recognizeJsOperator();
    
    // 字符检查
    bool isAlphaNumeric(char ch) const;
    bool isWhitespace(char ch) const;
    
    // 位置管理
    void advanceChar();
    char currentChar() const;
    char peekChar(int offset = 0) const;
    std::string readWhile(std::function<bool(char)> predicate);
    
    // 辅助方法
    bool checkChtlSequence(const std::string& sequence);
    void skipWhitespace();
    void skipComment();
    std::string consumeWhile(std::function<bool(char)> predicate);
    TokenType getKeywordType(const std::string& word);
    TokenType getOperatorType(const std::string& op);
};

} // namespace chtl

#endif // CHTL_JS_LEXER_H