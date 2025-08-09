#include "Parser/StandardParser.h"
#include "Node/Node.h"
#include "Node/Comment.h"
#include "Node/Template.h"
#include "Node/Custom.h"
#include "Node/Style.h"
#include "Node/Config.h"
#include "Node/Import.h"
#include "Node/Namespace.h"
#include "Node/Operate.h"
#include "Node/Origin.h"
#include <stdexcept>

namespace chtl {

StandardParser::StandardParser() : BasicParser() {
    // 构造函数
}

std::shared_ptr<Node> StandardParser::parse() {
    if (!lexer_ || !context_) {
        reportError("Parser not initialized");
        return nullptr;
    }
    
    // 开始解析
    getNextToken(); // 读取第一个token
    return parseDocument();
}

// 辅助方法
Token StandardParser::advance() {
    consumeToken();
    return previousToken_;
}

Token StandardParser::currentToken() {
    return peekNextToken();
}

Token StandardParser::peek() {
    // 保存当前状态
    Token current = currentToken();
    
    // 前进一个token
    advance();
    Token next = currentToken();
    
    // 恢复状态 - 这里有个问题，BasicParser没有提供回退功能
    // 暂时返回当前token作为下一个token的近似
    return current;
}

bool StandardParser::check(TokenType type) {
    if (isAtEnd()) return false;
    return currentToken().getType() == type;
}

bool StandardParser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

Token StandardParser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        return advance();
    }
    
    reportError(message);
    return currentToken();
}

std::shared_ptr<Node> StandardParser::parseDocument() {
    // 创建根文档节点
    auto document = std::make_shared<Element>("document");
    std::shared_ptr<Node> firstRootElement = nullptr;
    
    // 解析顶层元素
    while (!isAtEnd()) {
        // 跳过注释
        if (check(TokenType::HTML_COMMENT)) {
            auto comment = parseComment();
            if (comment) {
                document->appendChild(comment);
            }
            continue;
        }
        
        // 跳过其他注释（不会被生成）
        if (check(TokenType::SINGLE_LINE_COMMENT) || check(TokenType::MULTI_LINE_COMMENT)) {
            advance();
            continue;
        }
        
        // 解析配置块
        if (check(TokenType::CONFIGURATION)) {
            auto config = parseConfig();
            if (config) {
                document->appendChild(config);
            }
            continue;
        }
        
        // 解析导入
        if (check(TokenType::IMPORT)) {
            auto import = parseImport();
            if (import) {
                document->appendChild(import);
            }
            continue;
        }
        
        // 解析命名空间
        if (check(TokenType::NAMESPACE_KW)) {
            auto ns = parseNamespace();
            if (ns) {
                document->appendChild(ns);
            }
            continue;
        }
        
        // 解析模板
        if (check(TokenType::TEMPLATE)) {
            auto tmpl = parseTemplate();
            if (tmpl) {
                document->appendChild(tmpl);
            }
            continue;
        }
        
        // 解析自定义
        if (check(TokenType::CUSTOM)) {
            auto custom = parseCustom();
            if (custom) {
                document->appendChild(custom);
            }
            continue;
        }
        
        // 解析元素
        auto element = parseElement();
        if (element) {
            document->appendChild(element);
            
            // 如果是第一个根元素（通常是html），记录它
            if (!firstRootElement && element->getType() == NodeType::ELEMENT) {
                auto elem = std::dynamic_pointer_cast<Element>(element);
                if (elem && elem->getTagName() == "html") {
                    firstRootElement = element;
                }
            }
        } else {
            // 如果无法解析，跳过当前token
            if (!isAtEnd()) {
                reportError("Unexpected token: " + currentToken().getValue());
                advance();
            }
        }
    }
    
    // 如果只有一个html元素，直接返回它
    if (firstRootElement && document->getChildren().size() == 1) {
        return firstRootElement;
    }
    
    // 如果document中有html元素，直接返回document
    // 这样HtmlGenerator可以正确处理DOCTYPE的生成
    
    return document;
}

std::shared_ptr<Node> StandardParser::parseElement() {
    // 检查是否是标识符（元素名）
    if (!check(TokenType::IDENTIFIER)) {
        return nullptr;
    }
    
    // 获取元素名
    std::string tagName = advance().getValue();
    // std::cerr << "DEBUG: Parsing element: " << tagName << std::endl;
    auto element = std::make_shared<Element>(tagName);
    
    // 期待左大括号
    if (!match(TokenType::LEFT_BRACE)) {
        reportError("Expected '{' after element name '" + tagName + "'");
        return element;
    }
    
    // 解析元素内容
    parseElementContent(element);
    
    // 期待右大括号
    if (!match(TokenType::RIGHT_BRACE)) {
        reportError("Expected '}' to close element '" + tagName + "'");
    }
    
    return element;
}

void StandardParser::parseElementContent(std::shared_ptr<Element> element) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        // 跳过注释
        if (check(TokenType::HTML_COMMENT)) {
            auto comment = parseComment();
            if (comment) {
                element->appendChild(comment);
            }
            continue;
        }
        
        // 跳过其他注释
        if (check(TokenType::SINGLE_LINE_COMMENT) || check(TokenType::MULTI_LINE_COMMENT)) {
            advance();
            continue;
        }
        
        // 检查是否是属性（标识符后跟冒号或等号）
        if (check(TokenType::IDENTIFIER)) {
            // 解析属性
            parseAttribute(element);
            continue;
        }
        
        // 检查是否是text节点
        if (check(TokenType::TEXT)) {
            advance(); // 跳过 text 关键字
            auto textNode = parseText();
            if (textNode) {
                element->appendChild(textNode);
            }
            continue;
        }
        
        // 检查是否是style块
        if (check(TokenType::STYLE)) {
            advance(); // 跳过 style 关键字
            auto styleNode = parseInlineStyle(element);
            if (styleNode) {
                element->appendChild(styleNode);
            }
            continue;
        }
        
        // 解析嵌套元素
        auto child = parseElement();
        if (child) {
            element->appendChild(child);
        } else {
            // 无法识别的内容
            reportError("Unexpected token in element: " + currentToken().getValue());
            advance();
        }
    }
}

std::shared_ptr<Node> StandardParser::parseText() {
    // 期待左大括号
    if (!match(TokenType::LEFT_BRACE)) {
        reportError("Expected '{' after 'text'");
        return nullptr;
    }
    
    std::string content;
    
    // 收集文本内容，直到遇到右大括号
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        Token token = advance();
        
        // 处理字符串字面量
        if (token.getType() == TokenType::STRING_LITERAL) {
            // 去除引号
            std::string value = token.getValue();
            if (value.size() >= 2 && 
                ((value.front() == '"' && value.back() == '"') ||
                 (value.front() == '\'' && value.back() == '\''))) {
                value = value.substr(1, value.size() - 2);
            }
            content += value;
        }
        // 处理无引号字面量
        else if (token.getType() == TokenType::UNQUOTED_LITERAL ||
                 token.getType() == TokenType::IDENTIFIER) {
            content += token.getValue();
        }
        // 处理数字
        else if (token.getType() == TokenType::NUMBER) {
            content += token.getValue();
        }
        else {
            reportError("Unexpected token in text block: " + token.getValue());
        }
        
        // 如果有多个值，添加空格
        if (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            content += " ";
        }
    }
    
    // 期待右大括号
    if (!match(TokenType::RIGHT_BRACE)) {
        reportError("Expected '}' to close text block");
    }
    
    return std::make_shared<Text>(content);
}

std::shared_ptr<Node> StandardParser::parseComment() {
    if (!check(TokenType::HTML_COMMENT)) {
        return nullptr;
    }
    
    Token commentToken = advance();
    std::string content = commentToken.getValue();
    
    // 移除 -- 前缀（如果存在）
    if (content.size() >= 2 && content.substr(0, 2) == "--") {
        content = content.substr(2);
    }
    
    // 去除首尾空格
    size_t start = content.find_first_not_of(" \t");
    size_t end = content.find_last_not_of(" \t");
    if (start != std::string::npos && end != std::string::npos) {
        content = content.substr(start, end - start + 1);
    }
    
    return std::make_shared<Comment>(content);
}

std::shared_ptr<Node> StandardParser::parseTemplate() {
    // TODO: 实现模板解析
    reportError("Template parsing not yet implemented");
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseCustom() {
    // TODO: 实现自定义元素解析
    reportError("Custom element parsing not yet implemented");
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseStyle() {
    // TODO: 实现样式解析
    reportError("Style parsing not yet implemented");
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseConfig() {
    // TODO: 实现配置解析
    reportError("Config parsing not yet implemented");
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseImport() {
    // TODO: 实现导入解析
    reportError("Import parsing not yet implemented");
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseNamespace() {
    // TODO: 实现命名空间解析
    reportError("Namespace parsing not yet implemented");
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseOperate() {
    // TODO: 实现操作解析
    reportError("Operate parsing not yet implemented");
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseOrigin() {
    // TODO: 实现原始代码解析
    reportError("Origin parsing not yet implemented");
    return nullptr;
}



bool StandardParser::isStartOfElement() {
    // TODO: 实现元素开始检查
    return false;
}

bool StandardParser::isStartOfTemplate() {
    // TODO: 实现模板开始检查
    return false;
}

bool StandardParser::isStartOfCustom() {
    // TODO: 实现自定义元素开始检查
    return false;
}

bool StandardParser::isStartOfSpecialNode() {
    // TODO: 实现特殊节点开始检查
    return false;
}

void StandardParser::skipToNextElement() {
    // TODO: 实现跳转到下一个元素
}

void StandardParser::skipToClosingTag(const std::string& tagName) {
    // TODO: 实现跳转到关闭标签
    (void)tagName; // 抑制未使用参数警告
}

void StandardParser::parseAttribute(std::shared_ptr<Element> element) {
    // 获取属性名
    if (!check(TokenType::IDENTIFIER)) {
        reportError("Expected attribute name");
        return;
    }
    
    std::string attrName = advance().getValue();
    
    // 检查是否有冒号或等号
    if (!check(TokenType::COLON) && !check(TokenType::EQUALS)) {
        // 不是属性，可能是嵌套元素
        // 创建一个新的元素节点
        auto childElement = std::make_shared<Element>(attrName);
        
        // 期待左大括号
        if (match(TokenType::LEFT_BRACE)) {
            // 递归解析这个元素的内容
            parseElementContent(childElement);
            
            // 期待右大括号
            if (!match(TokenType::RIGHT_BRACE)) {
                reportError("Expected '}' to close element '" + attrName + "'");
            }
        }
        
        element->appendChild(childElement);
        return;
    }
    
    // 跳过冒号或等号
    if (!match(TokenType::COLON) && !match(TokenType::EQUALS)) {
        reportError("Expected ':' or '=' after attribute name");
        return;
    }
    
    // 获取属性值
    std::string attrValue;
    
    if (check(TokenType::STRING_LITERAL)) {
        attrValue = advance().getValue();
        // 去除引号
        if (attrValue.size() >= 2 && 
            ((attrValue.front() == '"' && attrValue.back() == '"') ||
             (attrValue.front() == '\'' && attrValue.back() == '\''))) {
            attrValue = attrValue.substr(1, attrValue.size() - 2);
        }
    }
    else if (check(TokenType::UNQUOTED_LITERAL) || 
             check(TokenType::IDENTIFIER) ||
             check(TokenType::NUMBER)) {
        attrValue = advance().getValue();
    }
    else {
        reportError("Expected attribute value");
        return;
    }
    
    // 设置属性
    element->setAttribute(attrName, attrValue);
    
    // 期待分号
    if (!match(TokenType::SEMICOLON)) {
        reportError("Expected ';' after attribute");
    }
}

std::shared_ptr<Node> StandardParser::parseInlineStyle(std::shared_ptr<Element> element) {
    // 期待左大括号
    if (!match(TokenType::LEFT_BRACE)) {
        reportError("Expected '{' after 'style'");
        return nullptr;
    }
    
    // 创建一个Style节点
    auto styleNode = std::make_shared<Style>(Style::StyleScope::LOCAL);
    
    // 解析样式内容
    std::string styleContent;
    int braceCount = 1;
    
    while (braceCount > 0 && !isAtEnd()) {
        Token token = advance();
        
        if (token.getType() == TokenType::LEFT_BRACE) {
            braceCount++;
        } else if (token.getType() == TokenType::RIGHT_BRACE) {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        styleContent += token.getValue();
        
        // 添加适当的空格
        if (!isAtEnd() && braceCount > 0) {
            TokenType nextType = currentToken().getType();
            if (nextType != TokenType::SEMICOLON && 
                nextType != TokenType::COLON &&
                nextType != TokenType::COMMA &&
                nextType != TokenType::RIGHT_BRACE &&
                token.getType() != TokenType::LEFT_BRACE) {
                styleContent += " ";
            }
        }
    }
    
    styleNode->setCssContent(styleContent);
    
    // 解析内联样式并应用到元素
    parseInlineStyleContent(element, styleContent);
    
    return styleNode;
}

void StandardParser::parseInlineStyleContent(std::shared_ptr<Element> element, const std::string& content) {
    // 简单的CSS解析：提取直接的属性-值对
    // TODO: 实现更完整的CSS解析，包括类选择器、伪类等
    
    // 这是一个简化的实现，只处理直接的属性
    size_t pos = 0;
    while (pos < content.length()) {
        // 跳过空白
        while (pos < content.length() && std::isspace(content[pos])) {
            pos++;
        }
        
        // 查找属性名
        size_t nameStart = pos;
        while (pos < content.length() && content[pos] != ':' && content[pos] != '{') {
            pos++;
        }
        
        if (pos >= content.length()) break;
        
        if (content[pos] == '{') {
            // 这是一个选择器，跳过整个块
            int braceCount = 1;
            pos++; // 跳过 '{'
            while (pos < content.length() && braceCount > 0) {
                if (content[pos] == '{') braceCount++;
                else if (content[pos] == '}') braceCount--;
                pos++;
            }
            continue;
        }
        
        std::string propName = content.substr(nameStart, pos - nameStart);
        // 去除空白
        propName.erase(0, propName.find_first_not_of(" \t\n\r"));
        propName.erase(propName.find_last_not_of(" \t\n\r") + 1);
        
        pos++; // 跳过 ':'
        
        // 查找属性值
        size_t valueStart = pos;
        while (pos < content.length() && content[pos] != ';' && content[pos] != '}') {
            pos++;
        }
        
        std::string propValue = content.substr(valueStart, pos - valueStart);
        // 去除空白
        propValue.erase(0, propValue.find_first_not_of(" \t\n\r"));
        propValue.erase(propValue.find_last_not_of(" \t\n\r") + 1);
        
        // 应用内联样式
        if (!propName.empty() && !propValue.empty()) {
            AttributeValue styleValue = element->getAttribute("style");
            std::string currentStyle;
            if (std::holds_alternative<std::string>(styleValue)) {
                currentStyle = std::get<std::string>(styleValue);
            }
            if (!currentStyle.empty()) {
                currentStyle += " ";
            }
            currentStyle += propName + ": " + propValue + ";";
            element->setAttribute("style", currentStyle);
        }
        
        if (pos < content.length() && content[pos] == ';') {
            pos++;
        }
    }
}

} // namespace chtl