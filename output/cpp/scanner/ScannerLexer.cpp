
// Generated from Scanner.g4 by ANTLR 4.13.1


#include "ScannerLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct ScannerLexerStaticData final {
  ScannerLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ScannerLexerStaticData(const ScannerLexerStaticData&) = delete;
  ScannerLexerStaticData(ScannerLexerStaticData&&) = delete;
  ScannerLexerStaticData& operator=(const ScannerLexerStaticData&) = delete;
  ScannerLexerStaticData& operator=(ScannerLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag scannerlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
ScannerLexerStaticData *scannerlexerLexerStaticData = nullptr;

void scannerlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (scannerlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(scannerlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ScannerLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "TEXT", "STYLE", "SCRIPT", "TEMPLATE_START", 
      "CUSTOM_START", "CONFIG_START", "NAMESPACE_START", "IMPORT_START", 
      "ORIGIN_START", "COLON_OR_EQUAL", "IDENTIFIER", "STRING_LITERAL", 
      "UNQUOTED_LITERAL", "ATTR_VALUE", "ANY_CONTENT", "WS", "COMMENT", 
      "MULTI_COMMENT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "';'", "'text'", "'style'", "'script'", "'[Template]'", 
      "'[Custom]'", "'[Configuration]'", "'[Namespace]'", "'[Import]'", 
      "'[Origin]'"
    },
    std::vector<std::string>{
      "", "", "", "", "TEXT", "STYLE", "SCRIPT", "TEMPLATE_START", "CUSTOM_START", 
      "CONFIG_START", "NAMESPACE_START", "IMPORT_START", "ORIGIN_START", 
      "COLON_OR_EQUAL", "IDENTIFIER", "STRING_LITERAL", "UNQUOTED_LITERAL", 
      "ATTR_VALUE", "ANY_CONTENT", "WS", "COMMENT", "MULTI_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,21,220,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,
  	1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,13,1,13,5,13,138,8,13,10,13,12,13,
  	141,9,13,1,14,1,14,1,14,1,14,5,14,147,8,14,10,14,12,14,150,9,14,1,14,
  	1,14,1,14,1,14,1,14,5,14,157,8,14,10,14,12,14,160,9,14,1,14,3,14,163,
  	8,14,1,15,4,15,166,8,15,11,15,12,15,167,1,15,5,15,171,8,15,10,15,12,15,
  	174,9,15,1,15,3,15,177,8,15,1,16,4,16,180,8,16,11,16,12,16,181,1,17,4,
  	17,185,8,17,11,17,12,17,186,1,18,4,18,190,8,18,11,18,12,18,191,1,18,1,
  	18,1,19,1,19,1,19,1,19,5,19,200,8,19,10,19,12,19,203,9,19,1,19,1,19,1,
  	20,1,20,1,20,1,20,5,20,211,8,20,10,20,12,20,214,9,20,1,20,1,20,1,20,1,
  	20,1,20,1,212,0,21,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,
  	23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,1,0,11,2,
  	0,58,58,61,61,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,4,0,
  	10,10,13,13,34,34,92,92,4,0,10,10,13,13,39,39,92,92,5,0,35,35,48,57,65,
  	90,95,95,97,122,7,0,35,35,40,41,45,45,48,58,65,90,95,95,97,122,3,0,10,
  	10,13,13,59,59,5,0,10,10,13,13,59,59,123,123,125,125,3,0,9,10,13,13,32,
  	32,2,0,10,10,13,13,233,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,
  	0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,
  	1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,
  	0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,
  	0,41,1,0,0,0,1,43,1,0,0,0,3,45,1,0,0,0,5,47,1,0,0,0,7,49,1,0,0,0,9,54,
  	1,0,0,0,11,60,1,0,0,0,13,67,1,0,0,0,15,78,1,0,0,0,17,87,1,0,0,0,19,103,
  	1,0,0,0,21,115,1,0,0,0,23,124,1,0,0,0,25,133,1,0,0,0,27,135,1,0,0,0,29,
  	162,1,0,0,0,31,165,1,0,0,0,33,179,1,0,0,0,35,184,1,0,0,0,37,189,1,0,0,
  	0,39,195,1,0,0,0,41,206,1,0,0,0,43,44,5,123,0,0,44,2,1,0,0,0,45,46,5,
  	125,0,0,46,4,1,0,0,0,47,48,5,59,0,0,48,6,1,0,0,0,49,50,5,116,0,0,50,51,
  	5,101,0,0,51,52,5,120,0,0,52,53,5,116,0,0,53,8,1,0,0,0,54,55,5,115,0,
  	0,55,56,5,116,0,0,56,57,5,121,0,0,57,58,5,108,0,0,58,59,5,101,0,0,59,
  	10,1,0,0,0,60,61,5,115,0,0,61,62,5,99,0,0,62,63,5,114,0,0,63,64,5,105,
  	0,0,64,65,5,112,0,0,65,66,5,116,0,0,66,12,1,0,0,0,67,68,5,91,0,0,68,69,
  	5,84,0,0,69,70,5,101,0,0,70,71,5,109,0,0,71,72,5,112,0,0,72,73,5,108,
  	0,0,73,74,5,97,0,0,74,75,5,116,0,0,75,76,5,101,0,0,76,77,5,93,0,0,77,
  	14,1,0,0,0,78,79,5,91,0,0,79,80,5,67,0,0,80,81,5,117,0,0,81,82,5,115,
  	0,0,82,83,5,116,0,0,83,84,5,111,0,0,84,85,5,109,0,0,85,86,5,93,0,0,86,
  	16,1,0,0,0,87,88,5,91,0,0,88,89,5,67,0,0,89,90,5,111,0,0,90,91,5,110,
  	0,0,91,92,5,102,0,0,92,93,5,105,0,0,93,94,5,103,0,0,94,95,5,117,0,0,95,
  	96,5,114,0,0,96,97,5,97,0,0,97,98,5,116,0,0,98,99,5,105,0,0,99,100,5,
  	111,0,0,100,101,5,110,0,0,101,102,5,93,0,0,102,18,1,0,0,0,103,104,5,91,
  	0,0,104,105,5,78,0,0,105,106,5,97,0,0,106,107,5,109,0,0,107,108,5,101,
  	0,0,108,109,5,115,0,0,109,110,5,112,0,0,110,111,5,97,0,0,111,112,5,99,
  	0,0,112,113,5,101,0,0,113,114,5,93,0,0,114,20,1,0,0,0,115,116,5,91,0,
  	0,116,117,5,73,0,0,117,118,5,109,0,0,118,119,5,112,0,0,119,120,5,111,
  	0,0,120,121,5,114,0,0,121,122,5,116,0,0,122,123,5,93,0,0,123,22,1,0,0,
  	0,124,125,5,91,0,0,125,126,5,79,0,0,126,127,5,114,0,0,127,128,5,105,0,
  	0,128,129,5,103,0,0,129,130,5,105,0,0,130,131,5,110,0,0,131,132,5,93,
  	0,0,132,24,1,0,0,0,133,134,7,0,0,0,134,26,1,0,0,0,135,139,7,1,0,0,136,
  	138,7,2,0,0,137,136,1,0,0,0,138,141,1,0,0,0,139,137,1,0,0,0,139,140,1,
  	0,0,0,140,28,1,0,0,0,141,139,1,0,0,0,142,148,5,34,0,0,143,147,8,3,0,0,
  	144,145,5,92,0,0,145,147,9,0,0,0,146,143,1,0,0,0,146,144,1,0,0,0,147,
  	150,1,0,0,0,148,146,1,0,0,0,148,149,1,0,0,0,149,151,1,0,0,0,150,148,1,
  	0,0,0,151,163,5,34,0,0,152,158,5,39,0,0,153,157,8,4,0,0,154,155,5,92,
  	0,0,155,157,9,0,0,0,156,153,1,0,0,0,156,154,1,0,0,0,157,160,1,0,0,0,158,
  	156,1,0,0,0,158,159,1,0,0,0,159,161,1,0,0,0,160,158,1,0,0,0,161,163,5,
  	39,0,0,162,142,1,0,0,0,162,152,1,0,0,0,163,30,1,0,0,0,164,166,7,5,0,0,
  	165,164,1,0,0,0,166,167,1,0,0,0,167,165,1,0,0,0,167,168,1,0,0,0,168,176,
  	1,0,0,0,169,171,7,6,0,0,170,169,1,0,0,0,171,174,1,0,0,0,172,170,1,0,0,
  	0,172,173,1,0,0,0,173,175,1,0,0,0,174,172,1,0,0,0,175,177,7,5,0,0,176,
  	172,1,0,0,0,176,177,1,0,0,0,177,32,1,0,0,0,178,180,8,7,0,0,179,178,1,
  	0,0,0,180,181,1,0,0,0,181,179,1,0,0,0,181,182,1,0,0,0,182,34,1,0,0,0,
  	183,185,8,8,0,0,184,183,1,0,0,0,185,186,1,0,0,0,186,184,1,0,0,0,186,187,
  	1,0,0,0,187,36,1,0,0,0,188,190,7,9,0,0,189,188,1,0,0,0,190,191,1,0,0,
  	0,191,189,1,0,0,0,191,192,1,0,0,0,192,193,1,0,0,0,193,194,6,18,0,0,194,
  	38,1,0,0,0,195,196,5,47,0,0,196,197,5,47,0,0,197,201,1,0,0,0,198,200,
  	8,10,0,0,199,198,1,0,0,0,200,203,1,0,0,0,201,199,1,0,0,0,201,202,1,0,
  	0,0,202,204,1,0,0,0,203,201,1,0,0,0,204,205,6,19,0,0,205,40,1,0,0,0,206,
  	207,5,47,0,0,207,208,5,42,0,0,208,212,1,0,0,0,209,211,9,0,0,0,210,209,
  	1,0,0,0,211,214,1,0,0,0,212,213,1,0,0,0,212,210,1,0,0,0,213,215,1,0,0,
  	0,214,212,1,0,0,0,215,216,5,42,0,0,216,217,5,47,0,0,217,218,1,0,0,0,218,
  	219,6,20,0,0,219,42,1,0,0,0,15,0,139,146,148,156,158,162,167,172,176,
  	181,186,191,201,212,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  scannerlexerLexerStaticData = staticData.release();
}

}

ScannerLexer::ScannerLexer(CharStream *input) : Lexer(input) {
  ScannerLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *scannerlexerLexerStaticData->atn, scannerlexerLexerStaticData->decisionToDFA, scannerlexerLexerStaticData->sharedContextCache);
}

ScannerLexer::~ScannerLexer() {
  delete _interpreter;
}

std::string ScannerLexer::getGrammarFileName() const {
  return "Scanner.g4";
}

const std::vector<std::string>& ScannerLexer::getRuleNames() const {
  return scannerlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& ScannerLexer::getChannelNames() const {
  return scannerlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& ScannerLexer::getModeNames() const {
  return scannerlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& ScannerLexer::getVocabulary() const {
  return scannerlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ScannerLexer::getSerializedATN() const {
  return scannerlexerLexerStaticData->serializedATN;
}

const atn::ATN& ScannerLexer::getATN() const {
  return *scannerlexerLexerStaticData->atn;
}




void ScannerLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  scannerlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(scannerlexerLexerOnceFlag, scannerlexerLexerInitialize);
#endif
}
