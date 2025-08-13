cmake_minimum_required(VERSION 3.16)
project(CHTL VERSION 1.0.0 LANGUAGES CXX)

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 查找必要的包
find_package(Threads REQUIRED)
find_package(Java QUIET COMPONENTS Runtime)

# ANTLR4运行时 - 使用内置版本
if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime/src")
    # 使用简化的CMakeLists.txt从源码构建
    if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime/CMakeLists.txt.simple")
        # 复制简化版作为主CMakeLists.txt
        configure_file(
            "${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime/CMakeLists.txt.simple"
            "${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime/CMakeLists.txt"
            COPYONLY
        )
    endif()
    
    # 设置标志以避免复杂的安装配置
    set(CHTL_INTERNAL_BUILD ON)
    add_subdirectory(third_party/antlr4-runtime)
    set(ANTLR4_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime/src")
elseif(EXISTS "${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime/lib")
    # 使用预构建的ANTLR4运行时
    set(ANTLR4_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime/include")
    
    # 查找库文件
    find_library(ANTLR4_RUNTIME_LIB 
        NAMES antlr4-runtime 
        PATHS "${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime/lib"
        NO_DEFAULT_PATH
    )
    
    if(NOT ANTLR4_RUNTIME_LIB)
        message(FATAL_ERROR "ANTLR4 runtime library not found.")
    endif()
    
    # 创建导入目标
    add_library(antlr4-runtime STATIC IMPORTED)
    set_target_properties(antlr4-runtime PROPERTIES
        IMPORTED_LOCATION "${ANTLR4_RUNTIME_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${ANTLR4_INCLUDE_DIR}"
    )
else()
    message(FATAL_ERROR "ANTLR4 runtime not found. Please run setup_dependencies script first.")
endif()

# 检查ANTLR工具（用于生成解析器）
find_program(ANTLR_EXECUTABLE
    NAMES antlr4 antlr
    PATHS /usr/local/bin /usr/bin
)

if(NOT ANTLR_EXECUTABLE)
    message(WARNING "ANTLR4 tool not found. Parser generation will be skipped.")
endif()

# 包含目录
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/generated
)

# ===== CHTL核心 - 完全独立实现 =====
file(GLOB_RECURSE CHTL_CORE_SOURCES
    src/chtl/core/*.cpp
    src/chtl/generator/*.cpp
    src/chtl/template/*.cpp
    src/chtl/custom/*.cpp
    src/chtl/origin/*.cpp
    src/chtl/import/*.cpp
    src/chtl/namespace/*.cpp
    src/chtl/constraint/*.cpp
    src/chtl/module/*.cpp
    src/chtl/error/*.cpp
    src/chtl/utils/*.cpp
)

# ===== CHTL独立解析器 =====
file(GLOB_RECURSE CHTL_PARSER_SOURCES
    src/chtl/parser/standalone/ParserRuntime.cpp
    src/chtl/parser/standalone/CHTLLexer.cpp
    src/chtl/parser/standalone/CHTLParser.cpp
    src/chtl/parser/standalone/CHTLJSLexer.cpp
    src/chtl/parser/standalone/CHTLJSParser.cpp
)

# ===== 扫描器 - 独立实现 =====
file(GLOB_RECURSE SCANNER_SOURCES
    src/chtl/scanner/*.cpp
)

# 添加精准扫描器
set(SCANNER_SOURCES 
    ${SCANNER_SOURCES}
    src/chtl/scanner/PrecisionScanner.cpp
)

# ===== 配置系统 - 由CHTL独立处理 =====
file(GLOB_RECURSE CONFIG_SOURCES
    src/chtl/config/*.cpp
    src/chtl/parser/standalone/ConfigLexer.cpp
    src/chtl/parser/standalone/ConfigParser.cpp
)

# ===== CSS解析器 - 使用ANTLR4 =====
if(EXISTS "${CMAKE_SOURCE_DIR}/generated/css")
    file(GLOB_RECURSE CSS_ANTLR_SOURCES
        generated/css/*.cpp
    )
else()
    set(CSS_ANTLR_SOURCES "")
    message(WARNING "CSS parser not generated. Run setup_dependencies.sh first.")
endif()

file(GLOB CSS_COMPILER_SOURCES
    src/chtl/CHTLCSSCompiler.cpp
    src/chtl/CHTLCSSPreprocessor.cpp
)

# ===== JS解析器 - 使用ANTLR4 =====
if(EXISTS "${CMAKE_SOURCE_DIR}/generated/js")
    file(GLOB_RECURSE JS_ANTLR_SOURCES
        generated/js/*.cpp
    )
else()
    set(JS_ANTLR_SOURCES "")
    message(WARNING "JS parser not generated. Run setup_dependencies.sh first.")
endif()

file(GLOB JS_COMPILER_SOURCES
    src/chtl/CHTLJSCompiler.cpp
    src/chtl/CHTLJSOptimizer.cpp
    src/chtl/optimizer/*.cpp
)

# ===== 主程序 =====
set(CHTL_MAIN_SOURCES
    src/main.cpp
)

# 创建库
# CHTL核心库（无ANTLR4依赖）
add_library(chtl_core STATIC
    ${CHTL_CORE_SOURCES}
    ${CHTL_PARSER_SOURCES}
    ${SCANNER_SOURCES}
    ${CONFIG_SOURCES}
)

# CSS/JS库（依赖ANTLR4）
add_library(chtl_css_js STATIC
    ${CSS_ANTLR_SOURCES}
    ${CSS_COMPILER_SOURCES}
    ${JS_ANTLR_SOURCES}
    ${JS_COMPILER_SOURCES}
)

# 链接ANTLR4仅到CSS/JS库
target_link_libraries(chtl_css_js PUBLIC antlr4-runtime)

# 主可执行文件
add_executable(chtl ${CHTL_MAIN_SOURCES})

# 链接
target_link_libraries(chtl
    chtl_core
    chtl_css_js
    Threads::Threads
)

# 安装规则
install(TARGETS chtl
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/chtl
    DESTINATION include
)

# 模块
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/module
    DESTINATION share/chtl
)

# 示例
install(DIRECTORY ${CMAKE_SOURCE_DIR}/examples
    DESTINATION share/chtl
)

# 文档
install(DIRECTORY ${CMAKE_SOURCE_DIR}/docs
    DESTINATION share/chtl
)

# 测试
enable_testing()

# 单元测试
file(GLOB_RECURSE TEST_SOURCES tests/unit/*.cpp)
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} 
        chtl_core 
        chtl_css_js 
        Threads::Threads
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# 自定义目标 - 生成解析器
if(ANTLR_EXECUTABLE AND Java_FOUND)
    add_custom_target(generate_parsers
        COMMAND ${CMAKE_SOURCE_DIR}/generate_parsers.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating ANTLR parsers for CSS and JavaScript"
    )
endif()

# 显示配置信息
message(STATUS "")
message(STATUS "CHTL Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "")
message(STATUS "Parser Implementation:")
message(STATUS "  CHTL Parser: Standalone (Native)")
message(STATUS "  CHTL JS Parser: Standalone (Native)")
message(STATUS "  Config Parser: Standalone (Native)")
message(STATUS "  Scanner: Standalone (Native)")
message(STATUS "  CSS Parser: ANTLR4")
message(STATUS "  JS Parser: ANTLR4")
message(STATUS "")
message(STATUS "Dependencies:")
message(STATUS "  ANTLR4 Runtime: ${antlr4-runtime_FOUND} (CSS/JS only)")
message(STATUS "  Threads: ${Threads_FOUND}")
message(STATUS "")