#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Namespace.h"
#include "Node/Custom.h"

using namespace chtl;

void testNamespace() {
    std::cout << "Testing Namespace Features\n";
    std::cout << "==========================\n\n";
    
    // 测试1：基本命名空间
    {
        std::cout << "Test 1: Basic namespace\n";
        std::string input = R"(
[Namespace] space {
    [Custom] @Element Box {
        div {
            style {
                width: 100px;
            }
        }
    }
}

div {
    @Element Box from space;
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
            
            // 打印命名空间树
            auto nsManager = context->getNamespaceManager();
            if (nsManager) {
                nsManager->printNamespaceTree();
            }
        } else {
            std::cout << "✗ Parse failed\n";
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
    }
    
    // 测试2：嵌套命名空间
    {
        std::cout << "\nTest 2: Nested namespace\n";
        std::string input = R"(
[Namespace] space {
    [Namespace] room {
        [Custom] @Element Box {
            div {
                style {
                    background: blue;
                }
            }
        }
    }
    
    [Namespace] room2 {
        [Custom] @Element Box {
            div {
                style {
                    background: red;
                }
            }
        }
    }
}

body {
    @Element Box from space.room2;
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
            
            auto nsManager = context->getNamespaceManager();
            if (nsManager) {
                nsManager->printNamespaceTree();
            }
        } else {
            std::cout << "✗ Parse failed\n";
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
        
        // 打印警告
        auto warnings = context->getWarnings();
        if (!warnings.empty()) {
            std::cout << "\nWarnings:\n";
            for (const auto& warning : warnings) {
                std::cout << "  - " << warning << "\n";
            }
        }
    }
    
    // 测试3：同名命名空间合并
    {
        std::cout << "\nTest 3: Namespace merging\n";
        std::string input = R"(
[Namespace] utils {
    [Custom] @Style TextStyle {
        color: black;
        font-size: 16px;
    }
}

[Namespace] utils {
    [Custom] @Element Button {
        button {
            style {
                @Style TextStyle;
            }
        }
    }
}

div {
    @Style TextStyle from utils;
}
)";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test3");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
            
            auto nsManager = context->getNamespaceManager();
            if (nsManager) {
                nsManager->printNamespaceTree();
                
                // 检测冲突
                auto conflicts = nsManager->detectConflicts();
                if (!conflicts.empty()) {
                    std::cout << "\nConflicts detected:\n";
                    for (const auto& conflict : conflicts) {
                        std::cout << "  - " << conflict.description << "\n";
                    }
                }
            }
        } else {
            std::cout << "✗ Parse failed\n";
            for (const auto& error : context->getErrors()) {
                std::cout << "  Error: " << error << "\n";
            }
        }
    }
    
    // 测试4：简化的嵌套语法
    {
        std::cout << "\nTest 4: Simplified nested namespace syntax\n";
        std::string input = R"(
[Namespace] space
[Namespace] room

[Custom] @Element Box {
    div {
        style {
            width: 200px;
        }
    }
}
)";
        
        auto lexer = std::make_shared<StandardLexer>();
        auto context = std::make_shared<StandardContext>();
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        auto stream = std::make_unique<std::istringstream>(input);
        lexer->initialize(std::move(stream), "test4");
        
        auto ast = parser->parse();
        if (ast && context->getErrors().empty()) {
            std::cout << "✓ Parse successful\n";
            
            auto nsManager = context->getNamespaceManager();
            if (nsManager) {
                nsManager->printNamespaceTree();
            }
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
        testNamespace();
        std::cout << "\n✓ All namespace tests completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}