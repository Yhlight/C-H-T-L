# 文档配置

# 安装文档文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION share/chtl-compiler/docs
    FILES_MATCHING PATTERN "*.md"
)