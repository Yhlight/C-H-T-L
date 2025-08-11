#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Custom.h"

using namespace chtl;

int main() {
    // 逐步增加复杂度来定位问题
    std::string code1 = R"([Custom] @Element Test1 {
    div { }
})";
    
    std::string code2 = R"([Custom] @Element Test2 {
    div {
        h2 { }
    }
})";
    
    std::string code3 = R"([Custom] @Element Test3 {
    div {
        h2 { "Title" }
    }
})";
    
    std::string codes[] = {code1, code2, code3};
    std::string names[] = {"Test1", "Test2", "Test3"};
    
    for (int i = 0; i < 3; ++i) {
        std::cout << "\n=== Testing " << names[i] << " ===" << std::endl;
        std::cout << codes[i] << std::endl;
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        
        auto input = std::make_unique<std::istringstream>(codes[i]);
        lexer->initialize(std::move(input), "test.chtl");
        
        StandardParser parser(lexer, context);
        
        try {
            auto ast = parser.parse();
            
            if (context->hasErrors()) {
                std::cout << "Parse errors:" << std::endl;
                for (const auto& error : context->getErrors()) {
                    std::cout << "  " << error << std::endl;
                }
            } else {
                std::cout << "✓ Parse successful!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    
    return 0;
}