#include <iostream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    std::string code = "[Custom] @Style MyStyle { color: red; }";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test");
    
    auto ast = parser.parse();
    
    std::cout << "Parse: " << (ast ? "OK" : "FAIL") << "\n";
    if (ast) {
        std::cout << "Children: " << ast->getChildren().size() << "\n";
    }
    
    for (const auto& err : context->getErrors()) {
        std::cout << "Error: " << err << "\n";
    }
    
    return 0;
}
