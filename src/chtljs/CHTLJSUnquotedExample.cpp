#include "CHTLJSContext.h"
#include "CHTLJSStateMachine.h"
#include "CHTLContext.h"
#include "CHTLGenerator.h"
#include "CHTLScript.h"
#include <iostream>

using namespace chtl;

int main() {
    // 创建上下文
    auto context = std::make_shared<CHTLContext>();
    auto jsContext = std::make_shared<CHTLJSContext>(context);
    
    // 创建生成器
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    std::cout << "=== CHTL JS 无修饰字面量示例 ===" << std::endl;
    
    // 示例1：在对象字面量中使用无修饰字面量
    std::cout << "\n--- 示例1：对象字面量中的无修饰值 ---" << std::endl;
    
    generator.generateElement("div", {{"id", "config-demo"}});
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 配置对象，使用无修饰字面量
        const config = {
            // 颜色值
            primaryColor: red,
            backgroundColor: white,
            borderColor: black,
            
            // 尺寸值
            width: 100px,
            height: 200px,
            padding: 10px,
            
            // 布尔值和数字不需要引号
            isEnabled: true,
            maxItems: 10,
            
            // 标识符作为值
            displayMode: fullscreen,
            position: relative,
            
            // 需要引号的值（包含特殊字符）
            className: "my-class",
            dataAttr: "data-value"
        };
        
        {{#config-demo}}->innerHTML = `
            <pre>${JSON.stringify(config, null, 2)}</pre>
        `;
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例2：在animate配置中使用无修饰字面量
    std::cout << "\n--- 示例2：动画配置中的无修饰值 ---" << std::endl;
    
    generator.generateElement("div", {{"id", "animate-demo"}});
    generator.beginLocalStyleBlock();
    generator.addStyleRule(".box", {
        {"width", "100px"},
        {"height", "100px"},
        {"background-color", "blue"},
        {"margin", "20px"}
    });
    generator.endStyleBlock();
    
    generator.generateElement("div", {{"class", "box"}});
    generator.closeElement();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        const fadeIn = animate({
            // 数字不需要引号
            duration: 1000,
            delay: 200,
            
            // 缓动函数名作为无修饰字面量
            easing: ease-in-out,
            
            // CSS属性值
            begin: {
                opacity: 0,
                transform: scale(0.8)
            },
            
            end: {
                opacity: 1,
                transform: scale(1)
            },
            
            // 方向和循环
            direction: alternate,
            loop: 3
        });
        
        // 应用动画
        {{.box}}->forEach(el => fadeIn(el));
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例3：事件配置中的无修饰字面量
    std::cout << "\n--- 示例3：事件配置中的无修饰值 ---" << std::endl;
    
    generator.generateElement("button", {{"id", "event-demo"}});
    generator.generateText("Click Me");
    generator.closeElement();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        {{#event-demo}}->listen({
            // 事件名作为属性名，不需要引号
            click: function() {
                this.style.backgroundColor = red;
            },
            
            mouseenter: function() {
                this.style.transform = scale(1.1);
            },
            
            mouseleave: function() {
                this.style.transform = scale(1);
            }
        });
    )");
    generator.endScriptBlock();
    
    // 示例4：样式对象中的无修饰字面量
    std::cout << "\n--- 示例4：动态样式中的无修饰值 ---" << std::endl;
    
    generator.generateElement("div", {{"id", "style-demo"}});
    generator.generateText("Styled Text");
    generator.closeElement();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 样式对象
        const styles = {
            // 颜色
            color: darkblue,
            backgroundColor: lightgray,
            
            // 字体
            fontSize: 16px,
            fontWeight: bold,
            fontFamily: Arial,
            
            // 布局
            display: flex,
            alignItems: center,
            justifyContent: center,
            
            // 边框
            border: "1px solid black",  // 复杂值需要引号
            borderRadius: 5px,
            
            // 间距
            padding: 10px,
            margin: 0
        };
        
        // 应用样式
        Object.assign({{#style-demo}}->style, styles);
    )");
    generator.endScriptBlock();
    
    // 示例5：验证和处理
    std::cout << "\n--- 示例5：无修饰字面量的验证 ---" << std::endl;
    
    // 测试状态机和上下文
    jsContext->getStateMachine().handleEvent(CHTLJSEvent::EnterScript);
    jsContext->getStateMachine().handleEvent(CHTLJSEvent::StartObject);
    
    // 测试各种值
    std::vector<std::string> testValues = {
        "red",          // 有效：颜色名
        "100px",        // 有效：尺寸值
        "true",         // 有效：布尔值
        "myVariable",   // 有效：标识符
        "my-class",     // 有效：包含连字符
        "123invalid",   // 无效：以数字开头
        "has space",    // 无效：包含空格
        "special@char", // 无效：包含特殊字符
    };
    
    std::cout << "\n验证结果：" << std::endl;
    for (const auto& value : testValues) {
        bool isValid = jsContext->validateUnquotedLiteral(value);
        std::string processed = jsContext->processUnquotedLiteral(value);
        std::cout << value << " -> " << (isValid ? "有效" : "无效") 
                  << " -> " << processed << std::endl;
    }
    
    // 输出生成的代码
    std::cout << "\n=== 生成的HTML ===" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    std::cout << "\n=== 生成的JavaScript（部分） ===" << std::endl;
    std::string js = generator.getJS();
    // 显示前500个字符
    std::cout << js.substr(0, std::min(size_t(500), js.length())) << "..." << std::endl;
    
    // 显示无修饰字面量映射
    std::cout << "\n=== 无修饰字面量映射 ===" << std::endl;
    jsContext->dumpUnquotedLiterals();
    
    return 0;
}

/* 预期功能展示：

1. 对象字面量中的无修饰值
   - 颜色名：red, white, black
   - 尺寸值：100px, 200px
   - 标识符：fullscreen, relative
   
2. 动画配置
   - 缓动函数：ease-in-out
   - 方向：alternate
   - CSS值：scale(0.8)
   
3. 事件配置
   - 事件名作为属性名
   - 动态样式值
   
4. 样式对象
   - CSS属性值的无修饰形式
   - 自动引号添加
   
5. 验证机制
   - 有效值识别
   - 无效值处理
   - 自动转换

*/