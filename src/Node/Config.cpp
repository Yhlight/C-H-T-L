#include "Node/Config.h"
#include <sstream>

namespace chtl {

std::string Config::getConfig(const std::string& key) const {
    auto it = configItems_.find(key);
    if (it != configItems_.end()) {
        // 如果是字符串，返回字符串
        if (std::holds_alternative<std::string>(it->second)) {
            return std::get<std::string>(it->second);
        }
        // 如果是数组，返回第一个元素
        else if (std::holds_alternative<std::vector<std::string>>(it->second)) {
            const auto& vec = std::get<std::vector<std::string>>(it->second);
            return vec.empty() ? "" : vec[0];
        }
    }
    return "";
}

void Config::addArrayConfigItem(const std::string& key, const std::string& value) {
    auto it = configItems_.find(key);
    if (it != configItems_.end() && std::holds_alternative<std::vector<std::string>>(it->second)) {
        std::get<std::vector<std::string>>(it->second).push_back(value);
    } else {
        // 创建新的数组
        configItems_[key] = std::vector<std::string>{value};
    }
}

std::vector<std::string> Config::getArrayConfig(const std::string& key) const {
    auto it = configItems_.find(key);
    if (it != configItems_.end() && std::holds_alternative<std::vector<std::string>>(it->second)) {
        return std::get<std::vector<std::string>>(it->second);
    }
    return std::vector<std::string>();
}

bool Config::hasArrayConfig(const std::string& key) const {
    auto it = configItems_.find(key);
    return it != configItems_.end() && std::holds_alternative<std::vector<std::string>>(it->second);
}

void Config::mergeConfig(const Config& other) {
    // 合并配置项
    for (const auto& [key, value] : other.configItems_) {
        configItems_[key] = value;
    }
}

std::shared_ptr<Node> Config::clone(bool deep) const {
    auto cloned = std::make_shared<Config>(configName_);
    cloned->configItems_ = configItems_;
    
    if (deep) {
        for (const auto& child : children_) {
            cloned->appendChild(child->clone(deep));
        }
    }
    
    return cloned;
}

std::string Config::toString() const {
    std::stringstream ss;
    ss << "[Configuration] {\n";
    
    // 输出配置项
    for (const auto& [key, value] : configItems_) {
        ss << "  " << key << " = ";
        
        // 处理不同类型的值
        if (std::holds_alternative<std::string>(value)) {
            const auto& str = std::get<std::string>(value);
            // 如果包含空格或为空，添加引号
            if (str.find(' ') != std::string::npos || str.empty()) {
                ss << "\"" << str << "\"";
            } else {
                ss << str;
            }
        } else if (std::holds_alternative<std::vector<std::string>>(value)) {
            const auto& vec = std::get<std::vector<std::string>>(value);
            ss << "[";
            for (size_t i = 0; i < vec.size(); ++i) {
                if (i > 0) ss << ", ";
                if (vec[i].find(' ') != std::string::npos || vec[i].empty()) {
                    ss << "\"" << vec[i] << "\"";
                } else {
                    ss << vec[i];
                }
            }
            ss << "]";
        }
        
        ss << ";\n";
    }
    
    ss << "}";
    return ss.str();
}

void Config::accept(Visitor* visitor) {
    // Visitor模式的基类不支持Config节点
    // 需要使用扩展的访问者或在基类中添加visitConfig方法
    (void)visitor;
}

} // namespace chtl