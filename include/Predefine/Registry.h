#ifndef CHTL_PREDEFINE_REGISTRY_H
#define CHTL_PREDEFINE_REGISTRY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace chtl {

// 预定义注册表 - 管理所有预定义的元素、样式、变量等
class Registry {
public:
    // 单例模式
    static Registry& getInstance();
    
    // 预定义元素信息
    struct ElementInfo {
        std::string name;
        std::string category;  // form, media, semantic, structure
        std::vector<std::string> allowedAttributes;
        std::vector<std::string> requiredAttributes;
        bool selfClosing;
        bool deprecated;
        std::string description;
    };
    
    // 预定义样式信息
    struct StyleInfo {
        std::string name;
        std::string category;  // layout, typography, color, animation
        std::vector<std::string> properties;
        std::string description;
    };
    
    // 预定义变量信息
    struct VarInfo {
        std::string name;
        std::string type;      // color, size, spacing, breakpoint
        std::string defaultValue;
        std::string description;
    };
    
    // 预定义函数信息
    struct FunctionInfo {
        std::string name;
        std::vector<std::string> parameters;
        std::string returnType;
        std::string description;
    };
    
    // 注册方法
    void registerElement(const ElementInfo& info);
    void registerStyle(const StyleInfo& info);
    void registerVar(const VarInfo& info);
    void registerFunction(const FunctionInfo& info);
    
    // 批量注册
    void registerElements(const std::vector<ElementInfo>& elements);
    void registerStyles(const std::vector<StyleInfo>& styles);
    void registerVars(const std::vector<VarInfo>& vars);
    void registerFunctions(const std::vector<FunctionInfo>& functions);
    
    // 查询方法
    bool hasElement(const std::string& name) const;
    bool hasStyle(const std::string& name) const;
    bool hasVar(const std::string& name) const;
    bool hasFunction(const std::string& name) const;
    
    // 获取信息
    const ElementInfo* getElement(const std::string& name) const;
    const StyleInfo* getStyle(const std::string& name) const;
    const VarInfo* getVar(const std::string& name) const;
    const FunctionInfo* getFunction(const std::string& name) const;
    
    // 获取列表
    std::vector<std::string> getAllElements() const;
    std::vector<std::string> getElementsByCategory(const std::string& category) const;
    std::vector<std::string> getAllStyles() const;
    std::vector<std::string> getStylesByCategory(const std::string& category) const;
    std::vector<std::string> getAllVars() const;
    std::vector<std::string> getVarsByType(const std::string& type) const;
    std::vector<std::string> getAllFunctions() const;
    
    // 属性验证
    bool isValidAttribute(const std::string& element, const std::string& attribute) const;
    bool isRequiredAttribute(const std::string& element, const std::string& attribute) const;
    std::vector<std::string> getMissingRequiredAttributes(const std::string& element, 
                                                         const std::vector<std::string>& providedAttributes) const;
    
    // 清理
    void clear();
    void clearElements();
    void clearStyles();
    void clearVars();
    void clearFunctions();
    
    // 初始化默认值
    void initializeDefaults();
    
private:
    Registry();
    ~Registry() = default;
    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;
    
    // 存储
    std::unordered_map<std::string, ElementInfo> elements_;
    std::unordered_map<std::string, StyleInfo> styles_;
    std::unordered_map<std::string, VarInfo> vars_;
    std::unordered_map<std::string, FunctionInfo> functions_;
    
    // 分类索引
    std::unordered_map<std::string, std::unordered_set<std::string>> elementsByCategory_;
    std::unordered_map<std::string, std::unordered_set<std::string>> stylesByCategory_;
    std::unordered_map<std::string, std::unordered_set<std::string>> varsByType_;
};

} // namespace chtl

#endif // CHTL_PREDEFINE_REGISTRY_H