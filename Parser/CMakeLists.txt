# 获取ANTLR4生成的文件
file(GLOB CHTL_GENERATED_SRC
    ${CMAKE_BINARY_DIR}/generated/CHTL/*.cpp
)
file(GLOB CSS_GENERATED_SRC
    ${CMAKE_BINARY_DIR}/generated/Css/*.cpp
)
file(GLOB JS_GENERATED_SRC
    ${CMAKE_BINARY_DIR}/generated/Js/*.cpp
)
file(GLOB CHTLJS_GENERATED_SRC
    ${CMAKE_BINARY_DIR}/generated/Chtl_Js/*.cpp
)

# 如果生成的文件还不存在，创建空列表
if(NOT CHTL_GENERATED_SRC)
    set(CHTL_GENERATED_SRC "")
endif()
if(NOT CSS_GENERATED_SRC)
    set(CSS_GENERATED_SRC "")
endif()
if(NOT JS_GENERATED_SRC)
    set(JS_GENERATED_SRC "")
endif()
if(NOT CHTLJS_GENERATED_SRC)
    set(CHTLJS_GENERATED_SRC "")
endif()

add_library(chtl-parser STATIC
    StandardParser.cpp
    ChtlVisitor.cpp
    CssVisitor.cpp
    JsVisitor.cpp
    ChtlJsVisitor.cpp
    ${CHTL_GENERATED_SRC}
    ${CSS_GENERATED_SRC}
    ${JS_GENERATED_SRC}
    ${CHTLJS_GENERATED_SRC}
)

target_include_directories(chtl-parser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/generated
    /usr/include/antlr4-runtime  # 添加ANTLR4运行时包含路径
)

target_link_libraries(chtl-parser PUBLIC
    chtl-common
    chtl-node
    chtl-context
    chtl-state
    chtl-scanner
    antlr4_shared
)

# 确保ANTLR4生成的文件在编译前生成
add_dependencies(chtl-parser 
    generate_CHTL
    generate_CSS
    generate_JavaScript
    generate_CHTLJavaScript
)