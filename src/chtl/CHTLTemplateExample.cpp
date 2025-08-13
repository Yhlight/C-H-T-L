#include "CHTLGenerator.h"
#include "CHTLTemplate.h"
#include <iostream>

using namespace chtl;

// 示例：演示CHTL模板系统的使用
int main() {
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 获取模板管理器
    auto templateManager = generator.getTemplateManager();
    
    // 示例1：样式组模板
    std::cout << "=== 示例1：样式组模板 ===" << std::endl;
    
    // 定义样式组模板
    templateManager->setTemplateState(TemplateState::DEFINITION);
    
    auto defaultTextStyle = std::make_shared<StyleTemplate>("DefaultText");
    defaultTextStyle->addStyle("color", "black");
    defaultTextStyle->addStyle("line-height", "1.6");
    defaultTextStyle->addStyle("font-family", "Arial, sans-serif");
    templateManager->registerStyleTemplate("DefaultText", defaultTextStyle);
    
    templateManager->setTemplateState(TemplateState::USE);
    
    // 使用样式组模板
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    generator.useTemplate("@Style DefaultText");
    generator.generateInlineStyle("font-size", "16px");  // 额外的样式
    generator.endStyleBlock();
    generator.beginTextBlock();
    generator.generateTextNode("这是使用样式模板的文本");
    generator.endTextBlock();
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例2：元素模板
    std::cout << "\n=== 示例2：元素模板 ===" << std::endl;
    generator.reset();
    
    templateManager->setTemplateState(TemplateState::DEFINITION);
    
    auto boxTemplate = std::make_shared<ElementTemplate>("Box");
    // 在实际实现中，这里会添加元素节点
    // boxTemplate->addElement(...);
    templateManager->registerElementTemplate("Box", boxTemplate);
    
    templateManager->setTemplateState(TemplateState::USE);
    
    // 使用元素模板
    generator.generateElement("body", {});
    generator.useTemplate("@Element Box");
    generator.closeElement();
    
    // 示例3：变量组模板
    std::cout << "\n=== 示例3：变量组模板 ===" << std::endl;
    generator.reset();
    
    templateManager->setTemplateState(TemplateState::DEFINITION);
    
    auto themeColorTemplate = std::make_shared<VarTemplate>("ThemeColor");
    themeColorTemplate->addVariable("tableColor", "rgb(255, 192, 203)");
    themeColorTemplate->addVariable("bgColor", "rgba(253, 144, 162, 1)");
    themeColorTemplate->addVariable("textColor", "#333");
    templateManager->registerVarTemplate("ThemeColor", themeColorTemplate);
    
    templateManager->setTemplateState(TemplateState::USE);
    
    // 使用变量组模板
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    // 使用变量
    std::string bgColor = generator.processVariableReference("ThemeColor(bgColor)");
    std::string textColor = generator.processVariableReference("ThemeColor(textColor)");
    generator.generateInlineStyle("background-color", bgColor);
    generator.generateInlineStyle("color", textColor);
    generator.endStyleBlock();
    generator.beginTextBlock();
    generator.generateTextNode("使用主题颜色的文本");
    generator.endTextBlock();
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例4：模板继承
    std::cout << "\n=== 示例4：模板继承 ===" << std::endl;
    generator.reset();
    
    templateManager->setTemplateState(TemplateState::DEFINITION);
    
    // 基础主题样式
    auto themeStyle = std::make_shared<StyleTemplate>("ThemeStyle");
    themeStyle->addStyle("color", "rgba(255, 192, 203, 1)");
    themeStyle->addStyle("background-color", "rgba(253, 144, 162, 1)");
    themeStyle->addStyle("padding", "10px");
    templateManager->registerStyleTemplate("ThemeStyle", themeStyle);
    
    // 继承的样式
    auto themeStyle2 = std::make_shared<StyleTemplate>("ThemeStyle2");
    themeStyle2->addStyle("background-color", "yellow");  // 覆盖父样式
    themeStyle2->addStyle("border", "1px solid black");   // 新增样式
    themeStyle2->inheritFrom("ThemeStyle");  // 继承ThemeStyle
    templateManager->registerStyleTemplate("ThemeStyle2", themeStyle2);
    
    templateManager->setTemplateState(TemplateState::USE);
    
    // 使用继承的样式
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    generator.useTemplate("@Style ThemeStyle2");
    generator.endStyleBlock();
    generator.beginTextBlock();
    generator.generateTextNode("使用继承样式的元素");
    generator.endTextBlock();
    generator.closeElement();
    
    std::cout << "完整输出：" << std::endl;
    std::cout << generator.getCombinedOutput() << std::endl;
    
    // 示例5：全缀名使用
    std::cout << "\n=== 示例5：全缀名使用 ===" << std::endl;
    generator.reset();
    
    // 使用不同的全缀名形式访问模板
    generator.generateElement("div", {});
    
    // 简单名称
    std::cout << "尝试查找 'ThemeStyle': " 
              << (templateManager->findStyleTemplate("ThemeStyle") != nullptr) << std::endl;
    
    // 部分限定名
    std::cout << "尝试查找 '@Style ThemeStyle': " 
              << (templateManager->findStyleTemplate("@Style ThemeStyle") != nullptr) << std::endl;
    
    // 完全限定名
    std::cout << "尝试查找 '[Template] @Style ThemeStyle': " 
              << (templateManager->findStyleTemplate("[Template] @Style ThemeStyle") != nullptr) << std::endl;
    
    generator.closeElement();
    
    // 示例6：全缀名解析器
    std::cout << "\n=== 示例6：全缀名解析器 ===" << std::endl;
    
    QualifiedNameResolver resolver;
    
    // 测试不同格式的解析
    std::vector<std::string> testNames = {
        "Box",
        "@Element Box",
        "[Template] @Style DefaultText",
        "[Custom] @Element MyElement"
    };
    
    for (const auto& name : testNames) {
        if (resolver.parse(name)) {
            std::cout << "解析 '" << name << "':" << std::endl;
            std::cout << "  前缀: " << resolver.getPrefix() << std::endl;
            std::cout << "  类型: " << resolver.getType() << std::endl;
            std::cout << "  名称: " << resolver.getName() << std::endl;
            std::cout << "  完整名: " << resolver.buildFullName() << std::endl;
            std::cout << "  部分名: " << resolver.buildPartialName() << std::endl;
        }
    }
    
    return 0;
}

/* 预期输出示例：

=== 示例1：样式组模板 ===
HTML输出：
<div style="color: black; line-height: 1.6; font-family: Arial, sans-serif; font-size: 16px;">
  这是使用样式模板的文本
</div>

=== 示例3：变量组模板 ===
HTML输出：
<div style="background-color: rgba(253, 144, 162, 1); color: #333;">
  使用主题颜色的文本
</div>

=== 示例4：模板继承 ===
样式会继承padding和color，但background-color会被覆盖为yellow

=== 示例5：全缀名使用 ===
所有三种形式都应该能找到模板

=== 示例6：全缀名解析器 ===
展示不同格式的解析结果

*/