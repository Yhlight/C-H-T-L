# CJmod JavaScript 实现设计

## 核心概念

CJmod 专注于扩展 CHTL JS 的语法和功能，通过 JavaScript 实现，与 CHTL JS 扫描器联动。

## 架构设计

### 1. CJmod 结构

```javascript
// cjmod.js - CJmod 模块定义
export default {
  name: '@cjmod/reactive',
  version: '1.0.0',
  
  // 语法扩展规则
  transforms: [
    {
      // 响应式赋值: count := 0
      pattern: /(\w+)\s*:=\s*(.+)/,
      replacement: (match, varName, value) => {
        return `const ${varName} = reactive(${value})`;
      }
    },
    {
      // 计算属性: doubled => count * 2
      pattern: /(\w+)\s*=>\s*(.+)/,
      replacement: (match, varName, expression) => {
        return `const ${varName} = computed(() => ${expression})`;
      }
    },
    {
      // 侦听器: watch count -> { ... }
      pattern: /watch\s+(\w+)\s*->\s*{/,
      replacement: (match, varName) => {
        return `watch(${varName}, () => {`;
      }
    }
  ],
  
  // 运行时代码
  runtime: `
    function reactive(value) {
      const subscribers = new Set();
      let internalValue = value;
      
      return new Proxy({
        get value() { return internalValue; },
        set value(newVal) {
          internalValue = newVal;
          subscribers.forEach(fn => fn());
        },
        subscribe(fn) { subscribers.add(fn); }
      }, {
        get(target, prop) {
          if (prop === 'value') return target.value;
          return target[prop];
        },
        set(target, prop, value) {
          if (prop === 'value') target.value = value;
          return true;
        }
      });
    }
    
    function computed(fn) {
      return { get value() { return fn(); } };
    }
    
    function watch(target, callback) {
      if (target.subscribe) {
        target.subscribe(callback);
      }
    }
  `,
  
  // 方法注入
  methods: {
    // 为 {{&}} 添加方法
    bindModel(varName) {
      this.addEventListener('input', (e) => {
        window[varName].value = e.target.value;
      });
      
      window[varName].subscribe(() => {
        this.value = window[varName].value;
      });
    }
  }
};
```

### 2. CHTL JS 扫描器集成

```javascript
// chtl-js-scanner.js - 修改现有扫描器
class CHTLJSScanner {
  constructor() {
    this.cjmods = new Map();
    this.transforms = [];
  }
  
  // 加载 CJmod
  loadCJmod(module) {
    this.cjmods.set(module.name, module);
    
    // 注册转换规则
    module.transforms.forEach(transform => {
      this.transforms.push({
        ...transform,
        module: module.name
      });
    });
  }
  
  // 扫描和转换代码
  scan(code) {
    let transformed = code;
    
    // 应用所有 CJmod 转换
    this.transforms.forEach(({ pattern, replacement }) => {
      transformed = transformed.replace(pattern, replacement);
    });
    
    // 处理 CHTL JS 特有语法
    transformed = this.processCHTLSyntax(transformed);
    
    // 注入运行时
    const runtime = this.generateRuntime();
    
    return runtime + '\n' + transformed;
  }
  
  // 处理 CHTL 特有语法
  processCHTLSyntax(code) {
    // {{&}} -> this
    code = code.replace(/\{\{&\}\}/g, 'this');
    
    // {{#id}} -> document.getElementById('id')
    code = code.replace(/\{\{#([\w-]+)\}\}/g, "document.getElementById('$1')");
    
    // {{.class}} -> document.getElementsByClassName('class')
    code = code.replace(/\{\{\.(\w+)\}\}/g, "document.getElementsByClassName('$1')");
    
    // -> 方法调用
    code = code.replace(/(\w+|this)->(\w+)\((.*?)\)/g, (match, obj, method, args) => {
      // 检查是否是 CJmod 方法
      for (const [name, module] of this.cjmods) {
        if (module.methods && module.methods[method]) {
          return `${obj}.${method}(${args})`;
        }
      }
      // 默认处理
      return `${obj}.${method}(${args})`;
    });
    
    return code;
  }
  
  // 生成运行时代码
  generateRuntime() {
    let runtime = '// CJmod Runtime\n';
    
    // 添加每个模块的运行时
    for (const [name, module] of this.cjmods) {
      if (module.runtime) {
        runtime += `// ${name}\n${module.runtime}\n\n`;
      }
      
      // 注入方法到原型
      if (module.methods) {
        runtime += `// ${name} methods\n`;
        for (const [methodName, methodCode] of Object.entries(module.methods)) {
          runtime += `Element.prototype.${methodName} = ${methodCode.toString()};\n`;
        }
      }
    }
    
    return runtime;
  }
}
```

### 3. 实际使用示例

```chtl
// app.chtl
[Import] @CJmod reactive from "@cjmod/reactive"
[Import] @CJmod animate from "@cjmod/animate"

body {
    div {
        id: "counter";
        
        script {
            // CJmod 响应式语法
            count := 0;
            doubled => count.value * 2;
            
            // 监听变化
            watch count -> {
                console.log("Count changed:", count.value);
                {{&}}.textContent = `Count: ${count.value}, Doubled: ${doubled.value}`;
            };
        }
        
        button {
            text { "增加" }
            script {
                {{&}}->listen("click", () => {
                    count.value++;
                });
            }
        }
    }
    
    input {
        id: "name-input";
        type: "text";
        
        script {
            name := "";
            
            // 双向绑定
            {{&}}->bindModel("name");
            
            watch name -> {
                {{#output}}.textContent = `Hello, ${name.value}!`;
            };
        }
    }
    
    div {
        id: "output";
        text { "Hello, !" }
    }
}
```

### 4. CJmod 加载器

```javascript
// cjmod-loader.js
class CJmodLoader {
  constructor(scanner) {
    this.scanner = scanner;
    this.registry = 'https://cjmod.chtl.io/api/';
  }
  
  async load(moduleName, version = 'latest') {
    try {
      // 尝试本地加载
      const module = await this.loadLocal(moduleName);
      if (module) {
        this.scanner.loadCJmod(module);
        return;
      }
      
      // 从注册表加载
      const module = await this.loadFromRegistry(moduleName, version);
      this.scanner.loadCJmod(module);
      
    } catch (error) {
      console.error(`Failed to load CJmod ${moduleName}:`, error);
    }
  }
  
  async loadLocal(moduleName) {
    try {
      // 尝试从 node_modules 加载
      const module = await import(`${moduleName}/cjmod.js`);
      return module.default;
    } catch {
      return null;
    }
  }
  
  async loadFromRegistry(moduleName, version) {
    const response = await fetch(`${this.registry}${moduleName}/${version}`);
    const moduleCode = await response.text();
    
    // 动态执行模块代码
    const module = new Function('exports', moduleCode + '; return exports.default;')({});
    return module;
  }
}
```

### 5. 编译器集成点

```cpp
// WebGenerator.cpp - 最小修改
void WebGenerator::visitScript(const std::shared_ptr<Script>& script) {
    std::string jsCode = script->getContent();
    
    // 检查是否有 CJmod 导入
    if (context_->hasCJmodImports()) {
        // 调用 JavaScript 扫描器处理
        jsCode = callJavaScriptScanner(jsCode, context_->getCJmodImports());
    } else {
        // 使用原有的 CHTL JS 处理
        jsCode = processJavaScriptEnhancements(jsCode);
    }
    
    jsCollector_.appendLine(jsCode);
}

std::string WebGenerator::callJavaScriptScanner(
    const std::string& code, 
    const std::vector<std::string>& cjmods
) {
    // 通过子进程调用 Node.js 运行扫描器
    std::string command = "node chtl-js-scanner-cli.js";
    
    // 传入代码和模块列表
    // ... 实现细节
    
    return processedCode;
}
```

## 优势

1. **纯 JS 实现**
   - 开发者熟悉，易于贡献
   - 调试方便，可热重载
   - 与 npm 生态无缝集成

2. **扫描器集成**
   - 利用现有的扫描切割机制
   - 不影响 CHTL 核心解析器
   - 转换规则清晰简单

3. **运行时注入**
   - 自动管理依赖
   - 避免全局污染
   - 支持 tree-shaking

4. **渐进式采用**
   - 可选的功能扩展
   - 向后兼容
   - 按需加载模块