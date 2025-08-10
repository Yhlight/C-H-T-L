#include <iostream>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

using namespace chtl;

void printToken(const Token& token) {
    std::cout << "Type: " << static_cast<int>(token.type) << " (";
    
    switch(token.type) {
        case TokenType::IMPORT: std::cout << "IMPORT"; break;
        case TokenType::AT_HTML: std::cout << "AT_HTML"; break;
        case TokenType::AT_STYLE: std::cout << "AT_STYLE"; break;
        case TokenType::AT_JAVASCRIPT: std::cout << "AT_JAVASCRIPT"; break;
        case TokenType::AT_CHTL: std::cout << "AT_CHTL"; break;
        case TokenType::FROM: std::cout << "FROM"; break;
        case TokenType::AS: std::cout << "AS"; break;
        case TokenType::IDENTIFIER: std::cout << "IDENTIFIER"; break;
        case TokenType::STRING_LITERAL: std::cout << "STRING_LITERAL"; break;
        case TokenType::SEMICOLON: std::cout << "SEMICOLON"; break;
        default: std::cout << "OTHER"; break;
    }
    
    std::cout << ") Value: '" << token.value << "'\n";
}

int main() {
    std::string testCode = "[Import] @Html from \"layout.html\" as layout;";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    
    auto input = std::make_unique<std::istringstream>(testCode);
    lexer->initialize(std::move(input), "test");
    
    std::cout << "Tokenizing: " << testCode << "\n\n";
    
    Token token = lexer->getNextToken();
    while (token.type != TokenType::EOF_TOKEN) {
        printToken(token);
        token = lexer->getNextToken();
    }
    
    return 0;
}