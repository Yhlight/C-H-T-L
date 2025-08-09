# Common library
add_library(chtl_common STATIC
    Token.h
    GlobalMap.h
    GlobalMap.cpp
)

target_include_directories(chtl_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Warnings
if (MSVC)
    target_compile_options(chtl_common PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_common PRIVATE -Wall -Wextra -Wpedantic)
endif()