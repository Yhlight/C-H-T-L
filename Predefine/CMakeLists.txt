# Predefine 预定义模块
set(PREDEFINE_SOURCES
    Registry.cpp
    PredefinedCustomElements.cpp
    PredefinedCustomStyles.cpp
    PredefinedCustomVariables.cpp
    PredefinedTemplateElements.cpp
    PredefinedTemplateStyles.cpp
    PredefinedTemplateVariables.cpp
)

set(PREDEFINE_HEADERS
    Registry.h
    PredefinedCustomElements.h
    PredefinedCustomStyles.h
    PredefinedCustomVariables.h
    PredefinedTemplateElements.h
    PredefinedTemplateStyles.h
    PredefinedTemplateVariables.h
)

# 创建静态库
add_library(chtl_predefine STATIC ${PREDEFINE_SOURCES})

# 包含目录
target_include_directories(chtl_predefine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/chtl>
)

# 链接依赖
target_link_libraries(chtl_predefine
    PUBLIC
        chtl_node
)

# 安装规则
install(TARGETS chtl_predefine
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES ${PREDEFINE_HEADERS}
    DESTINATION include/chtl/Predefine
)