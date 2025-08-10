#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Loader/ImportProcessor.h"
#include "Node/Import.h"
#include "Node/Custom.h"
#include "Node/Template.h"
#include "Generator/HtmlGenerator.h"

using namespace chtl;
namespace fs = std::filesystem;

void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

void testSpecificImports() {
    std::cout << "Testing Specific CHTL Imports\n";
    std::cout << "=============================\n\n";
    
    // 创建一个包含Custom和Template元素的CHTL文件
    std::string moduleContent = R"([Custom] @Element Card {
    div {
        class: "card";
        h2 { "Card Title" }
        p { "Card content" }
    }
}

[Custom] @Style CardStyle {
    background-color: #ffffff;
    border: 1px solid #ddd;
    border-radius: 8px;
    padding: 16px;
}

[Custom] @Var CardColors {
    primary: #007bff;
    secondary: #6c757d;
    success: #28a745;
}

[Template] @Element Modal(title, content) {
    div {
        class: "modal";
        div {
            class: "modal-header";
            h3 { {{title}} }
        }
        div {
            class: "modal-body";
            {{content}}
        }
    }
}

[Template] @Style ButtonStyle(color) {
    background-color: {{color}};
    color: white;
    border: none;
    padding: 8px 16px;
}

[Template] @Var ThemeColors(primary, secondary) {
    main: {{primary}};
    accent: {{secondary}};
}
)";
    
    createTestFile("components.chtl", moduleContent);
    
    // 测试导入各种类型的元素
    std::string testCode = R"([Import] [Custom] @Element Card from "components.chtl" as MyCard;
[Import] [Custom] @Style CardStyle from "components.chtl";
[Import] [Custom] @Var CardColors from "components.chtl" as MyColors;
[Import] [Template] @Element Modal from "components.chtl" as MyModal;
[Import] [Template] @Style ButtonStyle from "components.chtl";
[Import] [Template] @Var ThemeColors from "components.chtl" as MyTheme;

div {
    // 使用导入的Custom元素
    [Custom] @Element MyCard;
    
    // 使用导入的Template
    [Template] @Element MyModal("Welcome", "This is a modal dialog");
}
)";
    
    // 解析测试代码
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(testCode);
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
    
    // 处理导入
    ImportProcessor processor(context);
    int importCount = 0;
    int customCount = 0;
    int templateCount = 0;
    
    // 递归遍历AST处理导入
    std::function<void(std::shared_ptr<Node>)> processNode = [&](std::shared_ptr<Node> node) {
        if (auto importNode = std::dynamic_pointer_cast<Import>(node)) {
            importCount++;
            std::cout << "\nProcessing Import #" << importCount << ":\n";
            
            std::string typeName;
            switch(importNode->getType()) {
                case Import::ImportType::CUSTOM_ELEMENT:
                    typeName = "[Custom] @Element"; break;
                case Import::ImportType::CUSTOM_STYLE:
                    typeName = "[Custom] @Style"; break;
                case Import::ImportType::CUSTOM_VAR:
                    typeName = "[Custom] @Var"; break;
                case Import::ImportType::TEMPLATE_ELEMENT:
                    typeName = "[Template] @Element"; break;
                case Import::ImportType::TEMPLATE_STYLE:
                    typeName = "[Template] @Style"; break;
                case Import::ImportType::TEMPLATE_VAR:
                    typeName = "[Template] @Var"; break;
                default:
                    typeName = "Unknown"; break;
            }
            
            std::cout << "  Type: " << typeName << " " << importNode->getName() << "\n";
            std::cout << "  Path: " << importNode->getPath() << "\n";
            std::cout << "  Alias: " << importNode->getAlias() << "\n";
            
            auto result = processor.processImport(importNode, ".");
            std::cout << "  Result: " << (result.success ? "SUCCESS" : "FAILED") << "\n";
            
            if (!result.errors.empty()) {
                for (const auto& err : result.errors) {
                    std::cout << "  Error: " << err << "\n";
                }
            }
            
            std::cout << "  Generated " << result.generatedNodes.size() << " nodes\n";
            
            // 将生成的节点添加到AST根节点
            for (const auto& genNode : result.generatedNodes) {
                ast->addChild(genNode);
                
                if (std::dynamic_pointer_cast<Custom>(genNode)) {
                    customCount++;
                } else if (std::dynamic_pointer_cast<Template>(genNode)) {
                    templateCount++;
                }
            }
        }
        
        // 递归处理子节点
        for (const auto& child : node->getChildren()) {
            processNode(child);
        }
    };
    
    processNode(ast);
    
    std::cout << "\n--- Summary ---\n";
    std::cout << "Total imports processed: " << importCount << "\n";
    std::cout << "Custom nodes imported: " << customCount << "\n";
    std::cout << "Template nodes imported: " << templateCount << "\n";
    
    // 生成HTML查看结果
    std::cout << "\n--- Generated HTML ---\n";
    HtmlGenerator generator;
    std::ostringstream output;
    generator.generateToStream(ast, output);
    std::cout << output.str() << "\n";
    
    // 清理测试文件
    fs::remove("components.chtl");
}

int main() {
    try {
        testSpecificImports();
        std::cout << "\n✓ Specific imports test completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}