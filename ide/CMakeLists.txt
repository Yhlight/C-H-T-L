cmake_minimum_required(VERSION 3.16)
project(CHTL_IDE VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets WebEngineWidgets)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加CHTL编译器路径
set(CHTL_COMPILER_DIR "${CMAKE_SOURCE_DIR}/../")
set(CHTL_BUILD_DIR "${CMAKE_SOURCE_DIR}/../build")

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CHTL_COMPILER_DIR}/src
    ${CHTL_COMPILER_DIR}/generated
)

# 收集源文件
file(GLOB_RECURSE IDE_SOURCES
    src/*.cpp
    src/*.h
)

# 资源文件
set(IDE_RESOURCES
    resources/ide.qrc
)

# 创建可执行文件
add_executable(chtl-ide
    ${IDE_SOURCES}
    ${IDE_RESOURCES}
)

# 链接库
target_link_libraries(chtl-ide PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::WebEngineWidgets
    ${CHTL_BUILD_DIR}/lib/libchtl_core.a
    ${CHTL_BUILD_DIR}/lib/libchtljs_core.a
    pthread
    dl
    stdc++fs
)

# 复制官方模块
add_custom_command(TARGET chtl-ide POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/modules
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CHTL_BUILD_DIR}/module
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/modules
    COMMENT "Copying official modules..."
)

# 复制资源文件
add_custom_command(TARGET chtl-ide POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/resources/templates
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/templates
    COMMENT "Copying templates..."
)

# 安装规则
install(TARGETS chtl-ide
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/modules/
    DESTINATION share/chtl-ide/modules
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/templates/
    DESTINATION share/chtl-ide/templates
)