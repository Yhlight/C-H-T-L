#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Common/Token.h"

using namespace chtl;

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::AT_CHTL: return "@CHTL";
        case TokenType::AT_HTML: return "@HTML";
        case TokenType::AT_STYLE: return "@STYLE";
        case TokenType::AT_JAVASCRIPT: return "@JAVASCRIPT";
        case TokenType::DOT: return "DOT";
        case TokenType::WILDCARD: return "WILDCARD";
        case TokenType::ASTERISK: return "ASTERISK";
        case TokenType::IMPORT: return "IMPORT";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COLON: return "COLON";
        case TokenType::COMMA: return "COMMA";
        case TokenType::EOF_TOKEN: return "EOF";
        case TokenType::FROM: return "FROM";
        default: return "UNKNOWN(" + std::to_string(static_cast<int>(type)) + ")";
    }
}

int main() {
    // Test import statements
    std::string testCode = R"(
// Test new import syntax
Import @Chtl from "chtholly/core".*
Import @Style from "styles/base".*
Import @Html from "components".*

// Regular imports without wildcards
Import @Chtl from "utils/helper"
Import @JavaScript from "scripts/main"
)";

    // Create lexer
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(testCode);
    lexer->initialize(std::move(stream), "test.chtl");
    
    // Tokenize and print
    std::cout << "Tokens:" << std::endl;
    while (lexer->hasMoreTokens()) {
        Token token = lexer->getNextToken();
        std::cout << "  " << tokenTypeToString(token.type) 
                  << " [" << token.value << "]"
                  << " at line " << token.line << ", col " << token.column
                  << std::endl;
                  
        if (token.type == TokenType::EOF_TOKEN) break;
    }
    
    return 0;
}