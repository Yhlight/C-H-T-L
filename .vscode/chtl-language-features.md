# CHTL语言特性与VSCode配置

## 关于`[]`关键字冲突的解决方案

CHTL使用方括号`[]`作为声明块的关键字，例如：
- `[Template]`
- `[Custom]`
- `[Import]`
- `[Namespace]`
- `[Configuration]`
- `[Info]`
- `[Export]`
- `[Origin]`

这与VSCode的自动括号补全功能存在冲突。我们采取了以下措施：

### 1. 禁用方括号自动补全

在`.vscode/settings.json`中，为CHTL文件特别配置：
```json
"[chtl]": {
    "editor.autoClosingBrackets": "never",
    "editor.autoSurround": "never"
}
```

### 2. 修改语言配置

在`.vscode/extensions/chtl-syntax/language-configuration.json`中，从`autoClosingPairs`中移除了`["[", "]"]`。

### 3. 使用代码片段

为了方便输入CHTL的关键字块，我们提供了代码片段。输入以下前缀后按Tab：
- `template-style` → `[Template] @Style`
- `template-element` → `[Template] @Element`
- `custom-style` → `[Custom] @Style`
- `import` → `[Import] @...`
- `namespace` → `[Namespace]`

### 4. 其他建议

1. **手动输入方括号**：由于禁用了自动补全，需要手动输入完整的`[]`。

2. **使用Emmet缩写**：可以定义自定义的Emmet缩写来快速输入常用的CHTL结构。

3. **快捷键绑定**：可以创建自定义快捷键来插入常用的CHTL块结构。

### 5. 如果仍有问题

如果你发现方括号输入仍有问题，可以尝试：

1. 重新加载VSCode窗口：`Ctrl+Shift+P` → "Reload Window"
2. 确保CHTL语法扩展已启用
3. 检查是否有其他扩展干扰

### 6. 自定义快捷键示例

可以在`keybindings.json`中添加：
```json
{
    "key": "ctrl+alt+[",
    "command": "editor.action.insertSnippet",
    "when": "editorTextFocus && resourceExtname == .chtl",
    "args": {
        "snippet": "[$1] $0"
    }
}
```

这样按`Ctrl+Alt+[`就会插入`[]`并将光标放在方括号内。