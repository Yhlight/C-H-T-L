#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Node/Import.h"
#include "Node/Element.h"
#include "Context/StandardContext.h"

using namespace chtl;

void printImportNode(std::shared_ptr<Import> importNode, int indent = 0) {
    std::string prefix(indent, ' ');
    
    std::cout << prefix << "Import Node:" << std::endl;
    std::cout << prefix << "  Type: ";
    switch (importNode->getType()) {
        case Import::ImportType::ALL: std::cout << "ALL"; break;
        case Import::ImportType::HTML: std::cout << "HTML"; break;
        case Import::ImportType::CSS: std::cout << "CSS"; break;
        case Import::ImportType::JS: std::cout << "JS"; break;
        case Import::ImportType::CHTL: std::cout << "CHTL"; break;
        case Import::ImportType::CUSTOM_ELEMENT: std::cout << "CUSTOM_ELEMENT"; break;
        case Import::ImportType::CUSTOM_STYLE: std::cout << "CUSTOM_STYLE"; break;
        case Import::ImportType::CUSTOM_VAR: std::cout << "CUSTOM_VAR"; break;
        case Import::ImportType::TEMPLATE_ELEMENT: std::cout << "TEMPLATE_ELEMENT"; break;
        case Import::ImportType::TEMPLATE_STYLE: std::cout << "TEMPLATE_STYLE"; break;
        case Import::ImportType::TEMPLATE_VAR: std::cout << "TEMPLATE_VAR"; break;
    }
    std::cout << std::endl;
    
    std::cout << prefix << "  Path: " << importNode->getPath() << std::endl;
    std::cout << prefix << "  Name: " << importNode->getName() << std::endl;
    
    if (importNode->isImportAll()) {
        std::cout << prefix << "  Wildcard Import: YES" << std::endl;
    }
    
    auto items = importNode->getImportItems();
    if (!items.empty()) {
        std::cout << prefix << "  Import Items: ";
        for (const auto& item : items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

void printNode(std::shared_ptr<Node> node, int indent = 0) {
    if (!node) return;
    
    std::string prefix(indent, ' ');
    
    if (node->getType() == NodeType::IMPORT) {
        printImportNode(std::static_pointer_cast<Import>(node), indent);
    } else {
        std::cout << prefix << "Node: " << node->getTagName() << " (Type: " << static_cast<int>(node->getType()) << ")" << std::endl;
    }
    
    // Print children
    for (const auto& child : node->getChildren()) {
        printNode(child, indent + 2);
    }
}

int main() {
    // Read test file
    std::ifstream file("/workspace/test/test_new_import.chtl");
    if (!file.is_open()) {
        std::cerr << "Failed to open test file" << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    // Create lexer and context
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(content);
    lexer->initialize(std::move(stream), "test_new_import.chtl");
    
    auto context = std::make_shared<StandardContext>();
    
    // Create parser
    StandardParser parser(lexer, context);
    auto ast = parser.parse();
    
    // Print errors if any
    auto errors = parser.getErrors();
    if (!errors.empty()) {
        std::cout << "Parser errors:" << std::endl;
        for (const auto& error : errors) {
            std::cout << "  Line " << error.line << ", Column " << error.column 
                      << ": " << error.message << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Print the AST
    std::cout << "AST Structure:" << std::endl;
    if (ast) {
        printNode(ast);
    } else {
        std::cout << "Failed to parse" << std::endl;
    }
    
    return 0;
}