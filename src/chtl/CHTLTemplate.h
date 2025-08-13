#ifndef CHTL_TEMPLATE_H
#define CHTL_TEMPLATE_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include "CHTLContext.h"

namespace chtl {

// 模板类型
enum class TemplateType {
    STYLE,      // @Style
    ELEMENT,    // @Element
    VAR         // @Var
};

// 模板使用状态
enum class TemplateState {
    DEFINITION,  // 定义状态
    USE         // 使用状态
};

// 全缀名类型
enum class QualifiedNameType {
    SIMPLE,     // 简单名称: Box
    PARTIAL,    // 部分限定: @Element Box
    FULL        // 完全限定: [Template] @Element Box
};

// 全缀名解析器
class QualifiedNameResolver {
private:
    std::string prefix;      // [Template] 或 [Custom]
    std::string type;        // @Style, @Element, @Var
    std::string name;        // 模板名
    QualifiedNameType nameType;
    
public:
    QualifiedNameResolver() : nameType(QualifiedNameType::SIMPLE) {}
    
    // 解析全缀名
    bool parse(const std::string& fullName);
    
    // 获取解析结果
    const std::string& getPrefix() const { return prefix; }
    const std::string& getType() const { return type; }
    const std::string& getName() const { return name; }
    QualifiedNameType getNameType() const { return nameType; }
    
    // 构建全缀名
    std::string buildFullName() const;
    std::string buildPartialName() const;
    
    // 匹配检查
    bool matches(const std::string& otherName) const;
    bool matchesType(TemplateType templateType) const;
};

// 样式组模板
class StyleTemplate : public TemplateDefinition {
private:
    std::vector<std::pair<std::string, std::string>> styles;
    std::vector<std::string> inheritedTemplates;
    bool hasExplicitInherit;
    
public:
    StyleTemplate(const std::string& name) 
        : TemplateDefinition(name, "@Style"), hasExplicitInherit(false) {}
    
    // 添加样式属性
    void addStyle(const std::string& property, const std::string& value);
    
    // 继承
    void inheritFrom(const std::string& templateName, bool isExplicit = false);
    
    // 获取所有样式（包括继承的）
    std::vector<std::pair<std::string, std::string>> getAllStyles(
        const std::unordered_map<std::string, std::shared_ptr<StyleTemplate>>& templateMap) const;
    
    // 应用到元素
    void applyToElement(class CHTLGenerator& generator) const;
    
    // 检查是否有循环继承
    bool hasCircularInheritance(const std::string& checkName,
        const std::unordered_map<std::string, std::shared_ptr<StyleTemplate>>& templateMap) const;
};

// 元素模板
class ElementTemplate : public TemplateDefinition {
private:
    struct ElementNode {
        std::string name;
        std::unordered_map<std::string, std::string> attributes;
        std::vector<std::shared_ptr<ElementNode>> children;
        std::string textContent;
        std::shared_ptr<StyleTemplate> inlineStyles;
        bool hasStyleBlock;
    };
    
    std::vector<std::shared_ptr<ElementNode>> elements;
    std::vector<std::string> inheritedTemplates;
    
public:
    ElementTemplate(const std::string& name) 
        : TemplateDefinition(name, "@Element") {}
    
    // 添加元素
    void addElement(std::shared_ptr<ElementNode> element);
    
    // 继承
    void inheritFrom(const std::string& templateName);
    
    // 展开模板
    void expand(class CHTLGenerator& generator) const;
    
    // 获取所有元素（包括继承的）
    std::vector<std::shared_ptr<ElementNode>> getAllElements(
        const std::unordered_map<std::string, std::shared_ptr<ElementTemplate>>& templateMap) const;
};

// 变量组模板
class VarTemplate : public TemplateDefinition {
private:
    std::unordered_map<std::string, std::string> variables;
    std::vector<std::string> inheritedTemplates;
    
public:
    VarTemplate(const std::string& name) 
        : TemplateDefinition(name, "@Var") {}
    
    // 添加变量
    void addVariable(const std::string& varName, const std::string& value);
    
    // 继承
    void inheritFrom(const std::string& templateName);
    
    // 获取变量值
    std::optional<std::string> getVariable(const std::string& varName) const;
    
    // 获取所有变量（包括继承的）
    std::unordered_map<std::string, std::string> getAllVariables(
        const std::unordered_map<std::string, std::shared_ptr<VarTemplate>>& templateMap) const;
    
    // 变量替换
    std::string replaceVariables(const std::string& text) const;
};

// 模板管理器
class TemplateManager {
private:
    // 模板存储
    std::unordered_map<std::string, std::shared_ptr<StyleTemplate>> styleTemplates;
    std::unordered_map<std::string, std::shared_ptr<ElementTemplate>> elementTemplates;
    std::unordered_map<std::string, std::shared_ptr<VarTemplate>> varTemplates;
    
    // 当前状态
    TemplateState currentState;
    
    // 全缀名映射（支持多种访问方式）
    std::unordered_map<std::string, std::string> nameAliases;
    
    // 上下文引用
    std::shared_ptr<CHTLContext> context;
    
public:
    TemplateManager(std::shared_ptr<CHTLContext> ctx) 
        : context(ctx), currentState(TemplateState::USE) {}
    
    // 状态管理
    void setTemplateState(TemplateState state) { currentState = state; }
    TemplateState getTemplateState() const { return currentState; }
    
    // 注册模板
    bool registerStyleTemplate(const std::string& name, std::shared_ptr<StyleTemplate> tmpl);
    bool registerElementTemplate(const std::string& name, std::shared_ptr<ElementTemplate> tmpl);
    bool registerVarTemplate(const std::string& name, std::shared_ptr<VarTemplate> tmpl);
    
    // 查找模板（支持全缀名）
    std::shared_ptr<StyleTemplate> findStyleTemplate(const std::string& name) const;
    std::shared_ptr<ElementTemplate> findElementTemplate(const std::string& name) const;
    std::shared_ptr<VarTemplate> findVarTemplate(const std::string& name) const;
    
    // 通用查找（根据类型）
    std::shared_ptr<TemplateDefinition> findTemplate(const std::string& name, TemplateType type) const;
    
    // 使用模板
    bool useStyleTemplate(const std::string& name, class CHTLGenerator& generator);
    bool useElementTemplate(const std::string& name, class CHTLGenerator& generator);
    std::string useVarTemplate(const std::string& templateName, const std::string& varName);
    
    // 继承处理
    void processInheritance();
    
    // 全缀名支持
    void registerAlias(const std::string& alias, const std::string& fullName);
    std::string resolveAlias(const std::string& name) const;
    
    // 验证
    bool validateTemplate(const std::string& name, TemplateType type) const;
    bool checkCircularInheritance() const;
};

// 模板使用处理器
class TemplateUseProcessor {
private:
    TemplateManager& manager;
    CHTLGenerator& generator;
    
public:
    TemplateUseProcessor(TemplateManager& mgr, CHTLGenerator& gen) 
        : manager(mgr), generator(gen) {}
    
    // 处理模板使用语句
    bool processTemplateUse(const std::string& statement);
    
    // 处理变量引用
    std::string processVariableReference(const std::string& reference);
    
    // 解析使用语句
    struct UseStatement {
        std::string prefix;      // [Template] 或空
        std::string type;        // @Style, @Element, @Var
        std::string name;        // 模板名
        std::string varName;     // 变量名（仅用于变量组）
        bool hasPrefix;
    };
    
    UseStatement parseUseStatement(const std::string& statement);
};

// 模板继承处理器
class TemplateInheritanceProcessor {
private:
    // 检查循环继承
    template<typename T>
    bool checkCircularInheritance(
        const std::string& name,
        const std::unordered_map<std::string, std::shared_ptr<T>>& templates,
        std::unordered_set<std::string>& visited) const;
    
    // 解析继承链
    template<typename T>
    std::vector<std::string> resolveInheritanceChain(
        const std::string& name,
        const std::unordered_map<std::string, std::shared_ptr<T>>& templates) const;
    
public:
    // 处理样式组继承
    void processStyleInheritance(
        std::unordered_map<std::string, std::shared_ptr<StyleTemplate>>& templates);
    
    // 处理元素模板继承
    void processElementInheritance(
        std::unordered_map<std::string, std::shared_ptr<ElementTemplate>>& templates);
    
    // 处理变量组继承
    void processVarInheritance(
        std::unordered_map<std::string, std::shared_ptr<VarTemplate>>& templates);
    
    // 合并属性（后面的覆盖前面的）
    std::vector<std::pair<std::string, std::string>> mergeProperties(
        const std::vector<std::vector<std::pair<std::string, std::string>>>& propertyLists);
};

// 辅助函数
namespace TemplateHelper {
    // 解析模板类型
    TemplateType parseTemplateType(const std::string& typeStr);
    std::string templateTypeToString(TemplateType type);
    
    // 验证模板名称
    bool isValidTemplateName(const std::string& name);
    
    // 解析变量引用：TemplateName(varName)
    struct VarReference {
        std::string templateName;
        std::string varName;
        bool isValid;
    };
    VarReference parseVarReference(const std::string& reference);
}

} // namespace chtl

#endif // CHTL_TEMPLATE_H