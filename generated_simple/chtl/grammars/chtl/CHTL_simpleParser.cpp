
// Generated from grammars/chtl/CHTL_simple.g4 by ANTLR 4.13.1


#include "CHTL_simpleListener.h"
#include "CHTL_simpleVisitor.h"

#include "CHTL_simpleParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CHTL_simpleParserStaticData final {
  CHTL_simpleParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CHTL_simpleParserStaticData(const CHTL_simpleParserStaticData&) = delete;
  CHTL_simpleParserStaticData(CHTL_simpleParserStaticData&&) = delete;
  CHTL_simpleParserStaticData& operator=(const CHTL_simpleParserStaticData&) = delete;
  CHTL_simpleParserStaticData& operator=(CHTL_simpleParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag chtl_simpleParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CHTL_simpleParserStaticData *chtl_simpleParserStaticData = nullptr;

void chtl_simpleParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (chtl_simpleParserStaticData != nullptr) {
    return;
  }
#else
  assert(chtl_simpleParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CHTL_simpleParserStaticData>(
    std::vector<std::string>{
      "program", "statement", "elementStatement", "attributes", "attribute", 
      "elementContent", "textBlock", "styleBlock", "scriptBlock", "templateStatement", 
      "customStatement", "originStatement"
    },
    std::vector<std::string>{
      "", "", "", "'[Template]'", "'[Custom]'", "'[Origin]'", "'text'", 
      "'style'", "'script'", "'{'", "'}'", "';'", "':'", "'='", "'.'"
    },
    std::vector<std::string>{
      "", "WS", "COMMENT", "TEMPLATE", "CUSTOM", "ORIGIN", "TEXT", "STYLE", 
      "SCRIPT", "LBRACE", "RBRACE", "SEMICOLON", "COLON", "EQUALS", "DOT", 
      "IDENTIFIER", "NUMBER", "STRING"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,17,115,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,1,0,5,0,26,8,0,10,0,12,0,29,
  	9,0,1,1,1,1,1,1,1,1,3,1,35,8,1,1,2,1,2,3,2,39,8,2,1,2,1,2,1,2,1,2,3,2,
  	45,8,2,1,3,5,3,48,8,3,10,3,12,3,51,9,3,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,
  	5,1,5,5,5,62,8,5,10,5,12,5,65,9,5,1,6,1,6,1,6,5,6,70,8,6,10,6,12,6,73,
  	9,6,1,6,1,6,1,7,1,7,1,7,5,7,80,8,7,10,7,12,7,83,9,7,1,7,1,7,1,8,1,8,1,
  	8,5,8,90,8,8,10,8,12,8,93,9,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,
  	10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,0,0,12,0,2,
  	4,6,8,10,12,14,16,18,20,22,0,2,1,0,12,13,2,0,15,15,17,17,116,0,27,1,0,
  	0,0,2,34,1,0,0,0,4,36,1,0,0,0,6,49,1,0,0,0,8,52,1,0,0,0,10,63,1,0,0,0,
  	12,66,1,0,0,0,14,76,1,0,0,0,16,86,1,0,0,0,18,96,1,0,0,0,20,102,1,0,0,
  	0,22,108,1,0,0,0,24,26,3,2,1,0,25,24,1,0,0,0,26,29,1,0,0,0,27,25,1,0,
  	0,0,27,28,1,0,0,0,28,1,1,0,0,0,29,27,1,0,0,0,30,35,3,4,2,0,31,35,3,18,
  	9,0,32,35,3,20,10,0,33,35,3,22,11,0,34,30,1,0,0,0,34,31,1,0,0,0,34,32,
  	1,0,0,0,34,33,1,0,0,0,35,3,1,0,0,0,36,38,5,15,0,0,37,39,3,6,3,0,38,37,
  	1,0,0,0,38,39,1,0,0,0,39,44,1,0,0,0,40,41,5,9,0,0,41,42,3,10,5,0,42,43,
  	5,10,0,0,43,45,1,0,0,0,44,40,1,0,0,0,44,45,1,0,0,0,45,5,1,0,0,0,46,48,
  	3,8,4,0,47,46,1,0,0,0,48,51,1,0,0,0,49,47,1,0,0,0,49,50,1,0,0,0,50,7,
  	1,0,0,0,51,49,1,0,0,0,52,53,5,15,0,0,53,54,7,0,0,0,54,55,7,1,0,0,55,56,
  	5,11,0,0,56,9,1,0,0,0,57,62,3,4,2,0,58,62,3,12,6,0,59,62,3,14,7,0,60,
  	62,3,16,8,0,61,57,1,0,0,0,61,58,1,0,0,0,61,59,1,0,0,0,61,60,1,0,0,0,62,
  	65,1,0,0,0,63,61,1,0,0,0,63,64,1,0,0,0,64,11,1,0,0,0,65,63,1,0,0,0,66,
  	67,5,6,0,0,67,71,5,9,0,0,68,70,7,1,0,0,69,68,1,0,0,0,70,73,1,0,0,0,71,
  	69,1,0,0,0,71,72,1,0,0,0,72,74,1,0,0,0,73,71,1,0,0,0,74,75,5,10,0,0,75,
  	13,1,0,0,0,76,77,5,7,0,0,77,81,5,9,0,0,78,80,7,1,0,0,79,78,1,0,0,0,80,
  	83,1,0,0,0,81,79,1,0,0,0,81,82,1,0,0,0,82,84,1,0,0,0,83,81,1,0,0,0,84,
  	85,5,10,0,0,85,15,1,0,0,0,86,87,5,8,0,0,87,91,5,9,0,0,88,90,7,1,0,0,89,
  	88,1,0,0,0,90,93,1,0,0,0,91,89,1,0,0,0,91,92,1,0,0,0,92,94,1,0,0,0,93,
  	91,1,0,0,0,94,95,5,10,0,0,95,17,1,0,0,0,96,97,5,3,0,0,97,98,5,15,0,0,
  	98,99,5,9,0,0,99,100,3,10,5,0,100,101,5,10,0,0,101,19,1,0,0,0,102,103,
  	5,4,0,0,103,104,5,15,0,0,104,105,5,9,0,0,105,106,3,10,5,0,106,107,5,10,
  	0,0,107,21,1,0,0,0,108,109,5,5,0,0,109,110,5,15,0,0,110,111,5,9,0,0,111,
  	112,3,10,5,0,112,113,5,10,0,0,113,23,1,0,0,0,10,27,34,38,44,49,61,63,
  	71,81,91
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  chtl_simpleParserStaticData = staticData.release();
}

}

CHTL_simpleParser::CHTL_simpleParser(TokenStream *input) : CHTL_simpleParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CHTL_simpleParser::CHTL_simpleParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CHTL_simpleParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *chtl_simpleParserStaticData->atn, chtl_simpleParserStaticData->decisionToDFA, chtl_simpleParserStaticData->sharedContextCache, options);
}

CHTL_simpleParser::~CHTL_simpleParser() {
  delete _interpreter;
}

const atn::ATN& CHTL_simpleParser::getATN() const {
  return *chtl_simpleParserStaticData->atn;
}

std::string CHTL_simpleParser::getGrammarFileName() const {
  return "CHTL_simple.g4";
}

const std::vector<std::string>& CHTL_simpleParser::getRuleNames() const {
  return chtl_simpleParserStaticData->ruleNames;
}

const dfa::Vocabulary& CHTL_simpleParser::getVocabulary() const {
  return chtl_simpleParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CHTL_simpleParser::getSerializedATN() const {
  return chtl_simpleParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

CHTL_simpleParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTL_simpleParser::StatementContext *> CHTL_simpleParser::ProgramContext::statement() {
  return getRuleContexts<CHTL_simpleParser::StatementContext>();
}

CHTL_simpleParser::StatementContext* CHTL_simpleParser::ProgramContext::statement(size_t i) {
  return getRuleContext<CHTL_simpleParser::StatementContext>(i);
}


size_t CHTL_simpleParser::ProgramContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleProgram;
}

void CHTL_simpleParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void CHTL_simpleParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any CHTL_simpleParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::ProgramContext* CHTL_simpleParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CHTL_simpleParser::RuleProgram);
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
    setState(27);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 32824) != 0)) {
      setState(24);
      statement();
      setState(29);
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

CHTL_simpleParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTL_simpleParser::ElementStatementContext* CHTL_simpleParser::StatementContext::elementStatement() {
  return getRuleContext<CHTL_simpleParser::ElementStatementContext>(0);
}

CHTL_simpleParser::TemplateStatementContext* CHTL_simpleParser::StatementContext::templateStatement() {
  return getRuleContext<CHTL_simpleParser::TemplateStatementContext>(0);
}

CHTL_simpleParser::CustomStatementContext* CHTL_simpleParser::StatementContext::customStatement() {
  return getRuleContext<CHTL_simpleParser::CustomStatementContext>(0);
}

CHTL_simpleParser::OriginStatementContext* CHTL_simpleParser::StatementContext::originStatement() {
  return getRuleContext<CHTL_simpleParser::OriginStatementContext>(0);
}


size_t CHTL_simpleParser::StatementContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleStatement;
}

void CHTL_simpleParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void CHTL_simpleParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any CHTL_simpleParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::StatementContext* CHTL_simpleParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, CHTL_simpleParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(34);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTL_simpleParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(30);
        elementStatement();
        break;
      }

      case CHTL_simpleParser::TEMPLATE: {
        enterOuterAlt(_localctx, 2);
        setState(31);
        templateStatement();
        break;
      }

      case CHTL_simpleParser::CUSTOM: {
        enterOuterAlt(_localctx, 3);
        setState(32);
        customStatement();
        break;
      }

      case CHTL_simpleParser::ORIGIN: {
        enterOuterAlt(_localctx, 4);
        setState(33);
        originStatement();
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

//----------------- ElementStatementContext ------------------------------------------------------------------

CHTL_simpleParser::ElementStatementContext::ElementStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTL_simpleParser::ElementStatementContext::IDENTIFIER() {
  return getToken(CHTL_simpleParser::IDENTIFIER, 0);
}

CHTL_simpleParser::AttributesContext* CHTL_simpleParser::ElementStatementContext::attributes() {
  return getRuleContext<CHTL_simpleParser::AttributesContext>(0);
}

tree::TerminalNode* CHTL_simpleParser::ElementStatementContext::LBRACE() {
  return getToken(CHTL_simpleParser::LBRACE, 0);
}

CHTL_simpleParser::ElementContentContext* CHTL_simpleParser::ElementStatementContext::elementContent() {
  return getRuleContext<CHTL_simpleParser::ElementContentContext>(0);
}

tree::TerminalNode* CHTL_simpleParser::ElementStatementContext::RBRACE() {
  return getToken(CHTL_simpleParser::RBRACE, 0);
}


size_t CHTL_simpleParser::ElementStatementContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleElementStatement;
}

void CHTL_simpleParser::ElementStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementStatement(this);
}

void CHTL_simpleParser::ElementStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementStatement(this);
}


std::any CHTL_simpleParser::ElementStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitElementStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::ElementStatementContext* CHTL_simpleParser::elementStatement() {
  ElementStatementContext *_localctx = _tracker.createInstance<ElementStatementContext>(_ctx, getState());
  enterRule(_localctx, 4, CHTL_simpleParser::RuleElementStatement);
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
    setState(36);
    match(CHTL_simpleParser::IDENTIFIER);
    setState(38);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(37);
      attributes();
      break;
    }

    default:
      break;
    }
    setState(44);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTL_simpleParser::LBRACE) {
      setState(40);
      match(CHTL_simpleParser::LBRACE);
      setState(41);
      elementContent();
      setState(42);
      match(CHTL_simpleParser::RBRACE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributesContext ------------------------------------------------------------------

CHTL_simpleParser::AttributesContext::AttributesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTL_simpleParser::AttributeContext *> CHTL_simpleParser::AttributesContext::attribute() {
  return getRuleContexts<CHTL_simpleParser::AttributeContext>();
}

CHTL_simpleParser::AttributeContext* CHTL_simpleParser::AttributesContext::attribute(size_t i) {
  return getRuleContext<CHTL_simpleParser::AttributeContext>(i);
}


size_t CHTL_simpleParser::AttributesContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleAttributes;
}

void CHTL_simpleParser::AttributesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributes(this);
}

void CHTL_simpleParser::AttributesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributes(this);
}


std::any CHTL_simpleParser::AttributesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitAttributes(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::AttributesContext* CHTL_simpleParser::attributes() {
  AttributesContext *_localctx = _tracker.createInstance<AttributesContext>(_ctx, getState());
  enterRule(_localctx, 6, CHTL_simpleParser::RuleAttributes);

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
    setState(49);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(46);
        attribute(); 
      }
      setState(51);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeContext ------------------------------------------------------------------

CHTL_simpleParser::AttributeContext::AttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTL_simpleParser::AttributeContext::IDENTIFIER() {
  return getTokens(CHTL_simpleParser::IDENTIFIER);
}

tree::TerminalNode* CHTL_simpleParser::AttributeContext::IDENTIFIER(size_t i) {
  return getToken(CHTL_simpleParser::IDENTIFIER, i);
}

tree::TerminalNode* CHTL_simpleParser::AttributeContext::SEMICOLON() {
  return getToken(CHTL_simpleParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTL_simpleParser::AttributeContext::COLON() {
  return getToken(CHTL_simpleParser::COLON, 0);
}

tree::TerminalNode* CHTL_simpleParser::AttributeContext::EQUALS() {
  return getToken(CHTL_simpleParser::EQUALS, 0);
}

tree::TerminalNode* CHTL_simpleParser::AttributeContext::STRING() {
  return getToken(CHTL_simpleParser::STRING, 0);
}


size_t CHTL_simpleParser::AttributeContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleAttribute;
}

void CHTL_simpleParser::AttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttribute(this);
}

void CHTL_simpleParser::AttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttribute(this);
}


std::any CHTL_simpleParser::AttributeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitAttribute(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::AttributeContext* CHTL_simpleParser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 8, CHTL_simpleParser::RuleAttribute);
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
    setState(52);
    match(CHTL_simpleParser::IDENTIFIER);
    setState(53);
    _la = _input->LA(1);
    if (!(_la == CHTL_simpleParser::COLON

    || _la == CHTL_simpleParser::EQUALS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(54);
    _la = _input->LA(1);
    if (!(_la == CHTL_simpleParser::IDENTIFIER

    || _la == CHTL_simpleParser::STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(55);
    match(CHTL_simpleParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContentContext ------------------------------------------------------------------

CHTL_simpleParser::ElementContentContext::ElementContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTL_simpleParser::ElementStatementContext *> CHTL_simpleParser::ElementContentContext::elementStatement() {
  return getRuleContexts<CHTL_simpleParser::ElementStatementContext>();
}

CHTL_simpleParser::ElementStatementContext* CHTL_simpleParser::ElementContentContext::elementStatement(size_t i) {
  return getRuleContext<CHTL_simpleParser::ElementStatementContext>(i);
}

std::vector<CHTL_simpleParser::TextBlockContext *> CHTL_simpleParser::ElementContentContext::textBlock() {
  return getRuleContexts<CHTL_simpleParser::TextBlockContext>();
}

CHTL_simpleParser::TextBlockContext* CHTL_simpleParser::ElementContentContext::textBlock(size_t i) {
  return getRuleContext<CHTL_simpleParser::TextBlockContext>(i);
}

std::vector<CHTL_simpleParser::StyleBlockContext *> CHTL_simpleParser::ElementContentContext::styleBlock() {
  return getRuleContexts<CHTL_simpleParser::StyleBlockContext>();
}

CHTL_simpleParser::StyleBlockContext* CHTL_simpleParser::ElementContentContext::styleBlock(size_t i) {
  return getRuleContext<CHTL_simpleParser::StyleBlockContext>(i);
}

std::vector<CHTL_simpleParser::ScriptBlockContext *> CHTL_simpleParser::ElementContentContext::scriptBlock() {
  return getRuleContexts<CHTL_simpleParser::ScriptBlockContext>();
}

CHTL_simpleParser::ScriptBlockContext* CHTL_simpleParser::ElementContentContext::scriptBlock(size_t i) {
  return getRuleContext<CHTL_simpleParser::ScriptBlockContext>(i);
}


size_t CHTL_simpleParser::ElementContentContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleElementContent;
}

void CHTL_simpleParser::ElementContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementContent(this);
}

void CHTL_simpleParser::ElementContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementContent(this);
}


std::any CHTL_simpleParser::ElementContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitElementContent(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::ElementContentContext* CHTL_simpleParser::elementContent() {
  ElementContentContext *_localctx = _tracker.createInstance<ElementContentContext>(_ctx, getState());
  enterRule(_localctx, 10, CHTL_simpleParser::RuleElementContent);
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
    setState(63);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 33216) != 0)) {
      setState(61);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CHTL_simpleParser::IDENTIFIER: {
          setState(57);
          elementStatement();
          break;
        }

        case CHTL_simpleParser::TEXT: {
          setState(58);
          textBlock();
          break;
        }

        case CHTL_simpleParser::STYLE: {
          setState(59);
          styleBlock();
          break;
        }

        case CHTL_simpleParser::SCRIPT: {
          setState(60);
          scriptBlock();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(65);
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

//----------------- TextBlockContext ------------------------------------------------------------------

CHTL_simpleParser::TextBlockContext::TextBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTL_simpleParser::TextBlockContext::TEXT() {
  return getToken(CHTL_simpleParser::TEXT, 0);
}

tree::TerminalNode* CHTL_simpleParser::TextBlockContext::LBRACE() {
  return getToken(CHTL_simpleParser::LBRACE, 0);
}

tree::TerminalNode* CHTL_simpleParser::TextBlockContext::RBRACE() {
  return getToken(CHTL_simpleParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> CHTL_simpleParser::TextBlockContext::STRING() {
  return getTokens(CHTL_simpleParser::STRING);
}

tree::TerminalNode* CHTL_simpleParser::TextBlockContext::STRING(size_t i) {
  return getToken(CHTL_simpleParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTL_simpleParser::TextBlockContext::IDENTIFIER() {
  return getTokens(CHTL_simpleParser::IDENTIFIER);
}

tree::TerminalNode* CHTL_simpleParser::TextBlockContext::IDENTIFIER(size_t i) {
  return getToken(CHTL_simpleParser::IDENTIFIER, i);
}


size_t CHTL_simpleParser::TextBlockContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleTextBlock;
}

void CHTL_simpleParser::TextBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextBlock(this);
}

void CHTL_simpleParser::TextBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextBlock(this);
}


std::any CHTL_simpleParser::TextBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitTextBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::TextBlockContext* CHTL_simpleParser::textBlock() {
  TextBlockContext *_localctx = _tracker.createInstance<TextBlockContext>(_ctx, getState());
  enterRule(_localctx, 12, CHTL_simpleParser::RuleTextBlock);
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
    setState(66);
    match(CHTL_simpleParser::TEXT);
    setState(67);
    match(CHTL_simpleParser::LBRACE);
    setState(71);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTL_simpleParser::IDENTIFIER

    || _la == CHTL_simpleParser::STRING) {
      setState(68);
      _la = _input->LA(1);
      if (!(_la == CHTL_simpleParser::IDENTIFIER

      || _la == CHTL_simpleParser::STRING)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(73);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(74);
    match(CHTL_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StyleBlockContext ------------------------------------------------------------------

CHTL_simpleParser::StyleBlockContext::StyleBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTL_simpleParser::StyleBlockContext::STYLE() {
  return getToken(CHTL_simpleParser::STYLE, 0);
}

tree::TerminalNode* CHTL_simpleParser::StyleBlockContext::LBRACE() {
  return getToken(CHTL_simpleParser::LBRACE, 0);
}

tree::TerminalNode* CHTL_simpleParser::StyleBlockContext::RBRACE() {
  return getToken(CHTL_simpleParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> CHTL_simpleParser::StyleBlockContext::STRING() {
  return getTokens(CHTL_simpleParser::STRING);
}

tree::TerminalNode* CHTL_simpleParser::StyleBlockContext::STRING(size_t i) {
  return getToken(CHTL_simpleParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTL_simpleParser::StyleBlockContext::IDENTIFIER() {
  return getTokens(CHTL_simpleParser::IDENTIFIER);
}

tree::TerminalNode* CHTL_simpleParser::StyleBlockContext::IDENTIFIER(size_t i) {
  return getToken(CHTL_simpleParser::IDENTIFIER, i);
}


size_t CHTL_simpleParser::StyleBlockContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleStyleBlock;
}

void CHTL_simpleParser::StyleBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyleBlock(this);
}

void CHTL_simpleParser::StyleBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyleBlock(this);
}


std::any CHTL_simpleParser::StyleBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitStyleBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::StyleBlockContext* CHTL_simpleParser::styleBlock() {
  StyleBlockContext *_localctx = _tracker.createInstance<StyleBlockContext>(_ctx, getState());
  enterRule(_localctx, 14, CHTL_simpleParser::RuleStyleBlock);
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
    setState(76);
    match(CHTL_simpleParser::STYLE);
    setState(77);
    match(CHTL_simpleParser::LBRACE);
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTL_simpleParser::IDENTIFIER

    || _la == CHTL_simpleParser::STRING) {
      setState(78);
      _la = _input->LA(1);
      if (!(_la == CHTL_simpleParser::IDENTIFIER

      || _la == CHTL_simpleParser::STRING)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(84);
    match(CHTL_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptBlockContext ------------------------------------------------------------------

CHTL_simpleParser::ScriptBlockContext::ScriptBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTL_simpleParser::ScriptBlockContext::SCRIPT() {
  return getToken(CHTL_simpleParser::SCRIPT, 0);
}

tree::TerminalNode* CHTL_simpleParser::ScriptBlockContext::LBRACE() {
  return getToken(CHTL_simpleParser::LBRACE, 0);
}

tree::TerminalNode* CHTL_simpleParser::ScriptBlockContext::RBRACE() {
  return getToken(CHTL_simpleParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> CHTL_simpleParser::ScriptBlockContext::STRING() {
  return getTokens(CHTL_simpleParser::STRING);
}

tree::TerminalNode* CHTL_simpleParser::ScriptBlockContext::STRING(size_t i) {
  return getToken(CHTL_simpleParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTL_simpleParser::ScriptBlockContext::IDENTIFIER() {
  return getTokens(CHTL_simpleParser::IDENTIFIER);
}

tree::TerminalNode* CHTL_simpleParser::ScriptBlockContext::IDENTIFIER(size_t i) {
  return getToken(CHTL_simpleParser::IDENTIFIER, i);
}


size_t CHTL_simpleParser::ScriptBlockContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleScriptBlock;
}

void CHTL_simpleParser::ScriptBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScriptBlock(this);
}

void CHTL_simpleParser::ScriptBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScriptBlock(this);
}


std::any CHTL_simpleParser::ScriptBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitScriptBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::ScriptBlockContext* CHTL_simpleParser::scriptBlock() {
  ScriptBlockContext *_localctx = _tracker.createInstance<ScriptBlockContext>(_ctx, getState());
  enterRule(_localctx, 16, CHTL_simpleParser::RuleScriptBlock);
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
    setState(86);
    match(CHTL_simpleParser::SCRIPT);
    setState(87);
    match(CHTL_simpleParser::LBRACE);
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTL_simpleParser::IDENTIFIER

    || _la == CHTL_simpleParser::STRING) {
      setState(88);
      _la = _input->LA(1);
      if (!(_la == CHTL_simpleParser::IDENTIFIER

      || _la == CHTL_simpleParser::STRING)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(93);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(94);
    match(CHTL_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateStatementContext ------------------------------------------------------------------

CHTL_simpleParser::TemplateStatementContext::TemplateStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTL_simpleParser::TemplateStatementContext::TEMPLATE() {
  return getToken(CHTL_simpleParser::TEMPLATE, 0);
}

tree::TerminalNode* CHTL_simpleParser::TemplateStatementContext::IDENTIFIER() {
  return getToken(CHTL_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTL_simpleParser::TemplateStatementContext::LBRACE() {
  return getToken(CHTL_simpleParser::LBRACE, 0);
}

CHTL_simpleParser::ElementContentContext* CHTL_simpleParser::TemplateStatementContext::elementContent() {
  return getRuleContext<CHTL_simpleParser::ElementContentContext>(0);
}

tree::TerminalNode* CHTL_simpleParser::TemplateStatementContext::RBRACE() {
  return getToken(CHTL_simpleParser::RBRACE, 0);
}


size_t CHTL_simpleParser::TemplateStatementContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleTemplateStatement;
}

void CHTL_simpleParser::TemplateStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateStatement(this);
}

void CHTL_simpleParser::TemplateStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateStatement(this);
}


std::any CHTL_simpleParser::TemplateStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitTemplateStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::TemplateStatementContext* CHTL_simpleParser::templateStatement() {
  TemplateStatementContext *_localctx = _tracker.createInstance<TemplateStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, CHTL_simpleParser::RuleTemplateStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(CHTL_simpleParser::TEMPLATE);
    setState(97);
    match(CHTL_simpleParser::IDENTIFIER);
    setState(98);
    match(CHTL_simpleParser::LBRACE);
    setState(99);
    elementContent();
    setState(100);
    match(CHTL_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomStatementContext ------------------------------------------------------------------

CHTL_simpleParser::CustomStatementContext::CustomStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTL_simpleParser::CustomStatementContext::CUSTOM() {
  return getToken(CHTL_simpleParser::CUSTOM, 0);
}

tree::TerminalNode* CHTL_simpleParser::CustomStatementContext::IDENTIFIER() {
  return getToken(CHTL_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTL_simpleParser::CustomStatementContext::LBRACE() {
  return getToken(CHTL_simpleParser::LBRACE, 0);
}

CHTL_simpleParser::ElementContentContext* CHTL_simpleParser::CustomStatementContext::elementContent() {
  return getRuleContext<CHTL_simpleParser::ElementContentContext>(0);
}

tree::TerminalNode* CHTL_simpleParser::CustomStatementContext::RBRACE() {
  return getToken(CHTL_simpleParser::RBRACE, 0);
}


size_t CHTL_simpleParser::CustomStatementContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleCustomStatement;
}

void CHTL_simpleParser::CustomStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomStatement(this);
}

void CHTL_simpleParser::CustomStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomStatement(this);
}


std::any CHTL_simpleParser::CustomStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitCustomStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::CustomStatementContext* CHTL_simpleParser::customStatement() {
  CustomStatementContext *_localctx = _tracker.createInstance<CustomStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, CHTL_simpleParser::RuleCustomStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    match(CHTL_simpleParser::CUSTOM);
    setState(103);
    match(CHTL_simpleParser::IDENTIFIER);
    setState(104);
    match(CHTL_simpleParser::LBRACE);
    setState(105);
    elementContent();
    setState(106);
    match(CHTL_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OriginStatementContext ------------------------------------------------------------------

CHTL_simpleParser::OriginStatementContext::OriginStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTL_simpleParser::OriginStatementContext::ORIGIN() {
  return getToken(CHTL_simpleParser::ORIGIN, 0);
}

tree::TerminalNode* CHTL_simpleParser::OriginStatementContext::IDENTIFIER() {
  return getToken(CHTL_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTL_simpleParser::OriginStatementContext::LBRACE() {
  return getToken(CHTL_simpleParser::LBRACE, 0);
}

CHTL_simpleParser::ElementContentContext* CHTL_simpleParser::OriginStatementContext::elementContent() {
  return getRuleContext<CHTL_simpleParser::ElementContentContext>(0);
}

tree::TerminalNode* CHTL_simpleParser::OriginStatementContext::RBRACE() {
  return getToken(CHTL_simpleParser::RBRACE, 0);
}


size_t CHTL_simpleParser::OriginStatementContext::getRuleIndex() const {
  return CHTL_simpleParser::RuleOriginStatement;
}

void CHTL_simpleParser::OriginStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOriginStatement(this);
}

void CHTL_simpleParser::OriginStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTL_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOriginStatement(this);
}


std::any CHTL_simpleParser::OriginStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTL_simpleVisitor*>(visitor))
    return parserVisitor->visitOriginStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTL_simpleParser::OriginStatementContext* CHTL_simpleParser::originStatement() {
  OriginStatementContext *_localctx = _tracker.createInstance<OriginStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, CHTL_simpleParser::RuleOriginStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    match(CHTL_simpleParser::ORIGIN);
    setState(109);
    match(CHTL_simpleParser::IDENTIFIER);
    setState(110);
    match(CHTL_simpleParser::LBRACE);
    setState(111);
    elementContent();
    setState(112);
    match(CHTL_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void CHTL_simpleParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chtl_simpleParserInitialize();
#else
  ::antlr4::internal::call_once(chtl_simpleParserOnceFlag, chtl_simpleParserInitialize);
#endif
}
