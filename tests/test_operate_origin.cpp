#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Node/Operate.h"
#include "Node/Origin.h"
#include "Node/Template.h"
#include "Node/Custom.h"

using namespace chtl;

void printNode(std::shared_ptr<Node> node, int depth = 0) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    switch (node->getType()) {
        case NodeType::OPERATE: {
            auto operate = std::dynamic_pointer_cast<Operate>(node);
            std::cout << "[OPERATE] ";
            
            switch (operate->getOperationType()) {
                case Operate::OperationType::INSERT:
                    std::cout << "INSERT ";
                    break;
                case Operate::OperationType::DELETE:
                    std::cout << "DELETE ";
                    break;
                case Operate::OperationType::REPLACE:
                    std::cout << "REPLACE ";
                    break;
                default:
                    break;
            }
            
            if (operate->getPosition() != Operate::Position::DEFAULT) {
                switch (operate->getPosition()) {
                    case Operate::Position::BEFORE:
                        std::cout << "BEFORE ";
                        break;
                    case Operate::Position::AFTER:
                        std::cout << "AFTER ";
                        break;
                    case Operate::Position::AT:
                        std::cout << "AT ";
                        break;
                    case Operate::Position::TOP:
                        std::cout << "TOP ";
                        break;
                    case Operate::Position::BOTTOM:
                        std::cout << "BOTTOM ";
                        break;
                    default:
                        break;
                }
            }
            
            std::cout << operate->getSelector();
            
            // 打印约束（用于delete的额外目标）
            if (!operate->getConstraints().empty()) {
                std::cout << " (also: ";
                bool first = true;
                for (const auto& constraint : operate->getConstraints()) {
                    if (!first) std::cout << ", ";
                    std::cout << constraint;
                    first = false;
                }
                std::cout << ")";
            }
            
            std::cout << std::endl;
            
            // 打印内容（如果有）
            if (operate->getContent()) {
                printNode(operate->getContent(), depth + 1);
            }
            break;
        }
        
        case NodeType::ORIGIN: {
            auto origin = std::dynamic_pointer_cast<Origin>(node);
            std::cout << "[ORIGIN] ";
            
            switch (origin->getOriginType()) {
                case Origin::OriginType::HTML:
                    std::cout << "@Html";
                    break;
                case Origin::OriginType::STYLE:
                    std::cout << "@Style";
                    break;
                case Origin::OriginType::JAVASCRIPT:
                    std::cout << "@JavaScript";
                    break;
            }
            
            if (!origin->getOriginName().empty()) {
                std::cout << " " << origin->getOriginName();
            }
            
            if (origin->isInline()) {
                std::cout << " (inline)";
            }
            
            std::cout << " content: \"" << origin->getContent() << "\"" << std::endl;
            break;
        }
        
        case NodeType::ELEMENT: {
            auto element = std::dynamic_pointer_cast<Element>(node);
            std::cout << "<" << element->getTagName() << ">";
            
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
        
        case NodeType::CUSTOM: {
            auto custom = std::dynamic_pointer_cast<Custom>(node);
            std::cout << "[CUSTOM] ";
            switch (custom->getCustomType()) {
                case Custom::CustomType::ELEMENT:
                    std::cout << "@Element ";
                    break;
                case Custom::CustomType::STYLE:
                    std::cout << "@Style ";
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
    // 测试Operate操作
    std::string test1 = R"(
[Custom] @Element Box {
    div {
        class: box;
    }
    span {
        class: content;
    }
}

body {
    @Element Box {
        delete span;
        delete div[1];
        
        insert after div[0] {
            div {
                class: new-div;
                text { "Inserted content" }
            }
        }
        
        replace div[0] {
            section {
                class: replaced-section;
            }
        }
    }
}
)";

    // 测试Origin嵌入
    std::string test2 = R"(
[Origin] @Html {
    <div class="raw-html">
        <p>This is raw HTML content</p>
        <script>console.log("Hello");</script>
    </div>
}

div {
    [Origin] @Style {
        .special-class {
            background: linear-gradient(to right, #ff0000, #00ff00);
            transform: rotate(45deg);
        }
    }
    
    [Origin] @JavaScript {
        function handleClick(event) {
            console.log('Button clicked!', event);
            alert('Hello from CHTL!');
        }
    }
}
)";

    // 测试内联Origin
    std::string test3 = R"(
head {
    [Origin] @Style myStyles {
        /* Custom CSS that CHTL shouldn't process */
        @media (max-width: 768px) {
            .container { width: 100%; }
        }
    }
}

div {
    text { "Some content" }
    
    [Origin] @JavaScript inline console.log("Inline JS");
}
)";

    std::vector<std::pair<std::string, std::string>> tests = {
        {"Operate Test", test1},
        {"Origin Block Test", test2},
        {"Origin Inline Test", test3}
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