#pragma once

#include <memory>

#include "../Common/Types.h"
#include "BasicContext.h"
#include "StandardContext.h"
#include "ChtlContext.h"
#include "CssContext.h"
#include "JsContext.h"
#include "Chtl_JsContext.h"

namespace CHTL
{
    class ContextFactory
    {
    public:
        static std::unique_ptr<BasicContext> create(LanguageMode mode)
        {
            switch (mode)
            {
            case LanguageMode::Standard: return std::make_unique<StandardContext>();
            case LanguageMode::Chtl:     return std::make_unique<ChtlContext>();
            case LanguageMode::Css:      return std::make_unique<CssContext>();
            case LanguageMode::Js:       return std::make_unique<JsContext>();
            case LanguageMode::ChtlJs:   return std::make_unique<Chtl_JsContext>();
            case LanguageMode::Config:   return std::make_unique<StandardContext>();
            }
            return std::make_unique<StandardContext>();
        }
    };
}