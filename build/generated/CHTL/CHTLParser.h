
// Generated from /workspace/grammar/CHTL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLParser : public antlr4::Parser {
public:
  enum {
    TEXT = 1, STYLE = 2, SCRIPT = 3, TEMPLATE = 4, CUSTOM = 5, ORIGIN = 6, 
    IMPORT = 7, NAMESPACE = 8, CONFIGURATION = 9, NAME = 10, INFO = 11, 
    EXPORT = 12, AT_STYLE = 13, AT_ELEMENT = 14, AT_VAR = 15, AT_HTML = 16, 
    AT_JAVASCRIPT = 17, AT_CHTL = 18, INHERIT = 19, DELETE = 20, INSERT = 21, 
    AFTER = 22, BEFORE = 23, REPLACE = 24, AT = 25, TOP = 26, BOTTOM = 27, 
    FROM = 28, AS = 29, EXCEPT = 30, BOOLEAN = 31, COLON = 32, SEMICOLON = 33, 
    EQUALS = 34, COMMA = 35, DOT = 36, HASH = 37, AMPERSAND = 38, MINUS = 39, 
    LBRACE = 40, RBRACE = 41, LBRACKET = 42, RBRACKET = 43, LPAREN = 44, 
    RPAREN = 45, LINE_COMMENT = 46, BLOCK_COMMENT = 47, GENERATOR_COMMENT = 48, 
    STRING_LITERAL = 49, SINGLE_STRING_LITERAL = 50, IDENTIFIER = 51, NUMBER = 52, 
    UNQUOTED_LITERAL = 53, WS = 54
  };

  enum {
    RuleProgram = 0, RuleStatement = 1, RuleComment = 2, RuleTextNode = 3, 
    RuleStringLiteral = 4, RuleElement = 5, RuleElementName = 6, RuleElementBody = 7, 
    RuleElementContent = 8, RuleAttribute = 9, RuleAttributeName = 10, RuleAttributeValue = 11, 
    RuleStyleBlock = 12, RuleStyleContent = 13, RuleCssProperty = 14, RuleCssPropertyName = 15, 
    RuleCssPropertyValue = 16, RuleCssValue = 17, RuleCssSelector = 18, 
    RuleSelectorPattern = 19, RuleClassSelector = 20, RuleIdSelector = 21, 
    RuleAmpersandSelector = 22, RulePseudoSelector = 23, RuleScriptBlock = 24, 
    RuleJsCode = 25, RuleTemplateDeclaration = 26, RuleTemplateType = 27, 
    RuleTemplateName = 28, RuleTemplateBody = 29, RuleTemplateContent = 30, 
    RuleVarDeclaration = 31, RuleCustomDeclaration = 32, RuleCustomType = 33, 
    RuleCustomName = 34, RuleCustomBody = 35, RuleCustomContent = 36, RuleCssPropertyWithoutValue = 37, 
    RuleTemplateUsage = 38, RuleTemplateSpecialization = 39, RuleSpecializationContent = 40, 
    RuleVarAssignment = 41, RuleCustomUsage = 42, RuleCustomSpecialization = 43, 
    RuleInheritStatement = 44, RuleDeleteStatement = 45, RuleDeleteTarget = 46, 
    RuleElementIndex = 47, RuleInsertStatement = 48, RuleInsertPosition = 49, 
    RuleInsertTarget = 50, RuleInsertContent = 51, RuleExceptStatement = 52, 
    RuleExceptTarget = 53, RuleOriginBlock = 54, RuleOriginType = 55, RuleOriginName = 56, 
    RuleOriginBody = 57, RuleRawContent = 58, RuleImportStatement = 59, 
    RuleImportContent = 60, RuleImportHtml = 61, RuleImportCss = 62, RuleImportJs = 63, 
    RuleImportChtl = 64, RuleImportCustom = 65, RuleImportTemplate = 66, 
    RuleFilePath = 67, RuleNamespaceDeclaration = 68, RuleNamespaceName = 69, 
    RuleNamespaceBody = 70, RuleNamespaceContent = 71, RuleConfigurationBlock = 72, 
    RuleConfigContent = 73, RuleConfigAssignment = 74, RuleConfigValue = 75, 
    RuleNameBlock = 76, RuleNameAssignment = 77
  };

  explicit CHTLParser(antlr4::TokenStream *input);

  CHTLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CHTLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class StatementContext;
  class CommentContext;
  class TextNodeContext;
  class StringLiteralContext;
  class ElementContext;
  class ElementNameContext;
  class ElementBodyContext;
  class ElementContentContext;
  class AttributeContext;
  class AttributeNameContext;
  class AttributeValueContext;
  class StyleBlockContext;
  class StyleContentContext;
  class CssPropertyContext;
  class CssPropertyNameContext;
  class CssPropertyValueContext;
  class CssValueContext;
  class CssSelectorContext;
  class SelectorPatternContext;
  class ClassSelectorContext;
  class IdSelectorContext;
  class AmpersandSelectorContext;
  class PseudoSelectorContext;
  class ScriptBlockContext;
  class JsCodeContext;
  class TemplateDeclarationContext;
  class TemplateTypeContext;
  class TemplateNameContext;
  class TemplateBodyContext;
  class TemplateContentContext;
  class VarDeclarationContext;
  class CustomDeclarationContext;
  class CustomTypeContext;
  class CustomNameContext;
  class CustomBodyContext;
  class CustomContentContext;
  class CssPropertyWithoutValueContext;
  class TemplateUsageContext;
  class TemplateSpecializationContext;
  class SpecializationContentContext;
  class VarAssignmentContext;
  class CustomUsageContext;
  class CustomSpecializationContext;
  class InheritStatementContext;
  class DeleteStatementContext;
  class DeleteTargetContext;
  class ElementIndexContext;
  class InsertStatementContext;
  class InsertPositionContext;
  class InsertTargetContext;
  class InsertContentContext;
  class ExceptStatementContext;
  class ExceptTargetContext;
  class OriginBlockContext;
  class OriginTypeContext;
  class OriginNameContext;
  class OriginBodyContext;
  class RawContentContext;
  class ImportStatementContext;
  class ImportContentContext;
  class ImportHtmlContext;
  class ImportCssContext;
  class ImportJsContext;
  class ImportChtlContext;
  class ImportCustomContext;
  class ImportTemplateContext;
  class FilePathContext;
  class NamespaceDeclarationContext;
  class NamespaceNameContext;
  class NamespaceBodyContext;
  class NamespaceContentContext;
  class ConfigurationBlockContext;
  class ConfigContentContext;
  class ConfigAssignmentContext;
  class ConfigValueContext;
  class NameBlockContext;
  class NameAssignmentContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementContext *element();
    TextNodeContext *textNode();
    StyleBlockContext *styleBlock();
    ScriptBlockContext *scriptBlock();
    TemplateDeclarationContext *templateDeclaration();
    CustomDeclarationContext *customDeclaration();
    OriginBlockContext *originBlock();
    ImportStatementContext *importStatement();
    NamespaceDeclarationContext *namespaceDeclaration();
    ConfigurationBlockContext *configurationBlock();
    CommentContext *comment();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  CommentContext : public antlr4::ParserRuleContext {
  public:
    CommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LINE_COMMENT();
    antlr4::tree::TerminalNode *BLOCK_COMMENT();
    antlr4::tree::TerminalNode *GENERATOR_COMMENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CommentContext* comment();

  class  TextNodeContext : public antlr4::ParserRuleContext {
  public:
    TextNodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEXT();
    antlr4::tree::TerminalNode *LBRACE();
    StringLiteralContext *stringLiteral();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TextNodeContext* textNode();

  class  StringLiteralContext : public antlr4::ParserRuleContext {
  public:
    StringLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *SINGLE_STRING_LITERAL();
    antlr4::tree::TerminalNode *UNQUOTED_LITERAL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringLiteralContext* stringLiteral();

  class  ElementContext : public antlr4::ParserRuleContext {
  public:
    ElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementNameContext *elementName();
    ElementBodyContext *elementBody();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementContext* element();

  class  ElementNameContext : public antlr4::ParserRuleContext {
  public:
    ElementNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementNameContext* elementName();

  class  ElementBodyContext : public antlr4::ParserRuleContext {
  public:
    ElementBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<ElementContentContext *> elementContent();
    ElementContentContext* elementContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementBodyContext* elementBody();

  class  ElementContentContext : public antlr4::ParserRuleContext {
  public:
    ElementContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeContext *attribute();
    ElementContext *element();
    TextNodeContext *textNode();
    StyleBlockContext *styleBlock();
    ScriptBlockContext *scriptBlock();
    TemplateUsageContext *templateUsage();
    CustomUsageContext *customUsage();
    OriginBlockContext *originBlock();
    InsertStatementContext *insertStatement();
    DeleteStatementContext *deleteStatement();
    ExceptStatementContext *exceptStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementContentContext* elementContent();

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeNameContext *attributeName();
    AttributeValueContext *attributeValue();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *EQUALS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeContext* attribute();

  class  AttributeNameContext : public antlr4::ParserRuleContext {
  public:
    AttributeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeNameContext* attributeName();

  class  AttributeValueContext : public antlr4::ParserRuleContext {
  public:
    AttributeValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeValueContext* attributeValue();

  class  StyleBlockContext : public antlr4::ParserRuleContext {
  public:
    StyleBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STYLE();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StyleContentContext *> styleContent();
    StyleContentContext* styleContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StyleBlockContext* styleBlock();

  class  StyleContentContext : public antlr4::ParserRuleContext {
  public:
    StyleContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CssPropertyContext *cssProperty();
    CssSelectorContext *cssSelector();
    TemplateUsageContext *templateUsage();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StyleContentContext* styleContent();

  class  CssPropertyContext : public antlr4::ParserRuleContext {
  public:
    CssPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CssPropertyNameContext *cssPropertyName();
    antlr4::tree::TerminalNode *COLON();
    CssPropertyValueContext *cssPropertyValue();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssPropertyContext* cssProperty();

  class  CssPropertyNameContext : public antlr4::ParserRuleContext {
  public:
    CssPropertyNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssPropertyNameContext* cssPropertyName();

  class  CssPropertyValueContext : public antlr4::ParserRuleContext {
  public:
    CssPropertyValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();
    CssValueContext *cssValue();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssPropertyValueContext* cssPropertyValue();

  class  CssValueContext : public antlr4::ParserRuleContext {
  public:
    CssValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACE();
    antlr4::tree::TerminalNode* RBRACE(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssValueContext* cssValue();

  class  CssSelectorContext : public antlr4::ParserRuleContext {
  public:
    CssSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectorPatternContext *selectorPattern();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<CssPropertyContext *> cssProperty();
    CssPropertyContext* cssProperty(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssSelectorContext* cssSelector();

  class  SelectorPatternContext : public antlr4::ParserRuleContext {
  public:
    SelectorPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassSelectorContext *classSelector();
    IdSelectorContext *idSelector();
    AmpersandSelectorContext *ampersandSelector();
    PseudoSelectorContext *pseudoSelector();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectorPatternContext* selectorPattern();

  class  ClassSelectorContext : public antlr4::ParserRuleContext {
  public:
    ClassSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassSelectorContext* classSelector();

  class  IdSelectorContext : public antlr4::ParserRuleContext {
  public:
    IdSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HASH();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdSelectorContext* idSelector();

  class  AmpersandSelectorContext : public antlr4::ParserRuleContext {
  public:
    AmpersandSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AMPERSAND();
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AmpersandSelectorContext* ampersandSelector();

  class  PseudoSelectorContext : public antlr4::ParserRuleContext {
  public:
    PseudoSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PseudoSelectorContext* pseudoSelector();

  class  ScriptBlockContext : public antlr4::ParserRuleContext {
  public:
    ScriptBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SCRIPT();
    antlr4::tree::TerminalNode *LBRACE();
    JsCodeContext *jsCode();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScriptBlockContext* scriptBlock();

  class  JsCodeContext : public antlr4::ParserRuleContext {
  public:
    JsCodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> RBRACE();
    antlr4::tree::TerminalNode* RBRACE(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JsCodeContext* jsCode();

  class  TemplateDeclarationContext : public antlr4::ParserRuleContext {
  public:
    TemplateDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *TEMPLATE();
    antlr4::tree::TerminalNode *RBRACKET();
    TemplateTypeContext *templateType();
    TemplateNameContext *templateName();
    TemplateBodyContext *templateBody();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateDeclarationContext* templateDeclaration();

  class  TemplateTypeContext : public antlr4::ParserRuleContext {
  public:
    TemplateTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT_STYLE();
    antlr4::tree::TerminalNode *AT_ELEMENT();
    antlr4::tree::TerminalNode *AT_VAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateTypeContext* templateType();

  class  TemplateNameContext : public antlr4::ParserRuleContext {
  public:
    TemplateNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateNameContext* templateName();

  class  TemplateBodyContext : public antlr4::ParserRuleContext {
  public:
    TemplateBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<TemplateContentContext *> templateContent();
    TemplateContentContext* templateContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateBodyContext* templateBody();

  class  TemplateContentContext : public antlr4::ParserRuleContext {
  public:
    TemplateContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CssPropertyContext *cssProperty();
    ElementContext *element();
    VarDeclarationContext *varDeclaration();
    TemplateUsageContext *templateUsage();
    InheritStatementContext *inheritStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateContentContext* templateContent();

  class  VarDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    StringLiteralContext *stringLiteral();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDeclarationContext* varDeclaration();

  class  CustomDeclarationContext : public antlr4::ParserRuleContext {
  public:
    CustomDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *CUSTOM();
    antlr4::tree::TerminalNode *RBRACKET();
    CustomTypeContext *customType();
    CustomNameContext *customName();
    CustomBodyContext *customBody();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CustomDeclarationContext* customDeclaration();

  class  CustomTypeContext : public antlr4::ParserRuleContext {
  public:
    CustomTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT_STYLE();
    antlr4::tree::TerminalNode *AT_ELEMENT();
    antlr4::tree::TerminalNode *AT_VAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CustomTypeContext* customType();

  class  CustomNameContext : public antlr4::ParserRuleContext {
  public:
    CustomNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CustomNameContext* customName();

  class  CustomBodyContext : public antlr4::ParserRuleContext {
  public:
    CustomBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<CustomContentContext *> customContent();
    CustomContentContext* customContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CustomBodyContext* customBody();

  class  CustomContentContext : public antlr4::ParserRuleContext {
  public:
    CustomContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CssPropertyContext *cssProperty();
    CssPropertyWithoutValueContext *cssPropertyWithoutValue();
    ElementContext *element();
    VarDeclarationContext *varDeclaration();
    TemplateUsageContext *templateUsage();
    CustomUsageContext *customUsage();
    DeleteStatementContext *deleteStatement();
    InsertStatementContext *insertStatement();
    InheritStatementContext *inheritStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CustomContentContext* customContent();

  class  CssPropertyWithoutValueContext : public antlr4::ParserRuleContext {
  public:
    CssPropertyWithoutValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CssPropertyNameContext *> cssPropertyName();
    CssPropertyNameContext* cssPropertyName(size_t i);
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssPropertyWithoutValueContext* cssPropertyWithoutValue();

  class  TemplateUsageContext : public antlr4::ParserRuleContext {
  public:
    TemplateUsageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TemplateTypeContext *templateType();
    TemplateNameContext *templateName();
    antlr4::tree::TerminalNode *SEMICOLON();
    TemplateSpecializationContext *templateSpecialization();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateUsageContext* templateUsage();

  class  TemplateSpecializationContext : public antlr4::ParserRuleContext {
  public:
    TemplateSpecializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<SpecializationContentContext *> specializationContent();
    SpecializationContentContext* specializationContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateSpecializationContext* templateSpecialization();

  class  SpecializationContentContext : public antlr4::ParserRuleContext {
  public:
    SpecializationContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CssPropertyContext *cssProperty();
    DeleteStatementContext *deleteStatement();
    VarAssignmentContext *varAssignment();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecializationContentContext* specializationContent();

  class  VarAssignmentContext : public antlr4::ParserRuleContext {
  public:
    VarAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUALS();
    StringLiteralContext *stringLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarAssignmentContext* varAssignment();

  class  CustomUsageContext : public antlr4::ParserRuleContext {
  public:
    CustomUsageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CustomTypeContext *customType();
    CustomNameContext *customName();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *CUSTOM();
    antlr4::tree::TerminalNode *RBRACKET();
    CustomSpecializationContext *customSpecialization();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CustomUsageContext* customUsage();

  class  CustomSpecializationContext : public antlr4::ParserRuleContext {
  public:
    CustomSpecializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<SpecializationContentContext *> specializationContent();
    SpecializationContentContext* specializationContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CustomSpecializationContext* customSpecialization();

  class  InheritStatementContext : public antlr4::ParserRuleContext {
  public:
    InheritStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INHERIT();
    TemplateTypeContext *templateType();
    TemplateNameContext *templateName();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InheritStatementContext* inheritStatement();

  class  DeleteStatementContext : public antlr4::ParserRuleContext {
  public:
    DeleteStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();
    std::vector<DeleteTargetContext *> deleteTarget();
    DeleteTargetContext* deleteTarget(size_t i);
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeleteStatementContext* deleteStatement();

  class  DeleteTargetContext : public antlr4::ParserRuleContext {
  public:
    DeleteTargetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CssPropertyNameContext *cssPropertyName();
    ElementNameContext *elementName();
    ElementIndexContext *elementIndex();
    TemplateTypeContext *templateType();
    TemplateNameContext *templateName();
    CustomTypeContext *customType();
    CustomNameContext *customName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeleteTargetContext* deleteTarget();

  class  ElementIndexContext : public antlr4::ParserRuleContext {
  public:
    ElementIndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *RBRACKET();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementIndexContext* elementIndex();

  class  InsertStatementContext : public antlr4::ParserRuleContext {
  public:
    InsertStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    InsertPositionContext *insertPosition();
    InsertTargetContext *insertTarget();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<InsertContentContext *> insertContent();
    InsertContentContext* insertContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertStatementContext* insertStatement();

  class  InsertPositionContext : public antlr4::ParserRuleContext {
  public:
    InsertPositionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AFTER();
    antlr4::tree::TerminalNode *BEFORE();
    antlr4::tree::TerminalNode *REPLACE();
    antlr4::tree::TerminalNode *AT();
    antlr4::tree::TerminalNode *TOP();
    antlr4::tree::TerminalNode *BOTTOM();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertPositionContext* insertPosition();

  class  InsertTargetContext : public antlr4::ParserRuleContext {
  public:
    InsertTargetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementNameContext *elementName();
    ElementIndexContext *elementIndex();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertTargetContext* insertTarget();

  class  InsertContentContext : public antlr4::ParserRuleContext {
  public:
    InsertContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementContext *element();
    TemplateUsageContext *templateUsage();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertContentContext* insertContent();

  class  ExceptStatementContext : public antlr4::ParserRuleContext {
  public:
    ExceptStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXCEPT();
    std::vector<ExceptTargetContext *> exceptTarget();
    ExceptTargetContext* exceptTarget(size_t i);
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExceptStatementContext* exceptStatement();

  class  ExceptTargetContext : public antlr4::ParserRuleContext {
  public:
    ExceptTargetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementNameContext *elementName();
    TemplateTypeContext *templateType();
    TemplateNameContext *templateName();
    CustomTypeContext *customType();
    CustomNameContext *customName();
    antlr4::tree::TerminalNode *AT_HTML();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *CUSTOM();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *TEMPLATE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExceptTargetContext* exceptTarget();

  class  OriginBlockContext : public antlr4::ParserRuleContext {
  public:
    OriginBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *ORIGIN();
    antlr4::tree::TerminalNode *RBRACKET();
    OriginTypeContext *originType();
    OriginBodyContext *originBody();
    OriginNameContext *originName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OriginBlockContext* originBlock();

  class  OriginTypeContext : public antlr4::ParserRuleContext {
  public:
    OriginTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT_HTML();
    antlr4::tree::TerminalNode *AT_STYLE();
    antlr4::tree::TerminalNode *AT_JAVASCRIPT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OriginTypeContext* originType();

  class  OriginNameContext : public antlr4::ParserRuleContext {
  public:
    OriginNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OriginNameContext* originName();

  class  OriginBodyContext : public antlr4::ParserRuleContext {
  public:
    OriginBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    RawContentContext *rawContent();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OriginBodyContext* originBody();

  class  RawContentContext : public antlr4::ParserRuleContext {
  public:
    RawContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> RBRACE();
    antlr4::tree::TerminalNode* RBRACE(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RawContentContext* rawContent();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *RBRACKET();
    ImportContentContext *importContent();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportStatementContext* importStatement();

  class  ImportContentContext : public antlr4::ParserRuleContext {
  public:
    ImportContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportHtmlContext *importHtml();
    ImportCssContext *importCss();
    ImportJsContext *importJs();
    ImportChtlContext *importChtl();
    ImportCustomContext *importCustom();
    ImportTemplateContext *importTemplate();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportContentContext* importContent();

  class  ImportHtmlContext : public antlr4::ParserRuleContext {
  public:
    ImportHtmlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT_HTML();
    antlr4::tree::TerminalNode *FROM();
    FilePathContext *filePath();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportHtmlContext* importHtml();

  class  ImportCssContext : public antlr4::ParserRuleContext {
  public:
    ImportCssContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT_STYLE();
    antlr4::tree::TerminalNode *FROM();
    FilePathContext *filePath();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportCssContext* importCss();

  class  ImportJsContext : public antlr4::ParserRuleContext {
  public:
    ImportJsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT_JAVASCRIPT();
    antlr4::tree::TerminalNode *FROM();
    FilePathContext *filePath();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportJsContext* importJs();

  class  ImportChtlContext : public antlr4::ParserRuleContext {
  public:
    ImportChtlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT_CHTL();
    antlr4::tree::TerminalNode *FROM();
    FilePathContext *filePath();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportChtlContext* importChtl();

  class  ImportCustomContext : public antlr4::ParserRuleContext {
  public:
    ImportCustomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *CUSTOM();
    antlr4::tree::TerminalNode *RBRACKET();
    CustomTypeContext *customType();
    CustomNameContext *customName();
    antlr4::tree::TerminalNode *FROM();
    FilePathContext *filePath();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportCustomContext* importCustom();

  class  ImportTemplateContext : public antlr4::ParserRuleContext {
  public:
    ImportTemplateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *TEMPLATE();
    antlr4::tree::TerminalNode *RBRACKET();
    TemplateTypeContext *templateType();
    TemplateNameContext *templateName();
    antlr4::tree::TerminalNode *FROM();
    FilePathContext *filePath();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportTemplateContext* importTemplate();

  class  FilePathContext : public antlr4::ParserRuleContext {
  public:
    FilePathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FilePathContext* filePath();

  class  NamespaceDeclarationContext : public antlr4::ParserRuleContext {
  public:
    NamespaceDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *NAMESPACE();
    antlr4::tree::TerminalNode *RBRACKET();
    NamespaceNameContext *namespaceName();
    NamespaceBodyContext *namespaceBody();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<NamespaceContentContext *> namespaceContent();
    NamespaceContentContext* namespaceContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceDeclarationContext* namespaceDeclaration();

  class  NamespaceNameContext : public antlr4::ParserRuleContext {
  public:
    NamespaceNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceNameContext* namespaceName();

  class  NamespaceBodyContext : public antlr4::ParserRuleContext {
  public:
    NamespaceBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<NamespaceContentContext *> namespaceContent();
    NamespaceContentContext* namespaceContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceBodyContext* namespaceBody();

  class  NamespaceContentContext : public antlr4::ParserRuleContext {
  public:
    NamespaceContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NamespaceDeclarationContext *namespaceDeclaration();
    TemplateDeclarationContext *templateDeclaration();
    CustomDeclarationContext *customDeclaration();
    ExceptStatementContext *exceptStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceContentContext* namespaceContent();

  class  ConfigurationBlockContext : public antlr4::ParserRuleContext {
  public:
    ConfigurationBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *CONFIGURATION();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<ConfigContentContext *> configContent();
    ConfigContentContext* configContent(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConfigurationBlockContext* configurationBlock();

  class  ConfigContentContext : public antlr4::ParserRuleContext {
  public:
    ConfigContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConfigAssignmentContext *configAssignment();
    NameBlockContext *nameBlock();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConfigContentContext* configContent();

  class  ConfigAssignmentContext : public antlr4::ParserRuleContext {
  public:
    ConfigAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUALS();
    ConfigValueContext *configValue();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConfigAssignmentContext* configAssignment();

  class  ConfigValueContext : public antlr4::ParserRuleContext {
  public:
    ConfigValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *BOOLEAN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConfigValueContext* configValue();

  class  NameBlockContext : public antlr4::ParserRuleContext {
  public:
    NameBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *NAME();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<NameAssignmentContext *> nameAssignment();
    NameAssignmentContext* nameAssignment(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameBlockContext* nameBlock();

  class  NameAssignmentContext : public antlr4::ParserRuleContext {
  public:
    NameAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUALS();
    std::vector<StringLiteralContext *> stringLiteral();
    StringLiteralContext* stringLiteral(size_t i);
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameAssignmentContext* nameAssignment();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

