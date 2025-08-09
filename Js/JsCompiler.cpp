#include "JsCompiler.h"

namespace CHTL
{
    JsCompileResult JsCompiler::compile(std::string_view js) const
    {
        JsCompileResult result;
        result.original.assign(js.begin(), js.end());
        result.findings = analyzer_->analyze(js);
        return result;
    }
}