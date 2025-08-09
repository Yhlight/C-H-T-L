#include "CssAnalyzer.h"
#include "HeuristicCssBackend.h"

namespace CHTL
{
    CssAnalyzer::CssAnalyzer(std::shared_ptr<ICssBackend> backend)
        : backend_(std::move(backend))
    {
        if (!backend_) backend_ = std::make_shared<HeuristicCssBackend>();
    }

    CssFindings CssAnalyzer::analyze(std::string_view css) const
    {
        return backend_->analyze(css);
    }
}