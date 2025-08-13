#!/bin/bash

# ANTLR4 jar文件路径
ANTLR_JAR="/tmp/antlr-4.13.1-complete.jar"

# 检查jar文件是否存在
if [ ! -f "$ANTLR_JAR" ]; then
    echo "错误: ANTLR4 jar文件未找到: $ANTLR_JAR"
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
java -jar "$ANTLR_JAR" -o output/java/javascript -package javascript JavaScript.g4

echo "生成CSS.g4..."
java -jar "$ANTLR_JAR" -o output/java/css -package css CSS.g4

echo "生成CHTL.g4..."
java -jar "$ANTLR_JAR" -o output/java/chtl -package chtl CHTL.g4

# 生成依赖JavaScript的CHTLJavaScript
echo "生成CHTLJavaScript.g4..."
# 需要先复制JavaScript.g4到输出目录，因为CHTLJavaScript导入了它
cp JavaScript.g4 output/java/
java -jar "$ANTLR_JAR" -o output/java/chtljs -package chtljs -lib output/java CHTLJavaScript.g4

echo "生成Scanner.g4..."
java -jar "$ANTLR_JAR" -o output/java/scanner -package scanner Scanner.g4

# 生成C++目标代码
echo "========================================="
echo "生成C++目标代码..."
echo "========================================="

echo "生成JavaScript.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/javascript JavaScript.g4

echo "生成CSS.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/css CSS.g4

echo "生成CHTL.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/chtl CHTL.g4

# 生成依赖JavaScript的CHTLJavaScript (C++)
echo "生成CHTLJavaScript.g4 (C++)..."
cp JavaScript.g4 output/cpp/
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/chtljs -lib output/cpp CHTLJavaScript.g4

echo "生成Scanner.g4 (C++)..."
java -jar "$ANTLR_JAR" -Dlanguage=Cpp -o output/cpp/scanner Scanner.g4

echo "========================================="
echo "生成完成！"
echo "Java输出目录: output/java/"
echo "C++输出目录: output/cpp/"
echo "========================================="

# 显示生成的文件
echo ""
echo "生成的Java文件:"
find output/java -name "*.java" | sort

echo ""
echo "生成的C++文件:"
find output/cpp -name "*.cpp" -o -name "*.h" | sort