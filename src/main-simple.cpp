#include <iostream>
#include <fstream>
#include <memory>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Generator/WebGenerator.h"
#include "Context/ChtlContext.h"

using namespace chtl;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.chtl> [output.html]" << std::endl;
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = (argc >= 3) ? argv[2] : "output.html";
    
    try {
        // 读取输入文件
        std::ifstream file(inputFile);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << inputFile << std::endl;
            return 1;
        }
        
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();
        
        // 创建词法分析器
        auto lexer = std::make_shared<StandardLexer>(content);
        
        // 创建上下文
        auto context = std::make_shared<ChtlContext>();
        
        // 创建解析器
        StandardParser parser(lexer, context);
        
        // 解析
        auto ast = parser.parse();
        if (!ast) {
            std::cerr << "Error: Failed to parse " << inputFile << std::endl;
            return 1;
        }
        
        // 生成代码
        WebGenerator generator;
        generator.setContext(context);
        auto result = generator.generate(ast);
        
        if (!result.success) {
            std::cerr << "Error: Failed to generate code" << std::endl;
            for (const auto& error : result.errors) {
                std::cerr << "  " << error << std::endl;
            }
            return 1;
        }
        
        // 写入输出文件
        std::ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            std::cerr << "Error: Cannot create output file " << outputFile << std::endl;
            return 1;
        }
        
        outFile << result.html;
        outFile.close();
        
        std::cout << "Successfully compiled " << inputFile << " to " << outputFile << std::endl;
        
        // 显示警告（如果有）
        if (!result.warnings.empty()) {
            std::cout << "Warnings:" << std::endl;
            for (const auto& warning : result.warnings) {
                std::cout << "  " << warning << std::endl;
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}