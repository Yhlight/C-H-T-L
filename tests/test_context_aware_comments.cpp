#include <gtest/gtest.h>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Generator/HtmlGenerator.h"
#include <sstream>

class ContextAwareCommentTest : public ::testing::Test {
protected:
    std::shared_ptr<chtl::StandardLexer> lexer;
    std::shared_ptr<chtl::StandardContext> context;
    std::shared_ptr<chtl::StandardParser> parser;
    std::shared_ptr<chtl::HtmlGenerator> generator;
    
    void SetUp() override {
        lexer = std::make_shared<chtl::StandardLexer>();
        context = std::make_shared<chtl::StandardContext>();
        parser = std::make_shared<chtl::StandardParser>(lexer, context);
        generator = std::make_shared<chtl::HtmlGenerator>();
    }
    
    std::string parseAndGenerate(const std::string& code) {
        auto stream = std::make_unique<std::istringstream>(code);
        lexer->initialize(std::move(stream), "test");
        auto ast = parser->parse();
        
        std::stringstream output;
        generator->generate(ast, output);
        return output.str();
    }
};

// 测试HTML上下文中的注释
TEST_F(ContextAwareCommentTest, CommentInHtmlContext) {
    std::string code = R"(
body {
    -- 这是HTML上下文的注释
    div {
        text { "Hello" }
    }
}
)";
    
    std::string result = parseAndGenerate(code);
    
    // 应该生成HTML注释
    EXPECT_TRUE(result.find("<!-- 这是HTML上下文的注释 -->") != std::string::npos)
        << "HTML上下文应该生成HTML注释";
}

// 测试CSS上下文中的注释
TEST_F(ContextAwareCommentTest, CommentInCssContext) {
    std::string code = R"(
style {
    -- 这是CSS上下文的注释
    body {
        color: red;
    }
}
)";
    
    std::string result = parseAndGenerate(code);
    
    // 应该生成CSS注释
    EXPECT_TRUE(result.find("/* 这是CSS上下文的注释 */") != std::string::npos)
        << "CSS上下文应该生成CSS注释";
}

// 测试局部样式块中的注释
TEST_F(ContextAwareCommentTest, CommentInLocalStyleBlock) {
    std::string code = R"(
div {
    style {
        -- 局部样式块中的注释
        width: 100px;
        height: 200px;
    }
}
)";
    
    std::string result = parseAndGenerate(code);
    
    // 局部样式块中的注释应该生成CSS注释
    EXPECT_TRUE(result.find("/* 局部样式块中的注释 */") != std::string::npos)
        << "局部样式块中应该生成CSS注释";
}

// 测试JavaScript上下文中的注释
TEST_F(ContextAwareCommentTest, CommentInJsContext) {
    std::string code = R"(
script {
    -- 这是JavaScript上下文的注释
    var x = 10;
}
)";
    
    std::string result = parseAndGenerate(code);
    
    // 应该生成JavaScript注释
    EXPECT_TRUE(result.find("// 这是JavaScript上下文的注释") != std::string::npos)
        << "JavaScript上下文应该生成JavaScript单行注释";
}

// 测试Origin块中的注释
TEST_F(ContextAwareCommentTest, CommentInOriginBlocks) {
    std::string code = R"(
[Origin] @Style {
    -- CSS原始代码中的注释
    .class { color: blue; }
}

[Origin] @JavaScript {
    -- JavaScript原始代码中的注释  
    function test() { }
}

[Origin] @Html {
    -- HTML原始代码中的注释
    <p>Test</p>
}
)";
    
    std::string result = parseAndGenerate(code);
    
    // 检查各种Origin块中的注释格式
    EXPECT_TRUE(result.find("/* CSS原始代码中的注释 */") != std::string::npos)
        << "Origin @Style块应该生成CSS注释";
    
    EXPECT_TRUE(result.find("// JavaScript原始代码中的注释") != std::string::npos)
        << "Origin @JavaScript块应该生成JS注释";
    
    EXPECT_TRUE(result.find("<!-- HTML原始代码中的注释 -->") != std::string::npos)
        << "Origin @Html块应该生成HTML注释";
}

// 测试嵌套上下文中的注释
TEST_F(ContextAwareCommentTest, CommentInNestedContext) {
    std::string code = R"(
body {
    -- HTML注释1
    style {
        -- CSS注释
        div {
            color: red;
        }
    }
    -- HTML注释2
    script {
        -- JS注释
        console.log("test");
    }
    -- HTML注释3
}
)";
    
    std::string result = parseAndGenerate(code);
    
    // 验证各个上下文中的注释格式
    EXPECT_TRUE(result.find("<!-- HTML注释1 -->") != std::string::npos);
    EXPECT_TRUE(result.find("/* CSS注释 */") != std::string::npos);
    EXPECT_TRUE(result.find("<!-- HTML注释2 -->") != std::string::npos);
    EXPECT_TRUE(result.find("// JS注释") != std::string::npos);
    EXPECT_TRUE(result.find("<!-- HTML注释3 -->") != std::string::npos);
}