#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    std::string code = "[Custom] @Var Test { x: 1; }";
    
    std::cout << "Parsing: " << code << std::endl;
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test.chtl");
    
    StandardParser parser(lexer, context);
    
    auto ast = parser.parse();
    
    if (context->hasErrors()) {
        std::cout << "Errors:" << std::endl;
        for (const auto& error : context->getErrors()) {
            std::cout << "  " << error << std::endl;
        }
    } else {
        std::cout << "Success!" << std::endl;
    }
    
    return 0;
}