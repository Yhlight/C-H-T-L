#include "Generator/ConfigManager.h"
#include <algorithm>

namespace chtl {

ConfigManager::ConfigManager() {
    initializeDefaults();
}

void ConfigManager::initializeDefaults() {
    // 默认别名映射
    keywordAliases_["CUSTOM_STYLE"] = {"@Style", "@style", "@CSS", "@Css", "@css"};
    keywordAliases_["CUSTOM_ELEMENT"] = {"@Element"};
    keywordAliases_["CUSTOM_VAR"] = {"@Var"};
    keywordAliases_["TEMPLATE_STYLE"] = {"@Style"};
    keywordAliases_["TEMPLATE_ELEMENT"] = {"@Element"};
    keywordAliases_["TEMPLATE_VAR"] = {"@Var"};
    keywordAliases_["ORIGIN_HTML"] = {"@Html"};
    keywordAliases_["ORIGIN_STYLE"] = {"@Style"};
    keywordAliases_["ORIGIN_JAVASCRIPT"] = {"@JavaScript"};
    keywordAliases_["KEYWORD_INHERIT"] = {"inherit"};
    keywordAliases_["KEYWORD_DELETE"] = {"delete"};
    keywordAliases_["KEYWORD_INSERT"] = {"insert"};
    keywordAliases_["KEYWORD_AFTER"] = {"after"};
    keywordAliases_["KEYWORD_BEFORE"] = {"before"};
    keywordAliases_["KEYWORD_REPLACE"] = {"replace"};
    keywordAliases_["KEYWORD_ATTOP"] = {"at top"};
    keywordAliases_["KEYWORD_ATBOTTOM"] = {"at bottom"};
    keywordAliases_["KEYWORD_FROM"] = {"from"};
    keywordAliases_["KEYWORD_AS"] = {"as"};
    keywordAliases_["KEYWORD_EXCEPT"] = {"except"};
    keywordAliases_["KEYWORD_TEXT"] = {"text"};
    keywordAliases_["KEYWORD_STYLE"] = {"style"};
    keywordAliases_["KEYWORD_SCRIPT"] = {"script"};
    keywordAliases_["KEYWORD_CUSTOM"] = {"[Custom]"};
    keywordAliases_["KEYWORD_TEMPLATE"] = {"[Template]"};
    keywordAliases_["KEYWORD_ORIGIN"] = {"[Origin]"};
    keywordAliases_["KEYWORD_IMPORT"] = {"[Import]"};
    keywordAliases_["KEYWORD_NAMESPACE"] = {"[Namespace]"};
}

void ConfigManager::loadFromConfig(const std::shared_ptr<Config>& config) {
    if (!config) return;
    
    // 加载基本配置项
    if (auto value = config->getConfigItem("DEBUG_MODE")) {
        if (std::holds_alternative<std::string>(*value)) {
            std::string val = std::get<std::string>(*value);
            debugMode_ = (val == "true" || val == "1");
        }
    }
    
    if (auto value = config->getConfigItem("INDEX_INITIAL_COUNT")) {
        if (std::holds_alternative<std::string>(*value)) {
            indexInitialCount_ = std::stoi(std::get<std::string>(*value));
        }
    }
    
    if (auto value = config->getConfigItem("DISABLE_NAME_GROUP")) {
        if (std::holds_alternative<std::string>(*value)) {
            std::string val = std::get<std::string>(*value);
            disableNameGroup_ = (val == "true" || val == "1");
        }
    }
    
    // 如果Name组未被禁用，加载自定义关键字别名
    if (!disableNameGroup_) {
        // 处理Name.开头的配置项
        for (const auto& [key, value] : config->getConfigItems()) {
            if (key.substr(0, 5) == "Name.") {
                std::string keywordName = key.substr(5);
                
                if (std::holds_alternative<std::vector<std::string>>(value)) {
                    // 数组值，直接使用
                    keywordAliases_[keywordName] = std::get<std::vector<std::string>>(value);
                } else if (std::holds_alternative<std::string>(value)) {
                    // 单个值，转换为数组
                    keywordAliases_[keywordName] = {std::get<std::string>(value)};
                }
            }
        }
        
        // 处理OPTION_COUNT
        if (auto value = config->getConfigItem("Name.OPTION_COUNT")) {
            if (std::holds_alternative<std::string>(*value)) {
                optionCount_ = std::stoi(std::get<std::string>(*value));
            }
        }
    }
}

std::vector<std::string> ConfigManager::getKeywordAliases(const std::string& keyword) const {
    auto it = keywordAliases_.find(keyword);
    if (it != keywordAliases_.end()) {
        // 限制返回的别名数量
        std::vector<std::string> limited = it->second;
        if (limited.size() > static_cast<size_t>(optionCount_)) {
            limited.resize(optionCount_);
        }
        return limited;
    }
    return {};
}

bool ConfigManager::isKeywordAlias(const std::string& text, const std::string& keyword) const {
    auto aliases = getKeywordAliases(keyword);
    return std::find(aliases.begin(), aliases.end(), text) != aliases.end();
}

std::string ConfigManager::normalizeKeyword(const std::string& keyword) const {
    // 检查是否是某个关键字的别名
    for (const auto& [key, aliases] : keywordAliases_) {
        if (std::find(aliases.begin(), aliases.end(), keyword) != aliases.end()) {
            // 返回标准形式（第一个别名）
            return aliases.empty() ? keyword : aliases[0];
        }
    }
    return keyword;
}

} // namespace chtl