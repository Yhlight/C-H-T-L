
// Generated from CHTLJavaScript.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLJavaScriptParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, T__57 = 58, T__58 = 59, T__59 = 60, T__60 = 61, T__61 = 62, 
    T__62 = 63, T__63 = 64, T__64 = 65, T__65 = 66, T__66 = 67, T__67 = 68, 
    T__68 = 69, T__69 = 70, T__70 = 71, T__71 = 72, T__72 = 73, T__73 = 74, 
    T__74 = 75, T__75 = 76, T__76 = 77, T__77 = 78, T__78 = 79, T__79 = 80, 
    T__80 = 81, T__81 = 82, T__82 = 83, T__83 = 84, T__84 = 85, T__85 = 86, 
    T__86 = 87, T__87 = 88, T__88 = 89, T__89 = 90, T__90 = 91, T__91 = 92, 
    T__92 = 93, T__93 = 94, T__94 = 95, T__95 = 96, T__96 = 97, T__97 = 98, 
    T__98 = 99, T__99 = 100, T__100 = 101, T__101 = 102, T__102 = 103, T__103 = 104, 
    T__104 = 105, T__105 = 106, T__106 = 107, T__107 = 108, T__108 = 109, 
    T__109 = 110, T__110 = 111, T__111 = 112, T__112 = 113, T__113 = 114, 
    T__114 = 115, T__115 = 116, T__116 = 117, T__117 = 118, T__118 = 119, 
    T__119 = 120, T__120 = 121, T__121 = 122, T__122 = 123, T__123 = 124, 
    T__124 = 125, T__125 = 126, T__126 = 127, T__127 = 128, T__128 = 129, 
    ARROW = 130, NUMBER = 131, IDENTIFIER = 132, STRING_LITERAL = 133, WS = 134, 
    DECIMAL_LITERAL = 135, BINARY_LITERAL = 136, OCTAL_LITERAL = 137, HEX_LITERAL = 138, 
    TEMPLATE_STRING_LITERAL = 139, TEMPLATE_STRING_START = 140, TEMPLATE_STRING_MIDDLE = 141, 
    TEMPLATE_STRING_END = 142, REGEX_LITERAL = 143, SINGLE_LINE_COMMENT = 144, 
    MULTI_LINE_COMMENT = 145, LINE_TERMINATOR = 146
  };

  enum {
    RulePrimaryExpression = 0, RuleChtlSelector = 1, RuleSelectorExpression = 2, 
    RuleSelectorIdentifier = 3, RuleSelectorIndex = 4, RuleComplexSelector = 5, 
    RuleSelectorPart = 6, RuleMemberExpression = 7, RuleCallExpression = 8, 
    RuleAnimateCall = 9, RuleListenConfig = 10, RuleEventHandlerList = 11, 
    RuleEventHandler = 12, RuleDelegateConfig = 13, RuleDelegateProperty = 14, 
    RuleSelectorArray = 15, RuleAnimateConfig = 16, RuleAnimateProperty = 17, 
    RuleCssBlock = 18, RuleCssProperty = 19, RulePropertyName = 20, RulePropertyValue = 21, 
    RuleCssFunction = 22, RuleCssFunctionArguments = 23, RuleWhenArray = 24, 
    RuleWhenItem = 25, RuleWhenProperty = 26, RuleProgram = 27, RuleSourceElements = 28, 
    RuleSourceElement = 29, RuleDeclaration = 30, RuleHoistableDeclaration = 31, 
    RuleFunctionDeclaration = 32, RuleGeneratorDeclaration = 33, RuleAsyncFunctionDeclaration = 34, 
    RuleAsyncGeneratorDeclaration = 35, RuleClassDeclaration = 36, RuleClassExtends = 37, 
    RuleClassBody = 38, RuleClassElement = 39, RuleMethodDefinition = 40, 
    RuleFieldDefinition = 41, RuleLexicalDeclaration = 42, RuleLetOrConst = 43, 
    RuleBindingList = 44, RuleLexicalBinding = 45, RuleStatement = 46, RuleBlockStatement = 47, 
    RuleStatementList = 48, RuleVariableStatement = 49, RuleVariableDeclarationList = 50, 
    RuleVariableDeclaration = 51, RuleEmptyStatement = 52, RuleExpressionStatement = 53, 
    RuleIfStatement = 54, RuleIterationStatement = 55, RuleDoWhileStatement = 56, 
    RuleWhileStatement = 57, RuleForStatement = 58, RuleForInit = 59, RuleForInStatement = 60, 
    RuleForOfStatement = 61, RuleForInBinding = 62, RuleContinueStatement = 63, 
    RuleBreakStatement = 64, RuleReturnStatement = 65, RuleWithStatement = 66, 
    RuleLabelledStatement = 67, RuleSwitchStatement = 68, RuleCaseClause = 69, 
    RuleDefaultClause = 70, RuleThrowStatement = 71, RuleTryStatement = 72, 
    RuleCatchClause = 73, RuleCatchParameter = 74, RuleFinallyClause = 75, 
    RuleDebuggerStatement = 76, RuleImportStatement = 77, RuleImportClause = 78, 
    RuleImportedDefaultBinding = 79, RuleNamespaceImport = 80, RuleNamedImports = 81, 
    RuleImportsList = 82, RuleImportSpecifier = 83, RuleModuleSpecifier = 84, 
    RuleExportStatement = 85, RuleExportClause = 86, RuleExportsList = 87, 
    RuleExportSpecifier = 88, RuleExpression = 89, RuleAssignmentExpression = 90, 
    RuleAssignmentOperator = 91, RuleConditionalExpression = 92, RuleCoalesceExpression = 93, 
    RuleLogicalORExpression = 94, RuleLogicalANDExpression = 95, RuleBitwiseORExpression = 96, 
    RuleBitwiseXORExpression = 97, RuleBitwiseANDExpression = 98, RuleEqualityExpression = 99, 
    RuleRelationalExpression = 100, RuleShiftExpression = 101, RuleAdditiveExpression = 102, 
    RuleMultiplicativeExpression = 103, RuleExponentiationExpression = 104, 
    RuleUnaryExpression = 105, RuleUpdateExpression = 106, RuleLeftHandSideExpression = 107, 
    RuleNewExpression = 108, RuleSuperCall = 109, RuleImportCall = 110, 
    RuleArguments = 111, RuleArgumentList = 112, RuleArgument = 113, RuleMetaProperty = 114, 
    RuleParenthesizedExpression = 115, RuleLiteral = 116, RuleNullLiteral = 117, 
    RuleBooleanLiteral = 118, RuleNumericLiteral = 119, RuleStringLiteral = 120, 
    RuleArrayLiteral = 121, RuleElementList = 122, RuleArrayElement = 123, 
    RuleObjectLiteral = 124, RulePropertyDefinitionList = 125, RulePropertyDefinition = 126, 
    RuleFunctionExpression = 127, RuleGeneratorExpression = 128, RuleAsyncFunctionExpression = 129, 
    RuleAsyncGeneratorExpression = 130, RuleClassExpression = 131, RuleArrowFunction = 132, 
    RuleAsyncArrowFunction = 133, RuleArrowParameters = 134, RuleArrowBody = 135, 
    RuleYieldExpression = 136, RuleTemplateLiteral = 137, RuleTemplateSpans = 138, 
    RuleTemplateSpan = 139, RuleTemplateMiddle = 140, RuleRegularExpressionLiteral = 141, 
    RuleFormalParameterList = 142, RuleFormalParameter = 143, RuleRestParameter = 144, 
    RuleBindingElement = 145, RuleBindingPattern = 146, RuleObjectBindingPattern = 147, 
    RuleBindingPropertyList = 148, RuleBindingProperty = 149, RuleArrayBindingPattern = 150, 
    RuleBindingElementList = 151, RuleBindingElision = 152, RuleFunctionBody = 153, 
    RuleInitializer = 154, RuleBindingIdentifier = 155, RuleIdentifier = 156, 
    RuleIdentifierName = 157, RuleReservedWord = 158, RuleKeyword = 159, 
    RuleFutureReservedWord = 160
  };

  explicit CHTLJavaScriptParser(antlr4::TokenStream *input);

  CHTLJavaScriptParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CHTLJavaScriptParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class PrimaryExpressionContext;
  class ChtlSelectorContext;
  class SelectorExpressionContext;
  class SelectorIdentifierContext;
  class SelectorIndexContext;
  class ComplexSelectorContext;
  class SelectorPartContext;
  class MemberExpressionContext;
  class CallExpressionContext;
  class AnimateCallContext;
  class ListenConfigContext;
  class EventHandlerListContext;
  class EventHandlerContext;
  class DelegateConfigContext;
  class DelegatePropertyContext;
  class SelectorArrayContext;
  class AnimateConfigContext;
  class AnimatePropertyContext;
  class CssBlockContext;
  class CssPropertyContext;
  class PropertyNameContext;
  class PropertyValueContext;
  class CssFunctionContext;
  class CssFunctionArgumentsContext;
  class WhenArrayContext;
  class WhenItemContext;
  class WhenPropertyContext;
  class ProgramContext;
  class SourceElementsContext;
  class SourceElementContext;
  class DeclarationContext;
  class HoistableDeclarationContext;
  class FunctionDeclarationContext;
  class GeneratorDeclarationContext;
  class AsyncFunctionDeclarationContext;
  class AsyncGeneratorDeclarationContext;
  class ClassDeclarationContext;
  class ClassExtendsContext;
  class ClassBodyContext;
  class ClassElementContext;
  class MethodDefinitionContext;
  class FieldDefinitionContext;
  class LexicalDeclarationContext;
  class LetOrConstContext;
  class BindingListContext;
  class LexicalBindingContext;
  class StatementContext;
  class BlockStatementContext;
  class StatementListContext;
  class VariableStatementContext;
  class VariableDeclarationListContext;
  class VariableDeclarationContext;
  class EmptyStatementContext;
  class ExpressionStatementContext;
  class IfStatementContext;
  class IterationStatementContext;
  class DoWhileStatementContext;
  class WhileStatementContext;
  class ForStatementContext;
  class ForInitContext;
  class ForInStatementContext;
  class ForOfStatementContext;
  class ForInBindingContext;
  class ContinueStatementContext;
  class BreakStatementContext;
  class ReturnStatementContext;
  class WithStatementContext;
  class LabelledStatementContext;
  class SwitchStatementContext;
  class CaseClauseContext;
  class DefaultClauseContext;
  class ThrowStatementContext;
  class TryStatementContext;
  class CatchClauseContext;
  class CatchParameterContext;
  class FinallyClauseContext;
  class DebuggerStatementContext;
  class ImportStatementContext;
  class ImportClauseContext;
  class ImportedDefaultBindingContext;
  class NamespaceImportContext;
  class NamedImportsContext;
  class ImportsListContext;
  class ImportSpecifierContext;
  class ModuleSpecifierContext;
  class ExportStatementContext;
  class ExportClauseContext;
  class ExportsListContext;
  class ExportSpecifierContext;
  class ExpressionContext;
  class AssignmentExpressionContext;
  class AssignmentOperatorContext;
  class ConditionalExpressionContext;
  class CoalesceExpressionContext;
  class LogicalORExpressionContext;
  class LogicalANDExpressionContext;
  class BitwiseORExpressionContext;
  class BitwiseXORExpressionContext;
  class BitwiseANDExpressionContext;
  class EqualityExpressionContext;
  class RelationalExpressionContext;
  class ShiftExpressionContext;
  class AdditiveExpressionContext;
  class MultiplicativeExpressionContext;
  class ExponentiationExpressionContext;
  class UnaryExpressionContext;
  class UpdateExpressionContext;
  class LeftHandSideExpressionContext;
  class NewExpressionContext;
  class SuperCallContext;
  class ImportCallContext;
  class ArgumentsContext;
  class ArgumentListContext;
  class ArgumentContext;
  class MetaPropertyContext;
  class ParenthesizedExpressionContext;
  class LiteralContext;
  class NullLiteralContext;
  class BooleanLiteralContext;
  class NumericLiteralContext;
  class StringLiteralContext;
  class ArrayLiteralContext;
  class ElementListContext;
  class ArrayElementContext;
  class ObjectLiteralContext;
  class PropertyDefinitionListContext;
  class PropertyDefinitionContext;
  class FunctionExpressionContext;
  class GeneratorExpressionContext;
  class AsyncFunctionExpressionContext;
  class AsyncGeneratorExpressionContext;
  class ClassExpressionContext;
  class ArrowFunctionContext;
  class AsyncArrowFunctionContext;
  class ArrowParametersContext;
  class ArrowBodyContext;
  class YieldExpressionContext;
  class TemplateLiteralContext;
  class TemplateSpansContext;
  class TemplateSpanContext;
  class TemplateMiddleContext;
  class RegularExpressionLiteralContext;
  class FormalParameterListContext;
  class FormalParameterContext;
  class RestParameterContext;
  class BindingElementContext;
  class BindingPatternContext;
  class ObjectBindingPatternContext;
  class BindingPropertyListContext;
  class BindingPropertyContext;
  class ArrayBindingPatternContext;
  class BindingElementListContext;
  class BindingElisionContext;
  class FunctionBodyContext;
  class InitializerContext;
  class BindingIdentifierContext;
  class IdentifierContext;
  class IdentifierNameContext;
  class ReservedWordContext;
  class KeywordContext;
  class FutureReservedWordContext; 

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    LiteralContext *literal();
    ArrayLiteralContext *arrayLiteral();
    ObjectLiteralContext *objectLiteral();
    FunctionExpressionContext *functionExpression();
    ClassExpressionContext *classExpression();
    GeneratorExpressionContext *generatorExpression();
    AsyncFunctionExpressionContext *asyncFunctionExpression();
    AsyncGeneratorExpressionContext *asyncGeneratorExpression();
    RegularExpressionLiteralContext *regularExpressionLiteral();
    TemplateLiteralContext *templateLiteral();
    ParenthesizedExpressionContext *parenthesizedExpression();
    ChtlSelectorContext *chtlSelector();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  ChtlSelectorContext : public antlr4::ParserRuleContext {
  public:
    ChtlSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectorExpressionContext *selectorExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChtlSelectorContext* chtlSelector();

  class  SelectorExpressionContext : public antlr4::ParserRuleContext {
  public:
    SelectorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectorIdentifierContext *selectorIdentifier();
    SelectorIndexContext *selectorIndex();
    ComplexSelectorContext *complexSelector();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectorExpressionContext* selectorExpression();

  class  SelectorIdentifierContext : public antlr4::ParserRuleContext {
  public:
    SelectorIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectorIdentifierContext* selectorIdentifier();

  class  SelectorIndexContext : public antlr4::ParserRuleContext {
  public:
    SelectorIndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectorIndexContext* selectorIndex();

  class  ComplexSelectorContext : public antlr4::ParserRuleContext {
  public:
    ComplexSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SelectorPartContext *> selectorPart();
    SelectorPartContext* selectorPart(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComplexSelectorContext* complexSelector();

  class  SelectorPartContext : public antlr4::ParserRuleContext {
  public:
    SelectorPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectorIdentifierContext *selectorIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectorPartContext* selectorPart();

  class  MemberExpressionContext : public antlr4::ParserRuleContext {
  public:
    MemberExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExpressionContext *primaryExpression();
    ExpressionContext *expression();
    IdentifierNameContext *identifierName();
    MetaPropertyContext *metaProperty();
    MemberExpressionContext *memberExpression();
    ArgumentsContext *arguments();
    antlr4::tree::TerminalNode *ARROW();
    TemplateLiteralContext *templateLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MemberExpressionContext* memberExpression();
  MemberExpressionContext* memberExpression(int precedence);
  class  CallExpressionContext : public antlr4::ParserRuleContext {
  public:
    CallExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MemberExpressionContext *memberExpression();
    ArgumentsContext *arguments();
    SuperCallContext *superCall();
    ImportCallContext *importCall();
    AnimateCallContext *animateCall();
    CallExpressionContext *callExpression();
    ExpressionContext *expression();
    IdentifierNameContext *identifierName();
    antlr4::tree::TerminalNode *ARROW();
    TemplateLiteralContext *templateLiteral();
    ListenConfigContext *listenConfig();
    DelegateConfigContext *delegateConfig();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CallExpressionContext* callExpression();
  CallExpressionContext* callExpression(int precedence);
  class  AnimateCallContext : public antlr4::ParserRuleContext {
  public:
    AnimateCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnimateConfigContext *animateConfig();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AnimateCallContext* animateCall();

  class  ListenConfigContext : public antlr4::ParserRuleContext {
  public:
    ListenConfigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EventHandlerListContext *eventHandlerList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ListenConfigContext* listenConfig();

  class  EventHandlerListContext : public antlr4::ParserRuleContext {
  public:
    EventHandlerListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EventHandlerContext *> eventHandler();
    EventHandlerContext* eventHandler(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EventHandlerListContext* eventHandlerList();

  class  EventHandlerContext : public antlr4::ParserRuleContext {
  public:
    EventHandlerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    AssignmentExpressionContext *assignmentExpression();
    ArrowFunctionContext *arrowFunction();
    FunctionExpressionContext *functionExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EventHandlerContext* eventHandler();

  class  DelegateConfigContext : public antlr4::ParserRuleContext {
  public:
    DelegateConfigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DelegatePropertyContext *> delegateProperty();
    DelegatePropertyContext* delegateProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DelegateConfigContext* delegateConfig();

  class  DelegatePropertyContext : public antlr4::ParserRuleContext {
  public:
    DelegatePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlSelectorContext *chtlSelector();
    SelectorArrayContext *selectorArray();
    EventHandlerContext *eventHandler();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DelegatePropertyContext* delegateProperty();

  class  SelectorArrayContext : public antlr4::ParserRuleContext {
  public:
    SelectorArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ChtlSelectorContext *> chtlSelector();
    ChtlSelectorContext* chtlSelector(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectorArrayContext* selectorArray();

  class  AnimateConfigContext : public antlr4::ParserRuleContext {
  public:
    AnimateConfigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AnimatePropertyContext *> animateProperty();
    AnimatePropertyContext* animateProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AnimateConfigContext* animateConfig();

  class  AnimatePropertyContext : public antlr4::ParserRuleContext {
  public:
    AnimatePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    CssBlockContext *cssBlock();
    WhenArrayContext *whenArray();
    AssignmentExpressionContext *assignmentExpression();
    ArrowFunctionContext *arrowFunction();
    FunctionExpressionContext *functionExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AnimatePropertyContext* animateProperty();

  class  CssBlockContext : public antlr4::ParserRuleContext {
  public:
    CssBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CssPropertyContext *> cssProperty();
    CssPropertyContext* cssProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssBlockContext* cssBlock();

  class  CssPropertyContext : public antlr4::ParserRuleContext {
  public:
    CssPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyNameContext *propertyName();
    PropertyValueContext *propertyValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssPropertyContext* cssProperty();

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
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *IDENTIFIER();
    CssFunctionContext *cssFunction();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyValueContext* propertyValue();

  class  CssFunctionContext : public antlr4::ParserRuleContext {
  public:
    CssFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    CssFunctionArgumentsContext *cssFunctionArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssFunctionContext* cssFunction();

  class  CssFunctionArgumentsContext : public antlr4::ParserRuleContext {
  public:
    CssFunctionArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PropertyValueContext *> propertyValue();
    PropertyValueContext* propertyValue(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssFunctionArgumentsContext* cssFunctionArguments();

  class  WhenArrayContext : public antlr4::ParserRuleContext {
  public:
    WhenArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WhenItemContext *> whenItem();
    WhenItemContext* whenItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WhenArrayContext* whenArray();

  class  WhenItemContext : public antlr4::ParserRuleContext {
  public:
    WhenItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WhenPropertyContext *> whenProperty();
    WhenPropertyContext* whenProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WhenItemContext* whenItem();

  class  WhenPropertyContext : public antlr4::ParserRuleContext {
  public:
    WhenPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    CssPropertyContext *cssProperty();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WhenPropertyContext* whenProperty();

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    SourceElementsContext *sourceElements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  SourceElementsContext : public antlr4::ParserRuleContext {
  public:
    SourceElementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SourceElementContext *> sourceElement();
    SourceElementContext* sourceElement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SourceElementsContext* sourceElements();

  class  SourceElementContext : public antlr4::ParserRuleContext {
  public:
    SourceElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    DeclarationContext *declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SourceElementContext* sourceElement();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    HoistableDeclarationContext *hoistableDeclaration();
    ClassDeclarationContext *classDeclaration();
    LexicalDeclarationContext *lexicalDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclarationContext* declaration();

  class  HoistableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    HoistableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDeclarationContext *functionDeclaration();
    GeneratorDeclarationContext *generatorDeclaration();
    AsyncFunctionDeclarationContext *asyncFunctionDeclaration();
    AsyncGeneratorDeclarationContext *asyncGeneratorDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HoistableDeclarationContext* hoistableDeclaration();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    FunctionBodyContext *functionBody();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  GeneratorDeclarationContext : public antlr4::ParserRuleContext {
  public:
    GeneratorDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    FunctionBodyContext *functionBody();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GeneratorDeclarationContext* generatorDeclaration();

  class  AsyncFunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    AsyncFunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    FunctionBodyContext *functionBody();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AsyncFunctionDeclarationContext* asyncFunctionDeclaration();

  class  AsyncGeneratorDeclarationContext : public antlr4::ParserRuleContext {
  public:
    AsyncGeneratorDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    FunctionBodyContext *functionBody();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AsyncGeneratorDeclarationContext* asyncGeneratorDeclaration();

  class  ClassDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ClassDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    ClassBodyContext *classBody();
    ClassExtendsContext *classExtends();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassDeclarationContext* classDeclaration();

  class  ClassExtendsContext : public antlr4::ParserRuleContext {
  public:
    ClassExtendsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LeftHandSideExpressionContext *leftHandSideExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassExtendsContext* classExtends();

  class  ClassBodyContext : public antlr4::ParserRuleContext {
  public:
    ClassBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ClassElementContext *> classElement();
    ClassElementContext* classElement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassBodyContext* classBody();

  class  ClassElementContext : public antlr4::ParserRuleContext {
  public:
    ClassElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MethodDefinitionContext *methodDefinition();
    FieldDefinitionContext *fieldDefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassElementContext* classElement();

  class  MethodDefinitionContext : public antlr4::ParserRuleContext {
  public:
    MethodDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyNameContext *propertyName();
    FunctionBodyContext *functionBody();
    FormalParameterListContext *formalParameterList();
    FormalParameterContext *formalParameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MethodDefinitionContext* methodDefinition();

  class  FieldDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FieldDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyNameContext *propertyName();
    InitializerContext *initializer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FieldDefinitionContext* fieldDefinition();

  class  LexicalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    LexicalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LetOrConstContext *letOrConst();
    BindingListContext *bindingList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LexicalDeclarationContext* lexicalDeclaration();

  class  LetOrConstContext : public antlr4::ParserRuleContext {
  public:
    LetOrConstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LetOrConstContext* letOrConst();

  class  BindingListContext : public antlr4::ParserRuleContext {
  public:
    BindingListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LexicalBindingContext *> lexicalBinding();
    LexicalBindingContext* lexicalBinding(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingListContext* bindingList();

  class  LexicalBindingContext : public antlr4::ParserRuleContext {
  public:
    LexicalBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    InitializerContext *initializer();
    BindingPatternContext *bindingPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LexicalBindingContext* lexicalBinding();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockStatementContext *blockStatement();
    VariableStatementContext *variableStatement();
    EmptyStatementContext *emptyStatement();
    ExpressionStatementContext *expressionStatement();
    IfStatementContext *ifStatement();
    IterationStatementContext *iterationStatement();
    ContinueStatementContext *continueStatement();
    BreakStatementContext *breakStatement();
    ReturnStatementContext *returnStatement();
    WithStatementContext *withStatement();
    LabelledStatementContext *labelledStatement();
    SwitchStatementContext *switchStatement();
    ThrowStatementContext *throwStatement();
    TryStatementContext *tryStatement();
    DebuggerStatementContext *debuggerStatement();
    ImportStatementContext *importStatement();
    ExportStatementContext *exportStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  BlockStatementContext : public antlr4::ParserRuleContext {
  public:
    BlockStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementListContext *statementList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BlockStatementContext* blockStatement();

  class  StatementListContext : public antlr4::ParserRuleContext {
  public:
    StatementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementListContext* statementList();

  class  VariableStatementContext : public antlr4::ParserRuleContext {
  public:
    VariableStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclarationListContext *variableDeclarationList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableStatementContext* variableStatement();

  class  VariableDeclarationListContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDeclarationListContext* variableDeclarationList();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    InitializerContext *initializer();
    BindingPatternContext *bindingPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  EmptyStatementContext : public antlr4::ParserRuleContext {
  public:
    EmptyStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EmptyStatementContext* emptyStatement();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfStatementContext* ifStatement();

  class  IterationStatementContext : public antlr4::ParserRuleContext {
  public:
    IterationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DoWhileStatementContext *doWhileStatement();
    WhileStatementContext *whileStatement();
    ForStatementContext *forStatement();
    ForInStatementContext *forInStatement();
    ForOfStatementContext *forOfStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IterationStatementContext* iterationStatement();

  class  DoWhileStatementContext : public antlr4::ParserRuleContext {
  public:
    DoWhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DoWhileStatementContext* doWhileStatement();

  class  WhileStatementContext : public antlr4::ParserRuleContext {
  public:
    WhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WhileStatementContext* whileStatement();

  class  ForStatementContext : public antlr4::ParserRuleContext {
  public:
    ForStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    ForInitContext *forInit();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForStatementContext* forStatement();

  class  ForInitContext : public antlr4::ParserRuleContext {
  public:
    ForInitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    VariableDeclarationListContext *variableDeclarationList();
    LexicalDeclarationContext *lexicalDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForInitContext* forInit();

  class  ForInStatementContext : public antlr4::ParserRuleContext {
  public:
    ForInStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ForInBindingContext *forInBinding();
    ExpressionContext *expression();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForInStatementContext* forInStatement();

  class  ForOfStatementContext : public antlr4::ParserRuleContext {
  public:
    ForOfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ForInBindingContext *forInBinding();
    ExpressionContext *expression();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForOfStatementContext* forOfStatement();

  class  ForInBindingContext : public antlr4::ParserRuleContext {
  public:
    ForInBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    BindingPatternContext *bindingPattern();
    InitializerContext *initializer();
    LetOrConstContext *letOrConst();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForInBindingContext* forInBinding();

  class  ContinueStatementContext : public antlr4::ParserRuleContext {
  public:
    ContinueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContinueStatementContext* continueStatement();

  class  BreakStatementContext : public antlr4::ParserRuleContext {
  public:
    BreakStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BreakStatementContext* breakStatement();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  WithStatementContext : public antlr4::ParserRuleContext {
  public:
    WithStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WithStatementContext* withStatement();

  class  LabelledStatementContext : public antlr4::ParserRuleContext {
  public:
    LabelledStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LabelledStatementContext* labelledStatement();

  class  SwitchStatementContext : public antlr4::ParserRuleContext {
  public:
    SwitchStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    std::vector<CaseClauseContext *> caseClause();
    CaseClauseContext* caseClause(size_t i);
    DefaultClauseContext *defaultClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SwitchStatementContext* switchStatement();

  class  CaseClauseContext : public antlr4::ParserRuleContext {
  public:
    CaseClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    StatementListContext *statementList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CaseClauseContext* caseClause();

  class  DefaultClauseContext : public antlr4::ParserRuleContext {
  public:
    DefaultClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementListContext *statementList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DefaultClauseContext* defaultClause();

  class  ThrowStatementContext : public antlr4::ParserRuleContext {
  public:
    ThrowStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ThrowStatementContext* throwStatement();

  class  TryStatementContext : public antlr4::ParserRuleContext {
  public:
    TryStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockStatementContext *blockStatement();
    CatchClauseContext *catchClause();
    FinallyClauseContext *finallyClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TryStatementContext* tryStatement();

  class  CatchClauseContext : public antlr4::ParserRuleContext {
  public:
    CatchClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockStatementContext *blockStatement();
    CatchParameterContext *catchParameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CatchClauseContext* catchClause();

  class  CatchParameterContext : public antlr4::ParserRuleContext {
  public:
    CatchParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    BindingPatternContext *bindingPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CatchParameterContext* catchParameter();

  class  FinallyClauseContext : public antlr4::ParserRuleContext {
  public:
    FinallyClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockStatementContext *blockStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FinallyClauseContext* finallyClause();

  class  DebuggerStatementContext : public antlr4::ParserRuleContext {
  public:
    DebuggerStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DebuggerStatementContext* debuggerStatement();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportClauseContext *importClause();
    ModuleSpecifierContext *moduleSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportStatementContext* importStatement();

  class  ImportClauseContext : public antlr4::ParserRuleContext {
  public:
    ImportClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportedDefaultBindingContext *importedDefaultBinding();
    NamedImportsContext *namedImports();
    NamespaceImportContext *namespaceImport();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportClauseContext* importClause();

  class  ImportedDefaultBindingContext : public antlr4::ParserRuleContext {
  public:
    ImportedDefaultBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportedDefaultBindingContext* importedDefaultBinding();

  class  NamespaceImportContext : public antlr4::ParserRuleContext {
  public:
    NamespaceImportContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceImportContext* namespaceImport();

  class  NamedImportsContext : public antlr4::ParserRuleContext {
  public:
    NamedImportsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportsListContext *importsList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamedImportsContext* namedImports();

  class  ImportsListContext : public antlr4::ParserRuleContext {
  public:
    ImportsListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ImportSpecifierContext *> importSpecifier();
    ImportSpecifierContext* importSpecifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportsListContext* importsList();

  class  ImportSpecifierContext : public antlr4::ParserRuleContext {
  public:
    ImportSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    IdentifierNameContext *identifierName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportSpecifierContext* importSpecifier();

  class  ModuleSpecifierContext : public antlr4::ParserRuleContext {
  public:
    ModuleSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ModuleSpecifierContext* moduleSpecifier();

  class  ExportStatementContext : public antlr4::ParserRuleContext {
  public:
    ExportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExportClauseContext *exportClause();
    ModuleSpecifierContext *moduleSpecifier();
    VariableStatementContext *variableStatement();
    DeclarationContext *declaration();
    HoistableDeclarationContext *hoistableDeclaration();
    ClassDeclarationContext *classDeclaration();
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExportStatementContext* exportStatement();

  class  ExportClauseContext : public antlr4::ParserRuleContext {
  public:
    ExportClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExportsListContext *exportsList();
    IdentifierNameContext *identifierName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExportClauseContext* exportClause();

  class  ExportsListContext : public antlr4::ParserRuleContext {
  public:
    ExportsListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExportSpecifierContext *> exportSpecifier();
    ExportSpecifierContext* exportSpecifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExportsListContext* exportsList();

  class  ExportSpecifierContext : public antlr4::ParserRuleContext {
  public:
    ExportSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierNameContext *> identifierName();
    IdentifierNameContext* identifierName(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExportSpecifierContext* exportSpecifier();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssignmentExpressionContext *> assignmentExpression();
    AssignmentExpressionContext* assignmentExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();

  class  AssignmentExpressionContext : public antlr4::ParserRuleContext {
  public:
    AssignmentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionalExpressionContext *conditionalExpression();
    YieldExpressionContext *yieldExpression();
    ArrowFunctionContext *arrowFunction();
    AsyncArrowFunctionContext *asyncArrowFunction();
    LeftHandSideExpressionContext *leftHandSideExpression();
    AssignmentOperatorContext *assignmentOperator();
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssignmentExpressionContext* assignmentExpression();

  class  AssignmentOperatorContext : public antlr4::ParserRuleContext {
  public:
    AssignmentOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssignmentOperatorContext* assignmentOperator();

  class  ConditionalExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CoalesceExpressionContext *coalesceExpression();
    std::vector<AssignmentExpressionContext *> assignmentExpression();
    AssignmentExpressionContext* assignmentExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConditionalExpressionContext* conditionalExpression();

  class  CoalesceExpressionContext : public antlr4::ParserRuleContext {
  public:
    CoalesceExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicalORExpressionContext *logicalORExpression();
    CoalesceExpressionContext *coalesceExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CoalesceExpressionContext* coalesceExpression();

  class  LogicalORExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalORExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicalANDExpressionContext *> logicalANDExpression();
    LogicalANDExpressionContext* logicalANDExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicalORExpressionContext* logicalORExpression();

  class  LogicalANDExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalANDExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BitwiseORExpressionContext *> bitwiseORExpression();
    BitwiseORExpressionContext* bitwiseORExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicalANDExpressionContext* logicalANDExpression();

  class  BitwiseORExpressionContext : public antlr4::ParserRuleContext {
  public:
    BitwiseORExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BitwiseXORExpressionContext *> bitwiseXORExpression();
    BitwiseXORExpressionContext* bitwiseXORExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BitwiseORExpressionContext* bitwiseORExpression();

  class  BitwiseXORExpressionContext : public antlr4::ParserRuleContext {
  public:
    BitwiseXORExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BitwiseANDExpressionContext *> bitwiseANDExpression();
    BitwiseANDExpressionContext* bitwiseANDExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BitwiseXORExpressionContext* bitwiseXORExpression();

  class  BitwiseANDExpressionContext : public antlr4::ParserRuleContext {
  public:
    BitwiseANDExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EqualityExpressionContext *> equalityExpression();
    EqualityExpressionContext* equalityExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BitwiseANDExpressionContext* bitwiseANDExpression();

  class  EqualityExpressionContext : public antlr4::ParserRuleContext {
  public:
    EqualityExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RelationalExpressionContext *> relationalExpression();
    RelationalExpressionContext* relationalExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EqualityExpressionContext* equalityExpression();

  class  RelationalExpressionContext : public antlr4::ParserRuleContext {
  public:
    RelationalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ShiftExpressionContext *> shiftExpression();
    ShiftExpressionContext* shiftExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelationalExpressionContext* relationalExpression();

  class  ShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ShiftExpressionContext* shiftExpression();

  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AdditiveExpressionContext* additiveExpression();

  class  MultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExponentiationExpressionContext *> exponentiationExpression();
    ExponentiationExpressionContext* exponentiationExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MultiplicativeExpressionContext* multiplicativeExpression();

  class  ExponentiationExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExponentiationExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExpressionContext *unaryExpression();
    ExponentiationExpressionContext *exponentiationExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExponentiationExpressionContext* exponentiationExpression();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UpdateExpressionContext *updateExpression();
    UnaryExpressionContext *unaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  UpdateExpressionContext : public antlr4::ParserRuleContext {
  public:
    UpdateExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LeftHandSideExpressionContext *leftHandSideExpression();
    UnaryExpressionContext *unaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UpdateExpressionContext* updateExpression();

  class  LeftHandSideExpressionContext : public antlr4::ParserRuleContext {
  public:
    LeftHandSideExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NewExpressionContext *newExpression();
    CallExpressionContext *callExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LeftHandSideExpressionContext* leftHandSideExpression();

  class  NewExpressionContext : public antlr4::ParserRuleContext {
  public:
    NewExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MemberExpressionContext *memberExpression();
    NewExpressionContext *newExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NewExpressionContext* newExpression();

  class  SuperCallContext : public antlr4::ParserRuleContext {
  public:
    SuperCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgumentsContext *arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SuperCallContext* superCall();

  class  ImportCallContext : public antlr4::ParserRuleContext {
  public:
    ImportCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportCallContext* importCall();

  class  ArgumentsContext : public antlr4::ParserRuleContext {
  public:
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgumentListContext *argumentList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgumentsContext* arguments();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentContext *> argument();
    ArgumentContext* argument(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgumentListContext* argumentList();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgumentContext* argument();

  class  MetaPropertyContext : public antlr4::ParserRuleContext {
  public:
    MetaPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MetaPropertyContext* metaProperty();

  class  ParenthesizedExpressionContext : public antlr4::ParserRuleContext {
  public:
    ParenthesizedExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParenthesizedExpressionContext* parenthesizedExpression();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NullLiteralContext *nullLiteral();
    BooleanLiteralContext *booleanLiteral();
    NumericLiteralContext *numericLiteral();
    StringLiteralContext *stringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LiteralContext* literal();

  class  NullLiteralContext : public antlr4::ParserRuleContext {
  public:
    NullLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NullLiteralContext* nullLiteral();

  class  BooleanLiteralContext : public antlr4::ParserRuleContext {
  public:
    BooleanLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanLiteralContext* booleanLiteral();

  class  NumericLiteralContext : public antlr4::ParserRuleContext {
  public:
    NumericLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_LITERAL();
    antlr4::tree::TerminalNode *BINARY_LITERAL();
    antlr4::tree::TerminalNode *OCTAL_LITERAL();
    antlr4::tree::TerminalNode *HEX_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericLiteralContext* numericLiteral();

  class  StringLiteralContext : public antlr4::ParserRuleContext {
  public:
    StringLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StringLiteralContext* stringLiteral();

  class  ArrayLiteralContext : public antlr4::ParserRuleContext {
  public:
    ArrayLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementListContext *elementList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrayLiteralContext* arrayLiteral();

  class  ElementListContext : public antlr4::ParserRuleContext {
  public:
    ElementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArrayElementContext *> arrayElement();
    ArrayElementContext* arrayElement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementListContext* elementList();

  class  ArrayElementContext : public antlr4::ParserRuleContext {
  public:
    ArrayElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrayElementContext* arrayElement();

  class  ObjectLiteralContext : public antlr4::ParserRuleContext {
  public:
    ObjectLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyDefinitionListContext *propertyDefinitionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjectLiteralContext* objectLiteral();

  class  PropertyDefinitionListContext : public antlr4::ParserRuleContext {
  public:
    PropertyDefinitionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PropertyDefinitionContext *> propertyDefinition();
    PropertyDefinitionContext* propertyDefinition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyDefinitionListContext* propertyDefinitionList();

  class  PropertyDefinitionContext : public antlr4::ParserRuleContext {
  public:
    PropertyDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierNameContext *identifierName();
    PropertyNameContext *propertyName();
    AssignmentExpressionContext *assignmentExpression();
    MethodDefinitionContext *methodDefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyDefinitionContext* propertyDefinition();

  class  FunctionExpressionContext : public antlr4::ParserRuleContext {
  public:
    FunctionExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionBodyContext *functionBody();
    IdentifierContext *identifier();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionExpressionContext* functionExpression();

  class  GeneratorExpressionContext : public antlr4::ParserRuleContext {
  public:
    GeneratorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionBodyContext *functionBody();
    IdentifierContext *identifier();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GeneratorExpressionContext* generatorExpression();

  class  AsyncFunctionExpressionContext : public antlr4::ParserRuleContext {
  public:
    AsyncFunctionExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionBodyContext *functionBody();
    IdentifierContext *identifier();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AsyncFunctionExpressionContext* asyncFunctionExpression();

  class  AsyncGeneratorExpressionContext : public antlr4::ParserRuleContext {
  public:
    AsyncGeneratorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionBodyContext *functionBody();
    IdentifierContext *identifier();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AsyncGeneratorExpressionContext* asyncGeneratorExpression();

  class  ClassExpressionContext : public antlr4::ParserRuleContext {
  public:
    ClassExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassBodyContext *classBody();
    IdentifierContext *identifier();
    ClassExtendsContext *classExtends();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassExpressionContext* classExpression();

  class  ArrowFunctionContext : public antlr4::ParserRuleContext {
  public:
    ArrowFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrowParametersContext *arrowParameters();
    ArrowBodyContext *arrowBody();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrowFunctionContext* arrowFunction();

  class  AsyncArrowFunctionContext : public antlr4::ParserRuleContext {
  public:
    AsyncArrowFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrowParametersContext *arrowParameters();
    ArrowBodyContext *arrowBody();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AsyncArrowFunctionContext* asyncArrowFunction();

  class  ArrowParametersContext : public antlr4::ParserRuleContext {
  public:
    ArrowParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    FormalParameterListContext *formalParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrowParametersContext* arrowParameters();

  class  ArrowBodyContext : public antlr4::ParserRuleContext {
  public:
    ArrowBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();
    FunctionBodyContext *functionBody();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrowBodyContext* arrowBody();

  class  YieldExpressionContext : public antlr4::ParserRuleContext {
  public:
    YieldExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  YieldExpressionContext* yieldExpression();

  class  TemplateLiteralContext : public antlr4::ParserRuleContext {
  public:
    TemplateLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TemplateSpansContext *templateSpans();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateLiteralContext* templateLiteral();

  class  TemplateSpansContext : public antlr4::ParserRuleContext {
  public:
    TemplateSpansContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TemplateSpanContext *> templateSpan();
    TemplateSpanContext* templateSpan(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateSpansContext* templateSpans();

  class  TemplateSpanContext : public antlr4::ParserRuleContext {
  public:
    TemplateSpanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEMPLATE_STRING_LITERAL();
    antlr4::tree::TerminalNode *TEMPLATE_STRING_START();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *TEMPLATE_STRING_END();
    std::vector<TemplateMiddleContext *> templateMiddle();
    TemplateMiddleContext* templateMiddle(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateSpanContext* templateSpan();

  class  TemplateMiddleContext : public antlr4::ParserRuleContext {
  public:
    TemplateMiddleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEMPLATE_STRING_MIDDLE();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateMiddleContext* templateMiddle();

  class  RegularExpressionLiteralContext : public antlr4::ParserRuleContext {
  public:
    RegularExpressionLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REGEX_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RegularExpressionLiteralContext* regularExpressionLiteral();

  class  FormalParameterListContext : public antlr4::ParserRuleContext {
  public:
    FormalParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FormalParameterContext *> formalParameter();
    FormalParameterContext* formalParameter(size_t i);
    RestParameterContext *restParameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormalParameterListContext* formalParameterList();

  class  FormalParameterContext : public antlr4::ParserRuleContext {
  public:
    FormalParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingElementContext *bindingElement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormalParameterContext* formalParameter();

  class  RestParameterContext : public antlr4::ParserRuleContext {
  public:
    RestParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    BindingPatternContext *bindingPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RestParameterContext* restParameter();

  class  BindingElementContext : public antlr4::ParserRuleContext {
  public:
    BindingElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    InitializerContext *initializer();
    BindingPatternContext *bindingPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingElementContext* bindingElement();

  class  BindingPatternContext : public antlr4::ParserRuleContext {
  public:
    BindingPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ObjectBindingPatternContext *objectBindingPattern();
    ArrayBindingPatternContext *arrayBindingPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingPatternContext* bindingPattern();

  class  ObjectBindingPatternContext : public antlr4::ParserRuleContext {
  public:
    ObjectBindingPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingPropertyListContext *bindingPropertyList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjectBindingPatternContext* objectBindingPattern();

  class  BindingPropertyListContext : public antlr4::ParserRuleContext {
  public:
    BindingPropertyListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BindingPropertyContext *> bindingProperty();
    BindingPropertyContext* bindingProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingPropertyListContext* bindingPropertyList();

  class  BindingPropertyContext : public antlr4::ParserRuleContext {
  public:
    BindingPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingIdentifierContext *bindingIdentifier();
    PropertyNameContext *propertyName();
    BindingElementContext *bindingElement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingPropertyContext* bindingProperty();

  class  ArrayBindingPatternContext : public antlr4::ParserRuleContext {
  public:
    ArrayBindingPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BindingElementListContext *bindingElementList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrayBindingPatternContext* arrayBindingPattern();

  class  BindingElementListContext : public antlr4::ParserRuleContext {
  public:
    BindingElementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BindingElementContext *> bindingElement();
    BindingElementContext* bindingElement(size_t i);
    std::vector<BindingElisionContext *> bindingElision();
    BindingElisionContext* bindingElision(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingElementListContext* bindingElementList();

  class  BindingElisionContext : public antlr4::ParserRuleContext {
  public:
    BindingElisionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingElisionContext* bindingElision();

  class  FunctionBodyContext : public antlr4::ParserRuleContext {
  public:
    FunctionBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SourceElementsContext *sourceElements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionBodyContext* functionBody();

  class  InitializerContext : public antlr4::ParserRuleContext {
  public:
    InitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InitializerContext* initializer();

  class  BindingIdentifierContext : public antlr4::ParserRuleContext {
  public:
    BindingIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingIdentifierContext* bindingIdentifier();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentifierContext* identifier();

  class  IdentifierNameContext : public antlr4::ParserRuleContext {
  public:
    IdentifierNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ReservedWordContext *reservedWord();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentifierNameContext* identifierName();

  class  ReservedWordContext : public antlr4::ParserRuleContext {
  public:
    ReservedWordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    KeywordContext *keyword();
    FutureReservedWordContext *futureReservedWord();
    NullLiteralContext *nullLiteral();
    BooleanLiteralContext *booleanLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReservedWordContext* reservedWord();

  class  KeywordContext : public antlr4::ParserRuleContext {
  public:
    KeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  KeywordContext* keyword();

  class  FutureReservedWordContext : public antlr4::ParserRuleContext {
  public:
    FutureReservedWordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FutureReservedWordContext* futureReservedWord();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool memberExpressionSempred(MemberExpressionContext *_localctx, size_t predicateIndex);
  bool callExpressionSempred(CallExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

