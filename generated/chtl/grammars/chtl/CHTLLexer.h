
// Generated from grammars/chtl/CHTL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, COMMENT = 2, MULTILINE_COMMENT = 3, GENERATOR_COMMENT = 4, TEMPLATE = 5, 
    CUSTOM = 6, ORIGIN = 7, CONFIGURATION = 8, IMPORT = 9, NAMESPACE = 10, 
    INFO = 11, EXPORT = 12, STYLE = 13, ELEMENT = 14, VAR = 15, HTML = 16, 
    CSS = 17, JAVASCRIPT = 18, CHTL = 19, INHERIT = 20, DELETE = 21, INSERT = 22, 
    AFTER = 23, BEFORE = 24, REPLACE = 25, AT_TOP = 26, AT_BOTTOM = 27, 
    FROM = 28, AS = 29, EXCEPT = 30, TEXT = 31, STYLE_BLOCK = 32, SCRIPT = 33, 
    LBRACE = 34, RBRACE = 35, LBRACKET = 36, RBRACKET = 37, LPAREN = 38, 
    RPAREN = 39, SEMICOLON = 40, COLON = 41, EQUALS = 42, COMMA = 43, DOT = 44, 
    HASH = 45, PERIOD = 46, AMPERSAND = 47, IDENTIFIER = 48, NUMBER = 49, 
    STRING = 50, LITERAL = 51, NAME = 52
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

