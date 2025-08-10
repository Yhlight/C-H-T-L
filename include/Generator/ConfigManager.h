#ifndef CHTL_CONFIG_MANAGER_H
#define CHTL_CONFIG_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Node/Config.h"

namespace chtl {

class ConfigManager {
private:
    // 关键字别名映射
    std::unordered_map<std::string, std::vector<std::string>> keywordAliases_;
    
    // 其他配置项
    bool debugMode_ = false;
    int indexInitialCount_ = 0;
    bool disableNameGroup_ = false;
    int optionCount_ = 3;
    
    // 默认映射
    void initializeDefaults();
    
public:
    ConfigManager();
    
    // 从Config节点加载配置
    void loadFromConfig(const std::shared_ptr<Config>& config);
    
    // 获取关键字的所有别名
    std::vector<std::string> getKeywordAliases(const std::string& keyword) const;
    
    // 检查是否是某个关键字的别名
    bool isKeywordAlias(const std::string& text, const std::string& keyword) const;
    
    // 获取配置值
    bool isDebugMode() const { return debugMode_; }
    int getIndexInitialCount() const { return indexInitialCount_; }
    bool isNameGroupDisabled() const { return disableNameGroup_; }
    int getOptionCount() const { return optionCount_; }
    
    // 设置配置值
    void setDebugMode(bool mode) { debugMode_ = mode; }
    void setIndexInitialCount(int count) { indexInitialCount_ = count; }
    void setDisableNameGroup(bool disable) { disableNameGroup_ = disable; }
    void setOptionCount(int count) { optionCount_ = count; }
    
    // 规范化关键字（将别名转换为标准形式）
    std::string normalizeKeyword(const std::string& keyword) const;
};

} // namespace chtl

#endif // CHTL_CONFIG_MANAGER_H