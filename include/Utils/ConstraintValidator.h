#ifndef CHTL_CONSTRAINT_VALIDATOR_H
#define CHTL_CONSTRAINT_VALIDATOR_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "Node/Node.h"
#include "Context/BasicContext.h"

namespace chtl {

// 约束类型
enum class ConstraintType {
    PRECISE,        // 精确约束（具体元素或对象）
    TYPE,           // 类型约束（@Html, [Custom], [Template]）
    GLOBAL          // 全局约束（命名空间级别）
};

// 约束信息
struct ConstraintInfo {
    ConstraintType type;
    std::string value;              // 约束值
    std::string scope;              // 作用域（元素路径或命名空间）
    bool isViolated = false;        // 是否被违反
    std::vector<std::string> violations;  // 违反记录
};

// 约束验证器
class ConstraintValidator {
public:
    ConstraintValidator(std::shared_ptr<BasicContext> context);
    ~ConstraintValidator() = default;
    
    // 验证整个AST的约束
    bool validateConstraints(std::shared_ptr<Node> ast);
    
    // 验证单个节点的约束
    bool validateNode(std::shared_ptr<Node> node, std::shared_ptr<Node> parent);
    
    // 注册约束
    void registerConstraint(const std::string& scope, const std::string& constraint);
    
    // 获取约束违反报告
    std::vector<ConstraintInfo> getViolations() const;
    
    // 设置上下文
    void setContext(std::shared_ptr<BasicContext> context) { context_ = context; }
    
    // 清除所有约束
    void clear();
    
private:
    // 解析约束字符串
    ConstraintType parseConstraintType(const std::string& constraint);
    
    // 检查节点是否匹配约束
    bool matchesConstraint(std::shared_ptr<Node> node, const std::string& constraint);
    
    // 检查精确约束
    bool matchesPreciseConstraint(std::shared_ptr<Node> node, const std::string& constraint);
    
    // 检查类型约束
    bool matchesTypeConstraint(std::shared_ptr<Node> node, const std::string& constraint);
    
    // 获取节点的完整路径
    std::string getNodePath(std::shared_ptr<Node> node);
    
    // 递归验证
    void validateRecursive(std::shared_ptr<Node> node, 
                          const std::string& currentPath,
                          const std::unordered_set<std::string>& activeConstraints);
    
    // 提取约束中的具体信息
    struct ConstraintParts {
        std::string category;   // [Custom], [Template], @Html, 或元素名
        std::string type;       // @Element, @Style, @Var
        std::string name;       // 具体名称
    };
    ConstraintParts parseConstraintParts(const std::string& constraint);
    
private:
    std::shared_ptr<BasicContext> context_;
    
    // 约束映射：scope -> constraints
    std::unordered_map<std::string, std::unordered_set<std::string>> constraints_;
    
    // 违反记录
    std::vector<ConstraintInfo> violations_;
    
    // 当前路径栈（用于跟踪位置）
    std::vector<std::string> pathStack_;
    
    // 命名空间约束栈
    std::vector<std::unordered_set<std::string>> namespaceConstraintStack_;
};

} // namespace chtl

#endif // CHTL_CONSTRAINT_VALIDATOR_H