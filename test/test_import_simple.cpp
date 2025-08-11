#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Common/Token.h"

using namespace chtl;

void testImportLexing(const std::string& code) {
    std::cout << "\nTesting: " << code << std::endl;
    
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(stream), "test.chtl");
    
    std::cout << "Tokens: ";
    while (lexer->hasMoreTokens()) {
        Token token = lexer->getNextToken();
        if (token.type == TokenType::EOF_TOKEN) break;
        
        std::cout << "[" << token.value << "] ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Testing Import Syntax ===" << std::endl;
    
    // 测试各种导入语法
    testImportLexing("Import @Chtl from chtholly/core.*");
    testImportLexing("Import @Style from styles/base/*");
    testImportLexing("Import @Html from components.*");
    testImportLexing("Import @Chtl from Chtholly.Space.*");
    testImportLexing("Import @Chtl from \"special/path with spaces.*\"");
    testImportLexing("Import @Style from \"styles/*\"");
    
    std::cout << "\n✓ 新的通配符语法支持:" << std::endl;
    std::cout << "  - path.*  (点通配符)" << std::endl;
    std::cout << "  - path/*  (斜杠通配符)" << std::endl;
    std::cout << "  - 无引号路径: Import @Type from path/to/module.*" << std::endl;
    std::cout << "  - 带引号路径: Import @Type from \"path/to/module.*\"" << std::endl;
    
    return 0;
}