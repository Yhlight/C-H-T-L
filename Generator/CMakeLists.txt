add_library(chtl_generator STATIC
    BasicGenerator.h
    StandardGenerator.h
    StandardGenerator.cpp
    ConfigGenerator.h
    ConfigGenerator.cpp
    README.md
)

target_include_directories(chtl_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_generator PUBLIC chtl_common chtl_node)

if (MSVC)
    target_compile_options(chtl_generator PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_generator PRIVATE -Wall -Wextra -Wpedantic)
endif()