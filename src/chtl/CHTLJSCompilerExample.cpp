#include "CHTLContext.h"
#include "CHTLGenerator.h"
#include "CHTLJSCompiler.h"
#include <iostream>

using namespace chtl;

int main() {
    // 创建上下文
    auto context = std::make_shared<CHTLContext>();
    
    // 创建生成器
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    std::cout << "=== CHTL JavaScript Compiler Example ===" << std::endl;
    
    // 示例1：全局脚本块
    std::cout << "\n--- Example 1: Global Script Block ---" << std::endl;
    
    generator.generateElement("html", {});
    
    // head部分
    generator.generateElement("head", {});
    generator.generateElement("title", {});
    generator.generateText("CHTL JavaScript Example");
    generator.closeElement(); // title
    
    // 全局JavaScript
    std::string globalJS = R"(
        // Global JavaScript
        'use strict';
        
        // Constants
        const APP_NAME = 'CHTL JavaScript Demo';
        const VERSION = '1.0.0';
        
        // Utility functions
        function $(selector) {
            return document.querySelector(selector);
        }
        
        function $$(selector) {
            return document.querySelectorAll(selector);
        }
        
        // Application class
        class App {
            constructor() {
                this.name = APP_NAME;
                this.version = VERSION;
                this.modules = new Map();
            }
            
            init() {
                console.log(`Initializing ${this.name} v${this.version}`);
                this.setupEventListeners();
                this.loadModules();
            }
            
            setupEventListeners() {
                document.addEventListener('DOMContentLoaded', () => {
                    console.log('DOM ready');
                    this.onReady();
                });
            }
            
            loadModules() {
                // Dynamic module loading
                const modules = ['ui', 'api', 'utils'];
                modules.forEach(module => {
                    this.loadModule(module);
                });
            }
            
            async loadModule(name) {
                try {
                    const module = await import(`./${name}.js`);
                    this.modules.set(name, module);
                    console.log(`Module ${name} loaded`);
                } catch (error) {
                    console.error(`Failed to load module ${name}:`, error);
                }
            }
            
            onReady() {
                // Initialize UI components
                this.initializeComponents();
            }
            
            initializeComponents() {
                // Component initialization logic
                const components = $$('[data-component]');
                components.forEach(component => {
                    const type = component.dataset.component;
                    this.initComponent(type, component);
                });
            }
            
            initComponent(type, element) {
                console.log(`Initializing ${type} component`);
                // Component-specific initialization
            }
        }
        
        // Create and initialize app
        const app = new App();
        app.init();
    )";
    
    generator.processGlobalScriptBlock(globalJS);
    
    generator.closeElement(); // head
    
    // body部分
    generator.generateElement("body", {});
    
    // 示例2：ES6模块
    std::cout << "\n--- Example 2: ES6 Modules ---" << std::endl;
    
    auto jsProcessor = generator.getJSProcessor();
    
    // UI模块
    std::string uiModule = R"(
        // UI Module
        export class UIComponent {
            constructor(element) {
                this.element = element;
                this.isActive = false;
            }
            
            render() {
                throw new Error('render() must be implemented');
            }
            
            activate() {
                this.isActive = true;
                this.element.classList.add('active');
            }
            
            deactivate() {
                this.isActive = false;
                this.element.classList.remove('active');
            }
        }
        
        export class Button extends UIComponent {
            constructor(element) {
                super(element);
                this.onClick = null;
                this.init();
            }
            
            init() {
                this.element.addEventListener('click', (e) => {
                    if (this.onClick) {
                        this.onClick(e);
                    }
                });
            }
            
            render() {
                this.element.innerHTML = `
                    <span class="button-text">${this.element.dataset.text || 'Click'}</span>
                `;
            }
        }
        
        export default { UIComponent, Button };
    )";
    
    jsProcessor->addModule("ui", uiModule);
    
    // API模块
    std::string apiModule = R"(
        // API Module
        const API_BASE = '/api/v1';
        
        export async function fetchData(endpoint) {
            const response = await fetch(`${API_BASE}/${endpoint}`);
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            return await response.json();
        }
        
        export async function postData(endpoint, data) {
            const response = await fetch(`${API_BASE}/${endpoint}`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(data)
            });
            return await response.json();
        }
        
        export const api = {
            get: (endpoint) => fetchData(endpoint),
            post: (endpoint, data) => postData(endpoint, data),
            put: async (endpoint, data) => {
                // PUT implementation
            },
            delete: async (endpoint) => {
                // DELETE implementation
            }
        };
        
        export default api;
    )";
    
    jsProcessor->addModule("api", apiModule);
    
    // 示例3：JavaScript优化
    std::cout << "\n--- Example 3: JavaScript Optimization ---" << std::endl;
    
    auto jsCompiler = std::make_shared<JSCompiler>(context);
    
    std::string unoptimizedJS = R"(
        // Unoptimized code
        const DEBUG = false;
        const MAX_ITEMS = 100;
        
        function processItems(items) {
            if (DEBUG) {
                console.log('Processing items:', items);
            }
            
            // Dead code
            if (false) {
                console.log('This will never run');
            }
            
            // Inefficient loop
            for (var i = 0; i < items.length; i++) {
                var item = items[i];
                console.log('Item:', item);
                processItem(item);
            }
            
            return true;
            
            // Unreachable code
            console.log('This is unreachable');
        }
        
        function processItem(item) {
            debugger;  // Debug statement
            
            const result = item * 2;
            console.log('Result:', result);
            
            return result;
        }
    )";
    
    std::cout << "Unoptimized JS:\n" << unoptimizedJS << std::endl;
    
    // 优化设置
    JSOptimizer::Options optimizerOptions;
    optimizerOptions.removeDeadCode = true;
    optimizerOptions.removeConsoleLog = true;
    optimizerOptions.removeDebugger = true;
    optimizerOptions.inlineConstants = true;
    
    JSOptimizer optimizer(optimizerOptions);
    std::string optimizedJS = optimizer.optimize(unoptimizedJS);
    
    std::cout << "\nOptimized JS:\n" << optimizedJS << std::endl;
    
    // 示例4：语法验证
    std::cout << "\n--- Example 4: JavaScript Validation ---" << std::endl;
    
    std::string invalidJS = R"(
        // Invalid JavaScript
        function test() {
            const x = 10
            const y = 20  // Missing semicolon
            
            // Syntax error
            if (x > y {
                console.log('x is greater');
            }
            
            // Undefined variable
            console.log(undefinedVar);
            
            // Duplicate declaration
            const x = 30;
        }
    )";
    
    std::vector<std::string> errors;
    if (!jsCompiler->validate(invalidJS, errors)) {
        std::cout << "JavaScript validation errors:" << std::endl;
        for (const auto& error : errors) {
            std::cout << "  - " << error << std::endl;
        }
    }
    
    // 示例5：模块转换
    std::cout << "\n--- Example 5: Module Format Conversion ---" << std::endl;
    
    std::string es6Module = R"(
        import { Component } from './component';
        import utils from './utils';
        
        export class MyComponent extends Component {
            constructor() {
                super();
            }
        }
        
        export default MyComponent;
    )";
    
    auto moduleProcessor = std::make_shared<JSModuleProcessor>(context);
    
    std::cout << "ES6 Module:\n" << es6Module << std::endl;
    
    std::string commonJS = moduleProcessor->convertToCommonJS(es6Module);
    std::cout << "\nCommonJS Format:\n" << commonJS << std::endl;
    
    // 示例6：结合CHTL特性
    std::cout << "\n--- Example 6: Combined CHTL Features ---" << std::endl;
    
    generator.generateElement("div", {{"id", "app"}});
    
    // 局部脚本块（CHTL JS特性）
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 使用CHTL增强选择器
        const app = {{#app}};
        
        // 动画配置
        const fadeIn = animate({
            duration: 300,
            easing: ease-in-out,
            begin: { opacity: 0 },
            end: { opacity: 1 }
        });
        
        // 事件监听
        {{button}}->listen({
            click: function(e) {
                console.log('Button clicked!');
                fadeIn(this);
            },
            
            mouseenter: function() {
                this.classList.add('hover');
            },
            
            mouseleave: function() {
                this.classList.remove('hover');
            }
        });
    )");
    generator.endScriptBlock();
    
    generator.generateElement("button", {{"class", "btn"}});
    generator.generateText("Click Me");
    generator.closeElement(); // button
    
    generator.closeElement(); // #app
    generator.closeElement(); // body
    generator.closeElement(); // html
    
    // 输出生成的HTML
    std::cout << "\n=== Generated HTML ===" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 输出最终的JavaScript
    std::cout << "\n=== Final JavaScript ===" << std::endl;
    std::cout << generator.getJS() << std::endl;
    
    // 检查警告
    auto warnings = context->getWarnings();
    if (!warnings.empty()) {
        std::cout << "\n=== Warnings ===" << std::endl;
        for (const auto& warning : warnings) {
            std::cout << "Warning: " << warning << std::endl;
        }
    }
    
    return 0;
}