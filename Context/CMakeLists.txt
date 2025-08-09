add_library(chtl_context STATIC
    BasicContext.h
    StandardContext.h
    ChtlContext.h
    CssContext.h
    JsContext.h
    Chtl_JsContext.h
    ContextFactory.h
)

target_include_directories(chtl_context PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_context PUBLIC chtl_common)

if (MSVC)
    target_compile_options(chtl_context PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_context PRIVATE -Wall -Wextra -Wpedantic)
endif()