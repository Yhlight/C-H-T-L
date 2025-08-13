#include "CHTLGenerator.h"
#include "CHTLOrigin.h"
#include <iostream>

using namespace chtl;

// 示例：演示CHTL原始嵌入的使用
int main() {
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 获取原始嵌入管理器
    auto originManager = generator.getOriginManager();
    
    // 示例1：嵌入HTML代码
    std::cout << "=== 示例1：嵌入HTML代码 ===" << std::endl;
    
    // 直接嵌入HTML
    std::string htmlDecl = "[Origin] @Html {";
    std::string htmlContent = R"(
<div class="raw-html">
    <h1>这是原始HTML</h1>
    <p>这段HTML代码不会被CHTL处理</p>
    <script>console.log('内嵌的脚本也保持原样');</script>
</div>
)";
    
    generator.processOriginBlock(htmlDecl, htmlContent);
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例2：嵌入CSS代码
    std::cout << "\n=== 示例2：嵌入CSS代码 ===" << std::endl;
    generator.reset();
    
    std::string cssDecl = "[Origin] @Style {";
    std::string cssContent = R"(
/* 原始CSS代码 */
.custom-style {
    background: linear-gradient(45deg, #ff0000, #00ff00);
    transform: rotate(45deg);
    animation: spin 2s linear infinite;
}

@keyframes spin {
    from { transform: rotate(0deg); }
    to { transform: rotate(360deg); }
}
)";
    
    generator.processOriginBlock(cssDecl, cssContent);
    
    std::cout << "输出的原始CSS：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例3：嵌入JavaScript代码
    std::cout << "\n=== 示例3：嵌入JavaScript代码 ===" << std::endl;
    generator.reset();
    
    std::string jsDecl = "[Origin] @JavaScript {";
    std::string jsContent = R"(
// 原始JavaScript代码
function complexFunction() {
    const data = {
        nested: {
            value: 42
        }
    };
    
    // 使用一些CHTL可能不支持的特性
    const result = data?.nested?.value ?? 0;
    console.log(`Result: ${result}`);
}

// ES6模块语法
import { something } from './module.js';
export default complexFunction;
)";
    
    generator.processOriginBlock(jsDecl, jsContent);
    
    std::cout << "输出的原始JavaScript：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例4：增强原始嵌入（命名的原始嵌入）
    std::cout << "\n=== 示例4：增强原始嵌入 ===" << std::endl;
    generator.reset();
    
    // 定义命名的原始嵌入
    std::string namedDecl = "[Origin] @Html box {";
    std::string namedContent = R"(
<div class="reusable-box">
    <header>可重用的原始HTML片段</header>
    <main>
        <p>这个片段可以在多个地方使用</p>
    </main>
    <footer>版权所有</footer>
</div>
)";
    
    generator.processOriginBlock(namedDecl, namedContent);
    
    // 在body中使用
    generator.generateElement("body", {});
    
    // 第一次使用
    generator.generateElement("section", {{"id", "section1"}});
    generator.useOriginBlock("box");
    generator.closeElement();
    
    // 第二次使用
    generator.generateElement("section", {{"id", "section2"}});
    generator.useOriginBlock("box");
    generator.closeElement();
    
    generator.closeElement(); // </body>
    
    std::cout << "HTML输出（使用了两次命名的原始嵌入）：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例5：在任意节点中使用原始嵌入
    std::cout << "\n=== 示例5：在任意节点中使用原始嵌入 ===" << std::endl;
    generator.reset();
    
    generator.generateElement("div", {{"class", "container"}});
    
    // 在div内部嵌入原始HTML
    std::string innerDecl = "[Origin] @Html {";
    std::string innerContent = R"(
    <!-- 这是在div内部的原始HTML -->
    <custom-element>
        <slot name="header">默认标题</slot>
        <slot name="content">默认内容</slot>
    </custom-element>
)";
    
    generator.processOriginBlock(innerDecl, innerContent);
    
    generator.closeElement();
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例6：混合使用原始嵌入和CHTL
    std::cout << "\n=== 示例6：混合使用原始嵌入和CHTL ===" << std::endl;
    generator.reset();
    
    // CHTL生成的结构
    generator.generateElement("article", {});
    generator.generateElement("h1", {});
    generator.generateTextNode("CHTL生成的标题");
    generator.closeElement();
    
    // 嵌入原始HTML
    std::string mixedDecl = "[Origin] @Html {";
    std::string mixedContent = R"(
    <div class="raw-content">
        <p>这是原始HTML内容</p>
        <style>
            .raw-content { border: 1px solid red; }
        </style>
    </div>
)";
    generator.processOriginBlock(mixedDecl, mixedContent);
    
    // 继续CHTL生成
    generator.generateElement("p", {});
    generator.generateTextNode("CHTL生成的段落");
    generator.closeElement();
    
    generator.closeElement(); // </article>
    
    std::cout << "完整输出：" << std::endl;
    std::cout << generator.getCombinedOutput() << std::endl;
    
    return 0;
}

/* 预期输出示例：

=== 示例1：嵌入HTML代码 ===
HTML输出：

<div class="raw-html">
    <h1>这是原始HTML</h1>
    <p>这段HTML代码不会被CHTL处理</p>
    <script>console.log('内嵌的脚本也保持原样');</script>
</div>

=== 示例2：嵌入CSS代码 ===
输出的原始CSS：

/* 原始CSS代码 */
.custom-style {
    background: linear-gradient(45deg, #ff0000, #00ff00);
    transform: rotate(45deg);
    animation: spin 2s linear infinite;
}

@keyframes spin {
    from { transform: rotate(0deg); }
    to { transform: rotate(360deg); }
}

=== 示例4：增强原始嵌入 ===
两个section中都包含相同的原始HTML片段

=== 示例6：混合使用原始嵌入和CHTL ===
CHTL生成的内容和原始嵌入的内容无缝结合

*/