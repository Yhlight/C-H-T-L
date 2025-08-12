
// Generated from grammars/js/JavaScript_simple.g4 by ANTLR 4.13.1


#include "JavaScript_simpleListener.h"
#include "JavaScript_simpleVisitor.h"

#include "JavaScript_simpleParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct JavaScript_simpleParserStaticData final {
  JavaScript_simpleParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  JavaScript_simpleParserStaticData(const JavaScript_simpleParserStaticData&) = delete;
  JavaScript_simpleParserStaticData(JavaScript_simpleParserStaticData&&) = delete;
  JavaScript_simpleParserStaticData& operator=(const JavaScript_simpleParserStaticData&) = delete;
  JavaScript_simpleParserStaticData& operator=(JavaScript_simpleParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag javascript_simpleParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
JavaScript_simpleParserStaticData *javascript_simpleParserStaticData = nullptr;

void javascript_simpleParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (javascript_simpleParserStaticData != nullptr) {
    return;
  }
#else
  assert(javascript_simpleParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<JavaScript_simpleParserStaticData>(
    std::vector<std::string>{
      "program", "statement", "expressionStatement", "expression", "assignmentExpression", 
      "functionCall", "argumentList", "identifier", "literal", "variableDeclaration", 
      "functionDeclaration", "parameterList", "ifStatement", "forStatement", 
      "forInitializer", "whileStatement", "returnStatement", "blockStatement"
    },
    std::vector<std::string>{
      "", "", "", "'function'", "'var'", "'let'", "'const'", "'if'", "'else'", 
      "'for'", "'while'", "'return'", "", "", "", "'{'", "'}'", "'('", "')'", 
      "'['", "']'", "';'", "','", "'.'", "'='", "'+'", "'-'", "'*'", "'/'"
    },
    std::vector<std::string>{
      "", "WS", "COMMENT", "FUNCTION", "VAR", "LET", "CONST", "IF", "ELSE", 
      "FOR", "WHILE", "RETURN", "IDENTIFIER", "NUMBER", "STRING", "LBRACE", 
      "RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "SEMICOLON", 
      "COMMA", "DOT", "EQUALS", "PLUS", "MINUS", "MULTIPLY", "DIVIDE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,28,160,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,1,0,5,0,38,8,0,10,0,12,0,41,9,0,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,51,8,1,1,2,1,2,1,2,1,3,1,3,1,3,1,3,3,
  	3,60,8,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,3,5,69,8,5,1,5,1,5,1,6,1,6,1,6,5,
  	6,76,8,6,10,6,12,6,79,9,6,1,7,1,7,1,8,1,8,1,9,1,9,1,9,1,9,3,9,89,8,9,
  	1,9,1,9,1,10,1,10,1,10,1,10,3,10,97,8,10,1,10,1,10,1,10,1,11,1,11,1,11,
  	5,11,105,8,11,10,11,12,11,108,9,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	3,12,117,8,12,1,13,1,13,1,13,3,13,122,8,13,1,13,1,13,3,13,126,8,13,1,
  	13,1,13,3,13,130,8,13,1,13,1,13,1,13,1,14,1,14,3,14,137,8,14,1,15,1,15,
  	1,15,1,15,1,15,1,15,1,16,1,16,3,16,147,8,16,1,16,1,16,1,17,1,17,5,17,
  	153,8,17,10,17,12,17,156,9,17,1,17,1,17,1,17,0,0,18,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,34,0,2,1,0,13,14,1,0,4,6,164,0,39,1,0,0,0,
  	2,50,1,0,0,0,4,52,1,0,0,0,6,59,1,0,0,0,8,61,1,0,0,0,10,65,1,0,0,0,12,
  	72,1,0,0,0,14,80,1,0,0,0,16,82,1,0,0,0,18,84,1,0,0,0,20,92,1,0,0,0,22,
  	101,1,0,0,0,24,109,1,0,0,0,26,118,1,0,0,0,28,136,1,0,0,0,30,138,1,0,0,
  	0,32,144,1,0,0,0,34,150,1,0,0,0,36,38,3,2,1,0,37,36,1,0,0,0,38,41,1,0,
  	0,0,39,37,1,0,0,0,39,40,1,0,0,0,40,1,1,0,0,0,41,39,1,0,0,0,42,51,3,4,
  	2,0,43,51,3,18,9,0,44,51,3,20,10,0,45,51,3,24,12,0,46,51,3,26,13,0,47,
  	51,3,30,15,0,48,51,3,32,16,0,49,51,3,34,17,0,50,42,1,0,0,0,50,43,1,0,
  	0,0,50,44,1,0,0,0,50,45,1,0,0,0,50,46,1,0,0,0,50,47,1,0,0,0,50,48,1,0,
  	0,0,50,49,1,0,0,0,51,3,1,0,0,0,52,53,3,6,3,0,53,54,5,21,0,0,54,5,1,0,
  	0,0,55,60,3,8,4,0,56,60,3,10,5,0,57,60,3,14,7,0,58,60,3,16,8,0,59,55,
  	1,0,0,0,59,56,1,0,0,0,59,57,1,0,0,0,59,58,1,0,0,0,60,7,1,0,0,0,61,62,
  	5,12,0,0,62,63,5,24,0,0,63,64,3,6,3,0,64,9,1,0,0,0,65,66,5,12,0,0,66,
  	68,5,17,0,0,67,69,3,12,6,0,68,67,1,0,0,0,68,69,1,0,0,0,69,70,1,0,0,0,
  	70,71,5,18,0,0,71,11,1,0,0,0,72,77,3,6,3,0,73,74,5,22,0,0,74,76,3,6,3,
  	0,75,73,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,77,78,1,0,0,0,78,13,1,0,0,
  	0,79,77,1,0,0,0,80,81,5,12,0,0,81,15,1,0,0,0,82,83,7,0,0,0,83,17,1,0,
  	0,0,84,85,7,1,0,0,85,88,5,12,0,0,86,87,5,24,0,0,87,89,3,6,3,0,88,86,1,
  	0,0,0,88,89,1,0,0,0,89,90,1,0,0,0,90,91,5,21,0,0,91,19,1,0,0,0,92,93,
  	5,3,0,0,93,94,5,12,0,0,94,96,5,17,0,0,95,97,3,22,11,0,96,95,1,0,0,0,96,
  	97,1,0,0,0,97,98,1,0,0,0,98,99,5,18,0,0,99,100,3,34,17,0,100,21,1,0,0,
  	0,101,106,5,12,0,0,102,103,5,22,0,0,103,105,5,12,0,0,104,102,1,0,0,0,
  	105,108,1,0,0,0,106,104,1,0,0,0,106,107,1,0,0,0,107,23,1,0,0,0,108,106,
  	1,0,0,0,109,110,5,7,0,0,110,111,5,17,0,0,111,112,3,6,3,0,112,113,5,18,
  	0,0,113,116,3,2,1,0,114,115,5,8,0,0,115,117,3,2,1,0,116,114,1,0,0,0,116,
  	117,1,0,0,0,117,25,1,0,0,0,118,119,5,9,0,0,119,121,5,17,0,0,120,122,3,
  	28,14,0,121,120,1,0,0,0,121,122,1,0,0,0,122,123,1,0,0,0,123,125,5,21,
  	0,0,124,126,3,6,3,0,125,124,1,0,0,0,125,126,1,0,0,0,126,127,1,0,0,0,127,
  	129,5,21,0,0,128,130,3,6,3,0,129,128,1,0,0,0,129,130,1,0,0,0,130,131,
  	1,0,0,0,131,132,5,18,0,0,132,133,3,2,1,0,133,27,1,0,0,0,134,137,3,18,
  	9,0,135,137,3,4,2,0,136,134,1,0,0,0,136,135,1,0,0,0,137,29,1,0,0,0,138,
  	139,5,10,0,0,139,140,5,17,0,0,140,141,3,6,3,0,141,142,5,18,0,0,142,143,
  	3,2,1,0,143,31,1,0,0,0,144,146,5,11,0,0,145,147,3,6,3,0,146,145,1,0,0,
  	0,146,147,1,0,0,0,147,148,1,0,0,0,148,149,5,21,0,0,149,33,1,0,0,0,150,
  	154,5,15,0,0,151,153,3,2,1,0,152,151,1,0,0,0,153,156,1,0,0,0,154,152,
  	1,0,0,0,154,155,1,0,0,0,155,157,1,0,0,0,156,154,1,0,0,0,157,158,5,16,
  	0,0,158,35,1,0,0,0,15,39,50,59,68,77,88,96,106,116,121,125,129,136,146,
  	154
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  javascript_simpleParserStaticData = staticData.release();
}

}

JavaScript_simpleParser::JavaScript_simpleParser(TokenStream *input) : JavaScript_simpleParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

JavaScript_simpleParser::JavaScript_simpleParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  JavaScript_simpleParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *javascript_simpleParserStaticData->atn, javascript_simpleParserStaticData->decisionToDFA, javascript_simpleParserStaticData->sharedContextCache, options);
}

JavaScript_simpleParser::~JavaScript_simpleParser() {
  delete _interpreter;
}

const atn::ATN& JavaScript_simpleParser::getATN() const {
  return *javascript_simpleParserStaticData->atn;
}

std::string JavaScript_simpleParser::getGrammarFileName() const {
  return "JavaScript_simple.g4";
}

const std::vector<std::string>& JavaScript_simpleParser::getRuleNames() const {
  return javascript_simpleParserStaticData->ruleNames;
}

const dfa::Vocabulary& JavaScript_simpleParser::getVocabulary() const {
  return javascript_simpleParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView JavaScript_simpleParser::getSerializedATN() const {
  return javascript_simpleParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

JavaScript_simpleParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScript_simpleParser::StatementContext *> JavaScript_simpleParser::ProgramContext::statement() {
  return getRuleContexts<JavaScript_simpleParser::StatementContext>();
}

JavaScript_simpleParser::StatementContext* JavaScript_simpleParser::ProgramContext::statement(size_t i) {
  return getRuleContext<JavaScript_simpleParser::StatementContext>(i);
}


size_t JavaScript_simpleParser::ProgramContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleProgram;
}

void JavaScript_simpleParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void JavaScript_simpleParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any JavaScript_simpleParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::ProgramContext* JavaScript_simpleParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, JavaScript_simpleParser::RuleProgram);
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
    setState(39);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 65272) != 0)) {
      setState(36);
      statement();
      setState(41);
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

//----------------- StatementContext ------------------------------------------------------------------

JavaScript_simpleParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScript_simpleParser::ExpressionStatementContext* JavaScript_simpleParser::StatementContext::expressionStatement() {
  return getRuleContext<JavaScript_simpleParser::ExpressionStatementContext>(0);
}

JavaScript_simpleParser::VariableDeclarationContext* JavaScript_simpleParser::StatementContext::variableDeclaration() {
  return getRuleContext<JavaScript_simpleParser::VariableDeclarationContext>(0);
}

JavaScript_simpleParser::FunctionDeclarationContext* JavaScript_simpleParser::StatementContext::functionDeclaration() {
  return getRuleContext<JavaScript_simpleParser::FunctionDeclarationContext>(0);
}

JavaScript_simpleParser::IfStatementContext* JavaScript_simpleParser::StatementContext::ifStatement() {
  return getRuleContext<JavaScript_simpleParser::IfStatementContext>(0);
}

JavaScript_simpleParser::ForStatementContext* JavaScript_simpleParser::StatementContext::forStatement() {
  return getRuleContext<JavaScript_simpleParser::ForStatementContext>(0);
}

JavaScript_simpleParser::WhileStatementContext* JavaScript_simpleParser::StatementContext::whileStatement() {
  return getRuleContext<JavaScript_simpleParser::WhileStatementContext>(0);
}

JavaScript_simpleParser::ReturnStatementContext* JavaScript_simpleParser::StatementContext::returnStatement() {
  return getRuleContext<JavaScript_simpleParser::ReturnStatementContext>(0);
}

JavaScript_simpleParser::BlockStatementContext* JavaScript_simpleParser::StatementContext::blockStatement() {
  return getRuleContext<JavaScript_simpleParser::BlockStatementContext>(0);
}


size_t JavaScript_simpleParser::StatementContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleStatement;
}

void JavaScript_simpleParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void JavaScript_simpleParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any JavaScript_simpleParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::StatementContext* JavaScript_simpleParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, JavaScript_simpleParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(50);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScript_simpleParser::IDENTIFIER:
      case JavaScript_simpleParser::NUMBER:
      case JavaScript_simpleParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(42);
        expressionStatement();
        break;
      }

      case JavaScript_simpleParser::VAR:
      case JavaScript_simpleParser::LET:
      case JavaScript_simpleParser::CONST: {
        enterOuterAlt(_localctx, 2);
        setState(43);
        variableDeclaration();
        break;
      }

      case JavaScript_simpleParser::FUNCTION: {
        enterOuterAlt(_localctx, 3);
        setState(44);
        functionDeclaration();
        break;
      }

      case JavaScript_simpleParser::IF: {
        enterOuterAlt(_localctx, 4);
        setState(45);
        ifStatement();
        break;
      }

      case JavaScript_simpleParser::FOR: {
        enterOuterAlt(_localctx, 5);
        setState(46);
        forStatement();
        break;
      }

      case JavaScript_simpleParser::WHILE: {
        enterOuterAlt(_localctx, 6);
        setState(47);
        whileStatement();
        break;
      }

      case JavaScript_simpleParser::RETURN: {
        enterOuterAlt(_localctx, 7);
        setState(48);
        returnStatement();
        break;
      }

      case JavaScript_simpleParser::LBRACE: {
        enterOuterAlt(_localctx, 8);
        setState(49);
        blockStatement();
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

//----------------- ExpressionStatementContext ------------------------------------------------------------------

JavaScript_simpleParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::ExpressionStatementContext::expression() {
  return getRuleContext<JavaScript_simpleParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScript_simpleParser::ExpressionStatementContext::SEMICOLON() {
  return getToken(JavaScript_simpleParser::SEMICOLON, 0);
}


size_t JavaScript_simpleParser::ExpressionStatementContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleExpressionStatement;
}

void JavaScript_simpleParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void JavaScript_simpleParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}


std::any JavaScript_simpleParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::ExpressionStatementContext* JavaScript_simpleParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 4, JavaScript_simpleParser::RuleExpressionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    expression();
    setState(53);
    match(JavaScript_simpleParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

JavaScript_simpleParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScript_simpleParser::AssignmentExpressionContext* JavaScript_simpleParser::ExpressionContext::assignmentExpression() {
  return getRuleContext<JavaScript_simpleParser::AssignmentExpressionContext>(0);
}

JavaScript_simpleParser::FunctionCallContext* JavaScript_simpleParser::ExpressionContext::functionCall() {
  return getRuleContext<JavaScript_simpleParser::FunctionCallContext>(0);
}

JavaScript_simpleParser::IdentifierContext* JavaScript_simpleParser::ExpressionContext::identifier() {
  return getRuleContext<JavaScript_simpleParser::IdentifierContext>(0);
}

JavaScript_simpleParser::LiteralContext* JavaScript_simpleParser::ExpressionContext::literal() {
  return getRuleContext<JavaScript_simpleParser::LiteralContext>(0);
}


size_t JavaScript_simpleParser::ExpressionContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleExpression;
}

void JavaScript_simpleParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void JavaScript_simpleParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any JavaScript_simpleParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, JavaScript_simpleParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(59);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(55);
      assignmentExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(56);
      functionCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(57);
      identifier();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(58);
      literal();
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

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

JavaScript_simpleParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::AssignmentExpressionContext::IDENTIFIER() {
  return getToken(JavaScript_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScript_simpleParser::AssignmentExpressionContext::EQUALS() {
  return getToken(JavaScript_simpleParser::EQUALS, 0);
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::AssignmentExpressionContext::expression() {
  return getRuleContext<JavaScript_simpleParser::ExpressionContext>(0);
}


size_t JavaScript_simpleParser::AssignmentExpressionContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleAssignmentExpression;
}

void JavaScript_simpleParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}

void JavaScript_simpleParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}


std::any JavaScript_simpleParser::AssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::AssignmentExpressionContext* JavaScript_simpleParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 8, JavaScript_simpleParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    match(JavaScript_simpleParser::IDENTIFIER);
    setState(62);
    match(JavaScript_simpleParser::EQUALS);
    setState(63);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

JavaScript_simpleParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::FunctionCallContext::IDENTIFIER() {
  return getToken(JavaScript_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScript_simpleParser::FunctionCallContext::LPAREN() {
  return getToken(JavaScript_simpleParser::LPAREN, 0);
}

tree::TerminalNode* JavaScript_simpleParser::FunctionCallContext::RPAREN() {
  return getToken(JavaScript_simpleParser::RPAREN, 0);
}

JavaScript_simpleParser::ArgumentListContext* JavaScript_simpleParser::FunctionCallContext::argumentList() {
  return getRuleContext<JavaScript_simpleParser::ArgumentListContext>(0);
}


size_t JavaScript_simpleParser::FunctionCallContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleFunctionCall;
}

void JavaScript_simpleParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void JavaScript_simpleParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}


std::any JavaScript_simpleParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::FunctionCallContext* JavaScript_simpleParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 10, JavaScript_simpleParser::RuleFunctionCall);
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
    setState(65);
    match(JavaScript_simpleParser::IDENTIFIER);
    setState(66);
    match(JavaScript_simpleParser::LPAREN);
    setState(68);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0)) {
      setState(67);
      argumentList();
    }
    setState(70);
    match(JavaScript_simpleParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

JavaScript_simpleParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScript_simpleParser::ExpressionContext *> JavaScript_simpleParser::ArgumentListContext::expression() {
  return getRuleContexts<JavaScript_simpleParser::ExpressionContext>();
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::ArgumentListContext::expression(size_t i) {
  return getRuleContext<JavaScript_simpleParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScript_simpleParser::ArgumentListContext::COMMA() {
  return getTokens(JavaScript_simpleParser::COMMA);
}

tree::TerminalNode* JavaScript_simpleParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(JavaScript_simpleParser::COMMA, i);
}


size_t JavaScript_simpleParser::ArgumentListContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleArgumentList;
}

void JavaScript_simpleParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void JavaScript_simpleParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}


std::any JavaScript_simpleParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::ArgumentListContext* JavaScript_simpleParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 12, JavaScript_simpleParser::RuleArgumentList);
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
    setState(72);
    expression();
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScript_simpleParser::COMMA) {
      setState(73);
      match(JavaScript_simpleParser::COMMA);
      setState(74);
      expression();
      setState(79);
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

//----------------- IdentifierContext ------------------------------------------------------------------

JavaScript_simpleParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::IdentifierContext::IDENTIFIER() {
  return getToken(JavaScript_simpleParser::IDENTIFIER, 0);
}


size_t JavaScript_simpleParser::IdentifierContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleIdentifier;
}

void JavaScript_simpleParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void JavaScript_simpleParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


std::any JavaScript_simpleParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::IdentifierContext* JavaScript_simpleParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 14, JavaScript_simpleParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    match(JavaScript_simpleParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

JavaScript_simpleParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::LiteralContext::STRING() {
  return getToken(JavaScript_simpleParser::STRING, 0);
}

tree::TerminalNode* JavaScript_simpleParser::LiteralContext::NUMBER() {
  return getToken(JavaScript_simpleParser::NUMBER, 0);
}


size_t JavaScript_simpleParser::LiteralContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleLiteral;
}

void JavaScript_simpleParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void JavaScript_simpleParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any JavaScript_simpleParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::LiteralContext* JavaScript_simpleParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 16, JavaScript_simpleParser::RuleLiteral);
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
    setState(82);
    _la = _input->LA(1);
    if (!(_la == JavaScript_simpleParser::NUMBER

    || _la == JavaScript_simpleParser::STRING)) {
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

//----------------- VariableDeclarationContext ------------------------------------------------------------------

JavaScript_simpleParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::VariableDeclarationContext::IDENTIFIER() {
  return getToken(JavaScript_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScript_simpleParser::VariableDeclarationContext::SEMICOLON() {
  return getToken(JavaScript_simpleParser::SEMICOLON, 0);
}

tree::TerminalNode* JavaScript_simpleParser::VariableDeclarationContext::VAR() {
  return getToken(JavaScript_simpleParser::VAR, 0);
}

tree::TerminalNode* JavaScript_simpleParser::VariableDeclarationContext::LET() {
  return getToken(JavaScript_simpleParser::LET, 0);
}

tree::TerminalNode* JavaScript_simpleParser::VariableDeclarationContext::CONST() {
  return getToken(JavaScript_simpleParser::CONST, 0);
}

tree::TerminalNode* JavaScript_simpleParser::VariableDeclarationContext::EQUALS() {
  return getToken(JavaScript_simpleParser::EQUALS, 0);
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::VariableDeclarationContext::expression() {
  return getRuleContext<JavaScript_simpleParser::ExpressionContext>(0);
}


size_t JavaScript_simpleParser::VariableDeclarationContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleVariableDeclaration;
}

void JavaScript_simpleParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void JavaScript_simpleParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}


std::any JavaScript_simpleParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::VariableDeclarationContext* JavaScript_simpleParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 18, JavaScript_simpleParser::RuleVariableDeclaration);
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
    setState(84);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 112) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(85);
    match(JavaScript_simpleParser::IDENTIFIER);
    setState(88);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScript_simpleParser::EQUALS) {
      setState(86);
      match(JavaScript_simpleParser::EQUALS);
      setState(87);
      expression();
    }
    setState(90);
    match(JavaScript_simpleParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

JavaScript_simpleParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::FunctionDeclarationContext::FUNCTION() {
  return getToken(JavaScript_simpleParser::FUNCTION, 0);
}

tree::TerminalNode* JavaScript_simpleParser::FunctionDeclarationContext::IDENTIFIER() {
  return getToken(JavaScript_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScript_simpleParser::FunctionDeclarationContext::LPAREN() {
  return getToken(JavaScript_simpleParser::LPAREN, 0);
}

tree::TerminalNode* JavaScript_simpleParser::FunctionDeclarationContext::RPAREN() {
  return getToken(JavaScript_simpleParser::RPAREN, 0);
}

JavaScript_simpleParser::BlockStatementContext* JavaScript_simpleParser::FunctionDeclarationContext::blockStatement() {
  return getRuleContext<JavaScript_simpleParser::BlockStatementContext>(0);
}

JavaScript_simpleParser::ParameterListContext* JavaScript_simpleParser::FunctionDeclarationContext::parameterList() {
  return getRuleContext<JavaScript_simpleParser::ParameterListContext>(0);
}


size_t JavaScript_simpleParser::FunctionDeclarationContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleFunctionDeclaration;
}

void JavaScript_simpleParser::FunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDeclaration(this);
}

void JavaScript_simpleParser::FunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDeclaration(this);
}


std::any JavaScript_simpleParser::FunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::FunctionDeclarationContext* JavaScript_simpleParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 20, JavaScript_simpleParser::RuleFunctionDeclaration);
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
    setState(92);
    match(JavaScript_simpleParser::FUNCTION);
    setState(93);
    match(JavaScript_simpleParser::IDENTIFIER);
    setState(94);
    match(JavaScript_simpleParser::LPAREN);
    setState(96);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScript_simpleParser::IDENTIFIER) {
      setState(95);
      parameterList();
    }
    setState(98);
    match(JavaScript_simpleParser::RPAREN);
    setState(99);
    blockStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

JavaScript_simpleParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaScript_simpleParser::ParameterListContext::IDENTIFIER() {
  return getTokens(JavaScript_simpleParser::IDENTIFIER);
}

tree::TerminalNode* JavaScript_simpleParser::ParameterListContext::IDENTIFIER(size_t i) {
  return getToken(JavaScript_simpleParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> JavaScript_simpleParser::ParameterListContext::COMMA() {
  return getTokens(JavaScript_simpleParser::COMMA);
}

tree::TerminalNode* JavaScript_simpleParser::ParameterListContext::COMMA(size_t i) {
  return getToken(JavaScript_simpleParser::COMMA, i);
}


size_t JavaScript_simpleParser::ParameterListContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleParameterList;
}

void JavaScript_simpleParser::ParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterList(this);
}

void JavaScript_simpleParser::ParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterList(this);
}


std::any JavaScript_simpleParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::ParameterListContext* JavaScript_simpleParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 22, JavaScript_simpleParser::RuleParameterList);
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
    setState(101);
    match(JavaScript_simpleParser::IDENTIFIER);
    setState(106);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScript_simpleParser::COMMA) {
      setState(102);
      match(JavaScript_simpleParser::COMMA);
      setState(103);
      match(JavaScript_simpleParser::IDENTIFIER);
      setState(108);
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

//----------------- IfStatementContext ------------------------------------------------------------------

JavaScript_simpleParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::IfStatementContext::IF() {
  return getToken(JavaScript_simpleParser::IF, 0);
}

tree::TerminalNode* JavaScript_simpleParser::IfStatementContext::LPAREN() {
  return getToken(JavaScript_simpleParser::LPAREN, 0);
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::IfStatementContext::expression() {
  return getRuleContext<JavaScript_simpleParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScript_simpleParser::IfStatementContext::RPAREN() {
  return getToken(JavaScript_simpleParser::RPAREN, 0);
}

std::vector<JavaScript_simpleParser::StatementContext *> JavaScript_simpleParser::IfStatementContext::statement() {
  return getRuleContexts<JavaScript_simpleParser::StatementContext>();
}

JavaScript_simpleParser::StatementContext* JavaScript_simpleParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<JavaScript_simpleParser::StatementContext>(i);
}

tree::TerminalNode* JavaScript_simpleParser::IfStatementContext::ELSE() {
  return getToken(JavaScript_simpleParser::ELSE, 0);
}


size_t JavaScript_simpleParser::IfStatementContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleIfStatement;
}

void JavaScript_simpleParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void JavaScript_simpleParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}


std::any JavaScript_simpleParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::IfStatementContext* JavaScript_simpleParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, JavaScript_simpleParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    match(JavaScript_simpleParser::IF);
    setState(110);
    match(JavaScript_simpleParser::LPAREN);
    setState(111);
    expression();
    setState(112);
    match(JavaScript_simpleParser::RPAREN);
    setState(113);
    statement();
    setState(116);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(114);
      match(JavaScript_simpleParser::ELSE);
      setState(115);
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

//----------------- ForStatementContext ------------------------------------------------------------------

JavaScript_simpleParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::ForStatementContext::FOR() {
  return getToken(JavaScript_simpleParser::FOR, 0);
}

tree::TerminalNode* JavaScript_simpleParser::ForStatementContext::LPAREN() {
  return getToken(JavaScript_simpleParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> JavaScript_simpleParser::ForStatementContext::SEMICOLON() {
  return getTokens(JavaScript_simpleParser::SEMICOLON);
}

tree::TerminalNode* JavaScript_simpleParser::ForStatementContext::SEMICOLON(size_t i) {
  return getToken(JavaScript_simpleParser::SEMICOLON, i);
}

tree::TerminalNode* JavaScript_simpleParser::ForStatementContext::RPAREN() {
  return getToken(JavaScript_simpleParser::RPAREN, 0);
}

JavaScript_simpleParser::StatementContext* JavaScript_simpleParser::ForStatementContext::statement() {
  return getRuleContext<JavaScript_simpleParser::StatementContext>(0);
}

JavaScript_simpleParser::ForInitializerContext* JavaScript_simpleParser::ForStatementContext::forInitializer() {
  return getRuleContext<JavaScript_simpleParser::ForInitializerContext>(0);
}

std::vector<JavaScript_simpleParser::ExpressionContext *> JavaScript_simpleParser::ForStatementContext::expression() {
  return getRuleContexts<JavaScript_simpleParser::ExpressionContext>();
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::ForStatementContext::expression(size_t i) {
  return getRuleContext<JavaScript_simpleParser::ExpressionContext>(i);
}


size_t JavaScript_simpleParser::ForStatementContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleForStatement;
}

void JavaScript_simpleParser::ForStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStatement(this);
}

void JavaScript_simpleParser::ForStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStatement(this);
}


std::any JavaScript_simpleParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::ForStatementContext* JavaScript_simpleParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, JavaScript_simpleParser::RuleForStatement);
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
    setState(118);
    match(JavaScript_simpleParser::FOR);
    setState(119);
    match(JavaScript_simpleParser::LPAREN);
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28784) != 0)) {
      setState(120);
      forInitializer();
    }
    setState(123);
    match(JavaScript_simpleParser::SEMICOLON);
    setState(125);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0)) {
      setState(124);
      expression();
    }
    setState(127);
    match(JavaScript_simpleParser::SEMICOLON);
    setState(129);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0)) {
      setState(128);
      expression();
    }
    setState(131);
    match(JavaScript_simpleParser::RPAREN);
    setState(132);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForInitializerContext ------------------------------------------------------------------

JavaScript_simpleParser::ForInitializerContext::ForInitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScript_simpleParser::VariableDeclarationContext* JavaScript_simpleParser::ForInitializerContext::variableDeclaration() {
  return getRuleContext<JavaScript_simpleParser::VariableDeclarationContext>(0);
}

JavaScript_simpleParser::ExpressionStatementContext* JavaScript_simpleParser::ForInitializerContext::expressionStatement() {
  return getRuleContext<JavaScript_simpleParser::ExpressionStatementContext>(0);
}


size_t JavaScript_simpleParser::ForInitializerContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleForInitializer;
}

void JavaScript_simpleParser::ForInitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForInitializer(this);
}

void JavaScript_simpleParser::ForInitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForInitializer(this);
}


std::any JavaScript_simpleParser::ForInitializerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitForInitializer(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::ForInitializerContext* JavaScript_simpleParser::forInitializer() {
  ForInitializerContext *_localctx = _tracker.createInstance<ForInitializerContext>(_ctx, getState());
  enterRule(_localctx, 28, JavaScript_simpleParser::RuleForInitializer);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(136);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScript_simpleParser::VAR:
      case JavaScript_simpleParser::LET:
      case JavaScript_simpleParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(134);
        variableDeclaration();
        break;
      }

      case JavaScript_simpleParser::IDENTIFIER:
      case JavaScript_simpleParser::NUMBER:
      case JavaScript_simpleParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(135);
        expressionStatement();
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

//----------------- WhileStatementContext ------------------------------------------------------------------

JavaScript_simpleParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::WhileStatementContext::WHILE() {
  return getToken(JavaScript_simpleParser::WHILE, 0);
}

tree::TerminalNode* JavaScript_simpleParser::WhileStatementContext::LPAREN() {
  return getToken(JavaScript_simpleParser::LPAREN, 0);
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::WhileStatementContext::expression() {
  return getRuleContext<JavaScript_simpleParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaScript_simpleParser::WhileStatementContext::RPAREN() {
  return getToken(JavaScript_simpleParser::RPAREN, 0);
}

JavaScript_simpleParser::StatementContext* JavaScript_simpleParser::WhileStatementContext::statement() {
  return getRuleContext<JavaScript_simpleParser::StatementContext>(0);
}


size_t JavaScript_simpleParser::WhileStatementContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleWhileStatement;
}

void JavaScript_simpleParser::WhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStatement(this);
}

void JavaScript_simpleParser::WhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStatement(this);
}


std::any JavaScript_simpleParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::WhileStatementContext* JavaScript_simpleParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, JavaScript_simpleParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    match(JavaScript_simpleParser::WHILE);
    setState(139);
    match(JavaScript_simpleParser::LPAREN);
    setState(140);
    expression();
    setState(141);
    match(JavaScript_simpleParser::RPAREN);
    setState(142);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

JavaScript_simpleParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::ReturnStatementContext::RETURN() {
  return getToken(JavaScript_simpleParser::RETURN, 0);
}

tree::TerminalNode* JavaScript_simpleParser::ReturnStatementContext::SEMICOLON() {
  return getToken(JavaScript_simpleParser::SEMICOLON, 0);
}

JavaScript_simpleParser::ExpressionContext* JavaScript_simpleParser::ReturnStatementContext::expression() {
  return getRuleContext<JavaScript_simpleParser::ExpressionContext>(0);
}


size_t JavaScript_simpleParser::ReturnStatementContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleReturnStatement;
}

void JavaScript_simpleParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void JavaScript_simpleParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


std::any JavaScript_simpleParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::ReturnStatementContext* JavaScript_simpleParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, JavaScript_simpleParser::RuleReturnStatement);
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
    setState(144);
    match(JavaScript_simpleParser::RETURN);
    setState(146);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0)) {
      setState(145);
      expression();
    }
    setState(148);
    match(JavaScript_simpleParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockStatementContext ------------------------------------------------------------------

JavaScript_simpleParser::BlockStatementContext::BlockStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScript_simpleParser::BlockStatementContext::LBRACE() {
  return getToken(JavaScript_simpleParser::LBRACE, 0);
}

tree::TerminalNode* JavaScript_simpleParser::BlockStatementContext::RBRACE() {
  return getToken(JavaScript_simpleParser::RBRACE, 0);
}

std::vector<JavaScript_simpleParser::StatementContext *> JavaScript_simpleParser::BlockStatementContext::statement() {
  return getRuleContexts<JavaScript_simpleParser::StatementContext>();
}

JavaScript_simpleParser::StatementContext* JavaScript_simpleParser::BlockStatementContext::statement(size_t i) {
  return getRuleContext<JavaScript_simpleParser::StatementContext>(i);
}


size_t JavaScript_simpleParser::BlockStatementContext::getRuleIndex() const {
  return JavaScript_simpleParser::RuleBlockStatement;
}

void JavaScript_simpleParser::BlockStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockStatement(this);
}

void JavaScript_simpleParser::BlockStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScript_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockStatement(this);
}


std::any JavaScript_simpleParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScript_simpleVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScript_simpleParser::BlockStatementContext* JavaScript_simpleParser::blockStatement() {
  BlockStatementContext *_localctx = _tracker.createInstance<BlockStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, JavaScript_simpleParser::RuleBlockStatement);
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
    setState(150);
    match(JavaScript_simpleParser::LBRACE);
    setState(154);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 65272) != 0)) {
      setState(151);
      statement();
      setState(156);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(157);
    match(JavaScript_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void JavaScript_simpleParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  javascript_simpleParserInitialize();
#else
  ::antlr4::internal::call_once(javascript_simpleParserOnceFlag, javascript_simpleParserInitialize);
#endif
}
