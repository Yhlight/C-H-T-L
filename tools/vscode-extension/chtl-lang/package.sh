#!/bin/bash

# VS Code 扩展打包脚本

echo "开始打包 CHTL VS Code 扩展..."

# 检查是否安装了 vsce
if ! command -v vsce &> /dev/null; then
    echo "vsce 未安装，正在安装..."
    npm install -g vsce
fi

# 清理旧的构建文件
echo "清理旧的构建文件..."
rm -rf out/
rm -f *.vsix

# 安装依赖
echo "安装依赖..."
npm install

# 编译 TypeScript
echo "编译 TypeScript..."
npm run compile

# 检查编译是否成功
if [ $? -ne 0 ]; then
    echo "编译失败，请检查错误信息"
    exit 1
fi

# 检查必要的文件
echo "检查必要的文件..."
required_files=(
    "package.json"
    "README.md"
    "syntaxes/chtl.tmLanguage.json"
    "snippets/chtl.snippets.json"
    "language-configuration.json"
    "out/extension.js"
    "out/server.js"
    "out/compiler.js"
    "out/languageClient.js"
    "compilers/linux-x64/chtl"
)

for file in "${required_files[@]}"; do
    if [ ! -f "$file" ]; then
        echo "错误：缺少必要文件 $file"
        exit 1
    fi
done

# 创建 VSIX 包
echo "创建 VSIX 包..."
vsce package --no-dependencies

# 检查打包是否成功
if [ $? -eq 0 ]; then
    echo "打包成功！"
    ls -la *.vsix
    echo ""
    echo "你可以通过以下方式安装扩展："
    echo "1. 在 VS Code 中：扩展 -> 从 VSIX 安装..."
    echo "2. 命令行：code --install-extension chtl-lang-*.vsix"
else
    echo "打包失败，请检查错误信息"
    exit 1
fi