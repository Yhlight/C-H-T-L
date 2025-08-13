#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <variant>
#include <optional>

namespace chtl {
namespace config {

// 配置值类型
using ConfigValue = std::variant<
    bool,                           // 布尔值
    int,                           // 整数
    std::string,                   // 字符串
    std::vector<std::string>       // 字符串数组（用于组选项）
>;

// 配置项结构
struct ConfigItem {
    std::string name;
    ConfigValue value;
    std::optional<int> maxOptions;  // 对于数组类型，最大选项数
};

// 名称配置组
struct NameGroup {
    // 自定义样式关键字
    std::vector<std::string> customStyle;
    std::string customElement;
    std::string customVar;
    
    // 模板关键字
    std::string templateStyle;
    std::string templateElement;
    std::string templateVar;
    
    // 原始嵌入关键字
    std::string originHtml;
    std::string originStyle;
    std::string originJavaScript;
    
    // 导入关键字
    std::string importHtml;
    std::string importStyle;
    std::string importJavaScript;
    std::string importChtl;
    std::string importCJmod;
    
    // 操作关键字
    std::string keywordInherit;
    std::string keywordDelete;
    std::string keywordInsert;
    std::string keywordAfter;
    std::string keywordBefore;
    std::string keywordReplace;
    std::string keywordAtTop;
    std::string keywordAtBottom;
    std::string keywordFrom;
    std::string keywordAs;
    std::string keywordExcept;
    
    // 节点关键字
    std::string keywordText;
    std::string keywordStyle;
    std::string keywordScript;
    
    // 声明关键字
    std::string keywordCustom;
    std::string keywordTemplate;
    std::string keywordOrigin;
    std::string keywordImport;
    std::string keywordNamespace;
    
    // 组选项数量限制
    int optionCount = 3;
    
    // 默认构造函数，设置默认值
    NameGroup();
    
    // 从配置项初始化
    void initialize(const std::unordered_map<std::string, ConfigValue>& items);
    
    // 验证配置
    bool validate() const;
    
    // 获取所有可能的关键字变体
    std::vector<std::string> getAllKeywordVariants(const std::string& keywordType) const;
};

// 配置系统主类
class ConfigurationSystem {
public:
    // 单例模式
    static ConfigurationSystem& getInstance();
    
    // 禁用拷贝和移动
    ConfigurationSystem(const ConfigurationSystem&) = delete;
    ConfigurationSystem& operator=(const ConfigurationSystem&) = delete;
    ConfigurationSystem(ConfigurationSystem&&) = delete;
    ConfigurationSystem& operator=(ConfigurationSystem&&) = delete;
    
    // 加载配置
    bool loadConfiguration(const std::string& configContent);
    bool loadConfigurationFromFile(const std::string& filePath);
    
    // 获取配置值
    template<typename T>
    T getConfig(const std::string& key, const T& defaultValue = T{}) const;
    
    // 特殊获取器
    int getIndexInitialCount() const { return indexInitialCount; }
    bool isNameGroupDisabled() const { return disableNameGroup; }
    bool isDebugMode() const { return debugMode; }
    const NameGroup& getNameGroup() const { return nameGroup; }
    
    // 检查关键字是否匹配
    bool isKeyword(const std::string& token, const std::string& keywordType) const;
    
    // 获取关键字的规范形式
    std::string getCanonicalKeyword(const std::string& keywordType) const;
    
    // 重置为默认配置
    void reset();
    
    // 验证当前配置
    bool validateConfiguration() const;
    
    // 导出配置
    std::string exportConfiguration() const;
    
private:
    ConfigurationSystem();
    ~ConfigurationSystem() = default;
    
    // 配置值存储
    std::unordered_map<std::string, ConfigValue> configItems;
    
    // 核心配置项
    int indexInitialCount = 0;
    bool disableNameGroup = true;
    bool debugMode = false;
    
    // 名称配置组
    NameGroup nameGroup;
    
    // 解析配置内容
    bool parseConfiguration(const std::string& content);
    
    // 解析Name组
    bool parseNameGroup(const std::string& nameGroupContent);
    
    // 辅助函数
    ConfigValue parseValue(const std::string& value);
    std::vector<std::string> parseArrayValue(const std::string& value);
};

// 模板特化实现
template<>
inline bool ConfigurationSystem::getConfig<bool>(const std::string& key, const bool& defaultValue) const {
    auto it = configItems.find(key);
    if (it != configItems.end() && std::holds_alternative<bool>(it->second)) {
        return std::get<bool>(it->second);
    }
    return defaultValue;
}

template<>
inline int ConfigurationSystem::getConfig<int>(const std::string& key, const int& defaultValue) const {
    auto it = configItems.find(key);
    if (it != configItems.end() && std::holds_alternative<int>(it->second)) {
        return std::get<int>(it->second);
    }
    return defaultValue;
}

template<>
inline std::string ConfigurationSystem::getConfig<std::string>(const std::string& key, const std::string& defaultValue) const {
    auto it = configItems.find(key);
    if (it != configItems.end() && std::holds_alternative<std::string>(it->second)) {
        return std::get<std::string>(it->second);
    }
    return defaultValue;
}

template<>
inline std::vector<std::string> ConfigurationSystem::getConfig<std::vector<std::string>>(
    const std::string& key, const std::vector<std::string>& defaultValue) const {
    auto it = configItems.find(key);
    if (it != configItems.end() && std::holds_alternative<std::vector<std::string>>(it->second)) {
        return std::get<std::vector<std::string>>(it->second);
    }
    return defaultValue;
}

} // namespace config
} // namespace chtl