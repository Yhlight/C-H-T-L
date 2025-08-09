#include "CssAnalyzer.h"
#include "SelfCssBackend.h"

namespace CHTL
{
    CssAnalyzer::CssAnalyzer(std::shared_ptr<ICssBackend> backend)
        : backend_(std::move(backend))
    {
        if (!backend_) backend_ = std::make_shared<SelfCssBackend>();
    }

    CssFindings CssAnalyzer::analyze(std::string_view css) const
    {
        return backend_->analyze(css);
    }
}