add_library(chtl-context INTERFACE)

target_include_directories(chtl-context INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-context INTERFACE
    chtl-common
    chtl-node
)