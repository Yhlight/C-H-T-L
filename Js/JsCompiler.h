#pragma once

#include <string_view>
#include <memory>

#include "JsAnalyzer.h"
#include "JsCompileResult.h"

namespace CHTL
{
    class JsCompiler
    {
    public:
        explicit JsCompiler(std::shared_ptr<IJsBackend> backend = nullptr)
            : analyzer_(std::make_shared<JsAnalyzer>(std::move(backend))) {}

        JsCompileResult compile(std::string_view js) const;

    private:
        std::shared_ptr<JsAnalyzer> analyzer_;
    };
}