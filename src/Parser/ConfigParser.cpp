#include "Parser/ConfigParser.h"
#include "Node/Config.h"
#include "Common/Token.h"
#include <sstream>
#include <fstream> // Added for file writing

namespace chtl {

ConfigParser::ConfigParser() : BasicParser() {
}

std::shared_ptr<Node> ConfigParser::parse() {
    if (!lexer_ || !context_) {
        reportError("ConfigParser not initialized");
        return nullptr;
    }
    
    // 开始解析配置
    return parseConfiguration();
}

std::shared_ptr<Config> ConfigParser::parseConfiguration() {
    auto configNode = std::make_shared<Config>();
    
    // 期望当前是 [Configuration]
    if (!expectToken(TokenType::CONFIGURATION)) {
        reportError("Expected [Configuration]");
        return nullptr;
    }
    
    // 消费 [Configuration]
    consumeToken();
    
    // 期望 {
    if (!expectToken(TokenType::LEFT_BRACE)) {
        reportError("Expected '{' after [Configuration]");
        return configNode;
    }
    consumeToken();
    
    // 解析配置内容
    parseConfigContent(configNode);
    
    // 期望 }
    if (!expectToken(TokenType::RIGHT_BRACE)) {
        reportError("Expected '}' to close [Configuration]");
    } else {
        consumeToken();
    }
    
    return configNode;
}

void ConfigParser::parseConfigContent(std::shared_ptr<Config> configNode) {
    while (!isAtEnd() && peekNextToken().getType() != TokenType::RIGHT_BRACE) {
        Token currentToken = peekNextToken();
        
        // 跳过注释和空白
        if (currentToken.getType() == TokenType::SINGLE_LINE_COMMENT ||
            currentToken.getType() == TokenType::MULTI_LINE_COMMENT ||
            currentToken.getType() == TokenType::HTML_COMMENT) {
            consumeToken();
            continue;
        }
        
        // 检查是否是嵌套配置块 [Name]
        if (currentToken.getType() == TokenType::LEFT_BRACKET) {
            consumeToken(); // 消费 [
            
            Token nameToken = peekNextToken();
            if (nameToken.getType() == TokenType::IDENTIFIER) {
                std::string blockName = nameToken.getValue();
                consumeToken(); // 消费标识符
                
                if (!expectToken(TokenType::RIGHT_BRACKET)) {
                    reportError("Expected ']' after block name");
                    skipToNextStatement();
                    continue;
                }
                consumeToken(); // 消费 ]
                
                if (!expectToken(TokenType::LEFT_BRACE)) {
                    reportError("Expected '{' after [" + blockName + "]");
                    skipToNextStatement();
                    continue;
                }
                consumeToken(); // 消费 {
                
                // 解析嵌套配置块
                parseConfigGroup(configNode, blockName);
                
                if (!expectToken(TokenType::RIGHT_BRACE)) {
                    reportError("Expected '}' to close [" + blockName + "]");
                } else {
                    consumeToken();
                }
            }
            continue;
        }
        
        // 解析配置项
        if (currentToken.getType() == TokenType::IDENTIFIER) {
            parseConfigItem(configNode, "");
        } else {
            // 跳过未知token
            consumeToken();
        }
    }
}

void ConfigParser::parseConfigGroup(std::shared_ptr<Config> configNode, const std::string& groupName) {
    while (!isAtEnd() && peekNextToken().getType() != TokenType::RIGHT_BRACE) {
        Token currentToken = peekNextToken();
        
        // 跳过注释
        if (currentToken.getType() == TokenType::SINGLE_LINE_COMMENT ||
            currentToken.getType() == TokenType::MULTI_LINE_COMMENT ||
            currentToken.getType() == TokenType::HTML_COMMENT) {
            consumeToken();
            continue;
        }
        
        // 解析配置项
        if (currentToken.getType() == TokenType::IDENTIFIER) {
            parseConfigItem(configNode, groupName);
        } else {
            consumeToken();
        }
    }
}

void ConfigParser::parseConfigItem(std::shared_ptr<Config> configNode, const std::string& prefix) {
    // 获取配置键名
    Token keyToken = peekNextToken();
    if (keyToken.getType() != TokenType::IDENTIFIER) {
        reportError("Expected configuration key");
        skipToNextStatement();
        return;
    }
    std::string key = keyToken.getValue();
    consumeToken();
    
    // 构造完整键名
    if (!prefix.empty()) {
        key = prefix + "." + key;
    }
    
    // 期望 =
    if (!expectToken(TokenType::EQUALS)) {
        reportError("Expected '=' after configuration key");
        skipToNextStatement();
        return;
    }
    consumeToken();
    
    // 解析值
    Token valueToken = peekNextToken();
    
    // 检查是否是数组
    if (valueToken.getType() == TokenType::LEFT_BRACKET) {
        consumeToken(); // 消费 [
        
        std::vector<std::string> values;
        
        while (!isAtEnd() && peekNextToken().getType() != TokenType::RIGHT_BRACKET) {
            Token token = peekNextToken();
            
            if (token.getType() == TokenType::COMMA) {
                consumeToken();
                continue;
            }
            
            std::string value = parseConfigValue();
            if (!value.empty()) {
                values.push_back(value);
            }
        }
        
        if (!expectToken(TokenType::RIGHT_BRACKET)) {
            reportError("Expected ']' to close array value");
        } else {
            consumeToken();
        }
        
        configNode->setArrayConfig(key, values);
        
    } else {
        // 单个值
        std::string value = parseConfigValue();
        configNode->setConfig(key, value);
    }
    
    // 可选的分号
    if (peekNextToken().getType() == TokenType::SEMICOLON) {
        consumeToken();
    }
}

std::string ConfigParser::parseConfigValue() {
    Token token = peekNextToken();
    std::string value;
    
    switch (token.getType()) {
        case TokenType::STRING_LITERAL:
            value = token.getValue();
            // 去除引号
            if (value.size() >= 2 && 
                ((value.front() == '"' && value.back() == '"') ||
                 (value.front() == '\'' && value.back() == '\''))) {
                value = value.substr(1, value.size() - 2);
            }
            consumeToken();
            break;
            
        case TokenType::NUMBER:
            value = token.getValue();
            consumeToken();
            break;
            
        case TokenType::IDENTIFIER:
            value = token.getValue();
            consumeToken();
            
            // 处理布尔值
            if (value == "true" || value == "false") {
                // 保持原样
            }
            break;
            
        case TokenType::AT_STYLE:
        case TokenType::AT_ELEMENT:
        case TokenType::AT_VAR:
        case TokenType::AT_HTML:
        case TokenType::AT_JAVASCRIPT:
        case TokenType::AT_CHTL:
            value = token.getValue();
            consumeToken();
            break;
            
        case TokenType::LEFT_BRACKET:
            // 处理嵌套的特殊值如 [Custom]
            consumeToken(); // 消费 [
            if (peekNextToken().getType() == TokenType::IDENTIFIER) {
                value = "[" + peekNextToken().getValue() + "]";
                consumeToken();
                if (peekNextToken().getType() == TokenType::RIGHT_BRACKET) {
                    consumeToken();
                }
            }
            break;
            
        default:
            reportError("Unexpected token in configuration value: " + token.getValue());
            consumeToken();
            break;
    }
    
    return value;
}

void ConfigParser::exportConfig(std::shared_ptr<Config> configNode, ConfigFormat format, const std::string& filename) {
    std::string content;
    
    switch (format) {
        case ConfigFormat::JSON:
            content = exportToJSON(configNode);
            break;
        case ConfigFormat::YAML:
            content = exportToYAML(configNode);
            break;
        case ConfigFormat::INI:
            content = exportToINI(configNode);
            break;
        case ConfigFormat::TOML:
            content = exportToTOML(configNode);
            break;
        case ConfigFormat::XML:
            content = exportToXML(configNode);
            break;
        case ConfigFormat::CHTL:
            content = exportToCHTL(configNode);
            break;
    }
    
    // TODO: 写入文件
    if (!filename.empty()) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << content;
            file.close();
        }
    }
}

std::string ConfigParser::exportToJSON(std::shared_ptr<Config> configNode) {
    // TODO: 实现JSON导出
    return "{}";
}

std::string ConfigParser::exportToYAML(std::shared_ptr<Config> configNode) {
    // TODO: 实现YAML导出
    return "";
}

std::string ConfigParser::exportToINI(std::shared_ptr<Config> configNode) {
    // TODO: 实现INI导出
    return "";
}

std::string ConfigParser::exportToTOML(std::shared_ptr<Config> configNode) {
    // TODO: 实现TOML导出
    return "";
}

std::string ConfigParser::exportToXML(std::shared_ptr<Config> configNode) {
    // TODO: 实现XML导出
    return "<config></config>";
}

std::string ConfigParser::exportToCHTL(std::shared_ptr<Config> configNode) {
    // TODO: 实现CHTL导出
    return "[Configuration]\n";
}

void ConfigParser::skipToNextStatement() {
    while (!isAtEnd()) {
        Token token = peekNextToken();
        if (token.getType() == TokenType::SEMICOLON ||
            token.getType() == TokenType::RIGHT_BRACE) {
            if (token.getType() == TokenType::SEMICOLON) {
                consumeToken();
            }
            break;
        }
        consumeToken();
    }
}

} // namespace chtl