#include "CHTLGenerator.h"
#include "CHTLImport.h"
#include <iostream>
#include <fstream>

using namespace chtl;

// 创建测试文件
void createTestFiles() {
    // 创建测试HTML文件
    std::ofstream htmlFile("test.html");
    htmlFile << R"(
<div class="imported-html">
    <h1>Imported HTML Content</h1>
    <p>This HTML was imported from an external file.</p>
</div>
)";
    htmlFile.close();
    
    // 创建测试CSS文件
    std::ofstream cssFile("styles.css");
    cssFile << R"(
/* Imported CSS styles */
.imported-style {
    color: #333;
    font-size: 16px;
    margin: 10px;
}

.highlight {
    background-color: yellow;
    font-weight: bold;
}
)";
    cssFile.close();
    
    // 创建测试JavaScript文件
    std::ofstream jsFile("script.js");
    jsFile << R"(
// Imported JavaScript code
function importedFunction() {
    console.log('This function was imported');
    return 42;
}

const importedConfig = {
    theme: 'dark',
    language: 'en'
};
)";
    jsFile.close();
    
    // 创建测试CHTL文件
    std::ofstream chtlFile("components.chtl");
    chtlFile << R"(
[Custom] @Element Card
{
    div.card
    {
        style
        {
            border: 1px solid #ccc;
            padding: 15px;
            margin: 10px;
        }
        
        h3.card-title
        {
            text { "Card Title" }
        }
        
        div.card-body
        {
            text { "Card content goes here" }
        }
    }
}

[Template] @Style ButtonStyle
{
    padding: 10px 20px;
    border: none;
    border-radius: 4px;
    cursor: pointer;
}

[Custom] @Var Colors
{
    primary: "#007bff";
    secondary: "#6c757d";
    success: "#28a745";
}
)";
    chtlFile.close();
    
    // 创建module目录
    std::filesystem::create_directory("module");
    
    // 创建模块文件
    std::ofstream moduleFile("module/utils.chtl");
    moduleFile << R"(
[Template] @Element Header
{
    header
    {
        style
        {
            background: #f8f9fa;
            padding: 20px;
        }
        
        h1 { text { "Site Header" } }
        nav { text { "Navigation" } }
    }
}
)";
    moduleFile.close();
}

// 示例：演示CHTL导入系统的使用
int main() {
    // 创建测试文件
    createTestFiles();
    
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 配置导入路径
    ImportPathConfig pathConfig;
    pathConfig.currentDirectory = std::filesystem::current_path();
    pathConfig.moduleDirectory = pathConfig.currentDirectory / "src" / "module";
    pathConfig.officialModulePath = ""; // 示例中不使用官方模块
    pathConfig.searchOfficialFirst = false;
    
    generator.configureImportPaths(pathConfig);
    
    // 示例1：导入HTML文件（带as子句）
    std::cout << "=== 示例1：导入HTML文件 ===" << std::endl;
    
    generator.processImportStatement("[Import] @Html from test.html as importedHtml");
    
    // 使用导入的HTML
    generator.generateElement("body", {});
    generator.useOriginBlock("importedHtml");
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例2：导入CSS文件（带as子句）
    std::cout << "\n=== 示例2：导入CSS文件 ===" << std::endl;
    generator.reset();
    
    generator.processImportStatement("[Import] @Style from styles.css as importedStyles");
    
    // 使用导入的样式
    generator.generateElement("head", {});
    generator.generateElement("style", {});
    generator.useOriginBlock("importedStyles");
    generator.closeElement();
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例3：导入JavaScript文件（带as子句）
    std::cout << "\n=== 示例3：导入JavaScript文件 ===" << std::endl;
    generator.reset();
    
    generator.processImportStatement("[Import] @JavaScript from script.js as importedScript");
    
    // 使用导入的脚本
    generator.generateElement("script", {});
    generator.useOriginBlock("importedScript");
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例4：导入自定义元素
    std::cout << "\n=== 示例4：导入自定义元素 ===" << std::endl;
    generator.reset();
    
    generator.processImportStatement("[Import] [Custom] @Element Card from components.chtl");
    
    // 使用导入的自定义元素
    generator.generateElement("div", {{"class", "container"}});
    // TODO: 使用导入的Card自定义元素
    // generator.useCustom("@Element Card");
    generator.closeElement();
    
    // 示例5：导入模板
    std::cout << "\n=== 示例5：导入模板 ===" << std::endl;
    generator.reset();
    
    generator.processImportStatement("[Import] [Template] @Style ButtonStyle from components.chtl");
    
    // 使用导入的模板
    generator.generateElement("button", {});
    generator.beginStyleBlock();
    // TODO: 使用导入的ButtonStyle模板
    // generator.useTemplate("@Style ButtonStyle");
    generator.endStyleBlock();
    generator.generateTextNode("Click Me");
    generator.closeElement();
    
    // 示例6：导入变量组
    std::cout << "\n=== 示例6：导入变量组 ===" << std::endl;
    generator.reset();
    
    generator.processImportStatement("[Import] [Custom] @Var Colors from components.chtl");
    
    // 使用导入的变量
    generator.generateElement("div", {});
    generator.beginStyleBlock();
    // TODO: 使用导入的Colors变量
    // std::string primaryColor = generator.processVariableReference("Colors(primary)");
    // generator.generateInlineStyle("color", primaryColor);
    generator.endStyleBlock();
    generator.closeElement();
    
    // 示例7：导入整个CHTL文件
    std::cout << "\n=== 示例7：导入整个CHTL文件 ===" << std::endl;
    generator.reset();
    
    generator.processImportStatement("[Import] @Chtl from components");
    
    std::cout << "导入了components.chtl中的所有定义" << std::endl;
    
    // 示例8：从module目录导入
    std::cout << "\n=== 示例8：从module目录导入 ===" << std::endl;
    generator.reset();
    
    generator.processImportStatement("[Import] @Chtl from utils");
    
    std::cout << "从module目录导入了utils.chtl" << std::endl;
    
    // 示例9：带as子句的模板导入
    std::cout << "\n=== 示例9：带as子句的导入 ===" << std::endl;
    generator.reset();
    
    generator.processImportStatement("[Import] [Template] @Element Header from utils as SiteHeader");
    
    // 使用别名访问
    // TODO: 使用别名SiteHeader
    
    // 示例10：批量导入
    std::cout << "\n=== 示例10：批量导入 ===" << std::endl;
    generator.reset();
    
    std::vector<std::string> imports = {
        "[Import] @Html from test.html as html1",
        "[Import] @Style from styles.css as css1",
        "[Import] @JavaScript from script.js as js1"
    };
    
    generator.processImports(imports);
    
    std::cout << "批量导入了多个文件" << std::endl;
    
    // 清理测试文件
    std::filesystem::remove("test.html");
    std::filesystem::remove("styles.css");
    std::filesystem::remove("script.js");
    std::filesystem::remove("components.chtl");
    std::filesystem::remove("module/utils.chtl");
    std::filesystem::remove("module");
    
    return 0;
}

/* 预期输出示例：

=== 示例1：导入HTML文件 ===
HTML输出：
<body>
<div class="imported-html">
    <h1>Imported HTML Content</h1>
    <p>This HTML was imported from an external file.</p>
</div>
</body>

=== 示例2：导入CSS文件 ===
HTML输出：
<head>
  <style>
/* Imported CSS styles */
.imported-style {
    color: #333;
    font-size: 16px;
    margin: 10px;
}

.highlight {
    background-color: yellow;
    font-weight: bold;
}
  </style>
</head>

=== 示例4：导入自定义元素 ===
导入了components.chtl中的Card自定义元素

=== 示例7：导入整个CHTL文件 ===
导入了components.chtl中的所有定义

=== 示例8：从module目录导入 ===
从module目录导入了utils.chtl

*/