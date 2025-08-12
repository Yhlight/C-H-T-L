add_executable(chtl
    main.cpp
)

target_link_libraries(chtl
    chtl-core
    chtl-parser
    chtl-generator
    antlr4-runtime
)

# 设置安装
install(TARGETS chtl DESTINATION bin)