# CJmod 实际使用示例

## 1. 创建一个动画模块

### animate.cjmod.json
```json
{
  "name": "@cjmod/animate",
  "version": "1.0.0",
  "main": "index.js",
  "extensions": {
    "methods": [
      {
        "name": "fadeIn",
        "parameters": ["duration", "callback"],
        "async": true
      },
      {
        "name": "slideDown",
        "parameters": ["duration"],
        "async": true
      }
    ],
    "operators": [
      {
        "symbol": "~>",
        "precedence": 15,
        "description": "Animation chain operator"
      }
    ]
  }
}
```

### index.js
```javascript
// CJmod 动画模块实现
const CJmodAnimate = {
  // 方法实现
  methods: {
    fadeIn: function(duration = 300, callback) {
      const element = this;
      element.style.opacity = '0';
      element.style.display = 'block';
      element.style.transition = `opacity ${duration}ms ease-in-out`;
      
      // 强制重绘
      element.offsetHeight;
      
      element.style.opacity = '1';
      
      return new Promise((resolve) => {
        setTimeout(() => {
          element.style.transition = '';
          if (callback) callback();
          resolve(element);
        }, duration);
      });
    },
    
    slideDown: function(duration = 300) {
      const element = this;
      const height = element.scrollHeight;
      
      element.style.height = '0';
      element.style.overflow = 'hidden';
      element.style.transition = `height ${duration}ms ease-out`;
      element.style.display = 'block';
      
      // 强制重绘
      element.offsetHeight;
      
      element.style.height = height + 'px';
      
      return new Promise((resolve) => {
        setTimeout(() => {
          element.style.height = '';
          element.style.overflow = '';
          element.style.transition = '';
          resolve(element);
        }, duration);
      });
    }
  },
  
  // 操作符实现
  operators: {
    '~>': function(element, methodName, ...args) {
      if (typeof element[methodName] === 'function') {
        return element[methodName](...args);
      }
      throw new Error(`Method ${methodName} not found`);
    }
  },
  
  // 初始化代码
  init: function() {
    // 将方法注入到 Element.prototype
    Object.entries(this.methods).forEach(([name, fn]) => {
      if (!Element.prototype[name]) {
        Element.prototype[name] = fn;
      }
    });
  }
};

// 导出模块定义
if (typeof module !== 'undefined' && module.exports) {
  module.exports = CJmodAnimate;
}
```

## 2. 在 CHTL 中使用模块

### app.chtl
```chtl
[Import] @CJmod animate from "@cjmod/animate"
[Import] @CJmod validate from "@cjmod/validate"

body {
    // 导航菜单动画
    nav {
        id: "main-nav";
        style { display: none; }
        
        ul {
            li { a { href: "#home"; text { "首页" } } }
            li { a { href: "#about"; text { "关于" } } }
            li { a { href: "#contact"; text { "联系" } } }
        }
    }
    
    // 显示导航按钮
    button {
        id: "show-nav";
        text { "显示菜单" }
        
        script {
            {{&}}->listen("click", async () => {
                // 使用 CJmod 提供的动画方法
                await {{#main-nav}}~>slideDown(500);
                {{&}}.disabled = true;
            });
        }
    }
    
    // 登录表单
    form {
        id: "login-form";
        style { display: none; }
        
        input {
            type: "email";
            name: "email";
            placeholder: "邮箱地址";
            
            // 使用验证模块
            {{&}}->validate({
                required: true,
                email: true
            });
        }
        
        input {
            type: "password";
            name: "password";
            placeholder: "密码";
            
            {{&}}->validate({
                required: true,
                minLength: 8
            });
        }
        
        button {
            type: "submit";
            text { "登录" }
        }
        
        script {
            {{&}}->listen("submit", async (e) => {
                e.preventDefault();
                
                if ({{&}}->isValid()) {
                    // 提交表单
                    console.log("表单验证通过");
                }
            });
        }
    }
    
    // 显示登录表单
    button {
        text { "登录" }
        
        script {
            {{&}}->listen("click", () => {
                {{#login-form}}~>fadeIn(300);
            });
        }
    }
}
```

## 3. 编译流程集成

```cpp
// 在编译器中的使用
#include "CJmod/CJmodManager.h"
#include "Parser/StandardParser.h"
#include "Generator/WebGenerator.h"

void compileWithCJmod(const std::string& sourceFile) {
    // 1. 初始化 CJmod 管理器
    auto& cjmodManager = CJmodManager::getInstance();
    cjmodManager.initialize();
    
    // 2. 创建编译管道
    CJmodPipeline pipeline;
    
    // 3. 解析源文件
    StandardLexer lexer;
    lexer.initialize(sourceFile);
    
    // 让 CJmod 扩展词法分析器
    pipeline.executeLexerInit(&lexer);
    
    // 4. 语法分析
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    // 让 CJmod 扩展语法分析器
    pipeline.executeParserInit(&parser);
    
    // 5. 生成 AST
    auto ast = parser.parse();
    
    // 6. 处理导入
    auto imports = CJmodImportProcessor::parseImports(ast);
    CJmodImportProcessor::processImports(imports);
    
    // 7. AST 转换
    pipeline.executeASTTransform(ast);
    
    // 8. 代码生成
    WebGenerator generator;
    pipeline.executeGenerate(&generator);
    
    auto result = generator.generate(ast);
    
    // 9. 注入 CJmod 运行时
    std::string runtime = cjmodManager.generateCombinedRuntime();
    result.js = runtime + "\n" + result.js;
    
    // 10. 后处理
    pipeline.executePostprocess(result.js);
}
```

## 4. 运行时架构

```javascript
// 生成的运行时代码结构
(function() {
  'use strict';
  
  // CJmod 运行时核心
  window.CJmod = window.CJmod || {
    modules: {},
    operators: {},
    
    // 注册模块
    register: function(name, module) {
      this.modules[name] = module;
      if (module.init) {
        module.init();
      }
    },
    
    // 应用操作符
    applyOperator: function(op, left, right) {
      if (this.operators[op]) {
        return this.operators[op](left, right);
      }
      throw new Error(`Unknown operator: ${op}`);
    }
  };
  
  // 加载的模块
  CJmod.register('@cjmod/animate', {
    /* 模块代码 */
  });
  
  CJmod.register('@cjmod/validate', {
    /* 模块代码 */
  });
  
  // CHTL 增强的选择器
  window.$$ = function(selector) {
    const element = document.querySelector(selector);
    // 返回增强的元素
    return element;
  };
})();
```