# unique_ptr 迁移指南

## 概述

CHTL 项目当前使用 `shared_ptr` 管理 AST 节点，这导致了以下问题：
1. 所有权不清晰
2. 潜在的循环引用
3. 性能开销
4. 内存使用效率低

本指南说明如何逐步迁移到 `unique_ptr`。

## 核心设计原则

### 1. 清晰的所有权模型
- 父节点拥有子节点（`std::vector<std::unique_ptr<Node>>`）
- 子节点通过原始指针引用父节点（`Node* parent_`）
- 访问者和生成器使用原始指针遍历树

### 2. 移动语义
- 禁用拷贝构造和赋值
- 启用移动构造和赋值
- 使用 `std::move` 转移所有权

### 3. 安全的节点操作
```cpp
// 添加子节点（转移所有权）
void addChild(std::unique_ptr<Node> child) {
    if (child) {
        child->setParent(this);
        children_.push_back(std::move(child));
    }
}

// 获取子节点（不转移所有权）
Node* getChild(size_t index) const {
    return index < children_.size() ? children_[index].get() : nullptr;
}

// 取出子节点（转移所有权）
std::unique_ptr<Node> takeChild(size_t index) {
    if (index >= children_.size()) return nullptr;
    auto child = std::move(children_[index]);
    children_.erase(children_.begin() + index);
    if (child) child->setParent(nullptr);
    return child;
}
```

## 迁移步骤

### 第一阶段：创建新的基础设施
1. ✅ 创建 `UniqueNode` 基类
2. ✅ 创建 `UniqueParser` 示例
3. ⬜ 创建 `UniqueGenerator` 基类
4. ⬜ 创建节点工厂类

### 第二阶段：逐步迁移组件
1. ⬜ 迁移简单节点类型（Text, Comment）
2. ⬜ 迁移复杂节点类型（Element, Template）
3. ⬜ 迁移解析器
4. ⬜ 迁移生成器

### 第三阶段：更新接口
1. ⬜ 更新 Context 接口
2. ⬜ 更新 Visitor 模式
3. ⬜ 更新测试用例

### 第四阶段：清理和优化
1. ⬜ 移除旧的 shared_ptr 代码
2. ⬜ 性能测试和优化
3. ⬜ 内存使用分析

## 代码示例

### 创建节点
```cpp
// 旧代码（shared_ptr）
auto element = std::make_shared<Element>("div");
element->addChild(std::make_shared<Text>("Hello"));

// 新代码（unique_ptr）
auto element = std::make_unique<Element>("div");
element->addChild(std::make_unique<Text>("Hello"));
```

### 遍历树
```cpp
// 使用原始指针遍历
void visitNode(const Node* node) {
    if (!node) return;
    
    // 处理当前节点
    processNode(node);
    
    // 遍历子节点
    for (size_t i = 0; i < node->getChildCount(); ++i) {
        visitNode(node->getChild(i));
    }
}
```

### 修改树结构
```cpp
// 移动节点到另一个父节点
auto child = oldParent->takeChild(index);
if (child) {
    newParent->addChild(std::move(child));
}
```

## 注意事项

### 1. 避免悬空指针
- 永远不要存储原始指针的长期引用
- 使用弱引用模式处理交叉引用

### 2. 异常安全
- 使用 RAII 和智能指针确保异常安全
- 在可能抛出异常的地方使用 `std::move` 要小心

### 3. 性能考虑
- `unique_ptr` 比 `shared_ptr` 更轻量
- 移动操作比拷贝操作更高效
- 考虑使用对象池优化频繁的分配/释放

## 迁移检查清单

- [ ] 所有 `make_shared` 替换为 `make_unique`
- [ ] 所有 `shared_ptr` 参数改为原始指针或 `unique_ptr`
- [ ] 所有容器从 `vector<shared_ptr>` 改为 `vector<unique_ptr>`
- [ ] 移除不必要的引用计数检查
- [ ] 更新文档和注释
- [ ] 运行完整的测试套件
- [ ] 进行内存泄漏检查

## 工具和脚本

### 自动化迁移脚本（伪代码）
```bash
# 查找所有 shared_ptr 使用
grep -r "shared_ptr<.*Node>" src/ include/

# 替换 make_shared 为 make_unique
find . -name "*.cpp" -o -name "*.h" | xargs sed -i 's/make_shared/make_unique/g'

# 查找潜在的循环引用
# TODO: 编写分析工具
```

## 总结

迁移到 `unique_ptr` 是一个重要但值得的重构。它将带来：
- 更清晰的代码
- 更好的性能
- 更少的内存使用
- 更容易调试的所有权问题

这个迁移应该分阶段进行，每个阶段都要充分测试，确保系统的稳定性。