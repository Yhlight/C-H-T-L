# CJMOD (CHTL JavaScript Module) 文档

## 概述

CJMOD是CHTL提供的一种扩展CHTL JS语法的模块系统。与CMOD不同，CJMOD专注于JavaScript语法扩展，允许开发者通过C++接口自由扩展JavaScript语法，创建新的语言特性，而无需修改CHTL编译器源码。

## CJMOD vs CMOD

### 主要区别

| 特性 | CMOD | CJMOD |
|------|------|-------|
| 用途 | CHTL模板和自定义 | JavaScript语法扩展 |
| 主文件要求 | 需要同名主文件 | 无需主文件 |
| 导出控制 | 使用[Export] | 无导出控制 |
| 信息文件 | 基础[Info] | 基础[Info]（不扩展） |
| 文件类型 | .chtl文件 | .cpp/.h文件 |
| 运行时 | 编译时处理 | 动态加载扩展 |

### CJMOD特点

1. **无主文件要求**：src目录下的所有C++文件都会被编译，不需要特定的主文件
2. **简化的Info**：只使用基础的CMODInfo字段，不需要扩展信息
3. **动态扩展**：编译为动态库，运行时加载
4. **专注JS扩展**：专门用于扩展CHTL JS语法

## CJMOD结构

### 标准目录结构

```
ModuleName/
├── src/                # C++源代码
│   ├── Extension1.h    # 可以有多个扩展类
│   ├── Extension1.cpp
│   ├── Extension2.h
│   ├── Extension2.cpp
│   └── Utils.cpp       # 辅助代码
├── info/
│   └── ModuleName.chtl # 信息文件（必须与模块名相同）
└── build/              # 构建输出（自动生成）
    └── ModuleName.so   # 编译后的动态库
```

### 信息文件格式

CJMOD使用标准的[Info]块，不需要特殊扩展：

```chtl
[Info]
{
    name = "AsyncAwait";
    version = "1.0.0";
    description = "Adds async/await syntax support to CHTL JS";
    author = "CHTL Team";
    license = "MIT";
    category = "js-extension";
    minCHTLVersion = "1.0.0";
    maxCHTLVersion = "2.0.0";
}
```

注意：
- 不使用[JSExport]或[Export]
- 不需要jsVersion等扩展字段
- info文件名必须与模块名相同

## C++ API

### 扩展接口

```cpp
class ICJMODExtension {
public:
    // 获取扩展信息
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    virtual std::string getDescription() const = 0;
    
    // 初始化
    virtual bool initialize(std::shared_ptr<CHTLJSContext> context) = 0;
    
    // 预处理（在解析前）
    virtual std::string preprocess(const std::string& script) = 0;
    
    // 转换（在解析后）
    virtual std::string transform(const std::string& script) = 0;
    
    // 注册函数
    virtual void registerFunctions(std::shared_ptr<ScriptProcessor> processor) = 0;
    
    // 清理
    virtual void cleanup() = 0;
};
```

### 基类

```cpp
class CJMODExtensionBase : public ICJMODExtension {
    // 提供默认实现
    // 派生类只需重写需要的方法
};
```

### 导出宏

```cpp
// 在实现文件末尾使用
CJMOD_EXTENSION_FACTORY(YourExtensionClass)
```

## 创建CJMOD扩展

### 最小示例

```cpp
// MyExtension.h
#include <chtl/CHTLCJMOD.h>

class MyExtension : public chtl::CJMODExtensionBase {
public:
    MyExtension()
        : CJMODExtensionBase("MyExtension", "1.0.0", "My custom extension") {}
    
    // 只重写需要的方法
    std::string transform(const std::string& script) override {
        // 你的转换逻辑
        return script;
    }
};

// MyExtension.cpp
#include "MyExtension.h"

// 导出工厂函数
CJMOD_EXTENSION_FACTORY(MyExtension)
```

### 目录结构示例

```
MyModule/
├── src/
│   ├── MyExtension.h
│   └── MyExtension.cpp    # 不需要MyModule.cpp主文件
├── info/
│   └── MyModule.chtl      # 必须与模块名相同
```

### 示例2：管道操作符

```cpp
class PipelineExtension : public CJMODExtensionBase {
public:
    std::string transform(const std::string& script) override {
        // 转换 value |> func 为 func(value)
        std::regex pipeline(R"(([^|]+)\s*\|>\s*([^|;]+))");
        
        std::string result = script;
        std::smatch match;
        
        while (std::regex_search(result, match, pipeline)) {
            std::string value = trim(match[1]);
            std::string func = trim(match[2]);
            std::string replacement = func + "(" + value + ")";
            
            result = result.substr(0, match.position()) + 
                    replacement + 
                    result.substr(match.position() + match.length());
        }
        
        return result;
    }
};
```

### 示例3：响应式编程

```cpp
class ReactiveExtension : public CJMODExtensionBase {
public:
    void registerFunctions(std::shared_ptr<ScriptProcessor> processor) override {
        // 响应式对象
        processor->registerFunction("reactive",
            [](const std::vector<std::string>& args) -> std::string {
                return "new Proxy(" + args[0] + ", {"
                       "set: function(obj, prop, value) {"
                       "  obj[prop] = value;"
                       "  notifyObservers(prop, value);"
                       "  return true;"
                       "}})";
            });
        
        // 计算属性
        processor->registerFunction("computed",
            [](const std::vector<std::string>& args) -> std::string {
                return "(function() { "
                       "let cache = null; "
                       "return function() { "
                       "  if (cache === null) cache = (" + args[0] + ")(); "
                       "  return cache; "
                       "}; "
                       "})()";
            });
    }
};
```

## 使用CJMOD

### 在CHTL中导入

```chtl
// 导入整个CJMOD
[Import] @CJmod from AsyncAwait

// 使用扩展的语法
script
{
    async function loadData() {
        const response = await fetch('/api/data');
        return await response.json();
    }
    
    {{button}}->addEventListener('click', async () => {
        const data = await loadData();
        {{#result}}->textContent = data.message;
    });
}
```

### 管道操作符示例

```chtl
[Import] @CJmod from Pipeline

script
{
    const double = x => x * 2;
    const add10 = x => x + 10;
    const toString = x => x.toString();
    
    // 使用管道操作符
    const result = 5 |> double |> add10 |> toString;
    // 转换为: toString(add10(double(5)))
}
```

## 构建和打包

### 使用CJMODBuilder

```cpp
CJMODBuilder builder(context);
builder.setSourcePath("/path/to/source");
builder.setOutputPath("/path/to/output");

// 从模板创建
builder.buildFromTemplate("MyExtension", "syntax");

// 或构建现有模块
builder.build("MyExtension");
```

### 手动构建

```bash
# 编译扩展
g++ -std=c++17 -fPIC -shared \
    -I/path/to/chtl/include \
    MyExtension.cpp \
    -o MyExtension.so

# 打包为.cjmod
chtl-pack --type cjmod MyExtension/
```

## 高级特性

### 1. 状态管理

CJMOD扩展可以维护全局状态：

```cpp
class StatefulExtension : public CJMODExtensionBase {
private:
    std::unordered_map<std::string, std::string> state;
    
public:
    void registerFunctions(std::shared_ptr<ScriptProcessor> processor) override {
        processor->registerFunction("setState",
            [this](const std::vector<std::string>& args) -> std::string {
                if (args.size() >= 2) {
                    state[args[0]] = args[1];
                }
                return "undefined";
            });
    }
};
```

### 2. 语法检测

扩展可以影响脚本类型检测：

```cpp
// 在ScriptProcessor中
if (customSyntaxDetected) {
    return ScriptType::CHTLJS;
}
```

### 3. 链式转换

多个CJMOD可以串联工作：

```chtl
[Import] @CJmod from AsyncAwait
[Import] @CJmod from Pipeline
[Import] @CJmod from Reactive

script
{
    // 组合使用多种扩展
    const data = await fetch('/api') 
        |> response => response.json()
        |> reactive;
}
```

## 最佳实践

### 1. 性能考虑
- 避免在预处理器中进行复杂的正则匹配
- 缓存编译结果
- 使用增量转换

### 2. 兼容性
- 保持向后兼容
- 提供降级方案
- 明确版本依赖

### 3. 错误处理
- 提供清晰的错误信息
- 验证输入参数
- 优雅降级

### 4. 文档
- 为每个扩展函数提供JSDoc
- 包含使用示例
- 说明限制和边界情况

## 调试

### 启用调试输出

```cpp
class DebugExtension : public CJMODExtensionBase {
public:
    std::string preprocess(const std::string& script) override {
        if (debugMode) {
            std::cerr << "Preprocessing: " << script << std::endl;
        }
        return script;
    }
};
```

### 使用日志

```cpp
processor->registerFunction("__debug__",
    [](const std::vector<std::string>& args) -> std::string {
        return "console.log('[CJMOD Debug]', " + 
               join(args, ", ") + ")";
    });
```

## 限制

1. **安全性**：CJMOD运行在编译时，需要信任扩展代码
2. **复杂度**：复杂的语法转换可能影响编译性能
3. **调试**：转换后的代码可能难以调试
4. **兼容性**：需要考虑与其他CJMOD的交互

## 总结

CJMOD为CHTL JS提供了强大的扩展能力，使得开发者可以：
- 创建新的语法特性
- 优化代码性能
- 实现领域特定语言
- 分享和重用扩展

通过标准化的接口和模块系统，CJMOD让JavaScript语法扩展变得简单而强大。