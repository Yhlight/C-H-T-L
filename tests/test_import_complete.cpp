#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Loader/ImportProcessor.h"
#include "Node/Import.h"
#include "Node/Origin.h"
#include "Generator/HtmlGenerator.h"

using namespace chtl;

void testImportComplete() {
    std::cout << "Testing Complete Import Functionality\n";
    std::cout << "====================================\n\n";
    
    // CHTL代码示例
    std::string chtlCode = R"(
[Import] @Html from "layout.html" as layout;
[Import] @Style from "theme.css";
[Import] @Style from "custom.css" as customStyles;
[Import] @JavaScript from "utils.js";
[Import] @JavaScript from "app.js" as appModule;

div {
    h1 { "Welcome" }
    
    // 使用导入的HTML
    [Origin] @Html layout;
    
    // 使用导入的样式
    [Origin] @Style customStyles;
    
    // 使用导入的JS
    [Origin] @JavaScript appModule;
}
)";
    
    // 创建词法分析器、上下文和解析器
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    // 解析CHTL代码
    auto input = std::make_unique<std::istringstream>(chtlCode);
    lexer->initialize(std::move(input), "test.chtl");
    
    auto ast = parser.parse();
    
    if (!ast) {
        std::cout << "✗ Parse failed\n";
        for (const auto& error : context->getErrors()) {
            std::cout << "  Error: " << error << "\n";
        }
        return;
    }
    
    std::cout << "✓ Parse successful\n";
    
    // 处理导入节点
    ImportProcessor processor(context);
    int importCount = 0;
    int originCount = 0;
    
    // 递归遍历AST
    std::function<void(std::shared_ptr<Node>)> processNode = [&](std::shared_ptr<Node> node) {
        if (auto importNode = std::dynamic_pointer_cast<Import>(node)) {
            importCount++;
            std::cout << "\nProcessing Import #" << importCount << ":\n";
            std::string typeName;
            switch(importNode->getType()) {
                case Import::ImportType::HTML: typeName = "HTML"; break;
                case Import::ImportType::CSS: typeName = "CSS"; break;
                case Import::ImportType::JS: typeName = "JS"; break;
                case Import::ImportType::CHTL: typeName = "CHTL"; break;
                default: typeName = "Unknown"; break;
            }
            std::cout << "  Type: " << typeName << " (" << static_cast<int>(importNode->getType()) << ")\n";
            std::cout << "  Path: " << importNode->getPath() << "\n";
            std::cout << "  Alias: " << importNode->getAlias() << "\n";
            
            // 注意：这里只是演示，实际使用时需要提供正确的当前文件路径
            auto result = processor.processImport(importNode, "test.chtl");
            std::cout << "  Result: " << (result.success ? "SUCCESS" : "FAILED") << "\n";
            if (!result.errors.empty()) {
                for (const auto& err : result.errors) {
                    std::cout << "  Error: " << err << "\n";
                }
            }
            std::cout << "  Generated " << result.generatedNodes.size() << " nodes\n";
        }
        else if (auto originNode = std::dynamic_pointer_cast<Origin>(node)) {
            originCount++;
            std::cout << "\nFound Origin #" << originCount << ":\n";
            std::cout << "  Type: " << static_cast<int>(originNode->getType()) << "\n";
            
            // 获取name属性
            auto nameAttr = node->getAttribute("name");
            if (std::holds_alternative<std::string>(nameAttr)) {
                std::cout << "  Name: " << std::get<std::string>(nameAttr) << "\n";
            }
        }
        
        // 递归处理子节点
        for (const auto& child : node->getChildren()) {
            processNode(child);
        }
    };
    
    processNode(ast);
    
    std::cout << "\n--- Summary ---\n";
    std::cout << "Total imports found: " << importCount << "\n";
    std::cout << "Total origin references found: " << originCount << "\n";
    
    // 生成HTML查看结果
    std::cout << "\n--- Generated HTML ---\n";
    HtmlGenerator generator;
    std::ostringstream output;
    generator.generateToStream(ast, output);
    std::cout << output.str() << "\n";
}

int main() {
    try {
        testImportComplete();
        std::cout << "\n✓ Complete import test finished\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}