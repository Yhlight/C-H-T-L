# CHTL 测试套件
cmake_minimum_required(VERSION 3.16)

# 查找 Google Test
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    # 如果系统没有安装 GTest，使用 FetchContent 下载
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
endif()

# 启用测试
enable_testing()

# 包含目录
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 收集测试源文件
file(GLOB_RECURSE TEST_SOURCES 
    "unit/*.cpp"
    "integration/*.cpp"
)

# 创建测试可执行文件
add_executable(chtl_tests
    ${TEST_SOURCES}
    main.cpp
)

# 链接库
target_link_libraries(chtl_tests
    chtl_lib  # CHTL 库
    GTest::gtest
    GTest::gtest_main
    pthread
)

# 添加测试
add_test(NAME chtl_unit_tests COMMAND chtl_tests)

# 自定义测试目标
add_custom_target(test
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS chtl_tests
)