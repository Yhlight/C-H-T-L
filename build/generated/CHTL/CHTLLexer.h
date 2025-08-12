
// Generated from /workspace/grammar/CHTL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLLexer : public antlr4::Lexer {
public:
  enum {
    TEXT = 1, STYLE = 2, SCRIPT = 3, TEMPLATE = 4, CUSTOM = 5, ORIGIN = 6, 
    IMPORT = 7, NAMESPACE = 8, CONFIGURATION = 9, NAME = 10, INFO = 11, 
    EXPORT = 12, AT_STYLE = 13, AT_ELEMENT = 14, AT_VAR = 15, AT_HTML = 16, 
    AT_JAVASCRIPT = 17, AT_CHTL = 18, INHERIT = 19, DELETE = 20, INSERT = 21, 
    AFTER = 22, BEFORE = 23, REPLACE = 24, AT = 25, TOP = 26, BOTTOM = 27, 
    FROM = 28, AS = 29, EXCEPT = 30, BOOLEAN = 31, COLON = 32, SEMICOLON = 33, 
    EQUALS = 34, COMMA = 35, DOT = 36, HASH = 37, AMPERSAND = 38, MINUS = 39, 
    LBRACE = 40, RBRACE = 41, LBRACKET = 42, RBRACKET = 43, LPAREN = 44, 
    RPAREN = 45, LINE_COMMENT = 46, BLOCK_COMMENT = 47, GENERATOR_COMMENT = 48, 
    STRING_LITERAL = 49, SINGLE_STRING_LITERAL = 50, IDENTIFIER = 51, NUMBER = 52, 
    UNQUOTED_LITERAL = 53, WS = 54
  };

  explicit CHTLLexer(antlr4::CharStream *input);

  ~CHTLLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

