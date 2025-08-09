#include "Lexer/ConfigLexer.h"
#include "state/StateFactory.h"
#include "context/ContextFactory.h"
#include <sstream>
#include <algorithm>

namespace chtl {

ConfigLexer::ConfigLexer()
    : BasicLexer() {
}

std::shared_ptr<BasicState> ConfigLexer::createInitialState() {
    // ConfigLexer使用特殊的配置状态
    return StateFactory::createState(StateType::CHTL, this);
}

std::shared_ptr<BasicContext> ConfigLexer::createInitialContext() {
    // 使用标准的CHTL上下文
    return ContextFactory::createContext(ContextType::CHTL);
}

bool ConfigLexer::parseConfiguration(const std::string& text) {
    // 创建输入流
    auto stream = std::make_unique<std::istringstream>(text);
    if (!initialize(std::move(stream), "<config>")) {
        return false;
    }
    
    return parseConfigurationBlock();
}

bool ConfigLexer::parseConfigurationFromFile(const std::string& filename) {
    if (!initialize(filename)) {
        return false;
    }
    
    return parseConfigurationBlock();
}

bool ConfigLexer::parseConfigurationBlock() {
    configItems_.clear();
    arrayConfigItems_.clear();
    parseState_ = ParseState::LOOKING_FOR_CONFIG;
    
    Token token;
    while (hasMoreTokens()) {
        token = getNextToken();
        
        switch (parseState_) {
            case ParseState::LOOKING_FOR_CONFIG:
                if (token.getType() == TokenType::CONFIGURATION) {
                    parseState_ = ParseState::IN_CONFIG_BLOCK;
                }
                break;
                
            case ParseState::IN_CONFIG_BLOCK:
                if (token.getType() == TokenType::LEFT_BRACE) {
                    parseState_ = ParseState::PARSING_KEY;
                } else if (token.getType() == TokenType::RIGHT_BRACE) {
                    // 配置块结束
                    return true;
                }
                break;
                
            case ParseState::PARSING_KEY:
                if (token.getType() == TokenType::IDENTIFIER) {
                    currentKey_ = token.getValue();
                    if (VALID_CONFIG_KEYS.find(currentKey_) != VALID_CONFIG_KEYS.end()) {
                        parseState_ = ParseState::EXPECTING_COLON;
                    } else {
                        reportError("Invalid configuration key: " + currentKey_, 
                                  token.getLine(), token.getColumn());
                        return false;
                    }
                } else if (token.getType() == TokenType::RIGHT_BRACE) {
                    // 配置块结束
                    return true;
                }
                break;
                
            case ParseState::EXPECTING_COLON:
                if (token.getType() == TokenType::COLON) {
                    if (ARRAY_CONFIG_KEYS.find(currentKey_) != ARRAY_CONFIG_KEYS.end()) {
                        parseState_ = ParseState::PARSING_ARRAY;
                        currentArray_.clear();
                    } else {
                        parseState_ = ParseState::PARSING_VALUE;
                    }
                }
                break;
                
            case ParseState::PARSING_VALUE:
                if (token.getType() == TokenType::STRING_LITERAL ||
                    token.getType() == TokenType::IDENTIFIER ||
                    token.getType() == TokenType::NUMBER) {
                    currentValue_ = token.getValue();
                    parseState_ = ParseState::EXPECTING_SEMICOLON;
                }
                break;
                
            case ParseState::PARSING_ARRAY:
                if (token.getType() == TokenType::LEFT_BRACKET) {
                    // 数组开始
                } else if (token.getType() == TokenType::RIGHT_BRACKET) {
                    // 数组结束
                    arrayConfigItems_[currentKey_] = currentArray_;
                    parseState_ = ParseState::EXPECTING_SEMICOLON;
                } else if (token.getType() == TokenType::STRING_LITERAL ||
                         token.getType() == TokenType::IDENTIFIER) {
                    currentArray_.push_back(token.getValue());
                } else if (token.getType() == TokenType::COMMA) {
                    // 继续解析下一个数组元素
                }
                break;
                
            case ParseState::EXPECTING_SEMICOLON:
                if (token.getType() == TokenType::SEMICOLON) {
                    if (!currentArray_.empty()) {
                        // 已在PARSING_ARRAY中处理
                        currentArray_.clear();
                    } else {
                        configItems_[currentKey_] = currentValue_;
                    }
                    parseState_ = ParseState::PARSING_KEY;
                }
                break;
        }
    }
    
    return true;
}

std::string ConfigLexer::getConfigValue(const std::string& key) const {
    auto it = configItems_.find(key);
    return it != configItems_.end() ? it->second : "";
}

std::vector<std::string> ConfigLexer::getConfigArray(const std::string& key) const {
    auto it = arrayConfigItems_.find(key);
    return it != arrayConfigItems_.end() ? it->second : std::vector<std::string>();
}

bool ConfigLexer::hasConfig(const std::string& key) const {
    return configItems_.find(key) != configItems_.end() ||
           arrayConfigItems_.find(key) != arrayConfigItems_.end();
}

void ConfigLexer::applyKeywordAliases() {
    // 获取关键字别名配置
    std::unordered_map<std::string, std::string> aliases;
    
    // 处理单个别名
    for (const auto& [key, value] : configItems_) {
        if (key.find("keyword_") == 0) {
            std::string keyword = key.substr(8); // 移除 "keyword_" 前缀
            aliases[value] = keyword;
        }
    }
    
    // 处理数组别名
    auto keywordAliases = getConfigArray("keyword_aliases");
    for (size_t i = 0; i + 1 < keywordAliases.size(); i += 2) {
        aliases[keywordAliases[i]] = keywordAliases[i + 1];
    }
    
    // 应用到上下文
    if (auto chtlContext = std::dynamic_pointer_cast<ChtlContext>(context_)) {
        chtlContext->setKeywordAliases(aliases);
    }
}

// 验证助手方法
bool ConfigLexer::validateConfigKey(const std::string& key) const {
    return VALID_CONFIG_KEYS.find(key) != VALID_CONFIG_KEYS.end();
}

bool ConfigLexer::validateArrayValue(const std::string& key, const std::vector<std::string>& values) const {
    if (key == "keyword_aliases") {
        // 关键字别名必须成对出现
        return values.size() % 2 == 0;
    }
    return true;
}

} // namespace chtl