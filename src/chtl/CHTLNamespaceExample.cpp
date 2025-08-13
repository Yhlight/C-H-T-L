#include "CHTLGenerator.h"
#include "CHTLNamespace.h"
#include <iostream>

using namespace chtl;

// 示例：演示CHTL命名空间的使用
int main() {
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 获取命名空间管理器
    auto namespaceManager = generator.getNamespaceManager();
    auto templateManager = generator.getTemplateManager();
    auto customManager = generator.getCustomManager();
    
    // 示例1：基本命名空间
    std::cout << "=== 示例1：基本命名空间 ===" << std::endl;
    
    // 创建命名空间
    generator.processNamespaceDeclaration("[Namespace] space");
    
    // 在命名空间中定义自定义元素
    generator.beginCustomDefinition("@Element", "Box");
    generator.generateElement("div", {{"class", "box"}});
    generator.beginStyleBlock();
    generator.generateInlineStyle("width", "200px");
    generator.generateInlineStyle("height", "200px");
    generator.generateInlineStyle("border", "1px solid black");
    generator.endStyleBlock();
    generator.closeElement();
    generator.endCustomDefinition();
    
    // 注册到命名空间
    auto boxDef = customManager->findCustom("@Element Box");
    if (boxDef) {
        namespaceManager->registerItem("Box", NamespaceItemType::CUSTOM_ELEMENT, boxDef);
    }
    
    // 结束命名空间
    generator.endNamespace();
    
    // 使用命名空间中的元素
    generator.generateElement("body", {});
    generator.useCustomFromNamespace("Box", "space");
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例2：嵌套命名空间
    std::cout << "\n=== 示例2：嵌套命名空间 ===" << std::endl;
    generator.reset();
    
    // 创建嵌套命名空间
    generator.processNamespaceDeclaration("[Namespace] ui");
    generator.processNamespaceDeclaration("[Namespace] components");
    
    // 在嵌套命名空间中定义模板
    generator.beginTemplateDefinition("@Style", "ButtonStyle");
    templateManager->addTemplateStyle("ButtonStyle", "padding", "10px 20px");
    templateManager->addTemplateStyle("ButtonStyle", "background", "#007bff");
    templateManager->addTemplateStyle("ButtonStyle", "color", "white");
    templateManager->addTemplateStyle("ButtonStyle", "border", "none");
    templateManager->addTemplateStyle("ButtonStyle", "border-radius", "4px");
    generator.endTemplateDefinition();
    
    // 注册到命名空间
    auto buttonStyle = templateManager->findTemplate("@Style ButtonStyle");
    if (buttonStyle) {
        namespaceManager->registerItem("ButtonStyle", NamespaceItemType::TEMPLATE_STYLE, buttonStyle);
    }
    
    generator.endNamespace(); // 结束 components
    generator.endNamespace(); // 结束 ui
    
    // 使用嵌套命名空间中的模板
    generator.generateElement("button", {});
    generator.beginStyleBlock();
    generator.useTemplateFromNamespace("ButtonStyle", "ui.components");
    generator.endStyleBlock();
    generator.generateTextNode("Click Me");
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例3：文件默认命名空间
    std::cout << "\n=== 示例3：文件默认命名空间 ===" << std::endl;
    generator.reset();
    
    // 设置文件默认命名空间
    namespaceManager->setFileDefaultNamespace("test.chtl", "test");
    
    // 创建与文件名相同的命名空间
    auto testNs = namespaceManager->getOrCreateNamespace("test");
    
    // 在test命名空间中定义内容
    namespaceManager->beginNamespace("test");
    
    generator.beginCustomDefinition("@Element", "Card");
    generator.generateElement("div", {{"class", "card"}});
    generator.generateElement("h3", {{"class", "card-title"}});
    generator.generateTextNode("Card Title");
    generator.closeElement();
    generator.generateElement("div", {{"class", "card-body"}});
    generator.generateTextNode("Card content");
    generator.closeElement();
    generator.closeElement();
    generator.endCustomDefinition();
    
    auto cardDef = customManager->findCustom("@Element Card");
    if (cardDef) {
        namespaceManager->registerItem("Card", NamespaceItemType::CUSTOM_ELEMENT, cardDef);
    }
    
    namespaceManager->endNamespace();
    
    // 使用文件默认命名空间
    std::string defaultNs = namespaceManager->getFileDefaultNamespace("test.chtl");
    generator.useCustomFromNamespace("Card", defaultNs);
    
    std::cout << "使用文件默认命名空间 '" << defaultNs << "' 中的Card元素" << std::endl;
    
    // 示例4：命名空间合并
    std::cout << "\n=== 示例4：命名空间合并 ===" << std::endl;
    generator.reset();
    
    // 创建第一个space命名空间
    generator.processNamespaceDeclaration("[Namespace] shared");
    
    generator.beginTemplateDefinition("@Style", "TextStyle");
    templateManager->addTemplateStyle("TextStyle", "font-size", "16px");
    templateManager->addTemplateStyle("TextStyle", "line-height", "1.6");
    generator.endTemplateDefinition();
    
    auto textStyle = templateManager->findTemplate("@Style TextStyle");
    if (textStyle) {
        namespaceManager->registerItem("TextStyle", NamespaceItemType::TEMPLATE_STYLE, textStyle);
    }
    
    generator.endNamespace();
    
    // 创建第二个同名命名空间（会合并）
    generator.processNamespaceDeclaration("[Namespace] shared");
    
    generator.beginTemplateDefinition("@Style", "ColorStyle");
    templateManager->addTemplateStyle("ColorStyle", "color", "#333");
    templateManager->addTemplateStyle("ColorStyle", "background", "#f8f9fa");
    generator.endTemplateDefinition();
    
    auto colorStyle = templateManager->findTemplate("@Style ColorStyle");
    if (colorStyle) {
        namespaceManager->registerItem("ColorStyle", NamespaceItemType::TEMPLATE_STYLE, colorStyle);
    }
    
    generator.endNamespace();
    
    // 使用合并后的命名空间
    std::cout << "命名空间 'shared' 现在包含 TextStyle 和 ColorStyle" << std::endl;
    
    // 示例5：from语法使用
    std::cout << "\n=== 示例5：from语法使用 ===" << std::endl;
    generator.reset();
    
    // 创建多个命名空间
    generator.processNamespaceDeclaration("[Namespace] layout");
    
    generator.beginCustomDefinition("@Element", "Header");
    generator.generateElement("header", {});
    generator.generateElement("h1", {});
    generator.generateTextNode("Site Header");
    generator.closeElement();
    generator.closeElement();
    generator.endCustomDefinition();
    
    auto headerDef = customManager->findCustom("@Element Header");
    if (headerDef) {
        namespaceManager->registerItem("Header", NamespaceItemType::CUSTOM_ELEMENT, headerDef);
    }
    
    generator.endNamespace();
    
    generator.processNamespaceDeclaration("[Namespace] components");
    
    generator.beginCustomDefinition("@Element", "Header");  // 同名但在不同命名空间
    generator.generateElement("div", {{"class", "component-header"}});
    generator.generateTextNode("Component Header");
    generator.closeElement();
    generator.endCustomDefinition();
    
    auto compHeaderDef = customManager->findCustom("@Element Header");
    if (compHeaderDef) {
        namespaceManager->registerItem("Header", NamespaceItemType::CUSTOM_ELEMENT, compHeaderDef);
    }
    
    generator.endNamespace();
    
    // 使用from语法区分
    generator.generateElement("body", {});
    
    // 使用layout命名空间的Header
    NamespaceProcessor processor(*namespaceManager, generator);
    processor.processNamespacedUse("Header from layout", NamespaceItemType::CUSTOM_ELEMENT);
    
    // 使用components命名空间的Header
    processor.processNamespacedUse("Header from components", NamespaceItemType::CUSTOM_ELEMENT);
    
    generator.closeElement();
    
    std::cout << "使用from语法区分不同命名空间中的同名元素" << std::endl;
    
    // 示例6：冲突检测
    std::cout << "\n=== 示例6：冲突检测 ===" << std::endl;
    
    // 检测命名空间冲突
    auto conflicts = namespaceManager->detectConflicts("shared");
    if (conflicts.empty()) {
        std::cout << "命名空间 'shared' 没有冲突" << std::endl;
    } else {
        std::cout << "检测到冲突：" << std::endl;
        for (const auto& conflict : conflicts) {
            std::cout << "  - " << conflict << std::endl;
        }
    }
    
    return 0;
}

/* 预期输出示例：

=== 示例1：基本命名空间 ===
HTML输出：
<body>
  <div class="box" style="width: 200px; height: 200px; border: 1px solid black;"></div>
</body>

=== 示例2：嵌套命名空间 ===
HTML输出：
<button style="padding: 10px 20px; background: #007bff; color: white; border: none; border-radius: 4px;">Click Me</button>

=== 示例3：文件默认命名空间 ===
使用文件默认命名空间 'test' 中的Card元素

=== 示例4：命名空间合并 ===
命名空间 'shared' 现在包含 TextStyle 和 ColorStyle

=== 示例5：from语法使用 ===
使用from语法区分不同命名空间中的同名元素

=== 示例6：冲突检测 ===
命名空间 'shared' 没有冲突

*/