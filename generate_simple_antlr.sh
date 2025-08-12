#!/bin/bash

# ANTLR4简化语法代码生成脚本

echo "🚀 开始生成简化ANTLR4代码..."

# 设置ANTLR4工具路径
ANTLR4_JAR="antlr-4.13.1-complete.jar"

# 检查ANTLR4工具是否存在
if [ ! -f "$ANTLR4_JAR" ]; then
    echo "❌ 错误: 未找到ANTLR4工具 $ANTLR4_JAR"
    exit 1
fi

# 创建输出目录
mkdir -p generated_simple

# 生成简化CHTL语法代码
echo "📝 生成简化CHTL语法代码..."
java -jar "$ANTLR4_JAR" -Dlanguage=Cpp -visitor -listener -o generated_simple/chtl grammars/chtl/CHTL_simple.g4

# 生成简化CSS语法代码
echo "🎨 生成简化CSS语法代码..."
java -jar "$ANTLR4_JAR" -Dlanguage=Cpp -visitor -listener -o generated_simple/css grammars/css/CSS_simple.g4

# 生成简化JavaScript语法代码
echo "⚡ 生成简化JavaScript语法代码..."
java -jar "$ANTLR4_JAR" -Dlanguage=Cpp -visitor -listener -o generated_simple/js grammars/js/JavaScript_simple.g4

# 生成简化CHTL JS语法代码
echo "🔧 生成简化CHTL JS语法代码..."
java -jar "$ANTLR4_JAR" -Dlanguage=Cpp -visitor -listener -o generated_simple/chtljs grammars/chtljs/CHTLJS_simple.g4

echo "✅ 简化ANTLR4代码生成完成!"
echo ""
echo "📁 生成的文件位置:"
echo "  - CHTL: generated_simple/chtl/"
echo "  - CSS: generated_simple/css/"
echo "  - JavaScript: generated_simple/js/"
echo "  - CHTL JS: generated_simple/chtljs/"
echo ""
echo "🔍 查看生成的文件:"
ls -la generated_simple/