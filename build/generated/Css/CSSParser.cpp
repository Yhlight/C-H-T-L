
// Generated from /workspace/grammar/CSS.g4 by ANTLR 4.10


#include "CSSVisitor.h"

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

std::once_flag cssParserOnceFlag;
CSSParserStaticData *cssParserStaticData = nullptr;

void cssParserInitialize() {
  assert(cssParserStaticData == nullptr);
  auto staticData = std::make_unique<CSSParserStaticData>(
    std::vector<std::string>{
      "stylesheet", "statement", "charsetRule", "importRule", "namespaceRule", 
      "media", "mediaQueryList", "mediaQuery", "mediaType", "mediaExpression", 
      "mediaFeature", "page", "pseudoPage", "fontFace", "keyframes", "keyframeRule", 
      "keyframeSelector", "supports", "supportsCondition", "supportsNegation", 
      "supportsConjunction", "supportsDisjunction", "supportsConditionInParens", 
      "supportsDeclarationCondition", "generalEnclosed", "ruleset", "selectorList", 
      "selector", "combinator", "simpleSelector", "typeSelector", "typeNamespacePrefix", 
      "elementName", "universal", "idSelector", "classSelector", "attributeSelector", 
      "attributeOperator", "pseudoClass", "functionalPseudoClass", "pseudoElement", 
      "declaration", "property", "value", "term", "function", "hexcolor", 
      "url", "operator", "important", "nestedStatement"
    },
    std::vector<std::string>{
      "", "'@charset'", "'@import'", "'@namespace'", "'@media'", "'@page'", 
      "'@font-face'", "", "'@supports'", "'only'", "'not'", "'and'", "'or'", 
      "'from'", "'to'", "'!important'", "'('", "')'", "'{'", "'}'", "'['", 
      "']'", "':'", "';'", "','", "'.'", "'#'", "'+'", "'-'", "'>'", "'~'", 
      "'*'", "'|'", "'/'", "'='", "'~='", "'|='", "'^='", "'$='", "'*='", 
      "", "", "", "", "", "", "", "", "'url'"
    },
    std::vector<std::string>{
      "", "CHARSET", "IMPORT", "NAMESPACE", "MEDIA", "PAGE", "FONT_FACE", 
      "KEYFRAMES", "SUPPORTS", "ONLY", "NOT", "AND", "OR", "FROM", "TO", 
      "IMPORTANT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", 
      "COLON", "SEMICOLON", "COMMA", "DOT", "HASH", "PLUS", "MINUS", "GREATER", 
      "TILDE", "STAR", "PIPE", "SLASH", "EQUALS", "INCLUDES", "DASHMATCH", 
      "PREFIXMATCH", "SUFFIXMATCH", "SUBSTRINGMATCH", "LENGTH", "EMS", "EXS", 
      "ANGLE", "TIME", "FREQ", "PERCENTAGE", "FUNCTION", "URL", "NUMBER", 
      "STRING", "IDENT", "HEXDIGIT", "COMMENT", "SPACE", "ANY"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,55,484,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,1,0,5,0,104,8,0,10,0,12,0,107,9,0,1,0,1,0,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,121,8,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,3,3,
  	130,8,3,1,3,3,3,133,8,3,1,3,1,3,1,4,1,4,3,4,139,8,4,1,4,1,4,3,4,143,8,
  	4,1,4,1,4,1,5,1,5,1,5,1,5,5,5,151,8,5,10,5,12,5,154,9,5,1,5,1,5,1,6,1,
  	6,1,6,5,6,161,8,6,10,6,12,6,164,9,6,1,7,3,7,167,8,7,1,7,1,7,1,7,5,7,172,
  	8,7,10,7,12,7,175,9,7,1,7,1,7,1,7,5,7,180,8,7,10,7,12,7,183,9,7,3,7,185,
  	8,7,1,8,1,8,1,9,1,9,1,9,1,9,3,9,193,8,9,1,9,1,9,1,10,1,10,1,11,1,11,3,
  	11,201,8,11,1,11,1,11,5,11,205,8,11,10,11,12,11,208,9,11,1,11,1,11,1,
  	12,1,12,1,12,1,13,1,13,1,13,5,13,218,8,13,10,13,12,13,221,9,13,1,13,1,
  	13,1,14,1,14,1,14,1,14,5,14,229,8,14,10,14,12,14,232,9,14,1,14,1,14,1,
  	15,1,15,1,15,5,15,239,8,15,10,15,12,15,242,9,15,1,15,1,15,1,16,1,16,1,
  	16,5,16,249,8,16,10,16,12,16,252,9,16,1,17,1,17,1,17,1,17,5,17,258,8,
  	17,10,17,12,17,261,9,17,1,17,1,17,1,18,1,18,1,18,1,18,3,18,269,8,18,1,
  	19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,4,20,280,8,20,11,20,12,20,
  	281,1,21,1,21,1,21,1,21,1,21,4,21,289,8,21,11,21,12,21,290,1,22,1,22,
  	1,22,1,22,1,22,1,22,3,22,299,8,22,1,23,1,23,1,23,1,23,1,24,1,24,4,24,
  	307,8,24,11,24,12,24,308,1,24,1,24,1,25,1,25,1,25,5,25,316,8,25,10,25,
  	12,25,319,9,25,1,25,1,25,1,26,1,26,1,26,5,26,326,8,26,10,26,12,26,329,
  	9,26,1,27,1,27,1,27,1,27,5,27,335,8,27,10,27,12,27,338,9,27,1,28,1,28,
  	1,29,1,29,3,29,344,8,29,1,29,1,29,1,29,1,29,1,29,5,29,351,8,29,10,29,
  	12,29,354,9,29,1,29,1,29,1,29,1,29,1,29,4,29,361,8,29,11,29,12,29,362,
  	3,29,365,8,29,1,30,3,30,368,8,30,1,30,1,30,1,31,3,31,373,8,31,1,31,1,
  	31,1,32,1,32,1,33,3,33,380,8,33,1,33,1,33,1,34,1,34,1,34,1,35,1,35,1,
  	35,1,36,1,36,1,36,1,36,1,36,3,36,395,8,36,1,36,1,36,1,37,1,37,1,38,1,
  	38,3,38,403,8,38,1,38,1,38,3,38,407,8,38,1,39,1,39,3,39,411,8,39,1,39,
  	1,39,1,40,1,40,1,40,1,40,1,41,1,41,1,41,1,41,3,41,423,8,41,1,42,1,42,
  	1,42,5,42,428,8,42,10,42,12,42,431,9,42,1,43,1,43,3,43,435,8,43,1,43,
  	5,43,438,8,43,10,43,12,43,441,9,43,1,44,1,44,1,44,1,44,1,44,1,44,1,44,
  	1,44,1,44,1,44,1,44,1,44,1,44,3,44,456,8,44,1,45,1,45,5,45,460,8,45,10,
  	45,12,45,463,9,45,1,45,1,45,1,46,1,46,4,46,469,8,46,11,46,12,46,470,1,
  	47,1,47,1,47,1,47,1,47,1,48,1,48,1,49,1,49,1,50,1,50,1,50,0,0,51,0,2,
  	4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,
  	98,100,0,8,1,0,9,10,2,0,13,14,46,46,1,0,17,17,3,0,27,27,29,30,54,54,2,
  	0,31,31,51,51,1,0,50,51,1,0,34,39,3,0,24,24,33,33,54,54,509,0,105,1,0,
  	0,0,2,120,1,0,0,0,4,122,1,0,0,0,6,126,1,0,0,0,8,136,1,0,0,0,10,146,1,
  	0,0,0,12,157,1,0,0,0,14,184,1,0,0,0,16,186,1,0,0,0,18,188,1,0,0,0,20,
  	196,1,0,0,0,22,198,1,0,0,0,24,211,1,0,0,0,26,214,1,0,0,0,28,224,1,0,0,
  	0,30,235,1,0,0,0,32,245,1,0,0,0,34,253,1,0,0,0,36,268,1,0,0,0,38,270,
  	1,0,0,0,40,274,1,0,0,0,42,283,1,0,0,0,44,298,1,0,0,0,46,300,1,0,0,0,48,
  	304,1,0,0,0,50,312,1,0,0,0,52,322,1,0,0,0,54,330,1,0,0,0,56,339,1,0,0,
  	0,58,364,1,0,0,0,60,367,1,0,0,0,62,372,1,0,0,0,64,376,1,0,0,0,66,379,
  	1,0,0,0,68,383,1,0,0,0,70,386,1,0,0,0,72,389,1,0,0,0,74,398,1,0,0,0,76,
  	400,1,0,0,0,78,408,1,0,0,0,80,414,1,0,0,0,82,418,1,0,0,0,84,424,1,0,0,
  	0,86,432,1,0,0,0,88,455,1,0,0,0,90,457,1,0,0,0,92,466,1,0,0,0,94,472,
  	1,0,0,0,96,477,1,0,0,0,98,479,1,0,0,0,100,481,1,0,0,0,102,104,3,2,1,0,
  	103,102,1,0,0,0,104,107,1,0,0,0,105,103,1,0,0,0,105,106,1,0,0,0,106,108,
  	1,0,0,0,107,105,1,0,0,0,108,109,5,0,0,1,109,1,1,0,0,0,110,121,3,50,25,
  	0,111,121,3,10,5,0,112,121,3,22,11,0,113,121,3,26,13,0,114,121,3,28,14,
  	0,115,121,3,34,17,0,116,121,3,6,3,0,117,121,3,8,4,0,118,121,3,4,2,0,119,
  	121,3,100,50,0,120,110,1,0,0,0,120,111,1,0,0,0,120,112,1,0,0,0,120,113,
  	1,0,0,0,120,114,1,0,0,0,120,115,1,0,0,0,120,116,1,0,0,0,120,117,1,0,0,
  	0,120,118,1,0,0,0,120,119,1,0,0,0,121,3,1,0,0,0,122,123,5,1,0,0,123,124,
  	5,50,0,0,124,125,5,23,0,0,125,5,1,0,0,0,126,129,5,2,0,0,127,130,5,50,
  	0,0,128,130,3,94,47,0,129,127,1,0,0,0,129,128,1,0,0,0,130,132,1,0,0,0,
  	131,133,3,12,6,0,132,131,1,0,0,0,132,133,1,0,0,0,133,134,1,0,0,0,134,
  	135,5,23,0,0,135,7,1,0,0,0,136,138,5,3,0,0,137,139,5,51,0,0,138,137,1,
  	0,0,0,138,139,1,0,0,0,139,142,1,0,0,0,140,143,5,50,0,0,141,143,3,94,47,
  	0,142,140,1,0,0,0,142,141,1,0,0,0,143,144,1,0,0,0,144,145,5,23,0,0,145,
  	9,1,0,0,0,146,147,5,4,0,0,147,148,3,12,6,0,148,152,5,18,0,0,149,151,3,
  	50,25,0,150,149,1,0,0,0,151,154,1,0,0,0,152,150,1,0,0,0,152,153,1,0,0,
  	0,153,155,1,0,0,0,154,152,1,0,0,0,155,156,5,19,0,0,156,11,1,0,0,0,157,
  	162,3,14,7,0,158,159,5,24,0,0,159,161,3,14,7,0,160,158,1,0,0,0,161,164,
  	1,0,0,0,162,160,1,0,0,0,162,163,1,0,0,0,163,13,1,0,0,0,164,162,1,0,0,
  	0,165,167,7,0,0,0,166,165,1,0,0,0,166,167,1,0,0,0,167,168,1,0,0,0,168,
  	173,3,16,8,0,169,170,5,11,0,0,170,172,3,18,9,0,171,169,1,0,0,0,172,175,
  	1,0,0,0,173,171,1,0,0,0,173,174,1,0,0,0,174,185,1,0,0,0,175,173,1,0,0,
  	0,176,181,3,18,9,0,177,178,5,11,0,0,178,180,3,18,9,0,179,177,1,0,0,0,
  	180,183,1,0,0,0,181,179,1,0,0,0,181,182,1,0,0,0,182,185,1,0,0,0,183,181,
  	1,0,0,0,184,166,1,0,0,0,184,176,1,0,0,0,185,15,1,0,0,0,186,187,5,51,0,
  	0,187,17,1,0,0,0,188,189,5,16,0,0,189,192,3,20,10,0,190,191,5,22,0,0,
  	191,193,3,86,43,0,192,190,1,0,0,0,192,193,1,0,0,0,193,194,1,0,0,0,194,
  	195,5,17,0,0,195,19,1,0,0,0,196,197,5,51,0,0,197,21,1,0,0,0,198,200,5,
  	5,0,0,199,201,3,24,12,0,200,199,1,0,0,0,200,201,1,0,0,0,201,202,1,0,0,
  	0,202,206,5,18,0,0,203,205,3,82,41,0,204,203,1,0,0,0,205,208,1,0,0,0,
  	206,204,1,0,0,0,206,207,1,0,0,0,207,209,1,0,0,0,208,206,1,0,0,0,209,210,
  	5,19,0,0,210,23,1,0,0,0,211,212,5,22,0,0,212,213,5,51,0,0,213,25,1,0,
  	0,0,214,215,5,6,0,0,215,219,5,18,0,0,216,218,3,82,41,0,217,216,1,0,0,
  	0,218,221,1,0,0,0,219,217,1,0,0,0,219,220,1,0,0,0,220,222,1,0,0,0,221,
  	219,1,0,0,0,222,223,5,19,0,0,223,27,1,0,0,0,224,225,5,7,0,0,225,226,5,
  	51,0,0,226,230,5,18,0,0,227,229,3,30,15,0,228,227,1,0,0,0,229,232,1,0,
  	0,0,230,228,1,0,0,0,230,231,1,0,0,0,231,233,1,0,0,0,232,230,1,0,0,0,233,
  	234,5,19,0,0,234,29,1,0,0,0,235,236,3,32,16,0,236,240,5,18,0,0,237,239,
  	3,82,41,0,238,237,1,0,0,0,239,242,1,0,0,0,240,238,1,0,0,0,240,241,1,0,
  	0,0,241,243,1,0,0,0,242,240,1,0,0,0,243,244,5,19,0,0,244,31,1,0,0,0,245,
  	250,7,1,0,0,246,247,5,24,0,0,247,249,7,1,0,0,248,246,1,0,0,0,249,252,
  	1,0,0,0,250,248,1,0,0,0,250,251,1,0,0,0,251,33,1,0,0,0,252,250,1,0,0,
  	0,253,254,5,8,0,0,254,255,3,36,18,0,255,259,5,18,0,0,256,258,3,50,25,
  	0,257,256,1,0,0,0,258,261,1,0,0,0,259,257,1,0,0,0,259,260,1,0,0,0,260,
  	262,1,0,0,0,261,259,1,0,0,0,262,263,5,19,0,0,263,35,1,0,0,0,264,269,3,
  	38,19,0,265,269,3,40,20,0,266,269,3,42,21,0,267,269,3,44,22,0,268,264,
  	1,0,0,0,268,265,1,0,0,0,268,266,1,0,0,0,268,267,1,0,0,0,269,37,1,0,0,
  	0,270,271,5,10,0,0,271,272,5,54,0,0,272,273,3,44,22,0,273,39,1,0,0,0,
  	274,279,3,44,22,0,275,276,5,54,0,0,276,277,5,11,0,0,277,278,5,54,0,0,
  	278,280,3,44,22,0,279,275,1,0,0,0,280,281,1,0,0,0,281,279,1,0,0,0,281,
  	282,1,0,0,0,282,41,1,0,0,0,283,288,3,44,22,0,284,285,5,54,0,0,285,286,
  	5,12,0,0,286,287,5,54,0,0,287,289,3,44,22,0,288,284,1,0,0,0,289,290,1,
  	0,0,0,290,288,1,0,0,0,290,291,1,0,0,0,291,43,1,0,0,0,292,293,5,16,0,0,
  	293,294,3,36,18,0,294,295,5,17,0,0,295,299,1,0,0,0,296,299,3,46,23,0,
  	297,299,3,48,24,0,298,292,1,0,0,0,298,296,1,0,0,0,298,297,1,0,0,0,299,
  	45,1,0,0,0,300,301,5,16,0,0,301,302,3,82,41,0,302,303,5,17,0,0,303,47,
  	1,0,0,0,304,306,5,16,0,0,305,307,8,2,0,0,306,305,1,0,0,0,307,308,1,0,
  	0,0,308,306,1,0,0,0,308,309,1,0,0,0,309,310,1,0,0,0,310,311,5,17,0,0,
  	311,49,1,0,0,0,312,313,3,52,26,0,313,317,5,18,0,0,314,316,3,82,41,0,315,
  	314,1,0,0,0,316,319,1,0,0,0,317,315,1,0,0,0,317,318,1,0,0,0,318,320,1,
  	0,0,0,319,317,1,0,0,0,320,321,5,19,0,0,321,51,1,0,0,0,322,327,3,54,27,
  	0,323,324,5,24,0,0,324,326,3,54,27,0,325,323,1,0,0,0,326,329,1,0,0,0,
  	327,325,1,0,0,0,327,328,1,0,0,0,328,53,1,0,0,0,329,327,1,0,0,0,330,336,
  	3,58,29,0,331,332,3,56,28,0,332,333,3,58,29,0,333,335,1,0,0,0,334,331,
  	1,0,0,0,335,338,1,0,0,0,336,334,1,0,0,0,336,337,1,0,0,0,337,55,1,0,0,
  	0,338,336,1,0,0,0,339,340,7,3,0,0,340,57,1,0,0,0,341,344,3,60,30,0,342,
  	344,3,66,33,0,343,341,1,0,0,0,343,342,1,0,0,0,343,344,1,0,0,0,344,352,
  	1,0,0,0,345,351,3,68,34,0,346,351,3,70,35,0,347,351,3,72,36,0,348,351,
  	3,76,38,0,349,351,3,80,40,0,350,345,1,0,0,0,350,346,1,0,0,0,350,347,1,
  	0,0,0,350,348,1,0,0,0,350,349,1,0,0,0,351,354,1,0,0,0,352,350,1,0,0,0,
  	352,353,1,0,0,0,353,365,1,0,0,0,354,352,1,0,0,0,355,361,3,68,34,0,356,
  	361,3,70,35,0,357,361,3,72,36,0,358,361,3,76,38,0,359,361,3,80,40,0,360,
  	355,1,0,0,0,360,356,1,0,0,0,360,357,1,0,0,0,360,358,1,0,0,0,360,359,1,
  	0,0,0,361,362,1,0,0,0,362,360,1,0,0,0,362,363,1,0,0,0,363,365,1,0,0,0,
  	364,343,1,0,0,0,364,360,1,0,0,0,365,59,1,0,0,0,366,368,3,62,31,0,367,
  	366,1,0,0,0,367,368,1,0,0,0,368,369,1,0,0,0,369,370,3,64,32,0,370,61,
  	1,0,0,0,371,373,7,4,0,0,372,371,1,0,0,0,372,373,1,0,0,0,373,374,1,0,0,
  	0,374,375,5,32,0,0,375,63,1,0,0,0,376,377,5,51,0,0,377,65,1,0,0,0,378,
  	380,3,62,31,0,379,378,1,0,0,0,379,380,1,0,0,0,380,381,1,0,0,0,381,382,
  	5,31,0,0,382,67,1,0,0,0,383,384,5,26,0,0,384,385,5,51,0,0,385,69,1,0,
  	0,0,386,387,5,25,0,0,387,388,5,51,0,0,388,71,1,0,0,0,389,390,5,20,0,0,
  	390,394,5,51,0,0,391,392,3,74,37,0,392,393,7,5,0,0,393,395,1,0,0,0,394,
  	391,1,0,0,0,394,395,1,0,0,0,395,396,1,0,0,0,396,397,5,21,0,0,397,73,1,
  	0,0,0,398,399,7,6,0,0,399,75,1,0,0,0,400,402,5,22,0,0,401,403,5,22,0,
  	0,402,401,1,0,0,0,402,403,1,0,0,0,403,406,1,0,0,0,404,407,5,51,0,0,405,
  	407,3,78,39,0,406,404,1,0,0,0,406,405,1,0,0,0,407,77,1,0,0,0,408,410,
  	5,47,0,0,409,411,3,52,26,0,410,409,1,0,0,0,410,411,1,0,0,0,411,412,1,
  	0,0,0,412,413,5,17,0,0,413,79,1,0,0,0,414,415,5,22,0,0,415,416,5,22,0,
  	0,416,417,5,51,0,0,417,81,1,0,0,0,418,419,3,84,42,0,419,420,5,22,0,0,
  	420,422,3,86,43,0,421,423,5,15,0,0,422,421,1,0,0,0,422,423,1,0,0,0,423,
  	83,1,0,0,0,424,429,5,51,0,0,425,426,5,28,0,0,426,428,5,51,0,0,427,425,
  	1,0,0,0,428,431,1,0,0,0,429,427,1,0,0,0,429,430,1,0,0,0,430,85,1,0,0,
  	0,431,429,1,0,0,0,432,439,3,88,44,0,433,435,3,96,48,0,434,433,1,0,0,0,
  	434,435,1,0,0,0,435,436,1,0,0,0,436,438,3,88,44,0,437,434,1,0,0,0,438,
  	441,1,0,0,0,439,437,1,0,0,0,439,440,1,0,0,0,440,87,1,0,0,0,441,439,1,
  	0,0,0,442,456,5,49,0,0,443,456,5,46,0,0,444,456,5,40,0,0,445,456,5,41,
  	0,0,446,456,5,42,0,0,447,456,5,43,0,0,448,456,5,44,0,0,449,456,5,45,0,
  	0,450,456,5,50,0,0,451,456,5,51,0,0,452,456,3,94,47,0,453,456,3,92,46,
  	0,454,456,3,90,45,0,455,442,1,0,0,0,455,443,1,0,0,0,455,444,1,0,0,0,455,
  	445,1,0,0,0,455,446,1,0,0,0,455,447,1,0,0,0,455,448,1,0,0,0,455,449,1,
  	0,0,0,455,450,1,0,0,0,455,451,1,0,0,0,455,452,1,0,0,0,455,453,1,0,0,0,
  	455,454,1,0,0,0,456,89,1,0,0,0,457,461,5,47,0,0,458,460,3,86,43,0,459,
  	458,1,0,0,0,460,463,1,0,0,0,461,459,1,0,0,0,461,462,1,0,0,0,462,464,1,
  	0,0,0,463,461,1,0,0,0,464,465,5,17,0,0,465,91,1,0,0,0,466,468,5,26,0,
  	0,467,469,5,52,0,0,468,467,1,0,0,0,469,470,1,0,0,0,470,468,1,0,0,0,470,
  	471,1,0,0,0,471,93,1,0,0,0,472,473,5,48,0,0,473,474,5,16,0,0,474,475,
  	5,50,0,0,475,476,5,17,0,0,476,95,1,0,0,0,477,478,7,7,0,0,478,97,1,0,0,
  	0,479,480,5,15,0,0,480,99,1,0,0,0,481,482,5,23,0,0,482,101,1,0,0,0,48,
  	105,120,129,132,138,142,152,162,166,173,181,184,192,200,206,219,230,240,
  	250,259,268,281,290,298,308,317,327,336,343,350,352,360,362,364,367,372,
  	379,394,402,406,410,422,429,434,439,455,461,470
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


std::any CSSParser::StylesheetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitStylesheet(this);
  else
    return visitor->visitChildren(this);
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
    setState(105);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::CHARSET)
      | (1ULL << CSSParser::IMPORT)
      | (1ULL << CSSParser::NAMESPACE)
      | (1ULL << CSSParser::MEDIA)
      | (1ULL << CSSParser::PAGE)
      | (1ULL << CSSParser::FONT_FACE)
      | (1ULL << CSSParser::KEYFRAMES)
      | (1ULL << CSSParser::SUPPORTS)
      | (1ULL << CSSParser::LBRACE)
      | (1ULL << CSSParser::LBRACKET)
      | (1ULL << CSSParser::COLON)
      | (1ULL << CSSParser::SEMICOLON)
      | (1ULL << CSSParser::COMMA)
      | (1ULL << CSSParser::DOT)
      | (1ULL << CSSParser::HASH)
      | (1ULL << CSSParser::PLUS)
      | (1ULL << CSSParser::GREATER)
      | (1ULL << CSSParser::TILDE)
      | (1ULL << CSSParser::STAR)
      | (1ULL << CSSParser::PIPE)
      | (1ULL << CSSParser::IDENT)
      | (1ULL << CSSParser::SPACE))) != 0)) {
      setState(102);
      statement();
      setState(107);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(108);
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

CSSParser::MediaContext* CSSParser::StatementContext::media() {
  return getRuleContext<CSSParser::MediaContext>(0);
}

CSSParser::PageContext* CSSParser::StatementContext::page() {
  return getRuleContext<CSSParser::PageContext>(0);
}

CSSParser::FontFaceContext* CSSParser::StatementContext::fontFace() {
  return getRuleContext<CSSParser::FontFaceContext>(0);
}

CSSParser::KeyframesContext* CSSParser::StatementContext::keyframes() {
  return getRuleContext<CSSParser::KeyframesContext>(0);
}

CSSParser::SupportsContext* CSSParser::StatementContext::supports() {
  return getRuleContext<CSSParser::SupportsContext>(0);
}

CSSParser::ImportRuleContext* CSSParser::StatementContext::importRule() {
  return getRuleContext<CSSParser::ImportRuleContext>(0);
}

CSSParser::NamespaceRuleContext* CSSParser::StatementContext::namespaceRule() {
  return getRuleContext<CSSParser::NamespaceRuleContext>(0);
}

CSSParser::CharsetRuleContext* CSSParser::StatementContext::charsetRule() {
  return getRuleContext<CSSParser::CharsetRuleContext>(0);
}

CSSParser::NestedStatementContext* CSSParser::StatementContext::nestedStatement() {
  return getRuleContext<CSSParser::NestedStatementContext>(0);
}


size_t CSSParser::StatementContext::getRuleIndex() const {
  return CSSParser::RuleStatement;
}


std::any CSSParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
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
    setState(120);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::LBRACE:
      case CSSParser::LBRACKET:
      case CSSParser::COLON:
      case CSSParser::COMMA:
      case CSSParser::DOT:
      case CSSParser::HASH:
      case CSSParser::PLUS:
      case CSSParser::GREATER:
      case CSSParser::TILDE:
      case CSSParser::STAR:
      case CSSParser::PIPE:
      case CSSParser::IDENT:
      case CSSParser::SPACE: {
        enterOuterAlt(_localctx, 1);
        setState(110);
        ruleset();
        break;
      }

      case CSSParser::MEDIA: {
        enterOuterAlt(_localctx, 2);
        setState(111);
        media();
        break;
      }

      case CSSParser::PAGE: {
        enterOuterAlt(_localctx, 3);
        setState(112);
        page();
        break;
      }

      case CSSParser::FONT_FACE: {
        enterOuterAlt(_localctx, 4);
        setState(113);
        fontFace();
        break;
      }

      case CSSParser::KEYFRAMES: {
        enterOuterAlt(_localctx, 5);
        setState(114);
        keyframes();
        break;
      }

      case CSSParser::SUPPORTS: {
        enterOuterAlt(_localctx, 6);
        setState(115);
        supports();
        break;
      }

      case CSSParser::IMPORT: {
        enterOuterAlt(_localctx, 7);
        setState(116);
        importRule();
        break;
      }

      case CSSParser::NAMESPACE: {
        enterOuterAlt(_localctx, 8);
        setState(117);
        namespaceRule();
        break;
      }

      case CSSParser::CHARSET: {
        enterOuterAlt(_localctx, 9);
        setState(118);
        charsetRule();
        break;
      }

      case CSSParser::SEMICOLON: {
        enterOuterAlt(_localctx, 10);
        setState(119);
        nestedStatement();
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

//----------------- CharsetRuleContext ------------------------------------------------------------------

CSSParser::CharsetRuleContext::CharsetRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::CharsetRuleContext::CHARSET() {
  return getToken(CSSParser::CHARSET, 0);
}

tree::TerminalNode* CSSParser::CharsetRuleContext::STRING() {
  return getToken(CSSParser::STRING, 0);
}

tree::TerminalNode* CSSParser::CharsetRuleContext::SEMICOLON() {
  return getToken(CSSParser::SEMICOLON, 0);
}


size_t CSSParser::CharsetRuleContext::getRuleIndex() const {
  return CSSParser::RuleCharsetRule;
}


std::any CSSParser::CharsetRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitCharsetRule(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::CharsetRuleContext* CSSParser::charsetRule() {
  CharsetRuleContext *_localctx = _tracker.createInstance<CharsetRuleContext>(_ctx, getState());
  enterRule(_localctx, 4, CSSParser::RuleCharsetRule);

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
    match(CSSParser::CHARSET);
    setState(123);
    match(CSSParser::STRING);
    setState(124);
    match(CSSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportRuleContext ------------------------------------------------------------------

CSSParser::ImportRuleContext::ImportRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::ImportRuleContext::IMPORT() {
  return getToken(CSSParser::IMPORT, 0);
}

tree::TerminalNode* CSSParser::ImportRuleContext::SEMICOLON() {
  return getToken(CSSParser::SEMICOLON, 0);
}

tree::TerminalNode* CSSParser::ImportRuleContext::STRING() {
  return getToken(CSSParser::STRING, 0);
}

CSSParser::UrlContext* CSSParser::ImportRuleContext::url() {
  return getRuleContext<CSSParser::UrlContext>(0);
}

CSSParser::MediaQueryListContext* CSSParser::ImportRuleContext::mediaQueryList() {
  return getRuleContext<CSSParser::MediaQueryListContext>(0);
}


size_t CSSParser::ImportRuleContext::getRuleIndex() const {
  return CSSParser::RuleImportRule;
}


std::any CSSParser::ImportRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitImportRule(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::ImportRuleContext* CSSParser::importRule() {
  ImportRuleContext *_localctx = _tracker.createInstance<ImportRuleContext>(_ctx, getState());
  enterRule(_localctx, 6, CSSParser::RuleImportRule);
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
    setState(126);
    match(CSSParser::IMPORT);
    setState(129);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::STRING: {
        setState(127);
        match(CSSParser::STRING);
        break;
      }

      case CSSParser::URL: {
        setState(128);
        url();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(132);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::ONLY)
      | (1ULL << CSSParser::NOT)
      | (1ULL << CSSParser::LPAREN)
      | (1ULL << CSSParser::IDENT))) != 0)) {
      setState(131);
      mediaQueryList();
    }
    setState(134);
    match(CSSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamespaceRuleContext ------------------------------------------------------------------

CSSParser::NamespaceRuleContext::NamespaceRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::NamespaceRuleContext::NAMESPACE() {
  return getToken(CSSParser::NAMESPACE, 0);
}

tree::TerminalNode* CSSParser::NamespaceRuleContext::SEMICOLON() {
  return getToken(CSSParser::SEMICOLON, 0);
}

tree::TerminalNode* CSSParser::NamespaceRuleContext::STRING() {
  return getToken(CSSParser::STRING, 0);
}

CSSParser::UrlContext* CSSParser::NamespaceRuleContext::url() {
  return getRuleContext<CSSParser::UrlContext>(0);
}

tree::TerminalNode* CSSParser::NamespaceRuleContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}


size_t CSSParser::NamespaceRuleContext::getRuleIndex() const {
  return CSSParser::RuleNamespaceRule;
}


std::any CSSParser::NamespaceRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitNamespaceRule(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::NamespaceRuleContext* CSSParser::namespaceRule() {
  NamespaceRuleContext *_localctx = _tracker.createInstance<NamespaceRuleContext>(_ctx, getState());
  enterRule(_localctx, 8, CSSParser::RuleNamespaceRule);
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
    setState(136);
    match(CSSParser::NAMESPACE);
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::IDENT) {
      setState(137);
      match(CSSParser::IDENT);
    }
    setState(142);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::STRING: {
        setState(140);
        match(CSSParser::STRING);
        break;
      }

      case CSSParser::URL: {
        setState(141);
        url();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(144);
    match(CSSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaContext ------------------------------------------------------------------

CSSParser::MediaContext::MediaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::MediaContext::MEDIA() {
  return getToken(CSSParser::MEDIA, 0);
}

CSSParser::MediaQueryListContext* CSSParser::MediaContext::mediaQueryList() {
  return getRuleContext<CSSParser::MediaQueryListContext>(0);
}

tree::TerminalNode* CSSParser::MediaContext::LBRACE() {
  return getToken(CSSParser::LBRACE, 0);
}

tree::TerminalNode* CSSParser::MediaContext::RBRACE() {
  return getToken(CSSParser::RBRACE, 0);
}

std::vector<CSSParser::RulesetContext *> CSSParser::MediaContext::ruleset() {
  return getRuleContexts<CSSParser::RulesetContext>();
}

CSSParser::RulesetContext* CSSParser::MediaContext::ruleset(size_t i) {
  return getRuleContext<CSSParser::RulesetContext>(i);
}


size_t CSSParser::MediaContext::getRuleIndex() const {
  return CSSParser::RuleMedia;
}


std::any CSSParser::MediaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitMedia(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::MediaContext* CSSParser::media() {
  MediaContext *_localctx = _tracker.createInstance<MediaContext>(_ctx, getState());
  enterRule(_localctx, 10, CSSParser::RuleMedia);
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
    setState(146);
    match(CSSParser::MEDIA);
    setState(147);
    mediaQueryList();
    setState(148);
    match(CSSParser::LBRACE);
    setState(152);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::LBRACE)
      | (1ULL << CSSParser::LBRACKET)
      | (1ULL << CSSParser::COLON)
      | (1ULL << CSSParser::COMMA)
      | (1ULL << CSSParser::DOT)
      | (1ULL << CSSParser::HASH)
      | (1ULL << CSSParser::PLUS)
      | (1ULL << CSSParser::GREATER)
      | (1ULL << CSSParser::TILDE)
      | (1ULL << CSSParser::STAR)
      | (1ULL << CSSParser::PIPE)
      | (1ULL << CSSParser::IDENT)
      | (1ULL << CSSParser::SPACE))) != 0)) {
      setState(149);
      ruleset();
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(155);
    match(CSSParser::RBRACE);
   
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

std::vector<tree::TerminalNode *> CSSParser::MediaQueryListContext::COMMA() {
  return getTokens(CSSParser::COMMA);
}

tree::TerminalNode* CSSParser::MediaQueryListContext::COMMA(size_t i) {
  return getToken(CSSParser::COMMA, i);
}


size_t CSSParser::MediaQueryListContext::getRuleIndex() const {
  return CSSParser::RuleMediaQueryList;
}


std::any CSSParser::MediaQueryListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitMediaQueryList(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::MediaQueryListContext* CSSParser::mediaQueryList() {
  MediaQueryListContext *_localctx = _tracker.createInstance<MediaQueryListContext>(_ctx, getState());
  enterRule(_localctx, 12, CSSParser::RuleMediaQueryList);
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
    setState(157);
    mediaQuery();
    setState(162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::COMMA) {
      setState(158);
      match(CSSParser::COMMA);
      setState(159);
      mediaQuery();
      setState(164);
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

std::vector<CSSParser::MediaExpressionContext *> CSSParser::MediaQueryContext::mediaExpression() {
  return getRuleContexts<CSSParser::MediaExpressionContext>();
}

CSSParser::MediaExpressionContext* CSSParser::MediaQueryContext::mediaExpression(size_t i) {
  return getRuleContext<CSSParser::MediaExpressionContext>(i);
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


std::any CSSParser::MediaQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitMediaQuery(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::MediaQueryContext* CSSParser::mediaQuery() {
  MediaQueryContext *_localctx = _tracker.createInstance<MediaQueryContext>(_ctx, getState());
  enterRule(_localctx, 14, CSSParser::RuleMediaQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(184);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::ONLY:
      case CSSParser::NOT:
      case CSSParser::IDENT: {
        enterOuterAlt(_localctx, 1);
        setState(166);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CSSParser::ONLY

        || _la == CSSParser::NOT) {
          setState(165);
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
        setState(168);
        mediaType();
        setState(173);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CSSParser::AND) {
          setState(169);
          match(CSSParser::AND);
          setState(170);
          mediaExpression();
          setState(175);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case CSSParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(176);
        mediaExpression();
        setState(181);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CSSParser::AND) {
          setState(177);
          match(CSSParser::AND);
          setState(178);
          mediaExpression();
          setState(183);
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

tree::TerminalNode* CSSParser::MediaTypeContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}


size_t CSSParser::MediaTypeContext::getRuleIndex() const {
  return CSSParser::RuleMediaType;
}


std::any CSSParser::MediaTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitMediaType(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::MediaTypeContext* CSSParser::mediaType() {
  MediaTypeContext *_localctx = _tracker.createInstance<MediaTypeContext>(_ctx, getState());
  enterRule(_localctx, 16, CSSParser::RuleMediaType);

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
    match(CSSParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaExpressionContext ------------------------------------------------------------------

CSSParser::MediaExpressionContext::MediaExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::MediaExpressionContext::LPAREN() {
  return getToken(CSSParser::LPAREN, 0);
}

CSSParser::MediaFeatureContext* CSSParser::MediaExpressionContext::mediaFeature() {
  return getRuleContext<CSSParser::MediaFeatureContext>(0);
}

tree::TerminalNode* CSSParser::MediaExpressionContext::RPAREN() {
  return getToken(CSSParser::RPAREN, 0);
}

tree::TerminalNode* CSSParser::MediaExpressionContext::COLON() {
  return getToken(CSSParser::COLON, 0);
}

CSSParser::ValueContext* CSSParser::MediaExpressionContext::value() {
  return getRuleContext<CSSParser::ValueContext>(0);
}


size_t CSSParser::MediaExpressionContext::getRuleIndex() const {
  return CSSParser::RuleMediaExpression;
}


std::any CSSParser::MediaExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitMediaExpression(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::MediaExpressionContext* CSSParser::mediaExpression() {
  MediaExpressionContext *_localctx = _tracker.createInstance<MediaExpressionContext>(_ctx, getState());
  enterRule(_localctx, 18, CSSParser::RuleMediaExpression);
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
    setState(188);
    match(CSSParser::LPAREN);
    setState(189);
    mediaFeature();
    setState(192);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::COLON) {
      setState(190);
      match(CSSParser::COLON);
      setState(191);
      value();
    }
    setState(194);
    match(CSSParser::RPAREN);
   
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

tree::TerminalNode* CSSParser::MediaFeatureContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}


size_t CSSParser::MediaFeatureContext::getRuleIndex() const {
  return CSSParser::RuleMediaFeature;
}


std::any CSSParser::MediaFeatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitMediaFeature(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::MediaFeatureContext* CSSParser::mediaFeature() {
  MediaFeatureContext *_localctx = _tracker.createInstance<MediaFeatureContext>(_ctx, getState());
  enterRule(_localctx, 20, CSSParser::RuleMediaFeature);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(196);
    match(CSSParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PageContext ------------------------------------------------------------------

CSSParser::PageContext::PageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::PageContext::PAGE() {
  return getToken(CSSParser::PAGE, 0);
}

tree::TerminalNode* CSSParser::PageContext::LBRACE() {
  return getToken(CSSParser::LBRACE, 0);
}

tree::TerminalNode* CSSParser::PageContext::RBRACE() {
  return getToken(CSSParser::RBRACE, 0);
}

CSSParser::PseudoPageContext* CSSParser::PageContext::pseudoPage() {
  return getRuleContext<CSSParser::PseudoPageContext>(0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::PageContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::PageContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::PageContext::getRuleIndex() const {
  return CSSParser::RulePage;
}


std::any CSSParser::PageContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitPage(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::PageContext* CSSParser::page() {
  PageContext *_localctx = _tracker.createInstance<PageContext>(_ctx, getState());
  enterRule(_localctx, 22, CSSParser::RulePage);
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
    setState(198);
    match(CSSParser::PAGE);
    setState(200);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::COLON) {
      setState(199);
      pseudoPage();
    }
    setState(202);
    match(CSSParser::LBRACE);
    setState(206);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::IDENT) {
      setState(203);
      declaration();
      setState(208);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(209);
    match(CSSParser::RBRACE);
   
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

tree::TerminalNode* CSSParser::PseudoPageContext::COLON() {
  return getToken(CSSParser::COLON, 0);
}

tree::TerminalNode* CSSParser::PseudoPageContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}


size_t CSSParser::PseudoPageContext::getRuleIndex() const {
  return CSSParser::RulePseudoPage;
}


std::any CSSParser::PseudoPageContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitPseudoPage(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::PseudoPageContext* CSSParser::pseudoPage() {
  PseudoPageContext *_localctx = _tracker.createInstance<PseudoPageContext>(_ctx, getState());
  enterRule(_localctx, 24, CSSParser::RulePseudoPage);

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
    match(CSSParser::COLON);
    setState(212);
    match(CSSParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FontFaceContext ------------------------------------------------------------------

CSSParser::FontFaceContext::FontFaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::FontFaceContext::FONT_FACE() {
  return getToken(CSSParser::FONT_FACE, 0);
}

tree::TerminalNode* CSSParser::FontFaceContext::LBRACE() {
  return getToken(CSSParser::LBRACE, 0);
}

tree::TerminalNode* CSSParser::FontFaceContext::RBRACE() {
  return getToken(CSSParser::RBRACE, 0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::FontFaceContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::FontFaceContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::FontFaceContext::getRuleIndex() const {
  return CSSParser::RuleFontFace;
}


std::any CSSParser::FontFaceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitFontFace(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::FontFaceContext* CSSParser::fontFace() {
  FontFaceContext *_localctx = _tracker.createInstance<FontFaceContext>(_ctx, getState());
  enterRule(_localctx, 26, CSSParser::RuleFontFace);
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
    setState(214);
    match(CSSParser::FONT_FACE);
    setState(215);
    match(CSSParser::LBRACE);
    setState(219);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::IDENT) {
      setState(216);
      declaration();
      setState(221);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(222);
    match(CSSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyframesContext ------------------------------------------------------------------

CSSParser::KeyframesContext::KeyframesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::KeyframesContext::KEYFRAMES() {
  return getToken(CSSParser::KEYFRAMES, 0);
}

tree::TerminalNode* CSSParser::KeyframesContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}

tree::TerminalNode* CSSParser::KeyframesContext::LBRACE() {
  return getToken(CSSParser::LBRACE, 0);
}

tree::TerminalNode* CSSParser::KeyframesContext::RBRACE() {
  return getToken(CSSParser::RBRACE, 0);
}

std::vector<CSSParser::KeyframeRuleContext *> CSSParser::KeyframesContext::keyframeRule() {
  return getRuleContexts<CSSParser::KeyframeRuleContext>();
}

CSSParser::KeyframeRuleContext* CSSParser::KeyframesContext::keyframeRule(size_t i) {
  return getRuleContext<CSSParser::KeyframeRuleContext>(i);
}


size_t CSSParser::KeyframesContext::getRuleIndex() const {
  return CSSParser::RuleKeyframes;
}


std::any CSSParser::KeyframesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitKeyframes(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::KeyframesContext* CSSParser::keyframes() {
  KeyframesContext *_localctx = _tracker.createInstance<KeyframesContext>(_ctx, getState());
  enterRule(_localctx, 28, CSSParser::RuleKeyframes);
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
    setState(224);
    match(CSSParser::KEYFRAMES);
    setState(225);
    match(CSSParser::IDENT);
    setState(226);
    match(CSSParser::LBRACE);
    setState(230);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::FROM)
      | (1ULL << CSSParser::TO)
      | (1ULL << CSSParser::PERCENTAGE))) != 0)) {
      setState(227);
      keyframeRule();
      setState(232);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(233);
    match(CSSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyframeRuleContext ------------------------------------------------------------------

CSSParser::KeyframeRuleContext::KeyframeRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSSParser::KeyframeSelectorContext* CSSParser::KeyframeRuleContext::keyframeSelector() {
  return getRuleContext<CSSParser::KeyframeSelectorContext>(0);
}

tree::TerminalNode* CSSParser::KeyframeRuleContext::LBRACE() {
  return getToken(CSSParser::LBRACE, 0);
}

tree::TerminalNode* CSSParser::KeyframeRuleContext::RBRACE() {
  return getToken(CSSParser::RBRACE, 0);
}

std::vector<CSSParser::DeclarationContext *> CSSParser::KeyframeRuleContext::declaration() {
  return getRuleContexts<CSSParser::DeclarationContext>();
}

CSSParser::DeclarationContext* CSSParser::KeyframeRuleContext::declaration(size_t i) {
  return getRuleContext<CSSParser::DeclarationContext>(i);
}


size_t CSSParser::KeyframeRuleContext::getRuleIndex() const {
  return CSSParser::RuleKeyframeRule;
}


std::any CSSParser::KeyframeRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitKeyframeRule(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::KeyframeRuleContext* CSSParser::keyframeRule() {
  KeyframeRuleContext *_localctx = _tracker.createInstance<KeyframeRuleContext>(_ctx, getState());
  enterRule(_localctx, 30, CSSParser::RuleKeyframeRule);
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
    setState(235);
    keyframeSelector();
    setState(236);
    match(CSSParser::LBRACE);
    setState(240);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::IDENT) {
      setState(237);
      declaration();
      setState(242);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(243);
    match(CSSParser::RBRACE);
   
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

std::vector<tree::TerminalNode *> CSSParser::KeyframeSelectorContext::FROM() {
  return getTokens(CSSParser::FROM);
}

tree::TerminalNode* CSSParser::KeyframeSelectorContext::FROM(size_t i) {
  return getToken(CSSParser::FROM, i);
}

std::vector<tree::TerminalNode *> CSSParser::KeyframeSelectorContext::TO() {
  return getTokens(CSSParser::TO);
}

tree::TerminalNode* CSSParser::KeyframeSelectorContext::TO(size_t i) {
  return getToken(CSSParser::TO, i);
}

std::vector<tree::TerminalNode *> CSSParser::KeyframeSelectorContext::PERCENTAGE() {
  return getTokens(CSSParser::PERCENTAGE);
}

tree::TerminalNode* CSSParser::KeyframeSelectorContext::PERCENTAGE(size_t i) {
  return getToken(CSSParser::PERCENTAGE, i);
}

std::vector<tree::TerminalNode *> CSSParser::KeyframeSelectorContext::COMMA() {
  return getTokens(CSSParser::COMMA);
}

tree::TerminalNode* CSSParser::KeyframeSelectorContext::COMMA(size_t i) {
  return getToken(CSSParser::COMMA, i);
}


size_t CSSParser::KeyframeSelectorContext::getRuleIndex() const {
  return CSSParser::RuleKeyframeSelector;
}


std::any CSSParser::KeyframeSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitKeyframeSelector(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::KeyframeSelectorContext* CSSParser::keyframeSelector() {
  KeyframeSelectorContext *_localctx = _tracker.createInstance<KeyframeSelectorContext>(_ctx, getState());
  enterRule(_localctx, 32, CSSParser::RuleKeyframeSelector);
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
    setState(245);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::FROM)
      | (1ULL << CSSParser::TO)
      | (1ULL << CSSParser::PERCENTAGE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(250);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::COMMA) {
      setState(246);
      match(CSSParser::COMMA);
      setState(247);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CSSParser::FROM)
        | (1ULL << CSSParser::TO)
        | (1ULL << CSSParser::PERCENTAGE))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(252);
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

//----------------- SupportsContext ------------------------------------------------------------------

CSSParser::SupportsContext::SupportsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::SupportsContext::SUPPORTS() {
  return getToken(CSSParser::SUPPORTS, 0);
}

CSSParser::SupportsConditionContext* CSSParser::SupportsContext::supportsCondition() {
  return getRuleContext<CSSParser::SupportsConditionContext>(0);
}

tree::TerminalNode* CSSParser::SupportsContext::LBRACE() {
  return getToken(CSSParser::LBRACE, 0);
}

tree::TerminalNode* CSSParser::SupportsContext::RBRACE() {
  return getToken(CSSParser::RBRACE, 0);
}

std::vector<CSSParser::RulesetContext *> CSSParser::SupportsContext::ruleset() {
  return getRuleContexts<CSSParser::RulesetContext>();
}

CSSParser::RulesetContext* CSSParser::SupportsContext::ruleset(size_t i) {
  return getRuleContext<CSSParser::RulesetContext>(i);
}


size_t CSSParser::SupportsContext::getRuleIndex() const {
  return CSSParser::RuleSupports;
}


std::any CSSParser::SupportsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSupports(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SupportsContext* CSSParser::supports() {
  SupportsContext *_localctx = _tracker.createInstance<SupportsContext>(_ctx, getState());
  enterRule(_localctx, 34, CSSParser::RuleSupports);
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
    setState(253);
    match(CSSParser::SUPPORTS);
    setState(254);
    supportsCondition();
    setState(255);
    match(CSSParser::LBRACE);
    setState(259);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::LBRACE)
      | (1ULL << CSSParser::LBRACKET)
      | (1ULL << CSSParser::COLON)
      | (1ULL << CSSParser::COMMA)
      | (1ULL << CSSParser::DOT)
      | (1ULL << CSSParser::HASH)
      | (1ULL << CSSParser::PLUS)
      | (1ULL << CSSParser::GREATER)
      | (1ULL << CSSParser::TILDE)
      | (1ULL << CSSParser::STAR)
      | (1ULL << CSSParser::PIPE)
      | (1ULL << CSSParser::IDENT)
      | (1ULL << CSSParser::SPACE))) != 0)) {
      setState(256);
      ruleset();
      setState(261);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(262);
    match(CSSParser::RBRACE);
   
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

CSSParser::SupportsConditionInParensContext* CSSParser::SupportsConditionContext::supportsConditionInParens() {
  return getRuleContext<CSSParser::SupportsConditionInParensContext>(0);
}


size_t CSSParser::SupportsConditionContext::getRuleIndex() const {
  return CSSParser::RuleSupportsCondition;
}


std::any CSSParser::SupportsConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSupportsCondition(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SupportsConditionContext* CSSParser::supportsCondition() {
  SupportsConditionContext *_localctx = _tracker.createInstance<SupportsConditionContext>(_ctx, getState());
  enterRule(_localctx, 36, CSSParser::RuleSupportsCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(268);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(264);
      supportsNegation();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(265);
      supportsConjunction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(266);
      supportsDisjunction();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(267);
      supportsConditionInParens();
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

tree::TerminalNode* CSSParser::SupportsNegationContext::SPACE() {
  return getToken(CSSParser::SPACE, 0);
}

CSSParser::SupportsConditionInParensContext* CSSParser::SupportsNegationContext::supportsConditionInParens() {
  return getRuleContext<CSSParser::SupportsConditionInParensContext>(0);
}


size_t CSSParser::SupportsNegationContext::getRuleIndex() const {
  return CSSParser::RuleSupportsNegation;
}


std::any CSSParser::SupportsNegationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSupportsNegation(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SupportsNegationContext* CSSParser::supportsNegation() {
  SupportsNegationContext *_localctx = _tracker.createInstance<SupportsNegationContext>(_ctx, getState());
  enterRule(_localctx, 38, CSSParser::RuleSupportsNegation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
    match(CSSParser::NOT);
    setState(271);
    match(CSSParser::SPACE);
    setState(272);
    supportsConditionInParens();
   
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

std::vector<CSSParser::SupportsConditionInParensContext *> CSSParser::SupportsConjunctionContext::supportsConditionInParens() {
  return getRuleContexts<CSSParser::SupportsConditionInParensContext>();
}

CSSParser::SupportsConditionInParensContext* CSSParser::SupportsConjunctionContext::supportsConditionInParens(size_t i) {
  return getRuleContext<CSSParser::SupportsConditionInParensContext>(i);
}

std::vector<tree::TerminalNode *> CSSParser::SupportsConjunctionContext::SPACE() {
  return getTokens(CSSParser::SPACE);
}

tree::TerminalNode* CSSParser::SupportsConjunctionContext::SPACE(size_t i) {
  return getToken(CSSParser::SPACE, i);
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


std::any CSSParser::SupportsConjunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSupportsConjunction(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SupportsConjunctionContext* CSSParser::supportsConjunction() {
  SupportsConjunctionContext *_localctx = _tracker.createInstance<SupportsConjunctionContext>(_ctx, getState());
  enterRule(_localctx, 40, CSSParser::RuleSupportsConjunction);
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
    supportsConditionInParens();
    setState(279); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(275);
      match(CSSParser::SPACE);
      setState(276);
      match(CSSParser::AND);
      setState(277);
      match(CSSParser::SPACE);
      setState(278);
      supportsConditionInParens();
      setState(281); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CSSParser::SPACE);
   
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

std::vector<CSSParser::SupportsConditionInParensContext *> CSSParser::SupportsDisjunctionContext::supportsConditionInParens() {
  return getRuleContexts<CSSParser::SupportsConditionInParensContext>();
}

CSSParser::SupportsConditionInParensContext* CSSParser::SupportsDisjunctionContext::supportsConditionInParens(size_t i) {
  return getRuleContext<CSSParser::SupportsConditionInParensContext>(i);
}

std::vector<tree::TerminalNode *> CSSParser::SupportsDisjunctionContext::SPACE() {
  return getTokens(CSSParser::SPACE);
}

tree::TerminalNode* CSSParser::SupportsDisjunctionContext::SPACE(size_t i) {
  return getToken(CSSParser::SPACE, i);
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


std::any CSSParser::SupportsDisjunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSupportsDisjunction(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SupportsDisjunctionContext* CSSParser::supportsDisjunction() {
  SupportsDisjunctionContext *_localctx = _tracker.createInstance<SupportsDisjunctionContext>(_ctx, getState());
  enterRule(_localctx, 42, CSSParser::RuleSupportsDisjunction);
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
    setState(283);
    supportsConditionInParens();
    setState(288); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(284);
      match(CSSParser::SPACE);
      setState(285);
      match(CSSParser::OR);
      setState(286);
      match(CSSParser::SPACE);
      setState(287);
      supportsConditionInParens();
      setState(290); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CSSParser::SPACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsConditionInParensContext ------------------------------------------------------------------

CSSParser::SupportsConditionInParensContext::SupportsConditionInParensContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::SupportsConditionInParensContext::LPAREN() {
  return getToken(CSSParser::LPAREN, 0);
}

CSSParser::SupportsConditionContext* CSSParser::SupportsConditionInParensContext::supportsCondition() {
  return getRuleContext<CSSParser::SupportsConditionContext>(0);
}

tree::TerminalNode* CSSParser::SupportsConditionInParensContext::RPAREN() {
  return getToken(CSSParser::RPAREN, 0);
}

CSSParser::SupportsDeclarationConditionContext* CSSParser::SupportsConditionInParensContext::supportsDeclarationCondition() {
  return getRuleContext<CSSParser::SupportsDeclarationConditionContext>(0);
}

CSSParser::GeneralEnclosedContext* CSSParser::SupportsConditionInParensContext::generalEnclosed() {
  return getRuleContext<CSSParser::GeneralEnclosedContext>(0);
}


size_t CSSParser::SupportsConditionInParensContext::getRuleIndex() const {
  return CSSParser::RuleSupportsConditionInParens;
}


std::any CSSParser::SupportsConditionInParensContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSupportsConditionInParens(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SupportsConditionInParensContext* CSSParser::supportsConditionInParens() {
  SupportsConditionInParensContext *_localctx = _tracker.createInstance<SupportsConditionInParensContext>(_ctx, getState());
  enterRule(_localctx, 44, CSSParser::RuleSupportsConditionInParens);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(298);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(292);
      match(CSSParser::LPAREN);
      setState(293);
      supportsCondition();
      setState(294);
      match(CSSParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(296);
      supportsDeclarationCondition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(297);
      generalEnclosed();
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

//----------------- SupportsDeclarationConditionContext ------------------------------------------------------------------

CSSParser::SupportsDeclarationConditionContext::SupportsDeclarationConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::SupportsDeclarationConditionContext::LPAREN() {
  return getToken(CSSParser::LPAREN, 0);
}

CSSParser::DeclarationContext* CSSParser::SupportsDeclarationConditionContext::declaration() {
  return getRuleContext<CSSParser::DeclarationContext>(0);
}

tree::TerminalNode* CSSParser::SupportsDeclarationConditionContext::RPAREN() {
  return getToken(CSSParser::RPAREN, 0);
}


size_t CSSParser::SupportsDeclarationConditionContext::getRuleIndex() const {
  return CSSParser::RuleSupportsDeclarationCondition;
}


std::any CSSParser::SupportsDeclarationConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSupportsDeclarationCondition(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SupportsDeclarationConditionContext* CSSParser::supportsDeclarationCondition() {
  SupportsDeclarationConditionContext *_localctx = _tracker.createInstance<SupportsDeclarationConditionContext>(_ctx, getState());
  enterRule(_localctx, 46, CSSParser::RuleSupportsDeclarationCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(300);
    match(CSSParser::LPAREN);
    setState(301);
    declaration();
    setState(302);
    match(CSSParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GeneralEnclosedContext ------------------------------------------------------------------

CSSParser::GeneralEnclosedContext::GeneralEnclosedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::GeneralEnclosedContext::LPAREN() {
  return getToken(CSSParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> CSSParser::GeneralEnclosedContext::RPAREN() {
  return getTokens(CSSParser::RPAREN);
}

tree::TerminalNode* CSSParser::GeneralEnclosedContext::RPAREN(size_t i) {
  return getToken(CSSParser::RPAREN, i);
}


size_t CSSParser::GeneralEnclosedContext::getRuleIndex() const {
  return CSSParser::RuleGeneralEnclosed;
}


std::any CSSParser::GeneralEnclosedContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitGeneralEnclosed(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::GeneralEnclosedContext* CSSParser::generalEnclosed() {
  GeneralEnclosedContext *_localctx = _tracker.createInstance<GeneralEnclosedContext>(_ctx, getState());
  enterRule(_localctx, 48, CSSParser::RuleGeneralEnclosed);
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
    setState(304);
    match(CSSParser::LPAREN);
    setState(306); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(305);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == CSSParser::RPAREN)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(308); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::CHARSET)
      | (1ULL << CSSParser::IMPORT)
      | (1ULL << CSSParser::NAMESPACE)
      | (1ULL << CSSParser::MEDIA)
      | (1ULL << CSSParser::PAGE)
      | (1ULL << CSSParser::FONT_FACE)
      | (1ULL << CSSParser::KEYFRAMES)
      | (1ULL << CSSParser::SUPPORTS)
      | (1ULL << CSSParser::ONLY)
      | (1ULL << CSSParser::NOT)
      | (1ULL << CSSParser::AND)
      | (1ULL << CSSParser::OR)
      | (1ULL << CSSParser::FROM)
      | (1ULL << CSSParser::TO)
      | (1ULL << CSSParser::IMPORTANT)
      | (1ULL << CSSParser::LPAREN)
      | (1ULL << CSSParser::LBRACE)
      | (1ULL << CSSParser::RBRACE)
      | (1ULL << CSSParser::LBRACKET)
      | (1ULL << CSSParser::RBRACKET)
      | (1ULL << CSSParser::COLON)
      | (1ULL << CSSParser::SEMICOLON)
      | (1ULL << CSSParser::COMMA)
      | (1ULL << CSSParser::DOT)
      | (1ULL << CSSParser::HASH)
      | (1ULL << CSSParser::PLUS)
      | (1ULL << CSSParser::MINUS)
      | (1ULL << CSSParser::GREATER)
      | (1ULL << CSSParser::TILDE)
      | (1ULL << CSSParser::STAR)
      | (1ULL << CSSParser::PIPE)
      | (1ULL << CSSParser::SLASH)
      | (1ULL << CSSParser::EQUALS)
      | (1ULL << CSSParser::INCLUDES)
      | (1ULL << CSSParser::DASHMATCH)
      | (1ULL << CSSParser::PREFIXMATCH)
      | (1ULL << CSSParser::SUFFIXMATCH)
      | (1ULL << CSSParser::SUBSTRINGMATCH)
      | (1ULL << CSSParser::LENGTH)
      | (1ULL << CSSParser::EMS)
      | (1ULL << CSSParser::EXS)
      | (1ULL << CSSParser::ANGLE)
      | (1ULL << CSSParser::TIME)
      | (1ULL << CSSParser::FREQ)
      | (1ULL << CSSParser::PERCENTAGE)
      | (1ULL << CSSParser::FUNCTION)
      | (1ULL << CSSParser::URL)
      | (1ULL << CSSParser::NUMBER)
      | (1ULL << CSSParser::STRING)
      | (1ULL << CSSParser::IDENT)
      | (1ULL << CSSParser::HEXDIGIT)
      | (1ULL << CSSParser::COMMENT)
      | (1ULL << CSSParser::SPACE)
      | (1ULL << CSSParser::ANY))) != 0));
    setState(310);
    match(CSSParser::RPAREN);
   
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

tree::TerminalNode* CSSParser::RulesetContext::LBRACE() {
  return getToken(CSSParser::LBRACE, 0);
}

tree::TerminalNode* CSSParser::RulesetContext::RBRACE() {
  return getToken(CSSParser::RBRACE, 0);
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


std::any CSSParser::RulesetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitRuleset(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::RulesetContext* CSSParser::ruleset() {
  RulesetContext *_localctx = _tracker.createInstance<RulesetContext>(_ctx, getState());
  enterRule(_localctx, 50, CSSParser::RuleRuleset);
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
    setState(312);
    selectorList();
    setState(313);
    match(CSSParser::LBRACE);
    setState(317);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::IDENT) {
      setState(314);
      declaration();
      setState(319);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(320);
    match(CSSParser::RBRACE);
   
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

std::vector<tree::TerminalNode *> CSSParser::SelectorListContext::COMMA() {
  return getTokens(CSSParser::COMMA);
}

tree::TerminalNode* CSSParser::SelectorListContext::COMMA(size_t i) {
  return getToken(CSSParser::COMMA, i);
}


size_t CSSParser::SelectorListContext::getRuleIndex() const {
  return CSSParser::RuleSelectorList;
}


std::any CSSParser::SelectorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSelectorList(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SelectorListContext* CSSParser::selectorList() {
  SelectorListContext *_localctx = _tracker.createInstance<SelectorListContext>(_ctx, getState());
  enterRule(_localctx, 52, CSSParser::RuleSelectorList);
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
    setState(322);
    selector();
    setState(327);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::COMMA) {
      setState(323);
      match(CSSParser::COMMA);
      setState(324);
      selector();
      setState(329);
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


std::any CSSParser::SelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSelector(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SelectorContext* CSSParser::selector() {
  SelectorContext *_localctx = _tracker.createInstance<SelectorContext>(_ctx, getState());
  enterRule(_localctx, 54, CSSParser::RuleSelector);
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
    simpleSelector();
    setState(336);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::PLUS)
      | (1ULL << CSSParser::GREATER)
      | (1ULL << CSSParser::TILDE)
      | (1ULL << CSSParser::SPACE))) != 0)) {
      setState(331);
      combinator();
      setState(332);
      simpleSelector();
      setState(338);
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

tree::TerminalNode* CSSParser::CombinatorContext::PLUS() {
  return getToken(CSSParser::PLUS, 0);
}

tree::TerminalNode* CSSParser::CombinatorContext::GREATER() {
  return getToken(CSSParser::GREATER, 0);
}

tree::TerminalNode* CSSParser::CombinatorContext::TILDE() {
  return getToken(CSSParser::TILDE, 0);
}

tree::TerminalNode* CSSParser::CombinatorContext::SPACE() {
  return getToken(CSSParser::SPACE, 0);
}


size_t CSSParser::CombinatorContext::getRuleIndex() const {
  return CSSParser::RuleCombinator;
}


std::any CSSParser::CombinatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitCombinator(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::CombinatorContext* CSSParser::combinator() {
  CombinatorContext *_localctx = _tracker.createInstance<CombinatorContext>(_ctx, getState());
  enterRule(_localctx, 56, CSSParser::RuleCombinator);
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
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::PLUS)
      | (1ULL << CSSParser::GREATER)
      | (1ULL << CSSParser::TILDE)
      | (1ULL << CSSParser::SPACE))) != 0))) {
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

CSSParser::UniversalContext* CSSParser::SimpleSelectorContext::universal() {
  return getRuleContext<CSSParser::UniversalContext>(0);
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

std::vector<CSSParser::PseudoClassContext *> CSSParser::SimpleSelectorContext::pseudoClass() {
  return getRuleContexts<CSSParser::PseudoClassContext>();
}

CSSParser::PseudoClassContext* CSSParser::SimpleSelectorContext::pseudoClass(size_t i) {
  return getRuleContext<CSSParser::PseudoClassContext>(i);
}

std::vector<CSSParser::PseudoElementContext *> CSSParser::SimpleSelectorContext::pseudoElement() {
  return getRuleContexts<CSSParser::PseudoElementContext>();
}

CSSParser::PseudoElementContext* CSSParser::SimpleSelectorContext::pseudoElement(size_t i) {
  return getRuleContext<CSSParser::PseudoElementContext>(i);
}


size_t CSSParser::SimpleSelectorContext::getRuleIndex() const {
  return CSSParser::RuleSimpleSelector;
}


std::any CSSParser::SimpleSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitSimpleSelector(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::SimpleSelectorContext* CSSParser::simpleSelector() {
  SimpleSelectorContext *_localctx = _tracker.createInstance<SimpleSelectorContext>(_ctx, getState());
  enterRule(_localctx, 58, CSSParser::RuleSimpleSelector);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(364);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(343);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
      case 1: {
        setState(341);
        typeSelector();
        break;
      }

      case 2: {
        setState(342);
        universal();
        break;
      }

      default:
        break;
      }
      setState(352);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CSSParser::LBRACKET)
        | (1ULL << CSSParser::COLON)
        | (1ULL << CSSParser::DOT)
        | (1ULL << CSSParser::HASH))) != 0)) {
        setState(350);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
        case 1: {
          setState(345);
          idSelector();
          break;
        }

        case 2: {
          setState(346);
          classSelector();
          break;
        }

        case 3: {
          setState(347);
          attributeSelector();
          break;
        }

        case 4: {
          setState(348);
          pseudoClass();
          break;
        }

        case 5: {
          setState(349);
          pseudoElement();
          break;
        }

        default:
          break;
        }
        setState(354);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(360); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(360);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          setState(355);
          idSelector();
          break;
        }

        case 2: {
          setState(356);
          classSelector();
          break;
        }

        case 3: {
          setState(357);
          attributeSelector();
          break;
        }

        case 4: {
          setState(358);
          pseudoClass();
          break;
        }

        case 5: {
          setState(359);
          pseudoElement();
          break;
        }

        default:
          break;
        }
        setState(362); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CSSParser::LBRACKET)
        | (1ULL << CSSParser::COLON)
        | (1ULL << CSSParser::DOT)
        | (1ULL << CSSParser::HASH))) != 0));
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

CSSParser::ElementNameContext* CSSParser::TypeSelectorContext::elementName() {
  return getRuleContext<CSSParser::ElementNameContext>(0);
}

CSSParser::TypeNamespacePrefixContext* CSSParser::TypeSelectorContext::typeNamespacePrefix() {
  return getRuleContext<CSSParser::TypeNamespacePrefixContext>(0);
}


size_t CSSParser::TypeSelectorContext::getRuleIndex() const {
  return CSSParser::RuleTypeSelector;
}


std::any CSSParser::TypeSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitTypeSelector(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::TypeSelectorContext* CSSParser::typeSelector() {
  TypeSelectorContext *_localctx = _tracker.createInstance<TypeSelectorContext>(_ctx, getState());
  enterRule(_localctx, 60, CSSParser::RuleTypeSelector);

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
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(366);
      typeNamespacePrefix();
      break;
    }

    default:
      break;
    }
    setState(369);
    elementName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNamespacePrefixContext ------------------------------------------------------------------

CSSParser::TypeNamespacePrefixContext::TypeNamespacePrefixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::TypeNamespacePrefixContext::PIPE() {
  return getToken(CSSParser::PIPE, 0);
}

tree::TerminalNode* CSSParser::TypeNamespacePrefixContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}

tree::TerminalNode* CSSParser::TypeNamespacePrefixContext::STAR() {
  return getToken(CSSParser::STAR, 0);
}


size_t CSSParser::TypeNamespacePrefixContext::getRuleIndex() const {
  return CSSParser::RuleTypeNamespacePrefix;
}


std::any CSSParser::TypeNamespacePrefixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitTypeNamespacePrefix(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::TypeNamespacePrefixContext* CSSParser::typeNamespacePrefix() {
  TypeNamespacePrefixContext *_localctx = _tracker.createInstance<TypeNamespacePrefixContext>(_ctx, getState());
  enterRule(_localctx, 62, CSSParser::RuleTypeNamespacePrefix);
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
    setState(372);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::STAR

    || _la == CSSParser::IDENT) {
      setState(371);
      _la = _input->LA(1);
      if (!(_la == CSSParser::STAR

      || _la == CSSParser::IDENT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(374);
    match(CSSParser::PIPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementNameContext ------------------------------------------------------------------

CSSParser::ElementNameContext::ElementNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::ElementNameContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}


size_t CSSParser::ElementNameContext::getRuleIndex() const {
  return CSSParser::RuleElementName;
}


std::any CSSParser::ElementNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitElementName(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::ElementNameContext* CSSParser::elementName() {
  ElementNameContext *_localctx = _tracker.createInstance<ElementNameContext>(_ctx, getState());
  enterRule(_localctx, 64, CSSParser::RuleElementName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(376);
    match(CSSParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UniversalContext ------------------------------------------------------------------

CSSParser::UniversalContext::UniversalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::UniversalContext::STAR() {
  return getToken(CSSParser::STAR, 0);
}

CSSParser::TypeNamespacePrefixContext* CSSParser::UniversalContext::typeNamespacePrefix() {
  return getRuleContext<CSSParser::TypeNamespacePrefixContext>(0);
}


size_t CSSParser::UniversalContext::getRuleIndex() const {
  return CSSParser::RuleUniversal;
}


std::any CSSParser::UniversalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitUniversal(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::UniversalContext* CSSParser::universal() {
  UniversalContext *_localctx = _tracker.createInstance<UniversalContext>(_ctx, getState());
  enterRule(_localctx, 66, CSSParser::RuleUniversal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(379);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      setState(378);
      typeNamespacePrefix();
      break;
    }

    default:
      break;
    }
    setState(381);
    match(CSSParser::STAR);
   
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

tree::TerminalNode* CSSParser::IdSelectorContext::HASH() {
  return getToken(CSSParser::HASH, 0);
}

tree::TerminalNode* CSSParser::IdSelectorContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}


size_t CSSParser::IdSelectorContext::getRuleIndex() const {
  return CSSParser::RuleIdSelector;
}


std::any CSSParser::IdSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitIdSelector(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::IdSelectorContext* CSSParser::idSelector() {
  IdSelectorContext *_localctx = _tracker.createInstance<IdSelectorContext>(_ctx, getState());
  enterRule(_localctx, 68, CSSParser::RuleIdSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(383);
    match(CSSParser::HASH);
    setState(384);
    match(CSSParser::IDENT);
   
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

tree::TerminalNode* CSSParser::ClassSelectorContext::DOT() {
  return getToken(CSSParser::DOT, 0);
}

tree::TerminalNode* CSSParser::ClassSelectorContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}


size_t CSSParser::ClassSelectorContext::getRuleIndex() const {
  return CSSParser::RuleClassSelector;
}


std::any CSSParser::ClassSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitClassSelector(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::ClassSelectorContext* CSSParser::classSelector() {
  ClassSelectorContext *_localctx = _tracker.createInstance<ClassSelectorContext>(_ctx, getState());
  enterRule(_localctx, 70, CSSParser::RuleClassSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(386);
    match(CSSParser::DOT);
    setState(387);
    match(CSSParser::IDENT);
   
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

tree::TerminalNode* CSSParser::AttributeSelectorContext::LBRACKET() {
  return getToken(CSSParser::LBRACKET, 0);
}

std::vector<tree::TerminalNode *> CSSParser::AttributeSelectorContext::IDENT() {
  return getTokens(CSSParser::IDENT);
}

tree::TerminalNode* CSSParser::AttributeSelectorContext::IDENT(size_t i) {
  return getToken(CSSParser::IDENT, i);
}

tree::TerminalNode* CSSParser::AttributeSelectorContext::RBRACKET() {
  return getToken(CSSParser::RBRACKET, 0);
}

CSSParser::AttributeOperatorContext* CSSParser::AttributeSelectorContext::attributeOperator() {
  return getRuleContext<CSSParser::AttributeOperatorContext>(0);
}

tree::TerminalNode* CSSParser::AttributeSelectorContext::STRING() {
  return getToken(CSSParser::STRING, 0);
}


size_t CSSParser::AttributeSelectorContext::getRuleIndex() const {
  return CSSParser::RuleAttributeSelector;
}


std::any CSSParser::AttributeSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitAttributeSelector(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::AttributeSelectorContext* CSSParser::attributeSelector() {
  AttributeSelectorContext *_localctx = _tracker.createInstance<AttributeSelectorContext>(_ctx, getState());
  enterRule(_localctx, 72, CSSParser::RuleAttributeSelector);
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
    setState(389);
    match(CSSParser::LBRACKET);
    setState(390);
    match(CSSParser::IDENT);
    setState(394);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::EQUALS)
      | (1ULL << CSSParser::INCLUDES)
      | (1ULL << CSSParser::DASHMATCH)
      | (1ULL << CSSParser::PREFIXMATCH)
      | (1ULL << CSSParser::SUFFIXMATCH)
      | (1ULL << CSSParser::SUBSTRINGMATCH))) != 0)) {
      setState(391);
      attributeOperator();
      setState(392);
      _la = _input->LA(1);
      if (!(_la == CSSParser::STRING

      || _la == CSSParser::IDENT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(396);
    match(CSSParser::RBRACKET);
   
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

tree::TerminalNode* CSSParser::AttributeOperatorContext::EQUALS() {
  return getToken(CSSParser::EQUALS, 0);
}

tree::TerminalNode* CSSParser::AttributeOperatorContext::INCLUDES() {
  return getToken(CSSParser::INCLUDES, 0);
}

tree::TerminalNode* CSSParser::AttributeOperatorContext::DASHMATCH() {
  return getToken(CSSParser::DASHMATCH, 0);
}

tree::TerminalNode* CSSParser::AttributeOperatorContext::PREFIXMATCH() {
  return getToken(CSSParser::PREFIXMATCH, 0);
}

tree::TerminalNode* CSSParser::AttributeOperatorContext::SUFFIXMATCH() {
  return getToken(CSSParser::SUFFIXMATCH, 0);
}

tree::TerminalNode* CSSParser::AttributeOperatorContext::SUBSTRINGMATCH() {
  return getToken(CSSParser::SUBSTRINGMATCH, 0);
}


size_t CSSParser::AttributeOperatorContext::getRuleIndex() const {
  return CSSParser::RuleAttributeOperator;
}


std::any CSSParser::AttributeOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitAttributeOperator(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::AttributeOperatorContext* CSSParser::attributeOperator() {
  AttributeOperatorContext *_localctx = _tracker.createInstance<AttributeOperatorContext>(_ctx, getState());
  enterRule(_localctx, 74, CSSParser::RuleAttributeOperator);
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
    setState(398);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::EQUALS)
      | (1ULL << CSSParser::INCLUDES)
      | (1ULL << CSSParser::DASHMATCH)
      | (1ULL << CSSParser::PREFIXMATCH)
      | (1ULL << CSSParser::SUFFIXMATCH)
      | (1ULL << CSSParser::SUBSTRINGMATCH))) != 0))) {
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

//----------------- PseudoClassContext ------------------------------------------------------------------

CSSParser::PseudoClassContext::PseudoClassContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CSSParser::PseudoClassContext::COLON() {
  return getTokens(CSSParser::COLON);
}

tree::TerminalNode* CSSParser::PseudoClassContext::COLON(size_t i) {
  return getToken(CSSParser::COLON, i);
}

tree::TerminalNode* CSSParser::PseudoClassContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}

CSSParser::FunctionalPseudoClassContext* CSSParser::PseudoClassContext::functionalPseudoClass() {
  return getRuleContext<CSSParser::FunctionalPseudoClassContext>(0);
}


size_t CSSParser::PseudoClassContext::getRuleIndex() const {
  return CSSParser::RulePseudoClass;
}


std::any CSSParser::PseudoClassContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitPseudoClass(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::PseudoClassContext* CSSParser::pseudoClass() {
  PseudoClassContext *_localctx = _tracker.createInstance<PseudoClassContext>(_ctx, getState());
  enterRule(_localctx, 76, CSSParser::RulePseudoClass);
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
    setState(400);
    match(CSSParser::COLON);
    setState(402);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::COLON) {
      setState(401);
      match(CSSParser::COLON);
    }
    setState(406);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::IDENT: {
        setState(404);
        match(CSSParser::IDENT);
        break;
      }

      case CSSParser::FUNCTION: {
        setState(405);
        functionalPseudoClass();
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

//----------------- FunctionalPseudoClassContext ------------------------------------------------------------------

CSSParser::FunctionalPseudoClassContext::FunctionalPseudoClassContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::FunctionalPseudoClassContext::FUNCTION() {
  return getToken(CSSParser::FUNCTION, 0);
}

tree::TerminalNode* CSSParser::FunctionalPseudoClassContext::RPAREN() {
  return getToken(CSSParser::RPAREN, 0);
}

CSSParser::SelectorListContext* CSSParser::FunctionalPseudoClassContext::selectorList() {
  return getRuleContext<CSSParser::SelectorListContext>(0);
}


size_t CSSParser::FunctionalPseudoClassContext::getRuleIndex() const {
  return CSSParser::RuleFunctionalPseudoClass;
}


std::any CSSParser::FunctionalPseudoClassContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitFunctionalPseudoClass(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::FunctionalPseudoClassContext* CSSParser::functionalPseudoClass() {
  FunctionalPseudoClassContext *_localctx = _tracker.createInstance<FunctionalPseudoClassContext>(_ctx, getState());
  enterRule(_localctx, 78, CSSParser::RuleFunctionalPseudoClass);

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
    match(CSSParser::FUNCTION);
    setState(410);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      setState(409);
      selectorList();
      break;
    }

    default:
      break;
    }
    setState(412);
    match(CSSParser::RPAREN);
   
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

std::vector<tree::TerminalNode *> CSSParser::PseudoElementContext::COLON() {
  return getTokens(CSSParser::COLON);
}

tree::TerminalNode* CSSParser::PseudoElementContext::COLON(size_t i) {
  return getToken(CSSParser::COLON, i);
}

tree::TerminalNode* CSSParser::PseudoElementContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}


size_t CSSParser::PseudoElementContext::getRuleIndex() const {
  return CSSParser::RulePseudoElement;
}


std::any CSSParser::PseudoElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitPseudoElement(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::PseudoElementContext* CSSParser::pseudoElement() {
  PseudoElementContext *_localctx = _tracker.createInstance<PseudoElementContext>(_ctx, getState());
  enterRule(_localctx, 80, CSSParser::RulePseudoElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(414);
    match(CSSParser::COLON);
    setState(415);
    match(CSSParser::COLON);
    setState(416);
    match(CSSParser::IDENT);
   
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

tree::TerminalNode* CSSParser::DeclarationContext::COLON() {
  return getToken(CSSParser::COLON, 0);
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


std::any CSSParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::DeclarationContext* CSSParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 82, CSSParser::RuleDeclaration);
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
    setState(418);
    property();
    setState(419);
    match(CSSParser::COLON);
    setState(420);
    value();
    setState(422);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSSParser::IMPORTANT) {
      setState(421);
      match(CSSParser::IMPORTANT);
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

std::vector<tree::TerminalNode *> CSSParser::PropertyContext::IDENT() {
  return getTokens(CSSParser::IDENT);
}

tree::TerminalNode* CSSParser::PropertyContext::IDENT(size_t i) {
  return getToken(CSSParser::IDENT, i);
}

std::vector<tree::TerminalNode *> CSSParser::PropertyContext::MINUS() {
  return getTokens(CSSParser::MINUS);
}

tree::TerminalNode* CSSParser::PropertyContext::MINUS(size_t i) {
  return getToken(CSSParser::MINUS, i);
}


size_t CSSParser::PropertyContext::getRuleIndex() const {
  return CSSParser::RuleProperty;
}


std::any CSSParser::PropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitProperty(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::PropertyContext* CSSParser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 84, CSSParser::RuleProperty);
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
    setState(424);
    match(CSSParser::IDENT);
    setState(429);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSSParser::MINUS) {
      setState(425);
      match(CSSParser::MINUS);
      setState(426);
      match(CSSParser::IDENT);
      setState(431);
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


std::any CSSParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::ValueContext* CSSParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 86, CSSParser::RuleValue);
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
    setState(432);
    term();
    setState(439);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(434);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << CSSParser::COMMA)
          | (1ULL << CSSParser::SLASH)
          | (1ULL << CSSParser::SPACE))) != 0)) {
          setState(433);
          operator_();
        }
        setState(436);
        term(); 
      }
      setState(441);
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

//----------------- TermContext ------------------------------------------------------------------

CSSParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::TermContext::NUMBER() {
  return getToken(CSSParser::NUMBER, 0);
}

tree::TerminalNode* CSSParser::TermContext::PERCENTAGE() {
  return getToken(CSSParser::PERCENTAGE, 0);
}

tree::TerminalNode* CSSParser::TermContext::LENGTH() {
  return getToken(CSSParser::LENGTH, 0);
}

tree::TerminalNode* CSSParser::TermContext::EMS() {
  return getToken(CSSParser::EMS, 0);
}

tree::TerminalNode* CSSParser::TermContext::EXS() {
  return getToken(CSSParser::EXS, 0);
}

tree::TerminalNode* CSSParser::TermContext::ANGLE() {
  return getToken(CSSParser::ANGLE, 0);
}

tree::TerminalNode* CSSParser::TermContext::TIME() {
  return getToken(CSSParser::TIME, 0);
}

tree::TerminalNode* CSSParser::TermContext::FREQ() {
  return getToken(CSSParser::FREQ, 0);
}

tree::TerminalNode* CSSParser::TermContext::STRING() {
  return getToken(CSSParser::STRING, 0);
}

tree::TerminalNode* CSSParser::TermContext::IDENT() {
  return getToken(CSSParser::IDENT, 0);
}

CSSParser::UrlContext* CSSParser::TermContext::url() {
  return getRuleContext<CSSParser::UrlContext>(0);
}

CSSParser::HexcolorContext* CSSParser::TermContext::hexcolor() {
  return getRuleContext<CSSParser::HexcolorContext>(0);
}

CSSParser::FunctionContext* CSSParser::TermContext::function() {
  return getRuleContext<CSSParser::FunctionContext>(0);
}


size_t CSSParser::TermContext::getRuleIndex() const {
  return CSSParser::RuleTerm;
}


std::any CSSParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::TermContext* CSSParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 88, CSSParser::RuleTerm);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(455);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CSSParser::NUMBER: {
        enterOuterAlt(_localctx, 1);
        setState(442);
        match(CSSParser::NUMBER);
        break;
      }

      case CSSParser::PERCENTAGE: {
        enterOuterAlt(_localctx, 2);
        setState(443);
        match(CSSParser::PERCENTAGE);
        break;
      }

      case CSSParser::LENGTH: {
        enterOuterAlt(_localctx, 3);
        setState(444);
        match(CSSParser::LENGTH);
        break;
      }

      case CSSParser::EMS: {
        enterOuterAlt(_localctx, 4);
        setState(445);
        match(CSSParser::EMS);
        break;
      }

      case CSSParser::EXS: {
        enterOuterAlt(_localctx, 5);
        setState(446);
        match(CSSParser::EXS);
        break;
      }

      case CSSParser::ANGLE: {
        enterOuterAlt(_localctx, 6);
        setState(447);
        match(CSSParser::ANGLE);
        break;
      }

      case CSSParser::TIME: {
        enterOuterAlt(_localctx, 7);
        setState(448);
        match(CSSParser::TIME);
        break;
      }

      case CSSParser::FREQ: {
        enterOuterAlt(_localctx, 8);
        setState(449);
        match(CSSParser::FREQ);
        break;
      }

      case CSSParser::STRING: {
        enterOuterAlt(_localctx, 9);
        setState(450);
        match(CSSParser::STRING);
        break;
      }

      case CSSParser::IDENT: {
        enterOuterAlt(_localctx, 10);
        setState(451);
        match(CSSParser::IDENT);
        break;
      }

      case CSSParser::URL: {
        enterOuterAlt(_localctx, 11);
        setState(452);
        url();
        break;
      }

      case CSSParser::HASH: {
        enterOuterAlt(_localctx, 12);
        setState(453);
        hexcolor();
        break;
      }

      case CSSParser::FUNCTION: {
        enterOuterAlt(_localctx, 13);
        setState(454);
        function();
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

//----------------- FunctionContext ------------------------------------------------------------------

CSSParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::FunctionContext::FUNCTION() {
  return getToken(CSSParser::FUNCTION, 0);
}

tree::TerminalNode* CSSParser::FunctionContext::RPAREN() {
  return getToken(CSSParser::RPAREN, 0);
}

std::vector<CSSParser::ValueContext *> CSSParser::FunctionContext::value() {
  return getRuleContexts<CSSParser::ValueContext>();
}

CSSParser::ValueContext* CSSParser::FunctionContext::value(size_t i) {
  return getRuleContext<CSSParser::ValueContext>(i);
}


size_t CSSParser::FunctionContext::getRuleIndex() const {
  return CSSParser::RuleFunction;
}


std::any CSSParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::FunctionContext* CSSParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 90, CSSParser::RuleFunction);
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
    match(CSSParser::FUNCTION);
    setState(461);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::HASH)
      | (1ULL << CSSParser::LENGTH)
      | (1ULL << CSSParser::EMS)
      | (1ULL << CSSParser::EXS)
      | (1ULL << CSSParser::ANGLE)
      | (1ULL << CSSParser::TIME)
      | (1ULL << CSSParser::FREQ)
      | (1ULL << CSSParser::PERCENTAGE)
      | (1ULL << CSSParser::FUNCTION)
      | (1ULL << CSSParser::URL)
      | (1ULL << CSSParser::NUMBER)
      | (1ULL << CSSParser::STRING)
      | (1ULL << CSSParser::IDENT))) != 0)) {
      setState(458);
      value();
      setState(463);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(464);
    match(CSSParser::RPAREN);
   
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

tree::TerminalNode* CSSParser::HexcolorContext::HASH() {
  return getToken(CSSParser::HASH, 0);
}

std::vector<tree::TerminalNode *> CSSParser::HexcolorContext::HEXDIGIT() {
  return getTokens(CSSParser::HEXDIGIT);
}

tree::TerminalNode* CSSParser::HexcolorContext::HEXDIGIT(size_t i) {
  return getToken(CSSParser::HEXDIGIT, i);
}


size_t CSSParser::HexcolorContext::getRuleIndex() const {
  return CSSParser::RuleHexcolor;
}


std::any CSSParser::HexcolorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitHexcolor(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::HexcolorContext* CSSParser::hexcolor() {
  HexcolorContext *_localctx = _tracker.createInstance<HexcolorContext>(_ctx, getState());
  enterRule(_localctx, 92, CSSParser::RuleHexcolor);
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
    setState(466);
    match(CSSParser::HASH);
    setState(468); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(467);
      match(CSSParser::HEXDIGIT);
      setState(470); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CSSParser::HEXDIGIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UrlContext ------------------------------------------------------------------

CSSParser::UrlContext::UrlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::UrlContext::URL() {
  return getToken(CSSParser::URL, 0);
}

tree::TerminalNode* CSSParser::UrlContext::LPAREN() {
  return getToken(CSSParser::LPAREN, 0);
}

tree::TerminalNode* CSSParser::UrlContext::STRING() {
  return getToken(CSSParser::STRING, 0);
}

tree::TerminalNode* CSSParser::UrlContext::RPAREN() {
  return getToken(CSSParser::RPAREN, 0);
}


size_t CSSParser::UrlContext::getRuleIndex() const {
  return CSSParser::RuleUrl;
}


std::any CSSParser::UrlContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitUrl(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::UrlContext* CSSParser::url() {
  UrlContext *_localctx = _tracker.createInstance<UrlContext>(_ctx, getState());
  enterRule(_localctx, 94, CSSParser::RuleUrl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(472);
    match(CSSParser::URL);
    setState(473);
    match(CSSParser::LPAREN);
    setState(474);
    match(CSSParser::STRING);
    setState(475);
    match(CSSParser::RPAREN);
   
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

tree::TerminalNode* CSSParser::OperatorContext::COMMA() {
  return getToken(CSSParser::COMMA, 0);
}

tree::TerminalNode* CSSParser::OperatorContext::SPACE() {
  return getToken(CSSParser::SPACE, 0);
}

tree::TerminalNode* CSSParser::OperatorContext::SLASH() {
  return getToken(CSSParser::SLASH, 0);
}


size_t CSSParser::OperatorContext::getRuleIndex() const {
  return CSSParser::RuleOperator;
}


std::any CSSParser::OperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitOperator(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::OperatorContext* CSSParser::operator_() {
  OperatorContext *_localctx = _tracker.createInstance<OperatorContext>(_ctx, getState());
  enterRule(_localctx, 96, CSSParser::RuleOperator);
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
    setState(477);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CSSParser::COMMA)
      | (1ULL << CSSParser::SLASH)
      | (1ULL << CSSParser::SPACE))) != 0))) {
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

//----------------- ImportantContext ------------------------------------------------------------------

CSSParser::ImportantContext::ImportantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::ImportantContext::IMPORTANT() {
  return getToken(CSSParser::IMPORTANT, 0);
}


size_t CSSParser::ImportantContext::getRuleIndex() const {
  return CSSParser::RuleImportant;
}


std::any CSSParser::ImportantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitImportant(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::ImportantContext* CSSParser::important() {
  ImportantContext *_localctx = _tracker.createInstance<ImportantContext>(_ctx, getState());
  enterRule(_localctx, 98, CSSParser::RuleImportant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(479);
    match(CSSParser::IMPORTANT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NestedStatementContext ------------------------------------------------------------------

CSSParser::NestedStatementContext::NestedStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSSParser::NestedStatementContext::SEMICOLON() {
  return getToken(CSSParser::SEMICOLON, 0);
}


size_t CSSParser::NestedStatementContext::getRuleIndex() const {
  return CSSParser::RuleNestedStatement;
}


std::any CSSParser::NestedStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSSVisitor*>(visitor))
    return parserVisitor->visitNestedStatement(this);
  else
    return visitor->visitChildren(this);
}

CSSParser::NestedStatementContext* CSSParser::nestedStatement() {
  NestedStatementContext *_localctx = _tracker.createInstance<NestedStatementContext>(_ctx, getState());
  enterRule(_localctx, 100, CSSParser::RuleNestedStatement);

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
    match(CSSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void CSSParser::initialize() {
  std::call_once(cssParserOnceFlag, cssParserInitialize);
}
