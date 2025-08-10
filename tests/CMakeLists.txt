# 测试配置
set(TEST_SOURCES
    test_lexer.cpp
    test_parser.cpp
    test_template.cpp
    test_custom.cpp
    test_config.cpp
    test_import_namespace.cpp
    test_operate_origin.cpp
    test_chtl_js.cpp
    test_css_analyzer.cpp
    test_js_analyzer.cpp
    test_node.cpp
    test_chtl_nodes.cpp
    test_bridge_scanner.cpp
    test_comment.cpp
    test_simple_parser.cpp
    test_html_parsing.cpp
    test_style_parsing.cpp
    test_style_tokens.cpp
    test_simple_style.cpp
    test_template_parsing.cpp
    test_specialization.cpp
)

# 为每个测试文件创建单独的可执行文件
foreach(test_source ${TEST_SOURCES})
    # 获取测试名称（去掉.cpp扩展名）
    string(REPLACE ".cpp" "" test_name ${test_source})
    
    # 检查文件是否存在
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${test_source})
        # 创建测试可执行文件
        add_executable(${test_name} ${test_source})
        
        # 链接核心库
        target_link_libraries(${test_name} chtl_core)
        
        # 添加到CTest
        add_test(NAME ${test_name} COMMAND ${test_name})
        
        # 设置测试属性
        set_tests_properties(${test_name} PROPERTIES
            TIMEOUT 30
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )
    endif()
endforeach()

# 添加集成测试
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/integration_tests.cpp)
    add_executable(integration_tests integration_tests.cpp)
    target_link_libraries(integration_tests chtl_core)
    add_test(NAME integration_tests COMMAND integration_tests)
endif()

# 添加性能测试（可选）
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/performance_tests.cpp)
    add_executable(performance_tests performance_tests.cpp)
    target_link_libraries(performance_tests chtl_core)
    # 性能测试不加入常规测试
endif()

# 自定义测试目标
add_custom_target(check 
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS ${TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 测试数据目录
file(COPY ${CMAKE_SOURCE_DIR}/examples DESTINATION ${CMAKE_BINARY_DIR}/test_data)

# 状态信息
message(STATUS "Tests configured: ${TEST_SOURCES}")