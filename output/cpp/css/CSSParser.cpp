
// Generated from CSS.g4 by ANTLR 4.13.1


#include "CSSListener.h"

#include "CSSParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CSSParserStaticData final {
  CSSParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CSSParserStaticData(const CSSParserStaticData&) = delete;
  CSSParserStaticData(CSSParserStaticData&&) = delete;
  CSSParserStaticData& operator=(const CSSParserStaticData&) = delete;
  CSSParserStaticData& operator=(CSSParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag cssParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CSSParserStaticData *cssParserStaticData = nullptr;

void cssParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (cssParserStaticData != nullptr) {
    return;
  }
#else
  assert(cssParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CSSParserStaticData>(
    std::vector<std::string>{
      "stylesheet", "statement", "ruleset", "selectorList", "selector", 
      "combinator", "simpleSelector", "typeSelector", "universalSelector", 
      "idSelector", "classSelector", "attributeSelector", "attributeOperator", 
      "pseudoSelector", "pseudoClass", "pseudoClassArgument", "pseudoElement", 
      "declaration", "property", "value", "operator", "term", "unaryOperator", 
      "numeric", "percentage", "length", "angle", "time", "frequency", "resolution", 
      "hexcolor", "function", "functionArguments", "functionArgument", "calc", 
      "calcExpression", "calcTerm", "calcFactor", "atRule", "atImport", 
      "atMedia", "mediaQueryList", "mediaQuery", "mediaType", "mediaFeature", 
      "atKeyframes", "keyframeBlock", "keyframeSelector", "atFontFace", 
      "atSupports", "supportsCondition", "supportsNegation", "supportsConjunction", 
      "supportsDisjunction", "supportsInParens", "supportsFeature", "atPage", 
      "pseudoPage", "atNamespace", "atCharset", "atViewport", "atCounterStyle", 
      "atFontFeatureValues", "fontFamilyName", "fontFeatureValueBlock", 
      "atProperty", "expression", "comment"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "','", "'>'", "'+'", "'~'", "'*'", "'#'", "'.'", 
      "'['", "']'", "'='", "'~='", "'|='", "'^='", "'$='", "'*='", "':'", 
      "'('", "')'", "'is'", "'where'", "'has'", "'::'", "';'", "'-'", "'/'", 
      "'%'", "'calc'", "'@'", "", "'@import'", "'@media'", "'@keyframes'", 
      "'@font-face'", "'@supports'", "'@page'", "'@namespace'", "'@charset'", 
      "'@viewport'", "'@counter-style'", "'@font-feature-values'", "'@property'", 
      "'only'", "'not'", "'and'", "'or'", "'from'", "'to'", "'!important'", 
      "'px'", "'em'", "'rem'", "'vh'", "'vw'", "'vmin'", "'vmax'", "'ch'", 
      "'ex'", "'cm'", "'mm'", "'in'", "'pt'", "'pc'", "'deg'", "'rad'", 
      "'grad'", "'turn'", "'s'", "'ms'", "'Hz'", "'kHz'", "'dpi'", "'dpcm'", 
      "'dppx'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "COMMENT", 
      "IMPORT", "MEDIA", "KEYFRAMES", "FONT_FACE", "SUPPORTS", "PAGE", "NAMESPACE", 
      "CHARSET", "VIEWPORT", "COUNTER_STYLE", "FONT_FEATURE_VALUES", "PROPERTY", 
      "ONLY", "NOT", "AND", "OR", "FROM", "TO", "IMPORTANT", "PX", "EM", 
      "REM", "VH", "VW", "VMIN", "VMAX", "CH", "EX", "CM", "MM", "IN", "PT", 
      "PC", "DEG", "RAD", "GRAD", "TURN", "S", "MS", "HZ", "KHZ", "DPI", 
      "DPCM", "DPPX", "VARIABLE", "NUMBER", "STRING_LITERAL", "URI", "IDENTIFIER", 
      "HEX_DIGIT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,82,654,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,1,0,5,0,138,8,0,10,0,12,0,
  	141,9,0,1,0,1,0,1,1,1,1,1,1,3,1,148,8,1,1,2,1,2,1,2,5,2,153,8,2,10,2,
  	12,2,156,9,2,1,2,1,2,1,3,1,3,1,3,5,3,163,8,3,10,3,12,3,166,9,3,1,4,1,
  	4,1,4,1,4,5,4,172,8,4,10,4,12,4,175,9,4,1,5,1,5,1,6,1,6,3,6,181,8,6,1,
  	6,1,6,1,6,1,6,5,6,187,8,6,10,6,12,6,190,9,6,1,6,1,6,1,6,1,6,4,6,196,8,
  	6,11,6,12,6,197,3,6,200,8,6,1,7,1,7,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,
  	1,11,1,11,1,11,1,11,1,11,3,11,217,8,11,1,11,1,11,1,12,1,12,1,13,1,13,
  	3,13,225,8,13,1,14,1,14,1,14,1,14,1,14,1,14,3,14,233,8,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,247,8,14,1,15,1,
  	15,1,15,1,15,3,15,253,8,15,1,16,1,16,1,16,1,17,1,17,1,17,1,17,3,17,262,
  	8,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,270,8,17,3,17,272,8,17,1,18,1,
  	18,1,18,5,18,277,8,18,10,18,12,18,280,9,18,1,18,3,18,283,8,18,1,19,1,
  	19,3,19,287,8,19,1,19,5,19,290,8,19,10,19,12,19,293,9,19,1,20,1,20,1,
  	21,3,21,298,8,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,307,8,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,3,21,316,8,21,1,22,1,22,1,23,1,23,1,24,
  	1,24,1,24,1,25,1,25,1,25,1,26,1,26,1,26,1,27,1,27,1,27,1,28,1,28,1,28,
  	1,29,1,29,1,29,1,30,1,30,4,30,342,8,30,11,30,12,30,343,1,31,1,31,1,31,
  	3,31,349,8,31,1,31,1,31,1,32,1,32,1,32,5,32,356,8,32,10,32,12,32,359,
  	9,32,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,35,1,35,1,35,5,35,371,8,35,
  	10,35,12,35,374,9,35,1,36,1,36,1,36,5,36,379,8,36,10,36,12,36,382,9,36,
  	1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,393,8,37,1,38,1,38,
  	1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,3,38,407,8,38,1,39,
  	1,39,1,39,3,39,412,8,39,1,39,1,39,1,40,1,40,1,40,1,40,5,40,420,8,40,10,
  	40,12,40,423,9,40,1,40,1,40,1,41,1,41,1,41,5,41,430,8,41,10,41,12,41,
  	433,9,41,1,42,3,42,436,8,42,1,42,1,42,1,42,5,42,441,8,42,10,42,12,42,
  	444,9,42,1,42,1,42,1,42,5,42,449,8,42,10,42,12,42,452,9,42,3,42,454,8,
  	42,1,43,1,43,1,44,1,44,1,44,1,44,3,44,462,8,44,1,44,1,44,1,45,1,45,1,
  	45,1,45,5,45,470,8,45,10,45,12,45,473,9,45,1,45,1,45,1,46,1,46,1,46,5,
  	46,480,8,46,10,46,12,46,483,9,46,1,46,1,46,1,47,1,47,1,47,1,47,3,47,491,
  	8,47,1,47,1,47,1,47,5,47,496,8,47,10,47,12,47,499,9,47,1,48,1,48,1,48,
  	5,48,504,8,48,10,48,12,48,507,9,48,1,48,1,48,1,49,1,49,1,49,1,49,5,49,
  	515,8,49,10,49,12,49,518,9,49,1,49,1,49,1,50,1,50,1,50,1,50,3,50,526,
  	8,50,1,51,1,51,1,51,1,52,1,52,1,52,4,52,534,8,52,11,52,12,52,535,1,53,
  	1,53,1,53,4,53,541,8,53,11,53,12,53,542,1,54,1,54,1,54,1,54,1,54,3,54,
  	550,8,54,1,55,1,55,1,55,1,55,1,56,1,56,3,56,558,8,56,1,56,1,56,5,56,562,
  	8,56,10,56,12,56,565,9,56,1,56,1,56,1,57,1,57,1,57,1,58,1,58,3,58,574,
  	8,58,1,58,1,58,1,58,1,59,1,59,1,59,1,59,1,60,1,60,1,60,5,60,586,8,60,
  	10,60,12,60,589,9,60,1,60,1,60,1,61,1,61,1,61,1,61,5,61,597,8,61,10,61,
  	12,61,600,9,61,1,61,1,61,1,62,1,62,4,62,606,8,62,11,62,12,62,607,1,62,
  	1,62,5,62,612,8,62,10,62,12,62,615,9,62,1,62,1,62,1,63,1,63,1,64,1,64,
  	1,64,1,64,5,64,625,8,64,10,64,12,64,628,9,64,1,64,1,64,1,65,1,65,1,65,
  	1,65,5,65,636,8,65,10,65,12,65,639,9,65,1,65,1,65,1,66,1,66,1,66,1,66,
  	5,66,647,8,66,10,66,12,66,650,9,66,1,67,1,67,1,67,0,1,94,68,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,
  	56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,
  	102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,0,
  	14,2,0,4,6,82,82,2,0,78,78,80,80,1,0,12,17,1,0,21,23,3,0,3,3,27,27,82,
  	82,2,0,5,5,26,26,1,0,51,64,1,0,65,68,1,0,69,70,1,0,71,72,1,0,73,75,2,
  	0,7,7,27,27,1,0,78,79,1,0,44,45,683,0,139,1,0,0,0,2,147,1,0,0,0,4,149,
  	1,0,0,0,6,159,1,0,0,0,8,167,1,0,0,0,10,176,1,0,0,0,12,199,1,0,0,0,14,
  	201,1,0,0,0,16,203,1,0,0,0,18,205,1,0,0,0,20,208,1,0,0,0,22,211,1,0,0,
  	0,24,220,1,0,0,0,26,224,1,0,0,0,28,246,1,0,0,0,30,252,1,0,0,0,32,254,
  	1,0,0,0,34,271,1,0,0,0,36,282,1,0,0,0,38,284,1,0,0,0,40,294,1,0,0,0,42,
  	315,1,0,0,0,44,317,1,0,0,0,46,319,1,0,0,0,48,321,1,0,0,0,50,324,1,0,0,
  	0,52,327,1,0,0,0,54,330,1,0,0,0,56,333,1,0,0,0,58,336,1,0,0,0,60,339,
  	1,0,0,0,62,345,1,0,0,0,64,352,1,0,0,0,66,360,1,0,0,0,68,362,1,0,0,0,70,
  	367,1,0,0,0,72,375,1,0,0,0,74,392,1,0,0,0,76,406,1,0,0,0,78,408,1,0,0,
  	0,80,415,1,0,0,0,82,426,1,0,0,0,84,453,1,0,0,0,86,455,1,0,0,0,88,457,
  	1,0,0,0,90,465,1,0,0,0,92,476,1,0,0,0,94,490,1,0,0,0,96,500,1,0,0,0,98,
  	510,1,0,0,0,100,525,1,0,0,0,102,527,1,0,0,0,104,530,1,0,0,0,106,537,1,
  	0,0,0,108,549,1,0,0,0,110,551,1,0,0,0,112,555,1,0,0,0,114,568,1,0,0,0,
  	116,571,1,0,0,0,118,578,1,0,0,0,120,582,1,0,0,0,122,592,1,0,0,0,124,603,
  	1,0,0,0,126,618,1,0,0,0,128,620,1,0,0,0,130,631,1,0,0,0,132,642,1,0,0,
  	0,134,651,1,0,0,0,136,138,3,2,1,0,137,136,1,0,0,0,138,141,1,0,0,0,139,
  	137,1,0,0,0,139,140,1,0,0,0,140,142,1,0,0,0,141,139,1,0,0,0,142,143,5,
  	0,0,1,143,1,1,0,0,0,144,148,3,4,2,0,145,148,3,76,38,0,146,148,3,134,67,
  	0,147,144,1,0,0,0,147,145,1,0,0,0,147,146,1,0,0,0,148,3,1,0,0,0,149,150,
  	3,6,3,0,150,154,5,1,0,0,151,153,3,34,17,0,152,151,1,0,0,0,153,156,1,0,
  	0,0,154,152,1,0,0,0,154,155,1,0,0,0,155,157,1,0,0,0,156,154,1,0,0,0,157,
  	158,5,2,0,0,158,5,1,0,0,0,159,164,3,8,4,0,160,161,5,3,0,0,161,163,3,8,
  	4,0,162,160,1,0,0,0,163,166,1,0,0,0,164,162,1,0,0,0,164,165,1,0,0,0,165,
  	7,1,0,0,0,166,164,1,0,0,0,167,173,3,12,6,0,168,169,3,10,5,0,169,170,3,
  	12,6,0,170,172,1,0,0,0,171,168,1,0,0,0,172,175,1,0,0,0,173,171,1,0,0,
  	0,173,174,1,0,0,0,174,9,1,0,0,0,175,173,1,0,0,0,176,177,7,0,0,0,177,11,
  	1,0,0,0,178,181,3,14,7,0,179,181,3,16,8,0,180,178,1,0,0,0,180,179,1,0,
  	0,0,180,181,1,0,0,0,181,188,1,0,0,0,182,187,3,18,9,0,183,187,3,20,10,
  	0,184,187,3,22,11,0,185,187,3,26,13,0,186,182,1,0,0,0,186,183,1,0,0,0,
  	186,184,1,0,0,0,186,185,1,0,0,0,187,190,1,0,0,0,188,186,1,0,0,0,188,189,
  	1,0,0,0,189,200,1,0,0,0,190,188,1,0,0,0,191,196,3,18,9,0,192,196,3,20,
  	10,0,193,196,3,22,11,0,194,196,3,26,13,0,195,191,1,0,0,0,195,192,1,0,
  	0,0,195,193,1,0,0,0,195,194,1,0,0,0,196,197,1,0,0,0,197,195,1,0,0,0,197,
  	198,1,0,0,0,198,200,1,0,0,0,199,180,1,0,0,0,199,195,1,0,0,0,200,13,1,
  	0,0,0,201,202,5,80,0,0,202,15,1,0,0,0,203,204,5,7,0,0,204,17,1,0,0,0,
  	205,206,5,8,0,0,206,207,5,80,0,0,207,19,1,0,0,0,208,209,5,9,0,0,209,210,
  	5,80,0,0,210,21,1,0,0,0,211,212,5,10,0,0,212,216,5,80,0,0,213,214,3,24,
  	12,0,214,215,7,1,0,0,215,217,1,0,0,0,216,213,1,0,0,0,216,217,1,0,0,0,
  	217,218,1,0,0,0,218,219,5,11,0,0,219,23,1,0,0,0,220,221,7,2,0,0,221,25,
  	1,0,0,0,222,225,3,28,14,0,223,225,3,32,16,0,224,222,1,0,0,0,224,223,1,
  	0,0,0,225,27,1,0,0,0,226,227,5,18,0,0,227,232,5,80,0,0,228,229,5,19,0,
  	0,229,230,3,30,15,0,230,231,5,20,0,0,231,233,1,0,0,0,232,228,1,0,0,0,
  	232,233,1,0,0,0,233,247,1,0,0,0,234,235,5,18,0,0,235,236,5,45,0,0,236,
  	237,5,19,0,0,237,238,3,6,3,0,238,239,5,20,0,0,239,247,1,0,0,0,240,241,
  	5,18,0,0,241,242,7,3,0,0,242,243,5,19,0,0,243,244,3,6,3,0,244,245,5,20,
  	0,0,245,247,1,0,0,0,246,226,1,0,0,0,246,234,1,0,0,0,246,240,1,0,0,0,247,
  	29,1,0,0,0,248,253,5,80,0,0,249,253,5,77,0,0,250,253,5,78,0,0,251,253,
  	3,132,66,0,252,248,1,0,0,0,252,249,1,0,0,0,252,250,1,0,0,0,252,251,1,
  	0,0,0,253,31,1,0,0,0,254,255,5,24,0,0,255,256,5,80,0,0,256,33,1,0,0,0,
  	257,258,3,36,18,0,258,259,5,18,0,0,259,261,3,38,19,0,260,262,5,50,0,0,
  	261,260,1,0,0,0,261,262,1,0,0,0,262,263,1,0,0,0,263,264,5,25,0,0,264,
  	272,1,0,0,0,265,266,3,36,18,0,266,267,5,18,0,0,267,269,3,38,19,0,268,
  	270,5,50,0,0,269,268,1,0,0,0,269,270,1,0,0,0,270,272,1,0,0,0,271,257,
  	1,0,0,0,271,265,1,0,0,0,272,35,1,0,0,0,273,278,5,80,0,0,274,275,5,26,
  	0,0,275,277,5,80,0,0,276,274,1,0,0,0,277,280,1,0,0,0,278,276,1,0,0,0,
  	278,279,1,0,0,0,279,283,1,0,0,0,280,278,1,0,0,0,281,283,5,76,0,0,282,
  	273,1,0,0,0,282,281,1,0,0,0,283,37,1,0,0,0,284,291,3,42,21,0,285,287,
  	3,40,20,0,286,285,1,0,0,0,286,287,1,0,0,0,287,288,1,0,0,0,288,290,3,42,
  	21,0,289,286,1,0,0,0,290,293,1,0,0,0,291,289,1,0,0,0,291,292,1,0,0,0,
  	292,39,1,0,0,0,293,291,1,0,0,0,294,295,7,4,0,0,295,41,1,0,0,0,296,298,
  	3,44,22,0,297,296,1,0,0,0,297,298,1,0,0,0,298,306,1,0,0,0,299,307,3,46,
  	23,0,300,307,3,48,24,0,301,307,3,50,25,0,302,307,3,52,26,0,303,307,3,
  	54,27,0,304,307,3,56,28,0,305,307,3,58,29,0,306,299,1,0,0,0,306,300,1,
  	0,0,0,306,301,1,0,0,0,306,302,1,0,0,0,306,303,1,0,0,0,306,304,1,0,0,0,
  	306,305,1,0,0,0,307,316,1,0,0,0,308,316,5,78,0,0,309,316,5,80,0,0,310,
  	316,5,79,0,0,311,316,3,60,30,0,312,316,3,62,31,0,313,316,5,76,0,0,314,
  	316,3,68,34,0,315,297,1,0,0,0,315,308,1,0,0,0,315,309,1,0,0,0,315,310,
  	1,0,0,0,315,311,1,0,0,0,315,312,1,0,0,0,315,313,1,0,0,0,315,314,1,0,0,
  	0,316,43,1,0,0,0,317,318,7,5,0,0,318,45,1,0,0,0,319,320,5,77,0,0,320,
  	47,1,0,0,0,321,322,5,77,0,0,322,323,5,28,0,0,323,49,1,0,0,0,324,325,5,
  	77,0,0,325,326,7,6,0,0,326,51,1,0,0,0,327,328,5,77,0,0,328,329,7,7,0,
  	0,329,53,1,0,0,0,330,331,5,77,0,0,331,332,7,8,0,0,332,55,1,0,0,0,333,
  	334,5,77,0,0,334,335,7,9,0,0,335,57,1,0,0,0,336,337,5,77,0,0,337,338,
  	7,10,0,0,338,59,1,0,0,0,339,341,5,8,0,0,340,342,5,81,0,0,341,340,1,0,
  	0,0,342,343,1,0,0,0,343,341,1,0,0,0,343,344,1,0,0,0,344,61,1,0,0,0,345,
  	346,5,80,0,0,346,348,5,19,0,0,347,349,3,64,32,0,348,347,1,0,0,0,348,349,
  	1,0,0,0,349,350,1,0,0,0,350,351,5,20,0,0,351,63,1,0,0,0,352,357,3,66,
  	33,0,353,354,5,3,0,0,354,356,3,66,33,0,355,353,1,0,0,0,356,359,1,0,0,
  	0,357,355,1,0,0,0,357,358,1,0,0,0,358,65,1,0,0,0,359,357,1,0,0,0,360,
  	361,3,38,19,0,361,67,1,0,0,0,362,363,5,29,0,0,363,364,5,19,0,0,364,365,
  	3,70,35,0,365,366,5,20,0,0,366,69,1,0,0,0,367,372,3,72,36,0,368,369,7,
  	5,0,0,369,371,3,72,36,0,370,368,1,0,0,0,371,374,1,0,0,0,372,370,1,0,0,
  	0,372,373,1,0,0,0,373,71,1,0,0,0,374,372,1,0,0,0,375,380,3,74,37,0,376,
  	377,7,11,0,0,377,379,3,74,37,0,378,376,1,0,0,0,379,382,1,0,0,0,380,378,
  	1,0,0,0,380,381,1,0,0,0,381,73,1,0,0,0,382,380,1,0,0,0,383,393,3,46,23,
  	0,384,393,3,50,25,0,385,393,3,48,24,0,386,387,5,19,0,0,387,388,3,70,35,
  	0,388,389,5,20,0,0,389,393,1,0,0,0,390,393,3,68,34,0,391,393,5,76,0,0,
  	392,383,1,0,0,0,392,384,1,0,0,0,392,385,1,0,0,0,392,386,1,0,0,0,392,390,
  	1,0,0,0,392,391,1,0,0,0,393,75,1,0,0,0,394,407,3,78,39,0,395,407,3,80,
  	40,0,396,407,3,90,45,0,397,407,3,96,48,0,398,407,3,98,49,0,399,407,3,
  	112,56,0,400,407,3,116,58,0,401,407,3,118,59,0,402,407,3,120,60,0,403,
  	407,3,122,61,0,404,407,3,124,62,0,405,407,3,130,65,0,406,394,1,0,0,0,
  	406,395,1,0,0,0,406,396,1,0,0,0,406,397,1,0,0,0,406,398,1,0,0,0,406,399,
  	1,0,0,0,406,400,1,0,0,0,406,401,1,0,0,0,406,402,1,0,0,0,406,403,1,0,0,
  	0,406,404,1,0,0,0,406,405,1,0,0,0,407,77,1,0,0,0,408,409,5,32,0,0,409,
  	411,7,12,0,0,410,412,3,82,41,0,411,410,1,0,0,0,411,412,1,0,0,0,412,413,
  	1,0,0,0,413,414,5,25,0,0,414,79,1,0,0,0,415,416,5,33,0,0,416,417,3,82,
  	41,0,417,421,5,1,0,0,418,420,3,2,1,0,419,418,1,0,0,0,420,423,1,0,0,0,
  	421,419,1,0,0,0,421,422,1,0,0,0,422,424,1,0,0,0,423,421,1,0,0,0,424,425,
  	5,2,0,0,425,81,1,0,0,0,426,431,3,84,42,0,427,428,5,3,0,0,428,430,3,84,
  	42,0,429,427,1,0,0,0,430,433,1,0,0,0,431,429,1,0,0,0,431,432,1,0,0,0,
  	432,83,1,0,0,0,433,431,1,0,0,0,434,436,7,13,0,0,435,434,1,0,0,0,435,436,
  	1,0,0,0,436,437,1,0,0,0,437,442,3,86,43,0,438,439,5,46,0,0,439,441,3,
  	88,44,0,440,438,1,0,0,0,441,444,1,0,0,0,442,440,1,0,0,0,442,443,1,0,0,
  	0,443,454,1,0,0,0,444,442,1,0,0,0,445,450,3,88,44,0,446,447,5,46,0,0,
  	447,449,3,88,44,0,448,446,1,0,0,0,449,452,1,0,0,0,450,448,1,0,0,0,450,
  	451,1,0,0,0,451,454,1,0,0,0,452,450,1,0,0,0,453,435,1,0,0,0,453,445,1,
  	0,0,0,454,85,1,0,0,0,455,456,5,80,0,0,456,87,1,0,0,0,457,458,5,19,0,0,
  	458,461,5,80,0,0,459,460,5,18,0,0,460,462,3,38,19,0,461,459,1,0,0,0,461,
  	462,1,0,0,0,462,463,1,0,0,0,463,464,5,20,0,0,464,89,1,0,0,0,465,466,5,
  	34,0,0,466,467,5,80,0,0,467,471,5,1,0,0,468,470,3,92,46,0,469,468,1,0,
  	0,0,470,473,1,0,0,0,471,469,1,0,0,0,471,472,1,0,0,0,472,474,1,0,0,0,473,
  	471,1,0,0,0,474,475,5,2,0,0,475,91,1,0,0,0,476,477,3,94,47,0,477,481,
  	5,1,0,0,478,480,3,34,17,0,479,478,1,0,0,0,480,483,1,0,0,0,481,479,1,0,
  	0,0,481,482,1,0,0,0,482,484,1,0,0,0,483,481,1,0,0,0,484,485,5,2,0,0,485,
  	93,1,0,0,0,486,487,6,47,-1,0,487,491,5,48,0,0,488,491,5,49,0,0,489,491,
  	3,48,24,0,490,486,1,0,0,0,490,488,1,0,0,0,490,489,1,0,0,0,491,497,1,0,
  	0,0,492,493,10,1,0,0,493,494,5,3,0,0,494,496,3,94,47,2,495,492,1,0,0,
  	0,496,499,1,0,0,0,497,495,1,0,0,0,497,498,1,0,0,0,498,95,1,0,0,0,499,
  	497,1,0,0,0,500,501,5,35,0,0,501,505,5,1,0,0,502,504,3,34,17,0,503,502,
  	1,0,0,0,504,507,1,0,0,0,505,503,1,0,0,0,505,506,1,0,0,0,506,508,1,0,0,
  	0,507,505,1,0,0,0,508,509,5,2,0,0,509,97,1,0,0,0,510,511,5,36,0,0,511,
  	512,3,100,50,0,512,516,5,1,0,0,513,515,3,2,1,0,514,513,1,0,0,0,515,518,
  	1,0,0,0,516,514,1,0,0,0,516,517,1,0,0,0,517,519,1,0,0,0,518,516,1,0,0,
  	0,519,520,5,2,0,0,520,99,1,0,0,0,521,526,3,102,51,0,522,526,3,104,52,
  	0,523,526,3,106,53,0,524,526,3,108,54,0,525,521,1,0,0,0,525,522,1,0,0,
  	0,525,523,1,0,0,0,525,524,1,0,0,0,526,101,1,0,0,0,527,528,5,45,0,0,528,
  	529,3,108,54,0,529,103,1,0,0,0,530,533,3,108,54,0,531,532,5,46,0,0,532,
  	534,3,108,54,0,533,531,1,0,0,0,534,535,1,0,0,0,535,533,1,0,0,0,535,536,
  	1,0,0,0,536,105,1,0,0,0,537,540,3,108,54,0,538,539,5,47,0,0,539,541,3,
  	108,54,0,540,538,1,0,0,0,541,542,1,0,0,0,542,540,1,0,0,0,542,543,1,0,
  	0,0,543,107,1,0,0,0,544,545,5,19,0,0,545,546,3,100,50,0,546,547,5,20,
  	0,0,547,550,1,0,0,0,548,550,3,110,55,0,549,544,1,0,0,0,549,548,1,0,0,
  	0,550,109,1,0,0,0,551,552,5,19,0,0,552,553,3,34,17,0,553,554,5,20,0,0,
  	554,111,1,0,0,0,555,557,5,37,0,0,556,558,3,114,57,0,557,556,1,0,0,0,557,
  	558,1,0,0,0,558,559,1,0,0,0,559,563,5,1,0,0,560,562,3,34,17,0,561,560,
  	1,0,0,0,562,565,1,0,0,0,563,561,1,0,0,0,563,564,1,0,0,0,564,566,1,0,0,
  	0,565,563,1,0,0,0,566,567,5,2,0,0,567,113,1,0,0,0,568,569,5,18,0,0,569,
  	570,5,80,0,0,570,115,1,0,0,0,571,573,5,38,0,0,572,574,5,80,0,0,573,572,
  	1,0,0,0,573,574,1,0,0,0,574,575,1,0,0,0,575,576,7,12,0,0,576,577,5,25,
  	0,0,577,117,1,0,0,0,578,579,5,39,0,0,579,580,5,78,0,0,580,581,5,25,0,
  	0,581,119,1,0,0,0,582,583,5,40,0,0,583,587,5,1,0,0,584,586,3,34,17,0,
  	585,584,1,0,0,0,586,589,1,0,0,0,587,585,1,0,0,0,587,588,1,0,0,0,588,590,
  	1,0,0,0,589,587,1,0,0,0,590,591,5,2,0,0,591,121,1,0,0,0,592,593,5,41,
  	0,0,593,594,5,80,0,0,594,598,5,1,0,0,595,597,3,34,17,0,596,595,1,0,0,
  	0,597,600,1,0,0,0,598,596,1,0,0,0,598,599,1,0,0,0,599,601,1,0,0,0,600,
  	598,1,0,0,0,601,602,5,2,0,0,602,123,1,0,0,0,603,605,5,42,0,0,604,606,
  	3,126,63,0,605,604,1,0,0,0,606,607,1,0,0,0,607,605,1,0,0,0,607,608,1,
  	0,0,0,608,609,1,0,0,0,609,613,5,1,0,0,610,612,3,128,64,0,611,610,1,0,
  	0,0,612,615,1,0,0,0,613,611,1,0,0,0,613,614,1,0,0,0,614,616,1,0,0,0,615,
  	613,1,0,0,0,616,617,5,2,0,0,617,125,1,0,0,0,618,619,7,1,0,0,619,127,1,
  	0,0,0,620,621,5,30,0,0,621,622,5,80,0,0,622,626,5,1,0,0,623,625,3,34,
  	17,0,624,623,1,0,0,0,625,628,1,0,0,0,626,624,1,0,0,0,626,627,1,0,0,0,
  	627,629,1,0,0,0,628,626,1,0,0,0,629,630,5,2,0,0,630,129,1,0,0,0,631,632,
  	5,43,0,0,632,633,5,76,0,0,633,637,5,1,0,0,634,636,3,34,17,0,635,634,1,
  	0,0,0,636,639,1,0,0,0,637,635,1,0,0,0,637,638,1,0,0,0,638,640,1,0,0,0,
  	639,637,1,0,0,0,640,641,5,2,0,0,641,131,1,0,0,0,642,648,3,42,21,0,643,
  	644,3,40,20,0,644,645,3,42,21,0,645,647,1,0,0,0,646,643,1,0,0,0,647,650,
  	1,0,0,0,648,646,1,0,0,0,648,649,1,0,0,0,649,133,1,0,0,0,650,648,1,0,0,
  	0,651,652,5,31,0,0,652,135,1,0,0,0,61,139,147,154,164,173,180,186,188,
  	195,197,199,216,224,232,246,252,261,269,271,278,282,286,291,297,306,315,
  	343,348,357,372,380,392,406,411,421,431,435,442,450,453,461,471,481,490,
  	497,505,516,525,535,542,549,557,563,573,587,598,607,613,626,637,648
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  cssParserStaticData = staticData.release();
}

}

CSSParser::CSSParser(TokenStream *input) : CSSParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CSSParser::CSSParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CSSParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *cssParserStaticData->atn, cssParserStaticData->decisionToDFA, cssParserStaticData->sharedContextCache, options);
}

CSSParser::~CSSParser() {
  delete _interpreter;
}

const atn::ATN& CSSParser::getATN() const {
  return *cssParserStaticData->atn;
}

std::string CSSParser::getGrammarFileName() const {
  return "CSS.g4";
}

const std::vector<std::string>& CSSParser::getRuleNames() const {
  return cssParserStaticData->ruleNames;
}

const dfa::Vocabulary& CSSParser::getVocabulary() const {
  return cssParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CSSParser::getSerializedATN() const {
  return cssParserStaticData->serializedATN;
}


//----------------- StylesheetContext ------------------------------------------------------------------

CSSParser::StylesheetContext::StylesheetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::StylesheetContext::EOF() {
  return getToken(CSSParser::EOF, 0);
}

std::vector<CSSParser::StatementContext *> CSSParser::StylesheetContext::statement() {
  return getRuleContexts<CSSParser::StatementContext>();
}

CSSParser::StatementContext* CSSParser::StylesheetContext::statement(size_t i) {
  return getRuleContext<CSSParser::StatementContext>(i);
}


size_t CSSParser::StylesheetContext::getRuleIndex() const {
  return CSSParser::RuleStylesheet;
}

void CSSParser::StylesheetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStylesheet(this);
}

void CSSParser::StylesheetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStylesheet(this);
}

CSSParser::StylesheetContext* CSSParser::stylesheet() {
  StylesheetContext *_localctx = _tracker.createInstance<StylesheetContext>(_ctx, getState());
  enterRule(_localctx, 0, CSSParser::RuleStylesheet);
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
    setState(139);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17590055602170) != 0) || _la == CSSParser::IDENTIFIER

    || _la == CSSParser::WS) {
      setState(136);
      statement();
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(142);
    match(CSSParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CSSParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::RulesetContext* CSSParser::StatementContext::ruleset() {
  return getRuleContext<CSSParser::RulesetContext>(0);
}

CSSParser::AtRuleContext* CSSParser::StatementContext::atRule() {
  return getRuleContext<CSSParser::AtRuleContext>(0);
}

CSSParser::CommentContext* CSSParser::StatementContext::comment() {
  return getRuleContext<CSSParser::CommentContext>(0);
}


size_t CSSParser::StatementContext::getRuleIndex() const {
  return CSSParser::RuleStatement;
}

void CSSParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void CSSParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

CSSParser::StatementContext* CSSParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, CSSParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(147);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::T__0:
      case CSSParser::T__2:
      case CSSParser::T__3:
      case CSSParser::T__4:
      case CSSParser::T__5:
      case CSSParser::T__6:
      case CSSParser::T__7:
      case CSSParser::T__8:
      case CSSParser::T__9:
      case CSSParser::T__17:
      case CSSParser::T__23:
      case CSSParser::IDENTIFIER:
      case CSSParser::WS: {
        enterOuterAlt(_localctx, 1);
        setState(144);
        ruleset();
        break;
      }

      case CSSParser::IMPORT:
      case CSSParser::MEDIA:
      case CSSParser::KEYFRAMES:
      case CSSParser::FONT_FACE:
      case CSSParser::SUPPORTS:
      case CSSParser::PAGE:
      case CSSParser::NAMESPACE:
      case CSSParser::CHARSET:
      case CSSParser::VIEWPORT:
      case CSSParser::COUNTER_STYLE:
      case CSSParser::FONT_FEATURE_VALUES:
      case CSSParser::PROPERTY: {
        enterOuterAlt(_localctx, 2);
        setState(145);
        atRule();
        break;
      }

      case CSSParser::COMMENT: {
        enterOuterAlt(_localctx, 3);
        setState(146);
        comment();
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

//----------------- RulesetContext ------------------------------------------------------------------

CSSParser::RulesetContext::RulesetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::SelectorListContext* CSSParser::RulesetContext::selectorList() {
  return getRuleContext<CSSParser::SelectorListContext>(0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::RulesetContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::RulesetContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::RulesetContext::getRuleIndex() const {
  return CSSParser::RuleRuleset;
}

void CSSParser::RulesetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleset(this);
}

void CSSParser::RulesetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleset(this);
}

CSSParser::RulesetContext* CSSParser::ruleset() {
  RulesetContext *_localctx = _tracker.createInstance<RulesetContext>(_ctx, getState());
  enterRule(_localctx, 4, CSSParser::RuleRuleset);
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
    setState(149);
    selectorList();
    setState(150);
    match(CSSParser::T__0);
    setState(154);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::VARIABLE

    || _la == CSSParser::IDENTIFIER) {
      setState(151);
      declaration();
      setState(156);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(157);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorListContext ------------------------------------------------------------------

CSSParser::SelectorListContext::SelectorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::SelectorContext *> CSSParser::SelectorListContext::selector() {
  return getRuleContexts<CSSParser::SelectorContext>();
}

CSSParser::SelectorContext* CSSParser::SelectorListContext::selector(size_t i) {
  return getRuleContext<CSSParser::SelectorContext>(i);
}


size_t CSSParser::SelectorListContext::getRuleIndex() const {
  return CSSParser::RuleSelectorList;
}

void CSSParser::SelectorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectorList(this);
}

void CSSParser::SelectorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectorList(this);
}

CSSParser::SelectorListContext* CSSParser::selectorList() {
  SelectorListContext *_localctx = _tracker.createInstance<SelectorListContext>(_ctx, getState());
  enterRule(_localctx, 6, CSSParser::RuleSelectorList);
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
    setState(159);
    selector();
    setState(164);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::T__2) {
      setState(160);
      match(CSSParser::T__2);
      setState(161);
      selector();
      setState(166);
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

//----------------- SelectorContext ------------------------------------------------------------------

CSSParser::SelectorContext::SelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::SimpleSelectorContext *> CSSParser::SelectorContext::simpleSelector() {
  return getRuleContexts<CSSParser::SimpleSelectorContext>();
}

CSSParser::SimpleSelectorContext* CSSParser::SelectorContext::simpleSelector(size_t i) {
  return getRuleContext<CSSParser::SimpleSelectorContext>(i);
}

std::vector<CSSParser::CombinatorContext *> CSSParser::SelectorContext::combinator() {
  return getRuleContexts<CSSParser::CombinatorContext>();
}

CSSParser::CombinatorContext* CSSParser::SelectorContext::combinator(size_t i) {
  return getRuleContext<CSSParser::CombinatorContext>(i);
}


size_t CSSParser::SelectorContext::getRuleIndex() const {
  return CSSParser::RuleSelector;
}

void CSSParser::SelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelector(this);
}

void CSSParser::SelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelector(this);
}

CSSParser::SelectorContext* CSSParser::selector() {
  SelectorContext *_localctx = _tracker.createInstance<SelectorContext>(_ctx, getState());
  enterRule(_localctx, 8, CSSParser::RuleSelector);
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
    setState(167);
    simpleSelector();
    setState(173);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 112) != 0) || _la == CSSParser::WS) {
      setState(168);
      combinator();
      setState(169);
      simpleSelector();
      setState(175);
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

//----------------- CombinatorContext ------------------------------------------------------------------

CSSParser::CombinatorContext::CombinatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::CombinatorContext::WS() {
  return getToken(CSSParser::WS, 0);
}


size_t CSSParser::CombinatorContext::getRuleIndex() const {
  return CSSParser::RuleCombinator;
}

void CSSParser::CombinatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCombinator(this);
}

void CSSParser::CombinatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCombinator(this);
}

CSSParser::CombinatorContext* CSSParser::combinator() {
  CombinatorContext *_localctx = _tracker.createInstance<CombinatorContext>(_ctx, getState());
  enterRule(_localctx, 10, CSSParser::RuleCombinator);
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
    setState(176);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 112) != 0) || _la == CSSParser::WS)) {
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

//----------------- SimpleSelectorContext ------------------------------------------------------------------

CSSParser::SimpleSelectorContext::SimpleSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::TypeSelectorContext* CSSParser::SimpleSelectorContext::typeSelector() {
  return getRuleContext<CSSParser::TypeSelectorContext>(0);
}

CSSParser::UniversalSelectorContext* CSSParser::SimpleSelectorContext::universalSelector() {
  return getRuleContext<CSSParser::UniversalSelectorContext>(0);
}

std::vector<CSSParser::IdSelectorContext *> CSSParser::SimpleSelectorContext::idSelector() {
  return getRuleContexts<CSSParser::IdSelectorContext>();
}

CSSParser::IdSelectorContext* CSSParser::SimpleSelectorContext::idSelector(size_t i) {
  return getRuleContext<CSSParser::IdSelectorContext>(i);
}

std::vector<CSSParser::ClassSelectorContext *> CSSParser::SimpleSelectorContext::classSelector() {
  return getRuleContexts<CSSParser::ClassSelectorContext>();
}

CSSParser::ClassSelectorContext* CSSParser::SimpleSelectorContext::classSelector(size_t i) {
  return getRuleContext<CSSParser::ClassSelectorContext>(i);
}

std::vector<CSSParser::AttributeSelectorContext *> CSSParser::SimpleSelectorContext::attributeSelector() {
  return getRuleContexts<CSSParser::AttributeSelectorContext>();
}

CSSParser::AttributeSelectorContext* CSSParser::SimpleSelectorContext::attributeSelector(size_t i) {
  return getRuleContext<CSSParser::AttributeSelectorContext>(i);
}

std::vector<CSSParser::PseudoSelectorContext *> CSSParser::SimpleSelectorContext::pseudoSelector() {
  return getRuleContexts<CSSParser::PseudoSelectorContext>();
}

CSSParser::PseudoSelectorContext* CSSParser::SimpleSelectorContext::pseudoSelector(size_t i) {
  return getRuleContext<CSSParser::PseudoSelectorContext>(i);
}


size_t CSSParser::SimpleSelectorContext::getRuleIndex() const {
  return CSSParser::RuleSimpleSelector;
}

void CSSParser::SimpleSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimpleSelector(this);
}

void CSSParser::SimpleSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimpleSelector(this);
}

CSSParser::SimpleSelectorContext* CSSParser::simpleSelector() {
  SimpleSelectorContext *_localctx = _tracker.createInstance<SimpleSelectorContext>(_ctx, getState());
  enterRule(_localctx, 12, CSSParser::RuleSimpleSelector);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(199);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(180);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CSSParser::IDENTIFIER: {
          setState(178);
          typeSelector();
          break;
        }

        case CSSParser::T__6: {
          setState(179);
          universalSelector();
          break;
        }

        case CSSParser::T__0:
        case CSSParser::T__2:
        case CSSParser::T__3:
        case CSSParser::T__4:
        case CSSParser::T__5:
        case CSSParser::T__7:
        case CSSParser::T__8:
        case CSSParser::T__9:
        case CSSParser::T__17:
        case CSSParser::T__19:
        case CSSParser::T__23:
        case CSSParser::WS: {
          break;
        }

      default:
        break;
      }
      setState(188);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 17041152) != 0)) {
        setState(186);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case CSSParser::T__7: {
            setState(182);
            idSelector();
            break;
          }

          case CSSParser::T__8: {
            setState(183);
            classSelector();
            break;
          }

          case CSSParser::T__9: {
            setState(184);
            attributeSelector();
            break;
          }

          case CSSParser::T__17:
          case CSSParser::T__23: {
            setState(185);
            pseudoSelector();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(190);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(195); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(195);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case CSSParser::T__7: {
            setState(191);
            idSelector();
            break;
          }

          case CSSParser::T__8: {
            setState(192);
            classSelector();
            break;
          }

          case CSSParser::T__9: {
            setState(193);
            attributeSelector();
            break;
          }

          case CSSParser::T__17:
          case CSSParser::T__23: {
            setState(194);
            pseudoSelector();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(197); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 17041152) != 0));
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

//----------------- TypeSelectorContext ------------------------------------------------------------------

CSSParser::TypeSelectorContext::TypeSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::TypeSelectorContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}


size_t CSSParser::TypeSelectorContext::getRuleIndex() const {
  return CSSParser::RuleTypeSelector;
}

void CSSParser::TypeSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSelector(this);
}

void CSSParser::TypeSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSelector(this);
}

CSSParser::TypeSelectorContext* CSSParser::typeSelector() {
  TypeSelectorContext *_localctx = _tracker.createInstance<TypeSelectorContext>(_ctx, getState());
  enterRule(_localctx, 14, CSSParser::RuleTypeSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    match(CSSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UniversalSelectorContext ------------------------------------------------------------------

CSSParser::UniversalSelectorContext::UniversalSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CSSParser::UniversalSelectorContext::getRuleIndex() const {
  return CSSParser::RuleUniversalSelector;
}

void CSSParser::UniversalSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUniversalSelector(this);
}

void CSSParser::UniversalSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUniversalSelector(this);
}

CSSParser::UniversalSelectorContext* CSSParser::universalSelector() {
  UniversalSelectorContext *_localctx = _tracker.createInstance<UniversalSelectorContext>(_ctx, getState());
  enterRule(_localctx, 16, CSSParser::RuleUniversalSelector);

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
    match(CSSParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdSelectorContext ------------------------------------------------------------------

CSSParser::IdSelectorContext::IdSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::IdSelectorContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}


size_t CSSParser::IdSelectorContext::getRuleIndex() const {
  return CSSParser::RuleIdSelector;
}

void CSSParser::IdSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdSelector(this);
}

void CSSParser::IdSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdSelector(this);
}

CSSParser::IdSelectorContext* CSSParser::idSelector() {
  IdSelectorContext *_localctx = _tracker.createInstance<IdSelectorContext>(_ctx, getState());
  enterRule(_localctx, 18, CSSParser::RuleIdSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(205);
    match(CSSParser::T__7);
    setState(206);
    match(CSSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassSelectorContext ------------------------------------------------------------------

CSSParser::ClassSelectorContext::ClassSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::ClassSelectorContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}


size_t CSSParser::ClassSelectorContext::getRuleIndex() const {
  return CSSParser::RuleClassSelector;
}

void CSSParser::ClassSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassSelector(this);
}

void CSSParser::ClassSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassSelector(this);
}

CSSParser::ClassSelectorContext* CSSParser::classSelector() {
  ClassSelectorContext *_localctx = _tracker.createInstance<ClassSelectorContext>(_ctx, getState());
  enterRule(_localctx, 20, CSSParser::RuleClassSelector);

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
    match(CSSParser::T__8);
    setState(209);
    match(CSSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeSelectorContext ------------------------------------------------------------------

CSSParser::AttributeSelectorContext::AttributeSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CSSParser::AttributeSelectorContext::IDENTIFIER() {
  return getTokens(CSSParser::IDENTIFIER);
}

tree::TerminalNode* CSSParser::AttributeSelectorContext::IDENTIFIER(size_t i) {
  return getToken(CSSParser::IDENTIFIER, i);
}

CSSParser::AttributeOperatorContext* CSSParser::AttributeSelectorContext::attributeOperator() {
  return getRuleContext<CSSParser::AttributeOperatorContext>(0);
}

tree::TerminalNode* CSSParser::AttributeSelectorContext::STRING_LITERAL() {
  return getToken(CSSParser::STRING_LITERAL, 0);
}


size_t CSSParser::AttributeSelectorContext::getRuleIndex() const {
  return CSSParser::RuleAttributeSelector;
}

void CSSParser::AttributeSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributeSelector(this);
}

void CSSParser::AttributeSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributeSelector(this);
}

CSSParser::AttributeSelectorContext* CSSParser::attributeSelector() {
  AttributeSelectorContext *_localctx = _tracker.createInstance<AttributeSelectorContext>(_ctx, getState());
  enterRule(_localctx, 22, CSSParser::RuleAttributeSelector);
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
    match(CSSParser::T__9);
    setState(212);
    match(CSSParser::IDENTIFIER);
    setState(216);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258048) != 0)) {
      setState(213);
      attributeOperator();
      setState(214);
      _la = _input->LA(1);
      if (!(_la == CSSParser::STRING_LITERAL

      || _la == CSSParser::IDENTIFIER)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(218);
    match(CSSParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeOperatorContext ------------------------------------------------------------------

CSSParser::AttributeOperatorContext::AttributeOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CSSParser::AttributeOperatorContext::getRuleIndex() const {
  return CSSParser::RuleAttributeOperator;
}

void CSSParser::AttributeOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributeOperator(this);
}

void CSSParser::AttributeOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributeOperator(this);
}

CSSParser::AttributeOperatorContext* CSSParser::attributeOperator() {
  AttributeOperatorContext *_localctx = _tracker.createInstance<AttributeOperatorContext>(_ctx, getState());
  enterRule(_localctx, 24, CSSParser::RuleAttributeOperator);
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
      ((1ULL << _la) & 258048) != 0))) {
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

//----------------- PseudoSelectorContext ------------------------------------------------------------------

CSSParser::PseudoSelectorContext::PseudoSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::PseudoClassContext* CSSParser::PseudoSelectorContext::pseudoClass() {
  return getRuleContext<CSSParser::PseudoClassContext>(0);
}

CSSParser::PseudoElementContext* CSSParser::PseudoSelectorContext::pseudoElement() {
  return getRuleContext<CSSParser::PseudoElementContext>(0);
}


size_t CSSParser::PseudoSelectorContext::getRuleIndex() const {
  return CSSParser::RulePseudoSelector;
}

void CSSParser::PseudoSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudoSelector(this);
}

void CSSParser::PseudoSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudoSelector(this);
}

CSSParser::PseudoSelectorContext* CSSParser::pseudoSelector() {
  PseudoSelectorContext *_localctx = _tracker.createInstance<PseudoSelectorContext>(_ctx, getState());
  enterRule(_localctx, 26, CSSParser::RulePseudoSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(224);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::T__17: {
        enterOuterAlt(_localctx, 1);
        setState(222);
        pseudoClass();
        break;
      }

      case CSSParser::T__23: {
        enterOuterAlt(_localctx, 2);
        setState(223);
        pseudoElement();
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

//----------------- PseudoClassContext ------------------------------------------------------------------

CSSParser::PseudoClassContext::PseudoClassContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::PseudoClassContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}

CSSParser::PseudoClassArgumentContext* CSSParser::PseudoClassContext::pseudoClassArgument() {
  return getRuleContext<CSSParser::PseudoClassArgumentContext>(0);
}

tree::TerminalNode* CSSParser::PseudoClassContext::NOT() {
  return getToken(CSSParser::NOT, 0);
}

CSSParser::SelectorListContext* CSSParser::PseudoClassContext::selectorList() {
  return getRuleContext<CSSParser::SelectorListContext>(0);
}


size_t CSSParser::PseudoClassContext::getRuleIndex() const {
  return CSSParser::RulePseudoClass;
}

void CSSParser::PseudoClassContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudoClass(this);
}

void CSSParser::PseudoClassContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudoClass(this);
}

CSSParser::PseudoClassContext* CSSParser::pseudoClass() {
  PseudoClassContext *_localctx = _tracker.createInstance<PseudoClassContext>(_ctx, getState());
  enterRule(_localctx, 28, CSSParser::RulePseudoClass);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(246);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(226);
      match(CSSParser::T__17);
      setState(227);
      match(CSSParser::IDENTIFIER);
      setState(232);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CSSParser::T__18) {
        setState(228);
        match(CSSParser::T__18);
        setState(229);
        pseudoClassArgument();
        setState(230);
        match(CSSParser::T__19);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(234);
      match(CSSParser::T__17);
      setState(235);
      match(CSSParser::NOT);
      setState(236);
      match(CSSParser::T__18);
      setState(237);
      selectorList();
      setState(238);
      match(CSSParser::T__19);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(240);
      match(CSSParser::T__17);
      setState(241);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 14680064) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(242);
      match(CSSParser::T__18);
      setState(243);
      selectorList();
      setState(244);
      match(CSSParser::T__19);
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

//----------------- PseudoClassArgumentContext ------------------------------------------------------------------

CSSParser::PseudoClassArgumentContext::PseudoClassArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::PseudoClassArgumentContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CSSParser::PseudoClassArgumentContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}

tree::TerminalNode* CSSParser::PseudoClassArgumentContext::STRING_LITERAL() {
  return getToken(CSSParser::STRING_LITERAL, 0);
}

CSSParser::ExpressionContext* CSSParser::PseudoClassArgumentContext::expression() {
  return getRuleContext<CSSParser::ExpressionContext>(0);
}


size_t CSSParser::PseudoClassArgumentContext::getRuleIndex() const {
  return CSSParser::RulePseudoClassArgument;
}

void CSSParser::PseudoClassArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudoClassArgument(this);
}

void CSSParser::PseudoClassArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudoClassArgument(this);
}

CSSParser::PseudoClassArgumentContext* CSSParser::pseudoClassArgument() {
  PseudoClassArgumentContext *_localctx = _tracker.createInstance<PseudoClassArgumentContext>(_ctx, getState());
  enterRule(_localctx, 30, CSSParser::RulePseudoClassArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(252);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(248);
      match(CSSParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(249);
      match(CSSParser::NUMBER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(250);
      match(CSSParser::STRING_LITERAL);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(251);
      expression();
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

//----------------- PseudoElementContext ------------------------------------------------------------------

CSSParser::PseudoElementContext::PseudoElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::PseudoElementContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}


size_t CSSParser::PseudoElementContext::getRuleIndex() const {
  return CSSParser::RulePseudoElement;
}

void CSSParser::PseudoElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudoElement(this);
}

void CSSParser::PseudoElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudoElement(this);
}

CSSParser::PseudoElementContext* CSSParser::pseudoElement() {
  PseudoElementContext *_localctx = _tracker.createInstance<PseudoElementContext>(_ctx, getState());
  enterRule(_localctx, 32, CSSParser::RulePseudoElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    match(CSSParser::T__23);
    setState(255);
    match(CSSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

CSSParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::PropertyContext* CSSParser::DeclarationContext::property() {
  return getRuleContext<CSSParser::PropertyContext>(0);
}

CSSParser::ValueContext* CSSParser::DeclarationContext::value() {
  return getRuleContext<CSSParser::ValueContext>(0);
}

tree::TerminalNode* CSSParser::DeclarationContext::IMPORTANT() {
  return getToken(CSSParser::IMPORTANT, 0);
}


size_t CSSParser::DeclarationContext::getRuleIndex() const {
  return CSSParser::RuleDeclaration;
}

void CSSParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void CSSParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}

CSSParser::DeclarationContext* CSSParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 34, CSSParser::RuleDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(257);
      property();
      setState(258);
      match(CSSParser::T__17);
      setState(259);
      value();
      setState(261);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CSSParser::IMPORTANT) {
        setState(260);
        match(CSSParser::IMPORTANT);
      }
      setState(263);
      match(CSSParser::T__24);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(265);
      property();
      setState(266);
      match(CSSParser::T__17);
      setState(267);
      value();
      setState(269);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CSSParser::IMPORTANT) {
        setState(268);
        match(CSSParser::IMPORTANT);
      }
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

//----------------- PropertyContext ------------------------------------------------------------------

CSSParser::PropertyContext::PropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CSSParser::PropertyContext::IDENTIFIER() {
  return getTokens(CSSParser::IDENTIFIER);
}

tree::TerminalNode* CSSParser::PropertyContext::IDENTIFIER(size_t i) {
  return getToken(CSSParser::IDENTIFIER, i);
}

tree::TerminalNode* CSSParser::PropertyContext::VARIABLE() {
  return getToken(CSSParser::VARIABLE, 0);
}


size_t CSSParser::PropertyContext::getRuleIndex() const {
  return CSSParser::RuleProperty;
}

void CSSParser::PropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty(this);
}

void CSSParser::PropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty(this);
}

CSSParser::PropertyContext* CSSParser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 36, CSSParser::RuleProperty);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(282);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(273);
        match(CSSParser::IDENTIFIER);
        setState(278);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CSSParser::T__25) {
          setState(274);
          match(CSSParser::T__25);
          setState(275);
          match(CSSParser::IDENTIFIER);
          setState(280);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case CSSParser::VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(281);
        match(CSSParser::VARIABLE);
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

//----------------- ValueContext ------------------------------------------------------------------

CSSParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::TermContext *> CSSParser::ValueContext::term() {
  return getRuleContexts<CSSParser::TermContext>();
}

CSSParser::TermContext* CSSParser::ValueContext::term(size_t i) {
  return getRuleContext<CSSParser::TermContext>(i);
}

std::vector<CSSParser::OperatorContext *> CSSParser::ValueContext::operator_() {
  return getRuleContexts<CSSParser::OperatorContext>();
}

CSSParser::OperatorContext* CSSParser::ValueContext::operator_(size_t i) {
  return getRuleContext<CSSParser::OperatorContext>(i);
}


size_t CSSParser::ValueContext::getRuleIndex() const {
  return CSSParser::RuleValue;
}

void CSSParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void CSSParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}

CSSParser::ValueContext* CSSParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 38, CSSParser::RuleValue);
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
    setState(284);
    term();
    setState(291);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(286);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CSSParser::T__2

        || _la == CSSParser::T__26 || _la == CSSParser::WS) {
          setState(285);
          operator_();
        }
        setState(288);
        term(); 
      }
      setState(293);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperatorContext ------------------------------------------------------------------

CSSParser::OperatorContext::OperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::OperatorContext::WS() {
  return getToken(CSSParser::WS, 0);
}


size_t CSSParser::OperatorContext::getRuleIndex() const {
  return CSSParser::RuleOperator;
}

void CSSParser::OperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperator(this);
}

void CSSParser::OperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperator(this);
}

CSSParser::OperatorContext* CSSParser::operator_() {
  OperatorContext *_localctx = _tracker.createInstance<OperatorContext>(_ctx, getState());
  enterRule(_localctx, 40, CSSParser::RuleOperator);
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
    setState(294);
    _la = _input->LA(1);
    if (!(_la == CSSParser::T__2

    || _la == CSSParser::T__26 || _la == CSSParser::WS)) {
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

//----------------- TermContext ------------------------------------------------------------------

CSSParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::NumericContext* CSSParser::TermContext::numeric() {
  return getRuleContext<CSSParser::NumericContext>(0);
}

CSSParser::PercentageContext* CSSParser::TermContext::percentage() {
  return getRuleContext<CSSParser::PercentageContext>(0);
}

CSSParser::LengthContext* CSSParser::TermContext::length() {
  return getRuleContext<CSSParser::LengthContext>(0);
}

CSSParser::AngleContext* CSSParser::TermContext::angle() {
  return getRuleContext<CSSParser::AngleContext>(0);
}

CSSParser::TimeContext* CSSParser::TermContext::time() {
  return getRuleContext<CSSParser::TimeContext>(0);
}

CSSParser::FrequencyContext* CSSParser::TermContext::frequency() {
  return getRuleContext<CSSParser::FrequencyContext>(0);
}

CSSParser::ResolutionContext* CSSParser::TermContext::resolution() {
  return getRuleContext<CSSParser::ResolutionContext>(0);
}

CSSParser::UnaryOperatorContext* CSSParser::TermContext::unaryOperator() {
  return getRuleContext<CSSParser::UnaryOperatorContext>(0);
}

tree::TerminalNode* CSSParser::TermContext::STRING_LITERAL() {
  return getToken(CSSParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CSSParser::TermContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CSSParser::TermContext::URI() {
  return getToken(CSSParser::URI, 0);
}

CSSParser::HexcolorContext* CSSParser::TermContext::hexcolor() {
  return getRuleContext<CSSParser::HexcolorContext>(0);
}

CSSParser::FunctionContext* CSSParser::TermContext::function() {
  return getRuleContext<CSSParser::FunctionContext>(0);
}

tree::TerminalNode* CSSParser::TermContext::VARIABLE() {
  return getToken(CSSParser::VARIABLE, 0);
}

CSSParser::CalcContext* CSSParser::TermContext::calc() {
  return getRuleContext<CSSParser::CalcContext>(0);
}


size_t CSSParser::TermContext::getRuleIndex() const {
  return CSSParser::RuleTerm;
}

void CSSParser::TermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerm(this);
}

void CSSParser::TermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerm(this);
}

CSSParser::TermContext* CSSParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 42, CSSParser::RuleTerm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(315);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(297);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CSSParser::T__4

      || _la == CSSParser::T__25) {
        setState(296);
        unaryOperator();
      }
      setState(306);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
      case 1: {
        setState(299);
        numeric();
        break;
      }

      case 2: {
        setState(300);
        percentage();
        break;
      }

      case 3: {
        setState(301);
        length();
        break;
      }

      case 4: {
        setState(302);
        angle();
        break;
      }

      case 5: {
        setState(303);
        time();
        break;
      }

      case 6: {
        setState(304);
        frequency();
        break;
      }

      case 7: {
        setState(305);
        resolution();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(308);
      match(CSSParser::STRING_LITERAL);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(309);
      match(CSSParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(310);
      match(CSSParser::URI);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(311);
      hexcolor();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(312);
      function();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(313);
      match(CSSParser::VARIABLE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(314);
      calc();
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

//----------------- UnaryOperatorContext ------------------------------------------------------------------

CSSParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CSSParser::UnaryOperatorContext::getRuleIndex() const {
  return CSSParser::RuleUnaryOperator;
}

void CSSParser::UnaryOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOperator(this);
}

void CSSParser::UnaryOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOperator(this);
}

CSSParser::UnaryOperatorContext* CSSParser::unaryOperator() {
  UnaryOperatorContext *_localctx = _tracker.createInstance<UnaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 44, CSSParser::RuleUnaryOperator);
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
    setState(317);
    _la = _input->LA(1);
    if (!(_la == CSSParser::T__4

    || _la == CSSParser::T__25)) {
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

//----------------- NumericContext ------------------------------------------------------------------

CSSParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::NumericContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}


size_t CSSParser::NumericContext::getRuleIndex() const {
  return CSSParser::RuleNumeric;
}

void CSSParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void CSSParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}

CSSParser::NumericContext* CSSParser::numeric() {
  NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, getState());
  enterRule(_localctx, 46, CSSParser::RuleNumeric);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(319);
    match(CSSParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PercentageContext ------------------------------------------------------------------

CSSParser::PercentageContext::PercentageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::PercentageContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}


size_t CSSParser::PercentageContext::getRuleIndex() const {
  return CSSParser::RulePercentage;
}

void CSSParser::PercentageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPercentage(this);
}

void CSSParser::PercentageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPercentage(this);
}

CSSParser::PercentageContext* CSSParser::percentage() {
  PercentageContext *_localctx = _tracker.createInstance<PercentageContext>(_ctx, getState());
  enterRule(_localctx, 48, CSSParser::RulePercentage);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    match(CSSParser::NUMBER);
    setState(322);
    match(CSSParser::T__27);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LengthContext ------------------------------------------------------------------

CSSParser::LengthContext::LengthContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::LengthContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}

tree::TerminalNode* CSSParser::LengthContext::PX() {
  return getToken(CSSParser::PX, 0);
}

tree::TerminalNode* CSSParser::LengthContext::EM() {
  return getToken(CSSParser::EM, 0);
}

tree::TerminalNode* CSSParser::LengthContext::REM() {
  return getToken(CSSParser::REM, 0);
}

tree::TerminalNode* CSSParser::LengthContext::VH() {
  return getToken(CSSParser::VH, 0);
}

tree::TerminalNode* CSSParser::LengthContext::VW() {
  return getToken(CSSParser::VW, 0);
}

tree::TerminalNode* CSSParser::LengthContext::VMIN() {
  return getToken(CSSParser::VMIN, 0);
}

tree::TerminalNode* CSSParser::LengthContext::VMAX() {
  return getToken(CSSParser::VMAX, 0);
}

tree::TerminalNode* CSSParser::LengthContext::CH() {
  return getToken(CSSParser::CH, 0);
}

tree::TerminalNode* CSSParser::LengthContext::EX() {
  return getToken(CSSParser::EX, 0);
}

tree::TerminalNode* CSSParser::LengthContext::CM() {
  return getToken(CSSParser::CM, 0);
}

tree::TerminalNode* CSSParser::LengthContext::MM() {
  return getToken(CSSParser::MM, 0);
}

tree::TerminalNode* CSSParser::LengthContext::IN() {
  return getToken(CSSParser::IN, 0);
}

tree::TerminalNode* CSSParser::LengthContext::PT() {
  return getToken(CSSParser::PT, 0);
}

tree::TerminalNode* CSSParser::LengthContext::PC() {
  return getToken(CSSParser::PC, 0);
}


size_t CSSParser::LengthContext::getRuleIndex() const {
  return CSSParser::RuleLength;
}

void CSSParser::LengthContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLength(this);
}

void CSSParser::LengthContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLength(this);
}

CSSParser::LengthContext* CSSParser::length() {
  LengthContext *_localctx = _tracker.createInstance<LengthContext>(_ctx, getState());
  enterRule(_localctx, 50, CSSParser::RuleLength);
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
    match(CSSParser::NUMBER);
    setState(325);
    _la = _input->LA(1);
    if (!(((((_la - 51) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 51)) & 16383) != 0))) {
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

//----------------- AngleContext ------------------------------------------------------------------

CSSParser::AngleContext::AngleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AngleContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}

tree::TerminalNode* CSSParser::AngleContext::DEG() {
  return getToken(CSSParser::DEG, 0);
}

tree::TerminalNode* CSSParser::AngleContext::RAD() {
  return getToken(CSSParser::RAD, 0);
}

tree::TerminalNode* CSSParser::AngleContext::GRAD() {
  return getToken(CSSParser::GRAD, 0);
}

tree::TerminalNode* CSSParser::AngleContext::TURN() {
  return getToken(CSSParser::TURN, 0);
}


size_t CSSParser::AngleContext::getRuleIndex() const {
  return CSSParser::RuleAngle;
}

void CSSParser::AngleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAngle(this);
}

void CSSParser::AngleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAngle(this);
}

CSSParser::AngleContext* CSSParser::angle() {
  AngleContext *_localctx = _tracker.createInstance<AngleContext>(_ctx, getState());
  enterRule(_localctx, 52, CSSParser::RuleAngle);
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
    setState(327);
    match(CSSParser::NUMBER);
    setState(328);
    _la = _input->LA(1);
    if (!(((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 15) != 0))) {
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

//----------------- TimeContext ------------------------------------------------------------------

CSSParser::TimeContext::TimeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::TimeContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}

tree::TerminalNode* CSSParser::TimeContext::S() {
  return getToken(CSSParser::S, 0);
}

tree::TerminalNode* CSSParser::TimeContext::MS() {
  return getToken(CSSParser::MS, 0);
}


size_t CSSParser::TimeContext::getRuleIndex() const {
  return CSSParser::RuleTime;
}

void CSSParser::TimeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTime(this);
}

void CSSParser::TimeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTime(this);
}

CSSParser::TimeContext* CSSParser::time() {
  TimeContext *_localctx = _tracker.createInstance<TimeContext>(_ctx, getState());
  enterRule(_localctx, 54, CSSParser::RuleTime);
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
    match(CSSParser::NUMBER);
    setState(331);
    _la = _input->LA(1);
    if (!(_la == CSSParser::S

    || _la == CSSParser::MS)) {
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

//----------------- FrequencyContext ------------------------------------------------------------------

CSSParser::FrequencyContext::FrequencyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::FrequencyContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}

tree::TerminalNode* CSSParser::FrequencyContext::HZ() {
  return getToken(CSSParser::HZ, 0);
}

tree::TerminalNode* CSSParser::FrequencyContext::KHZ() {
  return getToken(CSSParser::KHZ, 0);
}


size_t CSSParser::FrequencyContext::getRuleIndex() const {
  return CSSParser::RuleFrequency;
}

void CSSParser::FrequencyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFrequency(this);
}

void CSSParser::FrequencyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFrequency(this);
}

CSSParser::FrequencyContext* CSSParser::frequency() {
  FrequencyContext *_localctx = _tracker.createInstance<FrequencyContext>(_ctx, getState());
  enterRule(_localctx, 56, CSSParser::RuleFrequency);
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
    setState(333);
    match(CSSParser::NUMBER);
    setState(334);
    _la = _input->LA(1);
    if (!(_la == CSSParser::HZ

    || _la == CSSParser::KHZ)) {
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

//----------------- ResolutionContext ------------------------------------------------------------------

CSSParser::ResolutionContext::ResolutionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::ResolutionContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}

tree::TerminalNode* CSSParser::ResolutionContext::DPI() {
  return getToken(CSSParser::DPI, 0);
}

tree::TerminalNode* CSSParser::ResolutionContext::DPCM() {
  return getToken(CSSParser::DPCM, 0);
}

tree::TerminalNode* CSSParser::ResolutionContext::DPPX() {
  return getToken(CSSParser::DPPX, 0);
}


size_t CSSParser::ResolutionContext::getRuleIndex() const {
  return CSSParser::RuleResolution;
}

void CSSParser::ResolutionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterResolution(this);
}

void CSSParser::ResolutionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitResolution(this);
}

CSSParser::ResolutionContext* CSSParser::resolution() {
  ResolutionContext *_localctx = _tracker.createInstance<ResolutionContext>(_ctx, getState());
  enterRule(_localctx, 58, CSSParser::RuleResolution);
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
    setState(336);
    match(CSSParser::NUMBER);
    setState(337);
    _la = _input->LA(1);
    if (!(((((_la - 73) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 73)) & 7) != 0))) {
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

//----------------- HexcolorContext ------------------------------------------------------------------

CSSParser::HexcolorContext::HexcolorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CSSParser::HexcolorContext::HEX_DIGIT() {
  return getTokens(CSSParser::HEX_DIGIT);
}

tree::TerminalNode* CSSParser::HexcolorContext::HEX_DIGIT(size_t i) {
  return getToken(CSSParser::HEX_DIGIT, i);
}


size_t CSSParser::HexcolorContext::getRuleIndex() const {
  return CSSParser::RuleHexcolor;
}

void CSSParser::HexcolorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHexcolor(this);
}

void CSSParser::HexcolorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHexcolor(this);
}

CSSParser::HexcolorContext* CSSParser::hexcolor() {
  HexcolorContext *_localctx = _tracker.createInstance<HexcolorContext>(_ctx, getState());
  enterRule(_localctx, 60, CSSParser::RuleHexcolor);
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
    setState(339);
    match(CSSParser::T__7);
    setState(341); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(340);
      match(CSSParser::HEX_DIGIT);
      setState(343); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CSSParser::HEX_DIGIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

CSSParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::FunctionContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}

CSSParser::FunctionArgumentsContext* CSSParser::FunctionContext::functionArguments() {
  return getRuleContext<CSSParser::FunctionArgumentsContext>(0);
}


size_t CSSParser::FunctionContext::getRuleIndex() const {
  return CSSParser::RuleFunction;
}

void CSSParser::FunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction(this);
}

void CSSParser::FunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction(this);
}

CSSParser::FunctionContext* CSSParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 62, CSSParser::RuleFunction);
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
    setState(345);
    match(CSSParser::IDENTIFIER);
    setState(346);
    match(CSSParser::T__18);
    setState(348);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 603980064) != 0) || ((((_la - 76) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 76)) & 31) != 0)) {
      setState(347);
      functionArguments();
    }
    setState(350);
    match(CSSParser::T__19);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgumentsContext ------------------------------------------------------------------

CSSParser::FunctionArgumentsContext::FunctionArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::FunctionArgumentContext *> CSSParser::FunctionArgumentsContext::functionArgument() {
  return getRuleContexts<CSSParser::FunctionArgumentContext>();
}

CSSParser::FunctionArgumentContext* CSSParser::FunctionArgumentsContext::functionArgument(size_t i) {
  return getRuleContext<CSSParser::FunctionArgumentContext>(i);
}


size_t CSSParser::FunctionArgumentsContext::getRuleIndex() const {
  return CSSParser::RuleFunctionArguments;
}

void CSSParser::FunctionArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArguments(this);
}

void CSSParser::FunctionArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArguments(this);
}

CSSParser::FunctionArgumentsContext* CSSParser::functionArguments() {
  FunctionArgumentsContext *_localctx = _tracker.createInstance<FunctionArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 64, CSSParser::RuleFunctionArguments);
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
    setState(352);
    functionArgument();
    setState(357);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::T__2) {
      setState(353);
      match(CSSParser::T__2);
      setState(354);
      functionArgument();
      setState(359);
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

//----------------- FunctionArgumentContext ------------------------------------------------------------------

CSSParser::FunctionArgumentContext::FunctionArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::ValueContext* CSSParser::FunctionArgumentContext::value() {
  return getRuleContext<CSSParser::ValueContext>(0);
}


size_t CSSParser::FunctionArgumentContext::getRuleIndex() const {
  return CSSParser::RuleFunctionArgument;
}

void CSSParser::FunctionArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArgument(this);
}

void CSSParser::FunctionArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArgument(this);
}

CSSParser::FunctionArgumentContext* CSSParser::functionArgument() {
  FunctionArgumentContext *_localctx = _tracker.createInstance<FunctionArgumentContext>(_ctx, getState());
  enterRule(_localctx, 66, CSSParser::RuleFunctionArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(360);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CalcContext ------------------------------------------------------------------

CSSParser::CalcContext::CalcContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::CalcExpressionContext* CSSParser::CalcContext::calcExpression() {
  return getRuleContext<CSSParser::CalcExpressionContext>(0);
}


size_t CSSParser::CalcContext::getRuleIndex() const {
  return CSSParser::RuleCalc;
}

void CSSParser::CalcContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalc(this);
}

void CSSParser::CalcContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalc(this);
}

CSSParser::CalcContext* CSSParser::calc() {
  CalcContext *_localctx = _tracker.createInstance<CalcContext>(_ctx, getState());
  enterRule(_localctx, 68, CSSParser::RuleCalc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
    match(CSSParser::T__28);
    setState(363);
    match(CSSParser::T__18);
    setState(364);
    calcExpression();
    setState(365);
    match(CSSParser::T__19);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CalcExpressionContext ------------------------------------------------------------------

CSSParser::CalcExpressionContext::CalcExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::CalcTermContext *> CSSParser::CalcExpressionContext::calcTerm() {
  return getRuleContexts<CSSParser::CalcTermContext>();
}

CSSParser::CalcTermContext* CSSParser::CalcExpressionContext::calcTerm(size_t i) {
  return getRuleContext<CSSParser::CalcTermContext>(i);
}


size_t CSSParser::CalcExpressionContext::getRuleIndex() const {
  return CSSParser::RuleCalcExpression;
}

void CSSParser::CalcExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalcExpression(this);
}

void CSSParser::CalcExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalcExpression(this);
}

CSSParser::CalcExpressionContext* CSSParser::calcExpression() {
  CalcExpressionContext *_localctx = _tracker.createInstance<CalcExpressionContext>(_ctx, getState());
  enterRule(_localctx, 70, CSSParser::RuleCalcExpression);
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
    setState(367);
    calcTerm();
    setState(372);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::T__4

    || _la == CSSParser::T__25) {
      setState(368);
      _la = _input->LA(1);
      if (!(_la == CSSParser::T__4

      || _la == CSSParser::T__25)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(369);
      calcTerm();
      setState(374);
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

//----------------- CalcTermContext ------------------------------------------------------------------

CSSParser::CalcTermContext::CalcTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::CalcFactorContext *> CSSParser::CalcTermContext::calcFactor() {
  return getRuleContexts<CSSParser::CalcFactorContext>();
}

CSSParser::CalcFactorContext* CSSParser::CalcTermContext::calcFactor(size_t i) {
  return getRuleContext<CSSParser::CalcFactorContext>(i);
}


size_t CSSParser::CalcTermContext::getRuleIndex() const {
  return CSSParser::RuleCalcTerm;
}

void CSSParser::CalcTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalcTerm(this);
}

void CSSParser::CalcTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalcTerm(this);
}

CSSParser::CalcTermContext* CSSParser::calcTerm() {
  CalcTermContext *_localctx = _tracker.createInstance<CalcTermContext>(_ctx, getState());
  enterRule(_localctx, 72, CSSParser::RuleCalcTerm);
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
    setState(375);
    calcFactor();
    setState(380);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::T__6

    || _la == CSSParser::T__26) {
      setState(376);
      _la = _input->LA(1);
      if (!(_la == CSSParser::T__6

      || _la == CSSParser::T__26)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(377);
      calcFactor();
      setState(382);
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

//----------------- CalcFactorContext ------------------------------------------------------------------

CSSParser::CalcFactorContext::CalcFactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::NumericContext* CSSParser::CalcFactorContext::numeric() {
  return getRuleContext<CSSParser::NumericContext>(0);
}

CSSParser::LengthContext* CSSParser::CalcFactorContext::length() {
  return getRuleContext<CSSParser::LengthContext>(0);
}

CSSParser::PercentageContext* CSSParser::CalcFactorContext::percentage() {
  return getRuleContext<CSSParser::PercentageContext>(0);
}

CSSParser::CalcExpressionContext* CSSParser::CalcFactorContext::calcExpression() {
  return getRuleContext<CSSParser::CalcExpressionContext>(0);
}

CSSParser::CalcContext* CSSParser::CalcFactorContext::calc() {
  return getRuleContext<CSSParser::CalcContext>(0);
}

tree::TerminalNode* CSSParser::CalcFactorContext::VARIABLE() {
  return getToken(CSSParser::VARIABLE, 0);
}


size_t CSSParser::CalcFactorContext::getRuleIndex() const {
  return CSSParser::RuleCalcFactor;
}

void CSSParser::CalcFactorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalcFactor(this);
}

void CSSParser::CalcFactorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalcFactor(this);
}

CSSParser::CalcFactorContext* CSSParser::calcFactor() {
  CalcFactorContext *_localctx = _tracker.createInstance<CalcFactorContext>(_ctx, getState());
  enterRule(_localctx, 74, CSSParser::RuleCalcFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(392);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(383);
      numeric();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(384);
      length();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(385);
      percentage();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(386);
      match(CSSParser::T__18);
      setState(387);
      calcExpression();
      setState(388);
      match(CSSParser::T__19);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(390);
      calc();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(391);
      match(CSSParser::VARIABLE);
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

//----------------- AtRuleContext ------------------------------------------------------------------

CSSParser::AtRuleContext::AtRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::AtImportContext* CSSParser::AtRuleContext::atImport() {
  return getRuleContext<CSSParser::AtImportContext>(0);
}

CSSParser::AtMediaContext* CSSParser::AtRuleContext::atMedia() {
  return getRuleContext<CSSParser::AtMediaContext>(0);
}

CSSParser::AtKeyframesContext* CSSParser::AtRuleContext::atKeyframes() {
  return getRuleContext<CSSParser::AtKeyframesContext>(0);
}

CSSParser::AtFontFaceContext* CSSParser::AtRuleContext::atFontFace() {
  return getRuleContext<CSSParser::AtFontFaceContext>(0);
}

CSSParser::AtSupportsContext* CSSParser::AtRuleContext::atSupports() {
  return getRuleContext<CSSParser::AtSupportsContext>(0);
}

CSSParser::AtPageContext* CSSParser::AtRuleContext::atPage() {
  return getRuleContext<CSSParser::AtPageContext>(0);
}

CSSParser::AtNamespaceContext* CSSParser::AtRuleContext::atNamespace() {
  return getRuleContext<CSSParser::AtNamespaceContext>(0);
}

CSSParser::AtCharsetContext* CSSParser::AtRuleContext::atCharset() {
  return getRuleContext<CSSParser::AtCharsetContext>(0);
}

CSSParser::AtViewportContext* CSSParser::AtRuleContext::atViewport() {
  return getRuleContext<CSSParser::AtViewportContext>(0);
}

CSSParser::AtCounterStyleContext* CSSParser::AtRuleContext::atCounterStyle() {
  return getRuleContext<CSSParser::AtCounterStyleContext>(0);
}

CSSParser::AtFontFeatureValuesContext* CSSParser::AtRuleContext::atFontFeatureValues() {
  return getRuleContext<CSSParser::AtFontFeatureValuesContext>(0);
}

CSSParser::AtPropertyContext* CSSParser::AtRuleContext::atProperty() {
  return getRuleContext<CSSParser::AtPropertyContext>(0);
}


size_t CSSParser::AtRuleContext::getRuleIndex() const {
  return CSSParser::RuleAtRule;
}

void CSSParser::AtRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtRule(this);
}

void CSSParser::AtRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtRule(this);
}

CSSParser::AtRuleContext* CSSParser::atRule() {
  AtRuleContext *_localctx = _tracker.createInstance<AtRuleContext>(_ctx, getState());
  enterRule(_localctx, 76, CSSParser::RuleAtRule);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(406);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::IMPORT: {
        enterOuterAlt(_localctx, 1);
        setState(394);
        atImport();
        break;
      }

      case CSSParser::MEDIA: {
        enterOuterAlt(_localctx, 2);
        setState(395);
        atMedia();
        break;
      }

      case CSSParser::KEYFRAMES: {
        enterOuterAlt(_localctx, 3);
        setState(396);
        atKeyframes();
        break;
      }

      case CSSParser::FONT_FACE: {
        enterOuterAlt(_localctx, 4);
        setState(397);
        atFontFace();
        break;
      }

      case CSSParser::SUPPORTS: {
        enterOuterAlt(_localctx, 5);
        setState(398);
        atSupports();
        break;
      }

      case CSSParser::PAGE: {
        enterOuterAlt(_localctx, 6);
        setState(399);
        atPage();
        break;
      }

      case CSSParser::NAMESPACE: {
        enterOuterAlt(_localctx, 7);
        setState(400);
        atNamespace();
        break;
      }

      case CSSParser::CHARSET: {
        enterOuterAlt(_localctx, 8);
        setState(401);
        atCharset();
        break;
      }

      case CSSParser::VIEWPORT: {
        enterOuterAlt(_localctx, 9);
        setState(402);
        atViewport();
        break;
      }

      case CSSParser::COUNTER_STYLE: {
        enterOuterAlt(_localctx, 10);
        setState(403);
        atCounterStyle();
        break;
      }

      case CSSParser::FONT_FEATURE_VALUES: {
        enterOuterAlt(_localctx, 11);
        setState(404);
        atFontFeatureValues();
        break;
      }

      case CSSParser::PROPERTY: {
        enterOuterAlt(_localctx, 12);
        setState(405);
        atProperty();
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

//----------------- AtImportContext ------------------------------------------------------------------

CSSParser::AtImportContext::AtImportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtImportContext::IMPORT() {
  return getToken(CSSParser::IMPORT, 0);
}

tree::TerminalNode* CSSParser::AtImportContext::STRING_LITERAL() {
  return getToken(CSSParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CSSParser::AtImportContext::URI() {
  return getToken(CSSParser::URI, 0);
}

CSSParser::MediaQueryListContext* CSSParser::AtImportContext::mediaQueryList() {
  return getRuleContext<CSSParser::MediaQueryListContext>(0);
}


size_t CSSParser::AtImportContext::getRuleIndex() const {
  return CSSParser::RuleAtImport;
}

void CSSParser::AtImportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtImport(this);
}

void CSSParser::AtImportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtImport(this);
}

CSSParser::AtImportContext* CSSParser::atImport() {
  AtImportContext *_localctx = _tracker.createInstance<AtImportContext>(_ctx, getState());
  enterRule(_localctx, 78, CSSParser::RuleAtImport);
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
    setState(408);
    match(CSSParser::IMPORT);
    setState(409);
    _la = _input->LA(1);
    if (!(_la == CSSParser::STRING_LITERAL

    || _la == CSSParser::URI)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(411);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 19) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 19)) & 2305843009314357249) != 0)) {
      setState(410);
      mediaQueryList();
    }
    setState(413);
    match(CSSParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtMediaContext ------------------------------------------------------------------

CSSParser::AtMediaContext::AtMediaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtMediaContext::MEDIA() {
  return getToken(CSSParser::MEDIA, 0);
}

CSSParser::MediaQueryListContext* CSSParser::AtMediaContext::mediaQueryList() {
  return getRuleContext<CSSParser::MediaQueryListContext>(0);
}

std::vector<CSSParser::StatementContext *> CSSParser::AtMediaContext::statement() {
  return getRuleContexts<CSSParser::StatementContext>();
}

CSSParser::StatementContext* CSSParser::AtMediaContext::statement(size_t i) {
  return getRuleContext<CSSParser::StatementContext>(i);
}


size_t CSSParser::AtMediaContext::getRuleIndex() const {
  return CSSParser::RuleAtMedia;
}

void CSSParser::AtMediaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtMedia(this);
}

void CSSParser::AtMediaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtMedia(this);
}

CSSParser::AtMediaContext* CSSParser::atMedia() {
  AtMediaContext *_localctx = _tracker.createInstance<AtMediaContext>(_ctx, getState());
  enterRule(_localctx, 80, CSSParser::RuleAtMedia);
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
    setState(415);
    match(CSSParser::MEDIA);
    setState(416);
    mediaQueryList();
    setState(417);
    match(CSSParser::T__0);
    setState(421);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17590055602170) != 0) || _la == CSSParser::IDENTIFIER

    || _la == CSSParser::WS) {
      setState(418);
      statement();
      setState(423);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(424);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaQueryListContext ------------------------------------------------------------------

CSSParser::MediaQueryListContext::MediaQueryListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::MediaQueryContext *> CSSParser::MediaQueryListContext::mediaQuery() {
  return getRuleContexts<CSSParser::MediaQueryContext>();
}

CSSParser::MediaQueryContext* CSSParser::MediaQueryListContext::mediaQuery(size_t i) {
  return getRuleContext<CSSParser::MediaQueryContext>(i);
}


size_t CSSParser::MediaQueryListContext::getRuleIndex() const {
  return CSSParser::RuleMediaQueryList;
}

void CSSParser::MediaQueryListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaQueryList(this);
}

void CSSParser::MediaQueryListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaQueryList(this);
}

CSSParser::MediaQueryListContext* CSSParser::mediaQueryList() {
  MediaQueryListContext *_localctx = _tracker.createInstance<MediaQueryListContext>(_ctx, getState());
  enterRule(_localctx, 82, CSSParser::RuleMediaQueryList);
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
    setState(426);
    mediaQuery();
    setState(431);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::T__2) {
      setState(427);
      match(CSSParser::T__2);
      setState(428);
      mediaQuery();
      setState(433);
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

//----------------- MediaQueryContext ------------------------------------------------------------------

CSSParser::MediaQueryContext::MediaQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::MediaTypeContext* CSSParser::MediaQueryContext::mediaType() {
  return getRuleContext<CSSParser::MediaTypeContext>(0);
}

std::vector<tree::TerminalNode *> CSSParser::MediaQueryContext::AND() {
  return getTokens(CSSParser::AND);
}

tree::TerminalNode* CSSParser::MediaQueryContext::AND(size_t i) {
  return getToken(CSSParser::AND, i);
}

std::vector<CSSParser::MediaFeatureContext *> CSSParser::MediaQueryContext::mediaFeature() {
  return getRuleContexts<CSSParser::MediaFeatureContext>();
}

CSSParser::MediaFeatureContext* CSSParser::MediaQueryContext::mediaFeature(size_t i) {
  return getRuleContext<CSSParser::MediaFeatureContext>(i);
}

tree::TerminalNode* CSSParser::MediaQueryContext::ONLY() {
  return getToken(CSSParser::ONLY, 0);
}

tree::TerminalNode* CSSParser::MediaQueryContext::NOT() {
  return getToken(CSSParser::NOT, 0);
}


size_t CSSParser::MediaQueryContext::getRuleIndex() const {
  return CSSParser::RuleMediaQuery;
}

void CSSParser::MediaQueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaQuery(this);
}

void CSSParser::MediaQueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaQuery(this);
}

CSSParser::MediaQueryContext* CSSParser::mediaQuery() {
  MediaQueryContext *_localctx = _tracker.createInstance<MediaQueryContext>(_ctx, getState());
  enterRule(_localctx, 84, CSSParser::RuleMediaQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(453);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::ONLY:
      case CSSParser::NOT:
      case CSSParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(435);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CSSParser::ONLY

        || _la == CSSParser::NOT) {
          setState(434);
          _la = _input->LA(1);
          if (!(_la == CSSParser::ONLY

          || _la == CSSParser::NOT)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
        }
        setState(437);
        mediaType();
        setState(442);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CSSParser::AND) {
          setState(438);
          match(CSSParser::AND);
          setState(439);
          mediaFeature();
          setState(444);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case CSSParser::T__18: {
        enterOuterAlt(_localctx, 2);
        setState(445);
        mediaFeature();
        setState(450);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CSSParser::AND) {
          setState(446);
          match(CSSParser::AND);
          setState(447);
          mediaFeature();
          setState(452);
          _errHandler->sync(this);
          _la = _input->LA(1);
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

//----------------- MediaTypeContext ------------------------------------------------------------------

CSSParser::MediaTypeContext::MediaTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::MediaTypeContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}


size_t CSSParser::MediaTypeContext::getRuleIndex() const {
  return CSSParser::RuleMediaType;
}

void CSSParser::MediaTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaType(this);
}

void CSSParser::MediaTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaType(this);
}

CSSParser::MediaTypeContext* CSSParser::mediaType() {
  MediaTypeContext *_localctx = _tracker.createInstance<MediaTypeContext>(_ctx, getState());
  enterRule(_localctx, 86, CSSParser::RuleMediaType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(455);
    match(CSSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaFeatureContext ------------------------------------------------------------------

CSSParser::MediaFeatureContext::MediaFeatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::MediaFeatureContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}

CSSParser::ValueContext* CSSParser::MediaFeatureContext::value() {
  return getRuleContext<CSSParser::ValueContext>(0);
}


size_t CSSParser::MediaFeatureContext::getRuleIndex() const {
  return CSSParser::RuleMediaFeature;
}

void CSSParser::MediaFeatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaFeature(this);
}

void CSSParser::MediaFeatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaFeature(this);
}

CSSParser::MediaFeatureContext* CSSParser::mediaFeature() {
  MediaFeatureContext *_localctx = _tracker.createInstance<MediaFeatureContext>(_ctx, getState());
  enterRule(_localctx, 88, CSSParser::RuleMediaFeature);
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
    setState(457);
    match(CSSParser::T__18);
    setState(458);
    match(CSSParser::IDENTIFIER);
    setState(461);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::T__17) {
      setState(459);
      match(CSSParser::T__17);
      setState(460);
      value();
    }
    setState(463);
    match(CSSParser::T__19);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtKeyframesContext ------------------------------------------------------------------

CSSParser::AtKeyframesContext::AtKeyframesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtKeyframesContext::KEYFRAMES() {
  return getToken(CSSParser::KEYFRAMES, 0);
}

tree::TerminalNode* CSSParser::AtKeyframesContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}

std::vector<CSSParser::KeyframeBlockContext *> CSSParser::AtKeyframesContext::keyframeBlock() {
  return getRuleContexts<CSSParser::KeyframeBlockContext>();
}

CSSParser::KeyframeBlockContext* CSSParser::AtKeyframesContext::keyframeBlock(size_t i) {
  return getRuleContext<CSSParser::KeyframeBlockContext>(i);
}


size_t CSSParser::AtKeyframesContext::getRuleIndex() const {
  return CSSParser::RuleAtKeyframes;
}

void CSSParser::AtKeyframesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtKeyframes(this);
}

void CSSParser::AtKeyframesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtKeyframes(this);
}

CSSParser::AtKeyframesContext* CSSParser::atKeyframes() {
  AtKeyframesContext *_localctx = _tracker.createInstance<AtKeyframesContext>(_ctx, getState());
  enterRule(_localctx, 90, CSSParser::RuleAtKeyframes);
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
    setState(465);
    match(CSSParser::KEYFRAMES);
    setState(466);
    match(CSSParser::IDENTIFIER);
    setState(467);
    match(CSSParser::T__0);
    setState(471);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 48) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 48)) & 536870915) != 0)) {
      setState(468);
      keyframeBlock();
      setState(473);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(474);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyframeBlockContext ------------------------------------------------------------------

CSSParser::KeyframeBlockContext::KeyframeBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::KeyframeSelectorContext* CSSParser::KeyframeBlockContext::keyframeSelector() {
  return getRuleContext<CSSParser::KeyframeSelectorContext>(0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::KeyframeBlockContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::KeyframeBlockContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::KeyframeBlockContext::getRuleIndex() const {
  return CSSParser::RuleKeyframeBlock;
}

void CSSParser::KeyframeBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyframeBlock(this);
}

void CSSParser::KeyframeBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyframeBlock(this);
}

CSSParser::KeyframeBlockContext* CSSParser::keyframeBlock() {
  KeyframeBlockContext *_localctx = _tracker.createInstance<KeyframeBlockContext>(_ctx, getState());
  enterRule(_localctx, 92, CSSParser::RuleKeyframeBlock);
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
    setState(476);
    keyframeSelector(0);
    setState(477);
    match(CSSParser::T__0);
    setState(481);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::VARIABLE

    || _la == CSSParser::IDENTIFIER) {
      setState(478);
      declaration();
      setState(483);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(484);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyframeSelectorContext ------------------------------------------------------------------

CSSParser::KeyframeSelectorContext::KeyframeSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::KeyframeSelectorContext::FROM() {
  return getToken(CSSParser::FROM, 0);
}

tree::TerminalNode* CSSParser::KeyframeSelectorContext::TO() {
  return getToken(CSSParser::TO, 0);
}

CSSParser::PercentageContext* CSSParser::KeyframeSelectorContext::percentage() {
  return getRuleContext<CSSParser::PercentageContext>(0);
}

std::vector<CSSParser::KeyframeSelectorContext *> CSSParser::KeyframeSelectorContext::keyframeSelector() {
  return getRuleContexts<CSSParser::KeyframeSelectorContext>();
}

CSSParser::KeyframeSelectorContext* CSSParser::KeyframeSelectorContext::keyframeSelector(size_t i) {
  return getRuleContext<CSSParser::KeyframeSelectorContext>(i);
}


size_t CSSParser::KeyframeSelectorContext::getRuleIndex() const {
  return CSSParser::RuleKeyframeSelector;
}

void CSSParser::KeyframeSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyframeSelector(this);
}

void CSSParser::KeyframeSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyframeSelector(this);
}


CSSParser::KeyframeSelectorContext* CSSParser::keyframeSelector() {
   return keyframeSelector(0);
}

CSSParser::KeyframeSelectorContext* CSSParser::keyframeSelector(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CSSParser::KeyframeSelectorContext *_localctx = _tracker.createInstance<KeyframeSelectorContext>(_ctx, parentState);
  CSSParser::KeyframeSelectorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 94;
  enterRecursionRule(_localctx, 94, CSSParser::RuleKeyframeSelector, precedence);

    

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
    setState(490);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::FROM: {
        setState(487);
        match(CSSParser::FROM);
        break;
      }

      case CSSParser::TO: {
        setState(488);
        match(CSSParser::TO);
        break;
      }

      case CSSParser::NUMBER: {
        setState(489);
        percentage();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(497);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<KeyframeSelectorContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleKeyframeSelector);
        setState(492);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(493);
        match(CSSParser::T__2);
        setState(494);
        keyframeSelector(2); 
      }
      setState(499);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AtFontFaceContext ------------------------------------------------------------------

CSSParser::AtFontFaceContext::AtFontFaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtFontFaceContext::FONT_FACE() {
  return getToken(CSSParser::FONT_FACE, 0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::AtFontFaceContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::AtFontFaceContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::AtFontFaceContext::getRuleIndex() const {
  return CSSParser::RuleAtFontFace;
}

void CSSParser::AtFontFaceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtFontFace(this);
}

void CSSParser::AtFontFaceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtFontFace(this);
}

CSSParser::AtFontFaceContext* CSSParser::atFontFace() {
  AtFontFaceContext *_localctx = _tracker.createInstance<AtFontFaceContext>(_ctx, getState());
  enterRule(_localctx, 96, CSSParser::RuleAtFontFace);
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
    setState(500);
    match(CSSParser::FONT_FACE);
    setState(501);
    match(CSSParser::T__0);
    setState(505);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::VARIABLE

    || _la == CSSParser::IDENTIFIER) {
      setState(502);
      declaration();
      setState(507);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(508);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtSupportsContext ------------------------------------------------------------------

CSSParser::AtSupportsContext::AtSupportsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtSupportsContext::SUPPORTS() {
  return getToken(CSSParser::SUPPORTS, 0);
}

CSSParser::SupportsConditionContext* CSSParser::AtSupportsContext::supportsCondition() {
  return getRuleContext<CSSParser::SupportsConditionContext>(0);
}

std::vector<CSSParser::StatementContext *> CSSParser::AtSupportsContext::statement() {
  return getRuleContexts<CSSParser::StatementContext>();
}

CSSParser::StatementContext* CSSParser::AtSupportsContext::statement(size_t i) {
  return getRuleContext<CSSParser::StatementContext>(i);
}


size_t CSSParser::AtSupportsContext::getRuleIndex() const {
  return CSSParser::RuleAtSupports;
}

void CSSParser::AtSupportsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtSupports(this);
}

void CSSParser::AtSupportsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtSupports(this);
}

CSSParser::AtSupportsContext* CSSParser::atSupports() {
  AtSupportsContext *_localctx = _tracker.createInstance<AtSupportsContext>(_ctx, getState());
  enterRule(_localctx, 98, CSSParser::RuleAtSupports);
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
    setState(510);
    match(CSSParser::SUPPORTS);
    setState(511);
    supportsCondition();
    setState(512);
    match(CSSParser::T__0);
    setState(516);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17590055602170) != 0) || _la == CSSParser::IDENTIFIER

    || _la == CSSParser::WS) {
      setState(513);
      statement();
      setState(518);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(519);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsConditionContext ------------------------------------------------------------------

CSSParser::SupportsConditionContext::SupportsConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::SupportsNegationContext* CSSParser::SupportsConditionContext::supportsNegation() {
  return getRuleContext<CSSParser::SupportsNegationContext>(0);
}

CSSParser::SupportsConjunctionContext* CSSParser::SupportsConditionContext::supportsConjunction() {
  return getRuleContext<CSSParser::SupportsConjunctionContext>(0);
}

CSSParser::SupportsDisjunctionContext* CSSParser::SupportsConditionContext::supportsDisjunction() {
  return getRuleContext<CSSParser::SupportsDisjunctionContext>(0);
}

CSSParser::SupportsInParensContext* CSSParser::SupportsConditionContext::supportsInParens() {
  return getRuleContext<CSSParser::SupportsInParensContext>(0);
}


size_t CSSParser::SupportsConditionContext::getRuleIndex() const {
  return CSSParser::RuleSupportsCondition;
}

void CSSParser::SupportsConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsCondition(this);
}

void CSSParser::SupportsConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsCondition(this);
}

CSSParser::SupportsConditionContext* CSSParser::supportsCondition() {
  SupportsConditionContext *_localctx = _tracker.createInstance<SupportsConditionContext>(_ctx, getState());
  enterRule(_localctx, 100, CSSParser::RuleSupportsCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(525);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(521);
      supportsNegation();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(522);
      supportsConjunction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(523);
      supportsDisjunction();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(524);
      supportsInParens();
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

//----------------- SupportsNegationContext ------------------------------------------------------------------

CSSParser::SupportsNegationContext::SupportsNegationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::SupportsNegationContext::NOT() {
  return getToken(CSSParser::NOT, 0);
}

CSSParser::SupportsInParensContext* CSSParser::SupportsNegationContext::supportsInParens() {
  return getRuleContext<CSSParser::SupportsInParensContext>(0);
}


size_t CSSParser::SupportsNegationContext::getRuleIndex() const {
  return CSSParser::RuleSupportsNegation;
}

void CSSParser::SupportsNegationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsNegation(this);
}

void CSSParser::SupportsNegationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsNegation(this);
}

CSSParser::SupportsNegationContext* CSSParser::supportsNegation() {
  SupportsNegationContext *_localctx = _tracker.createInstance<SupportsNegationContext>(_ctx, getState());
  enterRule(_localctx, 102, CSSParser::RuleSupportsNegation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(527);
    match(CSSParser::NOT);
    setState(528);
    supportsInParens();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsConjunctionContext ------------------------------------------------------------------

CSSParser::SupportsConjunctionContext::SupportsConjunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::SupportsInParensContext *> CSSParser::SupportsConjunctionContext::supportsInParens() {
  return getRuleContexts<CSSParser::SupportsInParensContext>();
}

CSSParser::SupportsInParensContext* CSSParser::SupportsConjunctionContext::supportsInParens(size_t i) {
  return getRuleContext<CSSParser::SupportsInParensContext>(i);
}

std::vector<tree::TerminalNode *> CSSParser::SupportsConjunctionContext::AND() {
  return getTokens(CSSParser::AND);
}

tree::TerminalNode* CSSParser::SupportsConjunctionContext::AND(size_t i) {
  return getToken(CSSParser::AND, i);
}


size_t CSSParser::SupportsConjunctionContext::getRuleIndex() const {
  return CSSParser::RuleSupportsConjunction;
}

void CSSParser::SupportsConjunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsConjunction(this);
}

void CSSParser::SupportsConjunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsConjunction(this);
}

CSSParser::SupportsConjunctionContext* CSSParser::supportsConjunction() {
  SupportsConjunctionContext *_localctx = _tracker.createInstance<SupportsConjunctionContext>(_ctx, getState());
  enterRule(_localctx, 104, CSSParser::RuleSupportsConjunction);
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
    setState(530);
    supportsInParens();
    setState(533); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(531);
      match(CSSParser::AND);
      setState(532);
      supportsInParens();
      setState(535); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CSSParser::AND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsDisjunctionContext ------------------------------------------------------------------

CSSParser::SupportsDisjunctionContext::SupportsDisjunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::SupportsInParensContext *> CSSParser::SupportsDisjunctionContext::supportsInParens() {
  return getRuleContexts<CSSParser::SupportsInParensContext>();
}

CSSParser::SupportsInParensContext* CSSParser::SupportsDisjunctionContext::supportsInParens(size_t i) {
  return getRuleContext<CSSParser::SupportsInParensContext>(i);
}

std::vector<tree::TerminalNode *> CSSParser::SupportsDisjunctionContext::OR() {
  return getTokens(CSSParser::OR);
}

tree::TerminalNode* CSSParser::SupportsDisjunctionContext::OR(size_t i) {
  return getToken(CSSParser::OR, i);
}


size_t CSSParser::SupportsDisjunctionContext::getRuleIndex() const {
  return CSSParser::RuleSupportsDisjunction;
}

void CSSParser::SupportsDisjunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsDisjunction(this);
}

void CSSParser::SupportsDisjunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsDisjunction(this);
}

CSSParser::SupportsDisjunctionContext* CSSParser::supportsDisjunction() {
  SupportsDisjunctionContext *_localctx = _tracker.createInstance<SupportsDisjunctionContext>(_ctx, getState());
  enterRule(_localctx, 106, CSSParser::RuleSupportsDisjunction);
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
    setState(537);
    supportsInParens();
    setState(540); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(538);
      match(CSSParser::OR);
      setState(539);
      supportsInParens();
      setState(542); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CSSParser::OR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsInParensContext ------------------------------------------------------------------

CSSParser::SupportsInParensContext::SupportsInParensContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::SupportsConditionContext* CSSParser::SupportsInParensContext::supportsCondition() {
  return getRuleContext<CSSParser::SupportsConditionContext>(0);
}

CSSParser::SupportsFeatureContext* CSSParser::SupportsInParensContext::supportsFeature() {
  return getRuleContext<CSSParser::SupportsFeatureContext>(0);
}


size_t CSSParser::SupportsInParensContext::getRuleIndex() const {
  return CSSParser::RuleSupportsInParens;
}

void CSSParser::SupportsInParensContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsInParens(this);
}

void CSSParser::SupportsInParensContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsInParens(this);
}

CSSParser::SupportsInParensContext* CSSParser::supportsInParens() {
  SupportsInParensContext *_localctx = _tracker.createInstance<SupportsInParensContext>(_ctx, getState());
  enterRule(_localctx, 108, CSSParser::RuleSupportsInParens);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(549);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(544);
      match(CSSParser::T__18);
      setState(545);
      supportsCondition();
      setState(546);
      match(CSSParser::T__19);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(548);
      supportsFeature();
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

//----------------- SupportsFeatureContext ------------------------------------------------------------------

CSSParser::SupportsFeatureContext::SupportsFeatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::DeclarationContext* CSSParser::SupportsFeatureContext::declaration() {
  return getRuleContext<CSSParser::DeclarationContext>(0);
}


size_t CSSParser::SupportsFeatureContext::getRuleIndex() const {
  return CSSParser::RuleSupportsFeature;
}

void CSSParser::SupportsFeatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsFeature(this);
}

void CSSParser::SupportsFeatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsFeature(this);
}

CSSParser::SupportsFeatureContext* CSSParser::supportsFeature() {
  SupportsFeatureContext *_localctx = _tracker.createInstance<SupportsFeatureContext>(_ctx, getState());
  enterRule(_localctx, 110, CSSParser::RuleSupportsFeature);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(551);
    match(CSSParser::T__18);
    setState(552);
    declaration();
    setState(553);
    match(CSSParser::T__19);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtPageContext ------------------------------------------------------------------

CSSParser::AtPageContext::AtPageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtPageContext::PAGE() {
  return getToken(CSSParser::PAGE, 0);
}

CSSParser::PseudoPageContext* CSSParser::AtPageContext::pseudoPage() {
  return getRuleContext<CSSParser::PseudoPageContext>(0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::AtPageContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::AtPageContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::AtPageContext::getRuleIndex() const {
  return CSSParser::RuleAtPage;
}

void CSSParser::AtPageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtPage(this);
}

void CSSParser::AtPageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtPage(this);
}

CSSParser::AtPageContext* CSSParser::atPage() {
  AtPageContext *_localctx = _tracker.createInstance<AtPageContext>(_ctx, getState());
  enterRule(_localctx, 112, CSSParser::RuleAtPage);
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
    setState(555);
    match(CSSParser::PAGE);
    setState(557);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::T__17) {
      setState(556);
      pseudoPage();
    }
    setState(559);
    match(CSSParser::T__0);
    setState(563);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::VARIABLE

    || _la == CSSParser::IDENTIFIER) {
      setState(560);
      declaration();
      setState(565);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(566);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PseudoPageContext ------------------------------------------------------------------

CSSParser::PseudoPageContext::PseudoPageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::PseudoPageContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}


size_t CSSParser::PseudoPageContext::getRuleIndex() const {
  return CSSParser::RulePseudoPage;
}

void CSSParser::PseudoPageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudoPage(this);
}

void CSSParser::PseudoPageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudoPage(this);
}

CSSParser::PseudoPageContext* CSSParser::pseudoPage() {
  PseudoPageContext *_localctx = _tracker.createInstance<PseudoPageContext>(_ctx, getState());
  enterRule(_localctx, 114, CSSParser::RulePseudoPage);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(568);
    match(CSSParser::T__17);
    setState(569);
    match(CSSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtNamespaceContext ------------------------------------------------------------------

CSSParser::AtNamespaceContext::AtNamespaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtNamespaceContext::NAMESPACE() {
  return getToken(CSSParser::NAMESPACE, 0);
}

tree::TerminalNode* CSSParser::AtNamespaceContext::STRING_LITERAL() {
  return getToken(CSSParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CSSParser::AtNamespaceContext::URI() {
  return getToken(CSSParser::URI, 0);
}

tree::TerminalNode* CSSParser::AtNamespaceContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}


size_t CSSParser::AtNamespaceContext::getRuleIndex() const {
  return CSSParser::RuleAtNamespace;
}

void CSSParser::AtNamespaceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtNamespace(this);
}

void CSSParser::AtNamespaceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtNamespace(this);
}

CSSParser::AtNamespaceContext* CSSParser::atNamespace() {
  AtNamespaceContext *_localctx = _tracker.createInstance<AtNamespaceContext>(_ctx, getState());
  enterRule(_localctx, 116, CSSParser::RuleAtNamespace);
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
    setState(571);
    match(CSSParser::NAMESPACE);
    setState(573);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::IDENTIFIER) {
      setState(572);
      match(CSSParser::IDENTIFIER);
    }
    setState(575);
    _la = _input->LA(1);
    if (!(_la == CSSParser::STRING_LITERAL

    || _la == CSSParser::URI)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(576);
    match(CSSParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtCharsetContext ------------------------------------------------------------------

CSSParser::AtCharsetContext::AtCharsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtCharsetContext::CHARSET() {
  return getToken(CSSParser::CHARSET, 0);
}

tree::TerminalNode* CSSParser::AtCharsetContext::STRING_LITERAL() {
  return getToken(CSSParser::STRING_LITERAL, 0);
}


size_t CSSParser::AtCharsetContext::getRuleIndex() const {
  return CSSParser::RuleAtCharset;
}

void CSSParser::AtCharsetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtCharset(this);
}

void CSSParser::AtCharsetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtCharset(this);
}

CSSParser::AtCharsetContext* CSSParser::atCharset() {
  AtCharsetContext *_localctx = _tracker.createInstance<AtCharsetContext>(_ctx, getState());
  enterRule(_localctx, 118, CSSParser::RuleAtCharset);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(578);
    match(CSSParser::CHARSET);
    setState(579);
    match(CSSParser::STRING_LITERAL);
    setState(580);
    match(CSSParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtViewportContext ------------------------------------------------------------------

CSSParser::AtViewportContext::AtViewportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtViewportContext::VIEWPORT() {
  return getToken(CSSParser::VIEWPORT, 0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::AtViewportContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::AtViewportContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::AtViewportContext::getRuleIndex() const {
  return CSSParser::RuleAtViewport;
}

void CSSParser::AtViewportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtViewport(this);
}

void CSSParser::AtViewportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtViewport(this);
}

CSSParser::AtViewportContext* CSSParser::atViewport() {
  AtViewportContext *_localctx = _tracker.createInstance<AtViewportContext>(_ctx, getState());
  enterRule(_localctx, 120, CSSParser::RuleAtViewport);
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
    setState(582);
    match(CSSParser::VIEWPORT);
    setState(583);
    match(CSSParser::T__0);
    setState(587);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::VARIABLE

    || _la == CSSParser::IDENTIFIER) {
      setState(584);
      declaration();
      setState(589);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(590);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtCounterStyleContext ------------------------------------------------------------------

CSSParser::AtCounterStyleContext::AtCounterStyleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtCounterStyleContext::COUNTER_STYLE() {
  return getToken(CSSParser::COUNTER_STYLE, 0);
}

tree::TerminalNode* CSSParser::AtCounterStyleContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::AtCounterStyleContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::AtCounterStyleContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::AtCounterStyleContext::getRuleIndex() const {
  return CSSParser::RuleAtCounterStyle;
}

void CSSParser::AtCounterStyleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtCounterStyle(this);
}

void CSSParser::AtCounterStyleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtCounterStyle(this);
}

CSSParser::AtCounterStyleContext* CSSParser::atCounterStyle() {
  AtCounterStyleContext *_localctx = _tracker.createInstance<AtCounterStyleContext>(_ctx, getState());
  enterRule(_localctx, 122, CSSParser::RuleAtCounterStyle);
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
    setState(592);
    match(CSSParser::COUNTER_STYLE);
    setState(593);
    match(CSSParser::IDENTIFIER);
    setState(594);
    match(CSSParser::T__0);
    setState(598);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::VARIABLE

    || _la == CSSParser::IDENTIFIER) {
      setState(595);
      declaration();
      setState(600);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(601);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtFontFeatureValuesContext ------------------------------------------------------------------

CSSParser::AtFontFeatureValuesContext::AtFontFeatureValuesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtFontFeatureValuesContext::FONT_FEATURE_VALUES() {
  return getToken(CSSParser::FONT_FEATURE_VALUES, 0);
}

std::vector<CSSParser::FontFamilyNameContext *> CSSParser::AtFontFeatureValuesContext::fontFamilyName() {
  return getRuleContexts<CSSParser::FontFamilyNameContext>();
}

CSSParser::FontFamilyNameContext* CSSParser::AtFontFeatureValuesContext::fontFamilyName(size_t i) {
  return getRuleContext<CSSParser::FontFamilyNameContext>(i);
}

std::vector<CSSParser::FontFeatureValueBlockContext *> CSSParser::AtFontFeatureValuesContext::fontFeatureValueBlock() {
  return getRuleContexts<CSSParser::FontFeatureValueBlockContext>();
}

CSSParser::FontFeatureValueBlockContext* CSSParser::AtFontFeatureValuesContext::fontFeatureValueBlock(size_t i) {
  return getRuleContext<CSSParser::FontFeatureValueBlockContext>(i);
}


size_t CSSParser::AtFontFeatureValuesContext::getRuleIndex() const {
  return CSSParser::RuleAtFontFeatureValues;
}

void CSSParser::AtFontFeatureValuesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtFontFeatureValues(this);
}

void CSSParser::AtFontFeatureValuesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtFontFeatureValues(this);
}

CSSParser::AtFontFeatureValuesContext* CSSParser::atFontFeatureValues() {
  AtFontFeatureValuesContext *_localctx = _tracker.createInstance<AtFontFeatureValuesContext>(_ctx, getState());
  enterRule(_localctx, 124, CSSParser::RuleAtFontFeatureValues);
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
    setState(603);
    match(CSSParser::FONT_FEATURE_VALUES);
    setState(605); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(604);
      fontFamilyName();
      setState(607); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CSSParser::STRING_LITERAL

    || _la == CSSParser::IDENTIFIER);
    setState(609);
    match(CSSParser::T__0);
    setState(613);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::T__29) {
      setState(610);
      fontFeatureValueBlock();
      setState(615);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(616);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FontFamilyNameContext ------------------------------------------------------------------

CSSParser::FontFamilyNameContext::FontFamilyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::FontFamilyNameContext::STRING_LITERAL() {
  return getToken(CSSParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CSSParser::FontFamilyNameContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}


size_t CSSParser::FontFamilyNameContext::getRuleIndex() const {
  return CSSParser::RuleFontFamilyName;
}

void CSSParser::FontFamilyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFontFamilyName(this);
}

void CSSParser::FontFamilyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFontFamilyName(this);
}

CSSParser::FontFamilyNameContext* CSSParser::fontFamilyName() {
  FontFamilyNameContext *_localctx = _tracker.createInstance<FontFamilyNameContext>(_ctx, getState());
  enterRule(_localctx, 126, CSSParser::RuleFontFamilyName);
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
    setState(618);
    _la = _input->LA(1);
    if (!(_la == CSSParser::STRING_LITERAL

    || _la == CSSParser::IDENTIFIER)) {
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

//----------------- FontFeatureValueBlockContext ------------------------------------------------------------------

CSSParser::FontFeatureValueBlockContext::FontFeatureValueBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::FontFeatureValueBlockContext::IDENTIFIER() {
  return getToken(CSSParser::IDENTIFIER, 0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::FontFeatureValueBlockContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::FontFeatureValueBlockContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::FontFeatureValueBlockContext::getRuleIndex() const {
  return CSSParser::RuleFontFeatureValueBlock;
}

void CSSParser::FontFeatureValueBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFontFeatureValueBlock(this);
}

void CSSParser::FontFeatureValueBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFontFeatureValueBlock(this);
}

CSSParser::FontFeatureValueBlockContext* CSSParser::fontFeatureValueBlock() {
  FontFeatureValueBlockContext *_localctx = _tracker.createInstance<FontFeatureValueBlockContext>(_ctx, getState());
  enterRule(_localctx, 128, CSSParser::RuleFontFeatureValueBlock);
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
    setState(620);
    match(CSSParser::T__29);
    setState(621);
    match(CSSParser::IDENTIFIER);
    setState(622);
    match(CSSParser::T__0);
    setState(626);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::VARIABLE

    || _la == CSSParser::IDENTIFIER) {
      setState(623);
      declaration();
      setState(628);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(629);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtPropertyContext ------------------------------------------------------------------

CSSParser::AtPropertyContext::AtPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::AtPropertyContext::PROPERTY() {
  return getToken(CSSParser::PROPERTY, 0);
}

tree::TerminalNode* CSSParser::AtPropertyContext::VARIABLE() {
  return getToken(CSSParser::VARIABLE, 0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::AtPropertyContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::AtPropertyContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::AtPropertyContext::getRuleIndex() const {
  return CSSParser::RuleAtProperty;
}

void CSSParser::AtPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtProperty(this);
}

void CSSParser::AtPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtProperty(this);
}

CSSParser::AtPropertyContext* CSSParser::atProperty() {
  AtPropertyContext *_localctx = _tracker.createInstance<AtPropertyContext>(_ctx, getState());
  enterRule(_localctx, 130, CSSParser::RuleAtProperty);
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
    setState(631);
    match(CSSParser::PROPERTY);
    setState(632);
    match(CSSParser::VARIABLE);
    setState(633);
    match(CSSParser::T__0);
    setState(637);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::VARIABLE

    || _la == CSSParser::IDENTIFIER) {
      setState(634);
      declaration();
      setState(639);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(640);
    match(CSSParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CSSParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSSParser::TermContext *> CSSParser::ExpressionContext::term() {
  return getRuleContexts<CSSParser::TermContext>();
}

CSSParser::TermContext* CSSParser::ExpressionContext::term(size_t i) {
  return getRuleContext<CSSParser::TermContext>(i);
}

std::vector<CSSParser::OperatorContext *> CSSParser::ExpressionContext::operator_() {
  return getRuleContexts<CSSParser::OperatorContext>();
}

CSSParser::OperatorContext* CSSParser::ExpressionContext::operator_(size_t i) {
  return getRuleContext<CSSParser::OperatorContext>(i);
}


size_t CSSParser::ExpressionContext::getRuleIndex() const {
  return CSSParser::RuleExpression;
}

void CSSParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void CSSParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

CSSParser::ExpressionContext* CSSParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 132, CSSParser::RuleExpression);
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
    setState(642);
    term();
    setState(648);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::T__2

    || _la == CSSParser::T__26 || _la == CSSParser::WS) {
      setState(643);
      operator_();
      setState(644);
      term();
      setState(650);
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

//----------------- CommentContext ------------------------------------------------------------------

CSSParser::CommentContext::CommentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::CommentContext::COMMENT() {
  return getToken(CSSParser::COMMENT, 0);
}


size_t CSSParser::CommentContext::getRuleIndex() const {
  return CSSParser::RuleComment;
}

void CSSParser::CommentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComment(this);
}

void CSSParser::CommentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComment(this);
}

CSSParser::CommentContext* CSSParser::comment() {
  CommentContext *_localctx = _tracker.createInstance<CommentContext>(_ctx, getState());
  enterRule(_localctx, 134, CSSParser::RuleComment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(651);
    match(CSSParser::COMMENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CSSParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 47: return keyframeSelectorSempred(antlrcpp::downCast<KeyframeSelectorContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CSSParser::keyframeSelectorSempred(KeyframeSelectorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void CSSParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  cssParserInitialize();
#else
  ::antlr4::internal::call_once(cssParserOnceFlag, cssParserInitialize);
#endif
}
