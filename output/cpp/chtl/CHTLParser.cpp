
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
      "htmlElement", "globalStyleElement", "globalStyleContent", "elementName", 
      "elementIndexAccess", "elementBody", "elementContent", "attribute", 
      "attributeName", "attributeValue", "textContent", "styleBlock", "styleContent", 
      "styleProperty", "propertyName", "propertyValue", "cssSelector", "pseudoClass", 
      "pseudoElement", "cssFunction", "cssArguments", "cssArgument", "scriptBlock", 
      "scriptContent", "elementUsage", "elementSpecialization", "elementSpecializationContent", 
      "styleUsage", "styleSpecialization", "variableDefinition", "variableUsage", 
      "variableArguments", "variableArgument", "variableAssignment", "namespacePath", 
      "exceptConstraint", "exceptTarget", "comment"
    },
    std::vector<std::string>{
      "", "'[Configuration]'", "'{'", "'}'", "'='", "';'", "'[Name]'", "'['", 
      "','", "']'", "'@'", "'[Namespace]'", "'[Import]'", "'from'", "'as'", 
      "'@Html'", "'@Style'", "'@JavaScript'", "'@Chtl'", "'[Custom]'", "'[Template]'", 
      "'.'", "'@Element'", "'@Var'", "'inherit'", "'delete'", "'insert'", 
      "'after'", "'before'", "'replace'", "'at'", "'top'", "'bottom'", "'[Origin]'", 
      "'style'", "'text'", "'script'", "':'", "'-'", "'#'", "'&'", "'::'", 
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
  	4,1,53,774,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,1,0,5,0,152,8,0,10,0,12,0,
  	155,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,169,8,1,1,
  	2,1,2,1,2,5,2,174,8,2,10,2,12,2,177,9,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,5,3,189,8,3,10,3,12,3,192,9,3,1,3,3,3,195,8,3,1,4,1,4,1,5,1,
  	5,1,5,1,5,3,5,203,8,5,1,6,1,6,1,6,1,6,5,6,209,8,6,10,6,12,6,212,9,6,1,
  	6,1,6,1,7,1,7,1,7,3,7,219,8,7,1,8,1,8,1,8,1,8,3,8,225,8,8,1,8,1,8,1,9,
  	1,9,1,9,3,9,232,8,9,1,10,1,10,5,10,236,8,10,10,10,12,10,239,9,10,1,10,
  	1,10,1,11,1,11,1,11,1,11,3,11,247,8,11,1,12,1,12,1,12,1,12,1,12,1,12,
  	3,12,255,8,12,1,12,3,12,258,8,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,
  	13,1,13,1,13,1,13,1,13,3,13,272,8,13,1,14,1,14,3,14,276,8,14,1,15,1,15,
  	1,15,5,15,281,8,15,10,15,12,15,284,9,15,1,16,1,16,1,16,1,16,1,16,1,17,
  	1,17,1,18,1,18,5,18,295,8,18,10,18,12,18,298,9,18,1,18,1,18,1,19,1,19,
  	1,19,1,19,3,19,306,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	3,20,317,8,20,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,23,1,23,5,23,328,8,
  	23,10,23,12,23,331,9,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,3,24,
  	341,8,24,1,25,1,25,1,25,3,25,346,8,25,1,25,3,25,349,8,25,1,25,1,25,1,
  	25,3,25,354,8,25,1,25,3,25,357,8,25,3,25,359,8,25,1,26,1,26,5,26,363,
  	8,26,10,26,12,26,366,9,26,1,26,1,26,1,27,1,27,1,27,3,27,373,8,27,1,28,
  	1,28,1,28,1,28,5,28,379,8,28,10,28,12,28,382,9,28,1,28,1,28,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,3,29,397,8,29,1,30,1,30,
  	1,30,1,30,1,30,5,30,404,8,30,10,30,12,30,407,9,30,1,30,1,30,1,31,1,31,
  	1,31,1,31,1,31,1,31,1,31,3,31,418,8,31,1,32,1,32,1,32,1,32,3,32,424,8,
  	32,1,33,1,33,3,33,428,8,33,1,34,1,34,1,34,3,34,433,8,34,1,34,1,34,1,34,
  	1,34,1,35,1,35,1,36,5,36,442,8,36,10,36,12,36,445,9,36,1,37,1,37,3,37,
  	449,8,37,1,37,1,37,1,37,3,37,454,8,37,1,38,1,38,1,38,1,38,1,38,1,39,5,
  	39,462,8,39,10,39,12,39,465,9,39,1,40,1,40,1,41,1,41,1,41,1,41,1,42,1,
  	42,5,42,475,8,42,10,42,12,42,478,9,42,1,42,1,42,1,43,1,43,1,43,1,43,1,
  	43,1,43,1,43,1,43,3,43,490,8,43,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,
  	44,1,44,1,44,3,44,502,8,44,1,45,1,45,1,46,1,46,1,46,3,46,509,8,46,1,47,
  	1,47,1,48,1,48,1,48,5,48,516,8,48,10,48,12,48,519,9,48,1,48,1,48,1,49,
  	1,49,1,49,1,49,5,49,527,8,49,10,49,12,49,530,9,49,1,49,1,49,1,49,3,49,
  	535,8,49,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,3,50,
  	548,8,50,1,51,1,51,1,51,5,51,553,8,51,10,51,12,51,556,9,51,1,52,1,52,
  	1,52,1,52,3,52,562,8,52,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,
  	3,53,573,8,53,1,54,1,54,1,54,1,55,1,55,1,55,1,56,1,56,1,56,3,56,584,8,
  	56,1,56,1,56,1,57,1,57,1,57,5,57,591,8,57,10,57,12,57,594,9,57,1,58,1,
  	58,1,59,1,59,1,59,1,59,1,59,1,60,4,60,604,8,60,11,60,12,60,605,1,60,3,
  	60,609,8,60,1,61,1,61,1,61,3,61,614,8,61,1,61,1,61,3,61,618,8,61,1,61,
  	1,61,1,61,1,61,1,61,3,61,625,8,61,1,61,1,61,3,61,629,8,61,1,61,1,61,1,
  	61,1,61,1,61,1,61,3,61,637,8,61,1,61,1,61,3,61,641,8,61,1,61,1,61,1,61,
  	1,61,1,61,1,61,3,61,649,8,61,1,61,1,61,3,61,653,8,61,1,61,1,61,1,61,1,
  	61,1,61,1,61,1,61,3,61,662,8,61,1,62,1,62,5,62,666,8,62,10,62,12,62,669,
  	9,62,1,62,1,62,1,63,1,63,1,63,1,63,3,63,677,8,63,1,64,1,64,1,64,3,64,
  	682,8,64,1,64,1,64,1,64,1,64,1,64,3,64,689,8,64,1,64,1,64,3,64,693,8,
  	64,1,65,1,65,5,65,697,8,65,10,65,12,65,700,9,65,1,65,1,65,1,66,1,66,1,
  	66,1,66,1,66,1,67,1,67,1,67,3,67,712,8,67,1,67,1,67,1,68,1,68,1,68,5,
  	68,719,8,68,10,68,12,68,722,9,68,1,69,1,69,1,69,1,69,3,69,728,8,69,1,
  	70,1,70,1,70,1,70,1,70,1,71,1,71,1,71,5,71,738,8,71,10,71,12,71,741,9,
  	71,1,72,1,72,1,72,1,72,5,72,747,8,72,10,72,12,72,750,9,72,1,72,1,72,1,
  	73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,1,73,3,73,763,8,73,1,73,1,73,3,
  	73,767,8,73,1,73,3,73,770,8,73,1,74,1,74,1,74,0,0,75,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,
  	106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,
  	142,144,146,148,0,6,2,0,16,16,22,23,1,0,15,17,1,0,3,3,2,0,34,36,52,52,
  	1,0,50,51,1,0,45,47,827,0,153,1,0,0,0,2,168,1,0,0,0,4,170,1,0,0,0,6,194,
  	1,0,0,0,8,196,1,0,0,0,10,202,1,0,0,0,12,204,1,0,0,0,14,218,1,0,0,0,16,
  	220,1,0,0,0,18,228,1,0,0,0,20,233,1,0,0,0,22,246,1,0,0,0,24,248,1,0,0,
  	0,26,271,1,0,0,0,28,275,1,0,0,0,30,277,1,0,0,0,32,285,1,0,0,0,34,290,
  	1,0,0,0,36,292,1,0,0,0,38,305,1,0,0,0,40,316,1,0,0,0,42,318,1,0,0,0,44,
  	323,1,0,0,0,46,325,1,0,0,0,48,340,1,0,0,0,50,358,1,0,0,0,52,360,1,0,0,
  	0,54,372,1,0,0,0,56,374,1,0,0,0,58,396,1,0,0,0,60,398,1,0,0,0,62,417,
  	1,0,0,0,64,419,1,0,0,0,66,427,1,0,0,0,68,429,1,0,0,0,70,438,1,0,0,0,72,
  	443,1,0,0,0,74,453,1,0,0,0,76,455,1,0,0,0,78,463,1,0,0,0,80,466,1,0,0,
  	0,82,468,1,0,0,0,84,472,1,0,0,0,86,489,1,0,0,0,88,501,1,0,0,0,90,503,
  	1,0,0,0,92,508,1,0,0,0,94,510,1,0,0,0,96,512,1,0,0,0,98,534,1,0,0,0,100,
  	547,1,0,0,0,102,549,1,0,0,0,104,561,1,0,0,0,106,572,1,0,0,0,108,574,1,
  	0,0,0,110,577,1,0,0,0,112,580,1,0,0,0,114,587,1,0,0,0,116,595,1,0,0,0,
  	118,597,1,0,0,0,120,608,1,0,0,0,122,661,1,0,0,0,124,663,1,0,0,0,126,676,
  	1,0,0,0,128,692,1,0,0,0,130,694,1,0,0,0,132,703,1,0,0,0,134,708,1,0,0,
  	0,136,715,1,0,0,0,138,727,1,0,0,0,140,729,1,0,0,0,142,734,1,0,0,0,144,
  	742,1,0,0,0,146,769,1,0,0,0,148,771,1,0,0,0,150,152,3,2,1,0,151,150,1,
  	0,0,0,152,155,1,0,0,0,153,151,1,0,0,0,153,154,1,0,0,0,154,156,1,0,0,0,
  	155,153,1,0,0,0,156,157,5,0,0,1,157,1,1,0,0,0,158,169,3,4,2,0,159,169,
  	3,18,9,0,160,169,3,24,12,0,161,169,3,32,16,0,162,169,3,42,21,0,163,169,
  	3,68,34,0,164,169,3,74,37,0,165,169,3,96,48,0,166,169,3,118,59,0,167,
  	169,3,148,74,0,168,158,1,0,0,0,168,159,1,0,0,0,168,160,1,0,0,0,168,161,
  	1,0,0,0,168,162,1,0,0,0,168,163,1,0,0,0,168,164,1,0,0,0,168,165,1,0,0,
  	0,168,166,1,0,0,0,168,167,1,0,0,0,169,3,1,0,0,0,170,171,5,1,0,0,171,175,
  	5,2,0,0,172,174,3,6,3,0,173,172,1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,
  	0,175,176,1,0,0,0,176,178,1,0,0,0,177,175,1,0,0,0,178,179,5,3,0,0,179,
  	5,1,0,0,0,180,181,3,8,4,0,181,182,5,4,0,0,182,183,3,10,5,0,183,184,5,
  	5,0,0,184,195,1,0,0,0,185,186,5,6,0,0,186,190,5,2,0,0,187,189,3,16,8,
  	0,188,187,1,0,0,0,189,192,1,0,0,0,190,188,1,0,0,0,190,191,1,0,0,0,191,
  	193,1,0,0,0,192,190,1,0,0,0,193,195,5,3,0,0,194,180,1,0,0,0,194,185,1,
  	0,0,0,195,7,1,0,0,0,196,197,5,52,0,0,197,9,1,0,0,0,198,203,5,50,0,0,199,
  	203,5,49,0,0,200,203,5,48,0,0,201,203,3,12,6,0,202,198,1,0,0,0,202,199,
  	1,0,0,0,202,200,1,0,0,0,202,201,1,0,0,0,203,11,1,0,0,0,204,205,5,7,0,
  	0,205,210,3,14,7,0,206,207,5,8,0,0,207,209,3,14,7,0,208,206,1,0,0,0,209,
  	212,1,0,0,0,210,208,1,0,0,0,210,211,1,0,0,0,211,213,1,0,0,0,212,210,1,
  	0,0,0,213,214,5,9,0,0,214,13,1,0,0,0,215,216,5,10,0,0,216,219,5,52,0,
  	0,217,219,5,50,0,0,218,215,1,0,0,0,218,217,1,0,0,0,219,15,1,0,0,0,220,
  	221,5,52,0,0,221,224,5,4,0,0,222,225,3,10,5,0,223,225,3,12,6,0,224,222,
  	1,0,0,0,224,223,1,0,0,0,225,226,1,0,0,0,226,227,5,5,0,0,227,17,1,0,0,
  	0,228,229,5,11,0,0,229,231,5,52,0,0,230,232,3,20,10,0,231,230,1,0,0,0,
  	231,232,1,0,0,0,232,19,1,0,0,0,233,237,5,2,0,0,234,236,3,22,11,0,235,
  	234,1,0,0,0,236,239,1,0,0,0,237,235,1,0,0,0,237,238,1,0,0,0,238,240,1,
  	0,0,0,239,237,1,0,0,0,240,241,5,3,0,0,241,21,1,0,0,0,242,247,3,18,9,0,
  	243,247,3,32,16,0,244,247,3,42,21,0,245,247,3,144,72,0,246,242,1,0,0,
  	0,246,243,1,0,0,0,246,244,1,0,0,0,246,245,1,0,0,0,247,23,1,0,0,0,248,
  	249,5,12,0,0,249,250,3,26,13,0,250,251,5,13,0,0,251,254,3,28,14,0,252,
  	253,5,14,0,0,253,255,5,52,0,0,254,252,1,0,0,0,254,255,1,0,0,0,255,257,
  	1,0,0,0,256,258,5,5,0,0,257,256,1,0,0,0,257,258,1,0,0,0,258,25,1,0,0,
  	0,259,272,5,15,0,0,260,272,5,16,0,0,261,272,5,17,0,0,262,272,5,18,0,0,
  	263,264,5,19,0,0,264,265,3,44,22,0,265,266,5,52,0,0,266,272,1,0,0,0,267,
  	268,5,20,0,0,268,269,3,34,17,0,269,270,5,52,0,0,270,272,1,0,0,0,271,259,
  	1,0,0,0,271,260,1,0,0,0,271,261,1,0,0,0,271,262,1,0,0,0,271,263,1,0,0,
  	0,271,267,1,0,0,0,272,27,1,0,0,0,273,276,5,50,0,0,274,276,3,30,15,0,275,
  	273,1,0,0,0,275,274,1,0,0,0,276,29,1,0,0,0,277,282,5,52,0,0,278,279,5,
  	21,0,0,279,281,5,52,0,0,280,278,1,0,0,0,281,284,1,0,0,0,282,280,1,0,0,
  	0,282,283,1,0,0,0,283,31,1,0,0,0,284,282,1,0,0,0,285,286,5,20,0,0,286,
  	287,3,34,17,0,287,288,5,52,0,0,288,289,3,36,18,0,289,33,1,0,0,0,290,291,
  	7,0,0,0,291,35,1,0,0,0,292,296,5,2,0,0,293,295,3,38,19,0,294,293,1,0,
  	0,0,295,298,1,0,0,0,296,294,1,0,0,0,296,297,1,0,0,0,297,299,1,0,0,0,298,
  	296,1,0,0,0,299,300,5,3,0,0,300,37,1,0,0,0,301,306,3,100,50,0,302,306,
  	3,74,37,0,303,306,3,40,20,0,304,306,3,132,66,0,305,301,1,0,0,0,305,302,
  	1,0,0,0,305,303,1,0,0,0,305,304,1,0,0,0,306,39,1,0,0,0,307,308,3,34,17,
  	0,308,309,5,52,0,0,309,310,5,5,0,0,310,317,1,0,0,0,311,312,5,24,0,0,312,
  	313,3,34,17,0,313,314,5,52,0,0,314,315,5,5,0,0,315,317,1,0,0,0,316,307,
  	1,0,0,0,316,311,1,0,0,0,317,41,1,0,0,0,318,319,5,19,0,0,319,320,3,44,
  	22,0,320,321,5,52,0,0,321,322,3,46,23,0,322,43,1,0,0,0,323,324,7,0,0,
  	0,324,45,1,0,0,0,325,329,5,2,0,0,326,328,3,48,24,0,327,326,1,0,0,0,328,
  	331,1,0,0,0,329,327,1,0,0,0,329,330,1,0,0,0,330,332,1,0,0,0,331,329,1,
  	0,0,0,332,333,5,3,0,0,333,47,1,0,0,0,334,341,3,100,50,0,335,341,3,74,
  	37,0,336,341,3,50,25,0,337,341,3,132,66,0,338,341,3,56,28,0,339,341,3,
  	60,30,0,340,334,1,0,0,0,340,335,1,0,0,0,340,336,1,0,0,0,340,337,1,0,0,
  	0,340,338,1,0,0,0,340,339,1,0,0,0,341,49,1,0,0,0,342,343,3,44,22,0,343,
  	345,5,52,0,0,344,346,3,52,26,0,345,344,1,0,0,0,345,346,1,0,0,0,346,348,
  	1,0,0,0,347,349,5,5,0,0,348,347,1,0,0,0,348,349,1,0,0,0,349,359,1,0,0,
  	0,350,351,3,34,17,0,351,353,5,52,0,0,352,354,3,52,26,0,353,352,1,0,0,
  	0,353,354,1,0,0,0,354,356,1,0,0,0,355,357,5,5,0,0,356,355,1,0,0,0,356,
  	357,1,0,0,0,357,359,1,0,0,0,358,342,1,0,0,0,358,350,1,0,0,0,359,51,1,
  	0,0,0,360,364,5,2,0,0,361,363,3,54,27,0,362,361,1,0,0,0,363,366,1,0,0,
  	0,364,362,1,0,0,0,364,365,1,0,0,0,365,367,1,0,0,0,366,364,1,0,0,0,367,
  	368,5,3,0,0,368,53,1,0,0,0,369,373,3,100,50,0,370,373,3,56,28,0,371,373,
  	3,140,70,0,372,369,1,0,0,0,372,370,1,0,0,0,372,371,1,0,0,0,373,55,1,0,
  	0,0,374,375,5,25,0,0,375,380,3,58,29,0,376,377,5,8,0,0,377,379,3,58,29,
  	0,378,376,1,0,0,0,379,382,1,0,0,0,380,378,1,0,0,0,380,381,1,0,0,0,381,
  	383,1,0,0,0,382,380,1,0,0,0,383,384,5,5,0,0,384,57,1,0,0,0,385,397,5,
  	52,0,0,386,387,5,52,0,0,387,388,5,7,0,0,388,389,5,49,0,0,389,397,5,9,
  	0,0,390,391,3,44,22,0,391,392,5,52,0,0,392,397,1,0,0,0,393,394,3,34,17,
  	0,394,395,5,52,0,0,395,397,1,0,0,0,396,385,1,0,0,0,396,386,1,0,0,0,396,
  	390,1,0,0,0,396,393,1,0,0,0,397,59,1,0,0,0,398,399,5,26,0,0,399,400,3,
  	62,31,0,400,401,3,64,32,0,401,405,5,2,0,0,402,404,3,66,33,0,403,402,1,
  	0,0,0,404,407,1,0,0,0,405,403,1,0,0,0,405,406,1,0,0,0,406,408,1,0,0,0,
  	407,405,1,0,0,0,408,409,5,3,0,0,409,61,1,0,0,0,410,418,5,27,0,0,411,418,
  	5,28,0,0,412,418,5,29,0,0,413,414,5,30,0,0,414,418,5,31,0,0,415,416,5,
  	30,0,0,416,418,5,32,0,0,417,410,1,0,0,0,417,411,1,0,0,0,417,412,1,0,0,
  	0,417,413,1,0,0,0,417,415,1,0,0,0,418,63,1,0,0,0,419,423,5,52,0,0,420,
  	421,5,7,0,0,421,422,5,49,0,0,422,424,5,9,0,0,423,420,1,0,0,0,423,424,
  	1,0,0,0,424,65,1,0,0,0,425,428,3,74,37,0,426,428,3,122,61,0,427,425,1,
  	0,0,0,427,426,1,0,0,0,428,67,1,0,0,0,429,430,5,33,0,0,430,432,3,70,35,
  	0,431,433,5,52,0,0,432,431,1,0,0,0,432,433,1,0,0,0,433,434,1,0,0,0,434,
  	435,5,2,0,0,435,436,3,72,36,0,436,437,5,3,0,0,437,69,1,0,0,0,438,439,
  	7,1,0,0,439,71,1,0,0,0,440,442,8,2,0,0,441,440,1,0,0,0,442,445,1,0,0,
  	0,443,441,1,0,0,0,443,444,1,0,0,0,444,73,1,0,0,0,445,443,1,0,0,0,446,
  	448,3,80,40,0,447,449,3,82,41,0,448,447,1,0,0,0,448,449,1,0,0,0,449,450,
  	1,0,0,0,450,451,3,84,42,0,451,454,1,0,0,0,452,454,3,76,38,0,453,446,1,
  	0,0,0,453,452,1,0,0,0,454,75,1,0,0,0,455,456,5,34,0,0,456,457,5,2,0,0,
  	457,458,3,78,39,0,458,459,5,3,0,0,459,77,1,0,0,0,460,462,8,2,0,0,461,
  	460,1,0,0,0,462,465,1,0,0,0,463,461,1,0,0,0,463,464,1,0,0,0,464,79,1,
  	0,0,0,465,463,1,0,0,0,466,467,7,3,0,0,467,81,1,0,0,0,468,469,5,7,0,0,
  	469,470,5,49,0,0,470,471,5,9,0,0,471,83,1,0,0,0,472,476,5,2,0,0,473,475,
  	3,86,43,0,474,473,1,0,0,0,475,478,1,0,0,0,476,474,1,0,0,0,476,477,1,0,
  	0,0,477,479,1,0,0,0,478,476,1,0,0,0,479,480,5,3,0,0,480,85,1,0,0,0,481,
  	490,3,88,44,0,482,490,3,74,37,0,483,490,3,96,48,0,484,490,3,118,59,0,
  	485,490,3,94,47,0,486,490,3,122,61,0,487,490,3,144,72,0,488,490,3,148,
  	74,0,489,481,1,0,0,0,489,482,1,0,0,0,489,483,1,0,0,0,489,484,1,0,0,0,
  	489,485,1,0,0,0,489,486,1,0,0,0,489,487,1,0,0,0,489,488,1,0,0,0,490,87,
  	1,0,0,0,491,492,3,90,45,0,492,493,5,37,0,0,493,494,3,92,46,0,494,495,
  	5,5,0,0,495,502,1,0,0,0,496,497,3,90,45,0,497,498,5,4,0,0,498,499,3,92,
  	46,0,499,500,5,5,0,0,500,502,1,0,0,0,501,491,1,0,0,0,501,496,1,0,0,0,
  	502,89,1,0,0,0,503,504,5,52,0,0,504,91,1,0,0,0,505,509,5,50,0,0,506,509,
  	5,51,0,0,507,509,3,134,67,0,508,505,1,0,0,0,508,506,1,0,0,0,508,507,1,
  	0,0,0,509,93,1,0,0,0,510,511,7,4,0,0,511,95,1,0,0,0,512,513,5,34,0,0,
  	513,517,5,2,0,0,514,516,3,98,49,0,515,514,1,0,0,0,516,519,1,0,0,0,517,
  	515,1,0,0,0,517,518,1,0,0,0,518,520,1,0,0,0,519,517,1,0,0,0,520,521,5,
  	3,0,0,521,97,1,0,0,0,522,535,3,100,50,0,523,524,3,106,53,0,524,528,5,
  	2,0,0,525,527,3,98,49,0,526,525,1,0,0,0,527,530,1,0,0,0,528,526,1,0,0,
  	0,528,529,1,0,0,0,529,531,1,0,0,0,530,528,1,0,0,0,531,532,5,3,0,0,532,
  	535,1,0,0,0,533,535,3,128,64,0,534,522,1,0,0,0,534,523,1,0,0,0,534,533,
  	1,0,0,0,535,99,1,0,0,0,536,537,3,102,51,0,537,538,5,37,0,0,538,539,3,
  	104,52,0,539,540,5,5,0,0,540,548,1,0,0,0,541,542,3,102,51,0,542,543,5,
  	8,0,0,543,548,1,0,0,0,544,545,3,102,51,0,545,546,5,5,0,0,546,548,1,0,
  	0,0,547,536,1,0,0,0,547,541,1,0,0,0,547,544,1,0,0,0,548,101,1,0,0,0,549,
  	554,5,52,0,0,550,551,5,38,0,0,551,553,5,52,0,0,552,550,1,0,0,0,553,556,
  	1,0,0,0,554,552,1,0,0,0,554,555,1,0,0,0,555,103,1,0,0,0,556,554,1,0,0,
  	0,557,562,5,50,0,0,558,562,5,51,0,0,559,562,3,134,67,0,560,562,3,112,
  	56,0,561,557,1,0,0,0,561,558,1,0,0,0,561,559,1,0,0,0,561,560,1,0,0,0,
  	562,105,1,0,0,0,563,564,5,21,0,0,564,573,5,52,0,0,565,566,5,39,0,0,566,
  	573,5,52,0,0,567,568,5,40,0,0,568,573,3,108,54,0,569,570,5,40,0,0,570,
  	573,3,110,55,0,571,573,5,40,0,0,572,563,1,0,0,0,572,565,1,0,0,0,572,567,
  	1,0,0,0,572,569,1,0,0,0,572,571,1,0,0,0,573,107,1,0,0,0,574,575,5,37,
  	0,0,575,576,5,52,0,0,576,109,1,0,0,0,577,578,5,41,0,0,578,579,5,52,0,
  	0,579,111,1,0,0,0,580,581,5,52,0,0,581,583,5,42,0,0,582,584,3,114,57,
  	0,583,582,1,0,0,0,583,584,1,0,0,0,584,585,1,0,0,0,585,586,5,43,0,0,586,
  	113,1,0,0,0,587,592,3,116,58,0,588,589,5,8,0,0,589,591,3,116,58,0,590,
  	588,1,0,0,0,591,594,1,0,0,0,592,590,1,0,0,0,592,593,1,0,0,0,593,115,1,
  	0,0,0,594,592,1,0,0,0,595,596,3,104,52,0,596,117,1,0,0,0,597,598,5,36,
  	0,0,598,599,5,2,0,0,599,600,3,120,60,0,600,601,5,3,0,0,601,119,1,0,0,
  	0,602,604,8,2,0,0,603,602,1,0,0,0,604,605,1,0,0,0,605,603,1,0,0,0,605,
  	606,1,0,0,0,606,609,1,0,0,0,607,609,1,0,0,0,608,603,1,0,0,0,608,607,1,
  	0,0,0,609,121,1,0,0,0,610,611,3,44,22,0,611,613,5,52,0,0,612,614,3,124,
  	62,0,613,612,1,0,0,0,613,614,1,0,0,0,614,617,1,0,0,0,615,616,5,13,0,0,
  	616,618,3,142,71,0,617,615,1,0,0,0,617,618,1,0,0,0,618,619,1,0,0,0,619,
  	620,5,5,0,0,620,662,1,0,0,0,621,622,3,34,17,0,622,624,5,52,0,0,623,625,
  	3,124,62,0,624,623,1,0,0,0,624,625,1,0,0,0,625,628,1,0,0,0,626,627,5,
  	13,0,0,627,629,3,142,71,0,628,626,1,0,0,0,628,629,1,0,0,0,629,630,1,0,
  	0,0,630,631,5,5,0,0,631,662,1,0,0,0,632,633,5,19,0,0,633,634,3,44,22,
  	0,634,636,5,52,0,0,635,637,3,124,62,0,636,635,1,0,0,0,636,637,1,0,0,0,
  	637,640,1,0,0,0,638,639,5,13,0,0,639,641,3,142,71,0,640,638,1,0,0,0,640,
  	641,1,0,0,0,641,642,1,0,0,0,642,643,5,5,0,0,643,662,1,0,0,0,644,645,5,
  	20,0,0,645,646,3,34,17,0,646,648,5,52,0,0,647,649,3,124,62,0,648,647,
  	1,0,0,0,648,649,1,0,0,0,649,652,1,0,0,0,650,651,5,13,0,0,651,653,3,142,
  	71,0,652,650,1,0,0,0,652,653,1,0,0,0,653,654,1,0,0,0,654,655,5,5,0,0,
  	655,662,1,0,0,0,656,657,5,33,0,0,657,658,3,70,35,0,658,659,5,52,0,0,659,
  	660,5,5,0,0,660,662,1,0,0,0,661,610,1,0,0,0,661,621,1,0,0,0,661,632,1,
  	0,0,0,661,644,1,0,0,0,661,656,1,0,0,0,662,123,1,0,0,0,663,667,5,2,0,0,
  	664,666,3,126,63,0,665,664,1,0,0,0,666,669,1,0,0,0,667,665,1,0,0,0,667,
  	668,1,0,0,0,668,670,1,0,0,0,669,667,1,0,0,0,670,671,5,3,0,0,671,125,1,
  	0,0,0,672,677,3,74,37,0,673,677,3,96,48,0,674,677,3,56,28,0,675,677,3,
  	60,30,0,676,672,1,0,0,0,676,673,1,0,0,0,676,674,1,0,0,0,676,675,1,0,0,
  	0,677,127,1,0,0,0,678,679,3,44,22,0,679,681,5,52,0,0,680,682,3,130,65,
  	0,681,680,1,0,0,0,681,682,1,0,0,0,682,683,1,0,0,0,683,684,5,5,0,0,684,
  	693,1,0,0,0,685,686,3,34,17,0,686,688,5,52,0,0,687,689,3,130,65,0,688,
  	687,1,0,0,0,688,689,1,0,0,0,689,690,1,0,0,0,690,691,5,5,0,0,691,693,1,
  	0,0,0,692,678,1,0,0,0,692,685,1,0,0,0,693,129,1,0,0,0,694,698,5,2,0,0,
  	695,697,3,100,50,0,696,695,1,0,0,0,697,700,1,0,0,0,698,696,1,0,0,0,698,
  	699,1,0,0,0,699,701,1,0,0,0,700,698,1,0,0,0,701,702,5,3,0,0,702,131,1,
  	0,0,0,703,704,5,52,0,0,704,705,5,37,0,0,705,706,5,50,0,0,706,707,5,5,
  	0,0,707,133,1,0,0,0,708,709,5,52,0,0,709,711,5,42,0,0,710,712,3,136,68,
  	0,711,710,1,0,0,0,711,712,1,0,0,0,712,713,1,0,0,0,713,714,5,43,0,0,714,
  	135,1,0,0,0,715,720,3,138,69,0,716,717,5,8,0,0,717,719,3,138,69,0,718,
  	716,1,0,0,0,719,722,1,0,0,0,720,718,1,0,0,0,720,721,1,0,0,0,721,137,1,
  	0,0,0,722,720,1,0,0,0,723,724,5,52,0,0,724,725,5,4,0,0,725,728,3,104,
  	52,0,726,728,5,52,0,0,727,723,1,0,0,0,727,726,1,0,0,0,728,139,1,0,0,0,
  	729,730,5,52,0,0,730,731,5,4,0,0,731,732,3,104,52,0,732,733,5,5,0,0,733,
  	141,1,0,0,0,734,739,5,52,0,0,735,736,5,21,0,0,736,738,5,52,0,0,737,735,
  	1,0,0,0,738,741,1,0,0,0,739,737,1,0,0,0,739,740,1,0,0,0,740,143,1,0,0,
  	0,741,739,1,0,0,0,742,743,5,44,0,0,743,748,3,146,73,0,744,745,5,8,0,0,
  	745,747,3,146,73,0,746,744,1,0,0,0,747,750,1,0,0,0,748,746,1,0,0,0,748,
  	749,1,0,0,0,749,751,1,0,0,0,750,748,1,0,0,0,751,752,5,5,0,0,752,145,1,
  	0,0,0,753,770,5,52,0,0,754,755,3,44,22,0,755,756,5,52,0,0,756,770,1,0,
  	0,0,757,758,3,34,17,0,758,759,5,52,0,0,759,770,1,0,0,0,760,762,5,19,0,
  	0,761,763,3,44,22,0,762,761,1,0,0,0,762,763,1,0,0,0,763,770,1,0,0,0,764,
  	766,5,20,0,0,765,767,3,34,17,0,766,765,1,0,0,0,766,767,1,0,0,0,767,770,
  	1,0,0,0,768,770,5,15,0,0,769,753,1,0,0,0,769,754,1,0,0,0,769,757,1,0,
  	0,0,769,760,1,0,0,0,769,764,1,0,0,0,769,768,1,0,0,0,770,147,1,0,0,0,771,
  	772,7,5,0,0,772,149,1,0,0,0,78,153,168,175,190,194,202,210,218,224,231,
  	237,246,254,257,271,275,282,296,305,316,329,340,345,348,353,356,358,364,
  	372,380,396,405,417,423,427,432,443,448,453,463,476,489,501,508,517,528,
  	534,547,554,561,572,583,592,605,608,613,617,624,628,636,640,648,652,661,
  	667,676,681,688,692,698,711,720,727,739,748,762,766,769
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
    setState(153);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4750019082590210) != 0)) {
      setState(150);
      topLevelStatement();
      setState(155);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(156);
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
    setState(168);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(158);
      configurationBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(159);
      namespaceDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(160);
      importStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(161);
      templateDeclaration();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(162);
      customDeclaration();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(163);
      originBlock();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(164);
      htmlElement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(165);
      styleBlock();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(166);
      scriptBlock();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(167);
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
    setState(170);
    match(CHTLParser::T__0);
    setState(171);
    match(CHTLParser::T__1);
    setState(175);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__5

    || _la == CHTLParser::IDENTIFIER) {
      setState(172);
      configurationItem();
      setState(177);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(178);
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
    setState(194);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(180);
        configKey();
        setState(181);
        match(CHTLParser::T__3);
        setState(182);
        configValue();
        setState(183);
        match(CHTLParser::T__4);
        break;
      }

      case CHTLParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(185);
        match(CHTLParser::T__5);
        setState(186);
        match(CHTLParser::T__1);
        setState(190);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CHTLParser::IDENTIFIER) {
          setState(187);
          nameConfigItem();
          setState(192);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(193);
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
    setState(196);
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
    setState(202);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(198);
        match(CHTLParser::STRING_LITERAL);
        break;
      }

      case CHTLParser::NUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(199);
        match(CHTLParser::NUMBER);
        break;
      }

      case CHTLParser::BOOLEAN: {
        enterOuterAlt(_localctx, 3);
        setState(200);
        match(CHTLParser::BOOLEAN);
        break;
      }

      case CHTLParser::T__6: {
        enterOuterAlt(_localctx, 4);
        setState(201);
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
    setState(204);
    match(CHTLParser::T__6);
    setState(205);
    configArrayItem();
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(206);
      match(CHTLParser::T__7);
      setState(207);
      configArrayItem();
      setState(212);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(213);
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
    setState(218);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__9: {
        enterOuterAlt(_localctx, 1);
        setState(215);
        match(CHTLParser::T__9);
        setState(216);
        match(CHTLParser::IDENTIFIER);
        break;
      }

      case CHTLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(217);
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
    setState(220);
    match(CHTLParser::IDENTIFIER);
    setState(221);
    match(CHTLParser::T__3);
    setState(224);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(222);
      configValue();
      break;
    }

    case 2: {
      setState(223);
      configValueArray();
      break;
    }

    default:
      break;
    }
    setState(226);
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
    setState(228);
    match(CHTLParser::T__10);
    setState(229);
    match(CHTLParser::IDENTIFIER);
    setState(231);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__1) {
      setState(230);
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
    setState(233);
    match(CHTLParser::T__1);
    setState(237);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17592187619328) != 0)) {
      setState(234);
      namespaceContent();
      setState(239);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(240);
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
    setState(246);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__10: {
        enterOuterAlt(_localctx, 1);
        setState(242);
        namespaceDeclaration();
        break;
      }

      case CHTLParser::T__19: {
        enterOuterAlt(_localctx, 2);
        setState(243);
        templateDeclaration();
        break;
      }

      case CHTLParser::T__18: {
        enterOuterAlt(_localctx, 3);
        setState(244);
        customDeclaration();
        break;
      }

      case CHTLParser::T__43: {
        enterOuterAlt(_localctx, 4);
        setState(245);
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
    setState(248);
    match(CHTLParser::T__11);
    setState(249);
    importType();
    setState(250);
    match(CHTLParser::T__12);
    setState(251);
    importPath();
    setState(254);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__13) {
      setState(252);
      match(CHTLParser::T__13);
      setState(253);
      match(CHTLParser::IDENTIFIER);
    }
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__4) {
      setState(256);
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
    setState(271);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__14: {
        enterOuterAlt(_localctx, 1);
        setState(259);
        match(CHTLParser::T__14);
        break;
      }

      case CHTLParser::T__15: {
        enterOuterAlt(_localctx, 2);
        setState(260);
        match(CHTLParser::T__15);
        break;
      }

      case CHTLParser::T__16: {
        enterOuterAlt(_localctx, 3);
        setState(261);
        match(CHTLParser::T__16);
        break;
      }

      case CHTLParser::T__17: {
        enterOuterAlt(_localctx, 4);
        setState(262);
        match(CHTLParser::T__17);
        break;
      }

      case CHTLParser::T__18: {
        enterOuterAlt(_localctx, 5);
        setState(263);
        match(CHTLParser::T__18);
        setState(264);
        customType();
        setState(265);
        match(CHTLParser::IDENTIFIER);
        break;
      }

      case CHTLParser::T__19: {
        enterOuterAlt(_localctx, 6);
        setState(267);
        match(CHTLParser::T__19);
        setState(268);
        templateType();
        setState(269);
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
    setState(275);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(273);
        match(CHTLParser::STRING_LITERAL);
        break;
      }

      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(274);
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
    setState(277);
    match(CHTLParser::IDENTIFIER);
    setState(282);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__20) {
      setState(278);
      match(CHTLParser::T__20);
      setState(279);
      match(CHTLParser::IDENTIFIER);
      setState(284);
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
    setState(285);
    match(CHTLParser::T__19);
    setState(286);
    templateType();
    setState(287);
    match(CHTLParser::IDENTIFIER);
    setState(288);
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
    setState(290);
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
    setState(292);
    match(CHTLParser::T__1);
    setState(296);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503719915880448) != 0)) {
      setState(293);
      templateContent();
      setState(298);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(299);
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
    setState(305);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(301);
      styleProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(302);
      htmlElement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(303);
      templateInheritance();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(304);
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
    setState(316);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__15:
      case CHTLParser::T__21:
      case CHTLParser::T__22: {
        enterOuterAlt(_localctx, 1);
        setState(307);
        templateType();
        setState(308);
        match(CHTLParser::IDENTIFIER);
        setState(309);
        match(CHTLParser::T__4);
        break;
      }

      case CHTLParser::T__23: {
        enterOuterAlt(_localctx, 2);
        setState(311);
        match(CHTLParser::T__23);
        setState(312);
        templateType();
        setState(313);
        match(CHTLParser::IDENTIFIER);
        setState(314);
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
    setState(318);
    match(CHTLParser::T__18);
    setState(319);
    customType();
    setState(320);
    match(CHTLParser::IDENTIFIER);
    setState(321);
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
    setState(323);
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
    setState(325);
    match(CHTLParser::T__1);
    setState(329);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503719999766528) != 0)) {
      setState(326);
      customContent();
      setState(331);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(332);
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
    setState(340);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(334);
      styleProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(335);
      htmlElement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(336);
      customInheritance();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(337);
      variableDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(338);
      deleteStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(339);
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
    setState(358);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(342);
      customType();
      setState(343);
      match(CHTLParser::IDENTIFIER);
      setState(345);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(344);
        customSpecialization();
      }
      setState(348);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__4) {
        setState(347);
        match(CHTLParser::T__4);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(350);
      templateType();
      setState(351);
      match(CHTLParser::IDENTIFIER);
      setState(353);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(352);
        customSpecialization();
      }
      setState(356);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__4) {
        setState(355);
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
    setState(360);
    match(CHTLParser::T__1);
    setState(364);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__24

    || _la == CHTLParser::IDENTIFIER) {
      setState(361);
      specializationContent();
      setState(366);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(367);
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
    setState(372);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(369);
      styleProperty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(370);
      deleteStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(371);
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
    setState(374);
    match(CHTLParser::T__24);
    setState(375);
    deleteTarget();
    setState(380);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(376);
      match(CHTLParser::T__7);
      setState(377);
      deleteTarget();
      setState(382);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(383);
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
    setState(396);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(385);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(386);
      match(CHTLParser::IDENTIFIER);
      setState(387);
      match(CHTLParser::T__6);
      setState(388);
      match(CHTLParser::NUMBER);
      setState(389);
      match(CHTLParser::T__8);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(390);
      customType();
      setState(391);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(393);
      templateType();
      setState(394);
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
    setState(398);
    match(CHTLParser::T__25);
    setState(399);
    insertPosition();
    setState(400);
    elementSelector();
    setState(401);
    match(CHTLParser::T__1);
    setState(405);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503728490610688) != 0)) {
      setState(402);
      insertContent();
      setState(407);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(408);
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
    setState(417);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(410);
      match(CHTLParser::T__26);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(411);
      match(CHTLParser::T__27);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(412);
      match(CHTLParser::T__28);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(413);
      match(CHTLParser::T__29);
      setState(414);
      match(CHTLParser::T__30);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(415);
      match(CHTLParser::T__29);
      setState(416);
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
    setState(419);
    match(CHTLParser::IDENTIFIER);
    setState(423);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::T__6) {
      setState(420);
      match(CHTLParser::T__6);
      setState(421);
      match(CHTLParser::NUMBER);
      setState(422);
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
    setState(427);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::T__33:
      case CHTLParser::T__34:
      case CHTLParser::T__35:
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(425);
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
        setState(426);
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
    setState(429);
    match(CHTLParser::T__32);
    setState(430);
    originType();
    setState(432);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::IDENTIFIER) {
      setState(431);
      match(CHTLParser::IDENTIFIER);
    }
    setState(434);
    match(CHTLParser::T__1);
    setState(435);
    originContent();
    setState(436);
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
    setState(438);
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
    setState(443);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 18014398509481974) != 0)) {
      setState(440);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == CHTLParser::T__2)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(445);
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

CHTLParser::GlobalStyleElementContext* CHTLParser::HtmlElementContext::globalStyleElement() {
  return getRuleContext<CHTLParser::GlobalStyleElementContext>(0);
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
    setState(453);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(446);
      elementName();
      setState(448);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__6) {
        setState(447);
        elementIndexAccess();
      }
      setState(450);
      elementBody();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(452);
      globalStyleElement();
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

//----------------- GlobalStyleElementContext ------------------------------------------------------------------

CHTLParser::GlobalStyleElementContext::GlobalStyleElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::GlobalStyleContentContext* CHTLParser::GlobalStyleElementContext::globalStyleContent() {
  return getRuleContext<CHTLParser::GlobalStyleContentContext>(0);
}


size_t CHTLParser::GlobalStyleElementContext::getRuleIndex() const {
  return CHTLParser::RuleGlobalStyleElement;
}

void CHTLParser::GlobalStyleElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobalStyleElement(this);
}

void CHTLParser::GlobalStyleElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobalStyleElement(this);
}

CHTLParser::GlobalStyleElementContext* CHTLParser::globalStyleElement() {
  GlobalStyleElementContext *_localctx = _tracker.createInstance<GlobalStyleElementContext>(_ctx, getState());
  enterRule(_localctx, 76, CHTLParser::RuleGlobalStyleElement);

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
    match(CHTLParser::T__33);
    setState(456);
    match(CHTLParser::T__1);
    setState(457);
    globalStyleContent();
    setState(458);
    match(CHTLParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalStyleContentContext ------------------------------------------------------------------

CHTLParser::GlobalStyleContentContext::GlobalStyleContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CHTLParser::GlobalStyleContentContext::getRuleIndex() const {
  return CHTLParser::RuleGlobalStyleContent;
}

void CHTLParser::GlobalStyleContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobalStyleContent(this);
}

void CHTLParser::GlobalStyleContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobalStyleContent(this);
}

CHTLParser::GlobalStyleContentContext* CHTLParser::globalStyleContent() {
  GlobalStyleContentContext *_localctx = _tracker.createInstance<GlobalStyleContentContext>(_ctx, getState());
  enterRule(_localctx, 78, CHTLParser::RuleGlobalStyleContent);
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
    setState(463);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 18014398509481974) != 0)) {
      setState(460);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == CHTLParser::T__2)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(465);
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
  enterRule(_localctx, 80, CHTLParser::RuleElementName);
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
  enterRule(_localctx, 82, CHTLParser::RuleElementIndexAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(468);
    match(CHTLParser::T__6);
    setState(469);
    match(CHTLParser::NUMBER);
    setState(470);
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
  enterRule(_localctx, 84, CHTLParser::RuleElementBody);
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
    setState(472);
    match(CHTLParser::T__1);
    setState(476);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8145311001804800) != 0)) {
      setState(473);
      elementContent();
      setState(478);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(479);
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
  enterRule(_localctx, 86, CHTLParser::RuleElementContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(489);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(481);
      attribute();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(482);
      htmlElement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(483);
      styleBlock();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(484);
      scriptBlock();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(485);
      textContent();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(486);
      elementUsage();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(487);
      exceptConstraint();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(488);
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
  enterRule(_localctx, 88, CHTLParser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(501);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(491);
      attributeName();
      setState(492);
      match(CHTLParser::T__36);
      setState(493);
      attributeValue();
      setState(494);
      match(CHTLParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(496);
      attributeName();
      setState(497);
      match(CHTLParser::T__3);
      setState(498);
      attributeValue();
      setState(499);
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
  enterRule(_localctx, 90, CHTLParser::RuleAttributeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(503);
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
  enterRule(_localctx, 92, CHTLParser::RuleAttributeValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(508);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(505);
        match(CHTLParser::STRING_LITERAL);
        break;
      }

      case CHTLParser::UNQUOTED_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(506);
        match(CHTLParser::UNQUOTED_LITERAL);
        break;
      }

      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(507);
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
  enterRule(_localctx, 94, CHTLParser::RuleTextContent);
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
  enterRule(_localctx, 96, CHTLParser::RuleStyleBlock);
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
    setState(512);
    match(CHTLParser::T__33);
    setState(513);
    match(CHTLParser::T__1);
    setState(517);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4505248909557760) != 0)) {
      setState(514);
      styleContent();
      setState(519);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(520);
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
  enterRule(_localctx, 98, CHTLParser::RuleStyleContent);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(534);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(522);
        styleProperty();
        break;
      }

      case CHTLParser::T__20:
      case CHTLParser::T__38:
      case CHTLParser::T__39: {
        enterOuterAlt(_localctx, 2);
        setState(523);
        cssSelector();
        setState(524);
        match(CHTLParser::T__1);
        setState(528);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4505248909557760) != 0)) {
          setState(525);
          styleContent();
          setState(530);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(531);
        match(CHTLParser::T__2);
        break;
      }

      case CHTLParser::T__15:
      case CHTLParser::T__21:
      case CHTLParser::T__22: {
        enterOuterAlt(_localctx, 3);
        setState(533);
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
  enterRule(_localctx, 100, CHTLParser::RuleStyleProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(547);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(536);
      propertyName();
      setState(537);
      match(CHTLParser::T__36);
      setState(538);
      propertyValue();
      setState(539);
      match(CHTLParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(541);
      propertyName();
      setState(542);
      match(CHTLParser::T__7);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(544);
      propertyName();
      setState(545);
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
  enterRule(_localctx, 102, CHTLParser::RulePropertyName);
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
    setState(549);
    match(CHTLParser::IDENTIFIER);
    setState(554);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__37) {
      setState(550);
      match(CHTLParser::T__37);
      setState(551);
      match(CHTLParser::IDENTIFIER);
      setState(556);
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
  enterRule(_localctx, 104, CHTLParser::RulePropertyValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(561);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(557);
      match(CHTLParser::STRING_LITERAL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(558);
      match(CHTLParser::UNQUOTED_LITERAL);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(559);
      variableUsage();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(560);
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
  enterRule(_localctx, 106, CHTLParser::RuleCssSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(572);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(563);
      match(CHTLParser::T__20);
      setState(564);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(565);
      match(CHTLParser::T__38);
      setState(566);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(567);
      match(CHTLParser::T__39);
      setState(568);
      pseudoClass();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(569);
      match(CHTLParser::T__39);
      setState(570);
      pseudoElement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(571);
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
  enterRule(_localctx, 108, CHTLParser::RulePseudoClass);

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
    match(CHTLParser::T__36);
    setState(575);
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
  enterRule(_localctx, 110, CHTLParser::RulePseudoElement);

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
    match(CHTLParser::T__40);
    setState(578);
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
  enterRule(_localctx, 112, CHTLParser::RuleCssFunction);
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
    setState(580);
    match(CHTLParser::IDENTIFIER);
    setState(581);
    match(CHTLParser::T__41);
    setState(583);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7881299347898368) != 0)) {
      setState(582);
      cssArguments();
    }
    setState(585);
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
  enterRule(_localctx, 114, CHTLParser::RuleCssArguments);
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
    cssArgument();
    setState(592);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(588);
      match(CHTLParser::T__7);
      setState(589);
      cssArgument();
      setState(594);
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
  enterRule(_localctx, 116, CHTLParser::RuleCssArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(595);
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
  enterRule(_localctx, 118, CHTLParser::RuleScriptBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(597);
    match(CHTLParser::T__35);
    setState(598);
    match(CHTLParser::T__1);
    setState(599);
    scriptContent();
    setState(600);
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
  enterRule(_localctx, 120, CHTLParser::RuleScriptContent);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(608);
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
        setState(603); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(602);
          _la = _input->LA(1);
          if (_la == 0 || _la == Token::EOF || (_la == CHTLParser::T__2)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(605); 
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
  enterRule(_localctx, 122, CHTLParser::RuleElementUsage);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(661);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(610);
      customType();
      setState(611);
      match(CHTLParser::IDENTIFIER);
      setState(613);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(612);
        elementSpecialization();
      }
      setState(617);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__12) {
        setState(615);
        match(CHTLParser::T__12);
        setState(616);
        namespacePath();
      }
      setState(619);
      match(CHTLParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(621);
      templateType();
      setState(622);
      match(CHTLParser::IDENTIFIER);
      setState(624);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(623);
        elementSpecialization();
      }
      setState(628);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__12) {
        setState(626);
        match(CHTLParser::T__12);
        setState(627);
        namespacePath();
      }
      setState(630);
      match(CHTLParser::T__4);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(632);
      match(CHTLParser::T__18);
      setState(633);
      customType();
      setState(634);
      match(CHTLParser::IDENTIFIER);
      setState(636);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(635);
        elementSpecialization();
      }
      setState(640);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__12) {
        setState(638);
        match(CHTLParser::T__12);
        setState(639);
        namespacePath();
      }
      setState(642);
      match(CHTLParser::T__4);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(644);
      match(CHTLParser::T__19);
      setState(645);
      templateType();
      setState(646);
      match(CHTLParser::IDENTIFIER);
      setState(648);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(647);
        elementSpecialization();
      }
      setState(652);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__12) {
        setState(650);
        match(CHTLParser::T__12);
        setState(651);
        namespacePath();
      }
      setState(654);
      match(CHTLParser::T__4);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(656);
      match(CHTLParser::T__32);
      setState(657);
      originType();
      setState(658);
      match(CHTLParser::IDENTIFIER);
      setState(659);
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
  enterRule(_localctx, 124, CHTLParser::RuleElementSpecialization);
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
    setState(663);
    match(CHTLParser::T__1);
    setState(667);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503719987118080) != 0)) {
      setState(664);
      elementSpecializationContent();
      setState(669);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(670);
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
  enterRule(_localctx, 126, CHTLParser::RuleElementSpecializationContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(676);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(672);
      htmlElement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(673);
      styleBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(674);
      deleteStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(675);
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
  enterRule(_localctx, 128, CHTLParser::RuleStyleUsage);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(692);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(678);
      customType();
      setState(679);
      match(CHTLParser::IDENTIFIER);
      setState(681);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(680);
        styleSpecialization();
      }
      setState(683);
      match(CHTLParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(685);
      templateType();
      setState(686);
      match(CHTLParser::IDENTIFIER);
      setState(688);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLParser::T__1) {
        setState(687);
        styleSpecialization();
      }
      setState(690);
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
  enterRule(_localctx, 130, CHTLParser::RuleStyleSpecialization);
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
    setState(694);
    match(CHTLParser::T__1);
    setState(698);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::IDENTIFIER) {
      setState(695);
      styleProperty();
      setState(700);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(701);
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
  enterRule(_localctx, 132, CHTLParser::RuleVariableDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(703);
    match(CHTLParser::IDENTIFIER);
    setState(704);
    match(CHTLParser::T__36);
    setState(705);
    match(CHTLParser::STRING_LITERAL);
    setState(706);
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
  enterRule(_localctx, 134, CHTLParser::RuleVariableUsage);
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
    setState(708);
    match(CHTLParser::IDENTIFIER);
    setState(709);
    match(CHTLParser::T__41);
    setState(711);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::IDENTIFIER) {
      setState(710);
      variableArguments();
    }
    setState(713);
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
  enterRule(_localctx, 136, CHTLParser::RuleVariableArguments);
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
    setState(715);
    variableArgument();
    setState(720);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(716);
      match(CHTLParser::T__7);
      setState(717);
      variableArgument();
      setState(722);
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
  enterRule(_localctx, 138, CHTLParser::RuleVariableArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(727);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(723);
      match(CHTLParser::IDENTIFIER);
      setState(724);
      match(CHTLParser::T__3);
      setState(725);
      propertyValue();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(726);
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
  enterRule(_localctx, 140, CHTLParser::RuleVariableAssignment);

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
    match(CHTLParser::IDENTIFIER);
    setState(730);
    match(CHTLParser::T__3);
    setState(731);
    propertyValue();
    setState(732);
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
  enterRule(_localctx, 142, CHTLParser::RuleNamespacePath);
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
    setState(734);
    match(CHTLParser::IDENTIFIER);
    setState(739);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__20) {
      setState(735);
      match(CHTLParser::T__20);
      setState(736);
      match(CHTLParser::IDENTIFIER);
      setState(741);
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
  enterRule(_localctx, 144, CHTLParser::RuleExceptConstraint);
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
    setState(742);
    match(CHTLParser::T__43);
    setState(743);
    exceptTarget();
    setState(748);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::T__7) {
      setState(744);
      match(CHTLParser::T__7);
      setState(745);
      exceptTarget();
      setState(750);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(751);
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
  enterRule(_localctx, 146, CHTLParser::RuleExceptTarget);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(769);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(753);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(754);
      customType();
      setState(755);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(757);
      templateType();
      setState(758);
      match(CHTLParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(760);
      match(CHTLParser::T__18);
      setState(762);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 12648448) != 0)) {
        setState(761);
        customType();
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(764);
      match(CHTLParser::T__19);
      setState(766);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 12648448) != 0)) {
        setState(765);
        templateType();
      }
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(768);
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
  enterRule(_localctx, 148, CHTLParser::RuleComment);
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
    setState(771);
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
