# VSCode + CMake 开发环境配置指南

本文档介绍如何在VSCode中配置CHTL项目的开发环境。

## 🚀 快速开始

### 1. 安装必要的扩展

打开VSCode后，按下 `Ctrl+Shift+X` 打开扩展面板，安装以下扩展：

**必须安装的扩展：**
- **CMake Tools** (ms-vscode.cmake-tools) - CMake集成
- **C/C++** (ms-vscode.cpptools) - C++语言支持
- **CMake** (twxs.cmake) - CMake语法高亮

**推荐安装的扩展：**
- **C/C++ Extension Pack** - C++开发工具包
- **LLDB** (vadimcn.vscode-lldb) - 更好的调试体验
- **Clang-Format** - 代码格式化
- **GitLens** - Git增强
- **Bracket Pair Colorizer 2** - 括号着色

### 2. 打开工作区

```bash
# 在项目根目录
code CHTL.code-workspace
```

或者在VSCode中：
1. 文件 → 打开工作区
2. 选择 `CHTL.code-workspace`

### 3. 配置CMake

首次打开项目时，CMake Tools会自动检测并提示配置：
1. 选择编译器（通常选择系统默认的g++或clang++）
2. 选择构建类型（Debug用于开发，Release用于发布）

或手动配置：
- 按 `Ctrl+Shift+P` 打开命令面板
- 输入 "CMake: Configure"
- 选择编译器和构建类型

### 4. 激活CHTL语法高亮

CHTL语法高亮扩展已包含在项目中：
1. 进入 `.vscode/extensions/chtl-syntax` 目录
2. 在该目录下运行：
   ```bash
   # 创建符号链接到VSCode扩展目录
   ln -s $(pwd) ~/.vscode/extensions/chtl-syntax
   ```
3. 重启VSCode

## 📁 项目结构

工作区包含三个主要文件夹：
- **CHTL Compiler** - 编译器核心代码
- **CHTL IDE** - IDE项目
- **CHTL Modules** - 模块系统

## ⌨️ 快捷键

| 快捷键 | 功能 |
|--------|------|
| `Ctrl+Shift+B` | 构建整个项目 |
| `F5` | 开始调试 |
| `Ctrl+F5` | 运行（不调试）|
| `F6` | 编译当前CHTL文件 |
| `F7` | 生成ANTLR解析器 |
| `F8` | 打包模块 |
| `Ctrl+Shift+T` | 运行测试 |
| `Ctrl+Shift+F` | 格式化C++代码 |
| `Ctrl+Alt+I` | 构建IDE |
| `Ctrl+Alt+C` | 清理构建 |

## 🛠️ 构建任务

VSCode任务（Tasks）可通过以下方式访问：
- 终端 → 运行任务
- 或按 `Ctrl+Shift+P` 输入 "Tasks: Run Task"

可用任务：
- **CMake: Configure** - 配置CMake项目
- **CMake: Build All** - 构建所有目标（默认构建任务）
- **Generate Parsers** - 生成ANTLR4解析器
- **Build CHTL Compiler** - 仅构建编译器
- **Build IDE** - 构建IDE项目
- **Pack Modules** - 打包CHTL模块
- **Clean Build** - 清理构建目录
- **Run Tests** - 运行所有测试
- **Compile Current CHTL File** - 编译当前打开的.chtl文件
- **Format C++ Code** - 格式化所有C++代码

## 🐛 调试配置

预配置的调试目标：
1. **Debug CHTL Compiler** - 调试编译器
2. **Debug CHTL IDE** - 调试IDE（需要Qt）
3. **Debug Current Test** - 调试当前测试文件
4. **LLDB: Debug CHTL Compiler** - 使用LLDB调试
5. **Attach to Process** - 附加到运行中的进程
6. **Run CHTL File (No Debug)** - 运行CHTL文件（不调试）

## 📝 编写CHTL代码

1. 创建新的`.chtl`文件
2. 使用代码片段快速插入常用结构：
   - 输入 `html` → 创建HTML结构
   - 输入 `template-style` → 创建样式模板
   - 输入 `chtholly` → 导入珂朵莉模块
   - 等等...

3. 按 `F6` 编译当前文件

## 🔧 IntelliSense配置

C++ IntelliSense已预配置，包括：
- 所有项目头文件路径
- ANTLR4运行时路径
- Qt5路径（用于IDE）
- 编译命令数据库支持

如需调整，编辑 `.vscode/c_cpp_properties.json`

## 📦 模块开发

### 创建新模块
1. 在 `module/` 目录创建模块文件夹
2. 遵循CMOD标准结构：
   ```
   MyModule/
   ├── src/
   │   └── MyModule.chtl
   └── info/
       └── MyModule.chtl
   ```
3. 按 `F8` 打包模块

### 使用模块
```chtl
[Import] @Chtl from MyModule

// 使用模块内容
```

## 🎯 最佳实践

### 1. 使用工作区
始终通过工作区文件打开项目，这样可以：
- 同时管理编译器、IDE和模块
- 使用预配置的设置
- 快速切换不同部分

### 2. 增量构建
- 修改代码后，使用 `Ctrl+Shift+B` 增量构建
- 只有在清理或首次构建时才需要完整构建

### 3. 调试技巧
- 使用断点调试复杂逻辑
- 查看"调试控制台"获取程序输出
- 使用"监视"窗口跟踪变量

### 4. 代码格式化
- 保存时自动格式化（已配置）
- 手动格式化：`Ctrl+Shift+F`
- 遵循Google C++代码规范

## 🔍 故障排除

### CMake配置失败
```bash
# 清理并重新配置
rm -rf build
# 重新打开VSCode，CMake会自动配置
```

### IntelliSense不工作
1. 确保CMake配置成功
2. 检查 `compile_commands.json` 是否生成
3. 重启VSCode

### 调试器无法启动
- 确保已安装gdb：`sudo apt install gdb`
- 检查可执行文件是否存在
- 查看调试控制台的错误信息

### CHTL语法高亮不显示
1. 确保已创建符号链接
2. 检查扩展是否启用
3. 重新加载窗口：`Ctrl+Shift+P` → "Reload Window"

## 📚 进阶配置

### 自定义构建变体
编辑 `.vscode/cmake-variants.yaml`：
```yaml
buildType:
  default: debug
  choices:
    debug:
      short: Debug
      long: Debug build
      buildType: Debug
    release:
      short: Release
      long: Release build
      buildType: Release
    relwithdebinfo:
      short: RelWithDebInfo
      long: Release with debug info
      buildType: RelWithDebInfo
```

### 添加自定义任务
编辑 `.vscode/tasks.json` 添加新任务

### 环境变量
编辑 `.vscode/settings.json` 的 `terminal.integrated.env.linux`

## 🎉 开始开发

现在你已经准备好开始CHTL开发了！

1. 打开一个`.chtl`文件试试语法高亮
2. 按 `F6` 编译它
3. 使用 `F5` 调试编译器
4. 享受开发过程！

有问题？查看项目文档或提交Issue。

---

*Happy Coding with CHTL! 🚀*