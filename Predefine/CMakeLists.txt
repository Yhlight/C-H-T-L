# Predefine sources
set(PREDEFINE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/Predefine/Registry.cpp
)

# Predefine headers
set(PREDEFINE_HEADERS
    ${CMAKE_SOURCE_DIR}/include/Predefine/Registry.h
)

# Create static library
add_library(chtl_predefine STATIC ${PREDEFINE_SOURCES})

# Set include directories
target_include_directories(chtl_predefine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/chtl>
)

# Link dependencies
target_link_libraries(chtl_predefine
    PUBLIC
        chtl_node
)

# Install library
install(TARGETS chtl_predefine
    EXPORT ChtlTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(FILES ${PREDEFINE_HEADERS}
    DESTINATION include/chtl/Predefine
)