#include "Generator/ConfigApplier.h"
#include "Generator/Generator.h"
#include "Context/ChtlContext.h"
#include <iostream>
#include <sstream>

namespace chtl {

ConfigApplier::ConfigApplier() {
    initializeDefaultHandlers();
}

ConfigApplier::~ConfigApplier() {}

void ConfigApplier::initialize(std::shared_ptr<ConfigManager> configManager) {
    configManager_ = configManager;
}

void ConfigApplier::initializeDefaultHandlers() {
    // 编译器级别配置
    configScopes_["OUTPUT_FORMAT"] = ConfigType::COMPILER;
    configScopes_["MINIFY_OUTPUT"] = ConfigType::COMPILER;
    configScopes_["GENERATE_SOURCE_MAP"] = ConfigType::COMPILER;
    configScopes_["STRICT_MODE"] = ConfigType::COMPILER;
    configScopes_["ERROR_LIMIT"] = ConfigType::COMPILER;
    
    // 生成器级别配置
    configScopes_["INDENT_SIZE"] = ConfigType::GENERATOR;
    configScopes_["USE_TABS"] = ConfigType::GENERATOR;
    configScopes_["LINE_ENDING"] = ConfigType::GENERATOR;
    configScopes_["QUOTE_STYLE"] = ConfigType::GENERATOR;
    configScopes_["ATTRIBUTE_QUOTES"] = ConfigType::GENERATOR;
    configScopes_["SELF_CLOSING_TAGS"] = ConfigType::GENERATOR;
    configScopes_["CSS_PREFIX"] = ConfigType::GENERATOR;
    configScopes_["JS_MODULE_TYPE"] = ConfigType::GENERATOR;
    
    // 运行时配置
    configScopes_["ENABLE_HOT_RELOAD"] = ConfigType::RUNTIME;
    configScopes_["DEBUG_OUTPUT"] = ConfigType::RUNTIME;
    configScopes_["PERFORMANCE_MONITORING"] = ConfigType::RUNTIME;
    configScopes_["LAZY_LOADING"] = ConfigType::RUNTIME;
    
    // 优化配置
    configScopes_["OPTIMIZE_CSS"] = ConfigType::OPTIMIZATION;
    configScopes_["OPTIMIZE_JS"] = ConfigType::OPTIMIZATION;
    configScopes_["REMOVE_COMMENTS"] = ConfigType::OPTIMIZATION;
    configScopes_["MERGE_SELECTORS"] = ConfigType::OPTIMIZATION;
    configScopes_["INLINE_CRITICAL_CSS"] = ConfigType::OPTIMIZATION;
    configScopes_["TREE_SHAKING"] = ConfigType::OPTIMIZATION;
    configScopes_["DEAD_CODE_ELIMINATION"] = ConfigType::OPTIMIZATION;
    
    // 注册默认处理器
    registerConfigHandler("OUTPUT_FORMAT", [this](const ConfigValue& value) {
        if (std::holds_alternative<std::string>(value)) {
            std::string format = std::get<std::string>(value);
            // 支持的格式：html, vue, react, web-component
            activeConfigs_["OUTPUT_FORMAT"] = format;
        }
    });
    
    registerConfigHandler("MINIFY_OUTPUT", [this](const ConfigValue& value) {
        if (std::holds_alternative<std::string>(value)) {
            std::string val = std::get<std::string>(value);
            bool minify = (val == "true" || val == "1");
            activeConfigs_["MINIFY_OUTPUT"] = minify ? "true" : "false";
        }
    });
    
    registerConfigHandler("INDENT_SIZE", [this](const ConfigValue& value) {
        if (std::holds_alternative<std::string>(value)) {
            try {
                int size = std::stoi(std::get<std::string>(value));
                if (size >= 0 && size <= 8) {
                    activeConfigs_["INDENT_SIZE"] = std::to_string(size);
                }
            } catch (...) {
                // 忽略无效值
            }
        }
    });
    
    registerConfigHandler("CSS_PREFIX", [this](const ConfigValue& value) {
        if (std::holds_alternative<std::vector<std::string>>(value)) {
            // 支持多个前缀
            activeConfigs_["CSS_PREFIX"] = value;
        } else if (std::holds_alternative<std::string>(value)) {
            // 单个前缀转换为数组
            activeConfigs_["CSS_PREFIX"] = std::vector<std::string>{std::get<std::string>(value)};
        }
    });
    
    registerConfigHandler("OPTIMIZE_CSS", [this](const ConfigValue& value) {
        if (std::holds_alternative<std::string>(value)) {
            std::string level = std::get<std::string>(value);
            // 支持的级别：none, basic, advanced
            if (level == "none" || level == "basic" || level == "advanced") {
                activeConfigs_["OPTIMIZE_CSS"] = level;
            }
        }
    });
}

void ConfigApplier::applyToGenerator(Generator* generator, const std::shared_ptr<Config>& config) {
    if (!generator || !config) return;
    
    // 应用生成器相关配置
    for (const auto& [key, value] : config->getConfigItems()) {
        auto scope = getConfigScope(key);
        if (scope == ConfigType::GENERATOR || scope == ConfigType::OPTIMIZATION) {
            applyConfigItem(key, value);
            
            // 直接应用某些配置到生成器
            if (key == "INDENT_SIZE" && activeConfigs_.find("INDENT_SIZE") != activeConfigs_.end()) {
                if (std::holds_alternative<std::string>(activeConfigs_["INDENT_SIZE"])) {
                    int size = std::stoi(std::get<std::string>(activeConfigs_["INDENT_SIZE"]));
                    // generator->setIndentSize(size); // 需要在Generator基类中添加此方法
                }
            }
        }
    }
}

void ConfigApplier::applyToContext(ChtlContext* context, const std::shared_ptr<Config>& config) {
    if (!context || !config) return;
    
    // 应用编译器级别配置
    for (const auto& [key, value] : config->getConfigItems()) {
        auto scope = getConfigScope(key);
        if (scope == ConfigType::COMPILER || scope == ConfigType::RUNTIME) {
            applyConfigItem(key, value);
            
            // 应用某些配置到上下文
            if (key == "STRICT_MODE" && activeConfigs_.find("STRICT_MODE") != activeConfigs_.end()) {
                if (std::holds_alternative<std::string>(activeConfigs_["STRICT_MODE"])) {
                    bool strict = std::get<std::string>(activeConfigs_["STRICT_MODE"]) == "true";
                    context->setStrictMode(strict);
                }
            }
            
            if (key == "ERROR_LIMIT" && activeConfigs_.find("ERROR_LIMIT") != activeConfigs_.end()) {
                if (std::holds_alternative<std::string>(activeConfigs_["ERROR_LIMIT"])) {
                    try {
                        int limit = std::stoi(std::get<std::string>(activeConfigs_["ERROR_LIMIT"]));
                        context->setErrorLimit(limit);
                    } catch (...) {
                        // 忽略无效值
                    }
                }
            }
        }
    }
}

void ConfigApplier::applyCompilerConfig(const std::shared_ptr<Config>& config) {
    if (!config) return;
    
    // 应用所有编译器级别的配置
    for (const auto& [key, value] : config->getConfigItems()) {
        if (getConfigScope(key) == ConfigType::COMPILER) {
            applyConfigItem(key, value);
        }
    }
}

void ConfigApplier::applyOptimizationConfig(const std::shared_ptr<Config>& config) {
    if (!config) return;
    
    // 应用所有优化配置
    for (const auto& [key, value] : config->getConfigItems()) {
        if (getConfigScope(key) == ConfigType::OPTIMIZATION) {
            applyConfigItem(key, value);
        }
    }
}

void ConfigApplier::registerConfigHandler(const std::string& name,
                                        std::function<void(const ConfigValue&)> handler) {
    configHandlers_[name] = handler;
}

ConfigApplier::ConfigType ConfigApplier::getConfigScope(const std::string& configName) const {
    auto it = configScopes_.find(configName);
    if (it != configScopes_.end()) {
        return it->second;
    }
    
    // 默认为编译器级别
    return ConfigType::COMPILER;
}

void ConfigApplier::applyConfigItem(const std::string& key, const ConfigValue& value) {
    // 验证配置值
    if (!validateConfigValue(key, value)) {
        std::cerr << "[Config] Invalid value for " << key << std::endl;
        return;
    }
    
    // 检查冲突
    if (!checkConfigConflicts(key, value)) {
        std::cerr << "[Config] Conflict detected for " << key << std::endl;
        return;
    }
    
    // 应用配置
    auto handler = configHandlers_.find(key);
    if (handler != configHandlers_.end()) {
        handler->second(value);
    } else {
        // 没有特定处理器，直接存储
        activeConfigs_[key] = value;
    }
}

bool ConfigApplier::validateConfigValue(const std::string& key, const ConfigValue& value) {
    // 基本验证
    if (key.empty()) return false;
    
    // 特定配置的验证
    if (key == "OUTPUT_FORMAT") {
        if (std::holds_alternative<std::string>(value)) {
            std::string format = std::get<std::string>(value);
            return format == "html" || format == "vue" || format == "react" || format == "web-component";
        }
        return false;
    }
    
    if (key == "LINE_ENDING") {
        if (std::holds_alternative<std::string>(value)) {
            std::string ending = std::get<std::string>(value);
            return ending == "lf" || ending == "crlf" || ending == "cr";
        }
        return false;
    }
    
    if (key == "QUOTE_STYLE") {
        if (std::holds_alternative<std::string>(value)) {
            std::string style = std::get<std::string>(value);
            return style == "single" || style == "double" || style == "auto";
        }
        return false;
    }
    
    // 默认验证通过
    return true;
}

bool ConfigApplier::checkConfigConflicts(const std::string& key, const ConfigValue& value) {
    // 检查配置冲突
    if (key == "MINIFY_OUTPUT") {
        // 如果启用了压缩，某些格式化配置将被忽略
        if (std::holds_alternative<std::string>(value) && std::get<std::string>(value) == "true") {
            auto indentConfig = activeConfigs_.find("INDENT_SIZE");
            if (indentConfig != activeConfigs_.end()) {
                std::cerr << "[Config] Warning: INDENT_SIZE will be ignored when MINIFY_OUTPUT is enabled" << std::endl;
            }
        }
    }
    
    if (key == "TREE_SHAKING" && activeConfigs_.find("DEAD_CODE_ELIMINATION") != activeConfigs_.end()) {
        // Tree shaking 包含了死代码消除
        std::cerr << "[Config] Info: TREE_SHAKING includes DEAD_CODE_ELIMINATION" << std::endl;
    }
    
    return true; // 允许配置，但给出警告
}

} // namespace chtl