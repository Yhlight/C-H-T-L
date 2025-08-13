#!/bin/bash

# ANTLR4代码生成脚本

echo "🚀 开始生成ANTLR4代码..."

# 设置ANTLR4工具路径
ANTLR4_JAR="antlr-4.13.1-complete.jar"

# 检查ANTLR4工具是否存在
if [ ! -f "$ANTLR4_JAR" ]; then
    echo "❌ 错误: 未找到ANTLR4工具 $ANTLR4_JAR"
    exit 1
fi

# 创建输出目录
mkdir -p generated

# 生成CHTL语法代码
echo "📝 生成CHTL语法代码..."
java -jar "$ANTLR4_JAR" -Dlanguage=Cpp -visitor -listener -o generated/chtl grammars/chtl/CHTL.g4

# 生成CSS语法代码
echo "🎨 生成CSS语法代码..."
java -jar "$ANTLR4_JAR" -Dlanguage=Cpp -visitor -listener -o generated/css grammars/css/CSS.g4

# 生成JavaScript语法代码
echo "⚡ 生成JavaScript语法代码..."
java -jar "$ANTLR4_JAR" -Dlanguage=Cpp -visitor -listener -o generated/js grammars/js/JavaScript.g4

# 生成CHTL JS语法代码
echo "🔧 生成CHTL JS语法代码..."
java -jar "$ANTLR4_JAR" -Dlanguage=Cpp -visitor -listener -o generated/chtljs grammars/chtljs/CHTLJS.g4

echo "✅ ANTLR4代码生成完成!"
echo ""
echo "📁 生成的文件位置:"
echo "  - CHTL: generated/chtl/"
echo "  - CSS: generated/css/"
echo "  - JavaScript: generated/js/"
echo "  - CHTL JS: generated/chtljs/"
echo ""
echo "🔍 查看生成的文件:"
ls -la generated/