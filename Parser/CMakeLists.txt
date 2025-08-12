add_library(chtl-parser STATIC
    StandardParser.cpp
    ChtlVisitor.cpp
    CssVisitor.cpp
    JsVisitor.cpp
    ChtlJsVisitor.cpp
    # ANTLR4生成的文件
    ${CMAKE_BINARY_DIR}/generated/CHTL/CHTLLexer.cpp
    ${CMAKE_BINARY_DIR}/generated/CHTL/CHTLParser.cpp
    ${CMAKE_BINARY_DIR}/generated/CHTL/CHTLVisitor.cpp
    ${CMAKE_BINARY_DIR}/generated/CHTL/CHTLBaseVisitor.cpp
    ${CMAKE_BINARY_DIR}/generated/Css/CSSLexer.cpp
    ${CMAKE_BINARY_DIR}/generated/Css/CSSParser.cpp
    ${CMAKE_BINARY_DIR}/generated/Css/CSSVisitor.cpp
    ${CMAKE_BINARY_DIR}/generated/Css/CSSBaseVisitor.cpp
    ${CMAKE_BINARY_DIR}/generated/Js/JavaScriptLexer.cpp
    ${CMAKE_BINARY_DIR}/generated/Js/JavaScriptParser.cpp
    ${CMAKE_BINARY_DIR}/generated/Js/JavaScriptVisitor.cpp
    ${CMAKE_BINARY_DIR}/generated/Js/JavaScriptBaseVisitor.cpp
    ${CMAKE_BINARY_DIR}/generated/Chtl_Js/CHTLJavaScriptLexer.cpp
    ${CMAKE_BINARY_DIR}/generated/Chtl_Js/CHTLJavaScriptParser.cpp
    ${CMAKE_BINARY_DIR}/generated/Chtl_Js/CHTLJavaScriptVisitor.cpp
    ${CMAKE_BINARY_DIR}/generated/Chtl_Js/CHTLJavaScriptBaseVisitor.cpp
)

target_include_directories(chtl-parser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/generated
)

target_link_libraries(chtl-parser PUBLIC
    chtl-common
    chtl-node
    chtl-context
    chtl-state
    antlr4_shared
)

# 确保ANTLR4生成的文件在编译前生成
add_dependencies(chtl-parser 
    generate_CHTL
    generate_CSS
    generate_JavaScript
    generate_CHTLJavaScript
)