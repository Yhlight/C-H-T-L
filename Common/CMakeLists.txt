add_library(chtl-common STATIC
    GlobalMap.cpp
)

target_include_directories(chtl-common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)