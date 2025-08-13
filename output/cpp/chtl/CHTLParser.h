
// Generated from CHTL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    SINGLE_LINE_COMMENT = 45, MULTI_LINE_COMMENT = 46, GENERATOR_COMMENT = 47, 
    BOOLEAN = 48, NUMBER = 49, STRING_LITERAL = 50, UNQUOTED_LITERAL = 51, 
    IDENTIFIER = 52, WS = 53
  };

  enum {
    RuleProgram = 0, RuleTopLevelStatement = 1, RuleConfigurationBlock = 2, 
    RuleConfigurationItem = 3, RuleConfigKey = 4, RuleConfigValue = 5, RuleConfigValueArray = 6, 
    RuleConfigArrayItem = 7, RuleNameConfigItem = 8, RuleNamespaceDeclaration = 9, 
    RuleNamespaceBody = 10, RuleNamespaceContent = 11, RuleImportStatement = 12, 
    RuleImportType = 13, RuleImportPath = 14, RuleDottedPath = 15, RuleTemplateDeclaration = 16, 
    RuleTemplateType = 17, RuleTemplateBody = 18, RuleTemplateContent = 19, 
    RuleTemplateInheritance = 20, RuleCustomDeclaration = 21, RuleCustomType = 22, 
    RuleCustomBody = 23, RuleCustomContent = 24, RuleCustomInheritance = 25, 
    RuleCustomSpecialization = 26, RuleSpecializationContent = 27, RuleDeleteStatement = 28, 
    RuleDeleteTarget = 29, RuleInsertStatement = 30, RuleInsertPosition = 31, 
    RuleElementSelector = 32, RuleInsertContent = 33, RuleOriginBlock = 34, 
    RuleOriginType = 35, RuleOriginContent = 36, RuleHtmlElement = 37, RuleGlobalStyleElement = 38, 
    RuleGlobalStyleContent = 39, RuleElementName = 40, RuleElementIndexAccess = 41, 
    RuleElementBody = 42, RuleElementContent = 43, RuleAttribute = 44, RuleAttributeName = 45, 
    RuleAttributeValue = 46, RuleTextContent = 47, RuleStyleBlock = 48, 
    RuleStyleContent = 49, RuleStyleProperty = 50, RulePropertyName = 51, 
    RulePropertyValue = 52, RuleCssSelector = 53, RulePseudoClass = 54, 
    RulePseudoElement = 55, RuleCssFunction = 56, RuleCssArguments = 57, 
    RuleCssArgument = 58, RuleScriptBlock = 59, RuleScriptContent = 60, 
    RuleElementUsage = 61, RuleElementSpecialization = 62, RuleElementSpecializationContent = 63, 
    RuleStyleUsage = 64, RuleStyleSpecialization = 65, RuleVariableDefinition = 66, 
    RuleVariableUsage = 67, RuleVariableArguments = 68, RuleVariableArgument = 69, 
    RuleVariableAssignment = 70, RuleNamespacePath = 71, RuleExceptConstraint = 72, 
    RuleExceptTarget = 73, RuleComment = 74
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
  class TopLevelStatementContext;
  class ConfigurationBlockContext;
  class ConfigurationItemContext;
  class ConfigKeyContext;
  class ConfigValueContext;
  class ConfigValueArrayContext;
  class ConfigArrayItemContext;
  class NameConfigItemContext;
  class NamespaceDeclarationContext;
  class NamespaceBodyContext;
  class NamespaceContentContext;
  class ImportStatementContext;
  class ImportTypeContext;
  class ImportPathContext;
  class DottedPathContext;
  class TemplateDeclarationContext;
  class TemplateTypeContext;
  class TemplateBodyContext;
  class TemplateContentContext;
  class TemplateInheritanceContext;
  class CustomDeclarationContext;
  class CustomTypeContext;
  class CustomBodyContext;
  class CustomContentContext;
  class CustomInheritanceContext;
  class CustomSpecializationContext;
  class SpecializationContentContext;
  class DeleteStatementContext;
  class DeleteTargetContext;
  class InsertStatementContext;
  class InsertPositionContext;
  class ElementSelectorContext;
  class InsertContentContext;
  class OriginBlockContext;
  class OriginTypeContext;
  class OriginContentContext;
  class HtmlElementContext;
  class GlobalStyleElementContext;
  class GlobalStyleContentContext;
  class ElementNameContext;
  class ElementIndexAccessContext;
  class ElementBodyContext;
  class ElementContentContext;
  class AttributeContext;
  class AttributeNameContext;
  class AttributeValueContext;
  class TextContentContext;
  class StyleBlockContext;
  class StyleContentContext;
  class StylePropertyContext;
  class PropertyNameContext;
  class PropertyValueContext;
  class CssSelectorContext;
  class PseudoClassContext;
  class PseudoElementContext;
  class CssFunctionContext;
  class CssArgumentsContext;
  class CssArgumentContext;
  class ScriptBlockContext;
  class ScriptContentContext;
  class ElementUsageContext;
  class ElementSpecializationContext;
  class ElementSpecializationContentContext;
  class StyleUsageContext;
  class StyleSpecializationContext;
  class VariableDefinitionContext;
  class VariableUsageContext;
  class VariableArgumentsContext;
  class VariableArgumentContext;
  class VariableAssignmentContext;
  class NamespacePathContext;
  class ExceptConstraintContext;
  class ExceptTargetContext;
  class CommentContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<TopLevelStatementContext *> topLevelStatement();
    TopLevelStatementContext* topLevelStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  TopLevelStatementContext : public antlr4::ParserRuleContext {
  public:
    TopLevelStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConfigurationBlockContext *configurationBlock();
    NamespaceDeclarationContext *namespaceDeclaration();
    ImportStatementContext *importStatement();
    TemplateDeclarationContext *templateDeclaration();
    CustomDeclarationContext *customDeclaration();
    OriginBlockContext *originBlock();
    HtmlElementContext *htmlElement();
    StyleBlockContext *styleBlock();
    ScriptBlockContext *scriptBlock();
    CommentContext *comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TopLevelStatementContext* topLevelStatement();

  class  ConfigurationBlockContext : public antlr4::ParserRuleContext {
  public:
    ConfigurationBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConfigurationItemContext *> configurationItem();
    ConfigurationItemContext* configurationItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigurationBlockContext* configurationBlock();

  class  ConfigurationItemContext : public antlr4::ParserRuleContext {
  public:
    ConfigurationItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConfigKeyContext *configKey();
    ConfigValueContext *configValue();
    std::vector<NameConfigItemContext *> nameConfigItem();
    NameConfigItemContext* nameConfigItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigurationItemContext* configurationItem();

  class  ConfigKeyContext : public antlr4::ParserRuleContext {
  public:
    ConfigKeyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigKeyContext* configKey();

  class  ConfigValueContext : public antlr4::ParserRuleContext {
  public:
    ConfigValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *BOOLEAN();
    ConfigValueArrayContext *configValueArray();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigValueContext* configValue();

  class  ConfigValueArrayContext : public antlr4::ParserRuleContext {
  public:
    ConfigValueArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConfigArrayItemContext *> configArrayItem();
    ConfigArrayItemContext* configArrayItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigValueArrayContext* configValueArray();

  class  ConfigArrayItemContext : public antlr4::ParserRuleContext {
  public:
    ConfigArrayItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigArrayItemContext* configArrayItem();

  class  NameConfigItemContext : public antlr4::ParserRuleContext {
  public:
    NameConfigItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ConfigValueContext *configValue();
    ConfigValueArrayContext *configValueArray();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NameConfigItemContext* nameConfigItem();

  class  NamespaceDeclarationContext : public antlr4::ParserRuleContext {
  public:
    NamespaceDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    NamespaceBodyContext *namespaceBody();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceDeclarationContext* namespaceDeclaration();

  class  NamespaceBodyContext : public antlr4::ParserRuleContext {
  public:
    NamespaceBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NamespaceContentContext *> namespaceContent();
    NamespaceContentContext* namespaceContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceBodyContext* namespaceBody();

  class  NamespaceContentContext : public antlr4::ParserRuleContext {
  public:
    NamespaceContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NamespaceDeclarationContext *namespaceDeclaration();
    TemplateDeclarationContext *templateDeclaration();
    CustomDeclarationContext *customDeclaration();
    ExceptConstraintContext *exceptConstraint();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceContentContext* namespaceContent();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportTypeContext *importType();
    ImportPathContext *importPath();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportStatementContext* importStatement();

  class  ImportTypeContext : public antlr4::ParserRuleContext {
  public:
    ImportTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CustomTypeContext *customType();
    antlr4::tree::TerminalNode *IDENTIFIER();
    TemplateTypeContext *templateType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportTypeContext* importType();

  class  ImportPathContext : public antlr4::ParserRuleContext {
  public:
    ImportPathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    DottedPathContext *dottedPath();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportPathContext* importPath();

  class  DottedPathContext : public antlr4::ParserRuleContext {
  public:
    DottedPathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DottedPathContext* dottedPath();

  class  TemplateDeclarationContext : public antlr4::ParserRuleContext {
  public:
    TemplateDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TemplateTypeContext *templateType();
    antlr4::tree::TerminalNode *IDENTIFIER();
    TemplateBodyContext *templateBody();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateDeclarationContext* templateDeclaration();

  class  TemplateTypeContext : public antlr4::ParserRuleContext {
  public:
    TemplateTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateTypeContext* templateType();

  class  TemplateBodyContext : public antlr4::ParserRuleContext {
  public:
    TemplateBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TemplateContentContext *> templateContent();
    TemplateContentContext* templateContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateBodyContext* templateBody();

  class  TemplateContentContext : public antlr4::ParserRuleContext {
  public:
    TemplateContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StylePropertyContext *styleProperty();
    HtmlElementContext *htmlElement();
    TemplateInheritanceContext *templateInheritance();
    VariableDefinitionContext *variableDefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateContentContext* templateContent();

  class  TemplateInheritanceContext : public antlr4::ParserRuleContext {
  public:
    TemplateInheritanceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TemplateTypeContext *templateType();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateInheritanceContext* templateInheritance();

  class  CustomDeclarationContext : public antlr4::ParserRuleContext {
  public:
    CustomDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CustomTypeContext *customType();
    antlr4::tree::TerminalNode *IDENTIFIER();
    CustomBodyContext *customBody();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CustomDeclarationContext* customDeclaration();

  class  CustomTypeContext : public antlr4::ParserRuleContext {
  public:
    CustomTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CustomTypeContext* customType();

  class  CustomBodyContext : public antlr4::ParserRuleContext {
  public:
    CustomBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CustomContentContext *> customContent();
    CustomContentContext* customContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CustomBodyContext* customBody();

  class  CustomContentContext : public antlr4::ParserRuleContext {
  public:
    CustomContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StylePropertyContext *styleProperty();
    HtmlElementContext *htmlElement();
    CustomInheritanceContext *customInheritance();
    VariableDefinitionContext *variableDefinition();
    DeleteStatementContext *deleteStatement();
    InsertStatementContext *insertStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CustomContentContext* customContent();

  class  CustomInheritanceContext : public antlr4::ParserRuleContext {
  public:
    CustomInheritanceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CustomTypeContext *customType();
    antlr4::tree::TerminalNode *IDENTIFIER();
    CustomSpecializationContext *customSpecialization();
    TemplateTypeContext *templateType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CustomInheritanceContext* customInheritance();

  class  CustomSpecializationContext : public antlr4::ParserRuleContext {
  public:
    CustomSpecializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SpecializationContentContext *> specializationContent();
    SpecializationContentContext* specializationContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CustomSpecializationContext* customSpecialization();

  class  SpecializationContentContext : public antlr4::ParserRuleContext {
  public:
    SpecializationContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StylePropertyContext *styleProperty();
    DeleteStatementContext *deleteStatement();
    VariableAssignmentContext *variableAssignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SpecializationContentContext* specializationContent();

  class  DeleteStatementContext : public antlr4::ParserRuleContext {
  public:
    DeleteStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeleteTargetContext *> deleteTarget();
    DeleteTargetContext* deleteTarget(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeleteStatementContext* deleteStatement();

  class  DeleteTargetContext : public antlr4::ParserRuleContext {
  public:
    DeleteTargetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *NUMBER();
    CustomTypeContext *customType();
    TemplateTypeContext *templateType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeleteTargetContext* deleteTarget();

  class  InsertStatementContext : public antlr4::ParserRuleContext {
  public:
    InsertStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InsertPositionContext *insertPosition();
    ElementSelectorContext *elementSelector();
    std::vector<InsertContentContext *> insertContent();
    InsertContentContext* insertContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InsertStatementContext* insertStatement();

  class  InsertPositionContext : public antlr4::ParserRuleContext {
  public:
    InsertPositionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InsertPositionContext* insertPosition();

  class  ElementSelectorContext : public antlr4::ParserRuleContext {
  public:
    ElementSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementSelectorContext* elementSelector();

  class  InsertContentContext : public antlr4::ParserRuleContext {
  public:
    InsertContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    HtmlElementContext *htmlElement();
    ElementUsageContext *elementUsage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InsertContentContext* insertContent();

  class  OriginBlockContext : public antlr4::ParserRuleContext {
  public:
    OriginBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OriginTypeContext *originType();
    OriginContentContext *originContent();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OriginBlockContext* originBlock();

  class  OriginTypeContext : public antlr4::ParserRuleContext {
  public:
    OriginTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OriginTypeContext* originType();

  class  OriginContentContext : public antlr4::ParserRuleContext {
  public:
    OriginContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OriginContentContext* originContent();

  class  HtmlElementContext : public antlr4::ParserRuleContext {
  public:
    HtmlElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementNameContext *elementName();
    ElementBodyContext *elementBody();
    ElementIndexAccessContext *elementIndexAccess();
    GlobalStyleElementContext *globalStyleElement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlElementContext* htmlElement();

  class  GlobalStyleElementContext : public antlr4::ParserRuleContext {
  public:
    GlobalStyleElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GlobalStyleContentContext *globalStyleContent();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GlobalStyleElementContext* globalStyleElement();

  class  GlobalStyleContentContext : public antlr4::ParserRuleContext {
  public:
    GlobalStyleContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GlobalStyleContentContext* globalStyleContent();

  class  ElementNameContext : public antlr4::ParserRuleContext {
  public:
    ElementNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementNameContext* elementName();

  class  ElementIndexAccessContext : public antlr4::ParserRuleContext {
  public:
    ElementIndexAccessContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementIndexAccessContext* elementIndexAccess();

  class  ElementBodyContext : public antlr4::ParserRuleContext {
  public:
    ElementBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementContentContext *> elementContent();
    ElementContentContext* elementContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementBodyContext* elementBody();

  class  ElementContentContext : public antlr4::ParserRuleContext {
  public:
    ElementContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeContext *attribute();
    HtmlElementContext *htmlElement();
    StyleBlockContext *styleBlock();
    ScriptBlockContext *scriptBlock();
    TextContentContext *textContent();
    ElementUsageContext *elementUsage();
    ExceptConstraintContext *exceptConstraint();
    CommentContext *comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementContentContext* elementContent();

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeNameContext *attributeName();
    AttributeValueContext *attributeValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeContext* attribute();

  class  AttributeNameContext : public antlr4::ParserRuleContext {
  public:
    AttributeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeNameContext* attributeName();

  class  AttributeValueContext : public antlr4::ParserRuleContext {
  public:
    AttributeValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *UNQUOTED_LITERAL();
    VariableUsageContext *variableUsage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeValueContext* attributeValue();

  class  TextContentContext : public antlr4::ParserRuleContext {
  public:
    TextContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *UNQUOTED_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextContentContext* textContent();

  class  StyleBlockContext : public antlr4::ParserRuleContext {
  public:
    StyleBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StyleContentContext *> styleContent();
    StyleContentContext* styleContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StyleBlockContext* styleBlock();

  class  StyleContentContext : public antlr4::ParserRuleContext {
  public:
    StyleContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StylePropertyContext *styleProperty();
    CssSelectorContext *cssSelector();
    std::vector<StyleContentContext *> styleContent();
    StyleContentContext* styleContent(size_t i);
    StyleUsageContext *styleUsage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StyleContentContext* styleContent();

  class  StylePropertyContext : public antlr4::ParserRuleContext {
  public:
    StylePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyNameContext *propertyName();
    PropertyValueContext *propertyValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StylePropertyContext* styleProperty();

  class  PropertyNameContext : public antlr4::ParserRuleContext {
  public:
    PropertyNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyNameContext* propertyName();

  class  PropertyValueContext : public antlr4::ParserRuleContext {
  public:
    PropertyValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *UNQUOTED_LITERAL();
    VariableUsageContext *variableUsage();
    CssFunctionContext *cssFunction();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyValueContext* propertyValue();

  class  CssSelectorContext : public antlr4::ParserRuleContext {
  public:
    CssSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    PseudoClassContext *pseudoClass();
    PseudoElementContext *pseudoElement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssSelectorContext* cssSelector();

  class  PseudoClassContext : public antlr4::ParserRuleContext {
  public:
    PseudoClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PseudoClassContext* pseudoClass();

  class  PseudoElementContext : public antlr4::ParserRuleContext {
  public:
    PseudoElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PseudoElementContext* pseudoElement();

  class  CssFunctionContext : public antlr4::ParserRuleContext {
  public:
    CssFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    CssArgumentsContext *cssArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssFunctionContext* cssFunction();

  class  CssArgumentsContext : public antlr4::ParserRuleContext {
  public:
    CssArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CssArgumentContext *> cssArgument();
    CssArgumentContext* cssArgument(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssArgumentsContext* cssArguments();

  class  CssArgumentContext : public antlr4::ParserRuleContext {
  public:
    CssArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyValueContext *propertyValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssArgumentContext* cssArgument();

  class  ScriptBlockContext : public antlr4::ParserRuleContext {
  public:
    ScriptBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ScriptContentContext *scriptContent();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScriptBlockContext* scriptBlock();

  class  ScriptContentContext : public antlr4::ParserRuleContext {
  public:
    ScriptContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScriptContentContext* scriptContent();

  class  ElementUsageContext : public antlr4::ParserRuleContext {
  public:
    ElementUsageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CustomTypeContext *customType();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ElementSpecializationContext *elementSpecialization();
    NamespacePathContext *namespacePath();
    TemplateTypeContext *templateType();
    OriginTypeContext *originType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementUsageContext* elementUsage();

  class  ElementSpecializationContext : public antlr4::ParserRuleContext {
  public:
    ElementSpecializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementSpecializationContentContext *> elementSpecializationContent();
    ElementSpecializationContentContext* elementSpecializationContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementSpecializationContext* elementSpecialization();

  class  ElementSpecializationContentContext : public antlr4::ParserRuleContext {
  public:
    ElementSpecializationContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    HtmlElementContext *htmlElement();
    StyleBlockContext *styleBlock();
    DeleteStatementContext *deleteStatement();
    InsertStatementContext *insertStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementSpecializationContentContext* elementSpecializationContent();

  class  StyleUsageContext : public antlr4::ParserRuleContext {
  public:
    StyleUsageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CustomTypeContext *customType();
    antlr4::tree::TerminalNode *IDENTIFIER();
    StyleSpecializationContext *styleSpecialization();
    TemplateTypeContext *templateType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StyleUsageContext* styleUsage();

  class  StyleSpecializationContext : public antlr4::ParserRuleContext {
  public:
    StyleSpecializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StylePropertyContext *> styleProperty();
    StylePropertyContext* styleProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StyleSpecializationContext* styleSpecialization();

  class  VariableDefinitionContext : public antlr4::ParserRuleContext {
  public:
    VariableDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDefinitionContext* variableDefinition();

  class  VariableUsageContext : public antlr4::ParserRuleContext {
  public:
    VariableUsageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    VariableArgumentsContext *variableArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableUsageContext* variableUsage();

  class  VariableArgumentsContext : public antlr4::ParserRuleContext {
  public:
    VariableArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VariableArgumentContext *> variableArgument();
    VariableArgumentContext* variableArgument(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableArgumentsContext* variableArguments();

  class  VariableArgumentContext : public antlr4::ParserRuleContext {
  public:
    VariableArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    PropertyValueContext *propertyValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableArgumentContext* variableArgument();

  class  VariableAssignmentContext : public antlr4::ParserRuleContext {
  public:
    VariableAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    PropertyValueContext *propertyValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableAssignmentContext* variableAssignment();

  class  NamespacePathContext : public antlr4::ParserRuleContext {
  public:
    NamespacePathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespacePathContext* namespacePath();

  class  ExceptConstraintContext : public antlr4::ParserRuleContext {
  public:
    ExceptConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExceptTargetContext *> exceptTarget();
    ExceptTargetContext* exceptTarget(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExceptConstraintContext* exceptConstraint();

  class  ExceptTargetContext : public antlr4::ParserRuleContext {
  public:
    ExceptTargetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    CustomTypeContext *customType();
    TemplateTypeContext *templateType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExceptTargetContext* exceptTarget();

  class  CommentContext : public antlr4::ParserRuleContext {
  public:
    CommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SINGLE_LINE_COMMENT();
    antlr4::tree::TerminalNode *MULTI_LINE_COMMENT();
    antlr4::tree::TerminalNode *GENERATOR_COMMENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CommentContext* comment();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

