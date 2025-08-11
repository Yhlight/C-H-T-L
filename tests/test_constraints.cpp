#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Utils/ConstraintValidator.h"

using namespace chtl;

void testConstraints() {
    std::cout << "Testing Constraint Features\n";
    std::cout << "===========================\n\n";
    
    // 测试1：精确约束
    {
        std::cout << "Test 1: Precise constraints\n";
        std::string input = R"(
div {
    except span, [Custom] @Element Box;
    
    p { }       // OK
    span { }    // Violation!
}
)";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test1");
        
        auto ast = parser->parse();
        if (ast) {
            std::cout << "✓ Parse successful\n";
            
            // 验证约束
            bool valid = context->validateConstraints(ast);
            std::cout << "Constraint validation: " << (valid ? "PASSED" : "FAILED") << "\n";
            
            if (!valid) {
                auto validator = context->getConstraintValidator();
                auto violations = validator->getViolations();
                std::cout << "Violations found: " << violations.size() << "\n";
                for (const auto& v : violations) {
                    std::cout << "  - " << v.violations[0] << "\n";
                }
            }
        } else {
            std::cout << "✗ Parse failed\n";
        }
        
        // 打印错误
        auto errors = context->getErrors();
        if (!errors.empty()) {
            std::cout << "\nErrors:\n";
            for (const auto& error : errors) {
                std::cout << "  - " << error << "\n";
            }
        }
    }
    
    // 测试2：类型约束
    {
        std::cout << "\nTest 2: Type constraints\n";
        std::string input = R"(
div {
    except @Html;
    except [Template] @Var;
    
    [Template] @Style TextStyle { }     // OK
    [Template] @Var ThemeColor { }      // Violation!
    span { }                            // Violation!
}
)";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test2");
        
        auto ast = parser->parse();
        if (ast) {
            std::cout << "✓ Parse successful\n";
            
            bool valid = context->validateConstraints(ast);
            std::cout << "Constraint validation: " << (valid ? "PASSED" : "FAILED") << "\n";
        } else {
            std::cout << "✗ Parse failed\n";
        }
        
        auto errors = context->getErrors();
        if (!errors.empty()) {
            std::cout << "\nErrors:\n";
            for (const auto& error : errors) {
                std::cout << "  - " << error << "\n";
            }
        }
    }
    
    // 测试3：全局约束
    {
        std::cout << "\nTest 3: Global constraints in namespace\n";
        std::string input = R"(
[Namespace] space {
    except [Template];
    
    [Custom] @Element Box { }     // OK
    [Template] @Style Text { }    // Violation!
}
)";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test3");
        
        auto ast = parser->parse();
        if (ast) {
            std::cout << "✓ Parse successful\n";
            
            bool valid = context->validateConstraints(ast);
            std::cout << "Constraint validation: " << (valid ? "PASSED" : "FAILED") << "\n";
        } else {
            std::cout << "✗ Parse failed\n";
        }
        
        auto errors = context->getErrors();
        if (!errors.empty()) {
            std::cout << "\nErrors:\n";
            for (const auto& error : errors) {
                std::cout << "  - " << error << "\n";
            }
        }
    }
    
    // 测试4：混合约束
    {
        std::cout << "\nTest 4: Mixed constraints\n";
        std::string input = R"(
[Custom] @Element Container {
    except [Custom], span;
    
    div {
        p { }                       // OK
        span { }                    // Violation!
    }
    
    [Custom] @Style MyStyle { }     // Violation!
}
)";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test4");
        
        auto ast = parser->parse();
        if (ast) {
            std::cout << "✓ Parse successful\n";
            
            bool valid = context->validateConstraints(ast);
            std::cout << "Constraint validation: " << (valid ? "PASSED" : "FAILED") << "\n";
            
            auto validator = context->getConstraintValidator();
            auto violations = validator->getViolations();
            std::cout << "Total violations: " << violations.size() << "\n";
        } else {
            std::cout << "✗ Parse failed\n";
        }
        
        auto errors = context->getErrors();
        if (!errors.empty()) {
            std::cout << "\nErrors:\n";
            for (const auto& error : errors) {
                std::cout << "  - " << error << "\n";
            }
        }
    }
}

int main() {
    try {
        testConstraints();
        std::cout << "\n✓ All constraint tests completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}