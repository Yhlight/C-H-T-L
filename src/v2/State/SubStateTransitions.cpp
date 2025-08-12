#include "v2/State/ChtlStateMachine.h"
#include "v2/Lexer/Token.h"
#include <iostream>

namespace chtl::v2 {

void ChtlStateMachine::registerElementSubStateTransitions() {
    // ELEMENT + ELEMENT_TAG 状态的转换
    StateKey tagKey{ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_TAG};
    std::vector<StateTransition>& tagRules = transitions_[tagKey];
    
    // # -> ELEMENT_ID
    tagRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::HASH);
        },
        ChtlParseState::ELEMENT,
        ChtlSubState::ELEMENT_ID,
        [](ParseContext& ctx) {
            // 准备收集 ID
        }
    });
    
    // . -> ELEMENT_CLASS
    tagRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::DOT);
        },
        ChtlParseState::ELEMENT,
        ChtlSubState::ELEMENT_CLASS,
        nullptr
    });
    
    // 标识符 -> ELEMENT_ATTR_NAME
    tagRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::IDENTIFIER) && 
                   !token.metadata.isHtmlTag;
        },
        ChtlParseState::ELEMENT,
        ChtlSubState::ELEMENT_ATTR_NAME,
        [](ParseContext& ctx) {
            // 开始属性
        }
    });
    
    // { -> ELEMENT_CONTENT
    tagRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::ELEMENT_CONTENT,
        ChtlSubState::NONE,
        nullptr
    });
    
    // ELEMENT + ELEMENT_ID 状态的转换
    StateKey idKey{ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_ID};
    std::vector<StateTransition>& idRules = transitions_[idKey];
    
    // 标识符 -> 收集 ID，回到 ELEMENT_TAG
    idRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::IDENTIFIER);
        },
        ChtlParseState::ELEMENT,
        ChtlSubState::ELEMENT_TAG,
        [](ParseContext& ctx) {
            // ID 已收集
        }
    });
    
    // ELEMENT + ELEMENT_CLASS 状态的转换
    StateKey classKey{ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_CLASS};
    std::vector<StateTransition>& classRules = transitions_[classKey];
    
    // 标识符 -> 收集类名
    classRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::IDENTIFIER);
        },
        ChtlParseState::ELEMENT,
        ChtlSubState::ELEMENT_TAG,
        [](ParseContext& ctx) {
            // 类名已收集
        }
    });
    
    // ELEMENT + ELEMENT_ATTR_NAME 状态的转换
    StateKey attrNameKey{ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_ATTR_NAME};
    std::vector<StateTransition>& attrNameRules = transitions_[attrNameKey];
    
    // = -> ELEMENT_ATTR_VALUE
    attrNameRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::EQUALS);
        },
        ChtlParseState::ELEMENT,
        ChtlSubState::ELEMENT_ATTR_VALUE,
        nullptr
    });
    
    // ELEMENT + ELEMENT_ATTR_VALUE 状态的转换
    StateKey attrValueKey{ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_ATTR_VALUE};
    std::vector<StateTransition>& attrValueRules = transitions_[attrValueKey];
    
    // 字符串或标识符 -> 收集值，回到 ELEMENT_TAG
    attrValueRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::STRING) || 
                   token.is(TokenType::IDENTIFIER);
        },
        ChtlParseState::ELEMENT,
        ChtlSubState::ELEMENT_TAG,
        [](ParseContext& ctx) {
            // 属性值已收集
        }
    });
}

void ChtlStateMachine::registerStyleContentSubStateTransitions() {
    // STYLE_CONTENT + CSS_SELECTOR 状态的转换
    StateKey selectorKey{ChtlParseState::STYLE_CONTENT, ChtlSubState::CSS_SELECTOR};
    std::vector<StateTransition>& selectorRules = transitions_[selectorKey];
    
    // : -> CSS_PSEUDO
    selectorRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::COLON);
        },
        ChtlParseState::STYLE_CONTENT,
        ChtlSubState::CSS_PSEUDO,
        nullptr
    });
    
    // > + ~ -> CSS_COMBINATOR
    selectorRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.value == ">" || 
                   token.value == "+" || 
                   token.value == "~";
        },
        ChtlParseState::STYLE_CONTENT,
        ChtlSubState::CSS_COMBINATOR,
        nullptr
    });
}

void ChtlStateMachine::registerDeclarationSubStateTransitions() {
    // DECLARATION + DECLARATION_TYPE 状态的转换
    StateKey typeKey{ChtlParseState::DECLARATION, ChtlSubState::DECLARATION_TYPE};
    std::vector<StateTransition>& typeRules = transitions_[typeKey];
    
    // @Element, @Style 等 -> DECLARATION_NAME
    typeRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.isReference();
        },
        ChtlParseState::DECLARATION,
        ChtlSubState::DECLARATION_NAME,
        nullptr
    });
    
    // DECLARATION + DECLARATION_NAME 状态的转换
    StateKey nameKey{ChtlParseState::DECLARATION, ChtlSubState::DECLARATION_NAME};
    std::vector<StateTransition>& nameRules = transitions_[nameKey];
    
    // ( -> DECLARATION_PARAMS
    nameRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::LEFT_PAREN);
        },
        ChtlParseState::DECLARATION,
        ChtlSubState::DECLARATION_PARAMS,
        nullptr
    });
}

void ChtlStateMachine::registerReferenceSubStateTransitions() {
    // REFERENCE + REFERENCE_TYPE 状态的转换
    StateKey typeKey{ChtlParseState::REFERENCE, ChtlSubState::REFERENCE_TYPE};
    std::vector<StateTransition>& typeRules = transitions_[typeKey];
    
    // 标识符 -> REFERENCE_NAME
    typeRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::IDENTIFIER);
        },
        ChtlParseState::REFERENCE,
        ChtlSubState::REFERENCE_NAME,
        nullptr
    });
    
    // REFERENCE + REFERENCE_NAME 状态的转换
    StateKey nameKey{ChtlParseState::REFERENCE, ChtlSubState::REFERENCE_NAME};
    std::vector<StateTransition>& nameRules = transitions_[nameKey];
    
    // ( -> REFERENCE_ARGS
    nameRules.push_back({
        [](const Token& token, ChtlContext ctx, ChtlSubState sub) {
            return token.is(TokenType::LEFT_PAREN);
        },
        ChtlParseState::REFERENCE,
        ChtlSubState::REFERENCE_ARGS,
        nullptr
    });
}

} // namespace chtl::v2