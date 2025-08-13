# CHTL 项目结构

## 目录结构

```
/workspace/
├── src/                        # 源代码
│   └── chtl/
│       ├── core/              # 核心功能
│       │   ├── Context.h/cpp  # 上下文管理
│       │   ├── StateMachine.h/cpp # 状态机
│       │   └── Types.h        # 基础类型定义
│       ├── parser/            # 解析器（ANTLR生成的代码）
│       │   ├── chtl/          # CHTL解析器
│       │   ├── css/           # CSS解析器
│       │   ├── js/            # JavaScript解析器
│       │   └── config/        # 配置解析器
│       ├── generator/         # 代码生成器
│       │   ├── HtmlGenerator.h/cpp
│       │   ├── CssGenerator.h/cpp
│       │   └── JsGenerator.h/cpp
│       ├── scanner/           # 扫描器
│       │   ├── UnifiedScanner.h/cpp
│       │   └── ScannerIntegration.h/cpp
│       ├── template/          # 模板系统
│       │   ├── Template.h/cpp
│       │   └── TemplateManager.h/cpp
│       ├── custom/            # Custom系统
│       │   ├── Custom.h/cpp
│       │   └── CustomManager.h/cpp
│       ├── origin/            # Origin系统
│       │   └── Origin.h/cpp
│       ├── import/            # Import系统
│       │   ├── Import.h/cpp
│       │   └── ImportResolver.h/cpp
│       ├── namespace/         # 命名空间系统
│       │   └── Namespace.h/cpp
│       ├── constraint/        # 约束系统
│       │   └── Constraint.h/cpp
│       ├── module/            # 模块系统
│       │   ├── CMOD.h/cpp
│       │   └── CJMOD.h/cpp
│       ├── optimizer/         # 优化器
│       │   ├── JSOptimizer.h/cpp
│       │   └── CSSOptimizer.h/cpp
│       ├── error/             # 错误处理
│       │   ├── ErrorHandler.h/cpp
│       │   └── Exception.h
│       ├── utils/             # 工具类
│       │   ├── StringUtils.h/cpp
│       │   ├── FileUtils.h/cpp
│       │   └── Memory.h/cpp
│       └── config/            # 配置系统
│           └── Configuration.h/cpp
├── include/                   # 公共头文件
│   └── chtl/
│       ├── chtl.h            # 主头文件
│       └── version.h         # 版本信息
├── lib/                      # 标准库
│   └── chtl/
│       ├── core/             # 核心模块
│       ├── ui/               # UI组件
│       ├── network/          # 网络模块
│       └── animation/        # 动画模块
├── tests/                    # 测试
│   ├── unit/                 # 单元测试
│   ├── integration/          # 集成测试
│   └── performance/          # 性能测试
├── tools/                    # 工具
│   ├── vscode/              # VSCode插件
│   ├── formatter/           # 代码格式化器
│   └── linter/              # 代码检查器
├── examples/                 # 示例
├── docs/                     # 文档
├── scripts/                  # 构建脚本
└── third_party/             # 第三方依赖
    └── antlr4-cpp-runtime/  # ANTLR运行时（将被移除）
```

## 模块划分原则

1. **单一职责**：每个模块只负责一个功能领域
2. **低耦合**：模块之间通过接口通信
3. **高内聚**：相关功能放在同一模块
4. **可测试**：每个模块都可以独立测试

## 依赖关系

```
core (基础)
  ↑
parser, scanner, error, utils (底层)
  ↑
generator, template, custom, origin, import, namespace, constraint (中层)
  ↑
module, optimizer, config (高层)
```