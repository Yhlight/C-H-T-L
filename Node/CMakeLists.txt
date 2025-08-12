add_library(chtl-node INTERFACE)

target_include_directories(chtl-node INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-node INTERFACE
    chtl-common
)