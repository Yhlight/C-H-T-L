#include "Lexer/ConfigLexer.h"
#include "state/StateFactory.h"
#include "context/ContextFactory.h"
#include "context/ChtlContext.h"
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
    
    configItems_.clear();
    arrayConfigItems_.clear();
    parseState_ = ParseState::INITIAL;
    
    Token token;
    while (hasMoreTokens()) {
        token = getNextToken();
        
        switch (parseState_) {
            case ParseState::INITIAL:
                if (token.getType() == TokenType::CONFIGURATION) {
                    parseState_ = ParseState::IN_CONFIGURATION;
                }
                break;
                
            case ParseState::IN_CONFIGURATION:
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
                        if (token.getType() == TokenType::COLON) {
                            if (ARRAY_CONFIG_KEYS.find(currentKey_) != ARRAY_CONFIG_KEYS.end()) {
                                parseState_ = ParseState::PARSING_ARRAY;
                                currentArray_.clear();
                            } else {
                                parseState_ = ParseState::PARSING_VALUE;
                            }
                        }
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
                
            case ParseState::PARSING_VALUE:
                if (token.getType() == TokenType::STRING_LITERAL ||
                    token.getType() == TokenType::IDENTIFIER ||
                    token.getType() == TokenType::NUMBER) {
                    currentValue_ = token.getValue();
                    configItems_[currentKey_] = currentValue_;
                    parseState_ = ParseState::PARSING_KEY;
                }
                break;
                
            case ParseState::PARSING_ARRAY:
                if (token.getType() == TokenType::LEFT_BRACKET) {
                    // 数组开始
                } else if (token.getType() == TokenType::RIGHT_BRACKET) {
                    // 数组结束
                    arrayConfigItems_[currentKey_] = currentArray_;
                    parseState_ = ParseState::PARSING_KEY;
                } else if (token.getType() == TokenType::STRING_LITERAL ||
                         token.getType() == TokenType::IDENTIFIER) {
                    currentArray_.push_back(token.getValue());
                } else if (token.getType() == TokenType::COMMA) {
                    // 继续解析下一个数组元素
                }
                break;
                
            default:
                break;
        }
    }
    
    return true;
}

bool ConfigLexer::parseConfigurationFile(const std::string& filename) {
    if (!initialize(filename)) {
        return false;
    }
    
    return parseConfiguration("");
}

std::string ConfigLexer::getConfigValue(const std::string& key, const std::string& defaultValue) const {
    auto it = configItems_.find(key);
    return it != configItems_.end() ? it->second : defaultValue;
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
    std::unordered_map<std::string, std::vector<std::string>> keywordAliasMap;
    
    // 处理单个别名
    for (const auto& [key, value] : configItems_) {
        if (key.find("keyword_") == 0) {
            std::string keyword = key.substr(8); // 移除 "keyword_" 前缀
            keywordAliasMap[keyword].push_back(value);
        }
    }
    
    // 处理数组别名
    auto keywordAliases = getConfigArray("keyword_aliases");
    for (size_t i = 0; i + 1 < keywordAliases.size(); i += 2) {
        keywordAliasMap[keywordAliases[i]].push_back(keywordAliases[i + 1]);
    }
    
    // 应用到上下文
    if (auto chtlContext = std::dynamic_pointer_cast<ChtlContext>(context_)) {
        for (const auto& [keyword, aliases] : keywordAliasMap) {
            chtlContext->setKeywordAliases(keyword, aliases);
        }
    }
}



} // namespace chtl