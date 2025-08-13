# CHTL (C++ Hypertext Language)

CHTL是一种创新的模板语言，将C++的强大功能与现代Web开发相结合。

## 🏗️ 架构概述

CHTL采用混合解析器架构，优化了性能和功能支持：

| 组件 | 实现方式 | 说明 |
|------|---------|------|
| **CHTL核心解析器** | 独立实现（原生C++） | 完全自主开发，无外部依赖 |
| **CHTL JS解析器** | 独立实现（原生C++） | 支持CHTL扩展的JavaScript语法 |
| **配置解析器** | 独立实现（原生C++） | 灵活的配置系统，支持自定义关键字 |
| **统一扫描器** | 独立实现（原生C++） | 智能识别和分发代码片段 |
| **CSS解析器** | ANTLR4 | 完整支持现代CSS标准 |
| **JavaScript解析器** | ANTLR4 | 完整支持ES6+语法 |

### 为什么采用混合架构？

1. **性能优化**：CHTL核心使用原生C++实现，启动速度快，内存占用低
2. **完整语言支持**：CSS和JavaScript使用ANTLR4，确保100%语法兼容性
3. **灵活配置**：配置系统独立实现，支持任意自定义关键字
4. **清晰分离**：不同语言片段由专门的解析器处理，架构清晰

## ✨ 主要特性

### 1. 直观的语法
```chtl
div class="container" {
    h1 { "Welcome to CHTL!" }
    p { "A modern template language" }
}
```

### 2. 内置样式支持
```chtl
style {
    /* 原生CSS - 由ANTLR4处理 */
    .container {
        display: flex;
        padding: 20px;
        background: linear-gradient(45deg, #667eea, #764ba2);
    }
}
```

### 3. JavaScript集成
```chtl
script {
    // CHTL增强的JavaScript
    var element = @Element Container;
    
    {{ "Dynamic content: " + new Date() }}
    
    // 原生JavaScript完全支持
    async function fetchData() {
        const response = await fetch('/api/data');
        return response.json();
    }
}
```

### 4. 模板系统
```chtl
[Template] @Element Card(title, content) {
    div class="card" {
        h2 { {{title}} }
        div class="content" { {{content}} }
    }
}

// 使用模板
@Card("Hello", "World")
```

### 5. 灵活的配置系统
```ini
# 自定义关键字（不限于[]或@）
[KeywordMapping]
Template = Layout
Custom = Component
Style = CSS

[Options]
ENABLE_MINIFICATION = true
DEBUG_MODE = false
```

## 🚀 快速开始

### 系统要求
- C++17编译器
- CMake 3.16+
- ANTLR4运行时（仅用于CSS/JS支持）

### 构建项目
```bash
# 克隆仓库
git clone https://github.com/yourusername/chtl.git
cd chtl

# 生成CSS/JS解析器（需要ANTLR4）
./generate_parsers.sh

# 构建项目
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### 基本使用
```bash
# 编译CHTL文件
./chtl input.chtl -o output.html

# 使用配置文件
./chtl input.chtl -c custom.config -o output.html
```

## 📦 模块系统

CHTL支持两种模块类型：

### CMOD（CHTL模块）
纯CHTL源代码模块，用于代码复用：
```bash
chtl --pack-cmod mymodule.chtl
```

### CJMOD（C++扩展模块）
编译的C++扩展，提供高性能功能：
```cpp
// chtholly.h
namespace chtholly {
    class Animation {
        // 动画API
    }
}
```

## 🛠️ 开发工具

### VSCode集成
- 语法高亮
- 自动完成
- 错误检查
- 代码片段

### 调试支持
- 源映射生成
- 错误追踪
- 性能分析

## 📖 文档

- [语法参考](docs/syntax.md)
- [模块开发指南](docs/modules.md)
- [配置选项](docs/configuration.md)
- [API文档](docs/api.md)

## 🤝 贡献

欢迎贡献！请查看[贡献指南](CONTRIBUTING.md)了解详情。

## 📄 许可证

本项目采用MIT许可证。详见[LICENSE](LICENSE)文件。

## 🙏 致谢

- ANTLR4项目 - 提供强大的CSS/JS解析支持
- 所有贡献者和支持者

---

**注意**：CHTL核心完全独立，无需ANTLR4即可运行基本功能。ANTLR4仅用于提供完整的CSS/JavaScript语言支持。