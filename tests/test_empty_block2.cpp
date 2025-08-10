#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    // 重定向 cerr 到 cout
    std::cerr.rdbuf(std::cout.rdbuf());
    
    std::string code = "div { h2 { } }";
    
    std::cout << "Code: " << code << std::endl;
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test.chtl");
    
    StandardParser parser(lexer, context);
    
    try {
        auto ast = parser.parse();
        
        if (context->hasErrors()) {
            std::cout << "\nParse errors:" << std::endl;
            for (const auto& error : context->getErrors()) {
                std::cout << "  " << error << std::endl;
            }
        } else {
            std::cout << "\n✓ Parse successful!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "\nException: " << e.what() << std::endl;
    }
    
    return 0;
}