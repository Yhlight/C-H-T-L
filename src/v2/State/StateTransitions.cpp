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
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::INITIAL];
    
    // [ -> DECLARATION (仅在全局上下文)
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::LEFT_BRACKET) && 
                   context == ChtlContext::GLOBAL;
        },
        ChtlParseState::DECLARATION,
        [](ParseContext& ctx) {
            ctx.getDeclarationData().isDefinition = true;
            std::cerr << "[Transition] INITIAL -> DECLARATION (definition)\n";
        }
    });
    
    // @ -> REFERENCE (不应在全局出现，但处理错误情况)
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::AT) && 
                   context == ChtlContext::GLOBAL;
        },
        ChtlParseState::INITIAL,  // 保持状态，报错
        [](ParseContext& ctx) {
            std::cerr << "[ERROR] @ references not allowed at top level\n";
        }
    });
    
    // style -> STYLE
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::STYLE);
        },
        ChtlParseState::STYLE,
        [](ParseContext& ctx) {
            std::cerr << "[Transition] INITIAL -> STYLE\n";
        }
    });
    
    // script -> SCRIPT
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::SCRIPT);
        },
        ChtlParseState::SCRIPT,
        nullptr
    });
    
    // HTML 元素
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::IDENTIFIER) && 
                   token.metadata.isHtmlTag;
        },
        ChtlParseState::ELEMENT,
        [](ParseContext& ctx) {
            ctx.resetElementData();
        }
    });
}

void ChtlStateMachine::registerElementTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::ELEMENT];
    
    // # -> 收集 ID
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::HASH);
        },
        ChtlParseState::ELEMENT,  // 保持在元素状态
        [](ParseContext& ctx) {
            // 准备收集 ID
            ctx.getElementData().id = "";  // 将在下一个标识符中填充
        }
    });
    
    // . -> 收集类名
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::DOT);
        },
        ChtlParseState::ELEMENT,  // 保持在元素状态
        nullptr
    });
    
    // { -> ELEMENT_CONTENT
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::ELEMENT_CONTENT,
        nullptr
    });
}

void ChtlStateMachine::registerStyleTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::STYLE];
    
    // { -> STYLE_CONTENT
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::STYLE_CONTENT,
        [](ParseContext& ctx) {
            ctx.resetContent();
            ctx.getCssContent() = "";
        }
    });
}

// ELEMENT_CONTENT 状态的转换
void ChtlStateMachine::registerElementContentTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::ELEMENT_CONTENT];
    
    // [ -> REFERENCE (局部上下文中是引用)
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::LEFT_BRACKET) && 
                   context == ChtlContext::LOCAL;
        },
        ChtlParseState::REFERENCE,
        [](ParseContext& ctx) {
            ctx.getDeclarationData().isDefinition = false;
            std::cerr << "[Transition] ELEMENT_CONTENT -> REFERENCE\n";
        }
    });
    
    // @ -> REFERENCE
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::AT);
        },
        ChtlParseState::REFERENCE,
        [](ParseContext& ctx) {
            ctx.getDeclarationData().isDefinition = false;
        }
    });
    
    // style -> STYLE (局部样式)
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::STYLE);
        },
        ChtlParseState::STYLE,
        [](ParseContext& ctx) {
            std::cerr << "[Transition] ELEMENT_CONTENT -> STYLE (local)\n";
        }
    });
    
    // script -> SCRIPT (局部脚本)
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::SCRIPT);
        },
        ChtlParseState::SCRIPT,
        nullptr
    });
    
    // text -> TEXT
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::TEXT);
        },
        ChtlParseState::TEXT,
        nullptr
    });
    
    // 嵌套元素
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::IDENTIFIER) && 
                   token.metadata.isHtmlTag;
        },
        ChtlParseState::ELEMENT,
        nullptr
    });
    
    // } -> 退出
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::RIGHT_BRACE);
        },
        ChtlParseState::ELEMENT_CONTENT,  // 保持状态，由解析器处理
        [this](ParseContext& ctx) {
            std::cerr << "[Transition] ELEMENT_CONTENT: '}' - should exit\n";
        }
    });
}

// STYLE_CONTENT 状态的转换
void ChtlStateMachine::registerStyleContentTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::STYLE_CONTENT];
    
    // 在 STYLE_CONTENT 中，整块收集内容
    // 只需要处理 text { } 的情况
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::TEXT);
        },
        ChtlParseState::TEXT,
        [](ParseContext& ctx) {
            // 标记这是 CSS 文本
            std::cerr << "[Transition] STYLE_CONTENT -> TEXT (for CSS)\n";
        }
    });
    
    // 其他所有内容都收集到 cssContent
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return !token.is(TokenType::RIGHT_BRACE) || 
                   token.metadata.contextHint == "nested";
        },
        ChtlParseState::STYLE_CONTENT,  // 保持状态
        [](ParseContext& ctx) {
            // 收集 CSS 内容
        }
    });
    
    // } -> 退出样式块
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::RIGHT_BRACE) && 
                   token.metadata.contextHint != "nested";
        },
        ChtlParseState::STYLE_CONTENT,  // 保持状态，由解析器处理
        nullptr
    });
}

void ChtlStateMachine::registerDeclarationTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::DECLARATION];
    
    // 在 DECLARATION 状态，收集声明内容
    // Template, Custom, Import 等
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::TEMPLATE) ||
                   token.is(TokenType::CUSTOM) ||
                   token.is(TokenType::IMPORT);
        },
        ChtlParseState::DECLARATION,  // 保持状态
        [](ParseContext& ctx) {
            // 记录声明类型
        }
    });
    
    // ] -> 声明结束
    rules.push_back({
        [](const Token& token, ChtlContext context) {
            return token.is(TokenType::RIGHT_BRACKET);
        },
        ChtlParseState::DECLARATION,  // 保持状态，由解析器处理后续
        nullptr
    });
}

} // namespace chtl::v2