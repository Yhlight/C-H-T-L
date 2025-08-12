# CMOD 是否应该包含 CJmod 功能？

## 🤔 问题分析

你提出了一个很好的问题：CMOD 作为组件包，是否应该能够包含 CJmod 语法扩展？

## ✅ 支持的理由

### 1. **完整的组件体验**
某些高级组件可能需要特定的语法支持才能发挥最佳效果。

```chtl
// @company/reactive-ui 包
package.cmod
├── components/
│   └── ReactiveForm.chtl    # 响应式表单组件
├── cjmods/
│   └── form-binding.so      # 表单双向绑定语法
└── package.json
```

使用时：
```chtl
[Import] @Element ReactiveForm from "@company/reactive-ui";
// 自动加载 form-binding 语法扩展

@Element ReactiveForm {
    // 使用包自带的语法扩展
    username <=> model.username;  // 双向绑定语法
    password <=> model.password;
}
```

### 2. **领域特定组件库**
某些专业领域的组件库可能需要自己的 DSL。

```chtl
// @charts/chtl-charts 包
package.cmod
├── components/
│   └── DataChart.chtl
├── cjmods/
│   └── chart-dsl.so        // 图表 DSL
└── examples/
```

```chtl
[Import] @Element DataChart from "@charts/chtl-charts";

@Element DataChart {
    // 使用图表专用语法
    data | filter(x => x > 0) 
         | map(x => x * 100)
         | plot {
             type: "bar",
             color: gradient(blue -> green)
         };
}
```

### 3. **版本一致性**
组件和其配套语法可以一起版本管理，避免兼容性问题。

## ❌ 反对的理由

### 1. **关注点分离**
- CMOD = 组件（what）
- CJmod = 语法（how）

混合可能导致职责不清。

### 2. **安全性考虑**
CJmod 是 C++ 动态库，涉及更多安全风险：
- 需要系统权限
- 可能有恶意代码
- 需要更严格的审查

### 3. **复杂度增加**
- 安装 CMOD 需要编译环境？
- 跨平台兼容性问题
- 包大小显著增加

### 4. **语法污染**
多个包带来的语法扩展可能冲突：
```chtl
// 包 A 定义了 |> 操作符
// 包 B 也定义了 |> 操作符
// 冲突！
```

## 🎯 推荐方案

### 方案一：分离但关联（推荐）

CMOD 和 CJmod 保持独立，但可以声明依赖关系：

```json
// package.cmod
{
  "name": "@company/reactive-ui",
  "version": "1.0.0",
  "cjmodDependencies": {
    "@company/reactive-syntax": "^1.0.0"
  },
  "exports": {
    "ReactiveForm": "./components/ReactiveForm.chtl"
  }
}
```

使用时：
```chtl
// 自动提示需要安装 CJmod
[Import] @Element ReactiveForm from "@company/reactive-ui";
// 提示：此组件推荐配合 @company/reactive-syntax 使用

// 用户选择是否安装
[Import] @CJmod reactive from "@company/reactive-syntax";
```

### 方案二：可选包含

CMOD 可以包含 CJmod，但必须是可选的：

```json
{
  "name": "@company/ui-kit",
  "optionalFeatures": {
    "syntax-extensions": {
      "description": "高级语法支持",
      "cjmods": ["./extensions/advanced.so"],
      "platforms": ["darwin-x64", "linux-x64", "win32-x64"]
    }
  }
}
```

安装时：
```bash
# 基础安装（仅组件）
chtl install @company/ui-kit

# 包含语法扩展
chtl install @company/ui-kit --with-syntax

# 或者稍后添加
chtl install @company/ui-kit/syntax-extensions
```

### 方案三：元包（Meta Package）

创建一个更高层的包类型，同时管理 CMOD 和 CJmod：

```
@company/reactive-suite (元包)
├── package.meta
├── components/          # CMOD 部分
│   └── reactive-ui/
├── syntax/             # CJmod 部分
│   └── reactive-syntax/
└── docs/
```

## 🏆 最佳实践建议

### 1. **默认分离**
- CMOD 专注于组件
- CJmod 专注于语法
- 保持简单和纯粹

### 2. **特殊情况下关联**
- 通过依赖声明关联
- 让用户选择是否需要语法扩展
- 提供清晰的文档说明

### 3. **未来可能**
随着生态系统成熟，可以考虑：
- 官方认证的"组件+语法"套件
- 沙箱化的 CJmod 运行环境
- 更智能的冲突解决机制

## 📊 实际例子

### 好的设计：mui-chtl
```json
// @mui/chtl package.cmod
{
  "name": "@mui/chtl",
  "description": "Material-UI for CHTL",
  "exports": {
    "Button": "./Button.chtl",
    "TextField": "./TextField.chtl"
  },
  "peerDependencies": {
    "@mui/theme-system": "^5.0.0"
  },
  "suggests": {
    "@mui/chtl-sx": "用于 sx prop 语法支持"
  }
}
```

用户可以选择：
```chtl
// 基础使用
[Import] @Element Button from "@mui/chtl";

// 或者带语法扩展
[Import] @CJmod sx from "@mui/chtl-sx";
[Import] @Element Button from "@mui/chtl";

@Element Button {
    sx: {
        m: 2,              // margin: 2 * 8px
        p: 1,              // padding: 1 * 8px  
        bgcolor: 'primary.main'
    }
}
```

## 🎁 结论

**CMOD 不应该默认包含 CJmod 功能，但应该支持声明对 CJmod 的依赖或推荐。**

这样可以：
1. 保持架构清晰
2. 给用户选择权
3. 避免安全风险
4. 简化包管理

未来随着技术成熟，可以探索更紧密的集成方式。