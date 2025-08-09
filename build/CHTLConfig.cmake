# CHTLConfig.cmake - CHTL CMake configuration file



set(CHTL_VERSION 1.0.0)
set(CHTL_VERSION_MAJOR 1)
set(CHTL_VERSION_MINOR 0)
set(CHTL_VERSION_PATCH 0)

include("${CMAKE_CURRENT_LIST_DIR}/CHTLTargets.cmake")

# 提供CHTL::chtl_core和CHTL::chtl_shared目标
set(CHTL_LIBRARIES CHTL::chtl_core)
set(CHTL_INCLUDE_DIRS "/usr/local/include/chtl")

# 检查组件
set(CHTL_FOUND TRUE)
foreach(component ${CHTL_FIND_COMPONENTS})
    if(component STREQUAL "shared")
        if(TARGET CHTL::chtl_shared)
            set(CHTL_shared_FOUND TRUE)
        else()
            set(CHTL_shared_FOUND FALSE)
            if(CHTL_FIND_REQUIRED_shared)
                set(CHTL_FOUND FALSE)
            endif()
        endif()
    endif()
endforeach()

check_required_components(CHTL)
