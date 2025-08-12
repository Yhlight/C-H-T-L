#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace chtl::v2::chtljs {

/**
 * CHTL-JS 表达式类型
 */
enum class ExpressionType {
    ELEMENT_SELECTOR,    // {{#id}}
    CURRENT_ELEMENT,     // {{&}}
    VARIABLE,           // {{varName}}
    FUNCTION_CALL,      // {{func()}}
    MEMBER_ACCESS,      // {{obj.prop}}
    TEMPLATE_LITERAL    // {{`text ${var}`}}
};

/**
 * CHTL-JS 表达式
 */
struct Expression {
    ExpressionType type;
    std::string raw;        // 原始表达式
    std::string compiled;   // 编译后的 JavaScript
    int startPos;          // 在源代码中的位置
    int endPos;
};

/**
 * CHTL-JS 编译结果
 */
struct ChtlJsResult {
    bool success = true;
    std::string javascript;    // 编译后的 JavaScript
    std::vector<Expression> expressions;  // 识别的表达式
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // 元数据
    bool hasElementSelectors = false;   // 是否包含元素选择器
    bool hasCurrentElement = false;     // 是否包含当前元素引用
    std::vector<std::string> dependencies;  // 依赖的运行时函数
};

/**
 * CHTL-JS 编译器
 * 只处理 CHTL-JS 扩展语法，不处理标准 JavaScript
 */
class ChtlJsCompiler {
public:
    ChtlJsCompiler();
    ~ChtlJsCompiler();
    
    /**
     * 编译 CHTL-JS 代码
     * @param code 包含 {{}} 语法的代码
     * @param context 编译上下文（如当前元素信息）
     * @return 编译结果
     */
    ChtlJsResult compile(const std::string& code, 
                        const std::map<std::string, std::string>& context = {});
    
    /**
     * 检查代码是否包含 CHTL-JS 语法
     */
    static bool hasChtlJsSyntax(const std::string& code);
    
    /**
     * 设置选项
     */
    void setOption(const std::string& name, bool value);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

/**
 * CHTL-JS 运行时生成器
 * 生成必要的运行时支持函数
 */
class ChtlJsRuntime {
public:
    /**
     * 生成元素选择器函数
     */
    static std::string generateSelectorFunction();
    
    /**
     * 生成当前元素获取函数
     */
    static std::string generateCurrentElementFunction();
    
    /**
     * 生成事件监听扩展
     */
    static std::string generateEventExtensions();
    
    /**
     * 生成完整的运行时库
     */
    static std::string generateFullRuntime();
};

} // namespace chtl::v2::chtljs