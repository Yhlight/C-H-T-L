# src/chtljs/CMakeLists.txt

# 收集源文件
set(CHTLJS_CORE_SOURCES "")

# 定义期望的源文件列表
set(EXPECTED_SOURCES
    CHTLJSContext.cpp
    CHTLJSStateMachine.cpp
)

# 检查每个源文件是否存在
foreach(source ${EXPECTED_SOURCES})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
        list(APPEND CHTLJS_CORE_SOURCES ${source})
    else()
        message(STATUS "Source file not found (will use stub): ${source}")
    endif()
endforeach()

# 如果没有找到任何源文件，创建一个占位库
if(NOT CHTLJS_CORE_SOURCES)
    # 创建一个简单的占位源文件
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/chtljs_stub.cpp" 
        "// Placeholder for CHTL JS core library\n"
        "namespace chtl { void chtljs_placeholder() {} }\n"
    )
    set(CHTLJS_CORE_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/chtljs_stub.cpp")
endif()

# CHTL JS核心库
add_library(chtljs_core STATIC ${CHTLJS_CORE_SOURCES})

# 添加包含目录
target_include_directories(chtljs_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/generated  # ANTLR生成的头文件
)

# 如果存在ANTLR生成的CHTL JS解析器
if(EXISTS "${CMAKE_SOURCE_DIR}/generated/CHTLJavaScriptLexer.cpp")
    target_sources(chtljs_core PRIVATE
        ${CMAKE_SOURCE_DIR}/generated/CHTLJavaScriptLexer.cpp
        ${CMAKE_SOURCE_DIR}/generated/CHTLJavaScriptParser.cpp
        ${CMAKE_SOURCE_DIR}/generated/CHTLJavaScriptBaseListener.cpp
        ${CMAKE_SOURCE_DIR}/generated/CHTLJavaScriptListener.cpp
    )
endif()

# 链接到CHTL核心库
target_link_libraries(chtljs_core PUBLIC
    chtl_core
)

# 安装头文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/chtljs
    FILES_MATCHING PATTERN "*.h"
)