# ANTLR4 Runtime CMake Configuration
cmake_minimum_required(VERSION 3.16)
project(antlr4-runtime VERSION 4.13.1 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 选项
option(ANTLR4_BUILD_SHARED "Build shared library" ON)
option(ANTLR4_BUILD_STATIC "Build static library" ON)

# 源文件
file(GLOB_RECURSE ANTLR4_SOURCES
    src/antlr4-runtime/*.cpp
    src/atn/*.cpp
    src/dfa/*.cpp
    src/misc/*.cpp
    src/support/*.cpp
    src/tree/*.cpp
    src/tree/pattern/*.cpp
    src/tree/xpath/*.cpp
)

# 创建库
if(ANTLR4_BUILD_SHARED)
    add_library(antlr4-runtime SHARED ${ANTLR4_SOURCES})
    set_target_properties(antlr4-runtime PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 4
        OUTPUT_NAME antlr4-runtime
    )
endif()

if(ANTLR4_BUILD_STATIC)
    add_library(antlr4-runtime-static STATIC ${ANTLR4_SOURCES})
    set_target_properties(antlr4-runtime-static PROPERTIES
        OUTPUT_NAME antlr4-runtime
    )
endif()

# 包含目录
if(ANTLR4_BUILD_SHARED)
    target_include_directories(antlr4-runtime PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include/antlr4-runtime>
    )
endif()

if(ANTLR4_BUILD_STATIC)
    target_include_directories(antlr4-runtime-static PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include/antlr4-runtime>
    )
endif()

# 编译定义
if(WIN32)
    if(ANTLR4_BUILD_SHARED)
        target_compile_definitions(antlr4-runtime PRIVATE ANTLR4CPP_EXPORTS)
    endif()
endif()

# 安装
install(DIRECTORY src/
    DESTINATION include/antlr4-runtime
    FILES_MATCHING PATTERN "*.h"
)

if(ANTLR4_BUILD_SHARED)
    install(TARGETS antlr4-runtime
        EXPORT antlr4-targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endif()

if(ANTLR4_BUILD_STATIC)
    install(TARGETS antlr4-runtime-static
        EXPORT antlr4-targets
        ARCHIVE DESTINATION lib
    )
endif()

# 导出配置（简化版本）
if(NOT CHTL_INTERNAL_BUILD)
    install(EXPORT antlr4-targets
        FILE antlr4-runtime-targets.cmake
        NAMESPACE antlr4::
        DESTINATION lib/cmake/antlr4-runtime
    )
endif()