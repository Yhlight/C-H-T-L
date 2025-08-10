#include "Node/Delete.h"

namespace chtl {

Delete::Delete() 
    : Node(NodeType::DELETE) {
}

std::shared_ptr<Node> Delete::clone(bool deep) const {
    auto cloned = std::make_shared<Delete>();
    
    // 复制删除目标
    cloned->targets_ = targets_;
    
    // 复制约束
    cloned->constraints_ = constraints_;
    
    (void)deep; // Delete 节点没有子节点
    
    return cloned;
}

std::string Delete::toString() const {
    std::string result = "[Delete]";
    if (!targets_.empty()) {
        result += " targets: ";
        for (size_t i = 0; i < targets_.size(); ++i) {
            if (i > 0) result += ", ";
            result += targets_[i];
        }
    }
    return result;
}

void Delete::accept(Visitor* visitor) {
    // visitor->visit(this);
    (void)visitor; // TODO: 实现 Visitor 模式
}

void Delete::addTarget(const std::string& target) {
    targets_.push_back(target);
}

void Delete::addTargets(const std::vector<std::string>& targets) {
    targets_.insert(targets_.end(), targets.begin(), targets.end());
}

const std::vector<std::string>& Delete::getTargets() const {
    return targets_;
}

void Delete::clearTargets() {
    targets_.clear();
}

bool Delete::hasTarget(const std::string& target) const {
    return std::find(targets_.begin(), targets_.end(), target) != targets_.end();
}

void Delete::addConstraint(const std::string& constraint) {
    constraints_.push_back(constraint);
}

const std::vector<std::string>& Delete::getConstraints() const {
    return constraints_;
}

} // namespace chtl