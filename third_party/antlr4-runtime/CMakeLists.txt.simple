# Simplified ANTLR4 Runtime for CHTL internal build
cmake_minimum_required(VERSION 3.16)
project(antlr4-runtime VERSION 4.13.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if source exists
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src")
    message(FATAL_ERROR "ANTLR4 runtime source not found. Please run setup_dependencies script.")
endif()

# Source files
file(GLOB_RECURSE ANTLR4_SOURCES
    src/antlr4-runtime/*.cpp
    src/atn/*.cpp
    src/dfa/*.cpp
    src/misc/*.cpp
    src/support/*.cpp
    src/tree/*.cpp
    src/tree/pattern/*.cpp
    src/tree/xpath/*.cpp
)

# Create static library only
add_library(antlr4-runtime STATIC ${ANTLR4_SOURCES})

# Include directories
target_include_directories(antlr4-runtime PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include/antlr4-runtime>
)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(antlr4-runtime PUBLIC ANTLR4CPP_STATIC)
    if(MSVC)
        target_compile_options(antlr4-runtime PRIVATE /MP /W3)
    endif()
endif()

# Export for parent project
if(NOT CHTL_STANDALONE_BUILD)
    set(ANTLR4_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" PARENT_SCOPE)
endif()