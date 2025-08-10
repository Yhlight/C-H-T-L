#include <iostream>
#include <memory>
#include <fstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    // 读取 components.chtl
    std::ifstream file("components.chtl");
    if (!file) {
        std::cerr << "Cannot open components.chtl" << std::endl;
        return 1;
    }
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    
    auto input = std::make_unique<std::ifstream>(std::move(file));
    lexer->initialize(std::move(input), "components.chtl");
    
    StandardParser parser(lexer, context);
    
    auto ast = parser.parse();
    
    if (context->hasErrors()) {
        std::cout << "Parse errors:" << std::endl;
        for (const auto& error : context->getErrors()) {
            std::cout << "  " << error << std::endl;
        }
    } else {
        std::cout << "Parse successful!" << std::endl;
        std::cout << "Root has " << ast->getChildren().size() << " children" << std::endl;
    }
    
    return 0;
}