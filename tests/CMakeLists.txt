# 测试配置

# 添加测试可执行文件
add_executable(test_scanner test_scanner.cpp)

# 链接必要的库
target_link_libraries(test_scanner)

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

# 添加测试
add_test(NAME ScannerTest COMMAND test_scanner)

# 设置测试工作目录
set_tests_properties(ScannerTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)