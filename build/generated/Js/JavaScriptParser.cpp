
// Generated from /workspace/grammar/JavaScript.g4 by ANTLR 4.10


#include "JavaScriptVisitor.h"

#include "JavaScriptParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct JavaScriptParserStaticData final {
  JavaScriptParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  JavaScriptParserStaticData(const JavaScriptParserStaticData&) = delete;
  JavaScriptParserStaticData(JavaScriptParserStaticData&&) = delete;
  JavaScriptParserStaticData& operator=(const JavaScriptParserStaticData&) = delete;
  JavaScriptParserStaticData& operator=(JavaScriptParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag javascriptParserOnceFlag;
JavaScriptParserStaticData *javascriptParserStaticData = nullptr;

void javascriptParserInitialize() {
  assert(javascriptParserStaticData == nullptr);
  auto staticData = std::make_unique<JavaScriptParserStaticData>(
    std::vector<std::string>{
      "program", "statement", "block", "variableStatement", "variableDeclarationList", 
      "varModifier", "variableDeclaration", "emptyStatement", "expressionStatement", 
      "ifStatement", "iterationStatement", "continueStatement", "breakStatement", 
      "returnStatement", "withStatement", "labelledStatement", "switchStatement", 
      "caseBlock", "caseClauses", "caseClause", "defaultClause", "throwStatement", 
      "tryStatement", "catchClause", "finallyClause", "functionDeclaration", 
      "classDeclaration", "classTail", "classElement", "methodDefinition", 
      "getter", "setter", "generatorMethod", "asyncMethod", "importStatement", 
      "importFromBlock", "importNamespace", "importSpecifier", "moduleExportName", 
      "exportStatement", "exportFromBlock", "exportNamespace", "exportSpecifier", 
      "declaration", "formalParameterList", "formalParameter", "restParameter", 
      "assignable", "propertyName", "expressionSequence", "singleExpression", 
      "assignmentOperator", "literal", "arrayLiteral", "elementList", "arrayElement", 
      "objectLiteral", "propertyAssignment", "arguments", "argumentList", 
      "argument", "anonymousFunction", "arrowFunction", "arrowFunctionParameters", 
      "arrowFunctionBody", "typeofExpression", "identifierName", "reservedWord", 
      "keyword"
    },
    std::vector<std::string>{
      "", "'break'", "'do'", "'instanceof'", "'typeof'", "'case'", "'else'", 
      "'new'", "'var'", "'catch'", "'finally'", "'return'", "'void'", "'continue'", 
      "'for'", "'switch'", "'while'", "'debugger'", "'function'", "'this'", 
      "'with'", "'default'", "'if'", "'throw'", "'delete'", "'in'", "'try'", 
      "'class'", "'enum'", "'extends'", "'super'", "'const'", "'export'", 
      "'import'", "'async'", "'await'", "'yield'", "'let'", "'static'", 
      "'from'", "'as'", "'of'", "'get'", "'set'", "'null'", "", "'undefined'", 
      "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "','", "'.'", "'\\u003F'", 
      "':'", "'...'", "'='", "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", 
      "'>>='", "'>>>='", "'&='", "'^='", "'|='", "'**='", "'\\u003F\\u003F='", 
      "'=>'", "'++'", "'--'", "'+'", "'-'", "'~'", "'!'", "'*'", "'/'", 
      "'%'", "'**'", "'\\u003F\\u003F'", "'<<'", "'>>'", "'>>>'", "'<'", 
      "'>'", "'<='", "'>='", "'=='", "'!='", "'==='", "'!=='", "'&'", "'^'", 
      "'|'", "'&&'", "'||'", "", "", "", "'`'"
    },
    std::vector<std::string>{
      "", "BREAK", "DO", "INSTANCEOF", "TYPEOF", "CASE", "ELSE", "NEW", 
      "VAR", "CATCH", "FINALLY", "RETURN", "VOID", "CONTINUE", "FOR", "SWITCH", 
      "WHILE", "DEBUGGER", "FUNCTION", "THIS", "WITH", "DEFAULT", "IF", 
      "THROW", "DELETE", "IN", "TRY", "CLASS", "ENUM", "EXTENDS", "SUPER", 
      "CONST", "EXPORT", "IMPORT", "ASYNC", "AWAIT", "YIELD", "LET", "STATIC", 
      "FROM", "AS", "OF", "GET", "SET", "NULL_LITERAL", "BOOLEAN", "UNDEFINED", 
      "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "SEMICOLON", 
      "COMMA", "DOT", "QUESTION", "COLON", "ELLIPSIS", "EQUALS", "STAR_EQUALS", 
      "SLASH_EQUALS", "PERCENT_EQUALS", "PLUS_EQUALS", "MINUS_EQUALS", "LSHIFT_EQUALS", 
      "RSHIFT_EQUALS", "URSHIFT_EQUALS", "AMPERSAND_EQUALS", "CARET_EQUALS", 
      "PIPE_EQUALS", "POWER_EQUALS", "NULLISH_EQUALS", "ARROW", "PLUSPLUS", 
      "MINUSMINUS", "PLUS", "MINUS", "TILDE", "EXCLAMATION", "STAR", "SLASH", 
      "PERCENT", "POWER", "NULLISH_COALESCING", "LSHIFT", "RSHIFT", "URSHIFT", 
      "LT", "GT", "LE", "GE", "EQUALS_OP", "NOT_EQUALS", "STRICT_EQUALS", 
      "STRICT_NOT_EQUALS", "AMPERSAND", "CARET", "PIPE", "AND_OP", "OR_OP", 
      "NUMBER", "BIGINT", "STRING", "BACKTICK", "TEMPLATE_STRING", "REGEX", 
      "IDENTIFIER", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,110,824,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,1,0,5,0,140,8,0,
  	10,0,12,0,143,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,165,8,1,1,2,1,2,5,2,169,8,2,10,2,12,2,
  	172,9,2,1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,4,1,4,5,4,183,8,4,10,4,12,4,186,
  	9,4,1,5,1,5,1,6,1,6,1,6,3,6,193,8,6,1,7,1,7,1,8,1,8,1,8,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,3,9,207,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,227,8,10,1,10,1,10,
  	3,10,231,8,10,1,10,1,10,3,10,235,8,10,1,10,1,10,1,10,1,10,1,10,1,10,3,
  	10,243,8,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,254,8,10,
  	1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,266,8,10,1,10,
  	1,10,1,10,1,10,1,10,3,10,273,8,10,1,11,1,11,3,11,277,8,11,1,11,1,11,1,
  	12,1,12,3,12,283,8,12,1,12,1,12,1,13,1,13,3,13,289,8,13,1,13,1,13,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,17,1,17,3,17,311,8,17,1,17,1,17,3,17,315,8,17,3,17,317,8,17,1,
  	17,1,17,1,18,4,18,322,8,18,11,18,12,18,323,1,19,1,19,1,19,1,19,5,19,330,
  	8,19,10,19,12,19,333,9,19,1,20,1,20,1,20,5,20,338,8,20,10,20,12,20,341,
  	9,20,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,3,22,351,8,22,1,22,3,22,
  	354,8,22,1,23,1,23,1,23,1,23,1,23,3,23,361,8,23,1,23,1,23,1,24,1,24,1,
  	24,1,25,3,25,369,8,25,1,25,1,25,3,25,373,8,25,1,25,1,25,1,25,3,25,378,
  	8,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,3,26,387,8,26,1,26,1,26,1,27,
  	1,27,5,27,393,8,27,10,27,12,27,396,9,27,1,27,1,27,1,28,3,28,401,8,28,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,28,3,28,410,8,28,1,29,1,29,1,29,3,29,
  	415,8,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,3,29,424,8,29,1,30,1,30,1,
  	30,1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,
  	32,3,32,443,8,32,1,32,1,32,1,32,1,33,1,33,1,33,1,33,3,33,452,8,33,1,33,
  	1,33,1,33,1,34,1,34,1,34,3,34,460,8,34,1,34,1,34,1,35,1,35,1,35,1,35,
  	3,35,468,8,35,1,35,1,35,1,35,1,36,1,36,1,36,1,36,5,36,477,8,36,10,36,
  	12,36,480,9,36,3,36,482,8,36,1,36,1,36,1,37,1,37,3,37,488,8,37,1,37,1,
  	37,3,37,492,8,37,1,38,1,38,1,39,1,39,1,39,3,39,499,8,39,1,39,1,39,1,39,
  	1,39,1,39,1,39,1,39,3,39,508,8,39,1,40,1,40,3,40,512,8,40,1,40,1,40,1,
  	40,1,41,1,41,1,41,1,41,5,41,521,8,41,10,41,12,41,524,9,41,3,41,526,8,
  	41,1,41,1,41,1,42,1,42,3,42,532,8,42,1,42,1,42,3,42,536,8,42,1,43,1,43,
  	1,43,3,43,541,8,43,1,44,1,44,1,44,5,44,546,8,44,10,44,12,44,549,9,44,
  	1,44,1,44,3,44,553,8,44,1,44,3,44,556,8,44,1,45,1,45,1,45,3,45,561,8,
  	45,1,46,1,46,1,46,1,47,1,47,1,47,3,47,569,8,47,1,48,1,48,1,48,1,48,1,
  	48,1,48,1,48,3,48,578,8,48,1,49,1,49,1,49,5,49,583,8,49,10,49,12,49,586,
  	9,49,1,50,1,50,1,50,1,50,1,50,1,50,3,50,594,8,50,1,50,1,50,1,50,1,50,
  	1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,
  	1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,3,50,
  	627,8,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,
  	1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,
  	1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,
  	1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,
  	1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,
  	1,50,5,50,698,8,50,10,50,12,50,701,9,50,1,51,1,51,1,52,1,52,1,53,1,53,
  	3,53,709,8,53,1,53,1,53,1,54,1,54,1,54,5,54,716,8,54,10,54,12,54,719,
  	9,54,1,55,3,55,722,8,55,1,55,1,55,3,55,726,8,55,1,56,1,56,1,56,1,56,5,
  	56,732,8,56,10,56,12,56,735,9,56,1,56,3,56,738,8,56,1,56,1,56,1,57,1,
  	57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,3,57,756,
  	8,57,1,58,1,58,3,58,760,8,58,1,58,1,58,1,59,1,59,1,59,5,59,767,8,59,10,
  	59,12,59,770,9,59,1,60,3,60,773,8,60,1,60,1,60,1,61,3,61,778,8,61,1,61,
  	1,61,3,61,782,8,61,1,61,1,61,3,61,786,8,61,1,61,1,61,1,61,1,62,3,62,792,
  	8,62,1,62,1,62,1,62,1,62,1,63,1,63,1,63,3,63,801,8,63,1,63,3,63,804,8,
  	63,1,64,1,64,3,64,808,8,64,1,65,1,65,1,65,1,66,1,66,3,66,815,8,66,1,67,
  	1,67,1,67,3,67,820,8,67,1,68,1,68,1,68,0,1,100,69,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,
  	62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,
  	106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,0,10,
  	3,0,8,8,31,31,37,37,2,0,103,103,107,107,1,0,80,82,1,0,76,77,1,0,85,87,
  	1,0,88,91,1,0,92,95,1,0,60,72,4,0,44,46,101,101,103,103,105,105,1,0,1,
  	41,906,0,141,1,0,0,0,2,164,1,0,0,0,4,166,1,0,0,0,6,175,1,0,0,0,8,178,
  	1,0,0,0,10,187,1,0,0,0,12,189,1,0,0,0,14,194,1,0,0,0,16,196,1,0,0,0,18,
  	199,1,0,0,0,20,272,1,0,0,0,22,274,1,0,0,0,24,280,1,0,0,0,26,286,1,0,0,
  	0,28,292,1,0,0,0,30,298,1,0,0,0,32,302,1,0,0,0,34,308,1,0,0,0,36,321,
  	1,0,0,0,38,325,1,0,0,0,40,334,1,0,0,0,42,342,1,0,0,0,44,346,1,0,0,0,46,
  	355,1,0,0,0,48,364,1,0,0,0,50,368,1,0,0,0,52,382,1,0,0,0,54,390,1,0,0,
  	0,56,409,1,0,0,0,58,423,1,0,0,0,60,425,1,0,0,0,62,431,1,0,0,0,64,438,
  	1,0,0,0,66,447,1,0,0,0,68,456,1,0,0,0,70,467,1,0,0,0,72,472,1,0,0,0,74,
  	487,1,0,0,0,76,493,1,0,0,0,78,507,1,0,0,0,80,511,1,0,0,0,82,516,1,0,0,
  	0,84,531,1,0,0,0,86,540,1,0,0,0,88,555,1,0,0,0,90,557,1,0,0,0,92,562,
  	1,0,0,0,94,568,1,0,0,0,96,577,1,0,0,0,98,579,1,0,0,0,100,626,1,0,0,0,
  	102,702,1,0,0,0,104,704,1,0,0,0,106,706,1,0,0,0,108,712,1,0,0,0,110,725,
  	1,0,0,0,112,727,1,0,0,0,114,755,1,0,0,0,116,757,1,0,0,0,118,763,1,0,0,
  	0,120,772,1,0,0,0,122,777,1,0,0,0,124,791,1,0,0,0,126,803,1,0,0,0,128,
  	807,1,0,0,0,130,809,1,0,0,0,132,814,1,0,0,0,134,819,1,0,0,0,136,821,1,
  	0,0,0,138,140,3,2,1,0,139,138,1,0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,
  	141,142,1,0,0,0,142,144,1,0,0,0,143,141,1,0,0,0,144,145,5,0,0,1,145,1,
  	1,0,0,0,146,165,3,4,2,0,147,165,3,6,3,0,148,165,3,14,7,0,149,165,3,16,
  	8,0,150,165,3,18,9,0,151,165,3,20,10,0,152,165,3,22,11,0,153,165,3,24,
  	12,0,154,165,3,26,13,0,155,165,3,28,14,0,156,165,3,30,15,0,157,165,3,
  	32,16,0,158,165,3,42,21,0,159,165,3,44,22,0,160,165,3,50,25,0,161,165,
  	3,52,26,0,162,165,3,68,34,0,163,165,3,78,39,0,164,146,1,0,0,0,164,147,
  	1,0,0,0,164,148,1,0,0,0,164,149,1,0,0,0,164,150,1,0,0,0,164,151,1,0,0,
  	0,164,152,1,0,0,0,164,153,1,0,0,0,164,154,1,0,0,0,164,155,1,0,0,0,164,
  	156,1,0,0,0,164,157,1,0,0,0,164,158,1,0,0,0,164,159,1,0,0,0,164,160,1,
  	0,0,0,164,161,1,0,0,0,164,162,1,0,0,0,164,163,1,0,0,0,165,3,1,0,0,0,166,
  	170,5,49,0,0,167,169,3,2,1,0,168,167,1,0,0,0,169,172,1,0,0,0,170,168,
  	1,0,0,0,170,171,1,0,0,0,171,173,1,0,0,0,172,170,1,0,0,0,173,174,5,50,
  	0,0,174,5,1,0,0,0,175,176,3,8,4,0,176,177,5,53,0,0,177,7,1,0,0,0,178,
  	179,3,10,5,0,179,184,3,12,6,0,180,181,5,54,0,0,181,183,3,12,6,0,182,180,
  	1,0,0,0,183,186,1,0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,9,1,0,0,0,
  	186,184,1,0,0,0,187,188,7,0,0,0,188,11,1,0,0,0,189,192,3,94,47,0,190,
  	191,5,59,0,0,191,193,3,100,50,0,192,190,1,0,0,0,192,193,1,0,0,0,193,13,
  	1,0,0,0,194,195,5,53,0,0,195,15,1,0,0,0,196,197,3,98,49,0,197,198,5,53,
  	0,0,198,17,1,0,0,0,199,200,5,22,0,0,200,201,5,47,0,0,201,202,3,98,49,
  	0,202,203,5,48,0,0,203,206,3,2,1,0,204,205,5,6,0,0,205,207,3,2,1,0,206,
  	204,1,0,0,0,206,207,1,0,0,0,207,19,1,0,0,0,208,209,5,2,0,0,209,210,3,
  	2,1,0,210,211,5,16,0,0,211,212,5,47,0,0,212,213,3,98,49,0,213,214,5,48,
  	0,0,214,215,5,53,0,0,215,273,1,0,0,0,216,217,5,16,0,0,217,218,5,47,0,
  	0,218,219,3,98,49,0,219,220,5,48,0,0,220,221,3,2,1,0,221,273,1,0,0,0,
  	222,223,5,14,0,0,223,226,5,47,0,0,224,227,3,98,49,0,225,227,3,8,4,0,226,
  	224,1,0,0,0,226,225,1,0,0,0,226,227,1,0,0,0,227,228,1,0,0,0,228,230,5,
  	53,0,0,229,231,3,98,49,0,230,229,1,0,0,0,230,231,1,0,0,0,231,232,1,0,
  	0,0,232,234,5,53,0,0,233,235,3,98,49,0,234,233,1,0,0,0,234,235,1,0,0,
  	0,235,236,1,0,0,0,236,237,5,48,0,0,237,273,3,2,1,0,238,239,5,14,0,0,239,
  	242,5,47,0,0,240,243,3,100,50,0,241,243,3,8,4,0,242,240,1,0,0,0,242,241,
  	1,0,0,0,243,244,1,0,0,0,244,245,5,25,0,0,245,246,3,98,49,0,246,247,5,
  	48,0,0,247,248,3,2,1,0,248,273,1,0,0,0,249,250,5,14,0,0,250,253,5,47,
  	0,0,251,254,3,100,50,0,252,254,3,8,4,0,253,251,1,0,0,0,253,252,1,0,0,
  	0,254,255,1,0,0,0,255,256,5,41,0,0,256,257,3,98,49,0,257,258,5,48,0,0,
  	258,259,3,2,1,0,259,273,1,0,0,0,260,261,5,14,0,0,261,262,5,35,0,0,262,
  	265,5,47,0,0,263,266,3,100,50,0,264,266,3,8,4,0,265,263,1,0,0,0,265,264,
  	1,0,0,0,266,267,1,0,0,0,267,268,5,41,0,0,268,269,3,98,49,0,269,270,5,
  	48,0,0,270,271,3,2,1,0,271,273,1,0,0,0,272,208,1,0,0,0,272,216,1,0,0,
  	0,272,222,1,0,0,0,272,238,1,0,0,0,272,249,1,0,0,0,272,260,1,0,0,0,273,
  	21,1,0,0,0,274,276,5,13,0,0,275,277,5,107,0,0,276,275,1,0,0,0,276,277,
  	1,0,0,0,277,278,1,0,0,0,278,279,5,53,0,0,279,23,1,0,0,0,280,282,5,1,0,
  	0,281,283,5,107,0,0,282,281,1,0,0,0,282,283,1,0,0,0,283,284,1,0,0,0,284,
  	285,5,53,0,0,285,25,1,0,0,0,286,288,5,11,0,0,287,289,3,98,49,0,288,287,
  	1,0,0,0,288,289,1,0,0,0,289,290,1,0,0,0,290,291,5,53,0,0,291,27,1,0,0,
  	0,292,293,5,20,0,0,293,294,5,47,0,0,294,295,3,98,49,0,295,296,5,48,0,
  	0,296,297,3,2,1,0,297,29,1,0,0,0,298,299,5,107,0,0,299,300,5,57,0,0,300,
  	301,3,2,1,0,301,31,1,0,0,0,302,303,5,15,0,0,303,304,5,47,0,0,304,305,
  	3,98,49,0,305,306,5,48,0,0,306,307,3,34,17,0,307,33,1,0,0,0,308,310,5,
  	49,0,0,309,311,3,36,18,0,310,309,1,0,0,0,310,311,1,0,0,0,311,316,1,0,
  	0,0,312,314,3,40,20,0,313,315,3,36,18,0,314,313,1,0,0,0,314,315,1,0,0,
  	0,315,317,1,0,0,0,316,312,1,0,0,0,316,317,1,0,0,0,317,318,1,0,0,0,318,
  	319,5,50,0,0,319,35,1,0,0,0,320,322,3,38,19,0,321,320,1,0,0,0,322,323,
  	1,0,0,0,323,321,1,0,0,0,323,324,1,0,0,0,324,37,1,0,0,0,325,326,5,5,0,
  	0,326,327,3,98,49,0,327,331,5,57,0,0,328,330,3,2,1,0,329,328,1,0,0,0,
  	330,333,1,0,0,0,331,329,1,0,0,0,331,332,1,0,0,0,332,39,1,0,0,0,333,331,
  	1,0,0,0,334,335,5,21,0,0,335,339,5,57,0,0,336,338,3,2,1,0,337,336,1,0,
  	0,0,338,341,1,0,0,0,339,337,1,0,0,0,339,340,1,0,0,0,340,41,1,0,0,0,341,
  	339,1,0,0,0,342,343,5,23,0,0,343,344,3,98,49,0,344,345,5,53,0,0,345,43,
  	1,0,0,0,346,347,5,26,0,0,347,353,3,4,2,0,348,350,3,46,23,0,349,351,3,
  	48,24,0,350,349,1,0,0,0,350,351,1,0,0,0,351,354,1,0,0,0,352,354,3,48,
  	24,0,353,348,1,0,0,0,353,352,1,0,0,0,354,45,1,0,0,0,355,360,5,9,0,0,356,
  	357,5,47,0,0,357,358,3,94,47,0,358,359,5,48,0,0,359,361,1,0,0,0,360,356,
  	1,0,0,0,360,361,1,0,0,0,361,362,1,0,0,0,362,363,3,4,2,0,363,47,1,0,0,
  	0,364,365,5,10,0,0,365,366,3,4,2,0,366,49,1,0,0,0,367,369,5,34,0,0,368,
  	367,1,0,0,0,368,369,1,0,0,0,369,370,1,0,0,0,370,372,5,18,0,0,371,373,
  	5,80,0,0,372,371,1,0,0,0,372,373,1,0,0,0,373,374,1,0,0,0,374,375,5,107,
  	0,0,375,377,5,47,0,0,376,378,3,88,44,0,377,376,1,0,0,0,377,378,1,0,0,
  	0,378,379,1,0,0,0,379,380,5,48,0,0,380,381,3,4,2,0,381,51,1,0,0,0,382,
  	383,5,27,0,0,383,386,5,107,0,0,384,385,5,29,0,0,385,387,3,100,50,0,386,
  	384,1,0,0,0,386,387,1,0,0,0,387,388,1,0,0,0,388,389,3,54,27,0,389,53,
  	1,0,0,0,390,394,5,49,0,0,391,393,3,56,28,0,392,391,1,0,0,0,393,396,1,
  	0,0,0,394,392,1,0,0,0,394,395,1,0,0,0,395,397,1,0,0,0,396,394,1,0,0,0,
  	397,398,5,50,0,0,398,55,1,0,0,0,399,401,5,38,0,0,400,399,1,0,0,0,400,
  	401,1,0,0,0,401,402,1,0,0,0,402,410,3,58,29,0,403,410,3,14,7,0,404,405,
  	3,96,48,0,405,406,5,59,0,0,406,407,3,100,50,0,407,408,5,53,0,0,408,410,
  	1,0,0,0,409,400,1,0,0,0,409,403,1,0,0,0,409,404,1,0,0,0,410,57,1,0,0,
  	0,411,412,3,96,48,0,412,414,5,47,0,0,413,415,3,88,44,0,414,413,1,0,0,
  	0,414,415,1,0,0,0,415,416,1,0,0,0,416,417,5,48,0,0,417,418,3,4,2,0,418,
  	424,1,0,0,0,419,424,3,60,30,0,420,424,3,62,31,0,421,424,3,64,32,0,422,
  	424,3,66,33,0,423,411,1,0,0,0,423,419,1,0,0,0,423,420,1,0,0,0,423,421,
  	1,0,0,0,423,422,1,0,0,0,424,59,1,0,0,0,425,426,5,42,0,0,426,427,3,96,
  	48,0,427,428,5,47,0,0,428,429,5,48,0,0,429,430,3,4,2,0,430,61,1,0,0,0,
  	431,432,5,43,0,0,432,433,3,96,48,0,433,434,5,47,0,0,434,435,3,88,44,0,
  	435,436,5,48,0,0,436,437,3,4,2,0,437,63,1,0,0,0,438,439,5,80,0,0,439,
  	440,3,96,48,0,440,442,5,47,0,0,441,443,3,88,44,0,442,441,1,0,0,0,442,
  	443,1,0,0,0,443,444,1,0,0,0,444,445,5,48,0,0,445,446,3,4,2,0,446,65,1,
  	0,0,0,447,448,5,34,0,0,448,449,3,96,48,0,449,451,5,47,0,0,450,452,3,88,
  	44,0,451,450,1,0,0,0,451,452,1,0,0,0,452,453,1,0,0,0,453,454,5,48,0,0,
  	454,455,3,4,2,0,455,67,1,0,0,0,456,459,5,33,0,0,457,460,3,70,35,0,458,
  	460,5,103,0,0,459,457,1,0,0,0,459,458,1,0,0,0,460,461,1,0,0,0,461,462,
  	5,53,0,0,462,69,1,0,0,0,463,464,5,80,0,0,464,465,5,40,0,0,465,468,5,107,
  	0,0,466,468,3,72,36,0,467,463,1,0,0,0,467,466,1,0,0,0,468,469,1,0,0,0,
  	469,470,5,39,0,0,470,471,5,103,0,0,471,71,1,0,0,0,472,481,5,49,0,0,473,
  	478,3,74,37,0,474,475,5,54,0,0,475,477,3,74,37,0,476,474,1,0,0,0,477,
  	480,1,0,0,0,478,476,1,0,0,0,478,479,1,0,0,0,479,482,1,0,0,0,480,478,1,
  	0,0,0,481,473,1,0,0,0,481,482,1,0,0,0,482,483,1,0,0,0,483,484,5,50,0,
  	0,484,73,1,0,0,0,485,488,5,107,0,0,486,488,3,76,38,0,487,485,1,0,0,0,
  	487,486,1,0,0,0,488,491,1,0,0,0,489,490,5,40,0,0,490,492,5,107,0,0,491,
  	489,1,0,0,0,491,492,1,0,0,0,492,75,1,0,0,0,493,494,7,1,0,0,494,77,1,0,
  	0,0,495,498,5,32,0,0,496,499,3,80,40,0,497,499,3,86,43,0,498,496,1,0,
  	0,0,498,497,1,0,0,0,499,500,1,0,0,0,500,501,5,53,0,0,501,508,1,0,0,0,
  	502,503,5,32,0,0,503,504,5,21,0,0,504,505,3,100,50,0,505,506,5,53,0,0,
  	506,508,1,0,0,0,507,495,1,0,0,0,507,502,1,0,0,0,508,79,1,0,0,0,509,512,
  	5,80,0,0,510,512,3,82,41,0,511,509,1,0,0,0,511,510,1,0,0,0,512,513,1,
  	0,0,0,513,514,5,39,0,0,514,515,5,103,0,0,515,81,1,0,0,0,516,525,5,49,
  	0,0,517,522,3,84,42,0,518,519,5,54,0,0,519,521,3,84,42,0,520,518,1,0,
  	0,0,521,524,1,0,0,0,522,520,1,0,0,0,522,523,1,0,0,0,523,526,1,0,0,0,524,
  	522,1,0,0,0,525,517,1,0,0,0,525,526,1,0,0,0,526,527,1,0,0,0,527,528,5,
  	50,0,0,528,83,1,0,0,0,529,532,5,107,0,0,530,532,3,76,38,0,531,529,1,0,
  	0,0,531,530,1,0,0,0,532,535,1,0,0,0,533,534,5,40,0,0,534,536,3,76,38,
  	0,535,533,1,0,0,0,535,536,1,0,0,0,536,85,1,0,0,0,537,541,3,6,3,0,538,
  	541,3,52,26,0,539,541,3,50,25,0,540,537,1,0,0,0,540,538,1,0,0,0,540,539,
  	1,0,0,0,541,87,1,0,0,0,542,547,3,90,45,0,543,544,5,54,0,0,544,546,3,90,
  	45,0,545,543,1,0,0,0,546,549,1,0,0,0,547,545,1,0,0,0,547,548,1,0,0,0,
  	548,552,1,0,0,0,549,547,1,0,0,0,550,551,5,54,0,0,551,553,3,92,46,0,552,
  	550,1,0,0,0,552,553,1,0,0,0,553,556,1,0,0,0,554,556,3,92,46,0,555,542,
  	1,0,0,0,555,554,1,0,0,0,556,89,1,0,0,0,557,560,3,94,47,0,558,559,5,59,
  	0,0,559,561,3,100,50,0,560,558,1,0,0,0,560,561,1,0,0,0,561,91,1,0,0,0,
  	562,563,5,58,0,0,563,564,3,94,47,0,564,93,1,0,0,0,565,569,5,107,0,0,566,
  	569,3,106,53,0,567,569,3,112,56,0,568,565,1,0,0,0,568,566,1,0,0,0,568,
  	567,1,0,0,0,569,95,1,0,0,0,570,578,3,132,66,0,571,578,5,103,0,0,572,578,
  	5,101,0,0,573,574,5,51,0,0,574,575,3,100,50,0,575,576,5,52,0,0,576,578,
  	1,0,0,0,577,570,1,0,0,0,577,571,1,0,0,0,577,572,1,0,0,0,577,573,1,0,0,
  	0,578,97,1,0,0,0,579,584,3,100,50,0,580,581,5,54,0,0,581,583,3,100,50,
  	0,582,580,1,0,0,0,583,586,1,0,0,0,584,582,1,0,0,0,584,585,1,0,0,0,585,
  	99,1,0,0,0,586,584,1,0,0,0,587,588,6,50,-1,0,588,627,3,122,61,0,589,627,
  	3,124,62,0,590,591,5,7,0,0,591,593,3,100,50,0,592,594,3,116,58,0,593,
  	592,1,0,0,0,593,594,1,0,0,0,594,627,1,0,0,0,595,596,5,24,0,0,596,627,
  	3,100,50,35,597,598,5,12,0,0,598,627,3,100,50,34,599,600,5,4,0,0,600,
  	627,3,100,50,33,601,602,5,74,0,0,602,627,3,100,50,32,603,604,5,75,0,0,
  	604,627,3,100,50,31,605,606,5,76,0,0,606,627,3,100,50,30,607,608,5,77,
  	0,0,608,627,3,100,50,29,609,610,5,78,0,0,610,627,3,100,50,28,611,612,
  	5,79,0,0,612,627,3,100,50,27,613,614,5,35,0,0,614,627,3,100,50,26,615,
  	627,5,19,0,0,616,627,5,107,0,0,617,627,5,30,0,0,618,627,3,104,52,0,619,
  	627,3,106,53,0,620,627,3,112,56,0,621,622,5,47,0,0,622,623,3,98,49,0,
  	623,624,5,48,0,0,624,627,1,0,0,0,625,627,3,130,65,0,626,587,1,0,0,0,626,
  	589,1,0,0,0,626,590,1,0,0,0,626,595,1,0,0,0,626,597,1,0,0,0,626,599,1,
  	0,0,0,626,601,1,0,0,0,626,603,1,0,0,0,626,605,1,0,0,0,626,607,1,0,0,0,
  	626,609,1,0,0,0,626,611,1,0,0,0,626,613,1,0,0,0,626,615,1,0,0,0,626,616,
  	1,0,0,0,626,617,1,0,0,0,626,618,1,0,0,0,626,619,1,0,0,0,626,620,1,0,0,
  	0,626,621,1,0,0,0,626,625,1,0,0,0,627,699,1,0,0,0,628,629,10,25,0,0,629,
  	630,5,83,0,0,630,698,3,100,50,26,631,632,10,24,0,0,632,633,7,2,0,0,633,
  	698,3,100,50,25,634,635,10,23,0,0,635,636,7,3,0,0,636,698,3,100,50,24,
  	637,638,10,22,0,0,638,639,7,4,0,0,639,698,3,100,50,23,640,641,10,21,0,
  	0,641,642,7,5,0,0,642,698,3,100,50,22,643,644,10,20,0,0,644,645,5,3,0,
  	0,645,698,3,100,50,21,646,647,10,19,0,0,647,648,5,25,0,0,648,698,3,100,
  	50,20,649,650,10,18,0,0,650,651,7,6,0,0,651,698,3,100,50,19,652,653,10,
  	17,0,0,653,654,5,96,0,0,654,698,3,100,50,18,655,656,10,16,0,0,656,657,
  	5,97,0,0,657,698,3,100,50,17,658,659,10,15,0,0,659,660,5,98,0,0,660,698,
  	3,100,50,16,661,662,10,14,0,0,662,663,5,99,0,0,663,698,3,100,50,15,664,
  	665,10,13,0,0,665,666,5,100,0,0,666,698,3,100,50,14,667,668,10,12,0,0,
  	668,669,5,84,0,0,669,698,3,100,50,13,670,671,10,11,0,0,671,672,5,56,0,
  	0,672,673,3,100,50,0,673,674,5,57,0,0,674,675,3,100,50,12,675,698,1,0,
  	0,0,676,677,10,10,0,0,677,678,5,59,0,0,678,698,3,100,50,11,679,680,10,
  	9,0,0,680,681,3,102,51,0,681,682,3,100,50,10,682,698,1,0,0,0,683,684,
  	10,41,0,0,684,685,5,51,0,0,685,686,3,98,49,0,686,687,5,52,0,0,687,698,
  	1,0,0,0,688,689,10,40,0,0,689,690,5,55,0,0,690,698,3,132,66,0,691,692,
  	10,39,0,0,692,698,3,116,58,0,693,694,10,37,0,0,694,698,5,74,0,0,695,696,
  	10,36,0,0,696,698,5,75,0,0,697,628,1,0,0,0,697,631,1,0,0,0,697,634,1,
  	0,0,0,697,637,1,0,0,0,697,640,1,0,0,0,697,643,1,0,0,0,697,646,1,0,0,0,
  	697,649,1,0,0,0,697,652,1,0,0,0,697,655,1,0,0,0,697,658,1,0,0,0,697,661,
  	1,0,0,0,697,664,1,0,0,0,697,667,1,0,0,0,697,670,1,0,0,0,697,676,1,0,0,
  	0,697,679,1,0,0,0,697,683,1,0,0,0,697,688,1,0,0,0,697,691,1,0,0,0,697,
  	693,1,0,0,0,697,695,1,0,0,0,698,701,1,0,0,0,699,697,1,0,0,0,699,700,1,
  	0,0,0,700,101,1,0,0,0,701,699,1,0,0,0,702,703,7,7,0,0,703,103,1,0,0,0,
  	704,705,7,8,0,0,705,105,1,0,0,0,706,708,5,51,0,0,707,709,3,108,54,0,708,
  	707,1,0,0,0,708,709,1,0,0,0,709,710,1,0,0,0,710,711,5,52,0,0,711,107,
  	1,0,0,0,712,717,3,110,55,0,713,714,5,54,0,0,714,716,3,110,55,0,715,713,
  	1,0,0,0,716,719,1,0,0,0,717,715,1,0,0,0,717,718,1,0,0,0,718,109,1,0,0,
  	0,719,717,1,0,0,0,720,722,5,58,0,0,721,720,1,0,0,0,721,722,1,0,0,0,722,
  	723,1,0,0,0,723,726,3,100,50,0,724,726,5,54,0,0,725,721,1,0,0,0,725,724,
  	1,0,0,0,726,111,1,0,0,0,727,728,5,49,0,0,728,733,3,114,57,0,729,730,5,
  	54,0,0,730,732,3,114,57,0,731,729,1,0,0,0,732,735,1,0,0,0,733,731,1,0,
  	0,0,733,734,1,0,0,0,734,737,1,0,0,0,735,733,1,0,0,0,736,738,5,54,0,0,
  	737,736,1,0,0,0,737,738,1,0,0,0,738,739,1,0,0,0,739,740,5,50,0,0,740,
  	113,1,0,0,0,741,742,3,96,48,0,742,743,5,57,0,0,743,744,3,100,50,0,744,
  	756,1,0,0,0,745,746,5,51,0,0,746,747,3,100,50,0,747,748,5,52,0,0,748,
  	749,5,57,0,0,749,750,3,100,50,0,750,756,1,0,0,0,751,756,3,58,29,0,752,
  	756,5,107,0,0,753,754,5,58,0,0,754,756,3,100,50,0,755,741,1,0,0,0,755,
  	745,1,0,0,0,755,751,1,0,0,0,755,752,1,0,0,0,755,753,1,0,0,0,756,115,1,
  	0,0,0,757,759,5,47,0,0,758,760,3,118,59,0,759,758,1,0,0,0,759,760,1,0,
  	0,0,760,761,1,0,0,0,761,762,5,48,0,0,762,117,1,0,0,0,763,768,3,120,60,
  	0,764,765,5,54,0,0,765,767,3,120,60,0,766,764,1,0,0,0,767,770,1,0,0,0,
  	768,766,1,0,0,0,768,769,1,0,0,0,769,119,1,0,0,0,770,768,1,0,0,0,771,773,
  	5,58,0,0,772,771,1,0,0,0,772,773,1,0,0,0,773,774,1,0,0,0,774,775,3,100,
  	50,0,775,121,1,0,0,0,776,778,5,34,0,0,777,776,1,0,0,0,777,778,1,0,0,0,
  	778,779,1,0,0,0,779,781,5,18,0,0,780,782,5,80,0,0,781,780,1,0,0,0,781,
  	782,1,0,0,0,782,783,1,0,0,0,783,785,5,47,0,0,784,786,3,88,44,0,785,784,
  	1,0,0,0,785,786,1,0,0,0,786,787,1,0,0,0,787,788,5,48,0,0,788,789,3,4,
  	2,0,789,123,1,0,0,0,790,792,5,34,0,0,791,790,1,0,0,0,791,792,1,0,0,0,
  	792,793,1,0,0,0,793,794,3,126,63,0,794,795,5,73,0,0,795,796,3,128,64,
  	0,796,125,1,0,0,0,797,804,5,107,0,0,798,800,5,47,0,0,799,801,3,88,44,
  	0,800,799,1,0,0,0,800,801,1,0,0,0,801,802,1,0,0,0,802,804,5,48,0,0,803,
  	797,1,0,0,0,803,798,1,0,0,0,804,127,1,0,0,0,805,808,3,100,50,0,806,808,
  	3,4,2,0,807,805,1,0,0,0,807,806,1,0,0,0,808,129,1,0,0,0,809,810,5,4,0,
  	0,810,811,3,100,50,0,811,131,1,0,0,0,812,815,5,107,0,0,813,815,3,134,
  	67,0,814,812,1,0,0,0,814,813,1,0,0,0,815,133,1,0,0,0,816,820,3,136,68,
  	0,817,820,5,44,0,0,818,820,5,45,0,0,819,816,1,0,0,0,819,817,1,0,0,0,819,
  	818,1,0,0,0,820,135,1,0,0,0,821,822,7,9,0,0,822,137,1,0,0,0,80,141,164,
  	170,184,192,206,226,230,234,242,253,265,272,276,282,288,310,314,316,323,
  	331,339,350,353,360,368,372,377,386,394,400,409,414,423,442,451,459,467,
  	478,481,487,491,498,507,511,522,525,531,535,540,547,552,555,560,568,577,
  	584,593,626,697,699,708,717,721,725,733,737,755,759,768,772,777,781,785,
  	791,800,803,807,814,819
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  javascriptParserStaticData = staticData.release();
}

}

JavaScriptParser::JavaScriptParser(TokenStream *input) : JavaScriptParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

JavaScriptParser::JavaScriptParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  JavaScriptParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *javascriptParserStaticData->atn, javascriptParserStaticData->decisionToDFA, javascriptParserStaticData->sharedContextCache, options);
}

JavaScriptParser::~JavaScriptParser() {
  delete _interpreter;
}

const atn::ATN& JavaScriptParser::getATN() const {
  return *javascriptParserStaticData->atn;
}

std::string JavaScriptParser::getGrammarFileName() const {
  return "JavaScript.g4";
}

const std::vector<std::string>& JavaScriptParser::getRuleNames() const {
  return javascriptParserStaticData->ruleNames;
}

const dfa::Vocabulary& JavaScriptParser::getVocabulary() const {
  return javascriptParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView JavaScriptParser::getSerializedATN() const {
  return javascriptParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

JavaScriptParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ProgramContext::EOF() {
  return getToken(JavaScriptParser::EOF, 0);
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::ProgramContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::ProgramContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}


size_t JavaScriptParser::ProgramContext::getRuleIndex() const {
  return JavaScriptParser::RuleProgram;
}


std::any JavaScriptParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ProgramContext* JavaScriptParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, JavaScriptParser::RuleProgram);
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
    setState(141);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::NULL_LITERAL)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::UNDEFINED)
      | (1ULL << JavaScriptParser::LPAREN)
      | (1ULL << JavaScriptParser::LBRACE)
      | (1ULL << JavaScriptParser::LBRACKET)
      | (1ULL << JavaScriptParser::SEMICOLON))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
      | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
      | (1ULL << (JavaScriptParser::PLUS - 74))
      | (1ULL << (JavaScriptParser::MINUS - 74))
      | (1ULL << (JavaScriptParser::TILDE - 74))
      | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
      | (1ULL << (JavaScriptParser::NUMBER - 74))
      | (1ULL << (JavaScriptParser::STRING - 74))
      | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
      setState(138);
      statement();
      setState(143);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(144);
    match(JavaScriptParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

JavaScriptParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::BlockContext* JavaScriptParser::StatementContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::VariableStatementContext* JavaScriptParser::StatementContext::variableStatement() {
  return getRuleContext<JavaScriptParser::VariableStatementContext>(0);
}

JavaScriptParser::EmptyStatementContext* JavaScriptParser::StatementContext::emptyStatement() {
  return getRuleContext<JavaScriptParser::EmptyStatementContext>(0);
}

JavaScriptParser::ExpressionStatementContext* JavaScriptParser::StatementContext::expressionStatement() {
  return getRuleContext<JavaScriptParser::ExpressionStatementContext>(0);
}

JavaScriptParser::IfStatementContext* JavaScriptParser::StatementContext::ifStatement() {
  return getRuleContext<JavaScriptParser::IfStatementContext>(0);
}

JavaScriptParser::IterationStatementContext* JavaScriptParser::StatementContext::iterationStatement() {
  return getRuleContext<JavaScriptParser::IterationStatementContext>(0);
}

JavaScriptParser::ContinueStatementContext* JavaScriptParser::StatementContext::continueStatement() {
  return getRuleContext<JavaScriptParser::ContinueStatementContext>(0);
}

JavaScriptParser::BreakStatementContext* JavaScriptParser::StatementContext::breakStatement() {
  return getRuleContext<JavaScriptParser::BreakStatementContext>(0);
}

JavaScriptParser::ReturnStatementContext* JavaScriptParser::StatementContext::returnStatement() {
  return getRuleContext<JavaScriptParser::ReturnStatementContext>(0);
}

JavaScriptParser::WithStatementContext* JavaScriptParser::StatementContext::withStatement() {
  return getRuleContext<JavaScriptParser::WithStatementContext>(0);
}

JavaScriptParser::LabelledStatementContext* JavaScriptParser::StatementContext::labelledStatement() {
  return getRuleContext<JavaScriptParser::LabelledStatementContext>(0);
}

JavaScriptParser::SwitchStatementContext* JavaScriptParser::StatementContext::switchStatement() {
  return getRuleContext<JavaScriptParser::SwitchStatementContext>(0);
}

JavaScriptParser::ThrowStatementContext* JavaScriptParser::StatementContext::throwStatement() {
  return getRuleContext<JavaScriptParser::ThrowStatementContext>(0);
}

JavaScriptParser::TryStatementContext* JavaScriptParser::StatementContext::tryStatement() {
  return getRuleContext<JavaScriptParser::TryStatementContext>(0);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::StatementContext::functionDeclaration() {
  return getRuleContext<JavaScriptParser::FunctionDeclarationContext>(0);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::StatementContext::classDeclaration() {
  return getRuleContext<JavaScriptParser::ClassDeclarationContext>(0);
}

JavaScriptParser::ImportStatementContext* JavaScriptParser::StatementContext::importStatement() {
  return getRuleContext<JavaScriptParser::ImportStatementContext>(0);
}

JavaScriptParser::ExportStatementContext* JavaScriptParser::StatementContext::exportStatement() {
  return getRuleContext<JavaScriptParser::ExportStatementContext>(0);
}


size_t JavaScriptParser::StatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleStatement;
}


std::any JavaScriptParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::StatementContext* JavaScriptParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, JavaScriptParser::RuleStatement);

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
      setState(146);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(147);
      variableStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(148);
      emptyStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(149);
      expressionStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(150);
      ifStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(151);
      iterationStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(152);
      continueStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(153);
      breakStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(154);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(155);
      withStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(156);
      labelledStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(157);
      switchStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(158);
      throwStatement();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(159);
      tryStatement();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(160);
      functionDeclaration();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(161);
      classDeclaration();
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(162);
      importStatement();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(163);
      exportStatement();
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

//----------------- BlockContext ------------------------------------------------------------------

JavaScriptParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::BlockContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::BlockContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::BlockContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::BlockContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}


size_t JavaScriptParser::BlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleBlock;
}


std::any JavaScriptParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::BlockContext* JavaScriptParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 4, JavaScriptParser::RuleBlock);
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
    match(JavaScriptParser::LBRACE);
    setState(170);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::NULL_LITERAL)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::UNDEFINED)
      | (1ULL << JavaScriptParser::LPAREN)
      | (1ULL << JavaScriptParser::LBRACE)
      | (1ULL << JavaScriptParser::LBRACKET)
      | (1ULL << JavaScriptParser::SEMICOLON))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
      | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
      | (1ULL << (JavaScriptParser::PLUS - 74))
      | (1ULL << (JavaScriptParser::MINUS - 74))
      | (1ULL << (JavaScriptParser::TILDE - 74))
      | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
      | (1ULL << (JavaScriptParser::NUMBER - 74))
      | (1ULL << (JavaScriptParser::STRING - 74))
      | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
      setState(167);
      statement();
      setState(172);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(173);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableStatementContext ------------------------------------------------------------------

JavaScriptParser::VariableStatementContext::VariableStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::VariableStatementContext::variableDeclarationList() {
  return getRuleContext<JavaScriptParser::VariableDeclarationListContext>(0);
}

tree::TerminalNode* JavaScriptParser::VariableStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::VariableStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableStatement;
}


std::any JavaScriptParser::VariableStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitVariableStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::VariableStatementContext* JavaScriptParser::variableStatement() {
  VariableStatementContext *_localctx = _tracker.createInstance<VariableStatementContext>(_ctx, getState());
  enterRule(_localctx, 6, JavaScriptParser::RuleVariableStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    variableDeclarationList();
    setState(176);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationListContext ------------------------------------------------------------------

JavaScriptParser::VariableDeclarationListContext::VariableDeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::VarModifierContext* JavaScriptParser::VariableDeclarationListContext::varModifier() {
  return getRuleContext<JavaScriptParser::VarModifierContext>(0);
}

std::vector<JavaScriptParser::VariableDeclarationContext *> JavaScriptParser::VariableDeclarationListContext::variableDeclaration() {
  return getRuleContexts<JavaScriptParser::VariableDeclarationContext>();
}

JavaScriptParser::VariableDeclarationContext* JavaScriptParser::VariableDeclarationListContext::variableDeclaration(size_t i) {
  return getRuleContext<JavaScriptParser::VariableDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::VariableDeclarationListContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::VariableDeclarationListContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::VariableDeclarationListContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableDeclarationList;
}


std::any JavaScriptParser::VariableDeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitVariableDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::variableDeclarationList() {
  VariableDeclarationListContext *_localctx = _tracker.createInstance<VariableDeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 8, JavaScriptParser::RuleVariableDeclarationList);
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
    varModifier();
    setState(179);
    variableDeclaration();
    setState(184);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(180);
      match(JavaScriptParser::COMMA);
      setState(181);
      variableDeclaration();
      setState(186);
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

//----------------- VarModifierContext ------------------------------------------------------------------

JavaScriptParser::VarModifierContext::VarModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::VarModifierContext::VAR() {
  return getToken(JavaScriptParser::VAR, 0);
}

tree::TerminalNode* JavaScriptParser::VarModifierContext::LET() {
  return getToken(JavaScriptParser::LET, 0);
}

tree::TerminalNode* JavaScriptParser::VarModifierContext::CONST() {
  return getToken(JavaScriptParser::CONST, 0);
}


size_t JavaScriptParser::VarModifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleVarModifier;
}


std::any JavaScriptParser::VarModifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitVarModifier(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::VarModifierContext* JavaScriptParser::varModifier() {
  VarModifierContext *_localctx = _tracker.createInstance<VarModifierContext>(_ctx, getState());
  enterRule(_localctx, 10, JavaScriptParser::RuleVarModifier);
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
    setState(187);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::LET))) != 0))) {
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

JavaScriptParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::AssignableContext* JavaScriptParser::VariableDeclarationContext::assignable() {
  return getRuleContext<JavaScriptParser::AssignableContext>(0);
}

tree::TerminalNode* JavaScriptParser::VariableDeclarationContext::EQUALS() {
  return getToken(JavaScriptParser::EQUALS, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::VariableDeclarationContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}


size_t JavaScriptParser::VariableDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableDeclaration;
}


std::any JavaScriptParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::VariableDeclarationContext* JavaScriptParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 12, JavaScriptParser::RuleVariableDeclaration);
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
    setState(189);
    assignable();
    setState(192);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::EQUALS) {
      setState(190);
      match(JavaScriptParser::EQUALS);
      setState(191);
      singleExpression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmptyStatementContext ------------------------------------------------------------------

JavaScriptParser::EmptyStatementContext::EmptyStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::EmptyStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::EmptyStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleEmptyStatement;
}


std::any JavaScriptParser::EmptyStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitEmptyStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::EmptyStatementContext* JavaScriptParser::emptyStatement() {
  EmptyStatementContext *_localctx = _tracker.createInstance<EmptyStatementContext>(_ctx, getState());
  enterRule(_localctx, 14, JavaScriptParser::RuleEmptyStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

JavaScriptParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ExpressionStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::ExpressionStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::ExpressionStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleExpressionStatement;
}


std::any JavaScriptParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExpressionStatementContext* JavaScriptParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, JavaScriptParser::RuleExpressionStatement);

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
    expressionSequence();
    setState(197);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

JavaScriptParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::IF() {
  return getToken(JavaScriptParser::IF, 0);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::IfStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::IfStatementContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::ELSE() {
  return getToken(JavaScriptParser::ELSE, 0);
}


size_t JavaScriptParser::IfStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleIfStatement;
}


std::any JavaScriptParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::IfStatementContext* JavaScriptParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, JavaScriptParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    match(JavaScriptParser::IF);
    setState(200);
    match(JavaScriptParser::LPAREN);
    setState(201);
    expressionSequence();
    setState(202);
    match(JavaScriptParser::RPAREN);
    setState(203);
    statement();
    setState(206);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(204);
      match(JavaScriptParser::ELSE);
      setState(205);
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

//----------------- IterationStatementContext ------------------------------------------------------------------

JavaScriptParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::DO() {
  return getToken(JavaScriptParser::DO, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::IterationStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::WHILE() {
  return getToken(JavaScriptParser::WHILE, 0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

std::vector<JavaScriptParser::ExpressionSequenceContext *> JavaScriptParser::IterationStatementContext::expressionSequence() {
  return getRuleContexts<JavaScriptParser::ExpressionSequenceContext>();
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::IterationStatementContext::expressionSequence(size_t i) {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(i);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> JavaScriptParser::IterationStatementContext::SEMICOLON() {
  return getTokens(JavaScriptParser::SEMICOLON);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::SEMICOLON(size_t i) {
  return getToken(JavaScriptParser::SEMICOLON, i);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::FOR() {
  return getToken(JavaScriptParser::FOR, 0);
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::IterationStatementContext::variableDeclarationList() {
  return getRuleContext<JavaScriptParser::VariableDeclarationListContext>(0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::IN() {
  return getToken(JavaScriptParser::IN, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::IterationStatementContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::OF() {
  return getToken(JavaScriptParser::OF, 0);
}

tree::TerminalNode* JavaScriptParser::IterationStatementContext::AWAIT() {
  return getToken(JavaScriptParser::AWAIT, 0);
}


size_t JavaScriptParser::IterationStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleIterationStatement;
}


std::any JavaScriptParser::IterationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitIterationStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::IterationStatementContext* JavaScriptParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, JavaScriptParser::RuleIterationStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(272);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(208);
      match(JavaScriptParser::DO);
      setState(209);
      statement();
      setState(210);
      match(JavaScriptParser::WHILE);
      setState(211);
      match(JavaScriptParser::LPAREN);
      setState(212);
      expressionSequence();
      setState(213);
      match(JavaScriptParser::RPAREN);
      setState(214);
      match(JavaScriptParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(216);
      match(JavaScriptParser::WHILE);
      setState(217);
      match(JavaScriptParser::LPAREN);
      setState(218);
      expressionSequence();
      setState(219);
      match(JavaScriptParser::RPAREN);
      setState(220);
      statement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(222);
      match(JavaScriptParser::FOR);
      setState(223);
      match(JavaScriptParser::LPAREN);
      setState(226);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaScriptParser::TYPEOF:
        case JavaScriptParser::NEW:
        case JavaScriptParser::VOID:
        case JavaScriptParser::FUNCTION:
        case JavaScriptParser::THIS:
        case JavaScriptParser::DELETE:
        case JavaScriptParser::SUPER:
        case JavaScriptParser::ASYNC:
        case JavaScriptParser::AWAIT:
        case JavaScriptParser::NULL_LITERAL:
        case JavaScriptParser::BOOLEAN:
        case JavaScriptParser::UNDEFINED:
        case JavaScriptParser::LPAREN:
        case JavaScriptParser::LBRACE:
        case JavaScriptParser::LBRACKET:
        case JavaScriptParser::PLUSPLUS:
        case JavaScriptParser::MINUSMINUS:
        case JavaScriptParser::PLUS:
        case JavaScriptParser::MINUS:
        case JavaScriptParser::TILDE:
        case JavaScriptParser::EXCLAMATION:
        case JavaScriptParser::NUMBER:
        case JavaScriptParser::STRING:
        case JavaScriptParser::TEMPLATE_STRING:
        case JavaScriptParser::IDENTIFIER: {
          setState(224);
          expressionSequence();
          break;
        }

        case JavaScriptParser::VAR:
        case JavaScriptParser::CONST:
        case JavaScriptParser::LET: {
          setState(225);
          variableDeclarationList();
          break;
        }

        case JavaScriptParser::SEMICOLON: {
          break;
        }

      default:
        break;
      }
      setState(228);
      match(JavaScriptParser::SEMICOLON);
      setState(230);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
        | (1ULL << JavaScriptParser::NEW)
        | (1ULL << JavaScriptParser::VOID)
        | (1ULL << JavaScriptParser::FUNCTION)
        | (1ULL << JavaScriptParser::THIS)
        | (1ULL << JavaScriptParser::DELETE)
        | (1ULL << JavaScriptParser::SUPER)
        | (1ULL << JavaScriptParser::ASYNC)
        | (1ULL << JavaScriptParser::AWAIT)
        | (1ULL << JavaScriptParser::NULL_LITERAL)
        | (1ULL << JavaScriptParser::BOOLEAN)
        | (1ULL << JavaScriptParser::UNDEFINED)
        | (1ULL << JavaScriptParser::LPAREN)
        | (1ULL << JavaScriptParser::LBRACE)
        | (1ULL << JavaScriptParser::LBRACKET))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
        | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
        | (1ULL << (JavaScriptParser::PLUS - 74))
        | (1ULL << (JavaScriptParser::MINUS - 74))
        | (1ULL << (JavaScriptParser::TILDE - 74))
        | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
        | (1ULL << (JavaScriptParser::NUMBER - 74))
        | (1ULL << (JavaScriptParser::STRING - 74))
        | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
        | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
        setState(229);
        expressionSequence();
      }
      setState(232);
      match(JavaScriptParser::SEMICOLON);
      setState(234);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
        | (1ULL << JavaScriptParser::NEW)
        | (1ULL << JavaScriptParser::VOID)
        | (1ULL << JavaScriptParser::FUNCTION)
        | (1ULL << JavaScriptParser::THIS)
        | (1ULL << JavaScriptParser::DELETE)
        | (1ULL << JavaScriptParser::SUPER)
        | (1ULL << JavaScriptParser::ASYNC)
        | (1ULL << JavaScriptParser::AWAIT)
        | (1ULL << JavaScriptParser::NULL_LITERAL)
        | (1ULL << JavaScriptParser::BOOLEAN)
        | (1ULL << JavaScriptParser::UNDEFINED)
        | (1ULL << JavaScriptParser::LPAREN)
        | (1ULL << JavaScriptParser::LBRACE)
        | (1ULL << JavaScriptParser::LBRACKET))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
        | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
        | (1ULL << (JavaScriptParser::PLUS - 74))
        | (1ULL << (JavaScriptParser::MINUS - 74))
        | (1ULL << (JavaScriptParser::TILDE - 74))
        | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
        | (1ULL << (JavaScriptParser::NUMBER - 74))
        | (1ULL << (JavaScriptParser::STRING - 74))
        | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
        | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
        setState(233);
        expressionSequence();
      }
      setState(236);
      match(JavaScriptParser::RPAREN);
      setState(237);
      statement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(238);
      match(JavaScriptParser::FOR);
      setState(239);
      match(JavaScriptParser::LPAREN);
      setState(242);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaScriptParser::TYPEOF:
        case JavaScriptParser::NEW:
        case JavaScriptParser::VOID:
        case JavaScriptParser::FUNCTION:
        case JavaScriptParser::THIS:
        case JavaScriptParser::DELETE:
        case JavaScriptParser::SUPER:
        case JavaScriptParser::ASYNC:
        case JavaScriptParser::AWAIT:
        case JavaScriptParser::NULL_LITERAL:
        case JavaScriptParser::BOOLEAN:
        case JavaScriptParser::UNDEFINED:
        case JavaScriptParser::LPAREN:
        case JavaScriptParser::LBRACE:
        case JavaScriptParser::LBRACKET:
        case JavaScriptParser::PLUSPLUS:
        case JavaScriptParser::MINUSMINUS:
        case JavaScriptParser::PLUS:
        case JavaScriptParser::MINUS:
        case JavaScriptParser::TILDE:
        case JavaScriptParser::EXCLAMATION:
        case JavaScriptParser::NUMBER:
        case JavaScriptParser::STRING:
        case JavaScriptParser::TEMPLATE_STRING:
        case JavaScriptParser::IDENTIFIER: {
          setState(240);
          singleExpression(0);
          break;
        }

        case JavaScriptParser::VAR:
        case JavaScriptParser::CONST:
        case JavaScriptParser::LET: {
          setState(241);
          variableDeclarationList();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(244);
      match(JavaScriptParser::IN);
      setState(245);
      expressionSequence();
      setState(246);
      match(JavaScriptParser::RPAREN);
      setState(247);
      statement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(249);
      match(JavaScriptParser::FOR);
      setState(250);
      match(JavaScriptParser::LPAREN);
      setState(253);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaScriptParser::TYPEOF:
        case JavaScriptParser::NEW:
        case JavaScriptParser::VOID:
        case JavaScriptParser::FUNCTION:
        case JavaScriptParser::THIS:
        case JavaScriptParser::DELETE:
        case JavaScriptParser::SUPER:
        case JavaScriptParser::ASYNC:
        case JavaScriptParser::AWAIT:
        case JavaScriptParser::NULL_LITERAL:
        case JavaScriptParser::BOOLEAN:
        case JavaScriptParser::UNDEFINED:
        case JavaScriptParser::LPAREN:
        case JavaScriptParser::LBRACE:
        case JavaScriptParser::LBRACKET:
        case JavaScriptParser::PLUSPLUS:
        case JavaScriptParser::MINUSMINUS:
        case JavaScriptParser::PLUS:
        case JavaScriptParser::MINUS:
        case JavaScriptParser::TILDE:
        case JavaScriptParser::EXCLAMATION:
        case JavaScriptParser::NUMBER:
        case JavaScriptParser::STRING:
        case JavaScriptParser::TEMPLATE_STRING:
        case JavaScriptParser::IDENTIFIER: {
          setState(251);
          singleExpression(0);
          break;
        }

        case JavaScriptParser::VAR:
        case JavaScriptParser::CONST:
        case JavaScriptParser::LET: {
          setState(252);
          variableDeclarationList();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(255);
      match(JavaScriptParser::OF);
      setState(256);
      expressionSequence();
      setState(257);
      match(JavaScriptParser::RPAREN);
      setState(258);
      statement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(260);
      match(JavaScriptParser::FOR);
      setState(261);
      match(JavaScriptParser::AWAIT);
      setState(262);
      match(JavaScriptParser::LPAREN);
      setState(265);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaScriptParser::TYPEOF:
        case JavaScriptParser::NEW:
        case JavaScriptParser::VOID:
        case JavaScriptParser::FUNCTION:
        case JavaScriptParser::THIS:
        case JavaScriptParser::DELETE:
        case JavaScriptParser::SUPER:
        case JavaScriptParser::ASYNC:
        case JavaScriptParser::AWAIT:
        case JavaScriptParser::NULL_LITERAL:
        case JavaScriptParser::BOOLEAN:
        case JavaScriptParser::UNDEFINED:
        case JavaScriptParser::LPAREN:
        case JavaScriptParser::LBRACE:
        case JavaScriptParser::LBRACKET:
        case JavaScriptParser::PLUSPLUS:
        case JavaScriptParser::MINUSMINUS:
        case JavaScriptParser::PLUS:
        case JavaScriptParser::MINUS:
        case JavaScriptParser::TILDE:
        case JavaScriptParser::EXCLAMATION:
        case JavaScriptParser::NUMBER:
        case JavaScriptParser::STRING:
        case JavaScriptParser::TEMPLATE_STRING:
        case JavaScriptParser::IDENTIFIER: {
          setState(263);
          singleExpression(0);
          break;
        }

        case JavaScriptParser::VAR:
        case JavaScriptParser::CONST:
        case JavaScriptParser::LET: {
          setState(264);
          variableDeclarationList();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(267);
      match(JavaScriptParser::OF);
      setState(268);
      expressionSequence();
      setState(269);
      match(JavaScriptParser::RPAREN);
      setState(270);
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

//----------------- ContinueStatementContext ------------------------------------------------------------------

JavaScriptParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ContinueStatementContext::CONTINUE() {
  return getToken(JavaScriptParser::CONTINUE, 0);
}

tree::TerminalNode* JavaScriptParser::ContinueStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

tree::TerminalNode* JavaScriptParser::ContinueStatementContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}


size_t JavaScriptParser::ContinueStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleContinueStatement;
}


std::any JavaScriptParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ContinueStatementContext* JavaScriptParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, JavaScriptParser::RuleContinueStatement);
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
    match(JavaScriptParser::CONTINUE);
    setState(276);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::IDENTIFIER) {
      setState(275);
      match(JavaScriptParser::IDENTIFIER);
    }
    setState(278);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

JavaScriptParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::BreakStatementContext::BREAK() {
  return getToken(JavaScriptParser::BREAK, 0);
}

tree::TerminalNode* JavaScriptParser::BreakStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

tree::TerminalNode* JavaScriptParser::BreakStatementContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}


size_t JavaScriptParser::BreakStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleBreakStatement;
}


std::any JavaScriptParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::BreakStatementContext* JavaScriptParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, JavaScriptParser::RuleBreakStatement);
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
    setState(280);
    match(JavaScriptParser::BREAK);
    setState(282);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::IDENTIFIER) {
      setState(281);
      match(JavaScriptParser::IDENTIFIER);
    }
    setState(284);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

JavaScriptParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ReturnStatementContext::RETURN() {
  return getToken(JavaScriptParser::RETURN, 0);
}

tree::TerminalNode* JavaScriptParser::ReturnStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ReturnStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}


size_t JavaScriptParser::ReturnStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleReturnStatement;
}


std::any JavaScriptParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ReturnStatementContext* JavaScriptParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, JavaScriptParser::RuleReturnStatement);
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
    match(JavaScriptParser::RETURN);
    setState(288);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::NULL_LITERAL)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::UNDEFINED)
      | (1ULL << JavaScriptParser::LPAREN)
      | (1ULL << JavaScriptParser::LBRACE)
      | (1ULL << JavaScriptParser::LBRACKET))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
      | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
      | (1ULL << (JavaScriptParser::PLUS - 74))
      | (1ULL << (JavaScriptParser::MINUS - 74))
      | (1ULL << (JavaScriptParser::TILDE - 74))
      | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
      | (1ULL << (JavaScriptParser::NUMBER - 74))
      | (1ULL << (JavaScriptParser::STRING - 74))
      | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
      setState(287);
      expressionSequence();
    }
    setState(290);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WithStatementContext ------------------------------------------------------------------

JavaScriptParser::WithStatementContext::WithStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::WITH() {
  return getToken(JavaScriptParser::WITH, 0);
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::WithStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::WithStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}


size_t JavaScriptParser::WithStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleWithStatement;
}


std::any JavaScriptParser::WithStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitWithStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::WithStatementContext* JavaScriptParser::withStatement() {
  WithStatementContext *_localctx = _tracker.createInstance<WithStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, JavaScriptParser::RuleWithStatement);

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
    match(JavaScriptParser::WITH);
    setState(293);
    match(JavaScriptParser::LPAREN);
    setState(294);
    expressionSequence();
    setState(295);
    match(JavaScriptParser::RPAREN);
    setState(296);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelledStatementContext ------------------------------------------------------------------

JavaScriptParser::LabelledStatementContext::LabelledStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::LabelledStatementContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScriptParser::LabelledStatementContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::LabelledStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}


size_t JavaScriptParser::LabelledStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleLabelledStatement;
}


std::any JavaScriptParser::LabelledStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitLabelledStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::LabelledStatementContext* JavaScriptParser::labelledStatement() {
  LabelledStatementContext *_localctx = _tracker.createInstance<LabelledStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, JavaScriptParser::RuleLabelledStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(298);
    match(JavaScriptParser::IDENTIFIER);
    setState(299);
    match(JavaScriptParser::COLON);
    setState(300);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SwitchStatementContext ------------------------------------------------------------------

JavaScriptParser::SwitchStatementContext::SwitchStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::SWITCH() {
  return getToken(JavaScriptParser::SWITCH, 0);
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::SwitchStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::CaseBlockContext* JavaScriptParser::SwitchStatementContext::caseBlock() {
  return getRuleContext<JavaScriptParser::CaseBlockContext>(0);
}


size_t JavaScriptParser::SwitchStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleSwitchStatement;
}


std::any JavaScriptParser::SwitchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitSwitchStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::SwitchStatementContext* JavaScriptParser::switchStatement() {
  SwitchStatementContext *_localctx = _tracker.createInstance<SwitchStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, JavaScriptParser::RuleSwitchStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(302);
    match(JavaScriptParser::SWITCH);
    setState(303);
    match(JavaScriptParser::LPAREN);
    setState(304);
    expressionSequence();
    setState(305);
    match(JavaScriptParser::RPAREN);
    setState(306);
    caseBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseBlockContext ------------------------------------------------------------------

JavaScriptParser::CaseBlockContext::CaseBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CaseBlockContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::CaseBlockContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::CaseClausesContext *> JavaScriptParser::CaseBlockContext::caseClauses() {
  return getRuleContexts<JavaScriptParser::CaseClausesContext>();
}

JavaScriptParser::CaseClausesContext* JavaScriptParser::CaseBlockContext::caseClauses(size_t i) {
  return getRuleContext<JavaScriptParser::CaseClausesContext>(i);
}

JavaScriptParser::DefaultClauseContext* JavaScriptParser::CaseBlockContext::defaultClause() {
  return getRuleContext<JavaScriptParser::DefaultClauseContext>(0);
}


size_t JavaScriptParser::CaseBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseBlock;
}


std::any JavaScriptParser::CaseBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitCaseBlock(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::CaseBlockContext* JavaScriptParser::caseBlock() {
  CaseBlockContext *_localctx = _tracker.createInstance<CaseBlockContext>(_ctx, getState());
  enterRule(_localctx, 34, JavaScriptParser::RuleCaseBlock);
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
    setState(308);
    match(JavaScriptParser::LBRACE);
    setState(310);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::CASE) {
      setState(309);
      caseClauses();
    }
    setState(316);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::DEFAULT) {
      setState(312);
      defaultClause();
      setState(314);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::CASE) {
        setState(313);
        caseClauses();
      }
    }
    setState(318);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClausesContext ------------------------------------------------------------------

JavaScriptParser::CaseClausesContext::CaseClausesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::CaseClauseContext *> JavaScriptParser::CaseClausesContext::caseClause() {
  return getRuleContexts<JavaScriptParser::CaseClauseContext>();
}

JavaScriptParser::CaseClauseContext* JavaScriptParser::CaseClausesContext::caseClause(size_t i) {
  return getRuleContext<JavaScriptParser::CaseClauseContext>(i);
}


size_t JavaScriptParser::CaseClausesContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseClauses;
}


std::any JavaScriptParser::CaseClausesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitCaseClauses(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::CaseClausesContext* JavaScriptParser::caseClauses() {
  CaseClausesContext *_localctx = _tracker.createInstance<CaseClausesContext>(_ctx, getState());
  enterRule(_localctx, 36, JavaScriptParser::RuleCaseClauses);
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
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(320);
      caseClause();
      setState(323); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == JavaScriptParser::CASE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClauseContext ------------------------------------------------------------------

JavaScriptParser::CaseClauseContext::CaseClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CaseClauseContext::CASE() {
  return getToken(JavaScriptParser::CASE, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::CaseClauseContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::CaseClauseContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::CaseClauseContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::CaseClauseContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}


size_t JavaScriptParser::CaseClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseClause;
}


std::any JavaScriptParser::CaseClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitCaseClause(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::CaseClauseContext* JavaScriptParser::caseClause() {
  CaseClauseContext *_localctx = _tracker.createInstance<CaseClauseContext>(_ctx, getState());
  enterRule(_localctx, 38, JavaScriptParser::RuleCaseClause);
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
    match(JavaScriptParser::CASE);
    setState(326);
    expressionSequence();
    setState(327);
    match(JavaScriptParser::COLON);
    setState(331);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::NULL_LITERAL)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::UNDEFINED)
      | (1ULL << JavaScriptParser::LPAREN)
      | (1ULL << JavaScriptParser::LBRACE)
      | (1ULL << JavaScriptParser::LBRACKET)
      | (1ULL << JavaScriptParser::SEMICOLON))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
      | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
      | (1ULL << (JavaScriptParser::PLUS - 74))
      | (1ULL << (JavaScriptParser::MINUS - 74))
      | (1ULL << (JavaScriptParser::TILDE - 74))
      | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
      | (1ULL << (JavaScriptParser::NUMBER - 74))
      | (1ULL << (JavaScriptParser::STRING - 74))
      | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
      setState(328);
      statement();
      setState(333);
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

//----------------- DefaultClauseContext ------------------------------------------------------------------

JavaScriptParser::DefaultClauseContext::DefaultClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::DefaultClauseContext::DEFAULT() {
  return getToken(JavaScriptParser::DEFAULT, 0);
}

tree::TerminalNode* JavaScriptParser::DefaultClauseContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::DefaultClauseContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::DefaultClauseContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}


size_t JavaScriptParser::DefaultClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleDefaultClause;
}


std::any JavaScriptParser::DefaultClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitDefaultClause(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::DefaultClauseContext* JavaScriptParser::defaultClause() {
  DefaultClauseContext *_localctx = _tracker.createInstance<DefaultClauseContext>(_ctx, getState());
  enterRule(_localctx, 40, JavaScriptParser::RuleDefaultClause);
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
    setState(334);
    match(JavaScriptParser::DEFAULT);
    setState(335);
    match(JavaScriptParser::COLON);
    setState(339);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::NULL_LITERAL)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::UNDEFINED)
      | (1ULL << JavaScriptParser::LPAREN)
      | (1ULL << JavaScriptParser::LBRACE)
      | (1ULL << JavaScriptParser::LBRACKET)
      | (1ULL << JavaScriptParser::SEMICOLON))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
      | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
      | (1ULL << (JavaScriptParser::PLUS - 74))
      | (1ULL << (JavaScriptParser::MINUS - 74))
      | (1ULL << (JavaScriptParser::TILDE - 74))
      | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
      | (1ULL << (JavaScriptParser::NUMBER - 74))
      | (1ULL << (JavaScriptParser::STRING - 74))
      | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
      setState(336);
      statement();
      setState(341);
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

//----------------- ThrowStatementContext ------------------------------------------------------------------

JavaScriptParser::ThrowStatementContext::ThrowStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ThrowStatementContext::THROW() {
  return getToken(JavaScriptParser::THROW, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ThrowStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::ThrowStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::ThrowStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleThrowStatement;
}


std::any JavaScriptParser::ThrowStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitThrowStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ThrowStatementContext* JavaScriptParser::throwStatement() {
  ThrowStatementContext *_localctx = _tracker.createInstance<ThrowStatementContext>(_ctx, getState());
  enterRule(_localctx, 42, JavaScriptParser::RuleThrowStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(342);
    match(JavaScriptParser::THROW);
    setState(343);
    expressionSequence();
    setState(344);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TryStatementContext ------------------------------------------------------------------

JavaScriptParser::TryStatementContext::TryStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::TryStatementContext::TRY() {
  return getToken(JavaScriptParser::TRY, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::TryStatementContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::CatchClauseContext* JavaScriptParser::TryStatementContext::catchClause() {
  return getRuleContext<JavaScriptParser::CatchClauseContext>(0);
}

JavaScriptParser::FinallyClauseContext* JavaScriptParser::TryStatementContext::finallyClause() {
  return getRuleContext<JavaScriptParser::FinallyClauseContext>(0);
}


size_t JavaScriptParser::TryStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleTryStatement;
}


std::any JavaScriptParser::TryStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitTryStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::TryStatementContext* JavaScriptParser::tryStatement() {
  TryStatementContext *_localctx = _tracker.createInstance<TryStatementContext>(_ctx, getState());
  enterRule(_localctx, 44, JavaScriptParser::RuleTryStatement);
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
    setState(346);
    match(JavaScriptParser::TRY);
    setState(347);
    block();
    setState(353);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::CATCH: {
        setState(348);
        catchClause();
        setState(350);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == JavaScriptParser::FINALLY) {
          setState(349);
          finallyClause();
        }
        break;
      }

      case JavaScriptParser::FINALLY: {
        setState(352);
        finallyClause();
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

//----------------- CatchClauseContext ------------------------------------------------------------------

JavaScriptParser::CatchClauseContext::CatchClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CatchClauseContext::CATCH() {
  return getToken(JavaScriptParser::CATCH, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::CatchClauseContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

tree::TerminalNode* JavaScriptParser::CatchClauseContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::AssignableContext* JavaScriptParser::CatchClauseContext::assignable() {
  return getRuleContext<JavaScriptParser::AssignableContext>(0);
}

tree::TerminalNode* JavaScriptParser::CatchClauseContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}


size_t JavaScriptParser::CatchClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleCatchClause;
}


std::any JavaScriptParser::CatchClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitCatchClause(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::CatchClauseContext* JavaScriptParser::catchClause() {
  CatchClauseContext *_localctx = _tracker.createInstance<CatchClauseContext>(_ctx, getState());
  enterRule(_localctx, 46, JavaScriptParser::RuleCatchClause);
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
    setState(355);
    match(JavaScriptParser::CATCH);
    setState(360);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::LPAREN) {
      setState(356);
      match(JavaScriptParser::LPAREN);
      setState(357);
      assignable();
      setState(358);
      match(JavaScriptParser::RPAREN);
    }
    setState(362);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FinallyClauseContext ------------------------------------------------------------------

JavaScriptParser::FinallyClauseContext::FinallyClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FinallyClauseContext::FINALLY() {
  return getToken(JavaScriptParser::FINALLY, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::FinallyClauseContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}


size_t JavaScriptParser::FinallyClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleFinallyClause;
}


std::any JavaScriptParser::FinallyClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitFinallyClause(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FinallyClauseContext* JavaScriptParser::finallyClause() {
  FinallyClauseContext *_localctx = _tracker.createInstance<FinallyClauseContext>(_ctx, getState());
  enterRule(_localctx, 48, JavaScriptParser::RuleFinallyClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(364);
    match(JavaScriptParser::FINALLY);
    setState(365);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

JavaScriptParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::FUNCTION() {
  return getToken(JavaScriptParser::FUNCTION, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::FunctionDeclarationContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::ASYNC() {
  return getToken(JavaScriptParser::ASYNC, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::STAR() {
  return getToken(JavaScriptParser::STAR, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::FunctionDeclarationContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::FunctionDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleFunctionDeclaration;
}


std::any JavaScriptParser::FunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 50, JavaScriptParser::RuleFunctionDeclaration);
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
    setState(368);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::ASYNC) {
      setState(367);
      match(JavaScriptParser::ASYNC);
    }
    setState(370);
    match(JavaScriptParser::FUNCTION);
    setState(372);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::STAR) {
      setState(371);
      match(JavaScriptParser::STAR);
    }
    setState(374);
    match(JavaScriptParser::IDENTIFIER);
    setState(375);
    match(JavaScriptParser::LPAREN);
    setState(377);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 49) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 49)) & ((1ULL << (JavaScriptParser::LBRACE - 49))
      | (1ULL << (JavaScriptParser::LBRACKET - 49))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 49))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 49)))) != 0)) {
      setState(376);
      formalParameterList();
    }
    setState(379);
    match(JavaScriptParser::RPAREN);
    setState(380);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclarationContext ------------------------------------------------------------------

JavaScriptParser::ClassDeclarationContext::ClassDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ClassDeclarationContext::CLASS() {
  return getToken(JavaScriptParser::CLASS, 0);
}

tree::TerminalNode* JavaScriptParser::ClassDeclarationContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

JavaScriptParser::ClassTailContext* JavaScriptParser::ClassDeclarationContext::classTail() {
  return getRuleContext<JavaScriptParser::ClassTailContext>(0);
}

tree::TerminalNode* JavaScriptParser::ClassDeclarationContext::EXTENDS() {
  return getToken(JavaScriptParser::EXTENDS, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ClassDeclarationContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}


size_t JavaScriptParser::ClassDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassDeclaration;
}


std::any JavaScriptParser::ClassDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitClassDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::classDeclaration() {
  ClassDeclarationContext *_localctx = _tracker.createInstance<ClassDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 52, JavaScriptParser::RuleClassDeclaration);
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
    setState(382);
    match(JavaScriptParser::CLASS);
    setState(383);
    match(JavaScriptParser::IDENTIFIER);
    setState(386);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::EXTENDS) {
      setState(384);
      match(JavaScriptParser::EXTENDS);
      setState(385);
      singleExpression(0);
    }
    setState(388);
    classTail();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassTailContext ------------------------------------------------------------------

JavaScriptParser::ClassTailContext::ClassTailContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ClassTailContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::ClassTailContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::ClassElementContext *> JavaScriptParser::ClassTailContext::classElement() {
  return getRuleContexts<JavaScriptParser::ClassElementContext>();
}

JavaScriptParser::ClassElementContext* JavaScriptParser::ClassTailContext::classElement(size_t i) {
  return getRuleContext<JavaScriptParser::ClassElementContext>(i);
}


size_t JavaScriptParser::ClassTailContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassTail;
}


std::any JavaScriptParser::ClassTailContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitClassTail(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ClassTailContext* JavaScriptParser::classTail() {
  ClassTailContext *_localctx = _tracker.createInstance<ClassTailContext>(_ctx, getState());
  enterRule(_localctx, 54, JavaScriptParser::RuleClassTail);
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
    setState(390);
    match(JavaScriptParser::LBRACE);
    setState(394);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::FROM)
      | (1ULL << JavaScriptParser::AS)
      | (1ULL << JavaScriptParser::OF)
      | (1ULL << JavaScriptParser::GET)
      | (1ULL << JavaScriptParser::SET)
      | (1ULL << JavaScriptParser::NULL_LITERAL)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::LBRACKET)
      | (1ULL << JavaScriptParser::SEMICOLON))) != 0) || ((((_la - 80) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 80)) & ((1ULL << (JavaScriptParser::STAR - 80))
      | (1ULL << (JavaScriptParser::NUMBER - 80))
      | (1ULL << (JavaScriptParser::STRING - 80))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 80)))) != 0)) {
      setState(391);
      classElement();
      setState(396);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(397);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassElementContext ------------------------------------------------------------------

JavaScriptParser::ClassElementContext::ClassElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::MethodDefinitionContext* JavaScriptParser::ClassElementContext::methodDefinition() {
  return getRuleContext<JavaScriptParser::MethodDefinitionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ClassElementContext::STATIC() {
  return getToken(JavaScriptParser::STATIC, 0);
}

JavaScriptParser::EmptyStatementContext* JavaScriptParser::ClassElementContext::emptyStatement() {
  return getRuleContext<JavaScriptParser::EmptyStatementContext>(0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::ClassElementContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::ClassElementContext::EQUALS() {
  return getToken(JavaScriptParser::EQUALS, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ClassElementContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ClassElementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}


size_t JavaScriptParser::ClassElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassElement;
}


std::any JavaScriptParser::ClassElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitClassElement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ClassElementContext* JavaScriptParser::classElement() {
  ClassElementContext *_localctx = _tracker.createInstance<ClassElementContext>(_ctx, getState());
  enterRule(_localctx, 56, JavaScriptParser::RuleClassElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(409);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(400);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
      case 1: {
        setState(399);
        match(JavaScriptParser::STATIC);
        break;
      }

      default:
        break;
      }
      setState(402);
      methodDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(403);
      emptyStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(404);
      propertyName();
      setState(405);
      match(JavaScriptParser::EQUALS);
      setState(406);
      singleExpression(0);
      setState(407);
      match(JavaScriptParser::SEMICOLON);
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

//----------------- MethodDefinitionContext ------------------------------------------------------------------

JavaScriptParser::MethodDefinitionContext::MethodDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::MethodDefinitionContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::MethodDefinitionContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::MethodDefinitionContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}

JavaScriptParser::GetterContext* JavaScriptParser::MethodDefinitionContext::getter() {
  return getRuleContext<JavaScriptParser::GetterContext>(0);
}

JavaScriptParser::SetterContext* JavaScriptParser::MethodDefinitionContext::setter() {
  return getRuleContext<JavaScriptParser::SetterContext>(0);
}

JavaScriptParser::GeneratorMethodContext* JavaScriptParser::MethodDefinitionContext::generatorMethod() {
  return getRuleContext<JavaScriptParser::GeneratorMethodContext>(0);
}

JavaScriptParser::AsyncMethodContext* JavaScriptParser::MethodDefinitionContext::asyncMethod() {
  return getRuleContext<JavaScriptParser::AsyncMethodContext>(0);
}


size_t JavaScriptParser::MethodDefinitionContext::getRuleIndex() const {
  return JavaScriptParser::RuleMethodDefinition;
}


std::any JavaScriptParser::MethodDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitMethodDefinition(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::MethodDefinitionContext* JavaScriptParser::methodDefinition() {
  MethodDefinitionContext *_localctx = _tracker.createInstance<MethodDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 58, JavaScriptParser::RuleMethodDefinition);
  size_t _la = 0;

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(411);
      propertyName();
      setState(412);
      match(JavaScriptParser::LPAREN);
      setState(414);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 49) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 49)) & ((1ULL << (JavaScriptParser::LBRACE - 49))
        | (1ULL << (JavaScriptParser::LBRACKET - 49))
        | (1ULL << (JavaScriptParser::ELLIPSIS - 49))
        | (1ULL << (JavaScriptParser::IDENTIFIER - 49)))) != 0)) {
        setState(413);
        formalParameterList();
      }
      setState(416);
      match(JavaScriptParser::RPAREN);
      setState(417);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(419);
      getter();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(420);
      setter();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(421);
      generatorMethod();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(422);
      asyncMethod();
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

//----------------- GetterContext ------------------------------------------------------------------

JavaScriptParser::GetterContext::GetterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::GetterContext::GET() {
  return getToken(JavaScriptParser::GET, 0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::GetterContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::GetterContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::GetterContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::GetterContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}


size_t JavaScriptParser::GetterContext::getRuleIndex() const {
  return JavaScriptParser::RuleGetter;
}


std::any JavaScriptParser::GetterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitGetter(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::GetterContext* JavaScriptParser::getter() {
  GetterContext *_localctx = _tracker.createInstance<GetterContext>(_ctx, getState());
  enterRule(_localctx, 60, JavaScriptParser::RuleGetter);

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
    match(JavaScriptParser::GET);
    setState(426);
    propertyName();
    setState(427);
    match(JavaScriptParser::LPAREN);
    setState(428);
    match(JavaScriptParser::RPAREN);
    setState(429);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetterContext ------------------------------------------------------------------

JavaScriptParser::SetterContext::SetterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::SetterContext::SET() {
  return getToken(JavaScriptParser::SET, 0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::SetterContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::SetterContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::SetterContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}

tree::TerminalNode* JavaScriptParser::SetterContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::SetterContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}


size_t JavaScriptParser::SetterContext::getRuleIndex() const {
  return JavaScriptParser::RuleSetter;
}


std::any JavaScriptParser::SetterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitSetter(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::SetterContext* JavaScriptParser::setter() {
  SetterContext *_localctx = _tracker.createInstance<SetterContext>(_ctx, getState());
  enterRule(_localctx, 62, JavaScriptParser::RuleSetter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(431);
    match(JavaScriptParser::SET);
    setState(432);
    propertyName();
    setState(433);
    match(JavaScriptParser::LPAREN);
    setState(434);
    formalParameterList();
    setState(435);
    match(JavaScriptParser::RPAREN);
    setState(436);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GeneratorMethodContext ------------------------------------------------------------------

JavaScriptParser::GeneratorMethodContext::GeneratorMethodContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::GeneratorMethodContext::STAR() {
  return getToken(JavaScriptParser::STAR, 0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::GeneratorMethodContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::GeneratorMethodContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::GeneratorMethodContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::GeneratorMethodContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::GeneratorMethodContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::GeneratorMethodContext::getRuleIndex() const {
  return JavaScriptParser::RuleGeneratorMethod;
}


std::any JavaScriptParser::GeneratorMethodContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitGeneratorMethod(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::GeneratorMethodContext* JavaScriptParser::generatorMethod() {
  GeneratorMethodContext *_localctx = _tracker.createInstance<GeneratorMethodContext>(_ctx, getState());
  enterRule(_localctx, 64, JavaScriptParser::RuleGeneratorMethod);
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
    match(JavaScriptParser::STAR);
    setState(439);
    propertyName();
    setState(440);
    match(JavaScriptParser::LPAREN);
    setState(442);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 49) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 49)) & ((1ULL << (JavaScriptParser::LBRACE - 49))
      | (1ULL << (JavaScriptParser::LBRACKET - 49))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 49))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 49)))) != 0)) {
      setState(441);
      formalParameterList();
    }
    setState(444);
    match(JavaScriptParser::RPAREN);
    setState(445);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AsyncMethodContext ------------------------------------------------------------------

JavaScriptParser::AsyncMethodContext::AsyncMethodContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::AsyncMethodContext::ASYNC() {
  return getToken(JavaScriptParser::ASYNC, 0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::AsyncMethodContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::AsyncMethodContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::AsyncMethodContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::AsyncMethodContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::AsyncMethodContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::AsyncMethodContext::getRuleIndex() const {
  return JavaScriptParser::RuleAsyncMethod;
}


std::any JavaScriptParser::AsyncMethodContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitAsyncMethod(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::AsyncMethodContext* JavaScriptParser::asyncMethod() {
  AsyncMethodContext *_localctx = _tracker.createInstance<AsyncMethodContext>(_ctx, getState());
  enterRule(_localctx, 66, JavaScriptParser::RuleAsyncMethod);
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
    setState(447);
    match(JavaScriptParser::ASYNC);
    setState(448);
    propertyName();
    setState(449);
    match(JavaScriptParser::LPAREN);
    setState(451);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 49) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 49)) & ((1ULL << (JavaScriptParser::LBRACE - 49))
      | (1ULL << (JavaScriptParser::LBRACKET - 49))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 49))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 49)))) != 0)) {
      setState(450);
      formalParameterList();
    }
    setState(453);
    match(JavaScriptParser::RPAREN);
    setState(454);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

JavaScriptParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ImportStatementContext::IMPORT() {
  return getToken(JavaScriptParser::IMPORT, 0);
}

tree::TerminalNode* JavaScriptParser::ImportStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::ImportFromBlockContext* JavaScriptParser::ImportStatementContext::importFromBlock() {
  return getRuleContext<JavaScriptParser::ImportFromBlockContext>(0);
}

tree::TerminalNode* JavaScriptParser::ImportStatementContext::STRING() {
  return getToken(JavaScriptParser::STRING, 0);
}


size_t JavaScriptParser::ImportStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportStatement;
}


std::any JavaScriptParser::ImportStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitImportStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportStatementContext* JavaScriptParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 68, JavaScriptParser::RuleImportStatement);

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
    match(JavaScriptParser::IMPORT);
    setState(459);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::LBRACE:
      case JavaScriptParser::STAR: {
        setState(457);
        importFromBlock();
        break;
      }

      case JavaScriptParser::STRING: {
        setState(458);
        match(JavaScriptParser::STRING);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(461);
    match(JavaScriptParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportFromBlockContext ------------------------------------------------------------------

JavaScriptParser::ImportFromBlockContext::ImportFromBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ImportFromBlockContext::FROM() {
  return getToken(JavaScriptParser::FROM, 0);
}

tree::TerminalNode* JavaScriptParser::ImportFromBlockContext::STRING() {
  return getToken(JavaScriptParser::STRING, 0);
}

tree::TerminalNode* JavaScriptParser::ImportFromBlockContext::STAR() {
  return getToken(JavaScriptParser::STAR, 0);
}

tree::TerminalNode* JavaScriptParser::ImportFromBlockContext::AS() {
  return getToken(JavaScriptParser::AS, 0);
}

tree::TerminalNode* JavaScriptParser::ImportFromBlockContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

JavaScriptParser::ImportNamespaceContext* JavaScriptParser::ImportFromBlockContext::importNamespace() {
  return getRuleContext<JavaScriptParser::ImportNamespaceContext>(0);
}


size_t JavaScriptParser::ImportFromBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportFromBlock;
}


std::any JavaScriptParser::ImportFromBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitImportFromBlock(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportFromBlockContext* JavaScriptParser::importFromBlock() {
  ImportFromBlockContext *_localctx = _tracker.createInstance<ImportFromBlockContext>(_ctx, getState());
  enterRule(_localctx, 70, JavaScriptParser::RuleImportFromBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(467);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::STAR: {
        setState(463);
        match(JavaScriptParser::STAR);
        setState(464);
        match(JavaScriptParser::AS);
        setState(465);
        match(JavaScriptParser::IDENTIFIER);
        break;
      }

      case JavaScriptParser::LBRACE: {
        setState(466);
        importNamespace();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(469);
    match(JavaScriptParser::FROM);
    setState(470);
    match(JavaScriptParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportNamespaceContext ------------------------------------------------------------------

JavaScriptParser::ImportNamespaceContext::ImportNamespaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ImportNamespaceContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::ImportNamespaceContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::ImportSpecifierContext *> JavaScriptParser::ImportNamespaceContext::importSpecifier() {
  return getRuleContexts<JavaScriptParser::ImportSpecifierContext>();
}

JavaScriptParser::ImportSpecifierContext* JavaScriptParser::ImportNamespaceContext::importSpecifier(size_t i) {
  return getRuleContext<JavaScriptParser::ImportSpecifierContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ImportNamespaceContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ImportNamespaceContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ImportNamespaceContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportNamespace;
}


std::any JavaScriptParser::ImportNamespaceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitImportNamespace(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportNamespaceContext* JavaScriptParser::importNamespace() {
  ImportNamespaceContext *_localctx = _tracker.createInstance<ImportNamespaceContext>(_ctx, getState());
  enterRule(_localctx, 72, JavaScriptParser::RuleImportNamespace);
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
    match(JavaScriptParser::LBRACE);
    setState(481);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::STRING

    || _la == JavaScriptParser::IDENTIFIER) {
      setState(473);
      importSpecifier();
      setState(478);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaScriptParser::COMMA) {
        setState(474);
        match(JavaScriptParser::COMMA);
        setState(475);
        importSpecifier();
        setState(480);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(483);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportSpecifierContext ------------------------------------------------------------------

JavaScriptParser::ImportSpecifierContext::ImportSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaScriptParser::ImportSpecifierContext::IDENTIFIER() {
  return getTokens(JavaScriptParser::IDENTIFIER);
}

tree::TerminalNode* JavaScriptParser::ImportSpecifierContext::IDENTIFIER(size_t i) {
  return getToken(JavaScriptParser::IDENTIFIER, i);
}

JavaScriptParser::ModuleExportNameContext* JavaScriptParser::ImportSpecifierContext::moduleExportName() {
  return getRuleContext<JavaScriptParser::ModuleExportNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::ImportSpecifierContext::AS() {
  return getToken(JavaScriptParser::AS, 0);
}


size_t JavaScriptParser::ImportSpecifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportSpecifier;
}


std::any JavaScriptParser::ImportSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitImportSpecifier(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportSpecifierContext* JavaScriptParser::importSpecifier() {
  ImportSpecifierContext *_localctx = _tracker.createInstance<ImportSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 74, JavaScriptParser::RuleImportSpecifier);
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
    setState(487);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      setState(485);
      match(JavaScriptParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(486);
      moduleExportName();
      break;
    }

    default:
      break;
    }
    setState(491);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::AS) {
      setState(489);
      match(JavaScriptParser::AS);
      setState(490);
      match(JavaScriptParser::IDENTIFIER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModuleExportNameContext ------------------------------------------------------------------

JavaScriptParser::ModuleExportNameContext::ModuleExportNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ModuleExportNameContext::STRING() {
  return getToken(JavaScriptParser::STRING, 0);
}

tree::TerminalNode* JavaScriptParser::ModuleExportNameContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}


size_t JavaScriptParser::ModuleExportNameContext::getRuleIndex() const {
  return JavaScriptParser::RuleModuleExportName;
}


std::any JavaScriptParser::ModuleExportNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitModuleExportName(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ModuleExportNameContext* JavaScriptParser::moduleExportName() {
  ModuleExportNameContext *_localctx = _tracker.createInstance<ModuleExportNameContext>(_ctx, getState());
  enterRule(_localctx, 76, JavaScriptParser::RuleModuleExportName);
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
    setState(493);
    _la = _input->LA(1);
    if (!(_la == JavaScriptParser::STRING

    || _la == JavaScriptParser::IDENTIFIER)) {
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

//----------------- ExportStatementContext ------------------------------------------------------------------

JavaScriptParser::ExportStatementContext::ExportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ExportStatementContext::EXPORT() {
  return getToken(JavaScriptParser::EXPORT, 0);
}

tree::TerminalNode* JavaScriptParser::ExportStatementContext::SEMICOLON() {
  return getToken(JavaScriptParser::SEMICOLON, 0);
}

JavaScriptParser::ExportFromBlockContext* JavaScriptParser::ExportStatementContext::exportFromBlock() {
  return getRuleContext<JavaScriptParser::ExportFromBlockContext>(0);
}

JavaScriptParser::DeclarationContext* JavaScriptParser::ExportStatementContext::declaration() {
  return getRuleContext<JavaScriptParser::DeclarationContext>(0);
}

tree::TerminalNode* JavaScriptParser::ExportStatementContext::DEFAULT() {
  return getToken(JavaScriptParser::DEFAULT, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ExportStatementContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}


size_t JavaScriptParser::ExportStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportStatement;
}


std::any JavaScriptParser::ExportStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitExportStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExportStatementContext* JavaScriptParser::exportStatement() {
  ExportStatementContext *_localctx = _tracker.createInstance<ExportStatementContext>(_ctx, getState());
  enterRule(_localctx, 78, JavaScriptParser::RuleExportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(507);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(495);
      match(JavaScriptParser::EXPORT);
      setState(498);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaScriptParser::LBRACE:
        case JavaScriptParser::STAR: {
          setState(496);
          exportFromBlock();
          break;
        }

        case JavaScriptParser::VAR:
        case JavaScriptParser::FUNCTION:
        case JavaScriptParser::CLASS:
        case JavaScriptParser::CONST:
        case JavaScriptParser::ASYNC:
        case JavaScriptParser::LET: {
          setState(497);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(500);
      match(JavaScriptParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(502);
      match(JavaScriptParser::EXPORT);
      setState(503);
      match(JavaScriptParser::DEFAULT);
      setState(504);
      singleExpression(0);
      setState(505);
      match(JavaScriptParser::SEMICOLON);
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

//----------------- ExportFromBlockContext ------------------------------------------------------------------

JavaScriptParser::ExportFromBlockContext::ExportFromBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ExportFromBlockContext::FROM() {
  return getToken(JavaScriptParser::FROM, 0);
}

tree::TerminalNode* JavaScriptParser::ExportFromBlockContext::STRING() {
  return getToken(JavaScriptParser::STRING, 0);
}

tree::TerminalNode* JavaScriptParser::ExportFromBlockContext::STAR() {
  return getToken(JavaScriptParser::STAR, 0);
}

JavaScriptParser::ExportNamespaceContext* JavaScriptParser::ExportFromBlockContext::exportNamespace() {
  return getRuleContext<JavaScriptParser::ExportNamespaceContext>(0);
}


size_t JavaScriptParser::ExportFromBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportFromBlock;
}


std::any JavaScriptParser::ExportFromBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitExportFromBlock(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExportFromBlockContext* JavaScriptParser::exportFromBlock() {
  ExportFromBlockContext *_localctx = _tracker.createInstance<ExportFromBlockContext>(_ctx, getState());
  enterRule(_localctx, 80, JavaScriptParser::RuleExportFromBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(511);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::STAR: {
        setState(509);
        match(JavaScriptParser::STAR);
        break;
      }

      case JavaScriptParser::LBRACE: {
        setState(510);
        exportNamespace();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(513);
    match(JavaScriptParser::FROM);
    setState(514);
    match(JavaScriptParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportNamespaceContext ------------------------------------------------------------------

JavaScriptParser::ExportNamespaceContext::ExportNamespaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ExportNamespaceContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

tree::TerminalNode* JavaScriptParser::ExportNamespaceContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<JavaScriptParser::ExportSpecifierContext *> JavaScriptParser::ExportNamespaceContext::exportSpecifier() {
  return getRuleContexts<JavaScriptParser::ExportSpecifierContext>();
}

JavaScriptParser::ExportSpecifierContext* JavaScriptParser::ExportNamespaceContext::exportSpecifier(size_t i) {
  return getRuleContext<JavaScriptParser::ExportSpecifierContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ExportNamespaceContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ExportNamespaceContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ExportNamespaceContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportNamespace;
}


std::any JavaScriptParser::ExportNamespaceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitExportNamespace(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExportNamespaceContext* JavaScriptParser::exportNamespace() {
  ExportNamespaceContext *_localctx = _tracker.createInstance<ExportNamespaceContext>(_ctx, getState());
  enterRule(_localctx, 82, JavaScriptParser::RuleExportNamespace);
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
    setState(516);
    match(JavaScriptParser::LBRACE);
    setState(525);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::STRING

    || _la == JavaScriptParser::IDENTIFIER) {
      setState(517);
      exportSpecifier();
      setState(522);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaScriptParser::COMMA) {
        setState(518);
        match(JavaScriptParser::COMMA);
        setState(519);
        exportSpecifier();
        setState(524);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(527);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportSpecifierContext ------------------------------------------------------------------

JavaScriptParser::ExportSpecifierContext::ExportSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ExportSpecifierContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

std::vector<JavaScriptParser::ModuleExportNameContext *> JavaScriptParser::ExportSpecifierContext::moduleExportName() {
  return getRuleContexts<JavaScriptParser::ModuleExportNameContext>();
}

JavaScriptParser::ModuleExportNameContext* JavaScriptParser::ExportSpecifierContext::moduleExportName(size_t i) {
  return getRuleContext<JavaScriptParser::ModuleExportNameContext>(i);
}

tree::TerminalNode* JavaScriptParser::ExportSpecifierContext::AS() {
  return getToken(JavaScriptParser::AS, 0);
}


size_t JavaScriptParser::ExportSpecifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportSpecifier;
}


std::any JavaScriptParser::ExportSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitExportSpecifier(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExportSpecifierContext* JavaScriptParser::exportSpecifier() {
  ExportSpecifierContext *_localctx = _tracker.createInstance<ExportSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 84, JavaScriptParser::RuleExportSpecifier);
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
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      setState(529);
      match(JavaScriptParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(530);
      moduleExportName();
      break;
    }

    default:
      break;
    }
    setState(535);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::AS) {
      setState(533);
      match(JavaScriptParser::AS);
      setState(534);
      moduleExportName();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

JavaScriptParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::VariableStatementContext* JavaScriptParser::DeclarationContext::variableStatement() {
  return getRuleContext<JavaScriptParser::VariableStatementContext>(0);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::DeclarationContext::classDeclaration() {
  return getRuleContext<JavaScriptParser::ClassDeclarationContext>(0);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::DeclarationContext::functionDeclaration() {
  return getRuleContext<JavaScriptParser::FunctionDeclarationContext>(0);
}


size_t JavaScriptParser::DeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleDeclaration;
}


std::any JavaScriptParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::DeclarationContext* JavaScriptParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 86, JavaScriptParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(540);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::VAR:
      case JavaScriptParser::CONST:
      case JavaScriptParser::LET: {
        enterOuterAlt(_localctx, 1);
        setState(537);
        variableStatement();
        break;
      }

      case JavaScriptParser::CLASS: {
        enterOuterAlt(_localctx, 2);
        setState(538);
        classDeclaration();
        break;
      }

      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::ASYNC: {
        enterOuterAlt(_localctx, 3);
        setState(539);
        functionDeclaration();
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

//----------------- FormalParameterListContext ------------------------------------------------------------------

JavaScriptParser::FormalParameterListContext::FormalParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::FormalParameterContext *> JavaScriptParser::FormalParameterListContext::formalParameter() {
  return getRuleContexts<JavaScriptParser::FormalParameterContext>();
}

JavaScriptParser::FormalParameterContext* JavaScriptParser::FormalParameterListContext::formalParameter(size_t i) {
  return getRuleContext<JavaScriptParser::FormalParameterContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::FormalParameterListContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::FormalParameterListContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}

JavaScriptParser::RestParameterContext* JavaScriptParser::FormalParameterListContext::restParameter() {
  return getRuleContext<JavaScriptParser::RestParameterContext>(0);
}


size_t JavaScriptParser::FormalParameterListContext::getRuleIndex() const {
  return JavaScriptParser::RuleFormalParameterList;
}


std::any JavaScriptParser::FormalParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitFormalParameterList(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::formalParameterList() {
  FormalParameterListContext *_localctx = _tracker.createInstance<FormalParameterListContext>(_ctx, getState());
  enterRule(_localctx, 88, JavaScriptParser::RuleFormalParameterList);
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
    setState(555);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET:
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(542);
        formalParameter();
        setState(547);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(543);
            match(JavaScriptParser::COMMA);
            setState(544);
            formalParameter(); 
          }
          setState(549);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
        }
        setState(552);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == JavaScriptParser::COMMA) {
          setState(550);
          match(JavaScriptParser::COMMA);
          setState(551);
          restParameter();
        }
        break;
      }

      case JavaScriptParser::ELLIPSIS: {
        enterOuterAlt(_localctx, 2);
        setState(554);
        restParameter();
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

//----------------- FormalParameterContext ------------------------------------------------------------------

JavaScriptParser::FormalParameterContext::FormalParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::AssignableContext* JavaScriptParser::FormalParameterContext::assignable() {
  return getRuleContext<JavaScriptParser::AssignableContext>(0);
}

tree::TerminalNode* JavaScriptParser::FormalParameterContext::EQUALS() {
  return getToken(JavaScriptParser::EQUALS, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::FormalParameterContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}


size_t JavaScriptParser::FormalParameterContext::getRuleIndex() const {
  return JavaScriptParser::RuleFormalParameter;
}


std::any JavaScriptParser::FormalParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitFormalParameter(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FormalParameterContext* JavaScriptParser::formalParameter() {
  FormalParameterContext *_localctx = _tracker.createInstance<FormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 90, JavaScriptParser::RuleFormalParameter);
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
    setState(557);
    assignable();
    setState(560);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::EQUALS) {
      setState(558);
      match(JavaScriptParser::EQUALS);
      setState(559);
      singleExpression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RestParameterContext ------------------------------------------------------------------

JavaScriptParser::RestParameterContext::RestParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::RestParameterContext::ELLIPSIS() {
  return getToken(JavaScriptParser::ELLIPSIS, 0);
}

JavaScriptParser::AssignableContext* JavaScriptParser::RestParameterContext::assignable() {
  return getRuleContext<JavaScriptParser::AssignableContext>(0);
}


size_t JavaScriptParser::RestParameterContext::getRuleIndex() const {
  return JavaScriptParser::RuleRestParameter;
}


std::any JavaScriptParser::RestParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitRestParameter(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::RestParameterContext* JavaScriptParser::restParameter() {
  RestParameterContext *_localctx = _tracker.createInstance<RestParameterContext>(_ctx, getState());
  enterRule(_localctx, 92, JavaScriptParser::RuleRestParameter);

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
    match(JavaScriptParser::ELLIPSIS);
    setState(563);
    assignable();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignableContext ------------------------------------------------------------------

JavaScriptParser::AssignableContext::AssignableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::AssignableContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::AssignableContext::arrayLiteral() {
  return getRuleContext<JavaScriptParser::ArrayLiteralContext>(0);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::AssignableContext::objectLiteral() {
  return getRuleContext<JavaScriptParser::ObjectLiteralContext>(0);
}


size_t JavaScriptParser::AssignableContext::getRuleIndex() const {
  return JavaScriptParser::RuleAssignable;
}


std::any JavaScriptParser::AssignableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitAssignable(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::AssignableContext* JavaScriptParser::assignable() {
  AssignableContext *_localctx = _tracker.createInstance<AssignableContext>(_ctx, getState());
  enterRule(_localctx, 94, JavaScriptParser::RuleAssignable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(568);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(565);
        match(JavaScriptParser::IDENTIFIER);
        break;
      }

      case JavaScriptParser::LBRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(566);
        arrayLiteral();
        break;
      }

      case JavaScriptParser::LBRACE: {
        enterOuterAlt(_localctx, 3);
        setState(567);
        objectLiteral();
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

//----------------- PropertyNameContext ------------------------------------------------------------------

JavaScriptParser::PropertyNameContext::PropertyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::PropertyNameContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyNameContext::STRING() {
  return getToken(JavaScriptParser::STRING, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyNameContext::NUMBER() {
  return getToken(JavaScriptParser::NUMBER, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyNameContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PropertyNameContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyNameContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}


size_t JavaScriptParser::PropertyNameContext::getRuleIndex() const {
  return JavaScriptParser::RulePropertyName;
}


std::any JavaScriptParser::PropertyNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitPropertyName(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::propertyName() {
  PropertyNameContext *_localctx = _tracker.createInstance<PropertyNameContext>(_ctx, getState());
  enterRule(_localctx, 96, JavaScriptParser::RulePropertyName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(577);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::BREAK:
      case JavaScriptParser::DO:
      case JavaScriptParser::INSTANCEOF:
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::CASE:
      case JavaScriptParser::ELSE:
      case JavaScriptParser::NEW:
      case JavaScriptParser::VAR:
      case JavaScriptParser::CATCH:
      case JavaScriptParser::FINALLY:
      case JavaScriptParser::RETURN:
      case JavaScriptParser::VOID:
      case JavaScriptParser::CONTINUE:
      case JavaScriptParser::FOR:
      case JavaScriptParser::SWITCH:
      case JavaScriptParser::WHILE:
      case JavaScriptParser::DEBUGGER:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::WITH:
      case JavaScriptParser::DEFAULT:
      case JavaScriptParser::IF:
      case JavaScriptParser::THROW:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::IN:
      case JavaScriptParser::TRY:
      case JavaScriptParser::CLASS:
      case JavaScriptParser::ENUM:
      case JavaScriptParser::EXTENDS:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::CONST:
      case JavaScriptParser::EXPORT:
      case JavaScriptParser::IMPORT:
      case JavaScriptParser::ASYNC:
      case JavaScriptParser::AWAIT:
      case JavaScriptParser::YIELD:
      case JavaScriptParser::LET:
      case JavaScriptParser::STATIC:
      case JavaScriptParser::FROM:
      case JavaScriptParser::AS:
      case JavaScriptParser::OF:
      case JavaScriptParser::NULL_LITERAL:
      case JavaScriptParser::BOOLEAN:
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(570);
        identifierName();
        break;
      }

      case JavaScriptParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(571);
        match(JavaScriptParser::STRING);
        break;
      }

      case JavaScriptParser::NUMBER: {
        enterOuterAlt(_localctx, 3);
        setState(572);
        match(JavaScriptParser::NUMBER);
        break;
      }

      case JavaScriptParser::LBRACKET: {
        enterOuterAlt(_localctx, 4);
        setState(573);
        match(JavaScriptParser::LBRACKET);
        setState(574);
        singleExpression(0);
        setState(575);
        match(JavaScriptParser::RBRACKET);
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

//----------------- ExpressionSequenceContext ------------------------------------------------------------------

JavaScriptParser::ExpressionSequenceContext::ExpressionSequenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::ExpressionSequenceContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ExpressionSequenceContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ExpressionSequenceContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ExpressionSequenceContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ExpressionSequenceContext::getRuleIndex() const {
  return JavaScriptParser::RuleExpressionSequence;
}


std::any JavaScriptParser::ExpressionSequenceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitExpressionSequence(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::expressionSequence() {
  ExpressionSequenceContext *_localctx = _tracker.createInstance<ExpressionSequenceContext>(_ctx, getState());
  enterRule(_localctx, 98, JavaScriptParser::RuleExpressionSequence);
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
    setState(579);
    singleExpression(0);
    setState(584);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(580);
      match(JavaScriptParser::COMMA);
      setState(581);
      singleExpression(0);
      setState(586);
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

//----------------- SingleExpressionContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext::SingleExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::AnonymousFunctionContext* JavaScriptParser::SingleExpressionContext::anonymousFunction() {
  return getRuleContext<JavaScriptParser::AnonymousFunctionContext>(0);
}

JavaScriptParser::ArrowFunctionContext* JavaScriptParser::SingleExpressionContext::arrowFunction() {
  return getRuleContext<JavaScriptParser::ArrowFunctionContext>(0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::NEW() {
  return getToken(JavaScriptParser::NEW, 0);
}

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::SingleExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::SingleExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

JavaScriptParser::ArgumentsContext* JavaScriptParser::SingleExpressionContext::arguments() {
  return getRuleContext<JavaScriptParser::ArgumentsContext>(0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::DELETE() {
  return getToken(JavaScriptParser::DELETE, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::VOID() {
  return getToken(JavaScriptParser::VOID, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::TYPEOF() {
  return getToken(JavaScriptParser::TYPEOF, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::PLUSPLUS() {
  return getToken(JavaScriptParser::PLUSPLUS, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::MINUSMINUS() {
  return getToken(JavaScriptParser::MINUSMINUS, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::PLUS() {
  return getToken(JavaScriptParser::PLUS, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::MINUS() {
  return getToken(JavaScriptParser::MINUS, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::TILDE() {
  return getToken(JavaScriptParser::TILDE, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::EXCLAMATION() {
  return getToken(JavaScriptParser::EXCLAMATION, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::AWAIT() {
  return getToken(JavaScriptParser::AWAIT, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::THIS() {
  return getToken(JavaScriptParser::THIS, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::SUPER() {
  return getToken(JavaScriptParser::SUPER, 0);
}

JavaScriptParser::LiteralContext* JavaScriptParser::SingleExpressionContext::literal() {
  return getRuleContext<JavaScriptParser::LiteralContext>(0);
}

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::SingleExpressionContext::arrayLiteral() {
  return getRuleContext<JavaScriptParser::ArrayLiteralContext>(0);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::SingleExpressionContext::objectLiteral() {
  return getRuleContext<JavaScriptParser::ObjectLiteralContext>(0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::SingleExpressionContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::TypeofExpressionContext* JavaScriptParser::SingleExpressionContext::typeofExpression() {
  return getRuleContext<JavaScriptParser::TypeofExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::POWER() {
  return getToken(JavaScriptParser::POWER, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::STAR() {
  return getToken(JavaScriptParser::STAR, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::SLASH() {
  return getToken(JavaScriptParser::SLASH, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::PERCENT() {
  return getToken(JavaScriptParser::PERCENT, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::LSHIFT() {
  return getToken(JavaScriptParser::LSHIFT, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::RSHIFT() {
  return getToken(JavaScriptParser::RSHIFT, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::URSHIFT() {
  return getToken(JavaScriptParser::URSHIFT, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::LT() {
  return getToken(JavaScriptParser::LT, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::GT() {
  return getToken(JavaScriptParser::GT, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::LE() {
  return getToken(JavaScriptParser::LE, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::GE() {
  return getToken(JavaScriptParser::GE, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::INSTANCEOF() {
  return getToken(JavaScriptParser::INSTANCEOF, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::IN() {
  return getToken(JavaScriptParser::IN, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::EQUALS_OP() {
  return getToken(JavaScriptParser::EQUALS_OP, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::NOT_EQUALS() {
  return getToken(JavaScriptParser::NOT_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::STRICT_EQUALS() {
  return getToken(JavaScriptParser::STRICT_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::STRICT_NOT_EQUALS() {
  return getToken(JavaScriptParser::STRICT_NOT_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::AMPERSAND() {
  return getToken(JavaScriptParser::AMPERSAND, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::CARET() {
  return getToken(JavaScriptParser::CARET, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::PIPE() {
  return getToken(JavaScriptParser::PIPE, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::AND_OP() {
  return getToken(JavaScriptParser::AND_OP, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::OR_OP() {
  return getToken(JavaScriptParser::OR_OP, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::NULLISH_COALESCING() {
  return getToken(JavaScriptParser::NULLISH_COALESCING, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::QUESTION() {
  return getToken(JavaScriptParser::QUESTION, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::EQUALS() {
  return getToken(JavaScriptParser::EQUALS, 0);
}

JavaScriptParser::AssignmentOperatorContext* JavaScriptParser::SingleExpressionContext::assignmentOperator() {
  return getRuleContext<JavaScriptParser::AssignmentOperatorContext>(0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::SingleExpressionContext::DOT() {
  return getToken(JavaScriptParser::DOT, 0);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::SingleExpressionContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}


size_t JavaScriptParser::SingleExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleSingleExpression;
}


std::any JavaScriptParser::SingleExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitSingleExpression(this);
  else
    return visitor->visitChildren(this);
}


JavaScriptParser::SingleExpressionContext* JavaScriptParser::singleExpression() {
   return singleExpression(0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::singleExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  JavaScriptParser::SingleExpressionContext *_localctx = _tracker.createInstance<SingleExpressionContext>(_ctx, parentState);
  JavaScriptParser::SingleExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 100;
  enterRecursionRule(_localctx, 100, JavaScriptParser::RuleSingleExpression, precedence);

    size_t _la = 0;

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
    setState(626);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(588);
      anonymousFunction();
      break;
    }

    case 2: {
      setState(589);
      arrowFunction();
      break;
    }

    case 3: {
      setState(590);
      match(JavaScriptParser::NEW);
      setState(591);
      singleExpression(0);
      setState(593);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
      case 1: {
        setState(592);
        arguments();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 4: {
      setState(595);
      match(JavaScriptParser::DELETE);
      setState(596);
      singleExpression(35);
      break;
    }

    case 5: {
      setState(597);
      match(JavaScriptParser::VOID);
      setState(598);
      singleExpression(34);
      break;
    }

    case 6: {
      setState(599);
      match(JavaScriptParser::TYPEOF);
      setState(600);
      singleExpression(33);
      break;
    }

    case 7: {
      setState(601);
      match(JavaScriptParser::PLUSPLUS);
      setState(602);
      singleExpression(32);
      break;
    }

    case 8: {
      setState(603);
      match(JavaScriptParser::MINUSMINUS);
      setState(604);
      singleExpression(31);
      break;
    }

    case 9: {
      setState(605);
      match(JavaScriptParser::PLUS);
      setState(606);
      singleExpression(30);
      break;
    }

    case 10: {
      setState(607);
      match(JavaScriptParser::MINUS);
      setState(608);
      singleExpression(29);
      break;
    }

    case 11: {
      setState(609);
      match(JavaScriptParser::TILDE);
      setState(610);
      singleExpression(28);
      break;
    }

    case 12: {
      setState(611);
      match(JavaScriptParser::EXCLAMATION);
      setState(612);
      singleExpression(27);
      break;
    }

    case 13: {
      setState(613);
      match(JavaScriptParser::AWAIT);
      setState(614);
      singleExpression(26);
      break;
    }

    case 14: {
      setState(615);
      match(JavaScriptParser::THIS);
      break;
    }

    case 15: {
      setState(616);
      match(JavaScriptParser::IDENTIFIER);
      break;
    }

    case 16: {
      setState(617);
      match(JavaScriptParser::SUPER);
      break;
    }

    case 17: {
      setState(618);
      literal();
      break;
    }

    case 18: {
      setState(619);
      arrayLiteral();
      break;
    }

    case 19: {
      setState(620);
      objectLiteral();
      break;
    }

    case 20: {
      setState(621);
      match(JavaScriptParser::LPAREN);
      setState(622);
      expressionSequence();
      setState(623);
      match(JavaScriptParser::RPAREN);
      break;
    }

    case 21: {
      setState(625);
      typeofExpression();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(699);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(697);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(628);

          if (!(precpred(_ctx, 25))) throw FailedPredicateException(this, "precpred(_ctx, 25)");
          setState(629);
          match(JavaScriptParser::POWER);
          setState(630);
          singleExpression(26);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(631);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(632);
          _la = _input->LA(1);
          if (!(((((_la - 80) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 80)) & ((1ULL << (JavaScriptParser::STAR - 80))
            | (1ULL << (JavaScriptParser::SLASH - 80))
            | (1ULL << (JavaScriptParser::PERCENT - 80)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(633);
          singleExpression(25);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(634);

          if (!(precpred(_ctx, 23))) throw FailedPredicateException(this, "precpred(_ctx, 23)");
          setState(635);
          _la = _input->LA(1);
          if (!(_la == JavaScriptParser::PLUS

          || _la == JavaScriptParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(636);
          singleExpression(24);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(637);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(638);
          _la = _input->LA(1);
          if (!(((((_la - 85) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 85)) & ((1ULL << (JavaScriptParser::LSHIFT - 85))
            | (1ULL << (JavaScriptParser::RSHIFT - 85))
            | (1ULL << (JavaScriptParser::URSHIFT - 85)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(639);
          singleExpression(23);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(640);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(641);
          _la = _input->LA(1);
          if (!(((((_la - 88) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 88)) & ((1ULL << (JavaScriptParser::LT - 88))
            | (1ULL << (JavaScriptParser::GT - 88))
            | (1ULL << (JavaScriptParser::LE - 88))
            | (1ULL << (JavaScriptParser::GE - 88)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(642);
          singleExpression(22);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(643);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(644);
          match(JavaScriptParser::INSTANCEOF);
          setState(645);
          singleExpression(21);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(646);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(647);
          match(JavaScriptParser::IN);
          setState(648);
          singleExpression(20);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(649);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(650);
          _la = _input->LA(1);
          if (!(((((_la - 92) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 92)) & ((1ULL << (JavaScriptParser::EQUALS_OP - 92))
            | (1ULL << (JavaScriptParser::NOT_EQUALS - 92))
            | (1ULL << (JavaScriptParser::STRICT_EQUALS - 92))
            | (1ULL << (JavaScriptParser::STRICT_NOT_EQUALS - 92)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(651);
          singleExpression(19);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(652);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(653);
          match(JavaScriptParser::AMPERSAND);
          setState(654);
          singleExpression(18);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(655);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(656);
          match(JavaScriptParser::CARET);
          setState(657);
          singleExpression(17);
          break;
        }

        case 11: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(658);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(659);
          match(JavaScriptParser::PIPE);
          setState(660);
          singleExpression(16);
          break;
        }

        case 12: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(661);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(662);
          match(JavaScriptParser::AND_OP);
          setState(663);
          singleExpression(15);
          break;
        }

        case 13: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(664);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(665);
          match(JavaScriptParser::OR_OP);
          setState(666);
          singleExpression(14);
          break;
        }

        case 14: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(667);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(668);
          match(JavaScriptParser::NULLISH_COALESCING);
          setState(669);
          singleExpression(13);
          break;
        }

        case 15: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(670);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(671);
          match(JavaScriptParser::QUESTION);
          setState(672);
          singleExpression(0);
          setState(673);
          match(JavaScriptParser::COLON);
          setState(674);
          singleExpression(12);
          break;
        }

        case 16: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(676);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(677);
          match(JavaScriptParser::EQUALS);
          setState(678);
          singleExpression(11);
          break;
        }

        case 17: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(679);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(680);
          assignmentOperator();
          setState(681);
          singleExpression(10);
          break;
        }

        case 18: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(683);

          if (!(precpred(_ctx, 41))) throw FailedPredicateException(this, "precpred(_ctx, 41)");
          setState(684);
          match(JavaScriptParser::LBRACKET);
          setState(685);
          expressionSequence();
          setState(686);
          match(JavaScriptParser::RBRACKET);
          break;
        }

        case 19: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(688);

          if (!(precpred(_ctx, 40))) throw FailedPredicateException(this, "precpred(_ctx, 40)");
          setState(689);
          match(JavaScriptParser::DOT);
          setState(690);
          identifierName();
          break;
        }

        case 20: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(691);

          if (!(precpred(_ctx, 39))) throw FailedPredicateException(this, "precpred(_ctx, 39)");
          setState(692);
          arguments();
          break;
        }

        case 21: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(693);

          if (!(precpred(_ctx, 37))) throw FailedPredicateException(this, "precpred(_ctx, 37)");
          setState(694);
          match(JavaScriptParser::PLUSPLUS);
          break;
        }

        case 22: {
          _localctx = _tracker.createInstance<SingleExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSingleExpression);
          setState(695);

          if (!(precpred(_ctx, 36))) throw FailedPredicateException(this, "precpred(_ctx, 36)");
          setState(696);
          match(JavaScriptParser::MINUSMINUS);
          break;
        }

        default:
          break;
        } 
      }
      setState(701);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AssignmentOperatorContext ------------------------------------------------------------------

JavaScriptParser::AssignmentOperatorContext::AssignmentOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::STAR_EQUALS() {
  return getToken(JavaScriptParser::STAR_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::SLASH_EQUALS() {
  return getToken(JavaScriptParser::SLASH_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::PERCENT_EQUALS() {
  return getToken(JavaScriptParser::PERCENT_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::PLUS_EQUALS() {
  return getToken(JavaScriptParser::PLUS_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::MINUS_EQUALS() {
  return getToken(JavaScriptParser::MINUS_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::LSHIFT_EQUALS() {
  return getToken(JavaScriptParser::LSHIFT_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::RSHIFT_EQUALS() {
  return getToken(JavaScriptParser::RSHIFT_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::URSHIFT_EQUALS() {
  return getToken(JavaScriptParser::URSHIFT_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::AMPERSAND_EQUALS() {
  return getToken(JavaScriptParser::AMPERSAND_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::CARET_EQUALS() {
  return getToken(JavaScriptParser::CARET_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::PIPE_EQUALS() {
  return getToken(JavaScriptParser::PIPE_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::POWER_EQUALS() {
  return getToken(JavaScriptParser::POWER_EQUALS, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::NULLISH_EQUALS() {
  return getToken(JavaScriptParser::NULLISH_EQUALS, 0);
}


size_t JavaScriptParser::AssignmentOperatorContext::getRuleIndex() const {
  return JavaScriptParser::RuleAssignmentOperator;
}


std::any JavaScriptParser::AssignmentOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitAssignmentOperator(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::AssignmentOperatorContext* JavaScriptParser::assignmentOperator() {
  AssignmentOperatorContext *_localctx = _tracker.createInstance<AssignmentOperatorContext>(_ctx, getState());
  enterRule(_localctx, 102, JavaScriptParser::RuleAssignmentOperator);
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
    setState(702);
    _la = _input->LA(1);
    if (!(((((_la - 60) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 60)) & ((1ULL << (JavaScriptParser::STAR_EQUALS - 60))
      | (1ULL << (JavaScriptParser::SLASH_EQUALS - 60))
      | (1ULL << (JavaScriptParser::PERCENT_EQUALS - 60))
      | (1ULL << (JavaScriptParser::PLUS_EQUALS - 60))
      | (1ULL << (JavaScriptParser::MINUS_EQUALS - 60))
      | (1ULL << (JavaScriptParser::LSHIFT_EQUALS - 60))
      | (1ULL << (JavaScriptParser::RSHIFT_EQUALS - 60))
      | (1ULL << (JavaScriptParser::URSHIFT_EQUALS - 60))
      | (1ULL << (JavaScriptParser::AMPERSAND_EQUALS - 60))
      | (1ULL << (JavaScriptParser::CARET_EQUALS - 60))
      | (1ULL << (JavaScriptParser::PIPE_EQUALS - 60))
      | (1ULL << (JavaScriptParser::POWER_EQUALS - 60))
      | (1ULL << (JavaScriptParser::NULLISH_EQUALS - 60)))) != 0))) {
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

//----------------- LiteralContext ------------------------------------------------------------------

JavaScriptParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::LiteralContext::NUMBER() {
  return getToken(JavaScriptParser::NUMBER, 0);
}

tree::TerminalNode* JavaScriptParser::LiteralContext::STRING() {
  return getToken(JavaScriptParser::STRING, 0);
}

tree::TerminalNode* JavaScriptParser::LiteralContext::BOOLEAN() {
  return getToken(JavaScriptParser::BOOLEAN, 0);
}

tree::TerminalNode* JavaScriptParser::LiteralContext::NULL_LITERAL() {
  return getToken(JavaScriptParser::NULL_LITERAL, 0);
}

tree::TerminalNode* JavaScriptParser::LiteralContext::UNDEFINED() {
  return getToken(JavaScriptParser::UNDEFINED, 0);
}

tree::TerminalNode* JavaScriptParser::LiteralContext::TEMPLATE_STRING() {
  return getToken(JavaScriptParser::TEMPLATE_STRING, 0);
}


size_t JavaScriptParser::LiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleLiteral;
}


std::any JavaScriptParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::LiteralContext* JavaScriptParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 104, JavaScriptParser::RuleLiteral);
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
    setState(704);
    _la = _input->LA(1);
    if (!(((((_la - 44) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 44)) & ((1ULL << (JavaScriptParser::NULL_LITERAL - 44))
      | (1ULL << (JavaScriptParser::BOOLEAN - 44))
      | (1ULL << (JavaScriptParser::UNDEFINED - 44))
      | (1ULL << (JavaScriptParser::NUMBER - 44))
      | (1ULL << (JavaScriptParser::STRING - 44))
      | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 44)))) != 0))) {
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

//----------------- ArrayLiteralContext ------------------------------------------------------------------

JavaScriptParser::ArrayLiteralContext::ArrayLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ArrayLiteralContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::ArrayLiteralContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}

JavaScriptParser::ElementListContext* JavaScriptParser::ArrayLiteralContext::elementList() {
  return getRuleContext<JavaScriptParser::ElementListContext>(0);
}


size_t JavaScriptParser::ArrayLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrayLiteral;
}


std::any JavaScriptParser::ArrayLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitArrayLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::arrayLiteral() {
  ArrayLiteralContext *_localctx = _tracker.createInstance<ArrayLiteralContext>(_ctx, getState());
  enterRule(_localctx, 106, JavaScriptParser::RuleArrayLiteral);
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
    setState(706);
    match(JavaScriptParser::LBRACKET);
    setState(708);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::NULL_LITERAL)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::UNDEFINED)
      | (1ULL << JavaScriptParser::LPAREN)
      | (1ULL << JavaScriptParser::LBRACE)
      | (1ULL << JavaScriptParser::LBRACKET)
      | (1ULL << JavaScriptParser::COMMA)
      | (1ULL << JavaScriptParser::ELLIPSIS))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
      | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
      | (1ULL << (JavaScriptParser::PLUS - 74))
      | (1ULL << (JavaScriptParser::MINUS - 74))
      | (1ULL << (JavaScriptParser::TILDE - 74))
      | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
      | (1ULL << (JavaScriptParser::NUMBER - 74))
      | (1ULL << (JavaScriptParser::STRING - 74))
      | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
      setState(707);
      elementList();
    }
    setState(710);
    match(JavaScriptParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementListContext ------------------------------------------------------------------

JavaScriptParser::ElementListContext::ElementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::ArrayElementContext *> JavaScriptParser::ElementListContext::arrayElement() {
  return getRuleContexts<JavaScriptParser::ArrayElementContext>();
}

JavaScriptParser::ArrayElementContext* JavaScriptParser::ElementListContext::arrayElement(size_t i) {
  return getRuleContext<JavaScriptParser::ArrayElementContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ElementListContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ElementListContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ElementListContext::getRuleIndex() const {
  return JavaScriptParser::RuleElementList;
}


std::any JavaScriptParser::ElementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitElementList(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ElementListContext* JavaScriptParser::elementList() {
  ElementListContext *_localctx = _tracker.createInstance<ElementListContext>(_ctx, getState());
  enterRule(_localctx, 108, JavaScriptParser::RuleElementList);
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
    setState(712);
    arrayElement();
    setState(717);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(713);
      match(JavaScriptParser::COMMA);
      setState(714);
      arrayElement();
      setState(719);
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

//----------------- ArrayElementContext ------------------------------------------------------------------

JavaScriptParser::ArrayElementContext::ArrayElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ArrayElementContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrayElementContext::ELLIPSIS() {
  return getToken(JavaScriptParser::ELLIPSIS, 0);
}

tree::TerminalNode* JavaScriptParser::ArrayElementContext::COMMA() {
  return getToken(JavaScriptParser::COMMA, 0);
}


size_t JavaScriptParser::ArrayElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrayElement;
}


std::any JavaScriptParser::ArrayElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitArrayElement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrayElementContext* JavaScriptParser::arrayElement() {
  ArrayElementContext *_localctx = _tracker.createInstance<ArrayElementContext>(_ctx, getState());
  enterRule(_localctx, 110, JavaScriptParser::RuleArrayElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(725);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::NEW:
      case JavaScriptParser::VOID:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::ASYNC:
      case JavaScriptParser::AWAIT:
      case JavaScriptParser::NULL_LITERAL:
      case JavaScriptParser::BOOLEAN:
      case JavaScriptParser::UNDEFINED:
      case JavaScriptParser::LPAREN:
      case JavaScriptParser::LBRACE:
      case JavaScriptParser::LBRACKET:
      case JavaScriptParser::ELLIPSIS:
      case JavaScriptParser::PLUSPLUS:
      case JavaScriptParser::MINUSMINUS:
      case JavaScriptParser::PLUS:
      case JavaScriptParser::MINUS:
      case JavaScriptParser::TILDE:
      case JavaScriptParser::EXCLAMATION:
      case JavaScriptParser::NUMBER:
      case JavaScriptParser::STRING:
      case JavaScriptParser::TEMPLATE_STRING:
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(721);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == JavaScriptParser::ELLIPSIS) {
          setState(720);
          match(JavaScriptParser::ELLIPSIS);
        }
        setState(723);
        singleExpression(0);
        break;
      }

      case JavaScriptParser::COMMA: {
        enterOuterAlt(_localctx, 2);
        setState(724);
        match(JavaScriptParser::COMMA);
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

//----------------- ObjectLiteralContext ------------------------------------------------------------------

JavaScriptParser::ObjectLiteralContext::ObjectLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::LBRACE() {
  return getToken(JavaScriptParser::LBRACE, 0);
}

std::vector<JavaScriptParser::PropertyAssignmentContext *> JavaScriptParser::ObjectLiteralContext::propertyAssignment() {
  return getRuleContexts<JavaScriptParser::PropertyAssignmentContext>();
}

JavaScriptParser::PropertyAssignmentContext* JavaScriptParser::ObjectLiteralContext::propertyAssignment(size_t i) {
  return getRuleContext<JavaScriptParser::PropertyAssignmentContext>(i);
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::RBRACE() {
  return getToken(JavaScriptParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ObjectLiteralContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ObjectLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleObjectLiteral;
}


std::any JavaScriptParser::ObjectLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitObjectLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::objectLiteral() {
  ObjectLiteralContext *_localctx = _tracker.createInstance<ObjectLiteralContext>(_ctx, getState());
  enterRule(_localctx, 112, JavaScriptParser::RuleObjectLiteral);
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
    setState(727);
    match(JavaScriptParser::LBRACE);
    setState(728);
    propertyAssignment();
    setState(733);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(729);
        match(JavaScriptParser::COMMA);
        setState(730);
        propertyAssignment(); 
      }
      setState(735);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    }
    setState(737);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::COMMA) {
      setState(736);
      match(JavaScriptParser::COMMA);
    }
    setState(739);
    match(JavaScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyAssignmentContext ------------------------------------------------------------------

JavaScriptParser::PropertyAssignmentContext::PropertyAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::PropertyAssignmentContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyAssignmentContext::COLON() {
  return getToken(JavaScriptParser::COLON, 0);
}

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::PropertyAssignmentContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PropertyAssignmentContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::PropertyAssignmentContext::LBRACKET() {
  return getToken(JavaScriptParser::LBRACKET, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyAssignmentContext::RBRACKET() {
  return getToken(JavaScriptParser::RBRACKET, 0);
}

JavaScriptParser::MethodDefinitionContext* JavaScriptParser::PropertyAssignmentContext::methodDefinition() {
  return getRuleContext<JavaScriptParser::MethodDefinitionContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyAssignmentContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyAssignmentContext::ELLIPSIS() {
  return getToken(JavaScriptParser::ELLIPSIS, 0);
}


size_t JavaScriptParser::PropertyAssignmentContext::getRuleIndex() const {
  return JavaScriptParser::RulePropertyAssignment;
}


std::any JavaScriptParser::PropertyAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitPropertyAssignment(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::PropertyAssignmentContext* JavaScriptParser::propertyAssignment() {
  PropertyAssignmentContext *_localctx = _tracker.createInstance<PropertyAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 114, JavaScriptParser::RulePropertyAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(755);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(741);
      propertyName();
      setState(742);
      match(JavaScriptParser::COLON);
      setState(743);
      singleExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(745);
      match(JavaScriptParser::LBRACKET);
      setState(746);
      singleExpression(0);
      setState(747);
      match(JavaScriptParser::RBRACKET);
      setState(748);
      match(JavaScriptParser::COLON);
      setState(749);
      singleExpression(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(751);
      methodDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(752);
      match(JavaScriptParser::IDENTIFIER);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(753);
      match(JavaScriptParser::ELLIPSIS);
      setState(754);
      singleExpression(0);
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

//----------------- ArgumentsContext ------------------------------------------------------------------

JavaScriptParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ArgumentsContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::ArgumentsContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::ArgumentListContext* JavaScriptParser::ArgumentsContext::argumentList() {
  return getRuleContext<JavaScriptParser::ArgumentListContext>(0);
}


size_t JavaScriptParser::ArgumentsContext::getRuleIndex() const {
  return JavaScriptParser::RuleArguments;
}


std::any JavaScriptParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArgumentsContext* JavaScriptParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 116, JavaScriptParser::RuleArguments);
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
    setState(757);
    match(JavaScriptParser::LPAREN);
    setState(759);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::NULL_LITERAL)
      | (1ULL << JavaScriptParser::BOOLEAN)
      | (1ULL << JavaScriptParser::UNDEFINED)
      | (1ULL << JavaScriptParser::LPAREN)
      | (1ULL << JavaScriptParser::LBRACE)
      | (1ULL << JavaScriptParser::LBRACKET)
      | (1ULL << JavaScriptParser::ELLIPSIS))) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & ((1ULL << (JavaScriptParser::PLUSPLUS - 74))
      | (1ULL << (JavaScriptParser::MINUSMINUS - 74))
      | (1ULL << (JavaScriptParser::PLUS - 74))
      | (1ULL << (JavaScriptParser::MINUS - 74))
      | (1ULL << (JavaScriptParser::TILDE - 74))
      | (1ULL << (JavaScriptParser::EXCLAMATION - 74))
      | (1ULL << (JavaScriptParser::NUMBER - 74))
      | (1ULL << (JavaScriptParser::STRING - 74))
      | (1ULL << (JavaScriptParser::TEMPLATE_STRING - 74))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 74)))) != 0)) {
      setState(758);
      argumentList();
    }
    setState(761);
    match(JavaScriptParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

JavaScriptParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::ArgumentContext *> JavaScriptParser::ArgumentListContext::argument() {
  return getRuleContexts<JavaScriptParser::ArgumentContext>();
}

JavaScriptParser::ArgumentContext* JavaScriptParser::ArgumentListContext::argument(size_t i) {
  return getRuleContext<JavaScriptParser::ArgumentContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ArgumentListContext::COMMA() {
  return getTokens(JavaScriptParser::COMMA);
}

tree::TerminalNode* JavaScriptParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(JavaScriptParser::COMMA, i);
}


size_t JavaScriptParser::ArgumentListContext::getRuleIndex() const {
  return JavaScriptParser::RuleArgumentList;
}


std::any JavaScriptParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArgumentListContext* JavaScriptParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 118, JavaScriptParser::RuleArgumentList);
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
    setState(763);
    argument();
    setState(768);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::COMMA) {
      setState(764);
      match(JavaScriptParser::COMMA);
      setState(765);
      argument();
      setState(770);
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

//----------------- ArgumentContext ------------------------------------------------------------------

JavaScriptParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ArgumentContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArgumentContext::ELLIPSIS() {
  return getToken(JavaScriptParser::ELLIPSIS, 0);
}


size_t JavaScriptParser::ArgumentContext::getRuleIndex() const {
  return JavaScriptParser::RuleArgument;
}


std::any JavaScriptParser::ArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitArgument(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArgumentContext* JavaScriptParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 120, JavaScriptParser::RuleArgument);
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
    setState(772);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::ELLIPSIS) {
      setState(771);
      match(JavaScriptParser::ELLIPSIS);
    }
    setState(774);
    singleExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnonymousFunctionContext ------------------------------------------------------------------

JavaScriptParser::AnonymousFunctionContext::AnonymousFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionContext::FUNCTION() {
  return getToken(JavaScriptParser::FUNCTION, 0);
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::AnonymousFunctionContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionContext::ASYNC() {
  return getToken(JavaScriptParser::ASYNC, 0);
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionContext::STAR() {
  return getToken(JavaScriptParser::STAR, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::AnonymousFunctionContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::AnonymousFunctionContext::getRuleIndex() const {
  return JavaScriptParser::RuleAnonymousFunction;
}


std::any JavaScriptParser::AnonymousFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitAnonymousFunction(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::AnonymousFunctionContext* JavaScriptParser::anonymousFunction() {
  AnonymousFunctionContext *_localctx = _tracker.createInstance<AnonymousFunctionContext>(_ctx, getState());
  enterRule(_localctx, 122, JavaScriptParser::RuleAnonymousFunction);
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
    setState(777);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::ASYNC) {
      setState(776);
      match(JavaScriptParser::ASYNC);
    }
    setState(779);
    match(JavaScriptParser::FUNCTION);
    setState(781);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::STAR) {
      setState(780);
      match(JavaScriptParser::STAR);
    }
    setState(783);
    match(JavaScriptParser::LPAREN);
    setState(785);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 49) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 49)) & ((1ULL << (JavaScriptParser::LBRACE - 49))
      | (1ULL << (JavaScriptParser::LBRACKET - 49))
      | (1ULL << (JavaScriptParser::ELLIPSIS - 49))
      | (1ULL << (JavaScriptParser::IDENTIFIER - 49)))) != 0)) {
      setState(784);
      formalParameterList();
    }
    setState(787);
    match(JavaScriptParser::RPAREN);
    setState(788);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionContext ------------------------------------------------------------------

JavaScriptParser::ArrowFunctionContext::ArrowFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ArrowFunctionParametersContext* JavaScriptParser::ArrowFunctionContext::arrowFunctionParameters() {
  return getRuleContext<JavaScriptParser::ArrowFunctionParametersContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionContext::ARROW() {
  return getToken(JavaScriptParser::ARROW, 0);
}

JavaScriptParser::ArrowFunctionBodyContext* JavaScriptParser::ArrowFunctionContext::arrowFunctionBody() {
  return getRuleContext<JavaScriptParser::ArrowFunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionContext::ASYNC() {
  return getToken(JavaScriptParser::ASYNC, 0);
}


size_t JavaScriptParser::ArrowFunctionContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrowFunction;
}


std::any JavaScriptParser::ArrowFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitArrowFunction(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrowFunctionContext* JavaScriptParser::arrowFunction() {
  ArrowFunctionContext *_localctx = _tracker.createInstance<ArrowFunctionContext>(_ctx, getState());
  enterRule(_localctx, 124, JavaScriptParser::RuleArrowFunction);
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
    setState(791);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::ASYNC) {
      setState(790);
      match(JavaScriptParser::ASYNC);
    }
    setState(793);
    arrowFunctionParameters();
    setState(794);
    match(JavaScriptParser::ARROW);
    setState(795);
    arrowFunctionBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionParametersContext ------------------------------------------------------------------

JavaScriptParser::ArrowFunctionParametersContext::ArrowFunctionParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionParametersContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionParametersContext::LPAREN() {
  return getToken(JavaScriptParser::LPAREN, 0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionParametersContext::RPAREN() {
  return getToken(JavaScriptParser::RPAREN, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::ArrowFunctionParametersContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::ArrowFunctionParametersContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrowFunctionParameters;
}


std::any JavaScriptParser::ArrowFunctionParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitArrowFunctionParameters(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrowFunctionParametersContext* JavaScriptParser::arrowFunctionParameters() {
  ArrowFunctionParametersContext *_localctx = _tracker.createInstance<ArrowFunctionParametersContext>(_ctx, getState());
  enterRule(_localctx, 126, JavaScriptParser::RuleArrowFunctionParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(803);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(797);
        match(JavaScriptParser::IDENTIFIER);
        break;
      }

      case JavaScriptParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(798);
        match(JavaScriptParser::LPAREN);
        setState(800);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 49) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 49)) & ((1ULL << (JavaScriptParser::LBRACE - 49))
          | (1ULL << (JavaScriptParser::LBRACKET - 49))
          | (1ULL << (JavaScriptParser::ELLIPSIS - 49))
          | (1ULL << (JavaScriptParser::IDENTIFIER - 49)))) != 0)) {
          setState(799);
          formalParameterList();
        }
        setState(802);
        match(JavaScriptParser::RPAREN);
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

//----------------- ArrowFunctionBodyContext ------------------------------------------------------------------

JavaScriptParser::ArrowFunctionBodyContext::ArrowFunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ArrowFunctionBodyContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::BlockContext* JavaScriptParser::ArrowFunctionBodyContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}


size_t JavaScriptParser::ArrowFunctionBodyContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrowFunctionBody;
}


std::any JavaScriptParser::ArrowFunctionBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitArrowFunctionBody(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrowFunctionBodyContext* JavaScriptParser::arrowFunctionBody() {
  ArrowFunctionBodyContext *_localctx = _tracker.createInstance<ArrowFunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 128, JavaScriptParser::RuleArrowFunctionBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(807);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(805);
      singleExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(806);
      block();
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

//----------------- TypeofExpressionContext ------------------------------------------------------------------

JavaScriptParser::TypeofExpressionContext::TypeofExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::TypeofExpressionContext::TYPEOF() {
  return getToken(JavaScriptParser::TYPEOF, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::TypeofExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}


size_t JavaScriptParser::TypeofExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleTypeofExpression;
}


std::any JavaScriptParser::TypeofExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitTypeofExpression(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::TypeofExpressionContext* JavaScriptParser::typeofExpression() {
  TypeofExpressionContext *_localctx = _tracker.createInstance<TypeofExpressionContext>(_ctx, getState());
  enterRule(_localctx, 130, JavaScriptParser::RuleTypeofExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(809);
    match(JavaScriptParser::TYPEOF);
    setState(810);
    singleExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierNameContext ------------------------------------------------------------------

JavaScriptParser::IdentifierNameContext::IdentifierNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IdentifierNameContext::IDENTIFIER() {
  return getToken(JavaScriptParser::IDENTIFIER, 0);
}

JavaScriptParser::ReservedWordContext* JavaScriptParser::IdentifierNameContext::reservedWord() {
  return getRuleContext<JavaScriptParser::ReservedWordContext>(0);
}


size_t JavaScriptParser::IdentifierNameContext::getRuleIndex() const {
  return JavaScriptParser::RuleIdentifierName;
}


std::any JavaScriptParser::IdentifierNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitIdentifierName(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::identifierName() {
  IdentifierNameContext *_localctx = _tracker.createInstance<IdentifierNameContext>(_ctx, getState());
  enterRule(_localctx, 132, JavaScriptParser::RuleIdentifierName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(814);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(812);
        match(JavaScriptParser::IDENTIFIER);
        break;
      }

      case JavaScriptParser::BREAK:
      case JavaScriptParser::DO:
      case JavaScriptParser::INSTANCEOF:
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::CASE:
      case JavaScriptParser::ELSE:
      case JavaScriptParser::NEW:
      case JavaScriptParser::VAR:
      case JavaScriptParser::CATCH:
      case JavaScriptParser::FINALLY:
      case JavaScriptParser::RETURN:
      case JavaScriptParser::VOID:
      case JavaScriptParser::CONTINUE:
      case JavaScriptParser::FOR:
      case JavaScriptParser::SWITCH:
      case JavaScriptParser::WHILE:
      case JavaScriptParser::DEBUGGER:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::WITH:
      case JavaScriptParser::DEFAULT:
      case JavaScriptParser::IF:
      case JavaScriptParser::THROW:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::IN:
      case JavaScriptParser::TRY:
      case JavaScriptParser::CLASS:
      case JavaScriptParser::ENUM:
      case JavaScriptParser::EXTENDS:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::CONST:
      case JavaScriptParser::EXPORT:
      case JavaScriptParser::IMPORT:
      case JavaScriptParser::ASYNC:
      case JavaScriptParser::AWAIT:
      case JavaScriptParser::YIELD:
      case JavaScriptParser::LET:
      case JavaScriptParser::STATIC:
      case JavaScriptParser::FROM:
      case JavaScriptParser::AS:
      case JavaScriptParser::OF:
      case JavaScriptParser::NULL_LITERAL:
      case JavaScriptParser::BOOLEAN: {
        enterOuterAlt(_localctx, 2);
        setState(813);
        reservedWord();
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

//----------------- ReservedWordContext ------------------------------------------------------------------

JavaScriptParser::ReservedWordContext::ReservedWordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::KeywordContext* JavaScriptParser::ReservedWordContext::keyword() {
  return getRuleContext<JavaScriptParser::KeywordContext>(0);
}

tree::TerminalNode* JavaScriptParser::ReservedWordContext::NULL_LITERAL() {
  return getToken(JavaScriptParser::NULL_LITERAL, 0);
}

tree::TerminalNode* JavaScriptParser::ReservedWordContext::BOOLEAN() {
  return getToken(JavaScriptParser::BOOLEAN, 0);
}


size_t JavaScriptParser::ReservedWordContext::getRuleIndex() const {
  return JavaScriptParser::RuleReservedWord;
}


std::any JavaScriptParser::ReservedWordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitReservedWord(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ReservedWordContext* JavaScriptParser::reservedWord() {
  ReservedWordContext *_localctx = _tracker.createInstance<ReservedWordContext>(_ctx, getState());
  enterRule(_localctx, 134, JavaScriptParser::RuleReservedWord);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(819);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::BREAK:
      case JavaScriptParser::DO:
      case JavaScriptParser::INSTANCEOF:
      case JavaScriptParser::TYPEOF:
      case JavaScriptParser::CASE:
      case JavaScriptParser::ELSE:
      case JavaScriptParser::NEW:
      case JavaScriptParser::VAR:
      case JavaScriptParser::CATCH:
      case JavaScriptParser::FINALLY:
      case JavaScriptParser::RETURN:
      case JavaScriptParser::VOID:
      case JavaScriptParser::CONTINUE:
      case JavaScriptParser::FOR:
      case JavaScriptParser::SWITCH:
      case JavaScriptParser::WHILE:
      case JavaScriptParser::DEBUGGER:
      case JavaScriptParser::FUNCTION:
      case JavaScriptParser::THIS:
      case JavaScriptParser::WITH:
      case JavaScriptParser::DEFAULT:
      case JavaScriptParser::IF:
      case JavaScriptParser::THROW:
      case JavaScriptParser::DELETE:
      case JavaScriptParser::IN:
      case JavaScriptParser::TRY:
      case JavaScriptParser::CLASS:
      case JavaScriptParser::ENUM:
      case JavaScriptParser::EXTENDS:
      case JavaScriptParser::SUPER:
      case JavaScriptParser::CONST:
      case JavaScriptParser::EXPORT:
      case JavaScriptParser::IMPORT:
      case JavaScriptParser::ASYNC:
      case JavaScriptParser::AWAIT:
      case JavaScriptParser::YIELD:
      case JavaScriptParser::LET:
      case JavaScriptParser::STATIC:
      case JavaScriptParser::FROM:
      case JavaScriptParser::AS:
      case JavaScriptParser::OF: {
        enterOuterAlt(_localctx, 1);
        setState(816);
        keyword();
        break;
      }

      case JavaScriptParser::NULL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(817);
        match(JavaScriptParser::NULL_LITERAL);
        break;
      }

      case JavaScriptParser::BOOLEAN: {
        enterOuterAlt(_localctx, 3);
        setState(818);
        match(JavaScriptParser::BOOLEAN);
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

//----------------- KeywordContext ------------------------------------------------------------------

JavaScriptParser::KeywordContext::KeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::KeywordContext::BREAK() {
  return getToken(JavaScriptParser::BREAK, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::DO() {
  return getToken(JavaScriptParser::DO, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::INSTANCEOF() {
  return getToken(JavaScriptParser::INSTANCEOF, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::TYPEOF() {
  return getToken(JavaScriptParser::TYPEOF, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::CASE() {
  return getToken(JavaScriptParser::CASE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::ELSE() {
  return getToken(JavaScriptParser::ELSE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::NEW() {
  return getToken(JavaScriptParser::NEW, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::VAR() {
  return getToken(JavaScriptParser::VAR, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::CATCH() {
  return getToken(JavaScriptParser::CATCH, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::FINALLY() {
  return getToken(JavaScriptParser::FINALLY, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::RETURN() {
  return getToken(JavaScriptParser::RETURN, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::VOID() {
  return getToken(JavaScriptParser::VOID, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::CONTINUE() {
  return getToken(JavaScriptParser::CONTINUE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::FOR() {
  return getToken(JavaScriptParser::FOR, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::SWITCH() {
  return getToken(JavaScriptParser::SWITCH, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::WHILE() {
  return getToken(JavaScriptParser::WHILE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::DEBUGGER() {
  return getToken(JavaScriptParser::DEBUGGER, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::FUNCTION() {
  return getToken(JavaScriptParser::FUNCTION, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::THIS() {
  return getToken(JavaScriptParser::THIS, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::WITH() {
  return getToken(JavaScriptParser::WITH, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::DEFAULT() {
  return getToken(JavaScriptParser::DEFAULT, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::IF() {
  return getToken(JavaScriptParser::IF, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::THROW() {
  return getToken(JavaScriptParser::THROW, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::DELETE() {
  return getToken(JavaScriptParser::DELETE, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::IN() {
  return getToken(JavaScriptParser::IN, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::TRY() {
  return getToken(JavaScriptParser::TRY, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::CLASS() {
  return getToken(JavaScriptParser::CLASS, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::ENUM() {
  return getToken(JavaScriptParser::ENUM, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::EXTENDS() {
  return getToken(JavaScriptParser::EXTENDS, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::SUPER() {
  return getToken(JavaScriptParser::SUPER, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::CONST() {
  return getToken(JavaScriptParser::CONST, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::EXPORT() {
  return getToken(JavaScriptParser::EXPORT, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::IMPORT() {
  return getToken(JavaScriptParser::IMPORT, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::ASYNC() {
  return getToken(JavaScriptParser::ASYNC, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::AWAIT() {
  return getToken(JavaScriptParser::AWAIT, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::YIELD() {
  return getToken(JavaScriptParser::YIELD, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::LET() {
  return getToken(JavaScriptParser::LET, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::STATIC() {
  return getToken(JavaScriptParser::STATIC, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::FROM() {
  return getToken(JavaScriptParser::FROM, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::AS() {
  return getToken(JavaScriptParser::AS, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::OF() {
  return getToken(JavaScriptParser::OF, 0);
}


size_t JavaScriptParser::KeywordContext::getRuleIndex() const {
  return JavaScriptParser::RuleKeyword;
}


std::any JavaScriptParser::KeywordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptVisitor*>(visitor))
    return parserVisitor->visitKeyword(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::KeywordContext* JavaScriptParser::keyword() {
  KeywordContext *_localctx = _tracker.createInstance<KeywordContext>(_ctx, getState());
  enterRule(_localctx, 136, JavaScriptParser::RuleKeyword);
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
    setState(821);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::BREAK)
      | (1ULL << JavaScriptParser::DO)
      | (1ULL << JavaScriptParser::INSTANCEOF)
      | (1ULL << JavaScriptParser::TYPEOF)
      | (1ULL << JavaScriptParser::CASE)
      | (1ULL << JavaScriptParser::ELSE)
      | (1ULL << JavaScriptParser::NEW)
      | (1ULL << JavaScriptParser::VAR)
      | (1ULL << JavaScriptParser::CATCH)
      | (1ULL << JavaScriptParser::FINALLY)
      | (1ULL << JavaScriptParser::RETURN)
      | (1ULL << JavaScriptParser::VOID)
      | (1ULL << JavaScriptParser::CONTINUE)
      | (1ULL << JavaScriptParser::FOR)
      | (1ULL << JavaScriptParser::SWITCH)
      | (1ULL << JavaScriptParser::WHILE)
      | (1ULL << JavaScriptParser::DEBUGGER)
      | (1ULL << JavaScriptParser::FUNCTION)
      | (1ULL << JavaScriptParser::THIS)
      | (1ULL << JavaScriptParser::WITH)
      | (1ULL << JavaScriptParser::DEFAULT)
      | (1ULL << JavaScriptParser::IF)
      | (1ULL << JavaScriptParser::THROW)
      | (1ULL << JavaScriptParser::DELETE)
      | (1ULL << JavaScriptParser::IN)
      | (1ULL << JavaScriptParser::TRY)
      | (1ULL << JavaScriptParser::CLASS)
      | (1ULL << JavaScriptParser::ENUM)
      | (1ULL << JavaScriptParser::EXTENDS)
      | (1ULL << JavaScriptParser::SUPER)
      | (1ULL << JavaScriptParser::CONST)
      | (1ULL << JavaScriptParser::EXPORT)
      | (1ULL << JavaScriptParser::IMPORT)
      | (1ULL << JavaScriptParser::ASYNC)
      | (1ULL << JavaScriptParser::AWAIT)
      | (1ULL << JavaScriptParser::YIELD)
      | (1ULL << JavaScriptParser::LET)
      | (1ULL << JavaScriptParser::STATIC)
      | (1ULL << JavaScriptParser::FROM)
      | (1ULL << JavaScriptParser::AS)
      | (1ULL << JavaScriptParser::OF))) != 0))) {
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

bool JavaScriptParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 50: return singleExpressionSempred(antlrcpp::downCast<SingleExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::singleExpressionSempred(SingleExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 25);
    case 1: return precpred(_ctx, 24);
    case 2: return precpred(_ctx, 23);
    case 3: return precpred(_ctx, 22);
    case 4: return precpred(_ctx, 21);
    case 5: return precpred(_ctx, 20);
    case 6: return precpred(_ctx, 19);
    case 7: return precpred(_ctx, 18);
    case 8: return precpred(_ctx, 17);
    case 9: return precpred(_ctx, 16);
    case 10: return precpred(_ctx, 15);
    case 11: return precpred(_ctx, 14);
    case 12: return precpred(_ctx, 13);
    case 13: return precpred(_ctx, 12);
    case 14: return precpred(_ctx, 11);
    case 15: return precpred(_ctx, 10);
    case 16: return precpred(_ctx, 9);
    case 17: return precpred(_ctx, 41);
    case 18: return precpred(_ctx, 40);
    case 19: return precpred(_ctx, 39);
    case 20: return precpred(_ctx, 37);
    case 21: return precpred(_ctx, 36);

  default:
    break;
  }
  return true;
}

void JavaScriptParser::initialize() {
  std::call_once(javascriptParserOnceFlag, javascriptParserInitialize);
}
