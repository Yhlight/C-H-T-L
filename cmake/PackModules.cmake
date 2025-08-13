# PackModules.cmake - 独立的模块打包脚本
# 可以通过 cmake -P 调用

# 包含模块功能
include("${CMAKE_CURRENT_LIST_DIR}/CHTLModules.cmake")

# 执行模块处理
process_chtl_modules(
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/module"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/module"
)