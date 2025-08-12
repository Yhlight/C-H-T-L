#ifndef CHTL_PARSER_CHTLVISITOR_H
#define CHTL_PARSER_CHTLVISITOR_H

#include "CHTL/CHTLBaseVisitor.h"
#include "CHTL/CHTLParser.h"
#include "Node/Node.h"
#include "Node/ElementNode.h"
#include "Node/TextNode.h"
#include "Node/StyleNode.h"
#include "Node/ScriptNode.h"
#include "Node/TemplateNode.h"
#include "Node/CustomNode.h"
#include "State/SymbolTable.h"
#include <memory>
#include <stack>
#include <any>

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
    std::any visitProgram(CHTLParser::ProgramContext* ctx) override;
    std::any visitElement(CHTLParser::ElementContext* ctx) override;
    std::any visitAttribute(CHTLParser::AttributeContext* ctx) override;
    std::any visitTextNode(CHTLParser::TextNodeContext* ctx) override;
    std::any visitStringLiteral(CHTLParser::StringLiteralContext* ctx) override;
    std::any visitComment(CHTLParser::CommentContext* ctx) override;
    
    // Style相关
    std::any visitStyleBlock(CHTLParser::StyleBlockContext* ctx) override;
    std::any visitStyleContent(CHTLParser::StyleContentContext* ctx) override;
    std::any visitCssProperty(CHTLParser::CssPropertyContext* ctx) override;
    std::any visitCssSelector(CHTLParser::CssSelectorContext* ctx) override;
    std::any visitClassSelector(CHTLParser::ClassSelectorContext* ctx) override;
    std::any visitIdSelector(CHTLParser::IdSelectorContext* ctx) override;
    
    // Script相关
    std::any visitScriptBlock(CHTLParser::ScriptBlockContext* ctx) override;
    
    // Template相关
    std::any visitTemplateDeclaration(CHTLParser::TemplateDeclarationContext* ctx) override;
    std::any visitTemplateType(CHTLParser::TemplateTypeContext* ctx) override;
    std::any visitTemplateName(CHTLParser::TemplateNameContext* ctx) override;
    std::any visitTemplateUsage(CHTLParser::TemplateUsageContext* ctx) override;
    
    // Custom相关
    std::any visitCustomDeclaration(CHTLParser::CustomDeclarationContext* ctx) override;
    std::any visitCustomType(CHTLParser::CustomTypeContext* ctx) override;
    std::any visitCustomName(CHTLParser::CustomNameContext* ctx) override;
    std::any visitCustomUsage(CHTLParser::CustomUsageContext* ctx) override;
    
    // Origin块相关
    std::any visitOriginBlock(CHTLParser::OriginBlockContext* ctx) override;
    
    // Import相关
    std::any visitImportStatement(CHTLParser::ImportStatementContext* ctx) override;
    std::any visitImportChtl(CHTLParser::ImportChtlContext* ctx) override;
    
    // Namespace相关
    std::any visitNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext* ctx) override;
    
    // Configuration相关
    std::any visitConfigurationBlock(CHTLParser::ConfigurationBlockContext* ctx) override;
    
private:
    // 辅助方法
    NodePtr createElementNode(const std::string& tagName);
    NodePtr createTextNode(const std::string& text);
    NodePtr createStyleNode();
    NodePtr createScriptNode(const std::string& content, bool isCHTLJS);
    NodePtr createTemplateNode(TemplateNode::TemplateType type, const std::string& name);
    NodePtr createCustomNode(CustomNode::CustomType type, const std::string& name);
    
    // 处理属性
    void processElementAttributes(NodePtr node, CHTLParser::ElementBodyContext* ctx);
    
    // 符号表注册
    void registerTemplate(const std::string& name, NodePtr templateNode);
    void registerCustom(const std::string& name, NodePtr customNode);
    
    // 检测CHTL JS扩展
    bool containsCHTLJSExtensions(const std::string& code) const;
    
    // 获取文本内容
    std::string getText(antlr4::tree::ParseTree* tree);
    
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