#ifndef CHTL_CONFIGURATION_PARSER_H
#define CHTL_CONFIGURATION_PARSER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "antlr4-runtime.h"
#include "generated/CHConfigLexer.h"
#include "generated/CHConfigParser.h"
#include "generated/CHConfigBaseVisitor.h"
#include "ConfigurationSystem.h"

namespace chtl {
namespace config {

// 配置解析结果
struct ParsedConfig {
    bool success = false;
    std::string errorMessage;
    std::unordered_map<std::string, ConfigValue> globalConfig;
    std::unordered_map<std::string, std::unordered_map<std::string, ConfigValue>> namedGroups;
};

// 配置访问者
class ConfigVisitor : public CHConfigBaseVisitor {
public:
    ConfigVisitor();
    
    // 获取解析结果
    ParsedConfig getResult() const { return result; }
    
    // 访问方法
    antlrcpp::Any visitConfigFile(CHConfigParser::ConfigFileContext* ctx) override;
    antlrcpp::Any visitConfigBlock(CHConfigParser::ConfigBlockContext* ctx) override;
    antlrcpp::Any visitConfigItem(CHConfigParser::ConfigItemContext* ctx) override;
    antlrcpp::Any visitValue(CHConfigParser::ValueContext* ctx) override;
    antlrcpp::Any visitArrayValue(CHConfigParser::ArrayValueContext* ctx) override;
    antlrcpp::Any visitObjectValue(CHConfigParser::ObjectValueContext* ctx) override;
    antlrcpp::Any visitKeywordValue(CHConfigParser::KeywordValueContext* ctx) override;
    
private:
    ParsedConfig result;
    std::string currentGroup;
    
    // 辅助方法
    std::string extractConfigName(CHConfigParser::ConfigHeaderContext* ctx);
    std::string extractKey(CHConfigParser::KeyContext* ctx);
    ConfigValue extractValue(CHConfigParser::ValueContext* ctx);
    std::string extractKeywordValue(CHConfigParser::KeywordValueContext* ctx);
    std::string normalizeKeyword(const std::string& raw);
};

// 高级配置解析器
class FlexibleConfigurationParser {
public:
    FlexibleConfigurationParser();
    
    // 解析配置文件
    ParsedConfig parseFile(const std::string& filename);
    ParsedConfig parseString(const std::string& content);
    
    // 设置选项
    void setAllowFreeformKeywords(bool allow) { allowFreeform = allow; }
    void setStrictMode(bool strict) { strictMode = strict; }
    
    // 关键字规范化规则
    void addNormalizationRule(const std::string& pattern, const std::string& replacement);
    
private:
    bool allowFreeform = true;
    bool strictMode = false;
    std::vector<std::pair<std::regex, std::string>> normalizationRules;
    
    ParsedConfig parseInternal(antlr4::ANTLRInputStream& input);
};

// 动态关键字系统
class DynamicKeywordSystem {
public:
    // 注册关键字模式
    void registerPattern(const std::string& name, const std::string& pattern);
    
    // 匹配关键字
    std::string matchKeyword(const std::string& input) const;
    
    // 获取所有变体
    std::vector<std::string> getVariants(const std::string& keywordType) const;
    
    // 从配置加载
    void loadFromConfig(const ParsedConfig& config);
    
private:
    struct KeywordPattern {
        std::string name;
        std::regex pattern;
        std::string template_;
    };
    
    std::unordered_map<std::string, std::vector<KeywordPattern>> patterns;
};

// 配置示例生成器
class ConfigExampleGenerator {
public:
    // 生成示例配置
    static std::string generateBasicExample();
    static std::string generateChineseExample();
    static std::string generateCreativeExample();
    static std::string generateMinimalExample();
    
    // 验证配置语法
    static bool validateSyntax(const std::string& config);
};

} // namespace config
} // namespace chtl

#endif // CHTL_CONFIGURATION_PARSER_H