#include "CHTLGenerator.h"
#include "CHTLScript.h"
#include <iostream>

using namespace chtl;

// 示例：演示CHTL局部script和增强选择器的使用
int main() {
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 获取脚本管理器
    auto scriptManager = generator.getScriptManager();
    
    // 示例1：基本的局部script
    std::cout << "=== 示例1：基本的局部script ===" << std::endl;
    
    generator.generateElement("div", {{"class", "container"}});
    
    // 创建一个带样式的按钮
    generator.generateElement("button", {{"id", "myButton"}});
    generator.generateTextNode("Click Me!");
    generator.closeElement(); // </button>
    
    // 添加局部script
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        {{#myButton}}.addEventListener('click', function() {
            alert('Button clicked!');
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement(); // </div>
    
    // 示例2：自动推断选择器
    std::cout << "\n=== 示例2：自动推断选择器 ===" << std::endl;
    
    generator.generateElement("div", {});
    
    generator.beginStyleBlock();
    generator.addInlineStyle("width", "200px");
    generator.addInlineStyle("height", "200px");
    generator.beginClassStyle("box");
    generator.addStyleProperty("background-color", "red");
    generator.addStyleProperty("cursor", "pointer");
    generator.endClassStyle();
    generator.endStyleBlock();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 自动推断：先找ID为box，然后找类名为box，最后找标签名为box
        {{box}}.addEventListener('mouseover', function() {
            this.style.backgroundColor = 'blue';
        });
        
        {{box}}.addEventListener('mouseout', function() {
            this.style.backgroundColor = 'red';
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement(); // </div>
    
    // 示例3：类选择器和ID选择器
    std::cout << "\n=== 示例3：类选择器和ID选择器 ===" << std::endl;
    
    generator.generateElement("form", {});
    
    generator.generateElement("input", {{"type", "text"}, {"class", "input-field"}, {"placeholder", "Name"}});
    generator.closeElement();
    
    generator.generateElement("input", {{"type", "email"}, {"class", "input-field"}, {"placeholder", "Email"}});
    generator.closeElement();
    
    generator.generateElement("button", {{"type", "submit"}, {"id", "submitBtn"}});
    generator.generateTextNode("Submit");
    generator.closeElement();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 类选择器 - 获取所有input-field
        {{.input-field}}.forEach(function(input) {
            input.addEventListener('focus', function() {
                this.style.borderColor = '#007bff';
            });
        });
        
        // ID选择器
        {{#submitBtn}}.addEventListener('click', function(e) {
            e.preventDefault();
            console.log('Form submitted');
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement(); // </form>
    
    // 示例4：标签选择器和索引访问
    std::cout << "\n=== 示例4：标签选择器和索引访问 ===" << std::endl;
    
    generator.generateElement("ul", {});
    
    for (int i = 0; i < 5; i++) {
        generator.generateElement("li", {});
        generator.generateTextNode("Item " + std::to_string(i + 1));
        generator.closeElement();
    }
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 获取所有li元素
        {{li}}.forEach(function(item, index) {
            item.addEventListener('click', function() {
                console.log('Clicked item ' + (index + 1));
            });
        });
        
        // 索引访问 - 第一个和最后一个特殊处理
        {{li[0]}}.style.fontWeight = 'bold';
        {{li[4]}}.style.fontStyle = 'italic';
    )");
    generator.endScriptBlock();
    
    generator.closeElement(); // </ul>
    
    // 示例5：后代选择器
    std::cout << "\n=== 示例5：后代选择器 ===" << std::endl;
    
    generator.generateElement("nav", {{"class", "navigation"}});
    
    generator.generateElement("ul", {});
    for (int i = 0; i < 3; i++) {
        generator.generateElement("li", {});
        generator.generateElement("a", {{"href", "#"}});
        generator.generateTextNode("Link " + std::to_string(i + 1));
        generator.closeElement(); // </a>
        generator.closeElement(); // </li>
    }
    generator.closeElement(); // </ul>
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 后代选择器 - 查找navigation类下的所有a标签
        {{.navigation a}}.forEach(function(link) {
            link.addEventListener('click', function(e) {
                e.preventDefault();
                console.log('Navigation link clicked: ' + this.textContent);
            });
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement(); // </nav>
    
    // 示例6：复杂的增强选择器组合
    std::cout << "\n=== 示例6：复杂的增强选择器组合 ===" << std::endl;
    
    generator.generateElement("div", {{"class", "app"}});
    
    // 创建多个带box类的div
    for (int i = 0; i < 3; i++) {
        generator.generateElement("div", {{"class", "box"}, {"data-index", std::to_string(i)}});
        generator.generateElement("span", {});
        generator.generateTextNode("Box " + std::to_string(i + 1));
        generator.closeElement(); // </span>
        generator.closeElement(); // </div>
    }
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 使用后代选择器找到box内的span
        {{.box span}}.forEach(function(span) {
            span.style.display = 'block';
            span.style.padding = '10px';
        });
        
        // 特定索引的box
        {{.box[1]}}.style.backgroundColor = '#f0f0f0';
        
        // 混合使用
        const boxes = {{.box}};
        boxes.forEach(function(box, index) {
            box.addEventListener('click', function() {
                // 在box内查找span
                const span = this.querySelector('span');
                span.textContent = 'Clicked!';
            });
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement(); // </div>
    
    // 输出生成的代码
    std::cout << "\n=== 生成的HTML ===" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    std::cout << "\n=== 生成的CSS ===" << std::endl;
    std::cout << generator.getCSS() << std::endl;
    
    std::cout << "\n=== 生成的JavaScript ===" << std::endl;
    std::cout << generator.getJS() << std::endl;
    
    return 0;
}

/* 预期输出示例：

生成的JavaScript将包含：
1. CHTL运行时支持函数（chtl_query, chtl_queryOne）
2. 作用域映射
3. 转换后的选择器代码：
   - {{#myButton}} -> chtl_queryOne('#myButton', null)
   - {{box}} -> (chtl_queryOne('#box', null) || chtl_queryOne('.box', null) || chtl_queryOne('box', null))
   - {{.input-field}} -> chtl_query('.input-field', scope)
   - {{li[0]}} -> chtl_query('li', scope)[0]
   - {{.navigation a}} -> chtl_query('.navigation a', scope)

HTML元素将包含data-chtl-scope属性用于作用域隔离。

*/