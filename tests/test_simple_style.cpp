#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Node/Style.h"

using namespace chtl;

void printAST(std::shared_ptr<Node> node, int depth = 0) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    std::cout << "[" << static_cast<int>(node->getType()) << "] ";
    
    if (node->getType() == NodeType::ELEMENT) {
        auto element = std::dynamic_pointer_cast<Element>(node);
        std::cout << "<" << element->getTagName() << ">";
    } else if (node->getType() == NodeType::TEXT) {
        auto text = std::dynamic_pointer_cast<Text>(node);
        std::cout << "TEXT: \"" << text->getData() << "\"";
    } else if (node->getType() == NodeType::STYLE) {
        auto style = std::dynamic_pointer_cast<Style>(node);
        std::cout << "STYLE: \"" << style->getCssContent() << "\"";
    }
    
    std::cout << std::endl;
    
    for (const auto& child : node->getChildren()) {
        printAST(child, depth + 1);
    }
}

int main() {
    std::string code = R"(div {
    style {
        color: red;
    }
    text { "Hello" }
})";

    std::cout << "Input:\n" << code << "\n---\n" << std::endl;

    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(stream), "test.chtl");
    
    StandardParser parser;
    parser.initialize(lexer, lexer->getContext());
    
    auto ast = parser.parse();
    
    if (parser.hasErrors()) {
        std::cout << "Errors:" << std::endl;
        for (const auto& error : parser.getErrors()) {
            std::cout << "  " << error.message << std::endl;
        }
    }
    
    if (ast) {
        std::cout << "\nAST:" << std::endl;
        printAST(ast);
    }
    
    return 0;
}