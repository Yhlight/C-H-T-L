# CJMOD 开发指南

CJMOD（CHTL JavaScript Module）是 CHTL 提供的 JavaScript 扩展机制，允许开发者使用 C++ 扩展 CHTL JS 的功能。

## 目录

1. [快速开始](#快速开始)
2. [项目结构](#项目结构)
3. [API 设计](#api-设计)
4. [内存管理](#内存管理)
5. [错误处理](#错误处理)
6. [性能优化](#性能优化)
7. [调试技巧](#调试技巧)
8. [发布流程](#发布流程)
9. [最佳实践](#最佳实践)

## 快速开始

### 1. 创建基本的 CJMOD

```cpp
#include "CHTLJSExtension.h"
#include <string>
#include <sstream>

namespace chtl {
namespace js {

// 创建扩展类
class MyExtension : public Extension {
public:
    MyExtension() : Extension("MyModule") {}
    
    void initialize() override {
        // 注册一个简单的函数
        function("greet", [](const Array& args) -> Value {
            auto name = getArg<std::string>(args, 0, "World");
            return "Hello, " + name + "!";
        });
        
        // 注册一个返回数字的函数
        function("add", [](const Array& args) -> Value {
            double a = getArg<double>(args, 0, 0.0);
            double b = getArg<double>(args, 1, 0.0);
            return a + b;
        });
    }
};

// 设置导出
struct MyExporter {
    MyExporter() {
        CJMODExporter::setHandlers([]() {
            auto ext = std::make_shared<MyExtension>();
            ExtensionManager::getInstance().registerExtension(ext);
        });
    }
};

static MyExporter exporter;

} // namespace js
} // namespace chtl
```

### 2. 在 CHTL 中使用

```chtl
-- 导入 CJMOD
[Import] @CJmod from MyModule

script {
    -- 调用函数
    var message = greet("CHTL");
    console.log(message);  -- 输出: Hello, CHTL!
    
    var result = add(10, 20);
    console.log(result);   -- 输出: 30
}
```

## 项目结构

```
MyModule/
├── src/
│   ├── mymodule.cpp      # 主实现文件
│   └── mymodule.h        # 头文件（可选）
└── info/
    └── MyModule.chtl     # 模块信息文件
```

### info/MyModule.chtl 示例

```chtl
-- MyModule CJMOD 信息

[Info]
{
    name = "MyModule";
    version = "1.0.0";
    description = "我的 CHTL JS 扩展模块";
    author = "Your Name";
    license = "MIT";
    dependencies = "";
    category = "extension";
    minCHTLVersion = "1.0.0";
    maxCHTLVersion = "2.0.0";
}
```

## API 设计

### 扩展类结构

```cpp
class MyExtension : public Extension {
public:
    MyExtension() : Extension("ModuleName") {}
    
    void initialize() override {
        // 在这里注册所有功能
    }
};
```

### 注册函数

使用 `function` 方法注册函数：

```cpp
void initialize() override {
    // 基本函数
    function("functionName", [](const Array& args) -> Value {
        // 函数实现
        return "result";
    });
    
    // 带参数处理的函数
    function("processData", [](const Array& args) -> Value {
        auto input = getArg<std::string>(args, 0);
        auto options = getArg<double>(args, 1, 1.0);
        
        // 处理逻辑
        return processedResult;
    });
}
```

### 参数获取

使用 `getArg` 模板函数安全地获取参数：

```cpp
// 获取字符串参数，默认值为 "default"
auto str = getArg<std::string>(args, 0, "default");

// 获取数字参数，默认值为 0.0
auto num = getArg<double>(args, 1, 0.0);

// 获取布尔参数，默认值为 false
auto flag = getArg<bool>(args, 2, false);
```

### 返回 JavaScript 代码

CJMOD 函数通常返回要执行的 JavaScript 代码字符串：

```cpp
function("createAnimation", [](const Array& args) -> Value {
    auto element = getArg<std::string>(args, 0);
    auto duration = getArg<double>(args, 1, 1000.0);
    
    std::stringstream js;
    js << "(function() {"
       << "  var el = " << element << ";"
       << "  el.style.transition = 'all " << duration << "ms ease';"
       << "  el.style.transform = 'scale(1.2)';"
       << "})()";
    
    return js.str();
});
```

## 内存管理

### 智能指针使用

始终使用智能指针管理扩展对象：

```cpp
auto extension = std::make_shared<MyExtension>();
ExtensionManager::getInstance().registerExtension(extension);
```

### 避免内存泄漏

- 使用 RAII 原则
- 避免裸指针
- 正确处理异常

## 错误处理

### 参数验证

```cpp
function("safeDivide", [](const Array& args) -> Value {
    if (args.size() < 2) {
        return "throw new Error('需要两个参数')";
    }
    
    auto a = getArg<double>(args, 0);
    auto b = getArg<double>(args, 1);
    
    if (b == 0) {
        return "throw new Error('除数不能为零')";
    }
    
    return std::to_string(a / b);
});
```

### 异常处理

```cpp
function("riskyOperation", [](const Array& args) -> Value {
    try {
        // 可能抛出异常的操作
        return performOperation(args);
    } catch (const std::exception& e) {
        std::stringstream js;
        js << "throw new Error('" << e.what() << "')";
        return js.str();
    }
});
```

## 性能优化

### 1. 缓存常用结果

```cpp
class OptimizedExtension : public Extension {
private:
    std::unordered_map<std::string, std::string> cache_;
    
public:
    void initialize() override {
        function("cachedOperation", [this](const Array& args) -> Value {
            auto key = getArg<std::string>(args, 0);
            
            auto it = cache_.find(key);
            if (it != cache_.end()) {
                return it->second;
            }
            
            auto result = expensiveOperation(key);
            cache_[key] = result;
            return result;
        });
    }
};
```

### 2. 避免频繁的字符串拼接

使用 `std::stringstream` 而不是 `+` 操作符：

```cpp
// 好的做法
std::stringstream js;
js << "var result = " << value << ";";
return js.str();

// 避免
return "var result = " + std::to_string(value) + ";";
```

## 调试技巧

### 1. 日志输出

```cpp
function("debugFunction", [](const Array& args) -> Value {
    auto input = getArg<std::string>(args, 0);
    
    // 在 JavaScript 控制台输出调试信息
    std::stringstream js;
    js << "console.log('[CJMOD Debug] Input:', '" << input << "');";
    js << "console.log('[CJMOD Debug] Args count:', " << args.size() << ");";
    
    // 实际功能
    js << "// 功能实现";
    
    return js.str();
});
```

### 2. 断言和检查

```cpp
function("validateInput", [](const Array& args) -> Value {
    if (args.empty()) {
        return "console.error('[CJMOD] 错误：没有提供参数')";
    }
    
    // 类型检查
    if (args[0].type() != typeid(std::string)) {
        return "console.error('[CJMOD] 错误：参数类型不正确')";
    }
    
    // 正常处理
    return processInput(args);
});
```

## 发布流程

### 1. 编译 CJMOD

```bash
# 使用提供的打包脚本
./scripts/pack_cjmod.sh module/MyModule

# 或手动编译
cd module/MyModule
mkdir build && cd build
cmake ..
make
```

### 2. 测试

创建测试文件 `test.chtl`：

```chtl
[Import] @CJmod from MyModule

script {
    -- 测试所有功能
    var testResults = [];
    
    -- 测试函数1
    testResults.push(myFunction1("test"));
    
    -- 测试函数2
    testResults.push(myFunction2(123));
    
    -- 输出结果
    console.log("测试结果:", testResults);
}
```

### 3. 打包发布

生成的 `.cjmod` 文件包含：
- 编译后的共享库
- 源代码
- 模块信息

## 最佳实践

### 1. 命名规范

- 模块名使用 PascalCase：`MyModule`
- 函数名使用 camelCase：`myFunction`
- 文件名使用小写：`mymodule.cpp`

### 2. 文档注释

```cpp
class WellDocumentedExtension : public Extension {
public:
    void initialize() override {
        // 动画效果：淡入
        // 参数1: 元素选择器
        // 参数2: 持续时间（毫秒，可选，默认400）
        function("fadeIn", [](const Array& args) -> Value {
            // 实现...
        });
    }
};
```

### 3. 版本兼容性

```cpp
void initialize() override {
    // 新版本功能
    function("newFeature", [](const Array& args) -> Value {
        return "// 新功能实现";
    });
    
    // 保持向后兼容
    function("oldFeature", [](const Array& args) -> Value {
        // 调用新功能但保持旧接口
        return "newFeature(" + getArg<std::string>(args, 0) + ")";
    });
}
```

### 4. 模块化设计

将相关功能组织在一起：

```cpp
class UIExtension : public Extension {
public:
    void initialize() override {
        // 动画相关
        registerAnimations();
        
        // DOM 操作相关
        registerDOMHelpers();
        
        // 事件处理相关
        registerEventHandlers();
    }
    
private:
    void registerAnimations() {
        function("fadeIn", /*...*/);
        function("fadeOut", /*...*/);
        function("slideIn", /*...*/);
    }
    
    void registerDOMHelpers() {
        function("addClass", /*...*/);
        function("removeClass", /*...*/);
        function("toggleClass", /*...*/);
    }
    
    void registerEventHandlers() {
        function("on", /*...*/);
        function("off", /*...*/);
        function("once", /*...*/);
    }
};
```

## 高级特性

### 1. 状态管理

```cpp
class StatefulExtension : public Extension {
private:
    struct State {
        int counter = 0;
        std::vector<std::string> history;
    };
    State state_;
    
public:
    void initialize() override {
        function("increment", [this](const Array& args) -> Value {
            state_.counter++;
            return std::to_string(state_.counter);
        });
        
        function("getHistory", [this](const Array& args) -> Value {
            std::stringstream js;
            js << "[";
            for (size_t i = 0; i < state_.history.size(); ++i) {
                if (i > 0) js << ",";
                js << "'" << state_.history[i] << "'";
            }
            js << "]";
            return js.str();
        });
    }
};
```

### 2. 异步操作

```cpp
function("asyncOperation", [](const Array& args) -> Value {
    auto callback = getArg<std::string>(args, 0);
    auto delay = getArg<double>(args, 1, 1000.0);
    
    std::stringstream js;
    js << "setTimeout(function() {"
       << "  " << callback << "('异步操作完成');"
       << "}, " << delay << ")";
    
    return js.str();
});
```

### 3. 复杂数据结构

```cpp
function("createComplexObject", [](const Array& args) -> Value {
    std::stringstream js;
    js << "{"
       << "  data: ["
       << "    { id: 1, name: 'Item 1' },"
       << "    { id: 2, name: 'Item 2' }"
       << "  ],"
       << "  methods: {"
       << "    getData: function() { return this.data; },"
       << "    addItem: function(item) { this.data.push(item); }"
       << "  }"
       << "}";
    
    return js.str();
});
```

## 总结

CJMOD 提供了强大而灵活的方式来扩展 CHTL JS 的功能。通过基于类的接口设计，开发者可以：

- 清晰地组织代码结构
- 安全地处理参数和错误
- 高效地实现复杂功能
- 轻松地维护和扩展模块

遵循本指南的最佳实践，您可以创建高质量、可维护的 CJMOD 扩展。