add_library(chtl_css_analyzer STATIC
    CssAnalyzer.h
    CssAnalyzer.cpp
    CssFindings.h
)

target_include_directories(chtl_css_analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_css_analyzer PUBLIC chtl_common chtl_node)

if (MSVC)
    target_compile_options(chtl_css_analyzer PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_css_analyzer PRIVATE -Wall -Wextra -Wpedantic)
endif()