#include "v2/ChtlJs/ChtlJsCompiler.h"
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
        
        // 查找所有 {{}} 表达式
        std::vector<Expression> expressions;
        findExpressions(code, expressions);
        
        if (expressions.empty()) {
            // 没有 CHTL-JS 语法，直接返回
            result.javascript = code;
            return result;
        }
        
        // 编译每个表达式
        std::string compiled = code;
        int offset = 0;
        
        for (auto& expr : expressions) {
            compileExpression(expr, context);
            
            // 替换原始表达式
            int adjustedStart = expr.startPos + offset;
            int adjustedEnd = expr.endPos + offset;
            int originalLength = adjustedEnd - adjustedStart;
            
            compiled.replace(adjustedStart, originalLength, expr.compiled);
            
            // 调整偏移量
            offset += expr.compiled.length() - originalLength;
            
            // 更新元数据
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
                default:
                    break;
            }
            
            result.expressions.push_back(expr);
        }
        
        result.javascript = compiled;
        result.success = result.errors.empty();
        
        return result;
    }
    
    void setOption(const std::string& name, bool value) {
        if (name == "strict") {
            strict_ = value;
        }
    }
    
private:
    void findExpressions(const std::string& code, std::vector<Expression>& expressions) {
        size_t pos = 0;
        
        while (pos < code.length()) {
            // 查找 {{
            size_t start = code.find("{{", pos);
            if (start == std::string::npos) break;
            
            // 查找对应的 }}
            size_t end = code.find("}}", start + 2);
            if (end == std::string::npos) {
                // 未闭合的表达式
                break;
            }
            
            // 提取表达式内容
            std::string content = code.substr(start + 2, end - start - 2);
            content = trim(content);
            
            if (!content.empty()) {
                Expression expr;
                expr.raw = content;
                expr.startPos = start;
                expr.endPos = end + 2;
                expr.type = determineExpressionType(content);
                
                expressions.push_back(expr);
            }
            
            pos = end + 2;
        }
    }
    
    ExpressionType determineExpressionType(const std::string& expr) {
        if (expr == "&") {
            return ExpressionType::CURRENT_ELEMENT;
        }
        
        if (expr.size() > 1 && expr[0] == '#') {
            return ExpressionType::ELEMENT_SELECTOR;
        }
        
        if (expr.find('(') != std::string::npos) {
            return ExpressionType::FUNCTION_CALL;
        }
        
        if (expr.find('.') != std::string::npos) {
            return ExpressionType::MEMBER_ACCESS;
        }
        
        if (expr[0] == '`') {
            return ExpressionType::TEMPLATE_LITERAL;
        }
        
        return ExpressionType::VARIABLE;
    }
    
    void compileExpression(Expression& expr, const std::map<std::string, std::string>& context) {
        switch (expr.type) {
            case ExpressionType::ELEMENT_SELECTOR:
                compileElementSelector(expr);
                break;
                
            case ExpressionType::CURRENT_ELEMENT:
                compileCurrentElement(expr, context);
                break;
                
            case ExpressionType::VARIABLE:
            case ExpressionType::FUNCTION_CALL:
            case ExpressionType::MEMBER_ACCESS:
            case ExpressionType::TEMPLATE_LITERAL:
                // 标准 JavaScript 表达式，直接使用
                expr.compiled = expr.raw;
                break;
        }
    }
    
    void compileElementSelector(Expression& expr) {
        // {{#id}} -> chtl.select('#id')
        std::string selector = expr.raw;
        expr.compiled = "chtl.select('" + selector + "')";
    }
    
    void compileCurrentElement(Expression& expr, const std::map<std::string, std::string>& context) {
        // {{&}} -> 根据上下文决定
        
        // 检查是否在特定元素的上下文中
        auto it = context.find("elementId");
        if (it != context.end() && !it->second.empty()) {
            expr.compiled = "document.getElementById('" + it->second + "')";
        } else {
            // 默认使用 this 或者一个占位符
            expr.compiled = "this";
        }
    }
    
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
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

bool ChtlJsCompiler::hasChtlJsSyntax(const std::string& code) {
    return code.find("{{") != std::string::npos;
}

void ChtlJsCompiler::setOption(const std::string& name, bool value) {
    impl_->setOption(name, value);
}

// ChtlJsRuntime 实现

std::string ChtlJsRuntime::generateSelectorFunction() {
    return R"(
// CHTL 元素选择器
window.chtl = window.chtl || {};
window.chtl.select = function(selector) {
    if (selector.startsWith('#')) {
        return document.getElementById(selector.substring(1));
    } else if (selector.startsWith('.')) {
        return document.getElementsByClassName(selector.substring(1))[0];
    } else {
        return document.querySelector(selector);
    }
};
)";
}

std::string ChtlJsRuntime::generateCurrentElementFunction() {
    return R"(
// CHTL 当前元素获取
window.chtl.getCurrentElement = function() {
    // 从事件或上下文中获取当前元素
    if (window.event && window.event.currentTarget) {
        return window.event.currentTarget;
    }
    return null;
};
)";
}

std::string ChtlJsRuntime::generateEventExtensions() {
    return R"(
// CHTL 事件扩展
Element.prototype.listen = function(event, handler) {
    this.addEventListener(event, handler);
    return this;
};
)";
}

std::string ChtlJsRuntime::generateFullRuntime() {
    std::stringstream runtime;
    runtime << "// CHTL Runtime Library\n";
    runtime << "(function() {\n";
    runtime << generateSelectorFunction();
    runtime << generateCurrentElementFunction();
    runtime << generateEventExtensions();
    runtime << "})();\n";
    return runtime.str();
}

} // namespace chtl::v2::chtljs