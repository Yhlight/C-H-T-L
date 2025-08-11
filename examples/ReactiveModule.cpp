#include "CJmod/CJmodInterface.h"
#include <sstream>

namespace chtl {
namespace cjmod {

// 响应式编程模块
class ReactiveModule : public ICJmod {
public:
    std::string getName() const override {
        return "reactive";
    }
    
    std::string getVersion() const override {
        return "1.0.0";
    }
    
    std::string getDescription() const override {
        return "Adds reactive programming capabilities to CHTL JS";
    }
    
    std::vector<TransformRule> getTransformRules() const override {
        std::vector<TransformRule> rules;
        
        // 响应式变量声明: count := 0
        rules.push_back({
            "reactive-declaration",
            std::regex(R"((\w+)\s*:=\s*(.+);)"),
            100,  // 高优先级
            [](const std::smatch& match) {
                return "const " + match[1].str() + " = reactive(" + match[2].str() + ");";
            },
            nullptr
        });
        
        // 计算属性: doubled => count.value * 2
        rules.push_back({
            "computed-property",
            std::regex(R"((\w+)\s*=>\s*(.+);)"),
            90,
            [](const std::smatch& match) {
                return "const " + match[1].str() + " = computed(() => " + match[2].str() + ");";
            },
            nullptr
        });
        
        // 监听器: watch count -> { ... }
        rules.push_back({
            "watch-statement",
            std::regex(R"(watch\s+(\w+)\s*->\s*\{)"),
            80,
            [](const std::smatch& match) {
                return "watch(" + match[1].str() + ", () => {";
            },
            nullptr
        });
        
        return rules;
    }
    
    std::vector<MethodInjection> getMethodInjections() const override {
        std::vector<MethodInjection> injections;
        
        // 双向绑定方法
        injections.push_back({
            "Element",
            "bindModel",
            R"(function(varName) {
                const element = this;
                const variable = window[varName];
                
                // 监听输入事件
                element.addEventListener('input', (e) => {
                    if (variable && variable.value !== undefined) {
                        variable.value = e.target.value;
                    }
                });
                
                // 监听变量变化
                if (variable && variable.subscribe) {
                    variable.subscribe(() => {
                        element.value = variable.value;
                    });
                }
            })",
            false
        });
        
        return injections;
    }
    
    std::vector<OperatorDefinition> getOperatorDefinitions() const override {
        // 这个模块不定义新运算符
        return {};
    }
    
    std::string getRuntimeCode() const override {
        return R"(
  // Reactive System
  function reactive(initialValue) {
    const subscribers = new Set();
    let value = initialValue;
    
    return {
      get value() {
        return value;
      },
      set value(newValue) {
        if (value !== newValue) {
          value = newValue;
          subscribers.forEach(fn => fn());
        }
      },
      subscribe(fn) {
        subscribers.add(fn);
        return () => subscribers.delete(fn);
      }
    };
  }
  
  function computed(computeFn) {
    let cachedValue;
    let dirty = true;
    
    return {
      get value() {
        if (dirty) {
          cachedValue = computeFn();
          dirty = false;
        }
        return cachedValue;
      },
      invalidate() {
        dirty = true;
      }
    };
  }
  
  function watch(target, callback) {
    if (target && target.subscribe) {
      return target.subscribe(callback);
    }
  }
)";
    }
};

// 工厂类
class ReactiveModuleFactory : public ICJmodFactory {
public:
    std::unique_ptr<ICJmod> create() override {
        return std::make_unique<ReactiveModule>();
    }
    
    std::string getModuleName() const override {
        return "reactive";
    }
};

// 语法覆写示例：改变 {{&}} 的行为
class EnhancedSelfReference : public ICJmod {
public:
    std::string getName() const override {
        return "enhanced-self";
    }
    
    std::string getVersion() const override {
        return "1.0.0";
    }
    
    std::string getDescription() const override {
        return "Enhances {{&}} to support chaining";
    }
    
    void initialize() override {
        // 覆写 {{&}} 语法
        TransformRule rule {
            "enhanced-self-reference",
            std::regex(R"(\{\{&\}\})"),
            1000,  // 最高优先级
            [](const std::smatch& match) {
                return "$(this)";  // 返回 jQuery 包装的对象
            },
            nullptr
        };
        
        CJmodProcessor::getInstance().overrideCHTLSyntax("self-reference", rule);
    }
    
    std::vector<TransformRule> getTransformRules() const override {
        return {};  // 通过 initialize 覆写，不需要规则
    }
    
    std::vector<MethodInjection> getMethodInjections() const override {
        return {};
    }
    
    std::vector<OperatorDefinition> getOperatorDefinitions() const override {
        return {};
    }
    
    std::string getRuntimeCode() const override {
        return R"(
  // jQuery-like wrapper
  function $(element) {
    if (typeof element === 'string') {
      return document.querySelector(element);
    }
    
    // 添加链式调用支持
    const wrapper = {
      el: element,
      addClass(className) {
        this.el.classList.add(className);
        return this;
      },
      removeClass(className) {
        this.el.classList.remove(className);
        return this;
      },
      on(event, handler) {
        this.el.addEventListener(event, handler);
        return this;
      }
    };
    
    return wrapper;
  }
)";
    }
};

} // namespace cjmod
} // namespace chtl