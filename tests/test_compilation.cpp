#include <gtest/gtest.h>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Node.h"
#include "Node/Comment.h"
#include <sstream>

// 简单的编译测试
TEST(CompilationTest, BasicCompilation) {
    // 测试基本类是否能正确实例化
    auto lexer = std::make_shared<chtl::StandardLexer>();
    EXPECT_NE(lexer, nullptr);
    
    auto context = std::make_shared<chtl::StandardContext>();
    EXPECT_NE(context, nullptr);
    
    auto parser = std::make_shared<chtl::StandardParser>(lexer, context);
    EXPECT_NE(parser, nullptr);
}

// 测试Node类的新方法
TEST(CompilationTest, NodeClassMethods) {
    auto node = std::make_shared<chtl::Node>(chtl::NodeType::ELEMENT, "div");
    
    // 测试addClass和getClasses
    node->addClass("test-class");
    node->addClass("another-class");
    
    auto classes = node->getClasses();
    EXPECT_EQ(classes.size(), 2);
    EXPECT_EQ(classes[0], "test-class");
    EXPECT_EQ(classes[1], "another-class");
    
    // 测试不重复添加
    node->addClass("test-class");
    EXPECT_EQ(node->getClasses().size(), 2);
    
    // 测试removeClass
    node->removeClass("test-class");
    EXPECT_EQ(node->getClasses().size(), 1);
    EXPECT_EQ(node->getClasses()[0], "another-class");
}

// 测试Comment节点
TEST(CompilationTest, CommentNode) {
    auto comment = std::make_shared<chtl::Comment>();
    comment->setContent("这是一个注释");
    
    EXPECT_EQ(comment->getContent(), "这是一个注释");
    EXPECT_EQ(comment->getType(), chtl::NodeType::COMMENT);
}