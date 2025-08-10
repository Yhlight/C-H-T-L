#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Custom.h"

using namespace chtl;

int main() {
    std::string code = R"([Custom] @Var CardColors {
    primary: #007bff;
    secondary: #6c757d;
    success: #28a745;
})";
    
    std::cout << "Parsing:\n" << code << std::endl;
    
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
            if (auto custom = std::dynamic_pointer_cast<Custom>(ast->getChildren()[0])) {
                std::cout << "Custom @Var: " << custom->getCustomName() << std::endl;
                std::cout << "Properties: " << custom->getProperties().size() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "\nException: " << e.what() << std::endl;
    }
    
    return 0;
}