#include "JsAnalyzer.h"
#include "HeuristicJsBackend.h"

namespace CHTL
{
    JsAnalyzer::JsAnalyzer(std::shared_ptr<IJsBackend> backend)
        : backend_(std::move(backend))
    {
        if (!backend_) backend_ = std::make_shared<HeuristicJsBackend>();
    }

    JsFindings JsAnalyzer::analyze(std::string_view js) const
    {
        return backend_->analyze(js);
    }
}