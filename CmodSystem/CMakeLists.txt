# CmodSystem CMOD系统模块
set(CMOD_SOURCES
    CmodPackager.cpp
    CmodValidator.cpp
    CmodExtractor.cpp
    CmodRegistry.cpp
)

set(CMOD_HEADERS
    CmodPackager.h
    CmodValidator.h
    CmodExtractor.h
    CmodRegistry.h
)

# 创建静态库
add_library(chtl_cmod_system STATIC ${CMOD_SOURCES})

# 包含目录
target_include_directories(chtl_cmod_system
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/chtl>
)

# 链接依赖
target_link_libraries(chtl_cmod_system
    PUBLIC
        chtl_parser
        chtl_generator
)

# 安装规则
install(TARGETS chtl_cmod_system
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES ${CMOD_HEADERS}
    DESTINATION include/chtl/CmodSystem
)