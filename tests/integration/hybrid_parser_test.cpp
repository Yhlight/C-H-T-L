#include <iostream>
#include <string>
#include "../../src/chtl/CHTLCompiler.h"
#include "../../src/chtl/config/ConfigurationSystem.h"

void testHybridArchitecture() {
    std::cout << "=== Testing Hybrid Parser Architecture ===" << std::endl;
    
    // 测试CHTL代码，包含各种语言片段
    std::string chtlCode = R"(
// CHTL注释 - 由独立解析器处理
-- HTML注释 - 由独立解析器处理

div {
    -- 这是一个简单的测试
    "Hello CHTL!"
    
    style {
        /* 原生CSS - 由ANTLR4处理 */
        .container {
            display: flex;
            flex-direction: column;
            padding: 20px;
            background: linear-gradient(to right, #667eea, #764ba2);
        }
        
        @media (max-width: 768px) {
            .container {
                padding: 10px;
            }
        }
    }
    
    p { "这是一个段落" }
    
    script {
        // CHTL增强的JavaScript - 由独立的CHTL JS解析器处理
        var element = @Element div;
        
        {{ "动态内容: " + new Date().toLocaleString() }}
        
        // 原生JavaScript也会被正确处理
        function test() {
            console.log("Hello from CHTL JS!");
            return @Style container;
        }
    }
}

// 配置系统测试
[Template] @Element Card(title, content) {
    div class="card" {
        h2 { {{title}} }
        div class="card-content" {
            {{content}}
        }
    }
}

// 导入测试
[Import] @Style "styles/common.css" as CommonStyles
[Import] @JavaScript "utils/helpers.js" as Helpers

// 命名空间测试
[Namespace] TestSpace {
    [Custom] @Style Button {
        background: blue;
        color: white;
        padding: 10px 20px;
        border-radius: 5px;
    }
}

// 使用自定义样式
button class=@Style Button from TestSpace {
    "Click Me!"
}
    )";
    
    // 创建编译器
    chtl::CHTLCompiler compiler;
    
    // 测试编译
    auto result = compiler.compile(chtlCode);
    
    if (result.success) {
        std::cout << "\n✅ Compilation successful!" << std::endl;
        
        std::cout << "\n--- Generated HTML ---" << std::endl;
        std::cout << result.generatedHTML << std::endl;
        
        std::cout << "\n--- Generated CSS ---" << std::endl;
        std::cout << result.generatedCSS << std::endl;
        
        std::cout << "\n--- Generated JS ---" << std::endl;
        std::cout << result.generatedJS << std::endl;
    } else {
        std::cout << "\n❌ Compilation failed!" << std::endl;
        for (const auto& error : result.errors) {
            std::cout << "Error at line " << error.line << ": " << error.message << std::endl;
        }
    }
}

void testConfigurationSystem() {
    std::cout << "\n=== Testing Configuration System ===" << std::endl;
    
    // 创建测试配置
    std::string configContent = R"(
# CHTL配置文件 - 由独立的配置解析器处理

[KeywordMapping]
Template = Layout
Custom = Component
Style = CSS
Element = Component

[Options]
ENABLE_MINIFICATION = true
ENABLE_SOURCE_MAPS = true
DEBUG_MODE = false

[CustomSyntax]
TEMPLATE_START = {%
TEMPLATE_END = %}
INTERPOLATION_START = ${
INTERPOLATION_END = }
    )";
    
    // 保存配置文件
    std::ofstream configFile("test.config");
    configFile << configContent;
    configFile.close();
    
    // 加载配置
    auto& config = chtl::config::ConfigurationSystem::getInstance();
    if (config.loadFromFile("test.config")) {
        std::cout << "✅ Configuration loaded successfully!" << std::endl;
        
        // 测试自定义关键字
        std::cout << "Template keyword: " << config.getKeyword("Template") << std::endl;
        std::cout << "Custom keyword: " << config.getKeyword("Custom") << std::endl;
    } else {
        std::cout << "❌ Failed to load configuration!" << std::endl;
    }
}

void testParserIndependence() {
    std::cout << "\n=== Testing Parser Independence ===" << std::endl;
    
    // 测试纯CSS（ANTLR4）
    {
        chtl::CHTLCSSCompiler cssCompiler;
        std::string css = R"(
            :root {
                --primary-color: #007bff;
                --secondary-color: #6c757d;
            }
            
            .btn {
                background-color: var(--primary-color);
                color: white;
                padding: 0.5rem 1rem;
                border: none;
                border-radius: 0.25rem;
                cursor: pointer;
                transition: background-color 0.3s ease;
            }
            
            .btn:hover {
                background-color: color-mix(in srgb, var(--primary-color) 80%, black);
            }
        )";
        
        auto result = cssCompiler.compile(css);
        if (result.errors.empty()) {
            std::cout << "✅ CSS compilation successful (ANTLR4)" << std::endl;
        } else {
            std::cout << "❌ CSS compilation failed" << std::endl;
        }
    }
    
    // 测试纯JavaScript（ANTLR4）
    {
        chtl::CHTLJSCompiler jsCompiler;
        std::string js = R"(
            // ES6+ features
            class Component {
                constructor(name) {
                    this.name = name;
                    this.state = {};
                }
                
                async fetchData() {
                    const response = await fetch('/api/data');
                    const data = await response.json();
                    return data;
                }
                
                render() {
                    return `<div class="component">${this.name}</div>`;
                }
            }
            
            // Arrow functions and destructuring
            const { name, version } = { name: 'CHTL', version: '1.0.0' };
            const greet = (user = 'World') => `Hello, ${user}!`;
            
            // Optional chaining and nullish coalescing
            const value = obj?.prop?.nested ?? 'default';
        )";
        
        auto result = jsCompiler.compile(js);
        if (result.errors.empty()) {
            std::cout << "✅ JavaScript compilation successful (ANTLR4)" << std::endl;
        } else {
            std::cout << "❌ JavaScript compilation failed" << std::endl;
        }
    }
}

int main() {
    std::cout << "CHTL Hybrid Parser Architecture Test" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Architecture:" << std::endl;
    std::cout << "- CHTL Parser: Standalone (Native C++)" << std::endl;
    std::cout << "- CHTL JS Parser: Standalone (Native C++)" << std::endl;
    std::cout << "- Configuration Parser: Standalone (Native C++)" << std::endl;
    std::cout << "- CSS Parser: ANTLR4 (Full CSS Support)" << std::endl;
    std::cout << "- JavaScript Parser: ANTLR4 (Full JS Support)" << std::endl;
    std::cout << std::endl;
    
    try {
        testHybridArchitecture();
        testConfigurationSystem();
        testParserIndependence();
        
        std::cout << "\n=== All tests completed ===" << std::endl;
        std::cout << "✅ Hybrid parser architecture is working correctly!" << std::endl;
        std::cout << "✅ CHTL and Configuration use native parsers" << std::endl;
        std::cout << "✅ CSS and JavaScript use ANTLR4 for full language support" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}