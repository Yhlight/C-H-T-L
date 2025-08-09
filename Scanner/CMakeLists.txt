add_library(chtl_scanner STATIC
    Segment/Segment.h
    BridgeScanner/BridgeScanner.h
    BridgeScanner/BridgeScanner.cpp
)

target_include_directories(chtl_scanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_scanner PUBLIC chtl_common)

if (MSVC)
    target_compile_options(chtl_scanner PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_scanner PRIVATE -Wall -Wextra -Wpedantic)
endif()