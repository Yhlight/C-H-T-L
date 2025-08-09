# CSS Static Analyzer Module
set(CSS_SOURCES
    CssAnalyzer.cpp
    CssTokenizer.cpp
    CssBlockExtractor.cpp
)

set(CSS_HEADERS
    CssAnalyzer.h
    CssTokenizer.h
    CssBlockExtractor.h
    CssTypes.h
)

add_library(chtl_css STATIC ${CSS_SOURCES})
target_include_directories(chtl_css PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(chtl_css chtl_common chtl_context chtl_state)