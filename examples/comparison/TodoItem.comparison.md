# Todo Item 组件对比

同样的功能，不同的实现方式，展示 CHTL 的独特设计理念。

## 需求
- 显示待办事项文本
- 复选框切换完成状态
- 删除按钮
- 完成时显示删除线
- 鼠标悬停效果

## React 实现
```jsx
// TodoItem.jsx
import React, { useState } from 'react';
import './TodoItem.css';

function TodoItem({ todo, onToggle, onDelete }) {
  const [isHovered, setIsHovered] = useState(false);
  
  return (
    <li 
      className={`todo-item ${todo.completed ? 'completed' : ''}`}
      onMouseEnter={() => setIsHovered(true)}
      onMouseLeave={() => setIsHovered(false)}
    >
      <input
        type="checkbox"
        checked={todo.completed}
        onChange={() => onToggle(todo.id)}
      />
      <span className="todo-text">{todo.text}</span>
      {isHovered && (
        <button 
          className="delete-btn"
          onClick={() => onDelete(todo.id)}
        >
          删除
        </button>
      )}
    </li>
  );
}

// TodoItem.css
.todo-item {
  display: flex;
  align-items: center;
  padding: 12px;
  border: 1px solid #e0e0e0;
  margin-bottom: 8px;
}

.todo-item.completed .todo-text {
  text-decoration: line-through;
  opacity: 0.6;
}

.delete-btn {
  margin-left: auto;
  background: #ff4444;
  color: white;
  border: none;
  padding: 4px 8px;
  cursor: pointer;
}
```

**问题**：
- 需要管理悬停状态
- CSS 分离在另一个文件
- 运行时的类名拼接
- 需要导入和样式依赖

---

## Vue 3 实现
```vue
<!-- TodoItem.vue -->
<template>
  <li 
    :class="['todo-item', { completed: todo.completed }]"
    @mouseenter="isHovered = true"
    @mouseleave="isHovered = false"
  >
    <input
      type="checkbox"
      :checked="todo.completed"
      @change="$emit('toggle', todo.id)"
    />
    <span class="todo-text">{{ todo.text }}</span>
    <button 
      v-if="isHovered"
      class="delete-btn"
      @click="$emit('delete', todo.id)"
    >
      删除
    </button>
  </li>
</template>

<script setup>
import { ref } from 'vue';

defineProps(['todo']);
defineEmits(['toggle', 'delete']);

const isHovered = ref(false);
</script>

<style scoped>
.todo-item {
  display: flex;
  align-items: center;
  padding: 12px;
  border: 1px solid #e0e0e0;
  margin-bottom: 8px;
}

.todo-item.completed .todo-text {
  text-decoration: line-through;
  opacity: 0.6;
}

.delete-btn {
  margin-left: auto;
  background: #ff4444;
  color: white;
  border: none;
  padding: 4px 8px;
  cursor: pointer;
}
</style>
```

**问题**：
- 三个不同的语言块
- 模板语法需要学习
- 仍然需要管理悬停状态
- 作用域样式的额外复杂性

---

## Svelte 实现
```svelte
<!-- TodoItem.svelte -->
<script>
  export let todo;
  export let onToggle;
  export let onDelete;
  
  let isHovered = false;
</script>

<li 
  class="todo-item"
  class:completed={todo.completed}
  on:mouseenter={() => isHovered = true}
  on:mouseleave={() => isHovered = false}
>
  <input
    type="checkbox"
    checked={todo.completed}
    on:change={() => onToggle(todo.id)}
  />
  <span class="todo-text">{todo.text}</span>
  {#if isHovered}
    <button 
      class="delete-btn"
      on:click={() => onDelete(todo.id)}
    >
      删除
    </button>
  {/if}
</li>

<style>
  .todo-item {
    display: flex;
    align-items: center;
    padding: 12px;
    border: 1px solid #e0e0e0;
    margin-bottom: 8px;
  }
  
  .completed .todo-text {
    text-decoration: line-through;
    opacity: 0.6;
  }
  
  .delete-btn {
    margin-left: auto;
    background: #ff4444;
    color: white;
    border: none;
    padding: 4px 8px;
    cursor: pointer;
  }
</style>
```

**更好但仍有问题**：
- 专有的模板语法
- 仍需手动管理状态
- 编译后体积较大

---

## CHTL 实现
```chtl
[Template] @Element TodoItem {
    li {
        class: "todo-item";
        
        // 局部样式，自动作用域
        style {
            display: flex;
            align-items: center;
            padding: 12px;
            border: 1px solid #e0e0e0;
            margin-bottom: 8px;
            transition: all 0.2s;
            
            // & 引用当前元素
            &:hover {
                background: #f5f5f5;
                transform: translateX(4px);
                
                // 悬停时显示删除按钮
                .delete-btn {
                    opacity: 1;
                }
            }
            
            // 完成状态样式
            &.completed {
                .todo-text {
                    text-decoration: line-through;
                    opacity: 0.6;
                }
            }
            
            input[type="checkbox"] {
                margin-right: 12px;
                cursor: pointer;
            }
            
            .todo-text {
                flex: 1;
            }
            
            .delete-btn {
                background: #ff4444;
                color: white;
                border: none;
                padding: 4px 8px;
                cursor: pointer;
                opacity: 0;  // 默认隐藏
                transition: opacity 0.2s;
                
                &:hover {
                    background: #cc0000;
                }
            }
        }
        
        // 结构定义
        input {
            type: "checkbox";
            checked: slot.completed;  // 属性来自插槽
            
            script {
                {{&}}.onchange = () => {
                    slot.onToggle(slot.todo.id);
                };
            }
        }
        
        span {
            class: "todo-text";
            text { slot.todo.text }
        }
        
        button {
            class: "delete-btn";
            text { "删除" }
            
            script {
                {{&}}.onclick = () => {
                    slot.onDelete(slot.todo.id);
                };
            }
        }
        
        // 根据完成状态添加类
        script {
            if (slot.todo.completed) {
                {{&}}.classList.add('completed');
            }
        }
    }
}

// 使用
@Element TodoItem {
    todo: { id: 1, text: "学习 CHTL", completed: false };
    onToggle: (id) => toggleTodo(id);
    onDelete: (id) => deleteTodo(id);
}
```

## CHTL 的独特优势

### 1. **结构即文档**
```chtl
li {
    input { type: "checkbox"; }
    span { class: "todo-text"; }
    button { class: "delete-btn"; }
}
```
一眼就能看出 HTML 结构，不需要在 JSX 或模板语法中寻找。

### 2. **样式自然内联**
- 样式直接写在使用的地方
- 自动作用域隔离
- `&` 符号智能引用
- 悬停显示用 CSS 实现，不需要 JS 状态

### 3. **脚本精准定位**
```chtl
script {
    {{&}}.onclick = () => {  // {{&}} 自动引用当前元素
        // 处理逻辑
    };
}
```
脚本直接附着在需要的元素上，不需要 ref 或查询。

### 4. **编译时优化**
CHTL 编译后：
```html
<li class="todo-item chtl-auto-1">
  <input type="checkbox">
  <span class="todo-text">学习 CHTL</span>
  <button class="delete-btn">删除</button>
</li>
```

```css
/* 自动生成的作用域样式 */
.chtl-auto-1 { ... }
.chtl-auto-1:hover { ... }
.chtl-auto-1:hover .delete-btn { opacity: 1; }
```

```js
// 自动生成的事件绑定
(function() {
  const element = document.querySelector('.chtl-auto-1');
  const checkbox = element.querySelector('input');
  checkbox.onchange = () => { ... };
})();
```

### 5. **零运行时框架**
- 没有虚拟 DOM
- 没有响应式系统开销
- 没有框架运行时
- 生成的是纯粹的 HTML/CSS/JS

### 6. **类型安全（可选）**
```chtl
[Template] @Element TodoItem<T extends Todo> {
    // 编译时类型检查
    li {
        span { text { slot.todo.text } }  // 类型安全的属性访问
    }
}
```

## 总结

CHTL 不是在 JavaScript 中嵌入 HTML（React），
不是模板语言（Vue），
不是编译优化的框架（Svelte），

**CHTL 是一种新的语言**，它：
- 以 HTML 结构为核心
- 统一了样式和脚本的表达
- 在编译时完成所有工作
- 生成最优的运行时代码
- 通过 CJmod 无限扩展

这就是 CHTL 的特别之处 - **它重新定义了前端开发应该是什么样子**。