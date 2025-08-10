#include <iostream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Generator/HtmlGenerator.h"

using namespace chtl;

int main() {
    // 把之前的Import后面的内容单独拿出来
    std::string code = "div { h1 { \"Hello\" } }";  // 注意前面有空格
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test");
    
    auto ast = parser.parse();
    
    std::cout << "Parse result:\n";
    std::cout << "- Children: " << ast->getChildren().size() << "\n";
    std::cout << "- Errors: " << context->getErrors().size() << "\n";
    
    if (ast->getChildren().size() > 0) {
        HtmlGenerator generator;
        std::ostringstream output;
        generator.generateToStream(ast, output);
        std::cout << "\nGenerated HTML:\n" << output.str() << "\n";
    }
    
    return 0;
}
