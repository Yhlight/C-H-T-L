add_library(chtl-scanner STATIC
    BridgeScanner/BridgeScanner.cpp
)

target_include_directories(chtl-scanner PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(chtl-scanner PUBLIC
    chtl-common
    chtl-context
)