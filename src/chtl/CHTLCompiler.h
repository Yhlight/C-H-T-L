#ifndef CHTL_COMPILER_CHTL_COMPILER_H
#define CHTL_COMPILER_CHTL_COMPILER_H

#include "../compiler/Compiler.h"
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <stack>

namespace chtl {

// 编译器状态枚举
enum class CompilerState {
    INITIAL,        // 初始状态
    ELEMENT,        // 元素状态
    ATTRIBUTES,     // 属性状态
    CONTENT,        // 内容状态
    STYLE_BLOCK,    // 样式块状态
    TEXT_BLOCK,     // 文本块状态
    SCRIPT_BLOCK,   // 脚本块状态
    TEMPLATE,       // 模板状态
    CUSTOM          // 自定义状态
};

// 元素上下文结构
struct ElementContext {
    std::string elementName;                    // 元素名称
    size_t lineNumber;                          // 行号
    std::map<std::string, std::string> attributes; // 属性映射
    bool hasAttributes;                         // 是否有属性
    std::string generatedClass;                 // 生成的类名
    std::string generatedId;                    // 生成的ID
    
    ElementContext() : lineNumber(0), hasAttributes(false) {}
};

// 模板信息结构
struct TemplateInfo {
    std::string type;                           // 模板类型
    std::string name;                           // 模板名称
    std::string content;                        // 模板内容
    std::map<std::string, std::string> parameters; // 模板参数
    
    TemplateInfo() = default;
};

// 自定义信息结构
struct CustomInfo {
    std::string type;                           // 自定义类型
    std::string name;                           // 自定义名称
    std::string content;                        // 自定义内容
    std::map<std::string, std::string> parameters; // 自定义参数
    
    CustomInfo() = default;
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
    
    // 上下文管理
    std::stack<ElementContext> contextStack_;
    
    // HTML元素支持
    std::set<std::string> singleTagElements_;  // 单标签元素
    std::set<std::string> blockElements_;      // 块级元素
    std::set<std::string> inlineElements_;     // 行内元素
    
    // 模板和自定义管理
    std::map<std::string, TemplateInfo> templates_;
    std::map<std::string, CustomInfo> customs_;
    
    // 当前处理的代码块
    std::string currentCSSRule_;
    std::string currentStyleBlock_;
    std::string currentScriptBlock_;
    
    // 初始化方法
    void initializeHTMLElements();
    
    // 状态机方法
    void parseCHTL(const std::string& sourceCode);
    void parseLine(const std::string& line, size_t lineNumber);
    
    // 状态处理方法
    void handleInitialState(const std::string& line, size_t lineNumber);
    void handleElementState(const std::string& line, size_t lineNumber);
    void handleAttributesState(const std::string& line, size_t lineNumber);
    void handleContentState(const std::string& line, size_t lineNumber);
    void handleStyleBlockState(const std::string& line, size_t lineNumber);
    void handleTextBlockState(const std::string& line, size_t lineNumber);
    void handleScriptBlockState(const std::string& line, size_t lineNumber);
    void handleTemplateState(const std::string& line, size_t lineNumber);
    void handleCustomState(const std::string& line, size_t lineNumber);
    
    // 元素处理方法
    void startElement(const std::string& elementName, const std::string& line);
    void openElement();
    void closeElement();
    
    // 文本块处理
    void startTextBlock();
    void endTextBlock();
    void addTextContent(const std::string& line);
    
    // 样式块处理 - 支持局部样式和上下文推导
    void startStyleBlock();
    void endStyleBlock();
    void parseCSSRule(const std::string& line);
    void processStyleBlockWithContext();
    
    // 脚本块处理
    void startScriptBlock();
    void endScriptBlock();
    void addScriptContent(const std::string& line);
    
    // 属性处理
    void parseAttribute(const std::string& line);
    void updateHTMLElementAttributes(const ElementContext& context);
    
    // 上下文推导处理
    std::vector<std::string> parseSelectors(const std::string& cssRule);
    std::string processSelectorWithContext(const std::string& selector);
    std::string getCurrentElementSelector();
    std::string extractCSSProperties(const std::string& cssRule);
    
    // 模板处理
    void parseTemplate(const std::string& line);
    void parseTemplateContent(const std::string& line);
    void parseTemplateUsage(const std::string& line);
    void endTemplate();
    
    // 自定义处理
    void parseCustom(const std::string& line);
    void parseCustomContent(const std::string& line);
    void endCustom();
    
    // 验证方法
    bool validateCHTLLine(const std::string& line);
    
    // 辅助方法
    std::string trim(const std::string& str);
    bool isComment(const std::string& line);
    
    // 其他指令处理
    void parseImport(const std::string& line);
    void parseNamespace(const std::string& line);
    void parseConfiguration(const std::string& line);
    void parseOrigin(const std::string& line);
    
    // 元素识别和验证
    std::string extractElementName(const std::string& line);
    std::vector<std::string> getAllHTMLElements();
    bool isSingleTagElement(const std::string& elementName);
    
    // 工具方法
    void processUnclosedElements();
    
    // 后处理方法
    void processTemplates();
    void processCustomElements();
    void processStyleGroups();
    void processVariableGroups();
    void processNamespaces();
    void processImports();
    void processConstraints();
    
    // 输出生成
    void generateHTML();
    void generateCSS();
    void generateJavaScript();
    
    // 重置方法
    void reset();
};

} // namespace chtl

#endif // CHTL_COMPILER_CHTL_COMPILER_H