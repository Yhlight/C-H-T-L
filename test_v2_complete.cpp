#include "v2/Parser/ChtlParser.h"
#include "v2/Generator/ChtlGenerator.h"
#include "v2/Css/NativeCssAnalyzer.h"
#include "v2/Js/NativeJsAnalyzer.h"
#include "v2/Import/ImportSystem.h"
#include "v2/Cmod/CmodSystem.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void testChtlV2Compiler() {
    // 创建一个综合测试 CHTL 文件
    std::string chtl = R"(
// 导入测试
[Import] @Style "styles/main.css"
[Import] @JavaScript "scripts/utils.js"
[Import] @Element CHTL::Forms/Input

// 全局样式
<style>
    :root {
        --primary-color: #007bff;
        --secondary-color: #6c757d;
    }
    
    body {
        margin: 0;
        padding: 0;
        font-family: system-ui, -apple-system, sans-serif;
    }
</style>

// 模板定义
[Template] @Element Card(title, content)
{
    div .card
    {
        h3 .card-title { {{title}} }
        div .card-content { {{content}} }
        
        style {
            .card {
                border: 1px solid #ddd;
                border-radius: 8px;
                padding: 16px;
                margin: 16px 0;
            }
            
            &:hover {
                box-shadow: 0 4px 8px rgba(0,0,0,0.1);
            }
        }
    }
}

// 主应用
div #app
{
    header
    {
        h1 { "CHTL v2 Test Application" }
        
        style {
            padding: 20px;
            background-color: var(--primary-color);
            color: white;
        }
    }
    
    main .container
    {
        // 使用模板
        @Card("Welcome", "This is a test of the CHTL v2 compiler.")
        
        section .features
        {
            h2 { "Features" }
            
            ul {
                li { "State-driven parsing" }
                li { "Independent compilers" }
                li { "Advanced CSS/JS analysis" }
                li { "CMOD system" }
            }
            
            style {
                .features {
                    background: #f8f9fa;
                    padding: 20px;
                    border-radius: 4px;
                }
                
                ul {
                    list-style-type: none;
                    padding-left: 0;
                }
                
                li::before {
                    content: "✓ ";
                    color: var(--primary-color);
                    font-weight: bold;
                }
            }
        }
        
        // 局部脚本测试
        script {
            const features = {{&}}.querySelector('.features');
            const title = {{#app}}.querySelector('h1');
            
            features.addEventListener('click', () => {
                console.log('Features clicked');
            });
            
            // 测试 CHTL-JS 功能
            {{#app}}.listen('custom-event', (e) => {
                console.log('Custom event:', e.detail);
            });
        }
        
        style {
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
    }
}

// 全局脚本
<script>
    // 初始化代码
    document.addEventListener('DOMContentLoaded', () => {
        console.log('CHTL v2 Application loaded');
        
        // 发送自定义事件
        const app = document.getElementById('app');
        app.dispatchEvent(new CustomEvent('custom-event', {
            detail: { message: 'Hello from CHTL v2!' }
        }));
    });
</script>
)";

    std::cout << "=== CHTL v2 编译器综合测试 ===" << std::endl;
    
    // 1. 解析 CHTL
    std::cout << "\n1. 解析 CHTL..." << std::endl;
    chtl::v2::ChtlParser parser(chtl);
    auto parseResult = parser.parse();
    
    if (!parseResult.errors.empty()) {
        std::cout << "解析错误:" << std::endl;
        for (const auto& error : parseResult.errors) {
            std::cout << "  - " << error << std::endl;
        }
    }
    
    if (!parseResult.warnings.empty()) {
        std::cout << "解析警告:" << std::endl;
        for (const auto& warning : parseResult.warnings) {
            std::cout << "  - " << warning << std::endl;
        }
    }
    
    if (!parseResult.ast) {
        std::cerr << "解析失败，无法生成 AST" << std::endl;
        return;
    }
    
    std::cout << "解析成功！" << std::endl;
    
    // 2. 生成代码
    std::cout << "\n2. 生成代码..." << std::endl;
    chtl::v2::ChtlGenerator generator;
    auto genResult = generator.generate(parseResult.ast.get());
    
    if (!genResult.errors.empty()) {
        std::cout << "生成错误:" << std::endl;
        for (const auto& error : genResult.errors) {
            std::cout << "  - " << error << std::endl;
        }
    }
    
    // 3. 分析 CSS
    std::cout << "\n3. 分析生成的 CSS..." << std::endl;
    chtl::v2::css::NativeCssAnalyzer cssAnalyzer;
    auto cssResult = cssAnalyzer.analyze(genResult.css);
    
    std::cout << "CSS 分析结果:" << std::endl;
    std::cout << "  有效: " << (cssResult.valid ? "是" : "否") << std::endl;
    std::cout << "  规则数: " << cssResult.ruleCount << std::endl;
    std::cout << "  选择器数: " << cssResult.selectors.size() << std::endl;
    
    // 4. 分析 JavaScript
    std::cout << "\n4. 分析生成的 JavaScript..." << std::endl;
    chtl::v2::js::NativeJsAnalyzer jsAnalyzer;
    auto jsResult = jsAnalyzer.analyze(genResult.javascript);
    
    std::cout << "JavaScript 分析结果:" << std::endl;
    std::cout << "  有效: " << (jsResult.valid ? "是" : "否") << std::endl;
    std::cout << "  函数数: " << jsResult.functionCount << std::endl;
    std::cout << "  变量数: " << jsResult.variables.size() << std::endl;
    
    // 5. 测试导入系统
    std::cout << "\n5. 测试导入系统..." << std::endl;
    chtl::v2::ImportSystem importSystem;
    importSystem.setProjectRoot("./");
    
    auto styleImport = importSystem.resolveImport("styles/main.css", chtl::v2::ImportType::Style);
    std::cout << "样式导入: " << (styleImport.success ? "成功" : "失败") << std::endl;
    
    auto jsImport = importSystem.resolveImport("scripts/utils.js", chtl::v2::ImportType::JavaScript);
    std::cout << "脚本导入: " << (jsImport.success ? "成功" : "失败") << std::endl;
    
    auto officialImport = importSystem.resolveImport("CHTL::Forms/Input", chtl::v2::ImportType::Element);
    std::cout << "官方模块导入: " << (officialImport.success ? "成功" : "失败") << std::endl;
    
    // 6. 测试 CMOD 系统
    std::cout << "\n6. 测试 CMOD 系统..." << std::endl;
    chtl::v2::cmod::CmodSystem cmodSystem;
    cmodSystem.addPackagePath("./cmod_modules");
    
    auto packages = cmodSystem.getInstalledPackages();
    std::cout << "已安装的 CMOD 包: " << packages.size() << std::endl;
    
    // 7. 输出生成的文件
    std::cout << "\n7. 输出生成的文件..." << std::endl;
    
    // 创建输出目录
    fs::create_directories("output/v2-test");
    
    // 写入 HTML
    std::ofstream htmlFile("output/v2-test/index.html");
    htmlFile << genResult.html;
    htmlFile.close();
    std::cout << "HTML 已写入: output/v2-test/index.html" << std::endl;
    
    // 写入 CSS
    if (!genResult.css.empty()) {
        std::ofstream cssFile("output/v2-test/styles.css");
        cssFile << genResult.css;
        cssFile.close();
        std::cout << "CSS 已写入: output/v2-test/styles.css" << std::endl;
    }
    
    // 写入 JavaScript
    if (!genResult.javascript.empty()) {
        std::ofstream jsFile("output/v2-test/scripts.js");
        jsFile << genResult.javascript;
        jsFile.close();
        std::cout << "JavaScript 已写入: output/v2-test/scripts.js" << std::endl;
    }
    
    std::cout << "\n=== 测试完成 ===" << std::endl;
    
    // 显示生成的代码片段
    std::cout << "\n生成的 HTML 预览:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << genResult.html.substr(0, 500) << "..." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    try {
        testChtlV2Compiler();
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}