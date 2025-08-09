#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Node/Node.h"

using namespace chtl;

void printNode(std::shared_ptr<Node> node, int depth = 0) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    if (node->getType() == NodeType::ELEMENT) {
        auto element = std::dynamic_pointer_cast<Element>(node);
        std::cout << "<" << element->getTagName() << ">";
        std::cout << " (children: " << element->getChildren().size() << ")" << std::endl;
        
        // 递归打印子节点
        for (const auto& child : element->getChildren()) {
            printNode(child, depth + 1);
        }
    } else if (node->getType() == NodeType::TEXT) {
        auto text = std::dynamic_pointer_cast<Text>(node);
        std::cout << "[TEXT] \"" << text->getData() << "\"" << std::endl;
    }
}

int main() {
    // 极简的CHTL代码
    std::string chtlCode = R"(
html {
    head {
        title { text { "Test" } }
    }
    body {
        p { text { "Hello" } }
    }
}
)";

    std::cout << "Input CHTL:" << std::endl;
    std::cout << chtlCode << std::endl;
    std::cout << "---" << std::endl;

    // 创建词法分析器
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(chtlCode);
    
    if (!lexer->initialize(std::move(stream), "test.chtl")) {
        std::cerr << "Failed to initialize lexer" << std::endl;
        return 1;
    }
    
    // 打印所有tokens
    std::cout << "\nTokens:" << std::endl;
    Token token;
    while ((token = lexer->getNextToken()).getType() != TokenType::EOF_TOKEN) {
        std::cout << "  " << token.getLine() << ":" << token.getColumn() 
                  << " [" << static_cast<int>(token.getType()) << "] "
                  << "\"" << token.getValue() << "\"" << std::endl;
    }
    
    // 重新初始化lexer用于解析
    stream = std::make_unique<std::istringstream>(chtlCode);
    lexer->initialize(std::move(stream), "test.chtl");
    
    // 创建解析器
    StandardParser parser;
    if (!parser.initialize(lexer, lexer->getContext())) {
        std::cerr << "Failed to initialize parser" << std::endl;
        return 1;
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
    if (ast) {
        printNode(ast);
    }
    
    return 0;
}