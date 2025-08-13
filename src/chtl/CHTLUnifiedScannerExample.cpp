#include "CHTLUnifiedScanner.h"
#include "CHTLContext.h"
#include "CHTLTemplate.h"
#include "CHTLCustom.h"
#include <iostream>
#include <iomanip>

using namespace chtl;

int main() {
    // 创建上下文
    auto context = std::make_shared<CHTLContext>();
    
    // 创建模板和自定义管理器
    auto templateManager = std::make_shared<TemplateManager>(context);
    auto customManager = std::make_shared<CustomManager>(context, templateManager.get());
    
    std::cout << "=== CHTL Unified Scanner Example ===" << std::endl;
    
    // 定义一些样式组和变量组用于测试
    auto buttonStyle = std::make_shared<StyleTemplate>("ButtonStyle");
    buttonStyle->addStyle("display", "inline-block");
    buttonStyle->addStyle("padding", "10px 20px");
    buttonStyle->addStyle("border-radius", "5px");
    buttonStyle->addStyle("cursor", "pointer");
    templateManager->registerTemplate(buttonStyle);
    
    auto colors = std::make_shared<VarTemplate>("Colors");
    colors->addVariable("primary", "#3498db");
    colors->addVariable("secondary", "#2ecc71");
    colors->addVariable("danger", "#e74c3c");
    templateManager->registerTemplate(colors);
    
    // 测试CHTL代码
    std::string chtlCode = R"(
-- 这是一个CHTL示例，展示统一扫描器的功能

[Template] @Style CardStyle
{
    background: white;
    border-radius: 8px;
    padding: 20px;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

html
{
    head
    {
        title: "CHTL Scanner Demo";
        
        -- 全局样式块，包含样式组和变量组
        style
        {
            /* 基础样式 */
            body {
                margin: 0;
                padding: 20px;
                background-color: Colors(primary);
            }
            
            .button {
                @Style ButtonStyle;
                background-color: Colors(secondary);
                color: white;
            }
            
            -- CSS中的生成性注释
            .card {
                @Style CardStyle;
            }
        }
    }
    
    body
    {
        div
        {
            class: "container";
            
            -- HTML上下文中的注释
            h1
            {
                text
                {
                    "CHTL Unified Scanner"
                }
            }
            
            -- JavaScript块
            script
            {
                // JavaScript注释
                const app = {
                    name: 'CHTL Demo',
                    version: '1.0.0'
                };
                
                -- JS中的生成性注释
                function init() {
                    console.log('Initializing ' + app.name);
                }
                
                /* 多行注释
                   测试注释处理 */
                init();
            }
            
            div
            {
                class: "card";
                
                style
                {
                    -- 局部样式块中的注释
                    background: Colors(secondary);
                    color: white;
                }
                
                text
                {
                    "This is a demonstration of the unified scanner"
                }
            }
        }
    }
}
)";
    
    // 创建扫描器
    CHTLUnifiedScanner scanner(chtlCode, context);
    scanner.setTemplateManager(templateManager);
    scanner.setCustomManager(customManager);
    
    // 配置扫描器
    ScannerConfig config;
    config.processGenerativeComments = true;
    config.expandStyleGroups = true;
    config.expandVarGroups = true;
    scanner.setConfig(config);
    
    // 执行扫描
    std::cout << "\n--- Scanning CHTL Code ---" << std::endl;
    scanner.scan();
    
    // 显示扫描结果
    std::cout << "\n--- Token Stream ---" << std::endl;
    std::cout << std::left << std::setw(20) << "Type" 
              << std::setw(15) << "Context"
              << std::setw(10) << "Line:Col"
              << "Value" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    const auto& tokens = scanner.getTokens();
    for (const auto& token : tokens) {
        if (token.type == TokenType::Whitespace || 
            token.type == TokenType::NewLine) {
            continue; // 跳过空白和换行以简化输出
        }
        
        std::cout << std::left << std::setw(20) << ScannerHelper::tokenTypeToString(token.type)
                  << std::setw(15) << ScannerHelper::contextToString(token.context)
                  << std::setw(10) << (std::to_string(token.line) + ":" + std::to_string(token.column));
        
        // 截断长值
        std::string value = token.value;
        if (value.length() > 40) {
            value = value.substr(0, 37) + "...";
        }
        // 替换换行符
        size_t pos = 0;
        while ((pos = value.find('\n')) != std::string::npos) {
            value.replace(pos, 1, "\\n");
        }
        
        std::cout << value << std::endl;
    }
    
    // 测试生成性注释处理
    std::cout << "\n--- Testing Generative Comments ---" << std::endl;
    
    GenerativeCommentProcessor commentProcessor(context);
    
    std::cout << "\nHTML Context:" << std::endl;
    std::string htmlComment = commentProcessor.processComment("This is a test comment", LanguageContext::HTML);
    std::cout << htmlComment << std::endl;
    
    std::cout << "\nCSS Context:" << std::endl;
    std::string cssComment = commentProcessor.processComment("Style information for the card component", LanguageContext::CSS);
    std::cout << cssComment << std::endl;
    
    std::cout << "\nJavaScript Context:" << std::endl;
    std::string jsComment = commentProcessor.processComment("Initialize the application", LanguageContext::JavaScript);
    std::cout << jsComment << std::endl;
    
    std::cout << "\nMulti-line JavaScript Comment:" << std::endl;
    std::string multilineJS = commentProcessor.processComment(
        "This is a longer comment\nthat spans multiple lines\nand should be formatted nicely", 
        LanguageContext::JavaScript
    );
    std::cout << multilineJS << std::endl;
    
    // 测试上下文推导
    std::cout << "\n--- Testing Context Inference ---" << std::endl;
    
    ScannerContextInferencer inferencer;
    
    inferencer.enterElement("div");
    std::cout << "After entering 'div': " << ScannerHelper::contextToString(inferencer.inferContext()) << std::endl;
    
    inferencer.enterElement("style");
    std::cout << "After entering 'style': " << ScannerHelper::contextToString(inferencer.inferContext()) << std::endl;
    
    inferencer.exitElement();
    std::cout << "After exiting 'style': " << ScannerHelper::contextToString(inferencer.inferContext()) << std::endl;
    
    inferencer.enterElement("script");
    std::cout << "After entering 'script': " << ScannerHelper::contextToString(inferencer.inferContext()) << std::endl;
    
    // 测试内容推导
    std::cout << "\n--- Testing Content-Based Context Inference ---" << std::endl;
    
    std::string cssContent = "body { margin: 0; padding: 10px; }";
    std::cout << "CSS-like content: " << ScannerHelper::contextToString(
        ScannerHelper::inferContextFromContent(cssContent)) << std::endl;
    
    std::string jsContent = "function test() { return 42; }";
    std::cout << "JS-like content: " << ScannerHelper::contextToString(
        ScannerHelper::inferContextFromContent(jsContent)) << std::endl;
    
    std::string htmlContent = "<div class='test'>Hello</div>";
    std::cout << "HTML-like content: " << ScannerHelper::contextToString(
        ScannerHelper::inferContextFromContent(htmlContent)) << std::endl;
    
    // 显示警告
    auto warnings = context->getWarnings();
    if (!warnings.empty()) {
        std::cout << "\n=== Warnings ===" << std::endl;
        for (const auto& warning : warnings) {
            std::cout << "Warning: " << warning << std::endl;
        }
    }
    
    return 0;
}