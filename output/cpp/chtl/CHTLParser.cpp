
// Generated from CHTL.g4 by ANTLR 4.13.1


#include "CHTLListener.h"

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

::antlr4::internal::OnceFlag chtlParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CHTLParserStaticData *chtlParserStaticData = nullptr;

void chtlParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (chtlParserStaticData != nullptr) {
    return;
  }
#else
  assert(chtlParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CHTLParserStaticData>(
    std::vector<std::string>{
      "program", "topLevelStatement", "configurationBlock", "configurationItem", 
      "configKey", "configValue", "configValueArray", "configArrayItem", 
      "nameConfigItem", "namespaceDeclaration", "namespaceBody", "namespaceContent", 
      "importStatement", "importType", "importPath", "dottedPath", "templateDeclaration", 
      "templateType", "templateBody", "templateContent", "templateInheritance", 
      "customDeclaration", "customType", "customBody", "customContent", 
      "customInheritance", "customSpecialization", "specializationContent", 
      "deleteStatement", "deleteTarget", "insertStatement", "insertPosition", 
      "elementSelector", "insertContent", "originBlock", "originType", "originContent", 
      "htmlElement", "elementName", "elementIndexAccess", "elementBody", 
      "elementContent", "attribute", "attributeName", "attributeValue", 
      "textContent", "styleBlock", "styleContent", "styleProperty", "propertyName", 
      "propertyValue", "cssSelector", "pseudoClass", "pseudoElement", "cssFunction", 
      "cssArguments", "cssArgument", "scriptBlock", "scriptContent", "elementUsage", 
      "elementSpecialization", "elementSpecializationContent", "styleUsage", 
      "styleSpecialization", "variableDefinition", "variableUsage", "variableArguments", 
      "variableArgument", "variableAssignment", "namespacePath", "exceptConstraint", 
      "exceptTarget", "comment"
    },
    std::vector<std::string>{
      "", "'[Configuration]'", "'{'", "'}'", "'='", "';'", "'[Name]'", "'['", 
      "','", "']'", "'@'", "'[Namespace]'", "'[Import]'", "'from'", "'as'", 
      "'@Html'", "'@Style'", "'@JavaScript'", "'@Chtl'", "'[Custom]'", "'[Template]'", 
      "'.'", "'@Element'", "'@Var'", "'inherit'", "'delete'", "'insert'", 
      "'after'", "'before'", "'replace'", "'at'", "'top'", "'bottom'", "'[Origin]'", 
      "'text'", "'style'", "'script'", "':'", "'-'", "'#'", "'&'", "'::'", 
      "'('", "')'", "'except'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "SINGLE_LINE_COMMENT", 
      "MULTI_LINE_COMMENT", "GENERATOR_COMMENT", "BOOLEAN", "NUMBER", "STRING_LITERAL", 
      "UNQUOTED_LITERAL", "IDENTIFIER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,53,756,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,1,0,5,0,148,8,0,10,0,12,0,151,9,0,1,0,1,0,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,165,8,1,1,2,1,2,1,2,5,2,170,8,
  	2,10,2,12,2,173,9,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,185,8,
  	3,10,3,12,3,188,9,3,1,3,3,3,191,8,3,1,4,1,4,1,5,1,5,1,5,1,5,3,5,199,8,
  	5,1,6,1,6,1,6,1,6,5,6,205,8,6,10,6,12,6,208,9,6,1,6,1,6,1,7,1,7,1,7,3,
  	7,215,8,7,1,8,1,8,1,8,1,8,3,8,221,8,8,1,8,1,8,1,9,1,9,1,9,3,9,228,8,9,
  	1,10,1,10,5,10,232,8,10,10,10,12,10,235,9,10,1,10,1,10,1,11,1,11,1,11,
  	1,11,3,11,243,8,11,1,12,1,12,1,12,1,12,1,12,1,12,3,12,251,8,12,1,12,3,
  	12,254,8,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,
  	13,3,13,268,8,13,1,14,1,14,3,14,272,8,14,1,15,1,15,1,15,5,15,277,8,15,
  	10,15,12,15,280,9,15,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,18,1,18,5,18,
  	291,8,18,10,18,12,18,294,9,18,1,18,1,18,1,19,1,19,1,19,1,19,3,19,302,
  	8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,313,8,20,1,21,
  	1,21,1,21,1,21,1,21,1,22,1,22,1,23,1,23,5,23,324,8,23,10,23,12,23,327,
  	9,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,3,24,337,8,24,1,25,1,25,
  	1,25,3,25,342,8,25,1,25,3,25,345,8,25,1,25,1,25,1,25,3,25,350,8,25,1,
  	25,3,25,353,8,25,3,25,355,8,25,1,26,1,26,5,26,359,8,26,10,26,12,26,362,
  	9,26,1,26,1,26,1,27,1,27,1,27,3,27,369,8,27,1,28,1,28,1,28,1,28,5,28,
  	375,8,28,10,28,12,28,378,9,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,3,29,393,8,29,1,30,1,30,1,30,1,30,1,30,5,30,
  	400,8,30,10,30,12,30,403,9,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,1,31,
  	1,31,3,31,414,8,31,1,32,1,32,1,32,1,32,3,32,420,8,32,1,33,1,33,3,33,424,
  	8,33,1,34,1,34,1,34,3,34,429,8,34,1,34,1,34,1,34,1,34,1,35,1,35,1,36,
  	5,36,438,8,36,10,36,12,36,441,9,36,1,37,1,37,3,37,445,8,37,1,37,1,37,
  	1,38,1,38,1,39,1,39,1,39,1,39,1,40,1,40,5,40,457,8,40,10,40,12,40,460,
  	9,40,1,40,1,40,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,3,41,472,8,41,
  	1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,3,42,484,8,42,1,43,
  	1,43,1,44,1,44,1,44,3,44,491,8,44,1,45,1,45,1,46,1,46,1,46,5,46,498,8,
  	46,10,46,12,46,501,9,46,1,46,1,46,1,47,1,47,1,47,1,47,5,47,509,8,47,10,
  	47,12,47,512,9,47,1,47,1,47,1,47,3,47,517,8,47,1,48,1,48,1,48,1,48,1,
  	48,1,48,1,48,1,48,1,48,1,48,1,48,3,48,530,8,48,1,49,1,49,1,49,5,49,535,
  	8,49,10,49,12,49,538,9,49,1,50,1,50,1,50,1,50,3,50,544,8,50,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,3,51,555,8,51,1,52,1,52,1,52,1,53,
  	1,53,1,53,1,54,1,54,1,54,3,54,566,8,54,1,54,1,54,1,55,1,55,1,55,5,55,
  	573,8,55,10,55,12,55,576,9,55,1,56,1,56,1,57,1,57,1,57,1,57,1,57,1,58,
  	4,58,586,8,58,11,58,12,58,587,1,58,3,58,591,8,58,1,59,1,59,1,59,3,59,
  	596,8,59,1,59,1,59,3,59,600,8,59,1,59,1,59,1,59,1,59,1,59,3,59,607,8,
  	59,1,59,1,59,3,59,611,8,59,1,59,1,59,1,59,1,59,1,59,1,59,3,59,619,8,59,
  	1,59,1,59,3,59,623,8,59,1,59,1,59,1,59,1,59,1,59,1,59,3,59,631,8,59,1,
  	59,1,59,3,59,635,8,59,1,59,1,59,1,59,1,59,1,59,1,59,1,59,3,59,644,8,59,
  	1,60,1,60,5,60,648,8,60,10,60,12,60,651,9,60,1,60,1,60,1,61,1,61,1,61,
  	1,61,3,61,659,8,61,1,62,1,62,1,62,3,62,664,8,62,1,62,1,62,1,62,1,62,1,
  	62,3,62,671,8,62,1,62,1,62,3,62,675,8,62,1,63,1,63,5,63,679,8,63,10,63,
  	12,63,682,9,63,1,63,1,63,1,64,1,64,1,64,1,64,1,64,1,65,1,65,1,65,3,65,
  	694,8,65,1,65,1,65,1,66,1,66,1,66,5,66,701,8,66,10,66,12,66,704,9,66,
  	1,67,1,67,1,67,1,67,3,67,710,8,67,1,68,1,68,1,68,1,68,1,68,1,69,1,69,
  	1,69,5,69,720,8,69,10,69,12,69,723,9,69,1,70,1,70,1,70,1,70,5,70,729,
  	8,70,10,70,12,70,732,9,70,1,70,1,70,1,71,1,71,1,71,1,71,1,71,1,71,1,71,
  	1,71,1,71,3,71,745,8,71,1,71,1,71,3,71,749,8,71,1,71,3,71,752,8,71,1,
  	72,1,72,1,72,0,0,73,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,
  	36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,
  	82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,
  	122,124,126,128,130,132,134,136,138,140,142,144,0,6,2,0,16,16,22,23,1,
  	0,15,17,1,0,3,3,2,0,34,36,52,52,1,0,50,51,1,0,45,47,809,0,149,1,0,0,0,
  	2,164,1,0,0,0,4,166,1,0,0,0,6,190,1,0,0,0,8,192,1,0,0,0,10,198,1,0,0,
  	0,12,200,1,0,0,0,14,214,1,0,0,0,16,216,1,0,0,0,18,224,1,0,0,0,20,229,
  	1,0,0,0,22,242,1,0,0,0,24,244,1,0,0,0,26,267,1,0,0,0,28,271,1,0,0,0,30,
  	273,1,0,0,0,32,281,1,0,0,0,34,286,1,0,0,0,36,288,1,0,0,0,38,301,1,0,0,
  	0,40,312,1,0,0,0,42,314,1,0,0,0,44,319,1,0,0,0,46,321,1,0,0,0,48,336,
  	1,0,0,0,50,354,1,0,0,0,52,356,1,0,0,0,54,368,1,0,0,0,56,370,1,0,0,0,58,
  	392,1,0,0,0,60,394,1,0,0,0,62,413,1,0,0,0,64,415,1,0,0,0,66,423,1,0,0,
  	0,68,425,1,0,0,0,70,434,1,0,0,0,72,439,1,0,0,0,74,442,1,0,0,0,76,448,
  	1,0,0,0,78,450,1,0,0,0,80,454,1,0,0,0,82,471,1,0,0,0,84,483,1,0,0,0,86,
  	485,1,0,0,0,88,490,1,0,0,0,90,492,1,0,0,0,92,494,1,0,0,0,94,516,1,0,0,
  	0,96,529,1,0,0,0,98,531,1,0,0,0,100,543,1,0,0,0,102,554,1,0,0,0,104,556,
  	1,0,0,0,106,559,1,0,0,0,108,562,1,0,0,0,110,569,1,0,0,0,112,577,1,0,0,
  	0,114,579,1,0,0,0,116,590,1,0,0,0,118,643,1,0,0,0,120,645,1,0,0,0,122,
  	658,1,0,0,0,124,674,1,0,0,0,126,676,1,0,0,0,128,685,1,0,0,0,130,690,1,
  	0,0,0,132,697,1,0,0,0,134,709,1,0,0,0,136,711,1,0,0,0,138,716,1,0,0,0,
  	140,724,1,0,0,0,142,751,1,0,0,0,144,753,1,0,0,0,146,148,3,2,1,0,147,146,
  	1,0,0,0,148,151,1,0,0,0,149,147,1,0,0,0,149,150,1,0,0,0,150,152,1,0,0,
  	0,151,149,1,0,0,0,152,153,5,0,0,1,153,1,1,0,0,0,154,165,3,4,2,0,155,165,
  	3,18,9,0,156,165,3,24,12,0,157,165,3,32,16,0,158,165,3,42,21,0,159,165,
  	3,68,34,0,160,165,3,74,37,0,161,165,3,92,46,0,162,165,3,114,57,0,163,
  	165,3,144,72,0,164,154,1,0,0,0,164,155,1,0,0,0,164,156,1,0,0,0,164,157,
  	1,0,0,0,164,158,1,0,0,0,164,159,1,0,0,0,164,160,1,0,0,0,164,161,1,0,0,
  	0,164,162,1,0,0,0,164,163,1,0,0,0,165,3,1,0,0,0,166,167,5,1,0,0,167,171,
  	5,2,0,0,168,170,3,6,3,0,169,168,1,0,0,0,170,173,1,0,0,0,171,169,1,0,0,
  	0,171,172,1,0,0,0,172,174,1,0,0,0,173,171,1,0,0,0,174,175,5,3,0,0,175,
  	5,1,0,0,0,176,177,3,8,4,0,177,178,5,4,0,0,178,179,3,10,5,0,179,180,5,
  	5,0,0,180,191,1,0,0,0,181,182,5,6,0,0,182,186,5,2,0,0,183,185,3,16,8,
  	0,184,183,1,0,0,0,185,188,1,0,0,0,186,184,1,0,0,0,186,187,1,0,0,0,187,
  	189,1,0,0,0,188,186,1,0,0,0,189,191,5,3,0,0,190,176,1,0,0,0,190,181,1,
  	0,0,0,191,7,1,0,0,0,192,193,5,52,0,0,193,9,1,0,0,0,194,199,5,50,0,0,195,
  	199,5,49,0,0,196,199,5,48,0,0,197,199,3,12,6,0,198,194,1,0,0,0,198,195,
  	1,0,0,0,198,196,1,0,0,0,198,197,1,0,0,0,199,11,1,0,0,0,200,201,5,7,0,
  	0,201,206,3,14,7,0,202,203,5,8,0,0,203,205,3,14,7,0,204,202,1,0,0,0,205,
  	208,1,0,0,0,206,204,1,0,0,0,206,207,1,0,0,0,207,209,1,0,0,0,208,206,1,
  	0,0,0,209,210,5,9,0,0,210,13,1,0,0,0,211,212,5,10,0,0,212,215,5,52,0,
  	0,213,215,5,50,0,0,214,211,1,0,0,0,214,213,1,0,0,0,215,15,1,0,0,0,216,
  	217,5,52,0,0,217,220,5,4,0,0,218,221,3,10,5,0,219,221,3,12,6,0,220,218,
  	1,0,0,0,220,219,1,0,0,0,221,222,1,0,0,0,222,223,5,5,0,0,223,17,1,0,0,
  	0,224,225,5,11,0,0,225,227,5,52,0,0,226,228,3,20,10,0,227,226,1,0,0,0,
  	227,228,1,0,0,0,228,19,1,0,0,0,229,233,5,2,0,0,230,232,3,22,11,0,231,
  	230,1,0,0,0,232,235,1,0,0,0,233,231,1,0,0,0,233,234,1,0,0,0,234,236,1,
  	0,0,0,235,233,1,0,0,0,236,237,5,3,0,0,237,21,1,0,0,0,238,243,3,18,9,0,
  	239,243,3,32,16,0,240,243,3,42,21,0,241,243,3,140,70,0,242,238,1,0,0,
  	0,242,239,1,0,0,0,242,240,1,0,0,0,242,241,1,0,0,0,243,23,1,0,0,0,244,
  	245,5,12,0,0,245,246,3,26,13,0,246,247,5,13,0,0,247,250,3,28,14,0,248,
  	249,5,14,0,0,249,251,5,52,0,0,250,248,1,0,0,0,250,251,1,0,0,0,251,253,
  	1,0,0,0,252,254,5,5,0,0,253,252,1,0,0,0,253,254,1,0,0,0,254,25,1,0,0,
  	0,255,268,5,15,0,0,256,268,5,16,0,0,257,268,5,17,0,0,258,268,5,18,0,0,
  	259,260,5,19,0,0,260,261,3,44,22,0,261,262,5,52,0,0,262,268,1,0,0,0,263,
  	264,5,20,0,0,264,265,3,34,17,0,265,266,5,52,0,0,266,268,1,0,0,0,267,255,
  	1,0,0,0,267,256,1,0,0,0,267,257,1,0,0,0,267,258,1,0,0,0,267,259,1,0,0,
  	0,267,263,1,0,0,0,268,27,1,0,0,0,269,272,5,50,0,0,270,272,3,30,15,0,271,
  	269,1,0,0,0,271,270,1,0,0,0,272,29,1,0,0,0,273,278,5,52,0,0,274,275,5,
  	21,0,0,275,277,5,52,0,0,276,274,1,0,0,0,277,280,1,0,0,0,278,276,1,0,0,
  	0,278,279,1,0,0,0,279,31,1,0,0,0,280,278,1,0,0,0,281,282,5,20,0,0,282,
  	283,3,34,17,0,283,284,5,52,0,0,284,285,3,36,18,0,285,33,1,0,0,0,286,287,
  	7,0,0,0,287,35,1,0,0,0,288,292,5,2,0,0,289,291,3,38,19,0,290,289,1,0,
  	0,0,291,294,1,0,0,0,292,290,1,0,0,0,292,293,1,0,0,0,293,295,1,0,0,0,294,
  	292,1,0,0,0,295,296,5,3,0,0,296,37,1,0,0,0,297,302,3,96,48,0,298,302,
  	3,74,37,0,299,302,3,40,20,0,300,302,3,128,64,0,301,297,1,0,0,0,301,298,
  	1,0,0,0,301,299,1,0,0,0,301,300,1,0,0,0,302,39,1,0,0,0,303,304,3,34,17,
  	0,304,305,5,52,0,0,305,306,5,5,0,0,306,313,1,0,0,0,307,308,5,24,0,0,308,
  	309,3,34,17,0,309,310,5,52,0,0,310,311,5,5,0,0,311,313,1,0,0,0,312,303,
  	1,0,0,0,312,307,1,0,0,0,313,41,1,0,0,0,314,315,5,19,0,0,315,316,3,44,
  	22,0,316,317,5,52,0,0,317,318,3,46,23,0,318,43,1,0,0,0,319,320,7,0,0,
  	0,320,45,1,0,0,0,321,325,5,2,0,0,322,324,3,48,24,0,323,322,1,0,0,0,324,
  	327,1,0,0,0,325,323,1,0,0,0,325,326,1,0,0,0,326,328,1,0,0,0,327,325,1,
  	0,0,0,328,329,5,3,0,0,329,47,1,0,0,0,330,337,3,96,48,0,331,337,3,74,37,
  	0,332,337,3,50,25,0,333,337,3,128,64,0,334,337,3,56,28,0,335,337,3,60,
  	30,0,336,330,1,0,0,0,336,331,1,0,0,0,336,332,1,0,0,0,336,333,1,0,0,0,
  	336,334,1,0,0,0,336,335,1,0,0,0,337,49,1,0,0,0,338,339,3,44,22,0,339,
  	341,5,52,0,0,340,342,3,52,26,0,341,340,1,0,0,0,341,342,1,0,0,0,342,344,
  	1,0,0,0,343,345,5,5,0,0,344,343,1,0,0,0,344,345,1,0,0,0,345,355,1,0,0,
  	0,346,347,3,34,17,0,347,349,5,52,0,0,348,350,3,52,26,0,349,348,1,0,0,
  	0,349,350,1,0,0,0,350,352,1,0,0,0,351,353,5,5,0,0,352,351,1,0,0,0,352,
  	353,1,0,0,0,353,355,1,0,0,0,354,338,1,0,0,0,354,346,1,0,0,0,355,51,1,
  	0,0,0,356,360,5,2,0,0,357,359,3,54,27,0,358,357,1,0,0,0,359,362,1,0,0,
  	0,360,358,1,0,0,0,360,361,1,0,0,0,361,363,1,0,0,0,362,360,1,0,0,0,363,
  	364,5,3,0,0,364,53,1,0,0,0,365,369,3,96,48,0,366,369,3,56,28,0,367,369,
  	3,136,68,0,368,365,1,0,0,0,368,366,1,0,0,0,368,367,1,0,0,0,369,55,1,0,
  	0,0,370,371,5,25,0,0,371,376,3,58,29,0,372,373,5,8,0,0,373,375,3,58,29,
  	0,374,372,1,0,0,0,375,378,1,0,0,0,376,374,1,0,0,0,376,377,1,0,0,0,377,
  	379,1,0,0,0,378,376,1,0,0,0,379,380,5,5,0,0,380,57,1,0,0,0,381,393,5,
  	52,0,0,382,383,5,52,0,0,383,384,5,7,0,0,384,385,5,49,0,0,385,393,5,9,
  	0,0,386,387,3,44,22,0,387,388,5,52,0,0,388,393,1,0,0,0,389,390,3,34,17,
  	0,390,391,5,52,0,0,391,393,1,0,0,0,392,381,1,0,0,0,392,382,1,0,0,0,392,
  	386,1,0,0,0,392,389,1,0,0,0,393,59,1,0,0,0,394,395,5,26,0,0,395,396,3,
  	62,31,0,396,397,3,64,32,0,397,401,5,2,0,0,398,400,3,66,33,0,399,398,1,
  	0,0,0,400,403,1,0,0,0,401,399,1,0,0,0,401,402,1,0,0,0,402,404,1,0,0,0,
  	403,401,1,0,0,0,404,405,5,3,0,0,405,61,1,0,0,0,406,414,5,27,0,0,407,414,
  	5,28,0,0,408,414,5,29,0,0,409,410,5,30,0,0,410,414,5,31,0,0,411,412,5,
  	30,0,0,412,414,5,32,0,0,413,406,1,0,0,0,413,407,1,0,0,0,413,408,1,0,0,
  	0,413,409,1,0,0,0,413,411,1,0,0,0,414,63,1,0,0,0,415,419,5,52,0,0,416,
  	417,5,7,0,0,417,418,5,49,0,0,418,420,5,9,0,0,419,416,1,0,0,0,419,420,
  	1,0,0,0,420,65,1,0,0,0,421,424,3,74,37,0,422,424,3,118,59,0,423,421,1,
  	0,0,0,423,422,1,0,0,0,424,67,1,0,0,0,425,426,5,33,0,0,426,428,3,70,35,
  	0,427,429,5,52,0,0,428,427,1,0,0,0,428,429,1,0,0,0,429,430,1,0,0,0,430,
  	431,5,2,0,0,431,432,3,72,36,0,432,433,5,3,0,0,433,69,1,0,0,0,434,435,
  	7,1,0,0,435,71,1,0,0,0,436,438,8,2,0,0,437,436,1,0,0,0,438,441,1,0,0,
  	0,439,437,1,0,0,0,439,440,1,0,0,0,440,73,1,0,0,0,441,439,1,0,0,0,442,
  	444,3,76,38,0,443,445,3,78,39,0,444,443,1,0,0,0,444,445,1,0,0,0,445,446,
  	1,0,0,0,446,447,3,80,40,0,447,75,1,0,0,0,448,449,7,3,0,0,449,77,1,0,0,
  	0,450,451,5,7,0,0,451,452,5,49,0,0,452,453,5,9,0,0,453,79,1,0,0,0,454,
  	458,5,2,0,0,455,457,3,82,41,0,456,455,1,0,0,0,457,460,1,0,0,0,458,456,
  	1,0,0,0,458,459,1,0,0,0,459,461,1,0,0,0,460,458,1,0,0,0,461,462,5,3,0,
  	0,462,81,1,0,0,0,463,472,3,84,42,0,464,472,3,74,37,0,465,472,3,92,46,
  	0,466,472,3,114,57,0,467,472,3,90,45,0,468,472,3,118,59,0,469,472,3,140,
  	70,0,470,472,3,144,72,0,471,463,1,0,0,0,471,464,1,0,0,0,471,465,1,0,0,
  	0,471,466,1,0,0,0,471,467,1,0,0,0,471,468,1,0,0,0,471,469,1,0,0,0,471,
  	470,1,0,0,0,472,83,1,0,0,0,473,474,3,86,43,0,474,475,5,37,0,0,475,476,
  	3,88,44,0,476,477,5,5,0,0,477,484,1,0,0,0,478,479,3,86,43,0,479,480,5,
  	4,0,0,480,481,3,88,44,0,481,482,5,5,0,0,482,484,1,0,0,0,483,473,1,0,0,
  	0,483,478,1,0,0,0,484,85,1,0,0,0,485,486,5,52,0,0,486,87,1,0,0,0,487,
  	491,5,50,0,0,488,491,5,51,0,0,489,491,3,130,65,0,490,487,1,0,0,0,490,
  	488,1,0,0,0,490,489,1,0,0,0,491,89,1,0,0,0,492,493,7,4,0,0,493,91,1,0,
  	0,0,494,495,5,35,0,0,495,499,5,2,0,0,496,498,3,94,47,0,497,496,1,0,0,
  	0,498,501,1,0,0,0,499,497,1,0,0,0,499,500,1,0,0,0,500,502,1,0,0,0,501,
  	499,1,0,0,0,502,503,5,3,0,0,503,93,1,0,0,0,504,517,3,96,48,0,505,506,
  	3,102,51,0,506,510,5,2,0,0,507,509,3,94,47,0,508,507,1,0,0,0,509,512,
  	1,0,0,0,510,508,1,0,0,0,510,511,1,0,0,0,511,513,1,0,0,0,512,510,1,0,0,
  	0,513,514,5,3,0,0,514,517,1,0,0,0,515,517,3,124,62,0,516,504,1,0,0,0,
  	516,505,1,0,0,0,516,515,1,0,0,0,517,95,1,0,0,0,518,519,3,98,49,0,519,
  	520,5,37,0,0,520,521,3,100,50,0,521,522,5,5,0,0,522,530,1,0,0,0,523,524,
  	3,98,49,0,524,525,5,8,0,0,525,530,1,0,0,0,526,527,3,98,49,0,527,528,5,
  	5,0,0,528,530,1,0,0,0,529,518,1,0,0,0,529,523,1,0,0,0,529,526,1,0,0,0,
  	530,97,1,0,0,0,531,536,5,52,0,0,532,533,5,38,0,0,533,535,5,52,0,0,534,
  	532,1,0,0,0,535,538,1,0,0,0,536,534,1,0,0,0,536,537,1,0,0,0,537,99,1,
  	0,0,0,538,536,1,0,0,0,539,544,5,50,0,0,540,544,5,51,0,0,541,544,3,130,
  	65,0,542,544,3,108,54,0,543,539,1,0,0,0,543,540,1,0,0,0,543,541,1,0,0,
  	0,543,542,1,0,0,0,544,101,1,0,0,0,545,546,5,21,0,0,546,555,5,52,0,0,547,
  	548,5,39,0,0,548,555,5,52,0,0,549,550,5,40,0,0,550,555,3,104,52,0,551,
  	552,5,40,0,0,552,555,3,106,53,0,553,555,5,40,0,0,554,545,1,0,0,0,554,
  	547,1,0,0,0,554,549,1,0,0,0,554,551,1,0,0,0,554,553,1,0,0,0,555,103,1,
  	0,0,0,556,557,5,37,0,0,557,558,5,52,0,0,558,105,1,0,0,0,559,560,5,41,
  	0,0,560,561,5,52,0,0,561,107,1,0,0,0,562,563,5,52,0,0,563,565,5,42,0,
  	0,564,566,3,110,55,0,565,564,1,0,0,0,565,566,1,0,0,0,566,567,1,0,0,0,
  	567,568,5,43,0,0,568,109,1,0,0,0,569,574,3,112,56,0,570,571,5,8,0,0,571,
  	573,3,112,56,0,572,570,1,0,0,0,573,576,1,0,0,0,574,572,1,0,0,0,574,575,
  	1,0,0,0,575,111,1,0,0,0,576,574,1,0,0,0,577,578,3,100,50,0,578,113,1,
  	0,0,0,579,580,5,36,0,0,580,581,5,2,0,0,581,582,3,116,58,0,582,583,5,3,
  	0,0,583,115,1,0,0,0,584,586,8,2,0,0,585,584,1,0,0,0,586,587,1,0,0,0,587,
  	585,1,0,0,0,587,588,1,0,0,0,588,591,1,0,0,0,589,591,1,0,0,0,590,585,1,
  	0,0,0,590,589,1,0,0,0,591,117,1,0,0,0,592,593,3,44,22,0,593,595,5,52,
  	0,0,594,596,3,120,60,0,595,594,1,0,0,0,595,596,1,0,0,0,596,599,1,0,0,
  	0,597,598,5,13,0,0,598,600,3,138,69,0,599,597,1,0,0,0,599,600,1,0,0,0,
  	600,601,1,0,0,0,601,602,5,5,0,0,602,644,1,0,0,0,603,604,3,34,17,0,604,
  	606,5,52,0,0,605,607,3,120,60,0,606,605,1,0,0,0,606,607,1,0,0,0,607,610,
  	1,0,0,0,608,609,5,13,0,0,609,611,3,138,69,0,610,608,1,0,0,0,610,611,1,
  	0,0,0,611,612,1,0,0,0,612,613,5,5,0,0,613,644,1,0,0,0,614,615,5,19,0,
  	0,615,616,3,44,22,0,616,618,5,52,0,0,617,619,3,120,60,0,618,617,1,0,0,
  	0,618,619,1,0,0,0,619,622,1,0,0,0,620,621,5,13,0,0,621,623,3,138,69,0,
  	622,620,1,0,0,0,622,623,1,0,0,0,623,624,1,0,0,0,624,625,5,5,0,0,625,644,
  	1,0,0,0,626,627,5,20,0,0,627,628,3,34,17,0,628,630,5,52,0,0,629,631,3,
  	120,60,0,630,629,1,0,0,0,630,631,1,0,0,0,631,634,1,0,0,0,632,633,5,13,
  	0,0,633,635,3,138,69,0,634,632,1,0,0,0,634,635,1,0,0,0,635,636,1,0,0,
  	0,636,637,5,5,0,0,637,644,1,0,0,0,638,639,5,33,0,0,639,640,3,70,35,0,
  	640,641,5,52,0,0,641,642,5,5,0,0,642,644,1,0,0,0,643,592,1,0,0,0,643,
  	603,1,0,0,0,643,614,1,0,0,0,643,626,1,0,0,0,643,638,1,0,0,0,644,119,1,
  	0,0,0,645,649,5,2,0,0,646,648,3,122,61,0,647,646,1,0,0,0,648,651,1,0,
  	0,0,649,647,1,0,0,0,649,650,1,0,0,0,650,652,1,0,0,0,651,649,1,0,0,0,652,
  	653,5,3,0,0,653,121,1,0,0,0,654,659,3,74,37,0,655,659,3,92,46,0,656,659,
  	3,56,28,0,657,659,3,60,30,0,658,654,1,0,0,0,658,655,1,0,0,0,658,656,1,
  	0,0,0,658,657,1,0,0,0,659,123,1,0,0,0,660,661,3,44,22,0,661,663,5,52,
  	0,0,662,664,3,126,63,0,663,662,1,0,0,0,663,664,1,0,0,0,664,665,1,0,0,
  	0,665,666,5,5,0,0,666,675,1,0,0,0,667,668,3,34,17,0,668,670,5,52,0,0,
  	669,671,3,126,63,0,670,669,1,0,0,0,670,671,1,0,0,0,671,672,1,0,0,0,672,
  	673,5,5,0,0,673,675,1,0,0,0,674,660,1,0,0,0,674,667,1,0,0,0,675,125,1,
  	0,0,0,676,680,5,2,0,0,677,679,3,96,48,0,678,677,1,0,0,0,679,682,1,0,0,
  	0,680,678,1,0,0,0,680,681,1,0,0,0,681,683,1,0,0,0,682,680,1,0,0,0,683,
  	684,5,3,0,0,684,127,1,0,0,0,685,686,5,52,0,0,686,687,5,37,0,0,687,688,
  	5,50,0,0,688,689,5,5,0,0,689,129,1,0,0,0,690,691,5,52,0,0,691,693,5,42,
  	0,0,692,694,3,132,66,0,693,692,1,0,0,0,693,694,1,0,0,0,694,695,1,0,0,
  	0,695,696,5,43,0,0,696,131,1,0,0,0,697,702,3,134,67,0,698,699,5,8,0,0,
  	699,701,3,134,67,0,700,698,1,0,0,0,701,704,1,0,0,0,702,700,1,0,0,0,702,
  	703,1,0,0,0,703,133,1,0,0,0,704,702,1,0,0,0,705,706,5,52,0,0,706,707,
  	5,4,0,0,707,710,3,100,50,0,708,710,5,52,0,0,709,705,1,0,0,0,709,708,1,
  	0,0,0,710,135,1,0,0,0,711,712,5,52,0,0,712,713,5,4,0,0,713,714,3,100,
  	50,0,714,715,5,5,0,0,715,137,1,0,0,0,716,721,5,52,0,0,717,718,5,21,0,
  	0,718,720,5,52,0,0,719,717,1,0,0,0,720,723,1,0,0,0,721,719,1,0,0,0,721,
  	722,1,0,0,0,722,139,1,0,0,0,723,721,1,0,0,0,724,725,5,44,0,0,725,730,
  	3,142,71,0,726,727,5,8,0,0,727,729,3,142,71,0,728,726,1,0,0,0,729,732,
  	1,0,0,0,730,728,1,0,0,0,730,731,1,0,0,0,731,733,1,0,0,0,732,730,1,0,0,
  	0,733,734,5,5,0,0,734,141,1,0,0,0,735,752,5,52,0,0,736,737,3,44,22,0,
  	737,738,5,52,0,0,738,752,1,0,0,0,739,740,3,34,17,0,740,741,5,52,0,0,741,
  	752,1,0,0,0,742,744,5,19,0,0,743,745,3,44,22,0,744,743,1,0,0,0,744,745,
  	1,0,0,0,745,752,1,0,0,0,746,748,5,20,0,0,747,749,3,34,17,0,748,747,1,
  	0,0,0,748,749,1,0,0,0,749,752,1,0,0,0,750,752,5,15,0,0,751,735,1,0,0,
  	0,751,736,1,0,0,0,751,739,1,0,0,0,751,742,1,0,0,0,751,746,1,0,0,0,751,
  	750,1,0,0,0,752,143,1,0,0,0,753,754,7,5,0,0,754,145,1,0,0,0,76,149,164,
  	171,186,190,198,206,214,220,227,233,242,250,253,267,271,278,292,301,312,
  	325,336,341,344,349,352,354,360,368,376,392,401,413,419,423,428,439,444,
  	458,471,483,490,499,510,516,529,536,543,554,565,574,587,590,595,599,606,
  	610,618,622,630,634,643,649,658,663,670,674,680,693,702,709,721,730,744,
  	748,751
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

std::vector<CHTLParser::TopLevelStatementContext *> CHTLParser::ProgramContext::topLevelStatement() {
  return getRuleContexts<CHTLParser::TopLevelStatementContext>();
}

CHTLParser::TopLevelStatementContext* CHTLParser::ProgramContext::topLevelStatement(size_t i) {
  return getRuleContext<CHTLParser::TopLevelStatementContext>(i);
}


size_t CHTLParser::ProgramContext::getRuleIndex() const {
  return CHTLParser::RuleProgram;
}

void CHTLParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void CHTLParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
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
    setState(149);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4750019082590210) != 0)) {
      setState(146);
      topLevelStatement();
      setState(151);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(152);
    match(CHTLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TopLevelStatementContext ------------------------------------------------------------------

CHTLParser::TopLevelStatementContext::TopLevelStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ConfigurationBlockContext* CHTLParser::TopLevelStatementContext::configurationBlock() {
  return getRuleContext<CHTLParser::ConfigurationBlockContext>(0);
}

CHTLParser::NamespaceDeclarationContext* CHTLParser::TopLevelStatementContext::namespaceDeclaration() {
  return getRuleContext<CHTLParser::NamespaceDeclarationContext>(0);
}

CHTLParser::ImportStatementContext* CHTLParser::TopLevelStatementContext::importStatement() {
  return getRuleContext<CHTLParser::ImportStatementContext>(0);
}

CHTLParser::TemplateDeclarationContext* CHTLParser::TopLevelStatementContext::templateDeclaration() {
  return getRuleContext<CHTLParser::TemplateDeclarationContext>(0);
}

CHTLParser::CustomDeclarationContext* CHTLParser::TopLevelStatementContext::customDeclaration() {
  return getRuleContext<CHTLParser::CustomDeclarationContext>(0);
}

CHTLParser::OriginBlockContext* CHTLParser::TopLevelStatementContext::originBlock() {
  return getRuleContext<CHTLParser::OriginBlockContext>(0);
}

CHTLParser::HtmlElementContext* CHTLParser::TopLevelStatementContext::htmlElement() {
  return getRuleContext<CHTLParser::HtmlElementContext>(0);
}

CHTLParser::StyleBlockContext* CHTLParser::TopLevelStatementContext::styleBlock() {
  return getRuleContext<CHTLParser::StyleBlockContext>(0);
}

CHTLParser::ScriptBlockContext* CHTLParser::TopLevelStatementContext::scriptBlock() {
  return getRuleContext<CHTLParser::ScriptBlockContext>(0);
}

CHTLParser::CommentContext* CHTLParser::TopLevelStatementContext::comment() {
  return getRuleContext<CHTLParser::CommentContext>(0);
}


size_t CHTLParser::TopLevelStatementContext::getRuleIndex() const {
  return CHTLParser::RuleTopLevelStatement;
}

void CHTLParser::TopLevelStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTopLevelStatement(this);
}

void CHTLParser::TopLevelStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTopLevelStatement(this);
}

CHTLParser::TopLevelStatementContext* CHTLParser::topLevelStatement() {
  TopLevelStatementContext *_localctx = _tracker.createInstance<TopLevelStatementContext>(_ctx, getState());
  enterRule(_localctx, 2, CHTLParser::RuleTopLevelStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(164);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(154);
      configurationBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(155);
      namespaceDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(156);
      importStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(157);
      templateDeclaration();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(158);
      customDeclaration();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(159);
      originBlock();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(160);
      htmlElement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(161);
      styleBlock();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(162);
      scriptBlock();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(163);
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

//----------------- ConfigurationBlockContext ------------------------------------------------------------------

CHTLParser::ConfigurationBlockContext::ConfigurationBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ConfigurationItemContext *> CHTLParser::ConfigurationBlockContext::configurationItem() {
  return getRuleContexts<CHTLParser::ConfigurationItemContext>();
}

CHTLParser::ConfigurationItemContext* CHTLParser::ConfigurationBlockContext::configurationItem(size_t i) {
  return getRuleContext<CHTLParser::ConfigurationItemContext>(i);
}


size_t CHTLParser::ConfigurationBlockContext::getRuleIndex() const {
  return CHTLParser::RuleConfigurationBlock;
}

void CHTLParser::ConfigurationBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigurationBlock(this);
}

void CHTLParser::ConfigurationBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigurationBlock(this);
}

CHTLParser::ConfigurationBlockContext* CHTLParser::configurationBlock() {
  ConfigurationBlockContext *_localctx = _tracker.createInstance<ConfigurationBlockContext>(_ctx, getState());
  enterRule(_localctx, 4, CHTLParser::RuleConfigurationBlock);
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
    setState(166);
    match(CHTLParser::T__0);
    setState(167);
    match(CHTLParser::T__1);
    setState(171);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__5

    || _la == CHTLParser::IDENTIFIER) {
      setState(168);
      configurationItem();
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(174);
    match(CHTLParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConfigurationItemContext ------------------------------------------------------------------

CHTLParser::ConfigurationItemContext::ConfigurationItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ConfigKeyContext* CHTLParser::ConfigurationItemContext::configKey() {
  return getRuleContext<CHTLParser::ConfigKeyContext>(0);
}

CHTLParser::ConfigValueContext* CHTLParser::ConfigurationItemContext::configValue() {
  return getRuleContext<CHTLParser::ConfigValueContext>(0);
}

std::vector<CHTLParser::NameConfigItemContext *> CHTLParser::ConfigurationItemContext::nameConfigItem() {
  return getRuleContexts<CHTLParser::NameConfigItemContext>();
}

CHTLParser::NameConfigItemContext* CHTLParser::ConfigurationItemContext::nameConfigItem(size_t i) {
  return getRuleContext<CHTLParser::NameConfigItemContext>(i);
}


size_t CHTLParser::ConfigurationItemContext::getRuleIndex() const {
  return CHTLParser::RuleConfigurationItem;
}

void CHTLParser::ConfigurationItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigurationItem(this);
}

void CHTLParser::ConfigurationItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigurationItem(this);
}

CHTLParser::ConfigurationItemContext* CHTLParser::configurationItem() {
  ConfigurationItemContext *_localctx = _tracker.createInstance<ConfigurationItemContext>(_ctx, getState());
  enterRule(_localctx, 6, CHTLParser::RuleConfigurationItem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(190);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(176);
        configKey();
        setState(177);
        match(CHTLParser::T__3);
        setState(178);
        configValue();
        setState(179);
        match(CHTLParser::T__4);
        break;
      }

      case CHTLParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(181);
        match(CHTLParser::T__5);
        setState(182);
        match(CHTLParser::T__1);
        setState(186);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CHTLParser::IDENTIFIER) {
          setState(183);
          nameConfigItem();
          setState(188);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(189);
        match(CHTLParser::T__2);
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

//----------------- ConfigKeyContext ------------------------------------------------------------------

CHTLParser::ConfigKeyContext::ConfigKeyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ConfigKeyContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ConfigKeyContext::getRuleIndex() const {
  return CHTLParser::RuleConfigKey;
}

void CHTLParser::ConfigKeyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigKey(this);
}

void CHTLParser::ConfigKeyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigKey(this);
}

CHTLParser::ConfigKeyContext* CHTLParser::configKey() {
  ConfigKeyContext *_localctx = _tracker.createInstance<ConfigKeyContext>(_ctx, getState());
  enterRule(_localctx, 8, CHTLParser::RuleConfigKey);

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
    match(CHTLParser::IDENTIFIER);
   
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

tree::TerminalNode* CHTLParser::ConfigValueContext::STRING_LITERAL() {
  return getToken(CHTLParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CHTLParser::ConfigValueContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}

tree::TerminalNode* CHTLParser::ConfigValueContext::BOOLEAN() {
  return getToken(CHTLParser::BOOLEAN, 0);
}

CHTLParser::ConfigValueArrayContext* CHTLParser::ConfigValueContext::configValueArray() {
  return getRuleContext<CHTLParser::ConfigValueArrayContext>(0);
}


size_t CHTLParser::ConfigValueContext::getRuleIndex() const {
  return CHTLParser::RuleConfigValue;
}

void CHTLParser::ConfigValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigValue(this);
}

void CHTLParser::ConfigValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigValue(this);
}

CHTLParser::ConfigValueContext* CHTLParser::configValue() {
  ConfigValueContext *_localctx = _tracker.createInstance<ConfigValueContext>(_ctx, getState());
  enterRule(_localctx, 10, CHTLParser::RuleConfigValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(198);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(194);
        match(CHTLParser::STRING_LITERAL);
        break;
      }

      case CHTLParser::NUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(195);
        match(CHTLParser::NUMBER);
        break;
      }

      case CHTLParser::BOOLEAN: {
        enterOuterAlt(_localctx, 3);
        setState(196);
        match(CHTLParser::BOOLEAN);
        break;
      }

      case CHTLParser::T__6: {
        enterOuterAlt(_localctx, 4);
        setState(197);
        configValueArray();
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

//----------------- ConfigValueArrayContext ------------------------------------------------------------------

CHTLParser::ConfigValueArrayContext::ConfigValueArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ConfigArrayItemContext *> CHTLParser::ConfigValueArrayContext::configArrayItem() {
  return getRuleContexts<CHTLParser::ConfigArrayItemContext>();
}

CHTLParser::ConfigArrayItemContext* CHTLParser::ConfigValueArrayContext::configArrayItem(size_t i) {
  return getRuleContext<CHTLParser::ConfigArrayItemContext>(i);
}


size_t CHTLParser::ConfigValueArrayContext::getRuleIndex() const {
  return CHTLParser::RuleConfigValueArray;
}

void CHTLParser::ConfigValueArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigValueArray(this);
}

void CHTLParser::ConfigValueArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigValueArray(this);
}

CHTLParser::ConfigValueArrayContext* CHTLParser::configValueArray() {
  ConfigValueArrayContext *_localctx = _tracker.createInstance<ConfigValueArrayContext>(_ctx, getState());
  enterRule(_localctx, 12, CHTLParser::RuleConfigValueArray);
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
    setState(200);
    match(CHTLParser::T__6);
    setState(201);
    configArrayItem();
    setState(206);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(202);
      match(CHTLParser::T__7);
      setState(203);
      configArrayItem();
      setState(208);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(209);
    match(CHTLParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConfigArrayItemContext ------------------------------------------------------------------

CHTLParser::ConfigArrayItemContext::ConfigArrayItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ConfigArrayItemContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::ConfigArrayItemContext::STRING_LITERAL() {
  return getToken(CHTLParser::STRING_LITERAL, 0);
}


size_t CHTLParser::ConfigArrayItemContext::getRuleIndex() const {
  return CHTLParser::RuleConfigArrayItem;
}

void CHTLParser::ConfigArrayItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigArrayItem(this);
}

void CHTLParser::ConfigArrayItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigArrayItem(this);
}

CHTLParser::ConfigArrayItemContext* CHTLParser::configArrayItem() {
  ConfigArrayItemContext *_localctx = _tracker.createInstance<ConfigArrayItemContext>(_ctx, getState());
  enterRule(_localctx, 14, CHTLParser::RuleConfigArrayItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(214);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__9: {
        enterOuterAlt(_localctx, 1);
        setState(211);
        match(CHTLParser::T__9);
        setState(212);
        match(CHTLParser::IDENTIFIER);
        break;
      }

      case CHTLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(213);
        match(CHTLParser::STRING_LITERAL);
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

//----------------- NameConfigItemContext ------------------------------------------------------------------

CHTLParser::NameConfigItemContext::NameConfigItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::NameConfigItemContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::ConfigValueContext* CHTLParser::NameConfigItemContext::configValue() {
  return getRuleContext<CHTLParser::ConfigValueContext>(0);
}

CHTLParser::ConfigValueArrayContext* CHTLParser::NameConfigItemContext::configValueArray() {
  return getRuleContext<CHTLParser::ConfigValueArrayContext>(0);
}


size_t CHTLParser::NameConfigItemContext::getRuleIndex() const {
  return CHTLParser::RuleNameConfigItem;
}

void CHTLParser::NameConfigItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNameConfigItem(this);
}

void CHTLParser::NameConfigItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNameConfigItem(this);
}

CHTLParser::NameConfigItemContext* CHTLParser::nameConfigItem() {
  NameConfigItemContext *_localctx = _tracker.createInstance<NameConfigItemContext>(_ctx, getState());
  enterRule(_localctx, 16, CHTLParser::RuleNameConfigItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
    match(CHTLParser::IDENTIFIER);
    setState(217);
    match(CHTLParser::T__3);
    setState(220);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(218);
      configValue();
      break;
    }

    case 2: {
      setState(219);
      configValueArray();
      break;
    }

    default:
      break;
    }
    setState(222);
    match(CHTLParser::T__4);
   
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

tree::TerminalNode* CHTLParser::NamespaceDeclarationContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::NamespaceBodyContext* CHTLParser::NamespaceDeclarationContext::namespaceBody() {
  return getRuleContext<CHTLParser::NamespaceBodyContext>(0);
}


size_t CHTLParser::NamespaceDeclarationContext::getRuleIndex() const {
  return CHTLParser::RuleNamespaceDeclaration;
}

void CHTLParser::NamespaceDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespaceDeclaration(this);
}

void CHTLParser::NamespaceDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespaceDeclaration(this);
}

CHTLParser::NamespaceDeclarationContext* CHTLParser::namespaceDeclaration() {
  NamespaceDeclarationContext *_localctx = _tracker.createInstance<NamespaceDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 18, CHTLParser::RuleNamespaceDeclaration);
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
    match(CHTLParser::T__10);
    setState(225);
    match(CHTLParser::IDENTIFIER);
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__1) {
      setState(226);
      namespaceBody();
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

std::vector<CHTLParser::NamespaceContentContext *> CHTLParser::NamespaceBodyContext::namespaceContent() {
  return getRuleContexts<CHTLParser::NamespaceContentContext>();
}

CHTLParser::NamespaceContentContext* CHTLParser::NamespaceBodyContext::namespaceContent(size_t i) {
  return getRuleContext<CHTLParser::NamespaceContentContext>(i);
}


size_t CHTLParser::NamespaceBodyContext::getRuleIndex() const {
  return CHTLParser::RuleNamespaceBody;
}

void CHTLParser::NamespaceBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespaceBody(this);
}

void CHTLParser::NamespaceBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespaceBody(this);
}

CHTLParser::NamespaceBodyContext* CHTLParser::namespaceBody() {
  NamespaceBodyContext *_localctx = _tracker.createInstance<NamespaceBodyContext>(_ctx, getState());
  enterRule(_localctx, 20, CHTLParser::RuleNamespaceBody);
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
    setState(229);
    match(CHTLParser::T__1);
    setState(233);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17592187619328) != 0)) {
      setState(230);
      namespaceContent();
      setState(235);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(236);
    match(CHTLParser::T__2);
   
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

CHTLParser::ExceptConstraintContext* CHTLParser::NamespaceContentContext::exceptConstraint() {
  return getRuleContext<CHTLParser::ExceptConstraintContext>(0);
}


size_t CHTLParser::NamespaceContentContext::getRuleIndex() const {
  return CHTLParser::RuleNamespaceContent;
}

void CHTLParser::NamespaceContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespaceContent(this);
}

void CHTLParser::NamespaceContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespaceContent(this);
}

CHTLParser::NamespaceContentContext* CHTLParser::namespaceContent() {
  NamespaceContentContext *_localctx = _tracker.createInstance<NamespaceContentContext>(_ctx, getState());
  enterRule(_localctx, 22, CHTLParser::RuleNamespaceContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__10: {
        enterOuterAlt(_localctx, 1);
        setState(238);
        namespaceDeclaration();
        break;
      }

      case CHTLParser::T__19: {
        enterOuterAlt(_localctx, 2);
        setState(239);
        templateDeclaration();
        break;
      }

      case CHTLParser::T__18: {
        enterOuterAlt(_localctx, 3);
        setState(240);
        customDeclaration();
        break;
      }

      case CHTLParser::T__43: {
        enterOuterAlt(_localctx, 4);
        setState(241);
        exceptConstraint();
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

//----------------- ImportStatementContext ------------------------------------------------------------------

CHTLParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ImportTypeContext* CHTLParser::ImportStatementContext::importType() {
  return getRuleContext<CHTLParser::ImportTypeContext>(0);
}

CHTLParser::ImportPathContext* CHTLParser::ImportStatementContext::importPath() {
  return getRuleContext<CHTLParser::ImportPathContext>(0);
}

tree::TerminalNode* CHTLParser::ImportStatementContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ImportStatementContext::getRuleIndex() const {
  return CHTLParser::RuleImportStatement;
}

void CHTLParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void CHTLParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}

CHTLParser::ImportStatementContext* CHTLParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, CHTLParser::RuleImportStatement);
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
    setState(244);
    match(CHTLParser::T__11);
    setState(245);
    importType();
    setState(246);
    match(CHTLParser::T__12);
    setState(247);
    importPath();
    setState(250);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__13) {
      setState(248);
      match(CHTLParser::T__13);
      setState(249);
      match(CHTLParser::IDENTIFIER);
    }
    setState(253);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__4) {
      setState(252);
      match(CHTLParser::T__4);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportTypeContext ------------------------------------------------------------------

CHTLParser::ImportTypeContext::ImportTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CustomTypeContext* CHTLParser::ImportTypeContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

tree::TerminalNode* CHTLParser::ImportTypeContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::TemplateTypeContext* CHTLParser::ImportTypeContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}


size_t CHTLParser::ImportTypeContext::getRuleIndex() const {
  return CHTLParser::RuleImportType;
}

void CHTLParser::ImportTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportType(this);
}

void CHTLParser::ImportTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportType(this);
}

CHTLParser::ImportTypeContext* CHTLParser::importType() {
  ImportTypeContext *_localctx = _tracker.createInstance<ImportTypeContext>(_ctx, getState());
  enterRule(_localctx, 26, CHTLParser::RuleImportType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(267);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__14: {
        enterOuterAlt(_localctx, 1);
        setState(255);
        match(CHTLParser::T__14);
        break;
      }

      case CHTLParser::T__15: {
        enterOuterAlt(_localctx, 2);
        setState(256);
        match(CHTLParser::T__15);
        break;
      }

      case CHTLParser::T__16: {
        enterOuterAlt(_localctx, 3);
        setState(257);
        match(CHTLParser::T__16);
        break;
      }

      case CHTLParser::T__17: {
        enterOuterAlt(_localctx, 4);
        setState(258);
        match(CHTLParser::T__17);
        break;
      }

      case CHTLParser::T__18: {
        enterOuterAlt(_localctx, 5);
        setState(259);
        match(CHTLParser::T__18);
        setState(260);
        customType();
        setState(261);
        match(CHTLParser::IDENTIFIER);
        break;
      }

      case CHTLParser::T__19: {
        enterOuterAlt(_localctx, 6);
        setState(263);
        match(CHTLParser::T__19);
        setState(264);
        templateType();
        setState(265);
        match(CHTLParser::IDENTIFIER);
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

//----------------- ImportPathContext ------------------------------------------------------------------

CHTLParser::ImportPathContext::ImportPathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportPathContext::STRING_LITERAL() {
  return getToken(CHTLParser::STRING_LITERAL, 0);
}

CHTLParser::DottedPathContext* CHTLParser::ImportPathContext::dottedPath() {
  return getRuleContext<CHTLParser::DottedPathContext>(0);
}


size_t CHTLParser::ImportPathContext::getRuleIndex() const {
  return CHTLParser::RuleImportPath;
}

void CHTLParser::ImportPathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportPath(this);
}

void CHTLParser::ImportPathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportPath(this);
}

CHTLParser::ImportPathContext* CHTLParser::importPath() {
  ImportPathContext *_localctx = _tracker.createInstance<ImportPathContext>(_ctx, getState());
  enterRule(_localctx, 28, CHTLParser::RuleImportPath);

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
    switch (_input->LA(1)) {
      case CHTLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(269);
        match(CHTLParser::STRING_LITERAL);
        break;
      }

      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(270);
        dottedPath();
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

//----------------- DottedPathContext ------------------------------------------------------------------

CHTLParser::DottedPathContext::DottedPathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::DottedPathContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::DottedPathContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}


size_t CHTLParser::DottedPathContext::getRuleIndex() const {
  return CHTLParser::RuleDottedPath;
}

void CHTLParser::DottedPathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDottedPath(this);
}

void CHTLParser::DottedPathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDottedPath(this);
}

CHTLParser::DottedPathContext* CHTLParser::dottedPath() {
  DottedPathContext *_localctx = _tracker.createInstance<DottedPathContext>(_ctx, getState());
  enterRule(_localctx, 30, CHTLParser::RuleDottedPath);
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
    setState(273);
    match(CHTLParser::IDENTIFIER);
    setState(278);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__20) {
      setState(274);
      match(CHTLParser::T__20);
      setState(275);
      match(CHTLParser::IDENTIFIER);
      setState(280);
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

CHTLParser::TemplateTypeContext* CHTLParser::TemplateDeclarationContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

tree::TerminalNode* CHTLParser::TemplateDeclarationContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::TemplateBodyContext* CHTLParser::TemplateDeclarationContext::templateBody() {
  return getRuleContext<CHTLParser::TemplateBodyContext>(0);
}


size_t CHTLParser::TemplateDeclarationContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateDeclaration;
}

void CHTLParser::TemplateDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateDeclaration(this);
}

void CHTLParser::TemplateDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateDeclaration(this);
}

CHTLParser::TemplateDeclarationContext* CHTLParser::templateDeclaration() {
  TemplateDeclarationContext *_localctx = _tracker.createInstance<TemplateDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 32, CHTLParser::RuleTemplateDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    match(CHTLParser::T__19);
    setState(282);
    templateType();
    setState(283);
    match(CHTLParser::IDENTIFIER);
    setState(284);
    templateBody();
   
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


size_t CHTLParser::TemplateTypeContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateType;
}

void CHTLParser::TemplateTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateType(this);
}

void CHTLParser::TemplateTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateType(this);
}

CHTLParser::TemplateTypeContext* CHTLParser::templateType() {
  TemplateTypeContext *_localctx = _tracker.createInstance<TemplateTypeContext>(_ctx, getState());
  enterRule(_localctx, 34, CHTLParser::RuleTemplateType);
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
    setState(286);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 12648448) != 0))) {
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

//----------------- TemplateBodyContext ------------------------------------------------------------------

CHTLParser::TemplateBodyContext::TemplateBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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

void CHTLParser::TemplateBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateBody(this);
}

void CHTLParser::TemplateBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateBody(this);
}

CHTLParser::TemplateBodyContext* CHTLParser::templateBody() {
  TemplateBodyContext *_localctx = _tracker.createInstance<TemplateBodyContext>(_ctx, getState());
  enterRule(_localctx, 36, CHTLParser::RuleTemplateBody);
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
    setState(288);
    match(CHTLParser::T__1);
    setState(292);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503719915880448) != 0)) {
      setState(289);
      templateContent();
      setState(294);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(295);
    match(CHTLParser::T__2);
   
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

CHTLParser::StylePropertyContext* CHTLParser::TemplateContentContext::styleProperty() {
  return getRuleContext<CHTLParser::StylePropertyContext>(0);
}

CHTLParser::HtmlElementContext* CHTLParser::TemplateContentContext::htmlElement() {
  return getRuleContext<CHTLParser::HtmlElementContext>(0);
}

CHTLParser::TemplateInheritanceContext* CHTLParser::TemplateContentContext::templateInheritance() {
  return getRuleContext<CHTLParser::TemplateInheritanceContext>(0);
}

CHTLParser::VariableDefinitionContext* CHTLParser::TemplateContentContext::variableDefinition() {
  return getRuleContext<CHTLParser::VariableDefinitionContext>(0);
}


size_t CHTLParser::TemplateContentContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateContent;
}

void CHTLParser::TemplateContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateContent(this);
}

void CHTLParser::TemplateContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateContent(this);
}

CHTLParser::TemplateContentContext* CHTLParser::templateContent() {
  TemplateContentContext *_localctx = _tracker.createInstance<TemplateContentContext>(_ctx, getState());
  enterRule(_localctx, 38, CHTLParser::RuleTemplateContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(301);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(297);
      styleProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(298);
      htmlElement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(299);
      templateInheritance();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(300);
      variableDefinition();
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

//----------------- TemplateInheritanceContext ------------------------------------------------------------------

CHTLParser::TemplateInheritanceContext::TemplateInheritanceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::TemplateTypeContext* CHTLParser::TemplateInheritanceContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

tree::TerminalNode* CHTLParser::TemplateInheritanceContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::TemplateInheritanceContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateInheritance;
}

void CHTLParser::TemplateInheritanceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateInheritance(this);
}

void CHTLParser::TemplateInheritanceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateInheritance(this);
}

CHTLParser::TemplateInheritanceContext* CHTLParser::templateInheritance() {
  TemplateInheritanceContext *_localctx = _tracker.createInstance<TemplateInheritanceContext>(_ctx, getState());
  enterRule(_localctx, 40, CHTLParser::RuleTemplateInheritance);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(312);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__15:
      case CHTLParser::T__21:
      case CHTLParser::T__22: {
        enterOuterAlt(_localctx, 1);
        setState(303);
        templateType();
        setState(304);
        match(CHTLParser::IDENTIFIER);
        setState(305);
        match(CHTLParser::T__4);
        break;
      }

      case CHTLParser::T__23: {
        enterOuterAlt(_localctx, 2);
        setState(307);
        match(CHTLParser::T__23);
        setState(308);
        templateType();
        setState(309);
        match(CHTLParser::IDENTIFIER);
        setState(310);
        match(CHTLParser::T__4);
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

//----------------- CustomDeclarationContext ------------------------------------------------------------------

CHTLParser::CustomDeclarationContext::CustomDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CustomTypeContext* CHTLParser::CustomDeclarationContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

tree::TerminalNode* CHTLParser::CustomDeclarationContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::CustomBodyContext* CHTLParser::CustomDeclarationContext::customBody() {
  return getRuleContext<CHTLParser::CustomBodyContext>(0);
}


size_t CHTLParser::CustomDeclarationContext::getRuleIndex() const {
  return CHTLParser::RuleCustomDeclaration;
}

void CHTLParser::CustomDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomDeclaration(this);
}

void CHTLParser::CustomDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomDeclaration(this);
}

CHTLParser::CustomDeclarationContext* CHTLParser::customDeclaration() {
  CustomDeclarationContext *_localctx = _tracker.createInstance<CustomDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 42, CHTLParser::RuleCustomDeclaration);

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
    match(CHTLParser::T__18);
    setState(315);
    customType();
    setState(316);
    match(CHTLParser::IDENTIFIER);
    setState(317);
    customBody();
   
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


size_t CHTLParser::CustomTypeContext::getRuleIndex() const {
  return CHTLParser::RuleCustomType;
}

void CHTLParser::CustomTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomType(this);
}

void CHTLParser::CustomTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomType(this);
}

CHTLParser::CustomTypeContext* CHTLParser::customType() {
  CustomTypeContext *_localctx = _tracker.createInstance<CustomTypeContext>(_ctx, getState());
  enterRule(_localctx, 44, CHTLParser::RuleCustomType);
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
    setState(319);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 12648448) != 0))) {
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

//----------------- CustomBodyContext ------------------------------------------------------------------

CHTLParser::CustomBodyContext::CustomBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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

void CHTLParser::CustomBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomBody(this);
}

void CHTLParser::CustomBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomBody(this);
}

CHTLParser::CustomBodyContext* CHTLParser::customBody() {
  CustomBodyContext *_localctx = _tracker.createInstance<CustomBodyContext>(_ctx, getState());
  enterRule(_localctx, 46, CHTLParser::RuleCustomBody);
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
    setState(321);
    match(CHTLParser::T__1);
    setState(325);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503719999766528) != 0)) {
      setState(322);
      customContent();
      setState(327);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(328);
    match(CHTLParser::T__2);
   
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

CHTLParser::StylePropertyContext* CHTLParser::CustomContentContext::styleProperty() {
  return getRuleContext<CHTLParser::StylePropertyContext>(0);
}

CHTLParser::HtmlElementContext* CHTLParser::CustomContentContext::htmlElement() {
  return getRuleContext<CHTLParser::HtmlElementContext>(0);
}

CHTLParser::CustomInheritanceContext* CHTLParser::CustomContentContext::customInheritance() {
  return getRuleContext<CHTLParser::CustomInheritanceContext>(0);
}

CHTLParser::VariableDefinitionContext* CHTLParser::CustomContentContext::variableDefinition() {
  return getRuleContext<CHTLParser::VariableDefinitionContext>(0);
}

CHTLParser::DeleteStatementContext* CHTLParser::CustomContentContext::deleteStatement() {
  return getRuleContext<CHTLParser::DeleteStatementContext>(0);
}

CHTLParser::InsertStatementContext* CHTLParser::CustomContentContext::insertStatement() {
  return getRuleContext<CHTLParser::InsertStatementContext>(0);
}


size_t CHTLParser::CustomContentContext::getRuleIndex() const {
  return CHTLParser::RuleCustomContent;
}

void CHTLParser::CustomContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomContent(this);
}

void CHTLParser::CustomContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomContent(this);
}

CHTLParser::CustomContentContext* CHTLParser::customContent() {
  CustomContentContext *_localctx = _tracker.createInstance<CustomContentContext>(_ctx, getState());
  enterRule(_localctx, 48, CHTLParser::RuleCustomContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(336);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(330);
      styleProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(331);
      htmlElement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(332);
      customInheritance();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(333);
      variableDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(334);
      deleteStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(335);
      insertStatement();
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

//----------------- CustomInheritanceContext ------------------------------------------------------------------

CHTLParser::CustomInheritanceContext::CustomInheritanceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CustomTypeContext* CHTLParser::CustomInheritanceContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

tree::TerminalNode* CHTLParser::CustomInheritanceContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::CustomSpecializationContext* CHTLParser::CustomInheritanceContext::customSpecialization() {
  return getRuleContext<CHTLParser::CustomSpecializationContext>(0);
}

CHTLParser::TemplateTypeContext* CHTLParser::CustomInheritanceContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}


size_t CHTLParser::CustomInheritanceContext::getRuleIndex() const {
  return CHTLParser::RuleCustomInheritance;
}

void CHTLParser::CustomInheritanceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomInheritance(this);
}

void CHTLParser::CustomInheritanceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomInheritance(this);
}

CHTLParser::CustomInheritanceContext* CHTLParser::customInheritance() {
  CustomInheritanceContext *_localctx = _tracker.createInstance<CustomInheritanceContext>(_ctx, getState());
  enterRule(_localctx, 50, CHTLParser::RuleCustomInheritance);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(354);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(338);
      customType();
      setState(339);
      match(CHTLParser::IDENTIFIER);
      setState(341);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(340);
        customSpecialization();
      }
      setState(344);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__4) {
        setState(343);
        match(CHTLParser::T__4);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(346);
      templateType();
      setState(347);
      match(CHTLParser::IDENTIFIER);
      setState(349);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(348);
        customSpecialization();
      }
      setState(352);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__4) {
        setState(351);
        match(CHTLParser::T__4);
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

//----------------- CustomSpecializationContext ------------------------------------------------------------------

CHTLParser::CustomSpecializationContext::CustomSpecializationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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

void CHTLParser::CustomSpecializationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomSpecialization(this);
}

void CHTLParser::CustomSpecializationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomSpecialization(this);
}

CHTLParser::CustomSpecializationContext* CHTLParser::customSpecialization() {
  CustomSpecializationContext *_localctx = _tracker.createInstance<CustomSpecializationContext>(_ctx, getState());
  enterRule(_localctx, 52, CHTLParser::RuleCustomSpecialization);
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
    setState(356);
    match(CHTLParser::T__1);
    setState(360);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__24

    || _la == CHTLParser::IDENTIFIER) {
      setState(357);
      specializationContent();
      setState(362);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(363);
    match(CHTLParser::T__2);
   
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

CHTLParser::StylePropertyContext* CHTLParser::SpecializationContentContext::styleProperty() {
  return getRuleContext<CHTLParser::StylePropertyContext>(0);
}

CHTLParser::DeleteStatementContext* CHTLParser::SpecializationContentContext::deleteStatement() {
  return getRuleContext<CHTLParser::DeleteStatementContext>(0);
}

CHTLParser::VariableAssignmentContext* CHTLParser::SpecializationContentContext::variableAssignment() {
  return getRuleContext<CHTLParser::VariableAssignmentContext>(0);
}


size_t CHTLParser::SpecializationContentContext::getRuleIndex() const {
  return CHTLParser::RuleSpecializationContent;
}

void CHTLParser::SpecializationContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSpecializationContent(this);
}

void CHTLParser::SpecializationContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSpecializationContent(this);
}

CHTLParser::SpecializationContentContext* CHTLParser::specializationContent() {
  SpecializationContentContext *_localctx = _tracker.createInstance<SpecializationContentContext>(_ctx, getState());
  enterRule(_localctx, 54, CHTLParser::RuleSpecializationContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(368);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(365);
      styleProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(366);
      deleteStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(367);
      variableAssignment();
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

//----------------- DeleteStatementContext ------------------------------------------------------------------

CHTLParser::DeleteStatementContext::DeleteStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::DeleteTargetContext *> CHTLParser::DeleteStatementContext::deleteTarget() {
  return getRuleContexts<CHTLParser::DeleteTargetContext>();
}

CHTLParser::DeleteTargetContext* CHTLParser::DeleteStatementContext::deleteTarget(size_t i) {
  return getRuleContext<CHTLParser::DeleteTargetContext>(i);
}


size_t CHTLParser::DeleteStatementContext::getRuleIndex() const {
  return CHTLParser::RuleDeleteStatement;
}

void CHTLParser::DeleteStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeleteStatement(this);
}

void CHTLParser::DeleteStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeleteStatement(this);
}

CHTLParser::DeleteStatementContext* CHTLParser::deleteStatement() {
  DeleteStatementContext *_localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, CHTLParser::RuleDeleteStatement);
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
    setState(370);
    match(CHTLParser::T__24);
    setState(371);
    deleteTarget();
    setState(376);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(372);
      match(CHTLParser::T__7);
      setState(373);
      deleteTarget();
      setState(378);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(379);
    match(CHTLParser::T__4);
   
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

tree::TerminalNode* CHTLParser::DeleteTargetContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::DeleteTargetContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}

CHTLParser::CustomTypeContext* CHTLParser::DeleteTargetContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

CHTLParser::TemplateTypeContext* CHTLParser::DeleteTargetContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}


size_t CHTLParser::DeleteTargetContext::getRuleIndex() const {
  return CHTLParser::RuleDeleteTarget;
}

void CHTLParser::DeleteTargetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeleteTarget(this);
}

void CHTLParser::DeleteTargetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeleteTarget(this);
}

CHTLParser::DeleteTargetContext* CHTLParser::deleteTarget() {
  DeleteTargetContext *_localctx = _tracker.createInstance<DeleteTargetContext>(_ctx, getState());
  enterRule(_localctx, 58, CHTLParser::RuleDeleteTarget);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(381);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(382);
      match(CHTLParser::IDENTIFIER);
      setState(383);
      match(CHTLParser::T__6);
      setState(384);
      match(CHTLParser::NUMBER);
      setState(385);
      match(CHTLParser::T__8);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(386);
      customType();
      setState(387);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(389);
      templateType();
      setState(390);
      match(CHTLParser::IDENTIFIER);
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

//----------------- InsertStatementContext ------------------------------------------------------------------

CHTLParser::InsertStatementContext::InsertStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::InsertPositionContext* CHTLParser::InsertStatementContext::insertPosition() {
  return getRuleContext<CHTLParser::InsertPositionContext>(0);
}

CHTLParser::ElementSelectorContext* CHTLParser::InsertStatementContext::elementSelector() {
  return getRuleContext<CHTLParser::ElementSelectorContext>(0);
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

void CHTLParser::InsertStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsertStatement(this);
}

void CHTLParser::InsertStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsertStatement(this);
}

CHTLParser::InsertStatementContext* CHTLParser::insertStatement() {
  InsertStatementContext *_localctx = _tracker.createInstance<InsertStatementContext>(_ctx, getState());
  enterRule(_localctx, 60, CHTLParser::RuleInsertStatement);
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
    setState(394);
    match(CHTLParser::T__25);
    setState(395);
    insertPosition();
    setState(396);
    elementSelector();
    setState(397);
    match(CHTLParser::T__1);
    setState(401);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503728490610688) != 0)) {
      setState(398);
      insertContent();
      setState(403);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(404);
    match(CHTLParser::T__2);
   
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


size_t CHTLParser::InsertPositionContext::getRuleIndex() const {
  return CHTLParser::RuleInsertPosition;
}

void CHTLParser::InsertPositionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsertPosition(this);
}

void CHTLParser::InsertPositionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsertPosition(this);
}

CHTLParser::InsertPositionContext* CHTLParser::insertPosition() {
  InsertPositionContext *_localctx = _tracker.createInstance<InsertPositionContext>(_ctx, getState());
  enterRule(_localctx, 62, CHTLParser::RuleInsertPosition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(413);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(406);
      match(CHTLParser::T__26);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(407);
      match(CHTLParser::T__27);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(408);
      match(CHTLParser::T__28);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(409);
      match(CHTLParser::T__29);
      setState(410);
      match(CHTLParser::T__30);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(411);
      match(CHTLParser::T__29);
      setState(412);
      match(CHTLParser::T__31);
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

//----------------- ElementSelectorContext ------------------------------------------------------------------

CHTLParser::ElementSelectorContext::ElementSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ElementSelectorContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::ElementSelectorContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}


size_t CHTLParser::ElementSelectorContext::getRuleIndex() const {
  return CHTLParser::RuleElementSelector;
}

void CHTLParser::ElementSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementSelector(this);
}

void CHTLParser::ElementSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementSelector(this);
}

CHTLParser::ElementSelectorContext* CHTLParser::elementSelector() {
  ElementSelectorContext *_localctx = _tracker.createInstance<ElementSelectorContext>(_ctx, getState());
  enterRule(_localctx, 64, CHTLParser::RuleElementSelector);
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
    match(CHTLParser::IDENTIFIER);
    setState(419);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__6) {
      setState(416);
      match(CHTLParser::T__6);
      setState(417);
      match(CHTLParser::NUMBER);
      setState(418);
      match(CHTLParser::T__8);
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

CHTLParser::HtmlElementContext* CHTLParser::InsertContentContext::htmlElement() {
  return getRuleContext<CHTLParser::HtmlElementContext>(0);
}

CHTLParser::ElementUsageContext* CHTLParser::InsertContentContext::elementUsage() {
  return getRuleContext<CHTLParser::ElementUsageContext>(0);
}


size_t CHTLParser::InsertContentContext::getRuleIndex() const {
  return CHTLParser::RuleInsertContent;
}

void CHTLParser::InsertContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsertContent(this);
}

void CHTLParser::InsertContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsertContent(this);
}

CHTLParser::InsertContentContext* CHTLParser::insertContent() {
  InsertContentContext *_localctx = _tracker.createInstance<InsertContentContext>(_ctx, getState());
  enterRule(_localctx, 66, CHTLParser::RuleInsertContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(423);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__33:
      case CHTLParser::T__34:
      case CHTLParser::T__35:
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(421);
        htmlElement();
        break;
      }

      case CHTLParser::T__15:
      case CHTLParser::T__18:
      case CHTLParser::T__19:
      case CHTLParser::T__21:
      case CHTLParser::T__22:
      case CHTLParser::T__32: {
        enterOuterAlt(_localctx, 2);
        setState(422);
        elementUsage();
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

//----------------- OriginBlockContext ------------------------------------------------------------------

CHTLParser::OriginBlockContext::OriginBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::OriginTypeContext* CHTLParser::OriginBlockContext::originType() {
  return getRuleContext<CHTLParser::OriginTypeContext>(0);
}

CHTLParser::OriginContentContext* CHTLParser::OriginBlockContext::originContent() {
  return getRuleContext<CHTLParser::OriginContentContext>(0);
}

tree::TerminalNode* CHTLParser::OriginBlockContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::OriginBlockContext::getRuleIndex() const {
  return CHTLParser::RuleOriginBlock;
}

void CHTLParser::OriginBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOriginBlock(this);
}

void CHTLParser::OriginBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOriginBlock(this);
}

CHTLParser::OriginBlockContext* CHTLParser::originBlock() {
  OriginBlockContext *_localctx = _tracker.createInstance<OriginBlockContext>(_ctx, getState());
  enterRule(_localctx, 68, CHTLParser::RuleOriginBlock);
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
    setState(425);
    match(CHTLParser::T__32);
    setState(426);
    originType();
    setState(428);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::IDENTIFIER) {
      setState(427);
      match(CHTLParser::IDENTIFIER);
    }
    setState(430);
    match(CHTLParser::T__1);
    setState(431);
    originContent();
    setState(432);
    match(CHTLParser::T__2);
   
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


size_t CHTLParser::OriginTypeContext::getRuleIndex() const {
  return CHTLParser::RuleOriginType;
}

void CHTLParser::OriginTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOriginType(this);
}

void CHTLParser::OriginTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOriginType(this);
}

CHTLParser::OriginTypeContext* CHTLParser::originType() {
  OriginTypeContext *_localctx = _tracker.createInstance<OriginTypeContext>(_ctx, getState());
  enterRule(_localctx, 70, CHTLParser::RuleOriginType);
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
    setState(434);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 229376) != 0))) {
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

//----------------- OriginContentContext ------------------------------------------------------------------

CHTLParser::OriginContentContext::OriginContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CHTLParser::OriginContentContext::getRuleIndex() const {
  return CHTLParser::RuleOriginContent;
}

void CHTLParser::OriginContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOriginContent(this);
}

void CHTLParser::OriginContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOriginContent(this);
}

CHTLParser::OriginContentContext* CHTLParser::originContent() {
  OriginContentContext *_localctx = _tracker.createInstance<OriginContentContext>(_ctx, getState());
  enterRule(_localctx, 72, CHTLParser::RuleOriginContent);
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
    setState(439);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 18014398509481974) != 0)) {
      setState(436);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == CHTLParser::T__2)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(441);
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

//----------------- HtmlElementContext ------------------------------------------------------------------

CHTLParser::HtmlElementContext::HtmlElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ElementNameContext* CHTLParser::HtmlElementContext::elementName() {
  return getRuleContext<CHTLParser::ElementNameContext>(0);
}

CHTLParser::ElementBodyContext* CHTLParser::HtmlElementContext::elementBody() {
  return getRuleContext<CHTLParser::ElementBodyContext>(0);
}

CHTLParser::ElementIndexAccessContext* CHTLParser::HtmlElementContext::elementIndexAccess() {
  return getRuleContext<CHTLParser::ElementIndexAccessContext>(0);
}


size_t CHTLParser::HtmlElementContext::getRuleIndex() const {
  return CHTLParser::RuleHtmlElement;
}

void CHTLParser::HtmlElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlElement(this);
}

void CHTLParser::HtmlElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlElement(this);
}

CHTLParser::HtmlElementContext* CHTLParser::htmlElement() {
  HtmlElementContext *_localctx = _tracker.createInstance<HtmlElementContext>(_ctx, getState());
  enterRule(_localctx, 74, CHTLParser::RuleHtmlElement);
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
    setState(442);
    elementName();
    setState(444);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__6) {
      setState(443);
      elementIndexAccess();
    }
    setState(446);
    elementBody();
   
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

void CHTLParser::ElementNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementName(this);
}

void CHTLParser::ElementNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementName(this);
}

CHTLParser::ElementNameContext* CHTLParser::elementName() {
  ElementNameContext *_localctx = _tracker.createInstance<ElementNameContext>(_ctx, getState());
  enterRule(_localctx, 76, CHTLParser::RuleElementName);
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
    setState(448);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503719886454784) != 0))) {
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

//----------------- ElementIndexAccessContext ------------------------------------------------------------------

CHTLParser::ElementIndexAccessContext::ElementIndexAccessContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ElementIndexAccessContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}


size_t CHTLParser::ElementIndexAccessContext::getRuleIndex() const {
  return CHTLParser::RuleElementIndexAccess;
}

void CHTLParser::ElementIndexAccessContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementIndexAccess(this);
}

void CHTLParser::ElementIndexAccessContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementIndexAccess(this);
}

CHTLParser::ElementIndexAccessContext* CHTLParser::elementIndexAccess() {
  ElementIndexAccessContext *_localctx = _tracker.createInstance<ElementIndexAccessContext>(_ctx, getState());
  enterRule(_localctx, 78, CHTLParser::RuleElementIndexAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(450);
    match(CHTLParser::T__6);
    setState(451);
    match(CHTLParser::NUMBER);
    setState(452);
    match(CHTLParser::T__8);
   
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

std::vector<CHTLParser::ElementContentContext *> CHTLParser::ElementBodyContext::elementContent() {
  return getRuleContexts<CHTLParser::ElementContentContext>();
}

CHTLParser::ElementContentContext* CHTLParser::ElementBodyContext::elementContent(size_t i) {
  return getRuleContext<CHTLParser::ElementContentContext>(i);
}


size_t CHTLParser::ElementBodyContext::getRuleIndex() const {
  return CHTLParser::RuleElementBody;
}

void CHTLParser::ElementBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementBody(this);
}

void CHTLParser::ElementBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementBody(this);
}

CHTLParser::ElementBodyContext* CHTLParser::elementBody() {
  ElementBodyContext *_localctx = _tracker.createInstance<ElementBodyContext>(_ctx, getState());
  enterRule(_localctx, 80, CHTLParser::RuleElementBody);
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
    setState(454);
    match(CHTLParser::T__1);
    setState(458);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8145311001804800) != 0)) {
      setState(455);
      elementContent();
      setState(460);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(461);
    match(CHTLParser::T__2);
   
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

CHTLParser::HtmlElementContext* CHTLParser::ElementContentContext::htmlElement() {
  return getRuleContext<CHTLParser::HtmlElementContext>(0);
}

CHTLParser::StyleBlockContext* CHTLParser::ElementContentContext::styleBlock() {
  return getRuleContext<CHTLParser::StyleBlockContext>(0);
}

CHTLParser::ScriptBlockContext* CHTLParser::ElementContentContext::scriptBlock() {
  return getRuleContext<CHTLParser::ScriptBlockContext>(0);
}

CHTLParser::TextContentContext* CHTLParser::ElementContentContext::textContent() {
  return getRuleContext<CHTLParser::TextContentContext>(0);
}

CHTLParser::ElementUsageContext* CHTLParser::ElementContentContext::elementUsage() {
  return getRuleContext<CHTLParser::ElementUsageContext>(0);
}

CHTLParser::ExceptConstraintContext* CHTLParser::ElementContentContext::exceptConstraint() {
  return getRuleContext<CHTLParser::ExceptConstraintContext>(0);
}

CHTLParser::CommentContext* CHTLParser::ElementContentContext::comment() {
  return getRuleContext<CHTLParser::CommentContext>(0);
}


size_t CHTLParser::ElementContentContext::getRuleIndex() const {
  return CHTLParser::RuleElementContent;
}

void CHTLParser::ElementContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementContent(this);
}

void CHTLParser::ElementContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementContent(this);
}

CHTLParser::ElementContentContext* CHTLParser::elementContent() {
  ElementContentContext *_localctx = _tracker.createInstance<ElementContentContext>(_ctx, getState());
  enterRule(_localctx, 82, CHTLParser::RuleElementContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(471);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(463);
      attribute();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(464);
      htmlElement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(465);
      styleBlock();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(466);
      scriptBlock();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(467);
      textContent();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(468);
      elementUsage();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(469);
      exceptConstraint();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(470);
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


size_t CHTLParser::AttributeContext::getRuleIndex() const {
  return CHTLParser::RuleAttribute;
}

void CHTLParser::AttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttribute(this);
}

void CHTLParser::AttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttribute(this);
}

CHTLParser::AttributeContext* CHTLParser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 84, CHTLParser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(483);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(473);
      attributeName();
      setState(474);
      match(CHTLParser::T__36);
      setState(475);
      attributeValue();
      setState(476);
      match(CHTLParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(478);
      attributeName();
      setState(479);
      match(CHTLParser::T__3);
      setState(480);
      attributeValue();
      setState(481);
      match(CHTLParser::T__4);
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

void CHTLParser::AttributeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributeName(this);
}

void CHTLParser::AttributeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributeName(this);
}

CHTLParser::AttributeNameContext* CHTLParser::attributeName() {
  AttributeNameContext *_localctx = _tracker.createInstance<AttributeNameContext>(_ctx, getState());
  enterRule(_localctx, 86, CHTLParser::RuleAttributeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(485);
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

tree::TerminalNode* CHTLParser::AttributeValueContext::STRING_LITERAL() {
  return getToken(CHTLParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CHTLParser::AttributeValueContext::UNQUOTED_LITERAL() {
  return getToken(CHTLParser::UNQUOTED_LITERAL, 0);
}

CHTLParser::VariableUsageContext* CHTLParser::AttributeValueContext::variableUsage() {
  return getRuleContext<CHTLParser::VariableUsageContext>(0);
}


size_t CHTLParser::AttributeValueContext::getRuleIndex() const {
  return CHTLParser::RuleAttributeValue;
}

void CHTLParser::AttributeValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributeValue(this);
}

void CHTLParser::AttributeValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributeValue(this);
}

CHTLParser::AttributeValueContext* CHTLParser::attributeValue() {
  AttributeValueContext *_localctx = _tracker.createInstance<AttributeValueContext>(_ctx, getState());
  enterRule(_localctx, 88, CHTLParser::RuleAttributeValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(490);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(487);
        match(CHTLParser::STRING_LITERAL);
        break;
      }

      case CHTLParser::UNQUOTED_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(488);
        match(CHTLParser::UNQUOTED_LITERAL);
        break;
      }

      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(489);
        variableUsage();
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

//----------------- TextContentContext ------------------------------------------------------------------

CHTLParser::TextContentContext::TextContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TextContentContext::STRING_LITERAL() {
  return getToken(CHTLParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CHTLParser::TextContentContext::UNQUOTED_LITERAL() {
  return getToken(CHTLParser::UNQUOTED_LITERAL, 0);
}


size_t CHTLParser::TextContentContext::getRuleIndex() const {
  return CHTLParser::RuleTextContent;
}

void CHTLParser::TextContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextContent(this);
}

void CHTLParser::TextContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextContent(this);
}

CHTLParser::TextContentContext* CHTLParser::textContent() {
  TextContentContext *_localctx = _tracker.createInstance<TextContentContext>(_ctx, getState());
  enterRule(_localctx, 90, CHTLParser::RuleTextContent);
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
    setState(492);
    _la = _input->LA(1);
    if (!(_la == CHTLParser::STRING_LITERAL

    || _la == CHTLParser::UNQUOTED_LITERAL)) {
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

//----------------- StyleBlockContext ------------------------------------------------------------------

CHTLParser::StyleBlockContext::StyleBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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

void CHTLParser::StyleBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyleBlock(this);
}

void CHTLParser::StyleBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyleBlock(this);
}

CHTLParser::StyleBlockContext* CHTLParser::styleBlock() {
  StyleBlockContext *_localctx = _tracker.createInstance<StyleBlockContext>(_ctx, getState());
  enterRule(_localctx, 92, CHTLParser::RuleStyleBlock);
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
    match(CHTLParser::T__34);
    setState(495);
    match(CHTLParser::T__1);
    setState(499);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4505248909557760) != 0)) {
      setState(496);
      styleContent();
      setState(501);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(502);
    match(CHTLParser::T__2);
   
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

CHTLParser::StylePropertyContext* CHTLParser::StyleContentContext::styleProperty() {
  return getRuleContext<CHTLParser::StylePropertyContext>(0);
}

CHTLParser::CssSelectorContext* CHTLParser::StyleContentContext::cssSelector() {
  return getRuleContext<CHTLParser::CssSelectorContext>(0);
}

std::vector<CHTLParser::StyleContentContext *> CHTLParser::StyleContentContext::styleContent() {
  return getRuleContexts<CHTLParser::StyleContentContext>();
}

CHTLParser::StyleContentContext* CHTLParser::StyleContentContext::styleContent(size_t i) {
  return getRuleContext<CHTLParser::StyleContentContext>(i);
}

CHTLParser::StyleUsageContext* CHTLParser::StyleContentContext::styleUsage() {
  return getRuleContext<CHTLParser::StyleUsageContext>(0);
}


size_t CHTLParser::StyleContentContext::getRuleIndex() const {
  return CHTLParser::RuleStyleContent;
}

void CHTLParser::StyleContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyleContent(this);
}

void CHTLParser::StyleContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyleContent(this);
}

CHTLParser::StyleContentContext* CHTLParser::styleContent() {
  StyleContentContext *_localctx = _tracker.createInstance<StyleContentContext>(_ctx, getState());
  enterRule(_localctx, 94, CHTLParser::RuleStyleContent);
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
    switch (_input->LA(1)) {
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(504);
        styleProperty();
        break;
      }

      case CHTLParser::T__20:
      case CHTLParser::T__38:
      case CHTLParser::T__39: {
        enterOuterAlt(_localctx, 2);
        setState(505);
        cssSelector();
        setState(506);
        match(CHTLParser::T__1);
        setState(510);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4505248909557760) != 0)) {
          setState(507);
          styleContent();
          setState(512);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(513);
        match(CHTLParser::T__2);
        break;
      }

      case CHTLParser::T__15:
      case CHTLParser::T__21:
      case CHTLParser::T__22: {
        enterOuterAlt(_localctx, 3);
        setState(515);
        styleUsage();
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

//----------------- StylePropertyContext ------------------------------------------------------------------

CHTLParser::StylePropertyContext::StylePropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::PropertyNameContext* CHTLParser::StylePropertyContext::propertyName() {
  return getRuleContext<CHTLParser::PropertyNameContext>(0);
}

CHTLParser::PropertyValueContext* CHTLParser::StylePropertyContext::propertyValue() {
  return getRuleContext<CHTLParser::PropertyValueContext>(0);
}


size_t CHTLParser::StylePropertyContext::getRuleIndex() const {
  return CHTLParser::RuleStyleProperty;
}

void CHTLParser::StylePropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyleProperty(this);
}

void CHTLParser::StylePropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyleProperty(this);
}

CHTLParser::StylePropertyContext* CHTLParser::styleProperty() {
  StylePropertyContext *_localctx = _tracker.createInstance<StylePropertyContext>(_ctx, getState());
  enterRule(_localctx, 96, CHTLParser::RuleStyleProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(529);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(518);
      propertyName();
      setState(519);
      match(CHTLParser::T__36);
      setState(520);
      propertyValue();
      setState(521);
      match(CHTLParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(523);
      propertyName();
      setState(524);
      match(CHTLParser::T__7);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(526);
      propertyName();
      setState(527);
      match(CHTLParser::T__4);
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

//----------------- PropertyNameContext ------------------------------------------------------------------

CHTLParser::PropertyNameContext::PropertyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::PropertyNameContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::PropertyNameContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}


size_t CHTLParser::PropertyNameContext::getRuleIndex() const {
  return CHTLParser::RulePropertyName;
}

void CHTLParser::PropertyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyName(this);
}

void CHTLParser::PropertyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyName(this);
}

CHTLParser::PropertyNameContext* CHTLParser::propertyName() {
  PropertyNameContext *_localctx = _tracker.createInstance<PropertyNameContext>(_ctx, getState());
  enterRule(_localctx, 98, CHTLParser::RulePropertyName);
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
    setState(531);
    match(CHTLParser::IDENTIFIER);
    setState(536);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__37) {
      setState(532);
      match(CHTLParser::T__37);
      setState(533);
      match(CHTLParser::IDENTIFIER);
      setState(538);
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

//----------------- PropertyValueContext ------------------------------------------------------------------

CHTLParser::PropertyValueContext::PropertyValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::PropertyValueContext::STRING_LITERAL() {
  return getToken(CHTLParser::STRING_LITERAL, 0);
}

tree::TerminalNode* CHTLParser::PropertyValueContext::UNQUOTED_LITERAL() {
  return getToken(CHTLParser::UNQUOTED_LITERAL, 0);
}

CHTLParser::VariableUsageContext* CHTLParser::PropertyValueContext::variableUsage() {
  return getRuleContext<CHTLParser::VariableUsageContext>(0);
}

CHTLParser::CssFunctionContext* CHTLParser::PropertyValueContext::cssFunction() {
  return getRuleContext<CHTLParser::CssFunctionContext>(0);
}


size_t CHTLParser::PropertyValueContext::getRuleIndex() const {
  return CHTLParser::RulePropertyValue;
}

void CHTLParser::PropertyValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyValue(this);
}

void CHTLParser::PropertyValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyValue(this);
}

CHTLParser::PropertyValueContext* CHTLParser::propertyValue() {
  PropertyValueContext *_localctx = _tracker.createInstance<PropertyValueContext>(_ctx, getState());
  enterRule(_localctx, 100, CHTLParser::RulePropertyValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(543);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(539);
      match(CHTLParser::STRING_LITERAL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(540);
      match(CHTLParser::UNQUOTED_LITERAL);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(541);
      variableUsage();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(542);
      cssFunction();
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

//----------------- CssSelectorContext ------------------------------------------------------------------

CHTLParser::CssSelectorContext::CssSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CssSelectorContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::PseudoClassContext* CHTLParser::CssSelectorContext::pseudoClass() {
  return getRuleContext<CHTLParser::PseudoClassContext>(0);
}

CHTLParser::PseudoElementContext* CHTLParser::CssSelectorContext::pseudoElement() {
  return getRuleContext<CHTLParser::PseudoElementContext>(0);
}


size_t CHTLParser::CssSelectorContext::getRuleIndex() const {
  return CHTLParser::RuleCssSelector;
}

void CHTLParser::CssSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCssSelector(this);
}

void CHTLParser::CssSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCssSelector(this);
}

CHTLParser::CssSelectorContext* CHTLParser::cssSelector() {
  CssSelectorContext *_localctx = _tracker.createInstance<CssSelectorContext>(_ctx, getState());
  enterRule(_localctx, 102, CHTLParser::RuleCssSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(554);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(545);
      match(CHTLParser::T__20);
      setState(546);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(547);
      match(CHTLParser::T__38);
      setState(548);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(549);
      match(CHTLParser::T__39);
      setState(550);
      pseudoClass();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(551);
      match(CHTLParser::T__39);
      setState(552);
      pseudoElement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(553);
      match(CHTLParser::T__39);
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

//----------------- PseudoClassContext ------------------------------------------------------------------

CHTLParser::PseudoClassContext::PseudoClassContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::PseudoClassContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::PseudoClassContext::getRuleIndex() const {
  return CHTLParser::RulePseudoClass;
}

void CHTLParser::PseudoClassContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudoClass(this);
}

void CHTLParser::PseudoClassContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudoClass(this);
}

CHTLParser::PseudoClassContext* CHTLParser::pseudoClass() {
  PseudoClassContext *_localctx = _tracker.createInstance<PseudoClassContext>(_ctx, getState());
  enterRule(_localctx, 104, CHTLParser::RulePseudoClass);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(556);
    match(CHTLParser::T__36);
    setState(557);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PseudoElementContext ------------------------------------------------------------------

CHTLParser::PseudoElementContext::PseudoElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::PseudoElementContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::PseudoElementContext::getRuleIndex() const {
  return CHTLParser::RulePseudoElement;
}

void CHTLParser::PseudoElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudoElement(this);
}

void CHTLParser::PseudoElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudoElement(this);
}

CHTLParser::PseudoElementContext* CHTLParser::pseudoElement() {
  PseudoElementContext *_localctx = _tracker.createInstance<PseudoElementContext>(_ctx, getState());
  enterRule(_localctx, 106, CHTLParser::RulePseudoElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(559);
    match(CHTLParser::T__40);
    setState(560);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CssFunctionContext ------------------------------------------------------------------

CHTLParser::CssFunctionContext::CssFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CssFunctionContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::CssArgumentsContext* CHTLParser::CssFunctionContext::cssArguments() {
  return getRuleContext<CHTLParser::CssArgumentsContext>(0);
}


size_t CHTLParser::CssFunctionContext::getRuleIndex() const {
  return CHTLParser::RuleCssFunction;
}

void CHTLParser::CssFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCssFunction(this);
}

void CHTLParser::CssFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCssFunction(this);
}

CHTLParser::CssFunctionContext* CHTLParser::cssFunction() {
  CssFunctionContext *_localctx = _tracker.createInstance<CssFunctionContext>(_ctx, getState());
  enterRule(_localctx, 108, CHTLParser::RuleCssFunction);
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
    setState(562);
    match(CHTLParser::IDENTIFIER);
    setState(563);
    match(CHTLParser::T__41);
    setState(565);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7881299347898368) != 0)) {
      setState(564);
      cssArguments();
    }
    setState(567);
    match(CHTLParser::T__42);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CssArgumentsContext ------------------------------------------------------------------

CHTLParser::CssArgumentsContext::CssArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::CssArgumentContext *> CHTLParser::CssArgumentsContext::cssArgument() {
  return getRuleContexts<CHTLParser::CssArgumentContext>();
}

CHTLParser::CssArgumentContext* CHTLParser::CssArgumentsContext::cssArgument(size_t i) {
  return getRuleContext<CHTLParser::CssArgumentContext>(i);
}


size_t CHTLParser::CssArgumentsContext::getRuleIndex() const {
  return CHTLParser::RuleCssArguments;
}

void CHTLParser::CssArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCssArguments(this);
}

void CHTLParser::CssArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCssArguments(this);
}

CHTLParser::CssArgumentsContext* CHTLParser::cssArguments() {
  CssArgumentsContext *_localctx = _tracker.createInstance<CssArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 110, CHTLParser::RuleCssArguments);
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
    setState(569);
    cssArgument();
    setState(574);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(570);
      match(CHTLParser::T__7);
      setState(571);
      cssArgument();
      setState(576);
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

//----------------- CssArgumentContext ------------------------------------------------------------------

CHTLParser::CssArgumentContext::CssArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::PropertyValueContext* CHTLParser::CssArgumentContext::propertyValue() {
  return getRuleContext<CHTLParser::PropertyValueContext>(0);
}


size_t CHTLParser::CssArgumentContext::getRuleIndex() const {
  return CHTLParser::RuleCssArgument;
}

void CHTLParser::CssArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCssArgument(this);
}

void CHTLParser::CssArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCssArgument(this);
}

CHTLParser::CssArgumentContext* CHTLParser::cssArgument() {
  CssArgumentContext *_localctx = _tracker.createInstance<CssArgumentContext>(_ctx, getState());
  enterRule(_localctx, 112, CHTLParser::RuleCssArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(577);
    propertyValue();
   
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

CHTLParser::ScriptContentContext* CHTLParser::ScriptBlockContext::scriptContent() {
  return getRuleContext<CHTLParser::ScriptContentContext>(0);
}


size_t CHTLParser::ScriptBlockContext::getRuleIndex() const {
  return CHTLParser::RuleScriptBlock;
}

void CHTLParser::ScriptBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScriptBlock(this);
}

void CHTLParser::ScriptBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScriptBlock(this);
}

CHTLParser::ScriptBlockContext* CHTLParser::scriptBlock() {
  ScriptBlockContext *_localctx = _tracker.createInstance<ScriptBlockContext>(_ctx, getState());
  enterRule(_localctx, 114, CHTLParser::RuleScriptBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(579);
    match(CHTLParser::T__35);
    setState(580);
    match(CHTLParser::T__1);
    setState(581);
    scriptContent();
    setState(582);
    match(CHTLParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptContentContext ------------------------------------------------------------------

CHTLParser::ScriptContentContext::ScriptContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CHTLParser::ScriptContentContext::getRuleIndex() const {
  return CHTLParser::RuleScriptContent;
}

void CHTLParser::ScriptContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScriptContent(this);
}

void CHTLParser::ScriptContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScriptContent(this);
}

CHTLParser::ScriptContentContext* CHTLParser::scriptContent() {
  ScriptContentContext *_localctx = _tracker.createInstance<ScriptContentContext>(_ctx, getState());
  enterRule(_localctx, 116, CHTLParser::RuleScriptContent);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(590);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__0:
      case CHTLParser::T__1:
      case CHTLParser::T__3:
      case CHTLParser::T__4:
      case CHTLParser::T__5:
      case CHTLParser::T__6:
      case CHTLParser::T__7:
      case CHTLParser::T__8:
      case CHTLParser::T__9:
      case CHTLParser::T__10:
      case CHTLParser::T__11:
      case CHTLParser::T__12:
      case CHTLParser::T__13:
      case CHTLParser::T__14:
      case CHTLParser::T__15:
      case CHTLParser::T__16:
      case CHTLParser::T__17:
      case CHTLParser::T__18:
      case CHTLParser::T__19:
      case CHTLParser::T__20:
      case CHTLParser::T__21:
      case CHTLParser::T__22:
      case CHTLParser::T__23:
      case CHTLParser::T__24:
      case CHTLParser::T__25:
      case CHTLParser::T__26:
      case CHTLParser::T__27:
      case CHTLParser::T__28:
      case CHTLParser::T__29:
      case CHTLParser::T__30:
      case CHTLParser::T__31:
      case CHTLParser::T__32:
      case CHTLParser::T__33:
      case CHTLParser::T__34:
      case CHTLParser::T__35:
      case CHTLParser::T__36:
      case CHTLParser::T__37:
      case CHTLParser::T__38:
      case CHTLParser::T__39:
      case CHTLParser::T__40:
      case CHTLParser::T__41:
      case CHTLParser::T__42:
      case CHTLParser::T__43:
      case CHTLParser::SINGLE_LINE_COMMENT:
      case CHTLParser::MULTI_LINE_COMMENT:
      case CHTLParser::GENERATOR_COMMENT:
      case CHTLParser::BOOLEAN:
      case CHTLParser::NUMBER:
      case CHTLParser::STRING_LITERAL:
      case CHTLParser::UNQUOTED_LITERAL:
      case CHTLParser::IDENTIFIER:
      case CHTLParser::WS: {
        enterOuterAlt(_localctx, 1);
        setState(585); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(584);
          _la = _input->LA(1);
          if (_la == 0 || _la == Token::EOF || (_la == CHTLParser::T__2)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(587); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 18014398509481974) != 0));
        break;
      }

      case CHTLParser::T__2: {
        enterOuterAlt(_localctx, 2);

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

//----------------- ElementUsageContext ------------------------------------------------------------------

CHTLParser::ElementUsageContext::ElementUsageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CustomTypeContext* CHTLParser::ElementUsageContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

tree::TerminalNode* CHTLParser::ElementUsageContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::ElementSpecializationContext* CHTLParser::ElementUsageContext::elementSpecialization() {
  return getRuleContext<CHTLParser::ElementSpecializationContext>(0);
}

CHTLParser::NamespacePathContext* CHTLParser::ElementUsageContext::namespacePath() {
  return getRuleContext<CHTLParser::NamespacePathContext>(0);
}

CHTLParser::TemplateTypeContext* CHTLParser::ElementUsageContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}

CHTLParser::OriginTypeContext* CHTLParser::ElementUsageContext::originType() {
  return getRuleContext<CHTLParser::OriginTypeContext>(0);
}


size_t CHTLParser::ElementUsageContext::getRuleIndex() const {
  return CHTLParser::RuleElementUsage;
}

void CHTLParser::ElementUsageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementUsage(this);
}

void CHTLParser::ElementUsageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementUsage(this);
}

CHTLParser::ElementUsageContext* CHTLParser::elementUsage() {
  ElementUsageContext *_localctx = _tracker.createInstance<ElementUsageContext>(_ctx, getState());
  enterRule(_localctx, 118, CHTLParser::RuleElementUsage);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(643);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(592);
      customType();
      setState(593);
      match(CHTLParser::IDENTIFIER);
      setState(595);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(594);
        elementSpecialization();
      }
      setState(599);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__12) {
        setState(597);
        match(CHTLParser::T__12);
        setState(598);
        namespacePath();
      }
      setState(601);
      match(CHTLParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(603);
      templateType();
      setState(604);
      match(CHTLParser::IDENTIFIER);
      setState(606);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(605);
        elementSpecialization();
      }
      setState(610);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__12) {
        setState(608);
        match(CHTLParser::T__12);
        setState(609);
        namespacePath();
      }
      setState(612);
      match(CHTLParser::T__4);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(614);
      match(CHTLParser::T__18);
      setState(615);
      customType();
      setState(616);
      match(CHTLParser::IDENTIFIER);
      setState(618);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(617);
        elementSpecialization();
      }
      setState(622);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__12) {
        setState(620);
        match(CHTLParser::T__12);
        setState(621);
        namespacePath();
      }
      setState(624);
      match(CHTLParser::T__4);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(626);
      match(CHTLParser::T__19);
      setState(627);
      templateType();
      setState(628);
      match(CHTLParser::IDENTIFIER);
      setState(630);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(629);
        elementSpecialization();
      }
      setState(634);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__12) {
        setState(632);
        match(CHTLParser::T__12);
        setState(633);
        namespacePath();
      }
      setState(636);
      match(CHTLParser::T__4);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(638);
      match(CHTLParser::T__32);
      setState(639);
      originType();
      setState(640);
      match(CHTLParser::IDENTIFIER);
      setState(641);
      match(CHTLParser::T__4);
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

//----------------- ElementSpecializationContext ------------------------------------------------------------------

CHTLParser::ElementSpecializationContext::ElementSpecializationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ElementSpecializationContentContext *> CHTLParser::ElementSpecializationContext::elementSpecializationContent() {
  return getRuleContexts<CHTLParser::ElementSpecializationContentContext>();
}

CHTLParser::ElementSpecializationContentContext* CHTLParser::ElementSpecializationContext::elementSpecializationContent(size_t i) {
  return getRuleContext<CHTLParser::ElementSpecializationContentContext>(i);
}


size_t CHTLParser::ElementSpecializationContext::getRuleIndex() const {
  return CHTLParser::RuleElementSpecialization;
}

void CHTLParser::ElementSpecializationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementSpecialization(this);
}

void CHTLParser::ElementSpecializationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementSpecialization(this);
}

CHTLParser::ElementSpecializationContext* CHTLParser::elementSpecialization() {
  ElementSpecializationContext *_localctx = _tracker.createInstance<ElementSpecializationContext>(_ctx, getState());
  enterRule(_localctx, 120, CHTLParser::RuleElementSpecialization);
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
    setState(645);
    match(CHTLParser::T__1);
    setState(649);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503719987118080) != 0)) {
      setState(646);
      elementSpecializationContent();
      setState(651);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(652);
    match(CHTLParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementSpecializationContentContext ------------------------------------------------------------------

CHTLParser::ElementSpecializationContentContext::ElementSpecializationContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::HtmlElementContext* CHTLParser::ElementSpecializationContentContext::htmlElement() {
  return getRuleContext<CHTLParser::HtmlElementContext>(0);
}

CHTLParser::StyleBlockContext* CHTLParser::ElementSpecializationContentContext::styleBlock() {
  return getRuleContext<CHTLParser::StyleBlockContext>(0);
}

CHTLParser::DeleteStatementContext* CHTLParser::ElementSpecializationContentContext::deleteStatement() {
  return getRuleContext<CHTLParser::DeleteStatementContext>(0);
}

CHTLParser::InsertStatementContext* CHTLParser::ElementSpecializationContentContext::insertStatement() {
  return getRuleContext<CHTLParser::InsertStatementContext>(0);
}


size_t CHTLParser::ElementSpecializationContentContext::getRuleIndex() const {
  return CHTLParser::RuleElementSpecializationContent;
}

void CHTLParser::ElementSpecializationContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementSpecializationContent(this);
}

void CHTLParser::ElementSpecializationContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementSpecializationContent(this);
}

CHTLParser::ElementSpecializationContentContext* CHTLParser::elementSpecializationContent() {
  ElementSpecializationContentContext *_localctx = _tracker.createInstance<ElementSpecializationContentContext>(_ctx, getState());
  enterRule(_localctx, 122, CHTLParser::RuleElementSpecializationContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(658);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(654);
      htmlElement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(655);
      styleBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(656);
      deleteStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(657);
      insertStatement();
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

//----------------- StyleUsageContext ------------------------------------------------------------------

CHTLParser::StyleUsageContext::StyleUsageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::CustomTypeContext* CHTLParser::StyleUsageContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

tree::TerminalNode* CHTLParser::StyleUsageContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::StyleSpecializationContext* CHTLParser::StyleUsageContext::styleSpecialization() {
  return getRuleContext<CHTLParser::StyleSpecializationContext>(0);
}

CHTLParser::TemplateTypeContext* CHTLParser::StyleUsageContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}


size_t CHTLParser::StyleUsageContext::getRuleIndex() const {
  return CHTLParser::RuleStyleUsage;
}

void CHTLParser::StyleUsageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyleUsage(this);
}

void CHTLParser::StyleUsageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyleUsage(this);
}

CHTLParser::StyleUsageContext* CHTLParser::styleUsage() {
  StyleUsageContext *_localctx = _tracker.createInstance<StyleUsageContext>(_ctx, getState());
  enterRule(_localctx, 124, CHTLParser::RuleStyleUsage);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(674);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(660);
      customType();
      setState(661);
      match(CHTLParser::IDENTIFIER);
      setState(663);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(662);
        styleSpecialization();
      }
      setState(665);
      match(CHTLParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(667);
      templateType();
      setState(668);
      match(CHTLParser::IDENTIFIER);
      setState(670);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(669);
        styleSpecialization();
      }
      setState(672);
      match(CHTLParser::T__4);
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

//----------------- StyleSpecializationContext ------------------------------------------------------------------

CHTLParser::StyleSpecializationContext::StyleSpecializationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::StylePropertyContext *> CHTLParser::StyleSpecializationContext::styleProperty() {
  return getRuleContexts<CHTLParser::StylePropertyContext>();
}

CHTLParser::StylePropertyContext* CHTLParser::StyleSpecializationContext::styleProperty(size_t i) {
  return getRuleContext<CHTLParser::StylePropertyContext>(i);
}


size_t CHTLParser::StyleSpecializationContext::getRuleIndex() const {
  return CHTLParser::RuleStyleSpecialization;
}

void CHTLParser::StyleSpecializationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyleSpecialization(this);
}

void CHTLParser::StyleSpecializationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyleSpecialization(this);
}

CHTLParser::StyleSpecializationContext* CHTLParser::styleSpecialization() {
  StyleSpecializationContext *_localctx = _tracker.createInstance<StyleSpecializationContext>(_ctx, getState());
  enterRule(_localctx, 126, CHTLParser::RuleStyleSpecialization);
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
    setState(676);
    match(CHTLParser::T__1);
    setState(680);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::IDENTIFIER) {
      setState(677);
      styleProperty();
      setState(682);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(683);
    match(CHTLParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDefinitionContext ------------------------------------------------------------------

CHTLParser::VariableDefinitionContext::VariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::VariableDefinitionContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::VariableDefinitionContext::STRING_LITERAL() {
  return getToken(CHTLParser::STRING_LITERAL, 0);
}


size_t CHTLParser::VariableDefinitionContext::getRuleIndex() const {
  return CHTLParser::RuleVariableDefinition;
}

void CHTLParser::VariableDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDefinition(this);
}

void CHTLParser::VariableDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDefinition(this);
}

CHTLParser::VariableDefinitionContext* CHTLParser::variableDefinition() {
  VariableDefinitionContext *_localctx = _tracker.createInstance<VariableDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 128, CHTLParser::RuleVariableDefinition);

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
    match(CHTLParser::IDENTIFIER);
    setState(686);
    match(CHTLParser::T__36);
    setState(687);
    match(CHTLParser::STRING_LITERAL);
    setState(688);
    match(CHTLParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableUsageContext ------------------------------------------------------------------

CHTLParser::VariableUsageContext::VariableUsageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::VariableUsageContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::VariableArgumentsContext* CHTLParser::VariableUsageContext::variableArguments() {
  return getRuleContext<CHTLParser::VariableArgumentsContext>(0);
}


size_t CHTLParser::VariableUsageContext::getRuleIndex() const {
  return CHTLParser::RuleVariableUsage;
}

void CHTLParser::VariableUsageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableUsage(this);
}

void CHTLParser::VariableUsageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableUsage(this);
}

CHTLParser::VariableUsageContext* CHTLParser::variableUsage() {
  VariableUsageContext *_localctx = _tracker.createInstance<VariableUsageContext>(_ctx, getState());
  enterRule(_localctx, 130, CHTLParser::RuleVariableUsage);
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
    setState(690);
    match(CHTLParser::IDENTIFIER);
    setState(691);
    match(CHTLParser::T__41);
    setState(693);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::IDENTIFIER) {
      setState(692);
      variableArguments();
    }
    setState(695);
    match(CHTLParser::T__42);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableArgumentsContext ------------------------------------------------------------------

CHTLParser::VariableArgumentsContext::VariableArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::VariableArgumentContext *> CHTLParser::VariableArgumentsContext::variableArgument() {
  return getRuleContexts<CHTLParser::VariableArgumentContext>();
}

CHTLParser::VariableArgumentContext* CHTLParser::VariableArgumentsContext::variableArgument(size_t i) {
  return getRuleContext<CHTLParser::VariableArgumentContext>(i);
}


size_t CHTLParser::VariableArgumentsContext::getRuleIndex() const {
  return CHTLParser::RuleVariableArguments;
}

void CHTLParser::VariableArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableArguments(this);
}

void CHTLParser::VariableArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableArguments(this);
}

CHTLParser::VariableArgumentsContext* CHTLParser::variableArguments() {
  VariableArgumentsContext *_localctx = _tracker.createInstance<VariableArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 132, CHTLParser::RuleVariableArguments);
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
    setState(697);
    variableArgument();
    setState(702);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(698);
      match(CHTLParser::T__7);
      setState(699);
      variableArgument();
      setState(704);
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

//----------------- VariableArgumentContext ------------------------------------------------------------------

CHTLParser::VariableArgumentContext::VariableArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::VariableArgumentContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::PropertyValueContext* CHTLParser::VariableArgumentContext::propertyValue() {
  return getRuleContext<CHTLParser::PropertyValueContext>(0);
}


size_t CHTLParser::VariableArgumentContext::getRuleIndex() const {
  return CHTLParser::RuleVariableArgument;
}

void CHTLParser::VariableArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableArgument(this);
}

void CHTLParser::VariableArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableArgument(this);
}

CHTLParser::VariableArgumentContext* CHTLParser::variableArgument() {
  VariableArgumentContext *_localctx = _tracker.createInstance<VariableArgumentContext>(_ctx, getState());
  enterRule(_localctx, 134, CHTLParser::RuleVariableArgument);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(705);
      match(CHTLParser::IDENTIFIER);
      setState(706);
      match(CHTLParser::T__3);
      setState(707);
      propertyValue();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(708);
      match(CHTLParser::IDENTIFIER);
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

//----------------- VariableAssignmentContext ------------------------------------------------------------------

CHTLParser::VariableAssignmentContext::VariableAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::VariableAssignmentContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::PropertyValueContext* CHTLParser::VariableAssignmentContext::propertyValue() {
  return getRuleContext<CHTLParser::PropertyValueContext>(0);
}


size_t CHTLParser::VariableAssignmentContext::getRuleIndex() const {
  return CHTLParser::RuleVariableAssignment;
}

void CHTLParser::VariableAssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableAssignment(this);
}

void CHTLParser::VariableAssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableAssignment(this);
}

CHTLParser::VariableAssignmentContext* CHTLParser::variableAssignment() {
  VariableAssignmentContext *_localctx = _tracker.createInstance<VariableAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 136, CHTLParser::RuleVariableAssignment);

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
    match(CHTLParser::IDENTIFIER);
    setState(712);
    match(CHTLParser::T__3);
    setState(713);
    propertyValue();
    setState(714);
    match(CHTLParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamespacePathContext ------------------------------------------------------------------

CHTLParser::NamespacePathContext::NamespacePathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::NamespacePathContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::NamespacePathContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}


size_t CHTLParser::NamespacePathContext::getRuleIndex() const {
  return CHTLParser::RuleNamespacePath;
}

void CHTLParser::NamespacePathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespacePath(this);
}

void CHTLParser::NamespacePathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespacePath(this);
}

CHTLParser::NamespacePathContext* CHTLParser::namespacePath() {
  NamespacePathContext *_localctx = _tracker.createInstance<NamespacePathContext>(_ctx, getState());
  enterRule(_localctx, 138, CHTLParser::RuleNamespacePath);
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
    setState(716);
    match(CHTLParser::IDENTIFIER);
    setState(721);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__20) {
      setState(717);
      match(CHTLParser::T__20);
      setState(718);
      match(CHTLParser::IDENTIFIER);
      setState(723);
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

//----------------- ExceptConstraintContext ------------------------------------------------------------------

CHTLParser::ExceptConstraintContext::ExceptConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ExceptTargetContext *> CHTLParser::ExceptConstraintContext::exceptTarget() {
  return getRuleContexts<CHTLParser::ExceptTargetContext>();
}

CHTLParser::ExceptTargetContext* CHTLParser::ExceptConstraintContext::exceptTarget(size_t i) {
  return getRuleContext<CHTLParser::ExceptTargetContext>(i);
}


size_t CHTLParser::ExceptConstraintContext::getRuleIndex() const {
  return CHTLParser::RuleExceptConstraint;
}

void CHTLParser::ExceptConstraintContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExceptConstraint(this);
}

void CHTLParser::ExceptConstraintContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExceptConstraint(this);
}

CHTLParser::ExceptConstraintContext* CHTLParser::exceptConstraint() {
  ExceptConstraintContext *_localctx = _tracker.createInstance<ExceptConstraintContext>(_ctx, getState());
  enterRule(_localctx, 140, CHTLParser::RuleExceptConstraint);
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
    setState(724);
    match(CHTLParser::T__43);
    setState(725);
    exceptTarget();
    setState(730);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(726);
      match(CHTLParser::T__7);
      setState(727);
      exceptTarget();
      setState(732);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(733);
    match(CHTLParser::T__4);
   
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

tree::TerminalNode* CHTLParser::ExceptTargetContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

CHTLParser::CustomTypeContext* CHTLParser::ExceptTargetContext::customType() {
  return getRuleContext<CHTLParser::CustomTypeContext>(0);
}

CHTLParser::TemplateTypeContext* CHTLParser::ExceptTargetContext::templateType() {
  return getRuleContext<CHTLParser::TemplateTypeContext>(0);
}


size_t CHTLParser::ExceptTargetContext::getRuleIndex() const {
  return CHTLParser::RuleExceptTarget;
}

void CHTLParser::ExceptTargetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExceptTarget(this);
}

void CHTLParser::ExceptTargetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExceptTarget(this);
}

CHTLParser::ExceptTargetContext* CHTLParser::exceptTarget() {
  ExceptTargetContext *_localctx = _tracker.createInstance<ExceptTargetContext>(_ctx, getState());
  enterRule(_localctx, 142, CHTLParser::RuleExceptTarget);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(751);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(735);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(736);
      customType();
      setState(737);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(739);
      templateType();
      setState(740);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(742);
      match(CHTLParser::T__18);
      setState(744);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 12648448) != 0)) {
        setState(743);
        customType();
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(746);
      match(CHTLParser::T__19);
      setState(748);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 12648448) != 0)) {
        setState(747);
        templateType();
      }
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(750);
      match(CHTLParser::T__14);
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

tree::TerminalNode* CHTLParser::CommentContext::SINGLE_LINE_COMMENT() {
  return getToken(CHTLParser::SINGLE_LINE_COMMENT, 0);
}

tree::TerminalNode* CHTLParser::CommentContext::MULTI_LINE_COMMENT() {
  return getToken(CHTLParser::MULTI_LINE_COMMENT, 0);
}

tree::TerminalNode* CHTLParser::CommentContext::GENERATOR_COMMENT() {
  return getToken(CHTLParser::GENERATOR_COMMENT, 0);
}


size_t CHTLParser::CommentContext::getRuleIndex() const {
  return CHTLParser::RuleComment;
}

void CHTLParser::CommentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComment(this);
}

void CHTLParser::CommentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComment(this);
}

CHTLParser::CommentContext* CHTLParser::comment() {
  CommentContext *_localctx = _tracker.createInstance<CommentContext>(_ctx, getState());
  enterRule(_localctx, 144, CHTLParser::RuleComment);
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
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 246290604621824) != 0))) {
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

void CHTLParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chtlParserInitialize();
#else
  ::antlr4::internal::call_once(chtlParserOnceFlag, chtlParserInitialize);
#endif
}
