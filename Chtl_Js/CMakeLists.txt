# CHTL-JS Compiler Module
set(CHTL_JS_SOURCES
    ChtlJsAnalyzer.cpp
    ChtlJsTokenizer.cpp
    ChtlJsTransformer.cpp
    ChtlJsGenerator.cpp
)

set(CHTL_JS_HEADERS
    ChtlJsTypes.h
    ChtlJsAnalyzer.h
    ChtlJsTokenizer.h
    ChtlJsTransformer.h
    ChtlJsGenerator.h
)

add_library(chtl_js STATIC ${CHTL_JS_SOURCES})
target_include_directories(chtl_js PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(chtl_js 
    chtl_common 
    chtl_context 
    chtl_state
    chtl_js_analyzer  # 链接标准JS分析器
)