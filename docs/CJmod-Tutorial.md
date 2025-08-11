# CJmod 开发教程 - 创建新的 JavaScript 语法

## 概述

CJmod 允许你通过简单的文本替换规则为 CHTL JS 添加新的语法。本教程将指导你创建自己的 CJmod 模块。

## 步骤 1: 理解 CJmod 的工作原理

CJmod 在 CHTL JS 编译阶段工作，使用正则表达式扫描和替换 JavaScript 代码。

```
CHTL 源码 → CHTL 编译器 → JavaScript 代码 → CJmod 处理 → 最终 JavaScript
```

## 步骤 2: 创建基本的 CJmod 模块

### 示例：创建 "空值合并" 语法

我们将创建一个模块，添加 `??` 操作符（类似于 JavaScript 的 nullish coalescing）。

```cpp
#include "CJmod/CJmodCorrect.h"

namespace chtl {
namespace cjmod {

class NullishModule : public ICJmod {
public:
    std::string getName() const override { 
        return "nullish"; 
    }
    
    std::string getVersion() const override { 
        return "1.0.0"; 
    }
    
    std::vector<ScanCutRule> getScanCutRules() const override {
        return {
            // value ?? defaultValue
            // 转换为: (value !== null && value !== undefined) ? value : defaultValue
            {
                "nullish-coalescing",
                std::regex(R"(([^?]+)\s*\?\?\s*([^;]+))"),
                "($1 !== null && $1 !== undefined) ? $1 : $2",
                100
            }
        };
    }
    
    std::vector<RuntimeInjection> getRuntimeInjections() const override {
        return {};  // 这个模块不需要运行时代码
    }
};

} // namespace cjmod
} // namespace chtl
```

## 步骤 3: 理解 ScanCutRule 结构

每个扫描切割规则包含：

```cpp
struct ScanCutRule {
    std::string name;           // 规则名称
    std::regex pattern;         // 匹配模式
    std::string replacement;    // 替换字符串
    int priority;              // 优先级（越高越先执行）
    std::function<bool(const std::string&)> validator;  // 可选验证函数
};
```

### 正则表达式捕获组

- `$1`, `$2`, `$3`... 代表捕获组
- 使用括号 `()` 创建捕获组
- 例如：`(\w+)` 捕获一个或多个字母数字字符

## 步骤 4: 添加更复杂的语法

### 示例：模式匹配语法

```cpp
class PatternMatchModule : public ICJmod {
public:
    std::string getName() const override { return "pattern-match"; }
    std::string getVersion() const override { return "1.0.0"; }
    
    std::vector<ScanCutRule> getScanCutRules() const override {
        return {
            // match value {
            //   case pattern1: result1
            //   case pattern2: result2
            //   default: defaultResult
            // }
            {
                "match-expression",
                std::regex(R"(match\s+(\w+)\s*\{)"),
                "(function() { const _value = $1; switch(true) {",
                100
            },
            
            // case pattern: result
            {
                "case-pattern",
                std::regex(R"(case\s+([^:]+):\s*([^;]+);)"),
                "case (_value === $1): return $2;",
                90
            },
            
            // default: result
            {
                "default-pattern",
                std::regex(R"(default:\s*([^}]+)\})"),
                "default: return $1; }})();",
                80
            }
        };
    }
    
    std::vector<RuntimeInjection> getRuntimeInjections() const override {
        return {};
    }
};
```

## 步骤 5: 添加运行时支持

有些语法需要运行时函数支持：

```cpp
class RangeModule : public ICJmod {
public:
    std::string getName() const override { return "range"; }
    std::string getVersion() const override { return "1.0.0"; }
    
    std::vector<ScanCutRule> getScanCutRules() const override {
        return {
            // 1..10  转换为  range(1, 10)
            {
                "range-syntax",
                std::regex(R"((\d+)\.\.(\d+))"),
                "range($1, $2)",
                100
            },
            
            // 1...10  转换为  range(1, 10, true) (exclusive)
            {
                "range-exclusive",
                std::regex(R"((\d+)\.\.\.(\d+))"),
                "range($1, $2, true)",
                100
            }
        };
    }
    
    std::vector<RuntimeInjection> getRuntimeInjections() const override {
        return {
            {
                R"(
window.range = function(start, end, exclusive = false) {
    const result = [];
    const limit = exclusive ? end - 1 : end;
    for (let i = start; i <= limit; i++) {
        result.push(i);
    }
    return result;
};
)",
                "before"  // 在用户代码之前注入
            }
        };
    }
};
```

## 步骤 6: 测试你的语法

创建测试文件：

```chtl
[Import] @CJmod from "./my-module.cjmod";

div {
    script {
        // 使用新语法
        let value = null;
        let result = value ?? "default";  // nullish coalescing
        
        // 范围语法
        let numbers = 1..10;
        let exclusive = 1...10;
        
        // 模式匹配
        let type = match typeof value {
            case "string": "It's a string"
            case "number": "It's a number"
            default: "Unknown type"
        }
    }
}
```

## 最佳实践

### 1. 优先级设置
- 100-80: 新操作符和语法结构
- 70-50: 函数调用转换
- 40-20: 细微的语法调整

### 2. 避免冲突
- 测试你的正则表达式不会匹配意外的代码
- 使用验证函数来限制替换的范围

### 3. 性能考虑
- 复杂的正则表达式会影响编译速度
- 尽量使用简单、精确的模式

### 4. 错误处理
```cpp
// 使用验证函数确保只在合适的上下文中应用规则
{
    "my-rule",
    std::regex(pattern),
    replacement,
    100,
    [](const std::string& context) {
        // 只在特定条件下应用此规则
        return context.find("enableMyFeature") != std::string::npos;
    }
}
```

## 完整示例：创建 "守卫语句" 语法

```cpp
class GuardModule : public ICJmod {
public:
    std::string getName() const override { return "guard"; }
    std::string getVersion() const override { return "1.0.0"; }
    
    std::vector<ScanCutRule> getScanCutRules() const override {
        return {
            // guard condition else return value;
            // 转换为: if (!(condition)) return value;
            {
                "guard-return",
                std::regex(R"(guard\s+([^;]+?)\s+else\s+return\s+([^;]+);)"),
                "if (!($1)) return $2;",
                100
            },
            
            // guard condition else { ... }
            // 转换为: if (!(condition)) { ... }
            {
                "guard-block",
                std::regex(R"(guard\s+([^;]+?)\s+else\s*\{)"),
                "if (!($1)) {",
                100
            },
            
            // unless condition { ... }
            // 转换为: if (!(condition)) { ... }
            {
                "unless-block",
                std::regex(R"(unless\s+\(([^)]+)\)\s*\{)"),
                "if (!($1)) {",
                90
            }
        };
    }
    
    std::vector<RuntimeInjection> getRuntimeInjections() const override {
        return {};
    }
};
```

使用示例：
```javascript
function divide(a, b) {
    guard b !== 0 else return null;
    return a / b;
}

unless (user.isLoggedIn) {
    redirectToLogin();
}
```

## 发布你的 CJmod

1. 将模块编译为共享库（.so/.dll）
2. 创建描述文件 `module.json`：
```json
{
    "name": "my-syntax",
    "version": "1.0.0",
    "description": "My custom syntax extensions",
    "entry": "./my-syntax.cjmod",
    "author": "Your Name"
}
```

3. 发布到 CJmod 仓库或分享给其他人

## 总结

通过 CJmod，你可以：
- 添加新的操作符
- 创建语法糖
- 实现 DSL（领域特定语言）
- 扩展 JavaScript 功能

记住：CJmod 的强大在于其简单性 - 通过文本替换实现语法扩展，让每个人都能创造自己的编程体验！