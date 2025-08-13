cmake_minimum_required(VERSION 3.16)
project(CHTL VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置默认构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加CMake模块路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# 包含CHTL模块功能
include(CHTLModules)

# 查找必需的包
find_package(Java QUIET COMPONENTS Runtime)

# 检查ANTLR工具
find_program(ANTLR_EXECUTABLE
    NAMES antlr4 antlr
    PATHS /usr/local/bin /usr/bin
)

if(NOT ANTLR_EXECUTABLE)
    message(WARNING "ANTLR4 not found. Parser generation will be skipped.")
endif()

# 添加子目录
add_subdirectory(src)

# 如果存在generated目录，添加它
if(EXISTS "${CMAKE_SOURCE_DIR}/generated")
    add_subdirectory(generated)
endif()

# 配置模块打包
# 这会在构建时自动执行
process_chtl_modules()

# 添加自定义目标
add_module_packing_target()

# 安装规则
install(DIRECTORY ${CMAKE_BINARY_DIR}/module/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/chtl/module
    FILES_MATCHING
    PATTERN "*.cmod"
    PATTERN "*.cjmod"
    PATTERN "modules.index"
)

# 创建一个目标来生成解析器
if(ANTLR_EXECUTABLE AND Java_FOUND)
    add_custom_target(generate-parsers
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/generated
        COMMAND ${CMAKE_SOURCE_DIR}/generate_parsers.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating ANTLR parsers..."
    )
endif()

# 创建完整构建目标
add_custom_target(build-all
    COMMAND ${CMAKE_COMMAND} --build . --target generate-parsers
    COMMAND ${CMAKE_COMMAND} --build . --target all
    COMMAND ${CMAKE_COMMAND} --build . --target pack-modules
    COMMENT "Building everything including parsers and modules..."
)

# 打印配置信息
message(STATUS "====================================")
message(STATUS "CHTL Configuration:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Module Source: ${CMAKE_SOURCE_DIR}/module")
message(STATUS "  Module Output: ${CMAKE_BINARY_DIR}/module")
message(STATUS "====================================")

# 添加测试
enable_testing()
add_test(NAME module_packing_test
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/PackModules.cmake
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)