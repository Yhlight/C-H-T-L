#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Import.h"

using namespace chtl;

void testImportSyntax() {
    std::cout << "Testing Import Syntax\n";
    std::cout << "====================\n\n";
    
    // 测试1：导入HTML文件
    {
        std::cout << "Test 1: Import HTML file\n";
        std::string input = "[Import] @Html from \"index.html\" as HomePage;\n";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test1");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
            
            // 检查Import节点
            if (ast->getChildren().size() > 0) {
                auto importNode = std::dynamic_pointer_cast<Import>(ast->getChildren()[0]);
                if (importNode) {
                    std::cout << "  Type: " << static_cast<int>(importNode->getType()) << " (HTML=" 
                              << static_cast<int>(Import::ImportType::HTML) << ")\n";
                    std::cout << "  Path: " << importNode->getPath() << "\n";
                    std::cout << "  Alias: " << importNode->getAlias() << "\n";
                }
            }
        } else {
            std::cout << "✗ Parse failed\n";
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
    }
    
    // 测试2：导入CSS文件
    {
        std::cout << "\nTest 2: Import CSS file\n";
        std::string input = "[Import] @Style from \"styles/main.css\";\n";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test2");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
        } else {
            std::cout << "✗ Parse failed\n";
        }
    }
    
    // 测试3：导入自定义元素
    {
        std::cout << "\nTest 3: Import custom element\n";
        std::string input = "[Import] [Custom] @Element Button from \"components.chtl\" as MyButton;\n";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test3");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
            
            if (ast->getChildren().size() > 0) {
                auto importNode = std::dynamic_pointer_cast<Import>(ast->getChildren()[0]);
                if (importNode) {
                    std::cout << "  Type: " << static_cast<int>(importNode->getType()) << " (CUSTOM_ELEMENT=" 
                              << static_cast<int>(Import::ImportType::CUSTOM_ELEMENT) << ")\n";
                    std::cout << "  Name: " << importNode->getName() << "\n";
                    std::cout << "  Path: " << importNode->getPath() << "\n";
                    std::cout << "  Alias: " << importNode->getAlias() << "\n";
                }
            }
        } else {
            std::cout << "✗ Parse failed\n";
        }
    }
    
    // 测试4：通配符导入
    {
        std::cout << "\nTest 4: Wildcard import\n";
        std::string input = "[Import] * from \"utils.chtl\";\n";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test4");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
            
            if (ast->getChildren().size() > 0) {
                auto importNode = std::dynamic_pointer_cast<Import>(ast->getChildren()[0]);
                if (importNode) {
                    std::cout << "  Type: " << static_cast<int>(importNode->getType()) << " (ALL=" 
                              << static_cast<int>(Import::ImportType::ALL) << ")\n";
                    std::cout << "  Path: " << importNode->getPath() << "\n";
                }
            }
        } else {
            std::cout << "✗ Parse failed\n";
        }
    }
    
    // 测试5：路径中使用.代替/
    {
        std::cout << "\nTest 5: Path with dots\n";
        std::string input = "[Import] @JavaScript from \"libs.utils.helpers.js\";\n";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test5");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
            
            if (ast->getChildren().size() > 0) {
                auto importNode = std::dynamic_pointer_cast<Import>(ast->getChildren()[0]);
                if (importNode) {
                    std::cout << "  Path: " << importNode->getPath() << " (should be libs/utils/helpers/js)\n";
                }
            }
        } else {
            std::cout << "✗ Parse failed\n";
        }
    }
    
    // 测试6：导入整个CHTL文件
    {
        std::cout << "\nTest 6: Import entire CHTL file\n";
        std::string input = "[Import] @Chtl from \"components.chtl\";\n";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test6");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
        } else {
            std::cout << "✗ Parse failed\n";
        }
    }
}

int main() {
    try {
        testImportSyntax();
        std::cout << "\n✓ All import syntax tests completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}