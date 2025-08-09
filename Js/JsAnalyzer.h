#pragma once

#include <string>
#include <string_view>
#include <memory>

#include "JsFindings.h"
#include "JsBackend.h"

namespace CHTL
{
    class JsAnalyzer
    {
    public:
        explicit JsAnalyzer(std::shared_ptr<IJsBackend> backend = nullptr);
        JsFindings analyze(std::string_view js) const;
    private:
        std::shared_ptr<IJsBackend> backend_;
    };
}