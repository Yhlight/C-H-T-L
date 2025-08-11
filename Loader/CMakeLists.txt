# Loader sources
set(LOADER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/Loader/FileLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/Loader/ModuleLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/Loader/CmodLoader.cpp
)

# Loader headers
set(LOADER_HEADERS
    ${CMAKE_SOURCE_DIR}/include/Loader/FileLoader.h
    ${CMAKE_SOURCE_DIR}/include/Loader/ModuleLoader.h
    ${CMAKE_SOURCE_DIR}/include/Loader/CmodLoader.h
)

# Create static library
add_library(chtl_loader STATIC ${LOADER_SOURCES})

# Set include directories
target_include_directories(chtl_loader
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/chtl>
)

# Link dependencies
target_link_libraries(chtl_loader
    PUBLIC
        chtl_parser
        chtl_cmod_system
)

# Install library
install(TARGETS chtl_loader
    EXPORT ChtlTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(FILES ${LOADER_HEADERS}
    DESTINATION include/chtl/Loader
)