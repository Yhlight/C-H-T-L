# src/CMakeLists.txt

# 添加CHTL编译器库
add_subdirectory(chtl)
add_subdirectory(chtljs)

# 检查main.cpp是否存在
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    # 创建主编译器可执行文件
    add_executable(chtlc main.cpp)
    
    # 链接库
    target_link_libraries(chtlc PRIVATE
        chtl_core
        chtl_parser
        chtljs_core
    )
    
    # 安装可执行文件
    install(TARGETS chtlc
        RUNTIME DESTINATION bin
    )
else()
    message(STATUS "main.cpp not found, skipping chtlc executable")
    
    # 创建一个占位可执行文件用于测试
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/chtlc_placeholder.cpp"
        "#include <iostream>\n"
        "int main() {\n"
        "    std::cout << \"CHTL Compiler Placeholder\\n\";\n"
        "    std::cout << \"Real implementation pending...\\n\";\n"
        "    return 0;\n"
        "}\n"
    )
    
    add_executable(chtlc "${CMAKE_CURRENT_BINARY_DIR}/chtlc_placeholder.cpp")
    
    install(TARGETS chtlc
        RUNTIME DESTINATION bin
    )
endif()