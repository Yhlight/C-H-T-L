#include <iostream>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Generator/HtmlGenerator.h"

using namespace chtl;

int main() {
    // 注意：没有开头的换行符
    std::string code = "div {\n    class: \"container\";\n    h1 { \"Hello World\" }\n}";
    
    auto lexer = std::make_shared<StandardLexer>();
    auto context = std::make_shared<StandardContext>();
    StandardParser parser(lexer, context);
    
    auto input = std::make_unique<std::istringstream>(code);
    lexer->initialize(std::move(input), "test");
    
    auto ast = parser.parse();
    
    std::cout << "Parse result:\n";
    std::cout << "- Root tag: " << ast->getTagName() << "\n";
    std::cout << "- Children: " << ast->getChildren().size() << "\n";
    
    // 生成HTML
    HtmlGenerator generator;
    std::ostringstream output;
    generator.generateToStream(ast, output);
    
    std::cout << "\nGenerated HTML:\n";
    std::cout << output.str() << "\n";
    
    return 0;
}
