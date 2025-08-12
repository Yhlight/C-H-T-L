#include "CJmod/CJmodCore.h"

namespace chtl {
namespace cjmod {

class ReactiveModule : public CJmodModule {
public:
    std::vector<SyntaxBuilder> syntax() override {
        std::vector<SyntaxBuilder> rules;
        
        // 响应式赋值 :=
        rules.push_back(
            SyntaxBuilder("reactive-assignment")
                .priority(200)
                .pattern(R"((\w+)\s*:=\s*([^;]+);?)")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string varName = result.captures.at("1");
                    std::string value = result.captures.at("2");
                    
                    std::stringstream code;
                    code << "const " << varName << " = CHTL.reactive(" << value << ")";
                    
                    // 注入运行时依赖
                    ctx->runtime().require("reactive");
                    
                    return code.str();
                })
        );
        
        // 计算属性 =>
        rules.push_back(
            SyntaxBuilder("computed-property")
                .priority(190)
                .scan([](ScanContext* ctx) {
                    std::vector<ScanResult> results;
                    
                    // 查找计算属性模式: identifier => { ... }
                    size_t pos = 0;
                    while ((pos = ctx->findNext("=>", pos)) != std::string::npos) {
                        // 检查是否在字符串或注释中
                        if (ctx->isInString() || ctx->isInComment()) {
                            pos += 2;
                            continue;
                        }
                        
                        // 向前查找标识符
                        size_t idStart = pos;
                        while (idStart > 0 && std::isspace(ctx->getCode()[ctx->getPosition() + idStart - 1])) {
                            idStart--;
                        }
                        
                        size_t idEnd = idStart;
                        while (idStart > 0 && std::isalnum(ctx->getCode()[ctx->getPosition() + idStart - 1])) {
                            idStart--;
                        }
                        
                        if (idStart < idEnd) {
                            std::string identifier = ctx->substring(idStart, idEnd - idStart);
                            
                            // 查找函数体
                            size_t funcStart = pos + 2;
                            while (funcStart < ctx->getLength() && 
                                   std::isspace(ctx->getCode()[ctx->getPosition() + funcStart])) {
                                funcStart++;
                            }
                            
                            if (ctx->matches("{", funcStart)) {
                                size_t funcEnd = ctx->findMatching('{', '}', funcStart);
                                if (funcEnd != std::string::npos) {
                                    ScanResult result;
                                    result.start = idStart;
                                    result.end = funcStart + funcEnd + 1;
                                    result.content = ctx->substring(idStart, result.end - idStart);
                                    result.captures["id"] = identifier;
                                    result.captures["body"] = ctx->substring(funcStart, funcEnd + 1);
                                    
                                    results.push_back(result);
                                    pos = result.end;
                                    continue;
                                }
                            }
                        }
                        
                        pos += 2;
                    }
                    
                    return results;
                })
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string id = result.captures.at("id");
                    std::string body = result.captures.at("body");
                    
                    std::stringstream code;
                    code << "const " << id << " = CHTL.computed(() => " << body << ")";
                    
                    ctx->runtime().require("computed");
                    
                    return code.str();
                })
        );
        
        // watch 语法
        rules.push_back(
            SyntaxBuilder("watch")
                .priority(180)
                .pattern(R"(watch\s+(\w+)\s*->\s*\{([^}]*)\})")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string target = result.captures.at("1");
                    std::string handler = result.captures.at("2");
                    
                    std::stringstream code;
                    code << "CHTL.watch(" << target << ", function(newVal, oldVal) {\n";
                    code << handler << "\n";
                    code << "})";
                    
                    ctx->runtime().require("watch");
                    
                    return code.str();
                })
        );
        
        return rules;
    }
    
    void runtime(RuntimeBuilder& builder) override {
        // 响应式系统运行时
        builder.addFunction("reactive", R"(function(initialValue) {
            let value = initialValue;
            const listeners = new Set();
            
            const reactive = {
                get value() {
                    return value;
                },
                set value(newValue) {
                    const oldValue = value;
                    value = newValue;
                    listeners.forEach(fn => fn(newValue, oldValue));
                },
                subscribe(fn) {
                    listeners.add(fn);
                    return () => listeners.delete(fn);
                },
                valueOf() {
                    return value;
                },
                toString() {
                    return String(value);
                }
            };
            
            return reactive;
        })");
        
        // 计算属性
        builder.addFunction("computed", R"(function(computeFn) {
            const reactive = CHTL.reactive(computeFn());
            
            // TODO: 实现依赖追踪
            
            return reactive;
        })");
        
        // 监听器
        builder.addFunction("watch", R"(function(target, handler) {
            if (target && typeof target.subscribe === 'function') {
                return target.subscribe(handler);
            }
            console.warn('Cannot watch non-reactive value:', target);
        })");
        
        // 扩展 CHTL 命名空间
        builder.addInitCode("CHTL.modules.reactive = { version: '1.0.0' };");
    }
};

} // namespace cjmod
} // namespace chtl

// 导出函数
extern "C" {
    chtl::cjmod::CJmodModule* createModule() {
        return new chtl::cjmod::ReactiveModule();
    }
    
    void destroyModule(chtl::cjmod::CJmodModule* module) {
        delete module;
    }
}