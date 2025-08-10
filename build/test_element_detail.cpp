#include <iostream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    std::string code = "div { h1 { \"Hello\" } }";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test");
    
    // 手动查看token
    std::cout << "Tokens:\n";
    Token token = lexer->getNextToken();
    int i = 0;
    while (token.type != TokenType::EOF_TOKEN && i < 10) {
        std::cout << "  [" << i << "] Type: " << static_cast<int>(token.type) 
                  << " Value: '" << token.value << "'\n";
        token = lexer->getNextToken();
        i++;
    }
    
    return 0;
}
