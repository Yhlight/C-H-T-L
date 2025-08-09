# 收集所有源文件
set(CHTL_SOURCES
    # Common
    Common/GlobalMap.cpp
    Common/Token.cpp
    
    # State
    State/ChtlState.cpp
    State/CssState.cpp
    State/StateFactory.cpp
    
    # Context
    Context/BasicContext.cpp
    Context/ChtlContext.cpp
    Context/ContextFactory.cpp
    
    # Lexer
    Lexer/BasicLexer.cpp
    Lexer/StandardLexer.cpp
    Lexer/ConfigLexer.cpp
    
    # Parser
    Parser/BasicParser.cpp
    Parser/StandardParser.cpp
    Parser/ConfigParser.cpp
    
    # Node
    Node/Node.cpp
    Node/Comment.cpp
    Node/Template.cpp
    Node/Custom.cpp
    Node/Style.cpp
    Node/Config.cpp
    Node/Import.cpp
    Node/Namespace.cpp
    Node/Operate.cpp
    Node/Origin.cpp
    
    # Generator
    Generator/BasicGenerator.cpp
    Generator/ConfigGenerator.cpp
    Generator/HtmlGenerator.cpp
    
    # Scanner
    Scanner/Segment.cpp
    Scanner/BridgeScanner.cpp
    
    # CSS Analyzer
    Css/CssAnalyzer.cpp
    Css/CssTokenizer.cpp
    Css/CssBlockExtractor.cpp
    
    # JS Analyzer
    Js/JsAnalyzer.cpp
    Js/JsTokenizer.cpp
    Js/JsBlockExtractor.cpp
    
    # CHTL-JS (只包含实际存在的文件)
    ChtlJs/ChtlJsState.cpp
    ChtlJs/ChtlJsContext.cpp
)

# 创建静态库
add_library(chtl_core STATIC ${CHTL_SOURCES})
target_include_directories(chtl_core PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/chtl>
)

# 创建共享库（可选）
add_library(chtl_shared SHARED ${CHTL_SOURCES})
target_include_directories(chtl_shared PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/chtl>
)
set_target_properties(chtl_shared PROPERTIES OUTPUT_NAME chtl)

# 主程序
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
    add_executable(chtl main.cpp)
    target_link_libraries(chtl chtl_core)
endif()

# 安装目标
install(TARGETS chtl_core chtl_shared
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

if(TARGET chtl)
    install(TARGETS chtl RUNTIME DESTINATION bin)
endif()

# 导出目标
install(TARGETS chtl_core chtl_shared
    EXPORT CHTLTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)