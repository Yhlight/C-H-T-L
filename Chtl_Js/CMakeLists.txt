# CHTL-JS Compiler Module
set(CHTL_JS_SOURCES
    ChtlJsLexer.cpp
    ChtlJsParser.cpp
    ChtlJsState.cpp
    ChtlJsContext.cpp
    ChtlJsTransformer.cpp
    ChtlJsGenerator.cpp
    ChtlJsCompiler.cpp
)

set(CHTL_JS_HEADERS
    ChtlJsTypes.h
    ChtlJsLexer.h
    ChtlJsParser.h
    ChtlJsState.h
    ChtlJsContext.h
    ChtlJsTransformer.h
    ChtlJsGenerator.h
    ChtlJsCompiler.h
)

add_library(chtl_js STATIC ${CHTL_JS_SOURCES})
target_include_directories(chtl_js PUBLIC ${CMAKE_SOURCE_DIR}/include)
# CHTL-JS是独立的编译器，不依赖CHTL主编译器