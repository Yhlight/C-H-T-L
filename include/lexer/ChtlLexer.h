#ifndef CHTL_CHTL_LEXER_H
#define CHTL_CHTL_LEXER_H

#include "lexer/BasicLexer.h"
#include "state/StateFactory.h"
#include "context/ChtlContext.h"

namespace chtl {

// CHTL词法分析器
class ChtlLexer : public BasicLexer {
private:
    // CHTL特有的配置
    bool allowUnquotedLiterals_;
    bool colonEqualsEquivalence_;  // CE对等式
    
public:
    ChtlLexer();
    virtual ~ChtlLexer() = default;
    
    // 配置选项
    void setAllowUnquotedLiterals(bool allow) { allowUnquotedLiterals_ = allow; }
    void setColonEqualsEquivalence(bool enable) { colonEqualsEquivalence_ = enable; }
    
    // 获取CHTL上下文
    std::shared_ptr<ChtlContext> getChtlContext() {
        return std::dynamic_pointer_cast<ChtlContext>(context_);
    }
    
protected:
    // 实现基类的纯虚函数
    std::shared_ptr<BasicState> createInitialState() override;
    std::shared_ptr<BasicContext> createInitialContext() override;
};

} // namespace chtl

#endif // CHTL_CHTL_LEXER_H