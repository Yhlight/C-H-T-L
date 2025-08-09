#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../Common/Types.h"
#include "../Lexer/StandardLexer.h"
#include "../Parser/StandardParser.h"
#include "../Generator/StandardGenerator.h"

using namespace CHTL;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: chtlc <input-file>\n";
        return 1;
    }

    const std::string inputPath = argv[1];
    std::ifstream in(inputPath);
    if (!in)
    {
        std::cerr << "Failed to open: " << inputPath << "\n";
        return 1;
    }

    std::ostringstream ss;
    ss << in.rdbuf();
    const std::string source = ss.str();

    // 词法
    StandardLexer lexer(LanguageMode::Chtl);
    auto tokens = lexer.tokenize(source);

    // 解析
    StandardParser parser;
    auto root = parser.parse(tokens);

    // 生成
    StandardGenerator generator;
    std::cout << generator.generate(*root);

    return 0;
}