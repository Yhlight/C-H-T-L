#ifndef CHTL_GENERATOR_H
#define CHTL_GENERATOR_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "Node/Node.h"
#include "Runtime/ChtlJsRuntime.h"

namespace chtl {

// 生成选项
struct GeneratorOptions {
    bool minify = false;                    // 是否压缩代码
    bool sourceMap = false;                 // 是否生成source map
    bool inlineStyles = false;              // 是否内联样式
    bool inlineScripts = false;             // 是否内联脚本
    std::string targetPlatform = "web";     // 目标平台: web, react, vue
    std::string outputPath = "";            // 输出路径
    bool modernJS = true;                   // 是否使用现代JS语法
    bool scopeStyles = true;                // 是否对样式添加作用域
};

// 生成结果
struct GeneratorResult {
    std::string html;                       // 生成的HTML
    std::string css;                        // 生成的CSS
    std::string js;                         // 生成的JavaScript
    std::string sourceMap;                  // Source Map
    std::vector<std::string> warnings;      // 警告信息
    std::vector<std::string> errors;        // 错误信息
    
    // 依赖信息
    std::vector<std::string> externalStyles;    // 外部样式文件
    std::vector<std::string> externalScripts;   // 外部脚本文件
    std::vector<std::string> assets;            // 资源文件
};

// 代码生成器基类
class Generator {
public:
    Generator(const GeneratorOptions& options = GeneratorOptions());
    virtual ~Generator() = default;
    
    // 生成代码
    virtual GeneratorResult generate(const std::shared_ptr<Node>& ast);
    
    // 设置选项
    void setOptions(const GeneratorOptions& options) { options_ = options; }
    const GeneratorOptions& getOptions() const { return options_; }
    
protected:
    // 访问者方法
    virtual void visit(const std::shared_ptr<Node>& node);
    virtual void visitElement(const std::shared_ptr<Element>& element);
    virtual void visitText(const std::shared_ptr<Text>& text);
    virtual void visitCustom(const std::shared_ptr<Custom>& custom);
    virtual void visitTemplate(const std::shared_ptr<Template>& tmpl);
    virtual void visitStyle(const std::shared_ptr<Style>& style);
    virtual void visitScript(const std::shared_ptr<Script>& script);
    virtual void visitImport(const std::shared_ptr<Import>& import);
    virtual void visitExport(const std::shared_ptr<Export>& exp);
    virtual void visitConfig(const std::shared_ptr<Config>& config);
    virtual void visitNamespace(const std::shared_ptr<Namespace>& ns);
    
    // 工具方法
    std::string indent(int level) const;
    std::string escape(const std::string& str) const;
    std::string generateUniqueId(const std::string& prefix = "chtl") const;
    std::string scopeSelector(const std::string& selector, const std::string& scope) const;
    
    // 代码收集器
    class CodeCollector {
    public:
        void append(const std::string& code);
        void appendLine(const std::string& code = "");
        void increaseIndent() { indentLevel_++; }
        void decreaseIndent() { if (indentLevel_ > 0) indentLevel_--; }
        std::string getCode() const { return stream_.str(); }
        void clear() { stream_.str(""); stream_.clear(); }
        
    private:
        std::stringstream stream_;
        int indentLevel_ = 0;
    };
    
    // 成员变量
    GeneratorOptions options_;
    GeneratorResult result_;
    CodeCollector htmlCollector_;
    CodeCollector cssCollector_;
    CodeCollector jsCollector_;
    
    // 上下文信息
    std::string currentScope_;                     // 当前作用域
    std::vector<std::string> scopeStack_;          // 作用域栈
    std::unordered_map<std::string, std::string> componentMap_;  // 组件映射
    std::unordered_map<std::string, std::string> styleMap_;      // 样式映射
    
    // 运行时集成
    std::unique_ptr<ChtlJsRuntime> jsRuntime_;
    
private:
    mutable int uniqueIdCounter_ = 0;
};

// Web平台生成器
class WebGenerator : public Generator {
public:
    using Generator::Generator;
    
    GeneratorResult generate(const std::shared_ptr<Node>& ast) override;
    
protected:
    void visitElement(const std::shared_ptr<Element>& element) override;
    void visitCustom(const std::shared_ptr<Custom>& custom) override;
    void visitStyle(const std::shared_ptr<Style>& style) override;
    void visitScript(const std::shared_ptr<Script>& script) override;
    
private:
    void generateHTMLDocument();
    void injectRuntimeCode();
    void processCustomComponent(const std::shared_ptr<Custom>& custom);
    void expandComponent(const std::string& componentName, 
                        const std::unordered_map<std::string, std::string>& props,
                        const std::vector<std::shared_ptr<Node>>& children);
};

// React平台生成器
class ReactGenerator : public Generator {
public:
    using Generator::Generator;
    
    GeneratorResult generate(const std::shared_ptr<Node>& ast) override;
    
protected:
    void visitElement(const std::shared_ptr<Element>& element) override;
    void visitCustom(const std::shared_ptr<Custom>& custom) override;
    
private:
    void generateReactComponent(const std::string& name);
    std::string convertToJSX(const std::shared_ptr<Node>& node);
    std::string camelCase(const std::string& str) const;
};

// Vue平台生成器
class VueGenerator : public Generator {
public:
    using Generator::Generator;
    
    GeneratorResult generate(const std::shared_ptr<Node>& ast) override;
    
protected:
    void visitElement(const std::shared_ptr<Element>& element) override;
    void visitCustom(const std::shared_ptr<Custom>& custom) override;
    
private:
    void generateVueComponent(const std::string& name);
    std::string convertToTemplate(const std::shared_ptr<Node>& node);
};

// 工厂函数
std::unique_ptr<Generator> createGenerator(const std::string& platform, 
                                          const GeneratorOptions& options = GeneratorOptions());

} // namespace chtl

#endif // CHTL_GENERATOR_H