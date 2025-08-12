cmake_minimum_required(VERSION 3.10)
project(CHTL VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# v2 源文件
set(V2_SOURCES
    # State
    src/v2/State/ChtlParseState.cpp
    src/v2/State/ChtlStateMachine.cpp
    src/v2/State/StateTransitions.cpp
    src/v2/State/SubStateTransitions.cpp
    
    # Context
    src/v2/Context/ParseContext.cpp
    
    # Lexer
    src/v2/Lexer/Token.cpp
    src/v2/Lexer/ChtlLexer.cpp
    
    # Node
    src/v2/Node/Node.cpp
    
    # Parser
    src/v2/Parser/ChtlParser.cpp
    
    # Generator
    src/v2/Generator/ChtlGenerator.cpp
    
    # CSS
    src/v2/Css/CssTokenizer.cpp
    src/v2/Css/CssParser.cpp
    src/v2/Css/NativeCssAnalyzer.cpp
    
    # JS (暂时禁用以修复编译问题)
#    src/v2/Js/JsTokenizer.cpp
#    src/v2/Js/JsParser.cpp
#    src/v2/Js/NativeJsAnalyzer.cpp
    
    # CHTL-JS
    src/v2/ChtlJs/ChtlJsCompiler.cpp
    
    # Scanner
    src/v2/Scanner/JsScanner.cpp
    src/v2/Scanner/CodeMerger.cpp
    
    # Import
    src/v2/Import/ImportSystem.cpp
    
    # CMOD (暂时禁用，需要 JSON 库)
    # src/v2/Cmod/CmodSystem.cpp
)

# CHTL v2 库
add_library(chtl_v2 STATIC ${V2_SOURCES})

# CLI 可执行文件
add_executable(chtl src/CLI/main.cpp)
target_link_libraries(chtl chtl_v2 stdc++fs)

# 安装
install(TARGETS chtl DESTINATION bin)
install(DIRECTORY include/v2 DESTINATION include/chtl)

# 打包配置
set(CPACK_PACKAGE_NAME "CHTL")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Component HTML Template Language Compiler")
include(CPack)