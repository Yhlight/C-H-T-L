#include <iostream>
#include <memory>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/ChtlContext.h"
#include "Node/Import.h"

using namespace chtl;

void testParseImport(const std::string& code, const std::string& testName) {
    std::cout << "\n=== Test: " << testName << " ===" << std::endl;
    std::cout << "Code: " << code << std::endl;
    
    // Create lexer and context
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(stream), "test.chtl");
    
    // Debug: print first few tokens
    std::cout << "DEBUG: First tokens:" << std::endl;
    for (int i = 0; i < 5 && lexer->hasMoreTokens(); i++) {
        auto token = lexer->peekNextToken();
        std::cout << "  Token " << i << ": type=" << static_cast<int>(token.type) 
                  << " value=[" << token.value << "]" << std::endl;
        lexer->getNextToken(); // consume
    }
    
    // Re-initialize for parsing
    stream = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(stream), "test.chtl");
    
    auto context = std::make_shared<ChtlContext>();
    
    // Create parser
    StandardParser parser(lexer, context);
    
    // Parse just the import statement
    try {
        auto node = parser.parse();
        
        // Debug: print what we got
        if (!node) {
            std::cout << "DEBUG: parse() returned nullptr" << std::endl;
        } else {
            std::cout << "DEBUG: Got node of type " << static_cast<int>(node->getType()) 
                      << " with " << node->getChildren().size() << " children" << std::endl;
        }
        
        // Check if we got an import node
        if (node && !node->getChildren().empty()) {
            auto firstChild = node->getChildren()[0];
            std::cout << "DEBUG: First child type: " << static_cast<int>(firstChild->getType()) << std::endl;
            
            if (firstChild->getType() == NodeType::IMPORT) {
                auto importNode = std::static_pointer_cast<Import>(firstChild);
                
                std::cout << "Import parsed successfully!" << std::endl;
                std::cout << "  Type: ";
                switch (importNode->getType()) {
                    case Import::ImportType::CHTL: std::cout << "CHTL"; break;
                    case Import::ImportType::CSS: std::cout << "CSS"; break;
                    case Import::ImportType::HTML: std::cout << "HTML"; break;
                    case Import::ImportType::JS: std::cout << "JS"; break;
                    default: std::cout << "OTHER"; break;
                }
                std::cout << std::endl;
                std::cout << "  Path: " << importNode->getPath() << std::endl;
                std::cout << "  Is wildcard: " << (importNode->isImportAll() ? "YES" : "NO") << std::endl;
                
                if (!importNode->getImportItems().empty()) {
                    std::cout << "  Import items: ";
                    for (const auto& item : importNode->getImportItems()) {
                        std::cout << item << " ";
                    }
                    std::cout << std::endl;
                }
            } else {
                std::cout << "ERROR: First child is not an import node" << std::endl;
            }
        } else {
            std::cout << "ERROR: Failed to parse or no children" << std::endl;
        }
        
        // Print errors if any
        auto errors = parser.getErrors();
        if (!errors.empty()) {
            std::cout << "Parser errors:" << std::endl;
            for (const auto& error : errors) {
                std::cout << "  " << error.message << " (line " << error.line << ")" << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "EXCEPTION during parsing: " << e.what() << std::endl;
    }
}

int main() {
    // Test new wildcard import syntax
    testParseImport("Import @Chtl from \"chtholly/core\".*", "Wildcard import CHTL");
    testParseImport("Import @Style from \"styles/base\".*", "Wildcard import Style");
    testParseImport("Import @Html from \"components\".*", "Wildcard import HTML");
    
    // Test regular imports (no wildcards)
    testParseImport("Import @Chtl from \"utils/helper\"", "Regular import CHTL");
    testParseImport("Import @JavaScript from \"scripts/main\"", "Regular import JS");
    
    // Test edge cases
    testParseImport("Import @Chtl from \"path\".* // comment", "Wildcard with comment");
    
    return 0;
}