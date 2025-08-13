#!/bin/bash

# ANTLR4 jar文件路径
ANTLR_JAR="/tmp/antlr-4.13.1-complete.jar"

# 检查jar文件是否存在
if [ ! -f "$ANTLR_JAR" ]; then
    echo "错误: ANTLR4 jar文件未找到: $ANTLR_JAR"
    echo "请先下载ANTLR4: wget https://www.antlr.org/download/antlr-4.13.1-complete.jar -O $ANTLR_JAR"
    exit 1
fi

# 创建输出目录
echo "创建输出目录..."
mkdir -p output/java
mkdir -p output/cpp

# 生成Java目标代码
echo "========================================="
echo "生成Java目标代码..."
echo "========================================="

# 先生成基础语法文件
echo "生成JavaScript.g4..."
java -jar "$ANTLR_JAR" -o output/java/javascript -package javascript grammars/JavaScript.g4

echo "生成CSS.g4..."
java -jar "$ANTLR_JAR" -o output/java/css -package css grammars/CSS.g4

echo "生成CHTL.g4..."
java -jar "$ANTLR_JAR" -o output/java/chtl -package chtl grammars/CHTL.g4

echo "生成CHTLJavaScript.g4..."
java -jar "$ANTLR_JAR" -o output/java/chtljs -package chtljs grammars/CHTLJavaScript.g4

echo "生成Scanner.g4..."
java -jar "$ANTLR_JAR" -o output/java/scanner -package scanner grammars/Scanner.g4

echo "生成CHConfig.g4..."
java -jar "$ANTLR_JAR" -o output/java/config -package config grammars/CHConfig.g4

# 生成C++目标代码
echo ""
echo "========================================="
echo "生成C++目标代码..."
echo "========================================="

# 复制JavaScript.g4到输出目录（有些语法文件需要引用它）
cp grammars/JavaScript.g4 output/cpp/

echo "生成JavaScript.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/javascript grammars/JavaScript.g4

echo "生成CSS.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/css grammars/CSS.g4

echo "生成CHTL.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/chtl grammars/CHTL.g4

echo "生成CHTLJavaScript.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/chtljs grammars/CHTLJavaScript.g4

echo "生成Scanner.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/scanner grammars/Scanner.g4

echo "生成CHConfig.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/config grammars/CHConfig.g4

# 清理临时文件
rm -f output/cpp/JavaScript.g4

echo ""
echo "========================================="
echo "生成完成!"
echo "Java输出: output/java/"
echo "C++输出: output/cpp/"
echo "========================================="