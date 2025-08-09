cmake_minimum_required(VERSION 3.16)
project(CHTL_Compiler VERSION 1.0.0 LANGUAGES CXX)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 收集库源文件（不包含main文件）
file(GLOB_RECURSE LIB_SOURCES 
    "${CMAKE_SOURCE_DIR}/src/Common/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Context/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Lexer/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/State/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Node/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Parser/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Generator/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Css/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Js/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Chtl_Js/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Scanner/*.cpp"
)

# 创建主可执行文件
add_executable(chtl ${LIB_SOURCES} src/main.cpp)

# 创建测试程序
add_executable(test_lexer ${LIB_SOURCES} src/test_lexer.cpp)
add_executable(test_node ${LIB_SOURCES} src/test_node.cpp)
add_executable(test_chtl_nodes ${LIB_SOURCES} src/test_chtl_nodes.cpp)
add_executable(test_bridge_scanner ${LIB_SOURCES} src/test_bridge_scanner.cpp)

# 启用测试
enable_testing()

# 添加测试子目录
add_subdirectory(tests)