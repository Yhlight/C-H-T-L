cmake_minimum_required(VERSION 3.15)
project(CHTL VERSION 1.0.0 LANGUAGES CXX)

# C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

# 包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 收集源文件
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# 排除被禁用的文件
list(FILTER SOURCES EXCLUDE REGEX ".*\\.disabled$")

# 收集头文件
file(GLOB_RECURSE HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

# 创建可执行文件
add_executable(chtl ${SOURCES} ${HEADERS})

# 链接文件系统库
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
    target_link_libraries(chtl stdc++fs)
endif()

# 安装规则
install(TARGETS chtl DESTINATION bin)
install(DIRECTORY include/ DESTINATION include/chtl)
install(DIRECTORY modules/ DESTINATION share/chtl/modules)
install(DIRECTORY examples/ DESTINATION share/chtl/examples)

# 创建包配置
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CHTLConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# 测试
enable_testing()
add_test(NAME hello_world 
    COMMAND chtl ${CMAKE_CURRENT_SOURCE_DIR}/examples/hello-world.chtl -o ${CMAKE_CURRENT_BINARY_DIR}/test-output
)

# 打印配置信息
message(STATUS "CHTL version: ${PROJECT_VERSION}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

# 创建module输出目录
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/module)

# 自动扫描和打包src/Module中的CMOD模块
file(GLOB MODULE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src/Module/*")
foreach(MODULE_DIR ${MODULE_DIRS})
    if(IS_DIRECTORY ${MODULE_DIR})
        get_filename_component(MODULE_NAME ${MODULE_DIR} NAME)
        
        # 检查是否是有效的CMOD结构（包含info目录）
        if(EXISTS "${MODULE_DIR}/info")
            message(STATUS "Found CMOD module: ${MODULE_NAME}")
            
            # 添加自定义命令来打包CMOD
            add_custom_command(
                OUTPUT ${CMAKE_BINARY_DIR}/module/${MODULE_NAME}.cmod
                COMMAND $<TARGET_FILE:chtl> --pack-cmod ${MODULE_DIR} -o ${CMAKE_BINARY_DIR}/module
                DEPENDS chtl
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Packing CMOD module: ${MODULE_NAME}"
            )
            
            # 添加自定义目标
            add_custom_target(pack_${MODULE_NAME}_cmod ALL
                DEPENDS ${CMAKE_BINARY_DIR}/module/${MODULE_NAME}.cmod
            )
        endif()
    endif()
endforeach()

# 添加一个总的打包目标
add_custom_target(pack_all_cmods
    COMMENT "Packing all CMOD modules"
)

# 将所有模块打包目标添加为依赖
foreach(MODULE_DIR ${MODULE_DIRS})
    if(IS_DIRECTORY ${MODULE_DIR})
        get_filename_component(MODULE_NAME ${MODULE_DIR} NAME)
        if(EXISTS "${MODULE_DIR}/info")
            add_dependencies(pack_all_cmods pack_${MODULE_NAME}_cmod)
        endif()
    endif()
endforeach()

# 安装CMOD模块
install(DIRECTORY ${CMAKE_BINARY_DIR}/module/
    DESTINATION share/chtl/module
    FILES_MATCHING PATTERN "*.cmod"
)