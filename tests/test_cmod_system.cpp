#include <gtest/gtest.h>
#include "CmodSystem/CmodValidator.h"
#include "CmodSystem/CmodExtractor.h"
#include "CmodSystem/CmodPackager.h"
#include "CmodSystem/CmodRegistry.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class CmodSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 创建测试目录结构
        testDir = "test_cmod_module";
        fs::create_directories(testDir + "/src");
        fs::create_directories(testDir + "/info");
        
        // 创建测试文件
        createTestModule();
    }
    
    void TearDown() override {
        // 清理测试目录
        fs::remove_all(testDir);
    }
    
    void createTestModule() {
        // 创建info文件
        std::ofstream infoFile(testDir + "/info/test_cmod_module.chtl");
        infoFile << "[Info]\n";
        infoFile << "{\n";
        infoFile << "    name = \"test_module\";\n";
        infoFile << "    version = \"1.0.0\";\n";
        infoFile << "    description = \"Test CMOD module\";\n";
        infoFile << "    author = \"Test Author\";\n";
        infoFile << "    license = \"MIT\";\n";
        infoFile << "    category = \"test\";\n";
        infoFile << "}\n\n";
        infoFile << "[Export]\n";
        infoFile << "{\n";
        infoFile << "    @Style TestStyle;\n";
        infoFile << "    @Element TestElement;\n";
        infoFile << "}\n";
        infoFile.close();
        
        // 创建主模块文件
        std::ofstream mainFile(testDir + "/src/test_cmod_module.chtl");
        mainFile << "[Template] @Style TestStyle {\n";
        mainFile << "    color: $color;\n";
        mainFile << "    font-size: $size;\n";
        mainFile << "}\n\n";
        mainFile << "[Template] @Element TestElement {\n";
        mainFile << "    <div class=\"test\">\n";
        mainFile << "        @content\n";
        mainFile << "    </div>\n";
        mainFile << "}\n";
        mainFile.close();
    }
    
    std::string testDir;
};

// 测试CMOD验证器
TEST_F(CmodSystemTest, ValidatorBasicTest) {
    chtl::CmodValidator validator;
    
    // 验证有效的模块结构
    auto result = validator.validateStructure(testDir);
    EXPECT_TRUE(result.isValid);
    EXPECT_TRUE(result.errors.empty());
}

TEST_F(CmodSystemTest, ValidatorInvalidStructureTest) {
    chtl::CmodValidator validator;
    
    // 验证不存在的目录
    auto result = validator.validateStructure("non_existent_dir");
    EXPECT_FALSE(result.isValid);
    EXPECT_FALSE(result.errors.empty());
}

// 测试CMOD信息提取器
TEST_F(CmodSystemTest, ExtractorBasicTest) {
    chtl::CmodExtractor extractor;
    
    // 从目录提取信息
    auto info = extractor.extractFromDirectory(testDir);
    EXPECT_NE(info, nullptr);
    EXPECT_EQ(info->name, "test_cmod_module");
}

// 测试版本解析
TEST_F(CmodSystemTest, VersionParsingTest) {
    chtl::CmodValidator validator;
    
    // 测试有效版本
    auto result = validator.validateVersion("1.0.0", "0.9.0", "2.0.0");
    EXPECT_TRUE(result.isValid);
    
    // 测试版本过低
    result = validator.validateVersion("0.8.0", "0.9.0", "2.0.0");
    EXPECT_FALSE(result.isValid);
    
    // 测试版本过高
    result = validator.validateVersion("2.1.0", "0.9.0", "2.0.0");
    EXPECT_FALSE(result.isValid);
}

// 测试CMOD打包器
TEST_F(CmodSystemTest, PackagerBasicTest) {
    chtl::CmodPackager packager;
    
    // 打包模块
    chtl::CmodPackager::PackageOptions options;
    options.outputPath = testDir + ".cmod";
    
    auto result = packager.package(testDir, options);
    EXPECT_TRUE(result.success);
    EXPECT_FALSE(result.packagePath.empty());
    
    // 清理生成的包文件
    fs::remove(result.packagePath);
}

// 测试CMOD注册表
TEST_F(CmodSystemTest, RegistryBasicTest) {
    chtl::CmodRegistry registry;
    
    // 初始化注册表
    EXPECT_TRUE(registry.initialize(testDir + "/registry.json"));
    
    // 注册模块
    chtl::CmodInfo info;
    info.name = "test_module";
    info.version = "1.0.0";
    
    EXPECT_TRUE(registry.registerModule(info, testDir));
    
    // 查询模块
    EXPECT_TRUE(registry.hasModule("test_module"));
    
    auto module = registry.getModule("test_module");
    EXPECT_NE(module, nullptr);
    EXPECT_EQ(module->info.name, "test_module");
    
    // 保存注册表
    EXPECT_TRUE(registry.save());
}

// 测试依赖解析
TEST_F(CmodSystemTest, DependencyParsingTest) {
    chtl::CmodValidator validator;
    
    // 测试有效的依赖字符串
    auto result = validator.validateDependencies("module1@1.0.0, module2@2.0.0");
    EXPECT_TRUE(result.isValid);
    
    // 测试无效版本的依赖
    result = validator.validateDependencies("module1@invalid_version");
    EXPECT_FALSE(result.isValid);
}

// 测试CMOD结构验证
TEST_F(CmodSystemTest, StructureValidationTest) {
    chtl::CmodStructure structure;
    structure.rootPath = testDir;
    structure.srcPath = testDir + "/src";
    structure.infoPath = testDir + "/info";
    structure.mainModuleFile = testDir + "/src/test_cmod_module.chtl";
    structure.infoFile = testDir + "/info/test_cmod_module.chtl";
    
    EXPECT_TRUE(structure.isValid());
    EXPECT_EQ(structure.getModuleName(), "test_cmod_module");
}

// 测试子模块
TEST_F(CmodSystemTest, SubmoduleTest) {
    // 创建子模块目录
    std::string submoduleDir = testDir + "/src/submodule";
    fs::create_directories(submoduleDir + "/src");
    fs::create_directories(submoduleDir + "/info");
    
    // 创建子模块文件
    std::ofstream subInfoFile(submoduleDir + "/info/submodule.chtl");
    subInfoFile << "[Info]\n{\n    name = \"submodule\";\n    version = \"1.0.0\";\n}\n";
    subInfoFile.close();
    
    std::ofstream subMainFile(submoduleDir + "/src/submodule.chtl");
    subMainFile << "-- Submodule content\n";
    subMainFile.close();
    
    // 验证包含子模块的结构
    chtl::CmodValidator validator;
    auto result = validator.validateStructure(testDir);
    EXPECT_TRUE(result.isValid);
    
    // 提取子模块信息
    chtl::CmodExtractor extractor;
    auto submodules = extractor.extractSubmodules(testDir);
    EXPECT_EQ(submodules.size(), 1);
    if (!submodules.empty()) {
        EXPECT_EQ(submodules[0]->name, "submodule");
    }
}