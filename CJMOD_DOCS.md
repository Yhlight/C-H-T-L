# CJMOD (CHTL JavaScript Module) 文档

## 概述

CJMOD是CHTL提供的一种扩展CHTL JS语法的模块系统。与CMOD不同，CJMOD允许开发者通过C++接口自由扩展JavaScript语法，创建新的语言特性，而无需修改CHTL编译器源码。

## 核心特性

### 1. 语法扩展
- 添加新的语法结构（如async/await、管道操作符）
- 实现DSL（领域特定语言）
- 语法糖转换

### 2. 函数扩展
- 注册自定义JavaScript函数
- 提供运行时功能扩展
- 性能优化的原生实现

### 3. 预处理器
- 在解析前修改脚本
- 宏展开
- 条件编译

### 4. 转换器
- AST级别的代码转换
- 语法降级
- 优化passes

## CJMOD结构

### 标准目录结构

```
ModuleName/
├── src/
│   ├── ModuleName.h      # 扩展头文件
│   ├── ModuleName.cpp    # 扩展实现
│   └── SubModule/        # 子模块（可选）
│       ├── src/
│       └── info/
├── info/
│   └── ModuleName.chtl   # 模块信息和导出表
└── build/                # 构建输出（自动生成）
    └── ModuleName.so     # 编译后的动态库
```

### 信息文件格式

```chtl
[Info]
{
    name = "AsyncAwait";
    version = "1.0.0";
    description = "Adds async/await syntax support to CHTL JS";
    author = "CHTL Team";
    license = "MIT";
    
    // CJMOD特定字段
    jsVersion = "ES6+";           // 支持的JS版本
    syntaxExtensions = "async, await";  // 提供的语法扩展
    requiredHeaders = "coroutine";      // 需要的C++头文件
}

[JSExport]
{
    functions {
        delay: "delay(ms: number): Promise<void>";
        sleep: "sleep(ms: number): Promise<void>";
    }
    
    syntaxes {
        async: "async function|arrow";
        await: "await expression";
    }
    
    operators {
        pipeline: "|>";
    }
}
```

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

### 示例1：异步语法扩展

```cpp
// AsyncAwait.h
class AsyncAwaitExtension : public CJMODExtensionBase {
public:
    AsyncAwaitExtension()
        : CJMODExtensionBase("AsyncAwait", "1.0.0", 
                            "Adds async/await support") {}
    
    std::string preprocess(const std::string& script) override {
        // 标记async函数
        std::regex asyncFunc(R"(async\s+function\s+(\w+))");
        return std::regex_replace(script, asyncFunc, 
                                 "function $1 /* __async__ */");
    }
    
    std::string transform(const std::string& script) override {
        // 转换await为yield
        std::regex awaitExpr(R"(await\s+([^;]+);)");
        return std::regex_replace(script, awaitExpr, 
                                 "yield $1; /* __await__ */");
    }
    
    void registerFunctions(std::shared_ptr<ScriptProcessor> processor) override {
        processor->registerFunction("delay", 
            [](const std::vector<std::string>& args) -> std::string {
                return "new Promise(resolve => setTimeout(resolve, " + 
                       args[0] + "))";
            });
    }
};

// AsyncAwait.cpp
CJMOD_EXTENSION_FACTORY(AsyncAwaitExtension)
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