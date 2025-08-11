#include <iostream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Import.h"

using namespace chtl;

void testPathParsing() {
    std::cout << "Testing Path Parsing\n";
    std::cout << "===================\n\n";
    
    std::vector<std::string> testCases = {
        R"([Import] @Html from "layout.html" as layout;)",
        R"([Import] @Style from "theme.css";)",
        R"([Import] @JavaScript from utils.js;)",
        R"([Import] @Style from styles.main.css;)"
    };
    
    for (size_t i = 0; i < testCases.size(); ++i) {
        std::cout << "Test " << (i+1) << ": " << testCases[i] << "\n";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        StandardParser parser(lexer, context);
        
        auto input = std::make_unique<std::istringstream>(testCases[i]);
        lexer->initialize(std::move(input), "test.chtl");
        
        auto ast = parser.parse();
        
        if (ast && ast->getChildren().size() > 0) {
            if (auto importNode = std::dynamic_pointer_cast<Import>(ast->getChildren()[0])) {
                std::cout << "  Path: " << importNode->getPath() << "\n";
                std::cout << "  Type: " << static_cast<int>(importNode->getType()) << "\n";
                std::cout << "  Alias: " << importNode->getAlias() << "\n";
            }
        } else {
            std::cout << "  Parse failed\n";
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    testPathParsing();
    return 0;
}