
// Generated from /workspace/grammar/CHTLJavaScript.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLJavaScriptParser : public antlr4::Parser {
public:
  enum {
    CHTL_ARROW = 1, CHTL_SELECTOR_START = 2, CHTL_SELECTOR_END = 3, HASH = 4, 
    AT = 5, SPACE = 6, LISTEN = 7, DELEGATE = 8, TARGET = 9, ANIMATE = 10, 
    DURATION = 11, EASING = 12, BEGIN_PROP = 13, END_PROP = 14, WHEN = 15, 
    LOOP = 16, DIRECTION = 17, DELAY = 18, CALLBACK = 19, BACKTICK = 20, 
    TEMPLATE_STRING = 21, REGEX = 22, IDENTIFIER = 23, LINE_COMMENT = 24, 
    BLOCK_COMMENT = 25, WS = 26, BREAK = 27, DO = 28, INSTANCEOF = 29, TYPEOF = 30, 
    CASE = 31, ELSE = 32, NEW = 33, VAR = 34, CATCH = 35, FINALLY = 36, 
    RETURN = 37, VOID = 38, CONTINUE = 39, FOR = 40, SWITCH = 41, WHILE = 42, 
    DEBUGGER = 43, FUNCTION = 44, THIS = 45, WITH = 46, DEFAULT = 47, IF = 48, 
    THROW = 49, DELETE = 50, IN = 51, TRY = 52, CLASS = 53, ENUM = 54, EXTENDS = 55, 
    SUPER = 56, CONST = 57, EXPORT = 58, IMPORT = 59, ASYNC = 60, AWAIT = 61, 
    YIELD = 62, LET = 63, STATIC = 64, FROM = 65, AS = 66, OF = 67, GET = 68, 
    SET = 69, NULL_ = 70, BOOLEAN = 71, UNDEFINED = 72, LPAREN = 73, RPAREN = 74, 
    LBRACE = 75, RBRACE = 76, LBRACKET = 77, RBRACKET = 78, SEMICOLON = 79, 
    COMMA = 80, DOT = 81, QUESTION = 82, COLON = 83, ELLIPSIS = 84, EQUALS = 85, 
    STAR_EQUALS = 86, SLASH_EQUALS = 87, PERCENT_EQUALS = 88, PLUS_EQUALS = 89, 
    MINUS_EQUALS = 90, LSHIFT_EQUALS = 91, RSHIFT_EQUALS = 92, URSHIFT_EQUALS = 93, 
    AMPERSAND_EQUALS = 94, CARET_EQUALS = 95, PIPE_EQUALS = 96, POWER_EQUALS = 97, 
    NULLISH_EQUALS = 98, ARROW = 99, PLUSPLUS = 100, MINUSMINUS = 101, PLUS = 102, 
    MINUS = 103, TILDE = 104, EXCLAMATION = 105, STAR = 106, SLASH = 107, 
    PERCENT = 108, POWER = 109, NULLISH_COALESCING = 110, LSHIFT = 111, 
    RSHIFT = 112, URSHIFT = 113, LT = 114, GT = 115, LE = 116, GE = 117, 
    EQUALS_OP = 118, NOT_EQUALS = 119, STRICT_EQUALS = 120, STRICT_NOT_EQUALS = 121, 
    AMPERSAND = 122, CARET = 123, PIPE = 124, AND_OP = 125, OR_OP = 126, 
    NUMBER = 127, BIGINT = 128, STRING = 129
  };

  enum {
    RuleSingleExpression = 0, RuleChtlSelectorList = 1, RuleChtlSelector = 2, 
    RuleChtlSelectorContent = 3, RuleCssSelector = 4, RuleCssSelectorPart = 5, 
    RuleListenObject = 6, RuleEventBinding = 7, RuleDelegateObject = 8, 
    RuleDelegateProperty = 9, RuleSelectorArray = 10, RuleAnimateCall = 11, 
    RuleAnimateObject = 12, RuleAnimateProperty = 13, RuleCssObject = 14, 
    RuleCssProperty = 15, RuleWhenArray = 16, RuleWhenObject = 17, RuleWhenProperty = 18, 
    RuleProgram = 19, RuleStatement = 20, RuleBlock = 21, RuleVariableStatement = 22, 
    RuleVariableDeclarationList = 23, RuleVarModifier = 24, RuleVariableDeclaration = 25, 
    RuleEmptyStatement = 26, RuleExpressionStatement = 27, RuleIfStatement = 28, 
    RuleIterationStatement = 29, RuleContinueStatement = 30, RuleBreakStatement = 31, 
    RuleReturnStatement = 32, RuleWithStatement = 33, RuleLabelledStatement = 34, 
    RuleSwitchStatement = 35, RuleCaseBlock = 36, RuleCaseClauses = 37, 
    RuleCaseClause = 38, RuleDefaultClause = 39, RuleThrowStatement = 40, 
    RuleTryStatement = 41, RuleCatchClause = 42, RuleFinallyClause = 43, 
    RuleFunctionDeclaration = 44, RuleClassDeclaration = 45, RuleClassTail = 46, 
    RuleClassElement = 47, RuleMethodDefinition = 48, RuleGetter = 49, RuleSetter = 50, 
    RuleGeneratorMethod = 51, RuleAsyncMethod = 52, RuleImportStatement = 53, 
    RuleImportFromBlock = 54, RuleImportNamespace = 55, RuleImportSpecifier = 56, 
    RuleModuleExportName = 57, RuleExportStatement = 58, RuleExportFromBlock = 59, 
    RuleExportNamespace = 60, RuleExportSpecifier = 61, RuleDeclaration = 62, 
    RuleFormalParameterList = 63, RuleFormalParameter = 64, RuleRestParameter = 65, 
    RuleAssignable = 66, RulePropertyName = 67, RuleExpressionSequence = 68, 
    RuleAssignmentOperator = 69, RuleLiteral = 70, RuleArrayLiteral = 71, 
    RuleElementList = 72, RuleArrayElement = 73, RuleObjectLiteral = 74, 
    RulePropertyAssignment = 75, RuleArguments = 76, RuleArgumentList = 77, 
    RuleArgument = 78, RuleAnonymousFunction = 79, RuleArrowFunction = 80, 
    RuleArrowFunctionParameters = 81, RuleArrowFunctionBody = 82, RuleTypeofExpression = 83, 
    RuleIdentifierName = 84, RuleReservedWord = 85, RuleKeyword = 86
  };

  explicit CHTLJavaScriptParser(antlr4::TokenStream *input);

  CHTLJavaScriptParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CHTLJavaScriptParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class SingleExpressionContext;
  class ChtlSelectorListContext;
  class ChtlSelectorContext;
  class ChtlSelectorContentContext;
  class CssSelectorContext;
  class CssSelectorPartContext;
  class ListenObjectContext;
  class EventBindingContext;
  class DelegateObjectContext;
  class DelegatePropertyContext;
  class SelectorArrayContext;
  class AnimateCallContext;
  class AnimateObjectContext;
  class AnimatePropertyContext;
  class CssObjectContext;
  class CssPropertyContext;
  class WhenArrayContext;
  class WhenObjectContext;
  class WhenPropertyContext;
  class ProgramContext;
  class StatementContext;
  class BlockContext;
  class VariableStatementContext;
  class VariableDeclarationListContext;
  class VarModifierContext;
  class VariableDeclarationContext;
  class EmptyStatementContext;
  class ExpressionStatementContext;
  class IfStatementContext;
  class IterationStatementContext;
  class ContinueStatementContext;
  class BreakStatementContext;
  class ReturnStatementContext;
  class WithStatementContext;
  class LabelledStatementContext;
  class SwitchStatementContext;
  class CaseBlockContext;
  class CaseClausesContext;
  class CaseClauseContext;
  class DefaultClauseContext;
  class ThrowStatementContext;
  class TryStatementContext;
  class CatchClauseContext;
  class FinallyClauseContext;
  class FunctionDeclarationContext;
  class ClassDeclarationContext;
  class ClassTailContext;
  class ClassElementContext;
  class MethodDefinitionContext;
  class GetterContext;
  class SetterContext;
  class GeneratorMethodContext;
  class AsyncMethodContext;
  class ImportStatementContext;
  class ImportFromBlockContext;
  class ImportNamespaceContext;
  class ImportSpecifierContext;
  class ModuleExportNameContext;
  class ExportStatementContext;
  class ExportFromBlockContext;
  class ExportNamespaceContext;
  class ExportSpecifierContext;
  class DeclarationContext;
  class FormalParameterListContext;
  class FormalParameterContext;
  class RestParameterContext;
  class AssignableContext;
  class PropertyNameContext;
  class ExpressionSequenceContext;
  class AssignmentOperatorContext;
  class LiteralContext;
  class ArrayLiteralContext;
  class ElementListContext;
  class ArrayElementContext;
  class ObjectLiteralContext;
  class PropertyAssignmentContext;
  class ArgumentsContext;
  class ArgumentListContext;
  class ArgumentContext;
  class AnonymousFunctionContext;
  class ArrowFunctionContext;
  class ArrowFunctionParametersContext;
  class ArrowFunctionBodyContext;
  class TypeofExpressionContext;
  class IdentifierNameContext;
  class ReservedWordContext;
  class KeywordContext; 

  class  SingleExpressionContext : public antlr4::ParserRuleContext {
  public:
    SingleExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlSelectorContext *chtlSelector();
    AnimateCallContext *animateCall();
    AnonymousFunctionContext *anonymousFunction();
    ArrowFunctionContext *arrowFunction();
    antlr4::tree::TerminalNode *NEW();
    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    ArgumentsContext *arguments();
    antlr4::tree::TerminalNode *DELETE();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *TYPEOF();
    antlr4::tree::TerminalNode *PLUSPLUS();
    antlr4::tree::TerminalNode *MINUSMINUS();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *TILDE();
    antlr4::tree::TerminalNode *EXCLAMATION();
    antlr4::tree::TerminalNode *AWAIT();
    antlr4::tree::TerminalNode *THIS();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SUPER();
    LiteralContext *literal();
    ArrayLiteralContext *arrayLiteral();
    ObjectLiteralContext *objectLiteral();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionSequenceContext *expressionSequence();
    antlr4::tree::TerminalNode *RPAREN();
    TypeofExpressionContext *typeofExpression();
    antlr4::tree::TerminalNode *POWER();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *PERCENT();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();
    antlr4::tree::TerminalNode *URSHIFT();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *INSTANCEOF();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *EQUALS_OP();
    antlr4::tree::TerminalNode *NOT_EQUALS();
    antlr4::tree::TerminalNode *STRICT_EQUALS();
    antlr4::tree::TerminalNode *STRICT_NOT_EQUALS();
    antlr4::tree::TerminalNode *AMPERSAND();
    antlr4::tree::TerminalNode *CARET();
    antlr4::tree::TerminalNode *PIPE();
    antlr4::tree::TerminalNode *AND_OP();
    antlr4::tree::TerminalNode *OR_OP();
    antlr4::tree::TerminalNode *NULLISH_COALESCING();
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *EQUALS();
    AssignmentOperatorContext *assignmentOperator();
    antlr4::tree::TerminalNode *CHTL_ARROW();
    IdentifierNameContext *identifierName();
    antlr4::tree::TerminalNode *LISTEN();
    ListenObjectContext *listenObject();
    antlr4::tree::TerminalNode *DELEGATE();
    DelegateObjectContext *delegateObject();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *DOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SingleExpressionContext* singleExpression();
  SingleExpressionContext* singleExpression(int precedence);
  class  ChtlSelectorListContext : public antlr4::ParserRuleContext {
  public:
    ChtlSelectorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ChtlSelectorContext *> chtlSelector();
    ChtlSelectorContext* chtlSelector(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlSelectorListContext* chtlSelectorList();

  class  ChtlSelectorContext : public antlr4::ParserRuleContext {
  public:
    ChtlSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHTL_SELECTOR_START();
    ChtlSelectorContentContext *chtlSelectorContent();
    antlr4::tree::TerminalNode *CHTL_SELECTOR_END();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlSelectorContext* chtlSelector();

  class  ChtlSelectorContentContext : public antlr4::ParserRuleContext {
  public:
    ChtlSelectorContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *HASH();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlSelectorContentContext* chtlSelectorContent();

  class  CssSelectorContext : public antlr4::ParserRuleContext {
  public:
    CssSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CssSelectorPartContext *> cssSelectorPart();
    CssSelectorPartContext* cssSelectorPart(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssSelectorContext* cssSelector();

  class  CssSelectorPartContext : public antlr4::ParserRuleContext {
  public:
    CssSelectorPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *HASH();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *SPACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssSelectorPartContext* cssSelectorPart();

  class  ListenObjectContext : public antlr4::ParserRuleContext {
  public:
    ListenObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<EventBindingContext *> eventBinding();
    EventBindingContext* eventBinding(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListenObjectContext* listenObject();

  class  EventBindingContext : public antlr4::ParserRuleContext {
  public:
    EventBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *COLON();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EventBindingContext* eventBinding();

  class  DelegateObjectContext : public antlr4::ParserRuleContext {
  public:
    DelegateObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<DelegatePropertyContext *> delegateProperty();
    DelegatePropertyContext* delegateProperty(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DelegateObjectContext* delegateObject();

  class  DelegatePropertyContext : public antlr4::ParserRuleContext {
  public:
    DelegatePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TARGET();
    antlr4::tree::TerminalNode *COLON();
    ChtlSelectorContext *chtlSelector();
    SelectorArrayContext *selectorArray();
    antlr4::tree::TerminalNode *IDENTIFIER();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DelegatePropertyContext* delegateProperty();

  class  SelectorArrayContext : public antlr4::ParserRuleContext {
  public:
    SelectorArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    std::vector<ChtlSelectorContext *> chtlSelector();
    ChtlSelectorContext* chtlSelector(size_t i);
    antlr4::tree::TerminalNode *RBRACKET();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectorArrayContext* selectorArray();

  class  AnimateCallContext : public antlr4::ParserRuleContext {
  public:
    AnimateCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANIMATE();
    antlr4::tree::TerminalNode *LPAREN();
    AnimateObjectContext *animateObject();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnimateCallContext* animateCall();

  class  AnimateObjectContext : public antlr4::ParserRuleContext {
  public:
    AnimateObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<AnimatePropertyContext *> animateProperty();
    AnimatePropertyContext* animateProperty(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnimateObjectContext* animateObject();

  class  AnimatePropertyContext : public antlr4::ParserRuleContext {
  public:
    AnimatePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DURATION();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *EASING();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *BEGIN_PROP();
    CssObjectContext *cssObject();
    antlr4::tree::TerminalNode *END_PROP();
    antlr4::tree::TerminalNode *WHEN();
    WhenArrayContext *whenArray();
    antlr4::tree::TerminalNode *LOOP();
    antlr4::tree::TerminalNode *DIRECTION();
    antlr4::tree::TerminalNode *DELAY();
    antlr4::tree::TerminalNode *CALLBACK();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnimatePropertyContext* animateProperty();

  class  CssObjectContext : public antlr4::ParserRuleContext {
  public:
    CssObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<CssPropertyContext *> cssProperty();
    CssPropertyContext* cssProperty(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssObjectContext* cssObject();

  class  CssPropertyContext : public antlr4::ParserRuleContext {
  public:
    CssPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMBER();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CssPropertyContext* cssProperty();

  class  WhenArrayContext : public antlr4::ParserRuleContext {
  public:
    WhenArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    std::vector<WhenObjectContext *> whenObject();
    WhenObjectContext* whenObject(size_t i);
    antlr4::tree::TerminalNode *RBRACKET();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhenArrayContext* whenArray();

  class  WhenObjectContext : public antlr4::ParserRuleContext {
  public:
    WhenObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<WhenPropertyContext *> whenProperty();
    WhenPropertyContext* whenProperty(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhenObjectContext* whenObject();

  class  WhenPropertyContext : public antlr4::ParserRuleContext {
  public:
    WhenPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhenPropertyContext* whenProperty();

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
    BlockContext *block();
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
    FunctionDeclarationContext *functionDeclaration();
    ClassDeclarationContext *classDeclaration();
    ImportStatementContext *importStatement();
    ExportStatementContext *exportStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  VariableStatementContext : public antlr4::ParserRuleContext {
  public:
    VariableStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclarationListContext *variableDeclarationList();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableStatementContext* variableStatement();

  class  VariableDeclarationListContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarModifierContext *varModifier();
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationListContext* variableDeclarationList();

  class  VarModifierContext : public antlr4::ParserRuleContext {
  public:
    VarModifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VAR();
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *CONST();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarModifierContext* varModifier();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignableContext *assignable();
    antlr4::tree::TerminalNode *EQUALS();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  EmptyStatementContext : public antlr4::ParserRuleContext {
  public:
    EmptyStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EmptyStatementContext* emptyStatement();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionSequenceContext *expressionSequence();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionSequenceContext *expressionSequence();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *ELSE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfStatementContext* ifStatement();

  class  IterationStatementContext : public antlr4::ParserRuleContext {
  public:
    IterationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DO();
    StatementContext *statement();
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionSequenceContext *> expressionSequence();
    ExpressionSequenceContext* expressionSequence(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    antlr4::tree::TerminalNode *FOR();
    VariableDeclarationListContext *variableDeclarationList();
    antlr4::tree::TerminalNode *IN();
    SingleExpressionContext *singleExpression();
    antlr4::tree::TerminalNode *OF();
    antlr4::tree::TerminalNode *AWAIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IterationStatementContext* iterationStatement();

  class  ContinueStatementContext : public antlr4::ParserRuleContext {
  public:
    ContinueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContinueStatementContext* continueStatement();

  class  BreakStatementContext : public antlr4::ParserRuleContext {
  public:
    BreakStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BreakStatementContext* breakStatement();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SEMICOLON();
    ExpressionSequenceContext *expressionSequence();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  WithStatementContext : public antlr4::ParserRuleContext {
  public:
    WithStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WITH();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionSequenceContext *expressionSequence();
    antlr4::tree::TerminalNode *RPAREN();
    StatementContext *statement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WithStatementContext* withStatement();

  class  LabelledStatementContext : public antlr4::ParserRuleContext {
  public:
    LabelledStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    StatementContext *statement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LabelledStatementContext* labelledStatement();

  class  SwitchStatementContext : public antlr4::ParserRuleContext {
  public:
    SwitchStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SWITCH();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionSequenceContext *expressionSequence();
    antlr4::tree::TerminalNode *RPAREN();
    CaseBlockContext *caseBlock();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SwitchStatementContext* switchStatement();

  class  CaseBlockContext : public antlr4::ParserRuleContext {
  public:
    CaseBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<CaseClausesContext *> caseClauses();
    CaseClausesContext* caseClauses(size_t i);
    DefaultClauseContext *defaultClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CaseBlockContext* caseBlock();

  class  CaseClausesContext : public antlr4::ParserRuleContext {
  public:
    CaseClausesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CaseClauseContext *> caseClause();
    CaseClauseContext* caseClause(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CaseClausesContext* caseClauses();

  class  CaseClauseContext : public antlr4::ParserRuleContext {
  public:
    CaseClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CASE();
    ExpressionSequenceContext *expressionSequence();
    antlr4::tree::TerminalNode *COLON();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CaseClauseContext* caseClause();

  class  DefaultClauseContext : public antlr4::ParserRuleContext {
  public:
    DefaultClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *COLON();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DefaultClauseContext* defaultClause();

  class  ThrowStatementContext : public antlr4::ParserRuleContext {
  public:
    ThrowStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *THROW();
    ExpressionSequenceContext *expressionSequence();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ThrowStatementContext* throwStatement();

  class  TryStatementContext : public antlr4::ParserRuleContext {
  public:
    TryStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRY();
    BlockContext *block();
    CatchClauseContext *catchClause();
    FinallyClauseContext *finallyClause();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TryStatementContext* tryStatement();

  class  CatchClauseContext : public antlr4::ParserRuleContext {
  public:
    CatchClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CATCH();
    BlockContext *block();
    antlr4::tree::TerminalNode *LPAREN();
    AssignableContext *assignable();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CatchClauseContext* catchClause();

  class  FinallyClauseContext : public antlr4::ParserRuleContext {
  public:
    FinallyClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FINALLY();
    BlockContext *block();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FinallyClauseContext* finallyClause();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    antlr4::tree::TerminalNode *ASYNC();
    antlr4::tree::TerminalNode *STAR();
    FormalParameterListContext *formalParameterList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  ClassDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ClassDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CLASS();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ClassTailContext *classTail();
    antlr4::tree::TerminalNode *EXTENDS();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassDeclarationContext* classDeclaration();

  class  ClassTailContext : public antlr4::ParserRuleContext {
  public:
    ClassTailContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<ClassElementContext *> classElement();
    ClassElementContext* classElement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassTailContext* classTail();

  class  ClassElementContext : public antlr4::ParserRuleContext {
  public:
    ClassElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MethodDefinitionContext *methodDefinition();
    antlr4::tree::TerminalNode *STATIC();
    EmptyStatementContext *emptyStatement();
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *EQUALS();
    SingleExpressionContext *singleExpression();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassElementContext* classElement();

  class  MethodDefinitionContext : public antlr4::ParserRuleContext {
  public:
    MethodDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    FormalParameterListContext *formalParameterList();
    GetterContext *getter();
    SetterContext *setter();
    GeneratorMethodContext *generatorMethod();
    AsyncMethodContext *asyncMethod();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MethodDefinitionContext* methodDefinition();

  class  GetterContext : public antlr4::ParserRuleContext {
  public:
    GetterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GET();
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GetterContext* getter();

  class  SetterContext : public antlr4::ParserRuleContext {
  public:
    SetterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET();
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *LPAREN();
    FormalParameterListContext *formalParameterList();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetterContext* setter();

  class  GeneratorMethodContext : public antlr4::ParserRuleContext {
  public:
    GeneratorMethodContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    FormalParameterListContext *formalParameterList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GeneratorMethodContext* generatorMethod();

  class  AsyncMethodContext : public antlr4::ParserRuleContext {
  public:
    AsyncMethodContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASYNC();
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    FormalParameterListContext *formalParameterList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AsyncMethodContext* asyncMethod();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *SEMICOLON();
    ImportFromBlockContext *importFromBlock();
    antlr4::tree::TerminalNode *STRING();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportStatementContext* importStatement();

  class  ImportFromBlockContext : public antlr4::ParserRuleContext {
  public:
    ImportFromBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ImportNamespaceContext *importNamespace();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportFromBlockContext* importFromBlock();

  class  ImportNamespaceContext : public antlr4::ParserRuleContext {
  public:
    ImportNamespaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<ImportSpecifierContext *> importSpecifier();
    ImportSpecifierContext* importSpecifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportNamespaceContext* importNamespace();

  class  ImportSpecifierContext : public antlr4::ParserRuleContext {
  public:
    ImportSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    ModuleExportNameContext *moduleExportName();
    antlr4::tree::TerminalNode *AS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportSpecifierContext* importSpecifier();

  class  ModuleExportNameContext : public antlr4::ParserRuleContext {
  public:
    ModuleExportNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModuleExportNameContext* moduleExportName();

  class  ExportStatementContext : public antlr4::ParserRuleContext {
  public:
    ExportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXPORT();
    antlr4::tree::TerminalNode *SEMICOLON();
    ExportFromBlockContext *exportFromBlock();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *DEFAULT();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExportStatementContext* exportStatement();

  class  ExportFromBlockContext : public antlr4::ParserRuleContext {
  public:
    ExportFromBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *STAR();
    ExportNamespaceContext *exportNamespace();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExportFromBlockContext* exportFromBlock();

  class  ExportNamespaceContext : public antlr4::ParserRuleContext {
  public:
    ExportNamespaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<ExportSpecifierContext *> exportSpecifier();
    ExportSpecifierContext* exportSpecifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExportNamespaceContext* exportNamespace();

  class  ExportSpecifierContext : public antlr4::ParserRuleContext {
  public:
    ExportSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<ModuleExportNameContext *> moduleExportName();
    ModuleExportNameContext* moduleExportName(size_t i);
    antlr4::tree::TerminalNode *AS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExportSpecifierContext* exportSpecifier();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableStatementContext *variableStatement();
    ClassDeclarationContext *classDeclaration();
    FunctionDeclarationContext *functionDeclaration();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  FormalParameterListContext : public antlr4::ParserRuleContext {
  public:
    FormalParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FormalParameterContext *> formalParameter();
    FormalParameterContext* formalParameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    RestParameterContext *restParameter();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalParameterListContext* formalParameterList();

  class  FormalParameterContext : public antlr4::ParserRuleContext {
  public:
    FormalParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignableContext *assignable();
    antlr4::tree::TerminalNode *EQUALS();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalParameterContext* formalParameter();

  class  RestParameterContext : public antlr4::ParserRuleContext {
  public:
    RestParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELLIPSIS();
    AssignableContext *assignable();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RestParameterContext* restParameter();

  class  AssignableContext : public antlr4::ParserRuleContext {
  public:
    AssignableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ArrayLiteralContext *arrayLiteral();
    ObjectLiteralContext *objectLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignableContext* assignable();

  class  PropertyNameContext : public antlr4::ParserRuleContext {
  public:
    PropertyNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierNameContext *identifierName();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *LBRACKET();
    SingleExpressionContext *singleExpression();
    antlr4::tree::TerminalNode *RBRACKET();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyNameContext* propertyName();

  class  ExpressionSequenceContext : public antlr4::ParserRuleContext {
  public:
    ExpressionSequenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionSequenceContext* expressionSequence();

  class  AssignmentOperatorContext : public antlr4::ParserRuleContext {
  public:
    AssignmentOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR_EQUALS();
    antlr4::tree::TerminalNode *SLASH_EQUALS();
    antlr4::tree::TerminalNode *PERCENT_EQUALS();
    antlr4::tree::TerminalNode *PLUS_EQUALS();
    antlr4::tree::TerminalNode *MINUS_EQUALS();
    antlr4::tree::TerminalNode *LSHIFT_EQUALS();
    antlr4::tree::TerminalNode *RSHIFT_EQUALS();
    antlr4::tree::TerminalNode *URSHIFT_EQUALS();
    antlr4::tree::TerminalNode *AMPERSAND_EQUALS();
    antlr4::tree::TerminalNode *CARET_EQUALS();
    antlr4::tree::TerminalNode *PIPE_EQUALS();
    antlr4::tree::TerminalNode *POWER_EQUALS();
    antlr4::tree::TerminalNode *NULLISH_EQUALS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentOperatorContext* assignmentOperator();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *TEMPLATE_STRING();
    antlr4::tree::TerminalNode *BOOLEAN();
    antlr4::tree::TerminalNode *NULL_();
    antlr4::tree::TerminalNode *UNDEFINED();
    antlr4::tree::TerminalNode *REGEX();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  ArrayLiteralContext : public antlr4::ParserRuleContext {
  public:
    ArrayLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    ElementListContext *elementList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayLiteralContext* arrayLiteral();

  class  ElementListContext : public antlr4::ParserRuleContext {
  public:
    ElementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArrayElementContext *> arrayElement();
    ArrayElementContext* arrayElement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementListContext* elementList();

  class  ArrayElementContext : public antlr4::ParserRuleContext {
  public:
    ArrayElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SingleExpressionContext *singleExpression();
    antlr4::tree::TerminalNode *ELLIPSIS();
    antlr4::tree::TerminalNode *COMMA();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayElementContext* arrayElement();

  class  ObjectLiteralContext : public antlr4::ParserRuleContext {
  public:
    ObjectLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<PropertyAssignmentContext *> propertyAssignment();
    PropertyAssignmentContext* propertyAssignment(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectLiteralContext* objectLiteral();

  class  PropertyAssignmentContext : public antlr4::ParserRuleContext {
  public:
    PropertyAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *COLON();
    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    MethodDefinitionContext *methodDefinition();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ELLIPSIS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyAssignmentContext* propertyAssignment();

  class  ArgumentsContext : public antlr4::ParserRuleContext {
  public:
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentListContext *argumentList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsContext* arguments();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentContext *> argument();
    ArgumentContext* argument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListContext* argumentList();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SingleExpressionContext *singleExpression();
    antlr4::tree::TerminalNode *ELLIPSIS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentContext* argument();

  class  AnonymousFunctionContext : public antlr4::ParserRuleContext {
  public:
    AnonymousFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    antlr4::tree::TerminalNode *ASYNC();
    antlr4::tree::TerminalNode *STAR();
    FormalParameterListContext *formalParameterList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnonymousFunctionContext* anonymousFunction();

  class  ArrowFunctionContext : public antlr4::ParserRuleContext {
  public:
    ArrowFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrowFunctionParametersContext *arrowFunctionParameters();
    antlr4::tree::TerminalNode *ARROW();
    ArrowFunctionBodyContext *arrowFunctionBody();
    antlr4::tree::TerminalNode *ASYNC();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrowFunctionContext* arrowFunction();

  class  ArrowFunctionParametersContext : public antlr4::ParserRuleContext {
  public:
    ArrowFunctionParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    FormalParameterListContext *formalParameterList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrowFunctionParametersContext* arrowFunctionParameters();

  class  ArrowFunctionBodyContext : public antlr4::ParserRuleContext {
  public:
    ArrowFunctionBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SingleExpressionContext *singleExpression();
    BlockContext *block();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrowFunctionBodyContext* arrowFunctionBody();

  class  TypeofExpressionContext : public antlr4::ParserRuleContext {
  public:
    TypeofExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPEOF();
    SingleExpressionContext *singleExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeofExpressionContext* typeofExpression();

  class  IdentifierNameContext : public antlr4::ParserRuleContext {
  public:
    IdentifierNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ReservedWordContext *reservedWord();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierNameContext* identifierName();

  class  ReservedWordContext : public antlr4::ParserRuleContext {
  public:
    ReservedWordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    KeywordContext *keyword();
    antlr4::tree::TerminalNode *NULL_();
    antlr4::tree::TerminalNode *BOOLEAN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReservedWordContext* reservedWord();

  class  KeywordContext : public antlr4::ParserRuleContext {
  public:
    KeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *DO();
    antlr4::tree::TerminalNode *INSTANCEOF();
    antlr4::tree::TerminalNode *TYPEOF();
    antlr4::tree::TerminalNode *CASE();
    antlr4::tree::TerminalNode *ELSE();
    antlr4::tree::TerminalNode *NEW();
    antlr4::tree::TerminalNode *VAR();
    antlr4::tree::TerminalNode *CATCH();
    antlr4::tree::TerminalNode *FINALLY();
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *SWITCH();
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *DEBUGGER();
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *THIS();
    antlr4::tree::TerminalNode *WITH();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *THROW();
    antlr4::tree::TerminalNode *DELETE();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *TRY();
    antlr4::tree::TerminalNode *CLASS();
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *EXTENDS();
    antlr4::tree::TerminalNode *SUPER();
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *EXPORT();
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *ASYNC();
    antlr4::tree::TerminalNode *AWAIT();
    antlr4::tree::TerminalNode *YIELD();
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *STATIC();
    antlr4::tree::TerminalNode *FROM();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *OF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeywordContext* keyword();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool singleExpressionSempred(SingleExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

