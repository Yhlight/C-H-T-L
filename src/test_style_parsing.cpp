#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Generator/HtmlGenerator.h"
#include "Node/Style.h"

using namespace chtl;

void printAST(std::shared_ptr<Node> node, int depth = 0) {
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
            printAST(child, depth + 1);
        }
    } else if (node->getType() == NodeType::TEXT) {
        auto text = std::dynamic_pointer_cast<Text>(node);
        std::cout << "[TEXT] \"" << text->getData() << "\"" << std::endl;
    } else if (node->getType() == NodeType::STYLE) {
        auto style = std::dynamic_pointer_cast<Style>(node);
        std::cout << "[STYLE] " << (style->isLocal() ? "LOCAL" : "GLOBAL") 
                  << " content: \"" << style->getCssContent() << "\"" << std::endl;
    }
}

int main() {
    // 测试内联样式
    std::string test1 = R"(div {
    style {
        width: 500px;
        height: 300px;
        background-color: #f0f0f0;
        margin: 0 auto;
    }
    
    text { "Styled div" }
})";

    // 测试带类选择器的样式
    std::string test2 = R"(div {
    style {
        .container {
            width: 800px;
            margin: 0 auto;
        }
        
        &:hover {
            background-color: #e0e0e0;
        }
    }
    
    text { "Container div" }
})";

    // 测试全局样式
    std::string test3 = R"(html {
    head {
        style {
            body {
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 0;
            }
        }
    }
    
    body {
        div {
            style {
                padding: 20px;
            }
        }
    }
})";

    std::vector<std::string> tests = {test1, test2, test3};
    
    for (size_t i = 0; i < tests.size(); i++) {
        std::cout << "\n=== Test " << (i + 1) << " ===" << std::endl;
        std::cout << "Input:\n" << tests[i] << std::endl;
        std::cout << "---" << std::endl;
        
        // 创建词法分析器
        auto lexer = std::make_shared<StandardLexer>();
        auto stream = std::make_unique<std::istringstream>(tests[i]);
        
        if (!lexer->initialize(std::move(stream), "test.chtl")) {
            std::cerr << "Failed to initialize lexer" << std::endl;
            continue;
        }
        
        // 创建解析器
        StandardParser parser;
        if (!parser.initialize(lexer, lexer->getContext())) {
            std::cerr << "Failed to initialize parser" << std::endl;
            continue;
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
        if (ast) {
            std::cout << "\nAST structure:" << std::endl;
            printAST(ast);
            
            // 生成HTML
            HtmlGenerator generator;
            generator.initialize(lexer->getContext());
            generator.setGenerateDoctype(false);
            
            BasicGenerator::GeneratorConfig config;
            config.prettyPrint = true;
            config.indentSize = 2;
            generator.setConfig(config);
            
            std::string html;
            if (generator.generateToString(ast, html)) {
                std::cout << "\nGenerated HTML:" << std::endl;
                std::cout << html << std::endl;
            }
        }
    }
    
    return 0;
}