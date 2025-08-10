cmake_minimum_required(VERSION 3.15)
project(CHTL VERSION 1.0.0 LANGUAGES CXX)

# C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

# 包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 收集源文件
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# 收集头文件
file(GLOB_RECURSE HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

# 创建可执行文件
add_executable(chtl ${SOURCES} ${HEADERS})

# 链接文件系统库
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
    target_link_libraries(chtl stdc++fs)
endif()

# 安装规则
install(TARGETS chtl DESTINATION bin)
install(DIRECTORY include/ DESTINATION include/chtl)
install(DIRECTORY modules/ DESTINATION share/chtl/modules)
install(DIRECTORY examples/ DESTINATION share/chtl/examples)

# 创建包配置
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CHTLConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# 测试
enable_testing()
add_test(NAME hello_world 
    COMMAND chtl ${CMAKE_CURRENT_SOURCE_DIR}/examples/hello-world.chtl -o ${CMAKE_CURRENT_BINARY_DIR}/test-output
)

# 打印配置信息
message(STATUS "CHTL version: ${PROJECT_VERSION}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")