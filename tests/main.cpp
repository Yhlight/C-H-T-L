#include <gtest/gtest.h>
#include <iostream>

// 自定义测试环境
class ChtlTestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        std::cout << "CHTL Test Suite Starting..." << std::endl;
        // 初始化测试环境
    }
    
    void TearDown() override {
        std::cout << "CHTL Test Suite Completed." << std::endl;
        // 清理测试环境
    }
};

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);
    
    // 添加全局测试环境
    ::testing::AddGlobalTestEnvironment(new ChtlTestEnvironment);
    
    // 运行所有测试
    return RUN_ALL_TESTS();
}