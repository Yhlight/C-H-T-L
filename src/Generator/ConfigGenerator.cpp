#include "Generator/ConfigGenerator.h"
#include <algorithm>
#include <sstream>

namespace chtl {

ConfigGenerator::ConfigGenerator(ConfigFormat format)
    : BasicGenerator(),
      format_(format),
      sortKeys_(false),
      includeComments_(true),
      maxLineLength_(120) {
}

bool ConfigGenerator::generate(std::shared_ptr<Node> node) {
    if (!node) {
        reportError("Cannot generate from null node");
        return false;
    }
    
    if (node->getType() != NodeType::CONFIG) {
        reportError("ConfigGenerator can only generate Config nodes");
        return false;
    }
    
    auto configNode = std::dynamic_pointer_cast<Config>(node);
    if (!configNode) {
        reportError("Failed to cast node to Config");
        return false;
    }
    
    beginGeneration();
    
    bool success = false;
    switch (format_) {
        case ConfigFormat::JSON:
            success = generateJson(configNode);
            break;
        case ConfigFormat::YAML:
            success = generateYaml(configNode);
            break;
        case ConfigFormat::INI:
            success = generateIni(configNode);
            break;
        case ConfigFormat::XML:
            success = generateXml(configNode);
            break;
        case ConfigFormat::PROPERTIES:
            success = generateProperties(configNode);
            break;
        case ConfigFormat::TOML:
            success = generateToml(configNode);
            break;
        case ConfigFormat::CHTL:
            success = generateChtl(configNode);
            break;
        default:
            reportError("Unknown config format");
            break;
    }
    
    endGeneration();
    return success;
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

void ConfigGenerator::generateComment(std::shared_ptr<Node> node) {
    // ConfigGenerator不处理注释节点
    reportWarning("ConfigGenerator does not handle comment nodes");
    (void)node;
}

void ConfigGenerator::generateConfig(std::shared_ptr<Node> node) {
    // 委托给generate方法
    generate(node);
}

bool ConfigGenerator::generateJson(std::shared_ptr<Config> config) {
    write("{");
    if (!config_.minify) writeLine();
    increaseIndent();
    
    auto configs = config->getConfigs();
    auto sortedKeys = sortKeys_ ? getSortedKeys(configs) : std::vector<std::string>();
    
    bool first = true;
    
    // 输出普通配置项
    if (sortKeys_) {
        for (const auto& key : sortedKeys) {
            if (!first) {
                write(",");
                if (!config_.minify) writeLine();
            }
            first = false;
            
            writeIndent();
            write("\"" + key + "\": ");
            writeJsonValue(configs[key]);
        }
    } else {
        for (const auto& [key, value] : configs) {
            if (!first) {
                write(",");
                if (!config_.minify) writeLine();
            }
            first = false;
            
            writeIndent();
            write("\"" + key + "\": ");
            writeJsonValue(value);
        }
    }
    
    // 输出数组配置项
    // TODO: 实现数组配置项的JSON输出
    
    decreaseIndent();
    if (!config_.minify) {
        writeLine();
        writeIndent();
    }
    write("}");
    
    return true;
}

bool ConfigGenerator::generateYaml(std::shared_ptr<Config> config) {
    if (yamlConfig_.explicitStart) {
        writeLine("---");
    }
    
    auto configs = config->getConfigs();
    
    // 输出配置名称（如果有）
    if (!config->getConfigName().empty()) {
        writeYamlComment("Configuration: " + config->getConfigName());
    }
    
    // 输出普通配置项
    for (const auto& [key, value] : configs) {
        writeYamlValue(key, value);
    }
    
    // TODO: 输出数组配置项
    
    if (yamlConfig_.explicitEnd) {
        writeLine("...");
    }
    
    return true;
}

bool ConfigGenerator::generateIni(std::shared_ptr<Config> config) {
    // 写入节名称
    if (!config->getConfigName().empty()) {
        writeIniSection(config->getConfigName());
    } else {
        writeIniSection("Configuration");
    }
    
    auto configs = config->getConfigs();
    
    // 输出配置项
    for (const auto& [key, value] : configs) {
        writeIniKeyValue(key, value);
    }
    
    return true;
}

bool ConfigGenerator::generateChtl(std::shared_ptr<Config> config) {
    // 生成CHTL原生格式
    write("[Configuration]");
    
    if (!config->getConfigName().empty()) {
        write(" " + config->getConfigName());
    }
    
    writeLine();
    writeLine("{");
    increaseIndent();
    
    auto configs = config->getConfigs();
    
    // 输出普通配置项
    for (const auto& [key, value] : configs) {
        writeIndent();
        write(key + ": ");
        
        // 检查是否需要引号
        if (value.find(' ') != std::string::npos || value.empty()) {
            write("\"" + value + "\"");
        } else {
            write(value);
        }
        writeLine(";");
    }
    
    // TODO: 输出数组配置项
    
    decreaseIndent();
    writeIndent();
    writeLine("}");
    
    return true;
}

// 占位实现
bool ConfigGenerator::generateXml(std::shared_ptr<Config> config) {
    (void)config;
    reportError("XML format not yet implemented");
    return false;
}

bool ConfigGenerator::generateProperties(std::shared_ptr<Config> config) {
    (void)config;
    reportError("Properties format not yet implemented");
    return false;
}

bool ConfigGenerator::generateToml(std::shared_ptr<Config> config) {
    (void)config;
    reportError("TOML format not yet implemented");
    return false;
}

// 辅助方法实现
void ConfigGenerator::writeJsonValue(const std::string& value, bool isLast) {
    if (needsQuoting(value, ConfigFormat::JSON)) {
        write("\"" + escapeJavaScript(value) + "\"");
    } else {
        write(value);
    }
    
    if (!isLast && jsonConfig_.trailingComma) {
        write(",");
    }
}

void ConfigGenerator::writeYamlValue(const std::string& key, const std::string& value) {
    writeIndent();
    write(key + ": ");
    
    if (needsQuoting(value, ConfigFormat::YAML)) {
        write("\"" + value + "\"");
    } else {
        write(value);
    }
    writeLine();
}

void ConfigGenerator::writeYamlComment(const std::string& comment) {
    if (includeComments_) {
        writeIndent();
        writeLine("# " + comment);
    }
}

void ConfigGenerator::writeIniSection(const std::string& section) {
    writeLine("[" + section + "]");
}

void ConfigGenerator::writeIniKeyValue(const std::string& key, const std::string& value) {
    writeIndent();
    writeLine(key + " = " + value);
}

void ConfigGenerator::writeIniComment(const std::string& comment) {
    if (includeComments_) {
        writeLine("; " + comment);
    }
}

std::vector<std::string> ConfigGenerator::getSortedKeys(
    const std::unordered_map<std::string, std::string>& map) {
    std::vector<std::string> keys;
    keys.reserve(map.size());
    
    for (const auto& [key, value] : map) {
        keys.push_back(key);
    }
    
    std::sort(keys.begin(), keys.end());
    return keys;
}

bool ConfigGenerator::needsQuoting(const std::string& value, ConfigFormat format) {
    if (value.empty()) return true;
    
    switch (format) {
        case ConfigFormat::JSON:
            // JSON需要引号的情况：非数字、非布尔值
            return !(value == "true" || value == "false" || value == "null" ||
                    std::all_of(value.begin(), value.end(), ::isdigit));
                    
        case ConfigFormat::YAML:
            // YAML需要引号的情况：包含特殊字符
            return value.find_first_of(":{}[]!&*#?|-<>=") != std::string::npos;
            
        default:
            return false;
    }
}

} // namespace chtl