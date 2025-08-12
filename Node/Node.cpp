#include "Node.h"
#include <algorithm>
#include <sstream>

namespace CHTL {

// 添加子节点
void Node::addChild(std::shared_ptr<Node> child) {
    if (child) {
        children_.push_back(child);
        child->setParent(this);
    }
}

// 删除子节点
void Node::removeChild(std::shared_ptr<Node> child) {
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        (*it)->setParent(nullptr);
        children_.erase(it);
    }
}

// 插入子节点
void Node::insertChild(size_t index, std::shared_ptr<Node> child) {
    if (child && index <= children_.size()) {
        children_.insert(children_.begin() + index, child);
        child->setParent(this);
    }
}

// 获取子节点
std::shared_ptr<Node> Node::getChild(size_t index) const {
    if (index < children_.size()) {
        return children_[index];
    }
    return nullptr;
}

// 设置属性
void Node::setAttribute(const std::string& key, const std::string& value) {
    attributes_[key] = value;
}

// 获取属性
std::string Node::getAttribute(const std::string& key) const {
    auto it = attributes_.find(key);
    if (it != attributes_.end()) {
        return it->second;
    }
    return "";
}

// 检查属性
bool Node::hasAttribute(const std::string& key) const {
    return attributes_.find(key) != attributes_.end();
}

// 删除属性
void Node::removeAttribute(const std::string& key) {
    attributes_.erase(key);
}

// 设置位置信息
void Node::setLocation(int startLine, int startColumn, int endLine, int endColumn) {
    startLine_ = startLine;
    startColumn_ = startColumn;
    endLine_ = endLine;
    endColumn_ = endColumn;
}

// 转换为字符串（调试用）
std::string Node::toString() const {
    std::stringstream ss;
    ss << "Node[type=" << static_cast<int>(type_) 
       << ", children=" << children_.size()
       << ", attributes=" << attributes_.size()
       << ", location=(" << startLine_ << ":" << startColumn_ 
       << "-" << endLine_ << ":" << endColumn_ << ")]";
    return ss.str();
}

} // namespace CHTL