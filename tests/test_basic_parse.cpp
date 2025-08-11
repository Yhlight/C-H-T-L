#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Custom.h"

using namespace chtl;

int main() {
    std::string input = "[Custom] @Style TextSet {\n    color,\n    font-size;\n}";
    
    std::cout << "Input:\n" << input << "\n\n";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    auto parser = std::make_shared<StandardParser>(lexer, context);
    
    auto stream = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(stream), "test");
    
    // 打印前几个token
    std::cout << "First few tokens:\n";
    for (int i = 0; i < 5; i++) {
        auto token = lexer->getNextToken();
        std::cout << "  Token " << i << ": type=" << static_cast<int>(token.type) 
                  << " value='" << token.value << "' line=" << token.line << "\n";
        if (token.type == TokenType::EOF_TOKEN) break;
    }
    
    // 重新初始化
    auto stream2 = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(stream2), "test");
    
    auto ast = parser->parse();
    
    if (ast) {
        std::cout << "✓ Parse successful\n";
        std::cout << "  Root type: " << static_cast<int>(ast->getType()) << "\n";
        std::cout << "  Children: " << ast->getChildren().size() << "\n";
        
        for (const auto& child : ast->getChildren()) {
            std::cout << "    Child type: " << static_cast<int>(child->getType()) << "\n";
            if (child->getType() == NodeType::CUSTOM) {
                auto custom = std::static_pointer_cast<Custom>(child);
                std::cout << "      Name: " << custom->getCustomName() << "\n";
                std::cout << "      Type: " << static_cast<int>(custom->getCustomType()) << "\n";
                
                auto props = custom->getProperties();
                std::cout << "      Properties: " << props.size() << "\n";
                for (const auto& [name, value] : props) {
                    std::cout << "        " << name << " = '" << value << "'\n";
                }
            }
        }
    } else {
        std::cout << "✗ Parse failed - null AST\n";
    }
    
    if (!context->getErrors().empty()) {
        std::cout << "\nErrors:\n";
        for (const auto& error : context->getErrors()) {
            std::cout << "  - " << error << "\n";
        }
    }
    
    return 0;
}