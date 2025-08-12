# CJmod 能力展示

CJmod 让 CHTL-JS 拥有无限的语法扩展可能。通过 C++ 插件，开发者可以创造全新的 JavaScript 语法。

## 核心能力

### 1. 响应式编程语法

```javascript
// 原始 JavaScript
let count = 0;
let doubled = count * 2;
// 需要手动更新 doubled

// CJmod reactive 模块
count := 0;                    // 响应式变量
doubled => count.value * 2;    // 自动计算属性

// 当 count 改变时，doubled 自动更新
count.value = 5;  // doubled 自动变成 10
```

### 2. 优雅的异步语法

```javascript
// 原始 JavaScript
fetch('/api/data')
  .then(res => res.json())
  .then(data => console.log(data))
  .catch(err => console.error(err));

// CJmod async 模块
data := await~ fetch('/api/data');  // 自动处理异步
console.log(data);  // 自动解析 JSON
```

### 3. 模式匹配

```javascript
// 原始 JavaScript
if (type === 'success') {
  handleSuccess(data);
} else if (type === 'error') {
  handleError(data);
} else {
  handleUnknown(data);
}

// CJmod pattern 模块
match type {
  'success' -> handleSuccess(data);
  'error' -> handleError(data);
  _ -> handleUnknown(data);
}
```

### 4. 管道操作符

```javascript
// 原始 JavaScript
const result = capitalize(trim(toLowerCase(input)));

// CJmod pipe 模块
const result = input 
  |> toLowerCase
  |> trim
  |> capitalize;
```

### 5. 装饰器语法（不需要编译器支持）

```javascript
// CJmod decorator 模块
@log
@cache(60)
@validate
function fetchUserData(userId) {
  return api.getUser(userId);
}
```

### 6. 区间和范围

```javascript
// 原始 JavaScript
for (let i = 0; i < 10; i++) {
  console.log(i);
}

// CJmod range 模块
for i in 0..10 {
  console.log(i);
}

// 数组切片
arr[1..5]    // 等同于 arr.slice(1, 5)
arr[..3]     // 等同于 arr.slice(0, 3)
arr[3..]     // 等同于 arr.slice(3)
```

### 7. 空值合并和可选链的增强

```javascript
// CJmod optional 模块
const name = user?.profile?.name ?? "Anonymous";

// 更强大的空值处理
const config = {
  port: env.PORT ?? config.port ?? 3000,
  host: env.HOST ?? "localhost"
};

// 安全导航
user?.address?.city?.toUpperCase?() ?? "N/A"
```

### 8. 类型守卫

```javascript
// CJmod guard 模块
guard typeof value {
  'string' -> processString(value);
  'number' -> processNumber(value);
  'object' -> {
    if (Array.isArray(value)) {
      processArray(value);
    } else {
      processObject(value);
    }
  }
}
```

### 9. 并发控制

```javascript
// CJmod concurrent 模块
// 并行执行多个异步操作
parallel {
  userData := fetch('/api/user');
  posts := fetch('/api/posts');
  comments := fetch('/api/comments');
}

// 所有请求完成后继续
console.log(userData, posts, comments);
```

### 10. 事件流处理

```javascript
// CJmod stream 模块
stream clicks from button {
  |> debounce(300)
  |> map(e => e.target.value)
  |> filter(val => val.length > 3)
  |> subscribe(val => {
    console.log('Search:', val);
  });
}
```

## 实际应用示例

### 示例 1：响应式 Todo 应用

```javascript
// 使用 CJmod reactive
todos := [];
filter := 'all';

// 自动计算的统计
activeTodos => todos.value.filter(t => !t.completed);
completedTodos => todos.value.filter(t => t.completed);
visibleTodos => {
  match filter.value {
    'active' -> activeTodos.value;
    'completed' -> completedTodos.value;
    _ -> todos.value;
  }
}

// 监听变化
watch todos -> {
  localStorage.setItem('todos', JSON.stringify(todos.value));
}
```

### 示例 2：表单验证

```javascript
// CJmod validate 模块
@validate({
  email: required & email,
  password: required & minLength(8),
  age: required & number & between(18, 100)
})
form := {
  email: '',
  password: '',
  age: null
};

// 自动生成验证状态
if (form.isValid) {
  submit(form.data);
}
```

### 示例 3：状态机

```javascript
// CJmod state 模块
machine LoadingState {
  initial idle;
  
  states {
    idle {
      on FETCH -> loading;
    }
    loading {
      on SUCCESS -> success;
      on ERROR -> error;
    }
    success {
      on RESET -> idle;
    }
    error {
      on RETRY -> loading;
      on RESET -> idle;
    }
  }
}

// 使用
state := LoadingState.create();
state.send('FETCH');  // 状态变为 loading
```

### 示例 4：依赖注入

```javascript
// CJmod inject 模块
@injectable
class UserService {
  @inject(HttpClient) http;
  @inject(AuthService) auth;
  
  async getProfile() {
    const token = await this.auth.getToken();
    return this.http.get('/profile', { token });
  }
}
```

## CJmod 模块开发示例

```cpp
// reactive.cpp - 实现响应式语法
class ReactiveModule : public CJmodModule {
public:
    std::vector<SyntaxBuilder> syntax() override {
        return {
            // := 响应式赋值
            SyntaxBuilder("reactive-assign")
                .pattern(R"((\w+)\s*:=\s*(.+);)")
                .generate([](const ScanResult& r, GenerateContext* ctx) {
                    return "const " + r.captures[1] + 
                           " = CHTL.reactive(" + r.captures[2] + ");";
                }),
            
            // => 计算属性
            SyntaxBuilder("computed")
                .pattern(R"((\w+)\s*=>\s*(.+);)")
                .generate([](const ScanResult& r, GenerateContext* ctx) {
                    return "const " + r.captures[1] + 
                           " = CHTL.computed(() => " + r.captures[2] + ");";
                }),
            
            // watch 语法
            SyntaxBuilder("watch")
                .pattern(R"(watch\s+(\w+)\s*->\s*\{([^}]+)\})")
                .generate([](const ScanResult& r, GenerateContext* ctx) {
                    return r.captures[1] + ".subscribe((newVal, oldVal) => {" 
                           + r.captures[2] + "});";
                })
        };
    }
    
    void runtime(RuntimeBuilder& builder) override {
        builder.addFunction("reactive", R"(
            function(initialValue) {
                let value = initialValue;
                const subscribers = new Set();
                
                return {
                    get value() { return value; },
                    set value(newValue) {
                        const oldValue = value;
                        value = newValue;
                        subscribers.forEach(fn => fn(newValue, oldValue));
                    },
                    subscribe(fn) {
                        subscribers.add(fn);
                        return () => subscribers.delete(fn);
                    }
                };
            }
        )");
        
        builder.addFunction("computed", R"(
            function(computeFn) {
                const result = CHTL.reactive(computeFn());
                // 实际实现需要依赖追踪
                return result;
            }
        )");
    }
};
```

## CJmod 的优势

### 1. **编译时转换**
- 零运行时开销
- 生成标准 JavaScript
- 完全的浏览器兼容性

### 2. **类型安全**
- C++ 编译时检查
- 生成正确的 JavaScript
- 避免运行时错误

### 3. **可组合性**
- 模块可以相互配合
- 逐步采用
- 按需加载

### 4. **调试友好**
- 生成可读的 JavaScript
- 保留源码映射
- 清晰的错误信息

### 5. **性能优化**
- 编译时优化
- 死代码消除
- 智能代码生成

## 无限可能

CJmod 让你可以：

1. **创造领域特定语言（DSL）**
   - 为特定业务创建专属语法
   - 简化复杂操作
   - 提高开发效率

2. **移植其他语言特性**
   - Python 的列表推导式
   - Ruby 的块语法
   - Rust 的模式匹配
   - Go 的并发模型

3. **实验新的编程范式**
   - 函数式编程增强
   - 响应式编程
   - 声明式编程
   - 元编程

4. **优化特定场景**
   - 游戏开发语法
   - 数据处理管道
   - UI 状态管理
   - 网络请求处理

CJmod 不仅仅是语法糖，它是一个强大的元编程系统，让 JavaScript 成为一个可以不断进化的语言。