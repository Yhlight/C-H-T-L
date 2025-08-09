# Module 官方CMOD模块源代码
# 此目录用于存放官方提供的CMOD模块
# 每个子目录是一个独立的CMOD模块

# 扫描所有子目录
file(GLOB MODULE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/*")

foreach(MODULE_DIR ${MODULE_DIRS})
    if(IS_DIRECTORY ${MODULE_DIR})
        get_filename_component(MODULE_NAME ${MODULE_DIR} NAME)
        
        # 如果子目录有CMakeLists.txt，添加它
        if(EXISTS "${MODULE_DIR}/CMakeLists.txt")
            add_subdirectory(${MODULE_NAME})
        endif()
    endif()
endforeach()

# 安装模块到share目录
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION share/chtl/modules
    PATTERN "CMakeLists.txt" EXCLUDE
    PATTERN "*.cpp" EXCLUDE
    PATTERN "*.h" EXCLUDE
)