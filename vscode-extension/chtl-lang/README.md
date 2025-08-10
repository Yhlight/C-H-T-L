# CHTL Language Support for VS Code

这是 CHTL (Chtholly Template Language) 的 Visual Studio Code 扩展，提供语法高亮、代码片段、智能感知和集成编译器支持。

## 功能特性

### 语法高亮
- 完整的 CHTL 语法高亮支持
- 支持所有 CHTL 构造：
  - 配置块 `[Configuration]` 和 `[Name]`
  - 导入/导出 `[Import]` 和 `[Export]`
  - 命名空间 `[Namespace]`
  - 模板和自定义组件 `[Template]` 和 `[Custom]`
  - 样式和脚本块 `style {}` 和 `script {}`
  - CHTL JS 增强语法（`{{selector}}`、`->`、`listen`、`animate` 等）

### 代码片段
- 60+ 个预定义的代码片段，加速开发
- 涵盖所有主要的 CHTL 构造
- 智能占位符和 Tab 导航

### 智能感知
- 悬停文档显示
- 自动完成建议
- 组件定义跳转
- 错误诊断

### 集成编译器
- 内置 CHTL 编译器（支持 Linux x64）
- 编译当前文件：`Ctrl+Shift+P` → "CHTL: Compile Current File"
- 编译所有文件：`Ctrl+Shift+P` → "CHTL: Compile All Files"
- 浏览器预览：`Ctrl+Shift+P` → "CHTL: Preview in Browser"
- CMOD 打包：`Ctrl+Shift+P` → "CHTL: Pack CMOD Module"

## 安装

1. 在 VS Code 中打开扩展面板（`Ctrl+Shift+X`）
2. 搜索 "CHTL"
3. 点击安装

或者从源码安装：
```bash
cd vscode-extension/chtl-lang
npm install
npm run compile
# 然后在 VS Code 中按 F5 运行扩展
```

## 使用方法

### 创建新的 CHTL 文件
1. 创建一个 `.chtl` 扩展名的文件
2. 开始编写 CHTL 代码，扩展会自动激活

### 编译文件
1. 打开一个 `.chtl` 文件
2. 按 `Ctrl+Shift+P` 打开命令面板
3. 运行 "CHTL: Compile Current File"
4. 编译结果将保存在配置的输出目录（默认 `dist`）

### 配置选项

在 VS Code 设置中可以配置：

- `chtl.compiler.path`: 自定义编译器路径（留空使用内置编译器）
- `chtl.compiler.outputDirectory`: 输出目录（默认：`dist`）
- `chtl.compiler.debugMode`: 启用调试模式
- `chtl.compiler.moduleSearchPaths`: 模块搜索路径
- `chtl.format.enable`: 启用格式化
- `chtl.format.indentSize`: 缩进大小
- `chtl.lint.enable`: 启用代码检查

## 示例代码

```chtl
// 基本的 CHTL 页面
html {
    head {
        title { text { "我的 CHTL 页面" } }
        style {
            body {
                font-family: Arial, sans-serif;
            }
        }
    }
    body {
        div {
            id: "app";
            class: "container";
            
            style {
                .container {
                    max-width: 1200px;
                    margin: 0 auto;
                }
                
                &:hover {
                    background-color: #f0f0f0;
                }
            }
            
            h1 { text { "欢迎使用 CHTL！" } }
            
            script {
                // CHTL JS 增强语法
                {{#app}}->listen({
                    click: function() {
                        console.log("Clicked!");
                    }
                });
            }
        }
    }
}
```

## 已知问题

- 编译器目前只支持 Linux x64 平台
- 某些复杂的 CHTL 构造可能还需要进一步优化

## 贡献

欢迎提交问题和拉取请求！

## 许可证

MIT