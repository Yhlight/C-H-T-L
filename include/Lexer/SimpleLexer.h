#ifndef CHTL_SIMPLE_LEXER_H
#define CHTL_SIMPLE_LEXER_H

#include "Lexer/BasicLexer.h"

namespace chtl {

// SimpleLexer - CHTL的基本词法分析器实现
class SimpleLexer : public BasicLexer {
public:
    SimpleLexer();
    virtual ~SimpleLexer() = default;
    
protected:
    // 实现纯虚函数
    std::shared_ptr<BasicState> createInitialState() override;
    std::shared_ptr<BasicContext> createInitialContext() override;
};

} // namespace chtl

#endif // CHTL_SIMPLE_LEXER_H