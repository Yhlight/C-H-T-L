#include <iostream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Generator/HtmlGenerator.h"
#include "Node/Import.h"

using namespace chtl;

int main() {
    std::string code = R"(
[Import] @Style from "test.css" as myStyles;

div {
    class: "container";
    h1 { "Hello World" }
}
)";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test.chtl");
    
    auto ast = parser.parse();
    
    if (!ast) {
        std::cout << "Parse failed\n";
        for (const auto& err : context->getErrors()) {
            std::cout << "Error: " << err << "\n";
        }
        return 1;
    }
    
    std::cout << "Parse successful!\n";
    std::cout << "AST has " << ast->getChildren().size() << " children:\n";
    
    for (size_t i = 0; i < ast->getChildren().size(); ++i) {
        auto child = ast->getChildren()[i];
        std::cout << "  [" << i << "] " << child->getTagName();
        if (std::dynamic_pointer_cast<Import>(child)) {
            std::cout << " (Import)";
        }
        std::cout << "\n";
    }
    
    // 生成HTML
    HtmlGenerator generator;
    std::ostringstream output;
    generator.generateToStream(ast, output);
    
    std::cout << "\nGenerated HTML:\n";
    std::cout << output.str() << "\n";
    
    return 0;
}