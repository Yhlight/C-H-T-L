add_library(chtl-state STATIC
    SymbolTable.cpp
    Symbol.cpp
    Scope.cpp
)

target_include_directories(chtl-state PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-state PUBLIC
    chtl-common
    chtl-node
)