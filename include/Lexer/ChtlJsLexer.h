#ifndef CHTL_JS_LEXER_H
#define CHTL_JS_LEXER_H

#include "Lexer/BasicLexer.h"
#include "State/ChtlJsState.h"
#include "Context/ChtlJsContext.h"
#include <memory>
#include <string>

namespace chtl {

/**
 * CHTL-JS词法分析器
 * 使用状态机和上下文推导来处理CHTL扩展的JavaScript语法
 */
class ChtlJsLexer : public BasicLexer {
private:
    std::shared_ptr<ChtlJsState> chtlJsState_;
    std::shared_ptr<ChtlJsContext> chtlJsContext_;
    
    // 缓冲区用于多字符token
    std::string tokenBuffer_;
    bool inChtlSequence_;
    
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
    void reset() override;
    
    // CHTL-JS特有方法
    bool isInChtlMode() const;
    std::shared_ptr<ChtlJsContext> getChtlJsContext() const { return chtlJsContext_; }
    
protected:
    // Token识别
    Token recognizeToken() override;
    
    // CHTL特有token识别
    Token recognizeChtlSelector();      // {{selector}}
    Token recognizeChtlArrow();         // ->
    Token recognizeChtlMethod();        // listen, delegate, animate
    
    // JavaScript token识别（复用标准JS）
    Token recognizeJsIdentifier();
    Token recognizeJsNumber();
    Token recognizeJsString();
    Token recognizeJsOperator();
    
    // 辅助方法
    bool checkChtlSequence(const std::string& sequence);
    void skipWhitespace();
    char peekChar(int offset = 0);
    std::string readUntil(const std::string& delimiter);
    std::string readWhile(std::function<bool(char)> predicate);
};

} // namespace chtl

#endif // CHTL_JS_LEXER_H