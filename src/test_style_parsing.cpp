#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Generator/HtmlGenerator.h"
#include "Node/Style.h"

using namespace chtl;

void printNode(std::shared_ptr<Node> node, int depth = 0) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    if (node->getType() == NodeType::ELEMENT) {
        auto element = std::dynamic_pointer_cast<Element>(node);
        std::cout << "<" << element->getTagName() << ">";
        
        // 打印属性
        auto attrs = element->getAttributes();
        if (!attrs.empty()) {
            std::cout << " {";
            bool first = true;
            for (const auto& [key, value] : attrs) {
                if (!first) std::cout << ", ";
                std::cout << key << "=";
                if (std::holds_alternative<std::string>(value)) {
                    std::cout << "\"" << std::get<std::string>(value) << "\"";
                }
                first = false;
            }
            std::cout << "}";
        }
        std::cout << std::endl;
        
        // 递归打印子节点
        for (const auto& child : element->getChildren()) {
            printNode(child, depth + 1);
        }
    } else if (node->getType() == NodeType::TEXT) {
        auto text = std::dynamic_pointer_cast<Text>(node);
        std::cout << "[TEXT] \"" << text->getData() << "\"" << std::endl;
    } else if (node->getType() == NodeType::STYLE) {
        auto style = std::dynamic_pointer_cast<Style>(node);
        std::cout << "[STYLE] " << (style->isLocal() ? "LOCAL" : "GLOBAL") 
                  << " \"" << style->getCssContent() << "\"" << std::endl;
    }
}

int main() {
    // 测试不同的style用法
    std::string test1 = R"(div {
    style {
        width: 300px;
        height: 200px;
        background-color: #f0f0f0;
        margin: 0 auto;
    }
    
    text { "Styled div" }
})";

    std::string test2 = R"(div {
    id: myDiv;
    class: container;
    
    style {
        // 内联样式
        padding: 20px;
        border: 1px solid #ccc;
        
        // 自动添加类名的样式
        .box {
            width: 100%;
            height: 100%;
        }
        
        // 使用&表示当前元素
        &:hover {
            background-color: #e0e0e0;
        }
    }
    
    p {
        text { "Content" }
    }
})";

    // 全局style块
    std::string test3 = R"(html {
    head {
        style {
            body {
                margin: 0;
                padding: 0;
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
            class: container;
            text { "Hello" }
        }
    }
})";

    std::cout << "=== Test 1: Basic inline style ===" << std::endl;
    std::cout << "Input:\n" << test1 << "\n---" << std::endl;
    
    // 创建词法分析器
    auto lexer1 = std::make_shared<StandardLexer>();
    auto stream1 = std::make_unique<std::istringstream>(test1);
    lexer1->initialize(std::move(stream1), "test1.chtl");
    
    // 创建解析器
    StandardParser parser1;
    parser1.initialize(lexer1, lexer1->getContext());
    
    // 解析
    auto ast1 = parser1.parse();
    
    if (parser1.hasErrors()) {
        std::cout << "Parse errors:" << std::endl;
        for (const auto& error : parser1.getErrors()) {
            std::cout << "  " << error.message << std::endl;
        }
    }
    
    std::cout << "\nAST:" << std::endl;
    if (ast1) printNode(ast1);
    
    // 生成HTML
    if (ast1 && !parser1.hasErrors()) {
        HtmlGenerator generator;
        generator.initialize(lexer1->getContext());
        generator.setGenerateDoctype(false);
        
        std::string html;
        if (generator.generateToString(ast1, html)) {
            std::cout << "\nGenerated HTML:\n" << html << std::endl;
        }
    }
    
    std::cout << "\n=== Test 2: Advanced inline style ===" << std::endl;
    std::cout << "Input:\n" << test2 << "\n---" << std::endl;
    
    auto lexer2 = std::make_shared<StandardLexer>();
    auto stream2 = std::make_unique<std::istringstream>(test2);
    lexer2->initialize(std::move(stream2), "test2.chtl");
    
    StandardParser parser2;
    parser2.initialize(lexer2, lexer2->getContext());
    auto ast2 = parser2.parse();
    
    if (parser2.hasErrors()) {
        std::cout << "Parse errors:" << std::endl;
        for (const auto& error : parser2.getErrors()) {
            std::cout << "  " << error.message << std::endl;
        }
    }
    
    std::cout << "\nAST:" << std::endl;
    if (ast2) printNode(ast2);
    
    std::cout << "\n=== Test 3: Global style block ===" << std::endl;
    std::cout << "Input:\n" << test3 << "\n---" << std::endl;
    
    auto lexer3 = std::make_shared<StandardLexer>();
    auto stream3 = std::make_unique<std::istringstream>(test3);
    lexer3->initialize(std::move(stream3), "test3.chtl");
    
    StandardParser parser3;
    parser3.initialize(lexer3, lexer3->getContext());
    auto ast3 = parser3.parse();
    
    if (parser3.hasErrors()) {
        std::cout << "Parse errors:" << std::endl;
        for (const auto& error : parser3.getErrors()) {
            std::cout << "  " << error.message << std::endl;
        }
    }
    
    std::cout << "\nAST:" << std::endl;
    if (ast3) printNode(ast3);
    
    return 0;
}