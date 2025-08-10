#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

using namespace chtl;

int main() {
    std::string input = "[Namespace] space {\n}\n";
    
    std::cout << "Input:\n" << input << "\n";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    auto parser = std::make_shared<StandardParser>(lexer, context);
    
    auto stream = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(stream), "test");
    
    // 打印前几个token
    std::cout << "\nTokens:\n";
    for (int i = 0; i < 5; i++) {
        auto token = lexer->getNextToken();
        std::cout << "  Token " << i << ": type=" << static_cast<int>(token.type) 
                  << " value='" << token.value << "'\n";
        if (token.type == TokenType::EOF_TOKEN) break;
    }
    
    // 重新初始化
    auto stream2 = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(stream2), "test");
    
    auto ast = parser->parse();
    
    if (ast) {
        std::cout << "\n✓ Parse successful\n";
        std::cout << "  Root children: " << ast->getChildren().size() << "\n";
    } else {
        std::cout << "\n✗ Parse failed - null AST\n";
    }
    
    auto errors = context->getErrors();
    if (!errors.empty()) {
        std::cout << "\nErrors:\n";
        for (const auto& error : errors) {
            std::cout << "  - " << error << "\n";
        }
    }
    
    return 0;
}