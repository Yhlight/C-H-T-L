# CHTL Language Support for VSCode

CHTL语言的VSCode扩展，提供语法高亮、代码片段、智能提示等功能。

## 功能特性

- 🎨 **语法高亮** - 完整的CHTL语法着色
- ✂️ **代码片段** - 常用代码模板
- 🔧 **语言配置** - 括号匹配、注释切换
- 🎯 **智能提示** - 关键字和标签自动完成
- 🎨 **主题支持** - 自定义颜色主题

## 目录结构

```
chtl-syntax/
├── src/                    # 扩展源代码（未来功能）
│   └── extension.ts        # 扩展主入口
│
├── syntaxes/              # 语法定义
│   └── chtl.tmLanguage.json   # TextMate语法
│
├── snippets/              # 代码片段
│   └── chtl.json              # CHTL代码片段
│
├── themes/                # 颜色主题（可选）
│   └── chtl-dark.json         # 深色主题
│
├── keybindings/           # 快捷键绑定
│   └── keybindings.json       # 自定义快捷键
│
├── images/                # 图标和图片资源
│   └── icon.png               # 扩展图标
│
├── language-configuration.json # 语言配置
├── package.json               # 扩展清单
└── README.md                  # 本文件
```

## 安装方法

### 开发模式安装

1. 在VSCode中打开CHTL项目
2. 扩展会自动从 `.vscode/extensions/` 加载

### 打包安装

```bash
# 安装vsce工具
npm install -g vsce

# 切换到扩展目录
cd .vscode/extensions/chtl-syntax

# 打包扩展
vsce package

# 安装生成的.vsix文件
code --install-extension chtl-syntax-0.0.1.vsix
```

## 使用说明

### 文件类型识别

扩展自动识别以下文件类型：
- `.chtl` - CHTL源文件
- `.cmod` - CHTL模块文件

### 代码片段

输入以下前缀触发代码片段：

- `template` - 模板定义
- `custom` - 自定义定义
- `element` - 元素模板
- `style` - 样式模板
- `var` - 变量组模板
- `import` - 导入语句
- `namespace` - 命名空间

### 快捷键

- `Ctrl+/` - 切换行注释
- `Ctrl+Shift+A` - 切换块注释
- `Alt+Shift+F` - 格式化文档（需要格式化器）

## 开发指南

### 修改语法高亮

编辑 `syntaxes/chtl.tmLanguage.json` 文件：

```json
{
  "patterns": [
    {
      "name": "keyword.control.chtl",
      "match": "\\b(Template|Custom|Import)\\b"
    }
  ]
}
```

### 添加代码片段

编辑 `snippets/chtl.json` 文件：

```json
{
  "My Snippet": {
    "prefix": "mysnip",
    "body": [
      "[Template] @${1:Style} ${2:name}",
      "{",
      "\t$0",
      "}"
    ],
    "description": "创建模板"
  }
}
```

### 调试扩展

1. 按 `F5` 启动扩展开发主机
2. 在新窗口中测试扩展功能
3. 查看调试控制台的输出

## 贡献指南

欢迎贡献代码！请遵循以下步骤：

1. Fork 项目
2. 创建功能分支
3. 提交更改
4. 发起 Pull Request

## 许可证

MIT License