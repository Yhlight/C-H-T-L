#include "CHTLJSCompiler.h"
#include "CHTLJavaScriptLexer.h"
#include "CHTLJavaScriptParser.h"
#include "CHTLJavaScriptBaseVisitor.h"
#include <sstream>
#include <regex>

namespace CHTL {

// 错误监听器实现
class CHTLJSCompiler::ErrorListener : public antlr4::BaseErrorListener {
public:
    ErrorListener(std::vector<std::string>& errors) : errors_(errors) {}
    
    void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol,
                    size_t line, size_t charPositionInLine,
                    const std::string& msg, std::exception_ptr e) override {
        std::stringstream ss;
        ss << "CHTL JavaScript语法错误 [" << line << ":" << charPositionInLine << "] " << msg;
        errors_.push_back(ss.str());
    }
    
private:
    std::vector<std::string>& errors_;
};

// CHTL JavaScript访问者实现
class CHTLJSCompiler::CHTLJSVisitorImpl : public CHTLJavaScriptBaseVisitor {
public:
    CHTLJSVisitorImpl() {}
    
    // TODO: 实现各个visit方法
    
private:
    std::shared_ptr<ASTNode> currentNode_;
};

CHTLJSCompiler::CHTLJSCompiler() {
    visitor_ = std::make_unique<CHTLJSVisitorImpl>();
    errorListener_ = std::make_unique<ErrorListener>(errors_);
}

CHTLJSCompiler::~CHTLJSCompiler() = default;

std::shared_ptr<ASTNode> CHTLJSCompiler::compile(const std::string& code) {
    // 先转换CHTL JS语法到标准JS
    std::string transformedCode = transform(code);
    
    // 创建一个脚本节点并标记为CHTL JS
    auto scriptNode = std::make_shared<ScriptBlockNode>(transformedCode, true);
    
    return scriptNode;
}

std::string CHTLJSCompiler::transform(const std::string& chtlJsCode) {
    std::string result = chtlJsCode;
    
    // 转换CHTL选择器 {{selector}}
    std::regex selectorRegex(R"(\{\{([^}]+)\}\})");
    result = std::regex_replace(result, selectorRegex, 
        [this](const std::smatch& match) {
            return generateSelectorFunction(match[1].str());
        });
    
    // 转换箭头操作符 ->
    std::regex arrowRegex(R"(\s*->\s*)");
    result = std::regex_replace(result, arrowRegex, ".");
    
    // 转换listen方法
    result = transformListen(result);
    
    // 转换delegate方法
    result = transformDelegate(result);
    
    // 转换animate函数
    result = transformAnimate(result);
    
    return result;
}

void CHTLJSCompiler::setContext(const std::unordered_map<std::string, std::string>& contextInfo) {
    contextInfo_ = contextInfo;
}

std::string CHTLJSCompiler::transformSelector(const std::string& selector) {
    std::string trimmed = selector;
    // 移除前后空格
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);
    
    // 处理不同类型的选择器
    if (trimmed[0] == '.') {
        // 类选择器
        return "document.querySelector('" + trimmed + "')";
    } else if (trimmed[0] == '#') {
        // ID选择器
        return "document.getElementById('" + trimmed.substr(1) + "')";
    } else if (trimmed.find('[') != std::string::npos) {
        // 索引选择器，如 button[0]
        size_t bracketPos = trimmed.find('[');
        std::string tagName = trimmed.substr(0, bracketPos);
        std::string index = trimmed.substr(bracketPos + 1, trimmed.find(']') - bracketPos - 1);
        return "document.getElementsByTagName('" + tagName + "')[" + index + "]";
    } else if (trimmed.find(' ') != std::string::npos) {
        // 复杂选择器
        return "document.querySelector('" + trimmed + "')";
    } else {
        // 简单标签选择器或类名/ID（需要根据上下文判断）
        // 先检查是否是上下文中定义的类或ID
        auto classIt = contextInfo_.find("class");
        auto idIt = contextInfo_.find("id");
        
        if (idIt != contextInfo_.end() && idIt->second.find(trimmed) != std::string::npos) {
            return "document.getElementById('" + trimmed + "')";
        } else if (classIt != contextInfo_.end() && classIt->second.find(trimmed) != std::string::npos) {
            return "document.querySelector('." + trimmed + "')";
        } else {
            // 默认作为标签选择器
            return "document.querySelector('" + trimmed + "')";
        }
    }
}

std::string CHTLJSCompiler::transformListen(const std::string& code) {
    // 转换 element.listen({ event: handler }) 到标准的 addEventListener
    std::regex listenRegex(R"(\.listen\s*\(\s*\{([^}]+)\}\s*\))");
    
    return std::regex_replace(code, listenRegex, 
        [](const std::smatch& match) {
            std::string listeners = match[1].str();
            std::stringstream result;
            
            // 解析事件和处理器
            std::regex eventRegex(R"((\w+)\s*:\s*([^,]+)(?:,|$))");
            std::sregex_iterator it(listeners.begin(), listeners.end(), eventRegex);
            std::sregex_iterator end;
            
            bool first = true;
            for (; it != end; ++it) {
                if (!first) result << "; ";
                first = false;
                
                std::string event = (*it)[1].str();
                std::string handler = (*it)[2].str();
                
                result << ".addEventListener('" << event << "', " << handler << ")";
            }
            
            return result.str();
        });
}

std::string CHTLJSCompiler::transformDelegate(const std::string& code) {
    // 转换事件委托语法
    // TODO: 实现事件委托的转换
    return code;
}

std::string CHTLJSCompiler::transformAnimate(const std::string& code) {
    // 转换动画语法到Web Animations API
    // TODO: 实现动画语法的转换
    return code;
}

std::string CHTLJSCompiler::generateSelectorFunction(const std::string& selector) {
    return transformSelector(selector);
}

} // namespace CHTL