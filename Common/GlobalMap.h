#ifndef CHTL_COMMON_GLOBALMAP_H
#define CHTL_COMMON_GLOBALMAP_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Types.h"

namespace CHTL {

/**
 * 全局静态表 - 管理关键字、内置函数、HTML标签等静态信息
 */
class GlobalMap {
public:
    // 获取单例实例
    static GlobalMap& getInstance();
    
    // 初始化所有映射表
    void initialize();
    
    // Token类型映射
    TokenType getTokenType(const std::string& keyword) const;
    std::string getTokenName(TokenType type) const;
    
    // 检查是否是关键字
    bool isKeyword(const std::string& word) const;
    
    // 检查是否是HTML标签
    bool isHTMLTag(const std::string& tag) const;
    
    // 检查是否是CSS属性
    bool isCSSProperty(const std::string& property) const;
    
    // 检查是否是void元素（自闭合标签）
    bool isVoidElement(const std::string& tag) const;
    
    // 获取CHTL配置的默认值
    std::string getDefaultConfig(const std::string& key) const;
    
    // 注册自定义关键字（用于配置组的Name块）
    void registerCustomKeyword(const std::string& name, const std::vector<std::string>& values);
    
    // 获取自定义关键字
    std::vector<std::string> getCustomKeyword(const std::string& name) const;
    
private:
    GlobalMap() = default;
    ~GlobalMap() = default;
    GlobalMap(const GlobalMap&) = delete;
    GlobalMap& operator=(const GlobalMap&) = delete;
    
    // 初始化各个映射表
    void initializeKeywords();
    void initializeHTMLTags();
    void initializeCSSProperties();
    void initializeVoidElements();
    void initializeDefaultConfigs();
    
private:
    // 关键字到Token类型的映射
    std::unordered_map<std::string, TokenType> keywordMap_;
    
    // Token类型到名称的映射
    std::unordered_map<TokenType, std::string> tokenNameMap_;
    
    // HTML标签集合
    std::unordered_map<std::string, bool> htmlTags_;
    
    // CSS属性集合
    std::unordered_map<std::string, bool> cssProperties_;
    
    // void元素集合
    std::unordered_map<std::string, bool> voidElements_;
    
    // 默认配置
    std::unordered_map<std::string, std::string> defaultConfigs_;
    
    // 自定义关键字映射
    std::unordered_map<std::string, std::vector<std::string>> customKeywords_;
    
    // 是否已初始化
    bool initialized_ = false;
};

} // namespace CHTL

#endif // CHTL_COMMON_GLOBALMAP_H