#ifndef CHTL_GENERATOR_STANDARDGENERATOR_H
#define CHTL_GENERATOR_STANDARDGENERATOR_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Node/Node.h"
#include "State/SymbolTable.h"

namespace CHTL {

/**
 * 生成结果
 */
struct GenerateResult {
    bool success = true;
    std::string html;
    std::string css;
    std::string javascript;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // 附加输出文件（如模块文件）
    std::unordered_map<std::string, std::string> additionalFiles;
};

/**
 * 标准生成器 - 负责从AST生成HTML、CSS和JavaScript代码
 * 整合了各语言的生成器
 */
class StandardGenerator {
public:
    StandardGenerator();
    ~StandardGenerator();
    
    /**
     * 从AST生成代码
     * @param ast AST根节点
     * @param symbolTable 符号表（可选）
     * @return 生成结果
     */
    GenerateResult generate(NodePtr ast, SymbolTable* symbolTable = nullptr);
    
    /**
     * 设置生成选项
     */
    void setMinify(bool minify) { minify_ = minify; }
    void setPrettify(bool prettify) { prettify_ = prettify; }
    void setSeparateFiles(bool separate) { separateFiles_ = separate; }
    void setModularize(bool modularize) { modularize_ = modularize; }
    
    /**
     * 设置输出配置
     */
    void setOutputConfig(const std::string& key, const std::string& value);
    
    /**
     * 设置优化级别
     */
    void setOptimizationLevel(int level) { optimizationLevel_ = level; }
    
private:
    /**
     * 预处理AST
     */
    void preprocessAST(NodePtr ast, SymbolTable* symbolTable);
    
    /**
     * 展开模板和自定义
     */
    void expandTemplatesAndCustoms(NodePtr ast, SymbolTable* symbolTable);
    
    /**
     * 收集样式
     */
    void collectStyles(NodePtr ast, std::vector<NodePtr>& styleNodes);
    
    /**
     * 收集脚本
     */
    void collectScripts(NodePtr ast, std::vector<NodePtr>& scriptNodes);
    
    /**
     * 生成HTML
     */
    std::string generateHTML(NodePtr ast);
    
    /**
     * 生成CSS
     */
    std::string generateCSS(const std::vector<NodePtr>& styleNodes);
    
    /**
     * 生成JavaScript
     */
    std::string generateJavaScript(const std::vector<NodePtr>& scriptNodes);
    
    /**
     * 生成模块文件
     */
    void generateModules(NodePtr ast, GenerateResult& result);
    
    /**
     * 优化代码
     */
    void optimizeCode(GenerateResult& result);
    
    /**
     * 格式化代码
     */
    std::string formatCode(const std::string& code, const std::string& language);
    
    /**
     * 压缩代码
     */
    std::string minifyCode(const std::string& code, const std::string& language);
    
    /**
     * 美化代码
     */
    std::string prettifyCode(const std::string& code, const std::string& language);
    
private:
    // 生成选项
    bool minify_ = false;
    bool prettify_ = true;
    bool separateFiles_ = false;
    bool modularize_ = false;
    int optimizationLevel_ = 1;
    
    // 输出配置
    std::unordered_map<std::string, std::string> outputConfig_;
    
    // 子生成器（在实现文件中定义）
    class HtmlGeneratorImpl;
    class CssGeneratorImpl;
    class JsGeneratorImpl;
    
    std::unique_ptr<HtmlGeneratorImpl> htmlGenerator_;
    std::unique_ptr<CssGeneratorImpl> cssGenerator_;
    std::unique_ptr<JsGeneratorImpl> jsGenerator_;
};

} // namespace CHTL

#endif // CHTL_GENERATOR_STANDARDGENERATOR_H