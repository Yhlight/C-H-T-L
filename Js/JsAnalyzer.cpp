#include "JsAnalyzer.h"
#include "SelfJsBackend.h"

namespace CHTL
{
    JsAnalyzer::JsAnalyzer(std::shared_ptr<IJsBackend> backend)
        : backend_(std::move(backend))
    {
        if (!backend_) backend_ = std::make_shared<SelfJsBackend>();
    }

    JsFindings JsAnalyzer::analyze(std::string_view js) const
    {
        return backend_->analyze(js);
    }
}