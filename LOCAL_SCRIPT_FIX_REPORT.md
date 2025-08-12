# 局部脚本收集问题分析报告

## 问题描述
局部脚本（元素内部的 script 标签）没有被正确收集和输出到最终的 JavaScript 文件中。

## 已完成的修复

### 1. ✅ 修正了脚本类型判断逻辑
- **问题**：原本依赖 `ScriptType::INLINE` 和 `isScoped()` 来判断局部脚本
- **修复**：改为根据父节点是否为元素节点来判断
- **代码**：
  ```cpp
  bool isLocalScript = false;
  if (parent && parent->getType() == NodeType::ELEMENT) {
      auto element = std::static_pointer_cast<Element>(parent);
      std::string tagName = element->getTagName();
      // body 和 html 内的脚本被认为是全局脚本
      if (tagName != "body" && tagName != "html" && tagName != "head") {
          isLocalScript = true;
      }
  }
  ```

### 2. ✅ 移除了基类的默认脚本处理
- **问题**：`Generator::visitScript` 和 `WebGenerator::visitScript` 都在处理脚本
- **修复**：让基类不处理任何脚本，完全由派生类决定

### 3. ✅ 修复了 Script::generateWrappedCode
- **问题**：该方法内部也在收集局部脚本，导致重复处理
- **修复**：移除了收集逻辑，只负责生成包装代码

## 当前状态

### 工作的部分
- 全局脚本正确输出（在 body 或 html 内的脚本）
- 脚本类型判断逻辑正确
- `collectLocalScript` 方法本身工作正常

### 不工作的部分
- 局部脚本虽然被识别，但没有出现在最终输出中
- `generateRuntimeCode` 中的 `collectedScripts_` 似乎为空

## 问题分析

### 可能的原因
1. **时序问题**：`collectedScripts_` 在 `generateRuntimeCode` 调用时为空
2. **实例问题**：可能有多个 `ChtlJsRuntime` 实例
3. **清理问题**：`collectedScripts_` 在不该清理的时候被清理了

### 调试发现
- `WebGenerator::visitScript` 正确识别了局部脚本
- `jsRuntime_->collectLocalScript` 被调用
- 但最终 `generateRuntimeCode` 返回的代码不包含局部脚本部分

## 下一步行动

### 1. 验证单例模式
确保 `ChtlJsRuntime::getInstance()` 真的返回同一个实例

### 2. 添加调试输出
在关键位置添加日志：
- `collectLocalScript` 调用时
- `generateRuntimeCode` 调用时
- 查看 `collectedScripts_.size()`

### 3. 检查调用链
追踪从 `visitScript` 到 `generateRuntimeCode` 的完整调用链

### 4. 考虑架构改进
可能需要重新设计局部脚本的收集和注入机制，确保：
- 收集和生成使用同一个实例
- 时序正确
- 不会意外清理

## 临时解决方案
如果问题难以快速解决，可以考虑：
1. 将局部脚本直接添加到 `jsCollector_` 而不是通过运行时
2. 或者修改 `injectRuntimeCode` 的时机

## 结论
局部脚本收集是 CHTL-JS 的核心功能，必须修复。当前的问题似乎是架构性的，可能需要更深入的调试和重构。