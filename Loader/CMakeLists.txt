add_library(chtl-loader INTERFACE)

target_include_directories(chtl-loader INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-loader INTERFACE
    chtl-module
)