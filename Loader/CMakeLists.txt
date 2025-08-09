# Loader 加载器模块
set(LOADER_SOURCES
    FileLoader.cpp
    ModuleLoader.cpp
    CmodLoader.cpp
)

set(LOADER_HEADERS
    FileLoader.h
    ModuleLoader.h
    CmodLoader.h
)

# 创建静态库
add_library(chtl_loader STATIC ${LOADER_SOURCES})

# 包含目录
target_include_directories(chtl_loader
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/chtl>
)

# 链接依赖
target_link_libraries(chtl_loader
    PUBLIC
        chtl_parser
        chtl_cmod_system
)

# 安装规则
install(TARGETS chtl_loader
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES ${LOADER_HEADERS}
    DESTINATION include/chtl/Loader
)