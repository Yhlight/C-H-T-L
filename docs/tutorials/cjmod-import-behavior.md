# CJmod 导入行为说明

## 导入语法

### 1. 导入整个模块（包含所有子模块）
```chtl
[Import] @CJmod from "ReactiveModule";
```
- 加载主模块
- 自动加载所有子模块
- 所有子模块的语法规则都会生效

### 2. 仅导入特定子模块
```chtl
[Import] @CJmod from "ReactiveModule.State";
[Import] @CJmod from "ReactiveModule/Computed";  // 支持 / 分隔符
```
- 只加载指定的子模块
- 只有该子模块的语法规则生效
- 主模块不会被加载（除非子模块依赖主模块）

### 3. 显式导入所有子模块
```chtl
[Import] @CJmod from "ReactiveModule.*";
[Import] @CJmod from "ReactiveModule/*";  // 等价写法
```
- 行为与导入主模块相同
- 提供显式的语法来表明意图

## 加载行为

### 主模块加载时
1. 解析主模块的 `info/模块名.chtl` 文件
2. 加载主模块的 C++ 实现
3. 自动扫描并加载所有子模块
4. 合并所有语法规则和运行时代码

### 子模块加载时
1. 确保主模块已加载（用于获取子模块信息）
2. 加载特定子模块的 `子模块名/info/子模块名.chtl`
3. 只应用该子模块的规则

## 示例对比

```chtl
// 场景1：需要完整的响应式功能
[Import] @CJmod from "ReactiveModule";
// 可以使用：reactive、state、computed、watch 等所有功能

// 场景2：只需要状态管理
[Import] @CJmod from "ReactiveModule.State";
// 只能使用：state、update、batch 等状态相关功能

// 场景3：需要状态和计算属性
[Import] @CJmod from "ReactiveModule.State";
[Import] @CJmod from "ReactiveModule.Computed";
// 可以使用：state 和 computed 功能，但不包括 watch
```

## 性能考虑

- 导入整个模块会加载所有子模块，可能会增加初始化时间
- 如果只需要特定功能，建议只导入相应的子模块
- 子模块之间可以有依赖关系，会自动处理