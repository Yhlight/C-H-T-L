#include "CJmod/CJmodCore.h"
#include <regex>
#include <sstream>

namespace chtl {
namespace cjmod {

// 管道操作符模块 - 让数据处理更优雅
class PipelineModule : public CJmodModule {
public:
    std::vector<SyntaxBuilder> syntax() override {
        return {
            // 基础管道操作符 |>
            SyntaxBuilder("pipe-operator")
                .priority(150)
                .description("管道操作符，将左侧的值作为右侧函数的第一个参数")
                .pattern(R"(([^|]+)\s*\|>\s*([a-zA-Z_]\w*))")
                .validate([](const ScanResult& result) {
                    return !result.captures.at("1").empty() && 
                           !result.captures.at("2").empty();
                })
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string value = result.captures.at("1");
                    std::string func = result.captures.at("2");
                    
                    // 去除值两端的空格
                    value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
                    
                    return func + "(" + value + ")";
                })
                .example("value |> trim |> toUpperCase")
                .example("data |> JSON.stringify |> console.log"),
            
            // 带参数的管道操作符
            SyntaxBuilder("pipe-with-args")
                .priority(145)
                .pattern(R"(([^|]+)\s*\|>\s*([a-zA-Z_]\w*)\s*\(([^)]*)\))")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string value = result.captures.at("1");
                    std::string func = result.captures.at("2");
                    std::string args = result.captures.at("3");
                    
                    value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
                    
                    // 如果有额外参数，value 作为第一个参数
                    if (!args.empty()) {
                        return func + "(" + value + ", " + args + ")";
                    } else {
                        return func + "(" + value + ")";
                    }
                })
                .example("numbers |> filter(x => x > 0) |> map(x => x * 2)"),
            
            // 链式管道（多个管道连续使用）
            SyntaxBuilder("chain-pipe")
                .priority(140)
                .scan([this](ScanContext* ctx) -> std::vector<ScanResult> {
                    std::vector<ScanResult> results;
                    std::string code = ctx->getCode();
                    size_t pos = ctx->getPosition();
                    
                    // 查找包含多个 |> 的表达式
                    std::regex chainRegex(R"(([^|;{}]+(?:\|>[^|;{}]+)+))");
                    auto begin = std::sregex_iterator(code.begin() + pos, code.end(), chainRegex);
                    auto end = std::sregex_iterator();
                    
                    for (auto it = begin; it != end; ++it) {
                        ScanResult result;
                        result.start = pos + it->position();
                        result.end = result.start + it->length();
                        result.content = it->str();
                        results.push_back(result);
                    }
                    
                    return results;
                })
                .generate([this](const ScanResult& result, GenerateContext* ctx) {
                    return processChainedPipes(result.content);
                }),
            
            // 异步管道 |>>
            SyntaxBuilder("async-pipe")
                .priority(135)
                .pattern(R"(([^|]+)\s*\|>>\s*([a-zA-Z_]\w*))")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string value = result.captures.at("1");
                    std::string func = result.captures.at("2");
                    
                    value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
                    
                    // 生成异步管道代码
                    return "(await " + func + "(" + value + "))";
                })
                .example("data |>> fetchDetails |>> processAsync"),
            
            // 错误处理管道 |?>
            SyntaxBuilder("safe-pipe")
                .priority(130)
                .pattern(R"(([^|]+)\s*\|\?>\s*([a-zA-Z_]\w*))")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string value = result.captures.at("1");
                    std::string func = result.captures.at("2");
                    
                    value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
                    
                    // 生成安全管道代码（捕获错误）
                    std::string varName = ctx->uniqueVar("safePipe");
                    
                    return "(() => { try { return " + func + "(" + value + 
                           "); } catch(e) { return null; } })()";
                })
                .example("userInput |?> parseInt |?> validateRange")
        };
    }
    
    void runtime(RuntimeBuilder& builder) override {
        // 添加一些实用的管道函数
        builder.addFunction("tap", R"(
            // 用于调试的 tap 函数
            function tap(fn) {
                return function(value) {
                    fn(value);
                    return value;
                };
            }
        )");
        
        builder.addFunction("when", R"(
            // 条件管道
            function when(predicate, fn) {
                return function(value) {
                    return predicate(value) ? fn(value) : value;
                };
            }
        )");
        
        builder.addFunction("unless", R"(
            // 反向条件管道
            function unless(predicate, fn) {
                return function(value) {
                    return !predicate(value) ? fn(value) : value;
                };
            }
        )");
        
        builder.addFunction("tryCatch", R"(
            // 错误处理管道
            function tryCatch(fn, errorHandler) {
                return function(value) {
                    try {
                        return fn(value);
                    } catch (error) {
                        return errorHandler ? errorHandler(error, value) : null;
                    }
                };
            }
        )");
        
        // 添加示例代码
        builder.addInitCode(R"(
            // 管道操作符使用示例
            if (typeof window !== 'undefined' && window.console) {
                console.log('%c🚀 Pipeline Module Loaded', 'color: #4a90e2; font-weight: bold');
                console.log('Try: "hello world" |> toUpperCase |> console.log');
            }
        )");
    }
    
private:
    // 处理链式管道
    std::string processChainedPipes(const std::string& expression) {
        std::vector<std::string> parts;
        std::string current;
        size_t i = 0;
        
        // 解析管道表达式
        while (i < expression.length()) {
            if (i < expression.length() - 1 && 
                expression[i] == '|' && expression[i + 1] == '>') {
                parts.push_back(current);
                current.clear();
                i += 2;
                
                // 跳过 |> 后的空格
                while (i < expression.length() && std::isspace(expression[i])) {
                    i++;
                }
            } else {
                current += expression[i];
                i++;
            }
        }
        
        if (!current.empty()) {
            parts.push_back(current);
        }
        
        // 构建嵌套的函数调用
        if (parts.empty()) return expression;
        
        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); i++) {
            std::string func = parts[i];
            
            // 去除函数名两端的空格
            func = std::regex_replace(func, std::regex("^\\s+|\\s+$"), "");
            
            // 检查是否有参数
            size_t parenPos = func.find('(');
            if (parenPos != std::string::npos) {
                // 有参数的情况
                std::string funcName = func.substr(0, parenPos);
                std::string args = func.substr(parenPos + 1);
                
                // 去除最后的 )
                if (!args.empty() && args.back() == ')') {
                    args.pop_back();
                }
                
                if (!args.empty()) {
                    result = funcName + "(" + result + ", " + args + ")";
                } else {
                    result = funcName + "(" + result + ")";
                }
            } else {
                // 无参数的情况
                result = func + "(" + result + ")";
            }
        }
        
        return result;
    }
};

// 导出函数
extern "C" {
    CJmodModule* createModule() {
        return new PipelineModule();
    }
    
    const char* getModuleName() {
        return "pipeline";
    }
    
    const char* getModuleVersion() {
        return "1.0.0";
    }
    
    const char* getModuleDescription() {
        return "Elegant pipeline operators for functional data transformation";
    }
}

} // namespace cjmod
} // namespace chtl