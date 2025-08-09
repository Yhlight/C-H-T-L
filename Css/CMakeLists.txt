add_library(chtl_css_analyzer STATIC
    Tokens.h
    Lexer.h
    Lexer.cpp
    Ast.h
    Parser.h
    Parser.cpp
    CssFindings.h
    CssBackend.h
    HeuristicCssBackend.h
    HeuristicCssBackend.cpp
    SelfCssBackend.h
    SelfCssBackend.cpp
    CssAnalyzer.h
    CssAnalyzer.cpp
    CssCompileResult.h
    CssCompiler.h
    CssCompiler.cpp
)

target_include_directories(chtl_css_analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_css_analyzer PUBLIC chtl_common chtl_node)

if (MSVC)
    target_compile_options(chtl_css_analyzer PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_css_analyzer PRIVATE -Wall -Wextra -Wpedantic)
endif()