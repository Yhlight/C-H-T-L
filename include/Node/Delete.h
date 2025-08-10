#ifndef CHTL_NODE_DELETE_H
#define CHTL_NODE_DELETE_H

#include "Node/Node.h"
#include <vector>
#include <string>
#include <algorithm>

namespace chtl {

/**
 * @brief Delete 节点 - 表示删除操作
 * 
 * 用于在自定义组件中删除继承的元素、样式或属性。
 */
class Delete : public Node {
private:
    std::vector<std::string> targets_;      // 删除目标列表
    std::vector<std::string> constraints_;  // 约束条件

public:
    Delete();
    virtual ~Delete() = default;

    // 基类接口实现
    std::shared_ptr<Node> clone(bool deep = true) const override;
    void accept(Visitor* visitor) override;
    std::string toString() const override;

    // 目标管理
    void addTarget(const std::string& target);
    void addTargets(const std::vector<std::string>& targets);
    const std::vector<std::string>& getTargets() const;
    void clearTargets();
    bool hasTarget(const std::string& target) const;

    // 约束管理
    void addConstraint(const std::string& constraint);
    const std::vector<std::string>& getConstraints() const;
};

} // namespace chtl

#endif // CHTL_NODE_DELETE_H