#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Node.h"
#include "Node/Element.h"
#include "Node/Text.h"
#include "Node/Comment.h"
#include "Node/Template.h"
#include "Node/Custom.h"
#include "Node/Style.h"

#include "Node/Config.h"
#include "Node/Import.h"
#include "Node/Namespace.h"
#include "Node/Operate.h"
#include "Node/Origin.h"
#include "Node/Info.h"
#include "Node/Export.h"
#include "Node/Script.h"
#include "Runtime/ChtlJsRuntime.h"
#include <algorithm>
#include <cctype>


namespace chtl {

StandardParser::StandardParser(std::shared_ptr<BasicLexer> lexer, std::shared_ptr<BasicContext> context)
    : BasicParser(),
      currentToken_(TokenType::EOF_TOKEN, "", 1, 1),
      previousToken_(TokenType::EOF_TOKEN, "", 1, 1) {
    // 初始化lexer和context
    initialize(lexer, context);
}

std::shared_ptr<Node> StandardParser::parse() {
    auto root = std::make_shared<Element>("document");
    root->setTagName("document");
    
    // 初始化第一个token
    currentToken_ = getNextToken();
    
    try {
        while (!isAtEnd()) {
            skipWhitespaceAndComments();

            if (isAtEnd()) break;
            
            auto node = parseTopLevel();

            if (node) {

                root->addChild(node);
            }
        }
    } catch (const std::exception& e) {
        addError("Parse error: " + std::string(e.what()));
    }
    
    return root;
}

std::shared_ptr<Node> StandardParser::parseTopLevel() {
    skipWhitespaceAndComments();
    

    
    if (isAtEnd()) return nullptr;
    
    // 检查特殊标记，使用更准确的TokenType判断
    if (currentToken_.type == TokenType::TEMPLATE) {
        advance();
        return parseTemplate();
    }
    if (currentToken_.type == TokenType::CUSTOM) {
        advance();
        return parseCustom();
    }
    if (currentToken_.type == TokenType::ORIGIN) {
        advance();
        return parseOrigin();
    }
    if (currentToken_.type == TokenType::CONFIGURATION) {
        advance();
        return parseConfiguration();
    }
    if (currentToken_.type == TokenType::IMPORT) {
        advance();
        return parseImport();
    }
    if (currentToken_.type == TokenType::NAMESPACE_KW) {
        advance();
        return parseNamespace();
    }
    // [Info] 和 [Export] 只在 CMOD 模式下解析
    if (currentToken_.type == TokenType::INFO) {
        if (!isCmodMode_) {
            addWarning("[Info] blocks are only for CMOD files and will be ignored");
            skipBlock();
            return nullptr;
        }
        advance();
        return parseInfo();
    }
    if (currentToken_.type == TokenType::EXPORT) {
        if (!isCmodMode_) {
            addWarning("[Export] blocks are only for CMOD files and will be ignored");
            skipBlock();
            return nullptr;
        }
        advance();
        return parseExport();
    }
    if (currentToken_.type == TokenType::SCRIPT) {
        advance();
        return parseScript();
    }
    
    // 检查特殊标记（以[开头）- 备用方案
    if (currentToken_.type == TokenType::LEFT_BRACKET) {
        return parseSpecialBlock();
    }
    
    // 检查Import语句 (Import @Chtl from "...")
    if (currentToken_.type == TokenType::IDENTIFIER && 
        currentToken_.value == "Import") {
        // std::cout << "DEBUG: Calling parseImportStatement" << std::endl;
        return parseImportStatement();
    }
    
    // 检查 @Element, @Style, @Var 引用
    if (currentToken_.type == TokenType::AT_ELEMENT || 
        currentToken_.type == TokenType::AT_STYLE || 
        currentToken_.type == TokenType::AT_VAR) {
        return parseReference();
    }
    
    // 检查HTML元素
    if (currentToken_.type == TokenType::IDENTIFIER) {
        try {
            return parseNode();  // parseNode 会处理元素
        } catch (const std::exception& e) {
            // 错误恢复：跳到下一个分号或右大括号
            while (!isAtEnd() && 
                   currentToken_.type != TokenType::SEMICOLON &&
                   currentToken_.type != TokenType::RIGHT_BRACE) {
                advance();
            }
            if (currentToken_.type == TokenType::SEMICOLON ||
                currentToken_.type == TokenType::RIGHT_BRACE) {
                advance();
            }
            return nullptr;
        }
    }
    
    // 检查注释
    if (currentToken_.type == TokenType::HTML_COMMENT) {
        return parseComment();
    }
    

    
    // 跳过无法处理的 token 以避免无限循环
    advance();
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseSpecialBlock() {
    consume(TokenType::LEFT_BRACKET, "Expected '['");
    
    auto blockType = consume(TokenType::IDENTIFIER, "Expected block type").value;
    
    consume(TokenType::RIGHT_BRACKET, "Expected ']'");
    
    // 检查是否是全缀名引用
    if ((blockType == "Template" || blockType == "Custom") && 
        (check(TokenType::AT_ELEMENT) || check(TokenType::AT_STYLE) || check(TokenType::AT_VAR))) {
        // 这是一个全缀名引用，解析引用
        auto typeToken = advance(); // @Element/@Style/@Var
        auto nameToken = consume(TokenType::IDENTIFIER, "Expected reference name");
        
        auto refNode = std::make_shared<Element>("reference");
        refNode->setAttribute("type", typeToken.value);
        refNode->setAttribute("name", nameToken.value);
        refNode->setAttribute("kind", blockType);  // Template 或 Custom
        
        // 检查是否有特例化块
        if (check(TokenType::LEFT_BRACE)) {
            consume(TokenType::LEFT_BRACE, "Expected '{'");
            parseSpecialization(refNode);
            consume(TokenType::RIGHT_BRACE, "Expected '}'");
        }
        
        consume(TokenType::SEMICOLON, "Expected ';'");

        return refNode;
    }
    
    // 普通特殊块
    if (blockType == "Template") {
        return parseTemplate();
    } else if (blockType == "Custom") {
        return parseCustom();
    } else if (blockType == "Origin") {
        return parseOrigin();
    } else if (blockType == "Configuration") {
        return parseConfiguration();
    } else if (blockType == "Import") {
        return parseImport();
    } else if (blockType == "Namespace") {
        return parseNamespace();
    } else if (blockType == "Info") {
        if (!isCmodMode_) {
            addWarning("[Info] blocks are only for CMOD files and will be ignored");
            skipBlock();
            return nullptr;
        }
        return parseInfo();
    } else if (blockType == "Export") {
        if (!isCmodMode_) {
            addWarning("[Export] blocks are only for CMOD files and will be ignored");
            skipBlock();
            return nullptr;
        }
        return parseExport();
    } else {
        addError("Unknown block type: " + blockType);
        skipToNextStatement();
        return nullptr;
    }
}

// 添加跳过块的方法
void StandardParser::skipBlock() {
    // 跳过可能的属性或名称
    while (!check(TokenType::LEFT_BRACE) && !check(TokenType::SEMICOLON) && !isAtEnd()) {
        advance();
    }
    
    // 如果是分号结尾，直接结束
    if (match(TokenType::SEMICOLON)) {
        return;
    }
    
    // 如果是大括号，跳过整个块
    if (match(TokenType::LEFT_BRACE)) {
        int braceCount = 1;
        while (braceCount > 0 && !isAtEnd()) {
            if (match(TokenType::LEFT_BRACE)) {
                braceCount++;
            } else if (match(TokenType::RIGHT_BRACE)) {
                braceCount--;
            } else {
                advance();
            }
        }
    }
}

std::shared_ptr<Node> StandardParser::parseElement() {
    // 元素标签名已被消费
    auto nameToken = previousToken_;
    
    auto element = std::make_shared<Element>(nameToken.value);
    
    // 检查是否有索引访问 element[index]
    if (match(TokenType::LEFT_BRACKET)) {
        auto indexToken = consume(TokenType::NUMBER, "Expected index number");
        element->setAttribute("_index", indexToken.value);
        consume(TokenType::RIGHT_BRACKET, "Expected ']'");
    }
    
    // 如果后面直接是分号，说明这是一个引用（如 @Element Box;）
    if (match(TokenType::SEMICOLON)) {
        return element;
    }
    
    // 否则应该有内容块
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查属性
        if (checkAttribute()) {
            parseAttributes(element);
        }
        // 检查except约束
        else if (check(TokenType::EXCEPT)) {
            parseExcept(element);
        }
        // 检查特殊操作（delete, insert）
        else if (check(TokenType::DELETE_KW) || check(TokenType::INSERT)) {
            auto op = parseOperation();
            if (op) {
                element->addChild(op);
            }
        }
        // 检查子元素
        else {
            auto child = parseNode();
            if (child) {
                element->addChild(child);
            }
        }
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    return element;
}

std::shared_ptr<Node> StandardParser::parseNode() {
    // text块
    if (currentToken_.value == "text") {
        advance();  // 消费 'text'
        return parseText();
    }
    
    // style块
    if (currentToken_.value == "style") {
        return parseStyleBlock();
    }
    
    // script块
    if (currentToken_.type == TokenType::SCRIPT_KW) {
        return parseScriptBlock();
    }
    
    // @Element, @Style, @Var引用
    if (currentToken_.type == TokenType::AT_ELEMENT || 
        currentToken_.type == TokenType::AT_STYLE || 
        currentToken_.type == TokenType::AT_VAR) {
        return parseReference();
    }
    
    // 特殊块
    if (currentToken_.type == TokenType::LEFT_BRACKET) {
        return parseSpecialBlock();
    }
    
    // 普通元素
    if (currentToken_.type == TokenType::IDENTIFIER) {
        advance();  // 消费元素名
        return parseElement();
    }
    
    advance();
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseText() {
    // text 关键字已经在 parseNode 中被识别，现在应该在 {
    if (!match(TokenType::LEFT_BRACE)) {
        throw std::runtime_error("Expected '{' after 'text'");
    }
    
    auto textNode = std::make_shared<Text>();
    std::string content;
    
    // 收集文本内容，支持字符串字面量和无引号字面量
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        auto token = advance();
        
        if (token.type == TokenType::STRING_LITERAL) {
            content += token.value;
        } else if (token.type == TokenType::UNQUOTED_LITERAL) {
            content += token.value;
        } else if (token.type == TokenType::IDENTIFIER) {
            content += token.value;
        }
        
        // 添加空格分隔
        if (!check(TokenType::RIGHT_BRACE)) {
            content += " ";
        }
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    textNode->setData(content);
    return textNode;
}

bool StandardParser::checkAttribute() {
    if (!check(TokenType::IDENTIFIER)) return false;
    
    // 保存当前lexer位置，而不是修改parser状态
    // 直接查看下一个token而不消费它
    Token nextToken = peekNextToken();
    return nextToken.type == TokenType::COLON || nextToken.type == TokenType::EQUALS;
}

void StandardParser::parseAttributes(std::shared_ptr<Node> element) {
    while (checkAttribute()) {
        auto nameToken = consume(TokenType::IDENTIFIER, "Expected attribute name");
        
        // CE对等式：':'与'='完全等价
        if (!match(TokenType::COLON) && !match(TokenType::EQUALS)) {
            addError("Expected ':' or '=' after attribute name");
            skipToNextStatement();
            return;
        }
        
        // 解析属性值
        std::string value;
        auto valueToken = advance();
        
        if (valueToken.type == TokenType::STRING_LITERAL) {
            value = valueToken.value;
        } else if (valueToken.type == TokenType::UNQUOTED_LITERAL) {
            value = valueToken.value;
        } else if (valueToken.type == TokenType::IDENTIFIER) {
            value = valueToken.value;
        } else if (valueToken.type == TokenType::NUMBER) {
            value = valueToken.value;
        } else {
            addError("Invalid attribute value");
            continue;
        }
        
        element->setAttribute(nameToken.value, value);
        
        consume(TokenType::SEMICOLON, "Expected ';' after attribute");
    }
}

std::shared_ptr<Node> StandardParser::parseStyleBlock() {
    consume(TokenType::IDENTIFIER, "style");
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    auto styleNode = std::make_shared<Style>();
    styleNode->setType(Style::StyleScope::LOCAL);
    
    parseStyleContent(styleNode);
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    return styleNode;
}

std::shared_ptr<Node> StandardParser::parseScriptBlock() {
    consume(TokenType::SCRIPT_KW, "script");
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    auto scriptNode = std::make_shared<Script>();
    
    // 为局部script块生成或获取元素ID
    std::string elementId;
    if (context_) {
        // 从上下文获取当前元素ID（如果有的话）
        // TODO: Get element ID from context if available
        // elementId = context_->getCurrentElementId();
    }
    if (elementId.empty()) {
        auto& runtime = ChtlJsRuntime::getInstance();
        elementId = runtime.generateElementId();
    }
    
    // 收集脚本内容直到遇到匹配的 }
    std::string scriptContent;
    int braceDepth = 1;
    bool inDoubleLeftBrace = false;
    (void)inDoubleLeftBrace; // TODO: 未来可能用于更复杂的语法分析
    
    while (!isAtEnd() && braceDepth > 0) {
        Token token = currentToken_;
        advance();
        
        // 检查 {{ 开始
        if (token.type == TokenType::DOUBLE_LEFT_BRACE) {
            // 检查是否是 {{&}} 模式
            if (!isAtEnd() && currentToken_.type == TokenType::AMPERSAND) {
                Token ampToken = currentToken_;
                advance();
                if (!isAtEnd() && currentToken_.type == TokenType::DOUBLE_RIGHT_BRACE) {
                    advance(); // 消费 }}
                    // 替换 {{&}} 为 {{&}}（保留原样，让运行时处理）
                    scriptContent += "{{&}}";
                    continue;
                } else {
                    // 不是 {{&}} 模式，恢复
                    scriptContent += "{{" + ampToken.value;
                }
            } else {
                // 可能是 {{selector}} 语法
                scriptContent += "{{";
            }
        }
        // 处理大括号以正确计算深度
        else if (token.type == TokenType::LEFT_BRACE) {
            scriptContent += token.value;
            braceDepth++;
        } else if (token.type == TokenType::RIGHT_BRACE) {
            braceDepth--;
            if (braceDepth == 0) {
                break; // 不添加最后的 }
            }
            scriptContent += token.value;
        } else if (token.type == TokenType::DOUBLE_RIGHT_BRACE) {
            scriptContent += "}}";
        } else if (token.type == TokenType::STRING_LITERAL) {
            // 字符串字面量，保留引号
            scriptContent += "\"" + token.value + "\"";
        } else {
            // 对于其他token，添加原始值
            scriptContent += token.value;
        }
        
        // 添加空格（智能处理）
        if (!isAtEnd() && braceDepth > 0) {
            Token next = currentToken_;
            
            // 决定是否需要空格
            bool needSpace = true;
            
            // 以下情况不需要空格
            if (token.type == TokenType::DOT || next.type == TokenType::DOT ||
                token.type == TokenType::LEFT_PAREN || next.type == TokenType::RIGHT_PAREN ||
                token.type == TokenType::LEFT_BRACKET || next.type == TokenType::RIGHT_BRACKET ||
                token.type == TokenType::SEMICOLON || next.type == TokenType::SEMICOLON ||
                token.type == TokenType::COMMA || next.type == TokenType::COMMA ||
                token.type == TokenType::COLON || next.type == TokenType::COLON ||
                token.type == TokenType::DOUBLE_LEFT_BRACE || next.type == TokenType::DOUBLE_LEFT_BRACE ||
                token.type == TokenType::DOUBLE_RIGHT_BRACE || next.type == TokenType::DOUBLE_RIGHT_BRACE ||
                (token.type == TokenType::OPERATOR && token.value == "!") ||
                (token.type == TokenType::IDENTIFIER && next.type == TokenType::LEFT_PAREN)) {
                needSpace = false;
            }
            
            // -> 操作符前后不需要空格
            if ((token.type == TokenType::HYPHEN && next.type == TokenType::OPERATOR && next.value == ">") ||
                (token.type == TokenType::OPERATOR && token.value == ">" && previous().type == TokenType::HYPHEN)) {
                needSpace = false;
            }
            
            if (needSpace) {
                scriptContent += " ";
            }
        }
    }
    
    // 去除首尾空白
    scriptContent.erase(0, scriptContent.find_first_not_of(" \t\n\r"));
    scriptContent.erase(scriptContent.find_last_not_of(" \t\n\r") + 1);
    
    scriptNode->setContent(scriptContent);
    scriptNode->setScriptType(Script::ScriptType::INLINE);  // 局部script块默认为内联类型
    scriptNode->setScope(elementId);  // 设置作用域为元素ID
    
    return scriptNode;
}

void StandardParser::parseStyleContent(std::shared_ptr<Style> styleNode) {
    std::string inlineStyles;  // 收集内联样式
    
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查@Style, @Var引用
        if (check(TokenType::AT_STYLE) || check(TokenType::AT_VAR)) {
            auto ref = parseStyleReference();
            if (ref) {
                styleNode->addChild(ref);
            }
            continue;
        }
        
        // 检查类选择器 .className
        if (check(TokenType::DOT)) {
            parseSelectorBlock(styleNode);
            continue;
        }
        
        // 检查ID选择器 #id
        if (currentToken_.value == "#") {
            parseSelectorBlock(styleNode);
            continue;
        }
        
        // 检查&符号（仅用于伪类和伪元素）
        if (check(TokenType::AMPERSAND)) {
            parseContextSelector(styleNode);
            continue;
        }
        
        // 其他都是内联样式属性
        if (check(TokenType::IDENTIFIER)) {
            std::string property;
            parseCssProperty(property);
            inlineStyles += property;
        } else {
            advance();
        }
    }
    
    // 将收集的内联样式设置到父元素的style属性
    if (!inlineStyles.empty() && styleNode->getParent()) {
        auto parent = styleNode->getParent();
        auto existingStyle = parent->getAttribute("style");
        if (std::holds_alternative<std::string>(existingStyle)) {
            std::string existing = std::get<std::string>(existingStyle);
            if (!existing.empty() && existing.back() != ';') {
                existing += "; ";
            }
            inlineStyles = existing + inlineStyles;
        }
        parent->setAttribute("style", inlineStyles);
    }
}

void StandardParser::parseSelectorBlock(std::shared_ptr<Style> styleNode) {
    std::string selector;
    
    // 解析选择器（.class 或 #id）
    if (match(TokenType::DOT)) {
        selector = ".";
        auto className = consume(TokenType::IDENTIFIER, "Expected class name");
        selector += className.value;
        
        // 自动添加类名到父元素
        if (auto parent = styleNode->getParent()) {
            parent->addClass(className.value);
        }
    } else if (currentToken_.value == "#") {
        advance();
        selector = "#";
        auto idName = consume(TokenType::IDENTIFIER, "Expected id name");
        selector += idName.value;
        
        // 自动设置ID到父元素
        if (auto parent = styleNode->getParent()) {
            parent->setAttribute("id", idName.value);
        }
    }
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // 创建一个全局样式节点
    auto globalStyle = std::make_shared<Style>();
    globalStyle->setType(Style::StyleScope::GLOBAL);
    globalStyle->setSelector(selector);
    
    // 解析样式内容
    std::string cssContent;
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (check(TokenType::IDENTIFIER)) {
            parseCssProperty(cssContent);
        } else {
            advance();
        }
    }
    
    globalStyle->setContent(cssContent);
    
    // 添加到样式节点（后续会被提升到全局）
    styleNode->addChild(globalStyle);
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
}

void StandardParser::parseContextSelector(std::shared_ptr<Style> styleNode) {
    consume(TokenType::AMPERSAND, "&");
    
    // &只能后跟:hover或::before这样的伪类/伪元素
    if (!check(TokenType::COLON)) {
        addError("& must be followed by pseudo-class or pseudo-element");
        skipToNextStatement();
        return;
    }
    
    std::string selector;
    
    // 获取父元素的类名或ID来替换&
    if (auto parent = styleNode->getParent()) {
        auto classes = parent->getClasses();
        if (!classes.empty()) {
            // 优先使用类名
            selector = "." + classes[0];
        } else {
            // 其次使用ID
            auto id = parent->getAttribute("id");
            if (std::holds_alternative<std::string>(id)) {
                selector = "#" + std::get<std::string>(id);
            }
        }
    }
    
    // 如果父元素既没有类名也没有ID，需要自动生成一个类名
    if (selector.empty()) {
        // 基于位置生成唯一类名
        std::string autoClass = "chtl-auto-" + 
            std::to_string(currentToken_.line) + "-" + 
            std::to_string(currentToken_.column);
        
        if (auto parent = styleNode->getParent()) {
            parent->addClass(autoClass);
        }
        selector = "." + autoClass;
    }
    
    // 解析伪类或伪元素
    consume(TokenType::COLON, ":");
    selector += ":";
    
    if (match(TokenType::COLON)) {
        selector += ":";  // 伪元素 ::
    }
    
    auto pseudo = consume(TokenType::IDENTIFIER, "Expected pseudo-class or pseudo-element name");
    selector += pseudo.value;
    
    // 检查是否有括号（如:nth-child(2)）
    if (match(TokenType::LEFT_PAREN)) {
        selector += "(";
        while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
            selector += advance().value;
        }
        consume(TokenType::RIGHT_PAREN, ")");
        selector += ")";
    }
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // 创建全局样式节点
    auto globalStyle = std::make_shared<Style>();
    globalStyle->setType(Style::StyleScope::GLOBAL);
    globalStyle->setSelector(selector);
    
    // 解析样式内容
    std::string cssContent;
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (check(TokenType::IDENTIFIER)) {
            parseCssProperty(cssContent);
        } else {
            advance();
        }
    }
    
    globalStyle->setContent(cssContent);
    
    // 添加到样式节点（后续会被提升到全局）
    styleNode->addChild(globalStyle);
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
}

void StandardParser::parseCssProperty(std::string& cssContent) {
    auto propertyName = consume(TokenType::IDENTIFIER, "Expected property name");
    
    if (!match(TokenType::COLON) && !match(TokenType::EQUALS)) {
        addError("Expected ':' or '=' after property name");
        skipToNextStatement();
        return;
    }
    
    cssContent += propertyName.value + ": ";
    
    // 收集属性值直到分号
    while (!check(TokenType::SEMICOLON) && !isAtEnd()) {
        auto token = advance();
        cssContent += token.value + " ";
    }
    
    consume(TokenType::SEMICOLON, "Expected ';'");
    cssContent += ";\n";
}

std::shared_ptr<Node> StandardParser::parseTemplate() {
    // [Template]已经被消费
    
    // 解析模板类型
    Template::TemplateType templateType;
    std::string templateName;
    
    if (match(TokenType::AT_STYLE)) {
        templateType = Template::TemplateType::STYLE;
        templateName = consume(TokenType::IDENTIFIER, "Expected template name").value;
    } else if (match(TokenType::AT_ELEMENT)) {
        templateType = Template::TemplateType::ELEMENT;
        templateName = consume(TokenType::IDENTIFIER, "Expected template name").value;
    } else if (match(TokenType::AT_VAR)) {
        templateType = Template::TemplateType::VAR;
        templateName = consume(TokenType::IDENTIFIER, "Expected template name").value;
    } else {
        addError("Expected template type (@Style, @Element, or @Var)");
        skipToNextStatement();
        return nullptr;
    }
    
    auto templateNode = std::make_shared<Template>();
    templateNode->setType(templateType);
    templateNode->setName(templateName);
    
    // 检查是否有参数列表
    if (match(TokenType::LEFT_PAREN)) {
        // 解析参数列表
        while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
            auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name").value;
            templateNode->setParameter(paramName, "");  // 模板参数只需要名称
            
            if (!match(TokenType::COMMA)) {
                break;
            }
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')'");
    }
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // 根据模板类型解析内容
    switch (templateType) {
        case Template::TemplateType::STYLE:
            parseStyleTemplateContent(templateNode);
            break;
        case Template::TemplateType::ELEMENT:
            parseElementTemplateContent(templateNode);
            break;
        case Template::TemplateType::VAR:
            parseVarTemplateContent(templateNode);
            break;
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    // 注册到上下文
    context_->registerTemplate(templateName, templateNode);
    
    return templateNode;
}

void StandardParser::parseStyleTemplateContent(std::shared_ptr<Template> templateNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查inherit继承
        if (match(TokenType::INHERIT)) {
            parseInherit(templateNode);
            continue;
        }
        
        // 检查@Style引用（组合式继承）
        if (check(TokenType::AT_STYLE)) {
            auto ref = parseStyleReference();
            if (ref) {
                templateNode->addChild(ref);
            }
            continue;
        }
        
        // CSS属性
        if (checkAttribute()) {
            parseTemplateProperty(templateNode);
        } else {
            advance();
        }
    }
}

void StandardParser::parseElementTemplateContent(std::shared_ptr<Template> templateNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查inherit继承
        if (match(TokenType::INHERIT)) {
            parseInherit(templateNode);
            continue;
        }
        
        // 检查@Element引用
        if (check(TokenType::AT_ELEMENT)) {
            auto ref = parseReference();
            if (ref) {
                templateNode->addChild(ref);
            }
            continue;
        }
        
        // 普通元素
        auto child = parseNode();
        if (child) {
            templateNode->addChild(child);
        }
    }
}

void StandardParser::parseVarTemplateContent(std::shared_ptr<Template> templateNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查inherit继承
        if (match(TokenType::INHERIT)) {
            parseInherit(templateNode);
            continue;
        }
        
        // 检查@Var引用
        if (check(TokenType::AT_VAR)) {
            auto ref = parseReference();
            if (ref) {
                templateNode->addChild(ref);
            }
            continue;
        }
        
        // 变量定义
        if (checkAttribute()) {
            parseTemplateProperty(templateNode);
        } else {
            advance();
        }
    }
}

void StandardParser::parseTemplateProperty(std::shared_ptr<Template> templateNode) {
    auto nameToken = consume(TokenType::IDENTIFIER, "Expected property name");
    
    if (!match(TokenType::COLON) && !match(TokenType::EQUALS)) {
        addError("Expected ':' or '=' after property name");
        skipToNextStatement();
        return;
    }
    
    // 属性值
    std::string value;
    auto valueToken = advance();
    
    if (valueToken.type == TokenType::STRING_LITERAL ||
        valueToken.type == TokenType::UNQUOTED_LITERAL ||
        valueToken.type == TokenType::IDENTIFIER ||
        valueToken.type == TokenType::NUMBER) {
        value = valueToken.value;
    }
    
    templateNode->addProperty(nameToken.value, value);
    
    consume(TokenType::SEMICOLON, "Expected ';'");
}

std::shared_ptr<Node> StandardParser::parseCustom() {
    // [Custom]已经被消费
    
    // 解析自定义类型
    Custom::CustomType customType;
    std::string customName;
    
    if (match(TokenType::AT_STYLE)) {
        customType = Custom::CustomType::STYLE;
        customName = consume(TokenType::IDENTIFIER, "Expected custom name").value;
    } else if (match(TokenType::AT_ELEMENT)) {
        customType = Custom::CustomType::ELEMENT;
        customName = consume(TokenType::IDENTIFIER, "Expected custom name").value;
    } else if (match(TokenType::AT_VAR)) {
        customType = Custom::CustomType::VAR;
        customName = consume(TokenType::IDENTIFIER, "Expected custom name").value;
    } else {
        addError("Expected custom type (@Style, @Element, or @Var)");
        skipToNextStatement();
        return nullptr;
    }
    
    // 创建Custom节点
    auto customNode = std::make_shared<Custom>();
    customNode->setType(customType);
    customNode->setName(customName);
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // 根据类型解析内容
    switch (customType) {
        case Custom::CustomType::STYLE:
            parseCustomStyleContent(customNode);
            break;
        case Custom::CustomType::ELEMENT:
            parseCustomElementContent(customNode);
            break;
        case Custom::CustomType::VAR:
            parseCustomVarContent(customNode);
            break;
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    // 注册到上下文
    context_->registerCustom(customName, customNode);
    
    return customNode;
}

void StandardParser::parseCustomStyleContent(std::shared_ptr<Custom> customNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查inherit继承
        if (match(TokenType::INHERIT)) {
            parseInherit(customNode);
            continue;
        }
        
        // 检查@Style引用
        if (check(TokenType::AT_STYLE)) {
            auto ref = parseStyleReference();
            if (ref) {
                customNode->addChild(ref);
            }
            continue;
        }
        
        // 属性（可能没有值）
        auto nameToken = consume(TokenType::IDENTIFIER, "Expected property name");
        
        // 检查是否有值
        if (match(TokenType::COLON) || match(TokenType::EQUALS)) {
            // 收集值直到分号或逗号
            std::string value;
            while (!check(TokenType::SEMICOLON) && !check(TokenType::COMMA) && 
                   !check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                auto token = advance();
                if (!value.empty() && token.value != " ") {
                    value += " ";
                }
                value += token.value;
            }
            
            // 去除尾部空格
            while (!value.empty() && value.back() == ' ') {
                value.pop_back();
            }
            
            customNode->addProperty(nameToken.value, value);
        } else {
            // 无值属性
            customNode->addProperty(nameToken.value, "");
        }
        
        // 消费分号或逗号
        if (check(TokenType::COMMA)) {
            advance();
        } else if (check(TokenType::SEMICOLON)) {
            advance();
        }
    }
}

void StandardParser::parseCustomElementContent(std::shared_ptr<Custom> customNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查inherit继承
        if (match(TokenType::INHERIT)) {
            parseInherit(customNode);
            continue;
        }
        
        // 元素
        auto child = parseNode();
        if (child) {
            customNode->addChild(child);
        }
    }
}

void StandardParser::parseCustomVarContent(std::shared_ptr<Custom> customNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查inherit继承
        if (match(TokenType::INHERIT)) {
            parseInherit(customNode);
            continue;
        }
        
        // 解析变量定义: name: value;
        if (check(TokenType::IDENTIFIER)) {
            auto nameToken = advance();
            consume(TokenType::COLON, "Expected ':' after variable name");
            
            // 收集值直到分号
            std::string value;
            while (!check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                value += advance().value;
                if (!check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE)) {
                    value += " ";
                }
            }
            
            // 去除尾部空格
            while (!value.empty() && value.back() == ' ') {
                value.pop_back();
            }
            
            customNode->addProperty(nameToken.value, value);
            
            // 消费分号（如果有）
            if (check(TokenType::SEMICOLON)) {
                advance();
            }
        } else {
            addError("Expected variable name");
            skipToNextStatement();
        }
    }
}

void StandardParser::parseInherit(std::shared_ptr<Node> node) {
    // inherit关键字已被消费
    
    // 解析继承的类型和名称
    if (match(TokenType::AT_STYLE) || match(TokenType::AT_ELEMENT) || match(TokenType::AT_VAR)) {
        auto name = consume(TokenType::IDENTIFIER, "Expected name to inherit").value;
        node->addInheritance(previous().value + " " + name);
    } else if (match(TokenType::CUSTOM) || match(TokenType::TEMPLATE)) {
        // [Custom] 或 [Template]
        auto type = previous().value;
        if (match(TokenType::AT_STYLE) || match(TokenType::AT_ELEMENT) || match(TokenType::AT_VAR)) {
            auto name = consume(TokenType::IDENTIFIER, "Expected name to inherit").value;
            node->addInheritance(type + " " + previous().value + " " + name);
        }
    }
    
    consume(TokenType::SEMICOLON, "Expected ';'");
}

std::shared_ptr<Node> StandardParser::parseReference() {
    auto typeToken = advance(); // @Style, @Element, or @Var
    auto nameToken = consume(TokenType::IDENTIFIER, "Expected reference name");
    

    
    auto refNode = std::make_shared<Element>("reference");
    refNode->setAttribute("type", typeToken.value);
    refNode->setAttribute("name", nameToken.value);
    
    // 检查是否有特例化块
    if (check(TokenType::LEFT_BRACE)) {

        consume(TokenType::LEFT_BRACE, "Expected '{'");
        parseSpecialization(refNode);
        consume(TokenType::RIGHT_BRACE, "Expected '}'");
    }
    
    // 检查是否有from子句（命名空间）
    if (match(TokenType::FROM)) {
        // 解析命名空间路径（支持嵌套，如 space.room2）
        std::string namespacePath;
        
        do {
            auto nsToken = consume(TokenType::IDENTIFIER, "Expected namespace name");
            if (!namespacePath.empty()) {
                namespacePath += ".";
            }
            namespacePath += nsToken.value;
        } while (match(TokenType::DOT));
        
        refNode->setAttribute("from", namespacePath);
        
        // 使用命名空间管理器验证和解析引用
        auto nsManager = std::static_pointer_cast<StandardContext>(context_)->getNamespaceManager();
        if (nsManager) {
            // 查找命名空间中的成员
            auto member = nsManager->findMember(namespacePath, nameToken.value);
            if (!member) {
                context_->addWarning("Member '" + nameToken.value + "' not found in namespace '" + namespacePath + "'");
            }
        }
    }
    
    // 分号对于带特例化的引用是可选的
    if (check(TokenType::SEMICOLON)) {
        advance();
    }
    
    return refNode;
}



std::shared_ptr<Node> StandardParser::parseStyleReference() {
    auto typeToken = advance(); // @Style or @Var
    auto nameToken = consume(TokenType::IDENTIFIER, "Expected reference name");
    
    auto refNode = std::make_shared<Element>("reference");
    refNode->setAttribute("type", typeToken.value);
    refNode->setAttribute("name", nameToken.value);
    
    // 变量组可能有参数
    if (typeToken.type == TokenType::AT_VAR && match(TokenType::LEFT_PAREN)) {
        parseVarArguments(refNode);
        consume(TokenType::RIGHT_PAREN, "Expected ')'");
    }
    
    // 检查是否有特例化
    if (check(TokenType::LEFT_BRACE)) {
        consume(TokenType::LEFT_BRACE, "Expected '{'");
        parseSpecialization(refNode);
        consume(TokenType::RIGHT_BRACE, "Expected '}'");
    }
    
    // 检查是否有from子句（命名空间）
    if (match(TokenType::FROM)) {
        // 解析命名空间路径（支持嵌套，如 space.room2）
        std::string namespacePath;
        
        do {
            auto nsToken = consume(TokenType::IDENTIFIER, "Expected namespace name");
            if (!namespacePath.empty()) {
                namespacePath += ".";
            }
            namespacePath += nsToken.value;
        } while (match(TokenType::DOT));
        
        refNode->setAttribute("from", namespacePath);
        
        // 使用命名空间管理器验证和解析引用
        auto nsManager = std::static_pointer_cast<StandardContext>(context_)->getNamespaceManager();
        if (nsManager) {
            // 查找命名空间中的成员
            auto member = nsManager->findMember(namespacePath, nameToken.value);
            if (!member) {
                context_->addWarning("Member '" + nameToken.value + "' not found in namespace '" + namespacePath + "'");
            }
        }
    }
    
    consume(TokenType::SEMICOLON, "Expected ';'");
    
    return refNode;
}

void StandardParser::parseVarArguments(std::shared_ptr<Node> refNode) {
    // 解析变量参数，如 ThemeColor(tableColor = rgb(145, 155, 200))
    while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
        auto varName = consume(TokenType::IDENTIFIER, "Expected variable name");
        
        if (match(TokenType::EQUALS)) {
            std::string value;
            // 收集值直到逗号或右括号
            while (!check(TokenType::COMMA) && !check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
                value += advance().value + " ";
            }
            refNode->setAttribute(varName.value, value);
        }
        
        if (match(TokenType::COMMA)) {
            continue;
        }
    }
}

void StandardParser::parseSpecialization(std::shared_ptr<Node> refNode) {
    // 解析特例化内容（delete, 属性覆盖等）
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        

        
        // delete操作
        if (match(TokenType::DELETE_KW)) {
            parseDelete(refNode);
            
            // 消耗可选的分号
            if (check(TokenType::SEMICOLON)) {
                advance();
            }
            continue;
        }
        
        // insert操作
        if (match(TokenType::INSERT)) {
            auto insertOp = parseInsert();
            if (insertOp) {
                refNode->addChild(insertOp);
            }
            continue;
        }
        
        // 其他内容根据引用类型处理
        if (refNode->getTagName().find("@Style") != std::string::npos) {
            // CSS属性
            if (checkAttribute()) {
                parseAttributes(refNode);
            }
        } else if (refNode->getTagName().find("@Element") != std::string::npos) {
            // 元素特例化
            auto child = parseNode();
            if (child) {
                refNode->addChild(child);
            }
        } else if (refNode->getTagName().find("@Var") != std::string::npos) {
            // 变量特例化
            if (checkAttribute()) {
                parseAttributes(refNode);
            }
        }
        
        // 如果没有匹配任何模式，跳过当前token避免无限循环
        if (!match(TokenType::DELETE_KW) && !checkAttribute() && 
            currentToken_.type != TokenType::RIGHT_BRACE) {

            advance();
        }
    }
}

std::string StandardParser::parseDeleteTarget() {
    std::string target;
    
    // 在样式上下文中，可能是属性名（包含连字符）
    if (currentToken_.type == TokenType::IDENTIFIER) {
        target = currentToken_.value;
        advance();
        
        // 处理连字符属性名（如 line-height）
        while (match(TokenType::HYPHEN)) {
            target += "-";
            if (currentToken_.type == TokenType::IDENTIFIER) {
                target += currentToken_.value;
                advance();
            }
        }
        
        // 检查是否有索引
        if (match(TokenType::LEFT_BRACKET)) {
            auto indexToken = consume(TokenType::NUMBER, "Expected index");
            consume(TokenType::RIGHT_BRACKET, "Expected ']'");
            target += "[" + indexToken.value + "]";
        }
    }
    // 检查是否是 @Element, @Style, @Var
    else if (currentToken_.type == TokenType::AT_ELEMENT || 
             currentToken_.type == TokenType::AT_STYLE || 
             currentToken_.type == TokenType::AT_VAR) {
        target = currentToken_.value + " ";
        advance();
        
        // 获取名称
        auto nameToken = consume(TokenType::IDENTIFIER, "Expected name");
        target += nameToken.value;
        
        // 检查是否有索引
        if (match(TokenType::LEFT_BRACKET)) {
            auto indexToken = consume(TokenType::NUMBER, "Expected index");
            consume(TokenType::RIGHT_BRACKET, "Expected ']'");
            target += "[" + indexToken.value + "]";
        }
    } else {
        throw std::runtime_error("Expected delete target");
    }
    
    return target;
}

void StandardParser::parseDelete(std::shared_ptr<Node> refNode) {
    // delete 关键字已经被消费
    
    // 解析删除列表 - 支持逗号分隔
    std::vector<std::string> deleteItems;
    
    // delete item1, item2, ...
    do {
        std::string item = parseDeleteTarget();
        deleteItems.push_back(item);
    } while (match(TokenType::COMMA));
    
    // 创建Delete节点
    for (const auto& item : deleteItems) {
        auto deleteNode = std::make_shared<Element>("delete");
        deleteNode->setAttribute("target", item);
        // 将删除节点添加到引用节点
        if (refNode) {
            refNode->addChild(deleteNode);
        }
    }
}

std::shared_ptr<Node> StandardParser::parseOperation() {
    if (match(TokenType::DELETE_KW)) {
        // delete在操作上下文中需要一个临时父节点
        auto tempNode = std::make_shared<Element>("temp");
        parseDelete(tempNode);
        // 返回第一个delete节点
        return tempNode->getChildren().empty() ? nullptr : tempNode->getChildren()[0];
    }
    
    if (match(TokenType::INSERT)) {
        return parseInsert();
    }
    
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseInsert() {
    // insert关键字已被消费
    
    auto insertNode = std::make_shared<Operate>();
    
    // 解析位置（after, before, replace, at top, at bottom）
    Operate::Position position = Operate::Position::AFTER;
    std::string target;
    
    if (match(TokenType::AFTER)) {
        position = Operate::Position::AFTER;
        target = parseInsertTarget();
    } else if (match(TokenType::BEFORE)) {
        position = Operate::Position::BEFORE;
        target = parseInsertTarget();
    } else if (match(TokenType::REPLACE)) {
        position = Operate::Position::REPLACE;
        target = parseInsertTarget();
    } else if (match(TokenType::AT)) {
        if (match(TokenType::TOP)) {
            position = Operate::Position::AT_TOP;
        } else if (match(TokenType::BOTTOM)) {
            position = Operate::Position::AT_BOTTOM;
        }
    }
    
    insertNode->setOperation(Operate::OperationType::INSERT);
    insertNode->setPosition(position);
    insertNode->setTarget(target);
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // 解析要插入的内容
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        auto child = parseNode();
        if (child) {
            insertNode->addChild(child);
        }
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    return insertNode;
}

std::string StandardParser::parseInsertTarget() {
    // 使用相同的逻辑解析 insert 和 delete 的目标
    return parseDeleteTarget();
}

std::shared_ptr<Node> StandardParser::parseOrigin() {
    // [Origin]已经被消费
    
    Origin::OriginType originType;
    
    if (match(TokenType::AT_HTML)) {
        originType = Origin::OriginType::HTML;
    } else if (match(TokenType::AT_STYLE)) {
        originType = Origin::OriginType::STYLE;
    } else if (match(TokenType::AT_JAVASCRIPT)) {
        originType = Origin::OriginType::JAVASCRIPT;
    } else {
        addError("Expected origin type (@Html, @Style, or @JavaScript)");
        skipToNextStatement();
        return nullptr;
    }
    
    auto originNode = std::make_shared<Origin>();
    originNode->setType(originType);
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // 收集原始内容
    std::string content;
    int braceCount = 1;
    
    while (braceCount > 0 && !isAtEnd()) {
        auto token = advance();
        
        if (token.type == TokenType::LEFT_BRACE) {
            braceCount++;
        } else if (token.type == TokenType::RIGHT_BRACE) {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        content += token.value + " ";
    }
    
    originNode->setContent(content);
    
    return originNode;
}

std::shared_ptr<Node> StandardParser::parseConfiguration() {
    // [Configuration]已经被消费
    
    auto configNode = std::make_shared<Config>();
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    parseConfigContent(configNode);
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    return configNode;
}

void StandardParser::parseConfigContent(std::shared_ptr<Config> configNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查[Name]子配置块
        if (check(TokenType::LEFT_BRACKET)) {
            consume(TokenType::LEFT_BRACKET, "[");
            auto blockName = consume(TokenType::IDENTIFIER, "Expected config block name").value;
            consume(TokenType::RIGHT_BRACKET, "]");
            
            if (blockName == "Name") {
                consume(TokenType::LEFT_BRACE, "Expected '{'");
                parseNameConfig(configNode);
                consume(TokenType::RIGHT_BRACE, "Expected '}'");
            }
            continue;
        }
        
        // 普通配置项
        parseConfigItem(configNode);
    }
}

void StandardParser::parseConfigItem(std::shared_ptr<Config> configNode) {
    auto nameToken = consume(TokenType::IDENTIFIER, "Expected config name");
    
    consume(TokenType::EQUALS, "Expected '='");
    
    // 配置值可能是单个值或数组
    if (match(TokenType::LEFT_BRACKET)) {
        // 数组值
        std::vector<std::string> values;
        
        while (!check(TokenType::RIGHT_BRACKET) && !isAtEnd()) {
            auto value = advance();
            values.push_back(value.value);
            
            if (!match(TokenType::COMMA)) {
                break;
            }
        }
        
        consume(TokenType::RIGHT_BRACKET, "Expected ']'");
        
        // 存储为逗号分隔的字符串
        std::string valueStr;
        for (size_t i = 0; i < values.size(); ++i) {
            valueStr += values[i];
            if (i < values.size() - 1) {
                valueStr += ",";
            }
        }
        configNode->setConfig(nameToken.value, valueStr);
    } else {
        // 单个值
        auto value = advance();
        configNode->setConfig(nameToken.value, value.value);
    }
    
    consume(TokenType::SEMICOLON, "Expected ';'");
}

void StandardParser::parseNameConfig(std::shared_ptr<Config> configNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        parseConfigItem(configNode);
    }
}

std::shared_ptr<Node> StandardParser::parseImportStatement() {
    // 这是旧语法，发出警告
    addWarning("'Import' without brackets is deprecated. Use '[Import]' instead.");
    
    // Import关键字
    consume(TokenType::IDENTIFIER, "Expected 'Import'");
    
    // 转发到parseImport处理
    return parseImport();
}

std::shared_ptr<Node> StandardParser::parseImport() {
    // [Import]已经被消费
    
    auto importNode = std::make_shared<Import>();
    
    // 解析导入类型
    Import::ImportType importType = Import::ImportType::CHTL;
    std::string importName;
    
    if (match(TokenType::AT_HTML)) {
        importType = Import::ImportType::HTML;
    } else if (match(TokenType::AT_STYLE)) {
        importType = Import::ImportType::CSS;
    } else if (match(TokenType::AT_JAVASCRIPT)) {
        importType = Import::ImportType::JS;
    } else if (match(TokenType::AT_CHTL)) {
        importType = Import::ImportType::CHTL;
    } else if (match(TokenType::CUSTOM)) {
        // [Custom] @Type Name
        if (match(TokenType::AT_ELEMENT)) {
            importType = Import::ImportType::CUSTOM_ELEMENT;
            importName = consume(TokenType::IDENTIFIER, "Expected custom element name").value;
        } else if (match(TokenType::AT_STYLE)) {
            importType = Import::ImportType::CUSTOM_STYLE;
            importName = consume(TokenType::IDENTIFIER, "Expected custom style name").value;
        } else if (match(TokenType::AT_VAR)) {
            importType = Import::ImportType::CUSTOM_VAR;
            importName = consume(TokenType::IDENTIFIER, "Expected custom var name").value;
        }
    } else if (match(TokenType::TEMPLATE)) {
        // [Template] @Type Name
        if (match(TokenType::AT_ELEMENT)) {
            importType = Import::ImportType::TEMPLATE_ELEMENT;
            importName = consume(TokenType::IDENTIFIER, "Expected template element name").value;
        } else if (match(TokenType::AT_STYLE)) {
            importType = Import::ImportType::TEMPLATE_STYLE;
            importName = consume(TokenType::IDENTIFIER, "Expected template style name").value;
        } else if (match(TokenType::AT_VAR)) {
            importType = Import::ImportType::TEMPLATE_VAR;
            importName = consume(TokenType::IDENTIFIER, "Expected template var name").value;
        }
    } else if (match(TokenType::ASTERISK)) {
        // 通配符导入
        importType = Import::ImportType::ALL;
        importNode->addImportItem("*");
    }
    
    importNode->setType(importType);
    if (!importName.empty()) {
        importNode->setName(importName);
        importNode->addImportItem(importName);
    }
    
    // 期望 'from' 关键字
    if (!matchIdentifier("from")) {
        addError("Expected 'from' in import statement");
        skipToNextStatement();
        return nullptr;
    }
    
    // 检查是否是 from namespace
    bool isFromNamespace = false;
    std::string namespaceName;
    
    if (checkIdentifier("namespace")) {
        advance(); // 消费 'namespace'
        isFromNamespace = true;
        namespaceName = consume(TokenType::IDENTIFIER, "Expected namespace name").value;
        importNode->setNamespaceImport(true);
        importNode->setTargetNamespace(namespaceName);
        (void)isFromNamespace; // 标记已设置
    } else {
        // 解析文件路径
        auto pathToken = consume(TokenType::STRING_LITERAL, "Expected file path");
        importNode->setFilePath(pathToken.value);
    }
    
    // 检查 'as' 重命名
    if (matchIdentifier("as")) {
        auto aliasToken = consume(TokenType::IDENTIFIER, "Expected alias name");
        importNode->setAlias(aliasToken.value);
        
        // 更新别名映射
        if (!importName.empty()) {
            importNode->addImportItem(importName, aliasToken.value);
        }
    }
    
    // 期望分号（可选）
    match(TokenType::SEMICOLON);
    
    return importNode;
}

std::shared_ptr<Node> StandardParser::parseNamespace() {
    // [Namespace]已经被消费
    
    auto namespaceNode = std::make_shared<Namespace>();
    
    auto nameToken = consume(TokenType::IDENTIFIER, "Expected namespace name");
    namespaceNode->setName(nameToken.value);
    
    // 获取命名空间管理器
    auto nsManager = std::static_pointer_cast<StandardContext>(context_)->getNamespaceManager();
    if (nsManager) {
        // 获取当前命名空间路径
        std::string currentPath = nsManager->getCurrentNamespace();
        
        // 注册命名空间
        nsManager->registerNamespace(namespaceNode, currentPath);
        
        // 设置新的当前命名空间
        std::string newPath = currentPath.empty() ? nameToken.value : currentPath + "." + nameToken.value;
        nsManager->setCurrentNamespace(newPath);
    }
    
    // 检查是否有内容块
    if (check(TokenType::LEFT_BRACE)) {
        consume(TokenType::LEFT_BRACE, "Expected '{'");
        
        // 解析命名空间内容
        parseNamespaceContent(namespaceNode);
        
        consume(TokenType::RIGHT_BRACE, "Expected '}'");
    } else {
        // 检查是否是简化的嵌套语法
        // [Namespace] space
        // [Namespace] room  // 只有一层关系时可以不写花括号
        if (check(TokenType::LEFT_BRACKET) && peekNext() == TokenType::NAMESPACE_KW) {
            // 下一行也是命名空间声明
            auto child = parseTopLevel();
            if (child && child->getType() == NodeType::NAMESPACE) {
                namespaceNode->addChild(child);
            }
        }
    }
    
    // 恢复上一级命名空间
    if (nsManager) {
        std::string currentPath = nsManager->getCurrentNamespace();
        size_t lastDot = currentPath.rfind('.');
        if (lastDot != std::string::npos) {
            nsManager->setCurrentNamespace(currentPath.substr(0, lastDot));
        } else {
            nsManager->setCurrentNamespace("");
        }
    }
    
    return namespaceNode;
}

void StandardParser::parseNamespaceContent(std::shared_ptr<Namespace> namespaceNode) {
    auto nsManager = std::static_pointer_cast<StandardContext>(context_)->getNamespaceManager();
    std::string currentNsPath = nsManager ? nsManager->getCurrentNamespace() : "";
    
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // except约束
        if (check(TokenType::EXCEPT)) {
            parseExcept(namespaceNode);
            continue;
        }
        
        // 嵌套命名空间或其他内容
        auto child = parseTopLevel();
        if (child) {
            namespaceNode->addChild(child);
            
            // 注册成员到命名空间
            if (nsManager && child->getType() != NodeType::NAMESPACE) {
                std::string memberName;
                
                // 根据节点类型获取名称
                if (child->getType() == NodeType::CUSTOM) {
                    auto custom = std::static_pointer_cast<Custom>(child);
                    memberName = custom->getCustomName();
                } else if (child->getType() == NodeType::TEMPLATE) {
                    auto tmpl = std::static_pointer_cast<Template>(child);
                    memberName = tmpl->getTemplateName();
                }
                
                if (!memberName.empty()) {
                    if (!nsManager->registerMember(currentNsPath, memberName, child->getType(), child)) {
                        context_->addWarning("Member '" + memberName + "' already exists in namespace '" + currentNsPath + "'");
                    }
                }
            }
        }
    }
}

void StandardParser::parseExcept(std::shared_ptr<Node> parent) {
    consume(TokenType::EXCEPT, "except");
    
    // 收集约束项
    std::vector<std::string> exceptItems;
    
    do {
        if (check(TokenType::AT_HTML)) {
            advance();
            exceptItems.push_back("@Html");
        } else if (check(TokenType::CUSTOM)) {
            advance();
            
            // 可能有具体类型
            if (check(TokenType::AT_ELEMENT) || check(TokenType::AT_STYLE) || check(TokenType::AT_VAR)) {
                auto type = advance();
                auto name = consume(TokenType::IDENTIFIER, "Expected name").value;
                exceptItems.push_back("[Custom] " + type.value + " " + name);
            } else {
                exceptItems.push_back("[Custom]");
            }
        } else if (check(TokenType::TEMPLATE)) {
            advance();
            
            // 可能有具体类型
            if (check(TokenType::AT_ELEMENT) || check(TokenType::AT_STYLE) || check(TokenType::AT_VAR)) {
                auto type = advance();
                exceptItems.push_back("[Template] " + type.value);
            } else {
                exceptItems.push_back("[Template]");
            }
        } else if (check(TokenType::IDENTIFIER)) {
            // HTML元素
            exceptItems.push_back(advance().value);
        }
    } while (match(TokenType::COMMA));
    
    consume(TokenType::SEMICOLON, "Expected ';'");
    
    // 添加约束到父节点
    for (const auto& item : exceptItems) {
        parent->addConstraint(item);
    }
}

std::shared_ptr<Node> StandardParser::parseInfo() {
    // [Info]已经被消费
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    auto infoNode = std::make_shared<Info>();
    
    // 解析Info内容 - 键值对格式
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 解析键名
        if (!check(TokenType::IDENTIFIER)) {
            addError("Expected property name in [Info] block");
            skipToNextStatement();
            continue;
        }
        
        std::string key = currentToken_.value;
        advance();
        
        // 期望冒号
        consume(TokenType::COLON, "Expected ':' after property name");
        
        // 解析值（字符串字面量或无引号字面量）
        std::string value;
        if (check(TokenType::STRING_LITERAL)) {
            value = currentToken_.value;
            advance();
        } else if (check(TokenType::IDENTIFIER) || check(TokenType::NUMBER)) {
            // 无引号的值
            value = currentToken_.value;
            advance();
            
            // 继续读取直到遇到逗号、分号或右大括号
            while (!isAtEnd() && 
                   !check(TokenType::COMMA) && 
                   !check(TokenType::SEMICOLON) &&
                   !check(TokenType::RIGHT_BRACE)) {
                if (check(TokenType::DOT) || check(TokenType::HYPHEN) || 
                    check(TokenType::IDENTIFIER) || check(TokenType::NUMBER)) {
                    value += currentToken_.value;
                    advance();
                } else {
                    break;
                }
            }
        } else {
            addError("Expected value after ':' in [Info] block");
            skipToNextStatement();
            continue;
        }
        
        // 设置属性
        infoNode->setProperty(key, value);
        
        // 可选的逗号或分号
        if (match(TokenType::COMMA) || match(TokenType::SEMICOLON)) {
            // 已消费
        }
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    return infoNode;
}

std::shared_ptr<Node> StandardParser::parseExport() {
    // [Export]已经被消费
    
    auto exportNode = std::make_shared<Export>();
    
    // 检查是否有 from namespace 语法
    if (check(TokenType::IDENTIFIER) && currentToken_.value == "from") {
        advance(); // 消费 'from'
        
        if (check(TokenType::IDENTIFIER)) {
            exportNode->setFromNamespace(currentToken_.value);
            advance();
        } else {
            addError("Expected namespace name after 'from'");
        }
    }
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // 解析Export内容
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::RIGHT_BRACE)) break;
        
        // 检查通配符导出
        if (match(TokenType::WILDCARD)) {
            exportNode->addExportItem(Export::ExportType::ALL, "*");
            // 可选的逗号或分号
            match(TokenType::COMMA) || match(TokenType::SEMICOLON);
            continue;
        }
        
        // 解析导出类型
        Export::ExportType exportType;
        if (match(TokenType::AT_ELEMENT)) {
            exportType = Export::ExportType::ELEMENT;
        } else if (match(TokenType::AT_STYLE)) {
            exportType = Export::ExportType::STYLE;
        } else if (match(TokenType::AT_VAR)) {
            exportType = Export::ExportType::VAR;
        } else if (check(TokenType::IDENTIFIER) && currentToken_.value == "namespace") {
            advance(); // 消费 'namespace'
            exportType = Export::ExportType::NAMESPACE;
        } else {
            addError("Expected export type (@Element, @Style, @Var, namespace, or *)");
            skipToNextStatement();
            continue;
        }
        
        // 解析名称和可选的别名
        if (!check(TokenType::IDENTIFIER)) {
            addError("Expected identifier after export type");
            skipToNextStatement();
            continue;
        }
        
        std::string name = currentToken_.value;
        advance();
        
        std::string alias;
        // 检查 'as' 别名语法
        if (check(TokenType::AS)) {
            advance(); // 消费 'as'
            if (check(TokenType::IDENTIFIER)) {
                alias = currentToken_.value;
                advance();
            } else {
                addError("Expected alias name after 'as'");
            }
        }
        
        exportNode->addExportItem(exportType, name, alias);
        
        // 处理逗号分隔的多个导出项
        if (match(TokenType::COMMA)) {
            // 如果是逗号，继续解析同类型的导出项
            while (!isAtEnd() && !check(TokenType::RIGHT_BRACE)) {
                if (!check(TokenType::IDENTIFIER)) {
                    addError("Expected identifier after ','");
                    break;
                }
                
                name = currentToken_.value;
                advance();
                
                alias = "";
                if (check(TokenType::AS)) {
                    advance();
                    if (check(TokenType::IDENTIFIER)) {
                        alias = currentToken_.value;
                        advance();
                    }
                }
                
                exportNode->addExportItem(exportType, name, alias);
                
                if (!match(TokenType::COMMA)) {
                    break;
                }
            }
        }
        
        // 可选的分号
        match(TokenType::SEMICOLON);
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    return exportNode;
}

std::shared_ptr<Node> StandardParser::parseScript() {
    // [Script]已经被消费
    
    auto scriptNode = std::make_shared<Script>();
    
    // 检查是否有命名的脚本块 [Script] @ScriptName
    if (check(TokenType::AT_STYLE) || check(TokenType::AT_ELEMENT) || 
        check(TokenType::AT_VAR) || check(TokenType::IDENTIFIER)) {
        
        if (match(TokenType::AT_STYLE) || match(TokenType::AT_ELEMENT) || 
            match(TokenType::AT_VAR)) {
            // 处理@前缀的名称
            if (check(TokenType::IDENTIFIER)) {
                scriptNode->setName(currentToken_.value);
                advance();
            }
        } else if (check(TokenType::IDENTIFIER)) {
            // 直接的标识符作为名称
            scriptNode->setName(currentToken_.value);
            advance();
        }
    }
    
    // 解析可选的属性
    while (!check(TokenType::LEFT_BRACE) && !isAtEnd()) {
        if (check(TokenType::IDENTIFIER)) {
            std::string attrName = currentToken_.value;
            advance();
            
            if (attrName == "type") {
                if (match(TokenType::EQUALS)) {
                    if (check(TokenType::STRING_LITERAL) || check(TokenType::IDENTIFIER)) {
                        std::string typeValue = currentToken_.value;
                        advance();
                        
                        if (typeValue == "module") {
                            scriptNode->setScriptType(Script::ScriptType::MODULE);
                        } else if (typeValue == "global") {
                            scriptNode->setScriptType(Script::ScriptType::GLOBAL);
                        } else if (typeValue == "scoped") {
                            scriptNode->setScriptType(Script::ScriptType::SCOPED);
                        } else if (typeValue == "inline") {
                            scriptNode->setScriptType(Script::ScriptType::INLINE);
                        }
                    }
                }
            } else if (attrName == "scope") {
                if (match(TokenType::EQUALS)) {
                    if (check(TokenType::STRING_LITERAL) || check(TokenType::IDENTIFIER)) {
                        scriptNode->setScope(currentToken_.value);
                        advance();
                    }
                }
            } else if (attrName == "defer") {
                scriptNode->setTiming(Script::ExecutionTiming::DEFERRED);
            } else if (attrName == "async") {
                scriptNode->setAsync(true);
            } else if (attrName == "onload") {
                scriptNode->setTiming(Script::ExecutionTiming::ON_LOAD);
            } else if (attrName == "onmount") {
                scriptNode->setTiming(Script::ExecutionTiming::ON_MOUNT);
            } else if (attrName == "ondemand") {
                scriptNode->setTiming(Script::ExecutionTiming::ON_DEMAND);
            } else if (attrName == "depends") {
                if (match(TokenType::EQUALS)) {
                    if (check(TokenType::STRING_LITERAL)) {
                        // 解析依赖列表（逗号分隔）
                        std::string deps = currentToken_.value;
                        advance();
                        
                        // 简单的逗号分隔解析
                        size_t start = 0;
                        size_t end = deps.find(',');
                        while (end != std::string::npos) {
                            std::string dep = deps.substr(start, end - start);
                            // 去除空格
                            dep.erase(0, dep.find_first_not_of(" \t"));
                            dep.erase(dep.find_last_not_of(" \t") + 1);
                            if (!dep.empty()) {
                                scriptNode->addDependency(dep);
                            }
                            start = end + 1;
                            end = deps.find(',', start);
                        }
                        // 处理最后一个依赖
                        std::string dep = deps.substr(start);
                        dep.erase(0, dep.find_first_not_of(" \t"));
                        dep.erase(dep.find_last_not_of(" \t") + 1);
                        if (!dep.empty()) {
                            scriptNode->addDependency(dep);
                        }
                    }
                }
            }
        } else {
            advance(); // 跳过未知的token
        }
    }
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // 收集脚本内容直到遇到 }
    std::string scriptContent;
    int braceDepth = 1;
    bool inString = false;
    // char stringChar = '\0';
    // bool escaped = false;
    
    while (!isAtEnd() && braceDepth > 0) {
        Token token = currentToken_;
        advance();
        
        // 处理字符串字面量以正确计算大括号深度
        if (token.type == TokenType::STRING_LITERAL) {
            // 字符串字面量，添加引号
            scriptContent += "\"" + token.value + "\"";
        } else if (token.type == TokenType::LEFT_BRACE) {
            scriptContent += token.value;
            if (!inString) {
                braceDepth++;
            }
        } else if (token.type == TokenType::RIGHT_BRACE) {
            if (!inString) {
                braceDepth--;
                if (braceDepth == 0) {
                    break; // 不添加最后的 }
                }
            }
            scriptContent += token.value;
        } else {
            // 对于其他token，添加原始值
            scriptContent += token.value;
        }
        
        // 添加空格（除非是某些特殊情况）
        if (!isAtEnd() && braceDepth > 0) {
            // 检查下一个token是否需要空格分隔
            Token next = currentToken_;
            if (token.type != TokenType::DOT && next.type != TokenType::DOT &&
                token.type != TokenType::LEFT_PAREN && next.type != TokenType::RIGHT_PAREN &&
                token.type != TokenType::LEFT_BRACKET && next.type != TokenType::RIGHT_BRACKET &&
                next.type != TokenType::COMMA && next.type != TokenType::SEMICOLON) {
                scriptContent += " ";
            }
        }
    }
    
    // 去除首尾空白
    scriptContent.erase(0, scriptContent.find_first_not_of(" \t\n\r"));
    scriptContent.erase(scriptContent.find_last_not_of(" \t\n\r") + 1);
    
    scriptNode->setContent(scriptContent);
    
    return scriptNode;
}

std::shared_ptr<Node> StandardParser::parseComment() {
    auto commentToken = consume(TokenType::HTML_COMMENT, "Expected comment");
    
    auto commentNode = std::make_shared<Comment>();
    commentNode->setContent(commentToken.value);
    
    return commentNode;
}

// 辅助方法实现

Token StandardParser::peek() {
    // BasicParser的peekNextToken()会返回下一个token而不消费它
    return peekNextToken();
}

Token StandardParser::previous() {
    return previousToken_;
}

Token StandardParser::advance() {
    previousToken_ = currentToken_;
    currentToken_ = getNextToken();  // 直接获取下一个token
    return previousToken_;
}

bool StandardParser::isAtEnd() {
    return currentToken_.type == TokenType::EOF_TOKEN;
}

bool StandardParser::check(TokenType type) {
    return !isAtEnd() && currentToken_.type == type;
}

bool StandardParser::checkIdentifier(const std::string& value) {
    return !isAtEnd() && currentToken_.type == TokenType::IDENTIFIER && currentToken_.value == value;
}

bool StandardParser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool StandardParser::matchIdentifier(const std::string& value) {
    if (checkIdentifier(value)) {
        advance();
        return true;
    }
    return false;
}

Token StandardParser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    
    addError(message + " at line " + std::to_string(currentToken_.line));
    throw std::runtime_error(message);
}

void StandardParser::skipWhitespaceAndComments() {
    while (!isAtEnd()) {
        // 跳过注释
        if (currentToken_.type == TokenType::SINGLE_LINE_COMMENT ||
            currentToken_.type == TokenType::MULTI_LINE_COMMENT) {
            advance();
            continue;
        }
        
        // 跳过空白（如果词法分析器产生了空白token）
        if (currentToken_.value.empty() || 
            std::all_of(currentToken_.value.begin(), currentToken_.value.end(), ::isspace)) {
            advance();
            continue;
        }
        
        break;
    }
}

void StandardParser::skipToNextStatement() {
    while (!isAtEnd()) {
        if (match(TokenType::SEMICOLON) || 
            match(TokenType::RIGHT_BRACE)) {
            break;
        }
        advance();
    }
}

TokenType StandardParser::peekNext() {
    // 保存当前状态
    Token savedCurrent = currentToken_;
    Token savedPrevious = previousToken_;
    
    // 前进一个token
    advance();
    TokenType nextType = currentToken_.type;
    
    // 恢复状态
    currentToken_ = savedCurrent;
    previousToken_ = savedPrevious;
    
    return nextType;
}

} // namespace chtl