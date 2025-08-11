#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"

using namespace chtl;

// 包装词法分析器以追踪token
class TracingLexer : public StandardLexer {
public:
    Token getNextToken() override {
        Token token = StandardLexer::getNextToken();
        std::cout << "Lexer returns: Type=" << static_cast<int>(token.type) 
                  << " Value='" << token.value << "' Line=" << token.line << std::endl;
        return token;
    }
};

int main() {
    std::string code = "div { h2 { } }";
    
    std::cout << "Code: " << code << std::endl << std::endl;
    
    auto lexer = std::make_shared<TracingLexer>();
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