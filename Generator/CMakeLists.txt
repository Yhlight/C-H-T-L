add_library(chtl-generator STATIC
    StandardGenerator.cpp
    HtmlGenerator.cpp
    CssGenerator.cpp
    JsGenerator.cpp
)

target_include_directories(chtl-generator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-generator PUBLIC
    chtl-common
    chtl-node
    chtl-state
    chtl-context
    chtl-optimize
)