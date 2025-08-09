#pragma once

#include <string_view>
#include <memory>

#include "CssAnalyzer.h"
#include "CssCompileResult.h"

namespace CHTL
{
    class CssCompiler
    {
    public:
        explicit CssCompiler(std::shared_ptr<ICssBackend> backend = nullptr)
            : analyzer_(std::make_shared<CssAnalyzer>(std::move(backend))) {}

        CssCompileResult compile(std::string_view css) const;

    private:
        std::shared_ptr<CssAnalyzer> analyzer_;
    };
}