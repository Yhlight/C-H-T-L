#include <iostream>
#include <sstream>
#include <fstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    std::ifstream file("components.chtl");
    if (!file) {
        std::cerr << "Cannot open components.chtl\n";
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    std::cout << "Content length: " << content.length() << " bytes\n";
    std::cout << "First 100 chars:\n" << content.substr(0, 100) << "\n...\n\n";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(content);
    lexer->initialize(std::move(input), "components.chtl");
    
    auto ast = parser.parse();
    
    if (!ast) {
        std::cout << "Parse failed!\n";
    } else {
        std::cout << "Parse succeeded!\n";
        std::cout << "Children: " << ast->getChildren().size() << "\n";
    }
    
    if (!context->getErrors().empty()) {
        std::cout << "Errors:\n";
        for (const auto& err : context->getErrors()) {
            std::cout << "  - " << err << "\n";
        }
    }
    
    return 0;
}
