#include <iostream>
#include <memory>
#include <sstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Custom.h"
#include "Node/Template.h"

using namespace chtl;

int main() {
    std::string code = R"([Custom] @Element Card {
    div.card {
        padding: 16px;
        border: 1px solid #ddd;
    }
}

[Template] @Element Modal(title, content) {
    div.modal {
        h2 { {{title}} }
        p { {{content}} }
    }
})";
    
    // First, let's see what tokens the lexer produces
    std::cout << "=== LEXER OUTPUT ===" << std::endl;
    auto lexer = std::make_shared<StandardLexer>();
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test.chtl");
    
    Token token;
    int tokenCount = 0;
    while ((token = lexer->getNextToken()).type != TokenType::EOF_TOKEN) {
        std::cout << tokenCount++ << ": " << static_cast<int>(token.type) << " '" << token.value << "'" << std::endl;
    }
    
    std::cout << "\n=== PARSER OUTPUT ===" << std::endl;
    
    // Now parse
    auto lexer2 = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer2, context);
    
    auto input2 = std::make_unique<std::istringstream>(code);
    lexer2->initialize(std::move(input2), "test.chtl");
    
    try {
        auto ast = parser.parse();
        
        if (context->hasErrors()) {
            std::cout << "Parse errors:" << std::endl;
            for (const auto& error : context->getErrors()) {
                std::cout << "  " << error << std::endl;
            }
        } else {
            std::cout << "Parse successful!" << std::endl;
            if (ast) {
                std::cout << "Root has " << ast->getChildren().size() << " children" << std::endl;
                for (const auto& child : ast->getChildren()) {
                    if (auto custom = std::dynamic_pointer_cast<Custom>(child)) {
                        std::cout << "- Custom: " << custom->getCustomName() << std::endl;
                    } else if (auto tmpl = std::dynamic_pointer_cast<Template>(child)) {
                        std::cout << "- Template: " << tmpl->getTemplateName() << std::endl;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}