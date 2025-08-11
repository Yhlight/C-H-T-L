#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Custom.h"

using namespace chtl;

int main() {
    std::string code = "[Custom] @Element Card {\n    div {\n        class: \"card\";\n        h2 { \"Card Title\" }\n        p { \"Card content\" }\n    }\n}";
    
    std::cout << "Parsing code:\n" << code << "\n" << std::endl;
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test.chtl");
    
    // Check first few tokens
    std::cout << "First few tokens:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        auto tok = lexer->getNextToken();
        std::cout << i << ": Type=" << static_cast<int>(tok.type) 
                  << " Value='" << tok.value << "' Line=" << tok.line << std::endl;
        if (tok.type == TokenType::EOF_TOKEN) break;
    }
    
    // Reset and parse
    auto input2 = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input2), "test.chtl");
    
    try {
        auto ast = parser.parse();
        
        if (context->hasErrors()) {
            std::cout << "\nParse errors:" << std::endl;
            for (const auto& error : context->getErrors()) {
                std::cout << "  " << error << std::endl;
            }
        } else {
            std::cout << "\nParse successful!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "\nException: " << e.what() << std::endl;
    }
    
    return 0;
}