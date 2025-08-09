#ifndef CHTL_GLOBAL_MAP_H
#define CHTL_GLOBAL_MAP_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <memory>
#include "Token.h"

namespace chtl {

// 全局静态映射表
class GlobalMap {
private:
    // 单例模式
    GlobalMap();
    static std::unique_ptr<GlobalMap> instance;
    
    // 关键字映射表
    std::unordered_map<std::string, TokenType> keywordMap;
    
    // 特殊标记映射表（如[Custom]）
    std::unordered_map<std::string, TokenType> specialMarkerMap;
    
    // AT前缀映射表（如@Style）
    std::unordered_map<std::string, TokenType> atPrefixMap;
    
    // HTML标签集合
    std::unordered_set<std::string> htmlTags;
    
    // HTML单标签集合
    std::unordered_set<std::string> htmlSingleTags;
    
    // CSS属性集合
    std::unordered_set<std::string> cssProperties;
    
    // JavaScript保留字集合
    std::unordered_set<std::string> jsReservedWords;
    
    // 配置组关键字映射（可动态修改）
    std::unordered_map<std::string, std::vector<std::string>> configKeywordAliases;
    
public:
    // 获取单例实例
    static GlobalMap& getInstance();
    
    // 删除拷贝构造和赋值操作符
    GlobalMap(const GlobalMap&) = delete;
    GlobalMap& operator=(const GlobalMap&) = delete;
    
    // 初始化方法
    void initialize();
    
    // 查询方法
    TokenType getKeywordType(const std::string& keyword) const;
    TokenType getSpecialMarkerType(const std::string& marker) const;
    TokenType getAtPrefixType(const std::string& prefix) const;
    
    bool isHtmlTag(const std::string& tag) const;
    bool isHtmlSingleTag(const std::string& tag) const;
    bool isCssProperty(const std::string& property) const;
    bool isJsReservedWord(const std::string& word) const;
    
    // 配置组支持
    void addKeywordAlias(const std::string& keyword, const std::string& alias);
    void setKeywordAliases(const std::string& keyword, const std::vector<std::string>& aliases);
    std::vector<std::string> getKeywordAliases(const std::string& keyword) const;
    
    // 用于调试
    void printKeywords() const;
    void printHtmlTags() const;
    
private:
    void initializeKeywords();
    void initializeSpecialMarkers();
    void initializeAtPrefixes();
    void initializeHtmlTags();
    void initializeCssProperties();
    void initializeJsReservedWords();
};

} // namespace chtl

#endif // CHTL_GLOBAL_MAP_H