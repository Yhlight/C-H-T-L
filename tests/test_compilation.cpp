#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Node.h"
#include "Node/Comment.h"
#include "Node/Element.h"

using namespace chtl;

bool testBasicCompilation() {
    std::cout << "Test: Basic Compilation" << std::endl;
    
    try {
        // 创建上下文和词法分析器
        auto context = std::make_shared<StandardContext>();
        auto lexer = std::make_shared<StandardLexer>();
        
        // 简单的CHTL代码
        std::string code = "div { p { text \"Hello, CHTL!\" } }";
        
        // 初始化词法分析器
        auto stream = std::make_unique<std::istringstream>(code);
        lexer->initialize(std::move(stream), "test");
        
        // 创建解析器
        auto parser = std::make_shared<StandardParser>(lexer, context);
        
        // 解析代码
        auto ast = parser->parse();
        
        if (ast) {
            std::cout << "  ✓ Successfully parsed basic CHTL code" << std::endl;
            return true;
        } else {
            std::cout << "  ✗ Failed to parse basic CHTL code" << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "  ✗ Exception: " << e.what() << std::endl;
        return false;
    }
}

bool testNodeClassMethods() {
    std::cout << "\nTest: Node Class Methods" << std::endl;
    
    try {
        // 使用Element而不是Node（Node是抽象类）
        auto node = std::make_shared<Element>("div");
        
        // 测试addClass
        node->addClass("container");
        node->addClass("active");
        node->addClass("container"); // 重复添加
        
        auto classes = node->getClasses();
        std::cout << "  Classes after addClass: size=" << classes.size() << " [";
        for (size_t i = 0; i < classes.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << "'" << classes[i] << "'";
        }
        std::cout << "]" << std::endl;
        
        if (classes.size() == 2 && 
            std::find(classes.begin(), classes.end(), "container") != classes.end() &&
            std::find(classes.begin(), classes.end(), "active") != classes.end()) {
            std::cout << "  ✓ addClass works correctly" << std::endl;
        } else {
            std::cout << "  ✗ addClass failed" << std::endl;
            return false;
        }
        
        // 测试removeClass
        node->removeClass("active");
        classes = node->getClasses();
        if (classes.size() == 1 && classes[0] == "container") {
            std::cout << "  ✓ removeClass works correctly" << std::endl;
        } else {
            std::cout << "  ✗ removeClass failed" << std::endl;
            return false;
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cout << "  ✗ Exception: " << e.what() << std::endl;
        return false;
    }
}

bool testCommentNode() {
    std::cout << "\nTest: Comment Node" << std::endl;
    
    try {
        auto comment = std::make_shared<Comment>("This is a CHTL comment");
        
        // 检查类型
        if (comment->getType() != NodeType::COMMENT) {
            std::cout << "  ✗ Wrong node type" << std::endl;
            return false;
        }
        
        // 检查内容
        if (comment->getContent() != "This is a CHTL comment") {
            std::cout << "  ✗ Wrong comment content" << std::endl;
            return false;
        }
        
        // 测试克隆
        auto cloned = std::dynamic_pointer_cast<Comment>(comment->clone());
        if (!cloned || cloned->getContent() != comment->getContent()) {
            std::cout << "  ✗ Clone failed" << std::endl;
            return false;
        }
        
        std::cout << "  ✓ Comment node works correctly" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cout << "  ✗ Exception: " << e.what() << std::endl;
        return false;
    }
}

int main() {
    std::cout << "CHTL Compilation Tests\n";
    std::cout << "======================\n";
    
    int passed = 0;
    int total = 0;
    
    // 运行测试
    if (testBasicCompilation()) passed++; total++;
    if (testNodeClassMethods()) passed++; total++;
    if (testCommentNode()) passed++; total++;
    
    // 总结
    std::cout << "\n======================\n";
    std::cout << "Total: " << total << " tests\n";
    std::cout << "Passed: " << passed << " tests\n";
    std::cout << "Failed: " << (total - passed) << " tests\n";
    
    return (passed == total) ? 0 : 1;
}