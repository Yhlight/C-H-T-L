# CJmod 架构原理说明

## 核心理解：CJmod = 模块化的 CHTL JS 扩展

### 1. **统一的扫描切割机制**

CHTL JS 和 CJmod 使用**完全相同**的扫描切割机制：

```cpp
// 官方 CHTL JS 语法
{{#id}}         →  document.getElementById('id')
{{.class}}      →  document.getElementsByClassName('class')
obj->method()   →  obj.method()
foreach x in y  →  y.forEach(x =>

// CJmod 扩展语法（响应式模块）
count := 0      →  let count = reactive(0)
double => x*2   →  let double = computed(() => x*2)
watch count {}  →  watch(count, () => {})
```

**这意味着**：
- CJmod 不是一个独立的系统
- CJmod 是 CHTL JS 语法规则的模块化组织方式
- 所有规则在**一次扫描**中完成

### 2. **实际的处理流程**

```cpp
std::string CHTLJSProcessor::processJavaScript(const std::string& jsCode,
                                               const std::vector<std::string>& activeModules) {
    // 收集所有规则（官方 + 模块）
    std::vector<ScanCutRule> allRules = officialRules_;
    
    // 添加激活模块的规则
    for (const auto& moduleName : activeModules) {
        auto moduleRules = modules_[moduleName]->getScanCutRules();
        allRules.insert(allRules.end(), moduleRules.begin(), moduleRules.end());
    }
    
    // 一次扫描应用所有规则
    return applyScanCutRules(jsCode, allRules);
}
```

### 3. **优先级系统的作用**

优先级确保了正确的转换顺序：

```
优先级 1000: {{&}}        → this              (最基础的转换)
优先级 900:  {{#id}}      → getElementById    (DOM 选择器)
优先级 800:  ->           → .                 (方法调用)
优先级 100:  :=           → reactive()        (响应式声明)
优先级 90:   =>           → computed()        (计算属性)
```

### 4. **为什么当前实现看起来是多次扫描？**

当前实现中的"多次扫描"实际上是为了处理：

1. **模块覆盖**：某些模块可能想要修改官方语法的行为
2. **依赖关系**：某些转换可能依赖于其他转换的结果

但理想情况下，应该是**一次扫描**：

```cpp
// 优化后的实现
class OptimizedCHTLJSProcessor {
    std::string processJavaScript(const std::string& jsCode,
                                 const std::vector<std::string>& activeModules) {
        // 1. 收集所有规则
        auto allRules = collectAllRules(activeModules);
        
        // 2. 解决冲突（覆盖、优先级）
        auto finalRules = resolveConflicts(allRules);
        
        // 3. 一次扫描完成所有转换
        return singlePassTransform(jsCode, finalRules);
    }
};
```

### 5. **CJmod 的本质**

CJmod 的本质是：
- **语法糖的模块化管理**：将相关的语法糖组织成模块
- **可选加载**：只有导入的模块才会激活其语法规则
- **命名空间隔离**：避免不同模块的语法冲突
- **版本管理**：支持不同版本的语法规则

### 6. **示例：完整的处理流程**

输入 CHTL 文件：
```chtl
[Import] @CJmod from "builtin:reactive";

div {
    script {
        count := 0;
        doubled => count.value * 2;
        
        {{#button}}->onclick = () => {
            count.value++;
        };
    }
}
```

处理步骤：
1. **解析阶段**：识别 `@CJmod` 导入，激活 "reactive" 模块
2. **代码生成**：生成初始 JavaScript
3. **扫描切割**（一次完成）：
   - `count := 0` → `let count = reactive(0)`
   - `doubled => count.value * 2` → `let doubled = computed(() => count.value * 2)`
   - `{{#button}}` → `document.getElementById('button')`
   - `->onclick` → `.onclick`

### 7. **扩展方式的统一性**

所有 CHTL JS 扩展都遵循相同的模式：
```cpp
struct ScanCutRule {
    std::string name;        // 规则名称
    std::regex pattern;      // 匹配模式
    std::string replacement; // 替换模板
    int priority;           // 优先级
};
```

无论是官方语法还是 CJmod 扩展，都是 `ScanCutRule` 的集合。

### 8. **为什么这种设计优雅？**

1. **简单性**：所有语法扩展都是文本转换
2. **可预测性**：优先级系统确保转换顺序
3. **模块化**：相关语法组织在一起
4. **非侵入性**：不影响核心编译器
5. **可扩展性**：添加新语法只需定义新规则

### 总结

CJmod 不是一个独立的系统，而是 CHTL JS 语法的模块化扩展机制。它使用与官方 CHTL JS 完全相同的扫描切割技术，通过模块化的方式组织和管理语法扩展，让开发者可以按需引入所需的语法特性。