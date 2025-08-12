// Generated from /workspace/chtl/grammar/CHTL.g4 by ANTLR 4.13.1
package chtl.parser;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class CHTLParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		AMP=1, KEYWORD_TEXT=2, KEYWORD_STYLE=3, KEYWORD_SCRIPT_KW=4, KEYWORD_TEMPLATE=5, 
		KEYWORD_CUSTOM=6, KEYWORD_ORIGIN=7, KEYWORD_CONFIGURATION=8, KEYWORD_IMPORT=9, 
		KEYWORD_NAMESPACE=10, KEYWORD_HTML=11, KEYWORD_HEAD=12, KEYWORD_BODY=13, 
		KEYWORD_DIV=14, KEYWORD_SPAN=15, KEYWORD_BUTTON=16, KEYWORD_INHERIT=17, 
		KEYWORD_DELETE=18, KEYWORD_INSERT=19, KEYWORD_AFTER=20, KEYWORD_BEFORE=21, 
		KEYWORD_REPLACE=22, KEYWORD_AT=23, TOP_KW=24, BOTTOM_KW=25, KEYWORD_FROM=26, 
		KEYWORD_AS=27, KEYWORD_EXCEPT=28, AT_STYLE=29, AT_ELEMENT=30, AT_VAR=31, 
		AT_HTML=32, AT_JS=33, AT_CHTL=34, FROM=35, AS=36, LBRACE=37, RBRACE=38, 
		LBRACK=39, RBRACK=40, LPAREN=41, RPAREN=42, COLON=43, EQUAL=44, SEMI=45, 
		COMMA=46, DOT=47, HASH=48, NUMBER=49, IDENT=50, STRING=51, LINE_COMMENT=52, 
		BLOCK_COMMENT=53, SPECIAL_COMMENT=54, WS=55;
	public static final int
		RULE_program = 0, RULE_statement = 1, RULE_elementNode = 2, RULE_elementName = 3, 
		RULE_block = 4, RULE_blockItem = 5, RULE_textBlock = 6, RULE_blockText = 7, 
		RULE_textLine = 8, RULE_textPiece = 9, RULE_styleBlock = 10, RULE_blockStyle = 11, 
		RULE_styleItem = 12, RULE_styleSelector = 13, RULE_selectorHead = 14, 
		RULE_scriptBlock = 15, RULE_blockScript = 16, RULE_scriptLine = 17, RULE_scriptPiece = 18, 
		RULE_attribute = 19, RULE_value = 20, RULE_valuePiece = 21, RULE_templateUsage = 22, 
		RULE_templateDecl = 23, RULE_customDecl = 24, RULE_originDecl = 25, RULE_configurationDecl = 26, 
		RULE_importStmt = 27, RULE_importTarget = 28, RULE_importPath = 29, RULE_namespaceDecl = 30, 
		RULE_inheritStmt = 31, RULE_deleteStmt = 32, RULE_identList = 33, RULE_insertStmt = 34, 
		RULE_selector = 35, RULE_exceptStmt = 36, RULE_exceptTargetList = 37, 
		RULE_exceptTarget = 38, RULE_atType = 39;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "statement", "elementNode", "elementName", "block", "blockItem", 
			"textBlock", "blockText", "textLine", "textPiece", "styleBlock", "blockStyle", 
			"styleItem", "styleSelector", "selectorHead", "scriptBlock", "blockScript", 
			"scriptLine", "scriptPiece", "attribute", "value", "valuePiece", "templateUsage", 
			"templateDecl", "customDecl", "originDecl", "configurationDecl", "importStmt", 
			"importTarget", "importPath", "namespaceDecl", "inheritStmt", "deleteStmt", 
			"identList", "insertStmt", "selector", "exceptStmt", "exceptTargetList", 
			"exceptTarget", "atType"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'&'", "'text'", "'style'", "'script'", "'[Template]'", "'[Custom]'", 
			"'[Origin]'", "'[Configuration]'", "'[Import]'", "'[Namespace]'", "'html'", 
			"'head'", "'body'", "'div'", "'span'", "'button'", "'inherit'", "'delete'", 
			"'insert'", "'after'", "'before'", "'replace'", "'at'", "'top'", "'bottom'", 
			"'from'", "'as'", "'except'", null, "'@Element'", "'@Var'", "'@Html'", 
			"'@JavaScript'", "'@Chtl'", null, null, "'{'", "'}'", "'['", "']'", "'('", 
			"')'", "':'", "'='", "';'", "','", "'.'", "'#'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "AMP", "KEYWORD_TEXT", "KEYWORD_STYLE", "KEYWORD_SCRIPT_KW", "KEYWORD_TEMPLATE", 
			"KEYWORD_CUSTOM", "KEYWORD_ORIGIN", "KEYWORD_CONFIGURATION", "KEYWORD_IMPORT", 
			"KEYWORD_NAMESPACE", "KEYWORD_HTML", "KEYWORD_HEAD", "KEYWORD_BODY", 
			"KEYWORD_DIV", "KEYWORD_SPAN", "KEYWORD_BUTTON", "KEYWORD_INHERIT", "KEYWORD_DELETE", 
			"KEYWORD_INSERT", "KEYWORD_AFTER", "KEYWORD_BEFORE", "KEYWORD_REPLACE", 
			"KEYWORD_AT", "TOP_KW", "BOTTOM_KW", "KEYWORD_FROM", "KEYWORD_AS", "KEYWORD_EXCEPT", 
			"AT_STYLE", "AT_ELEMENT", "AT_VAR", "AT_HTML", "AT_JS", "AT_CHTL", "FROM", 
			"AS", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "LPAREN", "RPAREN", "COLON", 
			"EQUAL", "SEMI", "COMMA", "DOT", "HASH", "NUMBER", "IDENT", "STRING", 
			"LINE_COMMENT", "BLOCK_COMMENT", "SPECIAL_COMMENT", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "CHTL.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CHTLParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(CHTLParser.EOF, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitProgram(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(83);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1161084279062524L) != 0)) {
				{
				{
				setState(80);
				statement();
				}
				}
				setState(85);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(86);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends ParserRuleContext {
		public ElementNodeContext elementNode() {
			return getRuleContext(ElementNodeContext.class,0);
		}
		public TextBlockContext textBlock() {
			return getRuleContext(TextBlockContext.class,0);
		}
		public StyleBlockContext styleBlock() {
			return getRuleContext(StyleBlockContext.class,0);
		}
		public ScriptBlockContext scriptBlock() {
			return getRuleContext(ScriptBlockContext.class,0);
		}
		public TemplateDeclContext templateDecl() {
			return getRuleContext(TemplateDeclContext.class,0);
		}
		public CustomDeclContext customDecl() {
			return getRuleContext(CustomDeclContext.class,0);
		}
		public OriginDeclContext originDecl() {
			return getRuleContext(OriginDeclContext.class,0);
		}
		public ConfigurationDeclContext configurationDecl() {
			return getRuleContext(ConfigurationDeclContext.class,0);
		}
		public ImportStmtContext importStmt() {
			return getRuleContext(ImportStmtContext.class,0);
		}
		public NamespaceDeclContext namespaceDecl() {
			return getRuleContext(NamespaceDeclContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_statement);
		try {
			setState(99);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(88);
				elementNode();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(89);
				textBlock();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(90);
				styleBlock();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(91);
				scriptBlock();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(92);
				templateDecl();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(93);
				customDecl();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(94);
				originDecl();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(95);
				configurationDecl();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(96);
				importStmt();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(97);
				namespaceDecl();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(98);
				match(SEMI);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ElementNodeContext extends ParserRuleContext {
		public ElementNameContext elementName() {
			return getRuleContext(ElementNameContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public ElementNodeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementNode; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitElementNode(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ElementNodeContext elementNode() throws RecognitionException {
		ElementNodeContext _localctx = new ElementNodeContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_elementNode);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(101);
			elementName();
			setState(102);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ElementNameContext extends ParserRuleContext {
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode KEYWORD_HTML() { return getToken(CHTLParser.KEYWORD_HTML, 0); }
		public TerminalNode KEYWORD_HEAD() { return getToken(CHTLParser.KEYWORD_HEAD, 0); }
		public TerminalNode KEYWORD_BODY() { return getToken(CHTLParser.KEYWORD_BODY, 0); }
		public TerminalNode KEYWORD_SPAN() { return getToken(CHTLParser.KEYWORD_SPAN, 0); }
		public TerminalNode KEYWORD_DIV() { return getToken(CHTLParser.KEYWORD_DIV, 0); }
		public TerminalNode KEYWORD_BUTTON() { return getToken(CHTLParser.KEYWORD_BUTTON, 0); }
		public TerminalNode KEYWORD_SCRIPT_KW() { return getToken(CHTLParser.KEYWORD_SCRIPT_KW, 0); }
		public ElementNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementName; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitElementName(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ElementNameContext elementName() throws RecognitionException {
		ElementNameContext _localctx = new ElementNameContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_elementName);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(104);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 1125899906971664L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(CHTLParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(CHTLParser.RBRACE, 0); }
		public List<BlockItemContext> blockItem() {
			return getRuleContexts(BlockItemContext.class);
		}
		public BlockItemContext blockItem(int i) {
			return getRuleContext(BlockItemContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitBlock(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(106);
			match(LBRACE);
			setState(110);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1161101191411740L) != 0)) {
				{
				{
				setState(107);
				blockItem();
				}
				}
				setState(112);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(113);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockItemContext extends ParserRuleContext {
		public AttributeContext attribute() {
			return getRuleContext(AttributeContext.class,0);
		}
		public ElementNodeContext elementNode() {
			return getRuleContext(ElementNodeContext.class,0);
		}
		public TextBlockContext textBlock() {
			return getRuleContext(TextBlockContext.class,0);
		}
		public StyleBlockContext styleBlock() {
			return getRuleContext(StyleBlockContext.class,0);
		}
		public ScriptBlockContext scriptBlock() {
			return getRuleContext(ScriptBlockContext.class,0);
		}
		public TemplateUsageContext templateUsage() {
			return getRuleContext(TemplateUsageContext.class,0);
		}
		public DeleteStmtContext deleteStmt() {
			return getRuleContext(DeleteStmtContext.class,0);
		}
		public InheritStmtContext inheritStmt() {
			return getRuleContext(InheritStmtContext.class,0);
		}
		public InsertStmtContext insertStmt() {
			return getRuleContext(InsertStmtContext.class,0);
		}
		public ExceptStmtContext exceptStmt() {
			return getRuleContext(ExceptStmtContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public BlockItemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_blockItem; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitBlockItem(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BlockItemContext blockItem() throws RecognitionException {
		BlockItemContext _localctx = new BlockItemContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_blockItem);
		try {
			setState(126);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(115);
				attribute();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(116);
				elementNode();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(117);
				textBlock();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(118);
				styleBlock();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(119);
				scriptBlock();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(120);
				templateUsage();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(121);
				deleteStmt();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(122);
				inheritStmt();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(123);
				insertStmt();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(124);
				exceptStmt();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(125);
				match(SEMI);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TextBlockContext extends ParserRuleContext {
		public TerminalNode KEYWORD_TEXT() { return getToken(CHTLParser.KEYWORD_TEXT, 0); }
		public BlockTextContext blockText() {
			return getRuleContext(BlockTextContext.class,0);
		}
		public TextBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_textBlock; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitTextBlock(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TextBlockContext textBlock() throws RecognitionException {
		TextBlockContext _localctx = new TextBlockContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_textBlock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(128);
			match(KEYWORD_TEXT);
			setState(129);
			blockText();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockTextContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(CHTLParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(CHTLParser.RBRACE, 0); }
		public List<TextLineContext> textLine() {
			return getRuleContexts(TextLineContext.class);
		}
		public TextLineContext textLine(int i) {
			return getRuleContext(TextLineContext.class,i);
		}
		public BlockTextContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_blockText; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitBlockText(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BlockTextContext blockText() throws RecognitionException {
		BlockTextContext _localctx = new BlockTextContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_blockText);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(131);
			match(LBRACE);
			setState(135);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4466216232026112L) != 0)) {
				{
				{
				setState(132);
				textLine();
				}
				}
				setState(137);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(138);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TextLineContext extends ParserRuleContext {
		public List<TextPieceContext> textPiece() {
			return getRuleContexts(TextPieceContext.class);
		}
		public TextPieceContext textPiece(int i) {
			return getRuleContext(TextPieceContext.class,i);
		}
		public TextLineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_textLine; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitTextLine(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TextLineContext textLine() throws RecognitionException {
		TextLineContext _localctx = new TextLineContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_textLine);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(141); 
			_errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					setState(140);
					textPiece();
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(143); 
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,5,_ctx);
			} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TextPieceContext extends ParserRuleContext {
		public TerminalNode STRING() { return getToken(CHTLParser.STRING, 0); }
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode NUMBER() { return getToken(CHTLParser.NUMBER, 0); }
		public TerminalNode DOT() { return getToken(CHTLParser.DOT, 0); }
		public TerminalNode HASH() { return getToken(CHTLParser.HASH, 0); }
		public TerminalNode COMMA() { return getToken(CHTLParser.COMMA, 0); }
		public TerminalNode LPAREN() { return getToken(CHTLParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(CHTLParser.RPAREN, 0); }
		public TerminalNode COLON() { return getToken(CHTLParser.COLON, 0); }
		public TerminalNode EQUAL() { return getToken(CHTLParser.EQUAL, 0); }
		public TextPieceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_textPiece; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitTextPiece(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TextPieceContext textPiece() throws RecognitionException {
		TextPieceContext _localctx = new TextPieceContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_textPiece);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(145);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4466216232026112L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StyleBlockContext extends ParserRuleContext {
		public TerminalNode KEYWORD_STYLE() { return getToken(CHTLParser.KEYWORD_STYLE, 0); }
		public BlockStyleContext blockStyle() {
			return getRuleContext(BlockStyleContext.class,0);
		}
		public StyleBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_styleBlock; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitStyleBlock(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StyleBlockContext styleBlock() throws RecognitionException {
		StyleBlockContext _localctx = new StyleBlockContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_styleBlock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(147);
			match(KEYWORD_STYLE);
			setState(148);
			blockStyle();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockStyleContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(CHTLParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(CHTLParser.RBRACE, 0); }
		public List<StyleItemContext> styleItem() {
			return getRuleContexts(StyleItemContext.class);
		}
		public StyleItemContext styleItem(int i) {
			return getRuleContext(StyleItemContext.class,i);
		}
		public BlockStyleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_blockStyle; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitBlockStyle(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BlockStyleContext blockStyle() throws RecognitionException {
		BlockStyleContext _localctx = new BlockStyleContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_blockStyle);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(150);
			match(LBRACE);
			setState(154);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1592109480017922L) != 0)) {
				{
				{
				setState(151);
				styleItem();
				}
				}
				setState(156);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(157);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StyleItemContext extends ParserRuleContext {
		public AttributeContext attribute() {
			return getRuleContext(AttributeContext.class,0);
		}
		public TemplateUsageContext templateUsage() {
			return getRuleContext(TemplateUsageContext.class,0);
		}
		public StyleSelectorContext styleSelector() {
			return getRuleContext(StyleSelectorContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public StyleItemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_styleItem; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitStyleItem(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StyleItemContext styleItem() throws RecognitionException {
		StyleItemContext _localctx = new StyleItemContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_styleItem);
		try {
			setState(163);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(159);
				attribute();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(160);
				templateUsage();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(161);
				styleSelector();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(162);
				match(SEMI);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StyleSelectorContext extends ParserRuleContext {
		public SelectorHeadContext selectorHead() {
			return getRuleContext(SelectorHeadContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public StyleSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_styleSelector; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitStyleSelector(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StyleSelectorContext styleSelector() throws RecognitionException {
		StyleSelectorContext _localctx = new StyleSelectorContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_styleSelector);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(165);
			selectorHead();
			setState(166);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SelectorHeadContext extends ParserRuleContext {
		public List<TerminalNode> DOT() { return getTokens(CHTLParser.DOT); }
		public TerminalNode DOT(int i) {
			return getToken(CHTLParser.DOT, i);
		}
		public List<TerminalNode> HASH() { return getTokens(CHTLParser.HASH); }
		public TerminalNode HASH(int i) {
			return getToken(CHTLParser.HASH, i);
		}
		public List<TerminalNode> AMP() { return getTokens(CHTLParser.AMP); }
		public TerminalNode AMP(int i) {
			return getToken(CHTLParser.AMP, i);
		}
		public List<TerminalNode> COLON() { return getTokens(CHTLParser.COLON); }
		public TerminalNode COLON(int i) {
			return getToken(CHTLParser.COLON, i);
		}
		public List<TerminalNode> IDENT() { return getTokens(CHTLParser.IDENT); }
		public TerminalNode IDENT(int i) {
			return getToken(CHTLParser.IDENT, i);
		}
		public SelectorHeadContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_selectorHead; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitSelectorHead(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SelectorHeadContext selectorHead() throws RecognitionException {
		SelectorHeadContext _localctx = new SelectorHeadContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_selectorHead);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(169); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(168);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 1556908464930818L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				}
				setState(171); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & 1556908464930818L) != 0) );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ScriptBlockContext extends ParserRuleContext {
		public TerminalNode KEYWORD_SCRIPT_KW() { return getToken(CHTLParser.KEYWORD_SCRIPT_KW, 0); }
		public BlockScriptContext blockScript() {
			return getRuleContext(BlockScriptContext.class,0);
		}
		public ScriptBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_scriptBlock; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitScriptBlock(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ScriptBlockContext scriptBlock() throws RecognitionException {
		ScriptBlockContext _localctx = new ScriptBlockContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_scriptBlock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(173);
			match(KEYWORD_SCRIPT_KW);
			setState(174);
			blockScript();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockScriptContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(CHTLParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(CHTLParser.RBRACE, 0); }
		public List<ScriptLineContext> scriptLine() {
			return getRuleContexts(ScriptLineContext.class);
		}
		public ScriptLineContext scriptLine(int i) {
			return getRuleContext(ScriptLineContext.class,i);
		}
		public BlockScriptContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_blockScript; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitBlockScript(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BlockScriptContext blockScript() throws RecognitionException {
		BlockScriptContext _localctx = new BlockScriptContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_blockScript);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(176);
			match(LBRACE);
			setState(180);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4466216232026112L) != 0)) {
				{
				{
				setState(177);
				scriptLine();
				}
				}
				setState(182);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(183);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ScriptLineContext extends ParserRuleContext {
		public List<ScriptPieceContext> scriptPiece() {
			return getRuleContexts(ScriptPieceContext.class);
		}
		public ScriptPieceContext scriptPiece(int i) {
			return getRuleContext(ScriptPieceContext.class,i);
		}
		public ScriptLineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_scriptLine; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitScriptLine(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ScriptLineContext scriptLine() throws RecognitionException {
		ScriptLineContext _localctx = new ScriptLineContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_scriptLine);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(186); 
			_errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					setState(185);
					scriptPiece();
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(188); 
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ScriptPieceContext extends ParserRuleContext {
		public TerminalNode STRING() { return getToken(CHTLParser.STRING, 0); }
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode NUMBER() { return getToken(CHTLParser.NUMBER, 0); }
		public TerminalNode DOT() { return getToken(CHTLParser.DOT, 0); }
		public TerminalNode HASH() { return getToken(CHTLParser.HASH, 0); }
		public TerminalNode COMMA() { return getToken(CHTLParser.COMMA, 0); }
		public TerminalNode LPAREN() { return getToken(CHTLParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(CHTLParser.RPAREN, 0); }
		public TerminalNode COLON() { return getToken(CHTLParser.COLON, 0); }
		public TerminalNode EQUAL() { return getToken(CHTLParser.EQUAL, 0); }
		public ScriptPieceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_scriptPiece; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitScriptPiece(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ScriptPieceContext scriptPiece() throws RecognitionException {
		ScriptPieceContext _localctx = new ScriptPieceContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_scriptPiece);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(190);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4466216232026112L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AttributeContext extends ParserRuleContext {
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public TerminalNode COLON() { return getToken(CHTLParser.COLON, 0); }
		public TerminalNode EQUAL() { return getToken(CHTLParser.EQUAL, 0); }
		public AttributeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attribute; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitAttribute(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AttributeContext attribute() throws RecognitionException {
		AttributeContext _localctx = new AttributeContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_attribute);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(192);
			match(IDENT);
			setState(193);
			_la = _input.LA(1);
			if ( !(_la==COLON || _la==EQUAL) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(194);
			value();
			setState(195);
			match(SEMI);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ValueContext extends ParserRuleContext {
		public List<ValuePieceContext> valuePiece() {
			return getRuleContexts(ValuePieceContext.class);
		}
		public ValuePieceContext valuePiece(int i) {
			return getRuleContext(ValuePieceContext.class,i);
		}
		public ValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitValue(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ValueContext value() throws RecognitionException {
		ValueContext _localctx = new ValueContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(198); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(197);
				valuePiece();
				}
				}
				setState(200); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & 4439827952959488L) != 0) );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ValuePieceContext extends ParserRuleContext {
		public TerminalNode STRING() { return getToken(CHTLParser.STRING, 0); }
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode NUMBER() { return getToken(CHTLParser.NUMBER, 0); }
		public TerminalNode DOT() { return getToken(CHTLParser.DOT, 0); }
		public TerminalNode HASH() { return getToken(CHTLParser.HASH, 0); }
		public TerminalNode COMMA() { return getToken(CHTLParser.COMMA, 0); }
		public TerminalNode LPAREN() { return getToken(CHTLParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(CHTLParser.RPAREN, 0); }
		public ValuePieceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_valuePiece; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitValuePiece(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ValuePieceContext valuePiece() throws RecognitionException {
		ValuePieceContext _localctx = new ValuePieceContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_valuePiece);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(202);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4439827952959488L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TemplateUsageContext extends ParserRuleContext {
		public AtTypeContext atType() {
			return getRuleContext(AtTypeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public TemplateUsageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateUsage; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitTemplateUsage(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TemplateUsageContext templateUsage() throws RecognitionException {
		TemplateUsageContext _localctx = new TemplateUsageContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_templateUsage);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(204);
			atType();
			setState(205);
			match(IDENT);
			setState(206);
			match(SEMI);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TemplateDeclContext extends ParserRuleContext {
		public TerminalNode KEYWORD_TEMPLATE() { return getToken(CHTLParser.KEYWORD_TEMPLATE, 0); }
		public AtTypeContext atType() {
			return getRuleContext(AtTypeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TemplateDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateDecl; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitTemplateDecl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TemplateDeclContext templateDecl() throws RecognitionException {
		TemplateDeclContext _localctx = new TemplateDeclContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_templateDecl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(208);
			match(KEYWORD_TEMPLATE);
			setState(209);
			atType();
			setState(210);
			match(IDENT);
			setState(211);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CustomDeclContext extends ParserRuleContext {
		public TerminalNode KEYWORD_CUSTOM() { return getToken(CHTLParser.KEYWORD_CUSTOM, 0); }
		public AtTypeContext atType() {
			return getRuleContext(AtTypeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public CustomDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_customDecl; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitCustomDecl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CustomDeclContext customDecl() throws RecognitionException {
		CustomDeclContext _localctx = new CustomDeclContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_customDecl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(213);
			match(KEYWORD_CUSTOM);
			setState(214);
			atType();
			setState(215);
			match(IDENT);
			setState(216);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class OriginDeclContext extends ParserRuleContext {
		public TerminalNode KEYWORD_ORIGIN() { return getToken(CHTLParser.KEYWORD_ORIGIN, 0); }
		public AtTypeContext atType() {
			return getRuleContext(AtTypeContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public OriginDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_originDecl; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitOriginDecl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final OriginDeclContext originDecl() throws RecognitionException {
		OriginDeclContext _localctx = new OriginDeclContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_originDecl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(218);
			match(KEYWORD_ORIGIN);
			setState(219);
			atType();
			setState(221);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENT) {
				{
				setState(220);
				match(IDENT);
				}
			}

			setState(223);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConfigurationDeclContext extends ParserRuleContext {
		public TerminalNode KEYWORD_CONFIGURATION() { return getToken(CHTLParser.KEYWORD_CONFIGURATION, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public ConfigurationDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_configurationDecl; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitConfigurationDecl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ConfigurationDeclContext configurationDecl() throws RecognitionException {
		ConfigurationDeclContext _localctx = new ConfigurationDeclContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_configurationDecl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(225);
			match(KEYWORD_CONFIGURATION);
			setState(226);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ImportStmtContext extends ParserRuleContext {
		public TerminalNode KEYWORD_IMPORT() { return getToken(CHTLParser.KEYWORD_IMPORT, 0); }
		public ImportTargetContext importTarget() {
			return getRuleContext(ImportTargetContext.class,0);
		}
		public TerminalNode FROM() { return getToken(CHTLParser.FROM, 0); }
		public ImportPathContext importPath() {
			return getRuleContext(ImportPathContext.class,0);
		}
		public TerminalNode AS() { return getToken(CHTLParser.AS, 0); }
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public ImportStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_importStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitImportStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ImportStmtContext importStmt() throws RecognitionException {
		ImportStmtContext _localctx = new ImportStmtContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_importStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(228);
			match(KEYWORD_IMPORT);
			setState(229);
			importTarget();
			setState(230);
			match(FROM);
			setState(231);
			importPath();
			setState(234);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==AS) {
				{
				setState(232);
				match(AS);
				setState(233);
				match(IDENT);
				}
			}

			setState(237);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
			case 1:
				{
				setState(236);
				match(SEMI);
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ImportTargetContext extends ParserRuleContext {
		public AtTypeContext atType() {
			return getRuleContext(AtTypeContext.class,0);
		}
		public TerminalNode AT_CHTL() { return getToken(CHTLParser.AT_CHTL, 0); }
		public TerminalNode KEYWORD_CUSTOM() { return getToken(CHTLParser.KEYWORD_CUSTOM, 0); }
		public TerminalNode KEYWORD_TEMPLATE() { return getToken(CHTLParser.KEYWORD_TEMPLATE, 0); }
		public ImportTargetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_importTarget; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitImportTarget(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ImportTargetContext importTarget() throws RecognitionException {
		ImportTargetContext _localctx = new ImportTargetContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_importTarget);
		try {
			setState(245);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case AT_STYLE:
			case AT_ELEMENT:
			case AT_VAR:
			case AT_HTML:
			case AT_JS:
				enterOuterAlt(_localctx, 1);
				{
				setState(239);
				atType();
				}
				break;
			case AT_CHTL:
				enterOuterAlt(_localctx, 2);
				{
				setState(240);
				match(AT_CHTL);
				}
				break;
			case KEYWORD_CUSTOM:
				enterOuterAlt(_localctx, 3);
				{
				setState(241);
				match(KEYWORD_CUSTOM);
				setState(242);
				atType();
				}
				break;
			case KEYWORD_TEMPLATE:
				enterOuterAlt(_localctx, 4);
				{
				setState(243);
				match(KEYWORD_TEMPLATE);
				setState(244);
				atType();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ImportPathContext extends ParserRuleContext {
		public TerminalNode STRING() { return getToken(CHTLParser.STRING, 0); }
		public List<TerminalNode> IDENT() { return getTokens(CHTLParser.IDENT); }
		public TerminalNode IDENT(int i) {
			return getToken(CHTLParser.IDENT, i);
		}
		public List<TerminalNode> DOT() { return getTokens(CHTLParser.DOT); }
		public TerminalNode DOT(int i) {
			return getToken(CHTLParser.DOT, i);
		}
		public ImportPathContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_importPath; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitImportPath(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ImportPathContext importPath() throws RecognitionException {
		ImportPathContext _localctx = new ImportPathContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_importPath);
		int _la;
		try {
			setState(256);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case STRING:
				enterOuterAlt(_localctx, 1);
				{
				setState(247);
				match(STRING);
				}
				break;
			case IDENT:
				enterOuterAlt(_localctx, 2);
				{
				setState(248);
				match(IDENT);
				setState(253);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==DOT) {
					{
					{
					setState(249);
					match(DOT);
					setState(250);
					match(IDENT);
					}
					}
					setState(255);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class NamespaceDeclContext extends ParserRuleContext {
		public TerminalNode KEYWORD_NAMESPACE() { return getToken(CHTLParser.KEYWORD_NAMESPACE, 0); }
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public NamespaceDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespaceDecl; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitNamespaceDecl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final NamespaceDeclContext namespaceDecl() throws RecognitionException {
		NamespaceDeclContext _localctx = new NamespaceDeclContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_namespaceDecl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(258);
			match(KEYWORD_NAMESPACE);
			setState(259);
			match(IDENT);
			setState(261);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LBRACE) {
				{
				setState(260);
				block();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class InheritStmtContext extends ParserRuleContext {
		public TerminalNode KEYWORD_INHERIT() { return getToken(CHTLParser.KEYWORD_INHERIT, 0); }
		public AtTypeContext atType() {
			return getRuleContext(AtTypeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public InheritStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inheritStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitInheritStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final InheritStmtContext inheritStmt() throws RecognitionException {
		InheritStmtContext _localctx = new InheritStmtContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_inheritStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(263);
			match(KEYWORD_INHERIT);
			setState(264);
			atType();
			setState(265);
			match(IDENT);
			setState(266);
			match(SEMI);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DeleteStmtContext extends ParserRuleContext {
		public TerminalNode KEYWORD_DELETE() { return getToken(CHTLParser.KEYWORD_DELETE, 0); }
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public AtTypeContext atType() {
			return getRuleContext(AtTypeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public IdentListContext identList() {
			return getRuleContext(IdentListContext.class,0);
		}
		public DeleteStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_deleteStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitDeleteStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DeleteStmtContext deleteStmt() throws RecognitionException {
		DeleteStmtContext _localctx = new DeleteStmtContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_deleteStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(268);
			match(KEYWORD_DELETE);
			setState(273);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case AT_STYLE:
			case AT_ELEMENT:
			case AT_VAR:
			case AT_HTML:
			case AT_JS:
				{
				setState(269);
				atType();
				setState(270);
				match(IDENT);
				}
				break;
			case IDENT:
				{
				setState(272);
				identList();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(275);
			match(SEMI);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IdentListContext extends ParserRuleContext {
		public List<TerminalNode> IDENT() { return getTokens(CHTLParser.IDENT); }
		public TerminalNode IDENT(int i) {
			return getToken(CHTLParser.IDENT, i);
		}
		public List<TerminalNode> COMMA() { return getTokens(CHTLParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(CHTLParser.COMMA, i);
		}
		public IdentListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitIdentList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IdentListContext identList() throws RecognitionException {
		IdentListContext _localctx = new IdentListContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_identList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(277);
			match(IDENT);
			setState(282);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(278);
				match(COMMA);
				setState(279);
				match(IDENT);
				}
				}
				setState(284);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class InsertStmtContext extends ParserRuleContext {
		public TerminalNode KEYWORD_INSERT() { return getToken(CHTLParser.KEYWORD_INSERT, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode KEYWORD_AFTER() { return getToken(CHTLParser.KEYWORD_AFTER, 0); }
		public TerminalNode KEYWORD_BEFORE() { return getToken(CHTLParser.KEYWORD_BEFORE, 0); }
		public TerminalNode KEYWORD_REPLACE() { return getToken(CHTLParser.KEYWORD_REPLACE, 0); }
		public TerminalNode KEYWORD_AT() { return getToken(CHTLParser.KEYWORD_AT, 0); }
		public TerminalNode TOP_KW() { return getToken(CHTLParser.TOP_KW, 0); }
		public TerminalNode BOTTOM_KW() { return getToken(CHTLParser.BOTTOM_KW, 0); }
		public SelectorContext selector() {
			return getRuleContext(SelectorContext.class,0);
		}
		public InsertStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_insertStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitInsertStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final InsertStmtContext insertStmt() throws RecognitionException {
		InsertStmtContext _localctx = new InsertStmtContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_insertStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(285);
			match(KEYWORD_INSERT);
			setState(293);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				{
				setState(286);
				match(KEYWORD_AFTER);
				}
				break;
			case 2:
				{
				setState(287);
				match(KEYWORD_BEFORE);
				}
				break;
			case 3:
				{
				setState(288);
				match(KEYWORD_REPLACE);
				}
				break;
			case 4:
				{
				setState(289);
				match(KEYWORD_AT);
				setState(290);
				match(TOP_KW);
				}
				break;
			case 5:
				{
				setState(291);
				match(KEYWORD_AT);
				setState(292);
				match(BOTTOM_KW);
				}
				break;
			}
			setState(296);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENT) {
				{
				setState(295);
				selector();
				}
			}

			setState(298);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SelectorContext extends ParserRuleContext {
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode LBRACK() { return getToken(CHTLParser.LBRACK, 0); }
		public TerminalNode NUMBER() { return getToken(CHTLParser.NUMBER, 0); }
		public TerminalNode RBRACK() { return getToken(CHTLParser.RBRACK, 0); }
		public SelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_selector; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitSelector(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SelectorContext selector() throws RecognitionException {
		SelectorContext _localctx = new SelectorContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_selector);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(300);
			match(IDENT);
			setState(304);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LBRACK) {
				{
				setState(301);
				match(LBRACK);
				setState(302);
				match(NUMBER);
				setState(303);
				match(RBRACK);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExceptStmtContext extends ParserRuleContext {
		public TerminalNode KEYWORD_EXCEPT() { return getToken(CHTLParser.KEYWORD_EXCEPT, 0); }
		public ExceptTargetListContext exceptTargetList() {
			return getRuleContext(ExceptTargetListContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(CHTLParser.SEMI, 0); }
		public ExceptStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exceptStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitExceptStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExceptStmtContext exceptStmt() throws RecognitionException {
		ExceptStmtContext _localctx = new ExceptStmtContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_exceptStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(306);
			match(KEYWORD_EXCEPT);
			setState(307);
			exceptTargetList();
			setState(308);
			match(SEMI);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExceptTargetListContext extends ParserRuleContext {
		public List<ExceptTargetContext> exceptTarget() {
			return getRuleContexts(ExceptTargetContext.class);
		}
		public ExceptTargetContext exceptTarget(int i) {
			return getRuleContext(ExceptTargetContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(CHTLParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(CHTLParser.COMMA, i);
		}
		public ExceptTargetListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exceptTargetList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitExceptTargetList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExceptTargetListContext exceptTargetList() throws RecognitionException {
		ExceptTargetListContext _localctx = new ExceptTargetListContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_exceptTargetList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(310);
			exceptTarget();
			setState(315);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(311);
				match(COMMA);
				setState(312);
				exceptTarget();
				}
				}
				setState(317);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExceptTargetContext extends ParserRuleContext {
		public TerminalNode IDENT() { return getToken(CHTLParser.IDENT, 0); }
		public TerminalNode KEYWORD_CUSTOM() { return getToken(CHTLParser.KEYWORD_CUSTOM, 0); }
		public TerminalNode KEYWORD_TEMPLATE() { return getToken(CHTLParser.KEYWORD_TEMPLATE, 0); }
		public AtTypeContext atType() {
			return getRuleContext(AtTypeContext.class,0);
		}
		public TerminalNode AT_CHTL() { return getToken(CHTLParser.AT_CHTL, 0); }
		public ExceptTargetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exceptTarget; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitExceptTarget(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExceptTargetContext exceptTarget() throws RecognitionException {
		ExceptTargetContext _localctx = new ExceptTargetContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_exceptTarget);
		try {
			setState(324);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IDENT:
				enterOuterAlt(_localctx, 1);
				{
				setState(318);
				match(IDENT);
				}
				break;
			case KEYWORD_CUSTOM:
				enterOuterAlt(_localctx, 2);
				{
				setState(319);
				match(KEYWORD_CUSTOM);
				}
				break;
			case KEYWORD_TEMPLATE:
				enterOuterAlt(_localctx, 3);
				{
				setState(320);
				match(KEYWORD_TEMPLATE);
				setState(321);
				atType();
				}
				break;
			case AT_STYLE:
			case AT_ELEMENT:
			case AT_VAR:
			case AT_HTML:
			case AT_JS:
				enterOuterAlt(_localctx, 4);
				{
				setState(322);
				atType();
				}
				break;
			case AT_CHTL:
				enterOuterAlt(_localctx, 5);
				{
				setState(323);
				match(AT_CHTL);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AtTypeContext extends ParserRuleContext {
		public TerminalNode AT_STYLE() { return getToken(CHTLParser.AT_STYLE, 0); }
		public TerminalNode AT_ELEMENT() { return getToken(CHTLParser.AT_ELEMENT, 0); }
		public TerminalNode AT_VAR() { return getToken(CHTLParser.AT_VAR, 0); }
		public TerminalNode AT_HTML() { return getToken(CHTLParser.AT_HTML, 0); }
		public TerminalNode AT_JS() { return getToken(CHTLParser.AT_JS, 0); }
		public AtTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atType; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLVisitor ) return ((CHTLVisitor<? extends T>)visitor).visitAtType(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AtTypeContext atType() throws RecognitionException {
		AtTypeContext _localctx = new AtTypeContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_atType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(326);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 16642998272L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u00017\u0149\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007\u001b"+
		"\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002\u001e\u0007\u001e"+
		"\u0002\u001f\u0007\u001f\u0002 \u0007 \u0002!\u0007!\u0002\"\u0007\"\u0002"+
		"#\u0007#\u0002$\u0007$\u0002%\u0007%\u0002&\u0007&\u0002\'\u0007\'\u0001"+
		"\u0000\u0005\u0000R\b\u0000\n\u0000\f\u0000U\t\u0000\u0001\u0000\u0001"+
		"\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0003"+
		"\u0001d\b\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0003\u0001"+
		"\u0003\u0001\u0004\u0001\u0004\u0005\u0004m\b\u0004\n\u0004\f\u0004p\t"+
		"\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0003\u0005\u007f\b\u0005\u0001\u0006\u0001\u0006\u0001"+
		"\u0006\u0001\u0007\u0001\u0007\u0005\u0007\u0086\b\u0007\n\u0007\f\u0007"+
		"\u0089\t\u0007\u0001\u0007\u0001\u0007\u0001\b\u0004\b\u008e\b\b\u000b"+
		"\b\f\b\u008f\u0001\t\u0001\t\u0001\n\u0001\n\u0001\n\u0001\u000b\u0001"+
		"\u000b\u0005\u000b\u0099\b\u000b\n\u000b\f\u000b\u009c\t\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\f\u0001\f\u0001\f\u0001\f\u0003\f\u00a4\b\f\u0001\r"+
		"\u0001\r\u0001\r\u0001\u000e\u0004\u000e\u00aa\b\u000e\u000b\u000e\f\u000e"+
		"\u00ab\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u0010\u0001\u0010\u0005"+
		"\u0010\u00b3\b\u0010\n\u0010\f\u0010\u00b6\t\u0010\u0001\u0010\u0001\u0010"+
		"\u0001\u0011\u0004\u0011\u00bb\b\u0011\u000b\u0011\f\u0011\u00bc\u0001"+
		"\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0001\u0014\u0004\u0014\u00c7\b\u0014\u000b\u0014\f\u0014\u00c8"+
		"\u0001\u0015\u0001\u0015\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0018"+
		"\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0019\u0001\u0019"+
		"\u0001\u0019\u0003\u0019\u00de\b\u0019\u0001\u0019\u0001\u0019\u0001\u001a"+
		"\u0001\u001a\u0001\u001a\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b"+
		"\u0001\u001b\u0001\u001b\u0003\u001b\u00eb\b\u001b\u0001\u001b\u0003\u001b"+
		"\u00ee\b\u001b\u0001\u001c\u0001\u001c\u0001\u001c\u0001\u001c\u0001\u001c"+
		"\u0001\u001c\u0003\u001c\u00f6\b\u001c\u0001\u001d\u0001\u001d\u0001\u001d"+
		"\u0001\u001d\u0005\u001d\u00fc\b\u001d\n\u001d\f\u001d\u00ff\t\u001d\u0003"+
		"\u001d\u0101\b\u001d\u0001\u001e\u0001\u001e\u0001\u001e\u0003\u001e\u0106"+
		"\b\u001e\u0001\u001f\u0001\u001f\u0001\u001f\u0001\u001f\u0001\u001f\u0001"+
		" \u0001 \u0001 \u0001 \u0001 \u0003 \u0112\b \u0001 \u0001 \u0001!\u0001"+
		"!\u0001!\u0005!\u0119\b!\n!\f!\u011c\t!\u0001\"\u0001\"\u0001\"\u0001"+
		"\"\u0001\"\u0001\"\u0001\"\u0001\"\u0003\"\u0126\b\"\u0001\"\u0003\"\u0129"+
		"\b\"\u0001\"\u0001\"\u0001#\u0001#\u0001#\u0001#\u0003#\u0131\b#\u0001"+
		"$\u0001$\u0001$\u0001$\u0001%\u0001%\u0001%\u0005%\u013a\b%\n%\f%\u013d"+
		"\t%\u0001&\u0001&\u0001&\u0001&\u0001&\u0001&\u0003&\u0145\b&\u0001\'"+
		"\u0001\'\u0001\'\u0000\u0000(\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010"+
		"\u0012\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,.02468:<>@BDFHJLN\u0000"+
		"\u0006\u0003\u0000\u0004\u0004\u000b\u001022\u0002\u0000),.3\u0004\u0000"+
		"\u0001\u0001++/022\u0001\u0000+,\u0002\u0000)*.3\u0001\u0000\u001d!\u0157"+
		"\u0000S\u0001\u0000\u0000\u0000\u0002c\u0001\u0000\u0000\u0000\u0004e"+
		"\u0001\u0000\u0000\u0000\u0006h\u0001\u0000\u0000\u0000\bj\u0001\u0000"+
		"\u0000\u0000\n~\u0001\u0000\u0000\u0000\f\u0080\u0001\u0000\u0000\u0000"+
		"\u000e\u0083\u0001\u0000\u0000\u0000\u0010\u008d\u0001\u0000\u0000\u0000"+
		"\u0012\u0091\u0001\u0000\u0000\u0000\u0014\u0093\u0001\u0000\u0000\u0000"+
		"\u0016\u0096\u0001\u0000\u0000\u0000\u0018\u00a3\u0001\u0000\u0000\u0000"+
		"\u001a\u00a5\u0001\u0000\u0000\u0000\u001c\u00a9\u0001\u0000\u0000\u0000"+
		"\u001e\u00ad\u0001\u0000\u0000\u0000 \u00b0\u0001\u0000\u0000\u0000\""+
		"\u00ba\u0001\u0000\u0000\u0000$\u00be\u0001\u0000\u0000\u0000&\u00c0\u0001"+
		"\u0000\u0000\u0000(\u00c6\u0001\u0000\u0000\u0000*\u00ca\u0001\u0000\u0000"+
		"\u0000,\u00cc\u0001\u0000\u0000\u0000.\u00d0\u0001\u0000\u0000\u00000"+
		"\u00d5\u0001\u0000\u0000\u00002\u00da\u0001\u0000\u0000\u00004\u00e1\u0001"+
		"\u0000\u0000\u00006\u00e4\u0001\u0000\u0000\u00008\u00f5\u0001\u0000\u0000"+
		"\u0000:\u0100\u0001\u0000\u0000\u0000<\u0102\u0001\u0000\u0000\u0000>"+
		"\u0107\u0001\u0000\u0000\u0000@\u010c\u0001\u0000\u0000\u0000B\u0115\u0001"+
		"\u0000\u0000\u0000D\u011d\u0001\u0000\u0000\u0000F\u012c\u0001\u0000\u0000"+
		"\u0000H\u0132\u0001\u0000\u0000\u0000J\u0136\u0001\u0000\u0000\u0000L"+
		"\u0144\u0001\u0000\u0000\u0000N\u0146\u0001\u0000\u0000\u0000PR\u0003"+
		"\u0002\u0001\u0000QP\u0001\u0000\u0000\u0000RU\u0001\u0000\u0000\u0000"+
		"SQ\u0001\u0000\u0000\u0000ST\u0001\u0000\u0000\u0000TV\u0001\u0000\u0000"+
		"\u0000US\u0001\u0000\u0000\u0000VW\u0005\u0000\u0000\u0001W\u0001\u0001"+
		"\u0000\u0000\u0000Xd\u0003\u0004\u0002\u0000Yd\u0003\f\u0006\u0000Zd\u0003"+
		"\u0014\n\u0000[d\u0003\u001e\u000f\u0000\\d\u0003.\u0017\u0000]d\u0003"+
		"0\u0018\u0000^d\u00032\u0019\u0000_d\u00034\u001a\u0000`d\u00036\u001b"+
		"\u0000ad\u0003<\u001e\u0000bd\u0005-\u0000\u0000cX\u0001\u0000\u0000\u0000"+
		"cY\u0001\u0000\u0000\u0000cZ\u0001\u0000\u0000\u0000c[\u0001\u0000\u0000"+
		"\u0000c\\\u0001\u0000\u0000\u0000c]\u0001\u0000\u0000\u0000c^\u0001\u0000"+
		"\u0000\u0000c_\u0001\u0000\u0000\u0000c`\u0001\u0000\u0000\u0000ca\u0001"+
		"\u0000\u0000\u0000cb\u0001\u0000\u0000\u0000d\u0003\u0001\u0000\u0000"+
		"\u0000ef\u0003\u0006\u0003\u0000fg\u0003\b\u0004\u0000g\u0005\u0001\u0000"+
		"\u0000\u0000hi\u0007\u0000\u0000\u0000i\u0007\u0001\u0000\u0000\u0000"+
		"jn\u0005%\u0000\u0000km\u0003\n\u0005\u0000lk\u0001\u0000\u0000\u0000"+
		"mp\u0001\u0000\u0000\u0000nl\u0001\u0000\u0000\u0000no\u0001\u0000\u0000"+
		"\u0000oq\u0001\u0000\u0000\u0000pn\u0001\u0000\u0000\u0000qr\u0005&\u0000"+
		"\u0000r\t\u0001\u0000\u0000\u0000s\u007f\u0003&\u0013\u0000t\u007f\u0003"+
		"\u0004\u0002\u0000u\u007f\u0003\f\u0006\u0000v\u007f\u0003\u0014\n\u0000"+
		"w\u007f\u0003\u001e\u000f\u0000x\u007f\u0003,\u0016\u0000y\u007f\u0003"+
		"@ \u0000z\u007f\u0003>\u001f\u0000{\u007f\u0003D\"\u0000|\u007f\u0003"+
		"H$\u0000}\u007f\u0005-\u0000\u0000~s\u0001\u0000\u0000\u0000~t\u0001\u0000"+
		"\u0000\u0000~u\u0001\u0000\u0000\u0000~v\u0001\u0000\u0000\u0000~w\u0001"+
		"\u0000\u0000\u0000~x\u0001\u0000\u0000\u0000~y\u0001\u0000\u0000\u0000"+
		"~z\u0001\u0000\u0000\u0000~{\u0001\u0000\u0000\u0000~|\u0001\u0000\u0000"+
		"\u0000~}\u0001\u0000\u0000\u0000\u007f\u000b\u0001\u0000\u0000\u0000\u0080"+
		"\u0081\u0005\u0002\u0000\u0000\u0081\u0082\u0003\u000e\u0007\u0000\u0082"+
		"\r\u0001\u0000\u0000\u0000\u0083\u0087\u0005%\u0000\u0000\u0084\u0086"+
		"\u0003\u0010\b\u0000\u0085\u0084\u0001\u0000\u0000\u0000\u0086\u0089\u0001"+
		"\u0000\u0000\u0000\u0087\u0085\u0001\u0000\u0000\u0000\u0087\u0088\u0001"+
		"\u0000\u0000\u0000\u0088\u008a\u0001\u0000\u0000\u0000\u0089\u0087\u0001"+
		"\u0000\u0000\u0000\u008a\u008b\u0005&\u0000\u0000\u008b\u000f\u0001\u0000"+
		"\u0000\u0000\u008c\u008e\u0003\u0012\t\u0000\u008d\u008c\u0001\u0000\u0000"+
		"\u0000\u008e\u008f\u0001\u0000\u0000\u0000\u008f\u008d\u0001\u0000\u0000"+
		"\u0000\u008f\u0090\u0001\u0000\u0000\u0000\u0090\u0011\u0001\u0000\u0000"+
		"\u0000\u0091\u0092\u0007\u0001\u0000\u0000\u0092\u0013\u0001\u0000\u0000"+
		"\u0000\u0093\u0094\u0005\u0003\u0000\u0000\u0094\u0095\u0003\u0016\u000b"+
		"\u0000\u0095\u0015\u0001\u0000\u0000\u0000\u0096\u009a\u0005%\u0000\u0000"+
		"\u0097\u0099\u0003\u0018\f\u0000\u0098\u0097\u0001\u0000\u0000\u0000\u0099"+
		"\u009c\u0001\u0000\u0000\u0000\u009a\u0098\u0001\u0000\u0000\u0000\u009a"+
		"\u009b\u0001\u0000\u0000\u0000\u009b\u009d\u0001\u0000\u0000\u0000\u009c"+
		"\u009a\u0001\u0000\u0000\u0000\u009d\u009e\u0005&\u0000\u0000\u009e\u0017"+
		"\u0001\u0000\u0000\u0000\u009f\u00a4\u0003&\u0013\u0000\u00a0\u00a4\u0003"+
		",\u0016\u0000\u00a1\u00a4\u0003\u001a\r\u0000\u00a2\u00a4\u0005-\u0000"+
		"\u0000\u00a3\u009f\u0001\u0000\u0000\u0000\u00a3\u00a0\u0001\u0000\u0000"+
		"\u0000\u00a3\u00a1\u0001\u0000\u0000\u0000\u00a3\u00a2\u0001\u0000\u0000"+
		"\u0000\u00a4\u0019\u0001\u0000\u0000\u0000\u00a5\u00a6\u0003\u001c\u000e"+
		"\u0000\u00a6\u00a7\u0003\b\u0004\u0000\u00a7\u001b\u0001\u0000\u0000\u0000"+
		"\u00a8\u00aa\u0007\u0002\u0000\u0000\u00a9\u00a8\u0001\u0000\u0000\u0000"+
		"\u00aa\u00ab\u0001\u0000\u0000\u0000\u00ab\u00a9\u0001\u0000\u0000\u0000"+
		"\u00ab\u00ac\u0001\u0000\u0000\u0000\u00ac\u001d\u0001\u0000\u0000\u0000"+
		"\u00ad\u00ae\u0005\u0004\u0000\u0000\u00ae\u00af\u0003 \u0010\u0000\u00af"+
		"\u001f\u0001\u0000\u0000\u0000\u00b0\u00b4\u0005%\u0000\u0000\u00b1\u00b3"+
		"\u0003\"\u0011\u0000\u00b2\u00b1\u0001\u0000\u0000\u0000\u00b3\u00b6\u0001"+
		"\u0000\u0000\u0000\u00b4\u00b2\u0001\u0000\u0000\u0000\u00b4\u00b5\u0001"+
		"\u0000\u0000\u0000\u00b5\u00b7\u0001\u0000\u0000\u0000\u00b6\u00b4\u0001"+
		"\u0000\u0000\u0000\u00b7\u00b8\u0005&\u0000\u0000\u00b8!\u0001\u0000\u0000"+
		"\u0000\u00b9\u00bb\u0003$\u0012\u0000\u00ba\u00b9\u0001\u0000\u0000\u0000"+
		"\u00bb\u00bc\u0001\u0000\u0000\u0000\u00bc\u00ba\u0001\u0000\u0000\u0000"+
		"\u00bc\u00bd\u0001\u0000\u0000\u0000\u00bd#\u0001\u0000\u0000\u0000\u00be"+
		"\u00bf\u0007\u0001\u0000\u0000\u00bf%\u0001\u0000\u0000\u0000\u00c0\u00c1"+
		"\u00052\u0000\u0000\u00c1\u00c2\u0007\u0003\u0000\u0000\u00c2\u00c3\u0003"+
		"(\u0014\u0000\u00c3\u00c4\u0005-\u0000\u0000\u00c4\'\u0001\u0000\u0000"+
		"\u0000\u00c5\u00c7\u0003*\u0015\u0000\u00c6\u00c5\u0001\u0000\u0000\u0000"+
		"\u00c7\u00c8\u0001\u0000\u0000\u0000\u00c8\u00c6\u0001\u0000\u0000\u0000"+
		"\u00c8\u00c9\u0001\u0000\u0000\u0000\u00c9)\u0001\u0000\u0000\u0000\u00ca"+
		"\u00cb\u0007\u0004\u0000\u0000\u00cb+\u0001\u0000\u0000\u0000\u00cc\u00cd"+
		"\u0003N\'\u0000\u00cd\u00ce\u00052\u0000\u0000\u00ce\u00cf\u0005-\u0000"+
		"\u0000\u00cf-\u0001\u0000\u0000\u0000\u00d0\u00d1\u0005\u0005\u0000\u0000"+
		"\u00d1\u00d2\u0003N\'\u0000\u00d2\u00d3\u00052\u0000\u0000\u00d3\u00d4"+
		"\u0003\b\u0004\u0000\u00d4/\u0001\u0000\u0000\u0000\u00d5\u00d6\u0005"+
		"\u0006\u0000\u0000\u00d6\u00d7\u0003N\'\u0000\u00d7\u00d8\u00052\u0000"+
		"\u0000\u00d8\u00d9\u0003\b\u0004\u0000\u00d91\u0001\u0000\u0000\u0000"+
		"\u00da\u00db\u0005\u0007\u0000\u0000\u00db\u00dd\u0003N\'\u0000\u00dc"+
		"\u00de\u00052\u0000\u0000\u00dd\u00dc\u0001\u0000\u0000\u0000\u00dd\u00de"+
		"\u0001\u0000\u0000\u0000\u00de\u00df\u0001\u0000\u0000\u0000\u00df\u00e0"+
		"\u0003\b\u0004\u0000\u00e03\u0001\u0000\u0000\u0000\u00e1\u00e2\u0005"+
		"\b\u0000\u0000\u00e2\u00e3\u0003\b\u0004\u0000\u00e35\u0001\u0000\u0000"+
		"\u0000\u00e4\u00e5\u0005\t\u0000\u0000\u00e5\u00e6\u00038\u001c\u0000"+
		"\u00e6\u00e7\u0005#\u0000\u0000\u00e7\u00ea\u0003:\u001d\u0000\u00e8\u00e9"+
		"\u0005$\u0000\u0000\u00e9\u00eb\u00052\u0000\u0000\u00ea\u00e8\u0001\u0000"+
		"\u0000\u0000\u00ea\u00eb\u0001\u0000\u0000\u0000\u00eb\u00ed\u0001\u0000"+
		"\u0000\u0000\u00ec\u00ee\u0005-\u0000\u0000\u00ed\u00ec\u0001\u0000\u0000"+
		"\u0000\u00ed\u00ee\u0001\u0000\u0000\u0000\u00ee7\u0001\u0000\u0000\u0000"+
		"\u00ef\u00f6\u0003N\'\u0000\u00f0\u00f6\u0005\"\u0000\u0000\u00f1\u00f2"+
		"\u0005\u0006\u0000\u0000\u00f2\u00f6\u0003N\'\u0000\u00f3\u00f4\u0005"+
		"\u0005\u0000\u0000\u00f4\u00f6\u0003N\'\u0000\u00f5\u00ef\u0001\u0000"+
		"\u0000\u0000\u00f5\u00f0\u0001\u0000\u0000\u0000\u00f5\u00f1\u0001\u0000"+
		"\u0000\u0000\u00f5\u00f3\u0001\u0000\u0000\u0000\u00f69\u0001\u0000\u0000"+
		"\u0000\u00f7\u0101\u00053\u0000\u0000\u00f8\u00fd\u00052\u0000\u0000\u00f9"+
		"\u00fa\u0005/\u0000\u0000\u00fa\u00fc\u00052\u0000\u0000\u00fb\u00f9\u0001"+
		"\u0000\u0000\u0000\u00fc\u00ff\u0001\u0000\u0000\u0000\u00fd\u00fb\u0001"+
		"\u0000\u0000\u0000\u00fd\u00fe\u0001\u0000\u0000\u0000\u00fe\u0101\u0001"+
		"\u0000\u0000\u0000\u00ff\u00fd\u0001\u0000\u0000\u0000\u0100\u00f7\u0001"+
		"\u0000\u0000\u0000\u0100\u00f8\u0001\u0000\u0000\u0000\u0101;\u0001\u0000"+
		"\u0000\u0000\u0102\u0103\u0005\n\u0000\u0000\u0103\u0105\u00052\u0000"+
		"\u0000\u0104\u0106\u0003\b\u0004\u0000\u0105\u0104\u0001\u0000\u0000\u0000"+
		"\u0105\u0106\u0001\u0000\u0000\u0000\u0106=\u0001\u0000\u0000\u0000\u0107"+
		"\u0108\u0005\u0011\u0000\u0000\u0108\u0109\u0003N\'\u0000\u0109\u010a"+
		"\u00052\u0000\u0000\u010a\u010b\u0005-\u0000\u0000\u010b?\u0001\u0000"+
		"\u0000\u0000\u010c\u0111\u0005\u0012\u0000\u0000\u010d\u010e\u0003N\'"+
		"\u0000\u010e\u010f\u00052\u0000\u0000\u010f\u0112\u0001\u0000\u0000\u0000"+
		"\u0110\u0112\u0003B!\u0000\u0111\u010d\u0001\u0000\u0000\u0000\u0111\u0110"+
		"\u0001\u0000\u0000\u0000\u0112\u0113\u0001\u0000\u0000\u0000\u0113\u0114"+
		"\u0005-\u0000\u0000\u0114A\u0001\u0000\u0000\u0000\u0115\u011a\u00052"+
		"\u0000\u0000\u0116\u0117\u0005.\u0000\u0000\u0117\u0119\u00052\u0000\u0000"+
		"\u0118\u0116\u0001\u0000\u0000\u0000\u0119\u011c\u0001\u0000\u0000\u0000"+
		"\u011a\u0118\u0001\u0000\u0000\u0000\u011a\u011b\u0001\u0000\u0000\u0000"+
		"\u011bC\u0001\u0000\u0000\u0000\u011c\u011a\u0001\u0000\u0000\u0000\u011d"+
		"\u0125\u0005\u0013\u0000\u0000\u011e\u0126\u0005\u0014\u0000\u0000\u011f"+
		"\u0126\u0005\u0015\u0000\u0000\u0120\u0126\u0005\u0016\u0000\u0000\u0121"+
		"\u0122\u0005\u0017\u0000\u0000\u0122\u0126\u0005\u0018\u0000\u0000\u0123"+
		"\u0124\u0005\u0017\u0000\u0000\u0124\u0126\u0005\u0019\u0000\u0000\u0125"+
		"\u011e\u0001\u0000\u0000\u0000\u0125\u011f\u0001\u0000\u0000\u0000\u0125"+
		"\u0120\u0001\u0000\u0000\u0000\u0125\u0121\u0001\u0000\u0000\u0000\u0125"+
		"\u0123\u0001\u0000\u0000\u0000\u0125\u0126\u0001\u0000\u0000\u0000\u0126"+
		"\u0128\u0001\u0000\u0000\u0000\u0127\u0129\u0003F#\u0000\u0128\u0127\u0001"+
		"\u0000\u0000\u0000\u0128\u0129\u0001\u0000\u0000\u0000\u0129\u012a\u0001"+
		"\u0000\u0000\u0000\u012a\u012b\u0003\b\u0004\u0000\u012bE\u0001\u0000"+
		"\u0000\u0000\u012c\u0130\u00052\u0000\u0000\u012d\u012e\u0005\'\u0000"+
		"\u0000\u012e\u012f\u00051\u0000\u0000\u012f\u0131\u0005(\u0000\u0000\u0130"+
		"\u012d\u0001\u0000\u0000\u0000\u0130\u0131\u0001\u0000\u0000\u0000\u0131"+
		"G\u0001\u0000\u0000\u0000\u0132\u0133\u0005\u001c\u0000\u0000\u0133\u0134"+
		"\u0003J%\u0000\u0134\u0135\u0005-\u0000\u0000\u0135I\u0001\u0000\u0000"+
		"\u0000\u0136\u013b\u0003L&\u0000\u0137\u0138\u0005.\u0000\u0000\u0138"+
		"\u013a\u0003L&\u0000\u0139\u0137\u0001\u0000\u0000\u0000\u013a\u013d\u0001"+
		"\u0000\u0000\u0000\u013b\u0139\u0001\u0000\u0000\u0000\u013b\u013c\u0001"+
		"\u0000\u0000\u0000\u013cK\u0001\u0000\u0000\u0000\u013d\u013b\u0001\u0000"+
		"\u0000\u0000\u013e\u0145\u00052\u0000\u0000\u013f\u0145\u0005\u0006\u0000"+
		"\u0000\u0140\u0141\u0005\u0005\u0000\u0000\u0141\u0145\u0003N\'\u0000"+
		"\u0142\u0145\u0003N\'\u0000\u0143\u0145\u0005\"\u0000\u0000\u0144\u013e"+
		"\u0001\u0000\u0000\u0000\u0144\u013f\u0001\u0000\u0000\u0000\u0144\u0140"+
		"\u0001\u0000\u0000\u0000\u0144\u0142\u0001\u0000\u0000\u0000\u0144\u0143"+
		"\u0001\u0000\u0000\u0000\u0145M\u0001\u0000\u0000\u0000\u0146\u0147\u0007"+
		"\u0005\u0000\u0000\u0147O\u0001\u0000\u0000\u0000\u001aScn~\u0087\u008f"+
		"\u009a\u00a3\u00ab\u00b4\u00bc\u00c8\u00dd\u00ea\u00ed\u00f5\u00fd\u0100"+
		"\u0105\u0111\u011a\u0125\u0128\u0130\u013b\u0144";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}