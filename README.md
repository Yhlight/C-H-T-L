# CHTL - Component HTML Template Language

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/yourusername/chtl)
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)
[![Version](https://img.shields.io/badge/version-1.0.0-orange)](https://github.com/yourusername/chtl/releases)

CHTL (Component HTML Template Language) 是一个现代化的组件化 HTML 模板语言，旨在提供更优雅、更强大的 Web 开发体验。

## ✨ 特性

- **组件化设计**：通过 `@Element`、`@Style`、`@Var` 实现真正的组件化开发
- **CHTL-JS 增强**：使用 `{{}}` 语法无缝集成 JavaScript，支持响应式编程
- **智能样式系统**：局部样式自动作用域化，支持 `&` 伪选择器
- **模板系统**：强大的模板定义和特化机制
- **CJmod 插件系统**：通过 C++ 插件实现无限语法扩展可能
- **完善的错误处理**：详细的错误信息和修复建议
- **跨平台支持**：支持 Web、React、Vue 等多种目标平台

## 🚀 快速开始

### 安装

```bash
# 克隆仓库
git clone https://github.com/yourusername/chtl.git
cd chtl

# 构建项目
mkdir build && cd build
cmake ..
make -j$(nproc)

# 安装（可选）
sudo make install
```

### 第一个 CHTL 文件

创建 `hello.chtl`：

```chtl
// 定义变量组
[Template] @Var Theme {
    primary: "#007bff";
    secondary: "#6c757d";
    spacing: "1rem";
}

// 定义可重用组件
[Template] @Element Button {
    button {
        class: "btn";
        style {
            background: Theme(primary);
            padding: Theme(spacing);
            border: none;
            border-radius: 4px;
            color: white;
            cursor: pointer;
            
            &:hover {
                opacity: 0.8;
            }
        }
        slot;  // 插槽，用于接收内容
    }
}

// 主页面
html {
    head {
        title { text { "Hello CHTL" } }
    }
    
    body {
        h1 { 
            text { "Welcome to CHTL!" }
            style {
                color: Theme(primary);
            }
        }
        
        @Element Button {
            text { "Click Me" }
            
            script {
                {{&}}.addEventListener('click', function() {
                    alert('Hello from CHTL-JS!');
                });
            }
        }
    }
}
```

编译：

```bash
chtl hello.chtl -o output/
```

## 📖 文档

### 基础语法

#### 元素定义
```chtl
div {
    id: "myDiv";
    class: "container active";
    data-value: 42;
    
    // 子元素
    p { text { "Hello" } }
}
```

#### 文本内容
```chtl
text { "Plain text content" }
```

#### 属性
```chtl
element {
    attribute: "value";      // 字符串
    number: 42;             // 数字
    boolean: true;          // 布尔值
}
```

### 模板系统

#### 定义模板
```chtl
[Template] @Element Card {
    div {
        class: "card";
        slot;  // 默认插槽
    }
}
```

#### 使用模板
```chtl
@Element Card {
    h2 { text { "Card Title" } }
    p { text { "Card content" } }
}
```

### 样式系统

#### 全局样式
```chtl
style {
    body {
        margin: 0;
        font-family: Arial, sans-serif;
    }
    
    @media (max-width: 768px) {
        .container {
            padding: 10px;
        }
    }
}
```

#### 局部样式
```chtl
div {
    style {
        padding: 20px;
        background: #f0f0f0;
        
        &:hover {
            background: #e0e0e0;
        }
    }
}
```

### CHTL-JS 语法

#### 元素引用
```chtl
script {
    {{&}}              // 当前元素
    {{#elementId}}     // 通过 ID 获取元素
}
```

#### 事件监听
```chtl
button {
    script {
        {{&}}.listen({
            click: function() { console.log('Clicked!'); },
            mouseenter: function() { this.style.opacity = '0.8'; }
        });
    }
}
```

### CJmod 系统

#### 导入模块
```chtl
[Import] @CJmod reactive from "builtin:reactive";

script {
    // 使用响应式赋值
    count := 0;
    
    // 计算属性
    doubled => { return count.value * 2; }
    
    // 监听变化
    watch count -> {
        console.log('Count changed:', newVal);
    }
}
```

#### 创建 CJmod 插件

```cpp
#include "CJmod/CJmodCore.h"

class MyModule : public CJmodModule {
public:
    std::vector<SyntaxBuilder> syntax() override {
        return {
            SyntaxBuilder("my-syntax")
                .pattern(R"(myKeyword\s+(\w+))")
                .generate([](const ScanResult& r, GenerateContext* ctx) {
                    return "console.log('" + r.captures.at("1") + "')";
                })
        };
    }
    
    void runtime(RuntimeBuilder& builder) override {
        builder.addFunction("myHelper", R"(
            function(value) {
                return value.toUpperCase();
            }
        )");
    }
};

// 导出函数
extern "C" {
    CJmodModule* createModule() {
        return new MyModule();
    }
}
```

## 🛠️ 高级特性

### 命名空间
```chtl
[Namespace] Components {
    [Template] @Element Button { ... }
    [Template] @Style theme { ... }
}

[Import] * from Components;
```

### 配置系统
```chtl
[Config] {
    output: "dist";
    platform: "web";
    minify: true;
}
```

### 操作继承
```chtl
[Template] @Element BaseButton {
    button { class: "btn"; }
}

[Template] @Element PrimaryButton inherit BaseButton {
    [Operate] {
        modify class: "btn btn-primary";
        insert style { background: blue; }
    }
}
```

## 🧪 测试

运行测试套件：

```bash
cd build
make test

# 或使用脚本
../scripts/run_tests.sh
```

## 🤝 贡献

我们欢迎所有形式的贡献！请查看 [CONTRIBUTING.md](CONTRIBUTING.md) 了解详情。

### 开发设置

```bash
# 安装开发依赖
sudo apt-get install cmake g++ libgtest-dev

# 启用调试构建
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

### 代码风格

- 使用 4 个空格缩进
- 遵循 Google C++ 风格指南
- 所有公共 API 必须有文档注释

## 📄 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件。

## 🙏 致谢

感谢所有贡献者和支持者，是你们让 CHTL 变得更好！

## 📞 联系方式

- 项目主页：[https://github.com/yourusername/chtl](https://github.com/yourusername/chtl)
- 问题反馈：[Issues](https://github.com/yourusername/chtl/issues)
- 邮件：your-email@example.com

---

Made with ❤️ by the CHTL Team