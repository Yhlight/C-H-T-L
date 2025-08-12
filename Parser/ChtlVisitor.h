#ifndef CHTL_PARSER_CHTLVISITOR_H
#define CHTL_PARSER_CHTLVISITOR_H

// TODO: 当ANTLR4生成代码后，取消下面的注释
// #include "CHTL/CHTLBaseVisitor.h"
// #include "CHTL/CHTLParser.h"

#include "Node/Node.h"
#include "Node/ElementNode.h"
#include "State/SymbolTable.h"
#include <memory>
#include <stack>

namespace CHTL {

// 临时定义，等待ANTLR4生成
namespace CHTLParser {
    class ProgramContext {};
    class ElementContext {};
    class AttributesContext {};
    class AttributeContext {};
    class TextNodeContext {};
    class LiteralContext {};
    class CommentContext {};
    class StyleBlockContext {};
    class StyleContentContext {};
    class InlineStyleContext {};
    class ClassSelectorContext {};
    class IdSelectorContext {};
    class ScriptBlockContext {};
    class TemplateDeclContext {};
    class StyleTemplateContext {};
    class ElementTemplateContext {};
    class VarTemplateContext {};
    class TemplateRefContext {};
    class CustomDeclContext {};
    class StyleCustomContext {};
    class ElementCustomContext {};
    class VarCustomContext {};
    class CustomRefContext {};
    class OriginBlockContext {};
    class ImportStmtContext {};
    class NamespaceDeclContext {};
    class QualifiedNameContext {};
    class ConfigBlockContext {};
    class ConfigEntryContext {};
}

// 临时基类，等待ANTLR4生成
class CHTLBaseVisitor {
public:
    virtual ~CHTLBaseVisitor() = default;
protected:
    // 临时实现
    class Any {};
    Any visitChildren(void*) { return Any(); }
};

using antlrcpp = CHTLBaseVisitor; // 临时别名

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
    antlrcpp::Any visitProgram(CHTLParser::ProgramContext* ctx);
    antlrcpp::Any visitElement(CHTLParser::ElementContext* ctx);
    antlrcpp::Any visitAttributes(CHTLParser::AttributesContext* ctx);
    antlrcpp::Any visitAttribute(CHTLParser::AttributeContext* ctx);
    antlrcpp::Any visitTextNode(CHTLParser::TextNodeContext* ctx);
    antlrcpp::Any visitLiteral(CHTLParser::LiteralContext* ctx);
    antlrcpp::Any visitComment(CHTLParser::CommentContext* ctx);
    
    // Style相关
    antlrcpp::Any visitStyleBlock(CHTLParser::StyleBlockContext* ctx);
    antlrcpp::Any visitStyleContent(CHTLParser::StyleContentContext* ctx);
    antlrcpp::Any visitInlineStyle(CHTLParser::InlineStyleContext* ctx);
    antlrcpp::Any visitClassSelector(CHTLParser::ClassSelectorContext* ctx);
    antlrcpp::Any visitIdSelector(CHTLParser::IdSelectorContext* ctx);
    
    // Script相关
    antlrcpp::Any visitScriptBlock(CHTLParser::ScriptBlockContext* ctx);
    
    // Template相关
    antlrcpp::Any visitTemplateDecl(CHTLParser::TemplateDeclContext* ctx);
    antlrcpp::Any visitStyleTemplate(CHTLParser::StyleTemplateContext* ctx);
    antlrcpp::Any visitElementTemplate(CHTLParser::ElementTemplateContext* ctx);
    antlrcpp::Any visitVarTemplate(CHTLParser::VarTemplateContext* ctx);
    antlrcpp::Any visitTemplateRef(CHTLParser::TemplateRefContext* ctx);
    
    // Custom相关
    antlrcpp::Any visitCustomDecl(CHTLParser::CustomDeclContext* ctx);
    antlrcpp::Any visitStyleCustom(CHTLParser::StyleCustomContext* ctx);
    antlrcpp::Any visitElementCustom(CHTLParser::ElementCustomContext* ctx);
    antlrcpp::Any visitVarCustom(CHTLParser::VarCustomContext* ctx);
    antlrcpp::Any visitCustomRef(CHTLParser::CustomRefContext* ctx);
    
    // Origin块相关
    antlrcpp::Any visitOriginBlock(CHTLParser::OriginBlockContext* ctx);
    
    // Import/Namespace相关
    antlrcpp::Any visitImportStmt(CHTLParser::ImportStmtContext* ctx);
    antlrcpp::Any visitNamespaceDecl(CHTLParser::NamespaceDeclContext* ctx);
    antlrcpp::Any visitQualifiedName(CHTLParser::QualifiedNameContext* ctx);
    
    // Configuration相关
    antlrcpp::Any visitConfigBlock(CHTLParser::ConfigBlockContext* ctx);
    antlrcpp::Any visitConfigEntry(CHTLParser::ConfigEntryContext* ctx);
    
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