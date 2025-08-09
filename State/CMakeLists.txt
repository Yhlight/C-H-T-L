add_library(chtl_state STATIC
    BasicState.h
    StandardState.h
    StandardState.cpp
    ChtlState.h
    ChtlState.cpp
    CssState.h
    JsState.h
    Chtl_JsState.h
    StateFactory.h
)

target_include_directories(chtl_state PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_state PUBLIC chtl_common chtl_context)

if (MSVC)
    target_compile_options(chtl_state PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_state PRIVATE -Wall -Wextra -Wpedantic)
endif()