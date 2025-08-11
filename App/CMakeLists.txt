# App 可执行文件
add_executable(chtl main.cpp)

# 链接核心库
target_link_libraries(chtl PRIVATE chtl_core)

# 设置输出目录
set_target_properties(chtl PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 安装规则
install(TARGETS chtl
    RUNTIME DESTINATION bin
)