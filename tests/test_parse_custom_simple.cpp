#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Custom.h"

using namespace chtl;

int main() {
    std::string code = R"([Custom] @Element Card {
    div.card {
        padding: 16px;
    }
})";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test.chtl");
    
    try {
        auto ast = parser.parse();
        
        if (context->hasErrors()) {
            std::cout << "Parse errors:" << std::endl;
            for (const auto& error : context->getErrors()) {
                std::cout << "  " << error << std::endl;
            }
        } else {
            std::cout << "Parse successful!" << std::endl;
            if (ast) {
                std::cout << "Root has " << ast->getChildren().size() << " children" << std::endl;
                for (const auto& child : ast->getChildren()) {
                    if (auto custom = std::dynamic_pointer_cast<Custom>(child)) {
                        std::cout << "- Custom: " << custom->getCustomName() 
                                  << " Type: " << static_cast<int>(custom->getCustomType()) << std::endl;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}