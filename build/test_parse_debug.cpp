#include <iostream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    std::string code = "div { h1 { \"Hello\" } }";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test");
    
    auto ast = parser.parse();
    
    if (!ast) {
        std::cout << "Parse failed!\n";
        for (const auto& err : context->getErrors()) {
            std::cout << "Error: " << err << "\n";
        }
    } else {
        std::cout << "Parse successful\n";
        std::cout << "Root has " << ast->getChildren().size() << " children\n";
        for (const auto& child : ast->getChildren()) {
            std::cout << "- " << child->getTagName() << "\n";
        }
    }
    
    return 0;
}
