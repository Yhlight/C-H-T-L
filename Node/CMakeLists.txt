add_library(chtl-node STATIC
    Node.cpp
    ElementNode.cpp
    TextNode.cpp
    StyleNode.cpp
    ScriptNode.cpp
    TemplateNode.cpp
    CustomNode.cpp
)

target_include_directories(chtl-node PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-node PUBLIC
    chtl-common
)