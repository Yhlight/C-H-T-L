#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"

using namespace chtl;

void testLexer(const std::string& code) {
    std::cout << "\nTesting: '" << code << "'" << std::endl;
    
    auto lexer = std::make_shared<StandardLexer>();
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test.chtl");
    
    Token token;
    int i = 0;
    while ((token = lexer->getNextToken()).type != TokenType::EOF_TOKEN) {
        std::cout << i++ << ": Type=" << static_cast<int>(token.type) 
                  << " Value='" << token.value << "'" << std::endl;
    }
}

int main() {
    // 测试不同的空格情况
    testLexer("h2 { }");      // 有空格
    testLexer("h2{ }");       // 没有空格
    testLexer("h2 {}");       // 完全没有空格
    testLexer("h2\n{\n}");    // 换行
    
    return 0;
}