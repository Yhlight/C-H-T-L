
// Generated from grammars/chtljs/CHTLJS.g4 by ANTLR 4.13.1


#include "CHTLJSLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct CHTLJSLexerStaticData final {
  CHTLJSLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CHTLJSLexerStaticData(const CHTLJSLexerStaticData&) = delete;
  CHTLJSLexerStaticData(CHTLJSLexerStaticData&&) = delete;
  CHTLJSLexerStaticData& operator=(const CHTLJSLexerStaticData&) = delete;
  CHTLJSLexerStaticData& operator=(CHTLJSLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag chtljslexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CHTLJSLexerStaticData *chtljslexerLexerStaticData = nullptr;

void chtljslexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (chtljslexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(chtljslexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CHTLJSLexerStaticData>(
    std::vector<std::string>{
      "CHTL_SCRIPT", "CHTL_LISTEN", "CHTL_DELEGATE", "CHTL_ANIMATE", "CHTL_AT", 
      "CHTL_WHEN", "CHTL_BEGIN", "CHTL_END", "CHTL_LOOP", "CHTL_DIRECTION", 
      "CHTL_DELAY", "CHTL_CALLBACK", "CHTL_TARGET", "CHTL_EASING", "CHTL_DURATION", 
      "CHTL_DOUBLE_BRACE", "CHTL_DOUBLE_BRACE_CLOSE", "CHTL_ARROW"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'script'", "'listen'", "'delegate'", "'animate'", "'at'", "'when'", 
      "'begin'", "'end'", "'loop'", "'direction'", "'delay'", "'callback'", 
      "'target'", "'easing'", "'duration'", "'{{'", "'}}'", "'->'"
    },
    std::vector<std::string>{
      "", "CHTL_SCRIPT", "CHTL_LISTEN", "CHTL_DELEGATE", "CHTL_ANIMATE", 
      "CHTL_AT", "CHTL_WHEN", "CHTL_BEGIN", "CHTL_END", "CHTL_LOOP", "CHTL_DIRECTION", 
      "CHTL_DELAY", "CHTL_CALLBACK", "CHTL_TARGET", "CHTL_EASING", "CHTL_DURATION", 
      "CHTL_DOUBLE_BRACE", "CHTL_DOUBLE_BRACE_CLOSE", "CHTL_ARROW"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,18,148,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,
  	13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,
  	15,1,15,1,16,1,16,1,16,1,17,1,17,1,17,0,0,18,1,1,3,2,5,3,7,4,9,5,11,6,
  	13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,
  	1,0,0,147,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,
  	0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,
  	1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,
  	0,0,0,33,1,0,0,0,0,35,1,0,0,0,1,37,1,0,0,0,3,44,1,0,0,0,5,51,1,0,0,0,
  	7,60,1,0,0,0,9,68,1,0,0,0,11,71,1,0,0,0,13,76,1,0,0,0,15,82,1,0,0,0,17,
  	86,1,0,0,0,19,91,1,0,0,0,21,101,1,0,0,0,23,107,1,0,0,0,25,116,1,0,0,0,
  	27,123,1,0,0,0,29,130,1,0,0,0,31,139,1,0,0,0,33,142,1,0,0,0,35,145,1,
  	0,0,0,37,38,5,115,0,0,38,39,5,99,0,0,39,40,5,114,0,0,40,41,5,105,0,0,
  	41,42,5,112,0,0,42,43,5,116,0,0,43,2,1,0,0,0,44,45,5,108,0,0,45,46,5,
  	105,0,0,46,47,5,115,0,0,47,48,5,116,0,0,48,49,5,101,0,0,49,50,5,110,0,
  	0,50,4,1,0,0,0,51,52,5,100,0,0,52,53,5,101,0,0,53,54,5,108,0,0,54,55,
  	5,101,0,0,55,56,5,103,0,0,56,57,5,97,0,0,57,58,5,116,0,0,58,59,5,101,
  	0,0,59,6,1,0,0,0,60,61,5,97,0,0,61,62,5,110,0,0,62,63,5,105,0,0,63,64,
  	5,109,0,0,64,65,5,97,0,0,65,66,5,116,0,0,66,67,5,101,0,0,67,8,1,0,0,0,
  	68,69,5,97,0,0,69,70,5,116,0,0,70,10,1,0,0,0,71,72,5,119,0,0,72,73,5,
  	104,0,0,73,74,5,101,0,0,74,75,5,110,0,0,75,12,1,0,0,0,76,77,5,98,0,0,
  	77,78,5,101,0,0,78,79,5,103,0,0,79,80,5,105,0,0,80,81,5,110,0,0,81,14,
  	1,0,0,0,82,83,5,101,0,0,83,84,5,110,0,0,84,85,5,100,0,0,85,16,1,0,0,0,
  	86,87,5,108,0,0,87,88,5,111,0,0,88,89,5,111,0,0,89,90,5,112,0,0,90,18,
  	1,0,0,0,91,92,5,100,0,0,92,93,5,105,0,0,93,94,5,114,0,0,94,95,5,101,0,
  	0,95,96,5,99,0,0,96,97,5,116,0,0,97,98,5,105,0,0,98,99,5,111,0,0,99,100,
  	5,110,0,0,100,20,1,0,0,0,101,102,5,100,0,0,102,103,5,101,0,0,103,104,
  	5,108,0,0,104,105,5,97,0,0,105,106,5,121,0,0,106,22,1,0,0,0,107,108,5,
  	99,0,0,108,109,5,97,0,0,109,110,5,108,0,0,110,111,5,108,0,0,111,112,5,
  	98,0,0,112,113,5,97,0,0,113,114,5,99,0,0,114,115,5,107,0,0,115,24,1,0,
  	0,0,116,117,5,116,0,0,117,118,5,97,0,0,118,119,5,114,0,0,119,120,5,103,
  	0,0,120,121,5,101,0,0,121,122,5,116,0,0,122,26,1,0,0,0,123,124,5,101,
  	0,0,124,125,5,97,0,0,125,126,5,115,0,0,126,127,5,105,0,0,127,128,5,110,
  	0,0,128,129,5,103,0,0,129,28,1,0,0,0,130,131,5,100,0,0,131,132,5,117,
  	0,0,132,133,5,114,0,0,133,134,5,97,0,0,134,135,5,116,0,0,135,136,5,105,
  	0,0,136,137,5,111,0,0,137,138,5,110,0,0,138,30,1,0,0,0,139,140,5,123,
  	0,0,140,141,5,123,0,0,141,32,1,0,0,0,142,143,5,125,0,0,143,144,5,125,
  	0,0,144,34,1,0,0,0,145,146,5,45,0,0,146,147,5,62,0,0,147,36,1,0,0,0,1,
  	0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  chtljslexerLexerStaticData = staticData.release();
}

}

CHTLJSLexer::CHTLJSLexer(CharStream *input) : Lexer(input) {
  CHTLJSLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *chtljslexerLexerStaticData->atn, chtljslexerLexerStaticData->decisionToDFA, chtljslexerLexerStaticData->sharedContextCache);
}

CHTLJSLexer::~CHTLJSLexer() {
  delete _interpreter;
}

std::string CHTLJSLexer::getGrammarFileName() const {
  return "CHTLJS.g4";
}

const std::vector<std::string>& CHTLJSLexer::getRuleNames() const {
  return chtljslexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CHTLJSLexer::getChannelNames() const {
  return chtljslexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CHTLJSLexer::getModeNames() const {
  return chtljslexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CHTLJSLexer::getVocabulary() const {
  return chtljslexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CHTLJSLexer::getSerializedATN() const {
  return chtljslexerLexerStaticData->serializedATN;
}

const atn::ATN& CHTLJSLexer::getATN() const {
  return *chtljslexerLexerStaticData->atn;
}




void CHTLJSLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chtljslexerLexerInitialize();
#else
  ::antlr4::internal::call_once(chtljslexerLexerOnceFlag, chtljslexerLexerInitialize);
#endif
}
