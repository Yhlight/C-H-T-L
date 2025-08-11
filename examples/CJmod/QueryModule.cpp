#include "CJmod/CJmodInterface.h"

namespace chtl {
namespace cjmod {

class QueryModule : public ICJmod {
public:
    std::string getName() const override {
        return "query";
    }
    
    std::string getVersion() const override {
        return "1.0.0";
    }
    
    std::string getDescription() const override {
        return "Enhanced DOM querying with powerful selectors";
    }
    
    std::vector<TransformRule> getTransformRules() const override {
        std::vector<TransformRule> rules;
        
        // 扩展选择器: {{:visible}} -> 所有可见元素
        rules.push_back({
            "visible-selector",
            std::regex(R"(\{\{:visible\}\})"),
            110,
            [](const std::smatch& match) {
                return "document.querySelectorAll(':not([style*=\"display: none\"]):not([hidden])')";
            },
            nullptr
        });
        
        // 父元素选择器: {{^}} -> 当前元素的父元素
        rules.push_back({
            "parent-selector",
            std::regex(R"(\{\{\^\}\})"),
            105,
            [](const std::smatch& match) {
                return "this.parentElement";
            },
            nullptr
        });
        
        // 兄弟选择器: {{+}} -> 下一个兄弟元素
        rules.push_back({
            "next-sibling",
            std::regex(R"(\{\{\+\}\})"),
            100,
            [](const std::smatch& match) {
                return "this.nextElementSibling";
            },
            nullptr
        });
        
        // 查询语法: $(".class") -> 返回 NodeList 包装器
        rules.push_back({
            "query-syntax",
            std::regex(R"(\$\s*\(\s*["']([^"']+)["']\s*\))"),
            95,
            [](const std::smatch& match) {
                return "new QueryList('" + match[1].str() + "')";
            },
            nullptr
        });
        
        // 属性包含选择器: {{[data-*]}} -> 包含 data- 属性的元素
        rules.push_back({
            "attribute-contains",
            std::regex(R"(\{\{\[([^\]]+)\*\]\}\})"),
            90,
            [](const std::smatch& match) {
                return "document.querySelectorAll('[" + match[1].str() + "]')";
            },
            nullptr
        });
        
        return rules;
    }
    
    std::vector<MethodInjection> getMethodInjections() const override {
        return {
            {
                "Element",
                "find",
                R"(function(selector) {
                    return this.querySelector(selector);
                })",
                false
            },
            {
                "Element",
                "findAll",
                R"(function(selector) {
                    return this.querySelectorAll(selector);
                })",
                false
            },
            {
                "Element",
                "closest",
                R"(function(selector) {
                    let element = this;
                    while (element && element !== document) {
                        if (element.matches(selector)) {
                            return element;
                        }
                        element = element.parentElement;
                    }
                    return null;
                })",
                false
            },
            {
                "Element",
                "siblings",
                R"(function(selector) {
                    const siblings = [];
                    let sibling = this.parentElement.firstElementChild;
                    
                    while (sibling) {
                        if (sibling !== this) {
                            if (!selector || sibling.matches(selector)) {
                                siblings.push(sibling);
                            }
                        }
                        sibling = sibling.nextElementSibling;
                    }
                    
                    return siblings;
                })",
                false
            }
        };
    }
    
    std::vector<OperatorDefinition> getOperatorDefinitions() const override {
        return {};
    }
    
    std::string getRuntimeCode() const override {
        return R"(
  // QueryList - jQuery-like wrapper for NodeList
  class QueryList {
    constructor(selector) {
      if (typeof selector === 'string') {
        this.elements = document.querySelectorAll(selector);
      } else if (selector instanceof NodeList) {
        this.elements = selector;
      } else if (selector instanceof Array) {
        this.elements = selector;
      } else {
        this.elements = [selector];
      }
    }
    
    each(callback) {
      this.elements.forEach((element, index) => {
        callback.call(element, index, element);
      });
      return this;
    }
    
    on(event, handler) {
      this.each(function() {
        this.addEventListener(event, handler);
      });
      return this;
    }
    
    addClass(className) {
      this.each(function() {
        this.classList.add(className);
      });
      return this;
    }
    
    removeClass(className) {
      this.each(function() {
        this.classList.remove(className);
      });
      return this;
    }
    
    show() {
      this.each(function() {
        this.style.display = '';
      });
      return this;
    }
    
    hide() {
      this.each(function() {
        this.style.display = 'none';
      });
      return this;
    }
    
    get length() {
      return this.elements.length;
    }
    
    get(index) {
      return this.elements[index];
    }
  }
  
  // 全局快捷函数
  window.$$ = function(selector) {
    return new QueryList(selector);
  };
)";
    }
};

} // namespace cjmod
} // namespace chtl