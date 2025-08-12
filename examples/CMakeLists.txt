# 示例配置

# 这里可以添加示例相关的构建配置
# 目前示例文件不需要编译，只需要安装

# 安装示例文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION share/chtl-compiler/examples
    FILES_MATCHING PATTERN "*.chtl"
)