#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    // 测试单个空块
    std::string code1 = "div { }";
    
    // 测试嵌套空块
    std::string code2 = "div { h2 { } }";
    
    std::string codes[] = {code1, code2};
    std::string names[] = {"Single empty block", "Nested empty block"};
    
    for (int i = 0; i < 2; ++i) {
        std::cout << "\n=== " << names[i] << " ===" << std::endl;
        std::cout << "Code: " << codes[i] << std::endl;
        
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