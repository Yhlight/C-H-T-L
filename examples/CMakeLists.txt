# 示例配置

# 添加ANTLR4示例可执行文件
add_executable(antlr_example antlr_example.cpp)

# 链接必要的库
target_link_libraries(antlr_example antlr4-runtime)

# 设置包含目录
target_include_directories(antlr_example PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/generated_simple
)

# 设置编译选项
target_compile_features(antlr_example PRIVATE cxx_std_17)

# 安装示例文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION share/chtl-compiler/examples
    FILES_MATCHING PATTERN "*.chtl" PATTERN "*.cpp"
)

# 安装生成的头文件
install(DIRECTORY ${CMAKE_SOURCE_DIR}/generated_simple/
    DESTINATION share/chtl-compiler/generated
    FILES_MATCHING PATTERN "*.h" PATTERN "*.cpp"
)