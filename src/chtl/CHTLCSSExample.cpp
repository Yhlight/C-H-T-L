#include "CHTLContext.h"
#include "CHTLGenerator.h"
#include "CHTLCSSCompiler.h"
#include <iostream>

using namespace chtl;

int main() {
    // 创建上下文
    auto context = std::make_shared<CHTLContext>();
    
    // 创建生成器
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    std::cout << "=== CHTL CSS Compiler Example ===" << std::endl;
    
    // 示例1：全局样式块
    std::cout << "\n--- Example 1: Global Style Block in Head ---" << std::endl;
    
    generator.generateElement("html", {});
    
    // head部分
    generator.generateElement("head", {});
    generator.generateElement("title", {});
    generator.generateText("CHTL CSS Example");
    generator.closeElement(); // title
    
    // 全局样式块（原生CSS）
    std::string globalCSS = R"(
        /* Global Styles */
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            color: #333;
            background-color: #f4f4f4;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
        
        /* Typography */
        h1, h2, h3 {
            margin-bottom: 1rem;
            color: #2c3e50;
        }
        
        h1 { font-size: 2.5rem; }
        h2 { font-size: 2rem; }
        h3 { font-size: 1.5rem; }
        
        /* Components */
        .card {
            background: white;
            border-radius: 8px;
            padding: 20px;
            margin-bottom: 20px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
            transition: transform 0.3s ease;
        }
        
        .card:hover {
            transform: translateY(-5px);
            box-shadow: 0 5px 15px rgba(0,0,0,0.2);
        }
        
        /* Buttons */
        .btn {
            display: inline-block;
            padding: 10px 20px;
            background: #3498db;
            color: white;
            text-decoration: none;
            border-radius: 5px;
            transition: background 0.3s ease;
        }
        
        .btn:hover {
            background: #2980b9;
        }
        
        /* Responsive */
        @media (max-width: 768px) {
            .container {
                padding: 10px;
            }
            
            h1 { font-size: 2rem; }
            h2 { font-size: 1.5rem; }
            h3 { font-size: 1.2rem; }
        }
    )";
    
    generator.processGlobalStyleBlock(globalCSS);
    
    generator.closeElement(); // head
    
    // body部分
    generator.generateElement("body", {});
    
    generator.generateElement("div", {{"class", "container"}});
    
    // 示例2：局部样式块
    std::cout << "\n--- Example 2: Local Style Block ---" << std::endl;
    
    generator.generateElement("section", {});
    
    // 局部样式块
    generator.beginLocalStyleBlock();
    generator.addStyleRule(".hero", {
        {"padding", "60px 0"},
        {"background", "linear-gradient(135deg, #667eea 0%, #764ba2 100%)"},
        {"color", "white"},
        {"text-align", "center"}
    });
    
    generator.addStyleRule(".hero h1", {
        {"font-size", "3rem"},
        {"margin-bottom", "20px"},
        {"color", "white"}
    });
    
    generator.addStyleRule(".hero p", {
        {"font-size", "1.2rem"},
        {"max-width", "600px"},
        {"margin", "0 auto"}
    });
    generator.endStyleBlock();
    
    generator.generateElement("div", {{"class", "hero"}});
    generator.generateElement("h1", {});
    generator.generateText("Welcome to CHTL");
    generator.closeElement(); // h1
    
    generator.generateElement("p", {});
    generator.generateText("A modern hypertext language with powerful CSS compilation");
    generator.closeElement(); // p
    generator.closeElement(); // .hero
    
    generator.closeElement(); // section
    
    // 示例3：CSS优化
    std::cout << "\n--- Example 3: CSS Optimization ---" << std::endl;
    
    // 创建CSS编译器和优化器
    auto cssCompiler = std::make_shared<CSSCompiler>(context);
    cssCompiler->setMinify(true);
    
    std::string unoptimizedCSS = R"(
        .box {
            margin-top: 10px;
            margin-right: 10px;
            margin-bottom: 10px;
            margin-left: 10px;
            
            padding-top: 20px;
            padding-right: 20px;
            padding-bottom: 20px;
            padding-left: 20px;
            
            background-color: #ffffff;
            color: #000000;
        }
        
        .box {
            border: 1px solid #cccccc;
        }
        
        .unused-class {
            display: none;
        }
    )";
    
    std::cout << "Unoptimized CSS:\n" << unoptimizedCSS << std::endl;
    
    // 编译和优化
    std::string optimizedCSS = cssCompiler->compile(unoptimizedCSS);
    std::cout << "\nOptimized CSS:\n" << optimizedCSS << std::endl;
    
    // 示例4：CSS验证
    std::cout << "\n--- Example 4: CSS Validation ---" << std::endl;
    
    std::string invalidCSS = R"(
        .invalid {
            color: ;  /* Missing value */
            font-size: 16;  /* Missing unit */
            margin: 10px 20px 30px;  /* Valid */
        }
        
        /* Missing closing brace
        .broken {
            color: red;
    )";
    
    std::vector<std::string> errors;
    if (!cssCompiler->validate(invalidCSS, errors)) {
        std::cout << "CSS validation errors:" << std::endl;
        for (const auto& error : errors) {
            std::cout << "  - " << error << std::endl;
        }
    }
    
    // 示例5：CSS引用验证
    std::cout << "\n--- Example 5: CSS Reference Validation ---" << std::endl;
    
    auto cssProcessor = generator.getCSSProcessor();
    
    // 添加一些测试元素
    generator.generateElement("div", {{"class", "card"}});
    generator.generateElement("h2", {});
    generator.generateText("Card Title");
    generator.closeElement(); // h2
    
    generator.generateElement("p", {});
    generator.generateText("Card content");
    generator.closeElement(); // p
    
    generator.generateElement("a", {{"href", "#"}, {"class", "btn"}});
    generator.generateText("Learn More");
    generator.closeElement(); // a
    
    generator.closeElement(); // .card
    
    generator.generateElement("div", {{"class", "nonexistent-class"}, {"id", "unique-id"}});
    generator.generateText("This uses a class that doesn't exist in CSS");
    generator.closeElement();
    
    generator.closeElement(); // .container
    generator.closeElement(); // body
    generator.closeElement(); // html
    
    // 提取使用的类和ID
    std::set<std::string> usedClasses = {"container", "hero", "card", "btn", "nonexistent-class"};
    std::set<std::string> usedIds = {"unique-id"};
    
    // 验证引用
    cssProcessor->validateReferences(usedClasses, usedIds);
    
    // 输出生成的HTML
    std::cout << "\n=== Generated HTML ===" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 输出最终的CSS
    std::cout << "\n=== Final Optimized CSS ===" << std::endl;
    std::cout << generator.getCSS() << std::endl;
    
    // 检查错误和警告
    auto warnings = context->getWarnings();
    if (!warnings.empty()) {
        std::cout << "\n=== Warnings ===" << std::endl;
        for (const auto& warning : warnings) {
            std::cout << "Warning: " << warning << std::endl;
        }
    }
    
    return 0;
}