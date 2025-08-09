#include <iostream>
#include <sstream>
#include <memory>
#include "Lexer/StandardLexer.h"
#include "Common/Token.h"

using namespace chtl;

std::string getTokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::UNQUOTED_LITERAL: return "UNQUOTED_LITERAL";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::TEXT: return "TEXT";
        case TokenType::STYLE: return "STYLE";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::COLON: return "COLON";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::DOT: return "DOT";
        case TokenType::AMPERSAND: return "AMPERSAND";
        case TokenType::SINGLE_LINE_COMMENT: return "SINGLE_LINE_COMMENT";
        case TokenType::HTML_COMMENT: return "HTML_COMMENT";
        case TokenType::EOF_TOKEN: return "EOF_TOKEN";
        default: return "UNKNOWN(" + std::to_string(static_cast<int>(type)) + ")";
    }
}

int main() {
    std::string code = R"(div {
    style {
        color: red;
    }
    text { "Hello" }
})";

    std::cout << "Input code:\n" << code << "\n---\n" << std::endl;

    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(code);
    
    if (!lexer->initialize(std::move(stream), "test.chtl")) {
        std::cerr << "Failed to initialize lexer" << std::endl;
        return 1;
    }
    
    std::cout << "Tokens:" << std::endl;
    Token token;
    int count = 0;
    while ((token = lexer->getNextToken()).getType() != TokenType::EOF_TOKEN) {
        std::cout << count++ << ": " 
                  << "[" << getTokenTypeName(token.getType()) << "] "
                  << "\"" << token.getValue() << "\" "
                  << "at " << token.getLine() << ":" << token.getColumn() 
                  << std::endl;
    }
    
    return 0;
}