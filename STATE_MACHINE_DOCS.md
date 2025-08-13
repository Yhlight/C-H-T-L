# CHTL状态机和上下文系统文档

## 概述

根据CHTL语法文档，我们实现了完整的状态机和上下文管理系统，包括：

1. **CHTL状态机** - 管理CHTL语言的解析状态
2. **CHTL上下文** - 管理符号表、作用域、模板等
3. **CHTL JS状态机** - 管理CHTL JavaScript扩展的解析状态
4. **CHTL JS上下文** - 管理DOM引用、事件绑定、动画等

## CHTL状态机 (CHTLStateMachine)

### 状态定义

```cpp
enum class CHTLState {
    INITIAL,                    // 初始状态
    IN_ELEMENT,                 // 在元素内部
    IN_TEXT,                    // 在text块内
    IN_STYLE,                   // 在style块内
    IN_SCRIPT,                  // 在script块内
    IN_TEMPLATE,                // 在[Template]声明内
    IN_CUSTOM,                  // 在[Custom]声明内
    IN_CONFIGURATION,           // 在[Configuration]内
    IN_NAMESPACE,               // 在[Namespace]内
    IN_IMPORT,                  // 在[Import]语句
    IN_ORIGIN,                  // 在[Origin]块内
    // ... 更多状态
};
```

### 使用示例

```cpp
#include "chtl/CHTLStateMachine.h"

chtl::CHTLStateMachine stateMachine;

// 处理元素开始
stateMachine.processEvent(chtl::CHTLEvent::IDENTIFIER);  // div
stateMachine.processEvent(chtl::CHTLEvent::OPEN_BRACE);  // {

// 检查当前状态
if (stateMachine.isInState(chtl::CHTLState::IN_ELEMENT)) {
    // 可以处理元素内容
}

// 处理样式块
stateMachine.processEvent(chtl::CHTLEvent::KEYWORD_STYLE);
stateMachine.processEvent(chtl::CHTLEvent::OPEN_BRACE);

// 检查是否可以使用某个特性
if (stateMachine.canUseFeature("delete")) {
    // 只在特例化块中可以使用delete
}
```

### 状态转换规则

- **INITIAL → IN_ELEMENT**: 遇到标识符（元素名）
- **INITIAL → IN_TEMPLATE**: 遇到[Template]
- **INITIAL → IN_CUSTOM**: 遇到[Custom]
- **IN_ELEMENT → IN_STYLE**: 遇到style关键字
- **IN_ELEMENT → IN_SCRIPT**: 遇到script关键字
- **IN_CUSTOM → IN_SPECIALIZATION**: 遇到{，进入特例化块

## CHTL上下文 (CHTLContext)

### 功能特性

1. **作用域管理**
   - 支持嵌套作用域
   - 符号查找遵循作用域链
   - 支持except约束

2. **符号管理**
   - 注册和查找符号
   - 支持多种符号类型（元素、样式、变量等）
   - 命名空间支持

3. **模板和自定义管理**
   - 模板定义和继承
   - 自定义特例化
   - 属性删除和添加

### 使用示例

```cpp
#include "chtl/CHTLContext.h"

chtl::CHTLContext context;

// 进入新的作用域
context.pushScope(chtl::ScopeType::ELEMENT, "div");

// 注册符号
context.registerSymbol("container", chtl::SymbolType::STYLE);

// 注册模板
auto styleTemplate = std::make_shared<chtl::TemplateDefinition>("DefaultText", "@Style");
styleTemplate->addProperty("color", "black");
styleTemplate->addProperty("font-size", "16px");
context.registerTemplate("@Style", "DefaultText", styleTemplate);

// 查找符号
auto symbol = context.lookupSymbol("container");
if (symbol) {
    // 使用符号
}

// 自动生成类名
std::string autoClass = context.generateAutoClassName("box");  // 返回 "box_1"

// 配置管理
context.setConfigValue("INDEX_INITIAL_COUNT", "0");
context.setConfigValue("DEBUG_MODE", "true");
```

### 命名空间支持

```cpp
// 进入命名空间
context.enterNamespace("components");

// 注册符号会自动添加命名空间前缀
context.registerSymbol("Button", chtl::SymbolType::CUSTOM_ELEMENT);

// 获取完全限定名
std::string fqn = context.getFullQualifiedName("Button");  // "components.Button"

// 退出命名空间
context.exitNamespace();
```

## CHTL JS状态机 (CHTLJSStateMachine)

### 特殊状态

```cpp
enum class CHTLJSState {
    // CHTL扩展状态
    IN_CHTL_SELECTOR,       // 在{{selector}}内
    IN_ARROW_OPERATION,     // 在->操作中
    IN_LISTEN_CONFIG,       // 在listen配置内
    IN_DELEGATE_CONFIG,     // 在delegate配置内
    IN_ANIMATE_CONFIG,      // 在animate配置内
    // ...
};
```

### CHTL特性检测

```cpp
chtljs::CHTLJSStateMachine jsStateMachine;

// 处理CHTL选择器
jsStateMachine.processEvent(chtljs::CHTLJSEvent::DOUBLE_OPEN_BRACE);  // {{
jsStateMachine.processEvent(chtljs::CHTLJSEvent::SELECTOR_CLASS);     // .box
jsStateMachine.processEvent(chtljs::CHTLJSEvent::DOUBLE_CLOSE_BRACE); // }}

// 检测使用的CHTL特性
if (jsStateMachine.isUsingCHTLFeatures()) {
    auto features = jsStateMachine.getDetectedFeatures();
    // 包含 CHTLFeature::ENHANCED_SELECTOR
}

// 验证CHTL语法
bool valid = jsStateMachine.validateCHTLSelector(".container button[0]");
```

## CHTL JS上下文 (CHTLJSContext)

### DOM引用管理

```cpp
chtljs::CHTLJSContext jsContext;

// 创建DOM引用
auto domRef = jsContext.createDOMReference(".container");
domRef->setOriginalExpression("{{.container}}");

// 生成JavaScript代码
std::string jsCode = domRef->toJavaScript();
// 输出: document.querySelector('.container')
```

### 事件绑定管理

```cpp
// 创建事件绑定
auto binding = jsContext.createEventBinding(domRef);

// 添加事件处理器
chtljs::EventHandler handler;
handler.eventName = "click";
handler.handlerCode = "() => { console.log('clicked'); }";
handler.isArrowFunction = true;
binding->addHandler(handler);

// 生成addEventListener代码
std::string listenerCode = binding->generateListenerCode();
```

### 动画管理

```cpp
// 创建动画定义
auto animation = jsContext.createAnimation();
animation->setDuration(1000);
animation->setEasing("ease-in-out");

// 添加CSS属性
chtljs::CSSProperty prop;
prop.name = "opacity";
prop.value = "0";
animation->addBeginProperty(prop);

prop.value = "1";
animation->addEndProperty(prop);

// 生成动画代码
std::string animCode = animation->generateAnimationCode();
```

### 验证功能

```cpp
// 验证选择器
bool validSelector = jsContext.validateSelector("{{.box button[0]}}");

// 验证事件名
bool validEvent = jsContext.validateEventName("click");

// 验证CSS属性
bool validProp = jsContext.validateCSSProperty("background-color");
```

## 集成示例

### CHTL解析流程

```cpp
class CHTLParser {
private:
    chtl::CHTLContext context;
    chtljs::CHTLJSContext jsContext;
    
public:
    void parseElement(const std::string& name) {
        // 更新CHTL状态机
        context.getStateMachine().processEvent(chtl::CHTLEvent::IDENTIFIER);
        context.getStateMachine().processEvent(chtl::CHTLEvent::OPEN_BRACE);
        
        // 进入元素作用域
        context.pushScope(chtl::ScopeType::ELEMENT, name);
    }
    
    void parseStyleBlock() {
        context.getStateMachine().processEvent(chtl::CHTLEvent::KEYWORD_STYLE);
        context.pushScope(chtl::ScopeType::STYLE, "style");
        
        // 自动生成类名功能
        if (needsAutoClass) {
            std::string className = context.generateAutoClassName();
            // 添加到元素
        }
    }
    
    void parseScriptBlock() {
        context.getStateMachine().processEvent(chtl::CHTLEvent::KEYWORD_SCRIPT);
        
        // 设置JS上下文的父上下文
        jsContext.setParentContext(&context);
        
        // 可以访问CHTL中定义的类名
        auto symbol = context.lookupSymbol("container");
        if (symbol && symbol->type == chtl::SymbolType::STYLE) {
            // 在JS中使用该类名
        }
    }
};
```

### 错误处理

```cpp
// CHTL错误处理
if (context.getStateMachine().hasErrors()) {
    for (const auto& error : context.getStateMachine().getErrors()) {
        std::cerr << "CHTL Error: " << error << std::endl;
    }
}

// CHTL JS错误处理
if (jsContext.hasErrors()) {
    for (const auto& error : jsContext.getErrors()) {
        std::cerr << "CHTL JS Error: " << error << std::endl;
    }
}
```

## 最佳实践

1. **状态管理**
   - 始终检查状态转换的有效性
   - 使用状态栈处理嵌套结构
   - 在错误时重置状态机

2. **上下文管理**
   - 正确管理作用域的进入和退出
   - 使用命名空间避免符号冲突
   - 利用自动生成功能简化开发

3. **验证**
   - 在处理前验证所有输入
   - 使用专门的验证器类
   - 提供清晰的错误信息

4. **代码生成**
   - 使用上下文中的信息生成正确的代码
   - 保持生成的代码可读性
   - 处理边界情况和特殊字符