#include <gtest/gtest.h>
#include "Lexer/StandardLexer.h"
#include "State/ChtlState.h"
#include "Context/StandardContext.h"

using namespace chtl;

class LexerTest : public ::testing::Test {
protected:
    void SetUp() override {
        context_ = std::make_shared<StandardContext>();
    }
    
    std::shared_ptr<Context> context_;
};

TEST_F(LexerTest, TokenizesSimpleElement) {
    std::string input = "div { }";
    StandardLexer lexer(input, context_);
    
    auto tokens = lexer.tokenize();
    
    ASSERT_GE(tokens.size(), 3);
    EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[0].value, "div");
    EXPECT_EQ(tokens[1].type, TokenType::LEFT_BRACE);
    EXPECT_EQ(tokens[2].type, TokenType::RIGHT_BRACE);
}

TEST_F(LexerTest, TokenizesAttributes) {
    std::string input = "div { id: \"test\"; class: \"btn\"; }";
    StandardLexer lexer(input, context_);
    
    auto tokens = lexer.tokenize();
    
    // 验证属性token
    auto it = std::find_if(tokens.begin(), tokens.end(), 
        [](const Token& t) { return t.value == "id"; });
    EXPECT_NE(it, tokens.end());
    
    it = std::find_if(tokens.begin(), tokens.end(), 
        [](const Token& t) { return t.value == "test"; });
    EXPECT_NE(it, tokens.end());
}

TEST_F(LexerTest, HandlesComments) {
    std::string input = "// This is a comment\ndiv { }";
    StandardLexer lexer(input, context_);
    
    auto tokens = lexer.tokenize();
    
    // 注释应该被跳过
    EXPECT_EQ(tokens[0].value, "div");
}

TEST_F(LexerTest, HandlesMultilineComments) {
    std::string input = "/* Multi\n   line\n   comment */\ndiv { }";
    StandardLexer lexer(input, context_);
    
    auto tokens = lexer.tokenize();
    
    EXPECT_EQ(tokens[0].value, "div");
}

TEST_F(LexerTest, TokenizesNumbers) {
    std::string input = "width: 100; height: 50.5;";
    StandardLexer lexer(input, context_);
    
    auto tokens = lexer.tokenize();
    
    auto it = std::find_if(tokens.begin(), tokens.end(), 
        [](const Token& t) { return t.value == "100"; });
    EXPECT_NE(it, tokens.end());
    EXPECT_EQ(it->type, TokenType::NUMBER);
    
    it = std::find_if(tokens.begin(), tokens.end(), 
        [](const Token& t) { return t.value == "50.5"; });
    EXPECT_NE(it, tokens.end());
    EXPECT_EQ(it->type, TokenType::NUMBER);
}

TEST_F(LexerTest, HandlesChtlJsSyntax) {
    std::string input = "{{#myId}}.style.color = 'red';";
    StandardLexer lexer(input, context_);
    
    auto tokens = lexer.tokenize();
    
    // 应该识别 CHTL-JS 语法
    auto it = std::find_if(tokens.begin(), tokens.end(), 
        [](const Token& t) { return t.type == TokenType::CHTL_JS_START; });
    EXPECT_NE(it, tokens.end());
}

TEST_F(LexerTest, ReportsInvalidCharacters) {
    std::string input = "div { @#$ }";
    StandardLexer lexer(input, context_);
    
    // 应该能处理无效字符而不崩溃
    EXPECT_NO_THROW(lexer.tokenize());
}