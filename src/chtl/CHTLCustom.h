#ifndef CHTL_CUSTOM_H
#define CHTL_CUSTOM_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include <variant>
#include "CHTLTemplate.h"

namespace chtl {

// 前向声明
class CHTLGenerator;

// 特例化操作类型
enum class SpecializationType {
    NONE,           // 无特例化
    DELETE,         // 删除操作
    INSERT,         // 插入操作
    REPLACE,        // 替换操作
    OVERRIDE        // 覆盖操作
};

// 插入位置
enum class InsertPosition {
    BEFORE,         // 在...之前
    AFTER,          // 在...之后
    REPLACE,        // 替换
    AT_TOP,         // 在顶部
    AT_BOTTOM       // 在底部
};

// 元素选择器
struct ElementSelector {
    std::string elementName;
    int index = -1;  // -1表示选择所有，>=0表示特定索引
    
    ElementSelector() = default;
    ElementSelector(const std::string& name, int idx = -1) 
        : elementName(name), index(idx) {}
    
    bool matches(const std::string& name, int currentIndex) const;
    std::string toString() const;
    static ElementSelector parse(const std::string& selector);
};

// 特例化操作
struct SpecializationOperation {
    SpecializationType type;
    std::vector<std::string> targets;  // 要操作的目标（属性名、元素选择器等）
    std::variant<std::monostate, InsertPosition, std::string> data;  // 额外数据
};

// 自定义样式组
class CustomStyleGroup : public StyleTemplate {
private:
    // 无值属性列表
    std::vector<std::string> valueRequiredProperties;
    
    // 特例化操作
    std::vector<SpecializationOperation> specializations;
    
    // 是否允许无值属性
    bool allowsValuelessProperties;
    
public:
    CustomStyleGroup(const std::string& name) 
        : StyleTemplate(name), allowsValuelessProperties(true) {}
    
    // 添加无值属性
    void addValuelessProperty(const std::string& property);
    
    // 检查属性是否需要值
    bool requiresValue(const std::string& property) const;
    
    // 添加特例化操作
    void addDeleteOperation(const std::vector<std::string>& properties);
    void addDeleteInheritance(const std::string& inheritedName);
    
    // 应用特例化
    void applySpecialization(const SpecializationOperation& op);
    
    // 获取有效属性（考虑删除操作）
    std::vector<std::pair<std::string, std::string>> getEffectiveStyles(
        const std::unordered_map<std::string, std::shared_ptr<StyleTemplate>>& templateMap,
        const std::unordered_map<std::string, std::string>& providedValues = {}) const;
};

// 自定义元素
class CustomElement : public ElementTemplate {
public:
    // 元素特例化数据
    struct ElementSpecialization {
        ElementSelector selector;
        std::shared_ptr<StyleTemplate> additionalStyles;
        std::unordered_map<std::string, std::string> additionalAttributes;
        std::string additionalContent;
    };
    
    // 插入操作数据
    struct InsertOperation {
        InsertPosition position;
        ElementSelector targetSelector;
        std::vector<std::shared_ptr<ElementNode>> elementsToInsert;
    };
    
    // 删除操作数据
    struct DeleteOperation {
        std::vector<ElementSelector> selectors;
        bool isInheritanceDeletion = false;
        std::string inheritanceTarget;
    };
    
private:
    std::vector<ElementSpecialization> specializations;
    std::vector<InsertOperation> insertOperations;
    std::vector<DeleteOperation> deleteOperations;
    
public:
    CustomElement(const std::string& name) : ElementTemplate(name) {}
    
    // 特例化操作
    void addElementSpecialization(const ElementSpecialization& spec);
    void addInsertOperation(const InsertOperation& op);
    void addDeleteOperation(const DeleteOperation& op);
    
    // 索引访问支持
    std::shared_ptr<ElementNode> getElementByIndex(const std::string& elementName, int index) const;
    std::vector<std::shared_ptr<ElementNode>> getElementsBySelector(const ElementSelector& selector) const;
    
    // 展开时应用特例化
    void expandWithSpecialization(CHTLGenerator& generator,
        const std::vector<SpecializationOperation>& userSpecializations = {}) const;
    
    // 应用插入操作
    std::vector<std::shared_ptr<ElementNode>> applyInsertions(
        const std::vector<std::shared_ptr<ElementNode>>& originalElements) const;
    
    // 应用删除操作
    std::vector<std::shared_ptr<ElementNode>> applyDeletions(
        const std::vector<std::shared_ptr<ElementNode>>& originalElements) const;
};

// 自定义变量组
class CustomVarGroup : public VarTemplate {
private:
    // 允许运行时覆盖的变量
    std::unordered_set<std::string> overridableVariables;
    
    // 特例化值
    std::unordered_map<std::string, std::string> specializationValues;
    
public:
    CustomVarGroup(const std::string& name) : VarTemplate(name) {}
    
    // 标记变量为可覆盖
    void markAsOverridable(const std::string& varName);
    
    // 检查变量是否可覆盖
    bool isOverridable(const std::string& varName) const;
    
    // 应用特例化值
    void applySpecializationValue(const std::string& varName, const std::string& value);
    
    // 获取变量值（考虑特例化）
    std::string getVariableWithSpecialization(const std::string& varName,
        const std::optional<std::string>& runtimeValue = std::nullopt) const;
};

// 自定义管理器
class CustomManager {
private:
    // 存储
    std::unordered_map<std::string, std::shared_ptr<CustomStyleGroup>> customStyles;
    std::unordered_map<std::string, std::shared_ptr<CustomElement>> customElements;
    std::unordered_map<std::string, std::shared_ptr<CustomVarGroup>> customVars;
    
    // 模板管理器引用（用于模板和自定义的相互继承）
    std::shared_ptr<TemplateManager> templateManager;
    
    // 上下文
    std::shared_ptr<CHTLContext> context;
    
public:
    CustomManager(std::shared_ptr<CHTLContext> ctx, std::shared_ptr<TemplateManager> tmplMgr)
        : context(ctx), templateManager(tmplMgr) {}
    
    // 注册自定义
    bool registerCustomStyle(const std::string& name, std::shared_ptr<CustomStyleGroup> custom);
    bool registerCustomElement(const std::string& name, std::shared_ptr<CustomElement> custom);
    bool registerCustomVar(const std::string& name, std::shared_ptr<CustomVarGroup> custom);
    
    // 查找自定义（支持全缀名）
    std::shared_ptr<CustomStyleGroup> findCustomStyle(const std::string& name) const;
    std::shared_ptr<CustomElement> findCustomElement(const std::string& name) const;
    std::shared_ptr<CustomVarGroup> findCustomVar(const std::string& name) const;
    
    // 使用自定义
    bool useCustomStyle(const std::string& name, CHTLGenerator& generator,
        const std::unordered_map<std::string, std::string>& providedValues = {});
    bool useCustomElement(const std::string& name, CHTLGenerator& generator,
        const std::vector<SpecializationOperation>& specializations = {});
    std::string useCustomVar(const std::string& templateName, const std::string& varName,
        const std::optional<std::string>& runtimeValue = std::nullopt);
};

// 特例化处理器
class SpecializationProcessor {
public:
    // 解析特例化语句
    struct SpecializationStatement {
        std::string targetType;     // @Style, @Element, @Var
        std::string targetName;     // 目标名称
        SpecializationType operation;
        std::vector<std::string> operands;
        std::unordered_map<std::string, std::string> values;
    };
    
    // 解析删除语句
    static SpecializationOperation parseDeleteStatement(const std::string& statement);
    
    // 解析插入语句
    static InsertOperation parseInsertStatement(const std::string& statement);
    
    // 解析变量特例化
    static std::pair<std::string, std::string> parseVariableSpecialization(const std::string& expr);
    
    // 解析元素选择器
    static ElementSelector parseElementSelector(const std::string& selector);
    
    // 验证特例化操作
    static bool validateSpecialization(const SpecializationStatement& spec);
};

// 自定义和模板的互操作性
class CustomTemplateInterop {
private:
    CustomManager& customManager;
    TemplateManager& templateManager;
    
public:
    CustomTemplateInterop(CustomManager& cm, TemplateManager& tm)
        : customManager(cm), templateManager(tm) {}
    
    // 从模板创建自定义
    std::shared_ptr<CustomStyleGroup> createCustomFromTemplate(
        const std::string& customName, const std::string& templateName);
    
    // 从自定义创建模板
    std::shared_ptr<StyleTemplate> createTemplateFromCustom(
        const std::string& templateName, const std::string& customName);
    
    // 处理相互继承
    bool processInterInheritance(const std::string& sourceName, const std::string& targetName);
    
    // 类型兼容性检查
    bool areTypesCompatible(const std::string& source, const std::string& target) const;
};

// 辅助函数
namespace CustomHelper {
    // 解析索引表达式，如 "div[1]" -> ("div", 1)
    std::pair<std::string, int> parseIndexedSelector(const std::string& selector);
    
    // 验证插入位置
    bool isValidInsertPosition(InsertPosition pos, const ElementSelector& target);
    
    // 合并特例化操作
    std::vector<SpecializationOperation> mergeSpecializations(
        const std::vector<SpecializationOperation>& base,
        const std::vector<SpecializationOperation>& overrides);
    
    // 应用删除过滤器
    template<typename T>
    std::vector<T> applyDeletionFilter(const std::vector<T>& items,
        const std::vector<std::string>& deletions);
}

} // namespace chtl

#endif // CHTL_CUSTOM_H