#include "Parser/ConfigParser.h"
#include "Node/Config.h"
#include <fstream>

namespace chtl {

std::shared_ptr<Config> ConfigParser::parseConfiguration() {
    auto configNode = std::make_shared<Config>();
    currentConfig_ = configNode;
    
    // 期望当前是 [Configuration]
    if (!check(TokenType::CONFIGURATION)) {
        addError("Expected [Configuration]");
        return nullptr;
    }
    
    // 消费 [Configuration]
    advance();
    
    // 期望 {
    if (!match(TokenType::LEFT_BRACE)) {
        addError("Expected '{' after [Configuration]");
        return configNode;
    }
    
    // 解析配置内容
    parseConfigContent(configNode);
    
    // 期望 }
    if (!match(TokenType::RIGHT_BRACE)) {
        addError("Expected '}' to close [Configuration]");
    }
    
    return configNode;
}

void ConfigParser::parseConfigContent(std::shared_ptr<Config> configNode) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        // 跳过注释和空白
        if (check(TokenType::SINGLE_LINE_COMMENT) ||
            check(TokenType::MULTI_LINE_COMMENT) ||
            check(TokenType::HTML_COMMENT)) {
            advance();
            continue;
        }
        
        // 检查是否是嵌套配置块 [Name]
        if (check(TokenType::LEFT_BRACKET)) {
            advance(); // 消费 [
            
            if (check(TokenType::IDENTIFIER)) {
                std::string blockName = advance().value;
                
                if (!match(TokenType::RIGHT_BRACKET)) {
                    addError("Expected ']' after block name");
                    skipToNextStatement();
                    continue;
                }
                
                if (!match(TokenType::LEFT_BRACE)) {
                    addError("Expected '{' after [" + blockName + "]");
                    skipToNextStatement();
                    continue;
                }
                
                // 解析嵌套配置块
                parseConfigGroup(configNode, blockName);
                
                if (!match(TokenType::RIGHT_BRACE)) {
                    addError("Expected '}' to close [" + blockName + "]");
                }
            }
            continue;
        }
        
        // 解析配置项
        if (check(TokenType::IDENTIFIER)) {
            parseConfigItem(configNode, "");
        } else {
            // 跳过未知token
            advance();
        }
    }
}

void ConfigParser::parseConfigGroup(std::shared_ptr<Config> configNode, const std::string& groupName) {
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        // 跳过注释
        if (check(TokenType::SINGLE_LINE_COMMENT) ||
            check(TokenType::MULTI_LINE_COMMENT) ||
            check(TokenType::HTML_COMMENT)) {
            advance();
            continue;
        }
        
        if (check(TokenType::IDENTIFIER)) {
            parseConfigItem(configNode, groupName);
        } else {
            advance();
        }
    }
}

void ConfigParser::parseConfigItem(std::shared_ptr<Config> configNode, const std::string& groupPrefix) {
    // 配置项名称
    std::string itemName = advance().value;
    
    if (!groupPrefix.empty()) {
        itemName = groupPrefix + "." + itemName;
    }
    
    // 期望 = 或 :
    if (!match(TokenType::EQUALS) && !match(TokenType::COLON)) {
        addError("Expected '=' or ':' after config item name");
        skipToNextStatement();
        return;
    }
    
    // 解析配置值
    auto value = parseConfigValue();
    if (value.has_value()) {
        configNode->setConfigItem(itemName, value.value());
    }
    
    // 期望分号或换行
    if (!match(TokenType::SEMICOLON)) {
        // 分号是可选的，但如果有其他token则报错
        if (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            // 允许换行作为语句结束
        }
    }
}

std::optional<ConfigValue> ConfigParser::parseConfigValue() {
    ConfigValue value;
    
    // 检查是否是数组 [...]
    if (check(TokenType::LEFT_BRACKET)) {
        advance();
        std::vector<std::string> arrayValues;
        
        while (!check(TokenType::RIGHT_BRACKET) && !isAtEnd()) {
            if (check(TokenType::STRING_LITERAL)) {
                arrayValues.push_back(advance().value);
            } else if (check(TokenType::IDENTIFIER)) {
                arrayValues.push_back(advance().value);
            } else if (check(TokenType::NUMBER)) {
                arrayValues.push_back(advance().value);
            } else if (check(TokenType::AT_PREFIX)) {
                // 处理 @Style 等
                std::string atValue = advance().value;
                if (check(TokenType::IDENTIFIER)) {
                    atValue += " " + advance().value;
                }
                arrayValues.push_back(atValue);
            }
            
            // 跳过逗号
            match(TokenType::COMMA);
        }
        
        if (!match(TokenType::RIGHT_BRACKET)) {
            addError("Expected ']' to close array");
        }
        
        value = arrayValues;
    }
    // 字符串值
    else if (check(TokenType::STRING_LITERAL)) {
        value = advance().value;
    }
    // 数字值
    else if (check(TokenType::NUMBER)) {
        value = advance().value;
    }
    // 布尔值
    else if (check(TokenType::TRUE) || check(TokenType::FALSE)) {
        value = advance().value;
    }
    // 标识符值
    else if (check(TokenType::IDENTIFIER)) {
        value = advance().value;
    }
    // @前缀值
    else if (check(TokenType::AT_PREFIX)) {
        std::string atValue = advance().value;
        if (check(TokenType::IDENTIFIER)) {
            atValue += " " + advance().value;
        }
        value = atValue;
    }
    else {
        addError("Expected config value");
        return std::nullopt;
    }
    
    return value;
}

void ConfigParser::skipToNextStatement() {
    while (!isAtEnd()) {
        if (match(TokenType::SEMICOLON) || 
            check(TokenType::RIGHT_BRACE)) {
            break;
        }
        advance();
    }
}

bool ConfigParser::exportConfig(std::shared_ptr<Config> config, 
                               const std::string& filename,
                               ConfigFormat format) {
    if (!config) {
        return false;
    }
    
    std::string content;
    
    switch (format) {
        case ConfigFormat::JSON:
            content = exportToJSON(config);
            break;
        case ConfigFormat::YAML:
            content = exportToYAML(config);
            break;
        case ConfigFormat::INI:
            content = exportToINI(config);
            break;
        case ConfigFormat::TOML:
            content = exportToTOML(config);
            break;
        case ConfigFormat::XML:
            content = exportToXML(config);
            break;
        case ConfigFormat::CHTL:
        default:
            content = exportToCHTL(config);
            break;
    }
    
    // 写入文件
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    file.close();
    
    return true;
}

std::string ConfigParser::exportToJSON(std::shared_ptr<Config> config) {
    // TODO: 实现JSON导出
    return "{\n  // JSON export not implemented yet\n}\n";
}

std::string ConfigParser::exportToYAML(std::shared_ptr<Config> config) {
    // TODO: 实现YAML导出
    return "# YAML export not implemented yet\n";
}

std::string ConfigParser::exportToINI(std::shared_ptr<Config> config) {
    // TODO: 实现INI导出
    return "; INI export not implemented yet\n";
}

std::string ConfigParser::exportToTOML(std::shared_ptr<Config> config) {
    // TODO: 实现TOML导出
    return "# TOML export not implemented yet\n";
}

std::string ConfigParser::exportToXML(std::shared_ptr<Config> config) {
    // TODO: 实现XML导出
    return "<!-- XML export not implemented yet -->\n<config>\n</config>\n";
}

std::string ConfigParser::exportToCHTL(std::shared_ptr<Config> config) {
    // TODO: 实现CHTL导出
    return "[Configuration]\n{\n  // CHTL export not implemented yet\n}\n";
}

ConfigFormat ConfigParser::detectFormat(const std::string& content) {
    // 简单的格式检测
    if (content.find("[Configuration]") != std::string::npos) {
        return ConfigFormat::CHTL;
    }
    if (content[0] == '{' || content.find("\"") != std::string::npos) {
        return ConfigFormat::JSON;
    }
    if (content.find("---") == 0 || content.find(": ") != std::string::npos) {
        return ConfigFormat::YAML;
    }
    if (content.find("[") != std::string::npos && content.find("=") != std::string::npos) {
        return ConfigFormat::INI;
    }
    if (content.find("[[") != std::string::npos || content.find("=") != std::string::npos) {
        return ConfigFormat::TOML;
    }
    if (content.find("<?xml") != std::string::npos || content.find("<") != std::string::npos) {
        return ConfigFormat::XML;
    }
    
    return ConfigFormat::CHTL;
}

// 静态成员定义
const std::unordered_set<std::string> ConfigParser::VALID_CONFIG_KEYS = {
    "INDEX_INITIAL_COUNT",
    "DISABLE_NAME_GROUP",
    "DEBUG_MODE",
    "OPTION_COUNT",
    // Name组配置项
    "CUSTOM_STYLE",
    "CUSTOM_ELEMENT", 
    "CUSTOM_VAR",
    "TEMPLATE_STYLE",
    "TEMPLATE_ELEMENT",
    "TEMPLATE_VAR",
    "ORIGIN_HTML",
    "ORIGIN_STYLE",
    "ORIGIN_JAVASCRIPT",
    "KEYWORD_INHERIT",
    "KEYWORD_DELETE",
    "KEYWORD_INSERT",
    "KEYWORD_AFTER",
    "KEYWORD_BEFORE",
    "KEYWORD_REPLACE",
    "KEYWORD_ATTOP",
    "KEYWORD_ATBOTTOM",
    "KEYWORD_FROM",
    "KEYWORD_AS",
    "KEYWORD_EXCEPT",
    "KEYWORD_TEXT",
    "KEYWORD_STYLE",
    "KEYWORD_CUSTOM",
    "KEYWORD_TEMPLATE",
    "KEYWORD_ORIGIN",
    "KEYWORD_IMPORT",
    "KEYWORD_NAMESPACE"
};

} // namespace chtl