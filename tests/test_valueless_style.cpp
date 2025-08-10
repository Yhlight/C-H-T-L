#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Generator/HtmlGenerator.h"
#include "Node/Custom.h"

using namespace chtl;

void testValuelessStyle() {
    std::cout << "Testing Valueless Style Groups\n";
    std::cout << "==============================\n\n";
    
    // 测试1：基本无值样式组
    {
        std::cout << "Test 1: Basic valueless style group\n";
        std::string input = R"([Custom] @Style TextSet {
    color,
    font-size;
}

div {
    style {
        @Style TextSet {
            color: red;
            font-size: 16px;
        }
    }
}
)";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test1");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
            
            // 简单打印AST结构
            std::cout << "  AST children count: " << ast->getChildren().size() << "\n";
        } else {
            std::cout << "✗ Parse failed\n";
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
    }
    
    // 测试2：在自定义样式中使用无值样式组
    {
        std::cout << "\nTest 2: Using valueless style in another custom style\n";
        std::string input = R"([Custom] @Style TextSet {
    color,
    font-size;
}

[Custom] @Style WhiteText {
    @Style TextSet {
        color: white;
        font-size: 16px;
    }
}
)";
        
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
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
    }
}





int main() {
    try {
        testValuelessStyle();
        std::cout << "\n✓ All valueless style tests completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}