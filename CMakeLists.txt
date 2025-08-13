cmake_minimum_required(VERSION 3.16)
project(CHTLCompiler VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 查找ANTLR4
find_package(antlr4-runtime REQUIRED)

# 设置源文件
set(SOURCES
    src/scanner/CodeScanner.cpp
    src/compiler/Compiler.cpp
    src/compiler/MainCompiler.cpp
    src/chtl/CHTLCompiler.cpp
    src/css/CSSCompiler.cpp
    src/js/JavaScriptCompiler.cpp
    src/chtljs/CHTLJSCompiler.cpp
    src/main.cpp
)

# 设置头文件
set(HEADERS
    src/scanner/CodeScanner.h
    src/compiler/Compiler.h
    src/compiler/MainCompiler.h
    src/chtl/CHTLCompiler.h
    src/css/CSSCompiler.h
    src/js/JavaScriptCompiler.h
    src/chtljs/CHTLJSCompiler.h
)

# 创建可执行文件
add_executable(chtl-compiler ${SOURCES} ${HEADERS})

# 添加ANTLR4生成的源文件
# target_sources(chtl-compiler PRIVATE
#     generated/chtl/grammars/chtl/grammars/chtl/CHTLLexer.cpp
#     generated/chtl/grammars/chtl/grammars/chtl/CHTLParser.cpp
#     generated/chtl/grammars/chtl/grammars/chtl/CHTLListener.cpp
#     generated/chtl/grammars/chtl/grammars/chtl/CHTLBaseListener.cpp
#     # generated/css/grammars/css/grammars/css/CSSLexer.cpp
#     # generated/css/grammars/css/grammars/css/CSSParser.cpp
#     # generated/css/grammars/css/grammars/css/CSSListener.cpp
#     # generated/css/grammars/css/grammars/css/CSSBaseListener.cpp
#     generated/js/grammars/js/grammars/js/JavaScriptLexer.cpp
#     generated/js/grammars/js/grammars/js/JavaScriptParser.cpp
#     generated/js/grammars/js/grammars/js/JavaScriptListener.cpp
#     generated/js/grammars/js/grammars/js/JavaScriptBaseListener.cpp
#     generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSLexer.cpp
#     generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSParser.cpp
#     generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSListener.cpp
#     generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSBaseListener.cpp
# )

# 链接ANTLR4库
target_link_libraries(chtl-compiler antlr4-runtime)

# 设置包含目录
target_include_directories(chtl-compiler PRIVATE
    src
    src/scanner
    src/compiler
    src/chtl
    src/css
    src/js
    src/chtljs
    src/utils
    generated
    generated/chtl/grammars/chtl/grammars/chtl
    generated/css/grammars/css/grammars/css
    generated/js/grammars/js/grammars/js
    generated/chtljs/grammars/chtljs/grammars/chtljs
    /usr/include/antlr4-runtime
)

# 安装目标
install(TARGETS chtl-compiler
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# 安装头文件
install(FILES ${HEADERS}
    DESTINATION include/chtl-compiler
)

# 安装生成的ANTLR4头文件
install(FILES generated/chtl/grammars/chtl/grammars/chtl/CHTLLexer.h
    generated/chtl/grammars/chtl/grammars/chtl/CHTLParser.h
    generated/chtl/grammars/chtl/grammars/chtl/CHTLListener.h
    generated/chtl/grammars/chtl/grammars/chtl/CHTLBaseListener.h
    generated/css/grammars/css/grammars/css/CSSLexer.h
    generated/css/grammars/css/grammars/css/CSSParser.h
    generated/css/grammars/css/grammars/css/CSSListener.h
    generated/css/grammars/css/grammars/css/CSSBaseListener.h
    generated/js/grammars/js/grammars/js/JavaScriptLexer.h
    generated/js/grammars/js/grammars/js/JavaScriptParser.h
    generated/js/grammars/js/grammars/js/JavaScriptListener.h
    generated/js/grammars/js/grammars/js/JavaScriptBaseListener.h
    generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSLexer.h
    generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSParser.h
    generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSListener.h
    generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSBaseListener.h
    DESTINATION include/chtl-compiler/antlr
)

# 安装语法文件
install(DIRECTORY grammars/
    DESTINATION share/chtl-compiler/grammars
    FILES_MATCHING PATTERN "*.g4"
)

# 设置测试
enable_testing()
add_subdirectory(tests)

# 设置文档
add_subdirectory(docs)

# 设置示例
add_subdirectory(examples)