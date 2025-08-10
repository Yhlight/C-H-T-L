#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Common/Token.h"

using namespace chtl;

void testImportLexing() {
    std::cout << "Testing Import Lexing\n";
    std::cout << "====================\n";
    
    // 测试输入
    std::string input = R"(Import @Chtl from "moduleA")";
    
    // 创建词法分析器
    auto lexer = std::make_shared<StandardLexer>();
    
    // 初始化
    auto iss = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(iss), "test");
    
    // 获取所有tokens
    std::cout << "Tokens:\n";
    while (true) {
        auto token = lexer->getNextToken();
        
        std::string typeName = "UNKNOWN";
        switch(token.type) {
            case TokenType::IDENTIFIER: typeName = "IDENTIFIER"; break;
            case TokenType::STRING_LITERAL: typeName = "STRING_LITERAL"; break;
            case TokenType::AT_CHTL: typeName = "AT_CHTL"; break;
            case TokenType::FROM: typeName = "FROM"; break;
            case TokenType::EOF_TOKEN: typeName = "EOF_TOKEN"; break;
            default: break;
        }
        
        std::cout << "  Type: " << static_cast<int>(token.type) 
                  << " (" << typeName << ")"
                  << " Value: '" << token.value << "'"
                  << " Line: " << token.line 
                  << " Column: " << token.column << "\n";
        
        if (token.type == TokenType::EOF_TOKEN) {
            break;
        }
    }
}

int main() {
    try {
        testImportLexing();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}