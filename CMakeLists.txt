cmake_minimum_required(VERSION 3.10)
project(CHTL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找ANTLR4运行时
find_package(antlr4-runtime REQUIRED)

# 设置ANTLR4工具路径
set(ANTLR4_JAR_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/antlr-4.13.1-complete.jar)

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/generated
    ${ANTLR4_INCLUDE_DIRS}
)

# ANTLR4 生成器函数
function(antlr4_generate GRAMMAR_NAME)
    set(GRAMMAR_FILE ${CMAKE_CURRENT_SOURCE_DIR}/grammar/${GRAMMAR_NAME}.g4)
    set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/${GRAMMAR_NAME})
    
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
antlr4_generate(CHTL)
antlr4_generate(CSS)
antlr4_generate(JavaScript)
antlr4_generate(CHTLJavaScript)

# 源文件
set(CHTL_SOURCES
    src/main.cpp
    src/Scanner.cpp
    src/CompilerDispatcher.cpp
    src/CHTLCompiler.cpp
    src/CSSCompiler.cpp
    src/JSCompiler.cpp
    src/CHTLJSCompiler.cpp
    src/CodeGenerator.cpp
    src/SymbolTable.cpp
    src/ASTNode.cpp
)

# 生成的源文件
set(GENERATED_SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CHTL/CHTLLexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CHTL/CHTLParser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CHTL/CHTLVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CHTL/CHTLBaseVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CSS/CSSLexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CSS/CSSParser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CSS/CSSVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CSS/CSSBaseVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/JavaScript/JavaScriptLexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/JavaScript/JavaScriptParser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/JavaScript/JavaScriptVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/JavaScript/JavaScriptBaseVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CHTLJavaScript/CHTLJavaScriptLexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CHTLJavaScript/CHTLJavaScriptParser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CHTLJavaScript/CHTLJavaScriptVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/CHTLJavaScript/CHTLJavaScriptBaseVisitor.cpp
)

# 创建可执行文件
add_executable(chtl ${CHTL_SOURCES} ${GENERATED_SOURCES})

# 链接库
target_link_libraries(chtl antlr4-runtime)

# 依赖关系
add_dependencies(chtl 
    generate_CHTL 
    generate_CSS 
    generate_JavaScript 
    generate_CHTLJavaScript
)

# 安装
install(TARGETS chtl DESTINATION bin)