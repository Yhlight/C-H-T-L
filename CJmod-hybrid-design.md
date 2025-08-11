# CJmod 混合设计方案

## 核心理念

CJmod 应该是 **简单的文本转换规则集合**，而不是复杂的 C++ 模块。

## 方案：CJmod 定义文件 + 最小 C++ 接口

### 1. CJmod 定义文件格式 (.cjmod)

```yaml
# animate.cjmod
name: animate
version: 1.0.0
description: Animation helpers

# 简单的文本替换规则
syntax:
  # 模式 -> 替换
  - pattern: "~> fadeIn"
    replace: ".style.opacity = '1'"
    
  - pattern: "~> fadeOut"
    replace: ".style.opacity = '0'"
    
  # 带参数的模式
  - pattern: "delay\\((\\d+)\\)"
    replace: "await new Promise(r => setTimeout(r, $1))"
    
  # 更复杂的转换
  - pattern: "(\\w+) ~> (\\w+)\\((.*?)\\)"
    replace: "$1.animate().$2($3)"

# 方法注入
methods:
  Element:
    fadeIn: |
      function(duration = 300) {
        this.style.opacity = '0';
        this.style.display = 'block';
        requestAnimationFrame(() => {
          this.style.opacity = '1';
        });
        return new Promise(r => setTimeout(r, duration));
      }
    
    fadeOut: |
      function(duration = 300) {
        this.style.opacity = '0';
        return new Promise(r => {
          setTimeout(() => {
            this.style.display = 'none';
          }, duration);
        });
      }

# 运行时代码
runtime: |
  Element.prototype.animate = function() {
    const queue = [];
    return {
      fadeIn: (d) => { queue.push(() => this.fadeIn(d)); return this; },
      fadeOut: (d) => { queue.push(() => this.fadeOut(d)); return this; },
      run: async () => { for (const fn of queue) await fn(); }
    };
  };
```

### 2. C++ 端最小加载器

```cpp
// CJmodSimpleLoader.h
#include <string>
#include <vector>
#include <map>

namespace chtl {

struct CJmodRule {
    std::string pattern;
    std::string replacement;
    bool isRegex;
};

struct CJmodDefinition {
    std::string name;
    std::string version;
    std::vector<CJmodRule> rules;
    std::map<std::string, std::map<std::string, std::string>> methods;
    std::string runtime;
};

class CJmodSimpleLoader {
public:
    // 从文件加载
    static CJmodDefinition loadFromFile(const std::string& path);
    
    // 从字符串加载
    static CJmodDefinition loadFromString(const std::string& content);
    
    // 应用转换规则
    static std::string applyRules(const std::string& jsCode, 
                                  const std::vector<CJmodRule>& rules);
    
    // 生成运行时
    static std::string generateRuntime(const CJmodDefinition& mod);
};

} // namespace chtl
```

### 3. JavaScript 处理器（核心逻辑）

```javascript
// cjmod-processor.js
class CJmodProcessor {
    constructor() {
        this.modules = new Map();
    }
    
    // 加载模块定义
    loadModule(definition) {
        const module = {
            name: definition.name,
            version: definition.version,
            rules: this.compileRules(definition.syntax),
            methods: definition.methods,
            runtime: definition.runtime
        };
        
        this.modules.set(module.name, module);
    }
    
    // 编译规则
    compileRules(syntax) {
        return syntax.map(rule => ({
            pattern: new RegExp(rule.pattern, 'g'),
            replace: rule.replace
        }));
    }
    
    // 处理代码
    process(code, activeModules = []) {
        let result = code;
        
        // 应用每个模块的规则
        for (const moduleName of activeModules) {
            const module = this.modules.get(moduleName);
            if (!module) continue;
            
            for (const rule of module.rules) {
                result = result.replace(rule.pattern, rule.replace);
            }
        }
        
        return result;
    }
    
    // 生成运行时
    generateRuntime(activeModules = []) {
        let runtime = '';
        
        for (const moduleName of activeModules) {
            const module = this.modules.get(moduleName);
            if (!module) continue;
            
            // 添加运行时代码
            if (module.runtime) {
                runtime += `\n// Module: ${moduleName}\n${module.runtime}\n`;
            }
            
            // 添加方法注入
            for (const [target, methods] of Object.entries(module.methods || {})) {
                for (const [name, impl] of Object.entries(methods)) {
                    runtime += `${target}.prototype.${name} = ${impl};\n`;
                }
            }
        }
        
        return runtime;
    }
}

module.exports = CJmodProcessor;
```

### 4. 集成方式

```cpp
// 在 WebGenerator 中
std::string WebGenerator::processJavaScriptWithCJmod(const std::string& code) {
    // 1. 收集活跃的 CJmod
    std::vector<std::string> activeModules = getActiveCJmods();
    
    // 2. 创建临时文件
    writeToFile("/tmp/input.js", code);
    writeToFile("/tmp/modules.json", json::serialize(activeModules));
    
    // 3. 调用 Node.js 处理
    std::string command = "node cjmod-process.js "
                         "--input /tmp/input.js "
                         "--modules /tmp/modules.json "
                         "--output /tmp/output.js";
    
    system(command.c_str());
    
    // 4. 读取结果
    return readFromFile("/tmp/output.js");
}
```

## 优势

1. **简单定义** - YAML/JSON 格式，无需编程
2. **灵活处理** - JavaScript 处理逻辑，易于扩展
3. **最小 C++ 代码** - 只做加载和调用
4. **热重载** - 修改 .cjmod 文件即可生效
5. **社区友好** - 前端开发者熟悉的工具链

## 使用示例

### 创建模块

```yaml
# reactive.cjmod
name: reactive
version: 1.0.0

syntax:
  - pattern: "(\\w+) := (.+);"
    replace: "const $1 = reactive($2);"
    
  - pattern: "watch (\\w+) ->"
    replace: "watch($1, () =>"
    
  - pattern: "(\\w+) => (.+);"
    replace: "const $1 = computed(() => $2);"

runtime: |
  function reactive(value) {
    let val = value;
    const subs = new Set();
    return {
      get value() { return val; },
      set value(v) { val = v; subs.forEach(fn => fn()); },
      subscribe(fn) { subs.add(fn); }
    };
  }
  
  function watch(target, callback) {
    if (target.subscribe) target.subscribe(callback);
  }
  
  function computed(fn) {
    return { get value() { return fn(); } };
  }
```

### 在 CHTL 中使用

```chtl
[Import] @CJmod reactive from "./reactive.cjmod"

body {
    script {
        count := 0;
        doubled => count.value * 2;
        
        watch count -> {
            console.log(count.value, doubled.value);
        };
    }
}
```

## 进一步简化：纯 JavaScript CJmod

```javascript
// animate.cjmod.js
export default {
    name: 'animate',
    version: '1.0.0',
    
    // 直接用 JS 函数处理
    transform(code) {
        return code
            .replace(/~>\s*fadeIn/g, '.style.opacity = "1"')
            .replace(/~>\s*fadeOut/g, '.style.opacity = "0"')
            .replace(/delay\((\d+)\)/g, 'await sleep($1)');
    },
    
    runtime: `
        window.sleep = ms => new Promise(r => setTimeout(r, ms));
    `
};
```

## 最终建议

1. **第一阶段**：使用 YAML/JSON 定义 + JavaScript 处理器
2. **第二阶段**：支持纯 JavaScript 模块
3. **第三阶段**：提供在线编辑器和模块市场

这样的设计：
- ✅ 简单易懂
- ✅ 易于创建和分享
- ✅ 灵活强大
- ✅ 社区友好
- ✅ 最小化 C++ 复杂度