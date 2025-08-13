#include "CHTLGenerator.h"
#include "CHTLTemplate.h"
#include "CHTLCustom.h"
#include <iostream>

using namespace chtl;

// 示例：演示CHTL自定义系统的使用
int main() {
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 获取管理器
    auto templateManager = generator.getTemplateManager();
    auto customManager = generator.getCustomManager();
    
    // 示例1：无值样式组
    std::cout << "=== 示例1：无值样式组 ===" << std::endl;
    
    // 定义无值样式组
    auto textSetCustom = std::make_shared<CustomStyleGroup>("TextSet");
    textSetCustom->addValuelessProperty("color");
    textSetCustom->addValuelessProperty("font-size");
    customManager->registerCustomStyle("TextSet", textSetCustom);
    
    // 使用无值样式组（提供值）
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    
    std::unordered_map<std::string, std::string> providedValues = {
        {"color", "red"},
        {"font-size", "16px"}
    };
    generator.useCustom("@Style TextSet", providedValues);
    
    generator.endStyleBlock();
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例2：样式组特例化 - 删除属性
    std::cout << "\n=== 示例2：样式组特例化 - 删除属性 ===" << std::endl;
    generator.reset();
    
    // 创建基础模板
    auto whiteTextTemplate = std::make_shared<StyleTemplate>("WhiteText");
    whiteTextTemplate->addStyle("color", "white");
    whiteTextTemplate->addStyle("font-size", "16px");
    whiteTextTemplate->addStyle("line-height", "1.6");
    whiteTextTemplate->addStyle("border", "1px black solid");
    templateManager->registerStyleTemplate("WhiteText", whiteTextTemplate);
    
    // 创建自定义（继承并删除属性）
    auto yellowTextCustom = std::make_shared<CustomStyleGroup>("YellowText");
    yellowTextCustom->inheritFrom("WhiteText");
    yellowTextCustom->addStyle("color", "yellow");  // 覆盖颜色
    yellowTextCustom->addDeleteOperation({"line-height", "border"});  // 删除属性
    customManager->registerCustomStyle("YellowText", yellowTextCustom);
    
    // 使用自定义样式
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    generator.useCustom("@Style YellowText");
    generator.endStyleBlock();
    generator.beginTextBlock();
    generator.generateTextNode("黄色文本（无line-height和border）");
    generator.endTextBlock();
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例3：自定义元素特例化
    std::cout << "\n=== 示例3：自定义元素特例化 ===" << std::endl;
    generator.reset();
    
    // 创建自定义元素
    auto boxCustom = std::make_shared<CustomElement>("Box");
    
    // 添加元素
    auto div1 = std::make_shared<ElementTemplate::ElementNode>();
    div1->name = "div";
    div1->textContent = "第一个div";
    boxCustom->addElement(div1);
    
    auto div2 = std::make_shared<ElementTemplate::ElementNode>();
    div2->name = "div";
    div2->textContent = "第二个div";
    boxCustom->addElement(div2);
    
    auto span1 = std::make_shared<ElementTemplate::ElementNode>();
    span1->name = "span";
    span1->textContent = "span元素";
    boxCustom->addElement(span1);
    
    customManager->registerCustomElement("Box", boxCustom);
    
    // 使用自定义元素（带特例化）
    generator.generateElement("body", {});
    
    // 准备特例化操作
    std::vector<SpecializationOperation> specializations;
    
    // 为span添加样式的特例化
    CustomElement::ElementSpecialization spanSpec;
    spanSpec.selector = ElementSelector("span");
    spanSpec.additionalAttributes["class"] = "highlight";
    // 实际使用中会添加到specializations
    
    generator.useCustom("@Element Box");
    
    generator.closeElement();
    
    // 示例4：索引访问
    std::cout << "\n=== 示例4：索引访问 ===" << std::endl;
    
    // 测试元素选择器
    ElementSelector selector1 = ElementSelector::parse("div[1]");
    std::cout << "选择器 'div[1]' 解析结果：" << selector1.toString() << std::endl;
    std::cout << "匹配 div,0: " << selector1.matches("div", 0) << std::endl;
    std::cout << "匹配 div,1: " << selector1.matches("div", 1) << std::endl;
    
    // 示例5：插入操作
    std::cout << "\n=== 示例5：插入操作 ===" << std::endl;
    
    // 创建插入操作
    CustomElement::InsertOperation insertOp;
    insertOp.position = InsertPosition::AFTER;
    insertOp.targetSelector = ElementSelector("div", 0);
    
    auto newDiv = std::make_shared<ElementTemplate::ElementNode>();
    newDiv->name = "div";
    newDiv->textContent = "插入的新div";
    insertOp.elementsToInsert.push_back(newDiv);
    
    // 示例6：删除操作
    std::cout << "\n=== 示例6：删除操作 ===" << std::endl;
    
    // 创建删除操作
    CustomElement::DeleteOperation deleteOp;
    deleteOp.selectors.push_back(ElementSelector("span"));
    deleteOp.selectors.push_back(ElementSelector("div", 1));
    
    // 示例7：变量组特例化
    std::cout << "\n=== 示例7：变量组特例化 ===" << std::endl;
    generator.reset();
    
    // 创建自定义变量组
    auto themeColorCustom = std::make_shared<CustomVarGroup>("ThemeColor");
    themeColorCustom->addVariable("tableColor", "rgb(255, 192, 203)");
    themeColorCustom->addVariable("textColor", "black");
    themeColorCustom->markAsOverridable("tableColor");  // 允许覆盖
    customManager->registerCustomVar("ThemeColor", themeColorCustom);
    
    // 使用变量（带特例化）
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    
    // 使用默认值
    std::string defaultColor = customManager->useCustomVar("ThemeColor", "tableColor");
    generator.generateInlineStyle("background-color", defaultColor);
    
    // 使用特例化值
    std::string customColor = customManager->useCustomVar("ThemeColor", "tableColor", 
                                                         "rgb(145, 155, 200)");
    generator.generateInlineStyle("border-color", customColor);
    
    generator.endStyleBlock();
    generator.closeElement();
    
    std::cout << "完整输出：" << std::endl;
    std::cout << generator.getCombinedOutput() << std::endl;
    
    // 示例8：模板和自定义的相互继承
    std::cout << "\n=== 示例8：模板和自定义的相互继承 ===" << std::endl;
    
    // 创建互操作处理器
    CustomTemplateInterop interop(*customManager, *templateManager);
    
    // 测试类型兼容性
    std::cout << "类型兼容性测试：" << std::endl;
    std::cout << "@Style 和 @Style: " << interop.areTypesCompatible("@Style A", "@Style B") << std::endl;
    std::cout << "@Style 和 @Element: " << interop.areTypesCompatible("@Style A", "@Element B") << std::endl;
    
    return 0;
}

/* 预期输出示例：

=== 示例1：无值样式组 ===
HTML输出：
<div style="color: red; font-size: 16px;">
</div>

=== 示例2：样式组特例化 - 删除属性 ===
HTML输出：
<div style="color: yellow; font-size: 16px;">
  黄色文本（无line-height和border）
</div>

=== 示例3：自定义元素特例化 ===
展开Box自定义元素，包含两个div和一个span

=== 示例4：索引访问 ===
选择器解析和匹配测试结果

=== 示例7：变量组特例化 ===
展示变量的默认值和特例化值的使用

*/