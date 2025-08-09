#ifndef CHTL_LEXER_STANDARD_LEXER_H
#define CHTL_LEXER_STANDARD_LEXER_H

#include "Lexer/BasicLexer.h"

namespace chtl {

/**
 * @brief StandardLexer - 标准CHTL语法分析器
 * 
 * 这是BasicLexer的标准实现，用于解析常规的CHTL代码。
 * 使用ChtlState作为默认状态，ChtlContext作为默认上下文。
 */
class StandardLexer : public BasicLexer {
public:
    StandardLexer();
    virtual ~StandardLexer() = default;

protected:
    // 实现BasicLexer的纯虚函数
    virtual std::shared_ptr<BasicState> createInitialState() override;
    virtual std::shared_ptr<BasicContext> createInitialContext() override;
};

} // namespace chtl

#endif // CHTL_LEXER_STANDARD_LEXER_H