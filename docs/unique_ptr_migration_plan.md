# unique_ptr 迁移计划

## 概述

将 CHTL 项目从 `shared_ptr` 迁移到 `unique_ptr`，以实现清晰的所有权模型。

## 迁移策略

### 第一阶段：创建并行实现
1. ✅ 创建新的 `NodeUnique` 基类和派生类
2. 创建新的 `ParserUnique` 类
3. 创建新的 `GeneratorUnique` 类
4. 保持现有代码不变，确保项目继续工作

### 第二阶段：逐步迁移
1. 迁移解析器到 `unique_ptr`
2. 迁移生成器到 `unique_ptr`
3. 迁移其他组件

### 第三阶段：清理
1. 删除旧的 `shared_ptr` 实现
2. 重命名 `Unique` 类为原始名称
3. 全面测试

## 所有权规则

### 基本原则
- **父节点拥有子节点**：使用 `unique_ptr<Node>`
- **父节点引用**：使用原始指针 `Node*`（不拥有）
- **临时引用**：使用原始指针或引用
- **转移所有权**：使用 `std::move`

### 具体实现

#### 1. AST 节点
```cpp
class Node {
    Node* parent_ = nullptr;  // 不拥有
    std::vector<std::unique_ptr<Node>> children_;  // 拥有
};
```

#### 2. 解析器
```cpp
class Parser {
    std::unique_ptr<Node> parseDocument();  // 返回所有权
    void parseElement(Node* parent);  // 接收原始指针
};
```

#### 3. 生成器
```cpp
class Generator {
    void generate(const Node* ast);  // 只读访问
    void visit(const Node* node);  // 只读访问
};
```

## 需要修改的主要文件

### 核心文件
- [ ] `include/Node/Node.h` - 节点定义
- [ ] `include/Parser/Parser.h` - 解析器接口
- [ ] `include/Generator/Generator.h` - 生成器接口
- [ ] `src/Parser/StandardParser.cpp` - 标准解析器实现
- [ ] `src/Generator/WebGenerator.cpp` - Web生成器实现

### 辅助文件
- [ ] 所有节点类型的实现文件
- [ ] 上下文管理相关文件
- [ ] 测试文件

## 潜在问题和解决方案

### 1. 循环引用
**问题**：模板引用可能导致循环引用
**解决**：使用弱引用或ID系统

### 2. 节点共享
**问题**：某些节点可能需要被多个父节点引用
**解决**：使用克隆或引用计数的特殊节点类型

### 3. 性能考虑
**问题**：频繁的移动操作可能影响性能
**解决**：使用移动语义优化，避免不必要的拷贝

## 测试策略

1. **单元测试**：为每个迁移的组件创建测试
2. **集成测试**：确保整个编译流程正常工作
3. **性能测试**：比较迁移前后的性能
4. **内存测试**：使用工具检测内存泄漏

## 时间估算

- 第一阶段：2-3天
- 第二阶段：3-5天
- 第三阶段：1-2天
- 测试和修复：2-3天

总计：8-13天