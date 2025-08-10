#include <iostream>
#include <memory>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/ChtlContext.h"
#include "Node/Import.h"

using namespace chtl;

// Need to expose parseImportStatement for testing
class TestParser : public StandardParser {
public:
    using StandardParser::StandardParser;
    using StandardParser::parseImportStatement;
    using StandardParser::currentToken_;
    using StandardParser::advance;
    using StandardParser::skipWhitespaceAndComments;
};

int main() {
    std::string code = "Import @Chtl from \"test/path\".*";
    
    // Create lexer and context
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(stream), "test.chtl");
    
    auto context = std::make_shared<ChtlContext>();
    
    // Create parser
    TestParser parser(lexer, context);
    
    // Initialize first token
    parser.currentToken_ = parser.getNextToken();
    
    std::cout << "First token: type=" << static_cast<int>(parser.currentToken_.type) 
              << " value=[" << parser.currentToken_.value << "]" << std::endl;
    
    // Try to parse import statement
    try {
        auto importNode = parser.parseImportStatement();
        
        if (importNode) {
            auto import = std::static_pointer_cast<Import>(importNode);
            std::cout << "Import parsed successfully!" << std::endl;
            std::cout << "  Path: " << import->getPath() << std::endl;
            std::cout << "  Is wildcard: " << (import->isImportAll() ? "YES" : "NO") << std::endl;
        } else {
            std::cout << "parseImportStatement returned nullptr" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Print errors
    auto errors = parser.getErrors();
    if (!errors.empty()) {
        std::cout << "Parser errors:" << std::endl;
        for (const auto& error : errors) {
            std::cout << "  " << error.message << std::endl;
        }
    }
    
    return 0;
}