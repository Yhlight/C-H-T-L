# 测试配置

# 添加测试可执行文件
add_executable(test_scanner test_scanner.cpp)
add_executable(test_chtl_compiler test_chtl_compiler.cpp)

# 链接必要的库 - 链接到包含CHTL编译器实现的源文件
target_sources(test_scanner PRIVATE
    ../src/scanner/CodeScanner.cpp
    ../src/compiler/Compiler.cpp
    ../src/chtl/CHTLCompiler.cpp
    ../src/css/CSSCompiler.cpp
    ../src/js/JavaScriptCompiler.cpp
    ../src/chtljs/CHTLJSCompiler.cpp
)

target_sources(test_chtl_compiler PRIVATE
    ../src/scanner/CodeScanner.cpp
    ../src/compiler/Compiler.cpp
    ../src/chtl/CHTLCompiler.cpp
    ../src/css/CSSCompiler.cpp
    ../src/js/JavaScriptCompiler.cpp
    ../src/chtljs/CHTLJSCompiler.cpp
)

# 设置包含目录
target_include_directories(test_scanner PRIVATE
    ../src
    ../src/scanner
    ../src/compiler
    ../src/chtl
    ../src/css
    ../src/js
    ../src/chtljs
    ../src/utils
)

target_include_directories(test_chtl_compiler PRIVATE
    ../src
    ../src/scanner
    ../src/compiler
    ../src/chtl
    ../src/css
    ../src/js
    ../src/chtljs
    ../src/utils
)

# 添加测试
add_test(NAME ScannerTest COMMAND test_scanner)
add_test(NAME CHTLCompilerTest COMMAND test_chtl_compiler)

# 设置测试工作目录
set_tests_properties(ScannerTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set_tests_properties(CHTLCompilerTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)