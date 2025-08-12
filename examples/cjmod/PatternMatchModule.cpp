#include "CJmod/CJmodCore.h"
#include <regex>
#include <vector>

namespace chtl {
namespace cjmod {

// 模式匹配模块 - 带来函数式编程的强大模式匹配
class PatternMatchModule : public CJmodModule {
public:
    std::vector<SyntaxBuilder> syntax() override {
        return {
            // match 表达式
            SyntaxBuilder("match-expression")
                .priority(200)
                .scan([this](ScanContext* ctx) -> std::vector<ScanResult> {
                    return scanMatchBlocks(ctx);
                })
                .generate([this](const ScanResult& result, GenerateContext* ctx) {
                    return generateMatchExpression(result, ctx);
                })
                .example(R"(
                    match value {
                        0 -> "zero";
                        1..10 -> "small";
                        n if n > 100 -> "large";
                        _ -> "other";
                    }
                )"),
            
            // 解构赋值增强
            SyntaxBuilder("destructuring")
                .priority(180)
                .pattern(R"(let\s*\{([^}]+)\}\s*=\s*([^;]+);)")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string pattern = result.captures.at("1");
                    std::string value = result.captures.at("2");
                    
                    // 增强的解构，支持默认值和重命名
                    return "const {" + processDestructuringPattern(pattern) + "} = " + value + ";";
                })
                .example("let { name, age = 18, email: userEmail } = user;"),
            
            // 数组模式匹配
            SyntaxBuilder("array-pattern")
                .priority(175)
                .pattern(R"(let\s*\[([^\]]+)\]\s*=\s*([^;]+);)")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string pattern = result.captures.at("1");
                    std::string value = result.captures.at("2");
                    
                    return "const [" + processArrayPattern(pattern) + "] = " + value + ";";
                })
                .example("let [first, ...rest] = array;")
                .example("let [x, , z] = coordinates;"),
            
            // when 守卫表达式
            SyntaxBuilder("when-guard")
                .priority(170)
                .pattern(R"(when\s*\(([^)]+)\)\s*\{([^}]+)\}\s*else\s*\{([^}]+)\})")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string condition = result.captures.at("1");
                    std::string thenBlock = result.captures.at("2");
                    std::string elseBlock = result.captures.at("3");
                    
                    return "(" + condition + ") ? (" + thenBlock + ") : (" + elseBlock + ")";
                })
                .example("when (user.isActive) { sendEmail() } else { logInactive() }"),
            
            // 类型模式匹配
            SyntaxBuilder("type-match")
                .priority(165)
                .pattern(R"(match\s+typeof\s+(\w+)\s*\{([^}]+)\})")
                .generate([this](const ScanResult& result, GenerateContext* ctx) {
                    std::string variable = result.captures.at("1");
                    std::string cases = result.captures.at("2");
                    
                    return generateTypeMatch(variable, cases, ctx);
                })
                .example(R"(
                    match typeof value {
                        'string' -> value.toUpperCase();
                        'number' -> value.toFixed(2);
                        'boolean' -> value ? 'yes' : 'no';
                        _ -> String(value);
                    }
                )")
        };
    }
    
    void runtime(RuntimeBuilder& builder) override {
        // 模式匹配运行时支持
        builder.addFunction("__match", R"(
            function __match(value, patterns) {
                for (const [pattern, handler] of patterns) {
                    if (pattern === '_' || pattern === value) {
                        return typeof handler === 'function' ? handler(value) : handler;
                    }
                    
                    // 范围匹配
                    if (typeof pattern === 'object' && pattern.__range) {
                        const [min, max] = pattern.__range;
                        if (value >= min && value <= max) {
                            return typeof handler === 'function' ? handler(value) : handler;
                        }
                    }
                    
                    // 条件匹配
                    if (typeof pattern === 'function' && pattern(value)) {
                        return typeof handler === 'function' ? handler(value) : handler;
                    }
                    
                    // 正则匹配
                    if (pattern instanceof RegExp && pattern.test(value)) {
                        return typeof handler === 'function' ? handler(value) : handler;
                    }
                    
                    // 数组包含匹配
                    if (Array.isArray(pattern) && pattern.includes(value)) {
                        return typeof handler === 'function' ? handler(value) : handler;
                    }
                }
                
                throw new Error('No matching pattern found for value: ' + value);
            }
        )");
        
        builder.addFunction("__range", R"(
            function __range(min, max) {
                return { __range: [min, max] };
            }
        )");
        
        builder.addFunction("__guard", R"(
            function __guard(predicate) {
                return predicate;
            }
        )");
        
        // 添加一些实用的模式匹配辅助函数
        builder.addGlobal("Some", R"(
            function Some(value) {
                return { __type: 'Some', value };
            }
        )");
        
        builder.addGlobal("None", R"(
            { __type: 'None' }
        )");
        
        builder.addGlobal("Ok", R"(
            function Ok(value) {
                return { __type: 'Ok', value };
            }
        )");
        
        builder.addGlobal("Err", R"(
            function Err(error) {
                return { __type: 'Err', error };
            }
        )");
    }
    
private:
    // 扫描 match 块
    std::vector<ScanResult> scanMatchBlocks(ScanContext* ctx) {
        std::vector<ScanResult> results;
        std::string code = ctx->getCode();
        size_t pos = ctx->getPosition();
        
        // 查找 match 表达式
        std::regex matchRegex(R"(match\s+([^{]+)\s*\{([^}]+)\})");
        auto begin = std::sregex_iterator(code.begin() + pos, code.end(), matchRegex);
        auto end = std::sregex_iterator();
        
        for (auto it = begin; it != end; ++it) {
            ScanResult result;
            result.start = pos + it->position();
            result.end = result.start + it->length();
            result.content = it->str();
            
            // 存储匹配的值表达式和 case 块
            result.userData["value"] = (*it)[1].str();
            result.userData["cases"] = (*it)[2].str();
            
            results.push_back(result);
        }
        
        return results;
    }
    
    // 生成 match 表达式
    std::string generateMatchExpression(const ScanResult& result, GenerateContext* ctx) {
        std::string value = result.userData.at("value");
        std::string cases = result.userData.at("cases");
        
        // 解析 case 语句
        std::vector<std::pair<std::string, std::string>> patterns;
        std::regex caseRegex(R"(([^->]+)->([^;]+);?)");
        auto begin = std::sregex_iterator(cases.begin(), cases.end(), caseRegex);
        auto end = std::sregex_iterator();
        
        for (auto it = begin; it != end; ++it) {
            std::string pattern = (*it)[1].str();
            std::string handler = (*it)[2].str();
            
            // 去除空格
            pattern = std::regex_replace(pattern, std::regex("^\\s+|\\s+$"), "");
            handler = std::regex_replace(handler, std::regex("^\\s+|\\s+$"), "");
            
            patterns.push_back({pattern, handler});
        }
        
        // 生成 JavaScript 代码
        std::stringstream ss;
        ss << "__match(" << value << ", [\n";
        
        for (const auto& [pattern, handler] : patterns) {
            ss << "  [";
            
            // 处理不同的模式类型
            if (pattern == "_") {
                ss << "'_'";
            } else if (pattern.find("..") != std::string::npos) {
                // 范围模式
                size_t dotPos = pattern.find("..");
                std::string min = pattern.substr(0, dotPos);
                std::string max = pattern.substr(dotPos + 2);
                ss << "__range(" << min << ", " << max << ")";
            } else if (pattern.find(" if ") != std::string::npos) {
                // 条件守卫
                size_t ifPos = pattern.find(" if ");
                std::string var = pattern.substr(0, ifPos);
                std::string condition = pattern.substr(ifPos + 4);
                ss << "__guard((" << var << ") => " << condition << ")";
            } else if (pattern[0] == '\'' || pattern[0] == '"') {
                // 字符串字面量
                ss << pattern;
            } else if (std::regex_match(pattern, std::regex("-?\\d+"))) {
                // 数字字面量
                ss << pattern;
            } else {
                // 变量或其他表达式
                ss << pattern;
            }
            
            ss << ", ";
            
            // 处理 handler
            if (handler.find("=>") != std::string::npos || 
                handler.find("return") != std::string::npos ||
                handler.find("{") != std::string::npos) {
                // 已经是函数形式
                ss << "(" << handler << ")";
            } else {
                // 简单表达式，包装成函数
                ss << "() => " << handler;
            }
            
            ss << "],\n";
        }
        
        ss << "])";
        
        return ss.str();
    }
    
    // 生成类型匹配
    std::string generateTypeMatch(const std::string& variable, 
                                  const std::string& cases, 
                                  GenerateContext* ctx) {
        std::stringstream ss;
        ss << "(function() {\n";
        ss << "  const __type = typeof " << variable << ";\n";
        ss << "  switch(__type) {\n";
        
        // 解析 case
        std::regex caseRegex(R"('(\w+)'\s*->\s*([^;]+);?)");
        auto begin = std::sregex_iterator(cases.begin(), cases.end(), caseRegex);
        auto end = std::sregex_iterator();
        
        for (auto it = begin; it != end; ++it) {
            std::string type = (*it)[1].str();
            std::string handler = (*it)[2].str();
            
            handler = std::regex_replace(handler, std::regex("^\\s+|\\s+$"), "");
            
            ss << "    case '" << type << "': return " << handler << ";\n";
        }
        
        // 默认 case
        if (cases.find("_") != std::string::npos) {
            std::regex defaultRegex(R"(_\s*->\s*([^;]+);?)");
            std::smatch match;
            if (std::regex_search(cases, match, defaultRegex)) {
                std::string handler = match[1].str();
                handler = std::regex_replace(handler, std::regex("^\\s+|\\s+$"), "");
                ss << "    default: return " << handler << ";\n";
            }
        }
        
        ss << "  }\n";
        ss << "})()";
        
        return ss.str();
    }
    
    // 处理解构模式
    static std::string processDestructuringPattern(const std::string& pattern) {
        // 这里简化处理，实际实现需要更复杂的解析
        return pattern;
    }
    
    // 处理数组模式
    static std::string processArrayPattern(const std::string& pattern) {
        // 这里简化处理，实际实现需要更复杂的解析
        return pattern;
    }
};

// 导出函数
extern "C" {
    CJmodModule* createModule() {
        return new PatternMatchModule();
    }
    
    const char* getModuleName() {
        return "pattern";
    }
    
    const char* getModuleVersion() {
        return "1.0.0";
    }
    
    const char* getModuleDescription() {
        return "Powerful pattern matching for JavaScript";
    }
}

} // namespace cjmod
} // namespace chtl