# CHTL IDE

一个功能完整的CHTL（C++ Hypertext Language）集成开发环境，支持所有CHTL语法特性。

![CHTL IDE](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Qt](https://img.shields.io/badge/Qt-5.15+-orange)

## 🌟 主要特性

### 完整的CHTL语法支持
- ✅ 注释系统（单行、多行、生成性注释）
- ✅ 文本节点和字面量
- ✅ CE对等式（: 和 = 等价）
- ✅ 元素节点和属性
- ✅ 局部样式块（内联样式、自动类名/ID、上下文推导）
- ✅ 模板系统（样式组、元素、变量组模板）
- ✅ 自定义系统（无值样式组、特例化操作）
- ✅ 原始嵌入（HTML、CSS、JavaScript）
- ✅ 导入系统（支持所有文件类型和模块）
- ✅ 命名空间（嵌套、合并、from语法）
- ✅ 约束系统（精确、类型、全局约束）
- ✅ CHTL JS扩展（增强选择器、事件处理、动画）
- ✅ 配置组
- ✅ CMOD/CJMOD模块系统

### IDE功能
- 🎨 **语法高亮** - 智能识别所有CHTL语法元素
- 💡 **代码补全** - 上下文感知的智能提示
- 🔍 **实时错误检测** - 编辑时即时发现语法错误
- 👁️ **实时预览** - 编辑时自动更新预览
- 📱 **设备模拟** - 支持多种设备预览
- 📦 **模块管理** - 内置官方模块，支持自定义模块
- 🏗️ **项目管理** - 完整的项目创建、构建、部署流程
- 🔧 **开发者工具** - 集成调试和分析工具

### 内置官方模块
- **Chtholly模块** - 基于《末日时在做什么？》珂朵莉主题的UI组件库
  - 优雅的配色方案（天蓝色、深红色主题）
  - 丰富的UI组件（按钮、卡片、标题、列表等）
  - 动画效果（妖精之翼浮动效果）
  - 响应式设计支持

## 🚀 快速开始

### 系统要求
- Qt 5.15 或更高版本
- C++17 兼容编译器
- CMake 3.16 或更高版本
- ANTLR4（可选，用于完整解析器支持）

### 构建步骤

1. **克隆仓库**
```bash
git clone https://github.com/chtl/chtl-ide.git
cd chtl-ide
```

2. **构建CHTL编译器**（如果还没有）
```bash
cd ..
mkdir build && cd build
cmake ..
make
```

3. **构建IDE**
```bash
cd ../ide
mkdir build && cd build
cmake ..
make
```

4. **运行IDE**
```bash
./bin/chtl-ide
```

## 📖 使用指南

### 创建第一个CHTL项目

1. 启动IDE后，会自动创建一个示例文件
2. 示例展示了如何使用Chtholly模块创建美观的页面
3. 点击"构建"按钮或按F6查看实时预览

### 基本工作流程

1. **编写代码** - 在编辑器中编写CHTL代码
2. **实时预览** - 代码会自动编译并在预览面板显示
3. **错误修复** - 根据错误提示修复语法问题
4. **保存项目** - 使用Ctrl+S保存文件
5. **导出结果** - 构建项目生成最终的HTML/CSS/JS文件

### 使用模块

```chtl
// 导入Chtholly模块
[Import] @Chtl from Chtholly

// 使用模块中的组件
div {
    style {
        @Style Chtholly.FairyCard;
    }
    
    h1 {
        style { @Style Chtholly.ChthollysH1; }
        text { "欢迎使用CHTL" }
    }
}
```

## 🛠️ 高级功能

### 自定义模块开发

1. 在`module`文件夹创建模块目录结构：
```
MyModule/
├── src/
│   └── MyModule.chtl
└── info/
    └── MyModule.chtl
```

2. 编写模块代码和信息文件
3. IDE会自动检测并加载模块

### CJMOD扩展开发

支持使用C++扩展CHTL JS语法：

1. 创建CJMOD目录结构
2. 实现扩展接口
3. 编译为动态库
4. 在CHTL中使用扩展功能

### 项目模板

IDE提供多种项目模板：
- 单页应用
- 多页网站
- UI组件库
- CHTL模块
- CJMOD扩展

## 🎨 界面预览

IDE采用现代化的界面设计：
- **左侧** - 项目浏览器和模块浏览器
- **中央** - 多标签代码编辑器
- **右侧** - 实时预览面板
- **底部** - 输出和错误信息

## 🤝 贡献

欢迎贡献代码、报告问题或提出建议！

### 开发指南

1. Fork项目
2. 创建功能分支
3. 提交更改
4. 发起Pull Request

### 代码规范

- 使用C++17标准
- 遵循Qt编码规范
- 添加适当的注释和文档

## 📄 许可证

本项目采用MIT许可证。详见[LICENSE](LICENSE)文件。

## 🙏 致谢

- ANTLR4项目提供的强大解析器生成器
- Qt框架提供的跨平台GUI支持
- 《末日时在做什么？》为Chtholly模块提供的灵感

特别致敬珂朵莉·诺塔·瑟尼欧里斯 —— 世界上最幸福的女孩。

## 📞 联系我们

- 项目主页：https://github.com/chtl/chtl-ide
- 问题反馈：https://github.com/chtl/chtl-ide/issues
- 邮件：support@chtl.dev

---

*"即使是这样的我，也想要成为某个人的幸福。" —— 珂朵莉*