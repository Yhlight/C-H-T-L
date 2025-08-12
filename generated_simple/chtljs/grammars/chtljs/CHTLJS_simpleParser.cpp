
// Generated from grammars/chtljs/CHTLJS_simple.g4 by ANTLR 4.13.1


#include "CHTLJS_simpleListener.h"
#include "CHTLJS_simpleVisitor.h"

#include "CHTLJS_simpleParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CHTLJS_simpleParserStaticData final {
  CHTLJS_simpleParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CHTLJS_simpleParserStaticData(const CHTLJS_simpleParserStaticData&) = delete;
  CHTLJS_simpleParserStaticData(CHTLJS_simpleParserStaticData&&) = delete;
  CHTLJS_simpleParserStaticData& operator=(const CHTLJS_simpleParserStaticData&) = delete;
  CHTLJS_simpleParserStaticData& operator=(CHTLJS_simpleParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag chtljs_simpleParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CHTLJS_simpleParserStaticData *chtljs_simpleParserStaticData = nullptr;

void chtljs_simpleParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (chtljs_simpleParserStaticData != nullptr) {
    return;
  }
#else
  assert(chtljs_simpleParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CHTLJS_simpleParserStaticData>(
    std::vector<std::string>{
      "chtlScriptBlock", "chtlScriptContent", "chtlStatement", "chtlSelectorStatement", 
      "chtlSelector", "selectorContent", "chtlListenStatement", "chtlListenObject", 
      "chtlListenEvents", "chtlListenEvent", "eventType", "eventHandler", 
      "chtlDelegateStatement", "chtlDelegateObject", "chtlDelegateConfig", 
      "chtlTargetConfig", "chtlEventConfig", "chtlAnimateStatement", "chtlAnimateObject", 
      "chtlAnimateConfig", "chtlAnimateProperty", "chtlDuration", "chtlEasing", 
      "easingValue", "chtlBegin", "chtlEnd", "chtlCssProperties", "chtlCssProperty", 
      "propertyName", "propertyValue", "methodCall", "arguments", "argumentList", 
      "basicStatement"
    },
    std::vector<std::string>{
      "", "", "", "'script'", "'listen'", "'delegate'", "'animate'", "'{{'", 
      "'}}'", "'->'", "", "", "", "'{'", "'}'", "'('", "')'", "';'", "':'", 
      "','", "'.'", "'#'"
    },
    std::vector<std::string>{
      "", "WS", "COMMENT", "CHTL_SCRIPT", "CHTL_LISTEN", "CHTL_DELEGATE", 
      "CHTL_ANIMATE", "CHTL_DOUBLE_BRACE", "CHTL_DOUBLE_BRACE_CLOSE", "CHTL_ARROW", 
      "IDENTIFIER", "NUMBER", "STRING", "LBRACE", "RBRACE", "LPAREN", "RPAREN", 
      "SEMICOLON", "COLON", "COMMA", "DOT", "HASH"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,21,231,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,1,0,1,0,1,0,1,0,
  	1,0,1,1,1,1,5,1,76,8,1,10,1,12,1,79,9,1,1,2,1,2,1,2,1,2,3,2,85,8,2,1,
  	3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,3,5,96,8,5,1,5,1,5,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,5,8,114,8,8,10,8,12,8,117,9,8,
  	1,9,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,
  	1,17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,19,1,19,1,19,5,19,160,
  	8,19,10,19,12,19,163,9,19,1,20,1,20,1,20,1,20,3,20,169,8,20,1,21,1,21,
  	1,21,1,21,1,22,1,22,1,22,1,22,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,
  	1,25,1,25,1,25,1,25,1,25,1,25,1,26,5,26,194,8,26,10,26,12,26,197,9,26,
  	1,27,1,27,1,27,1,27,1,27,1,28,1,28,1,29,5,29,207,8,29,10,29,12,29,210,
  	9,29,1,30,1,30,1,30,3,30,215,8,30,1,30,1,30,1,31,1,31,1,32,1,32,1,32,
  	5,32,224,8,32,10,32,12,32,227,9,32,1,33,1,33,1,33,0,0,34,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,
  	58,60,62,64,66,0,3,1,0,20,21,2,0,10,10,12,12,1,0,10,12,211,0,68,1,0,0,
  	0,2,77,1,0,0,0,4,84,1,0,0,0,6,86,1,0,0,0,8,90,1,0,0,0,10,95,1,0,0,0,12,
  	99,1,0,0,0,14,106,1,0,0,0,16,110,1,0,0,0,18,118,1,0,0,0,20,122,1,0,0,
  	0,22,124,1,0,0,0,24,126,1,0,0,0,26,133,1,0,0,0,28,137,1,0,0,0,30,141,
  	1,0,0,0,32,145,1,0,0,0,34,147,1,0,0,0,36,152,1,0,0,0,38,156,1,0,0,0,40,
  	168,1,0,0,0,42,170,1,0,0,0,44,174,1,0,0,0,46,178,1,0,0,0,48,180,1,0,0,
  	0,50,186,1,0,0,0,52,195,1,0,0,0,54,198,1,0,0,0,56,203,1,0,0,0,58,208,
  	1,0,0,0,60,211,1,0,0,0,62,218,1,0,0,0,64,220,1,0,0,0,66,228,1,0,0,0,68,
  	69,5,3,0,0,69,70,5,13,0,0,70,71,3,2,1,0,71,72,5,14,0,0,72,1,1,0,0,0,73,
  	76,3,4,2,0,74,76,3,66,33,0,75,73,1,0,0,0,75,74,1,0,0,0,76,79,1,0,0,0,
  	77,75,1,0,0,0,77,78,1,0,0,0,78,3,1,0,0,0,79,77,1,0,0,0,80,85,3,6,3,0,
  	81,85,3,12,6,0,82,85,3,24,12,0,83,85,3,34,17,0,84,80,1,0,0,0,84,81,1,
  	0,0,0,84,82,1,0,0,0,84,83,1,0,0,0,85,5,1,0,0,0,86,87,3,8,4,0,87,88,5,
  	20,0,0,88,89,3,60,30,0,89,7,1,0,0,0,90,91,5,7,0,0,91,92,3,10,5,0,92,93,
  	5,8,0,0,93,9,1,0,0,0,94,96,7,0,0,0,95,94,1,0,0,0,95,96,1,0,0,0,96,97,
  	1,0,0,0,97,98,5,10,0,0,98,11,1,0,0,0,99,100,3,8,4,0,100,101,5,20,0,0,
  	101,102,5,4,0,0,102,103,5,15,0,0,103,104,3,14,7,0,104,105,5,16,0,0,105,
  	13,1,0,0,0,106,107,5,13,0,0,107,108,3,16,8,0,108,109,5,14,0,0,109,15,
  	1,0,0,0,110,115,3,18,9,0,111,112,5,19,0,0,112,114,3,18,9,0,113,111,1,
  	0,0,0,114,117,1,0,0,0,115,113,1,0,0,0,115,116,1,0,0,0,116,17,1,0,0,0,
  	117,115,1,0,0,0,118,119,3,20,10,0,119,120,5,18,0,0,120,121,3,22,11,0,
  	121,19,1,0,0,0,122,123,5,10,0,0,123,21,1,0,0,0,124,125,7,1,0,0,125,23,
  	1,0,0,0,126,127,3,8,4,0,127,128,5,20,0,0,128,129,5,5,0,0,129,130,5,15,
  	0,0,130,131,3,26,13,0,131,132,5,16,0,0,132,25,1,0,0,0,133,134,5,13,0,
  	0,134,135,3,28,14,0,135,136,5,14,0,0,136,27,1,0,0,0,137,138,3,30,15,0,
  	138,139,5,19,0,0,139,140,3,32,16,0,140,29,1,0,0,0,141,142,5,10,0,0,142,
  	143,5,18,0,0,143,144,3,8,4,0,144,31,1,0,0,0,145,146,3,16,8,0,146,33,1,
  	0,0,0,147,148,5,6,0,0,148,149,5,15,0,0,149,150,3,36,18,0,150,151,5,16,
  	0,0,151,35,1,0,0,0,152,153,5,13,0,0,153,154,3,38,19,0,154,155,5,14,0,
  	0,155,37,1,0,0,0,156,161,3,40,20,0,157,158,5,19,0,0,158,160,3,40,20,0,
  	159,157,1,0,0,0,160,163,1,0,0,0,161,159,1,0,0,0,161,162,1,0,0,0,162,39,
  	1,0,0,0,163,161,1,0,0,0,164,169,3,42,21,0,165,169,3,44,22,0,166,169,3,
  	48,24,0,167,169,3,50,25,0,168,164,1,0,0,0,168,165,1,0,0,0,168,166,1,0,
  	0,0,168,167,1,0,0,0,169,41,1,0,0,0,170,171,5,10,0,0,171,172,5,18,0,0,
  	172,173,5,11,0,0,173,43,1,0,0,0,174,175,5,10,0,0,175,176,5,18,0,0,176,
  	177,3,46,23,0,177,45,1,0,0,0,178,179,7,1,0,0,179,47,1,0,0,0,180,181,5,
  	10,0,0,181,182,5,18,0,0,182,183,5,13,0,0,183,184,3,52,26,0,184,185,5,
  	14,0,0,185,49,1,0,0,0,186,187,5,10,0,0,187,188,5,18,0,0,188,189,5,13,
  	0,0,189,190,3,52,26,0,190,191,5,14,0,0,191,51,1,0,0,0,192,194,3,54,27,
  	0,193,192,1,0,0,0,194,197,1,0,0,0,195,193,1,0,0,0,195,196,1,0,0,0,196,
  	53,1,0,0,0,197,195,1,0,0,0,198,199,3,56,28,0,199,200,5,18,0,0,200,201,
  	3,58,29,0,201,202,5,17,0,0,202,55,1,0,0,0,203,204,5,10,0,0,204,57,1,0,
  	0,0,205,207,7,2,0,0,206,205,1,0,0,0,207,210,1,0,0,0,208,206,1,0,0,0,208,
  	209,1,0,0,0,209,59,1,0,0,0,210,208,1,0,0,0,211,212,5,10,0,0,212,214,5,
  	15,0,0,213,215,3,62,31,0,214,213,1,0,0,0,214,215,1,0,0,0,215,216,1,0,
  	0,0,216,217,5,16,0,0,217,61,1,0,0,0,218,219,3,64,32,0,219,63,1,0,0,0,
  	220,225,7,2,0,0,221,222,5,19,0,0,222,224,7,2,0,0,223,221,1,0,0,0,224,
  	227,1,0,0,0,225,223,1,0,0,0,225,226,1,0,0,0,226,65,1,0,0,0,227,225,1,
  	0,0,0,228,229,7,2,0,0,229,67,1,0,0,0,11,75,77,84,95,115,161,168,195,208,
  	214,225
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  chtljs_simpleParserStaticData = staticData.release();
}

}

CHTLJS_simpleParser::CHTLJS_simpleParser(TokenStream *input) : CHTLJS_simpleParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CHTLJS_simpleParser::CHTLJS_simpleParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CHTLJS_simpleParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *chtljs_simpleParserStaticData->atn, chtljs_simpleParserStaticData->decisionToDFA, chtljs_simpleParserStaticData->sharedContextCache, options);
}

CHTLJS_simpleParser::~CHTLJS_simpleParser() {
  delete _interpreter;
}

const atn::ATN& CHTLJS_simpleParser::getATN() const {
  return *chtljs_simpleParserStaticData->atn;
}

std::string CHTLJS_simpleParser::getGrammarFileName() const {
  return "CHTLJS_simple.g4";
}

const std::vector<std::string>& CHTLJS_simpleParser::getRuleNames() const {
  return chtljs_simpleParserStaticData->ruleNames;
}

const dfa::Vocabulary& CHTLJS_simpleParser::getVocabulary() const {
  return chtljs_simpleParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CHTLJS_simpleParser::getSerializedATN() const {
  return chtljs_simpleParserStaticData->serializedATN;
}


//----------------- ChtlScriptBlockContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlScriptBlockContext::ChtlScriptBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlScriptBlockContext::CHTL_SCRIPT() {
  return getToken(CHTLJS_simpleParser::CHTL_SCRIPT, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlScriptBlockContext::LBRACE() {
  return getToken(CHTLJS_simpleParser::LBRACE, 0);
}

CHTLJS_simpleParser::ChtlScriptContentContext* CHTLJS_simpleParser::ChtlScriptBlockContext::chtlScriptContent() {
  return getRuleContext<CHTLJS_simpleParser::ChtlScriptContentContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlScriptBlockContext::RBRACE() {
  return getToken(CHTLJS_simpleParser::RBRACE, 0);
}


size_t CHTLJS_simpleParser::ChtlScriptBlockContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlScriptBlock;
}

void CHTLJS_simpleParser::ChtlScriptBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlScriptBlock(this);
}

void CHTLJS_simpleParser::ChtlScriptBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlScriptBlock(this);
}


std::any CHTLJS_simpleParser::ChtlScriptBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlScriptBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlScriptBlockContext* CHTLJS_simpleParser::chtlScriptBlock() {
  ChtlScriptBlockContext *_localctx = _tracker.createInstance<ChtlScriptBlockContext>(_ctx, getState());
  enterRule(_localctx, 0, CHTLJS_simpleParser::RuleChtlScriptBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    match(CHTLJS_simpleParser::CHTL_SCRIPT);
    setState(69);
    match(CHTLJS_simpleParser::LBRACE);
    setState(70);
    chtlScriptContent();
    setState(71);
    match(CHTLJS_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlScriptContentContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlScriptContentContext::ChtlScriptContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJS_simpleParser::ChtlStatementContext *> CHTLJS_simpleParser::ChtlScriptContentContext::chtlStatement() {
  return getRuleContexts<CHTLJS_simpleParser::ChtlStatementContext>();
}

CHTLJS_simpleParser::ChtlStatementContext* CHTLJS_simpleParser::ChtlScriptContentContext::chtlStatement(size_t i) {
  return getRuleContext<CHTLJS_simpleParser::ChtlStatementContext>(i);
}

std::vector<CHTLJS_simpleParser::BasicStatementContext *> CHTLJS_simpleParser::ChtlScriptContentContext::basicStatement() {
  return getRuleContexts<CHTLJS_simpleParser::BasicStatementContext>();
}

CHTLJS_simpleParser::BasicStatementContext* CHTLJS_simpleParser::ChtlScriptContentContext::basicStatement(size_t i) {
  return getRuleContext<CHTLJS_simpleParser::BasicStatementContext>(i);
}


size_t CHTLJS_simpleParser::ChtlScriptContentContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlScriptContent;
}

void CHTLJS_simpleParser::ChtlScriptContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlScriptContent(this);
}

void CHTLJS_simpleParser::ChtlScriptContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlScriptContent(this);
}


std::any CHTLJS_simpleParser::ChtlScriptContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlScriptContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlScriptContentContext* CHTLJS_simpleParser::chtlScriptContent() {
  ChtlScriptContentContext *_localctx = _tracker.createInstance<ChtlScriptContentContext>(_ctx, getState());
  enterRule(_localctx, 2, CHTLJS_simpleParser::RuleChtlScriptContent);
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
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7360) != 0)) {
      setState(75);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CHTLJS_simpleParser::CHTL_ANIMATE:
        case CHTLJS_simpleParser::CHTL_DOUBLE_BRACE: {
          setState(73);
          chtlStatement();
          break;
        }

        case CHTLJS_simpleParser::IDENTIFIER:
        case CHTLJS_simpleParser::NUMBER:
        case CHTLJS_simpleParser::STRING: {
          setState(74);
          basicStatement();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
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

//----------------- ChtlStatementContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlStatementContext::ChtlStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::ChtlSelectorStatementContext* CHTLJS_simpleParser::ChtlStatementContext::chtlSelectorStatement() {
  return getRuleContext<CHTLJS_simpleParser::ChtlSelectorStatementContext>(0);
}

CHTLJS_simpleParser::ChtlListenStatementContext* CHTLJS_simpleParser::ChtlStatementContext::chtlListenStatement() {
  return getRuleContext<CHTLJS_simpleParser::ChtlListenStatementContext>(0);
}

CHTLJS_simpleParser::ChtlDelegateStatementContext* CHTLJS_simpleParser::ChtlStatementContext::chtlDelegateStatement() {
  return getRuleContext<CHTLJS_simpleParser::ChtlDelegateStatementContext>(0);
}

CHTLJS_simpleParser::ChtlAnimateStatementContext* CHTLJS_simpleParser::ChtlStatementContext::chtlAnimateStatement() {
  return getRuleContext<CHTLJS_simpleParser::ChtlAnimateStatementContext>(0);
}


size_t CHTLJS_simpleParser::ChtlStatementContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlStatement;
}

void CHTLJS_simpleParser::ChtlStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlStatement(this);
}

void CHTLJS_simpleParser::ChtlStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlStatement(this);
}


std::any CHTLJS_simpleParser::ChtlStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlStatementContext* CHTLJS_simpleParser::chtlStatement() {
  ChtlStatementContext *_localctx = _tracker.createInstance<ChtlStatementContext>(_ctx, getState());
  enterRule(_localctx, 4, CHTLJS_simpleParser::RuleChtlStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(84);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(80);
      chtlSelectorStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(81);
      chtlListenStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(82);
      chtlDelegateStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(83);
      chtlAnimateStatement();
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

//----------------- ChtlSelectorStatementContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlSelectorStatementContext::ChtlSelectorStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::ChtlSelectorContext* CHTLJS_simpleParser::ChtlSelectorStatementContext::chtlSelector() {
  return getRuleContext<CHTLJS_simpleParser::ChtlSelectorContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlSelectorStatementContext::DOT() {
  return getToken(CHTLJS_simpleParser::DOT, 0);
}

CHTLJS_simpleParser::MethodCallContext* CHTLJS_simpleParser::ChtlSelectorStatementContext::methodCall() {
  return getRuleContext<CHTLJS_simpleParser::MethodCallContext>(0);
}


size_t CHTLJS_simpleParser::ChtlSelectorStatementContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlSelectorStatement;
}

void CHTLJS_simpleParser::ChtlSelectorStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlSelectorStatement(this);
}

void CHTLJS_simpleParser::ChtlSelectorStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlSelectorStatement(this);
}


std::any CHTLJS_simpleParser::ChtlSelectorStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlSelectorStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlSelectorStatementContext* CHTLJS_simpleParser::chtlSelectorStatement() {
  ChtlSelectorStatementContext *_localctx = _tracker.createInstance<ChtlSelectorStatementContext>(_ctx, getState());
  enterRule(_localctx, 6, CHTLJS_simpleParser::RuleChtlSelectorStatement);

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
    chtlSelector();
    setState(87);
    match(CHTLJS_simpleParser::DOT);
    setState(88);
    methodCall();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlSelectorContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlSelectorContext::ChtlSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlSelectorContext::CHTL_DOUBLE_BRACE() {
  return getToken(CHTLJS_simpleParser::CHTL_DOUBLE_BRACE, 0);
}

CHTLJS_simpleParser::SelectorContentContext* CHTLJS_simpleParser::ChtlSelectorContext::selectorContent() {
  return getRuleContext<CHTLJS_simpleParser::SelectorContentContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlSelectorContext::CHTL_DOUBLE_BRACE_CLOSE() {
  return getToken(CHTLJS_simpleParser::CHTL_DOUBLE_BRACE_CLOSE, 0);
}


size_t CHTLJS_simpleParser::ChtlSelectorContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlSelector;
}

void CHTLJS_simpleParser::ChtlSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlSelector(this);
}

void CHTLJS_simpleParser::ChtlSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlSelector(this);
}


std::any CHTLJS_simpleParser::ChtlSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlSelector(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlSelectorContext* CHTLJS_simpleParser::chtlSelector() {
  ChtlSelectorContext *_localctx = _tracker.createInstance<ChtlSelectorContext>(_ctx, getState());
  enterRule(_localctx, 8, CHTLJS_simpleParser::RuleChtlSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    match(CHTLJS_simpleParser::CHTL_DOUBLE_BRACE);
    setState(91);
    selectorContent();
    setState(92);
    match(CHTLJS_simpleParser::CHTL_DOUBLE_BRACE_CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorContentContext ------------------------------------------------------------------

CHTLJS_simpleParser::SelectorContentContext::SelectorContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::SelectorContentContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::SelectorContentContext::DOT() {
  return getToken(CHTLJS_simpleParser::DOT, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::SelectorContentContext::HASH() {
  return getToken(CHTLJS_simpleParser::HASH, 0);
}


size_t CHTLJS_simpleParser::SelectorContentContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleSelectorContent;
}

void CHTLJS_simpleParser::SelectorContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectorContent(this);
}

void CHTLJS_simpleParser::SelectorContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectorContent(this);
}


std::any CHTLJS_simpleParser::SelectorContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitSelectorContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::SelectorContentContext* CHTLJS_simpleParser::selectorContent() {
  SelectorContentContext *_localctx = _tracker.createInstance<SelectorContentContext>(_ctx, getState());
  enterRule(_localctx, 10, CHTLJS_simpleParser::RuleSelectorContent);
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
    setState(95);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJS_simpleParser::DOT

    || _la == CHTLJS_simpleParser::HASH) {
      setState(94);
      _la = _input->LA(1);
      if (!(_la == CHTLJS_simpleParser::DOT

      || _la == CHTLJS_simpleParser::HASH)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(97);
    match(CHTLJS_simpleParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlListenStatementContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlListenStatementContext::ChtlListenStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::ChtlSelectorContext* CHTLJS_simpleParser::ChtlListenStatementContext::chtlSelector() {
  return getRuleContext<CHTLJS_simpleParser::ChtlSelectorContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlListenStatementContext::DOT() {
  return getToken(CHTLJS_simpleParser::DOT, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlListenStatementContext::CHTL_LISTEN() {
  return getToken(CHTLJS_simpleParser::CHTL_LISTEN, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlListenStatementContext::LPAREN() {
  return getToken(CHTLJS_simpleParser::LPAREN, 0);
}

CHTLJS_simpleParser::ChtlListenObjectContext* CHTLJS_simpleParser::ChtlListenStatementContext::chtlListenObject() {
  return getRuleContext<CHTLJS_simpleParser::ChtlListenObjectContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlListenStatementContext::RPAREN() {
  return getToken(CHTLJS_simpleParser::RPAREN, 0);
}


size_t CHTLJS_simpleParser::ChtlListenStatementContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlListenStatement;
}

void CHTLJS_simpleParser::ChtlListenStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlListenStatement(this);
}

void CHTLJS_simpleParser::ChtlListenStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlListenStatement(this);
}


std::any CHTLJS_simpleParser::ChtlListenStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlListenStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlListenStatementContext* CHTLJS_simpleParser::chtlListenStatement() {
  ChtlListenStatementContext *_localctx = _tracker.createInstance<ChtlListenStatementContext>(_ctx, getState());
  enterRule(_localctx, 12, CHTLJS_simpleParser::RuleChtlListenStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99);
    chtlSelector();
    setState(100);
    match(CHTLJS_simpleParser::DOT);
    setState(101);
    match(CHTLJS_simpleParser::CHTL_LISTEN);
    setState(102);
    match(CHTLJS_simpleParser::LPAREN);
    setState(103);
    chtlListenObject();
    setState(104);
    match(CHTLJS_simpleParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlListenObjectContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlListenObjectContext::ChtlListenObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlListenObjectContext::LBRACE() {
  return getToken(CHTLJS_simpleParser::LBRACE, 0);
}

CHTLJS_simpleParser::ChtlListenEventsContext* CHTLJS_simpleParser::ChtlListenObjectContext::chtlListenEvents() {
  return getRuleContext<CHTLJS_simpleParser::ChtlListenEventsContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlListenObjectContext::RBRACE() {
  return getToken(CHTLJS_simpleParser::RBRACE, 0);
}


size_t CHTLJS_simpleParser::ChtlListenObjectContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlListenObject;
}

void CHTLJS_simpleParser::ChtlListenObjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlListenObject(this);
}

void CHTLJS_simpleParser::ChtlListenObjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlListenObject(this);
}


std::any CHTLJS_simpleParser::ChtlListenObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlListenObject(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlListenObjectContext* CHTLJS_simpleParser::chtlListenObject() {
  ChtlListenObjectContext *_localctx = _tracker.createInstance<ChtlListenObjectContext>(_ctx, getState());
  enterRule(_localctx, 14, CHTLJS_simpleParser::RuleChtlListenObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    match(CHTLJS_simpleParser::LBRACE);
    setState(107);
    chtlListenEvents();
    setState(108);
    match(CHTLJS_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlListenEventsContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlListenEventsContext::ChtlListenEventsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJS_simpleParser::ChtlListenEventContext *> CHTLJS_simpleParser::ChtlListenEventsContext::chtlListenEvent() {
  return getRuleContexts<CHTLJS_simpleParser::ChtlListenEventContext>();
}

CHTLJS_simpleParser::ChtlListenEventContext* CHTLJS_simpleParser::ChtlListenEventsContext::chtlListenEvent(size_t i) {
  return getRuleContext<CHTLJS_simpleParser::ChtlListenEventContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::ChtlListenEventsContext::COMMA() {
  return getTokens(CHTLJS_simpleParser::COMMA);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlListenEventsContext::COMMA(size_t i) {
  return getToken(CHTLJS_simpleParser::COMMA, i);
}


size_t CHTLJS_simpleParser::ChtlListenEventsContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlListenEvents;
}

void CHTLJS_simpleParser::ChtlListenEventsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlListenEvents(this);
}

void CHTLJS_simpleParser::ChtlListenEventsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlListenEvents(this);
}


std::any CHTLJS_simpleParser::ChtlListenEventsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlListenEvents(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlListenEventsContext* CHTLJS_simpleParser::chtlListenEvents() {
  ChtlListenEventsContext *_localctx = _tracker.createInstance<ChtlListenEventsContext>(_ctx, getState());
  enterRule(_localctx, 16, CHTLJS_simpleParser::RuleChtlListenEvents);
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
    setState(110);
    chtlListenEvent();
    setState(115);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJS_simpleParser::COMMA) {
      setState(111);
      match(CHTLJS_simpleParser::COMMA);
      setState(112);
      chtlListenEvent();
      setState(117);
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

//----------------- ChtlListenEventContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlListenEventContext::ChtlListenEventContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::EventTypeContext* CHTLJS_simpleParser::ChtlListenEventContext::eventType() {
  return getRuleContext<CHTLJS_simpleParser::EventTypeContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlListenEventContext::COLON() {
  return getToken(CHTLJS_simpleParser::COLON, 0);
}

CHTLJS_simpleParser::EventHandlerContext* CHTLJS_simpleParser::ChtlListenEventContext::eventHandler() {
  return getRuleContext<CHTLJS_simpleParser::EventHandlerContext>(0);
}


size_t CHTLJS_simpleParser::ChtlListenEventContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlListenEvent;
}

void CHTLJS_simpleParser::ChtlListenEventContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlListenEvent(this);
}

void CHTLJS_simpleParser::ChtlListenEventContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlListenEvent(this);
}


std::any CHTLJS_simpleParser::ChtlListenEventContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlListenEvent(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlListenEventContext* CHTLJS_simpleParser::chtlListenEvent() {
  ChtlListenEventContext *_localctx = _tracker.createInstance<ChtlListenEventContext>(_ctx, getState());
  enterRule(_localctx, 18, CHTLJS_simpleParser::RuleChtlListenEvent);

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
    eventType();
    setState(119);
    match(CHTLJS_simpleParser::COLON);
    setState(120);
    eventHandler();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EventTypeContext ------------------------------------------------------------------

CHTLJS_simpleParser::EventTypeContext::EventTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::EventTypeContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}


size_t CHTLJS_simpleParser::EventTypeContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleEventType;
}

void CHTLJS_simpleParser::EventTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEventType(this);
}

void CHTLJS_simpleParser::EventTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEventType(this);
}


std::any CHTLJS_simpleParser::EventTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitEventType(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::EventTypeContext* CHTLJS_simpleParser::eventType() {
  EventTypeContext *_localctx = _tracker.createInstance<EventTypeContext>(_ctx, getState());
  enterRule(_localctx, 20, CHTLJS_simpleParser::RuleEventType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(CHTLJS_simpleParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EventHandlerContext ------------------------------------------------------------------

CHTLJS_simpleParser::EventHandlerContext::EventHandlerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::EventHandlerContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::EventHandlerContext::STRING() {
  return getToken(CHTLJS_simpleParser::STRING, 0);
}


size_t CHTLJS_simpleParser::EventHandlerContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleEventHandler;
}

void CHTLJS_simpleParser::EventHandlerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEventHandler(this);
}

void CHTLJS_simpleParser::EventHandlerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEventHandler(this);
}


std::any CHTLJS_simpleParser::EventHandlerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitEventHandler(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::EventHandlerContext* CHTLJS_simpleParser::eventHandler() {
  EventHandlerContext *_localctx = _tracker.createInstance<EventHandlerContext>(_ctx, getState());
  enterRule(_localctx, 22, CHTLJS_simpleParser::RuleEventHandler);
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
    setState(124);
    _la = _input->LA(1);
    if (!(_la == CHTLJS_simpleParser::IDENTIFIER

    || _la == CHTLJS_simpleParser::STRING)) {
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

//----------------- ChtlDelegateStatementContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlDelegateStatementContext::ChtlDelegateStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::ChtlSelectorContext* CHTLJS_simpleParser::ChtlDelegateStatementContext::chtlSelector() {
  return getRuleContext<CHTLJS_simpleParser::ChtlSelectorContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDelegateStatementContext::DOT() {
  return getToken(CHTLJS_simpleParser::DOT, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDelegateStatementContext::CHTL_DELEGATE() {
  return getToken(CHTLJS_simpleParser::CHTL_DELEGATE, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDelegateStatementContext::LPAREN() {
  return getToken(CHTLJS_simpleParser::LPAREN, 0);
}

CHTLJS_simpleParser::ChtlDelegateObjectContext* CHTLJS_simpleParser::ChtlDelegateStatementContext::chtlDelegateObject() {
  return getRuleContext<CHTLJS_simpleParser::ChtlDelegateObjectContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDelegateStatementContext::RPAREN() {
  return getToken(CHTLJS_simpleParser::RPAREN, 0);
}


size_t CHTLJS_simpleParser::ChtlDelegateStatementContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlDelegateStatement;
}

void CHTLJS_simpleParser::ChtlDelegateStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDelegateStatement(this);
}

void CHTLJS_simpleParser::ChtlDelegateStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDelegateStatement(this);
}


std::any CHTLJS_simpleParser::ChtlDelegateStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlDelegateStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlDelegateStatementContext* CHTLJS_simpleParser::chtlDelegateStatement() {
  ChtlDelegateStatementContext *_localctx = _tracker.createInstance<ChtlDelegateStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, CHTLJS_simpleParser::RuleChtlDelegateStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    chtlSelector();
    setState(127);
    match(CHTLJS_simpleParser::DOT);
    setState(128);
    match(CHTLJS_simpleParser::CHTL_DELEGATE);
    setState(129);
    match(CHTLJS_simpleParser::LPAREN);
    setState(130);
    chtlDelegateObject();
    setState(131);
    match(CHTLJS_simpleParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDelegateObjectContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlDelegateObjectContext::ChtlDelegateObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDelegateObjectContext::LBRACE() {
  return getToken(CHTLJS_simpleParser::LBRACE, 0);
}

CHTLJS_simpleParser::ChtlDelegateConfigContext* CHTLJS_simpleParser::ChtlDelegateObjectContext::chtlDelegateConfig() {
  return getRuleContext<CHTLJS_simpleParser::ChtlDelegateConfigContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDelegateObjectContext::RBRACE() {
  return getToken(CHTLJS_simpleParser::RBRACE, 0);
}


size_t CHTLJS_simpleParser::ChtlDelegateObjectContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlDelegateObject;
}

void CHTLJS_simpleParser::ChtlDelegateObjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDelegateObject(this);
}

void CHTLJS_simpleParser::ChtlDelegateObjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDelegateObject(this);
}


std::any CHTLJS_simpleParser::ChtlDelegateObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlDelegateObject(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlDelegateObjectContext* CHTLJS_simpleParser::chtlDelegateObject() {
  ChtlDelegateObjectContext *_localctx = _tracker.createInstance<ChtlDelegateObjectContext>(_ctx, getState());
  enterRule(_localctx, 26, CHTLJS_simpleParser::RuleChtlDelegateObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    match(CHTLJS_simpleParser::LBRACE);
    setState(134);
    chtlDelegateConfig();
    setState(135);
    match(CHTLJS_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDelegateConfigContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlDelegateConfigContext::ChtlDelegateConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::ChtlTargetConfigContext* CHTLJS_simpleParser::ChtlDelegateConfigContext::chtlTargetConfig() {
  return getRuleContext<CHTLJS_simpleParser::ChtlTargetConfigContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDelegateConfigContext::COMMA() {
  return getToken(CHTLJS_simpleParser::COMMA, 0);
}

CHTLJS_simpleParser::ChtlEventConfigContext* CHTLJS_simpleParser::ChtlDelegateConfigContext::chtlEventConfig() {
  return getRuleContext<CHTLJS_simpleParser::ChtlEventConfigContext>(0);
}


size_t CHTLJS_simpleParser::ChtlDelegateConfigContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlDelegateConfig;
}

void CHTLJS_simpleParser::ChtlDelegateConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDelegateConfig(this);
}

void CHTLJS_simpleParser::ChtlDelegateConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDelegateConfig(this);
}


std::any CHTLJS_simpleParser::ChtlDelegateConfigContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlDelegateConfig(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlDelegateConfigContext* CHTLJS_simpleParser::chtlDelegateConfig() {
  ChtlDelegateConfigContext *_localctx = _tracker.createInstance<ChtlDelegateConfigContext>(_ctx, getState());
  enterRule(_localctx, 28, CHTLJS_simpleParser::RuleChtlDelegateConfig);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    chtlTargetConfig();
    setState(138);
    match(CHTLJS_simpleParser::COMMA);
    setState(139);
    chtlEventConfig();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlTargetConfigContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlTargetConfigContext::ChtlTargetConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlTargetConfigContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlTargetConfigContext::COLON() {
  return getToken(CHTLJS_simpleParser::COLON, 0);
}

CHTLJS_simpleParser::ChtlSelectorContext* CHTLJS_simpleParser::ChtlTargetConfigContext::chtlSelector() {
  return getRuleContext<CHTLJS_simpleParser::ChtlSelectorContext>(0);
}


size_t CHTLJS_simpleParser::ChtlTargetConfigContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlTargetConfig;
}

void CHTLJS_simpleParser::ChtlTargetConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlTargetConfig(this);
}

void CHTLJS_simpleParser::ChtlTargetConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlTargetConfig(this);
}


std::any CHTLJS_simpleParser::ChtlTargetConfigContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlTargetConfig(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlTargetConfigContext* CHTLJS_simpleParser::chtlTargetConfig() {
  ChtlTargetConfigContext *_localctx = _tracker.createInstance<ChtlTargetConfigContext>(_ctx, getState());
  enterRule(_localctx, 30, CHTLJS_simpleParser::RuleChtlTargetConfig);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
    match(CHTLJS_simpleParser::IDENTIFIER);
    setState(142);
    match(CHTLJS_simpleParser::COLON);
    setState(143);
    chtlSelector();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlEventConfigContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlEventConfigContext::ChtlEventConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::ChtlListenEventsContext* CHTLJS_simpleParser::ChtlEventConfigContext::chtlListenEvents() {
  return getRuleContext<CHTLJS_simpleParser::ChtlListenEventsContext>(0);
}


size_t CHTLJS_simpleParser::ChtlEventConfigContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlEventConfig;
}

void CHTLJS_simpleParser::ChtlEventConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlEventConfig(this);
}

void CHTLJS_simpleParser::ChtlEventConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlEventConfig(this);
}


std::any CHTLJS_simpleParser::ChtlEventConfigContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlEventConfig(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlEventConfigContext* CHTLJS_simpleParser::chtlEventConfig() {
  ChtlEventConfigContext *_localctx = _tracker.createInstance<ChtlEventConfigContext>(_ctx, getState());
  enterRule(_localctx, 32, CHTLJS_simpleParser::RuleChtlEventConfig);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    chtlListenEvents();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlAnimateStatementContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlAnimateStatementContext::ChtlAnimateStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlAnimateStatementContext::CHTL_ANIMATE() {
  return getToken(CHTLJS_simpleParser::CHTL_ANIMATE, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlAnimateStatementContext::LPAREN() {
  return getToken(CHTLJS_simpleParser::LPAREN, 0);
}

CHTLJS_simpleParser::ChtlAnimateObjectContext* CHTLJS_simpleParser::ChtlAnimateStatementContext::chtlAnimateObject() {
  return getRuleContext<CHTLJS_simpleParser::ChtlAnimateObjectContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlAnimateStatementContext::RPAREN() {
  return getToken(CHTLJS_simpleParser::RPAREN, 0);
}


size_t CHTLJS_simpleParser::ChtlAnimateStatementContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlAnimateStatement;
}

void CHTLJS_simpleParser::ChtlAnimateStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAnimateStatement(this);
}

void CHTLJS_simpleParser::ChtlAnimateStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAnimateStatement(this);
}


std::any CHTLJS_simpleParser::ChtlAnimateStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlAnimateStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlAnimateStatementContext* CHTLJS_simpleParser::chtlAnimateStatement() {
  ChtlAnimateStatementContext *_localctx = _tracker.createInstance<ChtlAnimateStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, CHTLJS_simpleParser::RuleChtlAnimateStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(CHTLJS_simpleParser::CHTL_ANIMATE);
    setState(148);
    match(CHTLJS_simpleParser::LPAREN);
    setState(149);
    chtlAnimateObject();
    setState(150);
    match(CHTLJS_simpleParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlAnimateObjectContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlAnimateObjectContext::ChtlAnimateObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlAnimateObjectContext::LBRACE() {
  return getToken(CHTLJS_simpleParser::LBRACE, 0);
}

CHTLJS_simpleParser::ChtlAnimateConfigContext* CHTLJS_simpleParser::ChtlAnimateObjectContext::chtlAnimateConfig() {
  return getRuleContext<CHTLJS_simpleParser::ChtlAnimateConfigContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlAnimateObjectContext::RBRACE() {
  return getToken(CHTLJS_simpleParser::RBRACE, 0);
}


size_t CHTLJS_simpleParser::ChtlAnimateObjectContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlAnimateObject;
}

void CHTLJS_simpleParser::ChtlAnimateObjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAnimateObject(this);
}

void CHTLJS_simpleParser::ChtlAnimateObjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAnimateObject(this);
}


std::any CHTLJS_simpleParser::ChtlAnimateObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlAnimateObject(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlAnimateObjectContext* CHTLJS_simpleParser::chtlAnimateObject() {
  ChtlAnimateObjectContext *_localctx = _tracker.createInstance<ChtlAnimateObjectContext>(_ctx, getState());
  enterRule(_localctx, 36, CHTLJS_simpleParser::RuleChtlAnimateObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    match(CHTLJS_simpleParser::LBRACE);
    setState(153);
    chtlAnimateConfig();
    setState(154);
    match(CHTLJS_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlAnimateConfigContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlAnimateConfigContext::ChtlAnimateConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJS_simpleParser::ChtlAnimatePropertyContext *> CHTLJS_simpleParser::ChtlAnimateConfigContext::chtlAnimateProperty() {
  return getRuleContexts<CHTLJS_simpleParser::ChtlAnimatePropertyContext>();
}

CHTLJS_simpleParser::ChtlAnimatePropertyContext* CHTLJS_simpleParser::ChtlAnimateConfigContext::chtlAnimateProperty(size_t i) {
  return getRuleContext<CHTLJS_simpleParser::ChtlAnimatePropertyContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::ChtlAnimateConfigContext::COMMA() {
  return getTokens(CHTLJS_simpleParser::COMMA);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlAnimateConfigContext::COMMA(size_t i) {
  return getToken(CHTLJS_simpleParser::COMMA, i);
}


size_t CHTLJS_simpleParser::ChtlAnimateConfigContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlAnimateConfig;
}

void CHTLJS_simpleParser::ChtlAnimateConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAnimateConfig(this);
}

void CHTLJS_simpleParser::ChtlAnimateConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAnimateConfig(this);
}


std::any CHTLJS_simpleParser::ChtlAnimateConfigContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlAnimateConfig(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlAnimateConfigContext* CHTLJS_simpleParser::chtlAnimateConfig() {
  ChtlAnimateConfigContext *_localctx = _tracker.createInstance<ChtlAnimateConfigContext>(_ctx, getState());
  enterRule(_localctx, 38, CHTLJS_simpleParser::RuleChtlAnimateConfig);
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
    setState(156);
    chtlAnimateProperty();
    setState(161);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJS_simpleParser::COMMA) {
      setState(157);
      match(CHTLJS_simpleParser::COMMA);
      setState(158);
      chtlAnimateProperty();
      setState(163);
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

//----------------- ChtlAnimatePropertyContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlAnimatePropertyContext::ChtlAnimatePropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::ChtlDurationContext* CHTLJS_simpleParser::ChtlAnimatePropertyContext::chtlDuration() {
  return getRuleContext<CHTLJS_simpleParser::ChtlDurationContext>(0);
}

CHTLJS_simpleParser::ChtlEasingContext* CHTLJS_simpleParser::ChtlAnimatePropertyContext::chtlEasing() {
  return getRuleContext<CHTLJS_simpleParser::ChtlEasingContext>(0);
}

CHTLJS_simpleParser::ChtlBeginContext* CHTLJS_simpleParser::ChtlAnimatePropertyContext::chtlBegin() {
  return getRuleContext<CHTLJS_simpleParser::ChtlBeginContext>(0);
}

CHTLJS_simpleParser::ChtlEndContext* CHTLJS_simpleParser::ChtlAnimatePropertyContext::chtlEnd() {
  return getRuleContext<CHTLJS_simpleParser::ChtlEndContext>(0);
}


size_t CHTLJS_simpleParser::ChtlAnimatePropertyContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlAnimateProperty;
}

void CHTLJS_simpleParser::ChtlAnimatePropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAnimateProperty(this);
}

void CHTLJS_simpleParser::ChtlAnimatePropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAnimateProperty(this);
}


std::any CHTLJS_simpleParser::ChtlAnimatePropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlAnimateProperty(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlAnimatePropertyContext* CHTLJS_simpleParser::chtlAnimateProperty() {
  ChtlAnimatePropertyContext *_localctx = _tracker.createInstance<ChtlAnimatePropertyContext>(_ctx, getState());
  enterRule(_localctx, 40, CHTLJS_simpleParser::RuleChtlAnimateProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(168);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(164);
      chtlDuration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(165);
      chtlEasing();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(166);
      chtlBegin();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(167);
      chtlEnd();
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

//----------------- ChtlDurationContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlDurationContext::ChtlDurationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDurationContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDurationContext::COLON() {
  return getToken(CHTLJS_simpleParser::COLON, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlDurationContext::NUMBER() {
  return getToken(CHTLJS_simpleParser::NUMBER, 0);
}


size_t CHTLJS_simpleParser::ChtlDurationContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlDuration;
}

void CHTLJS_simpleParser::ChtlDurationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDuration(this);
}

void CHTLJS_simpleParser::ChtlDurationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDuration(this);
}


std::any CHTLJS_simpleParser::ChtlDurationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlDuration(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlDurationContext* CHTLJS_simpleParser::chtlDuration() {
  ChtlDurationContext *_localctx = _tracker.createInstance<ChtlDurationContext>(_ctx, getState());
  enterRule(_localctx, 42, CHTLJS_simpleParser::RuleChtlDuration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(CHTLJS_simpleParser::IDENTIFIER);
    setState(171);
    match(CHTLJS_simpleParser::COLON);
    setState(172);
    match(CHTLJS_simpleParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlEasingContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlEasingContext::ChtlEasingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlEasingContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlEasingContext::COLON() {
  return getToken(CHTLJS_simpleParser::COLON, 0);
}

CHTLJS_simpleParser::EasingValueContext* CHTLJS_simpleParser::ChtlEasingContext::easingValue() {
  return getRuleContext<CHTLJS_simpleParser::EasingValueContext>(0);
}


size_t CHTLJS_simpleParser::ChtlEasingContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlEasing;
}

void CHTLJS_simpleParser::ChtlEasingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlEasing(this);
}

void CHTLJS_simpleParser::ChtlEasingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlEasing(this);
}


std::any CHTLJS_simpleParser::ChtlEasingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlEasing(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlEasingContext* CHTLJS_simpleParser::chtlEasing() {
  ChtlEasingContext *_localctx = _tracker.createInstance<ChtlEasingContext>(_ctx, getState());
  enterRule(_localctx, 44, CHTLJS_simpleParser::RuleChtlEasing);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    match(CHTLJS_simpleParser::IDENTIFIER);
    setState(175);
    match(CHTLJS_simpleParser::COLON);
    setState(176);
    easingValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EasingValueContext ------------------------------------------------------------------

CHTLJS_simpleParser::EasingValueContext::EasingValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::EasingValueContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::EasingValueContext::STRING() {
  return getToken(CHTLJS_simpleParser::STRING, 0);
}


size_t CHTLJS_simpleParser::EasingValueContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleEasingValue;
}

void CHTLJS_simpleParser::EasingValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEasingValue(this);
}

void CHTLJS_simpleParser::EasingValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEasingValue(this);
}


std::any CHTLJS_simpleParser::EasingValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitEasingValue(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::EasingValueContext* CHTLJS_simpleParser::easingValue() {
  EasingValueContext *_localctx = _tracker.createInstance<EasingValueContext>(_ctx, getState());
  enterRule(_localctx, 46, CHTLJS_simpleParser::RuleEasingValue);
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
    setState(178);
    _la = _input->LA(1);
    if (!(_la == CHTLJS_simpleParser::IDENTIFIER

    || _la == CHTLJS_simpleParser::STRING)) {
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

//----------------- ChtlBeginContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlBeginContext::ChtlBeginContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlBeginContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlBeginContext::COLON() {
  return getToken(CHTLJS_simpleParser::COLON, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlBeginContext::LBRACE() {
  return getToken(CHTLJS_simpleParser::LBRACE, 0);
}

CHTLJS_simpleParser::ChtlCssPropertiesContext* CHTLJS_simpleParser::ChtlBeginContext::chtlCssProperties() {
  return getRuleContext<CHTLJS_simpleParser::ChtlCssPropertiesContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlBeginContext::RBRACE() {
  return getToken(CHTLJS_simpleParser::RBRACE, 0);
}


size_t CHTLJS_simpleParser::ChtlBeginContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlBegin;
}

void CHTLJS_simpleParser::ChtlBeginContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlBegin(this);
}

void CHTLJS_simpleParser::ChtlBeginContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlBegin(this);
}


std::any CHTLJS_simpleParser::ChtlBeginContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlBegin(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlBeginContext* CHTLJS_simpleParser::chtlBegin() {
  ChtlBeginContext *_localctx = _tracker.createInstance<ChtlBeginContext>(_ctx, getState());
  enterRule(_localctx, 48, CHTLJS_simpleParser::RuleChtlBegin);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    match(CHTLJS_simpleParser::IDENTIFIER);
    setState(181);
    match(CHTLJS_simpleParser::COLON);
    setState(182);
    match(CHTLJS_simpleParser::LBRACE);
    setState(183);
    chtlCssProperties();
    setState(184);
    match(CHTLJS_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlEndContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlEndContext::ChtlEndContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlEndContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlEndContext::COLON() {
  return getToken(CHTLJS_simpleParser::COLON, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlEndContext::LBRACE() {
  return getToken(CHTLJS_simpleParser::LBRACE, 0);
}

CHTLJS_simpleParser::ChtlCssPropertiesContext* CHTLJS_simpleParser::ChtlEndContext::chtlCssProperties() {
  return getRuleContext<CHTLJS_simpleParser::ChtlCssPropertiesContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlEndContext::RBRACE() {
  return getToken(CHTLJS_simpleParser::RBRACE, 0);
}


size_t CHTLJS_simpleParser::ChtlEndContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlEnd;
}

void CHTLJS_simpleParser::ChtlEndContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlEnd(this);
}

void CHTLJS_simpleParser::ChtlEndContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlEnd(this);
}


std::any CHTLJS_simpleParser::ChtlEndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlEnd(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlEndContext* CHTLJS_simpleParser::chtlEnd() {
  ChtlEndContext *_localctx = _tracker.createInstance<ChtlEndContext>(_ctx, getState());
  enterRule(_localctx, 50, CHTLJS_simpleParser::RuleChtlEnd);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    match(CHTLJS_simpleParser::IDENTIFIER);
    setState(187);
    match(CHTLJS_simpleParser::COLON);
    setState(188);
    match(CHTLJS_simpleParser::LBRACE);
    setState(189);
    chtlCssProperties();
    setState(190);
    match(CHTLJS_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlCssPropertiesContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlCssPropertiesContext::ChtlCssPropertiesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJS_simpleParser::ChtlCssPropertyContext *> CHTLJS_simpleParser::ChtlCssPropertiesContext::chtlCssProperty() {
  return getRuleContexts<CHTLJS_simpleParser::ChtlCssPropertyContext>();
}

CHTLJS_simpleParser::ChtlCssPropertyContext* CHTLJS_simpleParser::ChtlCssPropertiesContext::chtlCssProperty(size_t i) {
  return getRuleContext<CHTLJS_simpleParser::ChtlCssPropertyContext>(i);
}


size_t CHTLJS_simpleParser::ChtlCssPropertiesContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlCssProperties;
}

void CHTLJS_simpleParser::ChtlCssPropertiesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlCssProperties(this);
}

void CHTLJS_simpleParser::ChtlCssPropertiesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlCssProperties(this);
}


std::any CHTLJS_simpleParser::ChtlCssPropertiesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlCssProperties(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlCssPropertiesContext* CHTLJS_simpleParser::chtlCssProperties() {
  ChtlCssPropertiesContext *_localctx = _tracker.createInstance<ChtlCssPropertiesContext>(_ctx, getState());
  enterRule(_localctx, 52, CHTLJS_simpleParser::RuleChtlCssProperties);
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
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJS_simpleParser::IDENTIFIER) {
      setState(192);
      chtlCssProperty();
      setState(197);
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

//----------------- ChtlCssPropertyContext ------------------------------------------------------------------

CHTLJS_simpleParser::ChtlCssPropertyContext::ChtlCssPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::PropertyNameContext* CHTLJS_simpleParser::ChtlCssPropertyContext::propertyName() {
  return getRuleContext<CHTLJS_simpleParser::PropertyNameContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlCssPropertyContext::COLON() {
  return getToken(CHTLJS_simpleParser::COLON, 0);
}

CHTLJS_simpleParser::PropertyValueContext* CHTLJS_simpleParser::ChtlCssPropertyContext::propertyValue() {
  return getRuleContext<CHTLJS_simpleParser::PropertyValueContext>(0);
}

tree::TerminalNode* CHTLJS_simpleParser::ChtlCssPropertyContext::SEMICOLON() {
  return getToken(CHTLJS_simpleParser::SEMICOLON, 0);
}


size_t CHTLJS_simpleParser::ChtlCssPropertyContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleChtlCssProperty;
}

void CHTLJS_simpleParser::ChtlCssPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlCssProperty(this);
}

void CHTLJS_simpleParser::ChtlCssPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlCssProperty(this);
}


std::any CHTLJS_simpleParser::ChtlCssPropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitChtlCssProperty(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ChtlCssPropertyContext* CHTLJS_simpleParser::chtlCssProperty() {
  ChtlCssPropertyContext *_localctx = _tracker.createInstance<ChtlCssPropertyContext>(_ctx, getState());
  enterRule(_localctx, 54, CHTLJS_simpleParser::RuleChtlCssProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(198);
    propertyName();
    setState(199);
    match(CHTLJS_simpleParser::COLON);
    setState(200);
    propertyValue();
    setState(201);
    match(CHTLJS_simpleParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyNameContext ------------------------------------------------------------------

CHTLJS_simpleParser::PropertyNameContext::PropertyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::PropertyNameContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}


size_t CHTLJS_simpleParser::PropertyNameContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RulePropertyName;
}

void CHTLJS_simpleParser::PropertyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyName(this);
}

void CHTLJS_simpleParser::PropertyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyName(this);
}


std::any CHTLJS_simpleParser::PropertyNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitPropertyName(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::PropertyNameContext* CHTLJS_simpleParser::propertyName() {
  PropertyNameContext *_localctx = _tracker.createInstance<PropertyNameContext>(_ctx, getState());
  enterRule(_localctx, 56, CHTLJS_simpleParser::RulePropertyName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    match(CHTLJS_simpleParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyValueContext ------------------------------------------------------------------

CHTLJS_simpleParser::PropertyValueContext::PropertyValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::PropertyValueContext::STRING() {
  return getTokens(CHTLJS_simpleParser::STRING);
}

tree::TerminalNode* CHTLJS_simpleParser::PropertyValueContext::STRING(size_t i) {
  return getToken(CHTLJS_simpleParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::PropertyValueContext::NUMBER() {
  return getTokens(CHTLJS_simpleParser::NUMBER);
}

tree::TerminalNode* CHTLJS_simpleParser::PropertyValueContext::NUMBER(size_t i) {
  return getToken(CHTLJS_simpleParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::PropertyValueContext::IDENTIFIER() {
  return getTokens(CHTLJS_simpleParser::IDENTIFIER);
}

tree::TerminalNode* CHTLJS_simpleParser::PropertyValueContext::IDENTIFIER(size_t i) {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, i);
}


size_t CHTLJS_simpleParser::PropertyValueContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RulePropertyValue;
}

void CHTLJS_simpleParser::PropertyValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyValue(this);
}

void CHTLJS_simpleParser::PropertyValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyValue(this);
}


std::any CHTLJS_simpleParser::PropertyValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitPropertyValue(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::PropertyValueContext* CHTLJS_simpleParser::propertyValue() {
  PropertyValueContext *_localctx = _tracker.createInstance<PropertyValueContext>(_ctx, getState());
  enterRule(_localctx, 58, CHTLJS_simpleParser::RulePropertyValue);
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
    setState(208);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7168) != 0)) {
      setState(205);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 7168) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(210);
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

//----------------- MethodCallContext ------------------------------------------------------------------

CHTLJS_simpleParser::MethodCallContext::MethodCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::MethodCallContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::MethodCallContext::LPAREN() {
  return getToken(CHTLJS_simpleParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::MethodCallContext::RPAREN() {
  return getToken(CHTLJS_simpleParser::RPAREN, 0);
}

CHTLJS_simpleParser::ArgumentsContext* CHTLJS_simpleParser::MethodCallContext::arguments() {
  return getRuleContext<CHTLJS_simpleParser::ArgumentsContext>(0);
}


size_t CHTLJS_simpleParser::MethodCallContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleMethodCall;
}

void CHTLJS_simpleParser::MethodCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodCall(this);
}

void CHTLJS_simpleParser::MethodCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodCall(this);
}


std::any CHTLJS_simpleParser::MethodCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitMethodCall(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::MethodCallContext* CHTLJS_simpleParser::methodCall() {
  MethodCallContext *_localctx = _tracker.createInstance<MethodCallContext>(_ctx, getState());
  enterRule(_localctx, 60, CHTLJS_simpleParser::RuleMethodCall);
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
    setState(211);
    match(CHTLJS_simpleParser::IDENTIFIER);
    setState(212);
    match(CHTLJS_simpleParser::LPAREN);
    setState(214);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7168) != 0)) {
      setState(213);
      arguments();
    }
    setState(216);
    match(CHTLJS_simpleParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

CHTLJS_simpleParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJS_simpleParser::ArgumentListContext* CHTLJS_simpleParser::ArgumentsContext::argumentList() {
  return getRuleContext<CHTLJS_simpleParser::ArgumentListContext>(0);
}


size_t CHTLJS_simpleParser::ArgumentsContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleArguments;
}

void CHTLJS_simpleParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void CHTLJS_simpleParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


std::any CHTLJS_simpleParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ArgumentsContext* CHTLJS_simpleParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 62, CHTLJS_simpleParser::RuleArguments);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
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

CHTLJS_simpleParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::ArgumentListContext::STRING() {
  return getTokens(CHTLJS_simpleParser::STRING);
}

tree::TerminalNode* CHTLJS_simpleParser::ArgumentListContext::STRING(size_t i) {
  return getToken(CHTLJS_simpleParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::ArgumentListContext::NUMBER() {
  return getTokens(CHTLJS_simpleParser::NUMBER);
}

tree::TerminalNode* CHTLJS_simpleParser::ArgumentListContext::NUMBER(size_t i) {
  return getToken(CHTLJS_simpleParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::ArgumentListContext::IDENTIFIER() {
  return getTokens(CHTLJS_simpleParser::IDENTIFIER);
}

tree::TerminalNode* CHTLJS_simpleParser::ArgumentListContext::IDENTIFIER(size_t i) {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> CHTLJS_simpleParser::ArgumentListContext::COMMA() {
  return getTokens(CHTLJS_simpleParser::COMMA);
}

tree::TerminalNode* CHTLJS_simpleParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(CHTLJS_simpleParser::COMMA, i);
}


size_t CHTLJS_simpleParser::ArgumentListContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleArgumentList;
}

void CHTLJS_simpleParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void CHTLJS_simpleParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}


std::any CHTLJS_simpleParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::ArgumentListContext* CHTLJS_simpleParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 64, CHTLJS_simpleParser::RuleArgumentList);
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
    setState(220);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7168) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(225);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJS_simpleParser::COMMA) {
      setState(221);
      match(CHTLJS_simpleParser::COMMA);
      setState(222);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 7168) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(227);
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

//----------------- BasicStatementContext ------------------------------------------------------------------

CHTLJS_simpleParser::BasicStatementContext::BasicStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJS_simpleParser::BasicStatementContext::IDENTIFIER() {
  return getToken(CHTLJS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::BasicStatementContext::STRING() {
  return getToken(CHTLJS_simpleParser::STRING, 0);
}

tree::TerminalNode* CHTLJS_simpleParser::BasicStatementContext::NUMBER() {
  return getToken(CHTLJS_simpleParser::NUMBER, 0);
}


size_t CHTLJS_simpleParser::BasicStatementContext::getRuleIndex() const {
  return CHTLJS_simpleParser::RuleBasicStatement;
}

void CHTLJS_simpleParser::BasicStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBasicStatement(this);
}

void CHTLJS_simpleParser::BasicStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBasicStatement(this);
}


std::any CHTLJS_simpleParser::BasicStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLJS_simpleVisitor*>(visitor))
    return parserVisitor->visitBasicStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLJS_simpleParser::BasicStatementContext* CHTLJS_simpleParser::basicStatement() {
  BasicStatementContext *_localctx = _tracker.createInstance<BasicStatementContext>(_ctx, getState());
  enterRule(_localctx, 66, CHTLJS_simpleParser::RuleBasicStatement);
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
    setState(228);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7168) != 0))) {
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

void CHTLJS_simpleParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chtljs_simpleParserInitialize();
#else
  ::antlr4::internal::call_once(chtljs_simpleParserOnceFlag, chtljs_simpleParserInitialize);
#endif
}
