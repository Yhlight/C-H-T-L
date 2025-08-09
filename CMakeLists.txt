cmake_minimum_required(VERSION 3.14)
project(CHTL VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置默认构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# 添加编译选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    else()
        add_compile_options(-O3)
    endif()
elseif(MSVC)
    add_compile_options(/W4)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Od)
    else()
        add_compile_options(/O2)
    endif()
endif()

# 包含子目录
add_subdirectory(src)
add_subdirectory(tests)
# TODO: 以下模块待实现
# add_subdirectory(App)
# add_subdirectory(Predefine)
# add_subdirectory(Loader)
# add_subdirectory(CmodSystem)
# add_subdirectory(Module)

# 创建安装配置
include(CMakePackageConfigHelpers)

# 生成版本文件
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CHTLConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# 配置文件
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CHTLConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CHTLConfig.cmake"
    INSTALL_DESTINATION lib/cmake/CHTL
)

# 安装配置文件
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CHTLConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CHTLConfigVersion.cmake"
    DESTINATION lib/cmake/CHTL
)

# 导出目标
install(EXPORT CHTLTargets
    FILE CHTLTargets.cmake
    NAMESPACE CHTL::
    DESTINATION lib/cmake/CHTL
)

# 创建卸载目标
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

# 状态信息
message(STATUS "CHTL Compiler Configuration:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Tests: ${BUILD_TESTS}")