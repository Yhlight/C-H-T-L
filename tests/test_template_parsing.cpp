#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Generator/HtmlGenerator.h"
#include "Node/Template.h"
#include "Node/Custom.h"

using namespace chtl;

void printNode(std::shared_ptr<Node> node, int depth = 0) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    switch (node->getType()) {
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
            std::cout << tmpl->getTemplateName();
            
            // 打印参数
            auto params = tmpl->getParameters();
            if (!params.empty()) {
                std::cout << " {";
                bool first = true;
                for (const auto& [key, value] : params) {
                    if (!first) std::cout << ", ";
                    std::cout << key << ": " << value;
                    first = false;
                }
                std::cout << "}";
            }
            
            // 打印继承
            auto inherits = tmpl->getInheritance();
            if (!inherits.empty()) {
                std::cout << " inherits: [";
                bool first = true;
                for (const auto& inherit : inherits) {
                    if (!first) std::cout << ", ";
                    std::cout << inherit;
                    first = false;
                }
                std::cout << "]";
            }
            
            std::cout << std::endl;
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
            std::cout << custom->getCustomName();
            
            // 打印属性
            auto props = custom->getProperties();
            if (!props.empty()) {
                std::cout << " {";
                bool first = true;
                for (const auto& [key, value] : props) {
                    if (!first) std::cout << ", ";
                    std::cout << key;
                    if (!value.empty()) {
                        std::cout << ": " << value;
                    }
                    first = false;
                }
                std::cout << "}";
            }
            
            std::cout << std::endl;
            break;
        }
        
        case NodeType::TEXT: {
            auto text = std::dynamic_pointer_cast<Text>(node);
            std::cout << "[TEXT] \"" << text->getData() << "\"" << std::endl;
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
    // 测试样式模板
    std::string test1 = R"(
[Template] @Style DefaultText {
    color: black;
    line-height: 1.6;
    font-size: 16px;
}

[Template] @Style HeaderText {
    inherit @Style DefaultText;
    font-size: 24px;
    font-weight: bold;
}

div {
    style {
        @Style DefaultText;
    }
    
    h1 {
        style {
            @Style HeaderText;
        }
        text { "Hello Template" }
    }
}
)";

    // 测试元素模板
    std::string test2 = R"(
[Template] @Element Box {
    div {
        class: box-container;
        style {
            padding: 20px;
            border: 1px solid #ccc;
        }
        
        span {
            class: box-content;
        }
    }
}

body {
    @Element Box;
}
)";

    // 测试变量模板和自定义
    std::string test3 = 
"[Template] @Var ThemeColors {\n"
"    primaryColor: \"rgb(255, 192, 203)\";\n"
"    secondaryColor: \"rgb(253, 144, 162)\";\n"
"    textColor: \"black\";\n"
"}\n"
"\n"
"[Custom] @Style ColoredText {\n"
"    color,\n"
"    background-color;\n"
"}\n"
"\n"
"div {\n"
"    style {\n"
"        @Style ColoredText;\n"
"    }\n"
"}";

    std::vector<std::pair<std::string, std::string>> tests = {
        {"Style Template Test", test1},
        {"Element Template Test", test2},
        {"Variable Template and Custom Test", test3}
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