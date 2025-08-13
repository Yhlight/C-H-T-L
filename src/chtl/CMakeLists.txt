# src/chtl/CMakeLists.txt

# 收集源文件
set(CHTL_CORE_SOURCES "")

# 定义期望的源文件列表
set(EXPECTED_SOURCES
    CHTLContext.cpp
    CHTLGenerator.cpp
    CHTLStateMachine.cpp
    CHTLTemplate.cpp
    CHTLCustom.cpp
    CHTLOrigin.cpp
    CHTLImport.cpp
    CHTLNamespace.cpp
    CHTLConstraint.cpp
    CHTLScript.cpp
    CHTLCMOD.cpp
    CHTLCJMOD.cpp
    CHTLCSSCompiler.cpp
    CHTLJSCompiler.cpp
    CHTLCSSPreprocessor.cpp
    CHTLUnifiedScanner.cpp
)

# 检查每个源文件是否存在
foreach(source ${EXPECTED_SOURCES})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
        list(APPEND CHTL_CORE_SOURCES ${source})
    else()
        message(STATUS "Source file not found (will use stub): ${source}")
    endif()
endforeach()

# 如果没有找到任何源文件，创建一个占位库
if(NOT CHTL_CORE_SOURCES)
    # 创建一个简单的占位源文件
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/chtl_stub.cpp" 
        "// Placeholder for CHTL core library\n"
        "namespace chtl { void placeholder() {} }\n"
    )
    set(CHTL_CORE_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/chtl_stub.cpp")
endif()

# CHTL核心库
add_library(chtl_core STATIC ${CHTL_CORE_SOURCES})

# 添加包含目录
target_include_directories(chtl_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/generated  # ANTLR生成的头文件
)

# 如果存在ANTLR生成的解析器
if(EXISTS "${CMAKE_SOURCE_DIR}/generated/CHTLLexer.cpp")
    add_library(chtl_parser STATIC
        ${CMAKE_SOURCE_DIR}/generated/CHTLLexer.cpp
        ${CMAKE_SOURCE_DIR}/generated/CHTLParser.cpp
        ${CMAKE_SOURCE_DIR}/generated/CHTLBaseListener.cpp
        ${CMAKE_SOURCE_DIR}/generated/CHTLListener.cpp
        ${CMAKE_SOURCE_DIR}/generated/CSSLexer.cpp
        ${CMAKE_SOURCE_DIR}/generated/CSSParser.cpp
        ${CMAKE_SOURCE_DIR}/generated/CSSBaseListener.cpp
        ${CMAKE_SOURCE_DIR}/generated/CSSListener.cpp
        ${CMAKE_SOURCE_DIR}/generated/JavaScriptLexer.cpp
        ${CMAKE_SOURCE_DIR}/generated/JavaScriptParser.cpp
        ${CMAKE_SOURCE_DIR}/generated/JavaScriptBaseListener.cpp
        ${CMAKE_SOURCE_DIR}/generated/JavaScriptListener.cpp
    )
    
    target_include_directories(chtl_parser PUBLIC
        ${CMAKE_SOURCE_DIR}/generated
        ${CMAKE_SOURCE_DIR}/src
    )
    
    # 查找ANTLR运行时
    find_package(antlr4-runtime QUIET)
    if(antlr4-runtime_FOUND)
        target_link_libraries(chtl_parser PUBLIC antlr4-runtime)
    else()
        message(WARNING "ANTLR4 runtime not found. Parser functionality will be limited.")
    endif()
else()
    # 创建空的解析器库
    add_library(chtl_parser INTERFACE)
endif()

# 链接必要的系统库
find_package(Threads REQUIRED)
target_link_libraries(chtl_core PUBLIC
    Threads::Threads
    ${CMAKE_DL_LIBS}  # for dlopen/dlsym
)

# 如果在Unix系统上，添加文件系统支持
if(UNIX AND NOT APPLE)
    target_link_libraries(chtl_core PUBLIC stdc++fs)
endif()

# 安装头文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/chtl
    FILES_MATCHING PATTERN "*.h"
)