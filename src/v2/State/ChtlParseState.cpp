#include "v2/State/ChtlParseState.h"
#include <string>

namespace chtl::v2 {

const char* getStateName(ChtlParseState state) {
    switch (state) {
        case ChtlParseState::INITIAL: return "INITIAL";
        case ChtlParseState::ELEMENT: return "ELEMENT";
        case ChtlParseState::STYLE: return "STYLE";
        case ChtlParseState::SCRIPT: return "SCRIPT";
        case ChtlParseState::TEXT: return "TEXT";
        case ChtlParseState::ELEMENT_CONTENT: return "ELEMENT_CONTENT";
        case ChtlParseState::STYLE_CONTENT: return "STYLE_CONTENT";
        case ChtlParseState::SCRIPT_CONTENT: return "SCRIPT_CONTENT";
        case ChtlParseState::TEXT_CONTENT: return "TEXT_CONTENT";
        case ChtlParseState::DECLARATION: return "DECLARATION";
        case ChtlParseState::REFERENCE: return "REFERENCE";
        case ChtlParseState::STRING_LITERAL: return "STRING_LITERAL";
        case ChtlParseState::EXPRESSION: return "EXPRESSION";
        case ChtlParseState::CHTL_JS: return "CHTL_JS";
        default: return "UNKNOWN";
    }
}

const char* getContextName(ChtlContext context) {
    switch (context) {
        case ChtlContext::GLOBAL: return "GLOBAL";
        case ChtlContext::LOCAL: return "LOCAL";
        default: return "UNKNOWN";
    }
}

const char* getSubStateName(ChtlSubState subState) {
    switch (subState) {
        case ChtlSubState::NONE: return "NONE";
        
        // Element sub-states
        case ChtlSubState::ELEMENT_TAG: return "ELEMENT_TAG";
        case ChtlSubState::ELEMENT_ID: return "ELEMENT_ID";
        case ChtlSubState::ELEMENT_CLASS: return "ELEMENT_CLASS";
        case ChtlSubState::ELEMENT_ATTR_NAME: return "ELEMENT_ATTR_NAME";
        case ChtlSubState::ELEMENT_ATTR_VALUE: return "ELEMENT_ATTR_VALUE";
        
        // CSS sub-states
        case ChtlSubState::CSS_SELECTOR: return "CSS_SELECTOR";
        case ChtlSubState::CSS_PSEUDO: return "CSS_PSEUDO";
        case ChtlSubState::CSS_COMBINATOR: return "CSS_COMBINATOR";
        
        // Declaration sub-states
        case ChtlSubState::DECLARATION_TYPE: return "DECLARATION_TYPE";
        case ChtlSubState::DECLARATION_NAME: return "DECLARATION_NAME";
        case ChtlSubState::DECLARATION_PARAMS: return "DECLARATION_PARAMS";
        
        // Reference sub-states
        case ChtlSubState::REFERENCE_TYPE: return "REFERENCE_TYPE";
        case ChtlSubState::REFERENCE_NAME: return "REFERENCE_NAME";
        case ChtlSubState::REFERENCE_ARGS: return "REFERENCE_ARGS";
        
        // Expression sub-states
        case ChtlSubState::EXPR_LITERAL: return "EXPR_LITERAL";
        case ChtlSubState::EXPR_VARIABLE: return "EXPR_VARIABLE";
        case ChtlSubState::EXPR_FUNCTION: return "EXPR_FUNCTION";
        
        default: return "UNKNOWN";
    }
}

bool isBlockState(ChtlParseState state) {
    return state == ChtlParseState::ELEMENT ||
           state == ChtlParseState::STYLE ||
           state == ChtlParseState::SCRIPT ||
           state == ChtlParseState::TEXT ||
           state == ChtlParseState::DECLARATION;
}

bool isContentState(ChtlParseState state) {
    return state == ChtlParseState::ELEMENT_CONTENT ||
           state == ChtlParseState::STYLE_CONTENT ||
           state == ChtlParseState::SCRIPT_CONTENT ||
           state == ChtlParseState::TEXT_CONTENT;
}

bool needsAnalyzer(ChtlParseState state) {
    return state == ChtlParseState::STYLE_CONTENT ||
           state == ChtlParseState::SCRIPT_CONTENT;
}

} // namespace chtl::v2