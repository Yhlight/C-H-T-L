#include "ConfigurationSystem.h"
#include "ConfigurationParser.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <iostream>

namespace chtl {
namespace config {

// NameGroup 默认构造函数
NameGroup::NameGroup() {
    // 设置默认值
    customStyle = {"@Style", "@style", "@CSS", "@Css", "@css"};
    customElement = "@Element";
    customVar = "@Var";
    
    templateStyle = "@Style";
    templateElement = "@Element";
    templateVar = "@Var";
    
    originHtml = "@Html";
    originStyle = "@Style";
    originJavaScript = "@JavaScript";
    
    importHtml = "@Html";
    importStyle = "@Style";
    importJavaScript = "@JavaScript";
    importChtl = "@Chtl";
    importCJmod = "@CJmod";
    
    keywordInherit = "inherit";
    keywordDelete = "delete";
    keywordInsert = "insert";
    keywordAfter = "after";
    keywordBefore = "before";
    keywordReplace = "replace";
    keywordAtTop = "at top";
    keywordAtBottom = "at bottom";
    keywordFrom = "from";
    keywordAs = "as";
    keywordExcept = "except";
    
    keywordText = "text";
    keywordStyle = "style";
    keywordScript = "script";
    
    keywordCustom = "[Custom]";
    keywordTemplate = "[Template]";
    keywordOrigin = "[Origin]";
    keywordImport = "[Import]";
    keywordNamespace = "[Namespace]";
}

void NameGroup::initialize(const std::unordered_map<std::string, ConfigValue>& items) {
    // 辅助函数：获取字符串值
    auto getString = [&items](const std::string& key, const std::string& defaultValue) -> std::string {
        auto it = items.find(key);
        if (it != items.end() && std::holds_alternative<std::string>(it->second)) {
            return std::get<std::string>(it->second);
        }
        return defaultValue;
    };
    
    // 辅助函数：获取字符串数组值
    auto getStringArray = [&items](const std::string& key, const std::vector<std::string>& defaultValue) -> std::vector<std::string> {
        auto it = items.find(key);
        if (it != items.end() && std::holds_alternative<std::vector<std::string>>(it->second)) {
            return std::get<std::vector<std::string>>(it->second);
        }
        return defaultValue;
    };
    
    // 初始化各个字段
    customStyle = getStringArray("CUSTOM_STYLE", customStyle);
    customElement = getString("CUSTOM_ELEMENT", customElement);
    customVar = getString("CUSTOM_VAR", customVar);
    
    templateStyle = getString("TEMPLATE_STYLE", templateStyle);
    templateElement = getString("TEMPLATE_ELEMENT", templateElement);
    templateVar = getString("TEMPLATE_VAR", templateVar);
    
    originHtml = getString("ORIGIN_HTML", originHtml);
    originStyle = getString("ORIGIN_STYLE", originStyle);
    originJavaScript = getString("ORIGIN_JAVASCRIPT", originJavaScript);
    
    importHtml = getString("IMPORT_HTML", importHtml);
    importStyle = getString("IMPORT_STYLE", importStyle);
    importJavaScript = getString("IMPORT_JAVASCRIPT", importJavaScript);
    importChtl = getString("IMPORT_CHTL", importChtl);
    importCJmod = getString("IMPORT_CJMOD", importCJmod);  // 注意原配置中有拼写错误IMPOER_CRMOD
    
    keywordInherit = getString("KEYWORD_INHERIT", keywordInherit);
    keywordDelete = getString("KEYWORD_DELETE", keywordDelete);
    keywordInsert = getString("KEYWORD_INSERT", keywordInsert);
    keywordAfter = getString("KEYWORD_AFTER", keywordAfter);
    keywordBefore = getString("KEYWORD_BEFORE", keywordBefore);
    keywordReplace = getString("KEYWORD_REPLACE", keywordReplace);
    keywordAtTop = getString("KEYWORD_ATTOP", keywordAtTop);
    keywordAtBottom = getString("KEYWORD_ATBOTTOM", keywordAtBottom);
    keywordFrom = getString("KEYWORD_FROM", keywordFrom);
    keywordAs = getString("KEYWORD_AS", keywordAs);
    keywordExcept = getString("KEYWORD_EXCEPT", keywordExcept);
    
    keywordText = getString("KEYWORD_TEXT", keywordText);
    keywordStyle = getString("KEYWORD_STYLE", keywordStyle);
    keywordScript = getString("KEYWORD_SCRIPT", keywordScript);
    
    keywordCustom = getString("KEYWORD_CUSTOM", keywordCustom);
    keywordTemplate = getString("KEYWORD_TEMPLATE", keywordTemplate);
    keywordOrigin = getString("KEYWORD_ORIGIN", keywordOrigin);
    keywordImport = getString("KEYWORD_IMPORT", keywordImport);
    keywordNamespace = getString("KEYWORD_NAMESPACE", keywordNamespace);
    
    // 获取选项数量限制
    auto it = items.find("OPTION_COUNT");
    if (it != items.end() && std::holds_alternative<int>(it->second)) {
        optionCount = std::get<int>(it->second);
    }
}

bool NameGroup::validate() const {
    // 验证组选项数量
    if (customStyle.size() > static_cast<size_t>(optionCount)) {
        std::cerr << "Warning: CUSTOM_STYLE has " << customStyle.size() 
                  << " options, exceeding OPTION_COUNT limit of " << optionCount << std::endl;
    }
    
    // 验证必需字段不为空
    if (customElement.empty() || customVar.empty() ||
        templateStyle.empty() || templateElement.empty() || templateVar.empty()) {
        return false;
    }
    
    return true;
}

std::vector<std::string> NameGroup::getAllKeywordVariants(const std::string& keywordType) const {
    if (keywordType == "CUSTOM_STYLE") {
        return customStyle;
    } else if (keywordType == "CUSTOM_ELEMENT") {
        return {customElement};
    } else if (keywordType == "CUSTOM_VAR") {
        return {customVar};
    }
    // ... 其他类型类似处理
    
    return {};
}

// ConfigurationSystem 实现

ConfigurationSystem& ConfigurationSystem::getInstance() {
    static ConfigurationSystem instance;
    return instance;
}

ConfigurationSystem::ConfigurationSystem() {
    reset();
}

void ConfigurationSystem::reset() {
    configItems.clear();
    indexInitialCount = 0;
    disableNameGroup = true;
    debugMode = false;
    nameGroup = NameGroup();
}

bool ConfigurationSystem::loadConfiguration(const std::string& configContent) {
    reset();
    
    FlexibleConfigurationParser parser;
    auto result = parser.parseString(configContent);
    
    if (!result.success) {
        return false;
    }
    
    // 应用全局配置
    for (const auto& [key, value] : result.globalConfig) {
        configItems[key] = value;
    }
    
    // 处理Name组
    auto nameIt = result.namedGroups.find("Name");
    if (nameIt != result.namedGroups.end()) {
        nameGroup.initialize(nameIt->second);
    }
    
    // 加载动态关键字系统
    DynamicKeywordSystem dynamicKeywords;
    dynamicKeywords.loadFromConfig(result);
    
    return true;
}

bool ConfigurationSystem::loadConfigurationFromFile(const std::string& filePath) {
    FlexibleConfigurationParser parser;
    auto result = parser.parseFile(filePath);
    
    if (!result.success) {
        return false;
    }
    
    reset();
    
    // 应用全局配置
    for (const auto& [key, value] : result.globalConfig) {
        configItems[key] = value;
    }
    
    // 处理Name组
    auto nameIt = result.namedGroups.find("Name");
    if (nameIt != result.namedGroups.end()) {
        nameGroup.initialize(nameIt->second);
    }
    
    // 加载动态关键字系统
    DynamicKeywordSystem dynamicKeywords;
    dynamicKeywords.loadFromConfig(result);
    
    return true;
}

bool ConfigurationSystem::parseConfiguration(const std::string& content) {
    // 简化的配置解析器
    // 在实际实现中，应该使用ANTLR解析器来解析配置块
    
    // 提取Configuration块
    std::regex configBlockRegex(R"(\[Configuration\]\s*\{([^}]*(?:\{[^}]*\}[^}]*)*)\})");
    std::smatch match;
    
    if (!std::regex_search(content, match, configBlockRegex)) {
        return false;
    }
    
    std::string configBlock = match[1];
    
    // 解析简单的键值对
    std::regex kvRegex(R"((\w+)\s*=\s*([^;]+);)");
    auto kvBegin = std::sregex_iterator(configBlock.begin(), configBlock.end(), kvRegex);
    auto kvEnd = std::sregex_iterator();
    
    for (auto it = kvBegin; it != kvEnd; ++it) {
        std::string key = (*it)[1];
        std::string value = (*it)[2];
        
        // 去除首尾空白
        value.erase(0, value.find_first_not_of(" \t\n\r"));
        value.erase(value.find_last_not_of(" \t\n\r") + 1);
        
        // 特殊处理核心配置项
        if (key == "INDEX_INITIAL_COUNT") {
            indexInitialCount = std::stoi(value);
        } else if (key == "DISABLE_NAME_GROUP") {
            disableNameGroup = (value == "true");
        } else if (key == "DEBUG_MODE") {
            debugMode = (value == "true");
        } else {
            configItems[key] = parseValue(value);
        }
    }
    
    // 如果NAME组未被禁用，解析NAME组
    if (!disableNameGroup) {
        std::regex nameBlockRegex(R"(\[Name\]\s*\{([^}]*(?:\[[^\]]*\][^}]*)*)\})");
        if (std::regex_search(configBlock, match, nameBlockRegex)) {
            parseNameGroup(match[1]);
        }
    }
    
    return true;
}

bool ConfigurationSystem::parseNameGroup(const std::string& nameGroupContent) {
    std::unordered_map<std::string, ConfigValue> nameItems;
    
    // 解析Name组中的配置项
    std::regex kvRegex(R"((\w+)\s*=\s*([^;]+);)");
    auto kvBegin = std::sregex_iterator(nameGroupContent.begin(), nameGroupContent.end(), kvRegex);
    auto kvEnd = std::sregex_iterator();
    
    for (auto it = kvBegin; it != kvEnd; ++it) {
        std::string key = (*it)[1];
        std::string value = (*it)[2];
        
        // 去除首尾空白
        value.erase(0, value.find_first_not_of(" \t\n\r"));
        value.erase(value.find_last_not_of(" \t\n\r") + 1);
        
        nameItems[key] = parseValue(value);
    }
    
    // 初始化NameGroup
    nameGroup.initialize(nameItems);
    
    return nameGroup.validate();
}

ConfigValue ConfigurationSystem::parseValue(const std::string& value) {
    // 检查是否是数组
    if (value.front() == '[' && value.back() == ']') {
        return parseArrayValue(value);
    }
    
    // 检查是否是布尔值
    if (value == "true") return true;
    if (value == "false") return false;
    
    // 检查是否是数字
    try {
        size_t pos;
        int intValue = std::stoi(value, &pos);
        if (pos == value.length()) {
            return intValue;
        }
    } catch (...) {}
    
    // 否则作为字符串处理
    return value;
}

std::vector<std::string> ConfigurationSystem::parseArrayValue(const std::string& value) {
    std::vector<std::string> result;
    
    // 去除方括号
    std::string content = value.substr(1, value.length() - 2);
    
    // 按逗号分割
    std::regex itemRegex(R"(\s*([^,]+)\s*(?:,|$))");
    auto itemBegin = std::sregex_iterator(content.begin(), content.end(), itemRegex);
    auto itemEnd = std::sregex_iterator();
    
    for (auto it = itemBegin; it != itemEnd; ++it) {
        std::string item = (*it)[1];
        // 去除首尾空白
        item.erase(0, item.find_first_not_of(" \t\n\r"));
        item.erase(item.find_last_not_of(" \t\n\r") + 1);
        
        if (!item.empty()) {
            result.push_back(item);
        }
    }
    
    return result;
}

bool ConfigurationSystem::isKeyword(const std::string& token, const std::string& keywordType) const {
    if (disableNameGroup) {
        // 使用默认关键字
        return token == getCanonicalKeyword(keywordType);
    }
    
    // 检查自定义关键字
    auto variants = nameGroup.getAllKeywordVariants(keywordType);
    return std::find(variants.begin(), variants.end(), token) != variants.end();
}

std::string ConfigurationSystem::getCanonicalKeyword(const std::string& keywordType) const {
    if (disableNameGroup) {
        // 返回默认关键字
        if (keywordType == "CUSTOM_STYLE") return "@Style";
        if (keywordType == "CUSTOM_ELEMENT") return "@Element";
        if (keywordType == "CUSTOM_VAR") return "@Var";
        if (keywordType == "TEMPLATE_STYLE") return "@Style";
        if (keywordType == "TEMPLATE_ELEMENT") return "@Element";
        if (keywordType == "TEMPLATE_VAR") return "@Var";
        // ... 其他类型
    }
    
    // 使用配置的关键字
    if (keywordType == "CUSTOM_STYLE" && !nameGroup.customStyle.empty()) {
        return nameGroup.customStyle[0];
    }
    if (keywordType == "CUSTOM_ELEMENT") return nameGroup.customElement;
    if (keywordType == "CUSTOM_VAR") return nameGroup.customVar;
    // ... 其他类型
    
    return "";
}

bool ConfigurationSystem::validateConfiguration() const {
    if (!disableNameGroup) {
        return nameGroup.validate();
    }
    return true;
}

std::string ConfigurationSystem::exportConfiguration() const {
    std::stringstream ss;
    
    ss << "[Configuration]\n{\n";
    ss << "    INDEX_INITIAL_COUNT = " << indexInitialCount << ";\n";
    ss << "    DISABLE_NAME_GROUP = " << (disableNameGroup ? "true" : "false") << ";\n";
    ss << "    DEBUG_MODE = " << (debugMode ? "true" : "false") << ";\n";
    
    if (!disableNameGroup) {
        ss << "\n    [Name]\n    {\n";
        
        // 导出customStyle数组
        ss << "        CUSTOM_STYLE = [";
        for (size_t i = 0; i < nameGroup.customStyle.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << nameGroup.customStyle[i];
        }
        ss << "];\n";
        
        // 导出其他字段
        ss << "        CUSTOM_ELEMENT = " << nameGroup.customElement << ";\n";
        ss << "        CUSTOM_VAR = " << nameGroup.customVar << ";\n";
        // ... 其他字段类似
        
        ss << "        OPTION_COUNT = " << nameGroup.optionCount << ";\n";
        ss << "    }\n";
    }
    
    ss << "}\n";
    
    return ss.str();
}

} // namespace config
} // namespace chtl