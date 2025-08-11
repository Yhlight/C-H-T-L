#ifndef CHTL_CONFIG_APPLIER_H
#define CHTL_CONFIG_APPLIER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include "Node/Config.h"
#include "Generator/ConfigManager.h"

namespace chtl {

// 前向声明
class Generator;
class Node;
class ChtlContext;

/**
 * 配置应用器 - 负责将配置应用到生成过程中
 */
class ConfigApplier {
public:
    // 配置类型
    enum class ConfigType {
        COMPILER,      // 编译器级别配置
        GENERATOR,     // 生成器级别配置
        RUNTIME,       // 运行时配置
        OPTIMIZATION   // 优化配置
    };
    
    ConfigApplier();
    ~ConfigApplier();
    
    /**
     * 初始化配置应用器
     * @param configManager 配置管理器
     */
    void initialize(std::shared_ptr<ConfigManager> configManager);
    
    /**
     * 应用配置到生成器
     * @param generator 目标生成器
     * @param config 配置节点
     */
    void applyToGenerator(Generator* generator, const std::shared_ptr<Config>& config);
    
    /**
     * 应用配置到上下文
     * @param context 编译上下文
     * @param config 配置节点
     */
    void applyToContext(ChtlContext* context, const std::shared_ptr<Config>& config);
    
    /**
     * 处理编译器级别的配置
     */
    void applyCompilerConfig(const std::shared_ptr<Config>& config);
    
    /**
     * 处理优化配置
     */
    void applyOptimizationConfig(const std::shared_ptr<Config>& config);
    
    /**
     * 注册自定义配置处理器
     * @param name 配置名称
     * @param handler 处理函数
     */
    void registerConfigHandler(const std::string& name, 
                              std::function<void(const ConfigValue&)> handler);
    
    /**
     * 获取配置的生效范围
     * @param configName 配置名称
     * @return 配置类型
     */
    ConfigType getConfigScope(const std::string& configName) const;
    
private:
    std::shared_ptr<ConfigManager> configManager_;
    
    // 配置处理器映射
    std::unordered_map<std::string, std::function<void(const ConfigValue&)>> configHandlers_;
    
    // 配置范围映射
    std::unordered_map<std::string, ConfigType> configScopes_;
    
    // 当前应用的配置
    std::unordered_map<std::string, ConfigValue> activeConfigs_;
    
    // 初始化默认配置处理器
    void initializeDefaultHandlers();
    
    // 应用单个配置项
    void applyConfigItem(const std::string& key, const ConfigValue& value);
    
    // 验证配置值
    bool validateConfigValue(const std::string& key, const ConfigValue& value);
    
    // 配置冲突检查
    bool checkConfigConflicts(const std::string& key, const ConfigValue& value);
};

} // namespace chtl

#endif // CHTL_CONFIG_APPLIER_H