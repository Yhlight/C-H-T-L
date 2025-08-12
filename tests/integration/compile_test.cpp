#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "Compiler/Compiler.h"

namespace fs = std::filesystem;
using namespace chtl;

class CompileTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 创建临时目录
        testDir_ = fs::temp_directory_path() / "chtl_test";
        fs::create_directories(testDir_);
    }
    
    void TearDown() override {
        // 清理临时目录
        fs::remove_all(testDir_);
    }
    
    void writeFile(const std::string& filename, const std::string& content) {
        std::ofstream file(testDir_ / filename);
        file << content;
    }
    
    std::string readFile(const std::string& filename) {
        std::ifstream file(testDir_ / filename);
        return std::string(std::istreambuf_iterator<char>(file),
                          std::istreambuf_iterator<char>());
    }
    
    fs::path testDir_;
};

TEST_F(CompileTest, CompilesSimpleHtml) {
    std::string input = R"(
        html {
            head {
                title { text { "Test Page" } }
            }
            body {
                h1 { text { "Hello CHTL!" } }
                p { 
                    class: "content";
                    text { "This is a test." }
                }
            }
        }
    )";
    
    writeFile("test.chtl", input);
    
    Compiler compiler;
    compiler.setInputFile(testDir_ / "test.chtl");
    compiler.setOutputDir(testDir_ / "output");
    
    ASSERT_TRUE(compiler.compile());
    
    // 验证输出文件
    EXPECT_TRUE(fs::exists(testDir_ / "output" / "index.html"));
    
    auto html = readFile("output/index.html");
    EXPECT_NE(html.find("<title>Test Page</title>"), std::string::npos);
    EXPECT_NE(html.find("<h1>Hello CHTL!</h1>"), std::string::npos);
    EXPECT_NE(html.find("class=\"content\""), std::string::npos);
}

TEST_F(CompileTest, CompilesWithStyles) {
    std::string input = R"(
        html {
            head {
                style {
                    body {
                        margin: 0;
                        font-family: Arial, sans-serif;
                    }
                    .container {
                        max-width: 1200px;
                        margin: 0 auto;
                    }
                }
            }
            body {
                div {
                    class: "container";
                    h1 { text { "Styled Page" } }
                }
            }
        }
    )";
    
    writeFile("styled.chtl", input);
    
    Compiler compiler;
    compiler.setInputFile(testDir_ / "styled.chtl");
    compiler.setOutputDir(testDir_ / "output");
    
    ASSERT_TRUE(compiler.compile());
    
    // 验证CSS文件生成
    EXPECT_TRUE(fs::exists(testDir_ / "output" / "styles.css"));
    
    auto css = readFile("output/styles.css");
    EXPECT_NE(css.find("margin: 0"), std::string::npos);
    EXPECT_NE(css.find(".container"), std::string::npos);
}

TEST_F(CompileTest, CompilesWithScripts) {
    std::string input = R"(
        html {
            body {
                button {
                    id: "myButton";
                    text { "Click Me" }
                    
                    script {
                        {{&}}.addEventListener('click', function() {
                            alert('Button clicked!');
                        });
                    }
                }
                
                script {
                    console.log('Page loaded');
                }
            }
        }
    )";
    
    writeFile("scripted.chtl", input);
    
    Compiler compiler;
    compiler.setInputFile(testDir_ / "scripted.chtl");
    compiler.setOutputDir(testDir_ / "output");
    
    ASSERT_TRUE(compiler.compile());
    
    // 验证JS文件生成
    EXPECT_TRUE(fs::exists(testDir_ / "output" / "app.js"));
    
    auto js = readFile("output/app.js");
    EXPECT_NE(js.find("addEventListener"), std::string::npos);
    EXPECT_NE(js.find("console.log"), std::string::npos);
}

TEST_F(CompileTest, HandlesTemplates) {
    std::string input = R"(
        [Template] @Element Card {
            div {
                class: "card";
                slot;
            }
        }
        
        html {
            body {
                @Element Card {
                    h2 { text { "Card Title" } }
                    p { text { "Card content" } }
                }
            }
        }
    )";
    
    writeFile("templates.chtl", input);
    
    Compiler compiler;
    compiler.setInputFile(testDir_ / "templates.chtl");
    compiler.setOutputDir(testDir_ / "output");
    
    ASSERT_TRUE(compiler.compile());
    
    auto html = readFile("output/index.html");
    EXPECT_NE(html.find("class=\"card\""), std::string::npos);
    EXPECT_NE(html.find("Card Title"), std::string::npos);
}

TEST_F(CompileTest, HandlesImports) {
    // 创建被导入的文件
    writeFile("components/Button.chtl", R"(
        [Template] @Element Button {
            button {
                class: "btn";
                slot;
            }
        }
    )");
    
    writeFile("main.chtl", R"(
        [Import] @Element Button from "./components/Button";
        
        html {
            body {
                @Element Button {
                    text { "Click me" }
                }
            }
        }
    )");
    
    Compiler compiler;
    compiler.setInputFile(testDir_ / "main.chtl");
    compiler.setOutputDir(testDir_ / "output");
    
    ASSERT_TRUE(compiler.compile());
    
    auto html = readFile("output/index.html");
    EXPECT_NE(html.find("class=\"btn\""), std::string::npos);
    EXPECT_NE(html.find("Click me"), std::string::npos);
}

TEST_F(CompileTest, ReportsCompileErrors) {
    std::string input = R"(
        html {
            body {
                div {  // Missing closing brace
                    text { "Error" }
            }
        }
    )";
    
    writeFile("error.chtl", input);
    
    Compiler compiler;
    compiler.setInputFile(testDir_ / "error.chtl");
    compiler.setOutputDir(testDir_ / "output");
    
    EXPECT_FALSE(compiler.compile());
    EXPECT_GT(compiler.getErrors().size(), 0);
}