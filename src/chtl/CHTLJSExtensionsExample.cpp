#include "CHTLGenerator.h"
#include "CHTLScript.h"
#include <iostream>

using namespace chtl;

// 示例：演示CHTL JS扩展功能（箭头语法、listen、delegate、animate）
int main() {
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 示例1：箭头语法
    std::cout << "=== 示例1：箭头语法 ===" << std::endl;
    
    generator.generateElement("div", {{"class", "arrow-demo"}});
    
    generator.generateElement("button", {{"id", "arrowBtn"}});
    generator.generateTextNode("Click for Arrow Demo");
    generator.closeElement();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 使用->代替.明确表示使用CHTL JS语法
        {{#arrowBtn}}->addEventListener('click', function() {
            this->textContent = 'Arrow syntax works!';
            this->style->backgroundColor = 'green';
            console->log('Arrow syntax demonstration');
        });
        
        // 链式调用
        {{#arrowBtn}}->style->color = 'white';
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例2：增强监听器 listen
    std::cout << "\n=== 示例2：增强监听器 listen ===" << std::endl;
    
    generator.generateElement("div", {{"class", "listen-demo"}});
    
    for (int i = 0; i < 3; i++) {
        generator.generateElement("button", {{"class", "interactive-btn"}, {"data-id", std::to_string(i)}});
        generator.generateTextNode("Button " + std::to_string(i + 1));
        generator.closeElement();
    }
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 定义事件处理函数
        function handleMouseEnter(e) {
            e.target.style.backgroundColor = 'lightblue';
        }
        
        // 使用listen一次性绑定多个事件
        {{.interactive-btn}}->listen({
            click: () => {
                console.log('Button clicked!');
            },
            
            mouseenter: handleMouseEnter,
            
            mouseleave: function() {
                this.style.backgroundColor = '';
            },
            
            focus: (e) => {
                e.target.style.outline = '2px solid blue';
            }
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例3：事件委托 delegate
    std::cout << "\n=== 示例3：事件委托 delegate ===" << std::endl;
    
    generator.generateElement("div", {{"class", "delegate-demo"}});
    
    generator.generateElement("div", {{"id", "itemContainer"}});
    generator.generateElement("h3", {});
    generator.generateTextNode("Dynamic Item List");
    generator.closeElement();
    
    // 初始项目
    for (int i = 0; i < 2; i++) {
        generator.generateElement("div", {{"class", "item"}, {"data-item-id", std::to_string(i)}});
        generator.generateTextNode("Item " + std::to_string(i + 1));
        generator.generateElement("button", {{"class", "delete-btn"}});
        generator.generateTextNode("Delete");
        generator.closeElement();
        generator.closeElement();
    }
    generator.closeElement(); // </div#itemContainer>
    
    generator.generateElement("button", {{"id", "addItemBtn"}});
    generator.generateTextNode("Add Item");
    generator.closeElement();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        let itemCount = 2;
        
        // 使用事件委托处理动态元素
        {{#itemContainer}}->delegate({
            target: [{{.item}}, {{.delete-btn}}],
            
            click: function(e) {
                if (e.target.classList.contains('item')) {
                    console.log('Item clicked:', e.target.dataset.itemId);
                    e.target.style.backgroundColor = '#f0f0f0';
                } else if (e.target.classList.contains('delete-btn')) {
                    e.target.parentElement.remove();
                }
            },
            
            mouseenter: function(e) {
                if (e.target.classList.contains('item')) {
                    e.target.style.transform = 'scale(1.02)';
                }
            },
            
            mouseleave: function(e) {
                if (e.target.classList.contains('item')) {
                    e.target.style.transform = '';
                    e.target.style.backgroundColor = '';
                }
            }
        });
        
        // 添加新项目的按钮
        {{#addItemBtn}}->addEventListener('click', function() {
            const newItem = document.createElement('div');
            newItem.className = 'item';
            newItem.dataset.itemId = itemCount++;
            newItem.innerHTML = `Item ${itemCount} <button class="delete-btn">Delete</button>`;
            {{#itemContainer}}->appendChild(newItem);
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例4：动画 animate
    std::cout << "\n=== 示例4：动画 animate ===" << std::endl;
    
    generator.generateElement("div", {{"class", "animate-demo"}});
    
    generator.generateElement("div", {{"id", "animatedBox"}, {"style", "width:100px;height:100px;background:red;margin:20px;"}});
    generator.closeElement();
    
    generator.generateElement("button", {{"id", "animateBtn"}});
    generator.generateTextNode("Start Animation");
    generator.closeElement();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        {{#animateBtn}}->addEventListener('click', function() {
            const box = {{#animatedBox}};
            
            // animate返回一个函数，调用该函数并传入元素
            const animateBox = animate({
                duration: 2000,  // 2秒
                easing: ease-in-out,
                
                begin: {
                    opacity: 1,
                    transform: 'scale(1) rotate(0deg)'
                },
                
                when: [
                    {
                        at: 0.25,
                        opacity: 0.8,
                        transform: 'scale(1.2) rotate(90deg)',
                        backgroundColor: 'blue'
                    },
                    {
                        at: 0.5,
                        opacity: 0.6,
                        transform: 'scale(0.8) rotate(180deg)',
                        backgroundColor: 'green'
                    },
                    {
                        at: 0.75,
                        opacity: 0.8,
                        transform: 'scale(1.1) rotate(270deg)',
                        backgroundColor: 'yellow'
                    }
                ],
                
                end: {
                    opacity: 1,
                    transform: 'scale(1) rotate(360deg)',
                    backgroundColor: 'red'
                },
                
                loop: 3,  // 循环3次
                direction: 'normal',
                delay: 500,  // 延迟500ms开始
                
                callback: function() {
                    console.log('Animation completed!');
                    box->style->border = '3px solid black';
                }
            });
            
            // 对box元素应用动画
            animateBox(box);
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例5：组合使用
    std::cout << "\n=== 示例5：组合使用 ===" << std::endl;
    
    generator.generateElement("div", {{"class", "combined-demo"}});
    
    generator.generateElement("ul", {{"id", "menu"}});
    for (int i = 0; i < 3; i++) {
        generator.generateElement("li", {{"class", "menu-item"}});
        generator.generateElement("a", {{"href", "#"}, {"data-page", "page" + std::to_string(i)}});
        generator.generateTextNode("Page " + std::to_string(i + 1));
        generator.closeElement();
        generator.closeElement();
    }
    generator.closeElement();
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 使用委托处理菜单项
        {{#menu}}->delegate({
            target: {{.menu-item a}},
            
            click: function(e) {
                e.preventDefault();
                const page = e.target.dataset.page;
                
                // 移除其他项的active类
                {{.menu-item}}->forEach(item => item->classList->remove('active'));
                
                // 添加active类到当前项
                e.target->parentElement->classList->add('active');
                
                // 动画效果
                const slideAnimation = animate({
                    duration: 300,
                    easing: ease-out,
                    
                    begin: {
                        transform: 'translateX(0)'
                    },
                    
                    when: [
                        {
                            at: 0.5,
                            transform: 'translateX(10px)'
                        }
                    ],
                    
                    end: {
                        transform: 'translateX(0)'
                    }
                });
                
                // 应用动画到目标元素
                slideAnimation(e.target);
                
                console.log('Navigating to:', page);
            }
        });
        
        // 给菜单项添加hover效果
        {{.menu-item}}->listen({
            mouseenter: function() {
                this->style->backgroundColor = '#f0f0f0';
            },
            
            mouseleave: function() {
                this->style->backgroundColor = '';
            }
        });
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 添加样式
    generator.beginStyleBlock();
    generator.addGlobalStyle(R"(
        .arrow-demo, .listen-demo, .delegate-demo, .animate-demo, .combined-demo {
            margin: 20px;
            padding: 20px;
            border: 1px solid #ddd;
        }
        
        button {
            margin: 5px;
            padding: 8px 16px;
            cursor: pointer;
        }
        
        .item {
            padding: 10px;
            margin: 5px;
            border: 1px solid #ccc;
            transition: all 0.3s;
        }
        
        #menu {
            list-style: none;
            padding: 0;
        }
        
        .menu-item {
            display: inline-block;
            margin-right: 10px;
            padding: 10px;
            transition: background-color 0.3s;
        }
        
        .menu-item.active {
            background-color: #007bff;
            color: white;
        }
        
        .menu-item a {
            text-decoration: none;
            color: inherit;
        }
    )");
    generator.endStyleBlock();
    
    // 输出生成的代码
    std::cout << "\n=== 生成的HTML ===" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    std::cout << "\n=== 生成的JavaScript（部分） ===" << std::endl;
    std::string js = generator.getJS();
    // 只显示前1000个字符
    std::cout << js.substr(0, 1000) << "..." << std::endl;
    
    return 0;
}

/* 预期功能：

1. 箭头语法：->被转换为.
2. listen方法：一次性绑定多个事件
3. delegate方法：事件委托，处理动态元素
4. animate函数：基于requestAnimationFrame的动画
5. 所有功能可以组合使用

生成的JavaScript将包含：
- CHTL运行时函数（chtl_listen, chtl_delegate, chtl_animate）
- 事件委托注册表
- 动画处理逻辑

*/