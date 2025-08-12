#ifndef CHTL_GENERATOR_H
#define CHTL_GENERATOR_H

#include "Node/Node.h"
#include "Node/Element.h"
#include "Node/Text.h"
#include "Node/Comment.h"
#include "Node/Custom.h"
#include "Node/Template.h"
#include "Node/Style.h"
#include "Node/Script.h"
#include "Node/Import.h"
#include "Node/Export.h"
#include "Node/Config.h"
#include "Node/Namespace.h"
#include "Node/Operate.h"
#include "Node/Origin.h"
// #include "Node/Reference.h" // Not implemented yet
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "Runtime/ChtlJsRuntime.h"
#include "Generator/ConfigManager.h"
#include "Context/ChtlContext.h"

namespace chtl {

// 前向声明
class ChtlJsRuntime;

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
    bool success = false;                    // 是否成功
    std::string html;                       // 生成的HTML
    std::string css;                        // 生成的CSS
    std::string js;                         // 生成的JavaScript
    std::string sourceMap;                  // Source Map
    std::vector<std::string> warnings;      // 警告信息
    std::vector<std::string> errors;        // 错误信息
    
    // 辅助信息
    std::unordered_map<std::string, std::string> assets;  // 生成的资源文件
    std::unordered_map<std::string, std::string> metadata; // 元数据
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
    
    // 设置上下文
    void setContext(std::shared_ptr<ChtlContext> context) { currentContext_ = context; }
    
protected:
    // 错误处理辅助方法
    void addError(const std::string& message) { result_.errors.push_back(message); }
    void addWarning(const std::string& message) { result_.warnings.push_back(message); }
    
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
    std::shared_ptr<Node> ast_;  // 添加AST成员变量
    CodeCollector htmlCollector_;
    CodeCollector cssCollector_;
    CodeCollector jsCollector_;
    
    // 配置管理器
    std::unique_ptr<ConfigManager> configManager_;
    
    // 上下文信息
    std::string currentScope_;                     // 当前作用域
    std::vector<std::string> scopeStack_;          // 作用域栈
    std::unordered_map<std::string, std::string> componentMap_;  // 组件映射
    std::unordered_map<std::string, std::string> styleMap_;      // 样式映射
    
    // 运行时集成
    ChtlJsRuntime* jsRuntime_;
    
    // 当前编译上下文
    std::shared_ptr<ChtlContext> currentContext_;
    
    // 继承处理方法
    void scanConfiguration(const std::shared_ptr<Node>& node);
    void collectDefinitions(const std::shared_ptr<Node>& node);
    void resolveInheritance(std::shared_ptr<Node> node);
    void mergeStyleInheritance(std::shared_ptr<Node> target, const std::string& sourceName);
    void mergeElementInheritance(std::shared_ptr<Node> target, const std::string& sourceName);
    void mergeVarInheritance(std::shared_ptr<Node> target, const std::string& sourceName);
    std::shared_ptr<Node> findStyleDefinition(const std::string& name);
    std::shared_ptr<Node> findElementDefinition(const std::string& name);
    std::shared_ptr<Node> findVarDefinition(const std::string& name);
    void collectDeletedItems(std::shared_ptr<Node> node, std::set<std::string>& deletedItems);
    
    // 定义存储
    std::unordered_map<std::string, std::shared_ptr<Node>> templateDefinitions_;
    std::unordered_map<std::string, std::shared_ptr<Node>> customDefinitions_;
    
private:
    mutable int uniqueIdCounter_ = 0;
};

// Web平台生成器
class WebGenerator : public Generator {
public:
    using Generator::Generator;
    
    GeneratorResult generate(const std::shared_ptr<Node>& ast) override;
    void visit(const std::shared_ptr<Node>& node) override;
    
protected:
    void visitElement(const std::shared_ptr<Element>& element) override;
    void visitCustom(const std::shared_ptr<Custom>& custom) override;
    void visitTemplate(const std::shared_ptr<Template>& tmpl) override;
    void visitStyle(const std::shared_ptr<Style>& style) override;
    void visitScript(const std::shared_ptr<Script>& script) override;
    virtual void visitComment(const std::shared_ptr<Comment>& comment);
    virtual void visitOrigin(const std::shared_ptr<Origin>& origin);
    void visitImport(const std::shared_ptr<Import>& import) override;
    void visitExport(const std::shared_ptr<Export>& export_) override;
    
private:
    // 原始嵌入定义存储
    std::unordered_map<std::string, std::shared_ptr<Origin>> originDefinitions_;
    
    std::string generateHTMLDocument();
    void injectRuntimeCode();
    void processReference(const std::shared_ptr<Element>& refNode);
    void applyReferenceModifications(std::shared_ptr<Node> target,
                                    const std::shared_ptr<Element>& refNode);
    void mergeElement(std::shared_ptr<Node> target, 
                     const std::shared_ptr<Element>& source);
    void executeDeleteOperation(std::shared_ptr<Node> target,
                               const std::shared_ptr<Operate>& deleteOp);
    void deleteFromNode(std::shared_ptr<Node> node, const std::string& target);
    std::vector<std::shared_ptr<Node>>::iterator 
    findTargetNode(std::vector<std::shared_ptr<Node>>& children, 
                   const std::string& target, int& currentIndex);
    void processCustomComponent(const std::shared_ptr<Custom>& instance, 
                                const std::shared_ptr<Node>& definition);
    std::shared_ptr<Node> findComponentDefinition(const std::string& name, Custom::CustomType type);
    void applyInstanceModifications(std::shared_ptr<Node> target, 
                                    const std::shared_ptr<Custom>& instance);
    void executeInsertOperation(std::shared_ptr<Node> target, 
                                const std::shared_ptr<Operate>& insertOp);
    void expandComponent(const std::string& componentName,
                         const std::unordered_map<std::string, std::string>& props,
                         const std::vector<std::shared_ptr<Node>>& children);
    
    // 约束检查
    bool checkConstraints(const std::shared_ptr<Node>& node, Node* parent);
    bool matchesConstraint(const std::shared_ptr<Node>& node, const std::string& constraint);
    
    // 变量处理
    std::string processVarReferences(const std::string& css);
    std::string findVarValue(const std::string& varGroupName, const std::string& propertyName);
    void processStyleContent(const std::shared_ptr<Style>& style);
    std::string expandVarGroup(const std::string& varGroupName);
    
    // 原始嵌入处理
    std::string generateOriginKey(Origin::OriginType type, const std::string& name);
    std::shared_ptr<Origin> findOriginDefinition(const std::string& type, const std::string& name);
    
    // 工具函数
    std::string trim(const std::string& str);
    
    // CJmod 集成
    void visitScriptWithCJmod(const std::shared_ptr<Script>& script, bool isLocal);
    std::string processJavaScriptWithCJmod(const std::string& jsCode);
    void injectCJmodRuntime();
    
    // 活跃的 CJmod 模块
    std::set<std::string> activeCJmodModules_;
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