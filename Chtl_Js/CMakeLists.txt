add_library(chtl-chtljs STATIC
    ChtlJsParser.cpp
    ChtlJsTransformer.cpp
)

target_include_directories(chtl-chtljs PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-chtljs PUBLIC
    chtl-common
    chtl-node
    chtl-js
    antlr4_shared
)