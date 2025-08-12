#include <gtest/gtest.h>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/EnhancedContext.h"

using namespace chtl;

class ParserTest : public ::testing::Test {
protected:
    std::shared_ptr<Node> parse(const std::string& input) {
        auto context = std::make_shared<EnhancedContext>();
        StandardLexer lexer(input, context);
        auto tokens = lexer.tokenize();
        
        StandardParser parser(tokens, context);
        return parser.parse();
    }
};

TEST_F(ParserTest, ParsesSimpleElement) {
    auto ast = parse("div { }");
    
    ASSERT_NE(ast, nullptr);
    ASSERT_EQ(ast->getType(), NodeType::DOCUMENT);
    ASSERT_GT(ast->getChildren().size(), 0);
    
    auto firstChild = ast->getChildren()[0];
    EXPECT_EQ(firstChild->getType(), NodeType::ELEMENT);
    
    auto element = std::static_pointer_cast<Element>(firstChild);
    EXPECT_EQ(element->getTagName(), "div");
}

TEST_F(ParserTest, ParsesNestedElements) {
    auto ast = parse(R"(
        div {
            p {
                text { "Hello" }
            }
        }
    )");
    
    ASSERT_NE(ast, nullptr);
    auto div = ast->getChildren()[0];
    ASSERT_GT(div->getChildren().size(), 0);
    
    auto p = div->getChildren()[0];
    EXPECT_EQ(p->getType(), NodeType::ELEMENT);
    EXPECT_EQ(std::static_pointer_cast<Element>(p)->getTagName(), "p");
    
    ASSERT_GT(p->getChildren().size(), 0);
    auto textNode = p->getChildren()[0];
    EXPECT_EQ(textNode->getType(), NodeType::TEXT);
}

TEST_F(ParserTest, ParsesAttributes) {
    auto ast = parse(R"(
        div {
            id: "myDiv";
            class: "container active";
            data-value: 42;
        }
    )");
    
    auto div = std::static_pointer_cast<Element>(ast->getChildren()[0]);
    
    auto id = div->getAttribute("id");
    EXPECT_TRUE(std::holds_alternative<std::string>(id));
    EXPECT_EQ(std::get<std::string>(id), "myDiv");
    
    auto className = div->getAttribute("class");
    EXPECT_TRUE(std::holds_alternative<std::string>(className));
    EXPECT_EQ(std::get<std::string>(className), "container active");
}

TEST_F(ParserTest, ParsesTemplates) {
    auto ast = parse(R"(
        [Template] @Element Button {
            button {
                class: "btn";
                text { "Click me" }
            }
        }
    )");
    
    ASSERT_GT(ast->getChildren().size(), 0);
    auto templateNode = ast->getChildren()[0];
    EXPECT_EQ(templateNode->getType(), NodeType::TEMPLATE);
    
    auto tmpl = std::static_pointer_cast<Template>(templateNode);
    EXPECT_EQ(tmpl->getName(), "Button");
    EXPECT_EQ(tmpl->getTemplateType(), "@Element");
}

TEST_F(ParserTest, ParsesCustomComponents) {
    auto ast = parse(R"(
        [Custom] @Element Card {
            class: "card";
            padding: "20px";
        }
    )");
    
    ASSERT_GT(ast->getChildren().size(), 0);
    auto customNode = ast->getChildren()[0];
    EXPECT_EQ(customNode->getType(), NodeType::CUSTOM);
}

TEST_F(ParserTest, ParsesImports) {
    auto ast = parse(R"(
        [Import] @Element Button from "./components/Button";
        [Import] @Style theme from "./styles/theme";
    )");
    
    EXPECT_EQ(ast->getChildren().size(), 2);
    
    for (const auto& child : ast->getChildren()) {
        EXPECT_EQ(child->getType(), NodeType::IMPORT);
    }
}

TEST_F(ParserTest, HandlesInvalidSyntax) {
    // Missing closing brace
    EXPECT_THROW(parse("div { id: \"test\""), std::exception);
    
    // Missing semicolon after attribute
    // 根据实现，这可能是警告而不是错误
    auto ast = parse("div { id: \"test\" class: \"btn\"; }");
    EXPECT_NE(ast, nullptr);  // 应该能恢复
}

TEST_F(ParserTest, ParsesStyleBlocks) {
    auto ast = parse(R"(
        div {
            style {
                color: red;
                font-size: 16px;
            }
        }
    )");
    
    auto div = ast->getChildren()[0];
    ASSERT_GT(div->getChildren().size(), 0);
    
    auto styleBlock = div->getChildren()[0];
    EXPECT_EQ(styleBlock->getType(), NodeType::STYLE);
}

TEST_F(ParserTest, ParsesScriptBlocks) {
    auto ast = parse(R"(
        div {
            script {
                console.log("Hello CHTL!");
                {{&}}.style.color = 'blue';
            }
        }
    )");
    
    auto div = ast->getChildren()[0];
    auto scriptBlock = div->getChildren()[0];
    EXPECT_EQ(scriptBlock->getType(), NodeType::SCRIPT);
}