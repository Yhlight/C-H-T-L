#include "ConfigLexer.h"

#include "StandardLexer.h"

namespace CHTL
{
    std::vector<Token> ConfigLexer::tokenize(const std::string& source)
    {
        StandardLexer delegate(LanguageMode::Config);
        return delegate.tokenize(source);
    }
}