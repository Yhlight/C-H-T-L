#include "CssCompiler.h"

namespace CHTL
{
    CssCompileResult CssCompiler::compile(std::string_view css) const
    {
        CssCompileResult result;
        result.original.assign(css.begin(), css.end());
        result.findings = analyzer_->analyze(css);
        return result;
    }
}