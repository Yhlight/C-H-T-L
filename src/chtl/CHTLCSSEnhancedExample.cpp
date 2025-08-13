#include "CHTLContext.h"
#include "CHTLGenerator.h"
#include "CHTLTemplate.h"
#include "CHTLCustom.h"
#include <iostream>

using namespace chtl;

int main() {
    // 创建上下文
    auto context = std::make_shared<CHTLContext>();
    
    // 创建生成器
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 获取管理器
    auto templateManager = generator.getTemplateManager();
    auto customManager = generator.getCustomManager();
    
    std::cout << "=== CHTL Enhanced CSS Example ===" << std::endl;
    
    // 定义样式组模板
    std::cout << "\n--- Defining Style Group Templates ---" << std::endl;
    
    // 文本样式组
    auto textStyle = std::make_shared<StyleTemplate>("DefaultText");
    textStyle->addStyle("font-family", "Arial, sans-serif");
    textStyle->addStyle("line-height", "1.6");
    textStyle->addStyle("color", "#333");
    templateManager->registerTemplate(textStyle);
    
    // 按钮样式组
    auto buttonStyle = std::make_shared<StyleTemplate>("ButtonBase");
    buttonStyle->addStyle("display", "inline-block");
    buttonStyle->addStyle("padding", "10px 20px");
    buttonStyle->addStyle("border", "none");
    buttonStyle->addStyle("border-radius", "5px");
    buttonStyle->addStyle("cursor", "pointer");
    buttonStyle->addStyle("transition", "all 0.3s ease");
    templateManager->registerTemplate(buttonStyle);
    
    // 卡片样式组
    auto cardStyle = std::make_shared<StyleTemplate>("CardStyle");
    cardStyle->addStyle("background", "white");
    cardStyle->addStyle("border-radius", "8px");
    cardStyle->addStyle("padding", "20px");
    cardStyle->addStyle("box-shadow", "0 2px 4px rgba(0,0,0,0.1)");
    cardStyle->addStyle("margin-bottom", "20px");
    templateManager->registerTemplate(cardStyle);
    
    // 定义变量组模板
    std::cout << "\n--- Defining Variable Group Templates ---" << std::endl;
    
    // 主题颜色变量组
    auto themeColors = std::make_shared<VarTemplate>("ThemeColors");
    themeColors->addVariable("primary", "#3498db");
    themeColors->addVariable("secondary", "#2ecc71");
    themeColors->addVariable("danger", "#e74c3c");
    themeColors->addVariable("warning", "#f39c12");
    themeColors->addVariable("info", "#16a085");
    themeColors->addVariable("light", "#ecf0f1");
    themeColors->addVariable("dark", "#34495e");
    templateManager->registerTemplate(themeColors);
    
    // 尺寸变量组
    auto dimensions = std::make_shared<VarTemplate>("Spacing");
    dimensions->addVariable("xs", "5px");
    dimensions->addVariable("sm", "10px");
    dimensions->addVariable("md", "20px");
    dimensions->addVariable("lg", "30px");
    dimensions->addVariable("xl", "40px");
    templateManager->registerTemplate(dimensions);
    
    // 字体变量组
    auto fonts = std::make_shared<VarTemplate>("Typography");
    fonts->addVariable("headingFont", "'Helvetica Neue', Helvetica, Arial, sans-serif");
    fonts->addVariable("bodyFont", "Georgia, 'Times New Roman', serif");
    fonts->addVariable("codeFont", "'Courier New', Courier, monospace");
    fonts->addVariable("baseSize", "16px");
    fonts->addVariable("h1Size", "2.5rem");
    fonts->addVariable("h2Size", "2rem");
    fonts->addVariable("h3Size", "1.5rem");
    templateManager->registerTemplate(fonts);
    
    // 定义自定义样式组（带继承）
    std::cout << "\n--- Defining Custom Style Groups ---" << std::endl;
    
    // 主按钮样式（继承自ButtonBase）
    auto primaryButton = std::make_shared<CustomStyleGroup>("PrimaryButton");
    primaryButton->inherit("ButtonBase");
    primaryButton->addStyle("background-color", "ThemeColors(primary)");  // 使用变量组
    primaryButton->addStyle("color", "white");
    customManager->registerCustom(primaryButton);
    
    // 次要按钮样式
    auto secondaryButton = std::make_shared<CustomStyleGroup>("SecondaryButton");
    secondaryButton->inherit("ButtonBase");
    secondaryButton->addStyle("background-color", "ThemeColors(secondary)");
    secondaryButton->addStyle("color", "white");
    customManager->registerCustom(secondaryButton);
    
    // 开始生成HTML
    generator.generateElement("html", {});
    
    // head部分
    generator.generateElement("head", {});
    generator.generateElement("title", {});
    generator.generateText("Enhanced CSS with Style Groups and Variables");
    generator.closeElement(); // title
    
    // 全局样式块（使用样式组和变量组）
    std::string globalCSS = R"(
        /* 使用变量组设置CSS变量 */
        :root {
            --primary-color: ThemeColors(primary);
            --secondary-color: ThemeColors(secondary);
            --danger-color: ThemeColors(danger);
            --base-spacing: Spacing(md);
            --heading-font: Typography(headingFont);
            --body-font: Typography(bodyFont);
        }
        
        /* 基础样式 */
        body {
            @Style DefaultText;
            font-family: Typography(bodyFont);
            margin: 0;
            padding: Spacing(md);
            background-color: ThemeColors(light);
        }
        
        /* 标题样式 */
        h1, h2, h3 {
            font-family: Typography(headingFont);
            color: ThemeColors(dark);
            margin-bottom: Spacing(md);
        }
        
        h1 {
            font-size: Typography(h1Size);
        }
        
        h2 {
            font-size: Typography(h2Size);
        }
        
        h3 {
            font-size: Typography(h3Size);
        }
        
        /* 容器样式 */
        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: Spacing(lg);
        }
        
        /* 卡片组件 */
        .card {
            @Style CardStyle;
        }
        
        .card h3 {
            margin-top: 0;
            color: ThemeColors(primary);
        }
        
        /* 按钮样式 */
        .btn {
            @Style ButtonBase;
            margin-right: Spacing(sm);
        }
        
        .btn-primary {
            @Style PrimaryButton;
        }
        
        .btn-primary:hover {
            background-color: #2980b9;
            transform: translateY(-2px);
            box-shadow: 0 4px 8px rgba(0,0,0,0.2);
        }
        
        .btn-secondary {
            @Style SecondaryButton;
        }
        
        .btn-secondary:hover {
            background-color: #27ae60;
            transform: translateY(-2px);
            box-shadow: 0 4px 8px rgba(0,0,0,0.2);
        }
        
        /* 网格布局 */
        .grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: Spacing(md);
            margin-bottom: Spacing(lg);
        }
        
        /* 特性列表 */
        .features {
            list-style: none;
            padding: 0;
        }
        
        .features li {
            padding: Spacing(sm) 0;
            border-bottom: 1px solid ThemeColors(light);
        }
        
        .features li:before {
            content: "✓ ";
            color: ThemeColors(secondary);
            font-weight: bold;
            margin-right: Spacing(xs);
        }
        
        /* 代码块 */
        .code-example {
            background-color: #f8f8f8;
            border: 1px solid #ddd;
            border-radius: 4px;
            padding: Spacing(md);
            font-family: Typography(codeFont);
            font-size: 14px;
            overflow-x: auto;
            margin: Spacing(md) 0;
        }
        
        /* 响应式设计 */
        @media (max-width: 768px) {
            .container {
                padding: Spacing(md);
            }
            
            .grid {
                grid-template-columns: 1fr;
            }
            
            h1 {
                font-size: 2rem;
            }
        }
    )";
    
    generator.processGlobalStyleBlock(globalCSS);
    
    generator.closeElement(); // head
    
    // body部分
    generator.generateElement("body", {});
    
    generator.generateElement("div", {{"class", "container"}});
    
    // 标题
    generator.generateElement("h1", {});
    generator.generateText("CHTL Enhanced CSS Features");
    generator.closeElement();
    
    generator.generateElement("p", {});
    generator.generateText("This example demonstrates the use of Style Groups and Variable Groups in global CSS blocks.");
    generator.closeElement();
    
    // 特性展示
    generator.generateElement("div", {{"class", "grid"}});
    
    // 卡片1
    generator.generateElement("div", {{"class", "card"}});
    generator.generateElement("h3", {});
    generator.generateText("Style Groups");
    generator.closeElement();
    generator.generateElement("p", {});
    generator.generateText("Reusable style definitions that can be applied with @Style directive.");
    generator.closeElement();
    generator.generateElement("ul", {{"class", "features"}});
    generator.generateElement("li", {});
    generator.generateText("Define once, use anywhere");
    generator.closeElement();
    generator.generateElement("li", {});
    generator.generateText("Support inheritance");
    generator.closeElement();
    generator.generateElement("li", {});
    generator.generateText("Template and Custom variants");
    generator.closeElement();
    generator.closeElement(); // ul
    generator.closeElement(); // card
    
    // 卡片2
    generator.generateElement("div", {{"class", "card"}});
    generator.generateElement("h3", {});
    generator.generateText("Variable Groups");
    generator.closeElement();
    generator.generateElement("p", {});
    generator.generateText("Centralized value management with VarGroup(varName) syntax.");
    generator.closeElement();
    generator.generateElement("ul", {{"class", "features"}});
    generator.generateElement("li", {});
    generator.generateText("Consistent theming");
    generator.closeElement();
    generator.generateElement("li", {});
    generator.generateText("Easy maintenance");
    generator.closeElement();
    generator.generateElement("li", {});
    generator.generateText("Type-safe values");
    generator.closeElement();
    generator.closeElement(); // ul
    generator.closeElement(); // card
    
    // 卡片3
    generator.generateElement("div", {{"class", "card"}});
    generator.generateElement("h3", {});
    generator.generateText("Context Inference");
    generator.closeElement();
    generator.generateElement("p", {});
    generator.generateText("Smart detection of appropriate style groups and variables based on context.");
    generator.closeElement();
    generator.generateElement("ul", {{"class", "features"}});
    generator.generateElement("li", {});
    generator.generateText("Property-based suggestions");
    generator.closeElement();
    generator.generateElement("li", {});
    generator.generateText("Automatic type detection");
    generator.closeElement();
    generator.generateElement("li", {});
    generator.generateText("IDE-friendly");
    generator.closeElement();
    generator.closeElement(); // ul
    generator.closeElement(); // card
    
    generator.closeElement(); // grid
    
    // 代码示例
    generator.generateElement("h2", {});
    generator.generateText("Example Usage");
    generator.closeElement();
    
    generator.generateElement("div", {{"class", "code-example"}});
    generator.generateElement("pre", {});
    generator.generateText(R"(/* Define a style group */
[Template] @Style CardStyle
{
    background: white;
    border-radius: 8px;
    padding: 20px;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

/* Use in CSS */
.card {
    @Style CardStyle;
    margin-bottom: Spacing(md);
}

/* Use variables */
.button {
    background-color: ThemeColors(primary);
    padding: Spacing(sm) Spacing(md);
})");
    generator.closeElement(); // pre
    generator.closeElement(); // code-example
    
    // 按钮示例
    generator.generateElement("h2", {});
    generator.generateText("Button Examples");
    generator.closeElement();
    
    generator.generateElement("div", {});
    generator.generateElement("button", {{"class", "btn btn-primary"}});
    generator.generateText("Primary Button");
    generator.closeElement();
    
    generator.generateElement("button", {{"class", "btn btn-secondary"}});
    generator.generateText("Secondary Button");
    generator.closeElement();
    generator.closeElement(); // div
    
    generator.closeElement(); // container
    generator.closeElement(); // body
    generator.closeElement(); // html
    
    // 输出生成的HTML
    std::cout << "\n=== Generated HTML ===" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 输出最终的CSS
    std::cout << "\n=== Final CSS (with expanded style groups and variables) ===" << std::endl;
    std::cout << generator.getCSS() << std::endl;
    
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