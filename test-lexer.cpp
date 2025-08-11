#include <iostream>
#include <memory>
#include <fstream>
#include "Lexer/StandardLexer.h"
#include "Common/Token.h"

using namespace chtl;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }
    
    StandardLexer lexer;
    if (!lexer.initialize(argv[1])) {
        std::cerr << "Failed to initialize lexer" << std::endl;
        return 1;
    }
    
    Token token;
    while ((token = lexer.getNextToken()).type != TokenType::EOF_TOKEN) {
        std::cout << "Token: type=" << static_cast<int>(token.type) 
                  << ", value='" << token.value << "'" 
                  << ", line=" << token.line 
                  << ", column=" << token.column << std::endl;
    }
    
    return 0;
}