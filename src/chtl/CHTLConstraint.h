#ifndef CHTL_CONSTRAINT_H
#define CHTL_CONSTRAINT_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "CHTLContext.h"

namespace chtl {

// 前向声明
class CHTLGenerator;
class NamespaceManager;

// 约束类型
enum class ConstraintType {
    PRECISE,    // 精确约束（具体元素或对象）
    TYPE,       // 类型约束（@Html, [Custom], [Template]等）
    GLOBAL      // 全局约束（命名空间级别）
};

// 约束目标类型
enum class ConstraintTargetType {
    HTML_ELEMENT,       // HTML元素（如span, div）
    HTML_ALL,          // 所有HTML元素（@Html）
    CUSTOM_ELEMENT,    // 自定义元素
    CUSTOM_STYLE,      // 自定义样式组
    CUSTOM_VAR,        // 自定义变量组
    CUSTOM_ALL,        // 所有自定义（[Custom]）
    TEMPLATE_ELEMENT,  // 模板元素
    TEMPLATE_STYLE,    // 模板样式组
    TEMPLATE_VAR,      // 模板变量组
    TEMPLATE_ALL       // 所有模板（[Template]）
};

// 约束目标
struct ConstraintTarget {
    ConstraintTargetType type;
    std::string name;           // 具体名称（对于精确约束）
    std::string qualifier;      // 限定符（[Custom] 或 [Template]）
    std::string fullName;       // 完整名称（包含限定符）
    
    // 构造函数
    ConstraintTarget(ConstraintTargetType t = ConstraintTargetType::HTML_ELEMENT,
                    const std::string& n = "",
                    const std::string& q = "")
        : type(t), name(n), qualifier(q) {
        updateFullName();
    }
    
    void updateFullName();
    bool matches(const ConstraintTarget& other) const;
};

// 约束规则
class ConstraintRule {
private:
    ConstraintType type;
    std::vector<ConstraintTarget> targets;
    std::string scope;          // 应用范围（元素名或命名空间路径）
    bool isGlobal;             // 是否是全局约束
    
    // 源信息
    std::string sourceFile;
    int lineNumber;
    
public:
    ConstraintRule(ConstraintType t, const std::string& s = "", bool global = false)
        : type(t), scope(s), isGlobal(global), lineNumber(0) {}
    
    // 添加约束目标
    void addTarget(const ConstraintTarget& target);
    
    // 检查是否违反约束
    bool isViolated(const ConstraintTarget& target) const;
    bool isViolated(const std::string& elementOrType) const;
    
    // 获取器
    ConstraintType getType() const { return type; }
    const std::vector<ConstraintTarget>& getTargets() const { return targets; }
    const std::string& getScope() const { return scope; }
    bool isGlobalConstraint() const { return isGlobal; }
    
    // 源信息
    void setSourceInfo(const std::string& file, int line) {
        sourceFile = file;
        lineNumber = line;
    }
    
    // 生成违反信息
    std::string getViolationMessage(const ConstraintTarget& target) const;
};

// 约束管理器
class ConstraintManager {
private:
    // 元素级约束（元素路径 -> 约束规则）
    std::unordered_map<std::string, std::vector<std::shared_ptr<ConstraintRule>>> elementConstraints;
    
    // 命名空间级约束（命名空间路径 -> 约束规则）
    std::unordered_map<std::string, std::vector<std::shared_ptr<ConstraintRule>>> namespaceConstraints;
    
    // 当前约束栈（跟踪当前作用域的约束）
    std::vector<std::vector<std::shared_ptr<ConstraintRule>>> constraintStack;
    
    // 上下文
    std::shared_ptr<CHTLContext> context;
    
    // 命名空间管理器引用
    std::shared_ptr<NamespaceManager> namespaceManager;
    
public:
    ConstraintManager(std::shared_ptr<CHTLContext> ctx);
    
    // 设置命名空间管理器
    void setNamespaceManager(std::shared_ptr<NamespaceManager> mgr) { namespaceManager = mgr; }
    
    // 添加约束
    void addConstraint(std::shared_ptr<ConstraintRule> rule, const std::string& scope);
    
    // 添加元素约束
    void addElementConstraint(const std::string& elementPath, std::shared_ptr<ConstraintRule> rule);
    
    // 添加命名空间约束
    void addNamespaceConstraint(const std::string& namespacePath, std::shared_ptr<ConstraintRule> rule);
    
    // 检查约束
    bool checkConstraint(const ConstraintTarget& target, const std::string& currentScope) const;
    bool checkConstraint(const std::string& elementOrType, const std::string& currentScope) const;
    
    // 进入/退出作用域
    void enterScope(const std::string& scopeName);
    void exitScope();
    
    // 获取当前作用域的所有约束
    std::vector<std::shared_ptr<ConstraintRule>> getCurrentConstraints() const;
    
    // 获取违反的约束
    std::vector<std::string> getViolations(const ConstraintTarget& target, 
                                          const std::string& currentScope) const;
    
    // 清理
    void clear();
};

// 约束处理器
class ConstraintProcessor {
private:
    ConstraintManager& manager;
    CHTLGenerator& generator;
    
public:
    ConstraintProcessor(ConstraintManager& mgr, CHTLGenerator& gen)
        : manager(mgr), generator(gen) {}
    
    // 处理except语句
    void processExceptStatement(const std::string& statement, const std::string& currentScope);
    
    // 解析约束声明
    struct ExceptDeclaration {
        std::vector<ConstraintTarget> targets;
        ConstraintType type;
        bool isValid;
    };
    
    ExceptDeclaration parseExceptDeclaration(const std::string& declaration);
    
    // 解析单个约束目标
    ConstraintTarget parseConstraintTarget(const std::string& targetStr);
    
    // 验证使用
    bool validateUsage(const std::string& usage, const std::string& currentScope);
};

// 约束检查器
class ConstraintChecker {
private:
    const ConstraintManager& manager;
    std::string currentElementPath;
    std::string currentNamespace;
    
public:
    ConstraintChecker(const ConstraintManager& mgr)
        : manager(mgr) {}
    
    // 设置当前上下文
    void setCurrentElement(const std::string& path) { currentElementPath = path; }
    void setCurrentNamespace(const std::string& ns) { currentNamespace = ns; }
    
    // 检查HTML元素
    bool canUseHtmlElement(const std::string& elementName) const;
    
    // 检查自定义
    bool canUseCustom(const std::string& customType, const std::string& customName) const;
    
    // 检查模板
    bool canUseTemplate(const std::string& templateType, const std::string& templateName) const;
    
    // 检查定义
    bool canDefineCustom(const std::string& customType) const;
    bool canDefineTemplate(const std::string& templateType) const;
    
    // 获取详细错误信息
    std::string getConstraintError(const ConstraintTarget& target) const;
};

// 辅助函数
namespace ConstraintHelper {
    // 解析约束目标类型
    ConstraintTargetType parseTargetType(const std::string& typeStr);
    
    // 判断是否是类型约束
    bool isTypeConstraint(const std::string& constraint);
    
    // 判断是否是精确约束
    bool isPreciseConstraint(const std::string& constraint);
    
    // 规范化约束目标
    std::string normalizeTarget(const std::string& target);
    
    // 分割except语句中的多个目标
    std::vector<std::string> splitExceptTargets(const std::string& exceptClause);
    
    // 构建元素路径
    std::string buildElementPath(const std::vector<std::string>& elements);
    
    // 获取约束类型字符串
    std::string constraintTypeToString(ConstraintType type);
    
    // 获取目标类型字符串
    std::string targetTypeToString(ConstraintTargetType type);
}

} // namespace chtl

#endif // CHTL_CONSTRAINT_H