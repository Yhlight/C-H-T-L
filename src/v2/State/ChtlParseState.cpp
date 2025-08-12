#include "v2/State/ChtlParseState.h"

namespace chtl::v2 {

const char* getStateName(ChtlParseState state) {
    switch (state) {
        case ChtlParseState::TOP_LEVEL: return "TOP_LEVEL";
        case ChtlParseState::TEMPLATE_DECLARATION: return "TEMPLATE_DECLARATION";
        case ChtlParseState::CUSTOM_DECLARATION: return "CUSTOM_DECLARATION";
        case ChtlParseState::IMPORT_DECLARATION: return "IMPORT_DECLARATION";
        case ChtlParseState::CONFIG_DECLARATION: return "CONFIG_DECLARATION";
        case ChtlParseState::ORIGIN_DECLARATION: return "ORIGIN_DECLARATION";
        case ChtlParseState::ELEMENT_TAG: return "ELEMENT_TAG";
        case ChtlParseState::ELEMENT_CONTENT: return "ELEMENT_CONTENT";
        case ChtlParseState::ELEMENT_ATTRIBUTES: return "ELEMENT_ATTRIBUTES";
        case ChtlParseState::STYLE_BLOCK: return "STYLE_BLOCK";
        case ChtlParseState::STYLE_SELECTOR: return "STYLE_SELECTOR";
        case ChtlParseState::STYLE_PROPERTY_NAME: return "STYLE_PROPERTY_NAME";
        case ChtlParseState::STYLE_PROPERTY_VALUE: return "STYLE_PROPERTY_VALUE";
        case ChtlParseState::STYLE_TEXT_CONTENT: return "STYLE_TEXT_CONTENT";
        case ChtlParseState::SCRIPT_BLOCK: return "SCRIPT_BLOCK";
        case ChtlParseState::SCRIPT_CONTENT: return "SCRIPT_CONTENT";
        case ChtlParseState::TEXT_BLOCK: return "TEXT_BLOCK";
        case ChtlParseState::TEXT_CONTENT: return "TEXT_CONTENT";
        case ChtlParseState::ELEMENT_REFERENCE: return "ELEMENT_REFERENCE";
        case ChtlParseState::STYLE_REFERENCE: return "STYLE_REFERENCE";
        case ChtlParseState::VAR_REFERENCE: return "VAR_REFERENCE";
        case ChtlParseState::EXPRESSION: return "EXPRESSION";
        case ChtlParseState::STRING_LITERAL: return "STRING_LITERAL";
        case ChtlParseState::TEMPLATE_PARAMETER: return "TEMPLATE_PARAMETER";
        case ChtlParseState::CHTL_JS_EXPRESSION: return "CHTL_JS_EXPRESSION";
        case ChtlParseState::CHTL_JS_SELECTOR: return "CHTL_JS_SELECTOR";
        case ChtlParseState::INHERIT_OPERATION: return "INHERIT_OPERATION";
        case ChtlParseState::DELETE_OPERATION: return "DELETE_OPERATION";
        case ChtlParseState::INSERT_OPERATION: return "INSERT_OPERATION";
        default: return "UNKNOWN";
    }
}

bool isDeclarationState(ChtlParseState state) {
    switch (state) {
        case ChtlParseState::TEMPLATE_DECLARATION:
        case ChtlParseState::CUSTOM_DECLARATION:
        case ChtlParseState::IMPORT_DECLARATION:
        case ChtlParseState::CONFIG_DECLARATION:
        case ChtlParseState::ORIGIN_DECLARATION:
            return true;
        default:
            return false;
    }
}

bool isReferenceState(ChtlParseState state) {
    switch (state) {
        case ChtlParseState::ELEMENT_REFERENCE:
        case ChtlParseState::STYLE_REFERENCE:
        case ChtlParseState::VAR_REFERENCE:
            return true;
        default:
            return false;
    }
}

bool allowsNestedElements(ChtlParseState state) {
    switch (state) {
        case ChtlParseState::ELEMENT_CONTENT:
        case ChtlParseState::TEMPLATE_DECLARATION:
        case ChtlParseState::CUSTOM_DECLARATION:
            return true;
        default:
            return false;
    }
}

} // namespace chtl::v2