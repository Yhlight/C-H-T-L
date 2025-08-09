# JavaScript Static Analyzer Module
set(JS_SOURCES
    JsAnalyzer.cpp
    JsTokenizer.cpp
    JsBlockExtractor.cpp
)

set(JS_HEADERS
    JsAnalyzer.h
    JsTokenizer.h
    JsBlockExtractor.h
    JsTypes.h
)

add_library(chtl_js STATIC ${JS_SOURCES})
target_include_directories(chtl_js PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(chtl_js chtl_common chtl_context chtl_state)