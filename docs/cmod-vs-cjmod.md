# CMOD vs CJmod - CHTL 的两大模块系统

## 📦 CMOD - Component Module（组件模块）

CMOD 是 CHTL 的**组件打包和分发格式**，类似于 npm 包，但专门为 CHTL 组件设计。

### CMOD 是什么？

CMOD 是一种文件格式和包管理系统，用于：
- 打包和分享 CHTL 组件
- 管理组件依赖
- 发布可重用的 UI 库

### CMOD 文件结构

```
my-ui-library/
├── package.cmod          # CMOD 清单文件
├── components/           # 组件目录
│   ├── Button.chtl
│   ├── Card.chtl
│   └── Modal.chtl
├── styles/              # 样式资源
│   └── theme.chtl
├── assets/              # 静态资源
│   └── icons/
└── README.md
```

### package.cmod 示例

```json
{
  "name": "@myorg/ui-library",
  "version": "1.0.0",
  "description": "企业级 CHTL UI 组件库",
  "author": "Your Name",
  "license": "MIT",
  
  "exports": {
    "Button": "./components/Button.chtl",
    "Card": "./components/Card.chtl",
    "Modal": "./components/Modal.chtl",
    "theme": "./styles/theme.chtl"
  },
  
  "dependencies": {
    "@chtl/core": "^1.0.0",
    "@chtl/icons": "^2.1.0"
  },
  
  "peerDependencies": {
    "chtl": ">=1.0.0"
  },
  
  "files": [
    "components/**/*.chtl",
    "styles/**/*.chtl",
    "assets/**/*"
  ],
  
  "keywords": ["chtl", "ui", "components"],
  "repository": "https://github.com/myorg/ui-library"
}
```

### 使用 CMOD

#### 1. 安装 CMOD 包
```bash
# 使用 CHTL 包管理器
chtl install @myorg/ui-library

# 或从 git 安装
chtl install github:myorg/ui-library

# 或从本地路径安装
chtl install file:../my-ui-library
```

#### 2. 在 CHTL 中导入
```chtl
// 导入整个库
[Import] * from "@myorg/ui-library";

// 导入特定组件
[Import] @Element Button from "@myorg/ui-library/Button";
[Import] @Element { Card, Modal } from "@myorg/ui-library";

// 导入主题变量
[Import] @Var theme from "@myorg/ui-library/theme";

// 使用导入的组件
html {
    body {
        @Element Button {
            text { "点击我" }
        }
        
        @Element Card {
            h2 { text { "卡片标题" } }
            p { text { "卡片内容" } }
        }
    }
}
```

### 创建自己的 CMOD 包

#### 1. 初始化项目
```bash
chtl init --package my-components
cd my-components
```

#### 2. 创建组件
```chtl
// components/Button.chtl
[Template] @Element Button {
    button {
        class: "btn";
        style {
            padding: 8px 16px;
            background: #007bff;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            
            &:hover {
                background: #0056b3;
            }
            
            &:active {
                transform: scale(0.98);
            }
        }
        
        slot;  // 接收内容
    }
}

// 导出变体
[Template] @Element PrimaryButton inherit Button {
    [Operate] {
        modify class: "btn btn-primary";
    }
}

[Template] @Element SecondaryButton inherit Button {
    [Operate] {
        modify style {
            background: #6c757d;
            
            &:hover {
                background: #545b62;
            }
        }
    }
}
```

#### 3. 发布包
```bash
# 构建包
chtl build --package

# 发布到 CMOD 注册中心
chtl publish

# 或发布到私有注册中心
chtl publish --registry https://my-registry.com
```

### CMOD 的优势

1. **专为 CHTL 设计**
   - 理解 CHTL 语法
   - 优化的打包格式
   - 智能依赖解析

2. **组件级别的包管理**
   - 不是文件级别，而是组件级别
   - 自动处理样式和脚本依赖
   - 树摇优化

3. **版本管理**
   - 语义化版本控制
   - 自动兼容性检查
   - 平滑升级路径

4. **类型支持**
   - 自动生成类型定义
   - IDE 智能提示
   - 编译时类型检查

---

## 🔥 CJmod - CHTL JavaScript Module（语法扩展模块）

CJmod 是 CHTL 的**语法扩展系统**，通过 C++ 插件为 CHTL-JS 添加新的语法特性。

### CJmod 是什么？

CJmod 是一个元编程系统，允许开发者：
- 创造新的 JavaScript 语法
- 在编译时转换代码
- 扩展 CHTL-JS 的能力

### CJmod 与 CMOD 的区别

| 特性 | CMOD | CJmod |
|------|------|-------|
| **用途** | 组件打包和分发 | 语法扩展 |
| **内容** | CHTL 组件、样式、资源 | C++ 语法转换器 |
| **格式** | .cmod 包文件 | .so/.dll 动态库 |
| **分发** | 通过包管理器 | 内置或动态加载 |
| **使用** | `[Import] @Element` | `[Import] @CJmod` |
| **影响** | 添加可用组件 | 改变语言语法 |

### 使用场景对比

#### CMOD - 当你需要：
- 分享和重用 UI 组件
- 创建组件库
- 管理项目依赖
- 发布设计系统

```chtl
// 使用 CMOD 组件库
[Import] @Element Button from "@company/design-system";

@Element Button {
    variant: "primary";
    size: "large";
    text { "确定" }
}
```

#### CJmod - 当你需要：
- 添加新的语法特性
- 创建领域特定语言（DSL）
- 优化特定的代码模式
- 实验新的编程范式

```chtl
// 使用 CJmod 语法扩展
[Import] @CJmod reactive from "CHTL::reactive";

script {
    // CJmod 添加的新语法
    count := 0;  // 响应式变量
    doubled => count.value * 2;  // 计算属性
}
```

## 🎯 总结

### CMOD = 组件生态系统
- 类似 npm，但为 CHTL 优化
- 用于分享和管理组件
- 构建可重用的 UI 库

### CJmod = 语言扩展系统
- 类似 Babel 插件，但更强大
- 用于扩展语言语法
- 创造新的编程体验

两者共同构成了 CHTL 强大的生态系统：
- **CMOD** 让你站在巨人的肩膀上（重用他人的组件）
- **CJmod** 让你成为巨人（创造新的语法）

## 实际案例

### 企业级项目结构
```
my-app/
├── chtl.config.json       # CHTL 配置
├── package.cmod           # 项目的 CMOD 配置
├── node_modules/          # CMOD 包安装目录
│   ├── @chtl/core/
│   ├── @company/ui/       # 公司 UI 组件库 (CMOD)
│   └── @team/utils/       # 团队工具库 (CMOD)
├── cjmods/               # CJmod 模块
│   ├── reactive.so       # 响应式语法扩展
│   ├── pipeline.so       # 管道操作符
│   └── custom-dsl.so     # 自定义 DSL
└── src/
    └── App.chtl
```

### App.chtl
```chtl
// 导入 CMOD 组件
[Import] @Element { Button, Card } from "@company/ui";
[Import] @Var theme from "@company/ui/theme";

// 导入 CJmod 语法扩展
[Import] @CJmod reactive from "CHTL::reactive";
[Import] @CJmod pipeline from "./cjmods/pipeline";

// 使用两者的组合
@Element Card {
    style {
        background: theme(cardBackground);
    }
    
    h2 { text { "用户统计" } }
    
    script {
        // CJmod 提供的响应式语法
        userCount := 0;
        activeUsers := 0;
        
        // CJmod 提供的管道语法
        const stats = fetchUserStats()
            |> processData
            |> formatForDisplay;
    }
    
    // CMOD 提供的组件
    @Element Button {
        text { "刷新数据" }
        onclick: refreshStats;
    }
}
```

这就是 CMOD 和 CJmod 的区别和用途。它们相互补充，共同让 CHTL 成为一个既强大又灵活的前端开发平台。