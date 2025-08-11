#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/ChtlContext.h"
#include "Node/Import.h"
#include "Node/Element.h"

using namespace chtl;

void printNode(std::shared_ptr<Node> node, int indent = 0) {
    if (!node) return;
    
    std::string prefix(indent, ' ');
    
    std::cout << prefix << "Node: " << node->getTagName() 
              << " (Type: " << static_cast<int>(node->getType()) << ")"
              << " Children: " << node->getChildren().size();
    
    if (node->getType() == NodeType::IMPORT) {
        auto importNode = std::static_pointer_cast<Import>(node);
        std::cout << "\n" << prefix << "  → Type: ";
        switch (importNode->getType()) {
            case Import::ImportType::CHTL: std::cout << "CHTL"; break;
            case Import::ImportType::CSS: std::cout << "CSS"; break;
            case Import::ImportType::HTML: std::cout << "HTML"; break;
            case Import::ImportType::JS: std::cout << "JS"; break;
            default: std::cout << "OTHER"; break;
        }
        std::cout << ", Path: \"" << importNode->getPath() << "\"";
        if (importNode->isImportAll()) {
            std::cout << " [WILDCARD]";
        }
    }
    
    std::cout << std::endl;
    
    // Print children
    for (const auto& child : node->getChildren()) {
        printNode(child, indent + 2);
    }
}

int main() {
    // Read test file
    std::ifstream file("/workspace/test/test_unquoted_paths.chtl");
    if (!file.is_open()) {
        std::cerr << "Failed to open test file" << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    std::cout << "Parsing file content:" << std::endl;
    std::cout << content << std::endl;
    std::cout << "\n==================\n" << std::endl;
    
    // Create lexer and context
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(content);
    lexer->initialize(std::move(stream), "test_wildcard_import.chtl");
    
    auto context = std::make_shared<ChtlContext>();
    
    // Create parser
    StandardParser parser(lexer, context);
    
    // Parse
    auto ast = parser.parse();
    
    // Print AST
    std::cout << "AST Structure:" << std::endl;
    printNode(ast);
    
    // Print errors if any
    auto errors = parser.getErrors();
    if (!errors.empty()) {
        std::cout << "\nParser errors:" << std::endl;
        for (const auto& error : errors) {
            std::cout << "  Line " << error.line << ": " << error.message << std::endl;
        }
    }
    
    return 0;
}