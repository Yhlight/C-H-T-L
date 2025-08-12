#ifndef CHTL_PARSER_CHTLVISITOR_H
#define CHTL_PARSER_CHTLVISITOR_H

#include "CHTL/CHTLBaseVisitor.h"
#include "CHTL/CHTLParser.h"
#include "Node/Node.h"
#include "State/SymbolTable.h"
#include <memory>
#include <stack>

namespace CHTL {

/**
 * CHTL语法访问者 - 基于ANTLR4生成的代码
 * 负责遍历CHTL语法树并构建AST
 */
class ChtlVisitor : public CHTLBaseVisitor {
public:
    ChtlVisitor(SymbolTable* symbolTable);
    ~ChtlVisitor() = default;
    
    // 获取构建的AST根节点
    NodePtr getAST() { return rootNode_; }
    
    // 重写ANTLR4生成的visitor方法
    antlrcpp::Any visitProgram(CHTLParser::ProgramContext* ctx) override;
    antlrcpp::Any visitElement(CHTLParser::ElementContext* ctx) override;
    antlrcpp::Any visitAttributes(CHTLParser::AttributesContext* ctx) override;
    antlrcpp::Any visitAttribute(CHTLParser::AttributeContext* ctx) override;
    antlrcpp::Any visitTextNode(CHTLParser::TextNodeContext* ctx) override;
    antlrcpp::Any visitLiteral(CHTLParser::LiteralContext* ctx) override;
    antlrcpp::Any visitComment(CHTLParser::CommentContext* ctx) override;
    
    // Style相关
    antlrcpp::Any visitStyleBlock(CHTLParser::StyleBlockContext* ctx) override;
    antlrcpp::Any visitStyleContent(CHTLParser::StyleContentContext* ctx) override;
    antlrcpp::Any visitInlineStyle(CHTLParser::InlineStyleContext* ctx) override;
    antlrcpp::Any visitClassSelector(CHTLParser::ClassSelectorContext* ctx) override;
    antlrcpp::Any visitIdSelector(CHTLParser::IdSelectorContext* ctx) override;
    
    // Script相关
    antlrcpp::Any visitScriptBlock(CHTLParser::ScriptBlockContext* ctx) override;
    
    // Template相关
    antlrcpp::Any visitTemplateDecl(CHTLParser::TemplateDeclContext* ctx) override;
    antlrcpp::Any visitStyleTemplate(CHTLParser::StyleTemplateContext* ctx) override;
    antlrcpp::Any visitElementTemplate(CHTLParser::ElementTemplateContext* ctx) override;
    antlrcpp::Any visitVarTemplate(CHTLParser::VarTemplateContext* ctx) override;
    antlrcpp::Any visitTemplateRef(CHTLParser::TemplateRefContext* ctx) override;
    
    // Custom相关
    antlrcpp::Any visitCustomDecl(CHTLParser::CustomDeclContext* ctx) override;
    antlrcpp::Any visitStyleCustom(CHTLParser::StyleCustomContext* ctx) override;
    antlrcpp::Any visitElementCustom(CHTLParser::ElementCustomContext* ctx) override;
    antlrcpp::Any visitVarCustom(CHTLParser::VarCustomContext* ctx) override;
    antlrcpp::Any visitCustomRef(CHTLParser::CustomRefContext* ctx) override;
    
    // Origin块相关
    antlrcpp::Any visitOriginBlock(CHTLParser::OriginBlockContext* ctx) override;
    
    // Import/Namespace相关
    antlrcpp::Any visitImportStmt(CHTLParser::ImportStmtContext* ctx) override;
    antlrcpp::Any visitNamespaceDecl(CHTLParser::NamespaceDeclContext* ctx) override;
    antlrcpp::Any visitQualifiedName(CHTLParser::QualifiedNameContext* ctx) override;
    
    // Configuration相关
    antlrcpp::Any visitConfigBlock(CHTLParser::ConfigBlockContext* ctx) override;
    antlrcpp::Any visitConfigEntry(CHTLParser::ConfigEntryContext* ctx) override;
    
private:
    // 辅助方法
    NodePtr createElementNode(const std::string& tagName);
    NodePtr createTextNode(const std::string& text);
    NodePtr createStyleNode();
    NodePtr createScriptNode(const std::string& content, bool isCHTLJS);
    NodePtr createTemplateNode(NodeType type, const std::string& name);
    NodePtr createCustomNode(NodeType type, const std::string& name);
    
    // 处理属性
    void processAttributes(NodePtr node, CHTLParser::AttributesContext* ctx);
    
    // 处理样式
    void processInlineStyles(NodePtr styleNode, CHTLParser::StyleContentContext* ctx);
    void processClassSelectors(NodePtr styleNode, CHTLParser::StyleContentContext* ctx);
    
    // 符号表注册
    void registerTemplate(const std::string& name, NodePtr templateNode);
    void registerCustom(const std::string& name, NodePtr customNode);
    
    // 检测CHTL JS扩展
    bool containsCHTLJSExtensions(const std::string& code) const;
    
private:
    SymbolTable* symbolTable_;
    NodePtr rootNode_;
    NodePtr currentNode_;
    std::stack<NodePtr> nodeStack_;
    
    // 当前命名空间
    std::string currentNamespace_;
    
    // 配置信息
    std::unordered_map<std::string, std::string> config_;
};

} // namespace CHTL

#endif // CHTL_PARSER_CHTLVISITOR_H