add_executable(chtlc
    main.cpp
)

target_link_libraries(chtlc
    PRIVATE
        chtl_common
        chtl_context
        chtl_state
        chtl_lexer
        chtl_node
        chtl_parser
        chtl_generator
        chtl_scanner
        chtl_predefine
)

if (MSVC)
    target_compile_options(chtlc PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtlc PRIVATE -Wall -Wextra -Wpedantic)
endif()