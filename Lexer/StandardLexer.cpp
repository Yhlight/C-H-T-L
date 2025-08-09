#include "StandardLexer.h"

#include <cstddef>

#include "../State/StateFactory.h"
#include "../Context/ContextFactory.h"
#include "../State/BasicState.h"
#include "../Context/BasicContext.h"

namespace CHTL
{
    StandardLexer::StandardLexer(LanguageMode mode)
        : BasicLexer(mode)
        , state_(StateFactory::create(mode))
        , context_(ContextFactory::create(mode))
    {
    }

    StandardLexer::~StandardLexer() = default;

    std::vector<Token> StandardLexer::tokenize(const std::string& source)
    {
        std::size_t i = 0;
        while (i < source.size())
        {
            if (!state_->process(source, i, *context_))
            {
                // 无法处理当前字符，跳过避免死循环
                ++i;
            }
        }
        return context_->tokens();
    }
}