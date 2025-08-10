#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Context/StandardContext.h"
#include "Node/Custom.h"
#include "Node/Template.h"

using namespace chtl;

int main() {
    // Create a test file
    std::string filename = "test_components.chtl";
    std::ofstream file(filename);
    file << "[Custom] @Element Card {\n"
         << "    div.card {\n"
         << "        padding: 16px;\n"
         << "        border: 1px solid #ddd;\n"
         << "    }\n"
         << "}\n"
         << "\n"
         << "[Custom] @Style CardStyle {\n"
         << "    background: white;\n"
         << "    border-radius: 8px;\n"
         << "}\n"
         << "\n"
         << "[Template] @Element Modal(title, content) {\n"
         << "    div.modal {\n"
         << "        h2 { {{title}} }\n"
         << "        p { {{content}} }\n"
         << "    }\n"
         << "}";
    file.close();
    
    // Parse the file
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::ifstream>(filename);
    lexer->initialize(std::move(input), filename);
    
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
                        std::cout << "- Custom: " << custom->getCustomName() 
                                  << " Type: " << static_cast<int>(custom->getCustomType()) << std::endl;
                    } else if (auto tmpl = std::dynamic_pointer_cast<Template>(child)) {
                        std::cout << "- Template: " << tmpl->getTemplateName() << std::endl;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Clean up
    std::remove(filename.c_str());
    
    return 0;
}