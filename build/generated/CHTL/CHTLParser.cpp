
// Generated from /workspace/grammar/CHTL.g4 by ANTLR 4.10


#include "CHTLVisitor.h"

#include "CHTLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CHTLParserStaticData final {
  CHTLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CHTLParserStaticData(const CHTLParserStaticData&) = delete;
  CHTLParserStaticData(CHTLParserStaticData&&) = delete;
  CHTLParserStaticData& operator=(const CHTLParserStaticData&) = delete;
  CHTLParserStaticData& operator=(CHTLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag chtlParserOnceFlag;
CHTLParserStaticData *chtlParserStaticData = nullptr;

void chtlParserInitialize() {
  assert(chtlParserStaticData == nullptr);
  auto staticData = std::make_unique<CHTLParserStaticData>(
    std::vector<std::string>{
      "program", "statement", "comment", "textNode", "stringLiteral", "element", 
      "elementName", "elementBody", "elementContent", "attribute", "attributeName", 
      "attributeValue", "styleBlock", "styleContent", "cssProperty", "cssPropertyName", 
      "cssPropertyValue", "cssValue", "cssSelector", "selectorPattern", 
      "classSelector", "idSelector", "ampersandSelector", "pseudoSelector", 
      "scriptBlock", "jsCode", "templateDeclaration", "templateType", "templateName", 
      "templateBody", "templateContent", "varDeclaration", "customDeclaration", 
      "customType", "customName", "customBody", "customContent", "cssPropertyWithoutValue", 
      "templateUsage", "templateSpecialization", "specializationContent", 
      "varAssignment", "customUsage", "customSpecialization", "inheritStatement", 
      "deleteStatement", "deleteTarget", "elementIndex", "insertStatement", 
      "insertPosition", "insertTarget", "insertContent", "exceptStatement", 
      "exceptTarget", "originBlock", "originType", "originName", "originBody", 
      "rawContent", "importStatement", "importContent", "importHtml", "importCss", 
      "importJs", "importChtl", "importCustom", "importTemplate", "filePath", 
      "namespaceDeclaration", "namespaceName", "namespaceBody", "namespaceContent", 
      "configurationBlock", "configContent", "configAssignment", "configValue", 
      "nameBlock", "nameAssignment"
    },
    std::vector<std::string>{
      "", "'text'", "'style'", "'script'", "'Template'", "'Custom'", "'Origin'", 
      "'Import'", "'Namespace'", "'Configuration'", "'Name'", "'Info'", 
      "'Export'", "", "'@Element'", "'@Var'", "'@Html'", "'@JavaScript'", 
      "'@Chtl'", "'inherit'", "'delete'", "'insert'", "'after'", "'before'", 
      "'replace'", "'at'", "'top'", "'bottom'", "'from'", "'as'", "'except'", 
      "", "':'", "';'", "'='", "','", "'.'", "'#'", "'&'", "'-'", "'{'", 
      "'}'", "'['", "']'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "TEXT", "STYLE", "SCRIPT", "TEMPLATE", "CUSTOM", "ORIGIN", "IMPORT", 
      "NAMESPACE", "CONFIGURATION", "NAME", "INFO", "EXPORT", "AT_STYLE", 
      "AT_ELEMENT", "AT_VAR", "AT_HTML", "AT_JAVASCRIPT", "AT_CHTL", "INHERIT", 
      "DELETE", "INSERT", "AFTER", "BEFORE", "REPLACE", "AT", "TOP", "BOTTOM", 
      "FROM", "AS", "EXCEPT", "BOOLEAN", "COLON", "SEMICOLON", "EQUALS", 
      "COMMA", "DOT", "HASH", "AMPERSAND", "MINUS", "LBRACE", "RBRACE", 
      "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "LINE_COMMENT", "BLOCK_COMMENT", 
      "GENERATOR_COMMENT", "STRING_LITERAL", "SINGLE_STRING_LITERAL", "IDENTIFIER", 
      "NUMBER", "UNQUOTED_LITERAL", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,54,719,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,7,
  	77,1,0,5,0,158,8,0,10,0,12,0,161,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,3,1,176,8,1,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,
  	5,1,5,3,5,189,8,5,1,6,1,6,1,7,1,7,5,7,195,8,7,10,7,12,7,198,9,7,1,7,1,
  	7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,213,8,8,1,9,1,9,1,9,
  	1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,5,12,227,8,12,10,12,12,12,
  	230,9,12,1,12,1,12,1,13,1,13,1,13,3,13,237,8,13,1,14,1,14,1,14,1,14,1,
  	14,1,15,1,15,1,15,5,15,247,8,15,10,15,12,15,250,9,15,1,16,1,16,3,16,254,
  	8,16,1,17,4,17,257,8,17,11,17,12,17,258,1,18,1,18,1,18,5,18,264,8,18,
  	10,18,12,18,267,9,18,1,18,1,18,1,19,1,19,1,19,1,19,3,19,275,8,19,1,20,
  	1,20,1,20,1,21,1,21,1,21,1,22,1,22,1,22,3,22,286,8,22,1,22,1,22,1,22,
  	3,22,291,8,22,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,25,5,25,302,8,
  	25,10,25,12,25,305,9,25,1,26,1,26,1,26,1,26,1,26,1,26,3,26,313,8,26,1,
  	27,1,27,1,28,1,28,1,29,1,29,5,29,321,8,29,10,29,12,29,324,9,29,1,29,1,
  	29,1,30,1,30,1,30,1,30,1,30,3,30,333,8,30,1,31,1,31,1,31,1,31,1,31,1,
  	32,1,32,1,32,1,32,1,32,1,32,3,32,346,8,32,1,33,1,33,1,34,1,34,1,35,1,
  	35,5,35,354,8,35,10,35,12,35,357,9,35,1,35,1,35,1,36,1,36,1,36,1,36,1,
  	36,1,36,1,36,1,36,1,36,3,36,370,8,36,1,37,1,37,1,37,5,37,375,8,37,10,
  	37,12,37,378,9,37,1,37,1,37,1,38,1,38,1,38,3,38,385,8,38,1,38,1,38,1,
  	39,1,39,5,39,391,8,39,10,39,12,39,394,9,39,1,39,1,39,1,40,1,40,1,40,3,
  	40,401,8,40,1,41,1,41,1,41,1,41,1,42,1,42,1,42,3,42,410,8,42,1,42,1,42,
  	1,42,3,42,415,8,42,1,42,1,42,1,43,1,43,5,43,421,8,43,10,43,12,43,424,
  	9,43,1,43,1,43,1,44,1,44,1,44,1,44,1,44,1,45,1,45,1,45,1,45,5,45,437,
  	8,45,10,45,12,45,440,9,45,1,45,1,45,1,46,1,46,1,46,3,46,447,8,46,1,46,
  	1,46,1,46,1,46,1,46,1,46,3,46,455,8,46,1,47,1,47,1,47,1,47,1,48,1,48,
  	1,48,1,48,1,48,5,48,466,8,48,10,48,12,48,469,9,48,1,48,1,48,1,49,1,49,
  	1,49,1,49,1,49,1,49,1,49,3,49,480,8,49,1,50,1,50,3,50,484,8,50,1,51,1,
  	51,3,51,488,8,51,1,52,1,52,1,52,1,52,5,52,494,8,52,10,52,12,52,497,9,
  	52,1,52,1,52,1,53,1,53,1,53,3,53,504,8,53,1,53,1,53,3,53,508,8,53,1,53,
  	1,53,1,53,1,53,1,53,1,53,1,53,3,53,517,8,53,1,54,1,54,1,54,1,54,1,54,
  	3,54,524,8,54,1,54,1,54,1,55,1,55,1,56,1,56,1,57,1,57,1,57,1,57,1,58,
  	5,58,537,8,58,10,58,12,58,540,9,58,1,59,1,59,1,59,1,59,1,59,1,60,1,60,
  	1,60,1,60,1,60,1,60,3,60,553,8,60,1,61,1,61,1,61,1,61,1,61,3,61,560,8,
  	61,1,61,1,61,1,62,1,62,1,62,1,62,1,62,3,62,569,8,62,1,62,1,62,1,63,1,
  	63,1,63,1,63,1,63,3,63,578,8,63,1,63,1,63,1,64,1,64,1,64,1,64,1,64,1,
  	65,1,65,1,65,1,65,1,65,1,65,1,65,1,65,1,65,3,65,596,8,65,1,65,1,65,1,
  	66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,3,66,609,8,66,1,66,1,66,1,
  	67,1,67,1,68,1,68,1,68,1,68,1,68,3,68,620,8,68,1,68,1,68,1,68,1,68,1,
  	68,1,68,5,68,628,8,68,10,68,12,68,631,9,68,1,68,1,68,3,68,635,8,68,1,
  	69,1,69,1,69,5,69,640,8,69,10,69,12,69,643,9,69,1,70,1,70,5,70,647,8,
  	70,10,70,12,70,650,9,70,1,70,1,70,1,71,1,71,1,71,1,71,3,71,658,8,71,1,
  	72,1,72,1,72,1,72,1,72,5,72,665,8,72,10,72,12,72,668,9,72,1,72,1,72,1,
  	73,1,73,3,73,674,8,73,1,74,1,74,1,74,1,74,1,74,1,75,1,75,1,75,3,75,684,
  	8,75,1,76,1,76,1,76,1,76,1,76,5,76,691,8,76,10,76,12,76,694,9,76,1,76,
  	1,76,1,77,1,77,1,77,1,77,1,77,1,77,1,77,1,77,1,77,1,77,1,77,5,77,709,
  	8,77,10,77,12,77,712,9,77,1,77,1,77,1,77,3,77,717,8,77,1,77,0,0,78,0,
  	2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,
  	98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,
  	134,136,138,140,142,144,146,148,150,152,154,0,7,1,0,46,48,2,0,49,50,53,
  	53,2,0,32,32,34,34,2,0,33,33,41,41,1,0,41,41,1,0,13,15,2,0,13,13,16,17,
  	747,0,159,1,0,0,0,2,175,1,0,0,0,4,177,1,0,0,0,6,179,1,0,0,0,8,184,1,0,
  	0,0,10,186,1,0,0,0,12,190,1,0,0,0,14,192,1,0,0,0,16,212,1,0,0,0,18,214,
  	1,0,0,0,20,219,1,0,0,0,22,221,1,0,0,0,24,223,1,0,0,0,26,236,1,0,0,0,28,
  	238,1,0,0,0,30,243,1,0,0,0,32,253,1,0,0,0,34,256,1,0,0,0,36,260,1,0,0,
  	0,38,274,1,0,0,0,40,276,1,0,0,0,42,279,1,0,0,0,44,282,1,0,0,0,46,292,
  	1,0,0,0,48,295,1,0,0,0,50,303,1,0,0,0,52,306,1,0,0,0,54,314,1,0,0,0,56,
  	316,1,0,0,0,58,318,1,0,0,0,60,332,1,0,0,0,62,334,1,0,0,0,64,339,1,0,0,
  	0,66,347,1,0,0,0,68,349,1,0,0,0,70,351,1,0,0,0,72,369,1,0,0,0,74,371,
  	1,0,0,0,76,381,1,0,0,0,78,388,1,0,0,0,80,400,1,0,0,0,82,402,1,0,0,0,84,
  	409,1,0,0,0,86,418,1,0,0,0,88,427,1,0,0,0,90,432,1,0,0,0,92,454,1,0,0,
  	0,94,456,1,0,0,0,96,460,1,0,0,0,98,479,1,0,0,0,100,481,1,0,0,0,102,487,
  	1,0,0,0,104,489,1,0,0,0,106,516,1,0,0,0,108,518,1,0,0,0,110,527,1,0,0,
  	0,112,529,1,0,0,0,114,531,1,0,0,0,116,538,1,0,0,0,118,541,1,0,0,0,120,
  	552,1,0,0,0,122,554,1,0,0,0,124,563,1,0,0,0,126,572,1,0,0,0,128,581,1,
  	0,0,0,130,586,1,0,0,0,132,599,1,0,0,0,134,612,1,0,0,0,136,634,1,0,0,0,
  	138,636,1,0,0,0,140,644,1,0,0,0,142,657,1,0,0,0,144,659,1,0,0,0,146,673,
  	1,0,0,0,148,675,1,0,0,0,150,683,1,0,0,0,152,685,1,0,0,0,154,716,1,0,0,
  	0,156,158,3,2,1,0,157,156,1,0,0,0,158,161,1,0,0,0,159,157,1,0,0,0,159,
  	160,1,0,0,0,160,162,1,0,0,0,161,159,1,0,0,0,162,163,5,0,0,1,163,1,1,0,
  	0,0,164,176,3,10,5,0,165,176,3,6,3,0,166,176,3,24,12,0,167,176,3,48,24,
  	0,168,176,3,52,26,0,169,176,3,64,32,0,170,176,3,108,54,0,171,176,3,118,
  	59,0,172,176,3,136,68,0,173,176,3,144,72,0,174,176,3,4,2,0,175,164,1,
  	0,0,0,175,165,1,0,0,0,175,166,1,0,0,0,175,167,1,0,0,0,175,168,1,0,0,0,
  	175,169,1,0,0,0,175,170,1,0,0,0,175,171,1,0,0,0,175,172,1,0,0,0,175,173,
  	1,0,0,0,175,174,1,0,0,0,176,3,1,0,0,0,177,178,7,0,0,0,178,5,1,0,0,0,179,
  	180,5,1,0,0,180,181,5,40,0,0,181,182,3,8,4,0,182,183,5,41,0,0,183,7,1,
  	0,0,0,184,185,7,1,0,0,185,9,1,0,0,0,186,188,3,12,6,0,187,189,3,14,7,0,
  	188,187,1,0,0,0,188,189,1,0,0,0,189,11,1,0,0,0,190,191,5,51,0,0,191,13,
  	1,0,0,0,192,196,5,40,0,0,193,195,3,16,8,0,194,193,1,0,0,0,195,198,1,0,
  	0,0,196,194,1,0,0,0,196,197,1,0,0,0,197,199,1,0,0,0,198,196,1,0,0,0,199,
  	200,5,41,0,0,200,15,1,0,0,0,201,213,3,18,9,0,202,213,3,10,5,0,203,213,
  	3,6,3,0,204,213,3,24,12,0,205,213,3,48,24,0,206,213,3,76,38,0,207,213,
  	3,84,42,0,208,213,3,108,54,0,209,213,3,96,48,0,210,213,3,90,45,0,211,
  	213,3,104,52,0,212,201,1,0,0,0,212,202,1,0,0,0,212,203,1,0,0,0,212,204,
  	1,0,0,0,212,205,1,0,0,0,212,206,1,0,0,0,212,207,1,0,0,0,212,208,1,0,0,
  	0,212,209,1,0,0,0,212,210,1,0,0,0,212,211,1,0,0,0,213,17,1,0,0,0,214,
  	215,3,20,10,0,215,216,7,2,0,0,216,217,3,22,11,0,217,218,5,33,0,0,218,
  	19,1,0,0,0,219,220,5,51,0,0,220,21,1,0,0,0,221,222,3,8,4,0,222,23,1,0,
  	0,0,223,224,5,2,0,0,224,228,5,40,0,0,225,227,3,26,13,0,226,225,1,0,0,
  	0,227,230,1,0,0,0,228,226,1,0,0,0,228,229,1,0,0,0,229,231,1,0,0,0,230,
  	228,1,0,0,0,231,232,5,41,0,0,232,25,1,0,0,0,233,237,3,28,14,0,234,237,
  	3,36,18,0,235,237,3,76,38,0,236,233,1,0,0,0,236,234,1,0,0,0,236,235,1,
  	0,0,0,237,27,1,0,0,0,238,239,3,30,15,0,239,240,5,32,0,0,240,241,3,32,
  	16,0,241,242,5,33,0,0,242,29,1,0,0,0,243,248,5,51,0,0,244,245,5,39,0,
  	0,245,247,5,51,0,0,246,244,1,0,0,0,247,250,1,0,0,0,248,246,1,0,0,0,248,
  	249,1,0,0,0,249,31,1,0,0,0,250,248,1,0,0,0,251,254,3,8,4,0,252,254,3,
  	34,17,0,253,251,1,0,0,0,253,252,1,0,0,0,254,33,1,0,0,0,255,257,8,3,0,
  	0,256,255,1,0,0,0,257,258,1,0,0,0,258,256,1,0,0,0,258,259,1,0,0,0,259,
  	35,1,0,0,0,260,261,3,38,19,0,261,265,5,40,0,0,262,264,3,28,14,0,263,262,
  	1,0,0,0,264,267,1,0,0,0,265,263,1,0,0,0,265,266,1,0,0,0,266,268,1,0,0,
  	0,267,265,1,0,0,0,268,269,5,41,0,0,269,37,1,0,0,0,270,275,3,40,20,0,271,
  	275,3,42,21,0,272,275,3,44,22,0,273,275,3,46,23,0,274,270,1,0,0,0,274,
  	271,1,0,0,0,274,272,1,0,0,0,274,273,1,0,0,0,275,39,1,0,0,0,276,277,5,
  	36,0,0,277,278,5,51,0,0,278,41,1,0,0,0,279,280,5,37,0,0,280,281,5,51,
  	0,0,281,43,1,0,0,0,282,285,5,38,0,0,283,284,5,32,0,0,284,286,5,51,0,0,
  	285,283,1,0,0,0,285,286,1,0,0,0,286,290,1,0,0,0,287,288,5,32,0,0,288,
  	289,5,32,0,0,289,291,5,51,0,0,290,287,1,0,0,0,290,291,1,0,0,0,291,45,
  	1,0,0,0,292,293,5,32,0,0,293,294,5,51,0,0,294,47,1,0,0,0,295,296,5,3,
  	0,0,296,297,5,40,0,0,297,298,3,50,25,0,298,299,5,41,0,0,299,49,1,0,0,
  	0,300,302,8,4,0,0,301,300,1,0,0,0,302,305,1,0,0,0,303,301,1,0,0,0,303,
  	304,1,0,0,0,304,51,1,0,0,0,305,303,1,0,0,0,306,307,5,42,0,0,307,308,5,
  	4,0,0,308,309,5,43,0,0,309,310,3,54,27,0,310,312,3,56,28,0,311,313,3,
  	58,29,0,312,311,1,0,0,0,312,313,1,0,0,0,313,53,1,0,0,0,314,315,7,5,0,
  	0,315,55,1,0,0,0,316,317,5,51,0,0,317,57,1,0,0,0,318,322,5,40,0,0,319,
  	321,3,60,30,0,320,319,1,0,0,0,321,324,1,0,0,0,322,320,1,0,0,0,322,323,
  	1,0,0,0,323,325,1,0,0,0,324,322,1,0,0,0,325,326,5,41,0,0,326,59,1,0,0,
  	0,327,333,3,28,14,0,328,333,3,10,5,0,329,333,3,62,31,0,330,333,3,76,38,
  	0,331,333,3,88,44,0,332,327,1,0,0,0,332,328,1,0,0,0,332,329,1,0,0,0,332,
  	330,1,0,0,0,332,331,1,0,0,0,333,61,1,0,0,0,334,335,5,51,0,0,335,336,5,
  	32,0,0,336,337,3,8,4,0,337,338,5,33,0,0,338,63,1,0,0,0,339,340,5,42,0,
  	0,340,341,5,5,0,0,341,342,5,43,0,0,342,343,3,66,33,0,343,345,3,68,34,
  	0,344,346,3,70,35,0,345,344,1,0,0,0,345,346,1,0,0,0,346,65,1,0,0,0,347,
  	348,7,5,0,0,348,67,1,0,0,0,349,350,5,51,0,0,350,69,1,0,0,0,351,355,5,
  	40,0,0,352,354,3,72,36,0,353,352,1,0,0,0,354,357,1,0,0,0,355,353,1,0,
  	0,0,355,356,1,0,0,0,356,358,1,0,0,0,357,355,1,0,0,0,358,359,5,41,0,0,
  	359,71,1,0,0,0,360,370,3,28,14,0,361,370,3,74,37,0,362,370,3,10,5,0,363,
  	370,3,62,31,0,364,370,3,76,38,0,365,370,3,84,42,0,366,370,3,90,45,0,367,
  	370,3,96,48,0,368,370,3,88,44,0,369,360,1,0,0,0,369,361,1,0,0,0,369,362,
  	1,0,0,0,369,363,1,0,0,0,369,364,1,0,0,0,369,365,1,0,0,0,369,366,1,0,0,
  	0,369,367,1,0,0,0,369,368,1,0,0,0,370,73,1,0,0,0,371,376,3,30,15,0,372,
  	373,5,35,0,0,373,375,3,30,15,0,374,372,1,0,0,0,375,378,1,0,0,0,376,374,
  	1,0,0,0,376,377,1,0,0,0,377,379,1,0,0,0,378,376,1,0,0,0,379,380,5,33,
  	0,0,380,75,1,0,0,0,381,382,3,54,27,0,382,384,3,56,28,0,383,385,3,78,39,
  	0,384,383,1,0,0,0,384,385,1,0,0,0,385,386,1,0,0,0,386,387,5,33,0,0,387,
  	77,1,0,0,0,388,392,5,40,0,0,389,391,3,80,40,0,390,389,1,0,0,0,391,394,
  	1,0,0,0,392,390,1,0,0,0,392,393,1,0,0,0,393,395,1,0,0,0,394,392,1,0,0,
  	0,395,396,5,41,0,0,396,79,1,0,0,0,397,401,3,28,14,0,398,401,3,90,45,0,
  	399,401,3,82,41,0,400,397,1,0,0,0,400,398,1,0,0,0,400,399,1,0,0,0,401,
  	81,1,0,0,0,402,403,5,51,0,0,403,404,5,34,0,0,404,405,3,8,4,0,405,83,1,
  	0,0,0,406,407,5,42,0,0,407,408,5,5,0,0,408,410,5,43,0,0,409,406,1,0,0,
  	0,409,410,1,0,0,0,410,411,1,0,0,0,411,412,3,66,33,0,412,414,3,68,34,0,
  	413,415,3,86,43,0,414,413,1,0,0,0,414,415,1,0,0,0,415,416,1,0,0,0,416,
  	417,5,33,0,0,417,85,1,0,0,0,418,422,5,40,0,0,419,421,3,80,40,0,420,419,
  	1,0,0,0,421,424,1,0,0,0,422,420,1,0,0,0,422,423,1,0,0,0,423,425,1,0,0,
  	0,424,422,1,0,0,0,425,426,5,41,0,0,426,87,1,0,0,0,427,428,5,19,0,0,428,
  	429,3,54,27,0,429,430,3,56,28,0,430,431,5,33,0,0,431,89,1,0,0,0,432,433,
  	5,20,0,0,433,438,3,92,46,0,434,435,5,35,0,0,435,437,3,92,46,0,436,434,
  	1,0,0,0,437,440,1,0,0,0,438,436,1,0,0,0,438,439,1,0,0,0,439,441,1,0,0,
  	0,440,438,1,0,0,0,441,442,5,33,0,0,442,91,1,0,0,0,443,455,3,30,15,0,444,
  	446,3,12,6,0,445,447,3,94,47,0,446,445,1,0,0,0,446,447,1,0,0,0,447,455,
  	1,0,0,0,448,449,3,54,27,0,449,450,3,56,28,0,450,455,1,0,0,0,451,452,3,
  	66,33,0,452,453,3,68,34,0,453,455,1,0,0,0,454,443,1,0,0,0,454,444,1,0,
  	0,0,454,448,1,0,0,0,454,451,1,0,0,0,455,93,1,0,0,0,456,457,5,42,0,0,457,
  	458,5,52,0,0,458,459,5,43,0,0,459,95,1,0,0,0,460,461,5,21,0,0,461,462,
  	3,98,49,0,462,463,3,100,50,0,463,467,5,40,0,0,464,466,3,102,51,0,465,
  	464,1,0,0,0,466,469,1,0,0,0,467,465,1,0,0,0,467,468,1,0,0,0,468,470,1,
  	0,0,0,469,467,1,0,0,0,470,471,5,41,0,0,471,97,1,0,0,0,472,480,5,22,0,
  	0,473,480,5,23,0,0,474,480,5,24,0,0,475,476,5,25,0,0,476,480,5,26,0,0,
  	477,478,5,25,0,0,478,480,5,27,0,0,479,472,1,0,0,0,479,473,1,0,0,0,479,
  	474,1,0,0,0,479,475,1,0,0,0,479,477,1,0,0,0,480,99,1,0,0,0,481,483,3,
  	12,6,0,482,484,3,94,47,0,483,482,1,0,0,0,483,484,1,0,0,0,484,101,1,0,
  	0,0,485,488,3,10,5,0,486,488,3,76,38,0,487,485,1,0,0,0,487,486,1,0,0,
  	0,488,103,1,0,0,0,489,490,5,30,0,0,490,495,3,106,53,0,491,492,5,35,0,
  	0,492,494,3,106,53,0,493,491,1,0,0,0,494,497,1,0,0,0,495,493,1,0,0,0,
  	495,496,1,0,0,0,496,498,1,0,0,0,497,495,1,0,0,0,498,499,5,33,0,0,499,
  	105,1,0,0,0,500,517,3,12,6,0,501,503,3,54,27,0,502,504,3,56,28,0,503,
  	502,1,0,0,0,503,504,1,0,0,0,504,517,1,0,0,0,505,507,3,66,33,0,506,508,
  	3,68,34,0,507,506,1,0,0,0,507,508,1,0,0,0,508,517,1,0,0,0,509,517,5,16,
  	0,0,510,511,5,42,0,0,511,512,5,5,0,0,512,517,5,43,0,0,513,514,5,42,0,
  	0,514,515,5,4,0,0,515,517,5,43,0,0,516,500,1,0,0,0,516,501,1,0,0,0,516,
  	505,1,0,0,0,516,509,1,0,0,0,516,510,1,0,0,0,516,513,1,0,0,0,517,107,1,
  	0,0,0,518,519,5,42,0,0,519,520,5,6,0,0,520,521,5,43,0,0,521,523,3,110,
  	55,0,522,524,3,112,56,0,523,522,1,0,0,0,523,524,1,0,0,0,524,525,1,0,0,
  	0,525,526,3,114,57,0,526,109,1,0,0,0,527,528,7,6,0,0,528,111,1,0,0,0,
  	529,530,5,51,0,0,530,113,1,0,0,0,531,532,5,40,0,0,532,533,3,116,58,0,
  	533,534,5,41,0,0,534,115,1,0,0,0,535,537,8,4,0,0,536,535,1,0,0,0,537,
  	540,1,0,0,0,538,536,1,0,0,0,538,539,1,0,0,0,539,117,1,0,0,0,540,538,1,
  	0,0,0,541,542,5,42,0,0,542,543,5,7,0,0,543,544,5,43,0,0,544,545,3,120,
  	60,0,545,119,1,0,0,0,546,553,3,122,61,0,547,553,3,124,62,0,548,553,3,
  	126,63,0,549,553,3,128,64,0,550,553,3,130,65,0,551,553,3,132,66,0,552,
  	546,1,0,0,0,552,547,1,0,0,0,552,548,1,0,0,0,552,549,1,0,0,0,552,550,1,
  	0,0,0,552,551,1,0,0,0,553,121,1,0,0,0,554,555,5,16,0,0,555,556,5,28,0,
  	0,556,559,3,134,67,0,557,558,5,29,0,0,558,560,5,51,0,0,559,557,1,0,0,
  	0,559,560,1,0,0,0,560,561,1,0,0,0,561,562,5,33,0,0,562,123,1,0,0,0,563,
  	564,5,13,0,0,564,565,5,28,0,0,565,568,3,134,67,0,566,567,5,29,0,0,567,
  	569,5,51,0,0,568,566,1,0,0,0,568,569,1,0,0,0,569,570,1,0,0,0,570,571,
  	5,33,0,0,571,125,1,0,0,0,572,573,5,17,0,0,573,574,5,28,0,0,574,577,3,
  	134,67,0,575,576,5,29,0,0,576,578,5,51,0,0,577,575,1,0,0,0,577,578,1,
  	0,0,0,578,579,1,0,0,0,579,580,5,33,0,0,580,127,1,0,0,0,581,582,5,18,0,
  	0,582,583,5,28,0,0,583,584,3,134,67,0,584,585,5,33,0,0,585,129,1,0,0,
  	0,586,587,5,42,0,0,587,588,5,5,0,0,588,589,5,43,0,0,589,590,3,66,33,0,
  	590,591,3,68,34,0,591,592,5,28,0,0,592,595,3,134,67,0,593,594,5,29,0,
  	0,594,596,5,51,0,0,595,593,1,0,0,0,595,596,1,0,0,0,596,597,1,0,0,0,597,
  	598,5,33,0,0,598,131,1,0,0,0,599,600,5,42,0,0,600,601,5,4,0,0,601,602,
  	5,43,0,0,602,603,3,54,27,0,603,604,3,56,28,0,604,605,5,28,0,0,605,608,
  	3,134,67,0,606,607,5,29,0,0,607,609,5,51,0,0,608,606,1,0,0,0,608,609,
  	1,0,0,0,609,610,1,0,0,0,610,611,5,33,0,0,611,133,1,0,0,0,612,613,3,8,
  	4,0,613,135,1,0,0,0,614,615,5,42,0,0,615,616,5,8,0,0,616,617,5,43,0,0,
  	617,619,3,138,69,0,618,620,3,140,70,0,619,618,1,0,0,0,619,620,1,0,0,0,
  	620,635,1,0,0,0,621,622,5,42,0,0,622,623,5,8,0,0,623,624,5,43,0,0,624,
  	625,3,138,69,0,625,629,5,40,0,0,626,628,3,142,71,0,627,626,1,0,0,0,628,
  	631,1,0,0,0,629,627,1,0,0,0,629,630,1,0,0,0,630,632,1,0,0,0,631,629,1,
  	0,0,0,632,633,5,41,0,0,633,635,1,0,0,0,634,614,1,0,0,0,634,621,1,0,0,
  	0,635,137,1,0,0,0,636,641,5,51,0,0,637,638,5,36,0,0,638,640,5,51,0,0,
  	639,637,1,0,0,0,640,643,1,0,0,0,641,639,1,0,0,0,641,642,1,0,0,0,642,139,
  	1,0,0,0,643,641,1,0,0,0,644,648,5,40,0,0,645,647,3,142,71,0,646,645,1,
  	0,0,0,647,650,1,0,0,0,648,646,1,0,0,0,648,649,1,0,0,0,649,651,1,0,0,0,
  	650,648,1,0,0,0,651,652,5,41,0,0,652,141,1,0,0,0,653,658,3,136,68,0,654,
  	658,3,52,26,0,655,658,3,64,32,0,656,658,3,104,52,0,657,653,1,0,0,0,657,
  	654,1,0,0,0,657,655,1,0,0,0,657,656,1,0,0,0,658,143,1,0,0,0,659,660,5,
  	42,0,0,660,661,5,9,0,0,661,662,5,43,0,0,662,666,5,40,0,0,663,665,3,146,
  	73,0,664,663,1,0,0,0,665,668,1,0,0,0,666,664,1,0,0,0,666,667,1,0,0,0,
  	667,669,1,0,0,0,668,666,1,0,0,0,669,670,5,41,0,0,670,145,1,0,0,0,671,
  	674,3,148,74,0,672,674,3,152,76,0,673,671,1,0,0,0,673,672,1,0,0,0,674,
  	147,1,0,0,0,675,676,5,51,0,0,676,677,5,34,0,0,677,678,3,150,75,0,678,
  	679,5,33,0,0,679,149,1,0,0,0,680,684,3,8,4,0,681,684,5,52,0,0,682,684,
  	5,31,0,0,683,680,1,0,0,0,683,681,1,0,0,0,683,682,1,0,0,0,684,151,1,0,
  	0,0,685,686,5,42,0,0,686,687,5,10,0,0,687,688,5,43,0,0,688,692,5,40,0,
  	0,689,691,3,154,77,0,690,689,1,0,0,0,691,694,1,0,0,0,692,690,1,0,0,0,
  	692,693,1,0,0,0,693,695,1,0,0,0,694,692,1,0,0,0,695,696,5,41,0,0,696,
  	153,1,0,0,0,697,698,5,51,0,0,698,699,5,34,0,0,699,700,3,8,4,0,700,701,
  	5,33,0,0,701,717,1,0,0,0,702,703,5,51,0,0,703,704,5,34,0,0,704,705,5,
  	42,0,0,705,710,3,8,4,0,706,707,5,35,0,0,707,709,3,8,4,0,708,706,1,0,0,
  	0,709,712,1,0,0,0,710,708,1,0,0,0,710,711,1,0,0,0,711,713,1,0,0,0,712,
  	710,1,0,0,0,713,714,5,43,0,0,714,715,5,33,0,0,715,717,1,0,0,0,716,697,
  	1,0,0,0,716,702,1,0,0,0,717,155,1,0,0,0,59,159,175,188,196,212,228,236,
  	248,253,258,265,274,285,290,303,312,322,332,345,355,369,376,384,392,400,
  	409,414,422,438,446,454,467,479,483,487,495,503,507,516,523,538,552,559,
  	568,577,595,608,619,629,634,641,648,657,666,673,683,692,710,716
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  chtlParserStaticData = staticData.release();
}

}

CHTLParser::CHTLParser(TokenStream *input) : CHTLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CHTLParser::CHTLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CHTLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *chtlParserStaticData->atn, chtlParserStaticData->decisionToDFA, chtlParserStaticData->sharedContextCache, options);
}

CHTLParser::~CHTLParser() {
  delete _interpreter;
}

const atn::ATN& CHTLParser::getATN() const {
  return *chtlParserStaticData->atn;
}

std::string CHTLParser::getGrammarFileName() const {
  return "CHTL.g4";
}

const std::vector<std::string>& CHTLParser::getRuleNames() const {
  return chtlParserStaticData->ruleNames;
}

const dfa::Vocabulary& CHTLParser::getVocabulary() const {
  return chtlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CHTLParser::getSerializedATN() const {
  return chtlParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

CHTLParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ProgramContext::EOF() {
  return getToken(CHTLParser::EOF, 0);
}

std::vector<CHTLParser::StatementContext *> CHTLParser::ProgramContext::statement() {
  return getRuleContexts<CHTLParser::StatementContext>();
}

CHTLParser::StatementContext* CHTLParser::ProgramContext::statement(size_t i) {
  return getRuleContext<CHTLParser::StatementContext>(i);
}


size_t CHTLParser::ProgramContext::getRuleIndex() const {
  return CHTLParser::RuleProgram;
}


std::any CHTLParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ProgramContext* CHTLParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CHTLParser::RuleProgram);
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
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::TEXT)
      | (1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::LBRACKET)
      | (1ULL << CHTLParser::LINE_COMMENT)
      | (1ULL << CHTLParser::BLOCK_COMMENT)
      | (1ULL << CHTLParser::GENERATOR_COMMENT)
      | (1ULL << CHTLParser::IDENTIFIER))) != 0)) {
      setState(156);
      statement();
      setState(161);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(162);
    match(CHTLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CHTLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ElementContext* CHTLParser::StatementContext::element() {
  return getRuleContext<CHTLParser::ElementContext>(0);
}

CHTLParser::TextNodeContext* CHTLParser::StatementContext::textNode() {
  return getRuleContext<CHTLParser::TextNodeContext>(0);
}

CHTLParser::StyleBlockContext* CHTLParser::StatementContext::styleBlock() {
  return getRuleContext<CHTLParser::StyleBlockContext>(0);
}

CHTLParser::ScriptBlockContext* CHTLParser::StatementContext::scriptBlock() {
  return getRuleContext<CHTLParser::ScriptBlockContext>(0);
}

CHTLParser::TemplateDeclarationContext* CHTLParser::StatementContext::templateDeclaration() {
  return getRuleContext<CHTLParser::TemplateDeclarationContext>(0);
}

CHTLParser::CustomDeclarationContext* CHTLParser::StatementContext::customDeclaration() {
  return getRuleContext<CHTLParser::CustomDeclarationContext>(0);
}

CHTLParser::OriginBlockContext* CHTLParser::StatementContext::originBlock() {
  return getRuleContext<CHTLParser::OriginBlockContext>(0);
}

CHTLParser::ImportStatementContext* CHTLParser::StatementContext::importStatement() {
  return getRuleContext<CHTLParser::ImportStatementContext>(0);
}

CHTLParser::NamespaceDeclarationContext* CHTLParser::StatementContext::namespaceDeclaration() {
  return getRuleContext<CHTLParser::NamespaceDeclarationContext>(0);
}

CHTLParser::ConfigurationBlockContext* CHTLParser::StatementContext::configurationBlock() {
  return getRuleContext<CHTLParser::ConfigurationBlockContext>(0);
}

CHTLParser::CommentContext* CHTLParser::StatementContext::comment() {
  return getRuleContext<CHTLParser::CommentContext>(0);
}


size_t CHTLParser::StatementContext::getRuleIndex() const {
  return CHTLParser::RuleStatement;
}


std::any CHTLParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::StatementContext* CHTLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, CHTLParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(175);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(164);
      element();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(165);
      textNode();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(166);
      styleBlock();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(167);
      scriptBlock();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(168);
      templateDeclaration();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(169);
      customDeclaration();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(170);
      originBlock();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(171);
      importStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(172);
      namespaceDeclaration();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(173);
      configurationBlock();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(174);
      comment();
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

//----------------- CommentContext ------------------------------------------------------------------

CHTLParser::CommentContext::CommentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CommentContext::LINE_COMMENT() {
  return getToken(CHTLParser::LINE_COMMENT, 0);
}

tree::TerminalNode* CHTLParser::CommentContext::BLOCK_COMMENT() {
  return getToken(CHTLParser::BLOCK_COMMENT, 0);
}

tree::TerminalNode* CHTLParser::CommentContext::GENERATOR_COMMENT() {
  return getToken(CHTLParser::GENERATOR_COMMENT, 0);
}


size_t CHTLParser::CommentContext::getRuleIndex() const {
  return CHTLParser::RuleComment;
}


std::any CHTLParser::CommentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitComment(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CommentContext* CHTLParser::comment() {
  CommentContext *_localctx = _tracker.createInstance<CommentContext>(_ctx, getState());
  enterRule(_localctx, 4, CHTLParser::RuleComment);
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
    setState(177);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::LINE_COMMENT)
      | (1ULL << CHTLParser::BLOCK_COMMENT)
      | (1ULL << CHTLParser::GENERATOR_COMMENT))) != 0))) {
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

//----------------- TextNodeContext ------------------------------------------------------------------

CHTLParser::TextNodeContext::TextNodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TextNodeContext::TEXT() {
  return getToken(CHTLParser::TEXT, 0);
}

tree::TerminalNode* CHTLParser::TextNodeContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::StringLiteralContext* CHTLParser::TextNodeContext::stringLiteral() {
  return getRuleContext<CHTLParser::StringLiteralContext>(0);
}

tree::TerminalNode* CHTLParser::TextNodeContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::TextNodeContext::getRuleIndex() const {
  return CHTLParser::RuleTextNode;
}


std::any CHTLParser::TextNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitTextNode(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::TextNodeContext* CHTLParser::textNode() {
  TextNodeContext *_localctx = _tracker.createInstance<TextNodeContext>(_ctx, getState());
  enterRule(_localctx, 6, CHTLParser::RuleTextNode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(179);
    match(CHTLParser::TEXT);
    setState(180);
    match(CHTLParser::LBRACE);
    setState(181);
    stringLiteral();
    setState(182);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

CHTLParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::StringLiteralContext::STRING_LITERAL() {
  return getToken(CHTLParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CHTLParser::StringLiteralContext::SINGLE_STRING_LITERAL() {
  return getToken(CHTLParser::SINGLE_STRING_LITERAL, 0);
}

tree::TerminalNode* CHTLParser::StringLiteralContext::UNQUOTED_LITERAL() {
  return getToken(CHTLParser::UNQUOTED_LITERAL, 0);
}


size_t CHTLParser::StringLiteralContext::getRuleIndex() const {
  return CHTLParser::RuleStringLiteral;
}


std::any CHTLParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::StringLiteralContext* CHTLParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 8, CHTLParser::RuleStringLiteral);
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
    setState(184);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::STRING_LITERAL)
      | (1ULL << CHTLParser::SINGLE_STRING_LITERAL)
      | (1ULL << CHTLParser::UNQUOTED_LITERAL))) != 0))) {
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

//----------------- ElementContext ------------------------------------------------------------------

CHTLParser::ElementContext::ElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ElementNameContext* CHTLParser::ElementContext::elementName() {
  return getRuleContext<CHTLParser::ElementNameContext>(0);
}

CHTLParser::ElementBodyContext* CHTLParser::ElementContext::elementBody() {
  return getRuleContext<CHTLParser::ElementBodyContext>(0);
}


size_t CHTLParser::ElementContext::getRuleIndex() const {
  return CHTLParser::RuleElement;
}


std::any CHTLParser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ElementContext* CHTLParser::element() {
  ElementContext *_localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
  enterRule(_localctx, 10, CHTLParser::RuleElement);
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
    setState(186);
    elementName();
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACE) {
      setState(187);
      elementBody();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementNameContext ------------------------------------------------------------------

CHTLParser::ElementNameContext::ElementNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ElementNameContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ElementNameContext::getRuleIndex() const {
  return CHTLParser::RuleElementName;
}


std::any CHTLParser::ElementNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitElementName(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ElementNameContext* CHTLParser::elementName() {
  ElementNameContext *_localctx = _tracker.createInstance<ElementNameContext>(_ctx, getState());
  enterRule(_localctx, 12, CHTLParser::RuleElementName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementBodyContext ------------------------------------------------------------------

CHTLParser::ElementBodyContext::ElementBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ElementBodyContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::ElementBodyContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::ElementContentContext *> CHTLParser::ElementBodyContext::elementContent() {
  return getRuleContexts<CHTLParser::ElementContentContext>();
}

CHTLParser::ElementContentContext* CHTLParser::ElementBodyContext::elementContent(size_t i) {
  return getRuleContext<CHTLParser::ElementContentContext>(i);
}


size_t CHTLParser::ElementBodyContext::getRuleIndex() const {
  return CHTLParser::RuleElementBody;
}


std::any CHTLParser::ElementBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitElementBody(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ElementBodyContext* CHTLParser::elementBody() {
  ElementBodyContext *_localctx = _tracker.createInstance<ElementBodyContext>(_ctx, getState());
  enterRule(_localctx, 14, CHTLParser::RuleElementBody);
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
    setState(192);
    match(CHTLParser::LBRACE);
    setState(196);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::TEXT)
      | (1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR)
      | (1ULL << CHTLParser::DELETE)
      | (1ULL << CHTLParser::INSERT)
      | (1ULL << CHTLParser::EXCEPT)
      | (1ULL << CHTLParser::LBRACKET)
      | (1ULL << CHTLParser::IDENTIFIER))) != 0)) {
      setState(193);
      elementContent();
      setState(198);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(199);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContentContext ------------------------------------------------------------------

CHTLParser::ElementContentContext::ElementContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::AttributeContext* CHTLParser::ElementContentContext::attribute() {
  return getRuleContext<CHTLParser::AttributeContext>(0);
}

CHTLParser::ElementContext* CHTLParser::ElementContentContext::element() {
  return getRuleContext<CHTLParser::ElementContext>(0);
}

CHTLParser::TextNodeContext* CHTLParser::ElementContentContext::textNode() {
  return getRuleContext<CHTLParser::TextNodeContext>(0);
}

CHTLParser::StyleBlockContext* CHTLParser::ElementContentContext::styleBlock() {
  return getRuleContext<CHTLParser::StyleBlockContext>(0);
}

CHTLParser::ScriptBlockContext* CHTLParser::ElementContentContext::scriptBlock() {
  return getRuleContext<CHTLParser::ScriptBlockContext>(0);
}

CHTLParser::TemplateUsageContext* CHTLParser::ElementContentContext::templateUsage() {
  return getRuleContext<CHTLParser::TemplateUsageContext>(0);
}

CHTLParser::CustomUsageContext* CHTLParser::ElementContentContext::customUsage() {
  return getRuleContext<CHTLParser::CustomUsageContext>(0);
}

CHTLParser::OriginBlockContext* CHTLParser::ElementContentContext::originBlock() {
  return getRuleContext<CHTLParser::OriginBlockContext>(0);
}

CHTLParser::InsertStatementContext* CHTLParser::ElementContentContext::insertStatement() {
  return getRuleContext<CHTLParser::InsertStatementContext>(0);
}

CHTLParser::DeleteStatementContext* CHTLParser::ElementContentContext::deleteStatement() {
  return getRuleContext<CHTLParser::DeleteStatementContext>(0);
}

CHTLParser::ExceptStatementContext* CHTLParser::ElementContentContext::exceptStatement() {
  return getRuleContext<CHTLParser::ExceptStatementContext>(0);
}


size_t CHTLParser::ElementContentContext::getRuleIndex() const {
  return CHTLParser::RuleElementContent;
}


std::any CHTLParser::ElementContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitElementContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ElementContentContext* CHTLParser::elementContent() {
  ElementContentContext *_localctx = _tracker.createInstance<ElementContentContext>(_ctx, getState());
  enterRule(_localctx, 16, CHTLParser::RuleElementContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(212);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(201);
      attribute();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(202);
      element();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(203);
      textNode();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(204);
      styleBlock();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(205);
      scriptBlock();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(206);
      templateUsage();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(207);
      customUsage();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(208);
      originBlock();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(209);
      insertStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(210);
      deleteStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(211);
      exceptStatement();
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

//----------------- AttributeContext ------------------------------------------------------------------

CHTLParser::AttributeContext::AttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::AttributeNameContext* CHTLParser::AttributeContext::attributeName() {
  return getRuleContext<CHTLParser::AttributeNameContext>(0);
}

CHTLParser::AttributeValueContext* CHTLParser::AttributeContext::attributeValue() {
  return getRuleContext<CHTLParser::AttributeValueContext>(0);
}

tree::TerminalNode* CHTLParser::AttributeContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::AttributeContext::COLON() {
  return getToken(CHTLParser::COLON, 0);
}

tree::TerminalNode* CHTLParser::AttributeContext::EQUALS() {
  return getToken(CHTLParser::EQUALS, 0);
}


size_t CHTLParser::AttributeContext::getRuleIndex() const {
  return CHTLParser::RuleAttribute;
}


std::any CHTLParser::AttributeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitAttribute(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::AttributeContext* CHTLParser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 18, CHTLParser::RuleAttribute);
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
    attributeName();
    setState(215);
    _la = _input->LA(1);
    if (!(_la == CHTLParser::COLON

    || _la == CHTLParser::EQUALS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(216);
    attributeValue();
    setState(217);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeNameContext ------------------------------------------------------------------

CHTLParser::AttributeNameContext::AttributeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::AttributeNameContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::AttributeNameContext::getRuleIndex() const {
  return CHTLParser::RuleAttributeName;
}


std::any CHTLParser::AttributeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitAttributeName(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::AttributeNameContext* CHTLParser::attributeName() {
  AttributeNameContext *_localctx = _tracker.createInstance<AttributeNameContext>(_ctx, getState());
  enterRule(_localctx, 20, CHTLParser::RuleAttributeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeValueContext ------------------------------------------------------------------

CHTLParser::AttributeValueContext::AttributeValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::StringLiteralContext* CHTLParser::AttributeValueContext::stringLiteral() {
  return getRuleContext<CHTLParser::StringLiteralContext>(0);
}


size_t CHTLParser::AttributeValueContext::getRuleIndex() const {
  return CHTLParser::RuleAttributeValue;
}


std::any CHTLParser::AttributeValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitAttributeValue(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::AttributeValueContext* CHTLParser::attributeValue() {
  AttributeValueContext *_localctx = _tracker.createInstance<AttributeValueContext>(_ctx, getState());
  enterRule(_localctx, 22, CHTLParser::RuleAttributeValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StyleBlockContext ------------------------------------------------------------------

CHTLParser::StyleBlockContext::StyleBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::StyleBlockContext::STYLE() {
  return getToken(CHTLParser::STYLE, 0);
}

tree::TerminalNode* CHTLParser::StyleBlockContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::StyleBlockContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::StyleContentContext *> CHTLParser::StyleBlockContext::styleContent() {
  return getRuleContexts<CHTLParser::StyleContentContext>();
}

CHTLParser::StyleContentContext* CHTLParser::StyleBlockContext::styleContent(size_t i) {
  return getRuleContext<CHTLParser::StyleContentContext>(i);
}


size_t CHTLParser::StyleBlockContext::getRuleIndex() const {
  return CHTLParser::RuleStyleBlock;
}


std::any CHTLParser::StyleBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitStyleBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::StyleBlockContext* CHTLParser::styleBlock() {
  StyleBlockContext *_localctx = _tracker.createInstance<StyleBlockContext>(_ctx, getState());
  enterRule(_localctx, 24, CHTLParser::RuleStyleBlock);
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
    setState(223);
    match(CHTLParser::STYLE);
    setState(224);
    match(CHTLParser::LBRACE);
    setState(228);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR)
      | (1ULL << CHTLParser::COLON)
      | (1ULL << CHTLParser::DOT)
      | (1ULL << CHTLParser::HASH)
      | (1ULL << CHTLParser::AMPERSAND)
      | (1ULL << CHTLParser::IDENTIFIER))) != 0)) {
      setState(225);
      styleContent();
      setState(230);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(231);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StyleContentContext ------------------------------------------------------------------

CHTLParser::StyleContentContext::StyleContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CssPropertyContext* CHTLParser::StyleContentContext::cssProperty() {
  return getRuleContext<CHTLParser::CssPropertyContext>(0);
}

CHTLParser::CssSelectorContext* CHTLParser::StyleContentContext::cssSelector() {
  return getRuleContext<CHTLParser::CssSelectorContext>(0);
}

CHTLParser::TemplateUsageContext* CHTLParser::StyleContentContext::templateUsage() {
  return getRuleContext<CHTLParser::TemplateUsageContext>(0);
}


size_t CHTLParser::StyleContentContext::getRuleIndex() const {
  return CHTLParser::RuleStyleContent;
}


std::any CHTLParser::StyleContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitStyleContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::StyleContentContext* CHTLParser::styleContent() {
  StyleContentContext *_localctx = _tracker.createInstance<StyleContentContext>(_ctx, getState());
  enterRule(_localctx, 26, CHTLParser::RuleStyleContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(236);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(233);
        cssProperty();
        break;
      }

      case CHTLParser::COLON:
      case CHTLParser::DOT:
      case CHTLParser::HASH:
      case CHTLParser::AMPERSAND: {
        enterOuterAlt(_localctx, 2);
        setState(234);
        cssSelector();
        break;
      }

      case CHTLParser::AT_STYLE:
      case CHTLParser::AT_ELEMENT:
      case CHTLParser::AT_VAR: {
        enterOuterAlt(_localctx, 3);
        setState(235);
        templateUsage();
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

//----------------- CssPropertyContext ------------------------------------------------------------------

CHTLParser::CssPropertyContext::CssPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CssPropertyNameContext* CHTLParser::CssPropertyContext::cssPropertyName() {
  return getRuleContext<CHTLParser::CssPropertyNameContext>(0);
}

tree::TerminalNode* CHTLParser::CssPropertyContext::COLON() {
  return getToken(CHTLParser::COLON, 0);
}

CHTLParser::CssPropertyValueContext* CHTLParser::CssPropertyContext::cssPropertyValue() {
  return getRuleContext<CHTLParser::CssPropertyValueContext>(0);
}

tree::TerminalNode* CHTLParser::CssPropertyContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}


size_t CHTLParser::CssPropertyContext::getRuleIndex() const {
  return CHTLParser::RuleCssProperty;
}


std::any CHTLParser::CssPropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCssProperty(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CssPropertyContext* CHTLParser::cssProperty() {
  CssPropertyContext *_localctx = _tracker.createInstance<CssPropertyContext>(_ctx, getState());
  enterRule(_localctx, 28, CHTLParser::RuleCssProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(238);
    cssPropertyName();
    setState(239);
    match(CHTLParser::COLON);
    setState(240);
    cssPropertyValue();
    setState(241);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CssPropertyNameContext ------------------------------------------------------------------

CHTLParser::CssPropertyNameContext::CssPropertyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::CssPropertyNameContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::CssPropertyNameContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> CHTLParser::CssPropertyNameContext::MINUS() {
  return getTokens(CHTLParser::MINUS);
}

tree::TerminalNode* CHTLParser::CssPropertyNameContext::MINUS(size_t i) {
  return getToken(CHTLParser::MINUS, i);
}


size_t CHTLParser::CssPropertyNameContext::getRuleIndex() const {
  return CHTLParser::RuleCssPropertyName;
}


std::any CHTLParser::CssPropertyNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCssPropertyName(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CssPropertyNameContext* CHTLParser::cssPropertyName() {
  CssPropertyNameContext *_localctx = _tracker.createInstance<CssPropertyNameContext>(_ctx, getState());
  enterRule(_localctx, 30, CHTLParser::RuleCssPropertyName);
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
    setState(243);
    match(CHTLParser::IDENTIFIER);
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::MINUS) {
      setState(244);
      match(CHTLParser::MINUS);
      setState(245);
      match(CHTLParser::IDENTIFIER);
      setState(250);
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

//----------------- CssPropertyValueContext ------------------------------------------------------------------

CHTLParser::CssPropertyValueContext::CssPropertyValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::StringLiteralContext* CHTLParser::CssPropertyValueContext::stringLiteral() {
  return getRuleContext<CHTLParser::StringLiteralContext>(0);
}

CHTLParser::CssValueContext* CHTLParser::CssPropertyValueContext::cssValue() {
  return getRuleContext<CHTLParser::CssValueContext>(0);
}


size_t CHTLParser::CssPropertyValueContext::getRuleIndex() const {
  return CHTLParser::RuleCssPropertyValue;
}


std::any CHTLParser::CssPropertyValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCssPropertyValue(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CssPropertyValueContext* CHTLParser::cssPropertyValue() {
  CssPropertyValueContext *_localctx = _tracker.createInstance<CssPropertyValueContext>(_ctx, getState());
  enterRule(_localctx, 32, CHTLParser::RuleCssPropertyValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(253);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(251);
      stringLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(252);
      cssValue();
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

//----------------- CssValueContext ------------------------------------------------------------------

CHTLParser::CssValueContext::CssValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::CssValueContext::SEMICOLON() {
  return getTokens(CHTLParser::SEMICOLON);
}

tree::TerminalNode* CHTLParser::CssValueContext::SEMICOLON(size_t i) {
  return getToken(CHTLParser::SEMICOLON, i);
}

std::vector<tree::TerminalNode *> CHTLParser::CssValueContext::RBRACE() {
  return getTokens(CHTLParser::RBRACE);
}

tree::TerminalNode* CHTLParser::CssValueContext::RBRACE(size_t i) {
  return getToken(CHTLParser::RBRACE, i);
}


size_t CHTLParser::CssValueContext::getRuleIndex() const {
  return CHTLParser::RuleCssValue;
}


std::any CHTLParser::CssValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCssValue(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CssValueContext* CHTLParser::cssValue() {
  CssValueContext *_localctx = _tracker.createInstance<CssValueContext>(_ctx, getState());
  enterRule(_localctx, 34, CHTLParser::RuleCssValue);
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
    setState(256); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(255);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == CHTLParser::SEMICOLON

      || _la == CHTLParser::RBRACE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(258); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::TEXT)
      | (1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::TEMPLATE)
      | (1ULL << CHTLParser::CUSTOM)
      | (1ULL << CHTLParser::ORIGIN)
      | (1ULL << CHTLParser::IMPORT)
      | (1ULL << CHTLParser::NAMESPACE)
      | (1ULL << CHTLParser::CONFIGURATION)
      | (1ULL << CHTLParser::NAME)
      | (1ULL << CHTLParser::INFO)
      | (1ULL << CHTLParser::EXPORT)
      | (1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR)
      | (1ULL << CHTLParser::AT_HTML)
      | (1ULL << CHTLParser::AT_JAVASCRIPT)
      | (1ULL << CHTLParser::AT_CHTL)
      | (1ULL << CHTLParser::INHERIT)
      | (1ULL << CHTLParser::DELETE)
      | (1ULL << CHTLParser::INSERT)
      | (1ULL << CHTLParser::AFTER)
      | (1ULL << CHTLParser::BEFORE)
      | (1ULL << CHTLParser::REPLACE)
      | (1ULL << CHTLParser::AT)
      | (1ULL << CHTLParser::TOP)
      | (1ULL << CHTLParser::BOTTOM)
      | (1ULL << CHTLParser::FROM)
      | (1ULL << CHTLParser::AS)
      | (1ULL << CHTLParser::EXCEPT)
      | (1ULL << CHTLParser::BOOLEAN)
      | (1ULL << CHTLParser::COLON)
      | (1ULL << CHTLParser::EQUALS)
      | (1ULL << CHTLParser::COMMA)
      | (1ULL << CHTLParser::DOT)
      | (1ULL << CHTLParser::HASH)
      | (1ULL << CHTLParser::AMPERSAND)
      | (1ULL << CHTLParser::MINUS)
      | (1ULL << CHTLParser::LBRACE)
      | (1ULL << CHTLParser::LBRACKET)
      | (1ULL << CHTLParser::RBRACKET)
      | (1ULL << CHTLParser::LPAREN)
      | (1ULL << CHTLParser::RPAREN)
      | (1ULL << CHTLParser::LINE_COMMENT)
      | (1ULL << CHTLParser::BLOCK_COMMENT)
      | (1ULL << CHTLParser::GENERATOR_COMMENT)
      | (1ULL << CHTLParser::STRING_LITERAL)
      | (1ULL << CHTLParser::SINGLE_STRING_LITERAL)
      | (1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::UNQUOTED_LITERAL)
      | (1ULL << CHTLParser::WS))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CssSelectorContext ------------------------------------------------------------------

CHTLParser::CssSelectorContext::CssSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::SelectorPatternContext* CHTLParser::CssSelectorContext::selectorPattern() {
  return getRuleContext<CHTLParser::SelectorPatternContext>(0);
}

tree::TerminalNode* CHTLParser::CssSelectorContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::CssSelectorContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::CssPropertyContext *> CHTLParser::CssSelectorContext::cssProperty() {
  return getRuleContexts<CHTLParser::CssPropertyContext>();
}

CHTLParser::CssPropertyContext* CHTLParser::CssSelectorContext::cssProperty(size_t i) {
  return getRuleContext<CHTLParser::CssPropertyContext>(i);
}


size_t CHTLParser::CssSelectorContext::getRuleIndex() const {
  return CHTLParser::RuleCssSelector;
}


std::any CHTLParser::CssSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCssSelector(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CssSelectorContext* CHTLParser::cssSelector() {
  CssSelectorContext *_localctx = _tracker.createInstance<CssSelectorContext>(_ctx, getState());
  enterRule(_localctx, 36, CHTLParser::RuleCssSelector);
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
    setState(260);
    selectorPattern();
    setState(261);
    match(CHTLParser::LBRACE);
    setState(265);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::IDENTIFIER) {
      setState(262);
      cssProperty();
      setState(267);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(268);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorPatternContext ------------------------------------------------------------------

CHTLParser::SelectorPatternContext::SelectorPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ClassSelectorContext* CHTLParser::SelectorPatternContext::classSelector() {
  return getRuleContext<CHTLParser::ClassSelectorContext>(0);
}

CHTLParser::IdSelectorContext* CHTLParser::SelectorPatternContext::idSelector() {
  return getRuleContext<CHTLParser::IdSelectorContext>(0);
}

CHTLParser::AmpersandSelectorContext* CHTLParser::SelectorPatternContext::ampersandSelector() {
  return getRuleContext<CHTLParser::AmpersandSelectorContext>(0);
}

CHTLParser::PseudoSelectorContext* CHTLParser::SelectorPatternContext::pseudoSelector() {
  return getRuleContext<CHTLParser::PseudoSelectorContext>(0);
}


size_t CHTLParser::SelectorPatternContext::getRuleIndex() const {
  return CHTLParser::RuleSelectorPattern;
}


std::any CHTLParser::SelectorPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitSelectorPattern(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::SelectorPatternContext* CHTLParser::selectorPattern() {
  SelectorPatternContext *_localctx = _tracker.createInstance<SelectorPatternContext>(_ctx, getState());
  enterRule(_localctx, 38, CHTLParser::RuleSelectorPattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(274);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::DOT: {
        enterOuterAlt(_localctx, 1);
        setState(270);
        classSelector();
        break;
      }

      case CHTLParser::HASH: {
        enterOuterAlt(_localctx, 2);
        setState(271);
        idSelector();
        break;
      }

      case CHTLParser::AMPERSAND: {
        enterOuterAlt(_localctx, 3);
        setState(272);
        ampersandSelector();
        break;
      }

      case CHTLParser::COLON: {
        enterOuterAlt(_localctx, 4);
        setState(273);
        pseudoSelector();
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

//----------------- ClassSelectorContext ------------------------------------------------------------------

CHTLParser::ClassSelectorContext::ClassSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ClassSelectorContext::DOT() {
  return getToken(CHTLParser::DOT, 0);
}

tree::TerminalNode* CHTLParser::ClassSelectorContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ClassSelectorContext::getRuleIndex() const {
  return CHTLParser::RuleClassSelector;
}


std::any CHTLParser::ClassSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitClassSelector(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ClassSelectorContext* CHTLParser::classSelector() {
  ClassSelectorContext *_localctx = _tracker.createInstance<ClassSelectorContext>(_ctx, getState());
  enterRule(_localctx, 40, CHTLParser::RuleClassSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(276);
    match(CHTLParser::DOT);
    setState(277);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdSelectorContext ------------------------------------------------------------------

CHTLParser::IdSelectorContext::IdSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::IdSelectorContext::HASH() {
  return getToken(CHTLParser::HASH, 0);
}

tree::TerminalNode* CHTLParser::IdSelectorContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::IdSelectorContext::getRuleIndex() const {
  return CHTLParser::RuleIdSelector;
}


std::any CHTLParser::IdSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitIdSelector(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::IdSelectorContext* CHTLParser::idSelector() {
  IdSelectorContext *_localctx = _tracker.createInstance<IdSelectorContext>(_ctx, getState());
  enterRule(_localctx, 42, CHTLParser::RuleIdSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(279);
    match(CHTLParser::HASH);
    setState(280);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AmpersandSelectorContext ------------------------------------------------------------------

CHTLParser::AmpersandSelectorContext::AmpersandSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::AmpersandSelectorContext::AMPERSAND() {
  return getToken(CHTLParser::AMPERSAND, 0);
}

std::vector<tree::TerminalNode *> CHTLParser::AmpersandSelectorContext::COLON() {
  return getTokens(CHTLParser::COLON);
}

tree::TerminalNode* CHTLParser::AmpersandSelectorContext::COLON(size_t i) {
  return getToken(CHTLParser::COLON, i);
}

std::vector<tree::TerminalNode *> CHTLParser::AmpersandSelectorContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::AmpersandSelectorContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}


size_t CHTLParser::AmpersandSelectorContext::getRuleIndex() const {
  return CHTLParser::RuleAmpersandSelector;
}


std::any CHTLParser::AmpersandSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitAmpersandSelector(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::AmpersandSelectorContext* CHTLParser::ampersandSelector() {
  AmpersandSelectorContext *_localctx = _tracker.createInstance<AmpersandSelectorContext>(_ctx, getState());
  enterRule(_localctx, 44, CHTLParser::RuleAmpersandSelector);
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
    match(CHTLParser::AMPERSAND);
    setState(285);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(283);
      match(CHTLParser::COLON);
      setState(284);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    setState(290);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::COLON) {
      setState(287);
      match(CHTLParser::COLON);
      setState(288);
      match(CHTLParser::COLON);
      setState(289);
      match(CHTLParser::IDENTIFIER);
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

CHTLParser::PseudoSelectorContext::PseudoSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::PseudoSelectorContext::COLON() {
  return getToken(CHTLParser::COLON, 0);
}

tree::TerminalNode* CHTLParser::PseudoSelectorContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::PseudoSelectorContext::getRuleIndex() const {
  return CHTLParser::RulePseudoSelector;
}


std::any CHTLParser::PseudoSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitPseudoSelector(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::PseudoSelectorContext* CHTLParser::pseudoSelector() {
  PseudoSelectorContext *_localctx = _tracker.createInstance<PseudoSelectorContext>(_ctx, getState());
  enterRule(_localctx, 46, CHTLParser::RulePseudoSelector);

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
    match(CHTLParser::COLON);
    setState(293);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptBlockContext ------------------------------------------------------------------

CHTLParser::ScriptBlockContext::ScriptBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ScriptBlockContext::SCRIPT() {
  return getToken(CHTLParser::SCRIPT, 0);
}

tree::TerminalNode* CHTLParser::ScriptBlockContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::JsCodeContext* CHTLParser::ScriptBlockContext::jsCode() {
  return getRuleContext<CHTLParser::JsCodeContext>(0);
}

tree::TerminalNode* CHTLParser::ScriptBlockContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::ScriptBlockContext::getRuleIndex() const {
  return CHTLParser::RuleScriptBlock;
}


std::any CHTLParser::ScriptBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitScriptBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ScriptBlockContext* CHTLParser::scriptBlock() {
  ScriptBlockContext *_localctx = _tracker.createInstance<ScriptBlockContext>(_ctx, getState());
  enterRule(_localctx, 48, CHTLParser::RuleScriptBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    match(CHTLParser::SCRIPT);
    setState(296);
    match(CHTLParser::LBRACE);
    setState(297);
    jsCode();
    setState(298);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JsCodeContext ------------------------------------------------------------------

CHTLParser::JsCodeContext::JsCodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::JsCodeContext::RBRACE() {
  return getTokens(CHTLParser::RBRACE);
}

tree::TerminalNode* CHTLParser::JsCodeContext::RBRACE(size_t i) {
  return getToken(CHTLParser::RBRACE, i);
}


size_t CHTLParser::JsCodeContext::getRuleIndex() const {
  return CHTLParser::RuleJsCode;
}


std::any CHTLParser::JsCodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitJsCode(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::JsCodeContext* CHTLParser::jsCode() {
  JsCodeContext *_localctx = _tracker.createInstance<JsCodeContext>(_ctx, getState());
  enterRule(_localctx, 50, CHTLParser::RuleJsCode);
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
    setState(303);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::TEXT)
      | (1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::TEMPLATE)
      | (1ULL << CHTLParser::CUSTOM)
      | (1ULL << CHTLParser::ORIGIN)
      | (1ULL << CHTLParser::IMPORT)
      | (1ULL << CHTLParser::NAMESPACE)
      | (1ULL << CHTLParser::CONFIGURATION)
      | (1ULL << CHTLParser::NAME)
      | (1ULL << CHTLParser::INFO)
      | (1ULL << CHTLParser::EXPORT)
      | (1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR)
      | (1ULL << CHTLParser::AT_HTML)
      | (1ULL << CHTLParser::AT_JAVASCRIPT)
      | (1ULL << CHTLParser::AT_CHTL)
      | (1ULL << CHTLParser::INHERIT)
      | (1ULL << CHTLParser::DELETE)
      | (1ULL << CHTLParser::INSERT)
      | (1ULL << CHTLParser::AFTER)
      | (1ULL << CHTLParser::BEFORE)
      | (1ULL << CHTLParser::REPLACE)
      | (1ULL << CHTLParser::AT)
      | (1ULL << CHTLParser::TOP)
      | (1ULL << CHTLParser::BOTTOM)
      | (1ULL << CHTLParser::FROM)
      | (1ULL << CHTLParser::AS)
      | (1ULL << CHTLParser::EXCEPT)
      | (1ULL << CHTLParser::BOOLEAN)
      | (1ULL << CHTLParser::COLON)
      | (1ULL << CHTLParser::SEMICOLON)
      | (1ULL << CHTLParser::EQUALS)
      | (1ULL << CHTLParser::COMMA)
      | (1ULL << CHTLParser::DOT)
      | (1ULL << CHTLParser::HASH)
      | (1ULL << CHTLParser::AMPERSAND)
      | (1ULL << CHTLParser::MINUS)
      | (1ULL << CHTLParser::LBRACE)
      | (1ULL << CHTLParser::LBRACKET)
      | (1ULL << CHTLParser::RBRACKET)
      | (1ULL << CHTLParser::LPAREN)
      | (1ULL << CHTLParser::RPAREN)
      | (1ULL << CHTLParser::LINE_COMMENT)
      | (1ULL << CHTLParser::BLOCK_COMMENT)
      | (1ULL << CHTLParser::GENERATOR_COMMENT)
      | (1ULL << CHTLParser::STRING_LITERAL)
      | (1ULL << CHTLParser::SINGLE_STRING_LITERAL)
      | (1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::UNQUOTED_LITERAL)
      | (1ULL << CHTLParser::WS))) != 0)) {
      setState(300);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == CHTLParser::RBRACE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(305);
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

//----------------- TemplateDeclarationContext ------------------------------------------------------------------

CHTLParser::TemplateDeclarationContext::TemplateDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TemplateDeclarationContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::TemplateDeclarationContext::TEMPLATE() {
  return getToken(CHTLParser::TEMPLATE, 0);
}

tree::TerminalNode* CHTLParser::TemplateDeclarationContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

CHTLParser::TemplateTypeContext* CHTLParser::TemplateDeclarationContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

CHTLParser::TemplateNameContext* CHTLParser::TemplateDeclarationContext::templateName() {
  return getRuleContext<CHTLParser::TemplateNameContext>(0);
}

CHTLParser::TemplateBodyContext* CHTLParser::TemplateDeclarationContext::templateBody() {
  return getRuleContext<CHTLParser::TemplateBodyContext>(0);
}


size_t CHTLParser::TemplateDeclarationContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateDeclaration;
}


std::any CHTLParser::TemplateDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitTemplateDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::TemplateDeclarationContext* CHTLParser::templateDeclaration() {
  TemplateDeclarationContext *_localctx = _tracker.createInstance<TemplateDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 52, CHTLParser::RuleTemplateDeclaration);
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
    setState(306);
    match(CHTLParser::LBRACKET);
    setState(307);
    match(CHTLParser::TEMPLATE);
    setState(308);
    match(CHTLParser::RBRACKET);
    setState(309);
    templateType();
    setState(310);
    templateName();
    setState(312);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACE) {
      setState(311);
      templateBody();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateTypeContext ------------------------------------------------------------------

CHTLParser::TemplateTypeContext::TemplateTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TemplateTypeContext::AT_STYLE() {
  return getToken(CHTLParser::AT_STYLE, 0);
}

tree::TerminalNode* CHTLParser::TemplateTypeContext::AT_ELEMENT() {
  return getToken(CHTLParser::AT_ELEMENT, 0);
}

tree::TerminalNode* CHTLParser::TemplateTypeContext::AT_VAR() {
  return getToken(CHTLParser::AT_VAR, 0);
}


size_t CHTLParser::TemplateTypeContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateType;
}


std::any CHTLParser::TemplateTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitTemplateType(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::TemplateTypeContext* CHTLParser::templateType() {
  TemplateTypeContext *_localctx = _tracker.createInstance<TemplateTypeContext>(_ctx, getState());
  enterRule(_localctx, 54, CHTLParser::RuleTemplateType);
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
    setState(314);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR))) != 0))) {
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

//----------------- TemplateNameContext ------------------------------------------------------------------

CHTLParser::TemplateNameContext::TemplateNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TemplateNameContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::TemplateNameContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateName;
}


std::any CHTLParser::TemplateNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitTemplateName(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::TemplateNameContext* CHTLParser::templateName() {
  TemplateNameContext *_localctx = _tracker.createInstance<TemplateNameContext>(_ctx, getState());
  enterRule(_localctx, 56, CHTLParser::RuleTemplateName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(316);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateBodyContext ------------------------------------------------------------------

CHTLParser::TemplateBodyContext::TemplateBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TemplateBodyContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::TemplateBodyContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::TemplateContentContext *> CHTLParser::TemplateBodyContext::templateContent() {
  return getRuleContexts<CHTLParser::TemplateContentContext>();
}

CHTLParser::TemplateContentContext* CHTLParser::TemplateBodyContext::templateContent(size_t i) {
  return getRuleContext<CHTLParser::TemplateContentContext>(i);
}


size_t CHTLParser::TemplateBodyContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateBody;
}


std::any CHTLParser::TemplateBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitTemplateBody(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::TemplateBodyContext* CHTLParser::templateBody() {
  TemplateBodyContext *_localctx = _tracker.createInstance<TemplateBodyContext>(_ctx, getState());
  enterRule(_localctx, 58, CHTLParser::RuleTemplateBody);
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
    setState(318);
    match(CHTLParser::LBRACE);
    setState(322);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR)
      | (1ULL << CHTLParser::INHERIT)
      | (1ULL << CHTLParser::IDENTIFIER))) != 0)) {
      setState(319);
      templateContent();
      setState(324);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(325);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateContentContext ------------------------------------------------------------------

CHTLParser::TemplateContentContext::TemplateContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CssPropertyContext* CHTLParser::TemplateContentContext::cssProperty() {
  return getRuleContext<CHTLParser::CssPropertyContext>(0);
}

CHTLParser::ElementContext* CHTLParser::TemplateContentContext::element() {
  return getRuleContext<CHTLParser::ElementContext>(0);
}

CHTLParser::VarDeclarationContext* CHTLParser::TemplateContentContext::varDeclaration() {
  return getRuleContext<CHTLParser::VarDeclarationContext>(0);
}

CHTLParser::TemplateUsageContext* CHTLParser::TemplateContentContext::templateUsage() {
  return getRuleContext<CHTLParser::TemplateUsageContext>(0);
}

CHTLParser::InheritStatementContext* CHTLParser::TemplateContentContext::inheritStatement() {
  return getRuleContext<CHTLParser::InheritStatementContext>(0);
}


size_t CHTLParser::TemplateContentContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateContent;
}


std::any CHTLParser::TemplateContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitTemplateContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::TemplateContentContext* CHTLParser::templateContent() {
  TemplateContentContext *_localctx = _tracker.createInstance<TemplateContentContext>(_ctx, getState());
  enterRule(_localctx, 60, CHTLParser::RuleTemplateContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(332);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(327);
      cssProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(328);
      element();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(329);
      varDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(330);
      templateUsage();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(331);
      inheritStatement();
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

//----------------- VarDeclarationContext ------------------------------------------------------------------

CHTLParser::VarDeclarationContext::VarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::VarDeclarationContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::VarDeclarationContext::COLON() {
  return getToken(CHTLParser::COLON, 0);
}

CHTLParser::StringLiteralContext* CHTLParser::VarDeclarationContext::stringLiteral() {
  return getRuleContext<CHTLParser::StringLiteralContext>(0);
}

tree::TerminalNode* CHTLParser::VarDeclarationContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}


size_t CHTLParser::VarDeclarationContext::getRuleIndex() const {
  return CHTLParser::RuleVarDeclaration;
}


std::any CHTLParser::VarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitVarDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::VarDeclarationContext* CHTLParser::varDeclaration() {
  VarDeclarationContext *_localctx = _tracker.createInstance<VarDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 62, CHTLParser::RuleVarDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(334);
    match(CHTLParser::IDENTIFIER);
    setState(335);
    match(CHTLParser::COLON);
    setState(336);
    stringLiteral();
    setState(337);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomDeclarationContext ------------------------------------------------------------------

CHTLParser::CustomDeclarationContext::CustomDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CustomDeclarationContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::CustomDeclarationContext::CUSTOM() {
  return getToken(CHTLParser::CUSTOM, 0);
}

tree::TerminalNode* CHTLParser::CustomDeclarationContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

CHTLParser::CustomTypeContext* CHTLParser::CustomDeclarationContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

CHTLParser::CustomNameContext* CHTLParser::CustomDeclarationContext::customName() {
  return getRuleContext<CHTLParser::CustomNameContext>(0);
}

CHTLParser::CustomBodyContext* CHTLParser::CustomDeclarationContext::customBody() {
  return getRuleContext<CHTLParser::CustomBodyContext>(0);
}


size_t CHTLParser::CustomDeclarationContext::getRuleIndex() const {
  return CHTLParser::RuleCustomDeclaration;
}


std::any CHTLParser::CustomDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCustomDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CustomDeclarationContext* CHTLParser::customDeclaration() {
  CustomDeclarationContext *_localctx = _tracker.createInstance<CustomDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 64, CHTLParser::RuleCustomDeclaration);
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
    match(CHTLParser::LBRACKET);
    setState(340);
    match(CHTLParser::CUSTOM);
    setState(341);
    match(CHTLParser::RBRACKET);
    setState(342);
    customType();
    setState(343);
    customName();
    setState(345);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACE) {
      setState(344);
      customBody();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomTypeContext ------------------------------------------------------------------

CHTLParser::CustomTypeContext::CustomTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CustomTypeContext::AT_STYLE() {
  return getToken(CHTLParser::AT_STYLE, 0);
}

tree::TerminalNode* CHTLParser::CustomTypeContext::AT_ELEMENT() {
  return getToken(CHTLParser::AT_ELEMENT, 0);
}

tree::TerminalNode* CHTLParser::CustomTypeContext::AT_VAR() {
  return getToken(CHTLParser::AT_VAR, 0);
}


size_t CHTLParser::CustomTypeContext::getRuleIndex() const {
  return CHTLParser::RuleCustomType;
}


std::any CHTLParser::CustomTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCustomType(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CustomTypeContext* CHTLParser::customType() {
  CustomTypeContext *_localctx = _tracker.createInstance<CustomTypeContext>(_ctx, getState());
  enterRule(_localctx, 66, CHTLParser::RuleCustomType);
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
    setState(347);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR))) != 0))) {
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

//----------------- CustomNameContext ------------------------------------------------------------------

CHTLParser::CustomNameContext::CustomNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CustomNameContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::CustomNameContext::getRuleIndex() const {
  return CHTLParser::RuleCustomName;
}


std::any CHTLParser::CustomNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCustomName(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CustomNameContext* CHTLParser::customName() {
  CustomNameContext *_localctx = _tracker.createInstance<CustomNameContext>(_ctx, getState());
  enterRule(_localctx, 68, CHTLParser::RuleCustomName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomBodyContext ------------------------------------------------------------------

CHTLParser::CustomBodyContext::CustomBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CustomBodyContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::CustomBodyContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::CustomContentContext *> CHTLParser::CustomBodyContext::customContent() {
  return getRuleContexts<CHTLParser::CustomContentContext>();
}

CHTLParser::CustomContentContext* CHTLParser::CustomBodyContext::customContent(size_t i) {
  return getRuleContext<CHTLParser::CustomContentContext>(i);
}


size_t CHTLParser::CustomBodyContext::getRuleIndex() const {
  return CHTLParser::RuleCustomBody;
}


std::any CHTLParser::CustomBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCustomBody(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CustomBodyContext* CHTLParser::customBody() {
  CustomBodyContext *_localctx = _tracker.createInstance<CustomBodyContext>(_ctx, getState());
  enterRule(_localctx, 70, CHTLParser::RuleCustomBody);
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
    setState(351);
    match(CHTLParser::LBRACE);
    setState(355);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR)
      | (1ULL << CHTLParser::INHERIT)
      | (1ULL << CHTLParser::DELETE)
      | (1ULL << CHTLParser::INSERT)
      | (1ULL << CHTLParser::LBRACKET)
      | (1ULL << CHTLParser::IDENTIFIER))) != 0)) {
      setState(352);
      customContent();
      setState(357);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(358);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomContentContext ------------------------------------------------------------------

CHTLParser::CustomContentContext::CustomContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CssPropertyContext* CHTLParser::CustomContentContext::cssProperty() {
  return getRuleContext<CHTLParser::CssPropertyContext>(0);
}

CHTLParser::CssPropertyWithoutValueContext* CHTLParser::CustomContentContext::cssPropertyWithoutValue() {
  return getRuleContext<CHTLParser::CssPropertyWithoutValueContext>(0);
}

CHTLParser::ElementContext* CHTLParser::CustomContentContext::element() {
  return getRuleContext<CHTLParser::ElementContext>(0);
}

CHTLParser::VarDeclarationContext* CHTLParser::CustomContentContext::varDeclaration() {
  return getRuleContext<CHTLParser::VarDeclarationContext>(0);
}

CHTLParser::TemplateUsageContext* CHTLParser::CustomContentContext::templateUsage() {
  return getRuleContext<CHTLParser::TemplateUsageContext>(0);
}

CHTLParser::CustomUsageContext* CHTLParser::CustomContentContext::customUsage() {
  return getRuleContext<CHTLParser::CustomUsageContext>(0);
}

CHTLParser::DeleteStatementContext* CHTLParser::CustomContentContext::deleteStatement() {
  return getRuleContext<CHTLParser::DeleteStatementContext>(0);
}

CHTLParser::InsertStatementContext* CHTLParser::CustomContentContext::insertStatement() {
  return getRuleContext<CHTLParser::InsertStatementContext>(0);
}

CHTLParser::InheritStatementContext* CHTLParser::CustomContentContext::inheritStatement() {
  return getRuleContext<CHTLParser::InheritStatementContext>(0);
}


size_t CHTLParser::CustomContentContext::getRuleIndex() const {
  return CHTLParser::RuleCustomContent;
}


std::any CHTLParser::CustomContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCustomContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CustomContentContext* CHTLParser::customContent() {
  CustomContentContext *_localctx = _tracker.createInstance<CustomContentContext>(_ctx, getState());
  enterRule(_localctx, 72, CHTLParser::RuleCustomContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(369);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(360);
      cssProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(361);
      cssPropertyWithoutValue();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(362);
      element();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(363);
      varDeclaration();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(364);
      templateUsage();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(365);
      customUsage();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(366);
      deleteStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(367);
      insertStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(368);
      inheritStatement();
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

//----------------- CssPropertyWithoutValueContext ------------------------------------------------------------------

CHTLParser::CssPropertyWithoutValueContext::CssPropertyWithoutValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::CssPropertyNameContext *> CHTLParser::CssPropertyWithoutValueContext::cssPropertyName() {
  return getRuleContexts<CHTLParser::CssPropertyNameContext>();
}

CHTLParser::CssPropertyNameContext* CHTLParser::CssPropertyWithoutValueContext::cssPropertyName(size_t i) {
  return getRuleContext<CHTLParser::CssPropertyNameContext>(i);
}

tree::TerminalNode* CHTLParser::CssPropertyWithoutValueContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> CHTLParser::CssPropertyWithoutValueContext::COMMA() {
  return getTokens(CHTLParser::COMMA);
}

tree::TerminalNode* CHTLParser::CssPropertyWithoutValueContext::COMMA(size_t i) {
  return getToken(CHTLParser::COMMA, i);
}


size_t CHTLParser::CssPropertyWithoutValueContext::getRuleIndex() const {
  return CHTLParser::RuleCssPropertyWithoutValue;
}


std::any CHTLParser::CssPropertyWithoutValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCssPropertyWithoutValue(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CssPropertyWithoutValueContext* CHTLParser::cssPropertyWithoutValue() {
  CssPropertyWithoutValueContext *_localctx = _tracker.createInstance<CssPropertyWithoutValueContext>(_ctx, getState());
  enterRule(_localctx, 74, CHTLParser::RuleCssPropertyWithoutValue);
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
    setState(371);
    cssPropertyName();
    setState(376);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::COMMA) {
      setState(372);
      match(CHTLParser::COMMA);
      setState(373);
      cssPropertyName();
      setState(378);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(379);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateUsageContext ------------------------------------------------------------------

CHTLParser::TemplateUsageContext::TemplateUsageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::TemplateTypeContext* CHTLParser::TemplateUsageContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

CHTLParser::TemplateNameContext* CHTLParser::TemplateUsageContext::templateName() {
  return getRuleContext<CHTLParser::TemplateNameContext>(0);
}

tree::TerminalNode* CHTLParser::TemplateUsageContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

CHTLParser::TemplateSpecializationContext* CHTLParser::TemplateUsageContext::templateSpecialization() {
  return getRuleContext<CHTLParser::TemplateSpecializationContext>(0);
}


size_t CHTLParser::TemplateUsageContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateUsage;
}


std::any CHTLParser::TemplateUsageContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitTemplateUsage(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::TemplateUsageContext* CHTLParser::templateUsage() {
  TemplateUsageContext *_localctx = _tracker.createInstance<TemplateUsageContext>(_ctx, getState());
  enterRule(_localctx, 76, CHTLParser::RuleTemplateUsage);
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
    setState(381);
    templateType();
    setState(382);
    templateName();
    setState(384);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACE) {
      setState(383);
      templateSpecialization();
    }
    setState(386);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateSpecializationContext ------------------------------------------------------------------

CHTLParser::TemplateSpecializationContext::TemplateSpecializationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TemplateSpecializationContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::TemplateSpecializationContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::SpecializationContentContext *> CHTLParser::TemplateSpecializationContext::specializationContent() {
  return getRuleContexts<CHTLParser::SpecializationContentContext>();
}

CHTLParser::SpecializationContentContext* CHTLParser::TemplateSpecializationContext::specializationContent(size_t i) {
  return getRuleContext<CHTLParser::SpecializationContentContext>(i);
}


size_t CHTLParser::TemplateSpecializationContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateSpecialization;
}


std::any CHTLParser::TemplateSpecializationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitTemplateSpecialization(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::TemplateSpecializationContext* CHTLParser::templateSpecialization() {
  TemplateSpecializationContext *_localctx = _tracker.createInstance<TemplateSpecializationContext>(_ctx, getState());
  enterRule(_localctx, 78, CHTLParser::RuleTemplateSpecialization);
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
    setState(388);
    match(CHTLParser::LBRACE);
    setState(392);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::DELETE

    || _la == CHTLParser::IDENTIFIER) {
      setState(389);
      specializationContent();
      setState(394);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(395);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SpecializationContentContext ------------------------------------------------------------------

CHTLParser::SpecializationContentContext::SpecializationContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CssPropertyContext* CHTLParser::SpecializationContentContext::cssProperty() {
  return getRuleContext<CHTLParser::CssPropertyContext>(0);
}

CHTLParser::DeleteStatementContext* CHTLParser::SpecializationContentContext::deleteStatement() {
  return getRuleContext<CHTLParser::DeleteStatementContext>(0);
}

CHTLParser::VarAssignmentContext* CHTLParser::SpecializationContentContext::varAssignment() {
  return getRuleContext<CHTLParser::VarAssignmentContext>(0);
}


size_t CHTLParser::SpecializationContentContext::getRuleIndex() const {
  return CHTLParser::RuleSpecializationContent;
}


std::any CHTLParser::SpecializationContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitSpecializationContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::SpecializationContentContext* CHTLParser::specializationContent() {
  SpecializationContentContext *_localctx = _tracker.createInstance<SpecializationContentContext>(_ctx, getState());
  enterRule(_localctx, 80, CHTLParser::RuleSpecializationContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(400);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(397);
      cssProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(398);
      deleteStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(399);
      varAssignment();
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

//----------------- VarAssignmentContext ------------------------------------------------------------------

CHTLParser::VarAssignmentContext::VarAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::VarAssignmentContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::VarAssignmentContext::EQUALS() {
  return getToken(CHTLParser::EQUALS, 0);
}

CHTLParser::StringLiteralContext* CHTLParser::VarAssignmentContext::stringLiteral() {
  return getRuleContext<CHTLParser::StringLiteralContext>(0);
}


size_t CHTLParser::VarAssignmentContext::getRuleIndex() const {
  return CHTLParser::RuleVarAssignment;
}


std::any CHTLParser::VarAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitVarAssignment(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::VarAssignmentContext* CHTLParser::varAssignment() {
  VarAssignmentContext *_localctx = _tracker.createInstance<VarAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 82, CHTLParser::RuleVarAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(402);
    match(CHTLParser::IDENTIFIER);
    setState(403);
    match(CHTLParser::EQUALS);
    setState(404);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomUsageContext ------------------------------------------------------------------

CHTLParser::CustomUsageContext::CustomUsageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CustomTypeContext* CHTLParser::CustomUsageContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

CHTLParser::CustomNameContext* CHTLParser::CustomUsageContext::customName() {
  return getRuleContext<CHTLParser::CustomNameContext>(0);
}

tree::TerminalNode* CHTLParser::CustomUsageContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::CustomUsageContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::CustomUsageContext::CUSTOM() {
  return getToken(CHTLParser::CUSTOM, 0);
}

tree::TerminalNode* CHTLParser::CustomUsageContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

CHTLParser::CustomSpecializationContext* CHTLParser::CustomUsageContext::customSpecialization() {
  return getRuleContext<CHTLParser::CustomSpecializationContext>(0);
}


size_t CHTLParser::CustomUsageContext::getRuleIndex() const {
  return CHTLParser::RuleCustomUsage;
}


std::any CHTLParser::CustomUsageContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCustomUsage(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CustomUsageContext* CHTLParser::customUsage() {
  CustomUsageContext *_localctx = _tracker.createInstance<CustomUsageContext>(_ctx, getState());
  enterRule(_localctx, 84, CHTLParser::RuleCustomUsage);
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
    setState(409);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACKET) {
      setState(406);
      match(CHTLParser::LBRACKET);
      setState(407);
      match(CHTLParser::CUSTOM);
      setState(408);
      match(CHTLParser::RBRACKET);
    }
    setState(411);
    customType();
    setState(412);
    customName();
    setState(414);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACE) {
      setState(413);
      customSpecialization();
    }
    setState(416);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomSpecializationContext ------------------------------------------------------------------

CHTLParser::CustomSpecializationContext::CustomSpecializationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CustomSpecializationContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::CustomSpecializationContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::SpecializationContentContext *> CHTLParser::CustomSpecializationContext::specializationContent() {
  return getRuleContexts<CHTLParser::SpecializationContentContext>();
}

CHTLParser::SpecializationContentContext* CHTLParser::CustomSpecializationContext::specializationContent(size_t i) {
  return getRuleContext<CHTLParser::SpecializationContentContext>(i);
}


size_t CHTLParser::CustomSpecializationContext::getRuleIndex() const {
  return CHTLParser::RuleCustomSpecialization;
}


std::any CHTLParser::CustomSpecializationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitCustomSpecialization(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::CustomSpecializationContext* CHTLParser::customSpecialization() {
  CustomSpecializationContext *_localctx = _tracker.createInstance<CustomSpecializationContext>(_ctx, getState());
  enterRule(_localctx, 86, CHTLParser::RuleCustomSpecialization);
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
    match(CHTLParser::LBRACE);
    setState(422);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::DELETE

    || _la == CHTLParser::IDENTIFIER) {
      setState(419);
      specializationContent();
      setState(424);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(425);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InheritStatementContext ------------------------------------------------------------------

CHTLParser::InheritStatementContext::InheritStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::InheritStatementContext::INHERIT() {
  return getToken(CHTLParser::INHERIT, 0);
}

CHTLParser::TemplateTypeContext* CHTLParser::InheritStatementContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

CHTLParser::TemplateNameContext* CHTLParser::InheritStatementContext::templateName() {
  return getRuleContext<CHTLParser::TemplateNameContext>(0);
}

tree::TerminalNode* CHTLParser::InheritStatementContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}


size_t CHTLParser::InheritStatementContext::getRuleIndex() const {
  return CHTLParser::RuleInheritStatement;
}


std::any CHTLParser::InheritStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitInheritStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::InheritStatementContext* CHTLParser::inheritStatement() {
  InheritStatementContext *_localctx = _tracker.createInstance<InheritStatementContext>(_ctx, getState());
  enterRule(_localctx, 88, CHTLParser::RuleInheritStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    match(CHTLParser::INHERIT);
    setState(428);
    templateType();
    setState(429);
    templateName();
    setState(430);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteStatementContext ------------------------------------------------------------------

CHTLParser::DeleteStatementContext::DeleteStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::DeleteStatementContext::DELETE() {
  return getToken(CHTLParser::DELETE, 0);
}

std::vector<CHTLParser::DeleteTargetContext *> CHTLParser::DeleteStatementContext::deleteTarget() {
  return getRuleContexts<CHTLParser::DeleteTargetContext>();
}

CHTLParser::DeleteTargetContext* CHTLParser::DeleteStatementContext::deleteTarget(size_t i) {
  return getRuleContext<CHTLParser::DeleteTargetContext>(i);
}

tree::TerminalNode* CHTLParser::DeleteStatementContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> CHTLParser::DeleteStatementContext::COMMA() {
  return getTokens(CHTLParser::COMMA);
}

tree::TerminalNode* CHTLParser::DeleteStatementContext::COMMA(size_t i) {
  return getToken(CHTLParser::COMMA, i);
}


size_t CHTLParser::DeleteStatementContext::getRuleIndex() const {
  return CHTLParser::RuleDeleteStatement;
}


std::any CHTLParser::DeleteStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitDeleteStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::DeleteStatementContext* CHTLParser::deleteStatement() {
  DeleteStatementContext *_localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
  enterRule(_localctx, 90, CHTLParser::RuleDeleteStatement);
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
    setState(432);
    match(CHTLParser::DELETE);
    setState(433);
    deleteTarget();
    setState(438);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::COMMA) {
      setState(434);
      match(CHTLParser::COMMA);
      setState(435);
      deleteTarget();
      setState(440);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(441);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteTargetContext ------------------------------------------------------------------

CHTLParser::DeleteTargetContext::DeleteTargetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CssPropertyNameContext* CHTLParser::DeleteTargetContext::cssPropertyName() {
  return getRuleContext<CHTLParser::CssPropertyNameContext>(0);
}

CHTLParser::ElementNameContext* CHTLParser::DeleteTargetContext::elementName() {
  return getRuleContext<CHTLParser::ElementNameContext>(0);
}

CHTLParser::ElementIndexContext* CHTLParser::DeleteTargetContext::elementIndex() {
  return getRuleContext<CHTLParser::ElementIndexContext>(0);
}

CHTLParser::TemplateTypeContext* CHTLParser::DeleteTargetContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

CHTLParser::TemplateNameContext* CHTLParser::DeleteTargetContext::templateName() {
  return getRuleContext<CHTLParser::TemplateNameContext>(0);
}

CHTLParser::CustomTypeContext* CHTLParser::DeleteTargetContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

CHTLParser::CustomNameContext* CHTLParser::DeleteTargetContext::customName() {
  return getRuleContext<CHTLParser::CustomNameContext>(0);
}


size_t CHTLParser::DeleteTargetContext::getRuleIndex() const {
  return CHTLParser::RuleDeleteTarget;
}


std::any CHTLParser::DeleteTargetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitDeleteTarget(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::DeleteTargetContext* CHTLParser::deleteTarget() {
  DeleteTargetContext *_localctx = _tracker.createInstance<DeleteTargetContext>(_ctx, getState());
  enterRule(_localctx, 92, CHTLParser::RuleDeleteTarget);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(454);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(443);
      cssPropertyName();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(444);
      elementName();
      setState(446);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::LBRACKET) {
        setState(445);
        elementIndex();
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(448);
      templateType();
      setState(449);
      templateName();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(451);
      customType();
      setState(452);
      customName();
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

//----------------- ElementIndexContext ------------------------------------------------------------------

CHTLParser::ElementIndexContext::ElementIndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ElementIndexContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::ElementIndexContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}

tree::TerminalNode* CHTLParser::ElementIndexContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}


size_t CHTLParser::ElementIndexContext::getRuleIndex() const {
  return CHTLParser::RuleElementIndex;
}


std::any CHTLParser::ElementIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitElementIndex(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ElementIndexContext* CHTLParser::elementIndex() {
  ElementIndexContext *_localctx = _tracker.createInstance<ElementIndexContext>(_ctx, getState());
  enterRule(_localctx, 94, CHTLParser::RuleElementIndex);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(456);
    match(CHTLParser::LBRACKET);
    setState(457);
    match(CHTLParser::NUMBER);
    setState(458);
    match(CHTLParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertStatementContext ------------------------------------------------------------------

CHTLParser::InsertStatementContext::InsertStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::InsertStatementContext::INSERT() {
  return getToken(CHTLParser::INSERT, 0);
}

CHTLParser::InsertPositionContext* CHTLParser::InsertStatementContext::insertPosition() {
  return getRuleContext<CHTLParser::InsertPositionContext>(0);
}

CHTLParser::InsertTargetContext* CHTLParser::InsertStatementContext::insertTarget() {
  return getRuleContext<CHTLParser::InsertTargetContext>(0);
}

tree::TerminalNode* CHTLParser::InsertStatementContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::InsertStatementContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::InsertContentContext *> CHTLParser::InsertStatementContext::insertContent() {
  return getRuleContexts<CHTLParser::InsertContentContext>();
}

CHTLParser::InsertContentContext* CHTLParser::InsertStatementContext::insertContent(size_t i) {
  return getRuleContext<CHTLParser::InsertContentContext>(i);
}


size_t CHTLParser::InsertStatementContext::getRuleIndex() const {
  return CHTLParser::RuleInsertStatement;
}


std::any CHTLParser::InsertStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitInsertStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::InsertStatementContext* CHTLParser::insertStatement() {
  InsertStatementContext *_localctx = _tracker.createInstance<InsertStatementContext>(_ctx, getState());
  enterRule(_localctx, 96, CHTLParser::RuleInsertStatement);
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
    setState(460);
    match(CHTLParser::INSERT);
    setState(461);
    insertPosition();
    setState(462);
    insertTarget();
    setState(463);
    match(CHTLParser::LBRACE);
    setState(467);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR)
      | (1ULL << CHTLParser::IDENTIFIER))) != 0)) {
      setState(464);
      insertContent();
      setState(469);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(470);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertPositionContext ------------------------------------------------------------------

CHTLParser::InsertPositionContext::InsertPositionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::InsertPositionContext::AFTER() {
  return getToken(CHTLParser::AFTER, 0);
}

tree::TerminalNode* CHTLParser::InsertPositionContext::BEFORE() {
  return getToken(CHTLParser::BEFORE, 0);
}

tree::TerminalNode* CHTLParser::InsertPositionContext::REPLACE() {
  return getToken(CHTLParser::REPLACE, 0);
}

tree::TerminalNode* CHTLParser::InsertPositionContext::AT() {
  return getToken(CHTLParser::AT, 0);
}

tree::TerminalNode* CHTLParser::InsertPositionContext::TOP() {
  return getToken(CHTLParser::TOP, 0);
}

tree::TerminalNode* CHTLParser::InsertPositionContext::BOTTOM() {
  return getToken(CHTLParser::BOTTOM, 0);
}


size_t CHTLParser::InsertPositionContext::getRuleIndex() const {
  return CHTLParser::RuleInsertPosition;
}


std::any CHTLParser::InsertPositionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitInsertPosition(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::InsertPositionContext* CHTLParser::insertPosition() {
  InsertPositionContext *_localctx = _tracker.createInstance<InsertPositionContext>(_ctx, getState());
  enterRule(_localctx, 98, CHTLParser::RuleInsertPosition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(479);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(472);
      match(CHTLParser::AFTER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(473);
      match(CHTLParser::BEFORE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(474);
      match(CHTLParser::REPLACE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(475);
      match(CHTLParser::AT);
      setState(476);
      match(CHTLParser::TOP);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(477);
      match(CHTLParser::AT);
      setState(478);
      match(CHTLParser::BOTTOM);
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

//----------------- InsertTargetContext ------------------------------------------------------------------

CHTLParser::InsertTargetContext::InsertTargetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ElementNameContext* CHTLParser::InsertTargetContext::elementName() {
  return getRuleContext<CHTLParser::ElementNameContext>(0);
}

CHTLParser::ElementIndexContext* CHTLParser::InsertTargetContext::elementIndex() {
  return getRuleContext<CHTLParser::ElementIndexContext>(0);
}


size_t CHTLParser::InsertTargetContext::getRuleIndex() const {
  return CHTLParser::RuleInsertTarget;
}


std::any CHTLParser::InsertTargetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitInsertTarget(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::InsertTargetContext* CHTLParser::insertTarget() {
  InsertTargetContext *_localctx = _tracker.createInstance<InsertTargetContext>(_ctx, getState());
  enterRule(_localctx, 100, CHTLParser::RuleInsertTarget);
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
    elementName();
    setState(483);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACKET) {
      setState(482);
      elementIndex();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertContentContext ------------------------------------------------------------------

CHTLParser::InsertContentContext::InsertContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ElementContext* CHTLParser::InsertContentContext::element() {
  return getRuleContext<CHTLParser::ElementContext>(0);
}

CHTLParser::TemplateUsageContext* CHTLParser::InsertContentContext::templateUsage() {
  return getRuleContext<CHTLParser::TemplateUsageContext>(0);
}


size_t CHTLParser::InsertContentContext::getRuleIndex() const {
  return CHTLParser::RuleInsertContent;
}


std::any CHTLParser::InsertContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitInsertContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::InsertContentContext* CHTLParser::insertContent() {
  InsertContentContext *_localctx = _tracker.createInstance<InsertContentContext>(_ctx, getState());
  enterRule(_localctx, 102, CHTLParser::RuleInsertContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(487);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(485);
        element();
        break;
      }

      case CHTLParser::AT_STYLE:
      case CHTLParser::AT_ELEMENT:
      case CHTLParser::AT_VAR: {
        enterOuterAlt(_localctx, 2);
        setState(486);
        templateUsage();
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

//----------------- ExceptStatementContext ------------------------------------------------------------------

CHTLParser::ExceptStatementContext::ExceptStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ExceptStatementContext::EXCEPT() {
  return getToken(CHTLParser::EXCEPT, 0);
}

std::vector<CHTLParser::ExceptTargetContext *> CHTLParser::ExceptStatementContext::exceptTarget() {
  return getRuleContexts<CHTLParser::ExceptTargetContext>();
}

CHTLParser::ExceptTargetContext* CHTLParser::ExceptStatementContext::exceptTarget(size_t i) {
  return getRuleContext<CHTLParser::ExceptTargetContext>(i);
}

tree::TerminalNode* CHTLParser::ExceptStatementContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> CHTLParser::ExceptStatementContext::COMMA() {
  return getTokens(CHTLParser::COMMA);
}

tree::TerminalNode* CHTLParser::ExceptStatementContext::COMMA(size_t i) {
  return getToken(CHTLParser::COMMA, i);
}


size_t CHTLParser::ExceptStatementContext::getRuleIndex() const {
  return CHTLParser::RuleExceptStatement;
}


std::any CHTLParser::ExceptStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitExceptStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ExceptStatementContext* CHTLParser::exceptStatement() {
  ExceptStatementContext *_localctx = _tracker.createInstance<ExceptStatementContext>(_ctx, getState());
  enterRule(_localctx, 104, CHTLParser::RuleExceptStatement);
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
    setState(489);
    match(CHTLParser::EXCEPT);
    setState(490);
    exceptTarget();
    setState(495);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::COMMA) {
      setState(491);
      match(CHTLParser::COMMA);
      setState(492);
      exceptTarget();
      setState(497);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(498);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExceptTargetContext ------------------------------------------------------------------

CHTLParser::ExceptTargetContext::ExceptTargetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ElementNameContext* CHTLParser::ExceptTargetContext::elementName() {
  return getRuleContext<CHTLParser::ElementNameContext>(0);
}

CHTLParser::TemplateTypeContext* CHTLParser::ExceptTargetContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

CHTLParser::TemplateNameContext* CHTLParser::ExceptTargetContext::templateName() {
  return getRuleContext<CHTLParser::TemplateNameContext>(0);
}

CHTLParser::CustomTypeContext* CHTLParser::ExceptTargetContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

CHTLParser::CustomNameContext* CHTLParser::ExceptTargetContext::customName() {
  return getRuleContext<CHTLParser::CustomNameContext>(0);
}

tree::TerminalNode* CHTLParser::ExceptTargetContext::AT_HTML() {
  return getToken(CHTLParser::AT_HTML, 0);
}

tree::TerminalNode* CHTLParser::ExceptTargetContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::ExceptTargetContext::CUSTOM() {
  return getToken(CHTLParser::CUSTOM, 0);
}

tree::TerminalNode* CHTLParser::ExceptTargetContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

tree::TerminalNode* CHTLParser::ExceptTargetContext::TEMPLATE() {
  return getToken(CHTLParser::TEMPLATE, 0);
}


size_t CHTLParser::ExceptTargetContext::getRuleIndex() const {
  return CHTLParser::RuleExceptTarget;
}


std::any CHTLParser::ExceptTargetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitExceptTarget(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ExceptTargetContext* CHTLParser::exceptTarget() {
  ExceptTargetContext *_localctx = _tracker.createInstance<ExceptTargetContext>(_ctx, getState());
  enterRule(_localctx, 106, CHTLParser::RuleExceptTarget);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(516);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(500);
      elementName();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(501);
      templateType();
      setState(503);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::IDENTIFIER) {
        setState(502);
        templateName();
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(505);
      customType();
      setState(507);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::IDENTIFIER) {
        setState(506);
        customName();
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(509);
      match(CHTLParser::AT_HTML);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(510);
      match(CHTLParser::LBRACKET);
      setState(511);
      match(CHTLParser::CUSTOM);
      setState(512);
      match(CHTLParser::RBRACKET);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(513);
      match(CHTLParser::LBRACKET);
      setState(514);
      match(CHTLParser::TEMPLATE);
      setState(515);
      match(CHTLParser::RBRACKET);
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

//----------------- OriginBlockContext ------------------------------------------------------------------

CHTLParser::OriginBlockContext::OriginBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::OriginBlockContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::OriginBlockContext::ORIGIN() {
  return getToken(CHTLParser::ORIGIN, 0);
}

tree::TerminalNode* CHTLParser::OriginBlockContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

CHTLParser::OriginTypeContext* CHTLParser::OriginBlockContext::originType() {
  return getRuleContext<CHTLParser::OriginTypeContext>(0);
}

CHTLParser::OriginBodyContext* CHTLParser::OriginBlockContext::originBody() {
  return getRuleContext<CHTLParser::OriginBodyContext>(0);
}

CHTLParser::OriginNameContext* CHTLParser::OriginBlockContext::originName() {
  return getRuleContext<CHTLParser::OriginNameContext>(0);
}


size_t CHTLParser::OriginBlockContext::getRuleIndex() const {
  return CHTLParser::RuleOriginBlock;
}


std::any CHTLParser::OriginBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitOriginBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::OriginBlockContext* CHTLParser::originBlock() {
  OriginBlockContext *_localctx = _tracker.createInstance<OriginBlockContext>(_ctx, getState());
  enterRule(_localctx, 108, CHTLParser::RuleOriginBlock);
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
    setState(518);
    match(CHTLParser::LBRACKET);
    setState(519);
    match(CHTLParser::ORIGIN);
    setState(520);
    match(CHTLParser::RBRACKET);
    setState(521);
    originType();
    setState(523);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::IDENTIFIER) {
      setState(522);
      originName();
    }
    setState(525);
    originBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OriginTypeContext ------------------------------------------------------------------

CHTLParser::OriginTypeContext::OriginTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::OriginTypeContext::AT_HTML() {
  return getToken(CHTLParser::AT_HTML, 0);
}

tree::TerminalNode* CHTLParser::OriginTypeContext::AT_STYLE() {
  return getToken(CHTLParser::AT_STYLE, 0);
}

tree::TerminalNode* CHTLParser::OriginTypeContext::AT_JAVASCRIPT() {
  return getToken(CHTLParser::AT_JAVASCRIPT, 0);
}


size_t CHTLParser::OriginTypeContext::getRuleIndex() const {
  return CHTLParser::RuleOriginType;
}


std::any CHTLParser::OriginTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitOriginType(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::OriginTypeContext* CHTLParser::originType() {
  OriginTypeContext *_localctx = _tracker.createInstance<OriginTypeContext>(_ctx, getState());
  enterRule(_localctx, 110, CHTLParser::RuleOriginType);
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
    setState(527);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_HTML)
      | (1ULL << CHTLParser::AT_JAVASCRIPT))) != 0))) {
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

//----------------- OriginNameContext ------------------------------------------------------------------

CHTLParser::OriginNameContext::OriginNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::OriginNameContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::OriginNameContext::getRuleIndex() const {
  return CHTLParser::RuleOriginName;
}


std::any CHTLParser::OriginNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitOriginName(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::OriginNameContext* CHTLParser::originName() {
  OriginNameContext *_localctx = _tracker.createInstance<OriginNameContext>(_ctx, getState());
  enterRule(_localctx, 112, CHTLParser::RuleOriginName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(529);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OriginBodyContext ------------------------------------------------------------------

CHTLParser::OriginBodyContext::OriginBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::OriginBodyContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::RawContentContext* CHTLParser::OriginBodyContext::rawContent() {
  return getRuleContext<CHTLParser::RawContentContext>(0);
}

tree::TerminalNode* CHTLParser::OriginBodyContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::OriginBodyContext::getRuleIndex() const {
  return CHTLParser::RuleOriginBody;
}


std::any CHTLParser::OriginBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitOriginBody(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::OriginBodyContext* CHTLParser::originBody() {
  OriginBodyContext *_localctx = _tracker.createInstance<OriginBodyContext>(_ctx, getState());
  enterRule(_localctx, 114, CHTLParser::RuleOriginBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(531);
    match(CHTLParser::LBRACE);
    setState(532);
    rawContent();
    setState(533);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RawContentContext ------------------------------------------------------------------

CHTLParser::RawContentContext::RawContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::RawContentContext::RBRACE() {
  return getTokens(CHTLParser::RBRACE);
}

tree::TerminalNode* CHTLParser::RawContentContext::RBRACE(size_t i) {
  return getToken(CHTLParser::RBRACE, i);
}


size_t CHTLParser::RawContentContext::getRuleIndex() const {
  return CHTLParser::RuleRawContent;
}


std::any CHTLParser::RawContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitRawContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::RawContentContext* CHTLParser::rawContent() {
  RawContentContext *_localctx = _tracker.createInstance<RawContentContext>(_ctx, getState());
  enterRule(_localctx, 116, CHTLParser::RuleRawContent);
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
    setState(538);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::TEXT)
      | (1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::TEMPLATE)
      | (1ULL << CHTLParser::CUSTOM)
      | (1ULL << CHTLParser::ORIGIN)
      | (1ULL << CHTLParser::IMPORT)
      | (1ULL << CHTLParser::NAMESPACE)
      | (1ULL << CHTLParser::CONFIGURATION)
      | (1ULL << CHTLParser::NAME)
      | (1ULL << CHTLParser::INFO)
      | (1ULL << CHTLParser::EXPORT)
      | (1ULL << CHTLParser::AT_STYLE)
      | (1ULL << CHTLParser::AT_ELEMENT)
      | (1ULL << CHTLParser::AT_VAR)
      | (1ULL << CHTLParser::AT_HTML)
      | (1ULL << CHTLParser::AT_JAVASCRIPT)
      | (1ULL << CHTLParser::AT_CHTL)
      | (1ULL << CHTLParser::INHERIT)
      | (1ULL << CHTLParser::DELETE)
      | (1ULL << CHTLParser::INSERT)
      | (1ULL << CHTLParser::AFTER)
      | (1ULL << CHTLParser::BEFORE)
      | (1ULL << CHTLParser::REPLACE)
      | (1ULL << CHTLParser::AT)
      | (1ULL << CHTLParser::TOP)
      | (1ULL << CHTLParser::BOTTOM)
      | (1ULL << CHTLParser::FROM)
      | (1ULL << CHTLParser::AS)
      | (1ULL << CHTLParser::EXCEPT)
      | (1ULL << CHTLParser::BOOLEAN)
      | (1ULL << CHTLParser::COLON)
      | (1ULL << CHTLParser::SEMICOLON)
      | (1ULL << CHTLParser::EQUALS)
      | (1ULL << CHTLParser::COMMA)
      | (1ULL << CHTLParser::DOT)
      | (1ULL << CHTLParser::HASH)
      | (1ULL << CHTLParser::AMPERSAND)
      | (1ULL << CHTLParser::MINUS)
      | (1ULL << CHTLParser::LBRACE)
      | (1ULL << CHTLParser::LBRACKET)
      | (1ULL << CHTLParser::RBRACKET)
      | (1ULL << CHTLParser::LPAREN)
      | (1ULL << CHTLParser::RPAREN)
      | (1ULL << CHTLParser::LINE_COMMENT)
      | (1ULL << CHTLParser::BLOCK_COMMENT)
      | (1ULL << CHTLParser::GENERATOR_COMMENT)
      | (1ULL << CHTLParser::STRING_LITERAL)
      | (1ULL << CHTLParser::SINGLE_STRING_LITERAL)
      | (1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::UNQUOTED_LITERAL)
      | (1ULL << CHTLParser::WS))) != 0)) {
      setState(535);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == CHTLParser::RBRACE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(540);
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

//----------------- ImportStatementContext ------------------------------------------------------------------

CHTLParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportStatementContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::ImportStatementContext::IMPORT() {
  return getToken(CHTLParser::IMPORT, 0);
}

tree::TerminalNode* CHTLParser::ImportStatementContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

CHTLParser::ImportContentContext* CHTLParser::ImportStatementContext::importContent() {
  return getRuleContext<CHTLParser::ImportContentContext>(0);
}


size_t CHTLParser::ImportStatementContext::getRuleIndex() const {
  return CHTLParser::RuleImportStatement;
}


std::any CHTLParser::ImportStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitImportStatement(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ImportStatementContext* CHTLParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 118, CHTLParser::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(541);
    match(CHTLParser::LBRACKET);
    setState(542);
    match(CHTLParser::IMPORT);
    setState(543);
    match(CHTLParser::RBRACKET);
    setState(544);
    importContent();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportContentContext ------------------------------------------------------------------

CHTLParser::ImportContentContext::ImportContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ImportHtmlContext* CHTLParser::ImportContentContext::importHtml() {
  return getRuleContext<CHTLParser::ImportHtmlContext>(0);
}

CHTLParser::ImportCssContext* CHTLParser::ImportContentContext::importCss() {
  return getRuleContext<CHTLParser::ImportCssContext>(0);
}

CHTLParser::ImportJsContext* CHTLParser::ImportContentContext::importJs() {
  return getRuleContext<CHTLParser::ImportJsContext>(0);
}

CHTLParser::ImportChtlContext* CHTLParser::ImportContentContext::importChtl() {
  return getRuleContext<CHTLParser::ImportChtlContext>(0);
}

CHTLParser::ImportCustomContext* CHTLParser::ImportContentContext::importCustom() {
  return getRuleContext<CHTLParser::ImportCustomContext>(0);
}

CHTLParser::ImportTemplateContext* CHTLParser::ImportContentContext::importTemplate() {
  return getRuleContext<CHTLParser::ImportTemplateContext>(0);
}


size_t CHTLParser::ImportContentContext::getRuleIndex() const {
  return CHTLParser::RuleImportContent;
}


std::any CHTLParser::ImportContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitImportContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ImportContentContext* CHTLParser::importContent() {
  ImportContentContext *_localctx = _tracker.createInstance<ImportContentContext>(_ctx, getState());
  enterRule(_localctx, 120, CHTLParser::RuleImportContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(552);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(546);
      importHtml();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(547);
      importCss();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(548);
      importJs();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(549);
      importChtl();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(550);
      importCustom();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(551);
      importTemplate();
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

//----------------- ImportHtmlContext ------------------------------------------------------------------

CHTLParser::ImportHtmlContext::ImportHtmlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportHtmlContext::AT_HTML() {
  return getToken(CHTLParser::AT_HTML, 0);
}

tree::TerminalNode* CHTLParser::ImportHtmlContext::FROM() {
  return getToken(CHTLParser::FROM, 0);
}

CHTLParser::FilePathContext* CHTLParser::ImportHtmlContext::filePath() {
  return getRuleContext<CHTLParser::FilePathContext>(0);
}

tree::TerminalNode* CHTLParser::ImportHtmlContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::ImportHtmlContext::AS() {
  return getToken(CHTLParser::AS, 0);
}

tree::TerminalNode* CHTLParser::ImportHtmlContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ImportHtmlContext::getRuleIndex() const {
  return CHTLParser::RuleImportHtml;
}


std::any CHTLParser::ImportHtmlContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitImportHtml(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ImportHtmlContext* CHTLParser::importHtml() {
  ImportHtmlContext *_localctx = _tracker.createInstance<ImportHtmlContext>(_ctx, getState());
  enterRule(_localctx, 122, CHTLParser::RuleImportHtml);
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
    match(CHTLParser::AT_HTML);
    setState(555);
    match(CHTLParser::FROM);
    setState(556);
    filePath();
    setState(559);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::AS) {
      setState(557);
      match(CHTLParser::AS);
      setState(558);
      match(CHTLParser::IDENTIFIER);
    }
    setState(561);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportCssContext ------------------------------------------------------------------

CHTLParser::ImportCssContext::ImportCssContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportCssContext::AT_STYLE() {
  return getToken(CHTLParser::AT_STYLE, 0);
}

tree::TerminalNode* CHTLParser::ImportCssContext::FROM() {
  return getToken(CHTLParser::FROM, 0);
}

CHTLParser::FilePathContext* CHTLParser::ImportCssContext::filePath() {
  return getRuleContext<CHTLParser::FilePathContext>(0);
}

tree::TerminalNode* CHTLParser::ImportCssContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::ImportCssContext::AS() {
  return getToken(CHTLParser::AS, 0);
}

tree::TerminalNode* CHTLParser::ImportCssContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ImportCssContext::getRuleIndex() const {
  return CHTLParser::RuleImportCss;
}


std::any CHTLParser::ImportCssContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitImportCss(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ImportCssContext* CHTLParser::importCss() {
  ImportCssContext *_localctx = _tracker.createInstance<ImportCssContext>(_ctx, getState());
  enterRule(_localctx, 124, CHTLParser::RuleImportCss);
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
    setState(563);
    match(CHTLParser::AT_STYLE);
    setState(564);
    match(CHTLParser::FROM);
    setState(565);
    filePath();
    setState(568);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::AS) {
      setState(566);
      match(CHTLParser::AS);
      setState(567);
      match(CHTLParser::IDENTIFIER);
    }
    setState(570);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportJsContext ------------------------------------------------------------------

CHTLParser::ImportJsContext::ImportJsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportJsContext::AT_JAVASCRIPT() {
  return getToken(CHTLParser::AT_JAVASCRIPT, 0);
}

tree::TerminalNode* CHTLParser::ImportJsContext::FROM() {
  return getToken(CHTLParser::FROM, 0);
}

CHTLParser::FilePathContext* CHTLParser::ImportJsContext::filePath() {
  return getRuleContext<CHTLParser::FilePathContext>(0);
}

tree::TerminalNode* CHTLParser::ImportJsContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::ImportJsContext::AS() {
  return getToken(CHTLParser::AS, 0);
}

tree::TerminalNode* CHTLParser::ImportJsContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ImportJsContext::getRuleIndex() const {
  return CHTLParser::RuleImportJs;
}


std::any CHTLParser::ImportJsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitImportJs(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ImportJsContext* CHTLParser::importJs() {
  ImportJsContext *_localctx = _tracker.createInstance<ImportJsContext>(_ctx, getState());
  enterRule(_localctx, 126, CHTLParser::RuleImportJs);
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
    match(CHTLParser::AT_JAVASCRIPT);
    setState(573);
    match(CHTLParser::FROM);
    setState(574);
    filePath();
    setState(577);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::AS) {
      setState(575);
      match(CHTLParser::AS);
      setState(576);
      match(CHTLParser::IDENTIFIER);
    }
    setState(579);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportChtlContext ------------------------------------------------------------------

CHTLParser::ImportChtlContext::ImportChtlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportChtlContext::AT_CHTL() {
  return getToken(CHTLParser::AT_CHTL, 0);
}

tree::TerminalNode* CHTLParser::ImportChtlContext::FROM() {
  return getToken(CHTLParser::FROM, 0);
}

CHTLParser::FilePathContext* CHTLParser::ImportChtlContext::filePath() {
  return getRuleContext<CHTLParser::FilePathContext>(0);
}

tree::TerminalNode* CHTLParser::ImportChtlContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}


size_t CHTLParser::ImportChtlContext::getRuleIndex() const {
  return CHTLParser::RuleImportChtl;
}


std::any CHTLParser::ImportChtlContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitImportChtl(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ImportChtlContext* CHTLParser::importChtl() {
  ImportChtlContext *_localctx = _tracker.createInstance<ImportChtlContext>(_ctx, getState());
  enterRule(_localctx, 128, CHTLParser::RuleImportChtl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(581);
    match(CHTLParser::AT_CHTL);
    setState(582);
    match(CHTLParser::FROM);
    setState(583);
    filePath();
    setState(584);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportCustomContext ------------------------------------------------------------------

CHTLParser::ImportCustomContext::ImportCustomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportCustomContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::ImportCustomContext::CUSTOM() {
  return getToken(CHTLParser::CUSTOM, 0);
}

tree::TerminalNode* CHTLParser::ImportCustomContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

CHTLParser::CustomTypeContext* CHTLParser::ImportCustomContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

CHTLParser::CustomNameContext* CHTLParser::ImportCustomContext::customName() {
  return getRuleContext<CHTLParser::CustomNameContext>(0);
}

tree::TerminalNode* CHTLParser::ImportCustomContext::FROM() {
  return getToken(CHTLParser::FROM, 0);
}

CHTLParser::FilePathContext* CHTLParser::ImportCustomContext::filePath() {
  return getRuleContext<CHTLParser::FilePathContext>(0);
}

tree::TerminalNode* CHTLParser::ImportCustomContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::ImportCustomContext::AS() {
  return getToken(CHTLParser::AS, 0);
}

tree::TerminalNode* CHTLParser::ImportCustomContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ImportCustomContext::getRuleIndex() const {
  return CHTLParser::RuleImportCustom;
}


std::any CHTLParser::ImportCustomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitImportCustom(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ImportCustomContext* CHTLParser::importCustom() {
  ImportCustomContext *_localctx = _tracker.createInstance<ImportCustomContext>(_ctx, getState());
  enterRule(_localctx, 130, CHTLParser::RuleImportCustom);
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
    setState(586);
    match(CHTLParser::LBRACKET);
    setState(587);
    match(CHTLParser::CUSTOM);
    setState(588);
    match(CHTLParser::RBRACKET);
    setState(589);
    customType();
    setState(590);
    customName();
    setState(591);
    match(CHTLParser::FROM);
    setState(592);
    filePath();
    setState(595);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::AS) {
      setState(593);
      match(CHTLParser::AS);
      setState(594);
      match(CHTLParser::IDENTIFIER);
    }
    setState(597);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportTemplateContext ------------------------------------------------------------------

CHTLParser::ImportTemplateContext::ImportTemplateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportTemplateContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::ImportTemplateContext::TEMPLATE() {
  return getToken(CHTLParser::TEMPLATE, 0);
}

tree::TerminalNode* CHTLParser::ImportTemplateContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

CHTLParser::TemplateTypeContext* CHTLParser::ImportTemplateContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

CHTLParser::TemplateNameContext* CHTLParser::ImportTemplateContext::templateName() {
  return getRuleContext<CHTLParser::TemplateNameContext>(0);
}

tree::TerminalNode* CHTLParser::ImportTemplateContext::FROM() {
  return getToken(CHTLParser::FROM, 0);
}

CHTLParser::FilePathContext* CHTLParser::ImportTemplateContext::filePath() {
  return getRuleContext<CHTLParser::FilePathContext>(0);
}

tree::TerminalNode* CHTLParser::ImportTemplateContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::ImportTemplateContext::AS() {
  return getToken(CHTLParser::AS, 0);
}

tree::TerminalNode* CHTLParser::ImportTemplateContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ImportTemplateContext::getRuleIndex() const {
  return CHTLParser::RuleImportTemplate;
}


std::any CHTLParser::ImportTemplateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitImportTemplate(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ImportTemplateContext* CHTLParser::importTemplate() {
  ImportTemplateContext *_localctx = _tracker.createInstance<ImportTemplateContext>(_ctx, getState());
  enterRule(_localctx, 132, CHTLParser::RuleImportTemplate);
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
    setState(599);
    match(CHTLParser::LBRACKET);
    setState(600);
    match(CHTLParser::TEMPLATE);
    setState(601);
    match(CHTLParser::RBRACKET);
    setState(602);
    templateType();
    setState(603);
    templateName();
    setState(604);
    match(CHTLParser::FROM);
    setState(605);
    filePath();
    setState(608);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::AS) {
      setState(606);
      match(CHTLParser::AS);
      setState(607);
      match(CHTLParser::IDENTIFIER);
    }
    setState(610);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FilePathContext ------------------------------------------------------------------

CHTLParser::FilePathContext::FilePathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::StringLiteralContext* CHTLParser::FilePathContext::stringLiteral() {
  return getRuleContext<CHTLParser::StringLiteralContext>(0);
}


size_t CHTLParser::FilePathContext::getRuleIndex() const {
  return CHTLParser::RuleFilePath;
}


std::any CHTLParser::FilePathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitFilePath(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::FilePathContext* CHTLParser::filePath() {
  FilePathContext *_localctx = _tracker.createInstance<FilePathContext>(_ctx, getState());
  enterRule(_localctx, 134, CHTLParser::RuleFilePath);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(612);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamespaceDeclarationContext ------------------------------------------------------------------

CHTLParser::NamespaceDeclarationContext::NamespaceDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::NamespaceDeclarationContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::NamespaceDeclarationContext::NAMESPACE() {
  return getToken(CHTLParser::NAMESPACE, 0);
}

tree::TerminalNode* CHTLParser::NamespaceDeclarationContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

CHTLParser::NamespaceNameContext* CHTLParser::NamespaceDeclarationContext::namespaceName() {
  return getRuleContext<CHTLParser::NamespaceNameContext>(0);
}

CHTLParser::NamespaceBodyContext* CHTLParser::NamespaceDeclarationContext::namespaceBody() {
  return getRuleContext<CHTLParser::NamespaceBodyContext>(0);
}

tree::TerminalNode* CHTLParser::NamespaceDeclarationContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::NamespaceDeclarationContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::NamespaceContentContext *> CHTLParser::NamespaceDeclarationContext::namespaceContent() {
  return getRuleContexts<CHTLParser::NamespaceContentContext>();
}

CHTLParser::NamespaceContentContext* CHTLParser::NamespaceDeclarationContext::namespaceContent(size_t i) {
  return getRuleContext<CHTLParser::NamespaceContentContext>(i);
}


size_t CHTLParser::NamespaceDeclarationContext::getRuleIndex() const {
  return CHTLParser::RuleNamespaceDeclaration;
}


std::any CHTLParser::NamespaceDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitNamespaceDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::NamespaceDeclarationContext* CHTLParser::namespaceDeclaration() {
  NamespaceDeclarationContext *_localctx = _tracker.createInstance<NamespaceDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 136, CHTLParser::RuleNamespaceDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(634);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(614);
      match(CHTLParser::LBRACKET);
      setState(615);
      match(CHTLParser::NAMESPACE);
      setState(616);
      match(CHTLParser::RBRACKET);
      setState(617);
      namespaceName();
      setState(619);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::LBRACE) {
        setState(618);
        namespaceBody();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(621);
      match(CHTLParser::LBRACKET);
      setState(622);
      match(CHTLParser::NAMESPACE);
      setState(623);
      match(CHTLParser::RBRACKET);
      setState(624);
      namespaceName();
      setState(625);
      match(CHTLParser::LBRACE);
      setState(629);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CHTLParser::EXCEPT

      || _la == CHTLParser::LBRACKET) {
        setState(626);
        namespaceContent();
        setState(631);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(632);
      match(CHTLParser::RBRACE);
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

//----------------- NamespaceNameContext ------------------------------------------------------------------

CHTLParser::NamespaceNameContext::NamespaceNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::NamespaceNameContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::NamespaceNameContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> CHTLParser::NamespaceNameContext::DOT() {
  return getTokens(CHTLParser::DOT);
}

tree::TerminalNode* CHTLParser::NamespaceNameContext::DOT(size_t i) {
  return getToken(CHTLParser::DOT, i);
}


size_t CHTLParser::NamespaceNameContext::getRuleIndex() const {
  return CHTLParser::RuleNamespaceName;
}


std::any CHTLParser::NamespaceNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitNamespaceName(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::NamespaceNameContext* CHTLParser::namespaceName() {
  NamespaceNameContext *_localctx = _tracker.createInstance<NamespaceNameContext>(_ctx, getState());
  enterRule(_localctx, 138, CHTLParser::RuleNamespaceName);
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
    match(CHTLParser::IDENTIFIER);
    setState(641);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::DOT) {
      setState(637);
      match(CHTLParser::DOT);
      setState(638);
      match(CHTLParser::IDENTIFIER);
      setState(643);
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

//----------------- NamespaceBodyContext ------------------------------------------------------------------

CHTLParser::NamespaceBodyContext::NamespaceBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::NamespaceBodyContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::NamespaceBodyContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::NamespaceContentContext *> CHTLParser::NamespaceBodyContext::namespaceContent() {
  return getRuleContexts<CHTLParser::NamespaceContentContext>();
}

CHTLParser::NamespaceContentContext* CHTLParser::NamespaceBodyContext::namespaceContent(size_t i) {
  return getRuleContext<CHTLParser::NamespaceContentContext>(i);
}


size_t CHTLParser::NamespaceBodyContext::getRuleIndex() const {
  return CHTLParser::RuleNamespaceBody;
}


std::any CHTLParser::NamespaceBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitNamespaceBody(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::NamespaceBodyContext* CHTLParser::namespaceBody() {
  NamespaceBodyContext *_localctx = _tracker.createInstance<NamespaceBodyContext>(_ctx, getState());
  enterRule(_localctx, 140, CHTLParser::RuleNamespaceBody);
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
    setState(644);
    match(CHTLParser::LBRACE);
    setState(648);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::EXCEPT

    || _la == CHTLParser::LBRACKET) {
      setState(645);
      namespaceContent();
      setState(650);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(651);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamespaceContentContext ------------------------------------------------------------------

CHTLParser::NamespaceContentContext::NamespaceContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::NamespaceDeclarationContext* CHTLParser::NamespaceContentContext::namespaceDeclaration() {
  return getRuleContext<CHTLParser::NamespaceDeclarationContext>(0);
}

CHTLParser::TemplateDeclarationContext* CHTLParser::NamespaceContentContext::templateDeclaration() {
  return getRuleContext<CHTLParser::TemplateDeclarationContext>(0);
}

CHTLParser::CustomDeclarationContext* CHTLParser::NamespaceContentContext::customDeclaration() {
  return getRuleContext<CHTLParser::CustomDeclarationContext>(0);
}

CHTLParser::ExceptStatementContext* CHTLParser::NamespaceContentContext::exceptStatement() {
  return getRuleContext<CHTLParser::ExceptStatementContext>(0);
}


size_t CHTLParser::NamespaceContentContext::getRuleIndex() const {
  return CHTLParser::RuleNamespaceContent;
}


std::any CHTLParser::NamespaceContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitNamespaceContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::NamespaceContentContext* CHTLParser::namespaceContent() {
  NamespaceContentContext *_localctx = _tracker.createInstance<NamespaceContentContext>(_ctx, getState());
  enterRule(_localctx, 142, CHTLParser::RuleNamespaceContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(657);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(653);
      namespaceDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(654);
      templateDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(655);
      customDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(656);
      exceptStatement();
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

//----------------- ConfigurationBlockContext ------------------------------------------------------------------

CHTLParser::ConfigurationBlockContext::ConfigurationBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ConfigurationBlockContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::ConfigurationBlockContext::CONFIGURATION() {
  return getToken(CHTLParser::CONFIGURATION, 0);
}

tree::TerminalNode* CHTLParser::ConfigurationBlockContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

tree::TerminalNode* CHTLParser::ConfigurationBlockContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::ConfigurationBlockContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::ConfigContentContext *> CHTLParser::ConfigurationBlockContext::configContent() {
  return getRuleContexts<CHTLParser::ConfigContentContext>();
}

CHTLParser::ConfigContentContext* CHTLParser::ConfigurationBlockContext::configContent(size_t i) {
  return getRuleContext<CHTLParser::ConfigContentContext>(i);
}


size_t CHTLParser::ConfigurationBlockContext::getRuleIndex() const {
  return CHTLParser::RuleConfigurationBlock;
}


std::any CHTLParser::ConfigurationBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitConfigurationBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ConfigurationBlockContext* CHTLParser::configurationBlock() {
  ConfigurationBlockContext *_localctx = _tracker.createInstance<ConfigurationBlockContext>(_ctx, getState());
  enterRule(_localctx, 144, CHTLParser::RuleConfigurationBlock);
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
    setState(659);
    match(CHTLParser::LBRACKET);
    setState(660);
    match(CHTLParser::CONFIGURATION);
    setState(661);
    match(CHTLParser::RBRACKET);
    setState(662);
    match(CHTLParser::LBRACE);
    setState(666);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::LBRACKET

    || _la == CHTLParser::IDENTIFIER) {
      setState(663);
      configContent();
      setState(668);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(669);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConfigContentContext ------------------------------------------------------------------

CHTLParser::ConfigContentContext::ConfigContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ConfigAssignmentContext* CHTLParser::ConfigContentContext::configAssignment() {
  return getRuleContext<CHTLParser::ConfigAssignmentContext>(0);
}

CHTLParser::NameBlockContext* CHTLParser::ConfigContentContext::nameBlock() {
  return getRuleContext<CHTLParser::NameBlockContext>(0);
}


size_t CHTLParser::ConfigContentContext::getRuleIndex() const {
  return CHTLParser::RuleConfigContent;
}


std::any CHTLParser::ConfigContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitConfigContent(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ConfigContentContext* CHTLParser::configContent() {
  ConfigContentContext *_localctx = _tracker.createInstance<ConfigContentContext>(_ctx, getState());
  enterRule(_localctx, 146, CHTLParser::RuleConfigContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(673);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(671);
        configAssignment();
        break;
      }

      case CHTLParser::LBRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(672);
        nameBlock();
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

//----------------- ConfigAssignmentContext ------------------------------------------------------------------

CHTLParser::ConfigAssignmentContext::ConfigAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ConfigAssignmentContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::ConfigAssignmentContext::EQUALS() {
  return getToken(CHTLParser::EQUALS, 0);
}

CHTLParser::ConfigValueContext* CHTLParser::ConfigAssignmentContext::configValue() {
  return getRuleContext<CHTLParser::ConfigValueContext>(0);
}

tree::TerminalNode* CHTLParser::ConfigAssignmentContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}


size_t CHTLParser::ConfigAssignmentContext::getRuleIndex() const {
  return CHTLParser::RuleConfigAssignment;
}


std::any CHTLParser::ConfigAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitConfigAssignment(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ConfigAssignmentContext* CHTLParser::configAssignment() {
  ConfigAssignmentContext *_localctx = _tracker.createInstance<ConfigAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 148, CHTLParser::RuleConfigAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(675);
    match(CHTLParser::IDENTIFIER);
    setState(676);
    match(CHTLParser::EQUALS);
    setState(677);
    configValue();
    setState(678);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConfigValueContext ------------------------------------------------------------------

CHTLParser::ConfigValueContext::ConfigValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::StringLiteralContext* CHTLParser::ConfigValueContext::stringLiteral() {
  return getRuleContext<CHTLParser::StringLiteralContext>(0);
}

tree::TerminalNode* CHTLParser::ConfigValueContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}

tree::TerminalNode* CHTLParser::ConfigValueContext::BOOLEAN() {
  return getToken(CHTLParser::BOOLEAN, 0);
}


size_t CHTLParser::ConfigValueContext::getRuleIndex() const {
  return CHTLParser::RuleConfigValue;
}


std::any CHTLParser::ConfigValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitConfigValue(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::ConfigValueContext* CHTLParser::configValue() {
  ConfigValueContext *_localctx = _tracker.createInstance<ConfigValueContext>(_ctx, getState());
  enterRule(_localctx, 150, CHTLParser::RuleConfigValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(683);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::STRING_LITERAL:
      case CHTLParser::SINGLE_STRING_LITERAL:
      case CHTLParser::UNQUOTED_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(680);
        stringLiteral();
        break;
      }

      case CHTLParser::NUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(681);
        match(CHTLParser::NUMBER);
        break;
      }

      case CHTLParser::BOOLEAN: {
        enterOuterAlt(_localctx, 3);
        setState(682);
        match(CHTLParser::BOOLEAN);
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

//----------------- NameBlockContext ------------------------------------------------------------------

CHTLParser::NameBlockContext::NameBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::NameBlockContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::NameBlockContext::NAME() {
  return getToken(CHTLParser::NAME, 0);
}

tree::TerminalNode* CHTLParser::NameBlockContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

tree::TerminalNode* CHTLParser::NameBlockContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

tree::TerminalNode* CHTLParser::NameBlockContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

std::vector<CHTLParser::NameAssignmentContext *> CHTLParser::NameBlockContext::nameAssignment() {
  return getRuleContexts<CHTLParser::NameAssignmentContext>();
}

CHTLParser::NameAssignmentContext* CHTLParser::NameBlockContext::nameAssignment(size_t i) {
  return getRuleContext<CHTLParser::NameAssignmentContext>(i);
}


size_t CHTLParser::NameBlockContext::getRuleIndex() const {
  return CHTLParser::RuleNameBlock;
}


std::any CHTLParser::NameBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitNameBlock(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::NameBlockContext* CHTLParser::nameBlock() {
  NameBlockContext *_localctx = _tracker.createInstance<NameBlockContext>(_ctx, getState());
  enterRule(_localctx, 152, CHTLParser::RuleNameBlock);
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
    setState(685);
    match(CHTLParser::LBRACKET);
    setState(686);
    match(CHTLParser::NAME);
    setState(687);
    match(CHTLParser::RBRACKET);
    setState(688);
    match(CHTLParser::LBRACE);
    setState(692);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::IDENTIFIER) {
      setState(689);
      nameAssignment();
      setState(694);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(695);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameAssignmentContext ------------------------------------------------------------------

CHTLParser::NameAssignmentContext::NameAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::NameAssignmentContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::NameAssignmentContext::EQUALS() {
  return getToken(CHTLParser::EQUALS, 0);
}

std::vector<CHTLParser::StringLiteralContext *> CHTLParser::NameAssignmentContext::stringLiteral() {
  return getRuleContexts<CHTLParser::StringLiteralContext>();
}

CHTLParser::StringLiteralContext* CHTLParser::NameAssignmentContext::stringLiteral(size_t i) {
  return getRuleContext<CHTLParser::StringLiteralContext>(i);
}

tree::TerminalNode* CHTLParser::NameAssignmentContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::NameAssignmentContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLParser::NameAssignmentContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}

std::vector<tree::TerminalNode *> CHTLParser::NameAssignmentContext::COMMA() {
  return getTokens(CHTLParser::COMMA);
}

tree::TerminalNode* CHTLParser::NameAssignmentContext::COMMA(size_t i) {
  return getToken(CHTLParser::COMMA, i);
}


size_t CHTLParser::NameAssignmentContext::getRuleIndex() const {
  return CHTLParser::RuleNameAssignment;
}


std::any CHTLParser::NameAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CHTLVisitor*>(visitor))
    return parserVisitor->visitNameAssignment(this);
  else
    return visitor->visitChildren(this);
}

CHTLParser::NameAssignmentContext* CHTLParser::nameAssignment() {
  NameAssignmentContext *_localctx = _tracker.createInstance<NameAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 154, CHTLParser::RuleNameAssignment);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(716);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(697);
      match(CHTLParser::IDENTIFIER);
      setState(698);
      match(CHTLParser::EQUALS);
      setState(699);
      stringLiteral();
      setState(700);
      match(CHTLParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(702);
      match(CHTLParser::IDENTIFIER);
      setState(703);
      match(CHTLParser::EQUALS);
      setState(704);
      match(CHTLParser::LBRACKET);
      setState(705);
      stringLiteral();
      setState(710);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CHTLParser::COMMA) {
        setState(706);
        match(CHTLParser::COMMA);
        setState(707);
        stringLiteral();
        setState(712);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(713);
      match(CHTLParser::RBRACKET);
      setState(714);
      match(CHTLParser::SEMICOLON);
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

void CHTLParser::initialize() {
  std::call_once(chtlParserOnceFlag, chtlParserInitialize);
}
