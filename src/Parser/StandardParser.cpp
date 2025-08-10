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
#include <algorithm>
#include <cctype>


namespace chtl {

StandardParser::StandardParser(std::shared_ptr<BasicLexer> lexer, std::shared_ptr<BasicContext> context)
    : BasicParser(),
      currentIndent_(0),
      expectIndent_(0),
      inAttribute_(false),
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
    // 调试输出
    // std::cout << "DEBUG parseTopLevel: token type=" << static_cast<int>(currentToken_.type) 
    //           << " value=[" << currentToken_.value << "]" << std::endl;
    
    // 检查特殊块标记  
    if (currentToken_.type == TokenType::CUSTOM) {
        advance();
        return parseCustom();
    }
    if (currentToken_.type == TokenType::TEMPLATE) {
        advance();
        return parseTemplate();
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
    if (currentToken_.type == TokenType::INFO) {
        advance();
        return parseInfo();
    }
    if (currentToken_.type == TokenType::EXPORT) {
        advance();
        return parseExport();
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
    
    // 检查HTML元素
    if (currentToken_.type == TokenType::IDENTIFIER) {
        std::string tagName = currentToken_.value;
        advance();  // 消费元素名
        try {
            return parseElement();
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
    
    advance();
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseSpecialBlock() {
    consume(TokenType::LEFT_BRACKET, "Expected '['");
    
    auto typeToken = consume(TokenType::IDENTIFIER, "Expected block type");
    std::string blockType = typeToken.value;
    
    consume(TokenType::RIGHT_BRACKET, "Expected ']'");
    
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
        return parseInfo();
    } else if (blockType == "Export") {
        return parseExport();
    } else {
        addError("Unknown block type: " + blockType);
        skipToNextStatement();
        return nullptr;
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
        return parseText();
    }
    
    // style块
    if (currentToken_.value == "style") {
        return parseStyleBlock();
    }
    
    // @Element, @Style, @Var引用
    if (currentToken_.type == TokenType::AT_ELEMENT || 
        currentToken_.type == TokenType::AT_STYLE || 
        currentToken_.type == TokenType::AT_VAR) {
        return parseReference();
    }
    
    // 普通元素
    if (currentToken_.type == TokenType::IDENTIFIER) {
        advance();  // 消费元素名
        return parseElement();
    }
    
    // 特殊块
    if (currentToken_.type == TokenType::LEFT_BRACKET) {
        return parseSpecialBlock();
    }
    
    advance();
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseText() {
    consume(TokenType::IDENTIFIER, "text");
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
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
    
    textNode->setText(content);
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
    
    consume(TokenType::SEMICOLON, "Expected ';'");
    
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
    }
}

void StandardParser::parseDelete(std::shared_ptr<Node> refNode) {
    // [Delete]已经被消费
    
    // 解析删除列表
    std::vector<std::string> deleteItems;
    
    if (match(TokenType::LEFT_PAREN)) {
        // [Delete] (item1, item2, ...)
        while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
            auto item = consume(TokenType::IDENTIFIER, "Expected item to delete").value;
            deleteItems.push_back(item);
            
            if (!match(TokenType::COMMA)) {
                break;
            }
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')'");
    } else {
        // [Delete] item
        auto item = consume(TokenType::IDENTIFIER, "Expected item to delete").value;
        deleteItems.push_back(item);
    }
    
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
    std::string target;
    
    auto token = consume(TokenType::IDENTIFIER, "Expected target element");
    target = token.value;
    
    // 检查索引
    if (match(TokenType::LEFT_BRACKET)) {
        auto index = consume(TokenType::NUMBER, "Expected index").value;
        consume(TokenType::RIGHT_BRACKET, "Expected ']'");
        target += "[" + index + "]";
    }
    
    return target;
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
    // std::cout << "DEBUG parseImportStatement: entered" << std::endl;
    
    // Import关键字
    consume(TokenType::IDENTIFIER, "Expected 'Import'");
    
    auto importNode = std::make_shared<Import>();
    
    // 解析导入类型 (@Chtl, @Html, @Style, @JavaScript)
    Import::ImportType importType = Import::ImportType::CHTL;
    
    if (match(TokenType::AT_CHTL)) {
        importType = Import::ImportType::CHTL;
    } else if (match(TokenType::AT_HTML)) {
        importType = Import::ImportType::HTML;
    } else if (match(TokenType::AT_STYLE)) {
        importType = Import::ImportType::CSS;
    } else if (match(TokenType::AT_JAVASCRIPT)) {
        importType = Import::ImportType::JS;
    } else {
        addError("Expected import type (@Chtl, @Html, @Style, @JavaScript)");
        skipToNextStatement();
        return nullptr;
    }
    
    importNode->setType(importType);
    
    // 期望 'from' 关键字
    if (!check(TokenType::IDENTIFIER) || currentToken_.value != "from") {
        addError("Expected 'from' after import type");
        skipToNextStatement();
        return nullptr;
    }
    advance(); // 消费 'from'
    
    // 解析模块路径 - 支持字符串字面量或无引号的标识符路径
    std::string modulePath;
    
    if (check(TokenType::STRING_LITERAL)) {
        // 带引号的路径: "path/to/module" 或 "path/to/module.*"
        modulePath = currentToken_.value;
        advance();
    } else if (check(TokenType::IDENTIFIER)) {
        // 无引号的路径: path/to/module 或 Chtholly.Space
        modulePath = currentToken_.value;
        advance();
        
        // 继续读取路径的其余部分（处理 . 和 / 分隔符）
        while (!isAtEnd()) {
            if (check(TokenType::DOT)) {
                advance(); // 消费点
                modulePath += ".";
                
                if (check(TokenType::WILDCARD)) {
                    // 通配符: path.*
                    modulePath += "*";
                    advance();
                    break; // 通配符后路径结束
                } else if (check(TokenType::IDENTIFIER)) {
                    // 子模块: Chtholly.Space
                    modulePath += currentToken_.value;
                    advance();
                } else {
                    addError("Expected identifier or '*' after '.' in module path");
                    break;
                }
            } else if (check(TokenType::SLASH)) {
                // 路径分隔符
                advance();
                modulePath += "/";
                
                if (check(TokenType::WILDCARD)) {
                    // 通配符: path/*
                    modulePath += "*";
                    advance();
                    break; // 通配符后路径结束
                } else if (check(TokenType::IDENTIFIER)) {
                    modulePath += currentToken_.value;
                    advance();
                } else {
                    addError("Expected identifier or '*' after '/' in module path");
                    break;
                }
            } else {
                // 路径结束
                break;
            }
        }
    } else {
        addError("Expected module path after 'from'");
        skipToNextStatement();
        return nullptr;
    }
    
    importNode->setPath(modulePath);
    
    // 如果路径以 .* 或 /* 结尾，标记为通配符导入
    if (modulePath.size() >= 2 && 
        ((modulePath.substr(modulePath.size() - 2) == ".*") ||
         (modulePath.substr(modulePath.size() - 2) == "/*"))) {
        importNode->addImportItem("*");
    }
    
    return importNode;
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
    }
    
    importNode->setType(importType);
    if (!importName.empty()) {
        importNode->setName(importName);
    }
    
    // from子句
    consume(TokenType::FROM, "Expected 'from'");
    
    // 路径（支持字符串或标识符序列）
    std::string path;
    bool isStringLiteral = false;
    
    if (check(TokenType::STRING_LITERAL)) {
        // 字符串路径
        isStringLiteral = true;
        path = advance().value;
        // 移除引号
        if (path.size() >= 2 && path.front() == '"' && path.back() == '"') {
            path = path.substr(1, path.size() - 2);
        }
    } else {
        // 标识符序列（支持.代替/）
        while (!check(TokenType::AS) && !check(TokenType::SEMICOLON) && !isAtEnd()) {
            if (match(TokenType::DOT)) {
                path += "/";
            } else if (check(TokenType::IDENTIFIER)) {
                if (!path.empty() && path.back() != '/') {
                    path += "/";
                }
                path += advance().value;
            } else {
                break;
            }
        }
        
        // 只对标识符序列进行点号转换，不对字符串字面量进行转换
        for (size_t i = 0; i < path.length(); ++i) {
            if (path[i] == '.') {
                path[i] = '/';
            }
        }
    }
    
    importNode->setPath(path);
    
    // as子句（可选）
    if (match(TokenType::AS)) {
        auto alias = consume(TokenType::IDENTIFIER, "Expected alias").value;
        importNode->setAlias(alias);
    }
    
    consume(TokenType::SEMICOLON, "Expected ';'");
    
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
    
    auto infoNode = std::make_shared<Element>("info");
    
    // 解析Info内容
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (checkAttribute()) {
            parseAttributes(infoNode);
        } else {
            advance();
        }
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    return infoNode;
}

std::shared_ptr<Node> StandardParser::parseExport() {
    // [Export]已经被消费
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    auto exportNode = std::make_shared<Element>("export");

    // 解析Export内容
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipWhitespaceAndComments();
        
        if (check(TokenType::AT_STYLE) || check(TokenType::AT_ELEMENT) || check(TokenType::AT_VAR)) {
            auto type = advance();
            
            // 收集名称列表
            do {
                auto name = consume(TokenType::IDENTIFIER, "Expected export name");
                exportNode->addExport(type.value + " " + name.value);
            } while (match(TokenType::COMMA));
            
            consume(TokenType::SEMICOLON, "Expected ';'");
        } else {
            advance();
        }
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    return exportNode;
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
    if (isAtEnd()) return false;
    return currentToken_.type == type;
}

bool StandardParser::match(TokenType type) {
    if (check(type)) {
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