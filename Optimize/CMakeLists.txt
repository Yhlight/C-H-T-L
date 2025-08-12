add_library(chtl-optimize INTERFACE)

target_include_directories(chtl-optimize INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-optimize INTERFACE
    chtl-node
)