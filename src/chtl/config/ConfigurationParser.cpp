#include "ConfigurationParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

namespace chtl {
namespace config {

// ConfigVisitor 实现

ConfigVisitor::ConfigVisitor() {
    result.success = true;
}

antlrcpp::Any ConfigVisitor::visitConfigFile(CHConfigParser::ConfigFileContext* ctx) {
    for (auto block : ctx->configBlock()) {
        visit(block);
    }
    return result;
}

antlrcpp::Any ConfigVisitor::visitConfigBlock(CHConfigParser::ConfigBlockContext* ctx) {
    currentGroup = extractConfigName(ctx->configHeader());
    
    for (auto item : ctx->configItem()) {
        visit(item);
    }
    
    return nullptr;
}

antlrcpp::Any ConfigVisitor::visitConfigItem(CHConfigParser::ConfigItemContext* ctx) {
    if (ctx->nestedConfig()) {
        visit(ctx->nestedConfig());
        return nullptr;
    }
    
    std::string key = extractKey(ctx->key());
    ConfigValue value = extractValue(ctx->value());
    
    if (currentGroup.empty() || currentGroup == "Configuration") {
        result.globalConfig[key] = value;
    } else {
        result.namedGroups[currentGroup][key] = value;
    }
    
    return nullptr;
}

antlrcpp::Any ConfigVisitor::visitValue(CHConfigParser::ValueContext* ctx) {
    if (ctx->STRING_LITERAL()) {
        std::string str = ctx->STRING_LITERAL()->getText();
        // 移除引号
        if (str.length() >= 2) {
            str = str.substr(1, str.length() - 2);
        }
        return ConfigValue(str);
    }
    
    if (ctx->NUMBER()) {
        std::string numStr = ctx->NUMBER()->getText();
        if (numStr.find('.') != std::string::npos) {
            return ConfigValue(std::stod(numStr));
        }
        return ConfigValue(std::stoi(numStr));
    }
    
    if (ctx->BOOLEAN()) {
        std::string boolStr = ctx->BOOLEAN()->getText();
        return ConfigValue(boolStr == "true" || boolStr == "yes" || boolStr == "on");
    }
    
    if (ctx->arrayValue()) {
        return visit(ctx->arrayValue());
    }
    
    if (ctx->keywordValue()) {
        return ConfigValue(extractKeywordValue(ctx->keywordValue()));
    }
    
    return ConfigValue();
}

antlrcpp::Any ConfigVisitor::visitArrayValue(CHConfigParser::ArrayValueContext* ctx) {
    std::vector<std::string> array;
    
    for (auto valueCtx : ctx->value()) {
        ConfigValue val = visit(valueCtx).as<ConfigValue>();
        
        // 将值转换为字符串
        if (std::holds_alternative<std::string>(val)) {
            array.push_back(std::get<std::string>(val));
        } else if (std::holds_alternative<int>(val)) {
            array.push_back(std::to_string(std::get<int>(val)));
        } else if (std::holds_alternative<bool>(val)) {
            array.push_back(std::get<bool>(val) ? "true" : "false");
        }
    }
    
    return ConfigValue(array);
}

antlrcpp::Any ConfigVisitor::visitKeywordValue(CHConfigParser::KeywordValueContext* ctx) {
    return ConfigValue(extractKeywordValue(ctx));
}

std::string ConfigVisitor::extractConfigName(CHConfigParser::ConfigHeaderContext* ctx) {
    if (ctx->configName()) {
        if (ctx->configName()->IDENTIFIER()) {
            return ctx->configName()->IDENTIFIER()->getText();
        }
        if (ctx->configName()->STRING_LITERAL()) {
            std::string str = ctx->configName()->STRING_LITERAL()->getText();
            return str.substr(1, str.length() - 2);
        }
    }
    
    // 处理任意前缀的情况
    std::string fullText = ctx->getText();
    // 提取最后一个有意义的标识符
    std::regex idRegex(R"(\b(\w+)\s*[{\[]?\s*$)");
    std::smatch match;
    if (std::regex_search(fullText, match, idRegex)) {
        return match[1];
    }
    
    return "Configuration";
}

std::string ConfigVisitor::extractKey(CHConfigParser::KeyContext* ctx) {
    if (ctx->IDENTIFIER()) {
        return ctx->IDENTIFIER()->getText();
    }
    
    if (ctx->STRING_LITERAL()) {
        std::string str = ctx->STRING_LITERAL()->getText();
        return str.substr(1, str.length() - 2);
    }
    
    // 处理关键字别名
    return ctx->getText();
}

std::string ConfigVisitor::extractKeywordValue(CHConfigParser::KeywordValueContext* ctx) {
    std::string raw = ctx->getText();
    return normalizeKeyword(raw);
}

std::string ConfigVisitor::normalizeKeyword(const std::string& raw) {
    // 保留原始格式，让使用者决定如何处理
    return raw;
}

// FlexibleConfigurationParser 实现

FlexibleConfigurationParser::FlexibleConfigurationParser() {
    // 添加一些默认的规范化规则
    addNormalizationRule(R"(^\[(.+)\]$)", "$1");  // 移除方括号
    addNormalizationRule(R"(^@(.+)$)", "$1");     // 移除@符号
}

ParsedConfig FlexibleConfigurationParser::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        ParsedConfig result;
        result.success = false;
        result.errorMessage = "Cannot open file: " + filename;
        return result;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return parseString(buffer.str());
}

ParsedConfig FlexibleConfigurationParser::parseString(const std::string& content) {
    antlr4::ANTLRInputStream input(content);
    return parseInternal(input);
}

ParsedConfig FlexibleConfigurationParser::parseInternal(antlr4::ANTLRInputStream& input) {
    CHConfigLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CHConfigParser parser(&tokens);
    
    // 错误处理
    class ErrorListener : public antlr4::BaseErrorListener {
    public:
        std::vector<std::string> errors;
        
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol,
                        size_t line, size_t charPositionInLine,
                        const std::string& msg, std::exception_ptr e) override {
            std::stringstream ss;
            ss << "Line " << line << ":" << charPositionInLine << " - " << msg;
            errors.push_back(ss.str());
        }
    };
    
    ErrorListener errorListener;
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    
    auto tree = parser.configFile();
    
    if (!errorListener.errors.empty()) {
        ParsedConfig result;
        result.success = false;
        result.errorMessage = errorListener.errors[0];
        return result;
    }
    
    ConfigVisitor visitor;
    visitor.visit(tree);
    
    ParsedConfig result = visitor.getResult();
    
    // 应用规范化规则
    if (!strictMode && allowFreeform) {
        for (auto& [key, value] : result.globalConfig) {
            if (std::holds_alternative<std::string>(value)) {
                std::string str = std::get<std::string>(value);
                for (const auto& [pattern, replacement] : normalizationRules) {
                    str = std::regex_replace(str, pattern, replacement);
                }
                value = str;
            }
        }
    }
    
    return result;
}

void FlexibleConfigurationParser::addNormalizationRule(const std::string& pattern, 
                                                      const std::string& replacement) {
    normalizationRules.push_back({std::regex(pattern), replacement});
}

// DynamicKeywordSystem 实现

void DynamicKeywordSystem::registerPattern(const std::string& name, const std::string& pattern) {
    KeywordPattern kp;
    kp.name = name;
    kp.pattern = std::regex(pattern);
    kp.template_ = pattern;
    
    // 从pattern中提取基础类型
    std::string baseType;
    if (pattern.find("Template") != std::string::npos) {
        baseType = "Template";
    } else if (pattern.find("Custom") != std::string::npos) {
        baseType = "Custom";
    } else if (pattern.find("Import") != std::string::npos) {
        baseType = "Import";
    } else {
        baseType = name;
    }
    
    patterns[baseType].push_back(kp);
}

std::string DynamicKeywordSystem::matchKeyword(const std::string& input) const {
    for (const auto& [type, patternList] : patterns) {
        for (const auto& pattern : patternList) {
            if (std::regex_match(input, pattern.pattern)) {
                return type;
            }
        }
    }
    return "";
}

std::vector<std::string> DynamicKeywordSystem::getVariants(const std::string& keywordType) const {
    std::vector<std::string> variants;
    
    auto it = patterns.find(keywordType);
    if (it != patterns.end()) {
        for (const auto& pattern : it->second) {
            variants.push_back(pattern.template_);
        }
    }
    
    return variants;
}

void DynamicKeywordSystem::loadFromConfig(const ParsedConfig& config) {
    // 从Name组加载模式
    auto it = config.namedGroups.find("Name");
    if (it != config.namedGroups.end()) {
        for (const auto& [key, value] : it->second) {
            if (std::holds_alternative<std::vector<std::string>>(value)) {
                auto variants = std::get<std::vector<std::string>>(value);
                for (const auto& variant : variants) {
                    // 创建匹配模式
                    std::string pattern = "^" + std::regex_replace(variant, std::regex(R"([.+*?^${}()|[\]\\])"), R"(\$&)") + "$";
                    registerPattern(key, pattern);
                }
            } else if (std::holds_alternative<std::string>(value)) {
                std::string variant = std::get<std::string>(value);
                std::string pattern = "^" + std::regex_replace(variant, std::regex(R"([.+*?^${}()|[\]\\])"), R"(\$&)") + "$";
                registerPattern(key, pattern);
            }
        }
    }
}

// ConfigExampleGenerator 实现

std::string ConfigExampleGenerator::generateBasicExample() {
    return R"(// 基础配置示例
[Configuration] {
    DISABLE_NAME_GROUP = false;
    OPTION_COUNT = 10;
    
    [Name] {
        KEYWORD_TEMPLATE = ["[Template]", "Template", "<template>"];
        CUSTOM_STYLE = ["[Custom]", "@Custom", "custom:"];
        IMPORT_MODULE = ["[Import]", "import", "using"];
        ELEMENT_TAG = ["@Element", "elem", "tag"];
        STYLE_GROUP = ["@Style", "style", ".style"];
    }
})";
}

std::string ConfigExampleGenerator::generateChineseExample() {
    return R"(// 中文配置示例
配置 {
    禁用名称组 = 否;
    选项数量 = 8;
    
    名称组 {
        模板关键字 = ["模板", "【模板】", "範本"];
        自定义样式 = ["自定义", "定制", "客製"];
        导入模块 = ["导入", "引入", "載入"];
        元素标签 = ["元素", "組件", "部件"];
        样式组 = ["样式", "風格", "スタイル"];
    }
})";
}

std::string ConfigExampleGenerator::generateCreativeExample() {
    return R"(// 创意配置示例 - 完全自由的语法
🎨 Configuration 🎨
    DISABLE_NAME_GROUP → false
    OPTION_COUNT → 15
    
    💡 Name Group 💡
        KEYWORD_TEMPLATE ➜ Template | tpl | T
        CUSTOM_STYLE ➜ Custom | ✨Style | 🎨
        IMPORT_MODULE ➜ Import | require | include | use
        NAMESPACE ➜ namespace | ns | 📦
        ORIGIN_HTML ➜ raw-html | <html> | HTML
        
    🔧 Advanced 🔧
        ENABLE_EMOJI = true
        CUSTOM_OPERATORS = ["=>", "->", "::", "..."]
        INDENT_STYLE = "spaces"
        INDENT_SIZE = 2
)";
}

std::string ConfigExampleGenerator::generateMinimalExample() {
    return R"(// 最简配置 - 无需括号和符号
Configuration
    DISABLE_NAME_GROUP false
    
    Name
        KEYWORD_TEMPLATE Template
        CUSTOM_STYLE Style
        IMPORT_MODULE Import
)";
}

bool ConfigExampleGenerator::validateSyntax(const std::string& config) {
    FlexibleConfigurationParser parser;
    ParsedConfig result = parser.parseString(config);
    return result.success;
}

} // namespace config
} // namespace chtl