#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Generator/HtmlGenerator.h"

using namespace chtl;

void testCEEquation() {
    std::cout << "Testing CE Equation (Colon = Equal)\n";
    std::cout << "===================================\n\n";
    
    // 测试1：属性中使用等号
    {
        std::cout << "Test 1: Attributes with '=' instead of ':'\n";
        std::string input = R"(div {
    id = "myDiv";
    class = "container";
    style {
        width = 100px;
        height: 200px;
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
            std::cout << "✓ Parse successful with '=' in attributes\n";
            
            // 生成HTML验证
            HtmlGenerator generator;
            std::ostringstream output;
            generator.generateToStream(ast, output);
            
            std::cout << "Generated HTML:\n" << output.str() << "\n";
        } else {
            std::cout << "✗ Parse failed\n";
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
    }
    
    // 测试2：配置中使用冒号
    {
        std::cout << "\nTest 2: Configuration with ':' instead of '='\n";
        std::string input = R"([Configuration] {
    DEBUG_MODE : true;
    INDEX_INITIAL_COUNT : 0;
    [Name] {
        CUSTOM_STYLE : [@Style, @css];
        TEMPLATE_ELEMENT = @Element;
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
            std::cout << "✓ Parse successful with ':' in configuration\n";
        } else {
            std::cout << "✗ Parse failed\n";
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
    }
    
    // 测试3：模板中混合使用
    {
        std::cout << "\nTest 3: Template with mixed ':' and '='\n";
        std::string input = R"([Template] @Style TextStyle {
    color = black;
    font-size : 16px;
    line-height = 1.6;
}

[Custom] @Style CustomText {
    @Style TextStyle {
        color : red;
        delete font-size;
    }
}

div {
    style {
        @Style CustomText;
        background-color = #f0f0f0;
    }
}
)";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test3");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful with mixed ':' and '=' usage\n";
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
        testCEEquation();
        std::cout << "\n✓ All CE Equation tests completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}