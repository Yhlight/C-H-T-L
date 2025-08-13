#include "CHTLGenerator.h"
#include <iostream>

using namespace chtl;

// 示例：演示CHTL生成器的使用
int main() {
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    options.preserveGeneratorComments = true;
    options.extractStyleToGlobal = true;
    
    CHTLGenerator generator(context, options);
    
    // 示例1：基本元素和文本节点
    std::cout << "=== 示例1：基本元素和文本节点 ===" << std::endl;
    generator.reset();
    
    // 处理注释
    generator.processGeneratorComment("这是一个会被生成的注释");
    generator.processSingleLineComment("// 这个注释不会被生成");
    generator.processMultiLineComment("/* 这个多行注释也不会被生成 */");
    
    // div元素
    std::unordered_map<std::string, std::string> divAttrs = {
        {"id", "box"},        // 支持无引号字面量
        {"class", "welcome"}  // CE对等式：可以用:或=
    };
    generator.generateElement("div", divAttrs);
    
    // text块
    generator.beginTextBlock();
    generator.generateTextNode("HelloWorld");  // 支持无引号字面量
    generator.generateTextNode("\"这是带引号的文本\"");
    generator.generateTextNode("'单引号文本'");
    generator.endTextBlock();
    
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例2：局部样式块 - 内联样式
    std::cout << "\n=== 示例2：局部样式块 - 内联样式 ===" << std::endl;
    generator.reset();
    
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    
    // 内联样式
    generator.generateInlineStyle("width", "100px");
    generator.generateInlineStyle("height", "200px");
    generator.generateInlineStyle("background-color", "red");  // 支持无引号
    
    generator.endStyleBlock();
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例3：自动化类名
    std::cout << "\n=== 示例3：自动化类名 ===" << std::endl;
    generator.reset();
    
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    
    // 类选择器 - 自动添加类名到元素
    std::vector<std::pair<std::string, std::string>> boxStyles = {
        {"width", "300px"},
        {"height", "150px"},
        {"border", "1px solid black"}
    };
    generator.generateClassRule("box", boxStyles);
    
    generator.endStyleBlock();
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    std::cout << "CSS输出：" << std::endl;
    std::cout << generator.getCSS() << std::endl;
    
    // 示例4：上下文推导与伪类
    std::cout << "\n=== 示例4：上下文推导与伪类 ===" << std::endl;
    generator.reset();
    
    generator.generateElement("button", {});
    generator.beginStyleBlock();
    
    // 自动添加类名
    std::vector<std::pair<std::string, std::string>> buttonStyles = {
        {"padding", "10px 20px"},
        {"background", "blue"},
        {"color", "white"},
        {"border", "none"},
        {"cursor", "pointer"}
    };
    generator.generateClassRule("btn-primary", buttonStyles);
    
    // 使用&符号的伪类
    std::vector<std::pair<std::string, std::string>> hoverStyles = {
        {"background", "darkblue"},
        {"transform", "scale(1.05)"}
    };
    generator.generatePseudoRule(":hover", hoverStyles);
    
    // 伪元素
    std::vector<std::pair<std::string, std::string>> beforeStyles = {
        {"content", "\"→\""},
        {"margin-right", "5px"}
    };
    generator.generatePseudoRule("::before", beforeStyles);
    
    generator.endStyleBlock();
    
    generator.beginTextBlock();
    generator.generateTextNode("点击我");
    generator.endTextBlock();
    
    generator.closeElement();
    
    std::cout << "完整输出：" << std::endl;
    std::cout << generator.getCombinedOutput() << std::endl;
    
    // 示例5：复杂嵌套结构
    std::cout << "\n=== 示例5：复杂嵌套结构 ===" << std::endl;
    generator.reset();
    
    generator.processGeneratorComment("页面主体结构");
    
    generator.generateElement("html", {});
    generator.generateElement("head", {});
    generator.closeElement();  // </head>
    
    generator.generateElement("body", {});
    
    // 容器div
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    
    // 容器样式
    std::vector<std::pair<std::string, std::string>> containerStyles = {
        {"max-width", "1200px"},
        {"margin", "0 auto"},
        {"padding", "20px"}
    };
    generator.generateClassRule("container", containerStyles);
    generator.endStyleBlock();
    
    // 嵌套的span
    generator.generateElement("span", {});
    generator.beginStyleBlock();
    
    // ID选择器 - 自动添加ID
    std::vector<std::pair<std::string, std::string>> titleStyles = {
        {"font-size", "24px"},
        {"font-weight", "bold"}
    };
    generator.generateIdRule("title", titleStyles);
    generator.endStyleBlock();
    
    generator.beginTextBlock();
    generator.generateTextNode("这是标题");
    generator.endTextBlock();
    generator.closeElement();  // </span>
    
    generator.closeElement();  // </div>
    generator.closeElement();  // </body>
    generator.closeElement();  // </html>
    
    std::cout << "完整HTML文档：" << std::endl;
    std::cout << generator.getCombinedOutput() << std::endl;
    
    return 0;
}

/* 预期输出示例：

=== 示例1：基本元素和文本节点 ===
HTML输出：
<!-- 这是一个会被生成的注释 -->
<div id="box" class="welcome">
  HelloWorld
  这是带引号的文本
  单引号文本
</div>

=== 示例3：自动化类名 ===
HTML输出：
<div class="box">
</div>
CSS输出：
.box {
  width: 300px;
  height: 150px;
  border: 1px solid black;
}

=== 示例4：上下文推导与伪类 ===
完整输出：
<!DOCTYPE html>
<html>
<head>
<style>
.btn-primary {
  padding: 10px 20px;
  background: blue;
  color: white;
  border: none;
  cursor: pointer;
}

.btn-primary:hover {
  background: darkblue;
  transform: scale(1.05);
}

.btn-primary::before {
  content: "→";
  margin-right: 5px;
}
</style>
</head>
<body>
<button class="btn-primary">
  点击我
</button>
</body>
</html>

*/