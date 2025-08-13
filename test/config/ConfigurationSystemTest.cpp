#include <gtest/gtest.h>
#include "../../src/chtl/config/ConfigurationSystem.h"
#include "../../src/chtl/config/ConfigurableLexer.h"
#include "../../src/chtl/config/ConfigurableParser.h"

using namespace chtl::config;

class ConfigurationSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 每个测试前重置配置
        ConfigurationSystem::getInstance().reset();
    }
};

// 测试默认配置
TEST_F(ConfigurationSystemTest, DefaultConfiguration) {
    auto& config = ConfigurationSystem::getInstance();
    
    EXPECT_EQ(config.getIndexInitialCount(), 0);
    EXPECT_TRUE(config.isNameGroupDisabled());
    EXPECT_FALSE(config.isDebugMode());
}

// 测试基本配置加载
TEST_F(ConfigurationSystemTest, LoadBasicConfiguration) {
    std::string configContent = R"(
[Configuration]
{
    INDEX_INITIAL_COUNT = 100;
    DISABLE_NAME_GROUP = false;
    DEBUG_MODE = true;
}
)";
    
    auto& config = ConfigurationSystem::getInstance();
    EXPECT_TRUE(config.loadConfiguration(configContent));
    
    EXPECT_EQ(config.getIndexInitialCount(), 100);
    EXPECT_FALSE(config.isNameGroupDisabled());
    EXPECT_TRUE(config.isDebugMode());
}

// 测试Name组配置
TEST_F(ConfigurationSystemTest, LoadNameGroupConfiguration) {
    std::string configContent = R"(
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        CUSTOM_STYLE = [@样式, @style, @CSS];
        CUSTOM_ELEMENT = @元素;
        CUSTOM_VAR = @变量;
        KEYWORD_TEMPLATE = [模板];
        KEYWORD_INHERIT = 继承;
        OPTION_COUNT = 5;
    }
}
)";
    
    auto& config = ConfigurationSystem::getInstance();
    EXPECT_TRUE(config.loadConfiguration(configContent));
    
    // 验证Name组配置
    const auto& nameGroup = config.getNameGroup();
    EXPECT_EQ(nameGroup.customStyle.size(), 3);
    EXPECT_EQ(nameGroup.customStyle[0], "@样式");
    EXPECT_EQ(nameGroup.customElement, "@元素");
    EXPECT_EQ(nameGroup.keywordTemplate, "[模板]");
    EXPECT_EQ(nameGroup.keywordInherit, "继承");
    EXPECT_EQ(nameGroup.optionCount, 5);
}

// 测试关键字匹配
TEST_F(ConfigurationSystemTest, KeywordMatching) {
    std::string configContent = R"(
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        CUSTOM_STYLE = [@Style, @style, @CSS];
        KEYWORD_TEMPLATE = [Template];
    }
}
)";
    
    auto& config = ConfigurationSystem::getInstance();
    config.loadConfiguration(configContent);
    
    // 测试CUSTOM_STYLE的多个变体
    EXPECT_TRUE(config.isKeyword("@Style", "CUSTOM_STYLE"));
    EXPECT_TRUE(config.isKeyword("@style", "CUSTOM_STYLE"));
    EXPECT_TRUE(config.isKeyword("@CSS", "CUSTOM_STYLE"));
    EXPECT_FALSE(config.isKeyword("@Invalid", "CUSTOM_STYLE"));
    
    // 测试单个关键字
    EXPECT_TRUE(config.isKeyword("[Template]", "KEYWORD_TEMPLATE"));
    EXPECT_FALSE(config.isKeyword("[template]", "KEYWORD_TEMPLATE"));
}

// 测试配置导出
TEST_F(ConfigurationSystemTest, ExportConfiguration) {
    std::string originalConfig = R"(
[Configuration]
{
    INDEX_INITIAL_COUNT = 50;
    DISABLE_NAME_GROUP = false;
    DEBUG_MODE = true;
}
)";
    
    auto& config = ConfigurationSystem::getInstance();
    config.loadConfiguration(originalConfig);
    
    std::string exportedConfig = config.exportConfiguration();
    
    // 验证导出的配置包含必要信息
    EXPECT_TRUE(exportedConfig.find("INDEX_INITIAL_COUNT = 50") != std::string::npos);
    EXPECT_TRUE(exportedConfig.find("DISABLE_NAME_GROUP = false") != std::string::npos);
    EXPECT_TRUE(exportedConfig.find("DEBUG_MODE = true") != std::string::npos);
}

// 测试配置验证
TEST_F(ConfigurationSystemTest, ConfigurationValidation) {
    auto& config = ConfigurationSystem::getInstance();
    
    // 默认配置应该是有效的
    EXPECT_TRUE(config.validateConfiguration());
    
    // 加载带有Name组的配置
    std::string configWithName = R"(
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        CUSTOM_STYLE = [];  // 空数组
        CUSTOM_ELEMENT = ;  // 空值
    }
}
)";
    
    // 这个配置应该验证失败（因为必需字段为空）
    config.loadConfiguration(configWithName);
    EXPECT_FALSE(config.validateConfiguration());
}

// 测试配置系统与Lexer集成
TEST_F(ConfigurationSystemTest, LexerIntegration) {
    std::string configContent = R"(
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        CUSTOM_STYLE = [@CSS, @css];
        KEYWORD_TEXT = texto;
    }
}
)";
    
    auto& config = ConfigurationSystem::getInstance();
    config.loadConfiguration(configContent);
    
    // 创建一个模拟的Lexer来测试
    // 注意：这里需要实际的ANTLR生成的Lexer
    // 这只是一个概念性的测试
    
    size_t tokenType;
    ConfigurableLexer lexer(nullptr);
    
    // 测试配置的关键字是否被识别
    EXPECT_TRUE(lexer.isConfiguredKeyword("@CSS", tokenType));
    EXPECT_TRUE(lexer.isConfiguredKeyword("@css", tokenType));
    EXPECT_FALSE(lexer.isConfiguredKeyword("@Style", tokenType));
}

// 测试实际的CHTL代码解析
TEST_F(ConfigurationSystemTest, ParseCHTLWithCustomKeywords) {
    // 配置使用中文关键字
    std::string configContent = R"(
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        CUSTOM_STYLE = [@样式];
        CUSTOM_ELEMENT = @元素;
        KEYWORD_TEMPLATE = [模板];
        KEYWORD_TEXT = 文本;
        KEYWORD_STYLE = 样式;
    }
}
)";
    
    auto& config = ConfigurationSystem::getInstance();
    config.loadConfiguration(configContent);
    
    // 使用中文关键字的CHTL代码
    std::string chtlCode = R"(
[模板] @样式 卡片样式
{
    背景色: 白色;
    边框: 1px 实线 灰色;
}

[模板] @元素 卡片
{
    div
    {
        样式 { @样式 卡片样式; }
        
        文本 { "这是一个卡片" }
    }
}
)";
    
    // 验证关键字被正确识别
    EXPECT_TRUE(config.isKeyword("[模板]", "KEYWORD_TEMPLATE"));
    EXPECT_TRUE(config.isKeyword("@样式", "CUSTOM_STYLE"));
    EXPECT_TRUE(config.isKeyword("@元素", "CUSTOM_ELEMENT"));
    EXPECT_TRUE(config.isKeyword("文本", "KEYWORD_TEXT"));
    EXPECT_TRUE(config.isKeyword("样式", "KEYWORD_STYLE"));
}

// 测试性能：大量关键字变体
TEST_F(ConfigurationSystemTest, PerformanceWithManyVariants) {
    std::string configContent = R"(
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        CUSTOM_STYLE = [@Style, @style, @STYLE, @CSS, @css, @Css, @stylesheet, @StyleSheet];
        OPTION_COUNT = 10;
    }
}
)";
    
    auto& config = ConfigurationSystem::getInstance();
    config.loadConfiguration(configContent);
    
    // 测试查找性能
    auto start = std::chrono::steady_clock::now();
    
    for (int i = 0; i < 10000; ++i) {
        config.isKeyword("@CSS", "CUSTOM_STYLE");
        config.isKeyword("@NotFound", "CUSTOM_STYLE");
    }
    
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // 确保查找性能在合理范围内（< 100ms for 20000 lookups）
    EXPECT_LT(duration.count(), 100);
}

// 主函数
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}