# CHTL JS扩展功能文档

## 概述

CHTL JS提供了一系列扩展功能，让JavaScript编程更加简洁和强大。这些扩展包括：

- **箭头语法（->）**：明确表示使用CHTL JS语法
- **增强监听器（listen）**：一次性绑定多个事件
- **事件委托（delegate）**：处理动态元素的事件
- **动画系统（animate）**：基于requestAnimationFrame的动画

## 箭头语法

### 基本用法

使用`->`代替`.`来明确表示正在使用CHTL JS语法：

```chtl
script
{
    {{#myButton}}->addEventListener('click', function() {
        this->textContent = 'Clicked!';
        this->style->backgroundColor = 'green';
    });
}
```

### 链式调用

箭头语法支持链式调用：

```chtl
script
{
    {{.box}}->style->transform = 'scale(1.1)';
    document->body->classList->add('loaded');
}
```

### 与点语法的等价性

`->`与`.`完全等价，可以混合使用：

```chtl
script
{
    {{#element}}->style.color = 'red';  // 混合使用
    console->log(window.location.href); // 混合使用
}
```

## 增强监听器 - listen

### 基本语法

```chtl
script
{
    {{选择器}}->listen({
        事件类型: 处理函数,
        事件类型2: 处理函数2,
        // ...
    });
}
```

### 功能特点

1. **批量绑定**：一次调用绑定多个事件
2. **自动遍历**：自动为所有匹配元素绑定事件
3. **支持多种函数形式**：箭头函数、匿名函数、命名函数

### 使用示例

```chtl
button
{
    class: interactive;
    
    script
    {
        // 定义处理函数
        function handleClick(e) {
            console.log('Button clicked:', e.target);
        }
        
        // 使用listen绑定多个事件
        {{.interactive}}->listen({
            click: handleClick,
            
            mouseenter: () => {
                this->style->backgroundColor = 'lightblue';
            },
            
            mouseleave: function() {
                this.style.backgroundColor = '';
            },
            
            focus: (e) => {
                e.target.classList.add('focused');
            },
            
            blur: (e) => {
                e.target.classList.remove('focused');
            }
        });
    }
}
```

## 事件委托 - delegate

### 基本语法

```chtl
script
{
    {{父元素选择器}}->delegate({
        target: {{子元素选择器}} | [{{选择器1}}, {{选择器2}}],
        事件类型: 处理函数,
        事件类型2: 处理函数2,
        // ...
    });
}
```

### 功能特点

1. **动态元素支持**：自动处理后续添加的元素
2. **性能优化**：减少事件监听器数量
3. **全局注册表**：避免重复绑定
4. **多目标支持**：可以委托多个不同的子元素

### 使用示例

#### 单目标委托

```chtl
div
{
    id: container;
    
    script
    {
        {{#container}}->delegate({
            target: {{.item}},
            
            click: function(e) {
                console.log('Item clicked:', e.target);
                e.target->classList->toggle('selected');
            },
            
            mouseenter: function(e) {
                e.target->style->opacity = '0.8';
            },
            
            mouseleave: function(e) {
                e.target->style->opacity = '1';
            }
        });
    }
}
```

#### 多目标委托

```chtl
script
{
    {{#todoList}}->delegate({
        target: [{{.todo-item}}, {{.delete-btn}}, {{.edit-btn}}],
        
        click: function(e) {
            if (e.target.classList.contains('todo-item')) {
                e.target->classList->toggle('completed');
            } else if (e.target.classList.contains('delete-btn')) {
                e.target->closest('.todo-item')->remove();
            } else if (e.target.classList.contains('edit-btn')) {
                // 编辑逻辑
                const item = e.target->closest('.todo-item');
                const text = prompt('Edit todo:', item->textContent);
                if (text) item->textContent = text;
            }
        }
    });
}
```

### 事件委托的优势

1. **内存效率**：只需要一个事件监听器
2. **动态元素**：自动支持新增的元素
3. **简化代码**：集中管理相关事件

## 动画系统 - animate

### 基本语法

```chtl
script
{
    animate({
        element: 目标元素,
        duration: 持续时间(ms),
        easing: 缓动函数,
        begin: { /* 起始状态 */ },
        when: [ /* 关键帧 */ ],
        end: { /* 结束状态 */ },
        loop: 循环次数,
        direction: 播放方向,
        delay: 延迟时间(ms),
        callback: 完成回调
    });
}
```

### 配置选项

#### 必需参数

- **element**: 要动画的DOM元素

#### 可选参数

- **duration**: 动画持续时间（毫秒），默认1000
- **easing**: 缓动函数，支持：
  - `linear`: 线性
  - `ease-in`: 缓入
  - `ease-out`: 缓出
  - `ease-in-out`: 缓入缓出
- **begin**: 动画开始时的CSS属性
- **when**: 关键帧数组，每个关键帧包含：
  - `at`: 时间点（0-1之间）
  - CSS属性键值对
- **end**: 动画结束时的CSS属性
- **loop**: 循环次数，-1表示无限循环
- **direction**: 播放方向（'normal', 'reverse', 'alternate'）
- **delay**: 开始前的延迟（毫秒）
- **callback**: 动画完成后的回调函数

### 使用示例

#### 基础动画

```chtl
script
{
    const box = {{#myBox}};
    
    animate({
        element: box,
        duration: 1000,
        easing: ease-out,
        
        begin: {
            opacity: 0,
            transform: 'translateY(-20px)'
        },
        
        end: {
            opacity: 1,
            transform: 'translateY(0)'
        }
    });
}
```

#### 关键帧动画

```chtl
script
{
    {{#logo}}->addEventListener('click', function() {
        animate({
            element: this,
            duration: 2000,
            easing: ease-in-out,
            
            begin: {
                transform: 'rotate(0deg) scale(1)'
            },
            
            when: [
                {
                    at: 0.25,
                    transform: 'rotate(90deg) scale(1.2)',
                    filter: 'hue-rotate(90deg)'
                },
                {
                    at: 0.5,
                    transform: 'rotate(180deg) scale(0.8)',
                    filter: 'hue-rotate(180deg)'
                },
                {
                    at: 0.75,
                    transform: 'rotate(270deg) scale(1.1)',
                    filter: 'hue-rotate(270deg)'
                }
            ],
            
            end: {
                transform: 'rotate(360deg) scale(1)',
                filter: 'hue-rotate(360deg)'
            },
            
            callback: function() {
                console.log('Animation completed!');
            }
        });
    });
}
```

#### 循环动画

```chtl
script
{
    // 无限脉冲动画
    animate({
        element: {{.pulse}},
        duration: 1500,
        easing: ease-in-out,
        
        begin: {
            transform: 'scale(1)',
            opacity: 1
        },
        
        when: [
            {
                at: 0.5,
                transform: 'scale(1.1)',
                opacity: 0.7
            }
        ],
        
        end: {
            transform: 'scale(1)',
            opacity: 1
        },
        
        loop: -1  // 无限循环
    });
}
```

## 组合使用

所有CHTL JS扩展功能可以自由组合：

```chtl
div
{
    id: app;
    
    script
    {
        // 使用委托处理动态按钮
        {{#app}}->delegate({
            target: {{.btn}},
            
            click: function(e) {
                const btn = e.target;
                
                // 使用箭头语法操作
                btn->classList->add('clicked');
                
                // 触发动画
                animate({
                    element: btn,
                    duration: 300,
                    easing: ease-out,
                    
                    begin: {
                        transform: 'scale(1)'
                    },
                    
                    when: [
                        {
                            at: 0.5,
                            transform: 'scale(0.95)'
                        }
                    ],
                    
                    end: {
                        transform: 'scale(1)'
                    }
                });
            }
        });
        
        // 使用listen添加hover效果
        {{.btn}}->listen({
            mouseenter: function() {
                this->style->transform = 'translateY(-2px)';
                this->style->boxShadow = '0 4px 8px rgba(0,0,0,0.2)';
            },
            
            mouseleave: function() {
                this->style->transform = '';
                this->style->boxShadow = '';
            }
        });
    }
}
```

## 性能考虑

### listen方法

- 自动批量处理元素，减少代码量
- 内部使用标准addEventListener，性能无损

### delegate方法

- 使用事件冒泡机制，减少监听器数量
- 全局注册表避免重复绑定
- 适合大量动态元素的场景

### animate方法

- 基于requestAnimationFrame，60fps流畅动画
- 自动处理动画队列和清理
- 支持多属性同时动画

## 最佳实践

### 1. 选择合适的方法

```chtl
script
{
    // 静态元素，少量事件 -> 使用listen
    {{.static-btn}}->listen({
        click: handleClick
    });
    
    // 动态元素，大量相似元素 -> 使用delegate
    {{#list-container}}->delegate({
        target: {{.list-item}},
        click: handleItemClick
    });
}
```

### 2. 动画性能优化

```chtl
script
{
    // 优先使用transform和opacity（GPU加速）
    animate({
        element: box,
        duration: 500,
        begin: { transform: 'translateX(0)', opacity: 0 },
        end: { transform: 'translateX(100px)', opacity: 1 }
    });
    
    // 避免动画layout属性（如width, height）
}
```

### 3. 事件委托的正确使用

```chtl
script
{
    // 将委托绑定到稳定的父元素
    {{#app}}->delegate({  // app是不会被销毁的根元素
        target: [{{.dynamic-element}}, {{.another-dynamic}}],
        // ...
    });
}
```

## 调试技巧

### 查看生成的代码

```cpp
std::string js = generator.getJS();
std::cout << "Generated JavaScript:" << std::endl;
std::cout << js << std::endl;
```

### 运行时调试

```javascript
// 生成的代码包含CHTL运行时函数
window.chtl_listen    // listen运行时
window.chtl_delegate  // delegate运行时
window.chtl_animate   // animate运行时
```

## 兼容性

- 箭头语法：所有环境（编译时转换）
- listen：支持addEventListener的所有浏览器
- delegate：需要Element.matches支持（IE9+）
- animate：需要requestAnimationFrame支持（IE10+）