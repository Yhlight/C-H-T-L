#include "v2/ChtlJs/ChtlJsCompiler.h"
#include "v2/Scanner/Scanner.h"
#include <regex>
#include <sstream>

namespace chtl::v2::chtljs {

class ChtlJsCompiler::Impl {
public:
    ChtlJsResult compile(const std::string& code, 
                        const std::map<std::string, std::string>& context) {
        ChtlJsResult result;
        
        if (code.empty()) {
            result.javascript = code;
            return result;
        }
        
        // 使用扫描器切割代码
        JsScanner scanner;
        scanner.setScanMode(ScanMode::STRICT);
        
        // 设置 CHTL-JS 验证器
        scanner.setChtlJsValidator([this](const std::string& expr) {
            return isValidChtlJsExpression(expr);
        });
        
        // 扫描代码，提取 CHTL-JS 段
        auto segments = scanner.scan(code, SegmentType::JS);
        
        // 收集扫描错误
        auto scanErrors = scanner.getErrors();
        result.errors.insert(result.errors.end(), scanErrors.begin(), scanErrors.end());
        
        // 编译每个 CHTL-JS 段
        std::map<std::string, std::string> replacements;
        
        for (const auto& segment : segments) {
            if (segment.type == SegmentType::CHTL_JS) {
                // 编译 CHTL-JS 表达式
                Expression expr;
                expr.raw = segment.content;
                expr.startPos = segment.chtlJsInfo.originalStart;
                expr.endPos = segment.chtlJsInfo.originalEnd;
                
                compileExpression(expr, context);
                
                // 保存替换内容
                replacements[segment.chtlJsInfo.placeholder] = expr.compiled;
                
                // 更新元数据
                updateMetadata(expr, result);
                result.expressions.push_back(expr);
            }
        }
        
        // 合并代码
        result.javascript = CodeMerger::mergeJs(segments, replacements);
        result.success = result.errors.empty();
        
        return result;
    }
    
    void setOption(const std::string& name, bool value) {
        if (name == "strict") {
            strict_ = value;
        }
    }
    
private:
    bool isValidChtlJsExpression(const std::string& expr) {
        // 验证 CHTL-JS 表达式语法
        std::string trimmed = trim(expr);
        
        if (trimmed.empty()) {
            return false;
        }
        
        // 检查是否是有效的选择器或方法调用
        if (trimmed[0] == '#') {
            // ID 选择器
            return isValidSelector(trimmed);
        } else if (trimmed[0] == '&') {
            // 当前元素引用
            return true;
        } else {
            // 可能是方法调用或其他表达式
            return isValidMethodCall(trimmed);
        }
    }
    
    void compileExpression(Expression& expr, 
                          const std::map<std::string, std::string>& context) {
        std::string trimmed = trim(expr.raw);
        
        if (trimmed.empty()) {
            expr.type = ExpressionType::EMPTY;
            expr.compiled = "";
            return;
        }
        
        // 判断表达式类型并编译
        if (trimmed[0] == '#') {
            // ID 选择器: {{#elementId}}
            compileElementSelector(expr, trimmed, context);
        } else if (trimmed == "&") {
            // 当前元素: {{&}}
            compileCurrentElement(expr, context);
        } else if (trimmed.find('.') != std::string::npos) {
            // 方法调用: {{&}}.method() 或 {{#id}}.method()
            compileMethodCall(expr, trimmed, context);
        } else {
            // 其他表达式
            expr.type = ExpressionType::OTHER;
            expr.compiled = trimmed;
        }
    }
    
    void compileElementSelector(Expression& expr, const std::string& selector,
                               const std::map<std::string, std::string>& context) {
        expr.type = ExpressionType::ELEMENT_SELECTOR;
        
        // 提取 ID
        std::string id = selector.substr(1); // 去掉 #
        
        if (id.empty()) {
            expr.compiled = "null";
            return;
        }
        
        // 生成选择器代码
        expr.compiled = "document.getElementById('" + escapeString(id) + "')";
        expr.metadata["elementId"] = id;
    }
    
    void compileCurrentElement(Expression& expr,
                              const std::map<std::string, std::string>& context) {
        expr.type = ExpressionType::CURRENT_ELEMENT;
        
        // 从上下文获取当前元素信息
        auto it = context.find("currentElement");
        if (it != context.end() && !it->second.empty()) {
            expr.compiled = it->second;
        } else {
            // 默认使用 this 或特定的元素引用
            expr.compiled = "(function() { "
                          "var el = document.currentScript ? "
                          "document.currentScript.parentElement : null; "
                          "return el; })()";
        }
    }
    
    void compileMethodCall(Expression& expr, const std::string& call,
                          const std::map<std::string, std::string>& context) {
        expr.type = ExpressionType::METHOD_CALL;
        
        // 解析方法调用
        size_t dotPos = call.find('.');
        if (dotPos == std::string::npos) {
            expr.compiled = call;
            return;
        }
        
        std::string target = call.substr(0, dotPos);
        std::string methodPart = call.substr(dotPos + 1);
        
        // 编译目标
        Expression targetExpr;
        targetExpr.raw = target;
        compileExpression(targetExpr, context);
        
        // 检查是否是 listen 方法
        if (methodPart.find("listen") == 0) {
            expr.type = ExpressionType::LISTEN_METHOD;
            expr.compiled = compileListenMethod(targetExpr.compiled, methodPart);
        } else {
            // 普通方法调用
            expr.compiled = targetExpr.compiled + "." + methodPart;
        }
    }
    
    std::string compileListenMethod(const std::string& target, 
                                   const std::string& methodCall) {
        // 解析 listen 方法参数
        std::regex listenRegex(R"(listen\s*\(\s*['"]([^'"]+)['"]\s*,\s*(.+)\s*\))");
        std::smatch match;
        
        if (std::regex_match(methodCall, match, listenRegex)) {
            std::string eventName = match[1];
            std::string handler = match[2];
            
            // 生成事件监听代码
            return "(" + target + " && " + target + 
                   ".addEventListener('" + eventName + "', " + handler + "))";
        }
        
        // 如果解析失败，返回原始调用
        return target + "." + methodCall;
    }
    
    void updateMetadata(const Expression& expr, ChtlJsResult& result) {
        switch (expr.type) {
            case ExpressionType::ELEMENT_SELECTOR:
                result.hasElementSelectors = true;
                if (std::find(result.dependencies.begin(), 
                            result.dependencies.end(), 
                            "chtl.select") == result.dependencies.end()) {
                    result.dependencies.push_back("chtl.select");
                }
                break;
            case ExpressionType::CURRENT_ELEMENT:
                result.hasCurrentElement = true;
                break;
            case ExpressionType::LISTEN_METHOD:
                result.hasListenMethod = true;
                if (std::find(result.dependencies.begin(),
                            result.dependencies.end(),
                            "chtl.listen") == result.dependencies.end()) {
                    result.dependencies.push_back("chtl.listen");
                }
                break;
            default:
                break;
        }
    }
    
    bool isValidSelector(const std::string& selector) {
        // 简单的选择器验证
        if (selector.empty() || selector[0] != '#') {
            return false;
        }
        
        // ID 必须以字母开头，可以包含字母、数字、下划线、连字符
        std::regex idRegex("^#[a-zA-Z][a-zA-Z0-9_-]*$");
        return std::regex_match(selector, idRegex);
    }
    
    bool isValidMethodCall(const std::string& call) {
        // 简单的方法调用验证
        return call.find('.') != std::string::npos;
    }
    
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
    }
    
    std::string escapeString(const std::string& str) {
        std::string result;
        for (char c : str) {
            switch (c) {
                case '\'': result += "\\'"; break;
                case '"': result += "\\\""; break;
                case '\\': result += "\\\\"; break;
                case '\n': result += "\\n"; break;
                case '\r': result += "\\r"; break;
                case '\t': result += "\\t"; break;
                default: result += c;
            }
        }
        return result;
    }
    
    bool strict_ = false;
};

// ChtlJsCompiler 实现
ChtlJsCompiler::ChtlJsCompiler() 
    : impl_(std::make_unique<Impl>()) {
}

ChtlJsCompiler::~ChtlJsCompiler() = default;

ChtlJsResult ChtlJsCompiler::compile(const std::string& code,
                                    const std::map<std::string, std::string>& context) {
    return impl_->compile(code, context);
}

void ChtlJsCompiler::setOption(const std::string& name, bool value) {
    impl_->setOption(name, value);
}

// ChtlJsRuntime 实现
std::string ChtlJsRuntime::generateRuntime() {
    return R"(
// CHTL-JS Runtime
(function(window) {
    'use strict';
    
    // CHTL 命名空间
    window.chtl = window.chtl || {};
    
    // 增强的选择器函数
    window.chtl.select = function(selector) {
        if (typeof selector === 'string') {
            if (selector[0] === '#') {
                return document.getElementById(selector.slice(1));
            }
            return document.querySelector(selector);
        }
        return selector;
    };
    
    // 事件监听扩展
    window.chtl.listen = function(element, event, handler) {
        if (element && element.addEventListener) {
            element.addEventListener(event, handler);
            return function() {
                element.removeEventListener(event, handler);
            };
        }
        return function() {};
    };
    
    // 为元素添加 listen 方法
    if (typeof Element !== 'undefined') {
        Element.prototype.listen = function(event, handler) {
            return window.chtl.listen(this, event, handler);
        };
    }
    
    // 批量事件绑定
    window.chtl.delegate = function(parent, selector, event, handler) {
        parent = window.chtl.select(parent);
        if (!parent) return function() {};
        
        var delegateHandler = function(e) {
            var target = e.target;
            while (target && target !== parent) {
                if (target.matches && target.matches(selector)) {
                    handler.call(target, e);
                    break;
                }
                target = target.parentElement;
            }
        };
        
        parent.addEventListener(event, delegateHandler);
        return function() {
            parent.removeEventListener(event, delegateHandler);
        };
    };
    
})(window);
)";
}

std::string ChtlJsRuntime::generateModuleRuntime() {
    return R"(
// CHTL-JS Module Runtime
export const chtl = {
    select(selector) {
        if (typeof selector === 'string') {
            if (selector[0] === '#') {
                return document.getElementById(selector.slice(1));
            }
            return document.querySelector(selector);
        }
        return selector;
    },
    
    listen(element, event, handler) {
        if (element && element.addEventListener) {
            element.addEventListener(event, handler);
            return () => element.removeEventListener(event, handler);
        }
        return () => {};
    },
    
    delegate(parent, selector, event, handler) {
        parent = this.select(parent);
        if (!parent) return () => {};
        
        const delegateHandler = (e) => {
            let target = e.target;
            while (target && target !== parent) {
                if (target.matches && target.matches(selector)) {
                    handler.call(target, e);
                    break;
                }
                target = target.parentElement;
            }
        };
        
        parent.addEventListener(event, delegateHandler);
        return () => parent.removeEventListener(event, delegateHandler);
    }
};
)";
}

} // namespace chtl::v2::chtljs