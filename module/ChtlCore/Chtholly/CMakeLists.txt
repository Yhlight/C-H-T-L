cmake_minimum_required(VERSION 3.16)
project(Chtholly VERSION 1.0.0 LANGUAGES CXX)

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 源文件
set(CHTHOLLY_SOURCES
    src/chtholly.cpp
)

# 创建共享库
add_library(chtholly SHARED ${CHTHOLLY_SOURCES})

# 包含目录
target_include_directories(chtholly PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 导出符号
set_target_properties(chtholly PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/chtholly.h
)

# 安装规则
install(TARGETS chtholly
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

# 生成元数据
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/info/module.info"
    "${CMAKE_CURRENT_BINARY_DIR}/module.info"
    COPYONLY
)