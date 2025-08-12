cmake_minimum_required(VERSION 3.10)
project(CHTL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 查找ANTLR4运行时
find_package(antlr4-runtime CONFIG REQUIRED)

# 设置ANTLR4工具路径
set(ANTLR4_JAR_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/antlr-4.13.1-complete.jar)

# 全局包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)

# ANTLR4 生成器函数
function(antlr4_generate GRAMMAR_NAME OUTPUT_DIR)
    set(GRAMMAR_FILE ${CMAKE_CURRENT_SOURCE_DIR}/grammar/${GRAMMAR_NAME}.g4)
    set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/${OUTPUT_DIR})
    
    file(MAKE_DIRECTORY ${GENERATED_DIR})
    
    add_custom_command(
        OUTPUT 
            ${GENERATED_DIR}/${GRAMMAR_NAME}Lexer.cpp
            ${GENERATED_DIR}/${GRAMMAR_NAME}Parser.cpp
            ${GENERATED_DIR}/${GRAMMAR_NAME}Visitor.cpp
            ${GENERATED_DIR}/${GRAMMAR_NAME}BaseVisitor.cpp
        COMMAND java -jar ${ANTLR4_JAR_LOCATION} 
            -Dlanguage=Cpp 
            -visitor 
            -no-listener 
            -o ${GENERATED_DIR}
            ${GRAMMAR_FILE}
        DEPENDS ${GRAMMAR_FILE}
        COMMENT "Generating ${GRAMMAR_NAME} parser with ANTLR4"
    )
    
    add_custom_target(generate_${GRAMMAR_NAME} ALL
        DEPENDS 
            ${GENERATED_DIR}/${GRAMMAR_NAME}Lexer.cpp
            ${GENERATED_DIR}/${GRAMMAR_NAME}Parser.cpp
    )
endfunction()

# 生成各个语法解析器
antlr4_generate(CHTL CHTL)
antlr4_generate(CSS Css)
antlr4_generate(JavaScript Js)
antlr4_generate(CHTLJavaScript Chtl_Js)

# 添加子目录
add_subdirectory(Common)
add_subdirectory(Context)
add_subdirectory(State)
add_subdirectory(Lexer)
add_subdirectory(Node)
add_subdirectory(Parser)
add_subdirectory(Generator)
add_subdirectory(Scanner)
add_subdirectory(Predefine)
add_subdirectory(Optimize)
add_subdirectory(Utils)
add_subdirectory(Module)
add_subdirectory(Loader)
add_subdirectory(CmodSystem)
add_subdirectory(Css)
add_subdirectory(Js)
add_subdirectory(Chtl_Js)
add_subdirectory(App)

# 创建主库
add_library(chtl-core INTERFACE)
target_link_libraries(chtl-core INTERFACE
    chtl-common
    chtl-context
    chtl-state
    chtl-lexer
    chtl-node
    chtl-parser
    chtl-generator
    chtl-scanner
    chtl-predefine
    antlr4_shared
)