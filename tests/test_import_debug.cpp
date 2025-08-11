#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Import.h"

using namespace chtl;

int main() {
    std::string input = "[Import] @Html from \"index.html\" as HomePage;\n";
    
    std::cout << "Input: " << input << "\n";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    
    auto stream = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(stream), "test");
    
    // 打印token序列
    std::cout << "\nTokens:\n";
    for (int i = 0; i < 15; i++) {
        auto token = lexer->getNextToken();
        std::cout << "  " << i << ": type=" << static_cast<int>(token.type);
        
        // 打印token类型名称
        if (token.type == TokenType::IMPORT) std::cout << " (IMPORT)";
        else if (token.type == TokenType::AT_HTML) std::cout << " (AT_HTML)";
        else if (token.type == TokenType::FROM) std::cout << " (FROM)";
        else if (token.type == TokenType::AS) std::cout << " (AS)";
        else if (token.type == TokenType::IDENTIFIER) std::cout << " (IDENTIFIER)";
        else if (token.type == TokenType::STRING_LITERAL) std::cout << " (STRING_LITERAL)";
        else if (token.type == TokenType::SEMICOLON) std::cout << " (SEMICOLON)";
        else if (token.type == TokenType::EOF_TOKEN) std::cout << " (EOF)";
        
        std::cout << " value='" << token.value << "'\n";
        if (token.type == TokenType::EOF_TOKEN) break;
    }
    
    // 重新初始化解析
    auto stream2 = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(stream2), "test");
    
    auto parser = std::make_shared<StandardParser>(lexer, context);
    auto ast = parser->parse();
    
    if (ast) {
        std::cout << "\n✓ Parse successful\n";
        std::cout << "  AST type: " << static_cast<int>(ast->getType()) << "\n";
        std::cout << "  AST tag: " << ast->getTagName() << "\n";
        std::cout << "  Children: " << ast->getChildren().size() << "\n";
        
        // 递归打印AST
        std::function<void(std::shared_ptr<Node>, int)> printAST = 
            [&](std::shared_ptr<Node> node, int depth) {
                std::string indent(depth * 2, ' ');
                std::cout << indent << "- Type: " << static_cast<int>(node->getType())
                          << " Tag: " << node->getTagName() << "\n";
                
                auto importNode = std::dynamic_pointer_cast<Import>(node);
                if (importNode) {
                    std::cout << indent << "  Import type: " << static_cast<int>(importNode->getType()) << "\n";
                    std::cout << indent << "  Import path: " << importNode->getPath() << "\n";
                    std::cout << indent << "  Import alias: " << importNode->getAlias() << "\n";
                }
                
                for (const auto& child : node->getChildren()) {
                    printAST(child, depth + 1);
                }
            };
        
        for (const auto& child : ast->getChildren()) {
            printAST(child, 1);
        }
    } else {
        std::cout << "\n✗ Parse failed\n";
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