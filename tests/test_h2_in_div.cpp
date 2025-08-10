#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Element.h"

using namespace chtl;

int main() {
    // 重定向 cerr 到 cout
    std::cerr.rdbuf(std::cout.rdbuf());
    
    std::string code = "[Custom] @Element Test {\n"
                      "    div {\n"
                      "        h2 { }\n"
                      "    }\n"
                      "}";
    
    std::cout << "Parsing:\n" << code << "\n" << std::endl;
    
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
            
            // 打印解析树
            if (ast && ast->getChildren().size() > 0) {
                auto custom = ast->getChildren()[0];
                std::cout << "\nCustom element has " << custom->getChildren().size() << " children" << std::endl;
                if (custom->getChildren().size() > 0) {
                    auto div = custom->getChildren()[0];
                    if (auto elem = std::dynamic_pointer_cast<Element>(div)) {
                        std::cout << "First child is: " << elem->getTagName() 
                                  << " with " << elem->getChildren().size() << " children" << std::endl;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cout << "\nException: " << e.what() << std::endl;
    }
    
    return 0;
}