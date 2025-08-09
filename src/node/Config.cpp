#include "node/Config.h"
#include <sstream>

namespace chtl {

std::string Config::getConfig(const std::string& key) const {
    auto it = configItems_.find(key);
    return it != configItems_.end() ? it->second : "";
}

void Config::addArrayConfigItem(const std::string& key, const std::string& value) {
    arrayItems_[key].push_back(value);
}

std::vector<std::string> Config::getArrayConfig(const std::string& key) const {
    auto it = arrayItems_.find(key);
    return it != arrayItems_.end() ? it->second : std::vector<std::string>();
}

void Config::mergeConfig(const Config& other) {
    // 合并普通配置项
    for (const auto& [key, value] : other.configItems_) {
        configItems_[key] = value;
    }
    
    // 合并数组配置项
    for (const auto& [key, values] : other.arrayItems_) {
        if (arrayItems_.find(key) != arrayItems_.end()) {
            // 如果键已存在，追加值
            arrayItems_[key].insert(arrayItems_[key].end(), values.begin(), values.end());
        } else {
            // 如果键不存在，直接赋值
            arrayItems_[key] = values;
        }
    }
}

std::shared_ptr<Node> Config::clone(bool deep) const {
    (void)deep; // Config节点通常不包含子节点
    auto cloned = std::make_shared<Config>(configName_);
    cloned->configItems_ = configItems_;
    cloned->arrayItems_ = arrayItems_;
    return cloned;
}

std::string Config::toString() const {
    std::stringstream ss;
    ss << "[Configuration]";
    
    if (!configName_.empty()) {
        ss << " " << configName_;
    }
    
    ss << "\n{";
    
    // 输出普通配置项
    for (const auto& [key, value] : configItems_) {
        ss << "\n  " << key << ": ";
        
        // 检查是否需要引号
        if (value.find(' ') != std::string::npos || value.empty()) {
            ss << "\"" << value << "\"";
        } else {
            ss << value;
        }
        ss << ";";
    }
    
    // 输出数组配置项
    for (const auto& [key, values] : arrayItems_) {
        ss << "\n  " << key << ": [";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i > 0) ss << ", ";
            
            // 检查是否需要引号
            if (values[i].find(' ') != std::string::npos || values[i].empty()) {
                ss << "\"" << values[i] << "\"";
            } else {
                ss << values[i];
            }
        }
        ss << "];";
    }
    
    ss << "\n}";
    
    return ss.str();
}

void Config::accept(Visitor* visitor) {
    // 基础Visitor不支持Config，需要使用ExtendedVisitor
    (void)visitor;
}

} // namespace chtl