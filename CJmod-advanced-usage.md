# CJmod 高级使用示例

## 1. 协程模块使用

```chtl
[Import] @CJmod coroutine

body {
    script {
        // 定义异步生成器
        async* fetchPages(urls) {
            for (const url of urls) {
                const response = await fetch(url);
                const data = await response.json();
                yield data;
            }
        }
        
        // 使用异步生成器
        async function loadAllPages() {
            const urls = ['/api/page1', '/api/page2', '/api/page3'];
            
            for await (const pageData of fetchPages(urls)) {
                console.log('Loaded:', pageData);
                {{#content}}.appendChild(renderPage(pageData));
            }
        }
        
        // 无限滚动生成器
        async* infiniteScroll() {
            let page = 1;
            while (true) {
                const data = await fetch(`/api/items?page=${page}`);
                yield await data.json();
                page++;
            }
        }
    }
}
```

## 2. 类型注解模块使用

```chtl
[Import] @CJmod type-annotation

body {
    script {
        // 定义接口
        interface User {
            id: number;
            name: string;
            email: string;
            roles: string[];
        }
        
        interface Product {
            id: number;
            name: string;
            price: number;
            inStock: boolean;
        }
        
        // 使用类型注解
        let currentUser: User;
        let products: Product[] = [];
        
        function calculateTotal(items: Product[]): number {
            return items.reduce((sum, item) => sum + item.price, 0);
        }
        
        // 泛型函数
        function find<T>(array: T[], predicate: (item: T) => boolean): T | null {
            for (const item of array) {
                if (predicate(item)) return item;
            }
            return null;
        }
        
        // 使用
        const admin = find<User>(users, u => u.roles.includes('admin'));
    }
}
```

## 3. 响应式系统深度使用

```chtl
[Import] @CJmod reactive-system

body {
    div {
        id: "app";
        
        script {
            // 响应式状态
            count := 0;
            todos := [];
            filter := 'all';
            
            // 计算属性
            completedCount => todos.value.filter(t => t.completed).length;
            activeCount => todos.value.length - completedCount.value;
            
            filteredTodos => {
                switch(filter.value) {
                    case 'active': 
                        return todos.value.filter(t => !t.completed);
                    case 'completed': 
                        return todos.value.filter(t => t.completed);
                    default: 
                        return todos.value;
                }
            };
            
            // 副作用
            effect {
                console.log(`Total todos: ${todos.value.length}`);
                console.log(`Completed: ${completedCount.value}`);
                console.log(`Active: ${activeCount.value}`);
            }
            
            // 自动保存到 localStorage
            effect {
                localStorage.setItem('todos', JSON.stringify(todos.value));
            }
            
            // 渲染副作用
            effect {
                const container = {{#todo-list}};
                container.innerHTML = '';
                
                filteredTodos.value.forEach(todo => {
                    const item = createTodoElement(todo);
                    container.appendChild(item);
                });
            }
            
            // 方法
            function addTodo(text) {
                todos.value = [...todos.value, {
                    id: Date.now(),
                    text,
                    completed: false
                }];
            }
            
            function toggleTodo(id) {
                todos.value = todos.value.map(todo =>
                    todo.id === id 
                        ? {...todo, completed: !todo.completed}
                        : todo
                );
            }
        }
        
        // UI
        input {
            id: "new-todo";
            placeholder: "What needs to be done?";
            
            script {
                {{&}}->listen("keypress", (e) => {
                    if (e.key === 'Enter' && {{&}}.value.trim()) {
                        addTodo({{&}}.value.trim());
                        {{&}}.value = '';
                    }
                });
            }
        }
        
        ul { id: "todo-list"; }
        
        div {
            class: "filters";
            
            button {
                text { "All" }
                script {
                    {{&}}->listen("click", () => {
                        filter.value = 'all';
                    });
                }
            }
            
            button {
                text { "Active" }
                script {
                    {{&}}->listen("click", () => {
                        filter.value = 'active';
                    });
                }
            }
            
            button {
                text { "Completed" }
                script {
                    {{&}}->listen("click", () => {
                        filter.value = 'completed';
                    });
                }
            }
        }
    }
}
```

## 4. 宏系统使用

```chtl
[Import] @CJmod macro-system

body {
    script {
        // 定义组件宏
        defmacro component(name, props, template) {
            class name extends HTMLElement {
                constructor() {
                    super();
                    this.attachShadow({mode: 'open'});
                    this.props = props;
                }
                
                connectedCallback() {
                    this.render();
                }
                
                render() {
                    this.shadowRoot.innerHTML = template;
                }
            }
            
            customElements.define(name.toLowerCase() + '-component', name);
        }
        
        // 使用宏创建组件
        component(UserCard, 
            {name: '', avatar: '', bio: ''},
            `<div class="user-card">
                <img src="${this.props.avatar}" alt="${this.props.name}">
                <h3>${this.props.name}</h3>
                <p>${this.props.bio}</p>
            </div>`
        );
        
        // 定义测试宏
        defmacro test(description, body) {
            console.group('Test:', description);
            try {
                body
                console.log('✅ PASSED');
            } catch (error) {
                console.error('❌ FAILED:', error);
            }
            console.groupEnd();
        }
        
        // 使用测试宏
        test("Calculator addition", {
            const result = add(2, 3);
            assert(result === 5, "2 + 3 should equal 5");
        });
        
        // 定义性能测量宏
        defmacro measure(name, code) {
            const start = performance.now();
            code
            const end = performance.now();
            console.log(`${name} took ${end - start}ms`);
        }
        
        // 使用性能测量宏
        measure("Heavy computation", {
            let sum = 0;
            for (let i = 0; i < 1000000; i++) {
                sum += i;
            }
        });
    }
}
```

## 5. 组合多个高级模块

```chtl
[Import] @CJmod coroutine
[Import] @CJmod type-annotation  
[Import] @CJmod reactive-system
[Import] @CJmod macro-system

body {
    script {
        // 定义类型化的响应式状态
        interface AppState {
            user: User | null;
            posts: Post[];
            loading: boolean;
        }
        
        // 响应式状态
        state: AppState := {
            user: null,
            posts: [],
            loading: false
        };
        
        // 异步数据流
        async* dataStream() {
            state.loading = true;
            
            // 先加载用户
            const userResponse = await fetch('/api/user');
            const user = await userResponse.json();
            yield { type: 'user', data: user };
            
            // 然后加载帖子
            const postsResponse = await fetch(`/api/users/${user.id}/posts`);
            const posts = await postsResponse.json();
            yield { type: 'posts', data: posts };
            
            // 持续监听新帖子
            const ws = new WebSocket('ws://localhost:3000/posts');
            while (true) {
                const newPost = await new Promise(resolve => {
                    ws.onmessage = (e) => resolve(JSON.parse(e.data));
                });
                yield { type: 'newPost', data: newPost };
            }
        }
        
        // 处理数据流
        async function handleDataStream() {
            for await (const update of dataStream()) {
                switch (update.type) {
                    case 'user':
                        state.user = update.data;
                        break;
                    case 'posts':
                        state.posts = update.data;
                        state.loading = false;
                        break;
                    case 'newPost':
                        state.posts = [update.data, ...state.posts];
                        break;
                }
            }
        }
        
        // 定义渲染宏
        defmacro render(component, props) {
            effect {
                const container = {{#app}};
                container.innerHTML = component(props);
            }
        }
        
        // 使用渲染宏
        render(AppComponent, {
            user: state.user,
            posts: state.posts,
            loading: state.loading
        });
        
        // 启动应用
        handleDataStream();
    }
}
```

## CJmod 的强大之处

1. **深度集成编译器**
   - 可以注册新的 Token 类型
   - 可以添加新的关键字和语法
   - 可以修改 AST 生成过程
   - 可以自定义代码生成

2. **全局状态管理**
   - 模块间可以共享状态
   - 可以生成编译时元数据
   - 支持依赖追踪和分析

3. **灵活的扩展点**
   - 编译各阶段都有钩子
   - 可以包含头文件和源文件
   - 支持自定义节点类型

4. **强大的组合能力**
   - 多个模块可以协同工作
   - 可以基于其他模块构建
   - 支持模块间依赖管理

这种设计让 CJmod 成为一个真正强大的编译器扩展系统，而不仅仅是简单的文本替换工具！