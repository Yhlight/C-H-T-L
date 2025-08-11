#include "CJmod/CJmodCorrect.h"

namespace chtl {
namespace cjmod {

/**
 * Pipeline CJmod Module
 * 
 * 添加管道操作符语法，实现函数式编程风格
 * 
 * 新语法：
 * 1. value |> func        - 管道操作符
 * 2. value |> func1 |> func2  - 链式管道
 * 3. arr |>> func         - 数组映射管道
 * 4. arr |?> func         - 数组过滤管道
 */
class PipelineModule : public ICJmod {
public:
    std::string getName() const override { 
        return "pipeline"; 
    }
    
    std::string getVersion() const override { 
        return "1.0.0"; 
    }
    
    std::vector<std::string> getDependencies() const override {
        return {};  // 无依赖
    }
    
    std::vector<ScanCutRule> getScanCutRules() const override {
        return {
            // 1. 基本管道操作符: value |> func
            // 转换为: func(value)
            {
                "pipe-operator",
                std::regex(R"(([^|]+)\s*\|>\s*(\w+))"),
                "$2($1)",
                100  // 高优先级
            },
            
            // 2. 带参数的管道: value |> func(arg)
            // 转换为: func(value, arg)
            {
                "pipe-with-args",
                std::regex(R"(([^|]+)\s*\|>\s*(\w+)\s*\(([^)]*)\))"),
                "$2($1, $3)",
                95
            },
            
            // 3. 数组映射管道: arr |>> func
            // 转换为: arr.map(func)
            {
                "array-map-pipe",
                std::regex(R"(([^|]+)\s*\|>>\s*(\w+))"),
                "$1.map($2)",
                90
            },
            
            // 4. 数组过滤管道: arr |?> func  
            // 转换为: arr.filter(func)
            {
                "array-filter-pipe",
                std::regex(R"(([^|]+)\s*\|[?]>\s*(\w+))"),
                "$1.filter($2)",
                90
            },
            
            // 5. 组合函数定义: func1 >> func2
            // 转换为: (x) => func2(func1(x))
            {
                "function-composition",
                std::regex(R"((\w+)\s*>>\s*(\w+))"),
                "(x) => $2($1(x))",
                80
            },
            
            // 6. 部分应用语法: func(?, arg)
            // 转换为: (x) => func(x, arg)
            {
                "partial-application",
                std::regex(R"((\w+)\s*\(\s*\?\s*,\s*([^)]+)\))"),
                "(x) => $1(x, $2)",
                70
            }
        };
    }
    
    std::vector<RuntimeInjection> getRuntimeInjections() const override {
        return {
            {
                R"(
// Pipeline CJmod Runtime Utilities

// 管道辅助函数
window.pipe = function(...funcs) {
    return (value) => funcs.reduce((v, f) => f(v), value);
};

// 组合函数
window.compose = function(...funcs) {
    return pipe(...funcs.reverse());
};

// 柯里化辅助
window.curry = function(fn) {
    return function curried(...args) {
        if (args.length >= fn.length) {
            return fn.apply(this, args);
        } else {
            return function(...nextArgs) {
                return curried.apply(this, args.concat(nextArgs));
            };
        }
    };
};

// 常用的函数式工具
window.tap = function(fn) {
    return function(value) {
        fn(value);
        return value;
    };
};

window.identity = function(x) { return x; };

window.constant = function(value) {
    return function() { return value; };
};

// 数组工具
window.flatten = function(arr) {
    return arr.flat(Infinity);
};

window.unique = function(arr) {
    return [...new Set(arr)];
};

window.chunk = function(size) {
    return function(arr) {
        const chunks = [];
        for (let i = 0; i < arr.length; i += size) {
            chunks.push(arr.slice(i, i + size));
        }
        return chunks;
    };
};

// 数学工具
window.add = curry((a, b) => a + b);
window.subtract = curry((a, b) => a - b);
window.multiply = curry((a, b) => a * b);
window.divide = curry((a, b) => a / b);

// 字符串工具  
window.toUpperCase = (str) => str.toUpperCase();
window.toLowerCase = (str) => str.toLowerCase();
window.trim = (str) => str.trim();
window.split = curry((sep, str) => str.split(sep));
window.join = curry((sep, arr) => arr.join(sep));

// 逻辑工具
window.not = (x) => !x;
window.and = curry((a, b) => a && b);
window.or = curry((a, b) => a || b);

// 比较工具
window.equals = curry((a, b) => a === b);
window.gt = curry((a, b) => a > b);
window.lt = curry((a, b) => a < b);
window.gte = curry((a, b) => a >= b);
window.lte = curry((a, b) => a <= b);
)",
                "before"  // 在用户代码之前注入
            }
        };
    }
    
    std::map<std::string, std::string> getOverrides() const override {
        // 不覆盖任何官方语法
        return {};
    }
};

// 注册函数（供 CJmodLoader 使用）
extern "C" std::shared_ptr<ICJmod> createPipelineModule() {
    return std::make_shared<PipelineModule>();
}

} // namespace cjmod
} // namespace chtl