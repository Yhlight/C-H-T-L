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
    // 不要调用getNextToken()，因为peekNextToken()已经会获取第一个token
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
            auto template_ = parseTemplate();
            if (template_) {
                document->appendChild(template_);
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
            // std::cerr << "DEBUG: Found STYLE keyword" << std::endl;
            advance(); // 跳过 style 关键字
            auto styleNode = parseInlineStyle(element);
            if (styleNode) {
                element->appendChild(styleNode);
            }
            // std::cerr << "DEBUG: After parseInlineStyle, current token: " << currentToken().getValue() << std::endl;
            continue;
        }
        
        // 检查是否是模板使用 (@Style, @Element, @Var)
        if (check(TokenType::AT_STYLE) || check(TokenType::AT_ELEMENT) || check(TokenType::AT_VAR)) {
            parseTemplateUsage(element);
            continue;
        }
        
        // 解析嵌套元素
        auto child = parseElement();
        if (child) {
            element->appendChild(child);
        } else {
            // 无法识别的内容
            std::string tokenValue = currentToken().getValue();
            if (tokenValue.empty()) {
                tokenValue = "<empty>";
            }
            reportError("Unexpected token in element: '" + tokenValue + "' (type: " + std::to_string(static_cast<int>(currentToken().getType())) + ")");
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
    // 跳过 [Template]
    if (!match(TokenType::TEMPLATE)) {
        return nullptr;
    }
    
    // 期待 @Style, @Element, 或 @Var
    Token typeToken = currentToken();
    Template::TemplateType templateType;
    
    if (check(TokenType::AT_STYLE)) {
        advance();
        templateType = Template::TemplateType::STYLE;
    } else if (check(TokenType::AT_ELEMENT)) {
        advance();
        templateType = Template::TemplateType::ELEMENT;
    } else if (check(TokenType::AT_VAR)) {
        advance();
        templateType = Template::TemplateType::VAR;
    } else {
        reportError("Expected @Style, @Element, or @Var after [Template]");
        return nullptr;
    }
    
    // 期待模板名称
    if (!check(TokenType::IDENTIFIER)) {
        reportError("Expected template name");
        return nullptr;
    }
    
    std::string templateName = advance().getValue();
    auto templateNode = std::make_shared<Template>(templateType, templateName);
    
    // 期待左大括号
    if (!match(TokenType::LEFT_BRACE)) {
        reportError("Expected '{' after template name");
        return templateNode;
    }
    
    // 解析模板内容
    parseTemplateContent(templateNode);
    
    // 期待右大括号
    if (!match(TokenType::RIGHT_BRACE)) {
        reportError("Expected '}' to close template");
    }
    
    return templateNode;
}

std::shared_ptr<Node> StandardParser::parseCustom() {
    // 跳过 [Custom]
    if (!match(TokenType::CUSTOM)) {
        return nullptr;
    }
    
    // 期待 @Style, @Element, 或 @Var
    Custom::CustomType customType;
    
    if (check(TokenType::AT_STYLE)) {
        advance();
        customType = Custom::CustomType::STYLE;
    } else if (check(TokenType::AT_ELEMENT)) {
        advance();
        customType = Custom::CustomType::ELEMENT;
    } else if (check(TokenType::AT_VAR)) {
        advance();
        customType = Custom::CustomType::VAR;
    } else {
        reportError("Expected @Style, @Element, or @Var after [Custom]");
        return nullptr;
    }
    
    // 期待自定义名称
    if (!check(TokenType::IDENTIFIER)) {
        reportError("Expected custom name");
        return nullptr;
    }
    
    std::string customName = advance().getValue();
    auto customNode = std::make_shared<Custom>(customType, customName);
    
    // 期待左大括号
    if (!match(TokenType::LEFT_BRACE)) {
        reportError("Expected '{' after custom name");
        return customNode;
    }
    
    // 解析自定义内容
    parseCustomContent(customNode);
    
    // 期待右大括号
    if (!match(TokenType::RIGHT_BRACE)) {
        reportError("Expected '}' to close custom");
    }
    
    return customNode;
}

std::shared_ptr<Node> StandardParser::parseStyle() {
    // TODO: 实现样式解析
    reportError("Style parsing not yet implemented");
    return nullptr;
}

std::shared_ptr<Node> StandardParser::parseConfig() {
    // 跳过 [Configuration]
    if (!match(TokenType::CONFIGURATION)) {
        return nullptr;
    }
    
    auto configNode = std::make_shared<Config>();
    
    // 期待左大括号
    if (!match(TokenType::LEFT_BRACE)) {
        reportError("Expected '{' after [Configuration]");
        return configNode;
    }
    
    // 解析配置内容
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        // 跳过注释
        if (check(TokenType::HTML_COMMENT) || check(TokenType::SINGLE_LINE_COMMENT)) {
            advance();
            continue;
        }
        
        // 检查是否是嵌套的[Name]或其他配置组
        if (check(TokenType::LEFT_BRACKET)) {
            advance(); // 跳过 [
            if (check(TokenType::IDENTIFIER)) {
                std::string groupName = advance().getValue();
                if (!match(TokenType::RIGHT_BRACKET)) {
                    reportError("Expected ']' after group name");
                }
                
                if (match(TokenType::LEFT_BRACE)) {
                    // 解析嵌套配置组
                    parseConfigGroup(configNode, groupName);
                    match(TokenType::RIGHT_BRACE);
                }
            }
            continue;
        }
        
        // 解析配置项
        if (check(TokenType::IDENTIFIER)) {
            std::string key = advance().getValue();
            
            if (match(TokenType::EQUALS)) {
                // 解析值
                if (check(TokenType::LEFT_BRACKET)) {
                    // 数组值
                    advance(); // 跳过 [
                    std::vector<std::string> values;
                    
                    while (!check(TokenType::RIGHT_BRACKET) && !isAtEnd()) {
                        std::string value;
                        
                        if (check(TokenType::AT_STYLE) || check(TokenType::AT_ELEMENT) || 
                            check(TokenType::AT_VAR) || check(TokenType::AT_HTML) || 
                            check(TokenType::AT_JAVASCRIPT)) {
                            // @ 符号开头的值
                            value = advance().getValue();
                        } else if (check(TokenType::IDENTIFIER)) {
                            value = advance().getValue();
                        } else if (check(TokenType::STRING_LITERAL)) {
                            value = advance().getValue();
                            // 去除引号
                            if (value.size() >= 2) {
                                value = value.substr(1, value.size() - 2);
                            }
                        } else if (check(TokenType::NUMBER)) {
                            value = advance().getValue();
                        } else {
                            advance(); // 跳过无法识别的token
                            continue;
                        }
                        
                        values.push_back(value);
                        
                        // 跳过逗号
                        if (check(TokenType::COMMA)) {
                            advance();
                        }
                    }
                    
                    if (!match(TokenType::RIGHT_BRACKET)) {
                        reportError("Expected ']' to close array value");
                    }
                    
                    configNode->setArrayConfig(key, values);
                    
                } else {
                    // 单个值
                    std::string value;
                    
                    if (check(TokenType::STRING_LITERAL)) {
                        value = advance().getValue();
                        // 去除引号
                        if (value.size() >= 2) {
                            value = value.substr(1, value.size() - 2);
                        }
                    } else if (check(TokenType::IDENTIFIER)) {
                        value = advance().getValue();
                    } else if (check(TokenType::NUMBER)) {
                        value = advance().getValue();
                    } else if (check(TokenType::TRUE) || check(TokenType::FALSE)) {
                        value = advance().getValue();
                    } else if (check(TokenType::AT_STYLE) || check(TokenType::AT_ELEMENT) || 
                               check(TokenType::AT_VAR) || check(TokenType::AT_HTML)) {
                        value = advance().getValue();
                    } else {
                        reportError("Expected configuration value");
                    }
                    
                    configNode->setConfig(key, value);
                }
                
                // 跳过分号（可选）
                match(TokenType::SEMICOLON);
            }
        } else {
            // 跳过无法识别的内容
            advance();
        }
    }
    
    // 期待右大括号
    if (!match(TokenType::RIGHT_BRACE)) {
        reportError("Expected '}' to close [Configuration]");
    }
    
    return configNode;
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



void StandardParser::parseConfigGroup(std::shared_ptr<Config> configNode, const std::string& groupName) {
    // 解析嵌套的配置组，例如 [Name] 块
    // 将组内的配置项添加到配置节点，使用 groupName.key 格式
    
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        // 跳过注释
        if (check(TokenType::HTML_COMMENT) || check(TokenType::SINGLE_LINE_COMMENT)) {
            advance();
            continue;
        }
        
        // 解析配置项
        if (check(TokenType::IDENTIFIER)) {
            std::string key = advance().getValue();
            
            if (match(TokenType::EQUALS)) {
                // 构造完整的键名
                std::string fullKey = groupName + "." + key;
                
                // 解析值（与parseConfig中相同的逻辑）
                if (check(TokenType::LEFT_BRACKET)) {
                    // 数组值
                    advance(); // 跳过 [
                    std::vector<std::string> values;
                    
                    while (!check(TokenType::RIGHT_BRACKET) && !isAtEnd()) {
                        std::string value;
                        
                        if (check(TokenType::AT_STYLE) || check(TokenType::AT_ELEMENT) || 
                            check(TokenType::AT_VAR) || check(TokenType::AT_HTML) || 
                            check(TokenType::AT_JAVASCRIPT)) {
                            value = advance().getValue();
                        } else if (check(TokenType::IDENTIFIER)) {
                            value = advance().getValue();
                        } else if (check(TokenType::STRING_LITERAL)) {
                            value = advance().getValue();
                            if (value.size() >= 2) {
                                value = value.substr(1, value.size() - 2);
                            }
                        } else if (check(TokenType::NUMBER)) {
                            value = advance().getValue();
                        } else {
                            advance();
                            continue;
                        }
                        
                        values.push_back(value);
                        
                        if (check(TokenType::COMMA)) {
                            advance();
                        }
                    }
                    
                    if (!match(TokenType::RIGHT_BRACKET)) {
                        reportError("Expected ']' to close array value");
                    }
                    
                    configNode->setArrayConfig(fullKey, values);
                    
                } else {
                    // 单个值
                    std::string value;
                    
                    if (check(TokenType::STRING_LITERAL)) {
                        value = advance().getValue();
                        if (value.size() >= 2) {
                            value = value.substr(1, value.size() - 2);
                        }
                    } else if (check(TokenType::IDENTIFIER)) {
                        value = advance().getValue();
                    } else if (check(TokenType::NUMBER)) {
                        value = advance().getValue();
                    } else if (check(TokenType::TRUE) || check(TokenType::FALSE)) {
                        value = advance().getValue();
                    } else if (check(TokenType::AT_STYLE) || check(TokenType::AT_ELEMENT) || 
                               check(TokenType::AT_VAR) || check(TokenType::AT_HTML)) {
                        value = advance().getValue();
                    } else {
                        reportError("Expected configuration value");
                    }
                    
                    configNode->setConfig(fullKey, value);
                }
                
                match(TokenType::SEMICOLON);
            }
        } else {
            advance();
        }
    }
}

void StandardParser::parseTemplateUsage(std::shared_ptr<Element> element) {
    // 这里简单地将模板使用作为元素的属性记录
    // 在实际的编译过程中，需要展开模板
    
    std::string templateType;
    if (check(TokenType::AT_STYLE)) {
        advance();
        templateType = "@Style";
    } else if (check(TokenType::AT_ELEMENT)) {
        advance();
        templateType = "@Element";
    } else if (check(TokenType::AT_VAR)) {
        advance();
        templateType = "@Var";
    } else {
        return;
    }
    
    if (check(TokenType::IDENTIFIER)) {
        std::string templateName = advance().getValue();
        
        // 记录模板使用
        element->setAttribute("chtl-template-" + templateType, templateName);
        
        // 检查是否有参数块
        if (check(TokenType::LEFT_BRACE)) {
            advance(); // 跳过 {
            
            // TODO: 解析模板参数/特例化
            // 目前简单跳过内容
            int braceCount = 1;
            while (braceCount > 0 && !isAtEnd()) {
                if (check(TokenType::LEFT_BRACE)) {
                    braceCount++;
                } else if (check(TokenType::RIGHT_BRACE)) {
                    braceCount--;
                }
                advance();
            }
        } else {
            // 简单使用，期待分号
            match(TokenType::SEMICOLON);
        }
    }
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
    int indentLevel = 0;
    bool needSpace = false;
    
    // std::cerr << "DEBUG: parseInlineStyle started, next token: " << currentToken().getValue() << " type: " << static_cast<int>(currentToken().getType()) << std::endl;
    
    while (braceCount > 0 && !isAtEnd()) {
        Token token = currentToken();
        TokenType tokenType = token.getType();
        std::string tokenValue = token.getValue();
        
        advance(); // 在获取token信息后前进
        
        // std::cerr << "DEBUG: style token type=" << static_cast<int>(tokenType) << " value=\"" << tokenValue << "\" braceCount=" << braceCount << std::endl;
        
        // 跳过C风格注释
        if (tokenType == TokenType::SINGLE_LINE_COMMENT || 
            tokenType == TokenType::MULTI_LINE_COMMENT) {
            continue;
        }
        
        // 处理大括号
        if (tokenType == TokenType::LEFT_BRACE) {
            braceCount++;
            indentLevel++;
            styleContent += " {\n" + std::string(indentLevel * 2, ' ');
            needSpace = false;
        } 
        else if (tokenType == TokenType::RIGHT_BRACE) {
            braceCount--;
            if (braceCount == 0) {
                // 不要将最后的右大括号添加到内容中
                break;
            }
            
            indentLevel--;
            // 去除尾部空格
            while (!styleContent.empty() && std::isspace(styleContent.back())) {
                styleContent.pop_back();
            }
            styleContent += "\n" + std::string(indentLevel * 2, ' ') + "}";
            
            // 如果还有内容，添加换行
            if (braceCount > 0 && !isAtEnd() && currentToken().getType() != TokenType::RIGHT_BRACE) {
                styleContent += "\n" + std::string(indentLevel * 2, ' ');
            }
            needSpace = false;
        }
        // 处理分号
        else if (tokenType == TokenType::SEMICOLON) {
            styleContent += ";";
            if (braceCount == 1 && !isAtEnd() && currentToken().getType() != TokenType::RIGHT_BRACE) {
                styleContent += "\n" + std::string(indentLevel * 2, ' ');
            }
            needSpace = false;
        }
        // 处理冒号
        else if (tokenType == TokenType::COLON) {
            styleContent += ": ";
            needSpace = false;
        }
        // 处理逗号
        else if (tokenType == TokenType::COMMA) {
            styleContent += ", ";
            needSpace = false;
        }
        // 处理点（类选择器）
        else if (tokenType == TokenType::DOT) {
            styleContent += ".";
            needSpace = false;
        }
        // 处理与符号（CHTL特殊语法）
        else if (tokenType == TokenType::AMPERSAND) {
            styleContent += "&";
            needSpace = false;
        }
        // 处理其他token
        else {
            if (needSpace && !styleContent.empty() && !std::isspace(styleContent.back())) {
                styleContent += " ";
            }
            styleContent += tokenValue;
            needSpace = true;
            
            // 特殊处理：数值和单位之间不需要空格
            if (tokenType == TokenType::NUMBER) {
                needSpace = false;
            }
        }
    }
    
    styleNode->setCssContent(styleContent);
    
    // 解析内联样式并应用到元素
    parseInlineStyleContent(element, styleContent);
    
    return styleNode;
}

void StandardParser::parseTemplateContent(std::shared_ptr<Template> templateNode) {
    Template::TemplateType type = templateNode->getTemplateType();
    
    switch (type) {
        case Template::TemplateType::STYLE:
            // 解析样式模板内容：CSS属性和继承
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                // 检查是否是继承语句
                if (check(TokenType::AT_STYLE)) {
                    advance(); // 跳过 @Style
                    if (check(TokenType::IDENTIFIER)) {
                        std::string inheritName = advance().getValue();
                        templateNode->addInheritance(inheritName);
                        match(TokenType::SEMICOLON);
                    }
                    continue;
                }
                
                // 检查inherit关键字
                if (check(TokenType::INHERIT)) {
                    advance(); // 跳过 inherit
                    if (check(TokenType::AT_STYLE)) {
                        advance(); // 跳过 @Style
                        if (check(TokenType::IDENTIFIER)) {
                            std::string inheritName = advance().getValue();
                            templateNode->addInheritance(inheritName);
                            templateNode->setExplicitInherit(true);
                            match(TokenType::SEMICOLON);
                        }
                    }
                    continue;
                }
                
                // 解析CSS属性
                if (check(TokenType::IDENTIFIER)) {
                    std::string propertyName = advance().getValue();
                    if (match(TokenType::COLON)) {
                        // 收集属性值直到分号
                        std::string value;
                        while (!check(TokenType::SEMICOLON) && !isAtEnd()) {
                            value += currentToken().getValue();
                            if (!isAtEnd()) {
                                advance();
                                if (!check(TokenType::SEMICOLON)) {
                                    value += " ";
                                }
                            }
                        }
                        // 去除尾部空格
                        while (!value.empty() && std::isspace(value.back())) {
                            value.pop_back();
                        }
                        templateNode->setParameter(propertyName, value);
                        match(TokenType::SEMICOLON);
                    }
                } else {
                    // 跳过无法识别的token
                    advance();
                }
            }
            break;
            
        case Template::TemplateType::ELEMENT:
            // 解析元素模板内容：嵌套元素
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                // 检查是否是继承语句
                if (check(TokenType::AT_ELEMENT)) {
                    advance(); // 跳过 @Element
                    if (check(TokenType::IDENTIFIER)) {
                        std::string inheritName = advance().getValue();
                        templateNode->addInheritance(inheritName);
                        match(TokenType::SEMICOLON);
                    }
                    continue;
                }
                
                // 解析子元素
                auto element = parseElement();
                if (element) {
                    templateNode->appendChild(element);
                } else {
                    // 无法识别的内容
                    advance();
                }
            }
            break;
            
        case Template::TemplateType::VAR:
            // 解析变量模板内容：变量定义
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                if (check(TokenType::IDENTIFIER)) {
                    std::string varName = advance().getValue();
                    if (match(TokenType::COLON)) {
                        std::string value;
                        // 获取值（可能是字符串或其他）
                        if (check(TokenType::STRING_LITERAL)) {
                            value = advance().getValue();
                            // 去除引号
                            if (value.size() >= 2 && 
                                ((value.front() == '"' && value.back() == '"') ||
                                 (value.front() == '\'' && value.back() == '\''))) {
                                value = value.substr(1, value.size() - 2);
                            }
                        } else {
                            // 收集直到分号
                            while (!check(TokenType::SEMICOLON) && !isAtEnd()) {
                                value += currentToken().getValue();
                                advance();
                                if (!check(TokenType::SEMICOLON)) {
                                    value += " ";
                                }
                            }
                        }
                        templateNode->setParameter(varName, value);
                        match(TokenType::SEMICOLON);
                    }
                } else {
                    advance();
                }
            }
            break;
    }
}

void StandardParser::parseCustomContent(std::shared_ptr<Custom> customNode) {
    Custom::CustomType type = customNode->getCustomType();
    
    switch (type) {
        case Custom::CustomType::STYLE:
            // 解析自定义样式内容：属性列表（可能没有值）
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                if (check(TokenType::IDENTIFIER)) {
                    std::string propertyName = advance().getValue();
                    
                    // 检查是否有值
                    if (check(TokenType::COLON)) {
                        advance(); // 跳过冒号
                        // 收集值
                        std::string value;
                        while (!check(TokenType::SEMICOLON) && !check(TokenType::COMMA) && !isAtEnd()) {
                            value += currentToken().getValue();
                            advance();
                            if (!check(TokenType::SEMICOLON) && !check(TokenType::COMMA)) {
                                value += " ";
                            }
                        }
                        // 去除尾部空格
                        while (!value.empty() && std::isspace(value.back())) {
                            value.pop_back();
                        }
                        customNode->setProperty(propertyName, value);
                    } else {
                        // 没有值的属性
                        customNode->setProperty(propertyName, "");
                    }
                    
                    // 跳过分号或逗号
                    if (check(TokenType::SEMICOLON) || check(TokenType::COMMA)) {
                        advance();
                    }
                } else {
                    advance();
                }
            }
            break;
            
        case Custom::CustomType::ELEMENT:
            // 解析自定义元素内容：嵌套元素
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                auto element = parseElement();
                if (element) {
                    customNode->appendChild(element);
                } else {
                    advance();
                }
            }
            break;
            
        case Custom::CustomType::VAR:
            // 解析自定义变量内容：变量定义
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                if (check(TokenType::IDENTIFIER)) {
                    std::string varName = advance().getValue();
                    
                    if (check(TokenType::COLON)) {
                        advance(); // 跳过冒号
                        std::string value;
                        
                        if (check(TokenType::STRING_LITERAL)) {
                            value = advance().getValue();
                            // 去除引号
                            if (value.size() >= 2) {
                                value = value.substr(1, value.size() - 2);
                            }
                        } else {
                            // 收集直到分号
                            while (!check(TokenType::SEMICOLON) && !isAtEnd()) {
                                value += currentToken().getValue();
                                advance();
                                if (!check(TokenType::SEMICOLON)) {
                                    value += " ";
                                }
                            }
                        }
                        customNode->setProperty(varName, value);
                    } else {
                        // 没有值的变量
                        customNode->setProperty(varName, "");
                    }
                    
                    match(TokenType::SEMICOLON);
                } else {
                    advance();
                }
            }
            break;
    }
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