#include "v2/State/ChtlStateMachine.h"
#include "v2/Lexer/Token.h"
#include <iostream>

namespace chtl::v2 {

void ChtlStateMachine::registerTransitions() {
    // 清空现有规则
    transitions_.clear();
    
    // 注册各状态的转换规则
    registerTopLevelTransitions();
    registerElementContentTransitions();
    registerStyleBlockTransitions();
    registerTemplateDeclarationTransitions();
    registerScriptBlockTransitions();
    registerTextBlockTransitions();
    // TODO: 注册其他状态的转换规则
}

void ChtlStateMachine::registerTopLevelTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::TOP_LEVEL];
    
    // [Template] -> TEMPLATE_DECLARATION
    rules.push_back({
        // 条件：遇到 [ 后跟 Template
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::LEFT_BRACKET);
        },
        ChtlParseState::TEMPLATE_DECLARATION,
        // 动作：准备模板上下文
        [](ParseContext& ctx) {
            ctx.getTemplateData().isDefinition = true;
            ctx.enterScope("template");
        }
    });
    
    // style -> STYLE_BLOCK (全局样式)
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::STYLE);
        },
        ChtlParseState::STYLE_BLOCK,
        [](ParseContext& ctx) {
            std::cerr << "[Transition] TOP_LEVEL -> STYLE_BLOCK (global)\n";
        }
    });
    
    // script -> SCRIPT_BLOCK (全局脚本)
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::SCRIPT);
        },
        ChtlParseState::SCRIPT_BLOCK,
        nullptr
    });
    
    // HTML 元素 -> ELEMENT_TAG
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::IDENTIFIER) && 
                   token.metadata.isHtmlTag;
        },
        ChtlParseState::ELEMENT_TAG,
        [](ParseContext& ctx) {
            ctx.getElementData().tagName = ctx.getCurrentNode()->getValue();
        }
    });
    
    // Import 语句
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::IMPORT) ||
                   (token.is(TokenType::IDENTIFIER) && token.value == "Import");
        },
        ChtlParseState::IMPORT_DECLARATION,
        nullptr
    });
}

void ChtlStateMachine::registerElementContentTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::ELEMENT_CONTENT];
    
    // style -> STYLE_BLOCK (局部样式)
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::STYLE);
        },
        ChtlParseState::STYLE_BLOCK,
        [](ParseContext& ctx) {
            ctx.getElementData().hasLocalStyle = true;
            std::cerr << "[Transition] ELEMENT_CONTENT -> STYLE_BLOCK (local)\n";
        }
    });
    
    // script -> SCRIPT_BLOCK (局部脚本)
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::SCRIPT);
        },
        ChtlParseState::SCRIPT_BLOCK,
        [](ParseContext& ctx) {
            ctx.getElementData().hasLocalScript = true;
        }
    });
    
    // text -> TEXT_BLOCK
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::TEXT);
        },
        ChtlParseState::TEXT_BLOCK,
        nullptr
    });
    
    // @Element -> ELEMENT_REFERENCE (模板引用)
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::AT_ELEMENT);
        },
        ChtlParseState::ELEMENT_REFERENCE,
        [](ParseContext& ctx) {
            ctx.getTemplateData().isDefinition = false;
        }
    });
    
    // 嵌套元素
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::IDENTIFIER) && 
                   token.metadata.isHtmlTag;
        },
        ChtlParseState::ELEMENT_TAG,
        nullptr
    });
    
    // } -> 返回上一状态
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::RIGHT_BRACE);
        },
        ChtlParseState::ELEMENT_CONTENT,  // 保持当前状态，由解析器处理返回
        [this](ParseContext& ctx) {
            // 这里应该由解析器调用 popState()
            std::cerr << "[Transition] ELEMENT_CONTENT: '}' encountered\n";
        }
    });
}

void ChtlStateMachine::registerStyleBlockTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::STYLE_BLOCK];
    
    // { -> 进入样式内容
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::STYLE_BLOCK,  // 保持状态
        nullptr
    });
    
    // text -> STYLE_TEXT_CONTENT (用于全局样式的 text { "css" })
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::TEXT);
        },
        ChtlParseState::TEXT_BLOCK,
        [](ParseContext& ctx) {
            // 标记这是样式文本
            ctx.getCssData().currentPropertyName = "__style_text__";
        }
    });
    
    // 选择器：. 或 # 或标识符
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::DOT) || 
                   token.is(TokenType::HASH) ||
                   (token.is(TokenType::IDENTIFIER) && 
                    !token.metadata.isCssProperty);
        },
        ChtlParseState::STYLE_SELECTOR,
        [](ParseContext& ctx) {
            ctx.getCssData().currentSelector = "";
        }
    });
    
    // CSS 属性名
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::IDENTIFIER) && 
                   token.metadata.isCssProperty;
        },
        ChtlParseState::STYLE_PROPERTY_NAME,
        [](ParseContext& ctx) {
            ctx.getCssData().currentPropertyName = "";
        }
    });
    
    // : -> 属性值
    rules.push_back({
        [](const Token& token, const ParseContext& ctx) {
            return token.is(TokenType::COLON) && 
                   ctx.getState() == ChtlParseState::STYLE_PROPERTY_NAME;
        },
        ChtlParseState::STYLE_PROPERTY_VALUE,
        [](ParseContext& ctx) {
            ctx.getCssData().inPropertyValue = true;
        }
    });
    
    // } -> 返回
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::RIGHT_BRACE);
        },
        ChtlParseState::STYLE_BLOCK,  // 保持状态，由解析器处理
        nullptr
    });
}

void ChtlStateMachine::registerTemplateDeclarationTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::TEMPLATE_DECLARATION];
    
    // @Element Name(params) -> 继续在模板声明中
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::AT_ELEMENT);
        },
        ChtlParseState::TEMPLATE_DECLARATION,  // 保持状态
        nullptr
    });
    
    // { -> ELEMENT_CONTENT (模板体)
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::ELEMENT_CONTENT,
        [](ParseContext& ctx) {
            // 模板体是元素内容
            ctx.enterScope("template-body");
        }
    });
    
    // 参数名
    rules.push_back({
        [](const Token& token, const ParseContext& ctx) {
            return token.is(TokenType::IDENTIFIER) && 
                   ctx.getTemplateData().templateName.empty();
        },
        ChtlParseState::TEMPLATE_DECLARATION,
        [](ParseContext& ctx) {
            // 这应该是模板名
        }
    });
}

void ChtlStateMachine::registerScriptBlockTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::SCRIPT_BLOCK];
    
    // { -> SCRIPT_CONTENT
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::SCRIPT_CONTENT,
        nullptr
    });
}

void ChtlStateMachine::registerTextBlockTransitions() {
    std::vector<StateTransition>& rules = transitions_[ChtlParseState::TEXT_BLOCK];
    
    // { -> TEXT_CONTENT
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::LEFT_BRACE);
        },
        ChtlParseState::TEXT_CONTENT,
        nullptr
    });
    
    // 字符串字面量
    rules.push_back({
        [](const Token& token, const ParseContext&) {
            return token.is(TokenType::STRING);
        },
        ChtlParseState::TEXT_CONTENT,
        nullptr
    });
}

} // namespace chtl::v2