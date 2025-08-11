#include "Generator/ConfigGenerator.h"
#include "Node/Config.h"
#include <algorithm>
#include <sstream>

namespace chtl {

ConfigGenerator::ConfigGenerator() 
    : BasicGenerator(),
      sortKeys_(true),
      prettyPrint_(true),
      indentSize_(2) {
}

bool ConfigGenerator::generate(std::shared_ptr<Node> node) {
    if (!node || node->getType() != NodeType::CONFIG) {
        return false;
    }
    
    generateNode(node);
    return true;
}

void ConfigGenerator::generate(std::shared_ptr<Node> root, std::ostream& output) {
    if (!root) {
        return;
    }
    
    output_ = &output;
    currentIndent_ = 0;
    
    generateNode(root);
}

void ConfigGenerator::generateNode(std::shared_ptr<Node> node) {
    if (!node || !output_) {
        return;
    }
    
    switch (node->getType()) {
        case NodeType::CONFIG:
            generateConfig(node);
            break;
        default:
            // ConfigGenerator只处理Config节点
            break;
    }
}

void ConfigGenerator::generateElement(std::shared_ptr<Node> node) {
    // ConfigGenerator不处理元素节点
    reportWarning("ConfigGenerator does not handle element nodes");
    (void)node;
}

void ConfigGenerator::generateText(std::shared_ptr<Node> node) {
    // ConfigGenerator不处理文本节点
    reportWarning("ConfigGenerator does not handle text nodes");
    (void)node;
}

void ConfigGenerator::generateTemplate(std::shared_ptr<Node> node) {
    // ConfigGenerator不处理模板节点
    reportWarning("ConfigGenerator does not handle template nodes");
    (void)node;
}

void ConfigGenerator::generateCustom(std::shared_ptr<Node> node) {
    // ConfigGenerator不处理自定义节点
    reportWarning("ConfigGenerator does not handle custom nodes");
    (void)node;
}

void ConfigGenerator::generateStyle(std::shared_ptr<Node> node) {
    // ConfigGenerator不处理样式节点
    reportWarning("ConfigGenerator does not handle style nodes");
    (void)node;
}

void ConfigGenerator::generateComment(std::shared_ptr<Node> node) {
    // ConfigGenerator不处理注释节点
    reportWarning("ConfigGenerator does not handle comment nodes");
    (void)node;
}

void ConfigGenerator::generateConfig(std::shared_ptr<Node> node) {
    auto config = std::dynamic_pointer_cast<Config>(node);
    if (!config) {
        return;
    }
    
    // 根据当前格式生成配置
    std::string content;
    switch (currentFormat_) {
        case ConfigFormat::JSON:
            content = generateJSON(config);
            break;
        case ConfigFormat::YAML:
            content = generateYAML(config);
            break;
        case ConfigFormat::INI:
            content = generateINI(config);
            break;
        case ConfigFormat::TOML:
            content = generateTOML(config);
            break;
        case ConfigFormat::XML:
            content = generateXML(config);
            break;
        case ConfigFormat::CHTL:
        default:
            content = generateCHTL(config);
            break;
    }
    
    write(content);
}

std::string ConfigGenerator::generateJSON(std::shared_ptr<Config> config) {
    std::stringstream ss;
    ss << "{\n";
    
    auto configs = config->getConfigItems();
    std::vector<std::string> keys;
    
    // 收集所有键
    for (const auto& [key, value] : configs) {
        keys.push_back(key);
    }
    
    // 排序键（如果启用）
    if (sortKeys_) {
        std::sort(keys.begin(), keys.end());
    }
    
    // 生成JSON
    bool first = true;
    for (const auto& key : keys) {
        if (!first) {
            ss << ",\n";
        }
        first = false;
        
        ss << "  \"" << key << "\": ";
        
        auto value = configs.at(key);
        if (std::holds_alternative<std::string>(value)) {
            ss << "\"" << escapeJSON(std::get<std::string>(value)) << "\"";
        } else if (std::holds_alternative<std::vector<std::string>>(value)) {
            const auto& vec = std::get<std::vector<std::string>>(value);
            ss << "[";
            for (size_t i = 0; i < vec.size(); ++i) {
                if (i > 0) ss << ", ";
                ss << "\"" << escapeJSON(vec[i]) << "\"";
            }
            ss << "]";
        }
    }
    
    ss << "\n}";
    return ss.str();
}

std::string ConfigGenerator::generateYAML(std::shared_ptr<Config> config) {
    std::stringstream ss;
    
    auto configs = config->getConfigItems();
    
    for (const auto& [key, value] : configs) {
        ss << key << ": ";
        
        if (std::holds_alternative<std::string>(value)) {
            const auto& str = std::get<std::string>(value);
            if (str.find('\n') != std::string::npos || str.find('"') != std::string::npos) {
                ss << "|\n  " << str;
            } else {
                ss << str;
            }
        } else if (std::holds_alternative<std::vector<std::string>>(value)) {
            const auto& vec = std::get<std::vector<std::string>>(value);
            ss << "\n";
            for (const auto& item : vec) {
                ss << "  - " << item << "\n";
            }
        }
        
        ss << "\n";
    }
    
    return ss.str();
}

std::string ConfigGenerator::generateINI(std::shared_ptr<Config> config) {
    std::stringstream ss;
    
    auto configs = config->getConfigItems();
    
    for (const auto& [key, value] : configs) {
        ss << key << " = ";
        
        if (std::holds_alternative<std::string>(value)) {
            ss << std::get<std::string>(value);
        } else if (std::holds_alternative<std::vector<std::string>>(value)) {
            const auto& vec = std::get<std::vector<std::string>>(value);
            // INI不支持数组，使用逗号分隔
            for (size_t i = 0; i < vec.size(); ++i) {
                if (i > 0) ss << ", ";
                ss << vec[i];
            }
        }
        
        ss << "\n";
    }
    
    return ss.str();
}

std::string ConfigGenerator::generateTOML(std::shared_ptr<Config> config) {
    std::stringstream ss;
    
    auto configs = config->getConfigItems();
    
    for (const auto& [key, value] : configs) {
        ss << key << " = ";
        
        if (std::holds_alternative<std::string>(value)) {
            const auto& str = std::get<std::string>(value);
            // TOML字符串需要引号
            ss << "\"" << str << "\"";
        } else if (std::holds_alternative<std::vector<std::string>>(value)) {
            const auto& vec = std::get<std::vector<std::string>>(value);
            ss << "[";
            for (size_t i = 0; i < vec.size(); ++i) {
                if (i > 0) ss << ", ";
                ss << "\"" << vec[i] << "\"";
            }
            ss << "]";
        }
        
        ss << "\n";
    }
    
    return ss.str();
}

std::string ConfigGenerator::generateXML(std::shared_ptr<Config> config) {
    std::stringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    ss << "<configuration>\n";
    
    auto configs = config->getConfigItems();
    
    for (const auto& [key, value] : configs) {
        if (std::holds_alternative<std::string>(value)) {
            ss << "  <" << key << ">" << escapeXML(std::get<std::string>(value)) 
               << "</" << key << ">\n";
        } else if (std::holds_alternative<std::vector<std::string>>(value)) {
            const auto& vec = std::get<std::vector<std::string>>(value);
            ss << "  <" << key << ">\n";
            for (const auto& item : vec) {
                ss << "    <item>" << escapeXML(item) << "</item>\n";
            }
            ss << "  </" << key << ">\n";
        }
    }
    
    ss << "</configuration>";
    return ss.str();
}

std::string ConfigGenerator::generateCHTL(std::shared_ptr<Config> config) {
    // 使用Config节点自己的toString方法
    return config->toString();
}

void ConfigGenerator::write(const std::string& str) {
    if (output_) {
        *output_ << str;
    }
}

void ConfigGenerator::writeLine(const std::string& str) {
    write(str);
    write("\n");
}

void ConfigGenerator::writeIndent() {
    if (prettyPrint_) {
        write(std::string(currentIndent_ * indentSize_, ' '));
    }
}

void ConfigGenerator::increaseIndent() {
    currentIndent_++;
}

void ConfigGenerator::decreaseIndent() {
    if (currentIndent_ > 0) {
        currentIndent_--;
    }
}

std::string ConfigGenerator::escapeJSON(const std::string& str) {
    std::string result;
    for (char c : str) {
        switch (c) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\b': result += "\\b"; break;
            case '\f': result += "\\f"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default:
                if (c >= 0x20 && c <= 0x7E) {
                    result += c;
                } else {
                    // Unicode转义
                    char buf[7];
                    std::snprintf(buf, sizeof(buf), "\\u%04x", static_cast<unsigned char>(c));
                    result += buf;
                }
        }
    }
    return result;
}

std::string ConfigGenerator::escapeXML(const std::string& str) {
    std::string result;
    for (char c : str) {
        switch (c) {
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '&': result += "&amp;"; break;
            case '\'': result += "&apos;"; break;
            case '"': result += "&quot;"; break;
            default: result += c;
        }
    }
    return result;
}

std::vector<std::string> ConfigGenerator::getSortedKeys(const std::unordered_map<std::string, ConfigValue>& map) {
    std::vector<std::string> keys;
    for (const auto& [key, value] : map) {
        keys.push_back(key);
    }
    if (sortKeys_) {
        std::sort(keys.begin(), keys.end());
    }
    return keys;
}

void ConfigGenerator::reportWarning(const std::string& message) {
    // 简单实现，可以后续改进
    std::cerr << "ConfigGenerator Warning: " << message << std::endl;
}

} // namespace chtl