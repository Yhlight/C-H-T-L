add_library(chtl_lexer STATIC
    BasicLexer.h
    StandardLexer.h
    StandardLexer.cpp
    ConfigLexer.h
    ConfigLexer.cpp
)

target_include_directories(chtl_lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_lexer PUBLIC chtl_state chtl_context chtl_common)

if (MSVC)
    target_compile_options(chtl_lexer PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_lexer PRIVATE -Wall -Wextra -Wpedantic)
endif()