#ifndef CHTL_UNIFIED_SCANNER_H
#define CHTL_UNIFIED_SCANNER_H

#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <functional>
#include <unordered_map> // Added for handlers_

namespace chtl {
namespace scanner {

// 代码片段类型
enum class FragmentType {
    CHTL,       // CHTL标记和结构
    CHTL_JS,    // CHTL增强的JavaScript
    CSS,        // 原生CSS
    JS,         // 原生JavaScript
    TEXT,       // 文本内容
    COMMENT     // 注释
};

// 代码片段
struct CodeFragment {
    FragmentType type;
    std::string content;
    size_t startLine;
    size_t startColumn;
    size_t endLine;
    size_t endColumn;
    
    CodeFragment(FragmentType t, const std::string& c, 
                 size_t sl, size_t sc, size_t el, size_t ec)
        : type(t), content(c), startLine(sl), startColumn(sc),
          endLine(el), endColumn(ec) {}
};

// 扫描器上下文
enum class ScannerContext {
    TOP_LEVEL,      // 顶层CHTL
    HTML_ELEMENT,   // HTML元素内部
    STYLE_BLOCK,    // style块内部
    SCRIPT_BLOCK,   // script块内部
    TEMPLATE,       // 模板定义内部
    CUSTOM,         // 自定义定义内部
    ORIGIN,         // 原始嵌入内部
    STRING,         // 字符串字面量内部
    COMMENT         // 注释内部
};

// 统一扫描器 - 负责识别和切分不同类型的代码片段
class CHTLUnifiedScanner {
public:
    CHTLUnifiedScanner();
    ~CHTLUnifiedScanner();
    
    // 扫描输入并返回代码片段列表
    std::vector<CodeFragment> scan(const std::string& input);
    
    // 设置回调函数以处理不同类型的片段
    void setFragmentHandler(FragmentType type, 
                           std::function<void(const CodeFragment&)> handler);
    
    // 获取错误信息
    bool hasErrors() const { return !errors_.empty(); }
    const std::vector<std::string>& getErrors() const { return errors_; }
    
private:
    // 当前位置
    size_t pos_;
    size_t line_;
    size_t column_;
    std::string input_;
    
    // 上下文栈
    std::stack<ScannerContext> contextStack_;
    
    // 片段处理器
    std::unordered_map<FragmentType, std::function<void(const CodeFragment&)>> handlers_;
    
    // 错误列表
    std::vector<std::string> errors_;
    
    // 扫描方法
    void scanTopLevel(std::vector<CodeFragment>& fragments);
    void scanHTMLElement(std::vector<CodeFragment>& fragments);
    void scanStyleBlock(std::vector<CodeFragment>& fragments);
    void scanScriptBlock(std::vector<CodeFragment>& fragments);
    void scanCHTLJavaScript(std::vector<CodeFragment>& fragments);
    void scanTemplate(std::vector<CodeFragment>& fragments);
    void scanCustom(std::vector<CodeFragment>& fragments);
    void scanOrigin(std::vector<CodeFragment>& fragments, const std::string& originType);
    
    // 辅助方法
    char peek() const;
    char peekNext() const;
    char peekAhead(size_t n) const;
    char advance();
    void skipWhitespace();
    bool match(const std::string& text);
    bool matchKeyword(const std::string& keyword);
    std::string readUntil(const std::string& delimiter);
    std::string readUntilAny(const std::vector<std::string>& delimiters);
    std::string readIdentifier();
    std::string readString();
    std::string readComment();
    
    // 上下文管理
    void pushContext(ScannerContext ctx);
    void popContext();
    ScannerContext currentContext() const;
    
    // 片段创建
    void addFragment(std::vector<CodeFragment>& fragments, 
                    FragmentType type, 
                    const std::string& content,
                    size_t startLine, size_t startColumn,
                    size_t endLine, size_t endColumn);
    
    // 错误处理
    void reportError(const std::string& message);
    
    // CHTL特定检测
    bool isCHTLKeyword(const std::string& word) const;
    bool isCHTLDirective(const std::string& word) const;
    bool isAtStartOfCHTLStructure() const;
    bool isInCHTLJSContext() const;
};

// 扫描器集成器 - 协调不同解析器的工作
class ScannerIntegrator {
public:
    ScannerIntegrator();
    ~ScannerIntegrator();
    
    // 处理完整的CHTL文件
    void processFile(const std::string& filename, const std::string& content);
    
    // 获取处理结果
    std::string getGeneratedHTML() const { return generatedHTML_; }
    std::string getGeneratedCSS() const { return generatedCSS_; }
    std::string getGeneratedJS() const { return generatedJS_; }
    
    // 错误处理
    bool hasErrors() const;
    std::vector<std::string> getAllErrors() const;
    
private:
    std::unique_ptr<CHTLUnifiedScanner> scanner_;
    std::string generatedHTML_;
    std::string generatedCSS_;
    std::string generatedJS_;
    std::vector<std::string> errors_;
    
    // 片段处理器
    void handleCHTLFragment(const CodeFragment& fragment);
    void handleCHTLJSFragment(const CodeFragment& fragment);
    void handleCSSFragment(const CodeFragment& fragment);
    void handleJSFragment(const CodeFragment& fragment);
    void handleTextFragment(const CodeFragment& fragment);
    void handleCommentFragment(const CodeFragment& fragment);
};

} // namespace scanner
} // namespace chtl

#endif // CHTL_UNIFIED_SCANNER_H