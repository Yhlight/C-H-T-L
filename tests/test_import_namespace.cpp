#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Node/Import.h"
#include "Node/Namespace.h"
#include "Node/Template.h"
#include "Node/Custom.h"

using namespace chtl;

void printNode(std::shared_ptr<Node> node, int depth = 0) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    switch (node->getType()) {
        case NodeType::IMPORT: {
            auto import = std::dynamic_pointer_cast<Import>(node);
            std::cout << "[IMPORT] ";
            
            // 打印导入项
            for (const auto& item : import->getImportItems()) {
                std::cout << item;
                if (import->hasAlias(item)) {
                    std::cout << " as " << import->getAlias(item);
                }
            }
            
            std::cout << " from \"" << import->getFilePath() << "\"" << std::endl;
            break;
        }
        
        case NodeType::NAMESPACE: {
            auto ns = std::dynamic_pointer_cast<Namespace>(node);
            std::cout << "[NAMESPACE] " << ns->getNamespaceName() << std::endl;
            break;
        }
        
        case NodeType::ELEMENT: {
            auto element = std::dynamic_pointer_cast<Element>(node);
            std::cout << "<" << element->getTagName() << ">";
            
            // 打印属性
            auto attrs = element->getAttributes();
            if (!attrs.empty()) {
                std::cout << " {";
                bool first = true;
                for (const auto& [key, value] : attrs) {
                    if (!first) std::cout << ", ";
                    std::cout << key << "=";
                    if (std::holds_alternative<std::string>(value)) {
                        std::cout << "\"" << std::get<std::string>(value) << "\"";
                    }
                    first = false;
                }
                std::cout << "}";
            }
            std::cout << std::endl;
            break;
        }
        
        case NodeType::TEMPLATE: {
            auto tmpl = std::dynamic_pointer_cast<Template>(node);
            std::cout << "[TEMPLATE] ";
            switch (tmpl->getTemplateType()) {
                case Template::TemplateType::STYLE:
                    std::cout << "@Style ";
                    break;
                case Template::TemplateType::ELEMENT:
                    std::cout << "@Element ";
                    break;
                case Template::TemplateType::VAR:
                    std::cout << "@Var ";
                    break;
            }
            std::cout << tmpl->getTemplateName() << std::endl;
            break;
        }
        
        case NodeType::CUSTOM: {
            auto custom = std::dynamic_pointer_cast<Custom>(node);
            std::cout << "[CUSTOM] ";
            switch (custom->getCustomType()) {
                case Custom::CustomType::STYLE:
                    std::cout << "@Style ";
                    break;
                case Custom::CustomType::ELEMENT:
                    std::cout << "@Element ";
                    break;
                case Custom::CustomType::VAR:
                    std::cout << "@Var ";
                    break;
            }
            std::cout << custom->getCustomName() << std::endl;
            break;
        }
        
        default:
            std::cout << "[" << static_cast<int>(node->getType()) << "]" << std::endl;
            break;
    }
    
    // 递归打印子节点
    for (const auto& child : node->getChildren()) {
        printNode(child, depth + 1);
    }
}

int main() {
    // 测试Import语句
    std::string test1 = R"(
[Import] @Html from "components/header.html";
[Import] @Style from "styles/main.css" as mainStyles;
[Import] @JavaScript from "scripts/utils.js";

[Import] [Custom] @Element Box from "components.chtl" as MyBox;
[Import] [Template] @Style DefaultTheme from "themes.chtl";

[Import] @Chtl from components.ui.buttons;
[Import] * from "utils.chtl";
)";

    // 测试Namespace语句
    std::string test2 = R"(
[Namespace] UI {
    [Template] @Element Button {
        button {
            class: ui-button;
        }
    }
    
    [Custom] @Style ButtonStyle {
        background-color,
        border-radius;
    }
}

[Namespace] Components

[Custom] @Element Card {
    div {
        class: card;
    }
}
)";

    // 测试使用命名空间
    std::string test3 = R"(
[Import] @Chtl from "ui.chtl";

body {
    @Element Button from UI;
    
    div {
        @Style ButtonStyle from UI {
            background-color: blue;
            border-radius: 4px;
        }
    }
}
)";

    // 测试嵌套命名空间
    std::string test4 = R"(
[Namespace] App {
    [Namespace] UI {
        [Namespace] Buttons {
            [Template] @Element PrimaryButton {
                button {
                    class: primary-button;
                }
            }
        }
    }
    
    [Namespace] Data {
        [Template] @Var ApiEndpoints {
            baseUrl: "https://api.example.com";
            timeout: "5000";
        }
    }
}

body {
    @Element PrimaryButton from App.UI.Buttons;
}
)";

    std::vector<std::pair<std::string, std::string>> tests = {
        {"Import Test", test1},
        {"Namespace Test", test2},
        {"Using Namespace Test", test3},
        {"Nested Namespace Test", test4}
    };
    
    for (const auto& [name, code] : tests) {
        std::cout << "\n=== " << name << " ===" << std::endl;
        std::cout << "Input:\n" << code << "\n---" << std::endl;
        
        auto lexer = std::make_shared<StandardLexer>();
        auto stream = std::make_unique<std::istringstream>(code);
        lexer->initialize(std::move(stream), "test.chtl");
        
        StandardParser parser;
        parser.initialize(lexer, lexer->getContext());
        
        auto ast = parser.parse();
        
        if (parser.hasErrors()) {
            std::cout << "Parse errors:" << std::endl;
            for (const auto& error : parser.getErrors()) {
                std::cout << "  " << error.message << std::endl;
            }
        }
        
        std::cout << "\nAST:" << std::endl;
        if (ast) {
            printNode(ast);
        }
    }
    
    return 0;
}