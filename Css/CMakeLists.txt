# CSS Compiler Module
set(CSS_SOURCES
    CssLexer.cpp
    CssParser.cpp
    CssGenerator.cpp
    CssCompiler.cpp
    CssTokenizer.cpp
    CssAst.cpp
)

set(CSS_HEADERS
    CssLexer.h
    CssParser.h
    CssGenerator.h
    CssCompiler.h
    CssTokenizer.h
    CssAst.h
    CssTypes.h
)

add_library(chtl_css STATIC ${CSS_SOURCES})
target_include_directories(chtl_css PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(chtl_css chtl_common chtl_context chtl_state)