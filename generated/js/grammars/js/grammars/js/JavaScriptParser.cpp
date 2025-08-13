
// Generated from grammars/js/JavaScript.g4 by ANTLR 4.9.2


#include "JavaScriptListener.h"

#include "JavaScriptParser.h"


using namespace antlrcpp;
using namespace antlr4;

JavaScriptParser::JavaScriptParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

JavaScriptParser::~JavaScriptParser() {
  delete _interpreter;
}

std::string JavaScriptParser::getGrammarFileName() const {
  return "JavaScript.g4";
}

const std::vector<std::string>& JavaScriptParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& JavaScriptParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

JavaScriptParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ProgramContext::EOF() {
  return getToken(JavaScriptParser::EOF, 0);
}

std::vector<JavaScriptParser::SourceElementContext *> JavaScriptParser::ProgramContext::sourceElement() {
  return getRuleContexts<JavaScriptParser::SourceElementContext>();
}

JavaScriptParser::SourceElementContext* JavaScriptParser::ProgramContext::sourceElement(size_t i) {
  return getRuleContext<JavaScriptParser::SourceElementContext>(i);
}


size_t JavaScriptParser::ProgramContext::getRuleIndex() const {
  return JavaScriptParser::RuleProgram;
}

void JavaScriptParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void JavaScriptParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

JavaScriptParser::ProgramContext* JavaScriptParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, JavaScriptParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::SEMICOLON - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
      setState(234);
      sourceElement();
      setState(239);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(240);
    match(JavaScriptParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceElementContext ------------------------------------------------------------------

JavaScriptParser::SourceElementContext::SourceElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::StatementContext* JavaScriptParser::SourceElementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::SourceElementContext::functionDeclaration() {
  return getRuleContext<JavaScriptParser::FunctionDeclarationContext>(0);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::SourceElementContext::classDeclaration() {
  return getRuleContext<JavaScriptParser::ClassDeclarationContext>(0);
}


size_t JavaScriptParser::SourceElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleSourceElement;
}

void JavaScriptParser::SourceElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceElement(this);
}

void JavaScriptParser::SourceElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceElement(this);
}

JavaScriptParser::SourceElementContext* JavaScriptParser::sourceElement() {
  SourceElementContext *_localctx = _tracker.createInstance<SourceElementContext>(_ctx, getState());
  enterRule(_localctx, 2, JavaScriptParser::RuleSourceElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(245);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(242);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(243);
      functionDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(244);
      classDeclaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

JavaScriptParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::BlockContext* JavaScriptParser::StatementContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::VariableStatementContext* JavaScriptParser::StatementContext::variableStatement() {
  return getRuleContext<JavaScriptParser::VariableStatementContext>(0);
}

JavaScriptParser::EmptyStatementContext* JavaScriptParser::StatementContext::emptyStatement() {
  return getRuleContext<JavaScriptParser::EmptyStatementContext>(0);
}

JavaScriptParser::ExpressionStatementContext* JavaScriptParser::StatementContext::expressionStatement() {
  return getRuleContext<JavaScriptParser::ExpressionStatementContext>(0);
}

JavaScriptParser::IfStatementContext* JavaScriptParser::StatementContext::ifStatement() {
  return getRuleContext<JavaScriptParser::IfStatementContext>(0);
}

JavaScriptParser::IterationStatementContext* JavaScriptParser::StatementContext::iterationStatement() {
  return getRuleContext<JavaScriptParser::IterationStatementContext>(0);
}

JavaScriptParser::ContinueStatementContext* JavaScriptParser::StatementContext::continueStatement() {
  return getRuleContext<JavaScriptParser::ContinueStatementContext>(0);
}

JavaScriptParser::BreakStatementContext* JavaScriptParser::StatementContext::breakStatement() {
  return getRuleContext<JavaScriptParser::BreakStatementContext>(0);
}

JavaScriptParser::ReturnStatementContext* JavaScriptParser::StatementContext::returnStatement() {
  return getRuleContext<JavaScriptParser::ReturnStatementContext>(0);
}

JavaScriptParser::YieldStatementContext* JavaScriptParser::StatementContext::yieldStatement() {
  return getRuleContext<JavaScriptParser::YieldStatementContext>(0);
}

JavaScriptParser::WithStatementContext* JavaScriptParser::StatementContext::withStatement() {
  return getRuleContext<JavaScriptParser::WithStatementContext>(0);
}

JavaScriptParser::LabelledStatementContext* JavaScriptParser::StatementContext::labelledStatement() {
  return getRuleContext<JavaScriptParser::LabelledStatementContext>(0);
}

JavaScriptParser::SwitchStatementContext* JavaScriptParser::StatementContext::switchStatement() {
  return getRuleContext<JavaScriptParser::SwitchStatementContext>(0);
}

JavaScriptParser::ThrowStatementContext* JavaScriptParser::StatementContext::throwStatement() {
  return getRuleContext<JavaScriptParser::ThrowStatementContext>(0);
}

JavaScriptParser::TryStatementContext* JavaScriptParser::StatementContext::tryStatement() {
  return getRuleContext<JavaScriptParser::TryStatementContext>(0);
}

JavaScriptParser::DebuggerStatementContext* JavaScriptParser::StatementContext::debuggerStatement() {
  return getRuleContext<JavaScriptParser::DebuggerStatementContext>(0);
}

JavaScriptParser::ImportStatementContext* JavaScriptParser::StatementContext::importStatement() {
  return getRuleContext<JavaScriptParser::ImportStatementContext>(0);
}

JavaScriptParser::ExportStatementContext* JavaScriptParser::StatementContext::exportStatement() {
  return getRuleContext<JavaScriptParser::ExportStatementContext>(0);
}


size_t JavaScriptParser::StatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleStatement;
}

void JavaScriptParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void JavaScriptParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

JavaScriptParser::StatementContext* JavaScriptParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, JavaScriptParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(265);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(247);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(248);
      variableStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(249);
      emptyStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(250);
      expressionStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(251);
      ifStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(252);
      iterationStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(253);
      continueStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(254);
      breakStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(255);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(256);
      yieldStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(257);
      withStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(258);
      labelledStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(259);
      switchStatement();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(260);
      throwStatement();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(261);
      tryStatement();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(262);
      debuggerStatement();
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(263);
      importStatement();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(264);
      exportStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

JavaScriptParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::BlockContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::BlockContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

JavaScriptParser::StatementListContext* JavaScriptParser::BlockContext::statementList() {
  return getRuleContext<JavaScriptParser::StatementListContext>(0);
}


size_t JavaScriptParser::BlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleBlock;
}

void JavaScriptParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void JavaScriptParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

JavaScriptParser::BlockContext* JavaScriptParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 6, JavaScriptParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(267);
    match(JavaScriptParser::LBRACE);
    setState(269);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::SEMICOLON - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
      setState(268);
      statementList();
    }
    setState(271);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

JavaScriptParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::StatementListContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::StatementListContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}


size_t JavaScriptParser::StatementListContext::getRuleIndex() const {
  return JavaScriptParser::RuleStatementList;
}

void JavaScriptParser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void JavaScriptParser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}

JavaScriptParser::StatementListContext* JavaScriptParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 8, JavaScriptParser::RuleStatementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(274); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(273);
      statement();
      setState(276); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::SEMICOLON - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableStatementContext ------------------------------------------------------------------

JavaScriptParser::VariableStatementContext::VariableStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::VariableStatementContext::variableDeclarationList() {
  return getRuleContext<JavaScriptParser::VariableDeclarationListContext>(0);
}

tree::TerminalNode* JavaScriptParser::VariableStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

tree::TerminalNode* JavaScriptParser::VariableStatementContext::VAR() {
  return getToken(JavaScriptParser::VAR, 0);
}

tree::TerminalNode* JavaScriptParser::VariableStatementContext::LET() {
  return getToken(JavaScriptParser::LET, 0);
}

tree::TerminalNode* JavaScriptParser::VariableStatementContext::CONST() {
  return getToken(JavaScriptParser::CONST, 0);
}


size_t JavaScriptParser::VariableStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableStatement;
}

void JavaScriptParser::VariableStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableStatement(this);
}

void JavaScriptParser::VariableStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableStatement(this);
}

JavaScriptParser::VariableStatementContext* JavaScriptParser::variableStatement() {
  VariableStatementContext *_localctx = _tracker.createInstance<VariableStatementContext>(_ctx, getState());
  enterRule(_localctx, 10, JavaScriptParser::RuleVariableStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::LET))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(279);
    variableDeclarationList();
    setState(280);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationListContext ------------------------------------------------------------------

JavaScriptParser::VariableDeclarationListContext::VariableDeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::VariableDeclarationContext *> JavaScriptParser::VariableDeclarationListContext::variableDeclaration() {
  return getRuleContexts<JavaScriptParser::VariableDeclarationContext>();
}

JavaScriptParser::VariableDeclarationContext* JavaScriptParser::VariableDeclarationListContext::variableDeclaration(size_t i) {
  return getRuleContext<JavaScriptParser::VariableDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::VariableDeclarationListContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::VariableDeclarationListContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::VariableDeclarationListContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableDeclarationList;
}

void JavaScriptParser::VariableDeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclarationList(this);
}

void JavaScriptParser::VariableDeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclarationList(this);
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::variableDeclarationList() {
  VariableDeclarationListContext *_localctx = _tracker.createInstance<VariableDeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 12, JavaScriptParser::RuleVariableDeclarationList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    variableDeclaration();
    setState(287);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(283);
      match(JavaScriptParser::COMMA);
      setState(284);
      variableDeclaration();
      setState(289);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

JavaScriptParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::VariableDeclarationContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::BindingPatternContext* JavaScriptParser::VariableDeclarationContext::bindingPattern() {
  return getRuleContext<JavaScriptParser::BindingPatternContext>(0);
}

tree::TerminalNode* JavaScriptParser::VariableDeclarationContext::ASSIGN() {
  return getToken(JavaScriptParser::ASSIGN, 0);
}

JavaScriptParser::InitializerContext* JavaScriptParser::VariableDeclarationContext::initializer() {
  return getRuleContext<JavaScriptParser::InitializerContext>(0);
}


size_t JavaScriptParser::VariableDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableDeclaration;
}

void JavaScriptParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void JavaScriptParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}

JavaScriptParser::VariableDeclarationContext* JavaScriptParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, JavaScriptParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        setState(290);
        identifier();
        break;
      }

      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET: {
        setState(291);
        bindingPattern();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(296);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::ASSIGN) {
      setState(294);
      match(JavaScriptParser::ASSIGN);
      setState(295);
      initializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BindingPatternContext ------------------------------------------------------------------

JavaScriptParser::BindingPatternContext::BindingPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ObjectBindingPatternContext* JavaScriptParser::BindingPatternContext::objectBindingPattern() {
  return getRuleContext<JavaScriptParser::ObjectBindingPatternContext>(0);
}

JavaScriptParser::ArrayBindingPatternContext* JavaScriptParser::BindingPatternContext::arrayBindingPattern() {
  return getRuleContext<JavaScriptParser::ArrayBindingPatternContext>(0);
}


size_t JavaScriptParser::BindingPatternContext::getRuleIndex() const {
  return JavaScriptParser::RuleBindingPattern;
}

void JavaScriptParser::BindingPatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBindingPattern(this);
}

void JavaScriptParser::BindingPatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBindingPattern(this);
}

JavaScriptParser::BindingPatternContext* JavaScriptParser::bindingPattern() {
  BindingPatternContext *_localctx = _tracker.createInstance<BindingPatternContext>(_ctx, getState());
  enterRule(_localctx, 16, JavaScriptParser::RuleBindingPattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(300);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::LBRACE: {
        enterOuterAlt(_localctx, 1);
        setState(298);
        objectBindingPattern();
        break;
      }

      case JavaScriptParser::LBRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(299);
        arrayBindingPattern();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectBindingPatternContext ------------------------------------------------------------------

JavaScriptParser::ObjectBindingPatternContext::ObjectBindingPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ObjectBindingPatternContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::ObjectBindingPatternContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::BindingPropertyContext *> JavaScriptParser::ObjectBindingPatternContext::bindingProperty() {
  return getRuleContexts<JavaScriptParser::BindingPropertyContext>();
}

JavaScriptParser::BindingPropertyContext* JavaScriptParser::ObjectBindingPatternContext::bindingProperty(size_t i) {
  return getRuleContext<JavaScriptParser::BindingPropertyContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ObjectBindingPatternContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ObjectBindingPatternContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ObjectBindingPatternContext::getRuleIndex() const {
  return JavaScriptParser::RuleObjectBindingPattern;
}

void JavaScriptParser::ObjectBindingPatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectBindingPattern(this);
}

void JavaScriptParser::ObjectBindingPatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectBindingPattern(this);
}

JavaScriptParser::ObjectBindingPatternContext* JavaScriptParser::objectBindingPattern() {
  ObjectBindingPatternContext *_localctx = _tracker.createInstance<ObjectBindingPatternContext>(_ctx, getState());
  enterRule(_localctx, 18, JavaScriptParser::RuleObjectBindingPattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(302);
    match(JavaScriptParser::LBRACE);
    setState(311);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::IMPLEMENTS)
      | (1ULL << JavaScriptParser::INTERFACE)
      | (1ULL << JavaScriptParser::PACKAGE)
      | (1ULL << JavaScriptParser::PRIVATE)
      | (1ULL << JavaScriptParser::PROTECTED)
      | (1ULL << JavaScriptParser::PUBLIC)
      | (1ULL << JavaScriptParser::ABSTRACT)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::BYTE)
      | (1ULL << JavaScriptParser::CHAR)
      | (1ULL << JavaScriptParser::DOUBLE)
      | (1ULL << JavaScriptParser::FINAL)
      | (1ULL << JavaScriptParser::FLOAT)
      | (1ULL << JavaScriptParser::GOTO)
      | (1ULL << JavaScriptParser::INT)
      | (1ULL << JavaScriptParser::LONG)
      | (1ULL << JavaScriptParser::NATIVE)
      | (1ULL << JavaScriptParser::SHORT)
      | (1ULL << JavaScriptParser::SYNCHRONIZED)
      | (1ULL << JavaScriptParser::THROWS)
      | (1ULL << JavaScriptParser::TRANSIENT)
      | (1ULL << JavaScriptParser::VOLATILE)
      | (1ULL << JavaScriptParser::NULL))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::TRUE - 64))
      | (1ULL << (JavaScriptParser::FALSE - 64))
      | (1ULL << (JavaScriptParser::STRING - 64))
      | (1ULL << (JavaScriptParser::NUMBER - 64))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 64))
      | (1ULL << (JavaScriptParser::LBRACE - 64))
      | (1ULL << (JavaScriptParser::LBRACKET - 64)))) != 0)) {
      setState(303);
      bindingProperty();
      setState(308);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaScriptParser::COMMA) {
        setState(304);
        match(JavaScriptParser::COMMA);
        setState(305);
        bindingProperty();
        setState(310);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(313);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BindingPropertyContext ------------------------------------------------------------------

JavaScriptParser::BindingPropertyContext::BindingPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::BindingElementContext* JavaScriptParser::BindingPropertyContext::bindingElement() {
  return getRuleContext<JavaScriptParser::BindingElementContext>(0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::BindingPropertyContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::BindingPropertyContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}


size_t JavaScriptParser::BindingPropertyContext::getRuleIndex() const {
  return JavaScriptParser::RuleBindingProperty;
}

void JavaScriptParser::BindingPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBindingProperty(this);
}

void JavaScriptParser::BindingPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBindingProperty(this);
}

JavaScriptParser::BindingPropertyContext* JavaScriptParser::bindingProperty() {
  BindingPropertyContext *_localctx = _tracker.createInstance<BindingPropertyContext>(_ctx, getState());
  enterRule(_localctx, 20, JavaScriptParser::RuleBindingProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(318);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(315);
      propertyName();
      setState(316);
      match(JavaScriptParser::COLON);
      break;
    }

    default:
      break;
    }
    setState(320);
    bindingElement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BindingElementContext ------------------------------------------------------------------

JavaScriptParser::BindingElementContext::BindingElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::BindingElementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::BindingPatternContext* JavaScriptParser::BindingElementContext::bindingPattern() {
  return getRuleContext<JavaScriptParser::BindingPatternContext>(0);
}

tree::TerminalNode* JavaScriptParser::BindingElementContext::ASSIGN() {
  return getToken(JavaScriptParser::ASSIGN, 0);
}

JavaScriptParser::InitializerContext* JavaScriptParser::BindingElementContext::initializer() {
  return getRuleContext<JavaScriptParser::InitializerContext>(0);
}


size_t JavaScriptParser::BindingElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleBindingElement;
}

void JavaScriptParser::BindingElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBindingElement(this);
}

void JavaScriptParser::BindingElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBindingElement(this);
}

JavaScriptParser::BindingElementContext* JavaScriptParser::bindingElement() {
  BindingElementContext *_localctx = _tracker.createInstance<BindingElementContext>(_ctx, getState());
  enterRule(_localctx, 22, JavaScriptParser::RuleBindingElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        setState(322);
        identifier();
        break;
      }

      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET: {
        setState(323);
        bindingPattern();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(328);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::ASSIGN) {
      setState(326);
      match(JavaScriptParser::ASSIGN);
      setState(327);
      initializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayBindingPatternContext ------------------------------------------------------------------

JavaScriptParser::ArrayBindingPatternContext::ArrayBindingPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ArrayBindingPatternContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::ArrayBindingPatternContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}

std::vector<JavaScriptParser::BindingElementContext *> JavaScriptParser::ArrayBindingPatternContext::bindingElement() {
  return getRuleContexts<JavaScriptParser::BindingElementContext>();
}

JavaScriptParser::BindingElementContext* JavaScriptParser::ArrayBindingPatternContext::bindingElement(size_t i) {
  return getRuleContext<JavaScriptParser::BindingElementContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ArrayBindingPatternContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ArrayBindingPatternContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ArrayBindingPatternContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrayBindingPattern;
}

void JavaScriptParser::ArrayBindingPatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayBindingPattern(this);
}

void JavaScriptParser::ArrayBindingPatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayBindingPattern(this);
}

JavaScriptParser::ArrayBindingPatternContext* JavaScriptParser::arrayBindingPattern() {
  ArrayBindingPatternContext *_localctx = _tracker.createInstance<ArrayBindingPatternContext>(_ctx, getState());
  enterRule(_localctx, 24, JavaScriptParser::RuleArrayBindingPattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(330);
    match(JavaScriptParser::LBRACKET);
    setState(339);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82)))) != 0)) {
      setState(331);
      bindingElement();
      setState(336);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaScriptParser::COMMA) {
        setState(332);
        match(JavaScriptParser::COMMA);
        setState(333);
        bindingElement();
        setState(338);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(341);
    match(JavaScriptParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyNameContext ------------------------------------------------------------------

JavaScriptParser::PropertyNameContext::PropertyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::PropertyNameContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

JavaScriptParser::StringLiteralContext* JavaScriptParser::PropertyNameContext::stringLiteral() {
  return getRuleContext<JavaScriptParser::StringLiteralContext>(0);
}

JavaScriptParser::NumericLiteralContext* JavaScriptParser::PropertyNameContext::numericLiteral() {
  return getRuleContext<JavaScriptParser::NumericLiteralContext>(0);
}


size_t JavaScriptParser::PropertyNameContext::getRuleIndex() const {
  return JavaScriptParser::RulePropertyName;
}

void JavaScriptParser::PropertyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyName(this);
}

void JavaScriptParser::PropertyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyName(this);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::propertyName() {
  PropertyNameContext *_localctx = _tracker.createInstance<PropertyNameContext>(_ctx, getState());
  enterRule(_localctx, 26, JavaScriptParser::RulePropertyName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(346);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::BREAK:
      case JavaScriptParser::DO:
      case JavaScriptParser::INSTANCEOF:
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::CASE:
      case JavaScriptParser::ELSE:
      case JavaScriptParser::NEW:
      case JavaScriptParser::VAR:
      case JavaScriptParser::CATCH:
      case JavaScriptParser::FINALLY:
      case JavaScriptParser::RETURN:
      case JavaScriptParser::VOID:
      case JavaScriptParser::CONTINUE:
      case JavaScriptParser::FOR:
      case JavaScriptParser::SWITCH:
      case JavaScriptParser::WHILE:
      case JavaScriptParser::DEBUGGER:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::WITH:
      case JavaScriptParser::DEFAULT:
      case JavaScriptParser::IF:
      case JavaScriptParser::THROW:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::IN:
      case JavaScriptParser::TRY:
      case JavaScriptParser::CLASS:
      case JavaScriptParser::ENUM:
      case JavaScriptParser::EXTENDS:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::CONST:
      case JavaScriptParser::EXPORT:
      case JavaScriptParser::IMPORT:
      case JavaScriptParser::LET:
      case JavaScriptParser::STATIC:
      case JavaScriptParser::YIELD:
      case JavaScriptParser::IMPLEMENTS:
      case JavaScriptParser::INTERFACE:
      case JavaScriptParser::PACKAGE:
      case JavaScriptParser::PRIVATE:
      case JavaScriptParser::PROTECTED:
      case JavaScriptParser::PUBLIC:
      case JavaScriptParser::ABSTRACT:
      case JavaScriptParser::BOOLEAN:
      case JavaScriptParser::BYTE:
      case JavaScriptParser::CHAR:
      case JavaScriptParser::DOUBLE:
      case JavaScriptParser::FINAL:
      case JavaScriptParser::FLOAT:
      case JavaScriptParser::GOTO:
      case JavaScriptParser::INT:
      case JavaScriptParser::LONG:
      case JavaScriptParser::NATIVE:
      case JavaScriptParser::SHORT:
      case JavaScriptParser::SYNCHRONIZED:
      case JavaScriptParser::THROWS:
      case JavaScriptParser::TRANSIENT:
      case JavaScriptParser::VOLATILE:
      case JavaScriptParser::NULL:
      case JavaScriptParser::TRUE:
      case JavaScriptParser::FALSE:
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(343);
        identifierName();
        break;
      }

      case JavaScriptParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(344);
        stringLiteral();
        break;
      }

      case JavaScriptParser::NUMBER: {
        enterOuterAlt(_localctx, 3);
        setState(345);
        numericLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierNameContext ------------------------------------------------------------------

JavaScriptParser::IdentifierNameContext::IdentifierNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IdentifierNameContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

JavaScriptParser::ReservedWordContext* JavaScriptParser::IdentifierNameContext::reservedWord() {
  return getRuleContext<JavaScriptParser::ReservedWordContext>(0);
}


size_t JavaScriptParser::IdentifierNameContext::getRuleIndex() const {
  return JavaScriptParser::RuleIdentifierName;
}

void JavaScriptParser::IdentifierNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierName(this);
}

void JavaScriptParser::IdentifierNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierName(this);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::identifierName() {
  IdentifierNameContext *_localctx = _tracker.createInstance<IdentifierNameContext>(_ctx, getState());
  enterRule(_localctx, 28, JavaScriptParser::RuleIdentifierName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(350);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(348);
        match(JavaScriptParser::IDENTIFIER);
        break;
      }

      case JavaScriptParser::BREAK:
      case JavaScriptParser::DO:
      case JavaScriptParser::INSTANCEOF:
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::CASE:
      case JavaScriptParser::ELSE:
      case JavaScriptParser::NEW:
      case JavaScriptParser::VAR:
      case JavaScriptParser::CATCH:
      case JavaScriptParser::FINALLY:
      case JavaScriptParser::RETURN:
      case JavaScriptParser::VOID:
      case JavaScriptParser::CONTINUE:
      case JavaScriptParser::FOR:
      case JavaScriptParser::SWITCH:
      case JavaScriptParser::WHILE:
      case JavaScriptParser::DEBUGGER:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::WITH:
      case JavaScriptParser::DEFAULT:
      case JavaScriptParser::IF:
      case JavaScriptParser::THROW:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::IN:
      case JavaScriptParser::TRY:
      case JavaScriptParser::CLASS:
      case JavaScriptParser::ENUM:
      case JavaScriptParser::EXTENDS:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::CONST:
      case JavaScriptParser::EXPORT:
      case JavaScriptParser::IMPORT:
      case JavaScriptParser::LET:
      case JavaScriptParser::STATIC:
      case JavaScriptParser::YIELD:
      case JavaScriptParser::IMPLEMENTS:
      case JavaScriptParser::INTERFACE:
      case JavaScriptParser::PACKAGE:
      case JavaScriptParser::PRIVATE:
      case JavaScriptParser::PROTECTED:
      case JavaScriptParser::PUBLIC:
      case JavaScriptParser::ABSTRACT:
      case JavaScriptParser::BOOLEAN:
      case JavaScriptParser::BYTE:
      case JavaScriptParser::CHAR:
      case JavaScriptParser::DOUBLE:
      case JavaScriptParser::FINAL:
      case JavaScriptParser::FLOAT:
      case JavaScriptParser::GOTO:
      case JavaScriptParser::INT:
      case JavaScriptParser::LONG:
      case JavaScriptParser::NATIVE:
      case JavaScriptParser::SHORT:
      case JavaScriptParser::SYNCHRONIZED:
      case JavaScriptParser::THROWS:
      case JavaScriptParser::TRANSIENT:
      case JavaScriptParser::VOLATILE:
      case JavaScriptParser::NULL:
      case JavaScriptParser::TRUE:
      case JavaScriptParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(349);
        reservedWord();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReservedWordContext ------------------------------------------------------------------

JavaScriptParser::ReservedWordContext::ReservedWordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::KeywordContext* JavaScriptParser::ReservedWordContext::keyword() {
  return getRuleContext<JavaScriptParser::KeywordContext>(0);
}

JavaScriptParser::FutureReservedWordContext* JavaScriptParser::ReservedWordContext::futureReservedWord() {
  return getRuleContext<JavaScriptParser::FutureReservedWordContext>(0);
}

tree::TerminalNode* JavaScriptParser::ReservedWordContext::TRUE() {
  return getToken(JavaScriptParser::TRUE, 0);
}

tree::TerminalNode* JavaScriptParser::ReservedWordContext::FALSE() {
  return getToken(JavaScriptParser::FALSE, 0);
}

tree::TerminalNode* JavaScriptParser::ReservedWordContext::NULL() {
  return getToken(JavaScriptParser::NULL, 0);
}


size_t JavaScriptParser::ReservedWordContext::getRuleIndex() const {
  return JavaScriptParser::RuleReservedWord;
}

void JavaScriptParser::ReservedWordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReservedWord(this);
}

void JavaScriptParser::ReservedWordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReservedWord(this);
}

JavaScriptParser::ReservedWordContext* JavaScriptParser::reservedWord() {
  ReservedWordContext *_localctx = _tracker.createInstance<ReservedWordContext>(_ctx, getState());
  enterRule(_localctx, 30, JavaScriptParser::RuleReservedWord);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(355);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::BREAK:
      case JavaScriptParser::DO:
      case JavaScriptParser::INSTANCEOF:
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::CASE:
      case JavaScriptParser::ELSE:
      case JavaScriptParser::NEW:
      case JavaScriptParser::VAR:
      case JavaScriptParser::CATCH:
      case JavaScriptParser::FINALLY:
      case JavaScriptParser::RETURN:
      case JavaScriptParser::VOID:
      case JavaScriptParser::CONTINUE:
      case JavaScriptParser::FOR:
      case JavaScriptParser::SWITCH:
      case JavaScriptParser::WHILE:
      case JavaScriptParser::DEBUGGER:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::WITH:
      case JavaScriptParser::DEFAULT:
      case JavaScriptParser::IF:
      case JavaScriptParser::THROW:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::IN:
      case JavaScriptParser::TRY: {
        enterOuterAlt(_localctx, 1);
        setState(352);
        keyword();
        break;
      }

      case JavaScriptParser::CLASS:
      case JavaScriptParser::ENUM:
      case JavaScriptParser::EXTENDS:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::CONST:
      case JavaScriptParser::EXPORT:
      case JavaScriptParser::IMPORT:
      case JavaScriptParser::LET:
      case JavaScriptParser::STATIC:
      case JavaScriptParser::YIELD:
      case JavaScriptParser::IMPLEMENTS:
      case JavaScriptParser::INTERFACE:
      case JavaScriptParser::PACKAGE:
      case JavaScriptParser::PRIVATE:
      case JavaScriptParser::PROTECTED:
      case JavaScriptParser::PUBLIC:
      case JavaScriptParser::ABSTRACT:
      case JavaScriptParser::BOOLEAN:
      case JavaScriptParser::BYTE:
      case JavaScriptParser::CHAR:
      case JavaScriptParser::DOUBLE:
      case JavaScriptParser::FINAL:
      case JavaScriptParser::FLOAT:
      case JavaScriptParser::GOTO:
      case JavaScriptParser::INT:
      case JavaScriptParser::LONG:
      case JavaScriptParser::NATIVE:
      case JavaScriptParser::SHORT:
      case JavaScriptParser::SYNCHRONIZED:
      case JavaScriptParser::THROWS:
      case JavaScriptParser::TRANSIENT:
      case JavaScriptParser::VOLATILE: {
        enterOuterAlt(_localctx, 2);
        setState(353);
        futureReservedWord();
        break;
      }

      case JavaScriptParser::NULL:
      case JavaScriptParser::TRUE:
      case JavaScriptParser::FALSE: {
        enterOuterAlt(_localctx, 3);
        setState(354);
        _la = _input->LA(1);
        if (!(((((_la - 63) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 63)) & ((1ULL << (JavaScriptParser::NULL - 63))
          | (1ULL << (JavaScriptParser::TRUE - 63))
          | (1ULL << (JavaScriptParser::FALSE - 63)))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeywordContext ------------------------------------------------------------------

JavaScriptParser::KeywordContext::KeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::KeywordContext::BREAK() {
  return getToken(JavaScriptParser::BREAK, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::DO() {
  return getToken(JavaScriptParser::DO, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::INSTANCEOF() {
  return getToken(JavaScriptParser::INSTANCEOF, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::TYPEOF() {
  return getToken(JavaScriptParser::TYPEOF, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::CASE() {
  return getToken(JavaScriptParser::CASE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::ELSE() {
  return getToken(JavaScriptParser::ELSE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::NEW() {
  return getToken(JavaScriptParser::NEW, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::VAR() {
  return getToken(JavaScriptParser::VAR, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::CATCH() {
  return getToken(JavaScriptParser::CATCH, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::FINALLY() {
  return getToken(JavaScriptParser::FINALLY, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::RETURN() {
  return getToken(JavaScriptParser::RETURN, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::VOID() {
  return getToken(JavaScriptParser::VOID, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::CONTINUE() {
  return getToken(JavaScriptParser::CONTINUE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::FOR() {
  return getToken(JavaScriptParser::FOR, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::SWITCH() {
  return getToken(JavaScriptParser::SWITCH, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::WHILE() {
  return getToken(JavaScriptParser::WHILE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::DEBUGGER() {
  return getToken(JavaScriptParser::DEBUGGER, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::FUNCTION() {
  return getToken(JavaScriptParser::FUNCTION, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::THIS() {
  return getToken(JavaScriptParser::THIS, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::WITH() {
  return getToken(JavaScriptParser::WITH, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::DEFAULT() {
  return getToken(JavaScriptParser::DEFAULT, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::IF() {
  return getToken(JavaScriptParser::IF, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::THROW() {
  return getToken(JavaScriptParser::THROW, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::DELETE() {
  return getToken(JavaScriptParser::DELETE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::IN() {
  return getToken(JavaScriptParser::IN, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::TRY() {
  return getToken(JavaScriptParser::TRY, 0);
}


size_t JavaScriptParser::KeywordContext::getRuleIndex() const {
  return JavaScriptParser::RuleKeyword;
}

void JavaScriptParser::KeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword(this);
}

void JavaScriptParser::KeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword(this);
}

JavaScriptParser::KeywordContext* JavaScriptParser::keyword() {
  KeywordContext *_localctx = _tracker.createInstance<KeywordContext>(_ctx, getState());
  enterRule(_localctx, 32, JavaScriptParser::RuleKeyword);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(357);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FutureReservedWordContext ------------------------------------------------------------------

JavaScriptParser::FutureReservedWordContext::FutureReservedWordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::CLASS() {
  return getToken(JavaScriptParser::CLASS, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::ENUM() {
  return getToken(JavaScriptParser::ENUM, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::EXTENDS() {
  return getToken(JavaScriptParser::EXTENDS, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::SUPER() {
  return getToken(JavaScriptParser::SUPER, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::CONST() {
  return getToken(JavaScriptParser::CONST, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::EXPORT() {
  return getToken(JavaScriptParser::EXPORT, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::IMPORT() {
  return getToken(JavaScriptParser::IMPORT, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::LET() {
  return getToken(JavaScriptParser::LET, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::STATIC() {
  return getToken(JavaScriptParser::STATIC, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::YIELD() {
  return getToken(JavaScriptParser::YIELD, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::IMPLEMENTS() {
  return getToken(JavaScriptParser::IMPLEMENTS, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::INTERFACE() {
  return getToken(JavaScriptParser::INTERFACE, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::PACKAGE() {
  return getToken(JavaScriptParser::PACKAGE, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::PRIVATE() {
  return getToken(JavaScriptParser::PRIVATE, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::PROTECTED() {
  return getToken(JavaScriptParser::PROTECTED, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::PUBLIC() {
  return getToken(JavaScriptParser::PUBLIC, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::ABSTRACT() {
  return getToken(JavaScriptParser::ABSTRACT, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::BOOLEAN() {
  return getToken(JavaScriptParser::BOOLEAN, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::BYTE() {
  return getToken(JavaScriptParser::BYTE, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::CHAR() {
  return getToken(JavaScriptParser::CHAR, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::DOUBLE() {
  return getToken(JavaScriptParser::DOUBLE, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::FINAL() {
  return getToken(JavaScriptParser::FINAL, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::FLOAT() {
  return getToken(JavaScriptParser::FLOAT, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::GOTO() {
  return getToken(JavaScriptParser::GOTO, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::INT() {
  return getToken(JavaScriptParser::INT, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::LONG() {
  return getToken(JavaScriptParser::LONG, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::NATIVE() {
  return getToken(JavaScriptParser::NATIVE, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::SHORT() {
  return getToken(JavaScriptParser::SHORT, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::SYNCHRONIZED() {
  return getToken(JavaScriptParser::SYNCHRONIZED, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::THROWS() {
  return getToken(JavaScriptParser::THROWS, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::TRANSIENT() {
  return getToken(JavaScriptParser::TRANSIENT, 0);
}

tree::TerminalNode* JavaScriptParser::FutureReservedWordContext::VOLATILE() {
  return getToken(JavaScriptParser::VOLATILE, 0);
}


size_t JavaScriptParser::FutureReservedWordContext::getRuleIndex() const {
  return JavaScriptParser::RuleFutureReservedWord;
}

void JavaScriptParser::FutureReservedWordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFutureReservedWord(this);
}

void JavaScriptParser::FutureReservedWordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFutureReservedWord(this);
}

JavaScriptParser::FutureReservedWordContext* JavaScriptParser::futureReservedWord() {
  FutureReservedWordContext *_localctx = _tracker.createInstance<FutureReservedWordContext>(_ctx, getState());
  enterRule(_localctx, 34, JavaScriptParser::RuleFutureReservedWord);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(359);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::IMPLEMENTS)
      | (1ULL << JavaScriptParser::INTERFACE)
      | (1ULL << JavaScriptParser::PACKAGE)
      | (1ULL << JavaScriptParser::PRIVATE)
      | (1ULL << JavaScriptParser::PROTECTED)
      | (1ULL << JavaScriptParser::PUBLIC)
      | (1ULL << JavaScriptParser::ABSTRACT)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::BYTE)
      | (1ULL << JavaScriptParser::CHAR)
      | (1ULL << JavaScriptParser::DOUBLE)
      | (1ULL << JavaScriptParser::FINAL)
      | (1ULL << JavaScriptParser::FLOAT)
      | (1ULL << JavaScriptParser::GOTO)
      | (1ULL << JavaScriptParser::INT)
      | (1ULL << JavaScriptParser::LONG)
      | (1ULL << JavaScriptParser::NATIVE)
      | (1ULL << JavaScriptParser::SHORT)
      | (1ULL << JavaScriptParser::SYNCHRONIZED)
      | (1ULL << JavaScriptParser::THROWS)
      | (1ULL << JavaScriptParser::TRANSIENT)
      | (1ULL << JavaScriptParser::VOLATILE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

JavaScriptParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::StringLiteralContext::STRING() {
  return getToken(JavaScriptParser::STRING, 0);
}


size_t JavaScriptParser::StringLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleStringLiteral;
}

void JavaScriptParser::StringLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringLiteral(this);
}

void JavaScriptParser::StringLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringLiteral(this);
}

JavaScriptParser::StringLiteralContext* JavaScriptParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 36, JavaScriptParser::RuleStringLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(361);
    match(JavaScriptParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericLiteralContext ------------------------------------------------------------------

JavaScriptParser::NumericLiteralContext::NumericLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::NumericLiteralContext::NUMBER() {
  return getToken(JavaScriptParser::NUMBER, 0);
}


size_t JavaScriptParser::NumericLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleNumericLiteral;
}

void JavaScriptParser::NumericLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericLiteral(this);
}

void JavaScriptParser::NumericLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericLiteral(this);
}

JavaScriptParser::NumericLiteralContext* JavaScriptParser::numericLiteral() {
  NumericLiteralContext *_localctx = _tracker.createInstance<NumericLiteralContext>(_ctx, getState());
  enterRule(_localctx, 38, JavaScriptParser::RuleNumericLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(363);
    match(JavaScriptParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerContext ------------------------------------------------------------------

JavaScriptParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::InitializerContext::ASSIGN() {
  return getToken(JavaScriptParser::ASSIGN, 0);
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::InitializerContext::assignmentExpression() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(0);
}


size_t JavaScriptParser::InitializerContext::getRuleIndex() const {
  return JavaScriptParser::RuleInitializer;
}

void JavaScriptParser::InitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializer(this);
}

void JavaScriptParser::InitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializer(this);
}

JavaScriptParser::InitializerContext* JavaScriptParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 40, JavaScriptParser::RuleInitializer);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(365);
    match(JavaScriptParser::ASSIGN);
    setState(366);
    assignmentExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmptyStatementContext ------------------------------------------------------------------

JavaScriptParser::EmptyStatementContext::EmptyStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::EmptyStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::EmptyStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleEmptyStatement;
}

void JavaScriptParser::EmptyStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmptyStatement(this);
}

void JavaScriptParser::EmptyStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmptyStatement(this);
}

JavaScriptParser::EmptyStatementContext* JavaScriptParser::emptyStatement() {
  EmptyStatementContext *_localctx = _tracker.createInstance<EmptyStatementContext>(_ctx, getState());
  enterRule(_localctx, 42, JavaScriptParser::RuleEmptyStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(368);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

JavaScriptParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ExpressionContext* JavaScriptParser::ExpressionStatementContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ExpressionStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::ExpressionStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleExpressionStatement;
}

void JavaScriptParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void JavaScriptParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}

JavaScriptParser::ExpressionStatementContext* JavaScriptParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 44, JavaScriptParser::RuleExpressionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(370);
    expression();
    setState(371);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

JavaScriptParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::IF() {
  return getToken(JavaScriptParser::IF, 0);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::IfStatementContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::IfStatementContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::ELSE() {
  return getToken(JavaScriptParser::ELSE, 0);
}


size_t JavaScriptParser::IfStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleIfStatement;
}

void JavaScriptParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void JavaScriptParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}

JavaScriptParser::IfStatementContext* JavaScriptParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 46, JavaScriptParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(373);
    match(JavaScriptParser::IF);
    setState(374);
    match(JavaScriptParser::LPAREN);
    setState(375);
    expression();
    setState(376);
    match(JavaScriptParser::RPAREN);
    setState(377);
    statement();
    setState(380);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(378);
      match(JavaScriptParser::ELSE);
      setState(379);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IterationStatementContext ------------------------------------------------------------------

JavaScriptParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::DO() {
  return getToken(JavaScriptParser::DO, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::IterationStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::WHILE() {
  return getToken(JavaScriptParser::WHILE, 0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

std::vector<JavaScriptParser::ExpressionContext *> JavaScriptParser::IterationStatementContext::expression() {
  return getRuleContexts<JavaScriptParser::ExpressionContext>();
}

JavaScriptParser::ExpressionContext* JavaScriptParser::IterationStatementContext::expression(size_t i) {
  return getRuleContext<JavaScriptParser::ExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> JavaScriptParser::IterationStatementContext::SEMICOLON() {
  return getTokens(JavaScriptParser::SEMICOLON);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::SEMICOLON(size_t i) {
  return getToken(JavaScriptParser::SEMICOLON, i);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::FOR() {
  return getToken(JavaScriptParser::FOR, 0);
}

JavaScriptParser::ExpressionNoInContext* JavaScriptParser::IterationStatementContext::expressionNoIn() {
  return getRuleContext<JavaScriptParser::ExpressionNoInContext>(0);
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::IterationStatementContext::variableDeclarationList() {
  return getRuleContext<JavaScriptParser::VariableDeclarationListContext>(0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::IN() {
  return getToken(JavaScriptParser::IN, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::IterationStatementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::BindingPatternContext* JavaScriptParser::IterationStatementContext::bindingPattern() {
  return getRuleContext<JavaScriptParser::BindingPatternContext>(0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::OF() {
  return getToken(JavaScriptParser::OF, 0);
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::IterationStatementContext::assignmentExpression() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(0);
}


size_t JavaScriptParser::IterationStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleIterationStatement;
}

void JavaScriptParser::IterationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIterationStatement(this);
}

void JavaScriptParser::IterationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIterationStatement(this);
}

JavaScriptParser::IterationStatementContext* JavaScriptParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 48, JavaScriptParser::RuleIterationStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(439);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(382);
      match(JavaScriptParser::DO);
      setState(383);
      statement();
      setState(384);
      match(JavaScriptParser::WHILE);
      setState(385);
      match(JavaScriptParser::LPAREN);
      setState(386);
      expression();
      setState(387);
      match(JavaScriptParser::RPAREN);
      setState(388);
      match(JavaScriptParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(390);
      match(JavaScriptParser::WHILE);
      setState(391);
      match(JavaScriptParser::LPAREN);
      setState(392);
      expression();
      setState(393);
      match(JavaScriptParser::RPAREN);
      setState(394);
      statement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(396);
      match(JavaScriptParser::FOR);
      setState(397);
      match(JavaScriptParser::LPAREN);
      setState(400);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(398);
        expressionNoIn();
        break;
      }

      case 2: {
        setState(399);
        variableDeclarationList();
        break;
      }

      default:
        break;
      }
      setState(402);
      match(JavaScriptParser::SEMICOLON);
      setState(404);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
        | (1ULL << JavaScriptParser::NEW)
        | (1ULL << JavaScriptParser::VOID)
        | (1ULL << JavaScriptParser::FUNCTION)
        | (1ULL << JavaScriptParser::THIS)
        | (1ULL << JavaScriptParser::DELETE)
        | (1ULL << JavaScriptParser::CLASS)
        | (1ULL << JavaScriptParser::SUPER)
        | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
        | (1ULL << (JavaScriptParser::LPAREN - 82))
        | (1ULL << (JavaScriptParser::LBRACE - 82))
        | (1ULL << (JavaScriptParser::LBRACKET - 82))
        | (1ULL << (JavaScriptParser::ASSIGN - 82))
        | (1ULL << (JavaScriptParser::BANG - 82))
        | (1ULL << (JavaScriptParser::TILDE - 82))
        | (1ULL << (JavaScriptParser::INC - 82))
        | (1ULL << (JavaScriptParser::DEC - 82))
        | (1ULL << (JavaScriptParser::ADD - 82))
        | (1ULL << (JavaScriptParser::SUB - 82))
        | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
        setState(403);
        expression();
      }
      setState(406);
      match(JavaScriptParser::SEMICOLON);
      setState(408);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
        | (1ULL << JavaScriptParser::NEW)
        | (1ULL << JavaScriptParser::VOID)
        | (1ULL << JavaScriptParser::FUNCTION)
        | (1ULL << JavaScriptParser::THIS)
        | (1ULL << JavaScriptParser::DELETE)
        | (1ULL << JavaScriptParser::CLASS)
        | (1ULL << JavaScriptParser::SUPER)
        | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
        | (1ULL << (JavaScriptParser::LPAREN - 82))
        | (1ULL << (JavaScriptParser::LBRACE - 82))
        | (1ULL << (JavaScriptParser::LBRACKET - 82))
        | (1ULL << (JavaScriptParser::ASSIGN - 82))
        | (1ULL << (JavaScriptParser::BANG - 82))
        | (1ULL << (JavaScriptParser::TILDE - 82))
        | (1ULL << (JavaScriptParser::INC - 82))
        | (1ULL << (JavaScriptParser::DEC - 82))
        | (1ULL << (JavaScriptParser::ADD - 82))
        | (1ULL << (JavaScriptParser::SUB - 82))
        | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
        setState(407);
        expression();
      }
      setState(410);
      match(JavaScriptParser::RPAREN);
      setState(411);
      statement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(412);
      match(JavaScriptParser::FOR);
      setState(413);
      match(JavaScriptParser::LPAREN);
      setState(416);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaScriptParser::IDENTIFIER: {
          setState(414);
          identifier();
          break;
        }

        case JavaScriptParser::LBRACE:
        case JavaScriptParser::LBRACKET: {
          setState(415);
          bindingPattern();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(418);
      match(JavaScriptParser::IN);
      setState(419);
      expression();
      setState(420);
      match(JavaScriptParser::RPAREN);
      setState(421);
      statement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(423);
      match(JavaScriptParser::FOR);
      setState(424);
      match(JavaScriptParser::LPAREN);
      setState(425);
      identifier();
      setState(426);
      match(JavaScriptParser::OF);
      setState(427);
      assignmentExpression();
      setState(428);
      match(JavaScriptParser::RPAREN);
      setState(429);
      statement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(431);
      match(JavaScriptParser::FOR);
      setState(432);
      match(JavaScriptParser::LPAREN);
      setState(433);
      identifier();
      setState(434);
      match(JavaScriptParser::OF);
      setState(435);
      assignmentExpression();
      setState(436);
      match(JavaScriptParser::RPAREN);
      setState(437);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

JavaScriptParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ContinueStatementContext::CONTINUE() {
  return getToken(JavaScriptParser::CONTINUE, 0);
}

tree::TerminalNode* JavaScriptParser::ContinueStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ContinueStatementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}


size_t JavaScriptParser::ContinueStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleContinueStatement;
}

void JavaScriptParser::ContinueStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStatement(this);
}

void JavaScriptParser::ContinueStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStatement(this);
}

JavaScriptParser::ContinueStatementContext* JavaScriptParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 50, JavaScriptParser::RuleContinueStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(441);
    match(JavaScriptParser::CONTINUE);
    setState(443);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::IDENTIFIER) {
      setState(442);
      identifier();
    }
    setState(445);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

JavaScriptParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::BreakStatementContext::BREAK() {
  return getToken(JavaScriptParser::BREAK, 0);
}

tree::TerminalNode* JavaScriptParser::BreakStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::BreakStatementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}


size_t JavaScriptParser::BreakStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleBreakStatement;
}

void JavaScriptParser::BreakStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStatement(this);
}

void JavaScriptParser::BreakStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStatement(this);
}

JavaScriptParser::BreakStatementContext* JavaScriptParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 52, JavaScriptParser::RuleBreakStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(447);
    match(JavaScriptParser::BREAK);
    setState(449);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::IDENTIFIER) {
      setState(448);
      identifier();
    }
    setState(451);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

JavaScriptParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ReturnStatementContext::RETURN() {
  return getToken(JavaScriptParser::RETURN, 0);
}

tree::TerminalNode* JavaScriptParser::ReturnStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::ReturnStatementContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}


size_t JavaScriptParser::ReturnStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleReturnStatement;
}

void JavaScriptParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void JavaScriptParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}

JavaScriptParser::ReturnStatementContext* JavaScriptParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 54, JavaScriptParser::RuleReturnStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(453);
    match(JavaScriptParser::RETURN);
    setState(455);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
      setState(454);
      expression();
    }
    setState(457);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- YieldStatementContext ------------------------------------------------------------------

JavaScriptParser::YieldStatementContext::YieldStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::YieldStatementContext::YIELD() {
  return getToken(JavaScriptParser::YIELD, 0);
}

tree::TerminalNode* JavaScriptParser::YieldStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::YieldStatementContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}


size_t JavaScriptParser::YieldStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleYieldStatement;
}

void JavaScriptParser::YieldStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterYieldStatement(this);
}

void JavaScriptParser::YieldStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitYieldStatement(this);
}

JavaScriptParser::YieldStatementContext* JavaScriptParser::yieldStatement() {
  YieldStatementContext *_localctx = _tracker.createInstance<YieldStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, JavaScriptParser::RuleYieldStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(459);
    match(JavaScriptParser::YIELD);
    setState(461);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
      setState(460);
      expression();
    }
    setState(463);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WithStatementContext ------------------------------------------------------------------

JavaScriptParser::WithStatementContext::WithStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::WITH() {
  return getToken(JavaScriptParser::WITH, 0);
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::WithStatementContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::WithStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}


size_t JavaScriptParser::WithStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleWithStatement;
}

void JavaScriptParser::WithStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWithStatement(this);
}

void JavaScriptParser::WithStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWithStatement(this);
}

JavaScriptParser::WithStatementContext* JavaScriptParser::withStatement() {
  WithStatementContext *_localctx = _tracker.createInstance<WithStatementContext>(_ctx, getState());
  enterRule(_localctx, 58, JavaScriptParser::RuleWithStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(465);
    match(JavaScriptParser::WITH);
    setState(466);
    match(JavaScriptParser::LPAREN);
    setState(467);
    expression();
    setState(468);
    match(JavaScriptParser::RPAREN);
    setState(469);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelledStatementContext ------------------------------------------------------------------

JavaScriptParser::LabelledStatementContext::LabelledStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::LabelledStatementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* JavaScriptParser::LabelledStatementContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::LabelledStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}


size_t JavaScriptParser::LabelledStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleLabelledStatement;
}

void JavaScriptParser::LabelledStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabelledStatement(this);
}

void JavaScriptParser::LabelledStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabelledStatement(this);
}

JavaScriptParser::LabelledStatementContext* JavaScriptParser::labelledStatement() {
  LabelledStatementContext *_localctx = _tracker.createInstance<LabelledStatementContext>(_ctx, getState());
  enterRule(_localctx, 60, JavaScriptParser::RuleLabelledStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(471);
    identifier();
    setState(472);
    match(JavaScriptParser::COLON);
    setState(473);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SwitchStatementContext ------------------------------------------------------------------

JavaScriptParser::SwitchStatementContext::SwitchStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::SWITCH() {
  return getToken(JavaScriptParser::SWITCH, 0);
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::SwitchStatementContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::CaseBlockContext* JavaScriptParser::SwitchStatementContext::caseBlock() {
  return getRuleContext<JavaScriptParser::CaseBlockContext>(0);
}


size_t JavaScriptParser::SwitchStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleSwitchStatement;
}

void JavaScriptParser::SwitchStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitchStatement(this);
}

void JavaScriptParser::SwitchStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitchStatement(this);
}

JavaScriptParser::SwitchStatementContext* JavaScriptParser::switchStatement() {
  SwitchStatementContext *_localctx = _tracker.createInstance<SwitchStatementContext>(_ctx, getState());
  enterRule(_localctx, 62, JavaScriptParser::RuleSwitchStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(475);
    match(JavaScriptParser::SWITCH);
    setState(476);
    match(JavaScriptParser::LPAREN);
    setState(477);
    expression();
    setState(478);
    match(JavaScriptParser::RPAREN);
    setState(479);
    caseBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseBlockContext ------------------------------------------------------------------

JavaScriptParser::CaseBlockContext::CaseBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CaseBlockContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::CaseBlockContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::CaseClausesContext *> JavaScriptParser::CaseBlockContext::caseClauses() {
  return getRuleContexts<JavaScriptParser::CaseClausesContext>();
}

JavaScriptParser::CaseClausesContext* JavaScriptParser::CaseBlockContext::caseClauses(size_t i) {
  return getRuleContext<JavaScriptParser::CaseClausesContext>(i);
}

JavaScriptParser::DefaultClauseContext* JavaScriptParser::CaseBlockContext::defaultClause() {
  return getRuleContext<JavaScriptParser::DefaultClauseContext>(0);
}


size_t JavaScriptParser::CaseBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseBlock;
}

void JavaScriptParser::CaseBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseBlock(this);
}

void JavaScriptParser::CaseBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseBlock(this);
}

JavaScriptParser::CaseBlockContext* JavaScriptParser::caseBlock() {
  CaseBlockContext *_localctx = _tracker.createInstance<CaseBlockContext>(_ctx, getState());
  enterRule(_localctx, 64, JavaScriptParser::RuleCaseBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(481);
    match(JavaScriptParser::LBRACE);
    setState(483);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::CASE) {
      setState(482);
      caseClauses();
    }
    setState(489);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::DEFAULT) {
      setState(485);
      defaultClause();
      setState(487);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::CASE) {
        setState(486);
        caseClauses();
      }
    }
    setState(491);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClausesContext ------------------------------------------------------------------

JavaScriptParser::CaseClausesContext::CaseClausesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::CaseClauseContext *> JavaScriptParser::CaseClausesContext::caseClause() {
  return getRuleContexts<JavaScriptParser::CaseClauseContext>();
}

JavaScriptParser::CaseClauseContext* JavaScriptParser::CaseClausesContext::caseClause(size_t i) {
  return getRuleContext<JavaScriptParser::CaseClauseContext>(i);
}


size_t JavaScriptParser::CaseClausesContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseClauses;
}

void JavaScriptParser::CaseClausesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseClauses(this);
}

void JavaScriptParser::CaseClausesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseClauses(this);
}

JavaScriptParser::CaseClausesContext* JavaScriptParser::caseClauses() {
  CaseClausesContext *_localctx = _tracker.createInstance<CaseClausesContext>(_ctx, getState());
  enterRule(_localctx, 66, JavaScriptParser::RuleCaseClauses);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(494); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(493);
      caseClause();
      setState(496); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == JavaScriptParser::CASE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClauseContext ------------------------------------------------------------------

JavaScriptParser::CaseClauseContext::CaseClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CaseClauseContext::CASE() {
  return getToken(JavaScriptParser::CASE, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::CaseClauseContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::CaseClauseContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

JavaScriptParser::StatementListContext* JavaScriptParser::CaseClauseContext::statementList() {
  return getRuleContext<JavaScriptParser::StatementListContext>(0);
}


size_t JavaScriptParser::CaseClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseClause;
}

void JavaScriptParser::CaseClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseClause(this);
}

void JavaScriptParser::CaseClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseClause(this);
}

JavaScriptParser::CaseClauseContext* JavaScriptParser::caseClause() {
  CaseClauseContext *_localctx = _tracker.createInstance<CaseClauseContext>(_ctx, getState());
  enterRule(_localctx, 68, JavaScriptParser::RuleCaseClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(498);
    match(JavaScriptParser::CASE);
    setState(499);
    expression();
    setState(500);
    match(JavaScriptParser::COLON);
    setState(502);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::SEMICOLON - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
      setState(501);
      statementList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefaultClauseContext ------------------------------------------------------------------

JavaScriptParser::DefaultClauseContext::DefaultClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::DefaultClauseContext::DEFAULT() {
  return getToken(JavaScriptParser::DEFAULT, 0);
}

tree::TerminalNode* JavaScriptParser::DefaultClauseContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

JavaScriptParser::StatementListContext* JavaScriptParser::DefaultClauseContext::statementList() {
  return getRuleContext<JavaScriptParser::StatementListContext>(0);
}


size_t JavaScriptParser::DefaultClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleDefaultClause;
}

void JavaScriptParser::DefaultClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefaultClause(this);
}

void JavaScriptParser::DefaultClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefaultClause(this);
}

JavaScriptParser::DefaultClauseContext* JavaScriptParser::defaultClause() {
  DefaultClauseContext *_localctx = _tracker.createInstance<DefaultClauseContext>(_ctx, getState());
  enterRule(_localctx, 70, JavaScriptParser::RuleDefaultClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(504);
    match(JavaScriptParser::DEFAULT);
    setState(505);
    match(JavaScriptParser::COLON);
    setState(507);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::SEMICOLON - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
      setState(506);
      statementList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThrowStatementContext ------------------------------------------------------------------

JavaScriptParser::ThrowStatementContext::ThrowStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ThrowStatementContext::THROW() {
  return getToken(JavaScriptParser::THROW, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::ThrowStatementContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ThrowStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::ThrowStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleThrowStatement;
}

void JavaScriptParser::ThrowStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThrowStatement(this);
}

void JavaScriptParser::ThrowStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThrowStatement(this);
}

JavaScriptParser::ThrowStatementContext* JavaScriptParser::throwStatement() {
  ThrowStatementContext *_localctx = _tracker.createInstance<ThrowStatementContext>(_ctx, getState());
  enterRule(_localctx, 72, JavaScriptParser::RuleThrowStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(509);
    match(JavaScriptParser::THROW);
    setState(510);
    expression();
    setState(511);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TryStatementContext ------------------------------------------------------------------

JavaScriptParser::TryStatementContext::TryStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::TryStatementContext::TRY() {
  return getToken(JavaScriptParser::TRY, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::TryStatementContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::CatchBlockContext* JavaScriptParser::TryStatementContext::catchBlock() {
  return getRuleContext<JavaScriptParser::CatchBlockContext>(0);
}

JavaScriptParser::FinallyBlockContext* JavaScriptParser::TryStatementContext::finallyBlock() {
  return getRuleContext<JavaScriptParser::FinallyBlockContext>(0);
}


size_t JavaScriptParser::TryStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleTryStatement;
}

void JavaScriptParser::TryStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTryStatement(this);
}

void JavaScriptParser::TryStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTryStatement(this);
}

JavaScriptParser::TryStatementContext* JavaScriptParser::tryStatement() {
  TryStatementContext *_localctx = _tracker.createInstance<TryStatementContext>(_ctx, getState());
  enterRule(_localctx, 74, JavaScriptParser::RuleTryStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(526);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(513);
      match(JavaScriptParser::TRY);
      setState(514);
      block();
      setState(516);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::CATCH) {
        setState(515);
        catchBlock();
      }
      setState(519);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::FINALLY) {
        setState(518);
        finallyBlock();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(521);
      match(JavaScriptParser::TRY);
      setState(522);
      block();
      setState(523);
      catchBlock();
      setState(524);
      finallyBlock();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CatchBlockContext ------------------------------------------------------------------

JavaScriptParser::CatchBlockContext::CatchBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CatchBlockContext::CATCH() {
  return getToken(JavaScriptParser::CATCH, 0);
}

tree::TerminalNode* JavaScriptParser::CatchBlockContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::CatchBlockContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::CatchBlockContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::CatchBlockContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::BindingPatternContext* JavaScriptParser::CatchBlockContext::bindingPattern() {
  return getRuleContext<JavaScriptParser::BindingPatternContext>(0);
}


size_t JavaScriptParser::CatchBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleCatchBlock;
}

void JavaScriptParser::CatchBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCatchBlock(this);
}

void JavaScriptParser::CatchBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCatchBlock(this);
}

JavaScriptParser::CatchBlockContext* JavaScriptParser::catchBlock() {
  CatchBlockContext *_localctx = _tracker.createInstance<CatchBlockContext>(_ctx, getState());
  enterRule(_localctx, 76, JavaScriptParser::RuleCatchBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(528);
    match(JavaScriptParser::CATCH);
    setState(529);
    match(JavaScriptParser::LPAREN);
    setState(532);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        setState(530);
        identifier();
        break;
      }

      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET: {
        setState(531);
        bindingPattern();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(534);
    match(JavaScriptParser::RPAREN);
    setState(535);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FinallyBlockContext ------------------------------------------------------------------

JavaScriptParser::FinallyBlockContext::FinallyBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FinallyBlockContext::FINALLY() {
  return getToken(JavaScriptParser::FINALLY, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::FinallyBlockContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}


size_t JavaScriptParser::FinallyBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleFinallyBlock;
}

void JavaScriptParser::FinallyBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFinallyBlock(this);
}

void JavaScriptParser::FinallyBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFinallyBlock(this);
}

JavaScriptParser::FinallyBlockContext* JavaScriptParser::finallyBlock() {
  FinallyBlockContext *_localctx = _tracker.createInstance<FinallyBlockContext>(_ctx, getState());
  enterRule(_localctx, 78, JavaScriptParser::RuleFinallyBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(537);
    match(JavaScriptParser::FINALLY);
    setState(538);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DebuggerStatementContext ------------------------------------------------------------------

JavaScriptParser::DebuggerStatementContext::DebuggerStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::DebuggerStatementContext::DEBUGGER() {
  return getToken(JavaScriptParser::DEBUGGER, 0);
}

tree::TerminalNode* JavaScriptParser::DebuggerStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::DebuggerStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleDebuggerStatement;
}

void JavaScriptParser::DebuggerStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDebuggerStatement(this);
}

void JavaScriptParser::DebuggerStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDebuggerStatement(this);
}

JavaScriptParser::DebuggerStatementContext* JavaScriptParser::debuggerStatement() {
  DebuggerStatementContext *_localctx = _tracker.createInstance<DebuggerStatementContext>(_ctx, getState());
  enterRule(_localctx, 80, JavaScriptParser::RuleDebuggerStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(540);
    match(JavaScriptParser::DEBUGGER);
    setState(541);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

JavaScriptParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::FUNCTION() {
  return getToken(JavaScriptParser::FUNCTION, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::FunctionDeclarationContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::FunctionDeclarationContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::FunctionDeclarationContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::FunctionDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleFunctionDeclaration;
}

void JavaScriptParser::FunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDeclaration(this);
}

void JavaScriptParser::FunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDeclaration(this);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 82, JavaScriptParser::RuleFunctionDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(543);
    match(JavaScriptParser::FUNCTION);
    setState(544);
    identifier();
    setState(545);
    match(JavaScriptParser::LPAREN);
    setState(547);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 82)))) != 0)) {
      setState(546);
      formalParameterList();
    }
    setState(549);
    match(JavaScriptParser::RPAREN);
    setState(550);
    match(JavaScriptParser::LBRACE);
    setState(551);
    functionBody();
    setState(552);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterListContext ------------------------------------------------------------------

JavaScriptParser::FormalParameterListContext::FormalParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::FormalParameterArgContext *> JavaScriptParser::FormalParameterListContext::formalParameterArg() {
  return getRuleContexts<JavaScriptParser::FormalParameterArgContext>();
}

JavaScriptParser::FormalParameterArgContext* JavaScriptParser::FormalParameterListContext::formalParameterArg(size_t i) {
  return getRuleContext<JavaScriptParser::FormalParameterArgContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::FormalParameterListContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::FormalParameterListContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::FormalParameterListContext::getRuleIndex() const {
  return JavaScriptParser::RuleFormalParameterList;
}

void JavaScriptParser::FormalParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameterList(this);
}

void JavaScriptParser::FormalParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameterList(this);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::formalParameterList() {
  FormalParameterListContext *_localctx = _tracker.createInstance<FormalParameterListContext>(_ctx, getState());
  enterRule(_localctx, 84, JavaScriptParser::RuleFormalParameterList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(554);
    formalParameterArg();
    setState(559);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(555);
      match(JavaScriptParser::COMMA);
      setState(556);
      formalParameterArg();
      setState(561);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterArgContext ------------------------------------------------------------------

JavaScriptParser::FormalParameterArgContext::FormalParameterArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::FormalParameterArgContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::BindingPatternContext* JavaScriptParser::FormalParameterArgContext::bindingPattern() {
  return getRuleContext<JavaScriptParser::BindingPatternContext>(0);
}

tree::TerminalNode* JavaScriptParser::FormalParameterArgContext::ELLIPSIS() {
  return getToken(JavaScriptParser::ELLIPSIS, 0);
}


size_t JavaScriptParser::FormalParameterArgContext::getRuleIndex() const {
  return JavaScriptParser::RuleFormalParameterArg;
}

void JavaScriptParser::FormalParameterArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameterArg(this);
}

void JavaScriptParser::FormalParameterArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameterArg(this);
}

JavaScriptParser::FormalParameterArgContext* JavaScriptParser::formalParameterArg() {
  FormalParameterArgContext *_localctx = _tracker.createInstance<FormalParameterArgContext>(_ctx, getState());
  enterRule(_localctx, 86, JavaScriptParser::RuleFormalParameterArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(569);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(562);
        identifier();
        break;
      }

      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(563);
        bindingPattern();
        break;
      }

      case JavaScriptParser::ELLIPSIS: {
        enterOuterAlt(_localctx, 3);
        setState(564);
        match(JavaScriptParser::ELLIPSIS);
        setState(567);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case JavaScriptParser::IDENTIFIER: {
            setState(565);
            identifier();
            break;
          }

          case JavaScriptParser::LBRACE:
          case JavaScriptParser::LBRACKET: {
            setState(566);
            bindingPattern();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionBodyContext ------------------------------------------------------------------

JavaScriptParser::FunctionBodyContext::FunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::SourceElementsContext* JavaScriptParser::FunctionBodyContext::sourceElements() {
  return getRuleContext<JavaScriptParser::SourceElementsContext>(0);
}


size_t JavaScriptParser::FunctionBodyContext::getRuleIndex() const {
  return JavaScriptParser::RuleFunctionBody;
}

void JavaScriptParser::FunctionBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionBody(this);
}

void JavaScriptParser::FunctionBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionBody(this);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::functionBody() {
  FunctionBodyContext *_localctx = _tracker.createInstance<FunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 88, JavaScriptParser::RuleFunctionBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(572);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::SEMICOLON - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
      setState(571);
      sourceElements();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclarationContext ------------------------------------------------------------------

JavaScriptParser::ClassDeclarationContext::ClassDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ClassDeclarationContext::CLASS() {
  return getToken(JavaScriptParser::CLASS, 0);
}

std::vector<JavaScriptParser::IdentifierContext *> JavaScriptParser::ClassDeclarationContext::identifier() {
  return getRuleContexts<JavaScriptParser::IdentifierContext>();
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ClassDeclarationContext::identifier(size_t i) {
  return getRuleContext<JavaScriptParser::IdentifierContext>(i);
}

tree::TerminalNode* JavaScriptParser::ClassDeclarationContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::ClassDeclarationContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::ClassDeclarationContext::EXTENDS() {
  return getToken(JavaScriptParser::EXTENDS, 0);
}

JavaScriptParser::ClassBodyContext* JavaScriptParser::ClassDeclarationContext::classBody() {
  return getRuleContext<JavaScriptParser::ClassBodyContext>(0);
}


size_t JavaScriptParser::ClassDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassDeclaration;
}

void JavaScriptParser::ClassDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDeclaration(this);
}

void JavaScriptParser::ClassDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDeclaration(this);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::classDeclaration() {
  ClassDeclarationContext *_localctx = _tracker.createInstance<ClassDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 90, JavaScriptParser::RuleClassDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(574);
    match(JavaScriptParser::CLASS);
    setState(575);
    identifier();
    setState(578);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::EXTENDS) {
      setState(576);
      match(JavaScriptParser::EXTENDS);
      setState(577);
      identifier();
    }
    setState(580);
    match(JavaScriptParser::LBRACE);
    setState(582);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::IMPLEMENTS)
      | (1ULL << JavaScriptParser::INTERFACE)
      | (1ULL << JavaScriptParser::PACKAGE)
      | (1ULL << JavaScriptParser::PRIVATE)
      | (1ULL << JavaScriptParser::PROTECTED)
      | (1ULL << JavaScriptParser::PUBLIC)
      | (1ULL << JavaScriptParser::ABSTRACT)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::BYTE)
      | (1ULL << JavaScriptParser::CHAR)
      | (1ULL << JavaScriptParser::DOUBLE)
      | (1ULL << JavaScriptParser::FINAL)
      | (1ULL << JavaScriptParser::FLOAT)
      | (1ULL << JavaScriptParser::GOTO)
      | (1ULL << JavaScriptParser::INT)
      | (1ULL << JavaScriptParser::LONG)
      | (1ULL << JavaScriptParser::NATIVE)
      | (1ULL << JavaScriptParser::SHORT)
      | (1ULL << JavaScriptParser::SYNCHRONIZED)
      | (1ULL << JavaScriptParser::THROWS)
      | (1ULL << JavaScriptParser::TRANSIENT)
      | (1ULL << JavaScriptParser::VOLATILE)
      | (1ULL << JavaScriptParser::NULL))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::TRUE - 64))
      | (1ULL << (JavaScriptParser::FALSE - 64))
      | (1ULL << (JavaScriptParser::GET - 64))
      | (1ULL << (JavaScriptParser::SET - 64))
      | (1ULL << (JavaScriptParser::STRING - 64))
      | (1ULL << (JavaScriptParser::NUMBER - 64))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 64)))) != 0)) {
      setState(581);
      classBody();
    }
    setState(584);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassBodyContext ------------------------------------------------------------------

JavaScriptParser::ClassBodyContext::ClassBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::ClassElementContext *> JavaScriptParser::ClassBodyContext::classElement() {
  return getRuleContexts<JavaScriptParser::ClassElementContext>();
}

JavaScriptParser::ClassElementContext* JavaScriptParser::ClassBodyContext::classElement(size_t i) {
  return getRuleContext<JavaScriptParser::ClassElementContext>(i);
}


size_t JavaScriptParser::ClassBodyContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassBody;
}

void JavaScriptParser::ClassBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassBody(this);
}

void JavaScriptParser::ClassBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassBody(this);
}

JavaScriptParser::ClassBodyContext* JavaScriptParser::classBody() {
  ClassBodyContext *_localctx = _tracker.createInstance<ClassBodyContext>(_ctx, getState());
  enterRule(_localctx, 92, JavaScriptParser::RuleClassBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(587); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(586);
      classElement();
      setState(589); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::IMPLEMENTS)
      | (1ULL << JavaScriptParser::INTERFACE)
      | (1ULL << JavaScriptParser::PACKAGE)
      | (1ULL << JavaScriptParser::PRIVATE)
      | (1ULL << JavaScriptParser::PROTECTED)
      | (1ULL << JavaScriptParser::PUBLIC)
      | (1ULL << JavaScriptParser::ABSTRACT)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::BYTE)
      | (1ULL << JavaScriptParser::CHAR)
      | (1ULL << JavaScriptParser::DOUBLE)
      | (1ULL << JavaScriptParser::FINAL)
      | (1ULL << JavaScriptParser::FLOAT)
      | (1ULL << JavaScriptParser::GOTO)
      | (1ULL << JavaScriptParser::INT)
      | (1ULL << JavaScriptParser::LONG)
      | (1ULL << JavaScriptParser::NATIVE)
      | (1ULL << JavaScriptParser::SHORT)
      | (1ULL << JavaScriptParser::SYNCHRONIZED)
      | (1ULL << JavaScriptParser::THROWS)
      | (1ULL << JavaScriptParser::TRANSIENT)
      | (1ULL << JavaScriptParser::VOLATILE)
      | (1ULL << JavaScriptParser::NULL))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::TRUE - 64))
      | (1ULL << (JavaScriptParser::FALSE - 64))
      | (1ULL << (JavaScriptParser::GET - 64))
      | (1ULL << (JavaScriptParser::SET - 64))
      | (1ULL << (JavaScriptParser::STRING - 64))
      | (1ULL << (JavaScriptParser::NUMBER - 64))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 64)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassElementContext ------------------------------------------------------------------

JavaScriptParser::ClassElementContext::ClassElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::MethodDefinitionContext* JavaScriptParser::ClassElementContext::methodDefinition() {
  return getRuleContext<JavaScriptParser::MethodDefinitionContext>(0);
}


size_t JavaScriptParser::ClassElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassElement;
}

void JavaScriptParser::ClassElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassElement(this);
}

void JavaScriptParser::ClassElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassElement(this);
}

JavaScriptParser::ClassElementContext* JavaScriptParser::classElement() {
  ClassElementContext *_localctx = _tracker.createInstance<ClassElementContext>(_ctx, getState());
  enterRule(_localctx, 94, JavaScriptParser::RuleClassElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(591);
    methodDefinition();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodDefinitionContext ------------------------------------------------------------------

JavaScriptParser::MethodDefinitionContext::MethodDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::MethodDefinitionContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::MethodDefinitionContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::MethodDefinitionContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::GET() {
  return getToken(JavaScriptParser::GET, 0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::SET() {
  return getToken(JavaScriptParser::SET, 0);
}


size_t JavaScriptParser::MethodDefinitionContext::getRuleIndex() const {
  return JavaScriptParser::RuleMethodDefinition;
}

void JavaScriptParser::MethodDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodDefinition(this);
}

void JavaScriptParser::MethodDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodDefinition(this);
}

JavaScriptParser::MethodDefinitionContext* JavaScriptParser::methodDefinition() {
  MethodDefinitionContext *_localctx = _tracker.createInstance<MethodDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 96, JavaScriptParser::RuleMethodDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(594);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::GET

    || _la == JavaScriptParser::SET) {
      setState(593);
      _la = _input->LA(1);
      if (!(_la == JavaScriptParser::GET

      || _la == JavaScriptParser::SET)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(596);
    propertyName();
    setState(597);
    match(JavaScriptParser::LPAREN);
    setState(599);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 82)))) != 0)) {
      setState(598);
      formalParameterList();
    }
    setState(601);
    match(JavaScriptParser::RPAREN);
    setState(602);
    match(JavaScriptParser::LBRACE);
    setState(603);
    functionBody();
    setState(604);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

JavaScriptParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ImportStatementContext::IMPORT() {
  return getToken(JavaScriptParser::IMPORT, 0);
}

JavaScriptParser::ImportClauseContext* JavaScriptParser::ImportStatementContext::importClause() {
  return getRuleContext<JavaScriptParser::ImportClauseContext>(0);
}

JavaScriptParser::FromClauseContext* JavaScriptParser::ImportStatementContext::fromClause() {
  return getRuleContext<JavaScriptParser::FromClauseContext>(0);
}

tree::TerminalNode* JavaScriptParser::ImportStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::ModuleSpecifierContext* JavaScriptParser::ImportStatementContext::moduleSpecifier() {
  return getRuleContext<JavaScriptParser::ModuleSpecifierContext>(0);
}


size_t JavaScriptParser::ImportStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportStatement;
}

void JavaScriptParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void JavaScriptParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}

JavaScriptParser::ImportStatementContext* JavaScriptParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 98, JavaScriptParser::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(615);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(606);
      match(JavaScriptParser::IMPORT);
      setState(607);
      importClause();
      setState(608);
      fromClause();
      setState(609);
      match(JavaScriptParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(611);
      match(JavaScriptParser::IMPORT);
      setState(612);
      moduleSpecifier();
      setState(613);
      match(JavaScriptParser::SEMICOLON);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportClauseContext ------------------------------------------------------------------

JavaScriptParser::ImportClauseContext::ImportClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::DefaultImportContext* JavaScriptParser::ImportClauseContext::defaultImport() {
  return getRuleContext<JavaScriptParser::DefaultImportContext>(0);
}

JavaScriptParser::NameSpaceImportContext* JavaScriptParser::ImportClauseContext::nameSpaceImport() {
  return getRuleContext<JavaScriptParser::NameSpaceImportContext>(0);
}

JavaScriptParser::NamedImportsContext* JavaScriptParser::ImportClauseContext::namedImports() {
  return getRuleContext<JavaScriptParser::NamedImportsContext>(0);
}

tree::TerminalNode* JavaScriptParser::ImportClauseContext::COMMA() {
  return getToken(JavaScriptParser::COMMA, 0);
}


size_t JavaScriptParser::ImportClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportClause;
}

void JavaScriptParser::ImportClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportClause(this);
}

void JavaScriptParser::ImportClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportClause(this);
}

JavaScriptParser::ImportClauseContext* JavaScriptParser::importClause() {
  ImportClauseContext *_localctx = _tracker.createInstance<ImportClauseContext>(_ctx, getState());
  enterRule(_localctx, 100, JavaScriptParser::RuleImportClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(628);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(617);
      defaultImport();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(618);
      nameSpaceImport();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(619);
      namedImports();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(620);
      defaultImport();
      setState(621);
      match(JavaScriptParser::COMMA);
      setState(622);
      nameSpaceImport();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(624);
      defaultImport();
      setState(625);
      match(JavaScriptParser::COMMA);
      setState(626);
      namedImports();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefaultImportContext ------------------------------------------------------------------

JavaScriptParser::DefaultImportContext::DefaultImportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::DefaultImportContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}


size_t JavaScriptParser::DefaultImportContext::getRuleIndex() const {
  return JavaScriptParser::RuleDefaultImport;
}

void JavaScriptParser::DefaultImportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefaultImport(this);
}

void JavaScriptParser::DefaultImportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefaultImport(this);
}

JavaScriptParser::DefaultImportContext* JavaScriptParser::defaultImport() {
  DefaultImportContext *_localctx = _tracker.createInstance<DefaultImportContext>(_ctx, getState());
  enterRule(_localctx, 102, JavaScriptParser::RuleDefaultImport);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(630);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameSpaceImportContext ------------------------------------------------------------------

JavaScriptParser::NameSpaceImportContext::NameSpaceImportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::NameSpaceImportContext::ASTERISK() {
  return getToken(JavaScriptParser::ASTERISK, 0);
}

tree::TerminalNode* JavaScriptParser::NameSpaceImportContext::AS() {
  return getToken(JavaScriptParser::AS, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::NameSpaceImportContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}


size_t JavaScriptParser::NameSpaceImportContext::getRuleIndex() const {
  return JavaScriptParser::RuleNameSpaceImport;
}

void JavaScriptParser::NameSpaceImportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNameSpaceImport(this);
}

void JavaScriptParser::NameSpaceImportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNameSpaceImport(this);
}

JavaScriptParser::NameSpaceImportContext* JavaScriptParser::nameSpaceImport() {
  NameSpaceImportContext *_localctx = _tracker.createInstance<NameSpaceImportContext>(_ctx, getState());
  enterRule(_localctx, 104, JavaScriptParser::RuleNameSpaceImport);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(632);
    match(JavaScriptParser::ASTERISK);
    setState(633);
    match(JavaScriptParser::AS);
    setState(634);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamedImportsContext ------------------------------------------------------------------

JavaScriptParser::NamedImportsContext::NamedImportsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::NamedImportsContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::NamedImportsContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::ImportSpecifierContext *> JavaScriptParser::NamedImportsContext::importSpecifier() {
  return getRuleContexts<JavaScriptParser::ImportSpecifierContext>();
}

JavaScriptParser::ImportSpecifierContext* JavaScriptParser::NamedImportsContext::importSpecifier(size_t i) {
  return getRuleContext<JavaScriptParser::ImportSpecifierContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::NamedImportsContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::NamedImportsContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::NamedImportsContext::getRuleIndex() const {
  return JavaScriptParser::RuleNamedImports;
}

void JavaScriptParser::NamedImportsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamedImports(this);
}

void JavaScriptParser::NamedImportsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamedImports(this);
}

JavaScriptParser::NamedImportsContext* JavaScriptParser::namedImports() {
  NamedImportsContext *_localctx = _tracker.createInstance<NamedImportsContext>(_ctx, getState());
  enterRule(_localctx, 106, JavaScriptParser::RuleNamedImports);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(636);
    match(JavaScriptParser::LBRACE);
    setState(645);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::IMPLEMENTS)
      | (1ULL << JavaScriptParser::INTERFACE)
      | (1ULL << JavaScriptParser::PACKAGE)
      | (1ULL << JavaScriptParser::PRIVATE)
      | (1ULL << JavaScriptParser::PROTECTED)
      | (1ULL << JavaScriptParser::PUBLIC)
      | (1ULL << JavaScriptParser::ABSTRACT)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::BYTE)
      | (1ULL << JavaScriptParser::CHAR)
      | (1ULL << JavaScriptParser::DOUBLE)
      | (1ULL << JavaScriptParser::FINAL)
      | (1ULL << JavaScriptParser::FLOAT)
      | (1ULL << JavaScriptParser::GOTO)
      | (1ULL << JavaScriptParser::INT)
      | (1ULL << JavaScriptParser::LONG)
      | (1ULL << JavaScriptParser::NATIVE)
      | (1ULL << JavaScriptParser::SHORT)
      | (1ULL << JavaScriptParser::SYNCHRONIZED)
      | (1ULL << JavaScriptParser::THROWS)
      | (1ULL << JavaScriptParser::TRANSIENT)
      | (1ULL << JavaScriptParser::VOLATILE)
      | (1ULL << JavaScriptParser::NULL))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::TRUE - 64))
      | (1ULL << (JavaScriptParser::FALSE - 64))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 64)))) != 0)) {
      setState(637);
      importSpecifier();
      setState(642);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaScriptParser::COMMA) {
        setState(638);
        match(JavaScriptParser::COMMA);
        setState(639);
        importSpecifier();
        setState(644);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(647);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportSpecifierContext ------------------------------------------------------------------

JavaScriptParser::ImportSpecifierContext::ImportSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ImportSpecifierContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::ImportSpecifierContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::ImportSpecifierContext::AS() {
  return getToken(JavaScriptParser::AS, 0);
}


size_t JavaScriptParser::ImportSpecifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportSpecifier;
}

void JavaScriptParser::ImportSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportSpecifier(this);
}

void JavaScriptParser::ImportSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportSpecifier(this);
}

JavaScriptParser::ImportSpecifierContext* JavaScriptParser::importSpecifier() {
  ImportSpecifierContext *_localctx = _tracker.createInstance<ImportSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 108, JavaScriptParser::RuleImportSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(654);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(649);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(650);
      identifierName();
      setState(651);
      match(JavaScriptParser::AS);
      setState(652);
      identifier();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FromClauseContext ------------------------------------------------------------------

JavaScriptParser::FromClauseContext::FromClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FromClauseContext::FROM() {
  return getToken(JavaScriptParser::FROM, 0);
}

JavaScriptParser::ModuleSpecifierContext* JavaScriptParser::FromClauseContext::moduleSpecifier() {
  return getRuleContext<JavaScriptParser::ModuleSpecifierContext>(0);
}


size_t JavaScriptParser::FromClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleFromClause;
}

void JavaScriptParser::FromClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromClause(this);
}

void JavaScriptParser::FromClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromClause(this);
}

JavaScriptParser::FromClauseContext* JavaScriptParser::fromClause() {
  FromClauseContext *_localctx = _tracker.createInstance<FromClauseContext>(_ctx, getState());
  enterRule(_localctx, 110, JavaScriptParser::RuleFromClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(656);
    match(JavaScriptParser::FROM);
    setState(657);
    moduleSpecifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModuleSpecifierContext ------------------------------------------------------------------

JavaScriptParser::ModuleSpecifierContext::ModuleSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::StringLiteralContext* JavaScriptParser::ModuleSpecifierContext::stringLiteral() {
  return getRuleContext<JavaScriptParser::StringLiteralContext>(0);
}


size_t JavaScriptParser::ModuleSpecifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleModuleSpecifier;
}

void JavaScriptParser::ModuleSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModuleSpecifier(this);
}

void JavaScriptParser::ModuleSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModuleSpecifier(this);
}

JavaScriptParser::ModuleSpecifierContext* JavaScriptParser::moduleSpecifier() {
  ModuleSpecifierContext *_localctx = _tracker.createInstance<ModuleSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 112, JavaScriptParser::RuleModuleSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(659);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportStatementContext ------------------------------------------------------------------

JavaScriptParser::ExportStatementContext::ExportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ExportStatementContext::EXPORT() {
  return getToken(JavaScriptParser::EXPORT, 0);
}

JavaScriptParser::ExportClauseContext* JavaScriptParser::ExportStatementContext::exportClause() {
  return getRuleContext<JavaScriptParser::ExportClauseContext>(0);
}

tree::TerminalNode* JavaScriptParser::ExportStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::FromClauseContext* JavaScriptParser::ExportStatementContext::fromClause() {
  return getRuleContext<JavaScriptParser::FromClauseContext>(0);
}

JavaScriptParser::DefaultExportContext* JavaScriptParser::ExportStatementContext::defaultExport() {
  return getRuleContext<JavaScriptParser::DefaultExportContext>(0);
}

tree::TerminalNode* JavaScriptParser::ExportStatementContext::COMMA() {
  return getToken(JavaScriptParser::COMMA, 0);
}


size_t JavaScriptParser::ExportStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportStatement;
}

void JavaScriptParser::ExportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportStatement(this);
}

void JavaScriptParser::ExportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportStatement(this);
}

JavaScriptParser::ExportStatementContext* JavaScriptParser::exportStatement() {
  ExportStatementContext *_localctx = _tracker.createInstance<ExportStatementContext>(_ctx, getState());
  enterRule(_localctx, 114, JavaScriptParser::RuleExportStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(679);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(661);
      match(JavaScriptParser::EXPORT);
      setState(662);
      exportClause();
      setState(664);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::FROM) {
        setState(663);
        fromClause();
      }
      setState(666);
      match(JavaScriptParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(668);
      match(JavaScriptParser::EXPORT);
      setState(669);
      defaultExport();
      setState(672);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::COMMA) {
        setState(670);
        match(JavaScriptParser::COMMA);
        setState(671);
        exportClause();
      }
      setState(675);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::FROM) {
        setState(674);
        fromClause();
      }
      setState(677);
      match(JavaScriptParser::SEMICOLON);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportClauseContext ------------------------------------------------------------------

JavaScriptParser::ExportClauseContext::ExportClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ExportClauseContext::ASTERISK() {
  return getToken(JavaScriptParser::ASTERISK, 0);
}

JavaScriptParser::NameSpaceImportContext* JavaScriptParser::ExportClauseContext::nameSpaceImport() {
  return getRuleContext<JavaScriptParser::NameSpaceImportContext>(0);
}

JavaScriptParser::NamedExportsContext* JavaScriptParser::ExportClauseContext::namedExports() {
  return getRuleContext<JavaScriptParser::NamedExportsContext>(0);
}


size_t JavaScriptParser::ExportClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportClause;
}

void JavaScriptParser::ExportClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportClause(this);
}

void JavaScriptParser::ExportClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportClause(this);
}

JavaScriptParser::ExportClauseContext* JavaScriptParser::exportClause() {
  ExportClauseContext *_localctx = _tracker.createInstance<ExportClauseContext>(_ctx, getState());
  enterRule(_localctx, 116, JavaScriptParser::RuleExportClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(684);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(681);
      match(JavaScriptParser::ASTERISK);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(682);
      nameSpaceImport();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(683);
      namedExports();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamedExportsContext ------------------------------------------------------------------

JavaScriptParser::NamedExportsContext::NamedExportsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::NamedExportsContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::NamedExportsContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::ExportSpecifierContext *> JavaScriptParser::NamedExportsContext::exportSpecifier() {
  return getRuleContexts<JavaScriptParser::ExportSpecifierContext>();
}

JavaScriptParser::ExportSpecifierContext* JavaScriptParser::NamedExportsContext::exportSpecifier(size_t i) {
  return getRuleContext<JavaScriptParser::ExportSpecifierContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::NamedExportsContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::NamedExportsContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::NamedExportsContext::getRuleIndex() const {
  return JavaScriptParser::RuleNamedExports;
}

void JavaScriptParser::NamedExportsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamedExports(this);
}

void JavaScriptParser::NamedExportsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamedExports(this);
}

JavaScriptParser::NamedExportsContext* JavaScriptParser::namedExports() {
  NamedExportsContext *_localctx = _tracker.createInstance<NamedExportsContext>(_ctx, getState());
  enterRule(_localctx, 118, JavaScriptParser::RuleNamedExports);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(686);
    match(JavaScriptParser::LBRACE);
    setState(695);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::IMPLEMENTS)
      | (1ULL << JavaScriptParser::INTERFACE)
      | (1ULL << JavaScriptParser::PACKAGE)
      | (1ULL << JavaScriptParser::PRIVATE)
      | (1ULL << JavaScriptParser::PROTECTED)
      | (1ULL << JavaScriptParser::PUBLIC)
      | (1ULL << JavaScriptParser::ABSTRACT)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::BYTE)
      | (1ULL << JavaScriptParser::CHAR)
      | (1ULL << JavaScriptParser::DOUBLE)
      | (1ULL << JavaScriptParser::FINAL)
      | (1ULL << JavaScriptParser::FLOAT)
      | (1ULL << JavaScriptParser::GOTO)
      | (1ULL << JavaScriptParser::INT)
      | (1ULL << JavaScriptParser::LONG)
      | (1ULL << JavaScriptParser::NATIVE)
      | (1ULL << JavaScriptParser::SHORT)
      | (1ULL << JavaScriptParser::SYNCHRONIZED)
      | (1ULL << JavaScriptParser::THROWS)
      | (1ULL << JavaScriptParser::TRANSIENT)
      | (1ULL << JavaScriptParser::VOLATILE)
      | (1ULL << JavaScriptParser::NULL))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::TRUE - 64))
      | (1ULL << (JavaScriptParser::FALSE - 64))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 64)))) != 0)) {
      setState(687);
      exportSpecifier();
      setState(692);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaScriptParser::COMMA) {
        setState(688);
        match(JavaScriptParser::COMMA);
        setState(689);
        exportSpecifier();
        setState(694);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(697);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportSpecifierContext ------------------------------------------------------------------

JavaScriptParser::ExportSpecifierContext::ExportSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ExportSpecifierContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::ExportSpecifierContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::ExportSpecifierContext::AS() {
  return getToken(JavaScriptParser::AS, 0);
}


size_t JavaScriptParser::ExportSpecifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportSpecifier;
}

void JavaScriptParser::ExportSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportSpecifier(this);
}

void JavaScriptParser::ExportSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportSpecifier(this);
}

JavaScriptParser::ExportSpecifierContext* JavaScriptParser::exportSpecifier() {
  ExportSpecifierContext *_localctx = _tracker.createInstance<ExportSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 120, JavaScriptParser::RuleExportSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(704);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(699);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(700);
      identifierName();
      setState(701);
      match(JavaScriptParser::AS);
      setState(702);
      identifier();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefaultExportContext ------------------------------------------------------------------

JavaScriptParser::DefaultExportContext::DefaultExportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::DefaultExportContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::DefaultExportContext::functionDeclaration() {
  return getRuleContext<JavaScriptParser::FunctionDeclarationContext>(0);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::DefaultExportContext::classDeclaration() {
  return getRuleContext<JavaScriptParser::ClassDeclarationContext>(0);
}


size_t JavaScriptParser::DefaultExportContext::getRuleIndex() const {
  return JavaScriptParser::RuleDefaultExport;
}

void JavaScriptParser::DefaultExportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefaultExport(this);
}

void JavaScriptParser::DefaultExportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefaultExport(this);
}

JavaScriptParser::DefaultExportContext* JavaScriptParser::defaultExport() {
  DefaultExportContext *_localctx = _tracker.createInstance<DefaultExportContext>(_ctx, getState());
  enterRule(_localctx, 122, JavaScriptParser::RuleDefaultExport);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(709);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(706);
        identifier();
        break;
      }

      case JavaScriptParser::FUNCTION: {
        enterOuterAlt(_localctx, 2);
        setState(707);
        functionDeclaration();
        break;
      }

      case JavaScriptParser::CLASS: {
        enterOuterAlt(_localctx, 3);
        setState(708);
        classDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

JavaScriptParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::AssignmentExpressionContext *> JavaScriptParser::ExpressionContext::assignmentExpression() {
  return getRuleContexts<JavaScriptParser::AssignmentExpressionContext>();
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::ExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ExpressionContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ExpressionContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleExpression;
}

void JavaScriptParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void JavaScriptParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 124, JavaScriptParser::RuleExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(711);
    assignmentExpression();
    setState(716);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(712);
      match(JavaScriptParser::COMMA);
      setState(713);
      assignmentExpression();
      setState(718);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

JavaScriptParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ConditionalExpressionContext* JavaScriptParser::AssignmentExpressionContext::conditionalExpression() {
  return getRuleContext<JavaScriptParser::ConditionalExpressionContext>(0);
}

JavaScriptParser::YieldExpressionContext* JavaScriptParser::AssignmentExpressionContext::yieldExpression() {
  return getRuleContext<JavaScriptParser::YieldExpressionContext>(0);
}

JavaScriptParser::ArrowFunctionContext* JavaScriptParser::AssignmentExpressionContext::arrowFunction() {
  return getRuleContext<JavaScriptParser::ArrowFunctionContext>(0);
}

JavaScriptParser::AssignmentOperatorContext* JavaScriptParser::AssignmentExpressionContext::assignmentOperator() {
  return getRuleContext<JavaScriptParser::AssignmentOperatorContext>(0);
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::AssignmentExpressionContext::assignmentExpression() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(0);
}


size_t JavaScriptParser::AssignmentExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleAssignmentExpression;
}

void JavaScriptParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}

void JavaScriptParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 126, JavaScriptParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(725);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(719);
      conditionalExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(720);
      yieldExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(721);
      arrowFunction();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(722);
      assignmentOperator();
      setState(723);
      assignmentExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentOperatorContext ------------------------------------------------------------------

JavaScriptParser::AssignmentOperatorContext::AssignmentOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::ASSIGN() {
  return getToken(JavaScriptParser::ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::MUL_ASSIGN() {
  return getToken(JavaScriptParser::MUL_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::DIV_ASSIGN() {
  return getToken(JavaScriptParser::DIV_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::MOD_ASSIGN() {
  return getToken(JavaScriptParser::MOD_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::ADD_ASSIGN() {
  return getToken(JavaScriptParser::ADD_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::SUB_ASSIGN() {
  return getToken(JavaScriptParser::SUB_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::LSHIFT_ASSIGN() {
  return getToken(JavaScriptParser::LSHIFT_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::RSHIFT_ASSIGN() {
  return getToken(JavaScriptParser::RSHIFT_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::URSHIFT_ASSIGN() {
  return getToken(JavaScriptParser::URSHIFT_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::AND_ASSIGN() {
  return getToken(JavaScriptParser::AND_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::XOR_ASSIGN() {
  return getToken(JavaScriptParser::XOR_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::OR_ASSIGN() {
  return getToken(JavaScriptParser::OR_ASSIGN, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::POWER_ASSIGN() {
  return getToken(JavaScriptParser::POWER_ASSIGN, 0);
}


size_t JavaScriptParser::AssignmentOperatorContext::getRuleIndex() const {
  return JavaScriptParser::RuleAssignmentOperator;
}

void JavaScriptParser::AssignmentOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperator(this);
}

void JavaScriptParser::AssignmentOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperator(this);
}

JavaScriptParser::AssignmentOperatorContext* JavaScriptParser::assignmentOperator() {
  AssignmentOperatorContext *_localctx = _tracker.createInstance<AssignmentOperatorContext>(_ctx, getState());
  enterRule(_localctx, 128, JavaScriptParser::RuleAssignmentOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(727);
    _la = _input->LA(1);
    if (!(((((_la - 93) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 93)) & ((1ULL << (JavaScriptParser::ASSIGN - 93))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 93))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 93)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalExpressionContext ------------------------------------------------------------------

JavaScriptParser::ConditionalExpressionContext::ConditionalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::LogicalORExpressionContext* JavaScriptParser::ConditionalExpressionContext::logicalORExpression() {
  return getRuleContext<JavaScriptParser::LogicalORExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ConditionalExpressionContext::QUESTION() {
  return getToken(JavaScriptParser::QUESTION, 0);
}

std::vector<JavaScriptParser::AssignmentExpressionContext *> JavaScriptParser::ConditionalExpressionContext::assignmentExpression() {
  return getRuleContexts<JavaScriptParser::AssignmentExpressionContext>();
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::ConditionalExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::ConditionalExpressionContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}


size_t JavaScriptParser::ConditionalExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleConditionalExpression;
}

void JavaScriptParser::ConditionalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalExpression(this);
}

void JavaScriptParser::ConditionalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalExpression(this);
}

JavaScriptParser::ConditionalExpressionContext* JavaScriptParser::conditionalExpression() {
  ConditionalExpressionContext *_localctx = _tracker.createInstance<ConditionalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 130, JavaScriptParser::RuleConditionalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(729);
    logicalORExpression();
    setState(735);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::QUESTION) {
      setState(730);
      match(JavaScriptParser::QUESTION);
      setState(731);
      assignmentExpression();
      setState(732);
      match(JavaScriptParser::COLON);
      setState(733);
      assignmentExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalORExpressionContext ------------------------------------------------------------------

JavaScriptParser::LogicalORExpressionContext::LogicalORExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::LogicalANDExpressionContext *> JavaScriptParser::LogicalORExpressionContext::logicalANDExpression() {
  return getRuleContexts<JavaScriptParser::LogicalANDExpressionContext>();
}

JavaScriptParser::LogicalANDExpressionContext* JavaScriptParser::LogicalORExpressionContext::logicalANDExpression(size_t i) {
  return getRuleContext<JavaScriptParser::LogicalANDExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::LogicalORExpressionContext::OR() {
  return getTokens(JavaScriptParser::OR);
}

tree::TerminalNode* JavaScriptParser::LogicalORExpressionContext::OR(size_t i) {
  return getToken(JavaScriptParser::OR, i);
}


size_t JavaScriptParser::LogicalORExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleLogicalORExpression;
}

void JavaScriptParser::LogicalORExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalORExpression(this);
}

void JavaScriptParser::LogicalORExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalORExpression(this);
}

JavaScriptParser::LogicalORExpressionContext* JavaScriptParser::logicalORExpression() {
  LogicalORExpressionContext *_localctx = _tracker.createInstance<LogicalORExpressionContext>(_ctx, getState());
  enterRule(_localctx, 132, JavaScriptParser::RuleLogicalORExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(737);
    logicalANDExpression();
    setState(742);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::OR) {
      setState(738);
      match(JavaScriptParser::OR);
      setState(739);
      logicalANDExpression();
      setState(744);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalANDExpressionContext ------------------------------------------------------------------

JavaScriptParser::LogicalANDExpressionContext::LogicalANDExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::BitwiseORExpressionContext *> JavaScriptParser::LogicalANDExpressionContext::bitwiseORExpression() {
  return getRuleContexts<JavaScriptParser::BitwiseORExpressionContext>();
}

JavaScriptParser::BitwiseORExpressionContext* JavaScriptParser::LogicalANDExpressionContext::bitwiseORExpression(size_t i) {
  return getRuleContext<JavaScriptParser::BitwiseORExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::LogicalANDExpressionContext::AND() {
  return getTokens(JavaScriptParser::AND);
}

tree::TerminalNode* JavaScriptParser::LogicalANDExpressionContext::AND(size_t i) {
  return getToken(JavaScriptParser::AND, i);
}


size_t JavaScriptParser::LogicalANDExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleLogicalANDExpression;
}

void JavaScriptParser::LogicalANDExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalANDExpression(this);
}

void JavaScriptParser::LogicalANDExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalANDExpression(this);
}

JavaScriptParser::LogicalANDExpressionContext* JavaScriptParser::logicalANDExpression() {
  LogicalANDExpressionContext *_localctx = _tracker.createInstance<LogicalANDExpressionContext>(_ctx, getState());
  enterRule(_localctx, 134, JavaScriptParser::RuleLogicalANDExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(745);
    bitwiseORExpression();
    setState(750);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::AND) {
      setState(746);
      match(JavaScriptParser::AND);
      setState(747);
      bitwiseORExpression();
      setState(752);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseORExpressionContext ------------------------------------------------------------------

JavaScriptParser::BitwiseORExpressionContext::BitwiseORExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::BitwiseXORExpressionContext *> JavaScriptParser::BitwiseORExpressionContext::bitwiseXORExpression() {
  return getRuleContexts<JavaScriptParser::BitwiseXORExpressionContext>();
}

JavaScriptParser::BitwiseXORExpressionContext* JavaScriptParser::BitwiseORExpressionContext::bitwiseXORExpression(size_t i) {
  return getRuleContext<JavaScriptParser::BitwiseXORExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::BitwiseORExpressionContext::BITOR() {
  return getTokens(JavaScriptParser::BITOR);
}

tree::TerminalNode* JavaScriptParser::BitwiseORExpressionContext::BITOR(size_t i) {
  return getToken(JavaScriptParser::BITOR, i);
}


size_t JavaScriptParser::BitwiseORExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleBitwiseORExpression;
}

void JavaScriptParser::BitwiseORExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseORExpression(this);
}

void JavaScriptParser::BitwiseORExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseORExpression(this);
}

JavaScriptParser::BitwiseORExpressionContext* JavaScriptParser::bitwiseORExpression() {
  BitwiseORExpressionContext *_localctx = _tracker.createInstance<BitwiseORExpressionContext>(_ctx, getState());
  enterRule(_localctx, 136, JavaScriptParser::RuleBitwiseORExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(753);
    bitwiseXORExpression();
    setState(758);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::BITOR) {
      setState(754);
      match(JavaScriptParser::BITOR);
      setState(755);
      bitwiseXORExpression();
      setState(760);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseXORExpressionContext ------------------------------------------------------------------

JavaScriptParser::BitwiseXORExpressionContext::BitwiseXORExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::BitwiseANDExpressionContext *> JavaScriptParser::BitwiseXORExpressionContext::bitwiseANDExpression() {
  return getRuleContexts<JavaScriptParser::BitwiseANDExpressionContext>();
}

JavaScriptParser::BitwiseANDExpressionContext* JavaScriptParser::BitwiseXORExpressionContext::bitwiseANDExpression(size_t i) {
  return getRuleContext<JavaScriptParser::BitwiseANDExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::BitwiseXORExpressionContext::CARET() {
  return getTokens(JavaScriptParser::CARET);
}

tree::TerminalNode* JavaScriptParser::BitwiseXORExpressionContext::CARET(size_t i) {
  return getToken(JavaScriptParser::CARET, i);
}


size_t JavaScriptParser::BitwiseXORExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleBitwiseXORExpression;
}

void JavaScriptParser::BitwiseXORExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseXORExpression(this);
}

void JavaScriptParser::BitwiseXORExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseXORExpression(this);
}

JavaScriptParser::BitwiseXORExpressionContext* JavaScriptParser::bitwiseXORExpression() {
  BitwiseXORExpressionContext *_localctx = _tracker.createInstance<BitwiseXORExpressionContext>(_ctx, getState());
  enterRule(_localctx, 138, JavaScriptParser::RuleBitwiseXORExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(761);
    bitwiseANDExpression();
    setState(766);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::CARET) {
      setState(762);
      match(JavaScriptParser::CARET);
      setState(763);
      bitwiseANDExpression();
      setState(768);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseANDExpressionContext ------------------------------------------------------------------

JavaScriptParser::BitwiseANDExpressionContext::BitwiseANDExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::EqualityExpressionContext *> JavaScriptParser::BitwiseANDExpressionContext::equalityExpression() {
  return getRuleContexts<JavaScriptParser::EqualityExpressionContext>();
}

JavaScriptParser::EqualityExpressionContext* JavaScriptParser::BitwiseANDExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<JavaScriptParser::EqualityExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::BitwiseANDExpressionContext::BITAND() {
  return getTokens(JavaScriptParser::BITAND);
}

tree::TerminalNode* JavaScriptParser::BitwiseANDExpressionContext::BITAND(size_t i) {
  return getToken(JavaScriptParser::BITAND, i);
}


size_t JavaScriptParser::BitwiseANDExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleBitwiseANDExpression;
}

void JavaScriptParser::BitwiseANDExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseANDExpression(this);
}

void JavaScriptParser::BitwiseANDExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseANDExpression(this);
}

JavaScriptParser::BitwiseANDExpressionContext* JavaScriptParser::bitwiseANDExpression() {
  BitwiseANDExpressionContext *_localctx = _tracker.createInstance<BitwiseANDExpressionContext>(_ctx, getState());
  enterRule(_localctx, 140, JavaScriptParser::RuleBitwiseANDExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(769);
    equalityExpression();
    setState(774);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::BITAND) {
      setState(770);
      match(JavaScriptParser::BITAND);
      setState(771);
      equalityExpression();
      setState(776);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

JavaScriptParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::RelationalExpressionContext *> JavaScriptParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<JavaScriptParser::RelationalExpressionContext>();
}

JavaScriptParser::RelationalExpressionContext* JavaScriptParser::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<JavaScriptParser::RelationalExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::EqualityExpressionContext::EQUAL() {
  return getTokens(JavaScriptParser::EQUAL);
}

tree::TerminalNode* JavaScriptParser::EqualityExpressionContext::EQUAL(size_t i) {
  return getToken(JavaScriptParser::EQUAL, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::EqualityExpressionContext::NOTEQUAL() {
  return getTokens(JavaScriptParser::NOTEQUAL);
}

tree::TerminalNode* JavaScriptParser::EqualityExpressionContext::NOTEQUAL(size_t i) {
  return getToken(JavaScriptParser::NOTEQUAL, i);
}


size_t JavaScriptParser::EqualityExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleEqualityExpression;
}

void JavaScriptParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void JavaScriptParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}

JavaScriptParser::EqualityExpressionContext* JavaScriptParser::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 142, JavaScriptParser::RuleEqualityExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(777);
    relationalExpression();
    setState(782);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::EQUAL

    || _la == JavaScriptParser::NOTEQUAL) {
      setState(778);
      _la = _input->LA(1);
      if (!(_la == JavaScriptParser::EQUAL

      || _la == JavaScriptParser::NOTEQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(779);
      relationalExpression();
      setState(784);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

JavaScriptParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::ShiftExpressionContext *> JavaScriptParser::RelationalExpressionContext::shiftExpression() {
  return getRuleContexts<JavaScriptParser::ShiftExpressionContext>();
}

JavaScriptParser::ShiftExpressionContext* JavaScriptParser::RelationalExpressionContext::shiftExpression(size_t i) {
  return getRuleContext<JavaScriptParser::ShiftExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionContext::LT() {
  return getTokens(JavaScriptParser::LT);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::LT(size_t i) {
  return getToken(JavaScriptParser::LT, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionContext::GT() {
  return getTokens(JavaScriptParser::GT);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::GT(size_t i) {
  return getToken(JavaScriptParser::GT, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionContext::LE() {
  return getTokens(JavaScriptParser::LE);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::LE(size_t i) {
  return getToken(JavaScriptParser::LE, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionContext::GE() {
  return getTokens(JavaScriptParser::GE);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::GE(size_t i) {
  return getToken(JavaScriptParser::GE, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionContext::INSTANCEOF() {
  return getTokens(JavaScriptParser::INSTANCEOF);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::INSTANCEOF(size_t i) {
  return getToken(JavaScriptParser::INSTANCEOF, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionContext::IN() {
  return getTokens(JavaScriptParser::IN);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::IN(size_t i) {
  return getToken(JavaScriptParser::IN, i);
}


size_t JavaScriptParser::RelationalExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleRelationalExpression;
}

void JavaScriptParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void JavaScriptParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}

JavaScriptParser::RelationalExpressionContext* JavaScriptParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 144, JavaScriptParser::RuleRelationalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(785);
    shiftExpression();
    setState(790);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::INSTANCEOF

    || _la == JavaScriptParser::IN || ((((_la - 94) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 94)) & ((1ULL << (JavaScriptParser::GT - 94))
      | (1ULL << (JavaScriptParser::LT - 94))
      | (1ULL << (JavaScriptParser::LE - 94))
      | (1ULL << (JavaScriptParser::GE - 94)))) != 0)) {
      setState(786);
      _la = _input->LA(1);
      if (!(_la == JavaScriptParser::INSTANCEOF

      || _la == JavaScriptParser::IN || ((((_la - 94) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 94)) & ((1ULL << (JavaScriptParser::GT - 94))
        | (1ULL << (JavaScriptParser::LT - 94))
        | (1ULL << (JavaScriptParser::LE - 94))
        | (1ULL << (JavaScriptParser::GE - 94)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(787);
      shiftExpression();
      setState(792);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftExpressionContext ------------------------------------------------------------------

JavaScriptParser::ShiftExpressionContext::ShiftExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::AdditiveExpressionContext *> JavaScriptParser::ShiftExpressionContext::additiveExpression() {
  return getRuleContexts<JavaScriptParser::AdditiveExpressionContext>();
}

JavaScriptParser::AdditiveExpressionContext* JavaScriptParser::ShiftExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<JavaScriptParser::AdditiveExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ShiftExpressionContext::LSHIFT() {
  return getTokens(JavaScriptParser::LSHIFT);
}

tree::TerminalNode* JavaScriptParser::ShiftExpressionContext::LSHIFT(size_t i) {
  return getToken(JavaScriptParser::LSHIFT, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ShiftExpressionContext::RSHIFT() {
  return getTokens(JavaScriptParser::RSHIFT);
}

tree::TerminalNode* JavaScriptParser::ShiftExpressionContext::RSHIFT(size_t i) {
  return getToken(JavaScriptParser::RSHIFT, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ShiftExpressionContext::URSHIFT() {
  return getTokens(JavaScriptParser::URSHIFT);
}

tree::TerminalNode* JavaScriptParser::ShiftExpressionContext::URSHIFT(size_t i) {
  return getToken(JavaScriptParser::URSHIFT, i);
}


size_t JavaScriptParser::ShiftExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleShiftExpression;
}

void JavaScriptParser::ShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpression(this);
}

void JavaScriptParser::ShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpression(this);
}

JavaScriptParser::ShiftExpressionContext* JavaScriptParser::shiftExpression() {
  ShiftExpressionContext *_localctx = _tracker.createInstance<ShiftExpressionContext>(_ctx, getState());
  enterRule(_localctx, 146, JavaScriptParser::RuleShiftExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(793);
    additiveExpression();
    setState(798);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 113) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 113)) & ((1ULL << (JavaScriptParser::LSHIFT - 113))
      | (1ULL << (JavaScriptParser::RSHIFT - 113))
      | (1ULL << (JavaScriptParser::URSHIFT - 113)))) != 0)) {
      setState(794);
      _la = _input->LA(1);
      if (!(((((_la - 113) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 113)) & ((1ULL << (JavaScriptParser::LSHIFT - 113))
        | (1ULL << (JavaScriptParser::RSHIFT - 113))
        | (1ULL << (JavaScriptParser::URSHIFT - 113)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(795);
      additiveExpression();
      setState(800);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

JavaScriptParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::MultiplicativeExpressionContext* JavaScriptParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContext<JavaScriptParser::MultiplicativeExpressionContext>(0);
}

std::vector<JavaScriptParser::AdditiveExpressionContext *> JavaScriptParser::AdditiveExpressionContext::additiveExpression() {
  return getRuleContexts<JavaScriptParser::AdditiveExpressionContext>();
}

JavaScriptParser::AdditiveExpressionContext* JavaScriptParser::AdditiveExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<JavaScriptParser::AdditiveExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::AdditiveExpressionContext::ADD() {
  return getTokens(JavaScriptParser::ADD);
}

tree::TerminalNode* JavaScriptParser::AdditiveExpressionContext::ADD(size_t i) {
  return getToken(JavaScriptParser::ADD, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::AdditiveExpressionContext::SUB() {
  return getTokens(JavaScriptParser::SUB);
}

tree::TerminalNode* JavaScriptParser::AdditiveExpressionContext::SUB(size_t i) {
  return getToken(JavaScriptParser::SUB, i);
}


size_t JavaScriptParser::AdditiveExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleAdditiveExpression;
}

void JavaScriptParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void JavaScriptParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}

JavaScriptParser::AdditiveExpressionContext* JavaScriptParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 148, JavaScriptParser::RuleAdditiveExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(801);
    multiplicativeExpression();
    setState(806);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(802);
        _la = _input->LA(1);
        if (!(_la == JavaScriptParser::ADD

        || _la == JavaScriptParser::SUB)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(803);
        additiveExpression(); 
      }
      setState(808);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

JavaScriptParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::UnaryExpressionContext *> JavaScriptParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<JavaScriptParser::UnaryExpressionContext>();
}

JavaScriptParser::UnaryExpressionContext* JavaScriptParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<JavaScriptParser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::MultiplicativeExpressionContext::MUL() {
  return getTokens(JavaScriptParser::MUL);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionContext::MUL(size_t i) {
  return getToken(JavaScriptParser::MUL, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::MultiplicativeExpressionContext::DIV() {
  return getTokens(JavaScriptParser::DIV);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionContext::DIV(size_t i) {
  return getToken(JavaScriptParser::DIV, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::MultiplicativeExpressionContext::MOD() {
  return getTokens(JavaScriptParser::MOD);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionContext::MOD(size_t i) {
  return getToken(JavaScriptParser::MOD, i);
}


size_t JavaScriptParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleMultiplicativeExpression;
}

void JavaScriptParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void JavaScriptParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}

JavaScriptParser::MultiplicativeExpressionContext* JavaScriptParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 150, JavaScriptParser::RuleMultiplicativeExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(809);
    unaryExpression();
    setState(814);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 103) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 103)) & ((1ULL << (JavaScriptParser::MUL - 103))
      | (1ULL << (JavaScriptParser::DIV - 103))
      | (1ULL << (JavaScriptParser::MOD - 103)))) != 0)) {
      setState(810);
      _la = _input->LA(1);
      if (!(((((_la - 103) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 103)) & ((1ULL << (JavaScriptParser::MUL - 103))
        | (1ULL << (JavaScriptParser::DIV - 103))
        | (1ULL << (JavaScriptParser::MOD - 103)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(811);
      unaryExpression();
      setState(816);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

JavaScriptParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::UnaryOperatorContext* JavaScriptParser::UnaryExpressionContext::unaryOperator() {
  return getRuleContext<JavaScriptParser::UnaryOperatorContext>(0);
}

JavaScriptParser::UnaryExpressionContext* JavaScriptParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<JavaScriptParser::UnaryExpressionContext>(0);
}

JavaScriptParser::PostfixExpressionContext* JavaScriptParser::UnaryExpressionContext::postfixExpression() {
  return getRuleContext<JavaScriptParser::PostfixExpressionContext>(0);
}


size_t JavaScriptParser::UnaryExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleUnaryExpression;
}

void JavaScriptParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void JavaScriptParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}

JavaScriptParser::UnaryExpressionContext* JavaScriptParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 152, JavaScriptParser::RuleUnaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(821);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::VOID:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::BANG:
      case JavaScriptParser::TILDE:
      case JavaScriptParser::INC:
      case JavaScriptParser::DEC:
      case JavaScriptParser::ADD:
      case JavaScriptParser::SUB: {
        enterOuterAlt(_localctx, 1);
        setState(817);
        unaryOperator();
        setState(818);
        unaryExpression();
        break;
      }

      case JavaScriptParser::NEW:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::CLASS:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::IDENTIFIER:
      case JavaScriptParser::LPAREN:
      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(820);
        postfixExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOperatorContext ------------------------------------------------------------------

JavaScriptParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::DELETE() {
  return getToken(JavaScriptParser::DELETE, 0);
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::VOID() {
  return getToken(JavaScriptParser::VOID, 0);
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::TYPEOF() {
  return getToken(JavaScriptParser::TYPEOF, 0);
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::INC() {
  return getToken(JavaScriptParser::INC, 0);
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::DEC() {
  return getToken(JavaScriptParser::DEC, 0);
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::ADD() {
  return getToken(JavaScriptParser::ADD, 0);
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::SUB() {
  return getToken(JavaScriptParser::SUB, 0);
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::BANG() {
  return getToken(JavaScriptParser::BANG, 0);
}

tree::TerminalNode* JavaScriptParser::UnaryOperatorContext::TILDE() {
  return getToken(JavaScriptParser::TILDE, 0);
}


size_t JavaScriptParser::UnaryOperatorContext::getRuleIndex() const {
  return JavaScriptParser::RuleUnaryOperator;
}

void JavaScriptParser::UnaryOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOperator(this);
}

void JavaScriptParser::UnaryOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOperator(this);
}

JavaScriptParser::UnaryOperatorContext* JavaScriptParser::unaryOperator() {
  UnaryOperatorContext *_localctx = _tracker.createInstance<UnaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 154, JavaScriptParser::RuleUnaryOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(823);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::DELETE))) != 0) || ((((_la - 96) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 96)) & ((1ULL << (JavaScriptParser::BANG - 96))
      | (1ULL << (JavaScriptParser::TILDE - 96))
      | (1ULL << (JavaScriptParser::INC - 96))
      | (1ULL << (JavaScriptParser::DEC - 96))
      | (1ULL << (JavaScriptParser::ADD - 96))
      | (1ULL << (JavaScriptParser::SUB - 96)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixExpressionContext ------------------------------------------------------------------

JavaScriptParser::PostfixExpressionContext::PostfixExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::LeftHandSideExpressionContext* JavaScriptParser::PostfixExpressionContext::leftHandSideExpression() {
  return getRuleContext<JavaScriptParser::LeftHandSideExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::PostfixExpressionContext::INC() {
  return getToken(JavaScriptParser::INC, 0);
}

tree::TerminalNode* JavaScriptParser::PostfixExpressionContext::DEC() {
  return getToken(JavaScriptParser::DEC, 0);
}


size_t JavaScriptParser::PostfixExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RulePostfixExpression;
}

void JavaScriptParser::PostfixExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostfixExpression(this);
}

void JavaScriptParser::PostfixExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostfixExpression(this);
}

JavaScriptParser::PostfixExpressionContext* JavaScriptParser::postfixExpression() {
  PostfixExpressionContext *_localctx = _tracker.createInstance<PostfixExpressionContext>(_ctx, getState());
  enterRule(_localctx, 156, JavaScriptParser::RulePostfixExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(825);
    leftHandSideExpression();
    setState(827);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::INC

    || _la == JavaScriptParser::DEC) {
      setState(826);
      _la = _input->LA(1);
      if (!(_la == JavaScriptParser::INC

      || _la == JavaScriptParser::DEC)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LeftHandSideExpressionContext ------------------------------------------------------------------

JavaScriptParser::LeftHandSideExpressionContext::LeftHandSideExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::CallExpressionContext* JavaScriptParser::LeftHandSideExpressionContext::callExpression() {
  return getRuleContext<JavaScriptParser::CallExpressionContext>(0);
}

JavaScriptParser::NewExpressionContext* JavaScriptParser::LeftHandSideExpressionContext::newExpression() {
  return getRuleContext<JavaScriptParser::NewExpressionContext>(0);
}


size_t JavaScriptParser::LeftHandSideExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleLeftHandSideExpression;
}

void JavaScriptParser::LeftHandSideExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLeftHandSideExpression(this);
}

void JavaScriptParser::LeftHandSideExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLeftHandSideExpression(this);
}

JavaScriptParser::LeftHandSideExpressionContext* JavaScriptParser::leftHandSideExpression() {
  LeftHandSideExpressionContext *_localctx = _tracker.createInstance<LeftHandSideExpressionContext>(_ctx, getState());
  enterRule(_localctx, 158, JavaScriptParser::RuleLeftHandSideExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(831);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(829);
      callExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(830);
      newExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallExpressionContext ------------------------------------------------------------------

JavaScriptParser::CallExpressionContext::CallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::SuperPropertyContext* JavaScriptParser::CallExpressionContext::superProperty() {
  return getRuleContext<JavaScriptParser::SuperPropertyContext>(0);
}

JavaScriptParser::FunctionExpressionContext* JavaScriptParser::CallExpressionContext::functionExpression() {
  return getRuleContext<JavaScriptParser::FunctionExpressionContext>(0);
}

JavaScriptParser::ClassExpressionContext* JavaScriptParser::CallExpressionContext::classExpression() {
  return getRuleContext<JavaScriptParser::ClassExpressionContext>(0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::CallExpressionContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::ThisExpressionContext* JavaScriptParser::CallExpressionContext::thisExpression() {
  return getRuleContext<JavaScriptParser::ThisExpressionContext>(0);
}

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::CallExpressionContext::arrayLiteral() {
  return getRuleContext<JavaScriptParser::ArrayLiteralContext>(0);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::CallExpressionContext::objectLiteral() {
  return getRuleContext<JavaScriptParser::ObjectLiteralContext>(0);
}

JavaScriptParser::ParenthesizedExpressionContext* JavaScriptParser::CallExpressionContext::parenthesizedExpression() {
  return getRuleContext<JavaScriptParser::ParenthesizedExpressionContext>(0);
}

JavaScriptParser::NewExpressionContext* JavaScriptParser::CallExpressionContext::newExpression() {
  return getRuleContext<JavaScriptParser::NewExpressionContext>(0);
}

JavaScriptParser::CallExpressionContext* JavaScriptParser::CallExpressionContext::callExpression() {
  return getRuleContext<JavaScriptParser::CallExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::CallExpressionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::CallExpressionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::ArgumentsContext* JavaScriptParser::CallExpressionContext::arguments() {
  return getRuleContext<JavaScriptParser::ArgumentsContext>(0);
}

tree::TerminalNode* JavaScriptParser::CallExpressionContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::CallExpressionContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::CallExpressionContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::CallExpressionContext::DOT() {
  return getToken(JavaScriptParser::DOT, 0);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::CallExpressionContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

JavaScriptParser::TemplateLiteralContext* JavaScriptParser::CallExpressionContext::templateLiteral() {
  return getRuleContext<JavaScriptParser::TemplateLiteralContext>(0);
}


size_t JavaScriptParser::CallExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleCallExpression;
}

void JavaScriptParser::CallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallExpression(this);
}

void JavaScriptParser::CallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallExpression(this);
}


JavaScriptParser::CallExpressionContext* JavaScriptParser::callExpression() {
   return callExpression(0);
}

JavaScriptParser::CallExpressionContext* JavaScriptParser::callExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  JavaScriptParser::CallExpressionContext *_localctx = _tracker.createInstance<CallExpressionContext>(_ctx, parentState);
  JavaScriptParser::CallExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 160;
  enterRecursionRule(_localctx, 160, JavaScriptParser::RuleCallExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(843);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx)) {
    case 1: {
      setState(834);
      superProperty();
      break;
    }

    case 2: {
      setState(835);
      functionExpression();
      break;
    }

    case 3: {
      setState(836);
      classExpression();
      break;
    }

    case 4: {
      setState(837);
      identifier();
      break;
    }

    case 5: {
      setState(838);
      thisExpression();
      break;
    }

    case 6: {
      setState(839);
      arrayLiteral();
      break;
    }

    case 7: {
      setState(840);
      objectLiteral();
      break;
    }

    case 8: {
      setState(841);
      parenthesizedExpression();
      break;
    }

    case 9: {
      setState(842);
      newExpression();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(863);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(861);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<CallExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCallExpression);
          setState(845);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(846);
          match(JavaScriptParser::LPAREN);
          setState(848);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
            | (1ULL << JavaScriptParser::NEW)
            | (1ULL << JavaScriptParser::VOID)
            | (1ULL << JavaScriptParser::FUNCTION)
            | (1ULL << JavaScriptParser::THIS)
            | (1ULL << JavaScriptParser::DELETE)
            | (1ULL << JavaScriptParser::CLASS)
            | (1ULL << JavaScriptParser::SUPER)
            | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
            | (1ULL << (JavaScriptParser::LPAREN - 82))
            | (1ULL << (JavaScriptParser::LBRACE - 82))
            | (1ULL << (JavaScriptParser::LBRACKET - 82))
            | (1ULL << (JavaScriptParser::ASSIGN - 82))
            | (1ULL << (JavaScriptParser::BANG - 82))
            | (1ULL << (JavaScriptParser::TILDE - 82))
            | (1ULL << (JavaScriptParser::INC - 82))
            | (1ULL << (JavaScriptParser::DEC - 82))
            | (1ULL << (JavaScriptParser::ADD - 82))
            | (1ULL << (JavaScriptParser::SUB - 82))
            | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
            | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
            setState(847);
            arguments();
          }
          setState(850);
          match(JavaScriptParser::RPAREN);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<CallExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCallExpression);
          setState(851);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(852);
          match(JavaScriptParser::LBRACKET);
          setState(853);
          expression();
          setState(854);
          match(JavaScriptParser::RBRACKET);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<CallExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCallExpression);
          setState(856);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(857);
          match(JavaScriptParser::DOT);
          setState(858);
          identifierName();
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<CallExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCallExpression);
          setState(859);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(860);
          templateLiteral();
          break;
        }

        default:
          break;
        } 
      }
      setState(865);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

JavaScriptParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ArgumentListContext* JavaScriptParser::ArgumentsContext::argumentList() {
  return getRuleContext<JavaScriptParser::ArgumentListContext>(0);
}


size_t JavaScriptParser::ArgumentsContext::getRuleIndex() const {
  return JavaScriptParser::RuleArguments;
}

void JavaScriptParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void JavaScriptParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}

JavaScriptParser::ArgumentsContext* JavaScriptParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 162, JavaScriptParser::RuleArguments);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(866);
    argumentList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

JavaScriptParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::AssignmentExpressionContext *> JavaScriptParser::ArgumentListContext::assignmentExpression() {
  return getRuleContexts<JavaScriptParser::AssignmentExpressionContext>();
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::ArgumentListContext::assignmentExpression(size_t i) {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ArgumentListContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ArgumentListContext::getRuleIndex() const {
  return JavaScriptParser::RuleArgumentList;
}

void JavaScriptParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void JavaScriptParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}

JavaScriptParser::ArgumentListContext* JavaScriptParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 164, JavaScriptParser::RuleArgumentList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(868);
    assignmentExpression();
    setState(873);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(869);
      match(JavaScriptParser::COMMA);
      setState(870);
      assignmentExpression();
      setState(875);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NewExpressionContext ------------------------------------------------------------------

JavaScriptParser::NewExpressionContext::NewExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::NewExpressionContext::NEW() {
  return getToken(JavaScriptParser::NEW, 0);
}

JavaScriptParser::NewExpressionContext* JavaScriptParser::NewExpressionContext::newExpression() {
  return getRuleContext<JavaScriptParser::NewExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::NewExpressionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::NewExpressionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::ArgumentsContext* JavaScriptParser::NewExpressionContext::arguments() {
  return getRuleContext<JavaScriptParser::ArgumentsContext>(0);
}

tree::TerminalNode* JavaScriptParser::NewExpressionContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::NewExpressionContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::NewExpressionContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::NewExpressionContext::DOT() {
  return getToken(JavaScriptParser::DOT, 0);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::NewExpressionContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

JavaScriptParser::TemplateLiteralContext* JavaScriptParser::NewExpressionContext::templateLiteral() {
  return getRuleContext<JavaScriptParser::TemplateLiteralContext>(0);
}

JavaScriptParser::SuperPropertyContext* JavaScriptParser::NewExpressionContext::superProperty() {
  return getRuleContext<JavaScriptParser::SuperPropertyContext>(0);
}

JavaScriptParser::FunctionExpressionContext* JavaScriptParser::NewExpressionContext::functionExpression() {
  return getRuleContext<JavaScriptParser::FunctionExpressionContext>(0);
}

JavaScriptParser::ClassExpressionContext* JavaScriptParser::NewExpressionContext::classExpression() {
  return getRuleContext<JavaScriptParser::ClassExpressionContext>(0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::NewExpressionContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::ThisExpressionContext* JavaScriptParser::NewExpressionContext::thisExpression() {
  return getRuleContext<JavaScriptParser::ThisExpressionContext>(0);
}

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::NewExpressionContext::arrayLiteral() {
  return getRuleContext<JavaScriptParser::ArrayLiteralContext>(0);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::NewExpressionContext::objectLiteral() {
  return getRuleContext<JavaScriptParser::ObjectLiteralContext>(0);
}

JavaScriptParser::ParenthesizedExpressionContext* JavaScriptParser::NewExpressionContext::parenthesizedExpression() {
  return getRuleContext<JavaScriptParser::ParenthesizedExpressionContext>(0);
}


size_t JavaScriptParser::NewExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleNewExpression;
}

void JavaScriptParser::NewExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNewExpression(this);
}

void JavaScriptParser::NewExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNewExpression(this);
}

JavaScriptParser::NewExpressionContext* JavaScriptParser::newExpression() {
  NewExpressionContext *_localctx = _tracker.createInstance<NewExpressionContext>(_ctx, getState());
  enterRule(_localctx, 166, JavaScriptParser::RuleNewExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(909);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(876);
      match(JavaScriptParser::NEW);
      setState(877);
      newExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(878);
      match(JavaScriptParser::NEW);
      setState(879);
      newExpression();
      setState(880);
      match(JavaScriptParser::LPAREN);
      setState(882);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
        | (1ULL << JavaScriptParser::NEW)
        | (1ULL << JavaScriptParser::VOID)
        | (1ULL << JavaScriptParser::FUNCTION)
        | (1ULL << JavaScriptParser::THIS)
        | (1ULL << JavaScriptParser::DELETE)
        | (1ULL << JavaScriptParser::CLASS)
        | (1ULL << JavaScriptParser::SUPER)
        | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
        | (1ULL << (JavaScriptParser::LPAREN - 82))
        | (1ULL << (JavaScriptParser::LBRACE - 82))
        | (1ULL << (JavaScriptParser::LBRACKET - 82))
        | (1ULL << (JavaScriptParser::ASSIGN - 82))
        | (1ULL << (JavaScriptParser::BANG - 82))
        | (1ULL << (JavaScriptParser::TILDE - 82))
        | (1ULL << (JavaScriptParser::INC - 82))
        | (1ULL << (JavaScriptParser::DEC - 82))
        | (1ULL << (JavaScriptParser::ADD - 82))
        | (1ULL << (JavaScriptParser::SUB - 82))
        | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
        | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
        setState(881);
        arguments();
      }
      setState(884);
      match(JavaScriptParser::RPAREN);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(886);
      match(JavaScriptParser::NEW);
      setState(887);
      newExpression();
      setState(888);
      match(JavaScriptParser::LBRACKET);
      setState(889);
      expression();
      setState(890);
      match(JavaScriptParser::RBRACKET);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(892);
      match(JavaScriptParser::NEW);
      setState(893);
      newExpression();
      setState(894);
      match(JavaScriptParser::DOT);
      setState(895);
      identifierName();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(897);
      match(JavaScriptParser::NEW);
      setState(898);
      newExpression();
      setState(899);
      templateLiteral();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(901);
      superProperty();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(902);
      functionExpression();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(903);
      classExpression();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(904);
      identifier();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(905);
      thisExpression();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(906);
      arrayLiteral();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(907);
      objectLiteral();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(908);
      parenthesizedExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SuperPropertyContext ------------------------------------------------------------------

JavaScriptParser::SuperPropertyContext::SuperPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::SuperPropertyContext::SUPER() {
  return getToken(JavaScriptParser::SUPER, 0);
}

tree::TerminalNode* JavaScriptParser::SuperPropertyContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::SuperPropertyContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::SuperPropertyContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::SuperPropertyContext::DOT() {
  return getToken(JavaScriptParser::DOT, 0);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::SuperPropertyContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}


size_t JavaScriptParser::SuperPropertyContext::getRuleIndex() const {
  return JavaScriptParser::RuleSuperProperty;
}

void JavaScriptParser::SuperPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSuperProperty(this);
}

void JavaScriptParser::SuperPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSuperProperty(this);
}

JavaScriptParser::SuperPropertyContext* JavaScriptParser::superProperty() {
  SuperPropertyContext *_localctx = _tracker.createInstance<SuperPropertyContext>(_ctx, getState());
  enterRule(_localctx, 168, JavaScriptParser::RuleSuperProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(919);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(911);
      match(JavaScriptParser::SUPER);
      setState(912);
      match(JavaScriptParser::LBRACKET);
      setState(913);
      expression();
      setState(914);
      match(JavaScriptParser::RBRACKET);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(916);
      match(JavaScriptParser::SUPER);
      setState(917);
      match(JavaScriptParser::DOT);
      setState(918);
      identifierName();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionExpressionContext ------------------------------------------------------------------

JavaScriptParser::FunctionExpressionContext::FunctionExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FunctionExpressionContext::FUNCTION() {
  return getToken(JavaScriptParser::FUNCTION, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionExpressionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionExpressionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionExpressionContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::FunctionExpressionContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::FunctionExpressionContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::FunctionExpressionContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::FunctionExpressionContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::FunctionExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleFunctionExpression;
}

void JavaScriptParser::FunctionExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionExpression(this);
}

void JavaScriptParser::FunctionExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionExpression(this);
}

JavaScriptParser::FunctionExpressionContext* JavaScriptParser::functionExpression() {
  FunctionExpressionContext *_localctx = _tracker.createInstance<FunctionExpressionContext>(_ctx, getState());
  enterRule(_localctx, 170, JavaScriptParser::RuleFunctionExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(921);
    match(JavaScriptParser::FUNCTION);
    setState(923);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::IDENTIFIER) {
      setState(922);
      identifier();
    }
    setState(925);
    match(JavaScriptParser::LPAREN);
    setState(927);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 82)))) != 0)) {
      setState(926);
      formalParameterList();
    }
    setState(929);
    match(JavaScriptParser::RPAREN);
    setState(930);
    match(JavaScriptParser::LBRACE);
    setState(931);
    functionBody();
    setState(932);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassExpressionContext ------------------------------------------------------------------

JavaScriptParser::ClassExpressionContext::ClassExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ClassExpressionContext::CLASS() {
  return getToken(JavaScriptParser::CLASS, 0);
}

tree::TerminalNode* JavaScriptParser::ClassExpressionContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::ClassExpressionContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::IdentifierContext *> JavaScriptParser::ClassExpressionContext::identifier() {
  return getRuleContexts<JavaScriptParser::IdentifierContext>();
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ClassExpressionContext::identifier(size_t i) {
  return getRuleContext<JavaScriptParser::IdentifierContext>(i);
}

tree::TerminalNode* JavaScriptParser::ClassExpressionContext::EXTENDS() {
  return getToken(JavaScriptParser::EXTENDS, 0);
}

JavaScriptParser::ClassBodyContext* JavaScriptParser::ClassExpressionContext::classBody() {
  return getRuleContext<JavaScriptParser::ClassBodyContext>(0);
}


size_t JavaScriptParser::ClassExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassExpression;
}

void JavaScriptParser::ClassExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassExpression(this);
}

void JavaScriptParser::ClassExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassExpression(this);
}

JavaScriptParser::ClassExpressionContext* JavaScriptParser::classExpression() {
  ClassExpressionContext *_localctx = _tracker.createInstance<ClassExpressionContext>(_ctx, getState());
  enterRule(_localctx, 172, JavaScriptParser::RuleClassExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(934);
    match(JavaScriptParser::CLASS);
    setState(936);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::IDENTIFIER) {
      setState(935);
      identifier();
    }
    setState(940);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::EXTENDS) {
      setState(938);
      match(JavaScriptParser::EXTENDS);
      setState(939);
      identifier();
    }
    setState(942);
    match(JavaScriptParser::LBRACE);
    setState(944);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::IMPLEMENTS)
      | (1ULL << JavaScriptParser::INTERFACE)
      | (1ULL << JavaScriptParser::PACKAGE)
      | (1ULL << JavaScriptParser::PRIVATE)
      | (1ULL << JavaScriptParser::PROTECTED)
      | (1ULL << JavaScriptParser::PUBLIC)
      | (1ULL << JavaScriptParser::ABSTRACT)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::BYTE)
      | (1ULL << JavaScriptParser::CHAR)
      | (1ULL << JavaScriptParser::DOUBLE)
      | (1ULL << JavaScriptParser::FINAL)
      | (1ULL << JavaScriptParser::FLOAT)
      | (1ULL << JavaScriptParser::GOTO)
      | (1ULL << JavaScriptParser::INT)
      | (1ULL << JavaScriptParser::LONG)
      | (1ULL << JavaScriptParser::NATIVE)
      | (1ULL << JavaScriptParser::SHORT)
      | (1ULL << JavaScriptParser::SYNCHRONIZED)
      | (1ULL << JavaScriptParser::THROWS)
      | (1ULL << JavaScriptParser::TRANSIENT)
      | (1ULL << JavaScriptParser::VOLATILE)
      | (1ULL << JavaScriptParser::NULL))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::TRUE - 64))
      | (1ULL << (JavaScriptParser::FALSE - 64))
      | (1ULL << (JavaScriptParser::GET - 64))
      | (1ULL << (JavaScriptParser::SET - 64))
      | (1ULL << (JavaScriptParser::STRING - 64))
      | (1ULL << (JavaScriptParser::NUMBER - 64))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 64)))) != 0)) {
      setState(943);
      classBody();
    }
    setState(946);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

JavaScriptParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IdentifierContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}


size_t JavaScriptParser::IdentifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleIdentifier;
}

void JavaScriptParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void JavaScriptParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 174, JavaScriptParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(948);
    match(JavaScriptParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThisExpressionContext ------------------------------------------------------------------

JavaScriptParser::ThisExpressionContext::ThisExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ThisExpressionContext::THIS() {
  return getToken(JavaScriptParser::THIS, 0);
}


size_t JavaScriptParser::ThisExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleThisExpression;
}

void JavaScriptParser::ThisExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThisExpression(this);
}

void JavaScriptParser::ThisExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThisExpression(this);
}

JavaScriptParser::ThisExpressionContext* JavaScriptParser::thisExpression() {
  ThisExpressionContext *_localctx = _tracker.createInstance<ThisExpressionContext>(_ctx, getState());
  enterRule(_localctx, 176, JavaScriptParser::RuleThisExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(950);
    match(JavaScriptParser::THIS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayLiteralContext ------------------------------------------------------------------

JavaScriptParser::ArrayLiteralContext::ArrayLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ArrayLiteralContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::ArrayLiteralContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}

JavaScriptParser::ElementListContext* JavaScriptParser::ArrayLiteralContext::elementList() {
  return getRuleContext<JavaScriptParser::ElementListContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrayLiteralContext::COMMA() {
  return getToken(JavaScriptParser::COMMA, 0);
}


size_t JavaScriptParser::ArrayLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrayLiteral;
}

void JavaScriptParser::ArrayLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayLiteral(this);
}

void JavaScriptParser::ArrayLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayLiteral(this);
}

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::arrayLiteral() {
  ArrayLiteralContext *_localctx = _tracker.createInstance<ArrayLiteralContext>(_ctx, getState());
  enterRule(_localctx, 178, JavaScriptParser::RuleArrayLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(952);
    match(JavaScriptParser::LBRACKET);
    setState(957);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 82)))) != 0)) {
      setState(953);
      elementList();
      setState(955);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::COMMA) {
        setState(954);
        match(JavaScriptParser::COMMA);
      }
    }
    setState(959);
    match(JavaScriptParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementListContext ------------------------------------------------------------------

JavaScriptParser::ElementListContext::ElementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::AssignmentExpressionContext *> JavaScriptParser::ElementListContext::assignmentExpression() {
  return getRuleContexts<JavaScriptParser::AssignmentExpressionContext>();
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::ElementListContext::assignmentExpression(size_t i) {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ElementListContext::ELLIPSIS() {
  return getTokens(JavaScriptParser::ELLIPSIS);
}

tree::TerminalNode* JavaScriptParser::ElementListContext::ELLIPSIS(size_t i) {
  return getToken(JavaScriptParser::ELLIPSIS, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ElementListContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ElementListContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ElementListContext::getRuleIndex() const {
  return JavaScriptParser::RuleElementList;
}

void JavaScriptParser::ElementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementList(this);
}

void JavaScriptParser::ElementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementList(this);
}

JavaScriptParser::ElementListContext* JavaScriptParser::elementList() {
  ElementListContext *_localctx = _tracker.createInstance<ElementListContext>(_ctx, getState());
  enterRule(_localctx, 180, JavaScriptParser::RuleElementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(962);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::ELLIPSIS) {
      setState(961);
      match(JavaScriptParser::ELLIPSIS);
    }
    setState(964);
    assignmentExpression();
    setState(972);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(965);
        match(JavaScriptParser::COMMA);
        setState(967);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == JavaScriptParser::ELLIPSIS) {
          setState(966);
          match(JavaScriptParser::ELLIPSIS);
        }
        setState(969);
        assignmentExpression(); 
      }
      setState(974);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectLiteralContext ------------------------------------------------------------------

JavaScriptParser::ObjectLiteralContext::ObjectLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::PropertyDefinitionContext *> JavaScriptParser::ObjectLiteralContext::propertyDefinition() {
  return getRuleContexts<JavaScriptParser::PropertyDefinitionContext>();
}

JavaScriptParser::PropertyDefinitionContext* JavaScriptParser::ObjectLiteralContext::propertyDefinition(size_t i) {
  return getRuleContext<JavaScriptParser::PropertyDefinitionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ObjectLiteralContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ObjectLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleObjectLiteral;
}

void JavaScriptParser::ObjectLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectLiteral(this);
}

void JavaScriptParser::ObjectLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectLiteral(this);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::objectLiteral() {
  ObjectLiteralContext *_localctx = _tracker.createInstance<ObjectLiteralContext>(_ctx, getState());
  enterRule(_localctx, 182, JavaScriptParser::RuleObjectLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(975);
    match(JavaScriptParser::LBRACE);
    setState(984);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::IMPLEMENTS)
      | (1ULL << JavaScriptParser::INTERFACE)
      | (1ULL << JavaScriptParser::PACKAGE)
      | (1ULL << JavaScriptParser::PRIVATE)
      | (1ULL << JavaScriptParser::PROTECTED)
      | (1ULL << JavaScriptParser::PUBLIC)
      | (1ULL << JavaScriptParser::ABSTRACT)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::BYTE)
      | (1ULL << JavaScriptParser::CHAR)
      | (1ULL << JavaScriptParser::DOUBLE)
      | (1ULL << JavaScriptParser::FINAL)
      | (1ULL << JavaScriptParser::FLOAT)
      | (1ULL << JavaScriptParser::GOTO)
      | (1ULL << JavaScriptParser::INT)
      | (1ULL << JavaScriptParser::LONG)
      | (1ULL << JavaScriptParser::NATIVE)
      | (1ULL << JavaScriptParser::SHORT)
      | (1ULL << JavaScriptParser::SYNCHRONIZED)
      | (1ULL << JavaScriptParser::THROWS)
      | (1ULL << JavaScriptParser::TRANSIENT)
      | (1ULL << JavaScriptParser::VOLATILE)
      | (1ULL << JavaScriptParser::NULL))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::TRUE - 64))
      | (1ULL << (JavaScriptParser::FALSE - 64))
      | (1ULL << (JavaScriptParser::GET - 64))
      | (1ULL << (JavaScriptParser::SET - 64))
      | (1ULL << (JavaScriptParser::STRING - 64))
      | (1ULL << (JavaScriptParser::NUMBER - 64))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 64))
      | (1ULL << (JavaScriptParser::LPAREN - 64))
      | (1ULL << (JavaScriptParser::LBRACE - 64))
      | (1ULL << (JavaScriptParser::LBRACKET - 64))
      | (1ULL << (JavaScriptParser::ASSIGN - 64))
      | (1ULL << (JavaScriptParser::BANG - 64))
      | (1ULL << (JavaScriptParser::TILDE - 64))
      | (1ULL << (JavaScriptParser::INC - 64))
      | (1ULL << (JavaScriptParser::DEC - 64))
      | (1ULL << (JavaScriptParser::ADD - 64))
      | (1ULL << (JavaScriptParser::SUB - 64))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 64))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 64)))) != 0)) {
      setState(976);
      propertyDefinition();
      setState(981);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaScriptParser::COMMA) {
        setState(977);
        match(JavaScriptParser::COMMA);
        setState(978);
        propertyDefinition();
        setState(983);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(986);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyDefinitionContext ------------------------------------------------------------------

JavaScriptParser::PropertyDefinitionContext::PropertyDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::PropertyDefinitionContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyDefinitionContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::PropertyDefinitionContext::assignmentExpression() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::PropertyDefinitionContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyDefinitionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyDefinitionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyDefinitionContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::PropertyDefinitionContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyDefinitionContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::PropertyDefinitionContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyDefinitionContext::GET() {
  return getToken(JavaScriptParser::GET, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyDefinitionContext::SET() {
  return getToken(JavaScriptParser::SET, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyDefinitionContext::ELLIPSIS() {
  return getToken(JavaScriptParser::ELLIPSIS, 0);
}


size_t JavaScriptParser::PropertyDefinitionContext::getRuleIndex() const {
  return JavaScriptParser::RulePropertyDefinition;
}

void JavaScriptParser::PropertyDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyDefinition(this);
}

void JavaScriptParser::PropertyDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyDefinition(this);
}

JavaScriptParser::PropertyDefinitionContext* JavaScriptParser::propertyDefinition() {
  PropertyDefinitionContext *_localctx = _tracker.createInstance<PropertyDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 184, JavaScriptParser::RulePropertyDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1009);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(988);
      identifierName();
      setState(989);
      match(JavaScriptParser::COLON);
      setState(990);
      assignmentExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(993);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::GET

      || _la == JavaScriptParser::SET) {
        setState(992);
        _la = _input->LA(1);
        if (!(_la == JavaScriptParser::GET

        || _la == JavaScriptParser::SET)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(995);
      propertyName();
      setState(996);
      match(JavaScriptParser::LPAREN);
      setState(998);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 82) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
        | (1ULL << (JavaScriptParser::LBRACE - 82))
        | (1ULL << (JavaScriptParser::LBRACKET - 82))
        | (1ULL << (JavaScriptParser::ELLIPSIS - 82)))) != 0)) {
        setState(997);
        formalParameterList();
      }
      setState(1000);
      match(JavaScriptParser::RPAREN);
      setState(1001);
      match(JavaScriptParser::LBRACE);
      setState(1002);
      functionBody();
      setState(1003);
      match(JavaScriptParser::RBRACE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1006);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::ELLIPSIS) {
        setState(1005);
        match(JavaScriptParser::ELLIPSIS);
      }
      setState(1008);
      assignmentExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParenthesizedExpressionContext ------------------------------------------------------------------

JavaScriptParser::ParenthesizedExpressionContext::ParenthesizedExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ParenthesizedExpressionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::ParenthesizedExpressionContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ParenthesizedExpressionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}


size_t JavaScriptParser::ParenthesizedExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleParenthesizedExpression;
}

void JavaScriptParser::ParenthesizedExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenthesizedExpression(this);
}

void JavaScriptParser::ParenthesizedExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenthesizedExpression(this);
}

JavaScriptParser::ParenthesizedExpressionContext* JavaScriptParser::parenthesizedExpression() {
  ParenthesizedExpressionContext *_localctx = _tracker.createInstance<ParenthesizedExpressionContext>(_ctx, getState());
  enterRule(_localctx, 186, JavaScriptParser::RuleParenthesizedExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1011);
    match(JavaScriptParser::LPAREN);
    setState(1012);
    expression();
    setState(1013);
    match(JavaScriptParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateLiteralContext ------------------------------------------------------------------

JavaScriptParser::TemplateLiteralContext::TemplateLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaScriptParser::TemplateLiteralContext::BACKTICK() {
  return getTokens(JavaScriptParser::BACKTICK);
}

tree::TerminalNode* JavaScriptParser::TemplateLiteralContext::BACKTICK(size_t i) {
  return getToken(JavaScriptParser::BACKTICK, i);
}

std::vector<JavaScriptParser::TemplateElementContext *> JavaScriptParser::TemplateLiteralContext::templateElement() {
  return getRuleContexts<JavaScriptParser::TemplateElementContext>();
}

JavaScriptParser::TemplateElementContext* JavaScriptParser::TemplateLiteralContext::templateElement(size_t i) {
  return getRuleContext<JavaScriptParser::TemplateElementContext>(i);
}


size_t JavaScriptParser::TemplateLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleTemplateLiteral;
}

void JavaScriptParser::TemplateLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateLiteral(this);
}

void JavaScriptParser::TemplateLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateLiteral(this);
}

JavaScriptParser::TemplateLiteralContext* JavaScriptParser::templateLiteral() {
  TemplateLiteralContext *_localctx = _tracker.createInstance<TemplateLiteralContext>(_ctx, getState());
  enterRule(_localctx, 188, JavaScriptParser::RuleTemplateLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1015);
    match(JavaScriptParser::BACKTICK);
    setState(1017); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(1016);
      templateElement();
      setState(1019); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == JavaScriptParser::T__0 || _la == JavaScriptParser::TEMPLATE_CHAR);
    setState(1021);
    match(JavaScriptParser::BACKTICK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateElementContext ------------------------------------------------------------------

JavaScriptParser::TemplateElementContext::TemplateElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::TemplateCharactersContext* JavaScriptParser::TemplateElementContext::templateCharacters() {
  return getRuleContext<JavaScriptParser::TemplateCharactersContext>(0);
}

JavaScriptParser::TemplateSubstitutionContext* JavaScriptParser::TemplateElementContext::templateSubstitution() {
  return getRuleContext<JavaScriptParser::TemplateSubstitutionContext>(0);
}


size_t JavaScriptParser::TemplateElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleTemplateElement;
}

void JavaScriptParser::TemplateElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateElement(this);
}

void JavaScriptParser::TemplateElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateElement(this);
}

JavaScriptParser::TemplateElementContext* JavaScriptParser::templateElement() {
  TemplateElementContext *_localctx = _tracker.createInstance<TemplateElementContext>(_ctx, getState());
  enterRule(_localctx, 190, JavaScriptParser::RuleTemplateElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1025);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::TEMPLATE_CHAR: {
        enterOuterAlt(_localctx, 1);
        setState(1023);
        templateCharacters();
        break;
      }

      case JavaScriptParser::T__0: {
        enterOuterAlt(_localctx, 2);
        setState(1024);
        templateSubstitution();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateCharactersContext ------------------------------------------------------------------

JavaScriptParser::TemplateCharactersContext::TemplateCharactersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaScriptParser::TemplateCharactersContext::TEMPLATE_CHAR() {
  return getTokens(JavaScriptParser::TEMPLATE_CHAR);
}

tree::TerminalNode* JavaScriptParser::TemplateCharactersContext::TEMPLATE_CHAR(size_t i) {
  return getToken(JavaScriptParser::TEMPLATE_CHAR, i);
}


size_t JavaScriptParser::TemplateCharactersContext::getRuleIndex() const {
  return JavaScriptParser::RuleTemplateCharacters;
}

void JavaScriptParser::TemplateCharactersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateCharacters(this);
}

void JavaScriptParser::TemplateCharactersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateCharacters(this);
}

JavaScriptParser::TemplateCharactersContext* JavaScriptParser::templateCharacters() {
  TemplateCharactersContext *_localctx = _tracker.createInstance<TemplateCharactersContext>(_ctx, getState());
  enterRule(_localctx, 192, JavaScriptParser::RuleTemplateCharacters);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1028); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(1027);
              match(JavaScriptParser::TEMPLATE_CHAR);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(1030); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateSubstitutionContext ------------------------------------------------------------------

JavaScriptParser::TemplateSubstitutionContext::TemplateSubstitutionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::TemplateSubstitutionContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

JavaScriptParser::ExpressionContext* JavaScriptParser::TemplateSubstitutionContext::expression() {
  return getRuleContext<JavaScriptParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::TemplateSubstitutionContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}


size_t JavaScriptParser::TemplateSubstitutionContext::getRuleIndex() const {
  return JavaScriptParser::RuleTemplateSubstitution;
}

void JavaScriptParser::TemplateSubstitutionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateSubstitution(this);
}

void JavaScriptParser::TemplateSubstitutionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateSubstitution(this);
}

JavaScriptParser::TemplateSubstitutionContext* JavaScriptParser::templateSubstitution() {
  TemplateSubstitutionContext *_localctx = _tracker.createInstance<TemplateSubstitutionContext>(_ctx, getState());
  enterRule(_localctx, 194, JavaScriptParser::RuleTemplateSubstitution);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1032);
    match(JavaScriptParser::T__0);
    setState(1033);
    match(JavaScriptParser::LBRACE);
    setState(1034);
    expression();
    setState(1035);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- YieldExpressionContext ------------------------------------------------------------------

JavaScriptParser::YieldExpressionContext::YieldExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::YieldExpressionContext::YIELD() {
  return getToken(JavaScriptParser::YIELD, 0);
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::YieldExpressionContext::assignmentExpression() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(0);
}


size_t JavaScriptParser::YieldExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleYieldExpression;
}

void JavaScriptParser::YieldExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterYieldExpression(this);
}

void JavaScriptParser::YieldExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitYieldExpression(this);
}

JavaScriptParser::YieldExpressionContext* JavaScriptParser::yieldExpression() {
  YieldExpressionContext *_localctx = _tracker.createInstance<YieldExpressionContext>(_ctx, getState());
  enterRule(_localctx, 196, JavaScriptParser::RuleYieldExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1037);
    match(JavaScriptParser::YIELD);
    setState(1039);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0)) {
      setState(1038);
      assignmentExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionContext ------------------------------------------------------------------

JavaScriptParser::ArrowFunctionContext::ArrowFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ArrowParametersContext* JavaScriptParser::ArrowFunctionContext::arrowParameters() {
  return getRuleContext<JavaScriptParser::ArrowParametersContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionContext::ARROW() {
  return getToken(JavaScriptParser::ARROW, 0);
}

JavaScriptParser::ArrowFunctionBodyContext* JavaScriptParser::ArrowFunctionContext::arrowFunctionBody() {
  return getRuleContext<JavaScriptParser::ArrowFunctionBodyContext>(0);
}


size_t JavaScriptParser::ArrowFunctionContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrowFunction;
}

void JavaScriptParser::ArrowFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunction(this);
}

void JavaScriptParser::ArrowFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunction(this);
}

JavaScriptParser::ArrowFunctionContext* JavaScriptParser::arrowFunction() {
  ArrowFunctionContext *_localctx = _tracker.createInstance<ArrowFunctionContext>(_ctx, getState());
  enterRule(_localctx, 198, JavaScriptParser::RuleArrowFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1041);
    arrowParameters();
    setState(1042);
    match(JavaScriptParser::ARROW);
    setState(1043);
    arrowFunctionBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowParametersContext ------------------------------------------------------------------

JavaScriptParser::ArrowParametersContext::ArrowParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ArrowParametersContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowParametersContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::ArrowParametersContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::ArrowParametersContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}

JavaScriptParser::BindingPatternContext* JavaScriptParser::ArrowParametersContext::bindingPattern() {
  return getRuleContext<JavaScriptParser::BindingPatternContext>(0);
}


size_t JavaScriptParser::ArrowParametersContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrowParameters;
}

void JavaScriptParser::ArrowParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowParameters(this);
}

void JavaScriptParser::ArrowParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowParameters(this);
}

JavaScriptParser::ArrowParametersContext* JavaScriptParser::arrowParameters() {
  ArrowParametersContext *_localctx = _tracker.createInstance<ArrowParametersContext>(_ctx, getState());
  enterRule(_localctx, 200, JavaScriptParser::RuleArrowParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1052);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(1045);
        identifier();
        break;
      }

      case JavaScriptParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(1046);
        match(JavaScriptParser::LPAREN);
        setState(1048);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 82) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
          | (1ULL << (JavaScriptParser::LBRACE - 82))
          | (1ULL << (JavaScriptParser::LBRACKET - 82))
          | (1ULL << (JavaScriptParser::ELLIPSIS - 82)))) != 0)) {
          setState(1047);
          formalParameterList();
        }
        setState(1050);
        match(JavaScriptParser::RPAREN);
        break;
      }

      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET: {
        enterOuterAlt(_localctx, 3);
        setState(1051);
        bindingPattern();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionBodyContext ------------------------------------------------------------------

JavaScriptParser::ArrowFunctionBodyContext::ArrowFunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::ArrowFunctionBodyContext::assignmentExpression() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionBodyContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::ArrowFunctionBodyContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionBodyContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}


size_t JavaScriptParser::ArrowFunctionBodyContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrowFunctionBody;
}

void JavaScriptParser::ArrowFunctionBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunctionBody(this);
}

void JavaScriptParser::ArrowFunctionBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunctionBody(this);
}

JavaScriptParser::ArrowFunctionBodyContext* JavaScriptParser::arrowFunctionBody() {
  ArrowFunctionBodyContext *_localctx = _tracker.createInstance<ArrowFunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 202, JavaScriptParser::RuleArrowFunctionBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1059);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 109, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1054);
      assignmentExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1055);
      match(JavaScriptParser::LBRACE);
      setState(1056);
      functionBody();
      setState(1057);
      match(JavaScriptParser::RBRACE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::ExpressionNoInContext::ExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::AssignmentExpressionNoInContext *> JavaScriptParser::ExpressionNoInContext::assignmentExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::AssignmentExpressionNoInContext>();
}

JavaScriptParser::AssignmentExpressionNoInContext* JavaScriptParser::ExpressionNoInContext::assignmentExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::AssignmentExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ExpressionNoInContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ExpressionNoInContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleExpressionNoIn;
}

void JavaScriptParser::ExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionNoIn(this);
}

void JavaScriptParser::ExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionNoIn(this);
}

JavaScriptParser::ExpressionNoInContext* JavaScriptParser::expressionNoIn() {
  ExpressionNoInContext *_localctx = _tracker.createInstance<ExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 204, JavaScriptParser::RuleExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1061);
    assignmentExpressionNoIn();
    setState(1066);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(1062);
      match(JavaScriptParser::COMMA);
      setState(1063);
      assignmentExpressionNoIn();
      setState(1068);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::AssignmentExpressionNoInContext::AssignmentExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ConditionalExpressionNoInContext* JavaScriptParser::AssignmentExpressionNoInContext::conditionalExpressionNoIn() {
  return getRuleContext<JavaScriptParser::ConditionalExpressionNoInContext>(0);
}

JavaScriptParser::YieldExpressionContext* JavaScriptParser::AssignmentExpressionNoInContext::yieldExpression() {
  return getRuleContext<JavaScriptParser::YieldExpressionContext>(0);
}

JavaScriptParser::ArrowFunctionContext* JavaScriptParser::AssignmentExpressionNoInContext::arrowFunction() {
  return getRuleContext<JavaScriptParser::ArrowFunctionContext>(0);
}

JavaScriptParser::AssignmentOperatorContext* JavaScriptParser::AssignmentExpressionNoInContext::assignmentOperator() {
  return getRuleContext<JavaScriptParser::AssignmentOperatorContext>(0);
}

JavaScriptParser::AssignmentExpressionNoInContext* JavaScriptParser::AssignmentExpressionNoInContext::assignmentExpressionNoIn() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionNoInContext>(0);
}


size_t JavaScriptParser::AssignmentExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleAssignmentExpressionNoIn;
}

void JavaScriptParser::AssignmentExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpressionNoIn(this);
}

void JavaScriptParser::AssignmentExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpressionNoIn(this);
}

JavaScriptParser::AssignmentExpressionNoInContext* JavaScriptParser::assignmentExpressionNoIn() {
  AssignmentExpressionNoInContext *_localctx = _tracker.createInstance<AssignmentExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 206, JavaScriptParser::RuleAssignmentExpressionNoIn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1075);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 111, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1069);
      conditionalExpressionNoIn();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1070);
      yieldExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1071);
      arrowFunction();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1072);
      assignmentOperator();
      setState(1073);
      assignmentExpressionNoIn();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::ConditionalExpressionNoInContext::ConditionalExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::LogicalORExpressionNoInContext* JavaScriptParser::ConditionalExpressionNoInContext::logicalORExpressionNoIn() {
  return getRuleContext<JavaScriptParser::LogicalORExpressionNoInContext>(0);
}

tree::TerminalNode* JavaScriptParser::ConditionalExpressionNoInContext::QUESTION() {
  return getToken(JavaScriptParser::QUESTION, 0);
}

JavaScriptParser::AssignmentExpressionContext* JavaScriptParser::ConditionalExpressionNoInContext::assignmentExpression() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ConditionalExpressionNoInContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

JavaScriptParser::AssignmentExpressionNoInContext* JavaScriptParser::ConditionalExpressionNoInContext::assignmentExpressionNoIn() {
  return getRuleContext<JavaScriptParser::AssignmentExpressionNoInContext>(0);
}


size_t JavaScriptParser::ConditionalExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleConditionalExpressionNoIn;
}

void JavaScriptParser::ConditionalExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalExpressionNoIn(this);
}

void JavaScriptParser::ConditionalExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalExpressionNoIn(this);
}

JavaScriptParser::ConditionalExpressionNoInContext* JavaScriptParser::conditionalExpressionNoIn() {
  ConditionalExpressionNoInContext *_localctx = _tracker.createInstance<ConditionalExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 208, JavaScriptParser::RuleConditionalExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1077);
    logicalORExpressionNoIn();
    setState(1083);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::QUESTION) {
      setState(1078);
      match(JavaScriptParser::QUESTION);
      setState(1079);
      assignmentExpression();
      setState(1080);
      match(JavaScriptParser::COLON);
      setState(1081);
      assignmentExpressionNoIn();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalORExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::LogicalORExpressionNoInContext::LogicalORExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::LogicalANDExpressionNoInContext *> JavaScriptParser::LogicalORExpressionNoInContext::logicalANDExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::LogicalANDExpressionNoInContext>();
}

JavaScriptParser::LogicalANDExpressionNoInContext* JavaScriptParser::LogicalORExpressionNoInContext::logicalANDExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::LogicalANDExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::LogicalORExpressionNoInContext::OR() {
  return getTokens(JavaScriptParser::OR);
}

tree::TerminalNode* JavaScriptParser::LogicalORExpressionNoInContext::OR(size_t i) {
  return getToken(JavaScriptParser::OR, i);
}


size_t JavaScriptParser::LogicalORExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleLogicalORExpressionNoIn;
}

void JavaScriptParser::LogicalORExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalORExpressionNoIn(this);
}

void JavaScriptParser::LogicalORExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalORExpressionNoIn(this);
}

JavaScriptParser::LogicalORExpressionNoInContext* JavaScriptParser::logicalORExpressionNoIn() {
  LogicalORExpressionNoInContext *_localctx = _tracker.createInstance<LogicalORExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 210, JavaScriptParser::RuleLogicalORExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1085);
    logicalANDExpressionNoIn();
    setState(1090);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::OR) {
      setState(1086);
      match(JavaScriptParser::OR);
      setState(1087);
      logicalANDExpressionNoIn();
      setState(1092);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalANDExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::LogicalANDExpressionNoInContext::LogicalANDExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::BitwiseORExpressionNoInContext *> JavaScriptParser::LogicalANDExpressionNoInContext::bitwiseORExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::BitwiseORExpressionNoInContext>();
}

JavaScriptParser::BitwiseORExpressionNoInContext* JavaScriptParser::LogicalANDExpressionNoInContext::bitwiseORExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::BitwiseORExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::LogicalANDExpressionNoInContext::AND() {
  return getTokens(JavaScriptParser::AND);
}

tree::TerminalNode* JavaScriptParser::LogicalANDExpressionNoInContext::AND(size_t i) {
  return getToken(JavaScriptParser::AND, i);
}


size_t JavaScriptParser::LogicalANDExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleLogicalANDExpressionNoIn;
}

void JavaScriptParser::LogicalANDExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalANDExpressionNoIn(this);
}

void JavaScriptParser::LogicalANDExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalANDExpressionNoIn(this);
}

JavaScriptParser::LogicalANDExpressionNoInContext* JavaScriptParser::logicalANDExpressionNoIn() {
  LogicalANDExpressionNoInContext *_localctx = _tracker.createInstance<LogicalANDExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 212, JavaScriptParser::RuleLogicalANDExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1093);
    bitwiseORExpressionNoIn();
    setState(1098);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::AND) {
      setState(1094);
      match(JavaScriptParser::AND);
      setState(1095);
      bitwiseORExpressionNoIn();
      setState(1100);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseORExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::BitwiseORExpressionNoInContext::BitwiseORExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::BitwiseXORExpressionNoInContext *> JavaScriptParser::BitwiseORExpressionNoInContext::bitwiseXORExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::BitwiseXORExpressionNoInContext>();
}

JavaScriptParser::BitwiseXORExpressionNoInContext* JavaScriptParser::BitwiseORExpressionNoInContext::bitwiseXORExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::BitwiseXORExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::BitwiseORExpressionNoInContext::BITOR() {
  return getTokens(JavaScriptParser::BITOR);
}

tree::TerminalNode* JavaScriptParser::BitwiseORExpressionNoInContext::BITOR(size_t i) {
  return getToken(JavaScriptParser::BITOR, i);
}


size_t JavaScriptParser::BitwiseORExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleBitwiseORExpressionNoIn;
}

void JavaScriptParser::BitwiseORExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseORExpressionNoIn(this);
}

void JavaScriptParser::BitwiseORExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseORExpressionNoIn(this);
}

JavaScriptParser::BitwiseORExpressionNoInContext* JavaScriptParser::bitwiseORExpressionNoIn() {
  BitwiseORExpressionNoInContext *_localctx = _tracker.createInstance<BitwiseORExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 214, JavaScriptParser::RuleBitwiseORExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1101);
    bitwiseXORExpressionNoIn();
    setState(1106);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::BITOR) {
      setState(1102);
      match(JavaScriptParser::BITOR);
      setState(1103);
      bitwiseXORExpressionNoIn();
      setState(1108);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseXORExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::BitwiseXORExpressionNoInContext::BitwiseXORExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::BitwiseANDExpressionNoInContext *> JavaScriptParser::BitwiseXORExpressionNoInContext::bitwiseANDExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::BitwiseANDExpressionNoInContext>();
}

JavaScriptParser::BitwiseANDExpressionNoInContext* JavaScriptParser::BitwiseXORExpressionNoInContext::bitwiseANDExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::BitwiseANDExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::BitwiseXORExpressionNoInContext::CARET() {
  return getTokens(JavaScriptParser::CARET);
}

tree::TerminalNode* JavaScriptParser::BitwiseXORExpressionNoInContext::CARET(size_t i) {
  return getToken(JavaScriptParser::CARET, i);
}


size_t JavaScriptParser::BitwiseXORExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleBitwiseXORExpressionNoIn;
}

void JavaScriptParser::BitwiseXORExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseXORExpressionNoIn(this);
}

void JavaScriptParser::BitwiseXORExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseXORExpressionNoIn(this);
}

JavaScriptParser::BitwiseXORExpressionNoInContext* JavaScriptParser::bitwiseXORExpressionNoIn() {
  BitwiseXORExpressionNoInContext *_localctx = _tracker.createInstance<BitwiseXORExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 216, JavaScriptParser::RuleBitwiseXORExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1109);
    bitwiseANDExpressionNoIn();
    setState(1114);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::CARET) {
      setState(1110);
      match(JavaScriptParser::CARET);
      setState(1111);
      bitwiseANDExpressionNoIn();
      setState(1116);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseANDExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::BitwiseANDExpressionNoInContext::BitwiseANDExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::EqualityExpressionNoInContext *> JavaScriptParser::BitwiseANDExpressionNoInContext::equalityExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::EqualityExpressionNoInContext>();
}

JavaScriptParser::EqualityExpressionNoInContext* JavaScriptParser::BitwiseANDExpressionNoInContext::equalityExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::EqualityExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::BitwiseANDExpressionNoInContext::BITAND() {
  return getTokens(JavaScriptParser::BITAND);
}

tree::TerminalNode* JavaScriptParser::BitwiseANDExpressionNoInContext::BITAND(size_t i) {
  return getToken(JavaScriptParser::BITAND, i);
}


size_t JavaScriptParser::BitwiseANDExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleBitwiseANDExpressionNoIn;
}

void JavaScriptParser::BitwiseANDExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseANDExpressionNoIn(this);
}

void JavaScriptParser::BitwiseANDExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseANDExpressionNoIn(this);
}

JavaScriptParser::BitwiseANDExpressionNoInContext* JavaScriptParser::bitwiseANDExpressionNoIn() {
  BitwiseANDExpressionNoInContext *_localctx = _tracker.createInstance<BitwiseANDExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 218, JavaScriptParser::RuleBitwiseANDExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1117);
    equalityExpressionNoIn();
    setState(1122);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::BITAND) {
      setState(1118);
      match(JavaScriptParser::BITAND);
      setState(1119);
      equalityExpressionNoIn();
      setState(1124);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::EqualityExpressionNoInContext::EqualityExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::RelationalExpressionNoInContext *> JavaScriptParser::EqualityExpressionNoInContext::relationalExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::RelationalExpressionNoInContext>();
}

JavaScriptParser::RelationalExpressionNoInContext* JavaScriptParser::EqualityExpressionNoInContext::relationalExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::RelationalExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::EqualityExpressionNoInContext::EQUAL() {
  return getTokens(JavaScriptParser::EQUAL);
}

tree::TerminalNode* JavaScriptParser::EqualityExpressionNoInContext::EQUAL(size_t i) {
  return getToken(JavaScriptParser::EQUAL, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::EqualityExpressionNoInContext::NOTEQUAL() {
  return getTokens(JavaScriptParser::NOTEQUAL);
}

tree::TerminalNode* JavaScriptParser::EqualityExpressionNoInContext::NOTEQUAL(size_t i) {
  return getToken(JavaScriptParser::NOTEQUAL, i);
}


size_t JavaScriptParser::EqualityExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleEqualityExpressionNoIn;
}

void JavaScriptParser::EqualityExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpressionNoIn(this);
}

void JavaScriptParser::EqualityExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpressionNoIn(this);
}

JavaScriptParser::EqualityExpressionNoInContext* JavaScriptParser::equalityExpressionNoIn() {
  EqualityExpressionNoInContext *_localctx = _tracker.createInstance<EqualityExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 220, JavaScriptParser::RuleEqualityExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1125);
    relationalExpressionNoIn();
    setState(1130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::EQUAL

    || _la == JavaScriptParser::NOTEQUAL) {
      setState(1126);
      _la = _input->LA(1);
      if (!(_la == JavaScriptParser::EQUAL

      || _la == JavaScriptParser::NOTEQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1127);
      relationalExpressionNoIn();
      setState(1132);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::RelationalExpressionNoInContext::RelationalExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::ShiftExpressionNoInContext *> JavaScriptParser::RelationalExpressionNoInContext::shiftExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::ShiftExpressionNoInContext>();
}

JavaScriptParser::ShiftExpressionNoInContext* JavaScriptParser::RelationalExpressionNoInContext::shiftExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::ShiftExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionNoInContext::LT() {
  return getTokens(JavaScriptParser::LT);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionNoInContext::LT(size_t i) {
  return getToken(JavaScriptParser::LT, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionNoInContext::GT() {
  return getTokens(JavaScriptParser::GT);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionNoInContext::GT(size_t i) {
  return getToken(JavaScriptParser::GT, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionNoInContext::LE() {
  return getTokens(JavaScriptParser::LE);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionNoInContext::LE(size_t i) {
  return getToken(JavaScriptParser::LE, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionNoInContext::GE() {
  return getTokens(JavaScriptParser::GE);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionNoInContext::GE(size_t i) {
  return getToken(JavaScriptParser::GE, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::RelationalExpressionNoInContext::INSTANCEOF() {
  return getTokens(JavaScriptParser::INSTANCEOF);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionNoInContext::INSTANCEOF(size_t i) {
  return getToken(JavaScriptParser::INSTANCEOF, i);
}


size_t JavaScriptParser::RelationalExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleRelationalExpressionNoIn;
}

void JavaScriptParser::RelationalExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpressionNoIn(this);
}

void JavaScriptParser::RelationalExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpressionNoIn(this);
}

JavaScriptParser::RelationalExpressionNoInContext* JavaScriptParser::relationalExpressionNoIn() {
  RelationalExpressionNoInContext *_localctx = _tracker.createInstance<RelationalExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 222, JavaScriptParser::RuleRelationalExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1133);
    shiftExpressionNoIn();
    setState(1138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::INSTANCEOF || ((((_la - 94) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 94)) & ((1ULL << (JavaScriptParser::GT - 94))
      | (1ULL << (JavaScriptParser::LT - 94))
      | (1ULL << (JavaScriptParser::LE - 94))
      | (1ULL << (JavaScriptParser::GE - 94)))) != 0)) {
      setState(1134);
      _la = _input->LA(1);
      if (!(_la == JavaScriptParser::INSTANCEOF || ((((_la - 94) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 94)) & ((1ULL << (JavaScriptParser::GT - 94))
        | (1ULL << (JavaScriptParser::LT - 94))
        | (1ULL << (JavaScriptParser::LE - 94))
        | (1ULL << (JavaScriptParser::GE - 94)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1135);
      shiftExpressionNoIn();
      setState(1140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::ShiftExpressionNoInContext::ShiftExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::AdditiveExpressionNoInContext *> JavaScriptParser::ShiftExpressionNoInContext::additiveExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::AdditiveExpressionNoInContext>();
}

JavaScriptParser::AdditiveExpressionNoInContext* JavaScriptParser::ShiftExpressionNoInContext::additiveExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::AdditiveExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ShiftExpressionNoInContext::LSHIFT() {
  return getTokens(JavaScriptParser::LSHIFT);
}

tree::TerminalNode* JavaScriptParser::ShiftExpressionNoInContext::LSHIFT(size_t i) {
  return getToken(JavaScriptParser::LSHIFT, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ShiftExpressionNoInContext::RSHIFT() {
  return getTokens(JavaScriptParser::RSHIFT);
}

tree::TerminalNode* JavaScriptParser::ShiftExpressionNoInContext::RSHIFT(size_t i) {
  return getToken(JavaScriptParser::RSHIFT, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ShiftExpressionNoInContext::URSHIFT() {
  return getTokens(JavaScriptParser::URSHIFT);
}

tree::TerminalNode* JavaScriptParser::ShiftExpressionNoInContext::URSHIFT(size_t i) {
  return getToken(JavaScriptParser::URSHIFT, i);
}


size_t JavaScriptParser::ShiftExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleShiftExpressionNoIn;
}

void JavaScriptParser::ShiftExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpressionNoIn(this);
}

void JavaScriptParser::ShiftExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpressionNoIn(this);
}

JavaScriptParser::ShiftExpressionNoInContext* JavaScriptParser::shiftExpressionNoIn() {
  ShiftExpressionNoInContext *_localctx = _tracker.createInstance<ShiftExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 224, JavaScriptParser::RuleShiftExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1141);
    additiveExpressionNoIn();
    setState(1146);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 113) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 113)) & ((1ULL << (JavaScriptParser::LSHIFT - 113))
      | (1ULL << (JavaScriptParser::RSHIFT - 113))
      | (1ULL << (JavaScriptParser::URSHIFT - 113)))) != 0)) {
      setState(1142);
      _la = _input->LA(1);
      if (!(((((_la - 113) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 113)) & ((1ULL << (JavaScriptParser::LSHIFT - 113))
        | (1ULL << (JavaScriptParser::RSHIFT - 113))
        | (1ULL << (JavaScriptParser::URSHIFT - 113)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1143);
      additiveExpressionNoIn();
      setState(1148);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::AdditiveExpressionNoInContext::AdditiveExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::MultiplicativeExpressionNoInContext *> JavaScriptParser::AdditiveExpressionNoInContext::multiplicativeExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::MultiplicativeExpressionNoInContext>();
}

JavaScriptParser::MultiplicativeExpressionNoInContext* JavaScriptParser::AdditiveExpressionNoInContext::multiplicativeExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::MultiplicativeExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::AdditiveExpressionNoInContext::ADD() {
  return getTokens(JavaScriptParser::ADD);
}

tree::TerminalNode* JavaScriptParser::AdditiveExpressionNoInContext::ADD(size_t i) {
  return getToken(JavaScriptParser::ADD, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::AdditiveExpressionNoInContext::SUB() {
  return getTokens(JavaScriptParser::SUB);
}

tree::TerminalNode* JavaScriptParser::AdditiveExpressionNoInContext::SUB(size_t i) {
  return getToken(JavaScriptParser::SUB, i);
}


size_t JavaScriptParser::AdditiveExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleAdditiveExpressionNoIn;
}

void JavaScriptParser::AdditiveExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpressionNoIn(this);
}

void JavaScriptParser::AdditiveExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpressionNoIn(this);
}

JavaScriptParser::AdditiveExpressionNoInContext* JavaScriptParser::additiveExpressionNoIn() {
  AdditiveExpressionNoInContext *_localctx = _tracker.createInstance<AdditiveExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 226, JavaScriptParser::RuleAdditiveExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1149);
    multiplicativeExpressionNoIn();
    setState(1154);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::ADD

    || _la == JavaScriptParser::SUB) {
      setState(1150);
      _la = _input->LA(1);
      if (!(_la == JavaScriptParser::ADD

      || _la == JavaScriptParser::SUB)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1151);
      multiplicativeExpressionNoIn();
      setState(1156);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::MultiplicativeExpressionNoInContext::MultiplicativeExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::UnaryExpressionNoInContext *> JavaScriptParser::MultiplicativeExpressionNoInContext::unaryExpressionNoIn() {
  return getRuleContexts<JavaScriptParser::UnaryExpressionNoInContext>();
}

JavaScriptParser::UnaryExpressionNoInContext* JavaScriptParser::MultiplicativeExpressionNoInContext::unaryExpressionNoIn(size_t i) {
  return getRuleContext<JavaScriptParser::UnaryExpressionNoInContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::MultiplicativeExpressionNoInContext::MUL() {
  return getTokens(JavaScriptParser::MUL);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionNoInContext::MUL(size_t i) {
  return getToken(JavaScriptParser::MUL, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::MultiplicativeExpressionNoInContext::DIV() {
  return getTokens(JavaScriptParser::DIV);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionNoInContext::DIV(size_t i) {
  return getToken(JavaScriptParser::DIV, i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::MultiplicativeExpressionNoInContext::MOD() {
  return getTokens(JavaScriptParser::MOD);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionNoInContext::MOD(size_t i) {
  return getToken(JavaScriptParser::MOD, i);
}


size_t JavaScriptParser::MultiplicativeExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleMultiplicativeExpressionNoIn;
}

void JavaScriptParser::MultiplicativeExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpressionNoIn(this);
}

void JavaScriptParser::MultiplicativeExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpressionNoIn(this);
}

JavaScriptParser::MultiplicativeExpressionNoInContext* JavaScriptParser::multiplicativeExpressionNoIn() {
  MultiplicativeExpressionNoInContext *_localctx = _tracker.createInstance<MultiplicativeExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 228, JavaScriptParser::RuleMultiplicativeExpressionNoIn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1157);
    unaryExpressionNoIn();
    setState(1162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 103) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 103)) & ((1ULL << (JavaScriptParser::MUL - 103))
      | (1ULL << (JavaScriptParser::DIV - 103))
      | (1ULL << (JavaScriptParser::MOD - 103)))) != 0)) {
      setState(1158);
      _la = _input->LA(1);
      if (!(((((_la - 103) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 103)) & ((1ULL << (JavaScriptParser::MUL - 103))
        | (1ULL << (JavaScriptParser::DIV - 103))
        | (1ULL << (JavaScriptParser::MOD - 103)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1159);
      unaryExpressionNoIn();
      setState(1164);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionNoInContext ------------------------------------------------------------------

JavaScriptParser::UnaryExpressionNoInContext::UnaryExpressionNoInContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::UnaryOperatorContext* JavaScriptParser::UnaryExpressionNoInContext::unaryOperator() {
  return getRuleContext<JavaScriptParser::UnaryOperatorContext>(0);
}

JavaScriptParser::UnaryExpressionNoInContext* JavaScriptParser::UnaryExpressionNoInContext::unaryExpressionNoIn() {
  return getRuleContext<JavaScriptParser::UnaryExpressionNoInContext>(0);
}

JavaScriptParser::PostfixExpressionContext* JavaScriptParser::UnaryExpressionNoInContext::postfixExpression() {
  return getRuleContext<JavaScriptParser::PostfixExpressionContext>(0);
}


size_t JavaScriptParser::UnaryExpressionNoInContext::getRuleIndex() const {
  return JavaScriptParser::RuleUnaryExpressionNoIn;
}

void JavaScriptParser::UnaryExpressionNoInContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpressionNoIn(this);
}

void JavaScriptParser::UnaryExpressionNoInContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpressionNoIn(this);
}

JavaScriptParser::UnaryExpressionNoInContext* JavaScriptParser::unaryExpressionNoIn() {
  UnaryExpressionNoInContext *_localctx = _tracker.createInstance<UnaryExpressionNoInContext>(_ctx, getState());
  enterRule(_localctx, 230, JavaScriptParser::RuleUnaryExpressionNoIn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1169);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::VOID:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::BANG:
      case JavaScriptParser::TILDE:
      case JavaScriptParser::INC:
      case JavaScriptParser::DEC:
      case JavaScriptParser::ADD:
      case JavaScriptParser::SUB: {
        enterOuterAlt(_localctx, 1);
        setState(1165);
        unaryOperator();
        setState(1166);
        unaryExpressionNoIn();
        break;
      }

      case JavaScriptParser::NEW:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::CLASS:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::IDENTIFIER:
      case JavaScriptParser::LPAREN:
      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(1168);
        postfixExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceElementsContext ------------------------------------------------------------------

JavaScriptParser::SourceElementsContext::SourceElementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::SourceElementContext *> JavaScriptParser::SourceElementsContext::sourceElement() {
  return getRuleContexts<JavaScriptParser::SourceElementContext>();
}

JavaScriptParser::SourceElementContext* JavaScriptParser::SourceElementsContext::sourceElement(size_t i) {
  return getRuleContext<JavaScriptParser::SourceElementContext>(i);
}


size_t JavaScriptParser::SourceElementsContext::getRuleIndex() const {
  return JavaScriptParser::RuleSourceElements;
}

void JavaScriptParser::SourceElementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceElements(this);
}

void JavaScriptParser::SourceElementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceElements(this);
}

JavaScriptParser::SourceElementsContext* JavaScriptParser::sourceElements() {
  SourceElementsContext *_localctx = _tracker.createInstance<SourceElementsContext>(_ctx, getState());
  enterRule(_localctx, 232, JavaScriptParser::RuleSourceElements);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1172); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(1171);
      sourceElement();
      setState(1174); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::YIELD))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (JavaScriptParser::IDENTIFIER - 82))
      | (1ULL << (JavaScriptParser::LPAREN - 82))
      | (1ULL << (JavaScriptParser::LBRACE - 82))
      | (1ULL << (JavaScriptParser::LBRACKET - 82))
      | (1ULL << (JavaScriptParser::SEMICOLON - 82))
      | (1ULL << (JavaScriptParser::ASSIGN - 82))
      | (1ULL << (JavaScriptParser::BANG - 82))
      | (1ULL << (JavaScriptParser::TILDE - 82))
      | (1ULL << (JavaScriptParser::INC - 82))
      | (1ULL << (JavaScriptParser::DEC - 82))
      | (1ULL << (JavaScriptParser::ADD - 82))
      | (1ULL << (JavaScriptParser::SUB - 82))
      | (1ULL << (JavaScriptParser::ADD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::SUB_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MUL_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::DIV_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::MOD_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::POWER_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::LSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::RSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::URSHIFT_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::AND_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::OR_ASSIGN - 82))
      | (1ULL << (JavaScriptParser::XOR_ASSIGN - 82)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool JavaScriptParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 80: return callExpressionSempred(dynamic_cast<CallExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::callExpressionSempred(CallExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 13);
    case 1: return precpred(_ctx, 12);
    case 2: return precpred(_ctx, 11);
    case 3: return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> JavaScriptParser::_decisionToDFA;
atn::PredictionContextCache JavaScriptParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN JavaScriptParser::_atn;
std::vector<uint16_t> JavaScriptParser::_serializedATN;

std::vector<std::string> JavaScriptParser::_ruleNames = {
  "program", "sourceElement", "statement", "block", "statementList", "variableStatement", 
  "variableDeclarationList", "variableDeclaration", "bindingPattern", "objectBindingPattern", 
  "bindingProperty", "bindingElement", "arrayBindingPattern", "propertyName", 
  "identifierName", "reservedWord", "keyword", "futureReservedWord", "stringLiteral", 
  "numericLiteral", "initializer", "emptyStatement", "expressionStatement", 
  "ifStatement", "iterationStatement", "continueStatement", "breakStatement", 
  "returnStatement", "yieldStatement", "withStatement", "labelledStatement", 
  "switchStatement", "caseBlock", "caseClauses", "caseClause", "defaultClause", 
  "throwStatement", "tryStatement", "catchBlock", "finallyBlock", "debuggerStatement", 
  "functionDeclaration", "formalParameterList", "formalParameterArg", "functionBody", 
  "classDeclaration", "classBody", "classElement", "methodDefinition", "importStatement", 
  "importClause", "defaultImport", "nameSpaceImport", "namedImports", "importSpecifier", 
  "fromClause", "moduleSpecifier", "exportStatement", "exportClause", "namedExports", 
  "exportSpecifier", "defaultExport", "expression", "assignmentExpression", 
  "assignmentOperator", "conditionalExpression", "logicalORExpression", 
  "logicalANDExpression", "bitwiseORExpression", "bitwiseXORExpression", 
  "bitwiseANDExpression", "equalityExpression", "relationalExpression", 
  "shiftExpression", "additiveExpression", "multiplicativeExpression", "unaryExpression", 
  "unaryOperator", "postfixExpression", "leftHandSideExpression", "callExpression", 
  "arguments", "argumentList", "newExpression", "superProperty", "functionExpression", 
  "classExpression", "identifier", "thisExpression", "arrayLiteral", "elementList", 
  "objectLiteral", "propertyDefinition", "parenthesizedExpression", "templateLiteral", 
  "templateElement", "templateCharacters", "templateSubstitution", "yieldExpression", 
  "arrowFunction", "arrowParameters", "arrowFunctionBody", "expressionNoIn", 
  "assignmentExpressionNoIn", "conditionalExpressionNoIn", "logicalORExpressionNoIn", 
  "logicalANDExpressionNoIn", "bitwiseORExpressionNoIn", "bitwiseXORExpressionNoIn", 
  "bitwiseANDExpressionNoIn", "equalityExpressionNoIn", "relationalExpressionNoIn", 
  "shiftExpressionNoIn", "additiveExpressionNoIn", "multiplicativeExpressionNoIn", 
  "unaryExpressionNoIn", "sourceElements"
};

std::vector<std::string> JavaScriptParser::_literalNames = {
  "", "'$'", "", "", "", "'break'", "'do'", "'instanceof'", "'typeof'", 
  "'case'", "'else'", "'new'", "'var'", "'catch'", "'finally'", "'return'", 
  "'void'", "'continue'", "'for'", "'switch'", "'while'", "'debugger'", 
  "'function'", "'this'", "'with'", "'default'", "'if'", "'throw'", "'delete'", 
  "'in'", "'try'", "'class'", "'enum'", "'extends'", "'super'", "'const'", 
  "'export'", "'import'", "'let'", "'static'", "'yield'", "'implements'", 
  "'interface'", "'package'", "'private'", "'protected'", "'public'", "'abstract'", 
  "'boolean'", "'byte'", "'char'", "'double'", "'final'", "'float'", "'goto'", 
  "'int'", "'long'", "'native'", "'short'", "'synchronized'", "'throws'", 
  "'transient'", "'volatile'", "'null'", "'true'", "'false'", "'=>'", "'async'", 
  "'await'", "'get'", "'set'", "", "", "", "", "", "", "", "", "", "", "", 
  "", "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "':'", "','", "'.'", 
  "'='", "'>'", "'<'", "'!'", "'~'", "'\u003F'", "'++'", "'--'", "'+'", 
  "'-'", "", "'/'", "'%'", "'**'", "'+='", "'-='", "'*='", "'/='", "'%='", 
  "'**='", "'<<'", "'>>'", "'>>>'", "'<<='", "'>>='", "'>>>='", "'&'", "'|'", 
  "'^'", "'&='", "'|='", "'^='", "'...'", "", "", "'as'", "'`'", "'||'", 
  "'&&'", "'=='", "'!='", "'<='", "'>='"
};

std::vector<std::string> JavaScriptParser::_symbolicNames = {
  "", "", "WS", "COMMENT", "MULTILINE_COMMENT", "BREAK", "DO", "INSTANCEOF", 
  "TYPEOF", "CASE", "ELSE", "NEW", "VAR", "CATCH", "FINALLY", "RETURN", 
  "VOID", "CONTINUE", "FOR", "SWITCH", "WHILE", "DEBUGGER", "FUNCTION", 
  "THIS", "WITH", "DEFAULT", "IF", "THROW", "DELETE", "IN", "TRY", "CLASS", 
  "ENUM", "EXTENDS", "SUPER", "CONST", "EXPORT", "IMPORT", "LET", "STATIC", 
  "YIELD", "IMPLEMENTS", "INTERFACE", "PACKAGE", "PRIVATE", "PROTECTED", 
  "PUBLIC", "ABSTRACT", "BOOLEAN", "BYTE", "CHAR", "DOUBLE", "FINAL", "FLOAT", 
  "GOTO", "INT", "LONG", "NATIVE", "SHORT", "SYNCHRONIZED", "THROWS", "TRANSIENT", 
  "VOLATILE", "NULL", "TRUE", "FALSE", "ARROW", "ASYNC", "AWAIT", "GET", 
  "SET", "LITERAL", "STRING", "NUMBER", "DECIMAL_LITERAL", "HEX_INTEGER_LITERAL", 
  "OCTAL_INTEGER_LITERAL", "BINARY_INTEGER_LITERAL", "EXPONENT_PART", "REGEX", 
  "REGEX_BODY", "REGEX_FLAGS", "IDENTIFIER", "LPAREN", "RPAREN", "LBRACE", 
  "RBRACE", "LBRACKET", "RBRACKET", "SEMICOLON", "COLON", "COMMA", "DOT", 
  "ASSIGN", "GT", "LT", "BANG", "TILDE", "QUESTION", "INC", "DEC", "ADD", 
  "SUB", "MUL", "DIV", "MOD", "POWER", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", 
  "DIV_ASSIGN", "MOD_ASSIGN", "POWER_ASSIGN", "LSHIFT", "RSHIFT", "URSHIFT", 
  "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "URSHIFT_ASSIGN", "BITAND", "BITOR", 
  "CARET", "AND_ASSIGN", "OR_ASSIGN", "XOR_ASSIGN", "ELLIPSIS", "TEMPLATE_CHAR", 
  "ASTERISK", "AS", "BACKTICK", "OR", "AND", "EQUAL", "NOTEQUAL", "LE", 
  "GE", "OF", "FROM"
};

dfa::Vocabulary JavaScriptParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> JavaScriptParser::_tokenNames;

JavaScriptParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x8b, 0x49b, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 
       0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 
       0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 
       0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 0x9, 0x1f, 0x4, 0x20, 
       0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 0x9, 0x22, 0x4, 0x23, 
       0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 0x25, 0x4, 0x26, 
       0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 0x4, 0x29, 
       0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 0x2c, 
       0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
       0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 
       0x9, 0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 
       0x9, 0x35, 0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 
       0x9, 0x38, 0x4, 0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 
       0x9, 0x3b, 0x4, 0x3c, 0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 
       0x9, 0x3e, 0x4, 0x3f, 0x9, 0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 
       0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 
       0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 0x46, 0x9, 0x46, 0x4, 0x47, 
       0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 0x9, 0x49, 0x4, 0x4a, 
       0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 0x4c, 0x4, 0x4d, 
       0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 0x4, 0x50, 
       0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 0x53, 
       0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
       0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 
       0x9, 0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 
       0x9, 0x5c, 0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 
       0x9, 0x5f, 0x4, 0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 
       0x9, 0x62, 0x4, 0x63, 0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 
       0x9, 0x65, 0x4, 0x66, 0x9, 0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 
       0x9, 0x68, 0x4, 0x69, 0x9, 0x69, 0x4, 0x6a, 0x9, 0x6a, 0x4, 0x6b, 
       0x9, 0x6b, 0x4, 0x6c, 0x9, 0x6c, 0x4, 0x6d, 0x9, 0x6d, 0x4, 0x6e, 
       0x9, 0x6e, 0x4, 0x6f, 0x9, 0x6f, 0x4, 0x70, 0x9, 0x70, 0x4, 0x71, 
       0x9, 0x71, 0x4, 0x72, 0x9, 0x72, 0x4, 0x73, 0x9, 0x73, 0x4, 0x74, 
       0x9, 0x74, 0x4, 0x75, 0x9, 0x75, 0x4, 0x76, 0x9, 0x76, 0x3, 0x2, 
       0x7, 0x2, 0xee, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0xf1, 0xb, 0x2, 0x3, 
       0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0xf8, 0xa, 
       0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 
       0x10c, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x110, 0xa, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x6, 0x6, 0x6, 0x115, 0xa, 0x6, 0xd, 0x6, 0xe, 
       0x6, 0x116, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 
       0x8, 0x3, 0x8, 0x7, 0x8, 0x120, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x123, 
       0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x127, 0xa, 0x9, 0x3, 0x9, 
       0x3, 0x9, 0x5, 0x9, 0x12b, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 
       0x12f, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 
       0x135, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x138, 0xb, 0xb, 0x5, 0xb, 0x13a, 
       0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 
       0xc, 0x141, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x5, 
       0xd, 0x147, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x14b, 0xa, 0xd, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0x151, 0xa, 0xe, 
       0xc, 0xe, 0xe, 0xe, 0x154, 0xb, 0xe, 0x5, 0xe, 0x156, 0xa, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x15d, 0xa, 
       0xf, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x161, 0xa, 0x10, 0x3, 0x11, 
       0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x166, 0xa, 0x11, 0x3, 0x12, 0x3, 
       0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 
       0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 
       0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
       0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x17f, 0xa, 0x19, 
       0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
       0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
       0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
       0x5, 0x1a, 0x193, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x197, 
       0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x19b, 0xa, 0x1a, 0x3, 
       0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 
       0x1a, 0x1a3, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
       0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
       0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
       0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 
       0x1ba, 0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x1be, 0xa, 0x1b, 
       0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x1c4, 0xa, 
       0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x1ca, 
       0xa, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 
       0x1d0, 0xa, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
       0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 
       0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 
       0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x1e6, 0xa, 0x22, 
       0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x1ea, 0xa, 0x22, 0x5, 0x22, 0x1ec, 
       0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x6, 0x23, 0x1f1, 0xa, 
       0x23, 0xd, 0x23, 0xe, 0x23, 0x1f2, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 
       0x3, 0x24, 0x5, 0x24, 0x1f9, 0xa, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 
       0x25, 0x5, 0x25, 0x1fe, 0xa, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 
       0x3, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x207, 0xa, 
       0x27, 0x3, 0x27, 0x5, 0x27, 0x20a, 0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 
       0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x211, 0xa, 0x27, 0x3, 
       0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 0x217, 0xa, 0x28, 
       0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 
       0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 
       0x3, 0x2b, 0x5, 0x2b, 0x226, 0xa, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 
       0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x7, 
       0x2c, 0x230, 0xa, 0x2c, 0xc, 0x2c, 0xe, 0x2c, 0x233, 0xb, 0x2c, 0x3, 
       0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x23a, 
       0xa, 0x2d, 0x5, 0x2d, 0x23c, 0xa, 0x2d, 0x3, 0x2e, 0x5, 0x2e, 0x23f, 
       0xa, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 
       0x245, 0xa, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 0x249, 0xa, 0x2f, 
       0x3, 0x2f, 0x3, 0x2f, 0x3, 0x30, 0x6, 0x30, 0x24e, 0xa, 0x30, 0xd, 
       0x30, 0xe, 0x30, 0x24f, 0x3, 0x31, 0x3, 0x31, 0x3, 0x32, 0x5, 0x32, 
       0x255, 0xa, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x25a, 
       0xa, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 
       0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 
       0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x5, 0x33, 0x26a, 0xa, 0x33, 0x3, 
       0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 
       0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x5, 0x34, 0x277, 
       0xa, 0x34, 0x3, 0x35, 0x3, 0x35, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 
       0x3, 0x36, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x7, 0x37, 
       0x283, 0xa, 0x37, 0xc, 0x37, 0xe, 0x37, 0x286, 0xb, 0x37, 0x5, 0x37, 
       0x288, 0xa, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 
       0x38, 0x3, 0x38, 0x3, 0x38, 0x5, 0x38, 0x291, 0xa, 0x38, 0x3, 0x39, 
       0x3, 0x39, 0x3, 0x39, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x5, 0x3b, 0x29b, 0xa, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x2a3, 0xa, 0x3b, 
       0x3, 0x3b, 0x5, 0x3b, 0x2a6, 0xa, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x5, 
       0x3b, 0x2aa, 0xa, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 
       0x2af, 0xa, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x7, 
       0x3d, 0x2b5, 0xa, 0x3d, 0xc, 0x3d, 0xe, 0x3d, 0x2b8, 0xb, 0x3d, 0x5, 
       0x3d, 0x2ba, 0xa, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 
       0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x5, 0x3e, 0x2c3, 0xa, 0x3e, 0x3, 
       0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x2c8, 0xa, 0x3f, 0x3, 0x40, 
       0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x2cd, 0xa, 0x40, 0xc, 0x40, 0xe, 
       0x40, 0x2d0, 0xb, 0x40, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 
       0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x2d8, 0xa, 0x41, 0x3, 0x42, 0x3, 
       0x42, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 
       0x43, 0x5, 0x43, 0x2e2, 0xa, 0x43, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 
       0x7, 0x44, 0x2e7, 0xa, 0x44, 0xc, 0x44, 0xe, 0x44, 0x2ea, 0xb, 0x44, 
       0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x7, 0x45, 0x2ef, 0xa, 0x45, 0xc, 
       0x45, 0xe, 0x45, 0x2f2, 0xb, 0x45, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 
       0x7, 0x46, 0x2f7, 0xa, 0x46, 0xc, 0x46, 0xe, 0x46, 0x2fa, 0xb, 0x46, 
       0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x7, 0x47, 0x2ff, 0xa, 0x47, 0xc, 
       0x47, 0xe, 0x47, 0x302, 0xb, 0x47, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 
       0x7, 0x48, 0x307, 0xa, 0x48, 0xc, 0x48, 0xe, 0x48, 0x30a, 0xb, 0x48, 
       0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x7, 0x49, 0x30f, 0xa, 0x49, 0xc, 
       0x49, 0xe, 0x49, 0x312, 0xb, 0x49, 0x3, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 
       0x7, 0x4a, 0x317, 0xa, 0x4a, 0xc, 0x4a, 0xe, 0x4a, 0x31a, 0xb, 0x4a, 
       0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x7, 0x4b, 0x31f, 0xa, 0x4b, 0xc, 
       0x4b, 0xe, 0x4b, 0x322, 0xb, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x7, 0x4c, 0x327, 0xa, 0x4c, 0xc, 0x4c, 0xe, 0x4c, 0x32a, 0xb, 0x4c, 
       0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x7, 0x4d, 0x32f, 0xa, 0x4d, 0xc, 
       0x4d, 0xe, 0x4d, 0x332, 0xb, 0x4d, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 
       0x3, 0x4e, 0x5, 0x4e, 0x338, 0xa, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x3, 
       0x50, 0x3, 0x50, 0x5, 0x50, 0x33e, 0xa, 0x50, 0x3, 0x51, 0x3, 0x51, 
       0x5, 0x51, 0x342, 0xa, 0x51, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 
       0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 
       0x52, 0x5, 0x52, 0x34e, 0xa, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 
       0x5, 0x52, 0x353, 0xa, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 
       0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 
       0x52, 0x3, 0x52, 0x7, 0x52, 0x360, 0xa, 0x52, 0xc, 0x52, 0xe, 0x52, 
       0x363, 0xb, 0x52, 0x3, 0x53, 0x3, 0x53, 0x3, 0x54, 0x3, 0x54, 0x3, 
       0x54, 0x7, 0x54, 0x36a, 0xa, 0x54, 0xc, 0x54, 0xe, 0x54, 0x36d, 0xb, 
       0x54, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 
       0x55, 0x5, 0x55, 0x375, 0xa, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 
       0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 
       0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 
       0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 
       0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x390, 0xa, 
       0x55, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 
       0x56, 0x3, 0x56, 0x3, 0x56, 0x5, 0x56, 0x39a, 0xa, 0x56, 0x3, 0x57, 
       0x3, 0x57, 0x5, 0x57, 0x39e, 0xa, 0x57, 0x3, 0x57, 0x3, 0x57, 0x5, 
       0x57, 0x3a2, 0xa, 0x57, 0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 
       0x3, 0x57, 0x3, 0x58, 0x3, 0x58, 0x5, 0x58, 0x3ab, 0xa, 0x58, 0x3, 
       0x58, 0x3, 0x58, 0x5, 0x58, 0x3af, 0xa, 0x58, 0x3, 0x58, 0x3, 0x58, 
       0x5, 0x58, 0x3b3, 0xa, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x59, 0x3, 
       0x59, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x5, 
       0x5b, 0x3be, 0xa, 0x5b, 0x5, 0x5b, 0x3c0, 0xa, 0x5b, 0x3, 0x5b, 0x3, 
       0x5b, 0x3, 0x5c, 0x5, 0x5c, 0x3c5, 0xa, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 
       0x3, 0x5c, 0x5, 0x5c, 0x3ca, 0xa, 0x5c, 0x3, 0x5c, 0x7, 0x5c, 0x3cd, 
       0xa, 0x5c, 0xc, 0x5c, 0xe, 0x5c, 0x3d0, 0xb, 0x5c, 0x3, 0x5d, 0x3, 
       0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x7, 0x5d, 0x3d6, 0xa, 0x5d, 0xc, 0x5d, 
       0xe, 0x5d, 0x3d9, 0xb, 0x5d, 0x5, 0x5d, 0x3db, 0xa, 0x5d, 0x3, 0x5d, 
       0x3, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 
       0x5, 0x5e, 0x3e4, 0xa, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x5, 
       0x5e, 0x3e9, 0xa, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 
       0x3, 0x5e, 0x3, 0x5e, 0x5, 0x5e, 0x3f1, 0xa, 0x5e, 0x3, 0x5e, 0x5, 
       0x5e, 0x3f4, 0xa, 0x5e, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 
       0x3, 0x60, 0x3, 0x60, 0x6, 0x60, 0x3fc, 0xa, 0x60, 0xd, 0x60, 0xe, 
       0x60, 0x3fd, 0x3, 0x60, 0x3, 0x60, 0x3, 0x61, 0x3, 0x61, 0x5, 0x61, 
       0x404, 0xa, 0x61, 0x3, 0x62, 0x6, 0x62, 0x407, 0xa, 0x62, 0xd, 0x62, 
       0xe, 0x62, 0x408, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 
       0x63, 0x3, 0x64, 0x3, 0x64, 0x5, 0x64, 0x412, 0xa, 0x64, 0x3, 0x65, 
       0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 
       0x5, 0x66, 0x41b, 0xa, 0x66, 0x3, 0x66, 0x3, 0x66, 0x5, 0x66, 0x41f, 
       0xa, 0x66, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 
       0x5, 0x67, 0x426, 0xa, 0x67, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x7, 
       0x68, 0x42b, 0xa, 0x68, 0xc, 0x68, 0xe, 0x68, 0x42e, 0xb, 0x68, 0x3, 
       0x69, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x5, 
       0x69, 0x436, 0xa, 0x69, 0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6a, 
       0x3, 0x6a, 0x3, 0x6a, 0x5, 0x6a, 0x43e, 0xa, 0x6a, 0x3, 0x6b, 0x3, 
       0x6b, 0x3, 0x6b, 0x7, 0x6b, 0x443, 0xa, 0x6b, 0xc, 0x6b, 0xe, 0x6b, 
       0x446, 0xb, 0x6b, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x7, 0x6c, 0x44b, 
       0xa, 0x6c, 0xc, 0x6c, 0xe, 0x6c, 0x44e, 0xb, 0x6c, 0x3, 0x6d, 0x3, 
       0x6d, 0x3, 0x6d, 0x7, 0x6d, 0x453, 0xa, 0x6d, 0xc, 0x6d, 0xe, 0x6d, 
       0x456, 0xb, 0x6d, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x7, 0x6e, 0x45b, 
       0xa, 0x6e, 0xc, 0x6e, 0xe, 0x6e, 0x45e, 0xb, 0x6e, 0x3, 0x6f, 0x3, 
       0x6f, 0x3, 0x6f, 0x7, 0x6f, 0x463, 0xa, 0x6f, 0xc, 0x6f, 0xe, 0x6f, 
       0x466, 0xb, 0x6f, 0x3, 0x70, 0x3, 0x70, 0x3, 0x70, 0x7, 0x70, 0x46b, 
       0xa, 0x70, 0xc, 0x70, 0xe, 0x70, 0x46e, 0xb, 0x70, 0x3, 0x71, 0x3, 
       0x71, 0x3, 0x71, 0x7, 0x71, 0x473, 0xa, 0x71, 0xc, 0x71, 0xe, 0x71, 
       0x476, 0xb, 0x71, 0x3, 0x72, 0x3, 0x72, 0x3, 0x72, 0x7, 0x72, 0x47b, 
       0xa, 0x72, 0xc, 0x72, 0xe, 0x72, 0x47e, 0xb, 0x72, 0x3, 0x73, 0x3, 
       0x73, 0x3, 0x73, 0x7, 0x73, 0x483, 0xa, 0x73, 0xc, 0x73, 0xe, 0x73, 
       0x486, 0xb, 0x73, 0x3, 0x74, 0x3, 0x74, 0x3, 0x74, 0x7, 0x74, 0x48b, 
       0xa, 0x74, 0xc, 0x74, 0xe, 0x74, 0x48e, 0xb, 0x74, 0x3, 0x75, 0x3, 
       0x75, 0x3, 0x75, 0x3, 0x75, 0x5, 0x75, 0x494, 0xa, 0x75, 0x3, 0x76, 
       0x6, 0x76, 0x497, 0xa, 0x76, 0xd, 0x76, 0xe, 0x76, 0x498, 0x3, 0x76, 
       0x2, 0x3, 0xa2, 0x77, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 
       0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 
       0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 
       0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 
       0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 
       0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x80, 
       0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 
       0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 
       0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 0xc0, 0xc2, 
       0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 
       0xda, 0xdc, 0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0x2, 0x10, 
       0x5, 0x2, 0xe, 0xe, 0x25, 0x25, 0x28, 0x28, 0x3, 0x2, 0x41, 0x43, 
       0x3, 0x2, 0x7, 0x20, 0x3, 0x2, 0x21, 0x40, 0x3, 0x2, 0x47, 0x48, 
       0x6, 0x2, 0x5f, 0x5f, 0x6d, 0x72, 0x76, 0x78, 0x7c, 0x7e, 0x3, 0x2, 
       0x86, 0x87, 0x6, 0x2, 0x9, 0x9, 0x1f, 0x1f, 0x60, 0x61, 0x88, 0x89, 
       0x3, 0x2, 0x73, 0x75, 0x3, 0x2, 0x67, 0x68, 0x3, 0x2, 0x69, 0x6b, 
       0x7, 0x2, 0xa, 0xa, 0x12, 0x12, 0x1e, 0x1e, 0x62, 0x63, 0x65, 0x68, 
       0x3, 0x2, 0x65, 0x66, 0x5, 0x2, 0x9, 0x9, 0x60, 0x61, 0x88, 0x89, 
       0x2, 0x4da, 0x2, 0xef, 0x3, 0x2, 0x2, 0x2, 0x4, 0xf7, 0x3, 0x2, 0x2, 
       0x2, 0x6, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x8, 0x10d, 0x3, 0x2, 0x2, 0x2, 
       0xa, 0x114, 0x3, 0x2, 0x2, 0x2, 0xc, 0x118, 0x3, 0x2, 0x2, 0x2, 0xe, 
       0x11c, 0x3, 0x2, 0x2, 0x2, 0x10, 0x126, 0x3, 0x2, 0x2, 0x2, 0x12, 
       0x12e, 0x3, 0x2, 0x2, 0x2, 0x14, 0x130, 0x3, 0x2, 0x2, 0x2, 0x16, 
       0x140, 0x3, 0x2, 0x2, 0x2, 0x18, 0x146, 0x3, 0x2, 0x2, 0x2, 0x1a, 
       0x14c, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x1e, 
       0x160, 0x3, 0x2, 0x2, 0x2, 0x20, 0x165, 0x3, 0x2, 0x2, 0x2, 0x22, 
       0x167, 0x3, 0x2, 0x2, 0x2, 0x24, 0x169, 0x3, 0x2, 0x2, 0x2, 0x26, 
       0x16b, 0x3, 0x2, 0x2, 0x2, 0x28, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x2a, 
       0x16f, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x172, 0x3, 0x2, 0x2, 0x2, 0x2e, 
       0x174, 0x3, 0x2, 0x2, 0x2, 0x30, 0x177, 0x3, 0x2, 0x2, 0x2, 0x32, 
       0x1b9, 0x3, 0x2, 0x2, 0x2, 0x34, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x36, 
       0x1c1, 0x3, 0x2, 0x2, 0x2, 0x38, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x3a, 
       0x1cd, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x1d3, 0x3, 0x2, 0x2, 0x2, 0x3e, 
       0x1d9, 0x3, 0x2, 0x2, 0x2, 0x40, 0x1dd, 0x3, 0x2, 0x2, 0x2, 0x42, 
       0x1e3, 0x3, 0x2, 0x2, 0x2, 0x44, 0x1f0, 0x3, 0x2, 0x2, 0x2, 0x46, 
       0x1f4, 0x3, 0x2, 0x2, 0x2, 0x48, 0x1fa, 0x3, 0x2, 0x2, 0x2, 0x4a, 
       0x1ff, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x210, 0x3, 0x2, 0x2, 0x2, 0x4e, 
       0x212, 0x3, 0x2, 0x2, 0x2, 0x50, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x52, 
       0x21e, 0x3, 0x2, 0x2, 0x2, 0x54, 0x221, 0x3, 0x2, 0x2, 0x2, 0x56, 
       0x22c, 0x3, 0x2, 0x2, 0x2, 0x58, 0x23b, 0x3, 0x2, 0x2, 0x2, 0x5a, 
       0x23e, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x240, 0x3, 0x2, 0x2, 0x2, 0x5e, 
       0x24d, 0x3, 0x2, 0x2, 0x2, 0x60, 0x251, 0x3, 0x2, 0x2, 0x2, 0x62, 
       0x254, 0x3, 0x2, 0x2, 0x2, 0x64, 0x269, 0x3, 0x2, 0x2, 0x2, 0x66, 
       0x276, 0x3, 0x2, 0x2, 0x2, 0x68, 0x278, 0x3, 0x2, 0x2, 0x2, 0x6a, 
       0x27a, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x27e, 0x3, 0x2, 0x2, 0x2, 0x6e, 
       0x290, 0x3, 0x2, 0x2, 0x2, 0x70, 0x292, 0x3, 0x2, 0x2, 0x2, 0x72, 
       0x295, 0x3, 0x2, 0x2, 0x2, 0x74, 0x2a9, 0x3, 0x2, 0x2, 0x2, 0x76, 
       0x2ae, 0x3, 0x2, 0x2, 0x2, 0x78, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x7a, 
       0x2c2, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x2c7, 0x3, 0x2, 0x2, 0x2, 0x7e, 
       0x2c9, 0x3, 0x2, 0x2, 0x2, 0x80, 0x2d7, 0x3, 0x2, 0x2, 0x2, 0x82, 
       0x2d9, 0x3, 0x2, 0x2, 0x2, 0x84, 0x2db, 0x3, 0x2, 0x2, 0x2, 0x86, 
       0x2e3, 0x3, 0x2, 0x2, 0x2, 0x88, 0x2eb, 0x3, 0x2, 0x2, 0x2, 0x8a, 
       0x2f3, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x8e, 
       0x303, 0x3, 0x2, 0x2, 0x2, 0x90, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x92, 
       0x313, 0x3, 0x2, 0x2, 0x2, 0x94, 0x31b, 0x3, 0x2, 0x2, 0x2, 0x96, 
       0x323, 0x3, 0x2, 0x2, 0x2, 0x98, 0x32b, 0x3, 0x2, 0x2, 0x2, 0x9a, 
       0x337, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x339, 0x3, 0x2, 0x2, 0x2, 0x9e, 
       0x33b, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x341, 0x3, 0x2, 0x2, 0x2, 0xa2, 
       0x34d, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x364, 0x3, 0x2, 0x2, 0x2, 0xa6, 
       0x366, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x38f, 0x3, 0x2, 0x2, 0x2, 0xaa, 
       0x399, 0x3, 0x2, 0x2, 0x2, 0xac, 0x39b, 0x3, 0x2, 0x2, 0x2, 0xae, 
       0x3a8, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x3b6, 0x3, 0x2, 0x2, 0x2, 0xb2, 
       0x3b8, 0x3, 0x2, 0x2, 0x2, 0xb4, 0x3ba, 0x3, 0x2, 0x2, 0x2, 0xb6, 
       0x3c4, 0x3, 0x2, 0x2, 0x2, 0xb8, 0x3d1, 0x3, 0x2, 0x2, 0x2, 0xba, 
       0x3f3, 0x3, 0x2, 0x2, 0x2, 0xbc, 0x3f5, 0x3, 0x2, 0x2, 0x2, 0xbe, 
       0x3f9, 0x3, 0x2, 0x2, 0x2, 0xc0, 0x403, 0x3, 0x2, 0x2, 0x2, 0xc2, 
       0x406, 0x3, 0x2, 0x2, 0x2, 0xc4, 0x40a, 0x3, 0x2, 0x2, 0x2, 0xc6, 
       0x40f, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x413, 0x3, 0x2, 0x2, 0x2, 0xca, 
       0x41e, 0x3, 0x2, 0x2, 0x2, 0xcc, 0x425, 0x3, 0x2, 0x2, 0x2, 0xce, 
       0x427, 0x3, 0x2, 0x2, 0x2, 0xd0, 0x435, 0x3, 0x2, 0x2, 0x2, 0xd2, 
       0x437, 0x3, 0x2, 0x2, 0x2, 0xd4, 0x43f, 0x3, 0x2, 0x2, 0x2, 0xd6, 
       0x447, 0x3, 0x2, 0x2, 0x2, 0xd8, 0x44f, 0x3, 0x2, 0x2, 0x2, 0xda, 
       0x457, 0x3, 0x2, 0x2, 0x2, 0xdc, 0x45f, 0x3, 0x2, 0x2, 0x2, 0xde, 
       0x467, 0x3, 0x2, 0x2, 0x2, 0xe0, 0x46f, 0x3, 0x2, 0x2, 0x2, 0xe2, 
       0x477, 0x3, 0x2, 0x2, 0x2, 0xe4, 0x47f, 0x3, 0x2, 0x2, 0x2, 0xe6, 
       0x487, 0x3, 0x2, 0x2, 0x2, 0xe8, 0x493, 0x3, 0x2, 0x2, 0x2, 0xea, 
       0x496, 0x3, 0x2, 0x2, 0x2, 0xec, 0xee, 0x5, 0x4, 0x3, 0x2, 0xed, 
       0xec, 0x3, 0x2, 0x2, 0x2, 0xee, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xef, 0xed, 
       0x3, 0x2, 0x2, 0x2, 0xef, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf2, 0x3, 
       0x2, 0x2, 0x2, 0xf1, 0xef, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf3, 0x7, 0x2, 
       0x2, 0x3, 0xf3, 0x3, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf8, 0x5, 0x6, 0x4, 
       0x2, 0xf5, 0xf8, 0x5, 0x54, 0x2b, 0x2, 0xf6, 0xf8, 0x5, 0x5c, 0x2f, 
       0x2, 0xf7, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf5, 0x3, 0x2, 0x2, 0x2, 
       0xf7, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf8, 0x5, 0x3, 0x2, 0x2, 0x2, 0xf9, 
       0x10c, 0x5, 0x8, 0x5, 0x2, 0xfa, 0x10c, 0x5, 0xc, 0x7, 0x2, 0xfb, 
       0x10c, 0x5, 0x2c, 0x17, 0x2, 0xfc, 0x10c, 0x5, 0x2e, 0x18, 0x2, 0xfd, 
       0x10c, 0x5, 0x30, 0x19, 0x2, 0xfe, 0x10c, 0x5, 0x32, 0x1a, 0x2, 0xff, 
       0x10c, 0x5, 0x34, 0x1b, 0x2, 0x100, 0x10c, 0x5, 0x36, 0x1c, 0x2, 
       0x101, 0x10c, 0x5, 0x38, 0x1d, 0x2, 0x102, 0x10c, 0x5, 0x3a, 0x1e, 
       0x2, 0x103, 0x10c, 0x5, 0x3c, 0x1f, 0x2, 0x104, 0x10c, 0x5, 0x3e, 
       0x20, 0x2, 0x105, 0x10c, 0x5, 0x40, 0x21, 0x2, 0x106, 0x10c, 0x5, 
       0x4a, 0x26, 0x2, 0x107, 0x10c, 0x5, 0x4c, 0x27, 0x2, 0x108, 0x10c, 
       0x5, 0x52, 0x2a, 0x2, 0x109, 0x10c, 0x5, 0x64, 0x33, 0x2, 0x10a, 
       0x10c, 0x5, 0x74, 0x3b, 0x2, 0x10b, 0xf9, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0xfa, 0x3, 0x2, 0x2, 0x2, 0x10b, 0xfb, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0xfc, 0x3, 0x2, 0x2, 0x2, 0x10b, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0xfe, 0x3, 0x2, 0x2, 0x2, 0x10b, 0xff, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0x100, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x101, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0x102, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x103, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0x104, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x105, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0x106, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x107, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0x108, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x109, 0x3, 0x2, 0x2, 0x2, 0x10b, 
       0x10a, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x7, 0x3, 0x2, 0x2, 0x2, 0x10d, 
       0x10f, 0x7, 0x57, 0x2, 0x2, 0x10e, 0x110, 0x5, 0xa, 0x6, 0x2, 0x10f, 
       0x10e, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 0x3, 0x2, 0x2, 0x2, 0x110, 
       0x111, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x7, 0x58, 0x2, 0x2, 0x112, 
       0x9, 0x3, 0x2, 0x2, 0x2, 0x113, 0x115, 0x5, 0x6, 0x4, 0x2, 0x114, 
       0x113, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 0x3, 0x2, 0x2, 0x2, 0x116, 
       0x114, 0x3, 0x2, 0x2, 0x2, 0x116, 0x117, 0x3, 0x2, 0x2, 0x2, 0x117, 
       0xb, 0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 0x9, 0x2, 0x2, 0x2, 0x119, 
       0x11a, 0x5, 0xe, 0x8, 0x2, 0x11a, 0x11b, 0x7, 0x5b, 0x2, 0x2, 0x11b, 
       0xd, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x121, 0x5, 0x10, 0x9, 0x2, 0x11d, 
       0x11e, 0x7, 0x5d, 0x2, 0x2, 0x11e, 0x120, 0x5, 0x10, 0x9, 0x2, 0x11f, 
       0x11d, 0x3, 0x2, 0x2, 0x2, 0x120, 0x123, 0x3, 0x2, 0x2, 0x2, 0x121, 
       0x11f, 0x3, 0x2, 0x2, 0x2, 0x121, 0x122, 0x3, 0x2, 0x2, 0x2, 0x122, 
       0xf, 0x3, 0x2, 0x2, 0x2, 0x123, 0x121, 0x3, 0x2, 0x2, 0x2, 0x124, 
       0x127, 0x5, 0xb0, 0x59, 0x2, 0x125, 0x127, 0x5, 0x12, 0xa, 0x2, 0x126, 
       0x124, 0x3, 0x2, 0x2, 0x2, 0x126, 0x125, 0x3, 0x2, 0x2, 0x2, 0x127, 
       0x12a, 0x3, 0x2, 0x2, 0x2, 0x128, 0x129, 0x7, 0x5f, 0x2, 0x2, 0x129, 
       0x12b, 0x5, 0x2a, 0x16, 0x2, 0x12a, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12a, 
       0x12b, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x11, 0x3, 0x2, 0x2, 0x2, 0x12c, 
       0x12f, 0x5, 0x14, 0xb, 0x2, 0x12d, 0x12f, 0x5, 0x1a, 0xe, 0x2, 0x12e, 
       0x12c, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x12f, 
       0x13, 0x3, 0x2, 0x2, 0x2, 0x130, 0x139, 0x7, 0x57, 0x2, 0x2, 0x131, 
       0x136, 0x5, 0x16, 0xc, 0x2, 0x132, 0x133, 0x7, 0x5d, 0x2, 0x2, 0x133, 
       0x135, 0x5, 0x16, 0xc, 0x2, 0x134, 0x132, 0x3, 0x2, 0x2, 0x2, 0x135, 
       0x138, 0x3, 0x2, 0x2, 0x2, 0x136, 0x134, 0x3, 0x2, 0x2, 0x2, 0x136, 
       0x137, 0x3, 0x2, 0x2, 0x2, 0x137, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x138, 
       0x136, 0x3, 0x2, 0x2, 0x2, 0x139, 0x131, 0x3, 0x2, 0x2, 0x2, 0x139, 
       0x13a, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x13b, 
       0x13c, 0x7, 0x58, 0x2, 0x2, 0x13c, 0x15, 0x3, 0x2, 0x2, 0x2, 0x13d, 
       0x13e, 0x5, 0x1c, 0xf, 0x2, 0x13e, 0x13f, 0x7, 0x5c, 0x2, 0x2, 0x13f, 
       0x141, 0x3, 0x2, 0x2, 0x2, 0x140, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x140, 
       0x141, 0x3, 0x2, 0x2, 0x2, 0x141, 0x142, 0x3, 0x2, 0x2, 0x2, 0x142, 
       0x143, 0x5, 0x18, 0xd, 0x2, 0x143, 0x17, 0x3, 0x2, 0x2, 0x2, 0x144, 
       0x147, 0x5, 0xb0, 0x59, 0x2, 0x145, 0x147, 0x5, 0x12, 0xa, 0x2, 0x146, 
       0x144, 0x3, 0x2, 0x2, 0x2, 0x146, 0x145, 0x3, 0x2, 0x2, 0x2, 0x147, 
       0x14a, 0x3, 0x2, 0x2, 0x2, 0x148, 0x149, 0x7, 0x5f, 0x2, 0x2, 0x149, 
       0x14b, 0x5, 0x2a, 0x16, 0x2, 0x14a, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14a, 
       0x14b, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x14c, 
       0x155, 0x7, 0x59, 0x2, 0x2, 0x14d, 0x152, 0x5, 0x18, 0xd, 0x2, 0x14e, 
       0x14f, 0x7, 0x5d, 0x2, 0x2, 0x14f, 0x151, 0x5, 0x18, 0xd, 0x2, 0x150, 
       0x14e, 0x3, 0x2, 0x2, 0x2, 0x151, 0x154, 0x3, 0x2, 0x2, 0x2, 0x152, 
       0x150, 0x3, 0x2, 0x2, 0x2, 0x152, 0x153, 0x3, 0x2, 0x2, 0x2, 0x153, 
       0x156, 0x3, 0x2, 0x2, 0x2, 0x154, 0x152, 0x3, 0x2, 0x2, 0x2, 0x155, 
       0x14d, 0x3, 0x2, 0x2, 0x2, 0x155, 0x156, 0x3, 0x2, 0x2, 0x2, 0x156, 
       0x157, 0x3, 0x2, 0x2, 0x2, 0x157, 0x158, 0x7, 0x5a, 0x2, 0x2, 0x158, 
       0x1b, 0x3, 0x2, 0x2, 0x2, 0x159, 0x15d, 0x5, 0x1e, 0x10, 0x2, 0x15a, 
       0x15d, 0x5, 0x26, 0x14, 0x2, 0x15b, 0x15d, 0x5, 0x28, 0x15, 0x2, 
       0x15c, 0x159, 0x3, 0x2, 0x2, 0x2, 0x15c, 0x15a, 0x3, 0x2, 0x2, 0x2, 
       0x15c, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x1d, 0x3, 0x2, 0x2, 0x2, 
       0x15e, 0x161, 0x7, 0x54, 0x2, 0x2, 0x15f, 0x161, 0x5, 0x20, 0x11, 
       0x2, 0x160, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x160, 0x15f, 0x3, 0x2, 0x2, 
       0x2, 0x161, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x162, 0x166, 0x5, 0x22, 0x12, 
       0x2, 0x163, 0x166, 0x5, 0x24, 0x13, 0x2, 0x164, 0x166, 0x9, 0x3, 
       0x2, 0x2, 0x165, 0x162, 0x3, 0x2, 0x2, 0x2, 0x165, 0x163, 0x3, 0x2, 
       0x2, 0x2, 0x165, 0x164, 0x3, 0x2, 0x2, 0x2, 0x166, 0x21, 0x3, 0x2, 
       0x2, 0x2, 0x167, 0x168, 0x9, 0x4, 0x2, 0x2, 0x168, 0x23, 0x3, 0x2, 
       0x2, 0x2, 0x169, 0x16a, 0x9, 0x5, 0x2, 0x2, 0x16a, 0x25, 0x3, 0x2, 
       0x2, 0x2, 0x16b, 0x16c, 0x7, 0x4a, 0x2, 0x2, 0x16c, 0x27, 0x3, 0x2, 
       0x2, 0x2, 0x16d, 0x16e, 0x7, 0x4b, 0x2, 0x2, 0x16e, 0x29, 0x3, 0x2, 
       0x2, 0x2, 0x16f, 0x170, 0x7, 0x5f, 0x2, 0x2, 0x170, 0x171, 0x5, 0x80, 
       0x41, 0x2, 0x171, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x172, 0x173, 0x7, 0x5b, 
       0x2, 0x2, 0x173, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x174, 0x175, 0x5, 0x7e, 
       0x40, 0x2, 0x175, 0x176, 0x7, 0x5b, 0x2, 0x2, 0x176, 0x2f, 0x3, 0x2, 
       0x2, 0x2, 0x177, 0x178, 0x7, 0x1c, 0x2, 0x2, 0x178, 0x179, 0x7, 0x55, 
       0x2, 0x2, 0x179, 0x17a, 0x5, 0x7e, 0x40, 0x2, 0x17a, 0x17b, 0x7, 
       0x56, 0x2, 0x2, 0x17b, 0x17e, 0x5, 0x6, 0x4, 0x2, 0x17c, 0x17d, 0x7, 
       0xc, 0x2, 0x2, 0x17d, 0x17f, 0x5, 0x6, 0x4, 0x2, 0x17e, 0x17c, 0x3, 
       0x2, 0x2, 0x2, 0x17e, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x31, 0x3, 
       0x2, 0x2, 0x2, 0x180, 0x181, 0x7, 0x8, 0x2, 0x2, 0x181, 0x182, 0x5, 
       0x6, 0x4, 0x2, 0x182, 0x183, 0x7, 0x16, 0x2, 0x2, 0x183, 0x184, 0x7, 
       0x55, 0x2, 0x2, 0x184, 0x185, 0x5, 0x7e, 0x40, 0x2, 0x185, 0x186, 
       0x7, 0x56, 0x2, 0x2, 0x186, 0x187, 0x7, 0x5b, 0x2, 0x2, 0x187, 0x1ba, 
       0x3, 0x2, 0x2, 0x2, 0x188, 0x189, 0x7, 0x16, 0x2, 0x2, 0x189, 0x18a, 
       0x7, 0x55, 0x2, 0x2, 0x18a, 0x18b, 0x5, 0x7e, 0x40, 0x2, 0x18b, 0x18c, 
       0x7, 0x56, 0x2, 0x2, 0x18c, 0x18d, 0x5, 0x6, 0x4, 0x2, 0x18d, 0x1ba, 
       0x3, 0x2, 0x2, 0x2, 0x18e, 0x18f, 0x7, 0x14, 0x2, 0x2, 0x18f, 0x192, 
       0x7, 0x55, 0x2, 0x2, 0x190, 0x193, 0x5, 0xce, 0x68, 0x2, 0x191, 0x193, 
       0x5, 0xe, 0x8, 0x2, 0x192, 0x190, 0x3, 0x2, 0x2, 0x2, 0x192, 0x191, 
       0x3, 0x2, 0x2, 0x2, 0x192, 0x193, 0x3, 0x2, 0x2, 0x2, 0x193, 0x194, 
       0x3, 0x2, 0x2, 0x2, 0x194, 0x196, 0x7, 0x5b, 0x2, 0x2, 0x195, 0x197, 
       0x5, 0x7e, 0x40, 0x2, 0x196, 0x195, 0x3, 0x2, 0x2, 0x2, 0x196, 0x197, 
       0x3, 0x2, 0x2, 0x2, 0x197, 0x198, 0x3, 0x2, 0x2, 0x2, 0x198, 0x19a, 
       0x7, 0x5b, 0x2, 0x2, 0x199, 0x19b, 0x5, 0x7e, 0x40, 0x2, 0x19a, 0x199, 
       0x3, 0x2, 0x2, 0x2, 0x19a, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19c, 
       0x3, 0x2, 0x2, 0x2, 0x19c, 0x19d, 0x7, 0x56, 0x2, 0x2, 0x19d, 0x1ba, 
       0x5, 0x6, 0x4, 0x2, 0x19e, 0x19f, 0x7, 0x14, 0x2, 0x2, 0x19f, 0x1a2, 
       0x7, 0x55, 0x2, 0x2, 0x1a0, 0x1a3, 0x5, 0xb0, 0x59, 0x2, 0x1a1, 0x1a3, 
       0x5, 0x12, 0xa, 0x2, 0x1a2, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a1, 
       0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 
       0x7, 0x1f, 0x2, 0x2, 0x1a5, 0x1a6, 0x5, 0x7e, 0x40, 0x2, 0x1a6, 0x1a7, 
       0x7, 0x56, 0x2, 0x2, 0x1a7, 0x1a8, 0x5, 0x6, 0x4, 0x2, 0x1a8, 0x1ba, 
       0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1aa, 0x7, 0x14, 0x2, 0x2, 0x1aa, 0x1ab, 
       0x7, 0x55, 0x2, 0x2, 0x1ab, 0x1ac, 0x5, 0xb0, 0x59, 0x2, 0x1ac, 0x1ad, 
       0x7, 0x8a, 0x2, 0x2, 0x1ad, 0x1ae, 0x5, 0x80, 0x41, 0x2, 0x1ae, 0x1af, 
       0x7, 0x56, 0x2, 0x2, 0x1af, 0x1b0, 0x5, 0x6, 0x4, 0x2, 0x1b0, 0x1ba, 
       0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1b2, 0x7, 0x14, 0x2, 0x2, 0x1b2, 0x1b3, 
       0x7, 0x55, 0x2, 0x2, 0x1b3, 0x1b4, 0x5, 0xb0, 0x59, 0x2, 0x1b4, 0x1b5, 
       0x7, 0x8a, 0x2, 0x2, 0x1b5, 0x1b6, 0x5, 0x80, 0x41, 0x2, 0x1b6, 0x1b7, 
       0x7, 0x56, 0x2, 0x2, 0x1b7, 0x1b8, 0x5, 0x6, 0x4, 0x2, 0x1b8, 0x1ba, 
       0x3, 0x2, 0x2, 0x2, 0x1b9, 0x180, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x188, 
       0x3, 0x2, 0x2, 0x2, 0x1b9, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x19e, 
       0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1b1, 
       0x3, 0x2, 0x2, 0x2, 0x1ba, 0x33, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bd, 
       0x7, 0x13, 0x2, 0x2, 0x1bc, 0x1be, 0x5, 0xb0, 0x59, 0x2, 0x1bd, 0x1bc, 
       0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1be, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x1bf, 
       0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1c0, 0x7, 0x5b, 0x2, 0x2, 0x1c0, 0x35, 
       0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c3, 0x7, 0x7, 0x2, 0x2, 0x1c2, 0x1c4, 
       0x5, 0xb0, 0x59, 0x2, 0x1c3, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c4, 
       0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c6, 
       0x7, 0x5b, 0x2, 0x2, 0x1c6, 0x37, 0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1c9, 
       0x7, 0x11, 0x2, 0x2, 0x1c8, 0x1ca, 0x5, 0x7e, 0x40, 0x2, 0x1c9, 0x1c8, 
       0x3, 0x2, 0x2, 0x2, 0x1c9, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x1ca, 0x1cb, 
       0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cc, 0x7, 0x5b, 0x2, 0x2, 0x1cc, 0x39, 
       0x3, 0x2, 0x2, 0x2, 0x1cd, 0x1cf, 0x7, 0x2a, 0x2, 0x2, 0x1ce, 0x1d0, 
       0x5, 0x7e, 0x40, 0x2, 0x1cf, 0x1ce, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x1d0, 
       0x3, 0x2, 0x2, 0x2, 0x1d0, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1d1, 0x1d2, 
       0x7, 0x5b, 0x2, 0x2, 0x1d2, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1d4, 
       0x7, 0x1a, 0x2, 0x2, 0x1d4, 0x1d5, 0x7, 0x55, 0x2, 0x2, 0x1d5, 0x1d6, 
       0x5, 0x7e, 0x40, 0x2, 0x1d6, 0x1d7, 0x7, 0x56, 0x2, 0x2, 0x1d7, 0x1d8, 
       0x5, 0x6, 0x4, 0x2, 0x1d8, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x1d9, 0x1da, 
       0x5, 0xb0, 0x59, 0x2, 0x1da, 0x1db, 0x7, 0x5c, 0x2, 0x2, 0x1db, 0x1dc, 
       0x5, 0x6, 0x4, 0x2, 0x1dc, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1de, 
       0x7, 0x15, 0x2, 0x2, 0x1de, 0x1df, 0x7, 0x55, 0x2, 0x2, 0x1df, 0x1e0, 
       0x5, 0x7e, 0x40, 0x2, 0x1e0, 0x1e1, 0x7, 0x56, 0x2, 0x2, 0x1e1, 0x1e2, 
       0x5, 0x42, 0x22, 0x2, 0x1e2, 0x41, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e5, 
       0x7, 0x57, 0x2, 0x2, 0x1e4, 0x1e6, 0x5, 0x44, 0x23, 0x2, 0x1e5, 0x1e4, 
       0x3, 0x2, 0x2, 0x2, 0x1e5, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1eb, 
       0x3, 0x2, 0x2, 0x2, 0x1e7, 0x1e9, 0x5, 0x48, 0x25, 0x2, 0x1e8, 0x1ea, 
       0x5, 0x44, 0x23, 0x2, 0x1e9, 0x1e8, 0x3, 0x2, 0x2, 0x2, 0x1e9, 0x1ea, 
       0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1ec, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1e7, 
       0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ec, 0x3, 0x2, 0x2, 0x2, 0x1ec, 0x1ed, 
       0x3, 0x2, 0x2, 0x2, 0x1ed, 0x1ee, 0x7, 0x58, 0x2, 0x2, 0x1ee, 0x43, 
       0x3, 0x2, 0x2, 0x2, 0x1ef, 0x1f1, 0x5, 0x46, 0x24, 0x2, 0x1f0, 0x1ef, 
       0x3, 0x2, 0x2, 0x2, 0x1f1, 0x1f2, 0x3, 0x2, 0x2, 0x2, 0x1f2, 0x1f0, 
       0x3, 0x2, 0x2, 0x2, 0x1f2, 0x1f3, 0x3, 0x2, 0x2, 0x2, 0x1f3, 0x45, 
       0x3, 0x2, 0x2, 0x2, 0x1f4, 0x1f5, 0x7, 0xb, 0x2, 0x2, 0x1f5, 0x1f6, 
       0x5, 0x7e, 0x40, 0x2, 0x1f6, 0x1f8, 0x7, 0x5c, 0x2, 0x2, 0x1f7, 0x1f9, 
       0x5, 0xa, 0x6, 0x2, 0x1f8, 0x1f7, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1f9, 
       0x3, 0x2, 0x2, 0x2, 0x1f9, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fb, 
       0x7, 0x1b, 0x2, 0x2, 0x1fb, 0x1fd, 0x7, 0x5c, 0x2, 0x2, 0x1fc, 0x1fe, 
       0x5, 0xa, 0x6, 0x2, 0x1fd, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1fe, 
       0x3, 0x2, 0x2, 0x2, 0x1fe, 0x49, 0x3, 0x2, 0x2, 0x2, 0x1ff, 0x200, 
       0x7, 0x1d, 0x2, 0x2, 0x200, 0x201, 0x5, 0x7e, 0x40, 0x2, 0x201, 0x202, 
       0x7, 0x5b, 0x2, 0x2, 0x202, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x203, 0x204, 
       0x7, 0x20, 0x2, 0x2, 0x204, 0x206, 0x5, 0x8, 0x5, 0x2, 0x205, 0x207, 
       0x5, 0x4e, 0x28, 0x2, 0x206, 0x205, 0x3, 0x2, 0x2, 0x2, 0x206, 0x207, 
       0x3, 0x2, 0x2, 0x2, 0x207, 0x209, 0x3, 0x2, 0x2, 0x2, 0x208, 0x20a, 
       0x5, 0x50, 0x29, 0x2, 0x209, 0x208, 0x3, 0x2, 0x2, 0x2, 0x209, 0x20a, 
       0x3, 0x2, 0x2, 0x2, 0x20a, 0x211, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x20c, 
       0x7, 0x20, 0x2, 0x2, 0x20c, 0x20d, 0x5, 0x8, 0x5, 0x2, 0x20d, 0x20e, 
       0x5, 0x4e, 0x28, 0x2, 0x20e, 0x20f, 0x5, 0x50, 0x29, 0x2, 0x20f, 
       0x211, 0x3, 0x2, 0x2, 0x2, 0x210, 0x203, 0x3, 0x2, 0x2, 0x2, 0x210, 
       0x20b, 0x3, 0x2, 0x2, 0x2, 0x211, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x212, 
       0x213, 0x7, 0xf, 0x2, 0x2, 0x213, 0x216, 0x7, 0x55, 0x2, 0x2, 0x214, 
       0x217, 0x5, 0xb0, 0x59, 0x2, 0x215, 0x217, 0x5, 0x12, 0xa, 0x2, 0x216, 
       0x214, 0x3, 0x2, 0x2, 0x2, 0x216, 0x215, 0x3, 0x2, 0x2, 0x2, 0x217, 
       0x218, 0x3, 0x2, 0x2, 0x2, 0x218, 0x219, 0x7, 0x56, 0x2, 0x2, 0x219, 
       0x21a, 0x5, 0x8, 0x5, 0x2, 0x21a, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x21b, 
       0x21c, 0x7, 0x10, 0x2, 0x2, 0x21c, 0x21d, 0x5, 0x8, 0x5, 0x2, 0x21d, 
       0x51, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x21f, 0x7, 0x17, 0x2, 0x2, 0x21f, 
       0x220, 0x7, 0x5b, 0x2, 0x2, 0x220, 0x53, 0x3, 0x2, 0x2, 0x2, 0x221, 
       0x222, 0x7, 0x18, 0x2, 0x2, 0x222, 0x223, 0x5, 0xb0, 0x59, 0x2, 0x223, 
       0x225, 0x7, 0x55, 0x2, 0x2, 0x224, 0x226, 0x5, 0x56, 0x2c, 0x2, 0x225, 
       0x224, 0x3, 0x2, 0x2, 0x2, 0x225, 0x226, 0x3, 0x2, 0x2, 0x2, 0x226, 
       0x227, 0x3, 0x2, 0x2, 0x2, 0x227, 0x228, 0x7, 0x56, 0x2, 0x2, 0x228, 
       0x229, 0x7, 0x57, 0x2, 0x2, 0x229, 0x22a, 0x5, 0x5a, 0x2e, 0x2, 0x22a, 
       0x22b, 0x7, 0x58, 0x2, 0x2, 0x22b, 0x55, 0x3, 0x2, 0x2, 0x2, 0x22c, 
       0x231, 0x5, 0x58, 0x2d, 0x2, 0x22d, 0x22e, 0x7, 0x5d, 0x2, 0x2, 0x22e, 
       0x230, 0x5, 0x58, 0x2d, 0x2, 0x22f, 0x22d, 0x3, 0x2, 0x2, 0x2, 0x230, 
       0x233, 0x3, 0x2, 0x2, 0x2, 0x231, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x231, 
       0x232, 0x3, 0x2, 0x2, 0x2, 0x232, 0x57, 0x3, 0x2, 0x2, 0x2, 0x233, 
       0x231, 0x3, 0x2, 0x2, 0x2, 0x234, 0x23c, 0x5, 0xb0, 0x59, 0x2, 0x235, 
       0x23c, 0x5, 0x12, 0xa, 0x2, 0x236, 0x239, 0x7, 0x7f, 0x2, 0x2, 0x237, 
       0x23a, 0x5, 0xb0, 0x59, 0x2, 0x238, 0x23a, 0x5, 0x12, 0xa, 0x2, 0x239, 
       0x237, 0x3, 0x2, 0x2, 0x2, 0x239, 0x238, 0x3, 0x2, 0x2, 0x2, 0x23a, 
       0x23c, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x234, 0x3, 0x2, 0x2, 0x2, 0x23b, 
       0x235, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x236, 0x3, 0x2, 0x2, 0x2, 0x23c, 
       0x59, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x23f, 0x5, 0xea, 0x76, 0x2, 0x23e, 
       0x23d, 0x3, 0x2, 0x2, 0x2, 0x23e, 0x23f, 0x3, 0x2, 0x2, 0x2, 0x23f, 
       0x5b, 0x3, 0x2, 0x2, 0x2, 0x240, 0x241, 0x7, 0x21, 0x2, 0x2, 0x241, 
       0x244, 0x5, 0xb0, 0x59, 0x2, 0x242, 0x243, 0x7, 0x23, 0x2, 0x2, 0x243, 
       0x245, 0x5, 0xb0, 0x59, 0x2, 0x244, 0x242, 0x3, 0x2, 0x2, 0x2, 0x244, 
       0x245, 0x3, 0x2, 0x2, 0x2, 0x245, 0x246, 0x3, 0x2, 0x2, 0x2, 0x246, 
       0x248, 0x7, 0x57, 0x2, 0x2, 0x247, 0x249, 0x5, 0x5e, 0x30, 0x2, 0x248, 
       0x247, 0x3, 0x2, 0x2, 0x2, 0x248, 0x249, 0x3, 0x2, 0x2, 0x2, 0x249, 
       0x24a, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x24b, 0x7, 0x58, 0x2, 0x2, 0x24b, 
       0x5d, 0x3, 0x2, 0x2, 0x2, 0x24c, 0x24e, 0x5, 0x60, 0x31, 0x2, 0x24d, 
       0x24c, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x24f, 0x3, 0x2, 0x2, 0x2, 0x24f, 
       0x24d, 0x3, 0x2, 0x2, 0x2, 0x24f, 0x250, 0x3, 0x2, 0x2, 0x2, 0x250, 
       0x5f, 0x3, 0x2, 0x2, 0x2, 0x251, 0x252, 0x5, 0x62, 0x32, 0x2, 0x252, 
       0x61, 0x3, 0x2, 0x2, 0x2, 0x253, 0x255, 0x9, 0x6, 0x2, 0x2, 0x254, 
       0x253, 0x3, 0x2, 0x2, 0x2, 0x254, 0x255, 0x3, 0x2, 0x2, 0x2, 0x255, 
       0x256, 0x3, 0x2, 0x2, 0x2, 0x256, 0x257, 0x5, 0x1c, 0xf, 0x2, 0x257, 
       0x259, 0x7, 0x55, 0x2, 0x2, 0x258, 0x25a, 0x5, 0x56, 0x2c, 0x2, 0x259, 
       0x258, 0x3, 0x2, 0x2, 0x2, 0x259, 0x25a, 0x3, 0x2, 0x2, 0x2, 0x25a, 
       0x25b, 0x3, 0x2, 0x2, 0x2, 0x25b, 0x25c, 0x7, 0x56, 0x2, 0x2, 0x25c, 
       0x25d, 0x7, 0x57, 0x2, 0x2, 0x25d, 0x25e, 0x5, 0x5a, 0x2e, 0x2, 0x25e, 
       0x25f, 0x7, 0x58, 0x2, 0x2, 0x25f, 0x63, 0x3, 0x2, 0x2, 0x2, 0x260, 
       0x261, 0x7, 0x27, 0x2, 0x2, 0x261, 0x262, 0x5, 0x66, 0x34, 0x2, 0x262, 
       0x263, 0x5, 0x70, 0x39, 0x2, 0x263, 0x264, 0x7, 0x5b, 0x2, 0x2, 0x264, 
       0x26a, 0x3, 0x2, 0x2, 0x2, 0x265, 0x266, 0x7, 0x27, 0x2, 0x2, 0x266, 
       0x267, 0x5, 0x72, 0x3a, 0x2, 0x267, 0x268, 0x7, 0x5b, 0x2, 0x2, 0x268, 
       0x26a, 0x3, 0x2, 0x2, 0x2, 0x269, 0x260, 0x3, 0x2, 0x2, 0x2, 0x269, 
       0x265, 0x3, 0x2, 0x2, 0x2, 0x26a, 0x65, 0x3, 0x2, 0x2, 0x2, 0x26b, 
       0x277, 0x5, 0x68, 0x35, 0x2, 0x26c, 0x277, 0x5, 0x6a, 0x36, 0x2, 
       0x26d, 0x277, 0x5, 0x6c, 0x37, 0x2, 0x26e, 0x26f, 0x5, 0x68, 0x35, 
       0x2, 0x26f, 0x270, 0x7, 0x5d, 0x2, 0x2, 0x270, 0x271, 0x5, 0x6a, 
       0x36, 0x2, 0x271, 0x277, 0x3, 0x2, 0x2, 0x2, 0x272, 0x273, 0x5, 0x68, 
       0x35, 0x2, 0x273, 0x274, 0x7, 0x5d, 0x2, 0x2, 0x274, 0x275, 0x5, 
       0x6c, 0x37, 0x2, 0x275, 0x277, 0x3, 0x2, 0x2, 0x2, 0x276, 0x26b, 
       0x3, 0x2, 0x2, 0x2, 0x276, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x276, 0x26d, 
       0x3, 0x2, 0x2, 0x2, 0x276, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x276, 0x272, 
       0x3, 0x2, 0x2, 0x2, 0x277, 0x67, 0x3, 0x2, 0x2, 0x2, 0x278, 0x279, 
       0x5, 0xb0, 0x59, 0x2, 0x279, 0x69, 0x3, 0x2, 0x2, 0x2, 0x27a, 0x27b, 
       0x7, 0x81, 0x2, 0x2, 0x27b, 0x27c, 0x7, 0x82, 0x2, 0x2, 0x27c, 0x27d, 
       0x5, 0xb0, 0x59, 0x2, 0x27d, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x287, 
       0x7, 0x57, 0x2, 0x2, 0x27f, 0x284, 0x5, 0x6e, 0x38, 0x2, 0x280, 0x281, 
       0x7, 0x5d, 0x2, 0x2, 0x281, 0x283, 0x5, 0x6e, 0x38, 0x2, 0x282, 0x280, 
       0x3, 0x2, 0x2, 0x2, 0x283, 0x286, 0x3, 0x2, 0x2, 0x2, 0x284, 0x282, 
       0x3, 0x2, 0x2, 0x2, 0x284, 0x285, 0x3, 0x2, 0x2, 0x2, 0x285, 0x288, 
       0x3, 0x2, 0x2, 0x2, 0x286, 0x284, 0x3, 0x2, 0x2, 0x2, 0x287, 0x27f, 
       0x3, 0x2, 0x2, 0x2, 0x287, 0x288, 0x3, 0x2, 0x2, 0x2, 0x288, 0x289, 
       0x3, 0x2, 0x2, 0x2, 0x289, 0x28a, 0x7, 0x58, 0x2, 0x2, 0x28a, 0x6d, 
       0x3, 0x2, 0x2, 0x2, 0x28b, 0x291, 0x5, 0xb0, 0x59, 0x2, 0x28c, 0x28d, 
       0x5, 0x1e, 0x10, 0x2, 0x28d, 0x28e, 0x7, 0x82, 0x2, 0x2, 0x28e, 0x28f, 
       0x5, 0xb0, 0x59, 0x2, 0x28f, 0x291, 0x3, 0x2, 0x2, 0x2, 0x290, 0x28b, 
       0x3, 0x2, 0x2, 0x2, 0x290, 0x28c, 0x3, 0x2, 0x2, 0x2, 0x291, 0x6f, 
       0x3, 0x2, 0x2, 0x2, 0x292, 0x293, 0x7, 0x8b, 0x2, 0x2, 0x293, 0x294, 
       0x5, 0x72, 0x3a, 0x2, 0x294, 0x71, 0x3, 0x2, 0x2, 0x2, 0x295, 0x296, 
       0x5, 0x26, 0x14, 0x2, 0x296, 0x73, 0x3, 0x2, 0x2, 0x2, 0x297, 0x298, 
       0x7, 0x26, 0x2, 0x2, 0x298, 0x29a, 0x5, 0x76, 0x3c, 0x2, 0x299, 0x29b, 
       0x5, 0x70, 0x39, 0x2, 0x29a, 0x299, 0x3, 0x2, 0x2, 0x2, 0x29a, 0x29b, 
       0x3, 0x2, 0x2, 0x2, 0x29b, 0x29c, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x29d, 
       0x7, 0x5b, 0x2, 0x2, 0x29d, 0x2aa, 0x3, 0x2, 0x2, 0x2, 0x29e, 0x29f, 
       0x7, 0x26, 0x2, 0x2, 0x29f, 0x2a2, 0x5, 0x7c, 0x3f, 0x2, 0x2a0, 0x2a1, 
       0x7, 0x5d, 0x2, 0x2, 0x2a1, 0x2a3, 0x5, 0x76, 0x3c, 0x2, 0x2a2, 0x2a0, 
       0x3, 0x2, 0x2, 0x2, 0x2a2, 0x2a3, 0x3, 0x2, 0x2, 0x2, 0x2a3, 0x2a5, 
       0x3, 0x2, 0x2, 0x2, 0x2a4, 0x2a6, 0x5, 0x70, 0x39, 0x2, 0x2a5, 0x2a4, 
       0x3, 0x2, 0x2, 0x2, 0x2a5, 0x2a6, 0x3, 0x2, 0x2, 0x2, 0x2a6, 0x2a7, 
       0x3, 0x2, 0x2, 0x2, 0x2a7, 0x2a8, 0x7, 0x5b, 0x2, 0x2, 0x2a8, 0x2aa, 
       0x3, 0x2, 0x2, 0x2, 0x2a9, 0x297, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x29e, 
       0x3, 0x2, 0x2, 0x2, 0x2aa, 0x75, 0x3, 0x2, 0x2, 0x2, 0x2ab, 0x2af, 
       0x7, 0x81, 0x2, 0x2, 0x2ac, 0x2af, 0x5, 0x6a, 0x36, 0x2, 0x2ad, 0x2af, 
       0x5, 0x78, 0x3d, 0x2, 0x2ae, 0x2ab, 0x3, 0x2, 0x2, 0x2, 0x2ae, 0x2ac, 
       0x3, 0x2, 0x2, 0x2, 0x2ae, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x2af, 0x77, 
       0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2b9, 0x7, 0x57, 0x2, 0x2, 0x2b1, 0x2b6, 
       0x5, 0x7a, 0x3e, 0x2, 0x2b2, 0x2b3, 0x7, 0x5d, 0x2, 0x2, 0x2b3, 0x2b5, 
       0x5, 0x7a, 0x3e, 0x2, 0x2b4, 0x2b2, 0x3, 0x2, 0x2, 0x2, 0x2b5, 0x2b8, 
       0x3, 0x2, 0x2, 0x2, 0x2b6, 0x2b4, 0x3, 0x2, 0x2, 0x2, 0x2b6, 0x2b7, 
       0x3, 0x2, 0x2, 0x2, 0x2b7, 0x2ba, 0x3, 0x2, 0x2, 0x2, 0x2b8, 0x2b6, 
       0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2b1, 0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2ba, 
       0x3, 0x2, 0x2, 0x2, 0x2ba, 0x2bb, 0x3, 0x2, 0x2, 0x2, 0x2bb, 0x2bc, 
       0x7, 0x58, 0x2, 0x2, 0x2bc, 0x79, 0x3, 0x2, 0x2, 0x2, 0x2bd, 0x2c3, 
       0x5, 0xb0, 0x59, 0x2, 0x2be, 0x2bf, 0x5, 0x1e, 0x10, 0x2, 0x2bf, 
       0x2c0, 0x7, 0x82, 0x2, 0x2, 0x2c0, 0x2c1, 0x5, 0xb0, 0x59, 0x2, 0x2c1, 
       0x2c3, 0x3, 0x2, 0x2, 0x2, 0x2c2, 0x2bd, 0x3, 0x2, 0x2, 0x2, 0x2c2, 
       0x2be, 0x3, 0x2, 0x2, 0x2, 0x2c3, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x2c4, 
       0x2c8, 0x5, 0xb0, 0x59, 0x2, 0x2c5, 0x2c8, 0x5, 0x54, 0x2b, 0x2, 
       0x2c6, 0x2c8, 0x5, 0x5c, 0x2f, 0x2, 0x2c7, 0x2c4, 0x3, 0x2, 0x2, 
       0x2, 0x2c7, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2c7, 0x2c6, 0x3, 0x2, 0x2, 
       0x2, 0x2c8, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x2c9, 0x2ce, 0x5, 0x80, 0x41, 
       0x2, 0x2ca, 0x2cb, 0x7, 0x5d, 0x2, 0x2, 0x2cb, 0x2cd, 0x5, 0x80, 
       0x41, 0x2, 0x2cc, 0x2ca, 0x3, 0x2, 0x2, 0x2, 0x2cd, 0x2d0, 0x3, 0x2, 
       0x2, 0x2, 0x2ce, 0x2cc, 0x3, 0x2, 0x2, 0x2, 0x2ce, 0x2cf, 0x3, 0x2, 
       0x2, 0x2, 0x2cf, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2ce, 0x3, 0x2, 
       0x2, 0x2, 0x2d1, 0x2d8, 0x5, 0x84, 0x43, 0x2, 0x2d2, 0x2d8, 0x5, 
       0xc6, 0x64, 0x2, 0x2d3, 0x2d8, 0x5, 0xc8, 0x65, 0x2, 0x2d4, 0x2d5, 
       0x5, 0x82, 0x42, 0x2, 0x2d5, 0x2d6, 0x5, 0x80, 0x41, 0x2, 0x2d6, 
       0x2d8, 0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2d1, 0x3, 0x2, 0x2, 0x2, 0x2d7, 
       0x2d2, 0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2d3, 0x3, 0x2, 0x2, 0x2, 0x2d7, 
       0x2d4, 0x3, 0x2, 0x2, 0x2, 0x2d8, 0x81, 0x3, 0x2, 0x2, 0x2, 0x2d9, 
       0x2da, 0x9, 0x7, 0x2, 0x2, 0x2da, 0x83, 0x3, 0x2, 0x2, 0x2, 0x2db, 
       0x2e1, 0x5, 0x86, 0x44, 0x2, 0x2dc, 0x2dd, 0x7, 0x64, 0x2, 0x2, 0x2dd, 
       0x2de, 0x5, 0x80, 0x41, 0x2, 0x2de, 0x2df, 0x7, 0x5c, 0x2, 0x2, 0x2df, 
       0x2e0, 0x5, 0x80, 0x41, 0x2, 0x2e0, 0x2e2, 0x3, 0x2, 0x2, 0x2, 0x2e1, 
       0x2dc, 0x3, 0x2, 0x2, 0x2, 0x2e1, 0x2e2, 0x3, 0x2, 0x2, 0x2, 0x2e2, 
       0x85, 0x3, 0x2, 0x2, 0x2, 0x2e3, 0x2e8, 0x5, 0x88, 0x45, 0x2, 0x2e4, 
       0x2e5, 0x7, 0x84, 0x2, 0x2, 0x2e5, 0x2e7, 0x5, 0x88, 0x45, 0x2, 0x2e6, 
       0x2e4, 0x3, 0x2, 0x2, 0x2, 0x2e7, 0x2ea, 0x3, 0x2, 0x2, 0x2, 0x2e8, 
       0x2e6, 0x3, 0x2, 0x2, 0x2, 0x2e8, 0x2e9, 0x3, 0x2, 0x2, 0x2, 0x2e9, 
       0x87, 0x3, 0x2, 0x2, 0x2, 0x2ea, 0x2e8, 0x3, 0x2, 0x2, 0x2, 0x2eb, 
       0x2f0, 0x5, 0x8a, 0x46, 0x2, 0x2ec, 0x2ed, 0x7, 0x85, 0x2, 0x2, 0x2ed, 
       0x2ef, 0x5, 0x8a, 0x46, 0x2, 0x2ee, 0x2ec, 0x3, 0x2, 0x2, 0x2, 0x2ef, 
       0x2f2, 0x3, 0x2, 0x2, 0x2, 0x2f0, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x2f0, 
       0x2f1, 0x3, 0x2, 0x2, 0x2, 0x2f1, 0x89, 0x3, 0x2, 0x2, 0x2, 0x2f2, 
       0x2f0, 0x3, 0x2, 0x2, 0x2, 0x2f3, 0x2f8, 0x5, 0x8c, 0x47, 0x2, 0x2f4, 
       0x2f5, 0x7, 0x7a, 0x2, 0x2, 0x2f5, 0x2f7, 0x5, 0x8c, 0x47, 0x2, 0x2f6, 
       0x2f4, 0x3, 0x2, 0x2, 0x2, 0x2f7, 0x2fa, 0x3, 0x2, 0x2, 0x2, 0x2f8, 
       0x2f6, 0x3, 0x2, 0x2, 0x2, 0x2f8, 0x2f9, 0x3, 0x2, 0x2, 0x2, 0x2f9, 
       0x8b, 0x3, 0x2, 0x2, 0x2, 0x2fa, 0x2f8, 0x3, 0x2, 0x2, 0x2, 0x2fb, 
       0x300, 0x5, 0x8e, 0x48, 0x2, 0x2fc, 0x2fd, 0x7, 0x7b, 0x2, 0x2, 0x2fd, 
       0x2ff, 0x5, 0x8e, 0x48, 0x2, 0x2fe, 0x2fc, 0x3, 0x2, 0x2, 0x2, 0x2ff, 
       0x302, 0x3, 0x2, 0x2, 0x2, 0x300, 0x2fe, 0x3, 0x2, 0x2, 0x2, 0x300, 
       0x301, 0x3, 0x2, 0x2, 0x2, 0x301, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x302, 
       0x300, 0x3, 0x2, 0x2, 0x2, 0x303, 0x308, 0x5, 0x90, 0x49, 0x2, 0x304, 
       0x305, 0x7, 0x79, 0x2, 0x2, 0x305, 0x307, 0x5, 0x90, 0x49, 0x2, 0x306, 
       0x304, 0x3, 0x2, 0x2, 0x2, 0x307, 0x30a, 0x3, 0x2, 0x2, 0x2, 0x308, 
       0x306, 0x3, 0x2, 0x2, 0x2, 0x308, 0x309, 0x3, 0x2, 0x2, 0x2, 0x309, 
       0x8f, 0x3, 0x2, 0x2, 0x2, 0x30a, 0x308, 0x3, 0x2, 0x2, 0x2, 0x30b, 
       0x310, 0x5, 0x92, 0x4a, 0x2, 0x30c, 0x30d, 0x9, 0x8, 0x2, 0x2, 0x30d, 
       0x30f, 0x5, 0x92, 0x4a, 0x2, 0x30e, 0x30c, 0x3, 0x2, 0x2, 0x2, 0x30f, 
       0x312, 0x3, 0x2, 0x2, 0x2, 0x310, 0x30e, 0x3, 0x2, 0x2, 0x2, 0x310, 
       0x311, 0x3, 0x2, 0x2, 0x2, 0x311, 0x91, 0x3, 0x2, 0x2, 0x2, 0x312, 
       0x310, 0x3, 0x2, 0x2, 0x2, 0x313, 0x318, 0x5, 0x94, 0x4b, 0x2, 0x314, 
       0x315, 0x9, 0x9, 0x2, 0x2, 0x315, 0x317, 0x5, 0x94, 0x4b, 0x2, 0x316, 
       0x314, 0x3, 0x2, 0x2, 0x2, 0x317, 0x31a, 0x3, 0x2, 0x2, 0x2, 0x318, 
       0x316, 0x3, 0x2, 0x2, 0x2, 0x318, 0x319, 0x3, 0x2, 0x2, 0x2, 0x319, 
       0x93, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x318, 0x3, 0x2, 0x2, 0x2, 0x31b, 
       0x320, 0x5, 0x96, 0x4c, 0x2, 0x31c, 0x31d, 0x9, 0xa, 0x2, 0x2, 0x31d, 
       0x31f, 0x5, 0x96, 0x4c, 0x2, 0x31e, 0x31c, 0x3, 0x2, 0x2, 0x2, 0x31f, 
       0x322, 0x3, 0x2, 0x2, 0x2, 0x320, 0x31e, 0x3, 0x2, 0x2, 0x2, 0x320, 
       0x321, 0x3, 0x2, 0x2, 0x2, 0x321, 0x95, 0x3, 0x2, 0x2, 0x2, 0x322, 
       0x320, 0x3, 0x2, 0x2, 0x2, 0x323, 0x328, 0x5, 0x98, 0x4d, 0x2, 0x324, 
       0x325, 0x9, 0xb, 0x2, 0x2, 0x325, 0x327, 0x5, 0x96, 0x4c, 0x2, 0x326, 
       0x324, 0x3, 0x2, 0x2, 0x2, 0x327, 0x32a, 0x3, 0x2, 0x2, 0x2, 0x328, 
       0x326, 0x3, 0x2, 0x2, 0x2, 0x328, 0x329, 0x3, 0x2, 0x2, 0x2, 0x329, 
       0x97, 0x3, 0x2, 0x2, 0x2, 0x32a, 0x328, 0x3, 0x2, 0x2, 0x2, 0x32b, 
       0x330, 0x5, 0x9a, 0x4e, 0x2, 0x32c, 0x32d, 0x9, 0xc, 0x2, 0x2, 0x32d, 
       0x32f, 0x5, 0x9a, 0x4e, 0x2, 0x32e, 0x32c, 0x3, 0x2, 0x2, 0x2, 0x32f, 
       0x332, 0x3, 0x2, 0x2, 0x2, 0x330, 0x32e, 0x3, 0x2, 0x2, 0x2, 0x330, 
       0x331, 0x3, 0x2, 0x2, 0x2, 0x331, 0x99, 0x3, 0x2, 0x2, 0x2, 0x332, 
       0x330, 0x3, 0x2, 0x2, 0x2, 0x333, 0x334, 0x5, 0x9c, 0x4f, 0x2, 0x334, 
       0x335, 0x5, 0x9a, 0x4e, 0x2, 0x335, 0x338, 0x3, 0x2, 0x2, 0x2, 0x336, 
       0x338, 0x5, 0x9e, 0x50, 0x2, 0x337, 0x333, 0x3, 0x2, 0x2, 0x2, 0x337, 
       0x336, 0x3, 0x2, 0x2, 0x2, 0x338, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x339, 
       0x33a, 0x9, 0xd, 0x2, 0x2, 0x33a, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x33b, 
       0x33d, 0x5, 0xa0, 0x51, 0x2, 0x33c, 0x33e, 0x9, 0xe, 0x2, 0x2, 0x33d, 
       0x33c, 0x3, 0x2, 0x2, 0x2, 0x33d, 0x33e, 0x3, 0x2, 0x2, 0x2, 0x33e, 
       0x9f, 0x3, 0x2, 0x2, 0x2, 0x33f, 0x342, 0x5, 0xa2, 0x52, 0x2, 0x340, 
       0x342, 0x5, 0xa8, 0x55, 0x2, 0x341, 0x33f, 0x3, 0x2, 0x2, 0x2, 0x341, 
       0x340, 0x3, 0x2, 0x2, 0x2, 0x342, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x343, 
       0x344, 0x8, 0x52, 0x1, 0x2, 0x344, 0x34e, 0x5, 0xaa, 0x56, 0x2, 0x345, 
       0x34e, 0x5, 0xac, 0x57, 0x2, 0x346, 0x34e, 0x5, 0xae, 0x58, 0x2, 
       0x347, 0x34e, 0x5, 0xb0, 0x59, 0x2, 0x348, 0x34e, 0x5, 0xb2, 0x5a, 
       0x2, 0x349, 0x34e, 0x5, 0xb4, 0x5b, 0x2, 0x34a, 0x34e, 0x5, 0xb8, 
       0x5d, 0x2, 0x34b, 0x34e, 0x5, 0xbc, 0x5f, 0x2, 0x34c, 0x34e, 0x5, 
       0xa8, 0x55, 0x2, 0x34d, 0x343, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x345, 
       0x3, 0x2, 0x2, 0x2, 0x34d, 0x346, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x347, 
       0x3, 0x2, 0x2, 0x2, 0x34d, 0x348, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x349, 
       0x3, 0x2, 0x2, 0x2, 0x34d, 0x34a, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x34b, 
       0x3, 0x2, 0x2, 0x2, 0x34d, 0x34c, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x361, 
       0x3, 0x2, 0x2, 0x2, 0x34f, 0x350, 0xc, 0xf, 0x2, 0x2, 0x350, 0x352, 
       0x7, 0x55, 0x2, 0x2, 0x351, 0x353, 0x5, 0xa4, 0x53, 0x2, 0x352, 0x351, 
       0x3, 0x2, 0x2, 0x2, 0x352, 0x353, 0x3, 0x2, 0x2, 0x2, 0x353, 0x354, 
       0x3, 0x2, 0x2, 0x2, 0x354, 0x360, 0x7, 0x56, 0x2, 0x2, 0x355, 0x356, 
       0xc, 0xe, 0x2, 0x2, 0x356, 0x357, 0x7, 0x59, 0x2, 0x2, 0x357, 0x358, 
       0x5, 0x7e, 0x40, 0x2, 0x358, 0x359, 0x7, 0x5a, 0x2, 0x2, 0x359, 0x360, 
       0x3, 0x2, 0x2, 0x2, 0x35a, 0x35b, 0xc, 0xd, 0x2, 0x2, 0x35b, 0x35c, 
       0x7, 0x5e, 0x2, 0x2, 0x35c, 0x360, 0x5, 0x1e, 0x10, 0x2, 0x35d, 0x35e, 
       0xc, 0xc, 0x2, 0x2, 0x35e, 0x360, 0x5, 0xbe, 0x60, 0x2, 0x35f, 0x34f, 
       0x3, 0x2, 0x2, 0x2, 0x35f, 0x355, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x35a, 
       0x3, 0x2, 0x2, 0x2, 0x35f, 0x35d, 0x3, 0x2, 0x2, 0x2, 0x360, 0x363, 
       0x3, 0x2, 0x2, 0x2, 0x361, 0x35f, 0x3, 0x2, 0x2, 0x2, 0x361, 0x362, 
       0x3, 0x2, 0x2, 0x2, 0x362, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x363, 0x361, 
       0x3, 0x2, 0x2, 0x2, 0x364, 0x365, 0x5, 0xa6, 0x54, 0x2, 0x365, 0xa5, 
       0x3, 0x2, 0x2, 0x2, 0x366, 0x36b, 0x5, 0x80, 0x41, 0x2, 0x367, 0x368, 
       0x7, 0x5d, 0x2, 0x2, 0x368, 0x36a, 0x5, 0x80, 0x41, 0x2, 0x369, 0x367, 
       0x3, 0x2, 0x2, 0x2, 0x36a, 0x36d, 0x3, 0x2, 0x2, 0x2, 0x36b, 0x369, 
       0x3, 0x2, 0x2, 0x2, 0x36b, 0x36c, 0x3, 0x2, 0x2, 0x2, 0x36c, 0xa7, 
       0x3, 0x2, 0x2, 0x2, 0x36d, 0x36b, 0x3, 0x2, 0x2, 0x2, 0x36e, 0x36f, 
       0x7, 0xd, 0x2, 0x2, 0x36f, 0x390, 0x5, 0xa8, 0x55, 0x2, 0x370, 0x371, 
       0x7, 0xd, 0x2, 0x2, 0x371, 0x372, 0x5, 0xa8, 0x55, 0x2, 0x372, 0x374, 
       0x7, 0x55, 0x2, 0x2, 0x373, 0x375, 0x5, 0xa4, 0x53, 0x2, 0x374, 0x373, 
       0x3, 0x2, 0x2, 0x2, 0x374, 0x375, 0x3, 0x2, 0x2, 0x2, 0x375, 0x376, 
       0x3, 0x2, 0x2, 0x2, 0x376, 0x377, 0x7, 0x56, 0x2, 0x2, 0x377, 0x390, 
       0x3, 0x2, 0x2, 0x2, 0x378, 0x379, 0x7, 0xd, 0x2, 0x2, 0x379, 0x37a, 
       0x5, 0xa8, 0x55, 0x2, 0x37a, 0x37b, 0x7, 0x59, 0x2, 0x2, 0x37b, 0x37c, 
       0x5, 0x7e, 0x40, 0x2, 0x37c, 0x37d, 0x7, 0x5a, 0x2, 0x2, 0x37d, 0x390, 
       0x3, 0x2, 0x2, 0x2, 0x37e, 0x37f, 0x7, 0xd, 0x2, 0x2, 0x37f, 0x380, 
       0x5, 0xa8, 0x55, 0x2, 0x380, 0x381, 0x7, 0x5e, 0x2, 0x2, 0x381, 0x382, 
       0x5, 0x1e, 0x10, 0x2, 0x382, 0x390, 0x3, 0x2, 0x2, 0x2, 0x383, 0x384, 
       0x7, 0xd, 0x2, 0x2, 0x384, 0x385, 0x5, 0xa8, 0x55, 0x2, 0x385, 0x386, 
       0x5, 0xbe, 0x60, 0x2, 0x386, 0x390, 0x3, 0x2, 0x2, 0x2, 0x387, 0x390, 
       0x5, 0xaa, 0x56, 0x2, 0x388, 0x390, 0x5, 0xac, 0x57, 0x2, 0x389, 
       0x390, 0x5, 0xae, 0x58, 0x2, 0x38a, 0x390, 0x5, 0xb0, 0x59, 0x2, 
       0x38b, 0x390, 0x5, 0xb2, 0x5a, 0x2, 0x38c, 0x390, 0x5, 0xb4, 0x5b, 
       0x2, 0x38d, 0x390, 0x5, 0xb8, 0x5d, 0x2, 0x38e, 0x390, 0x5, 0xbc, 
       0x5f, 0x2, 0x38f, 0x36e, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x370, 0x3, 0x2, 
       0x2, 0x2, 0x38f, 0x378, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x37e, 0x3, 0x2, 
       0x2, 0x2, 0x38f, 0x383, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x387, 0x3, 0x2, 
       0x2, 0x2, 0x38f, 0x388, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x389, 0x3, 0x2, 
       0x2, 0x2, 0x38f, 0x38a, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x38b, 0x3, 0x2, 
       0x2, 0x2, 0x38f, 0x38c, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x38d, 0x3, 0x2, 
       0x2, 0x2, 0x38f, 0x38e, 0x3, 0x2, 0x2, 0x2, 0x390, 0xa9, 0x3, 0x2, 
       0x2, 0x2, 0x391, 0x392, 0x7, 0x24, 0x2, 0x2, 0x392, 0x393, 0x7, 0x59, 
       0x2, 0x2, 0x393, 0x394, 0x5, 0x7e, 0x40, 0x2, 0x394, 0x395, 0x7, 
       0x5a, 0x2, 0x2, 0x395, 0x39a, 0x3, 0x2, 0x2, 0x2, 0x396, 0x397, 0x7, 
       0x24, 0x2, 0x2, 0x397, 0x398, 0x7, 0x5e, 0x2, 0x2, 0x398, 0x39a, 
       0x5, 0x1e, 0x10, 0x2, 0x399, 0x391, 0x3, 0x2, 0x2, 0x2, 0x399, 0x396, 
       0x3, 0x2, 0x2, 0x2, 0x39a, 0xab, 0x3, 0x2, 0x2, 0x2, 0x39b, 0x39d, 
       0x7, 0x18, 0x2, 0x2, 0x39c, 0x39e, 0x5, 0xb0, 0x59, 0x2, 0x39d, 0x39c, 
       0x3, 0x2, 0x2, 0x2, 0x39d, 0x39e, 0x3, 0x2, 0x2, 0x2, 0x39e, 0x39f, 
       0x3, 0x2, 0x2, 0x2, 0x39f, 0x3a1, 0x7, 0x55, 0x2, 0x2, 0x3a0, 0x3a2, 
       0x5, 0x56, 0x2c, 0x2, 0x3a1, 0x3a0, 0x3, 0x2, 0x2, 0x2, 0x3a1, 0x3a2, 
       0x3, 0x2, 0x2, 0x2, 0x3a2, 0x3a3, 0x3, 0x2, 0x2, 0x2, 0x3a3, 0x3a4, 
       0x7, 0x56, 0x2, 0x2, 0x3a4, 0x3a5, 0x7, 0x57, 0x2, 0x2, 0x3a5, 0x3a6, 
       0x5, 0x5a, 0x2e, 0x2, 0x3a6, 0x3a7, 0x7, 0x58, 0x2, 0x2, 0x3a7, 0xad, 
       0x3, 0x2, 0x2, 0x2, 0x3a8, 0x3aa, 0x7, 0x21, 0x2, 0x2, 0x3a9, 0x3ab, 
       0x5, 0xb0, 0x59, 0x2, 0x3aa, 0x3a9, 0x3, 0x2, 0x2, 0x2, 0x3aa, 0x3ab, 
       0x3, 0x2, 0x2, 0x2, 0x3ab, 0x3ae, 0x3, 0x2, 0x2, 0x2, 0x3ac, 0x3ad, 
       0x7, 0x23, 0x2, 0x2, 0x3ad, 0x3af, 0x5, 0xb0, 0x59, 0x2, 0x3ae, 0x3ac, 
       0x3, 0x2, 0x2, 0x2, 0x3ae, 0x3af, 0x3, 0x2, 0x2, 0x2, 0x3af, 0x3b0, 
       0x3, 0x2, 0x2, 0x2, 0x3b0, 0x3b2, 0x7, 0x57, 0x2, 0x2, 0x3b1, 0x3b3, 
       0x5, 0x5e, 0x30, 0x2, 0x3b2, 0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3b2, 0x3b3, 
       0x3, 0x2, 0x2, 0x2, 0x3b3, 0x3b4, 0x3, 0x2, 0x2, 0x2, 0x3b4, 0x3b5, 
       0x7, 0x58, 0x2, 0x2, 0x3b5, 0xaf, 0x3, 0x2, 0x2, 0x2, 0x3b6, 0x3b7, 
       0x7, 0x54, 0x2, 0x2, 0x3b7, 0xb1, 0x3, 0x2, 0x2, 0x2, 0x3b8, 0x3b9, 
       0x7, 0x19, 0x2, 0x2, 0x3b9, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x3ba, 0x3bf, 
       0x7, 0x59, 0x2, 0x2, 0x3bb, 0x3bd, 0x5, 0xb6, 0x5c, 0x2, 0x3bc, 0x3be, 
       0x7, 0x5d, 0x2, 0x2, 0x3bd, 0x3bc, 0x3, 0x2, 0x2, 0x2, 0x3bd, 0x3be, 
       0x3, 0x2, 0x2, 0x2, 0x3be, 0x3c0, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3bb, 
       0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3c0, 0x3, 0x2, 0x2, 0x2, 0x3c0, 0x3c1, 
       0x3, 0x2, 0x2, 0x2, 0x3c1, 0x3c2, 0x7, 0x5a, 0x2, 0x2, 0x3c2, 0xb5, 
       0x3, 0x2, 0x2, 0x2, 0x3c3, 0x3c5, 0x7, 0x7f, 0x2, 0x2, 0x3c4, 0x3c3, 
       0x3, 0x2, 0x2, 0x2, 0x3c4, 0x3c5, 0x3, 0x2, 0x2, 0x2, 0x3c5, 0x3c6, 
       0x3, 0x2, 0x2, 0x2, 0x3c6, 0x3ce, 0x5, 0x80, 0x41, 0x2, 0x3c7, 0x3c9, 
       0x7, 0x5d, 0x2, 0x2, 0x3c8, 0x3ca, 0x7, 0x7f, 0x2, 0x2, 0x3c9, 0x3c8, 
       0x3, 0x2, 0x2, 0x2, 0x3c9, 0x3ca, 0x3, 0x2, 0x2, 0x2, 0x3ca, 0x3cb, 
       0x3, 0x2, 0x2, 0x2, 0x3cb, 0x3cd, 0x5, 0x80, 0x41, 0x2, 0x3cc, 0x3c7, 
       0x3, 0x2, 0x2, 0x2, 0x3cd, 0x3d0, 0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3cc, 
       0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3cf, 0x3, 0x2, 0x2, 0x2, 0x3cf, 0xb7, 
       0x3, 0x2, 0x2, 0x2, 0x3d0, 0x3ce, 0x3, 0x2, 0x2, 0x2, 0x3d1, 0x3da, 
       0x7, 0x57, 0x2, 0x2, 0x3d2, 0x3d7, 0x5, 0xba, 0x5e, 0x2, 0x3d3, 0x3d4, 
       0x7, 0x5d, 0x2, 0x2, 0x3d4, 0x3d6, 0x5, 0xba, 0x5e, 0x2, 0x3d5, 0x3d3, 
       0x3, 0x2, 0x2, 0x2, 0x3d6, 0x3d9, 0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d5, 
       0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d8, 0x3, 0x2, 0x2, 0x2, 0x3d8, 0x3db, 
       0x3, 0x2, 0x2, 0x2, 0x3d9, 0x3d7, 0x3, 0x2, 0x2, 0x2, 0x3da, 0x3d2, 
       0x3, 0x2, 0x2, 0x2, 0x3da, 0x3db, 0x3, 0x2, 0x2, 0x2, 0x3db, 0x3dc, 
       0x3, 0x2, 0x2, 0x2, 0x3dc, 0x3dd, 0x7, 0x58, 0x2, 0x2, 0x3dd, 0xb9, 
       0x3, 0x2, 0x2, 0x2, 0x3de, 0x3df, 0x5, 0x1e, 0x10, 0x2, 0x3df, 0x3e0, 
       0x7, 0x5c, 0x2, 0x2, 0x3e0, 0x3e1, 0x5, 0x80, 0x41, 0x2, 0x3e1, 0x3f4, 
       0x3, 0x2, 0x2, 0x2, 0x3e2, 0x3e4, 0x9, 0x6, 0x2, 0x2, 0x3e3, 0x3e2, 
       0x3, 0x2, 0x2, 0x2, 0x3e3, 0x3e4, 0x3, 0x2, 0x2, 0x2, 0x3e4, 0x3e5, 
       0x3, 0x2, 0x2, 0x2, 0x3e5, 0x3e6, 0x5, 0x1c, 0xf, 0x2, 0x3e6, 0x3e8, 
       0x7, 0x55, 0x2, 0x2, 0x3e7, 0x3e9, 0x5, 0x56, 0x2c, 0x2, 0x3e8, 0x3e7, 
       0x3, 0x2, 0x2, 0x2, 0x3e8, 0x3e9, 0x3, 0x2, 0x2, 0x2, 0x3e9, 0x3ea, 
       0x3, 0x2, 0x2, 0x2, 0x3ea, 0x3eb, 0x7, 0x56, 0x2, 0x2, 0x3eb, 0x3ec, 
       0x7, 0x57, 0x2, 0x2, 0x3ec, 0x3ed, 0x5, 0x5a, 0x2e, 0x2, 0x3ed, 0x3ee, 
       0x7, 0x58, 0x2, 0x2, 0x3ee, 0x3f4, 0x3, 0x2, 0x2, 0x2, 0x3ef, 0x3f1, 
       0x7, 0x7f, 0x2, 0x2, 0x3f0, 0x3ef, 0x3, 0x2, 0x2, 0x2, 0x3f0, 0x3f1, 
       0x3, 0x2, 0x2, 0x2, 0x3f1, 0x3f2, 0x3, 0x2, 0x2, 0x2, 0x3f2, 0x3f4, 
       0x5, 0x80, 0x41, 0x2, 0x3f3, 0x3de, 0x3, 0x2, 0x2, 0x2, 0x3f3, 0x3e3, 
       0x3, 0x2, 0x2, 0x2, 0x3f3, 0x3f0, 0x3, 0x2, 0x2, 0x2, 0x3f4, 0xbb, 
       0x3, 0x2, 0x2, 0x2, 0x3f5, 0x3f6, 0x7, 0x55, 0x2, 0x2, 0x3f6, 0x3f7, 
       0x5, 0x7e, 0x40, 0x2, 0x3f7, 0x3f8, 0x7, 0x56, 0x2, 0x2, 0x3f8, 0xbd, 
       0x3, 0x2, 0x2, 0x2, 0x3f9, 0x3fb, 0x7, 0x83, 0x2, 0x2, 0x3fa, 0x3fc, 
       0x5, 0xc0, 0x61, 0x2, 0x3fb, 0x3fa, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3fd, 
       0x3, 0x2, 0x2, 0x2, 0x3fd, 0x3fb, 0x3, 0x2, 0x2, 0x2, 0x3fd, 0x3fe, 
       0x3, 0x2, 0x2, 0x2, 0x3fe, 0x3ff, 0x3, 0x2, 0x2, 0x2, 0x3ff, 0x400, 
       0x7, 0x83, 0x2, 0x2, 0x400, 0xbf, 0x3, 0x2, 0x2, 0x2, 0x401, 0x404, 
       0x5, 0xc2, 0x62, 0x2, 0x402, 0x404, 0x5, 0xc4, 0x63, 0x2, 0x403, 
       0x401, 0x3, 0x2, 0x2, 0x2, 0x403, 0x402, 0x3, 0x2, 0x2, 0x2, 0x404, 
       0xc1, 0x3, 0x2, 0x2, 0x2, 0x405, 0x407, 0x7, 0x80, 0x2, 0x2, 0x406, 
       0x405, 0x3, 0x2, 0x2, 0x2, 0x407, 0x408, 0x3, 0x2, 0x2, 0x2, 0x408, 
       0x406, 0x3, 0x2, 0x2, 0x2, 0x408, 0x409, 0x3, 0x2, 0x2, 0x2, 0x409, 
       0xc3, 0x3, 0x2, 0x2, 0x2, 0x40a, 0x40b, 0x7, 0x3, 0x2, 0x2, 0x40b, 
       0x40c, 0x7, 0x57, 0x2, 0x2, 0x40c, 0x40d, 0x5, 0x7e, 0x40, 0x2, 0x40d, 
       0x40e, 0x7, 0x58, 0x2, 0x2, 0x40e, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x40f, 
       0x411, 0x7, 0x2a, 0x2, 0x2, 0x410, 0x412, 0x5, 0x80, 0x41, 0x2, 0x411, 
       0x410, 0x3, 0x2, 0x2, 0x2, 0x411, 0x412, 0x3, 0x2, 0x2, 0x2, 0x412, 
       0xc7, 0x3, 0x2, 0x2, 0x2, 0x413, 0x414, 0x5, 0xca, 0x66, 0x2, 0x414, 
       0x415, 0x7, 0x44, 0x2, 0x2, 0x415, 0x416, 0x5, 0xcc, 0x67, 0x2, 0x416, 
       0xc9, 0x3, 0x2, 0x2, 0x2, 0x417, 0x41f, 0x5, 0xb0, 0x59, 0x2, 0x418, 
       0x41a, 0x7, 0x55, 0x2, 0x2, 0x419, 0x41b, 0x5, 0x56, 0x2c, 0x2, 0x41a, 
       0x419, 0x3, 0x2, 0x2, 0x2, 0x41a, 0x41b, 0x3, 0x2, 0x2, 0x2, 0x41b, 
       0x41c, 0x3, 0x2, 0x2, 0x2, 0x41c, 0x41f, 0x7, 0x56, 0x2, 0x2, 0x41d, 
       0x41f, 0x5, 0x12, 0xa, 0x2, 0x41e, 0x417, 0x3, 0x2, 0x2, 0x2, 0x41e, 
       0x418, 0x3, 0x2, 0x2, 0x2, 0x41e, 0x41d, 0x3, 0x2, 0x2, 0x2, 0x41f, 
       0xcb, 0x3, 0x2, 0x2, 0x2, 0x420, 0x426, 0x5, 0x80, 0x41, 0x2, 0x421, 
       0x422, 0x7, 0x57, 0x2, 0x2, 0x422, 0x423, 0x5, 0x5a, 0x2e, 0x2, 0x423, 
       0x424, 0x7, 0x58, 0x2, 0x2, 0x424, 0x426, 0x3, 0x2, 0x2, 0x2, 0x425, 
       0x420, 0x3, 0x2, 0x2, 0x2, 0x425, 0x421, 0x3, 0x2, 0x2, 0x2, 0x426, 
       0xcd, 0x3, 0x2, 0x2, 0x2, 0x427, 0x42c, 0x5, 0xd0, 0x69, 0x2, 0x428, 
       0x429, 0x7, 0x5d, 0x2, 0x2, 0x429, 0x42b, 0x5, 0xd0, 0x69, 0x2, 0x42a, 
       0x428, 0x3, 0x2, 0x2, 0x2, 0x42b, 0x42e, 0x3, 0x2, 0x2, 0x2, 0x42c, 
       0x42a, 0x3, 0x2, 0x2, 0x2, 0x42c, 0x42d, 0x3, 0x2, 0x2, 0x2, 0x42d, 
       0xcf, 0x3, 0x2, 0x2, 0x2, 0x42e, 0x42c, 0x3, 0x2, 0x2, 0x2, 0x42f, 
       0x436, 0x5, 0xd2, 0x6a, 0x2, 0x430, 0x436, 0x5, 0xc6, 0x64, 0x2, 
       0x431, 0x436, 0x5, 0xc8, 0x65, 0x2, 0x432, 0x433, 0x5, 0x82, 0x42, 
       0x2, 0x433, 0x434, 0x5, 0xd0, 0x69, 0x2, 0x434, 0x436, 0x3, 0x2, 
       0x2, 0x2, 0x435, 0x42f, 0x3, 0x2, 0x2, 0x2, 0x435, 0x430, 0x3, 0x2, 
       0x2, 0x2, 0x435, 0x431, 0x3, 0x2, 0x2, 0x2, 0x435, 0x432, 0x3, 0x2, 
       0x2, 0x2, 0x436, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x437, 0x43d, 0x5, 0xd4, 
       0x6b, 0x2, 0x438, 0x439, 0x7, 0x64, 0x2, 0x2, 0x439, 0x43a, 0x5, 
       0x80, 0x41, 0x2, 0x43a, 0x43b, 0x7, 0x5c, 0x2, 0x2, 0x43b, 0x43c, 
       0x5, 0xd0, 0x69, 0x2, 0x43c, 0x43e, 0x3, 0x2, 0x2, 0x2, 0x43d, 0x438, 
       0x3, 0x2, 0x2, 0x2, 0x43d, 0x43e, 0x3, 0x2, 0x2, 0x2, 0x43e, 0xd3, 
       0x3, 0x2, 0x2, 0x2, 0x43f, 0x444, 0x5, 0xd6, 0x6c, 0x2, 0x440, 0x441, 
       0x7, 0x84, 0x2, 0x2, 0x441, 0x443, 0x5, 0xd6, 0x6c, 0x2, 0x442, 0x440, 
       0x3, 0x2, 0x2, 0x2, 0x443, 0x446, 0x3, 0x2, 0x2, 0x2, 0x444, 0x442, 
       0x3, 0x2, 0x2, 0x2, 0x444, 0x445, 0x3, 0x2, 0x2, 0x2, 0x445, 0xd5, 
       0x3, 0x2, 0x2, 0x2, 0x446, 0x444, 0x3, 0x2, 0x2, 0x2, 0x447, 0x44c, 
       0x5, 0xd8, 0x6d, 0x2, 0x448, 0x449, 0x7, 0x85, 0x2, 0x2, 0x449, 0x44b, 
       0x5, 0xd8, 0x6d, 0x2, 0x44a, 0x448, 0x3, 0x2, 0x2, 0x2, 0x44b, 0x44e, 
       0x3, 0x2, 0x2, 0x2, 0x44c, 0x44a, 0x3, 0x2, 0x2, 0x2, 0x44c, 0x44d, 
       0x3, 0x2, 0x2, 0x2, 0x44d, 0xd7, 0x3, 0x2, 0x2, 0x2, 0x44e, 0x44c, 
       0x3, 0x2, 0x2, 0x2, 0x44f, 0x454, 0x5, 0xda, 0x6e, 0x2, 0x450, 0x451, 
       0x7, 0x7a, 0x2, 0x2, 0x451, 0x453, 0x5, 0xda, 0x6e, 0x2, 0x452, 0x450, 
       0x3, 0x2, 0x2, 0x2, 0x453, 0x456, 0x3, 0x2, 0x2, 0x2, 0x454, 0x452, 
       0x3, 0x2, 0x2, 0x2, 0x454, 0x455, 0x3, 0x2, 0x2, 0x2, 0x455, 0xd9, 
       0x3, 0x2, 0x2, 0x2, 0x456, 0x454, 0x3, 0x2, 0x2, 0x2, 0x457, 0x45c, 
       0x5, 0xdc, 0x6f, 0x2, 0x458, 0x459, 0x7, 0x7b, 0x2, 0x2, 0x459, 0x45b, 
       0x5, 0xdc, 0x6f, 0x2, 0x45a, 0x458, 0x3, 0x2, 0x2, 0x2, 0x45b, 0x45e, 
       0x3, 0x2, 0x2, 0x2, 0x45c, 0x45a, 0x3, 0x2, 0x2, 0x2, 0x45c, 0x45d, 
       0x3, 0x2, 0x2, 0x2, 0x45d, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x45e, 0x45c, 
       0x3, 0x2, 0x2, 0x2, 0x45f, 0x464, 0x5, 0xde, 0x70, 0x2, 0x460, 0x461, 
       0x7, 0x79, 0x2, 0x2, 0x461, 0x463, 0x5, 0xde, 0x70, 0x2, 0x462, 0x460, 
       0x3, 0x2, 0x2, 0x2, 0x463, 0x466, 0x3, 0x2, 0x2, 0x2, 0x464, 0x462, 
       0x3, 0x2, 0x2, 0x2, 0x464, 0x465, 0x3, 0x2, 0x2, 0x2, 0x465, 0xdd, 
       0x3, 0x2, 0x2, 0x2, 0x466, 0x464, 0x3, 0x2, 0x2, 0x2, 0x467, 0x46c, 
       0x5, 0xe0, 0x71, 0x2, 0x468, 0x469, 0x9, 0x8, 0x2, 0x2, 0x469, 0x46b, 
       0x5, 0xe0, 0x71, 0x2, 0x46a, 0x468, 0x3, 0x2, 0x2, 0x2, 0x46b, 0x46e, 
       0x3, 0x2, 0x2, 0x2, 0x46c, 0x46a, 0x3, 0x2, 0x2, 0x2, 0x46c, 0x46d, 
       0x3, 0x2, 0x2, 0x2, 0x46d, 0xdf, 0x3, 0x2, 0x2, 0x2, 0x46e, 0x46c, 
       0x3, 0x2, 0x2, 0x2, 0x46f, 0x474, 0x5, 0xe2, 0x72, 0x2, 0x470, 0x471, 
       0x9, 0xf, 0x2, 0x2, 0x471, 0x473, 0x5, 0xe2, 0x72, 0x2, 0x472, 0x470, 
       0x3, 0x2, 0x2, 0x2, 0x473, 0x476, 0x3, 0x2, 0x2, 0x2, 0x474, 0x472, 
       0x3, 0x2, 0x2, 0x2, 0x474, 0x475, 0x3, 0x2, 0x2, 0x2, 0x475, 0xe1, 
       0x3, 0x2, 0x2, 0x2, 0x476, 0x474, 0x3, 0x2, 0x2, 0x2, 0x477, 0x47c, 
       0x5, 0xe4, 0x73, 0x2, 0x478, 0x479, 0x9, 0xa, 0x2, 0x2, 0x479, 0x47b, 
       0x5, 0xe4, 0x73, 0x2, 0x47a, 0x478, 0x3, 0x2, 0x2, 0x2, 0x47b, 0x47e, 
       0x3, 0x2, 0x2, 0x2, 0x47c, 0x47a, 0x3, 0x2, 0x2, 0x2, 0x47c, 0x47d, 
       0x3, 0x2, 0x2, 0x2, 0x47d, 0xe3, 0x3, 0x2, 0x2, 0x2, 0x47e, 0x47c, 
       0x3, 0x2, 0x2, 0x2, 0x47f, 0x484, 0x5, 0xe6, 0x74, 0x2, 0x480, 0x481, 
       0x9, 0xb, 0x2, 0x2, 0x481, 0x483, 0x5, 0xe6, 0x74, 0x2, 0x482, 0x480, 
       0x3, 0x2, 0x2, 0x2, 0x483, 0x486, 0x3, 0x2, 0x2, 0x2, 0x484, 0x482, 
       0x3, 0x2, 0x2, 0x2, 0x484, 0x485, 0x3, 0x2, 0x2, 0x2, 0x485, 0xe5, 
       0x3, 0x2, 0x2, 0x2, 0x486, 0x484, 0x3, 0x2, 0x2, 0x2, 0x487, 0x48c, 
       0x5, 0xe8, 0x75, 0x2, 0x488, 0x489, 0x9, 0xc, 0x2, 0x2, 0x489, 0x48b, 
       0x5, 0xe8, 0x75, 0x2, 0x48a, 0x488, 0x3, 0x2, 0x2, 0x2, 0x48b, 0x48e, 
       0x3, 0x2, 0x2, 0x2, 0x48c, 0x48a, 0x3, 0x2, 0x2, 0x2, 0x48c, 0x48d, 
       0x3, 0x2, 0x2, 0x2, 0x48d, 0xe7, 0x3, 0x2, 0x2, 0x2, 0x48e, 0x48c, 
       0x3, 0x2, 0x2, 0x2, 0x48f, 0x490, 0x5, 0x9c, 0x4f, 0x2, 0x490, 0x491, 
       0x5, 0xe8, 0x75, 0x2, 0x491, 0x494, 0x3, 0x2, 0x2, 0x2, 0x492, 0x494, 
       0x5, 0x9e, 0x50, 0x2, 0x493, 0x48f, 0x3, 0x2, 0x2, 0x2, 0x493, 0x492, 
       0x3, 0x2, 0x2, 0x2, 0x494, 0xe9, 0x3, 0x2, 0x2, 0x2, 0x495, 0x497, 
       0x5, 0x4, 0x3, 0x2, 0x496, 0x495, 0x3, 0x2, 0x2, 0x2, 0x497, 0x498, 
       0x3, 0x2, 0x2, 0x2, 0x498, 0x496, 0x3, 0x2, 0x2, 0x2, 0x498, 0x499, 
       0x3, 0x2, 0x2, 0x2, 0x499, 0xeb, 0x3, 0x2, 0x2, 0x2, 0x7f, 0xef, 
       0xf7, 0x10b, 0x10f, 0x116, 0x121, 0x126, 0x12a, 0x12e, 0x136, 0x139, 
       0x140, 0x146, 0x14a, 0x152, 0x155, 0x15c, 0x160, 0x165, 0x17e, 0x192, 
       0x196, 0x19a, 0x1a2, 0x1b9, 0x1bd, 0x1c3, 0x1c9, 0x1cf, 0x1e5, 0x1e9, 
       0x1eb, 0x1f2, 0x1f8, 0x1fd, 0x206, 0x209, 0x210, 0x216, 0x225, 0x231, 
       0x239, 0x23b, 0x23e, 0x244, 0x248, 0x24f, 0x254, 0x259, 0x269, 0x276, 
       0x284, 0x287, 0x290, 0x29a, 0x2a2, 0x2a5, 0x2a9, 0x2ae, 0x2b6, 0x2b9, 
       0x2c2, 0x2c7, 0x2ce, 0x2d7, 0x2e1, 0x2e8, 0x2f0, 0x2f8, 0x300, 0x308, 
       0x310, 0x318, 0x320, 0x328, 0x330, 0x337, 0x33d, 0x341, 0x34d, 0x352, 
       0x35f, 0x361, 0x36b, 0x374, 0x38f, 0x399, 0x39d, 0x3a1, 0x3aa, 0x3ae, 
       0x3b2, 0x3bd, 0x3bf, 0x3c4, 0x3c9, 0x3ce, 0x3d7, 0x3da, 0x3e3, 0x3e8, 
       0x3f0, 0x3f3, 0x3fd, 0x403, 0x408, 0x411, 0x41a, 0x41e, 0x425, 0x42c, 
       0x435, 0x43d, 0x444, 0x44c, 0x454, 0x45c, 0x464, 0x46c, 0x474, 0x47c, 
       0x484, 0x48c, 0x493, 0x498, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

JavaScriptParser::Initializer JavaScriptParser::_init;
