add_library(chtl-module INTERFACE)

target_include_directories(chtl-module INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-module INTERFACE
    chtl-common
    chtl-node
)