#include <iostream>
#include <memory>
#include <vector>

// 使用 unique_ptr 的 AST 示例
class Node {
public:
    explicit Node(const std::string& name) : name_(name) {}
    
    void addChild(std::unique_ptr<Node> child) {
        if (child) {
            child->parent_ = this;
            children_.push_back(std::move(child));
        }
    }
    
    void print(int depth = 0) const {
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << name_ << std::endl;
        
        for (const auto& child : children_) {
            child->print(depth + 1);
        }
    }
    
private:
    std::string name_;
    Node* parent_ = nullptr;
    std::vector<std::unique_ptr<Node>> children_;
};

int main() {
    // 创建 AST
    auto root = std::make_unique<Node>("html");
    
    auto head = std::make_unique<Node>("head");
    head->addChild(std::make_unique<Node>("title"));
    
    auto body = std::make_unique<Node>("body");
    body->addChild(std::make_unique<Node>("h1"));
    body->addChild(std::make_unique<Node>("p"));
    
    // 转移所有权
    root->addChild(std::move(head));
    root->addChild(std::move(body));
    
    // 打印 AST
    root->print();
    
    return 0;
}

/* 输出：
html
  head
    title
  body
    h1
    p
*/