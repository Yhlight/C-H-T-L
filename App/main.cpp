#include <iostream>
#include <string>
#include "Common/GlobalMap.h"
#include "Common/Token.h"

using namespace chtl;

int main(int argc, char* argv[]) {
    std::cout << "CHTL Compiler v1.0.0" << std::endl;
    std::cout << "=====================" << std::endl;
    
    // 测试Token和GlobalMap
    std::cout << "\n测试Token和GlobalMap功能：" << std::endl;
    
    // 测试关键字识别
    std::string testKeyword = "style";
    TokenType type = GlobalMap::getKeywordType(testKeyword);
    if (type != TokenType::UNKNOWN) {
        Token token(type, testKeyword, 1, 1);
        std::cout << "识别到关键字: ";
        token.print();
    }
    
    // 测试HTML标签识别
    std::string testTag = "div";
    if (GlobalMap::isHtmlTag(testTag)) {
        std::cout << "'" << testTag << "' 是有效的HTML标签" << std::endl;
        if (GlobalMap::isHtmlSingleTag(testTag)) {
            std::cout << "  (自闭合标签)" << std::endl;
        }
    }
    
    // 测试特殊标记
    std::string testMarker = "[Template]";
    TokenType markerType = GlobalMap::getSpecialMarkerType(testMarker);
    if (markerType != TokenType::UNKNOWN) {
        Token markerToken(markerType, testMarker, 1, 1);
        std::cout << "识别到特殊标记: ";
        markerToken.print();
    }
    
    // 测试AT前缀
    std::string testPrefix = "@Style";
    TokenType prefixType = GlobalMap::getAtPrefixType(testPrefix);
    if (prefixType != TokenType::UNKNOWN) {
        Token prefixToken(prefixType, testPrefix, 1, 1);
        std::cout << "识别到AT前缀: ";
        prefixToken.print();
    }
    
    // 测试Token类的方法
    std::cout << "\n测试Token类方法：" << std::endl;
    Token keywordToken(TokenType::STYLE, "style", 2, 5);
    std::cout << "Token是否为关键字: " << (keywordToken.isKeyword() ? "是" : "否") << std::endl;
    std::cout << "Token是否为特殊标记: " << (keywordToken.isSpecialMarker() ? "是" : "否") << std::endl;
    
    if (argc > 1) {
        std::cout << "\n输入文件: " << argv[1] << std::endl;
        // TODO: 实现文件编译流程
    } else {
        std::cout << "\n用法: chtl <input.chtl> [options]" << std::endl;
    }
    
    return 0;
}