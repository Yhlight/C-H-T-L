#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Generator/HtmlGenerator.h"
#include "Node/Comment.h"

using namespace chtl;

void printAST(std::shared_ptr<Node> node, int depth) {
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
                } else if (std::holds_alternative<int>(value)) {
                    std::cout << std::get<int>(value);
                } else if (std::holds_alternative<double>(value)) {
                    std::cout << std::get<double>(value);
                } else if (std::holds_alternative<bool>(value)) {
                    std::cout << (std::get<bool>(value) ? "true" : "false");
                }
                first = false;
            }
            std::cout << "}";
        }
        std::cout << std::endl;
        
        // 递归打印子节点
        for (const auto& child : element->getChildren()) {
            printAST(child, depth + 1);
        }
    } else if (node->getType() == NodeType::TEXT) {
        auto text = std::dynamic_pointer_cast<Text>(node);
        std::cout << "[TEXT] \"" << text->getData() << "\"" << std::endl;
    } else if (node->getType() == NodeType::COMMENT) {
        auto comment = std::dynamic_pointer_cast<Comment>(node);
        std::cout << "[COMMENT] \"" << comment->getContent() << "\"" << std::endl;
    }
}

int main() {
    // 简单的CHTL代码（没有style块）
    std::string chtlCode = R"(
html {
    head {
        title {
            text { "Test Page" }
        }
    }
    
    body {
        h1 {
            id: main-title;
            class: header;
            
            text { "Hello CHTL" }
        }
        
        p {
            text { "This is a paragraph." }
        }
        
        div {
            class: container;
            
            a {
                href: "https://example.com";
                target: "_blank";
                
                text { "Visit Example" }
            }
        }
    }
}
)";

    std::cout << "CHTL Input:" << std::endl;
    std::cout << chtlCode << std::endl;
    std::cout << "---" << std::endl;

    // 创建词法分析器
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(chtlCode);
    
    if (!lexer->initialize(std::move(stream), "test.chtl")) {
        std::cerr << "Failed to initialize lexer" << std::endl;
        return 1;
    }
    
    // 创建解析器
    StandardParser parser;
    if (!parser.initialize(lexer, lexer->getContext())) {
        std::cerr << "Failed to initialize parser" << std::endl;
        return 1;
    }
    
    // 解析
    auto ast = parser.parse();
    
    if (!ast) {
        std::cerr << "Failed to parse CHTL" << std::endl;
        return 1;
    }
    
    // 打印AST根节点信息
    std::cout << "\nAST Root type: " << static_cast<int>(ast->getType()) << std::endl;
    if (ast->getType() == NodeType::ELEMENT) {
        auto rootElement = std::dynamic_pointer_cast<Element>(ast);
        std::cout << "Root element name: " << rootElement->getTagName() << std::endl;
        std::cout << "Children count: " << rootElement->getChildren().size() << std::endl;
    }
    
    std::cout << "\nFull AST structure:" << std::endl;
    printAST(ast, 0);
    
    // 生成HTML
    HtmlGenerator generator;
    generator.initialize(lexer->getContext());
    generator.setGenerateDoctype(true);
    
    // 配置生成器
    BasicGenerator::GeneratorConfig config;
    config.prettyPrint = true;
    config.indentSize = 2;
    generator.setConfig(config);
    
    std::string html;
    if (generator.generateToString(ast, html)) {
        std::cout << "\nGenerated HTML:" << std::endl;
        std::cout << html << std::endl;
    } else {
        std::cerr << "Failed to generate HTML" << std::endl;
        
        // 打印错误
        for (const auto& error : generator.getErrors()) {
            std::cerr << "Error: " << error << std::endl;
        }
    }
    
    return 0;
}