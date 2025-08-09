add_library(chtl_parser STATIC
    BasicParser.h
    StandardParser.h
    StandardParser.cpp
    ConfigParser.h
    ConfigParser.cpp
    README.md
)

target_include_directories(chtl_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_parser PUBLIC chtl_common chtl_node)

if (MSVC)
    target_compile_options(chtl_parser PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_parser PRIVATE -Wall -Wextra -Wpedantic)
endif()