#include "Parser/ConfigParser.h"
#include "Lexer/ConfigLexer.h"
#include "Context/ChtlContext.h"
#include <iostream>
#include <sstream>

namespace chtl {

// 定义有效的配置键
const std::unordered_set<std::string> ConfigParser::VALID_CONFIG_KEYS = {
    "output_dir", "input_dir", "target", "version", "debug", "optimize",
    "encoding", "strict_mode", "max_errors", "max_warnings",
    "include_paths", "library_paths", "defines", "features",
    "keyword_aliases", "import_aliases", "extensions", "plugins",
    "license", "author", "description", "homepage"
};

const std::unordered_set<std::string> ConfigParser::ARRAY_CONFIG_KEYS = {
    "include_paths", "library_paths", "defines", "features",
    "keyword_aliases", "import_aliases", "extensions", "plugins"
};

ConfigParser::ConfigParser()
    : BasicParser(), configState_(ConfigParseState::INITIAL) {
}

void ConfigParser::initializeParser() {
    configState_ = ConfigParseState::INITIAL;
    currentConfig_ = nullptr;
    currentKey_.clear();
    currentArray_.clear();
}

void ConfigParser::finalizeParser() {
    if (currentConfig_) {
        applySpecialConfigurations();
    }
}

std::shared_ptr<Node> ConfigParser::parse() {
    auto config = parseConfiguration();
    if (config) {
        rootNode_ = config;
        state_ = ParseState::SUCCESS;
    }
    return rootNode_;
}

std::shared_ptr<Config> ConfigParser::parseConfiguration() {
    initializeParser();
    configState_ = ConfigParseState::EXPECT_CONFIGURATION;
    
    // 查找[Configuration]标记
    while (!isAtEnd()) {
        Token token = peekNextToken();
        
        if (token.getType() == TokenType::CONFIGURATION) {
            consumeToken();
            configState_ = ConfigParseState::EXPECT_NAME_OR_BRACE;
            break;
        } else if (token.getType() == TokenType::EOF_TOKEN) {
            reportError("No [Configuration] block found");
            return nullptr;
        } else {
            // 跳过非配置token
            consumeToken();
        }
    }
    
    if (configState_ != ConfigParseState::EXPECT_NAME_OR_BRACE) {
        return nullptr;
    }
    
    // 创建配置节点
    currentConfig_ = std::make_shared<Config>();
    
    // 解析可选的配置名称
    Token nextToken = peekNextToken();
    if (nextToken.getType() == TokenType::IDENTIFIER) {
        currentConfig_->setConfigName(nextToken.getValue());
        consumeToken();
    }
    
    // 期望左大括号
    if (!expectToken(TokenType::LEFT_BRACE, "Expected '{' after [Configuration]")) {
        return nullptr;
    }
    
    configState_ = ConfigParseState::IN_CONFIG_BLOCK;
    
    // 解析配置块
    if (!parseConfigurationBlock()) {
        return nullptr;
    }
    
    // 期望右大括号
    if (!expectToken(TokenType::RIGHT_BRACE, "Expected '}' to close [Configuration] block")) {
        return nullptr;
    }
    
    configState_ = ConfigParseState::COMPLETE;
    finalizeParser();
    
    return currentConfig_;
}

std::shared_ptr<Config> ConfigParser::parseConfigurationFromFile(const std::string& filename) {
    // 创建专门的ConfigLexer
    auto lexer = std::make_shared<ConfigLexer>();
    auto context = std::make_shared<ChtlContext>();
    
    if (!initialize(lexer, context)) {
        return nullptr;
    }
    
    if (!lexer_->initialize(filename)) {
        reportError("Failed to open configuration file: " + filename);
        return nullptr;
    }
    
    return parseConfiguration();
}

std::shared_ptr<Config> ConfigParser::parseConfigurationFromString(const std::string& content) {
    // 创建专门的ConfigLexer
    auto lexer = std::make_shared<ConfigLexer>();
    auto context = std::make_shared<ChtlContext>();
    
    if (!initialize(lexer, context)) {
        return nullptr;
    }
    
    auto stream = std::make_unique<std::istringstream>(content);
    if (!lexer_->initialize(std::move(stream), "<config-string>")) {
        reportError("Failed to initialize configuration parser");
        return nullptr;
    }
    
    return parseConfiguration();
}

bool ConfigParser::parseConfigurationBlock() {
    while (configState_ == ConfigParseState::IN_CONFIG_BLOCK && !isAtEnd()) {
        Token token = peekNextToken();
        
        if (token.getType() == TokenType::RIGHT_BRACE) {
            // 配置块结束
            return true;
        }
        
        if (token.getType() == TokenType::IDENTIFIER) {
            currentKey_ = token.getValue();
            consumeToken();
            
            if (!isValidConfigKey(currentKey_)) {
                reportWarning("Unknown configuration key: " + currentKey_);
            }
            
            if (!expectToken(TokenType::COLON, "Expected ':' after configuration key")) {
                synchronize();
                continue;
            }
            
            if (isArrayConfigKey(currentKey_)) {
                if (!parseConfigArray()) {
                    synchronize();
                    continue;
                }
            } else {
                if (!parseConfigValue()) {
                    synchronize();
                    continue;
                }
            }
            
            if (!expectToken(TokenType::SEMICOLON, "Expected ';' after configuration value")) {
                synchronize();
                continue;
            }
        } else {
            reportError("Expected configuration key", token);
            synchronize();
        }
    }
    
    return !hasErrors();
}

bool ConfigParser::parseConfigValue() {
    std::string value;
    
    Token token = peekNextToken();
    switch (token.getType()) {
        case TokenType::STRING_LITERAL:
            consumeToken();
            value = token.getValue();
            break;
            
        case TokenType::NUMBER:
            consumeToken();
            value = token.getValue();
            break;
            
        case TokenType::IDENTIFIER:
            consumeToken();
            value = token.getValue();
            break;
            

            
        default:
            reportError("Invalid configuration value", token);
            return false;
    }
    
    if (validateConfigValue(currentKey_, value)) {
        currentConfig_->setConfig(currentKey_, value);
        return true;
    }
    
    return false;
}

bool ConfigParser::parseConfigArray() {
    currentArray_.clear();
    
    if (!expectToken(TokenType::LEFT_BRACKET, "Expected '[' to start array")) {
        return false;
    }
    
    // 解析数组元素
    bool first = true;
    while (!isAtEnd()) {
        Token token = peekNextToken();
        
        if (token.getType() == TokenType::RIGHT_BRACKET) {
            consumeToken();
            break;
        }
        
        if (!first) {
            if (!expectToken(TokenType::COMMA, "Expected ',' between array elements")) {
                return false;
            }
        }
        first = false;
        
        std::string element;
        if (!parseArrayElement(element)) {
            return false;
        }
        currentArray_.push_back(element);
    }
    
    if (validateArrayValues(currentKey_, currentArray_)) {
        currentConfig_->setArrayConfig(currentKey_, currentArray_);
        return true;
    }
    
    return false;
}

bool ConfigParser::parseArrayElement(std::string& result) {
    Token token = peekNextToken();
    
    switch (token.getType()) {
        case TokenType::STRING_LITERAL:
        case TokenType::IDENTIFIER:
        case TokenType::NUMBER:
            consumeToken();
            result = token.getValue();
            return true;
            
        default:
            reportError("Invalid array element", token);
            return false;
    }
}

bool ConfigParser::isValidConfigKey(const std::string& key) const {
    return VALID_CONFIG_KEYS.find(key) != VALID_CONFIG_KEYS.end();
}

bool ConfigParser::isArrayConfigKey(const std::string& key) const {
    return ARRAY_CONFIG_KEYS.find(key) != ARRAY_CONFIG_KEYS.end();
}

bool ConfigParser::validateConfigValue(const std::string& key, const std::string& value) {
    // 基本验证
    if (key == "debug" || key == "optimize" || key == "strict_mode") {
        if (value != "true" && value != "false") {
            reportError("Configuration key '" + key + "' must be true or false");
            return false;
        }
    } else if (key == "max_errors" || key == "max_warnings") {
        try {
            int num = std::stoi(value);
            if (num < 0) {
                reportError("Configuration key '" + key + "' must be non-negative");
                return false;
            }
        } catch (...) {
            reportError("Configuration key '" + key + "' must be a number");
            return false;
        }
    }
    
    return true;
}

bool ConfigParser::validateArrayValues(const std::string& key, const std::vector<std::string>& values) {
    if (key == "keyword_aliases") {
        // 关键字别名必须成对出现
        if (values.size() % 2 != 0) {
            reportError("keyword_aliases must contain pairs of (keyword, alias)");
            return false;
        }
    }
    
    return true;
}

void ConfigParser::applySpecialConfigurations() {
    if (!currentConfig_ || !context_) {
        return;
    }
    
    applyKeywordAliases();
    applyImportPaths();
    
    // 应用其他特殊配置
    if (currentConfig_->hasConfig("debug")) {
        bool debug = currentConfig_->getConfig("debug") == "true";
        context_->setConfig("debug_mode", debug ? "true" : "false");
    }
    
    if (currentConfig_->hasConfig("strict_mode")) {
        bool strict = currentConfig_->getConfig("strict_mode") == "true";
        context_->setConfig("strict_mode", strict ? "true" : "false");
    }
}

void ConfigParser::applyKeywordAliases() {
    if (!currentConfig_->hasArrayConfig("keyword_aliases")) {
        return;
    }
    
    auto aliases = currentConfig_->getArrayConfig("keyword_aliases");
    auto chtlContext = std::dynamic_pointer_cast<ChtlContext>(context_);
    
    if (chtlContext) {
        for (size_t i = 0; i + 1 < aliases.size(); i += 2) {
            chtlContext->addKeywordAlias(aliases[i], aliases[i + 1]);
        }
    }
}

void ConfigParser::applyImportPaths() {
    if (!currentConfig_->hasArrayConfig("include_paths")) {
        return;
    }
    
    auto paths = currentConfig_->getArrayConfig("include_paths");
    for (const auto& path : paths) {
        context_->setConfig("include_path", path);
    }
}

} // namespace chtl