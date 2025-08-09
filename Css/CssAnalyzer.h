#pragma once

#include <string>
#include <string_view>
#include <memory>

#include "CssFindings.h"
#include "CssBackend.h"

namespace CHTL
{
    class CssAnalyzer
    {
    public:
        explicit CssAnalyzer(std::shared_ptr<ICssBackend> backend = nullptr);
        CssFindings analyze(std::string_view css) const;
    private:
        std::shared_ptr<ICssBackend> backend_;
    };
}