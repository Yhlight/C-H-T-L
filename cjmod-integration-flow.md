# CJmod 与 CHTL JS 编译器集成流程

## 集成架构

```
┌─────────────────────────────────────────────────────────┐
│                   CHTL 编译器 (C++)                      │
├─────────────────────────────────────────────────────────┤
│                                                          │
│  Parser → AST → Generator                                │
│                      ↓                                   │
│                 Script Node                              │
│                      ↓                                   │
│  ┌──────────────────────────────────────────────────┐  │
│  │          检测 CJmod 导入 & 提取 JS 代码           │  │
│  └──────────────────────────────────────────────────┘  │
│                      ↓                                   │
│  ┌──────────────────────────────────────────────────┐  │
│  │            调用 Node.js 子进程                    │  │
│  └──────────────────────────────────────────────────┘  │
└─────────────────────────┬───────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│              CHTL JS Scanner (Node.js)                   │
├─────────────────────────────────────────────────────────┤
│                                                          │
│  1. 加载 CJmod 模块                                      │
│  2. 应用语法转换规则                                     │
│  3. 处理 CHTL JS 语法 ({{&}}, ->, etc.)                │
│  4. 注入运行时代码                                       │
│  5. 返回处理后的 JS                                     │
│                                                          │
└─────────────────────────────────────────────────────────┘
```

## 详细实现

### 1. C++ 端最小修改

```cpp
// src/Generator/WebGenerator.cpp
#include <cstdlib>
#include <sstream>
#include <fstream>

class WebGenerator {
private:
    // 新增：CJmod 导入信息
    struct CJmodImport {
        std::string moduleName;
        std::string source;
        std::string version;
    };
    
    std::vector<CJmodImport> cjmodImports_;
    
    // 调用 Node.js 处理器
    std::string processCJmodScript(const std::string& jsCode) {
        // 创建临时文件
        std::string inputFile = "/tmp/chtl_js_input_" + std::to_string(rand()) + ".js";
        std::string outputFile = "/tmp/chtl_js_output_" + std::to_string(rand()) + ".js";
        std::string modulesFile = "/tmp/chtl_modules_" + std::to_string(rand()) + ".json";
        
        // 写入 JS 代码
        std::ofstream out(inputFile);
        out << jsCode;
        out.close();
        
        // 写入模块信息
        std::ofstream modOut(modulesFile);
        modOut << "[";
        for (size_t i = 0; i < cjmodImports_.size(); ++i) {
            if (i > 0) modOut << ",";
            modOut << "\"" << cjmodImports_[i].moduleName << "\"";
        }
        modOut << "]";
        modOut.close();
        
        // 调用 Node.js 脚本
        std::string command = "node " + getCJmodScannerPath() + 
                             " --input " + inputFile +
                             " --output " + outputFile +
                             " --modules " + modulesFile;
        
        int result = std::system(command.c_str());
        
        if (result != 0) {
            // 回退到原始 CHTL JS 处理
            return processJavaScriptEnhancements(jsCode);
        }
        
        // 读取结果
        std::ifstream in(outputFile);
        std::stringstream buffer;
        buffer << in.rdbuf();
        
        // 清理临时文件
        std::remove(inputFile.c_str());
        std::remove(outputFile.c_str());
        std::remove(modulesFile.c_str());
        
        return buffer.str();
    }
    
    std::string getCJmodScannerPath() {
        // 可以从环境变量或配置文件读取
        const char* path = std::getenv("CHTL_CJMOD_SCANNER");
        if (path) return std::string(path);
        
        // 默认路径
        return "/usr/local/lib/chtl/cjmod-scanner-cli.js";
    }
    
public:
    void visitScript(const std::shared_ptr<Script>& script) override {
        std::string jsCode = script->getContent();
        
        // 如果有 CJmod 导入，使用 Node.js 处理
        if (!cjmodImports_.empty()) {
            jsCode = processCJmodScript(jsCode);
        } else {
            // 使用原有的处理方式
            jsCode = processJavaScriptEnhancements(jsCode);
        }
        
        jsCollector_.appendLine(jsCode);
    }
    
    // 在解析导入时调用
    void addCJmodImport(const std::string& moduleName, 
                       const std::string& source,
                       const std::string& version = "latest") {
        cjmodImports_.push_back({moduleName, source, version});
    }
};
```

### 2. Node.js CLI 工具

```javascript
// cjmod-scanner-cli.js
#!/usr/bin/env node

const fs = require('fs');
const path = require('path');
const { CHTLJSScanner } = require('./chtl-js-scanner');
const { CJmodLoader } = require('./cjmod-loader');

// 解析命令行参数
const args = process.argv.slice(2);
const options = {};

for (let i = 0; i < args.length; i += 2) {
    const key = args[i].replace('--', '');
    options[key] = args[i + 1];
}

async function main() {
    try {
        // 读取输入
        const inputCode = fs.readFileSync(options.input, 'utf8');
        const modules = JSON.parse(fs.readFileSync(options.modules, 'utf8'));
        
        // 创建扫描器
        const scanner = new CHTLJSScanner();
        const loader = new CJmodLoader(scanner);
        
        // 加载模块
        for (const moduleName of modules) {
            await loader.load(moduleName);
        }
        
        // 处理代码
        const outputCode = scanner.scan(inputCode);
        
        // 写入输出
        fs.writeFileSync(options.output, outputCode);
        
        process.exit(0);
    } catch (error) {
        console.error('CJmod Scanner Error:', error);
        process.exit(1);
    }
}

main();
```

### 3. 优化的扫描器实现

```javascript
// chtl-js-scanner.js
class CHTLJSScanner {
    constructor() {
        this.cjmods = new Map();
        this.transforms = [];
        this.runtimeCode = new Set();
    }
    
    scan(code) {
        // 1. 预处理：提取位置信息
        const positions = this.extractPositions(code);
        
        // 2. 应用 CJmod 转换
        let transformed = this.applyCJmodTransforms(code);
        
        // 3. 处理 CHTL JS 语法
        transformed = this.processCHTLSyntax(transformed);
        
        // 4. 恢复位置信息（用于调试）
        transformed = this.restorePositions(transformed, positions);
        
        // 5. 生成最终代码
        return this.generateFinalCode(transformed);
    }
    
    applyCJmodTransforms(code) {
        let result = code;
        
        // 按优先级排序转换规则
        const sortedTransforms = [...this.transforms].sort((a, b) => 
            (b.priority || 0) - (a.priority || 0)
        );
        
        for (const transform of sortedTransforms) {
            if (transform.pattern instanceof RegExp) {
                result = result.replace(transform.pattern, transform.replacement);
            } else if (typeof transform.transform === 'function') {
                result = transform.transform(result, this);
            }
        }
        
        return result;
    }
    
    processCHTLSyntax(code) {
        // 使用更智能的替换策略，避免在字符串中替换
        const tokens = this.tokenize(code);
        const processed = [];
        
        for (let i = 0; i < tokens.length; i++) {
            const token = tokens[i];
            
            if (token.type === 'chtl-ref') {
                processed.push(this.processCHTLReference(token.value));
            } else if (token.type === 'method-call' && token.value === '->') {
                processed.push(this.processMethodCall(tokens, i));
                i++; // Skip method name
            } else {
                processed.push(token.value);
            }
        }
        
        return processed.join('');
    }
    
    processCHTLReference(ref) {
        // {{&}} -> this
        if (ref === '{{&}}') return 'this';
        
        // {{#id}} -> document.getElementById('id')
        const idMatch = ref.match(/\{\{#([\w-]+)\}\}/);
        if (idMatch) return `document.getElementById('${idMatch[1]}')`;
        
        // {{.class}} -> document.getElementsByClassName('class')
        const classMatch = ref.match(/\{\{\.(\w+)\}\}/);
        if (classMatch) return `document.getElementsByClassName('${classMatch[1]}')`;
        
        // {{selector}} -> document.querySelector('selector')
        const selectorMatch = ref.match(/\{\{(.+)\}\}/);
        if (selectorMatch) return `document.querySelector('${selectorMatch[1]}')`;
        
        return ref;
    }
    
    generateFinalCode(transformedCode) {
        const runtime = Array.from(this.runtimeCode).join('\n\n');
        
        return `
// CHTL JavaScript Runtime
(function() {
    'use strict';
    
    ${runtime}
    
    // User Code
    ${transformedCode}
})();
`;
    }
}

module.exports = { CHTLJSScanner };
```

## 性能优化

### 1. 缓存机制

```javascript
// cjmod-cache.js
class CJmodCache {
    constructor() {
        this.transformCache = new Map();
        this.moduleCache = new Map();
    }
    
    getCachedTransform(code, moduleHash) {
        const key = this.hash(code + moduleHash);
        return this.transformCache.get(key);
    }
    
    setCachedTransform(code, moduleHash, result) {
        const key = this.hash(code + moduleHash);
        this.transformCache.set(key, result);
    }
    
    hash(str) {
        // 简单的哈希函数
        let hash = 0;
        for (let i = 0; i < str.length; i++) {
            const char = str.charCodeAt(i);
            hash = ((hash << 5) - hash) + char;
            hash = hash & hash;
        }
        return hash.toString(36);
    }
}
```

### 2. 批处理模式

```cpp
// 支持批量处理多个脚本
class BatchProcessor {
public:
    void addScript(const std::string& id, const std::string& code) {
        scripts_[id] = code;
    }
    
    std::map<std::string, std::string> processAll() {
        // 一次性处理所有脚本，减少进程启动开销
        return callBatchProcessor(scripts_, cjmodImports_);
    }
    
private:
    std::map<std::string, std::string> scripts_;
};
```

## 开发体验优化

### 1. 实时重载

```javascript
// 开发模式下的实时重载
if (process.env.NODE_ENV === 'development') {
    const chokidar = require('chokidar');
    
    // 监听 CJmod 文件变化
    chokidar.watch('./node_modules/@cjmod/**/*.js')
        .on('change', (path) => {
            console.log(`CJmod changed: ${path}`);
            // 清除缓存，重新加载
            clearModuleCache(path);
            // 通知浏览器重载
            if (typeof window !== 'undefined') {
                window.location.reload();
            }
        });
}
```

### 2. 错误提示

```javascript
// 增强的错误提示
class CJmodError extends Error {
    constructor(message, module, line, column) {
        super(message);
        this.name = 'CJmodError';
        this.module = module;
        this.line = line;
        this.column = column;
    }
    
    toString() {
        return `${this.name} in ${this.module} at ${this.line}:${this.column}\n${this.message}`;
    }
}
```

这种架构设计充分利用了 CHTL JS 的扫描切割机制，让 CJmod 能够：

1. **灵活扩展** - 通过 JavaScript 轻松添加新语法
2. **高效集成** - 最小化对 C++ 编译器的修改
3. **良好性能** - 通过缓存和批处理优化
4. **优秀体验** - 支持热重载和友好的错误提示

这样开发者就可以专注于创造有用的 JS 扩展，而不需要深入了解 CHTL 编译器的内部实现！