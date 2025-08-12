#include "v2/State/ChtlStateMachine.h"
#include "v2/Lexer/Token.h"
#include <iostream>

namespace chtl::v2 {

void ChtlStateMachine::registerTransitions() {
    // 清空现有规则
    transitions_.clear();
    
    // 注册各状态的转换规则
    registerInitialTransitions();
    registerElementTransitions();
    registerStyleTransitions();
    registerDeclarationTransitions();
    // TODO: 注册其他状态的转换规则
}

void ChtlStateMachine::registerInitialTransitions() {
    // [ -> DECLARATION (仅在全局上下文)
    addTransition(ChtlParseState::INITIAL, ChtlSubState::NONE,
        [](const Token& token, ChtlContext context, ChtlSubState) {
            return token.is(TokenType::LEFT_BRACKET) && 
                   context == ChtlContext::GLOBAL;
        },
        ChtlParseState::DECLARATION, ChtlSubState::NONE,
        [](ParseContext& ctx) {
            ctx.getDeclarationData().isDefinition = true;
        }
    );
    
    // @ -> REFERENCE (总是引用)
    addTransition(ChtlParseState::INITIAL, ChtlSubState::NONE,
        [](const Token& token, ChtlContext, ChtlSubState) {
            return token.is(TokenType::AT) || token.is(TokenType::AT_ELEMENT);
        },
        ChtlParseState::REFERENCE, ChtlSubState::NONE
    );
    
    // <style> -> STYLE (全局样式)
    addTransition(ChtlParseState::INITIAL, ChtlSubState::NONE,
        [](const Token& token, ChtlContext, ChtlSubState) {
            return token.is(TokenType::IDENTIFIER) && token.value == "style";
            // TODO: 更精确的检测需要查看前一个 token 是否是 <
        },
        ChtlParseState::STYLE, ChtlSubState::NONE,
        [](ParseContext& ctx) {
            // 开始收集样式内容
        }
    );
    
    // <script> -> SCRIPT (全局脚本)
    addTransition(ChtlParseState::INITIAL, ChtlSubState::NONE,
        [](const Token& token, ChtlContext, ChtlSubState) {
            return token.is(TokenType::IDENTIFIER) && token.value == "script";
            // TODO: 更精确的检测需要查看前一个 token 是否是 <
        },
        ChtlParseState::SCRIPT, ChtlSubState::NONE,
        [](ParseContext& ctx) {
            // 开始收集脚本内容
        }
    );
    
    // HTML标签 -> ELEMENT
    addTransition(ChtlParseState::INITIAL, ChtlSubState::NONE,
        [](const Token& token, ChtlContext, ChtlSubState) {
            return token.is(TokenType::IDENTIFIER) && token.metadata.isHtmlTag;
        },
        ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_TAG
    );
}

void ChtlStateMachine::registerElementTransitions() {
    // { -> ELEMENT_CONTENT
    addTransition(ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_TAG,
        [](const Token& token, ChtlContext, ChtlSubState) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::ELEMENT_CONTENT, ChtlSubState::NONE,
        [](ParseContext& ctx) {
            // 进入元素内容，切换到局部上下文
        }
    );
    
    // # -> ELEMENT_ID
    addTransition(ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_TAG,
        [](const Token& token, ChtlContext, ChtlSubState) {
            return token.is(TokenType::HASH);
        },
        ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_ID
    );
    
    // . -> ELEMENT_CLASS
    addTransition(ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_TAG,
        [](const Token& token, ChtlContext, ChtlSubState) {
            return token.is(TokenType::DOT);
        },
        ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_CLASS
    );
}

void ChtlStateMachine::registerStyleTransitions() {
    // { -> STYLE_CONTENT (收集整块内容)
    addTransition(ChtlParseState::STYLE, ChtlSubState::NONE,
        [](const Token& token, ChtlContext, ChtlSubState) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::STYLE_CONTENT, ChtlSubState::NONE,
        [](ParseContext& ctx) {
            // 开始收集 CSS 内容
        }
    );
}

void ChtlStateMachine::registerScriptTransitions() {
    // TODO: 实现脚本状态转换
}

void ChtlStateMachine::registerDeclarationTransitions() {
    // TODO: 实现声明状态转换
}

void ChtlStateMachine::registerReferenceTransitions() {
    // TODO: 实现引用状态转换
}

} // namespace chtl::v2