#include <iostream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Node.h"

using namespace chtl;

void printAST(const std::shared_ptr<Node>& node, int depth = 0) {
    if (!node) return;
    
    std::string indent(depth * 2, ' ');
    std::cout << indent << "Node: " << node->getTypeName();
    
    if (node->getType() == NodeType::ELEMENT) {
        auto elem = std::static_pointer_cast<Element>(node);
        std::cout << " <" << elem->getTagName() << ">";
    } else if (node->getType() == NodeType::TEXT) {
        auto text = std::static_pointer_cast<Text>(node);
        std::cout << " \"" << text->getData() << "\"";
    }
    
    std::cout << std::endl;
    
    for (const auto& child : node->getChildren()) {
        printAST(child, depth + 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file.chtl>" << std::endl;
        return 1;
    }
    
    try {
        StandardLexer lexer;
        if (!lexer.initialize(argv[1])) {
            std::cerr << "Failed to initialize lexer" << std::endl;
            return 1;
        }
        
        auto context = std::make_shared<StandardContext>();
        StandardParser parser(lexer, context);
        
        auto ast = parser.parse();
        if (!ast) {
            std::cerr << "Failed to parse" << std::endl;
            return 1;
        }
        
        std::cout << "=== AST ===" << std::endl;
        printAST(ast);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}