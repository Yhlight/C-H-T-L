#include <iostream>
#include <memory>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Import.h"

using namespace chtl;

void testImportParsing() {
    std::cout << "Testing Import Parsing\n";
    std::cout << "=====================\n";
    
    // 测试输入
    std::string input = R"(
Import @Chtl from "moduleA"
Import @Chtl from "moduleB"
div { class "test" }
)";
    
    // 创建解析器
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    auto parser = std::make_shared<StandardParser>(lexer, context);
    
    // 初始化词法分析器
    auto iss = std::make_unique<std::istringstream>(input);
    lexer->initialize(std::move(iss), "test");
    
    // 解析
    auto ast = parser->parse();
    
    if (!ast) {
        std::cout << "✗ Failed to parse\n";
        return;
    }
    
    std::cout << "✓ Parse successful\n";
    
    // 查找Import节点
    int importCount = 0;
    int totalNodes = 0;
    std::function<void(std::shared_ptr<Node>, int)> findImports = [&](std::shared_ptr<Node> node, int depth) {
        if (!node) return;
        
        totalNodes++;
        std::string indent(depth * 2, ' ');
        std::cout << indent << "Node type: " << static_cast<int>(node->getType()) 
                  << " (" << node->getTagName() << ")";
        
        if (node->getType() == NodeType::ELEMENT) {
            auto elem = std::static_pointer_cast<Element>(node);
            std::cout << " tag=" << elem->getTagName();
        }
        
        std::cout << " children=" << node->getChildren().size() << "\n";
        
        if (node->getType() == NodeType::IMPORT) {
            importCount++;
            auto importNode = std::static_pointer_cast<Import>(node);
            std::cout << indent << "  Found Import: " << importNode->getPath() << "\n";
        }
        
        for (const auto& child : node->getChildren()) {
            findImports(child, depth + 1);
        }
    };
    
    findImports(ast, 0);
    
    std::cout << "\nTotal nodes: " << totalNodes << "\n";
    std::cout << "Total imports found: " << importCount << "\n";
    
    // 打印错误
    auto errors = context->getErrors();
    if (!errors.empty()) {
        std::cout << "\nParse errors:\n";
        for (const auto& error : errors) {
            std::cout << "  - " << error << "\n";
        }
    }
}

int main() {
    try {
        testImportParsing();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}