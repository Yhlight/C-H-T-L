#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <memory>
#include <sstream>
#include <unordered_set>
#include "ASTNode.h"
#include "SymbolTable.h"

namespace CHTL {

// 代码生成器配置
struct GeneratorConfig {
    bool minify = false;
    bool prettify = true;
    bool generateSourceMap = false;
    bool inlineStyles = false;
    bool inlineScripts = false;
    int indentSize = 2;
    std::string indentChar = " ";
};

// 代码生成器
class CodeGenerator : public ASTVisitor {
public:
    CodeGenerator(SymbolTable* symbolTable);
    ~CodeGenerator() = default;
    
    // 生成HTML、CSS和JavaScript
    void generate(const std::shared_ptr<ASTNode>& ast);
    
    // 获取生成的代码
    std::string getHTML() const { return htmlStream_.str(); }
    std::string getCSS() const { return cssStream_.str(); }
    std::string getJavaScript() const { return jsStream_.str(); }
    
    // 设置配置
    void setConfig(const GeneratorConfig& config) { config_ = config; }
    
    // 访问者方法实现
    void visitElement(ElementNode* node) override;
    void visitText(TextNode* node) override;
    void visitStyleBlock(StyleBlockNode* node) override;
    void visitScriptBlock(ScriptBlockNode* node) override;
    void visitTemplate(TemplateNode* node) override;
    void visitCustom(CustomNode* node) override;
    
private:
    // 输出流
    std::stringstream htmlStream_;
    std::stringstream cssStream_;
    std::stringstream jsStream_;
    
    // 当前输出流
    std::stringstream* currentStream_;
    
    // 符号表引用
    SymbolTable* symbolTable_;
    
    // 配置
    GeneratorConfig config_;
    
    // 缩进管理
    int indentLevel_ = 0;
    void indent();
    void dedent();
    std::string getIndent() const;
    
    // HTML生成辅助函数
    void generateElement(ElementNode* node);
    void generateAttributes(ElementNode* node);
    void generateChildren(const std::shared_ptr<ASTNode>& node);
    
    // CSS生成辅助函数
    void generateStyleBlock(StyleBlockNode* node);
    void generateInlineStyles(const std::unordered_map<std::string, std::string>& styles);
    void generateClassStyles(const std::string& className, StyleBlockNode* node);
    std::string generateUniqueClassName();
    
    // JavaScript生成辅助函数
    void generateScriptBlock(ScriptBlockNode* node);
    void generateCHTLJSHelpers();
    
    // 模板展开
    void expandTemplate(TemplateNode* node);
    void expandCustom(CustomNode* node);
    
    // 工具函数
    std::string escapeHTML(const std::string& text);
    std::string escapeJS(const std::string& text);
    bool isVoidElement(const std::string& tagName);
    
    // 已生成的类名集合（用于避免重复）
    std::unordered_set<std::string> generatedClasses_;
    
    // 类名计数器
    int classNameCounter_ = 0;
};

} // namespace CHTL

#endif // CODE_GENERATOR_H