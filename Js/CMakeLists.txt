add_library(chtl_js_analyzer STATIC
    JsFindings.h
    JsBackend.h
    HeuristicJsBackend.h
    HeuristicJsBackend.cpp
    JsAnalyzer.h
    JsAnalyzer.cpp
    JsCompileResult.h
    JsCompiler.h
    JsCompiler.cpp
)

target_include_directories(chtl_js_analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_js_analyzer PUBLIC chtl_common chtl_node)

if (MSVC)
    target_compile_options(chtl_js_analyzer PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_js_analyzer PRIVATE -Wall -Wextra -Wpedantic)
endif()