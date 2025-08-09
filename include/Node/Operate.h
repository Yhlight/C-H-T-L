#ifndef CHTL_OPERATE_H
#define CHTL_OPERATE_H

#include "Node/Node.h"
#include <set>

namespace chtl {

// Operate节点 - 操作节点，用于insert、delete、replace等操作
class Operate : public Node {
public:
    enum class OperationType {
        INSERT,     // insert操作
        DELETE,     // delete操作
        REPLACE,    // replace操作
        MOVE        // 移动操作（扩展）
    };
    
    enum class Position {
        BEFORE,     // before
        AFTER,      // after
        AT,         // at
        TOP,        // top
        BOTTOM,     // bottom
        AT_TOP,     // at top
        AT_BOTTOM,  // at bottom
        REPLACE,    // replace
        DEFAULT     // 默认位置
    };
    
private:
    OperationType operationType_;
    Position position_ = Position::DEFAULT;
    std::string target_;                        // 操作目标
    std::string selector_;                      // 选择器
    std::shared_ptr<Node> content_;            // 操作内容
    std::set<std::string> constraints_;        // except约束
    
public:
    Operate(OperationType type)
        : Node(NodeType::OPERATE, "operate"), operationType_(type) {}
    
    // 默认构造函数
    Operate() : Node(NodeType::OPERATE, "operate"), operationType_(OperationType::INSERT) {}
    
    // 操作类型
    OperationType getOperationType() const { return operationType_; }
    OperationType getOperation() const { return operationType_; }
    void setOperationType(OperationType type) { operationType_ = type; }
    void setOperation(OperationType type) { operationType_ = type; }
    
    // 位置管理
    Position getPosition() const { return position_; }
    void setPosition(Position pos) { position_ = pos; }
    
    // 目标和选择器
    const std::string& getTarget() const { return target_; }
    void setTarget(const std::string& target) { target_ = target; }
    
    const std::string& getSelector() const { return selector_; }
    void setSelector(const std::string& selector) { selector_ = selector; }
    
    // 操作内容
    std::shared_ptr<Node> getContent() const { return content_; }
    void setContent(const std::shared_ptr<Node>& content) { content_ = content; }
    
    // 约束管理
    void addConstraint(const std::string& constraint) { constraints_.insert(constraint); }
    void removeConstraint(const std::string& constraint) { constraints_.erase(constraint); }
    bool hasConstraint(const std::string& constraint) const { return constraints_.find(constraint) != constraints_.end(); }
    const std::set<std::string>& getConstraints() const { return constraints_; }
    void clearConstraints() { constraints_.clear(); }
    
    // 辅助方法
    std::string getOperationTypeString() const;
    std::string getPositionString() const;
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_OPERATE_H