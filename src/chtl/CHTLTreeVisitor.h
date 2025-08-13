#pragma once

#include "generated/CHTLParserBaseVisitor.h"
#include "CHTLContext.h"
#include "CHTLGenerator.h"
#include <memory>

namespace chtl {

/**
 * CHTL解析树访问器
 * 遍历ANTLR生成的解析树并生成HTML/CSS/JS
 */
class CHTLTreeVisitor : public CHTLParserBaseVisitor {
public:
    CHTLTreeVisitor(std::shared_ptr<CHTLContext> context);
    
    // 访问编译单元（顶层）
    antlrcpp::Any visitCompilationUnit(CHTLParser::CompilationUnitContext* ctx) override;
    
    // 访问HTML元素
    antlrcpp::Any visitHtmlElement(CHTLParser::HtmlElementContext* ctx) override;
    
    // 访问文本节点
    antlrcpp::Any visitTextNode(CHTLParser::TextNodeContext* ctx) override;
    
    // 访问样式块
    antlrcpp::Any visitStyleBlock(CHTLParser::StyleBlockContext* ctx) override;
    
    // 访问脚本块
    antlrcpp::Any visitScriptBlock(CHTLParser::ScriptBlockContext* ctx) override;
    
    // 访问模板定义
    antlrcpp::Any visitTemplateDefinition(CHTLParser::TemplateDefinitionContext* ctx) override;
    
    // 访问自定义定义
    antlrcpp::Any visitCustomDefinition(CHTLParser::CustomDefinitionContext* ctx) override;
    
    // 访问导入语句
    antlrcpp::Any visitImportStatement(CHTLParser::ImportStatementContext* ctx) override;
    
    // 访问命名空间
    antlrcpp::Any visitNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext* ctx) override;
    
    // 访问属性
    antlrcpp::Any visitAttribute(CHTLParser::AttributeContext* ctx) override;
    
    // 访问表达式
    antlrcpp::Any visitExpression(CHTLParser::ExpressionContext* ctx) override;
    
    /**
     * 获取生成器
     */
    CHTLGenerator& getGenerator() { return *generator; }
    
private:
    std::shared_ptr<CHTLContext> context;
    std::unique_ptr<CHTLGenerator> generator;
    
    // 当前处理状态
    std::string currentNamespace;
    std::vector<std::string> scopeStack;
    
    // 辅助方法
    std::string evaluateExpression(CHTLParser::ExpressionContext* ctx);
    void enterScope(const std::string& scope);
    void exitScope();
    std::string getCurrentScope() const;
};

} // namespace chtl