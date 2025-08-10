#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

using namespace chtl;

void testSimple() {
    // 测试最简单的属性赋值
    std::string input = R"(div {
    id = "test";
    class : "box";
})";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    auto parser = std::make_shared<StandardParser>(lexer, context);
    
    auto stream = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(stream), "test");
    
    // 先打印一些token看看
    std::cout << "Tokens:\n";
    for (int i = 0; i < 10; i++) {
        auto token = lexer->getNextToken();
        std::cout << "  " << static_cast<int>(token.type) << ": " << token.value << "\n";
        if (token.type == TokenType::EOF_TOKEN) break;
    }
    
    // 重新初始化
    auto stream2 = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(stream2), "test");
    
    auto ast = parser->parse();
    
    if (ast && context->getErrors().empty()) {
        std::cout << "✓ CE Equation works for attributes!\n";
    } else {
        std::cout << "✗ Failed\n";
        for (const auto& error : context->getErrors()) {
            std::cout << "  Error: " << error << "\n";
        }
    }
}

int main() {
    testSimple();
    return 0;
}