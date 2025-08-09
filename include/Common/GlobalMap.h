#ifndef CHTL_GLOBAL_MAP_H
#define CHTL_GLOBAL_MAP_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include "TokenType.h"

namespace chtl {

// 全局静态映射表类
class GlobalMap {
private:
    // 私有构造函数，防止实例化
    GlobalMap() = delete;
    
public:
    // 关键字映射表
    static const std::unordered_map<std::string, TokenType> KEYWORD_MAP;
    
    // 特殊标记映射表（如[Custom]）
    static const std::unordered_map<std::string, TokenType> SPECIAL_MARKER_MAP;
    
    // AT前缀映射表（如@Style）
    static const std::unordered_map<std::string, TokenType> AT_PREFIX_MAP;
    
    // HTML标签集合
    static const std::unordered_set<std::string> HTML_TAGS;
    
    // HTML单标签集合
    static const std::unordered_set<std::string> HTML_SINGLE_TAGS;
    
    // CSS属性集合
    static const std::unordered_set<std::string> CSS_PROPERTIES;
    
    // JavaScript保留字集合
    static const std::unordered_set<std::string> JS_RESERVED_WORDS;
    
    // TokenType到字符串的映射
    static const std::unordered_map<TokenType, std::string> TOKEN_TYPE_STRINGS;
    
    // 查询方法
    static TokenType getKeywordType(const std::string& keyword);
    static TokenType getSpecialMarkerType(const std::string& marker);
    static TokenType getAtPrefixType(const std::string& prefix);
    
    static bool isHtmlTag(const std::string& tag);
    static bool isHtmlSingleTag(const std::string& tag);
    static bool isCssProperty(const std::string& property);
    static bool isJsReservedWord(const std::string& word);
    
    // Token类型转字符串
    static std::string tokenTypeToString(TokenType type);
    
    // 用于调试
    static void printKeywords();
    static void printHtmlTags();
    static void printTokenTypes();
};

} // namespace chtl

#endif // CHTL_GLOBAL_MAP_H