#include "ChtlVisitor.h"
#include "Node/TextNode.h"
#include "Node/StyleNode.h"
#include "Node/ScriptNode.h"

namespace CHTL {

ChtlVisitor::ChtlVisitor(SymbolTable* symbolTable)
    : symbolTable_(symbolTable) {
    // 创建根节点
    rootNode_ = std::make_shared<ElementNode>("html");
    currentNode_ = rootNode_;
    nodeStack_.push(rootNode_);
}

// TODO: 实现所有visitor方法
// 这些方法将在ANTLR4生成代码后实现

antlrcpp::Any ChtlVisitor::visitProgram(CHTLParser::ProgramContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitElement(CHTLParser::ElementContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitAttributes(CHTLParser::AttributesContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitAttribute(CHTLParser::AttributeContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitTextNode(CHTLParser::TextNodeContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitLiteral(CHTLParser::LiteralContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitComment(CHTLParser::CommentContext* ctx) {
    // 注释通常被忽略
    return Any();
}

antlrcpp::Any ChtlVisitor::visitStyleBlock(CHTLParser::StyleBlockContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitStyleContent(CHTLParser::StyleContentContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitInlineStyle(CHTLParser::InlineStyleContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitClassSelector(CHTLParser::ClassSelectorContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitIdSelector(CHTLParser::IdSelectorContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitScriptBlock(CHTLParser::ScriptBlockContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitTemplateDecl(CHTLParser::TemplateDeclContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitStyleTemplate(CHTLParser::StyleTemplateContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitElementTemplate(CHTLParser::ElementTemplateContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitVarTemplate(CHTLParser::VarTemplateContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitTemplateRef(CHTLParser::TemplateRefContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitCustomDecl(CHTLParser::CustomDeclContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitStyleCustom(CHTLParser::StyleCustomContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitElementCustom(CHTLParser::ElementCustomContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitVarCustom(CHTLParser::VarCustomContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitCustomRef(CHTLParser::CustomRefContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitOriginBlock(CHTLParser::OriginBlockContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitImportStmt(CHTLParser::ImportStmtContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitNamespaceDecl(CHTLParser::NamespaceDeclContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitQualifiedName(CHTLParser::QualifiedNameContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitConfigBlock(CHTLParser::ConfigBlockContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

antlrcpp::Any ChtlVisitor::visitConfigEntry(CHTLParser::ConfigEntryContext* ctx) {
    // TODO: 实现
    return visitChildren(ctx);
}

// 辅助方法实现

NodePtr ChtlVisitor::createElementNode(const std::string& tagName) {
    return std::make_shared<ElementNode>(tagName);
}

NodePtr ChtlVisitor::createTextNode(const std::string& text) {
    return std::make_shared<TextNode>(text);
}

NodePtr ChtlVisitor::createStyleNode() {
    return std::make_shared<StyleNode>();
}

NodePtr ChtlVisitor::createScriptNode(const std::string& content, bool isCHTLJS) {
    return std::make_shared<ScriptNode>(content, isCHTLJS);
}

NodePtr ChtlVisitor::createTemplateNode(NodeType type, const std::string& name) {
    // TODO: 实现模板节点创建
    return nullptr;
}

NodePtr ChtlVisitor::createCustomNode(NodeType type, const std::string& name) {
    // TODO: 实现自定义节点创建
    return nullptr;
}

void ChtlVisitor::processAttributes(NodePtr node, CHTLParser::AttributesContext* ctx) {
    // TODO: 实现属性处理
}

void ChtlVisitor::processInlineStyles(NodePtr styleNode, CHTLParser::StyleContentContext* ctx) {
    // TODO: 实现内联样式处理
}

void ChtlVisitor::processClassSelectors(NodePtr styleNode, CHTLParser::StyleContentContext* ctx) {
    // TODO: 实现类选择器处理
}

void ChtlVisitor::registerTemplate(const std::string& name, NodePtr templateNode) {
    // TODO: 在符号表中注册模板
}

void ChtlVisitor::registerCustom(const std::string& name, NodePtr customNode) {
    // TODO: 在符号表中注册自定义
}

bool ChtlVisitor::containsCHTLJSExtensions(const std::string& code) const {
    // 检查CHTL JS特有的语法
    return code.find("{{") != std::string::npos ||
           code.find("->") != std::string::npos ||
           code.find("listen") != std::string::npos ||
           code.find("delegate") != std::string::npos ||
           code.find("animate") != std::string::npos;
}

} // namespace CHTL