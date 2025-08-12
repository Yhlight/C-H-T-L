add_library(chtl-lexer INTERFACE)

target_include_directories(chtl-lexer INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-lexer INTERFACE
    chtl-common
)