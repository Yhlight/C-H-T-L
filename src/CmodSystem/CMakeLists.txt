# CMOD System sources
set(CMOD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CmodInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CmodValidator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CmodExtractor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CmodPackager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CmodRegistry.cpp
)

# CMOD System headers
set(CMOD_HEADERS
    ${CMAKE_SOURCE_DIR}/include/CmodSystem/CmodInfo.h
    ${CMAKE_SOURCE_DIR}/include/CmodSystem/CmodValidator.h
    ${CMAKE_SOURCE_DIR}/include/CmodSystem/CmodExtractor.h
    ${CMAKE_SOURCE_DIR}/include/CmodSystem/CmodPackager.h
    ${CMAKE_SOURCE_DIR}/include/CmodSystem/CmodRegistry.h
)

# Create CMOD System library
add_library(chtl_cmod_system STATIC ${CMOD_SOURCES})

# Set include directories
target_include_directories(chtl_cmod_system
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/chtl>
)

# Link dependencies
target_link_libraries(chtl_cmod_system
    PUBLIC
        chtl_parser
        chtl_generator
)

# Install library
install(TARGETS chtl_cmod_system
    EXPORT ChtlTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(FILES ${CMOD_HEADERS}
    DESTINATION include/chtl/CmodSystem
)