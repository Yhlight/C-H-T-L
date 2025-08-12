add_library(chtl-cmodsystem INTERFACE)

target_include_directories(chtl-cmodsystem INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-cmodsystem INTERFACE
    chtl-module
    chtl-loader
)