# CHTL (C++ Hypertext Language)

<div align="center">
  
  [![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
  [![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
  [![Version](https://img.shields.io/badge/version-1.0.0-orange.svg)]()
  [![Platform](https://img.shields.io/badge/platform-Linux%20|%20macOS%20|%20Windows-lightgrey.svg)]()
</div>

> 革命性的Web开发语言，将C++的强大功能与直观的HTML式语法完美结合

## 🌟 特性亮点

### 核心特性
- **🚀 原生性能** - 编译为优化的HTML/CSS/JS，零运行时开销
- **🔒 类型安全** - 基于C++的强类型系统，编译时错误检查
- **🧩 组件系统** - 强大的模板(Template)和自定义(Custom)组件
- **📦 模块系统** - CMOD/CJMOD双模块架构，支持热加载
- **⚡ 增强JavaScript** - CHTL JS扩展语法，革新DOM操作方式
- **🛠️ 集成工具链** - 完整的编译器、IDE和开发工具

### 创新语法
- **声明式结构** - 使用`[Template]`、`[Custom]`等关键字定义组件
- **智能选择器** - `{{selector}}`增强选择器语法
- **链式操作** - `->listen()`、`->delegate()`等流畅API
- **样式组合** - 通过`@Style`引用实现样式复用
- **命名空间** - 完整的命名空间和作用域管理

## 🚀 快速开始

### 环境要求
- CMake 3.10+
- C++17编译器 (GCC 7+, Clang 5+, MSVC 2017+)
- ANTLR 4.13.1
- Qt5 (可选，用于IDE)

### 一键构建
```bash
# 克隆仓库
git clone https://github.com/yourusername/chtl.git
cd chtl

# 使用统一构建脚本
./scripts/build_all.sh

# 或分步构建
./scripts/build_compiler.sh    # 构建编译器
./scripts/pack_modules.sh       # 打包模块
./scripts/build_ide.sh          # 构建IDE（可选）
```

### 第一个CHTL程序
```chtl
// hello.chtl
[Import] @Chtl from Chtholly

html {
    head {
        title: "Hello CHTL!";
    }
    
    body {
        div {
            style { @Style Chtholly.FairyCard; }
            
            h1 { text { "Welcome to CHTL!" } }
            
            button {
                text { "Click Me" }
                
                script {
                    {{button}}->listen({
                        click: () => {
                            alert('Hello from CHTL!');
                        }
                    });
                }
            }
        }
    }
}
```

编译运行：
```bash
./build/bin/chtlc hello.chtl -o hello.html
# 在浏览器中打开 hello.html
```

## 📚 文档体系

### 核心文档
- [**语法手册**](docs/CHTL_Syntax.md) - 完整的CHTL语法参考
- [**快速入门**](docs/Getting_Started.md) - 30分钟掌握CHTL
- [**API参考**](docs/API_Reference.md) - 标准库和内置函数
- [**最佳实践**](docs/Best_Practices.md) - 编码规范和设计模式

### 进阶主题
- [**模块系统**](docs/Module_System.md) - CMOD/CJMOD开发指南
- [**模板系统**](docs/Template_System.md) - 高级模板技巧
- [**CHTL JS**](docs/CHTL_JS.md) - 增强JavaScript语法
- [**性能优化**](docs/Performance.md) - 优化技巧和基准测试

### 开发工具
- [**VSCode配置**](VSCODE_SETUP.md) - VSCode开发环境设置
- [**构建系统**](docs/Build_System.md) - CMake配置详解
- [**调试指南**](docs/Debugging.md) - 调试技巧和工具

## 🛠️ VSCode + CMake 开发环境

项目已完整适配VSCode + CMake环境：

### VSCode特性
- ✅ 完整的CHTL语法高亮
- ✅ 智能代码补全和提示
- ✅ 集成构建和调试
- ✅ 一键编译运行（F6）
- ✅ 解决`[]`关键字冲突问题

### 快速配置
1. 安装推荐扩展：
   - CMake Tools
   - C/C++
   - 打开项目会自动提示

2. 使用工作区：
   ```bash
   code CHTL.code-workspace
   ```

3. 构建快捷键：
   - `Ctrl+Shift+B` - 构建项目
   - `F5` - 调试运行
   - `F6` - 编译当前CHTL文件

详见 [VSCode设置指南](VSCODE_SETUP.md)

## 🎯 项目结构

```
chtl/
├── src/                    # 编译器源代码
│   ├── chtl/              # CHTL核心实现
│   ├── chtl_js/           # CHTL JS扩展
│   ├── css/               # CSS处理器
│   └── js/                # JavaScript处理器
├── grammar/               # ANTLR语法定义
├── module/                # 标准模块库
│   └── Chtholly/         # 珂朵莉主题模块
├── ide/                   # IDE项目
├── scripts/              # 构建和工具脚本
├── examples/             # 示例代码
└── docs/                 # 文档
```

## 🤝 贡献指南

我们欢迎所有形式的贡献！

### 贡献方式
- 🐛 报告Bug
- 💡 提出新特性
- 📝 改进文档
- 🔧 提交代码

### 开发流程
1. Fork项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建Pull Request

### 代码规范
- 遵循Google C++代码规范
- 使用clang-format格式化代码
- 编写单元测试
- 更新相关文档

## 📄 许可证

本项目采用MIT许可证 - 查看 [LICENSE](LICENSE) 文件了解详情

## 🙏 致谢

- ANTLR项目提供的强大解析器生成器
- Qt框架支持IDE开发
- VSCode提供优秀的编辑器体验
- 所有贡献者的辛勤付出

---

<div align="center">
  <sub>Built with ❤️ by the CHTL Team</sub>
</div>