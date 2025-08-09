#pragma once

#include "BasicLexer.h"

#include <memory>

namespace CHTL
{
    class StandardLexer : public BasicLexer
    {
    public:
        explicit StandardLexer(LanguageMode mode);
        ~StandardLexer();
        std::vector<Token> tokenize(const std::string& source) override;

    private:
        std::unique_ptr<class BasicState> state_;
        std::unique_ptr<class BasicContext> context_;
    };
}