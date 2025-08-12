add_library(chtl-js STATIC
    JsParser.cpp
)

target_include_directories(chtl-js PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-js PUBLIC
    chtl-common
    chtl-node
    antlr4_shared
)