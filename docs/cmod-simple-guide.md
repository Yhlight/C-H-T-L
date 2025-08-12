# CMOD 简单说明

## CMOD 是什么？

**CMOD = CHTL 的组件包**

就像：
- npm 包 → JavaScript
- pip 包 → Python  
- **CMOD 包 → CHTL**

## 🎁 CMOD 包含什么？

```
一个 CMOD 包
├── 📦 可重用的组件（Button、Card、Modal...）
├── 🎨 共享的样式（主题、颜色、间距...）
├── 📄 组件文档
└── 🖼️ 相关资源（图标、字体...）
```

## 📥 如何使用 CMOD？

### 1. 安装别人的组件库
```bash
# 安装 Ant Design 的 CHTL 版本
chtl install @antd/chtl

# 安装公司内部组件库
chtl install @company/ui-kit
```

### 2. 在项目中使用
```chtl
// 导入组件
[Import] @Element Button from "@antd/chtl/Button";
[Import] @Element Card from "@company/ui-kit/Card";

// 直接使用
html {
    body {
        @Element Card {
            title: "用户信息";
            
            @Element Button {
                type: "primary";
                text { "保存" }
            }
        }
    }
}
```

## 📤 创建自己的 CMOD

### 1. 创建一个按钮组件
```chtl
// my-button.chtl
[Template] @Element MyButton {
    button {
        class: "my-btn";
        style {
            background: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            
            &:hover {
                background: #45a049;
            }
        }
        slot;
    }
}
```

### 2. 打包成 CMOD
```bash
# 初始化 CMOD 项目
chtl init --package my-components

# 添加组件
cp my-button.chtl my-components/components/

# 发布
cd my-components
chtl publish
```

### 3. 其他人就可以使用了
```bash
chtl install @yourname/my-components
```

## 🌟 CMOD 的好处

1. **共享组件**
   - 不用重复造轮子
   - 团队统一 UI 风格

2. **版本管理**
   - 组件更新不影响旧项目
   - 可以锁定版本

3. **依赖管理**
   - 自动安装组件需要的其他包
   - 避免依赖冲突

4. **文档集成**
   - 组件自带使用说明
   - IDE 自动提示

## 🆚 CMOD vs 普通文件

### 普通方式（复制粘贴）
```chtl
// 需要手动复制 Button.chtl 到每个项目
// 更新时需要手动替换所有项目的文件
// 没有版本控制
```

### CMOD 方式
```chtl
// 一行命令安装
[Import] @Element Button from "@ui/button";
// 自动更新
// 版本控制
// 依赖管理
```

## 📊 实际例子

### 公司设计系统
```
@company/design-system (CMOD)
├── components/
│   ├── Button.chtl      # 标准按钮
│   ├── Input.chtl       # 标准输入框
│   ├── Table.chtl       # 数据表格
│   └── Form.chtl        # 表单组件
├── styles/
│   ├── colors.chtl      # 公司配色
│   ├── typography.chtl  # 字体规范
│   └── spacing.chtl     # 间距系统
└── package.cmod         # 包配置
```

团队使用：
```chtl
[Import] * from "@company/design-system";

// 所有项目自动统一风格
@Element Form {
    @Element Input {
        label: "用户名";
        placeholder: "请输入用户名";
    }
    
    @Element Button {
        type: "primary";
        text { "登录" }
    }
}
```

## 🎯 总结

**CMOD = CHTL 世界的 npm**

- 用来打包和分享 CHTL 组件
- 让组件可以被重复使用
- 管理项目的组件依赖
- 构建组件生态系统

简单说：**CMOD 让你不用重复写代码，直接用别人写好的组件。**