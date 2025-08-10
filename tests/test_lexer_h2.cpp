#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"

using namespace chtl;

int main() {
    std::string code = "div { h2 { } }";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test.chtl");
    
    std::cout << "Tokens for: '" << code << "'" << std::endl;
    
    Token token;
    int i = 0;
    while ((token = lexer->getNextToken()).type != TokenType::EOF_TOKEN) {
        std::cout << i++ << ": Type=" << static_cast<int>(token.type) 
                  << " Value='" << token.value << "' Line=" << token.line 
                  << " Column=" << token.column << std::endl;
    }
    
    return 0;
}