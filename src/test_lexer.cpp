#include <iostream>
#include <iomanip>
#include <sstream>
#include "Lexer/BasicLexer.h"
#include "Common/GlobalMap.h"

using namespace chtl;

void printToken(const Token& token) {
    std::cout << std::left 
              << std::setw(25) << token.getTypeString() 
              << std::setw(20) << ("\"" + token.getValue() + "\"")
              << " [" << token.getLine() << ":" << token.getColumn() << "]" 
              << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "CHTL Lexer Test" << std::endl;
    std::cout << "===============" << std::endl;
    
    // 创建词法分析器
    BasicLexer lexer;
    
    // 使用文件或测试字符串
    std::string filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "examples/test.chtl";
    }
    
    std::cout << "\n分析文件: " << filename << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    // 初始化词法分析器
    if (!lexer.initialize(filename)) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        
        // 使用测试字符串
        std::cout << "\n使用测试字符串进行分析..." << std::endl;
        std::string testCode = R"(
[Template] @Style MyStyle
{
    color: red;
    font-size: 16px;
}

div
{
    class: my-class;
    id: myId;
    
    style
    {
        width: 100px;
        height: 200px;
    }
    
    text
    {
        "Hello CHTL!"
    }
}
)";
        
        auto stream = std::make_unique<std::istringstream>(testCode);
        if (!lexer.initialize(std::move(stream), "<test>")) {
            std::cerr << "初始化失败" << std::endl;
            return 1;
        }
    }
    
    // 输出表头
    std::cout << std::left 
              << std::setw(25) << "Token Type" 
              << std::setw(20) << "Value" 
              << "Position" 
              << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    // 获取并打印所有Token
    Token token;
    int tokenCount = 0;
    
    do {
        token = lexer.getNextToken();
        if (token.getType() != TokenType::EOF_TOKEN) {
            printToken(token);
            tokenCount++;
        }
    } while (token.getType() != TokenType::EOF_TOKEN);
    
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "总共识别到 " << tokenCount << " 个Token" << std::endl;
    
    // 检查错误
    if (lexer.hasError()) {
        std::cout << "\n错误: " << lexer.getLastError() << std::endl;
    }
    
    // 打印上下文信息
    auto context = lexer.getChtlContext();
    if (context) {
        std::cout << "\n上下文信息:" << std::endl;
        if (context->hasErrors()) {
            std::cout << "错误数量: " << context->getErrors().size() << std::endl;
            for (const auto& error : context->getErrors()) {
                std::cout << "  - " << error << std::endl;
            }
        }
        if (context->hasWarnings()) {
            std::cout << "警告数量: " << context->getWarnings().size() << std::endl;
            for (const auto& warning : context->getWarnings()) {
                std::cout << "  - " << warning << std::endl;
            }
        }
    }
    
    return 0;
}