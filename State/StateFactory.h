#pragma once

#include <memory>

#include "../Common/Types.h"
#include "BasicState.h"
#include "StandardState.h"
#include "ChtlState.h"
#include "CssState.h"
#include "JsState.h"
#include "Chtl_JsState.h"

namespace CHTL
{
    class StateFactory
    {
    public:
        static std::unique_ptr<BasicState> create(LanguageMode mode)
        {
            switch (mode)
            {
            case LanguageMode::Standard: return std::make_unique<StandardState>();
            case LanguageMode::Chtl:     return std::make_unique<ChtlState>();
            case LanguageMode::Css:      return std::make_unique<CssState>();
            case LanguageMode::Js:       return std::make_unique<JsState>();
            case LanguageMode::ChtlJs:   return std::make_unique<Chtl_JsState>();
            case LanguageMode::Config:   return std::make_unique<StandardState>();
            }
            return std::make_unique<StandardState>();
        }
    };
}