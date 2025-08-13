#ifndef CHTL_CSS_COMPILER_H
#define CHTL_CSS_COMPILER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "CHTLContext.h"
#include "../../generated/CSSLexer.h"
#include "../../generated/CSSParser.h"
#include "../../generated/CSSBaseListener.h"

namespace chtl {

// 前向声明
class TemplateManager;
class CustomManager;
class CHTLEnhancedCSSCompiler;

// CSS规则结构
struct CSSRule {
    std::vector<std::string> selectors;
    std::unordered_map<std::string, std::string> declarations;
    std::string rawContent;  // 原始内容，用于某些特殊情况
    
    std::string toString() const;
};

// CSS @规则结构
struct CSSAtRule {
    std::string type;       // @media, @keyframes等
    std::string condition;  // 条件或名称
    std::vector<CSSRule> rules;
    std::string rawContent;
    
    std::string toString() const;
};

// CSS编译器监听器
class CSSCompilerListener : public CSSBaseListener {
private:
    std::vector<CSSRule> rules;
    std::vector<CSSAtRule> atRules;
    CSSRule currentRule;
    CSSAtRule currentAtRule;
    std::string currentProperty;
    std::string currentValue;
    bool inAtRule = false;
    std::stringstream output;
    
    // 配置选项
    bool minify = false;
    bool preserveComments = false;
    
public:
    CSSCompilerListener(bool minifyOutput = false, bool keepComments = false);
    
    // 获取编译后的CSS
    std::string getCompiledCSS() const { return output.str(); }
    
    // 获取规则列表（用于分析）
    const std::vector<CSSRule>& getRules() const { return rules; }
    const std::vector<CSSAtRule>& getAtRules() const { return atRules; }
    
    // CSS解析器监听器方法
    void enterStylesheet(CSSParser::StylesheetContext* ctx) override;
    void exitStylesheet(CSSParser::StylesheetContext* ctx) override;
    
    void enterRuleset(CSSParser::RulesetContext* ctx) override;
    void exitRuleset(CSSParser::RulesetContext* ctx) override;
    
    void enterSelectorList(CSSParser::SelectorListContext* ctx) override;
    void enterSelector(CSSParser::SelectorContext* ctx) override;
    
    void enterDeclaration(CSSParser::DeclarationContext* ctx) override;
    void exitDeclaration(CSSParser::DeclarationContext* ctx) override;
    
    void enterProperty(CSSParser::PropertyContext* ctx) override;
    void enterValue(CSSParser::ValueContext* ctx) override;
    
    // @规则处理
    void enterAtMedia(CSSParser::AtMediaContext* ctx) override;
    void exitAtMedia(CSSParser::AtMediaContext* ctx) override;
    
    void enterAtKeyframes(CSSParser::AtKeyframesContext* ctx) override;
    void exitAtKeyframes(CSSParser::AtKeyframesContext* ctx) override;
    
    void enterAtImport(CSSParser::AtImportContext* ctx) override;
    
    void enterComment(CSSParser::CommentContext* ctx) override;
    
private:
    // 辅助方法
    std::string extractText(antlr4::ParserRuleContext* ctx);
    std::string formatSelector(const std::string& selector);
    std::string formatDeclaration(const std::string& property, const std::string& value);
    void writeRule(const CSSRule& rule);
    void writeAtRule(const CSSAtRule& atRule);
    std::string getIndent() const;
};

// CSS编译器
class CSSCompiler {
private:
    std::shared_ptr<CHTLContext> context;
    bool minify;
    bool preserveComments;
    
public:
    CSSCompiler(std::shared_ptr<CHTLContext> ctx);
    
    // 编译选项
    void setMinify(bool value) { minify = value; }
    void setPreserveComments(bool value) { preserveComments = value; }
    
    // 编译CSS
    std::string compile(const std::string& css);
    
    // 编译并返回规则列表（用于分析）
    std::pair<std::string, std::vector<CSSRule>> compileWithAnalysis(const std::string& css);
    
    // 验证CSS
    bool validate(const std::string& css, std::vector<std::string>& errors);
    
    // 处理CHTL的全局样式块
    std::string processGlobalStyleBlock(const std::string& cssContent);
    
    // 合并多个CSS块
    std::string mergeCSSBlocks(const std::vector<std::string>& blocks);
    
private:
    // 错误处理
    class CSSErrorListener : public antlr4::BaseErrorListener {
    private:
        std::vector<std::string>& errors;
        
    public:
        CSSErrorListener(std::vector<std::string>& errs) : errors(errs) {}
        
        void syntaxError(antlr4::Recognizer* recognizer,
                        antlr4::Token* offendingSymbol,
                        size_t line,
                        size_t charPositionInLine,
                        const std::string& msg,
                        std::exception_ptr e) override;
    };
};

// CSS优化器
class CSSOptimizer {
public:
    // 优化选项
    struct Options {
        bool mergeRules = true;         // 合并相同选择器的规则
        bool removeEmptyRules = true;   // 移除空规则
        bool shorthandProperties = true; // 使用简写属性
        bool removeRedundant = true;    // 移除冗余声明
        bool optimizeColors = true;     // 优化颜色值
        bool optimizeUnits = true;      // 优化单位
    };
    
private:
    Options options;
    
public:
    CSSOptimizer(const Options& opts = Options()) : options(opts) {}
    
    // 优化CSS规则
    std::vector<CSSRule> optimize(const std::vector<CSSRule>& rules);
    
    // 优化单个规则
    CSSRule optimizeRule(const CSSRule& rule);
    
    // 合并规则
    std::vector<CSSRule> mergeRules(const std::vector<CSSRule>& rules);
    
private:
    // 优化颜色值
    std::string optimizeColor(const std::string& color);
    
    // 优化单位
    std::string optimizeUnit(const std::string& value);
    
    // 转换为简写属性
    std::unordered_map<std::string, std::string> toShorthand(
        const std::unordered_map<std::string, std::string>& declarations);
};

// CSS处理器 - 集成到CHTL
class CHTLCSSProcessor {
private:
    std::shared_ptr<CHTLContext> context;
    std::shared_ptr<CSSCompiler> compiler;
    std::shared_ptr<CSSOptimizer> optimizer;
    std::shared_ptr<CHTLEnhancedCSSCompiler> enhancedCompiler;  // 添加增强编译器
    
    // 存储所有的CSS块
    std::vector<std::string> globalStyleBlocks;
    std::vector<std::string> localStyleBlocks;
    
    // 模板和自定义管理器引用
    std::shared_ptr<TemplateManager> templateManager;
    std::shared_ptr<CustomManager> customManager;
    
public:
    CHTLCSSProcessor(std::shared_ptr<CHTLContext> ctx);
    
    // 设置管理器
    void setTemplateManager(std::shared_ptr<TemplateManager> mgr);
    void setCustomManager(std::shared_ptr<CustomManager> mgr);
    
    // 添加全局样式块（来自<style>标签）
    void addGlobalStyleBlock(const std::string& css);
    
    // 添加局部样式块（来自元素内的style {}）
    void addLocalStyleBlock(const std::string& css, const std::string& scope = "");
    
    // 处理并生成最终的CSS
    std::string generateFinalCSS();
    
    // 获取所有的类名和ID（用于验证）
    std::pair<std::set<std::string>, std::set<std::string>> extractSelectorsInfo();
    
    // 验证CSS引用
    void validateReferences(const std::set<std::string>& usedClasses,
                           const std::set<std::string>& usedIds);
                           
    // 启用/禁用增强功能
    void setEnhancedMode(bool enabled) { useEnhancedMode = enabled; }
    
private:
    bool useEnhancedMode = true;  // 默认启用增强功能
};

} // namespace chtl

#endif // CHTL_CSS_COMPILER_H