#include <gtest/gtest.h>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Generator/HtmlGenerator.h"
#include "Node/Custom.h"
#include "Node/Element.h"
#include <sstream>

class SpecializationTest : public ::testing::Test {
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
    
    std::shared_ptr<chtl::Node> parseCode(const std::string& code) {
        auto stream = std::make_unique<std::istringstream>(code);
        lexer->initialize(std::move(stream), "test");
        return parser->parse();
    }
};

// 测试delete操作在自定义元素中的实现
TEST_F(SpecializationTest, DeleteInCustomElement) {
    std::string code = R"(
[Custom] @Element Box {
    div { }
    span { }
    div { }
}

body {
    @Element Box {
        delete span;
        delete div[1];
    }
}
)";
    
    auto ast = parseCode(code);
    ASSERT_NE(ast, nullptr);
    
    // 验证Custom定义被正确解析
    auto custom = ast->getChildByTag("[Custom]");
    ASSERT_NE(custom, nullptr);
    ASSERT_EQ(custom->getChildren().size(), 3); // 3个子元素
    
    // 验证使用时的特例化
    auto body = ast->getChildByTag("body");
    ASSERT_NE(body, nullptr);
    
    auto boxUsage = body->getChildByTag("@Element");
    ASSERT_NE(boxUsage, nullptr);
    
    // 检查delete操作是否被解析
    bool hasDeleteSpan = false;
    bool hasDeleteDiv = false;
    for (const auto& child : boxUsage->getChildren()) {
        if (child->getType() == chtl::NodeType::DELETE) {
            auto deleteTarget = child->getAttribute("target");
            if (std::holds_alternative<std::string>(deleteTarget)) {
                std::string target = std::get<std::string>(deleteTarget);
                if (target == "span") hasDeleteSpan = true;
                if (target == "div[1]") hasDeleteDiv = true;
            }
        }
    }
    
    EXPECT_TRUE(hasDeleteSpan) << "delete span 应该被解析";
    EXPECT_TRUE(hasDeleteDiv) << "delete div[1] 应该被解析";
}

// 测试insert操作在自定义元素中的实现
TEST_F(SpecializationTest, InsertInCustomElement) {
    std::string code = R"(
[Custom] @Element Box {
    div { }
    span { }
}

body {
    @Element Box {
        insert after div[0] {
            div {
                style {
                    width: 100px;
                }
            }
        }
        
        insert before span {
            text { "Inserted text" }
        }
        
        insert at top {
            div { class: header; }
        }
    }
}
)";
    
    auto ast = parseCode(code);
    ASSERT_NE(ast, nullptr);
    
    auto body = ast->getChildByTag("body");
    ASSERT_NE(body, nullptr);
    
    auto boxUsage = body->getChildByTag("@Element");
    ASSERT_NE(boxUsage, nullptr);
    
    // 验证insert操作
    int insertCount = 0;
    for (const auto& child : boxUsage->getChildren()) {
        if (child->getType() == chtl::NodeType::ELEMENT && 
            child->getTagName() == "insert") {
            insertCount++;
            
            // 检查insert的位置属性
            auto position = child->getAttribute("position");
            EXPECT_TRUE(std::holds_alternative<std::string>(position));
        }
    }
    
    EXPECT_EQ(insertCount, 3) << "应该有3个insert操作";
}

// 测试自定义样式组的delete操作
TEST_F(SpecializationTest, DeleteInCustomStyle) {
    std::string code = R"(
[Template] @Style WhiteText {
    color: white;
    font-size: 16px;
    line-height: 1.6;
    border: 1px black solid;
}

[Custom] @Style YellowText {
    @Style WhiteText {
        delete line-height, border;
    }
    color: yellow;
}

div {
    style {
        @Style YellowText {
            delete color;
        }
    }
}
)";
    
    auto ast = parseCode(code);
    ASSERT_NE(ast, nullptr);
    
    // 验证Template被解析
    auto template_ = ast->getChildByTag("[Template]");
    ASSERT_NE(template_, nullptr);
    
    // 验证Custom被解析
    auto custom = ast->getChildByTag("[Custom]");
    ASSERT_NE(custom, nullptr);
    
    // 验证div中的样式特例化
    auto div = ast->getChildByTag("div");
    ASSERT_NE(div, nullptr);
    
    auto style = div->getChildByTag("style");
    ASSERT_NE(style, nullptr);
}

// 测试生成器是否正确处理特例化
TEST_F(SpecializationTest, GeneratorHandlesSpecialization) {
    std::string code = R"(
[Custom] @Element Card {
    div {
        class: card;
        div {
            class: card-header;
            text { "Header" }
        }
        div {
            class: card-body;
            text { "Body" }
        }
    }
}

body {
    @Element Card {
        delete div[0];  -- 删除header
        insert at bottom {
            div {
                class: card-footer;
                text { "Footer" }
            }
        }
    }
}
)";
    
    auto ast = parseCode(code);
    ASSERT_NE(ast, nullptr);
    
    // 生成HTML
    std::stringstream output;
    generator->generate(ast, output);
    std::string html = output.str();
    
    // 验证生成的HTML
    EXPECT_TRUE(html.find("card-body") != std::string::npos) << "应该包含card-body";
    EXPECT_TRUE(html.find("card-footer") != std::string::npos) << "应该包含card-footer";
    EXPECT_TRUE(html.find("card-header") == std::string::npos) << "不应该包含被删除的card-header";
    EXPECT_TRUE(html.find("-- 删除header") != std::string::npos) << "应该保留CHTL的--注释";
}