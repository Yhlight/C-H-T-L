add_library(chtl_node STATIC
    Node.h
)

target_include_directories(chtl_node PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_node PUBLIC chtl_common)

if (MSVC)
    target_compile_options(chtl_node PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_node PRIVATE -Wall -Wextra -Wpedantic)
endif()