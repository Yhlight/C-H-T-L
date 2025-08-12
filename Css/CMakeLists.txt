add_library(chtl-css STATIC
    CssParser.cpp
)

target_include_directories(chtl-css PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-css PUBLIC
    chtl-common
    chtl-node
    antlr4_shared
)