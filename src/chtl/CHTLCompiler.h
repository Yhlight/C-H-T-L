#ifndef CHTL_COMPILER_CHTL_COMPILER_H
#define CHTL_COMPILER_CHTL_COMPILER_H

#include "../compiler/Compiler.h"
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <functional>

namespace chtl {

// 编译器状态枚举 - 更细粒度的状态控制
enum class CompilerState {
    INITIAL,            // 初始状态
    ROOT,              // 根状态
    ELEMENT_DECL,      // 元素声明状态
    ELEMENT_OPEN,      // 元素打开状态
    ELEMENT_CONTENT,   // 元素内容状态
    ELEMENT_CLOSE,     // 元素关闭状态
    ATTRIBUTE_LIST,    // 属性列表状态
    ATTRIBUTE_PAIR,    // 属性键值对状态
    STYLE_BLOCK,       // 样式块状态
    STYLE_RULE,        // 样式规则状态
    STYLE_PROPERTY,    // 样式属性状态
    TEXT_BLOCK,        // 文本块状态
    SCRIPT_BLOCK,      // 脚本块状态
    TEMPLATE_DECL,     // 模板声明状态
    TEMPLATE_CONTENT,  // 模板内容状态
    CUSTOM_DECL,       // 自定义声明状态
    CUSTOM_CONTENT,    // 自定义内容状态
    IMPORT_DECL,       // 导入声明状态
    NAMESPACE_DECL,    // 命名空间声明状态
    CONFIG_DECL,       // 配置声明状态
    ORIGIN_BLOCK,      // 原始代码块状态
    COMMENT_BLOCK      // 注释块状态
};

// 上下文类型枚举
enum class ContextType {
    ROOT,           // 根上下文
    ELEMENT,        // 元素上下文
    STYLE,          // 样式上下文
    SCRIPT,         // 脚本上下文
    TEMPLATE,       // 模板上下文
    CUSTOM,         // 自定义上下文
    IMPORT,         // 导入上下文
    NAMESPACE,      // 命名空间上下文
    CONFIG,         // 配置上下文
    ORIGIN          // 原始代码上下文
};

// 上下文结构 - 支持嵌套和继承
struct CompilerContext {
    ContextType type;                                    // 上下文类型
    std::string name;                                    // 上下文名称
    size_t lineNumber;                                   // 行号
    size_t depth;                                        // 嵌套深度
    std::map<std::string, std::string> attributes;      // 属性映射
    std::map<std::string, std::string> metadata;        // 元数据
    std::vector<std::string> content;                    // 内容列表
    std::vector<std::string> generatedClasses;          // 生成的类名
    std::vector<std::string> generatedIds;              // 生成的ID
    std::string parentSelector;                          // 父选择器
    std::string currentSelector;                         // 当前选择器
    bool isActive;                                       // 是否激活
    bool hasChildren;                                    // 是否有子元素
    
    CompilerContext() : type(ContextType::ROOT), lineNumber(0), depth(0), isActive(true), hasChildren(false) {}
    
    // 获取完整选择器路径
    std::string getFullSelector() const {
        if (parentSelector.empty()) {
            return currentSelector;
        }
        return parentSelector + " " + currentSelector;
    }
    
    // 生成唯一标识符
    std::string generateUniqueId() const {
        static size_t counter = 0;
        return "chtl-" + std::to_string(depth) + "-" + std::to_string(++counter);
    }
};

// 状态转换规则
struct StateTransition {
    CompilerState from;                                  // 从状态
    std::string trigger;                                 // 触发条件
    CompilerState to;                                    // 到状态
    std::function<void(const std::string&)> action;      // 转换动作
    bool requiresContext;                                // 是否需要上下文
    
    StateTransition(CompilerState f, const std::string& t, CompilerState to_state, 
                   std::function<void(const std::string&)> a = nullptr, bool req = false)
        : from(f), trigger(t), to(to_state), action(a), requiresContext(req) {}
};

// 上下文推导规则
struct ContextRule {
    std::string pattern;                                 // 匹配模式
    std::function<std::string(const CompilerContext&, const std::string&)> transform; // 转换函数
    int priority;                                        // 优先级
    
    ContextRule(const std::string& p, 
                std::function<std::string(const CompilerContext&, const std::string&)> t, 
                int prio = 0)
        : pattern(p), transform(t), priority(prio) {}
};

// CHTL编译器类
class CHTLCompiler : public Compiler {
public:
    CHTLCompiler();
    ~CHTLCompiler() = default;

    // 编译CHTL代码
    bool compile(const std::string& sourceCode);
    
    // 验证CHTL代码
    bool validate(const std::string& sourceCode);
    
    // 获取编译后的HTML
    std::string getHTML() const { return htmlOutput_; }
    
    // 获取编译后的CSS
    std::string getCSS() const { return cssOutput_; }
    
    // 获取编译后的JavaScript
    std::string getJavaScript() const { return jsOutput_; }

private:
    // 输出内容
    std::string htmlOutput_;
    std::string cssOutput_;
    std::string jsOutput_;
    
    // 状态机
    CompilerState currentState_;
    size_t currentLineNumber_;
    
    // 上下文管理 - 使用栈结构支持嵌套
    std::stack<std::shared_ptr<CompilerContext>> contextStack_;
    std::map<std::string, std::shared_ptr<CompilerContext>> contextRegistry_;
    
    // 状态转换表
    std::vector<StateTransition> stateTransitions_;
    
    // 上下文推导规则
    std::vector<ContextRule> contextRules_;
    
    // HTML元素支持
    std::set<std::string> singleTagElements_;  // 单标签元素
    std::set<std::string> blockElements_;      // 块级元素
    std::set<std::string> inlineElements_;     // 行内元素
    
    // 模板和自定义管理
    std::map<std::string, std::shared_ptr<CompilerContext>> templates_;
    std::map<std::string, std::shared_ptr<CompilerContext>> customs_;
    
    // 当前处理的代码块
    std::string currentStyleBlock_;
    std::string currentScriptBlock_;
    
    // 初始化方法
    void initializeHTMLElements();
    void initializeStateTransitions();
    void initializeContextRules();
    
    // 状态机核心方法
    void parseCHTL(const std::string& sourceCode);
    void parseLine(const std::string& line, size_t lineNumber);
    bool transitionState(const std::string& trigger);
    void executeStateAction(const std::string& trigger);
    
    // 状态处理方法 - 基于当前状态和上下文
    void handleState(const std::string& line, size_t lineNumber);
    
    // 上下文管理方法
    std::shared_ptr<CompilerContext> createContext(ContextType type, const std::string& name = "");
    void pushContext(std::shared_ptr<CompilerContext> context);
    std::shared_ptr<CompilerContext> popContext();
    std::shared_ptr<CompilerContext> getCurrentContext();
    void updateContext(const std::string& line);
    
    // 上下文推导方法
    std::string deriveContext(const std::string& input);
    std::string applyContextRules(const std::string& input);
    std::string generateSelector(const std::shared_ptr<CompilerContext>& context);
    
    // 元素处理方法
    void processElement(const std::string& line);
    void processAttribute(const std::string& line);
    void processStyleBlock(const std::string& line);
    void processTextBlock(const std::string& line);
    void processScriptBlock(const std::string& line);
    
    // HTML标签管理方法
    void updateHTMLElement(const std::shared_ptr<CompilerContext>& context);
    void closeElement();
    
    // 模板和自定义处理
    void processTemplate(const std::string& line);
    void processCustom(const std::string& line);
    void processImport(const std::string& line);
    void processNamespace(const std::string& line);
    void processConfiguration(const std::string& line);
    void processOrigin(const std::string& line);
    
    // 输出生成方法
    void generateHTML();
    void generateCSS();
    void generateJavaScript();
    
    // 验证方法
    bool validateCHTLLine(const std::string& line);
    
    // 辅助方法
    std::string trim(const std::string& str);
    bool isComment(const std::string& line);
    std::string extractElementName(const std::string& line);
    bool isSingleTagElement(const std::string& elementName);
    std::vector<std::string> getAllHTMLElements();
    
    // 后处理方法
    void processTemplates();
    void processCustomElements();
    void processStyleGroups();
    void processVariableGroups();
    void processNamespaces();
    void processImports();
    void processConstraints();
    
    // 重置方法
    void reset();
};

} // namespace chtl

#endif // CHTL_COMPILER_CHTL_COMPILER_H