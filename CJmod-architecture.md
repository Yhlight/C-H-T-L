# CJmod 混合架构设计

## 架构概览

```
┌─────────────────────────────────────────────────────────────┐
│                      CHTL 编译器 (C++)                       │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌──────────────┐  ┌─────────────────┐   │
│  │   Parser    │  │  CJmod Host  │  │   Generator     │   │
│  │             │──│    (C++)     │──│                 │   │
│  │             │  │              │  │                 │   │
│  └─────────────┘  └──────┬───────┘  └─────────────────┘   │
│                           │                                  │
│                    ┌──────┴───────┐                         │
│                    │   V8/Node    │                         │
│                    │  Embedded    │                         │
│                    └──────┬───────┘                         │
└───────────────────────────┼─────────────────────────────────┘
                            │
┌───────────────────────────┼─────────────────────────────────┐
│                    CJmod 模块 (JavaScript)                   │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌──────────────┐  ┌─────────────────┐   │
│  │  Transform  │  │   Runtime    │  │   Methods    │   │
│  │   Rules     │  │   Library    │  │  & Operators │   │
│  └─────────────┘  └──────────────┘  └─────────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

## 核心组件

### 1. CJmod Host (C++)
负责加载和执行 JavaScript 模块：

```cpp
// include/CJmod/CJmodHost.h
#ifndef CHTL_CJMOD_HOST_H
#define CHTL_CJMOD_HOST_H

#include <memory>
#include <string>
#include <v8.h>
#include "Node/Node.h"

namespace chtl {

class CJmodHost {
public:
    CJmodHost();
    ~CJmodHost();
    
    // 初始化 V8 引擎
    bool initialize();
    
    // 加载 CJmod 模块
    bool loadModule(const std::string& modulePath);
    
    // 执行转换规则
    struct TransformResult {
        bool success;
        std::string output;
        std::string error;
    };
    
    // 在 JS 中执行 AST 转换
    TransformResult transformAST(const std::string& astJson, 
                                const std::string& moduleName);
    
    // 获取运行时代码
    std::string getRuntimeCode(const std::string& moduleName);
    
    // 执行自定义函数
    TransformResult executeFunction(const std::string& moduleName,
                                   const std::string& functionName,
                                   const std::string& args);
    
private:
    std::unique_ptr<v8::Platform> platform_;
    std::unique_ptr<v8::Isolate> isolate_;
    std::unique_ptr<v8::Persistent<v8::Context>> context_;
    
    // AST 序列化/反序列化
    std::string serializeAST(const std::shared_ptr<Node>& ast);
    std::shared_ptr<Node> deserializeAST(const std::string& json);
};

} // namespace chtl

#endif
```

### 2. CJmod JavaScript 接口

```javascript
// cjmod-interface.js
/**
 * CJmod 模块接口定义
 */
class CJmodModule {
    constructor(config) {
        this.name = config.name;
        this.version = config.version;
        this.transforms = [];
        this.runtime = {};
    }
    
    /**
     * 注册 AST 转换规则
     */
    transform(pattern, handler) {
        this.transforms.push({ pattern, handler });
    }
    
    /**
     * 注册运行时方法
     */
    method(selector, name, implementation) {
        if (!this.runtime.methods) {
            this.runtime.methods = {};
        }
        if (!this.runtime.methods[selector]) {
            this.runtime.methods[selector] = {};
        }
        this.runtime.methods[selector][name] = implementation;
    }
    
    /**
     * 注册操作符
     */
    operator(symbol, handler, options = {}) {
        if (!this.runtime.operators) {
            this.runtime.operators = {};
        }
        this.runtime.operators[symbol] = {
            handler,
            precedence: options.precedence || 10,
            associativity: options.associativity || 'left'
        };
    }
    
    /**
     * 处理 AST
     */
    processAST(ast) {
        let modified = false;
        
        const walk = (node) => {
            for (const transform of this.transforms) {
                if (this.matchPattern(node, transform.pattern)) {
                    const result = transform.handler(node);
                    if (result) {
                        Object.assign(node, result);
                        modified = true;
                    }
                }
            }
            
            if (node.children) {
                node.children.forEach(walk);
            }
        };
        
        walk(ast);
        return { ast, modified };
    }
    
    /**
     * 生成运行时代码
     */
    generateRuntime() {
        const runtime = [];
        
        // 生成方法注入代码
        if (this.runtime.methods) {
            runtime.push(this.generateMethodInjections());
        }
        
        // 生成操作符代码
        if (this.runtime.operators) {
            runtime.push(this.generateOperatorOverloads());
        }
        
        return runtime.join('\n\n');
    }
    
    // 私有方法
    matchPattern(node, pattern) {
        // 实现模式匹配逻辑
        // 支持类型匹配、属性匹配、子节点匹配等
    }
    
    generateMethodInjections() {
        // 生成方法注入的 JavaScript 代码
    }
    
    generateOperatorOverloads() {
        // 生成操作符重载的 JavaScript 代码
    }
}

// 导出给 C++ 使用的接口
if (typeof __CJmodBridge !== 'undefined') {
    __CJmodBridge.CJmodModule = CJmodModule;
}
```

### 3. 实际模块示例

```javascript
// @cjmod/animate/index.js
const CJmod = require('cjmod-interface');

const animate = new CJmod.Module({
    name: '@cjmod/animate',
    version: '1.0.0'
});

// 注册 AST 转换：将 ~> 操作符转换为方法调用
animate.transform({
    type: 'BinaryExpression',
    operator: '~>'
}, (node) => {
    // 转换 element ~> fadeIn(300) 
    // 为 element.fadeIn(300)
    return {
        type: 'CallExpression',
        callee: {
            type: 'MemberExpression',
            object: node.left,
            property: { type: 'Identifier', name: node.right.name }
        },
        arguments: node.right.arguments
    };
});

// 注册运行时方法
animate.method('*', 'fadeIn', function(duration = 300) {
    const element = this;
    return new Promise((resolve) => {
        element.style.transition = `opacity ${duration}ms`;
        element.style.opacity = '0';
        
        requestAnimationFrame(() => {
            element.style.opacity = '1';
            setTimeout(resolve, duration);
        });
    });
});

animate.method('*', 'slideDown', function(duration = 300) {
    const element = this;
    const height = element.scrollHeight;
    
    element.style.height = '0';
    element.style.overflow = 'hidden';
    element.style.transition = `height ${duration}ms`;
    
    requestAnimationFrame(() => {
        element.style.height = height + 'px';
    });
});

// 注册操作符
animate.operator('~>', function(left, right) {
    if (typeof left[right.method] === 'function') {
        return left[right.method].apply(left, right.args);
    }
}, { precedence: 15 });

module.exports = animate;
```

### 4. 编译器集成

```cpp
// src/CJmod/CJmodIntegration.cpp
#include "CJmod/CJmodHost.h"
#include "CJmod/CJmodManager.h"
#include "Parser/StandardParser.h"
#include "Generator/WebGenerator.h"

namespace chtl {

class CJmodCompilerIntegration {
private:
    CJmodHost jsHost_;
    CJmodManager& manager_;
    
public:
    CJmodCompilerIntegration() : manager_(CJmodManager::getInstance()) {
        jsHost_.initialize();
    }
    
    // 在解析阶段注入扩展
    void integrateParser(StandardParser* parser) {
        // 添加新的 token 类型（如果需要）
        parser->addTokenHandler("~>", [this](Token token) {
            // 处理自定义操作符
            return std::make_shared<BinaryOp>("~>", token);
        });
    }
    
    // AST 转换阶段
    void transformAST(std::shared_ptr<Node> ast) {
        // 获取所有加载的 CJmod
        auto modules = manager_.getLoadedModules();
        
        for (const auto& moduleName : modules) {
            // 序列化 AST 为 JSON
            std::string astJson = serializeAST(ast);
            
            // 在 JavaScript 中执行转换
            auto result = jsHost_.transformAST(astJson, moduleName);
            
            if (result.success && result.modified) {
                // 反序列化修改后的 AST
                ast = deserializeAST(result.output);
            }
        }
    }
    
    // 代码生成阶段
    void integrateGenerator(WebGenerator* generator) {
        // 收集所有模块的运行时代码
        std::string combinedRuntime;
        
        for (const auto& moduleName : manager_.getLoadedModules()) {
            std::string runtime = jsHost_.getRuntimeCode(moduleName);
            combinedRuntime += runtime + "\n";
        }
        
        // 注入到生成的 JS 中
        generator->prependJavaScript(combinedRuntime);
    }
};

} // namespace chtl
```

### 5. 中间扫描器集成

```cpp
// 扩展现有的 JS 中间扫描器
class EnhancedJSScanner : public StandardJSScanner {
public:
    void scanWithCJmod(const std::string& script) {
        // 1. 预处理：应用 CJmod 语法转换
        std::string transformed = applyCJmodTransforms(script);
        
        // 2. 标准扫描
        scan(transformed);
        
        // 3. 后处理：注入 CJmod 运行时引用
        injectCJmodReferences();
    }
    
private:
    std::string applyCJmodTransforms(const std::string& script) {
        // 调用 JS 引擎执行语法转换
        return jsHost_.executeFunction("@cjmod/core", 
                                     "transformScript", 
                                     script).output;
    }
    
    void injectCJmodReferences() {
        // 识别 CJmod 方法调用并添加必要的引用
        for (auto& call : methodCalls_) {
            if (isCJmodMethod(call)) {
                addDependency(call.module);
            }
        }
    }
};
```

## 开发流程

### 1. CJmod 开发者视角

```bash
# 创建新模块
$ chtl cjmod create @mycompany/validation

# 开发模块
$ cd validation
$ npm install
$ npm run dev  # 热重载开发

# 测试模块
$ chtl cjmod test

# 发布模块
$ chtl cjmod publish
```

### 2. CHTL 开发者视角

```chtl
// 安装模块
[Install] @cjmod/animate@1.0.0
[Install] @cjmod/validate from "./local-module"

// 使用模块
[Import] @CJmod animate
[Import] @CJmod validate as v

body {
    div {
        id: "content";
        
        // 使用 CJmod 提供的功能
        script {
            {{&}}~>fadeIn(500);
            
            // 链式调用
            {{&}}~>fadeIn(300)~>slideDown(200);
        }
    }
    
    form {
        input {
            // 使用验证模块
            {{&}}->v.email();
            {{&}}->v.required();
        }
    }
}
```

## 优势总结

1. **JS 模块开发**
   - 降低贡献门槛
   - 利用 JS 生态系统
   - 快速迭代

2. **C++ 深度集成**
   - 编译时优化
   - 类型安全
   - 性能保证

3. **灵活的扩展点**
   - AST 转换
   - 运行时注入
   - 语法扩展

4. **与中间扫描器联动**
   - 预处理脚本
   - 依赖分析
   - 代码优化