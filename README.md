# CHTL编译器

基于ANTLR4实现的CHTL（超文本语言）编译器系统，支持4个独立的编译器：

- **CHTL编译器**: 编译CHTL语法为HTML、CSS和JavaScript
- **CSS编译器**: 编译CSS原生语法
- **JavaScript编译器**: 编译JavaScript原生语法  
- **CHTL JS编译器**: 编译CHTL扩展的JavaScript语法

## 特性

- 🚀 4个编译器独立工作，互不干扰
- 🔍 智能代码扫描器，精准切割不同类型的代码块
- 📝 完整的CHTL语法支持（模板、自定义、命名空间等）
- 🎨 CSS语法验证和优化
- ⚡ JavaScript ES6+语法支持
- 🔧 CHTL JS增强语法（选择器、监听器、动画等）
- 📊 详细的编译统计信息
- 🛠️ 可配置的编译选项

## 系统要求

- C++17 或更高版本
- CMake 3.16 或更高版本
- ANTLR4 运行时库

## 安装

### 1. 克隆仓库

```bash
git clone https://github.com/your-username/chtl-compiler.git
cd chtl-compiler
```

### 2. 安装依赖

#### Ubuntu/Debian:
```bash
sudo apt-get install antlr4-runtime
```

#### macOS:
```bash
brew install antlr4-runtime
```

#### Windows:
```bash
# 使用vcpkg
vcpkg install antlr4-runtime
```

### 3. 编译

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

### 4. 安装

```bash
sudo make install
```

## 使用方法

### 基本用法

```bash
# 编译CHTL文件
chtl-compiler input.chtl

# 指定输出目录
chtl-compiler -o ./dist input.chtl

# 指定输出文件名
chtl-compiler -h index.html -c style.css -j script.js input.chtl
```

### 命令行选项

| 选项 | 长选项 | 描述 |
|------|--------|------|
| `-o` | `--output` | 指定输出目录 |
| `-h` | `--html` | 指定HTML输出文件名 |
| `-c` | `--css` | 指定CSS输出文件名 |
| `-j` | `--js` | 指定JavaScript输出文件名 |
| | `--minify` | 压缩输出文件 |
| | `--optimize` | 优化输出（默认启用） |
| | `--debug` | 启用调试模式 |
| | `--help` | 显示帮助信息 |
| | `--version` | 显示版本信息 |

## CHTL语法示例

### 基本元素

```chtl
html
{
    head
    {
        title
        {
            text
            {
                我的页面
            }
        }
    }
    
    body
    {
        div
        {
            style
            {
                width: 100px;
                height: 100px;
                background-color: red;
            }
            
            text
            {
                红色方块
            }
        }
    }
}
```

### 模板

```chtl
[Template] @Style Button
{
    padding: 10px 20px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
}

[Template] @Element Card
{
    div
    {
        style
        {
            @Style Button;
            background-color: white;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        
        text
        {
            卡片内容
        }
    }
}
```

### 自定义元素

```chtl
[Custom] @Element Navigation
{
    nav
    {
        ul
        {
            li
            {
                a
                {
                    text
                    {
                        首页
                    }
                }
            }
        }
    }
}

body
{
    @Element Navigation
    {
        style
        {
            background-color: #333;
            color: white;
        }
    }
}
```

### CHTL JS增强语法

```chtl
script
{
    // CHTL选择器
    {{button}}->addEventListener('click', () => {
        console.log('按钮被点击');
    });
    
    // 事件委托
    {{nav}}->delegate({
        target: {{a}},
        click: (e) => {
            e.preventDefault();
            console.log('链接被点击');
        }
    });
    
    // 动画
    animate({
        duration: 1000,
        easing: ease-in-out,
        begin: {
            opacity: 0,
            transform: 'translateY(20px)'
        },
        end: {
            opacity: 1,
            transform: 'translateY(0)'
        }
    });
}
```

## 项目结构

```
chtl-compiler/
├── src/                    # 源代码
│   ├── scanner/           # 代码扫描器
│   ├── compiler/          # 编译器基类和主编译器
│   ├── chtl/              # CHTL编译器
│   ├── css/               # CSS编译器
│   ├── js/                # JavaScript编译器
│   ├── chtljs/            # CHTL JS编译器
│   └── utils/             # 工具函数
├── grammars/              # ANTLR4语法文件
│   ├── chtl/              # CHTL语法
│   ├── css/               # CSS语法
│   ├── js/                # JavaScript语法
│   └── chtljs/            # CHTL JS语法
├── examples/              # 示例文件
├── tests/                 # 测试文件
├── docs/                  # 文档
└── CMakeLists.txt         # CMake构建文件
```

## 开发

### 添加新的语法特性

1. 修改相应的ANTLR4语法文件（`.g4`）
2. 更新对应的编译器实现
3. 添加测试用例
4. 更新文档

### 运行测试

```bash
cd build
make test
```

### 代码风格

- 使用C++17标准
- 遵循Google C++代码风格
- 所有公共API必须有文档注释
- 单元测试覆盖率不低于80%

## 贡献

欢迎贡献代码！请遵循以下步骤：

1. Fork 项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开 Pull Request

## 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 联系方式

- 项目主页: https://github.com/your-username/chtl-compiler
- 问题反馈: https://github.com/your-username/chtl-compiler/issues
- 邮箱: your-email@example.com

## 致谢

- [ANTLR4](https://www.antlr.org/) - 强大的解析器生成器
- [CHTL语法文档](CHTL语法文档.md) - 详细的语法规范
- 所有贡献者和用户的支持