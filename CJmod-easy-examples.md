# CJmod 简化创建示例

## 1. 最简单的方式 - 使用宏

```cpp
#include "CJmod/CJmodMacros.h"

// 方式 1: 使用 DEFINE_CJMOD 一体化宏
DEFINE_CJMOD("hello-world", "1.0.0",
    CJMOD_DESC("My first CJmod module")
    SYNTAX_SIMPLE("hello", "console.log('Hello, World!')")
    METHOD_SIMPLE("Element", "sayHello", "alert('Hello from ' + this.tagName);")
);

// 方式 2: 使用步骤宏
void createAnimateModule() {
    CJMOD_BEGIN("animate", "1.0.0");
    CJMOD_DESC("Simple animation module");
    
    // 简单语法替换
    SYNTAX_SIMPLE("fadeIn", "this.style.opacity = '1'");
    SYNTAX_SIMPLE("fadeOut", "this.style.opacity = '0'");
    
    // 带转换的语法
    SYNTAX_TRANSFORM("wait\\s+(\\d+)") {
        return "await new Promise(r => setTimeout(r, " + m[1].str() + "))";
    });
    
    // 添加方法
    METHOD_WITH_PARAMS("Element", "fade", "opacity, duration",
        "this.style.transition = `opacity ${duration}ms`;"
        "this.style.opacity = opacity;"
    );
    
    CJMOD_END();
}
```

## 2. 响应式模块 - 3行代码

```cpp
DEFINE_CJMOD("reactive-mini", "1.0.0",
    SYNTAX_SIMPLE(R"((\w+)\s*:=\s*(.+);)", "const $1 = reactive($2);")
    SYNTAX_SIMPLE(R"(watch\s+(\w+)\s*->)", "watch($1, () =>")
    CJMOD_RUNTIME_FILE("reactive-mini.js")
);
```

## 3. 使用预定义模板

```cpp
#include "CJmod/CJmodMacros.h"

// 创建包含常用功能的模块
void createUtilityModule() {
    CJMOD_BEGIN("utils", "1.0.0");
    CJMOD_DESC("Common utilities");
    
    // 使用预定义的语法组
    cjmod::macros::defineDebugSyntax(module);
    cjmod::macros::defineAnimationSyntax(module);
    
    // 添加自定义内容
    SYNTAX_SIMPLE("foreach", "forEach");
    SYNTAX_SIMPLE("is null", "=== null");
    SYNTAX_SIMPLE("is not null", "!== null");
    
    CJMOD_END();
}
```

## 4. 表格式定义

```cpp
// 使用数组批量定义语法
struct SyntaxDef {
    const char* pattern;
    const char* replacement;
};

SyntaxDef syntaxRules[] = {
    { "@@", "document.querySelector" },
    { "!!", "console.log" },
    { "??", "|| " },
    { "=>=>", "async () =>" },
    { nullptr, nullptr }
};

void createFromTable() {
    CJMOD_BEGIN("shortcuts", "1.0.0");
    
    for (int i = 0; syntaxRules[i].pattern; i++) {
        CJMOD_SYNTAX(syntaxRules[i].pattern, syntaxRules[i].replacement);
    }
    
    CJMOD_END();
}
```

## 5. JSON 风格定义

```cpp
// 模拟 JSON 风格的定义
void createJSONStyleModule() {
    auto config = R"({
        "name": "json-style",
        "version": "1.0.0",
        "syntax": {
            "fn": "function",
            "ret": "return",
            "cls": "class"
        },
        "methods": {
            "Element": {
                "show": "this.style.display = 'block'",
                "hide": "this.style.display = 'none'"
            }
        }
    })";
    
    // 解析并创建模块
    CJMOD_BEGIN("json-style", "1.0.0");
    
    // 简化的硬编码版本
    SYNTAX_SIMPLE("fn", "function");
    SYNTAX_SIMPLE("ret", "return");
    SYNTAX_SIMPLE("cls", "class");
    
    METHOD_SIMPLE("Element", "show", "this.style.display = 'block';");
    METHOD_SIMPLE("Element", "hide", "this.style.display = 'none';");
    
    CJMOD_END();
}
```

## 6. 单行模块定义

```cpp
// 极简模块 - 一行定义一个功能
DEFINE_CJMOD("log", "1.0.0", SYNTAX_SIMPLE("log", "console.log"));
DEFINE_CJMOD("jq", "1.0.0", SYNTAX_SIMPLE("$", "document.querySelector"));
DEFINE_CJMOD("hide", "1.0.0", METHOD_SIMPLE("Element", "hide", "this.style.display='none';"));
```

## 7. 批量生成助手函数

```cpp
// 助手函数：快速创建事件处理模块
void createEventModule(const std::string& eventName) {
    std::string moduleName = eventName + "-helper";
    
    CJMOD_BEGIN(moduleName, "1.0.0");
    CJMOD_DESC("Helper for " + eventName + " events");
    
    // on click -> addEventListener('click',
    std::string pattern = "on " + eventName + " ->";
    std::string replace = "addEventListener('" + eventName + "',";
    CJMOD_SYNTAX(pattern, replace);
    
    // 快捷方法
    METHOD_WITH_PARAMS("Element", eventName, "handler",
        ("this.addEventListener('" + eventName + "', handler); return this;").c_str()
    );
    
    CJMOD_END();
}

// 批量创建
void createAllEventModules() {
    const char* events[] = {"click", "hover", "focus", "blur", "change", nullptr};
    
    for (int i = 0; events[i]; i++) {
        createEventModule(events[i]);
    }
}
```

## 8. 使用 Lambda 简化

```cpp
// Lambda 风格定义
auto createModule = [](const std::string& name, auto setupFn) {
    CJMOD_BEGIN(name, "1.0.0");
    setupFn(module);
    CJMOD_END();
};

// 使用
createModule("my-module", [](auto& m) {
    m.syntax("=>", "() =>")
     .syntax("!!", "console.log")
     .method("Element", "flash", "function() { /* flash effect */ }");
});
```

## 9. 继承式创建

```cpp
// 基础模块类
class BaseCJmod {
protected:
    CJmodBuilder builder;
    
public:
    BaseCJmod(const std::string& name) : builder(name, "1.0.0") {}
    
    virtual void setup() = 0;
    
    void build() {
        setup();
        auto module = builder.build();
        CJmodProcessor::getInstance().registerModule(std::move(module));
    }
};

// 具体实现
class MyAnimateModule : public BaseCJmod {
public:
    MyAnimateModule() : BaseCJmod("my-animate") {}
    
    void setup() override {
        builder
            .description("My animation module")
            .syntax("fade", "opacity")
            .syntax("slide", "transform");
    }
};

// 使用
MyAnimateModule().build();
```

## 10. 配置文件驱动

```cpp
// config.cjmod
/*
module: form-tools
version: 1.0.0
syntax:
  - [required, "required: true"]
  - [email, "type: 'email'"]
  - [number, "type: 'number'"]
methods:
  Element:
    - [validate, "return this.checkValidity();"]
*/

// 加载器
void loadFromConfig(const std::string& configFile) {
    // 简化示例 - 实际需要解析配置文件
    CJMOD_BEGIN("form-tools", "1.0.0");
    SYNTAX_SIMPLE("required", "required: true");
    SYNTAX_SIMPLE("email", "type: 'email'");
    METHOD_SIMPLE("Element", "validate", "return this.checkValidity();");
    CJMOD_END();
}
```

## 使用这些简化模块

```chtl
[Import] @CJmod hello-world
[Import] @CJmod shortcuts

body {
    div {
        script {
            // 使用 hello-world 模块
            hello;  // 输出 Hello, World!
            
            // 使用 shortcuts 模块
            !! "Starting app";  // console.log
            const el = @@ "#app";  // document.querySelector
            
            el.sayHello();  // 来自 hello-world 模块
        }
    }
}
```

## 总结

通过这些简化方式，创建 CJmod 变得极其简单：

1. **宏定义** - 减少样板代码
2. **一体化宏** - 一个语句完成整个模块
3. **预定义模板** - 复用常见模式
4. **表格/数组** - 批量定义规则
5. **单行定义** - 极简模块
6. **Lambda** - 函数式风格
7. **继承** - 面向对象风格
8. **配置文件** - 外部化定义

选择最适合你的方式，快速创建强大的 CJmod 扩展！