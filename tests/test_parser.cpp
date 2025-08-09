#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Generator/HtmlGenerator.h"
#include "Common/GlobalMap.h"
#include "Node/Comment.h"

using namespace chtl;

std::string getNodeTypeName(NodeType type) {
    switch (type) {
        case NodeType::ELEMENT: return "ELEMENT";
        case NodeType::TEXT: return "TEXT";
        case NodeType::COMMENT: return "COMMENT";
        case NodeType::TEMPLATE: return "TEMPLATE";
        case NodeType::CUSTOM: return "CUSTOM";
        case NodeType::STYLE: return "STYLE";
        case NodeType::CONFIG: return "CONFIG";
        case NodeType::IMPORT: return "IMPORT";
        case NodeType::NAMESPACE: return "NAMESPACE";
        case NodeType::OPERATE: return "OPERATE";
        case NodeType::ORIGIN: return "ORIGIN";
        default: return "UNKNOWN";
    }
}

void printNode(std::shared_ptr<Node> node, int depth = 0) {
    if (!node) return;
    
    // 打印缩进
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    // 打印节点信息
    std::cout << "[" << getNodeTypeName(node->getType()) << "]";
    
    if (node->getType() == NodeType::ELEMENT) {
        auto element = std::dynamic_pointer_cast<Element>(node);
        std::cout << " <" << element->getTagName() << ">";
        
        // 打印属性
        auto attrs = element->getAttributes();
        if (!attrs.empty()) {
            std::cout << " {";
            bool first = true;
            for (const auto& [key, value] : attrs) {
                if (!first) std::cout << ", ";
                std::cout << key << "=";
                
                // 处理AttributeValue
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
    }
    else if (node->getType() == NodeType::TEXT) {
        auto text = std::dynamic_pointer_cast<Text>(node);
        std::cout << " \"" << text->getData() << "\"";
    }
    else if (node->getType() == NodeType::COMMENT) {
        auto comment = std::dynamic_pointer_cast<Comment>(node);
        std::cout << " \"" << comment->getContent() << "\"";
    }
    
    std::cout << std::endl;
    
    // 递归打印子节点
    for (const auto& child : node->getChildren()) {
        printNode(child, depth + 1);
    }
}

void testParser(const std::string& chtlCode) {
    std::cout << "=== Testing CHTL Parser ===" << std::endl;
    std::cout << "Input CHTL code:" << std::endl;
    std::cout << "---" << std::endl;
    std::cout << chtlCode << std::endl;
    std::cout << "---" << std::endl;
    
    // 创建词法分析器
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(chtlCode);
    
    if (!lexer->initialize(std::move(stream), "test.chtl")) {
        std::cerr << "Failed to initialize lexer" << std::endl;
        return;
    }
    
    // 创建解析器
    StandardParser parser;
    if (!parser.initialize(lexer, lexer->getContext())) {
        std::cerr << "Failed to initialize parser" << std::endl;
        return;
    }
    
    // 解析
    auto ast = parser.parse();
    
    // 检查错误
    if (parser.hasErrors()) {
        std::cout << "\nParse errors:" << std::endl;
        for (const auto& error : parser.getErrors()) {
            std::cout << "  " << error.filename << ":" << error.line << ":" 
                     << error.column << ": " << error.message << std::endl;
        }
    }
    
    // 打印AST
    std::cout << "\nAST structure:" << std::endl;
    printNode(ast);
    
    // 生成HTML
    if (ast && !parser.hasErrors()) {
        std::cout << "\nGenerated HTML:" << std::endl;
        std::cout << "---" << std::endl;
        
        HtmlGenerator generator;
        generator.initialize(lexer->getContext());
        
        std::string html;
        if (generator.generateToString(ast, html)) {
            std::cout << html << std::endl;
        } else {
            std::cerr << "Failed to generate HTML" << std::endl;
        }
        
        std::cout << "---" << std::endl;
    }
}

int main() {
    // 测试基础元素和文本
    std::string test1 = R"(
-- 基础测试
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
    }
}
)";

    // 测试内联样式
    std::string test2 = R"(
div {
    style {
        width: 500px;
        height: 300px;
        background-color: #f0f0f0;
        margin: 0 auto;
    }
    
    text { "Styled div" }
}
)";

    // 测试嵌套元素和属性
    std::string test3 = R"(
ul {
    class: menu;
    
    li {
        a {
            href: "/home";
            text { "Home" }
        }
    }
    
    li {
        a {
            href: "/about";
            text { "About" }
        }
    }
}
)";

    // 运行测试
    testParser(test1);
    std::cout << "\n\n";
    testParser(test2);
    std::cout << "\n\n";
    testParser(test3);
    
    return 0;
}