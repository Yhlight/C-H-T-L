# CHTL 项目结构重组计划

## 当前问题
- 155+ 个测试文件散落在根目录
- 源代码和测试混在一起
- 没有清晰的模块划分
- 构建产物和源代码混杂

## 建议的新结构

```
/workspace/
├── src/                      # 核心源代码
│   ├── core/                 # 核心编译器组件
│   │   ├── lexer/           # 词法分析
│   │   ├── parser/          # 语法分析
│   │   ├── scanner/         # 代码扫描器
│   │   └── ast/             # AST 节点定义
│   ├── state/               # 状态机实现
│   │   ├── ChtlState.cpp
│   │   ├── CssState.cpp
│   │   ├── JsState.cpp
│   │   └── ChtlJsState.cpp
│   ├── context/             # 上下文管理
│   ├── generator/           # 代码生成器
│   │   ├── HtmlGenerator.cpp
│   │   ├── ReactGenerator.cpp
│   │   └── VueGenerator.cpp
│   ├── error/               # 错误处理
│   ├── utils/               # 工具类
│   └── main.cpp            # 主程序入口
│
├── include/                 # 头文件
│   └── chtl/               # 公共API
│       ├── core/
│       ├── state/
│       └── ...
│
├── tests/                   # 所有测试
│   ├── unit/               # 单元测试
│   ├── integration/        # 集成测试
│   ├── fixtures/           # 测试用例文件
│   │   ├── basic/         # 基础语法测试
│   │   ├── template/      # 模板系统测试
│   │   ├── style/         # 样式系统测试
│   │   ├── script/        # 脚本功能测试
│   │   └── error/         # 错误处理测试
│   └── performance/        # 性能测试
│
├── modules/                 # CHTL 标准库模块
│   ├── std/                # 标准库
│   ├── ui/                 # UI 组件库
│   └── utils/              # 工具模块
│
├── examples/               # 示例项目
│   ├── hello-world/
│   ├── todo-app/
│   └── component-library/
│
├── tools/                  # 开发工具
│   ├── vscode-extension/   # VS Code 扩展
│   ├── cli/                # 命令行工具
│   └── scripts/            # 构建脚本
│
├── docs/                   # 文档
│   ├── design/            # 设计文档
│   ├── api/               # API 文档
│   └── tutorials/         # 教程
│
├── build/                  # 构建输出（git忽略）
├── dist/                   # 发布文件（git忽略）
└── temp/                   # 临时文件（git忽略）
```

## 重组步骤

### 1. 创建新的目录结构
```bash
mkdir -p tests/fixtures/{basic,template,style,script,error}
mkdir -p examples/{hello-world,todo-app,component-library}
mkdir -p tools/{cli,scripts}
mkdir -p docs/{design,api,tutorials}
```

### 2. 移动测试文件
- `test-basic-*.chtl` → `tests/fixtures/basic/`
- `test-template-*.chtl` → `tests/fixtures/template/`
- `test-style-*.chtl` → `tests/fixtures/style/`
- `test-script-*.chtl` → `tests/fixtures/script/`
- `test-error-*.chtl` → `tests/fixtures/error/`

### 3. 整理源代码
- 将 `src/` 下的目录名改为小写
- 移动 VS Code 扩展到 `tools/`
- 整理构建脚本到 `tools/scripts/`

### 4. 更新构建配置
- 更新 CMakeLists.txt 路径
- 更新 .gitignore
- 创建新的构建脚本