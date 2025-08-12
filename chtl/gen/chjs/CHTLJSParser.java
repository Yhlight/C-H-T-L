// Generated from /workspace/chtl/grammar/chjs/CHTLJS.g4 by ANTLR 4.13.1
package chtl.chjs.parser;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class CHTLJSParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		LBRACE2=1, RBRACE2=2, ARROW=3, DOT=4, HASH=5, LBRACK=6, RBRACK=7, LPAREN=8, 
		RPAREN=9, COMMA=10, SEMI=11, COLON=12, NUMBER=13, IDENT=14, LISTEN=15, 
		DELEGATE=16, ANIMATE=17, ARGCHUNK=18, OTHER=19, WS=20;
	public static final int
		RULE_program = 0, RULE_piece = 1, RULE_moustache = 2, RULE_arrowUse = 3, 
		RULE_keywordUse = 4, RULE_selector = 5, RULE_simpleSelector = 6, RULE_argChunk = 7;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "piece", "moustache", "arrowUse", "keywordUse", "selector", 
			"simpleSelector", "argChunk"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'{{'", "'}}'", "'->'", "'.'", "'#'", "'['", "']'", "'('", "')'", 
			"','", "';'", "':'", null, null, "'listen'", "'delegate'", "'animate'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "LBRACE2", "RBRACE2", "ARROW", "DOT", "HASH", "LBRACK", "RBRACK", 
			"LPAREN", "RPAREN", "COMMA", "SEMI", "COLON", "NUMBER", "IDENT", "LISTEN", 
			"DELEGATE", "ANIMATE", "ARGCHUNK", "OTHER", "WS"
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
	public String getGrammarFileName() { return "CHTLJS.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CHTLJSParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(CHTLJSParser.EOF, 0); }
		public List<PieceContext> piece() {
			return getRuleContexts(PieceContext.class);
		}
		public PieceContext piece(int i) {
			return getRuleContext(PieceContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLJSVisitor ) return ((CHTLJSVisitor<? extends T>)visitor).visitProgram(this);
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
			setState(19);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 753666L) != 0)) {
				{
				{
				setState(16);
				piece();
				}
				}
				setState(21);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(22);
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
	public static class PieceContext extends ParserRuleContext {
		public MoustacheContext moustache() {
			return getRuleContext(MoustacheContext.class,0);
		}
		public ArrowUseContext arrowUse() {
			return getRuleContext(ArrowUseContext.class,0);
		}
		public KeywordUseContext keywordUse() {
			return getRuleContext(KeywordUseContext.class,0);
		}
		public TerminalNode OTHER() { return getToken(CHTLJSParser.OTHER, 0); }
		public PieceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_piece; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLJSVisitor ) return ((CHTLJSVisitor<? extends T>)visitor).visitPiece(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PieceContext piece() throws RecognitionException {
		PieceContext _localctx = new PieceContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_piece);
		try {
			setState(28);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(24);
				moustache();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(25);
				arrowUse();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(26);
				keywordUse();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(27);
				match(OTHER);
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
	public static class MoustacheContext extends ParserRuleContext {
		public TerminalNode LBRACE2() { return getToken(CHTLJSParser.LBRACE2, 0); }
		public SelectorContext selector() {
			return getRuleContext(SelectorContext.class,0);
		}
		public TerminalNode RBRACE2() { return getToken(CHTLJSParser.RBRACE2, 0); }
		public MoustacheContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_moustache; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLJSVisitor ) return ((CHTLJSVisitor<? extends T>)visitor).visitMoustache(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MoustacheContext moustache() throws RecognitionException {
		MoustacheContext _localctx = new MoustacheContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_moustache);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(30);
			match(LBRACE2);
			setState(31);
			selector();
			setState(32);
			match(RBRACE2);
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
	public static class ArrowUseContext extends ParserRuleContext {
		public MoustacheContext moustache() {
			return getRuleContext(MoustacheContext.class,0);
		}
		public TerminalNode ARROW() { return getToken(CHTLJSParser.ARROW, 0); }
		public TerminalNode IDENT() { return getToken(CHTLJSParser.IDENT, 0); }
		public TerminalNode LPAREN() { return getToken(CHTLJSParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(CHTLJSParser.RPAREN, 0); }
		public List<ArgChunkContext> argChunk() {
			return getRuleContexts(ArgChunkContext.class);
		}
		public ArgChunkContext argChunk(int i) {
			return getRuleContext(ArgChunkContext.class,i);
		}
		public ArrowUseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrowUse; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLJSVisitor ) return ((CHTLJSVisitor<? extends T>)visitor).visitArrowUse(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArrowUseContext arrowUse() throws RecognitionException {
		ArrowUseContext _localctx = new ArrowUseContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_arrowUse);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(34);
			moustache();
			setState(35);
			match(ARROW);
			setState(36);
			match(IDENT);
			setState(45);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LPAREN) {
				{
				setState(37);
				match(LPAREN);
				setState(41);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(38);
						argChunk();
						}
						} 
					}
					setState(43);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				}
				setState(44);
				match(RPAREN);
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
	public static class KeywordUseContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(CHTLJSParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(CHTLJSParser.RPAREN, 0); }
		public TerminalNode LISTEN() { return getToken(CHTLJSParser.LISTEN, 0); }
		public TerminalNode DELEGATE() { return getToken(CHTLJSParser.DELEGATE, 0); }
		public TerminalNode ANIMATE() { return getToken(CHTLJSParser.ANIMATE, 0); }
		public List<ArgChunkContext> argChunk() {
			return getRuleContexts(ArgChunkContext.class);
		}
		public ArgChunkContext argChunk(int i) {
			return getRuleContext(ArgChunkContext.class,i);
		}
		public KeywordUseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_keywordUse; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLJSVisitor ) return ((CHTLJSVisitor<? extends T>)visitor).visitKeywordUse(this);
			else return visitor.visitChildren(this);
		}
	}

	public final KeywordUseContext keywordUse() throws RecognitionException {
		KeywordUseContext _localctx = new KeywordUseContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_keywordUse);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(47);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 229376L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(48);
			match(LPAREN);
			setState(52);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,4,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(49);
					argChunk();
					}
					} 
				}
				setState(54);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,4,_ctx);
			}
			setState(55);
			match(RPAREN);
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
		public List<SimpleSelectorContext> simpleSelector() {
			return getRuleContexts(SimpleSelectorContext.class);
		}
		public SimpleSelectorContext simpleSelector(int i) {
			return getRuleContext(SimpleSelectorContext.class,i);
		}
		public List<TerminalNode> WS() { return getTokens(CHTLJSParser.WS); }
		public TerminalNode WS(int i) {
			return getToken(CHTLJSParser.WS, i);
		}
		public SelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_selector; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLJSVisitor ) return ((CHTLJSVisitor<? extends T>)visitor).visitSelector(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SelectorContext selector() throws RecognitionException {
		SelectorContext _localctx = new SelectorContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_selector);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(57);
			simpleSelector();
			setState(64);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1065008L) != 0)) {
				{
				{
				setState(59);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==WS) {
					{
					setState(58);
					match(WS);
					}
				}

				setState(61);
				simpleSelector();
				}
				}
				setState(66);
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
	public static class SimpleSelectorContext extends ParserRuleContext {
		public TerminalNode HASH() { return getToken(CHTLJSParser.HASH, 0); }
		public List<TerminalNode> IDENT() { return getTokens(CHTLJSParser.IDENT); }
		public TerminalNode IDENT(int i) {
			return getToken(CHTLJSParser.IDENT, i);
		}
		public TerminalNode LBRACK() { return getToken(CHTLJSParser.LBRACK, 0); }
		public TerminalNode NUMBER() { return getToken(CHTLJSParser.NUMBER, 0); }
		public TerminalNode RBRACK() { return getToken(CHTLJSParser.RBRACK, 0); }
		public TerminalNode DOT() { return getToken(CHTLJSParser.DOT, 0); }
		public List<TerminalNode> WS() { return getTokens(CHTLJSParser.WS); }
		public TerminalNode WS(int i) {
			return getToken(CHTLJSParser.WS, i);
		}
		public SimpleSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_simpleSelector; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLJSVisitor ) return ((CHTLJSVisitor<? extends T>)visitor).visitSimpleSelector(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SimpleSelectorContext simpleSelector() throws RecognitionException {
		SimpleSelectorContext _localctx = new SimpleSelectorContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_simpleSelector);
		int _la;
		try {
			int _alt;
			setState(89);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case HASH:
				enterOuterAlt(_localctx, 1);
				{
				setState(67);
				match(HASH);
				setState(68);
				match(IDENT);
				setState(72);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==LBRACK) {
					{
					setState(69);
					match(LBRACK);
					setState(70);
					match(NUMBER);
					setState(71);
					match(RBRACK);
					}
				}

				}
				break;
			case DOT:
				enterOuterAlt(_localctx, 2);
				{
				setState(74);
				match(DOT);
				setState(75);
				match(IDENT);
				setState(80);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,8,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(76);
						match(WS);
						setState(77);
						match(IDENT);
						}
						} 
					}
					setState(82);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,8,_ctx);
				}
				}
				break;
			case IDENT:
				enterOuterAlt(_localctx, 3);
				{
				setState(83);
				match(IDENT);
				setState(87);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==LBRACK) {
					{
					setState(84);
					match(LBRACK);
					setState(85);
					match(NUMBER);
					setState(86);
					match(RBRACK);
					}
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
	public static class ArgChunkContext extends ParserRuleContext {
		public TerminalNode ARGCHUNK() { return getToken(CHTLJSParser.ARGCHUNK, 0); }
		public TerminalNode LPAREN() { return getToken(CHTLJSParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(CHTLJSParser.RPAREN, 0); }
		public ArgChunkContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_argChunk; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CHTLJSVisitor ) return ((CHTLJSVisitor<? extends T>)visitor).visitArgChunk(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArgChunkContext argChunk() throws RecognitionException {
		ArgChunkContext _localctx = new ArgChunkContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_argChunk);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(91);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 262912L) != 0)) ) {
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
		"\u0004\u0001\u0014^\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0001"+
		"\u0000\u0005\u0000\u0012\b\u0000\n\u0000\f\u0000\u0015\t\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0003\u0001"+
		"\u001d\b\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0005\u0003(\b\u0003"+
		"\n\u0003\f\u0003+\t\u0003\u0001\u0003\u0003\u0003.\b\u0003\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0005\u00043\b\u0004\n\u0004\f\u00046\t\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0003\u0005<\b\u0005"+
		"\u0001\u0005\u0005\u0005?\b\u0005\n\u0005\f\u0005B\t\u0005\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006I\b\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0005\u0006O\b\u0006"+
		"\n\u0006\f\u0006R\t\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0003\u0006X\b\u0006\u0003\u0006Z\b\u0006\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0000\u0000\b\u0000\u0002\u0004\u0006\b\n\f\u000e\u0000\u0002\u0001"+
		"\u0000\u000f\u0011\u0002\u0000\b\t\u0012\u0012c\u0000\u0013\u0001\u0000"+
		"\u0000\u0000\u0002\u001c\u0001\u0000\u0000\u0000\u0004\u001e\u0001\u0000"+
		"\u0000\u0000\u0006\"\u0001\u0000\u0000\u0000\b/\u0001\u0000\u0000\u0000"+
		"\n9\u0001\u0000\u0000\u0000\fY\u0001\u0000\u0000\u0000\u000e[\u0001\u0000"+
		"\u0000\u0000\u0010\u0012\u0003\u0002\u0001\u0000\u0011\u0010\u0001\u0000"+
		"\u0000\u0000\u0012\u0015\u0001\u0000\u0000\u0000\u0013\u0011\u0001\u0000"+
		"\u0000\u0000\u0013\u0014\u0001\u0000\u0000\u0000\u0014\u0016\u0001\u0000"+
		"\u0000\u0000\u0015\u0013\u0001\u0000\u0000\u0000\u0016\u0017\u0005\u0000"+
		"\u0000\u0001\u0017\u0001\u0001\u0000\u0000\u0000\u0018\u001d\u0003\u0004"+
		"\u0002\u0000\u0019\u001d\u0003\u0006\u0003\u0000\u001a\u001d\u0003\b\u0004"+
		"\u0000\u001b\u001d\u0005\u0013\u0000\u0000\u001c\u0018\u0001\u0000\u0000"+
		"\u0000\u001c\u0019\u0001\u0000\u0000\u0000\u001c\u001a\u0001\u0000\u0000"+
		"\u0000\u001c\u001b\u0001\u0000\u0000\u0000\u001d\u0003\u0001\u0000\u0000"+
		"\u0000\u001e\u001f\u0005\u0001\u0000\u0000\u001f \u0003\n\u0005\u0000"+
		" !\u0005\u0002\u0000\u0000!\u0005\u0001\u0000\u0000\u0000\"#\u0003\u0004"+
		"\u0002\u0000#$\u0005\u0003\u0000\u0000$-\u0005\u000e\u0000\u0000%)\u0005"+
		"\b\u0000\u0000&(\u0003\u000e\u0007\u0000\'&\u0001\u0000\u0000\u0000(+"+
		"\u0001\u0000\u0000\u0000)\'\u0001\u0000\u0000\u0000)*\u0001\u0000\u0000"+
		"\u0000*,\u0001\u0000\u0000\u0000+)\u0001\u0000\u0000\u0000,.\u0005\t\u0000"+
		"\u0000-%\u0001\u0000\u0000\u0000-.\u0001\u0000\u0000\u0000.\u0007\u0001"+
		"\u0000\u0000\u0000/0\u0007\u0000\u0000\u000004\u0005\b\u0000\u000013\u0003"+
		"\u000e\u0007\u000021\u0001\u0000\u0000\u000036\u0001\u0000\u0000\u0000"+
		"42\u0001\u0000\u0000\u000045\u0001\u0000\u0000\u000057\u0001\u0000\u0000"+
		"\u000064\u0001\u0000\u0000\u000078\u0005\t\u0000\u00008\t\u0001\u0000"+
		"\u0000\u00009@\u0003\f\u0006\u0000:<\u0005\u0014\u0000\u0000;:\u0001\u0000"+
		"\u0000\u0000;<\u0001\u0000\u0000\u0000<=\u0001\u0000\u0000\u0000=?\u0003"+
		"\f\u0006\u0000>;\u0001\u0000\u0000\u0000?B\u0001\u0000\u0000\u0000@>\u0001"+
		"\u0000\u0000\u0000@A\u0001\u0000\u0000\u0000A\u000b\u0001\u0000\u0000"+
		"\u0000B@\u0001\u0000\u0000\u0000CD\u0005\u0005\u0000\u0000DH\u0005\u000e"+
		"\u0000\u0000EF\u0005\u0006\u0000\u0000FG\u0005\r\u0000\u0000GI\u0005\u0007"+
		"\u0000\u0000HE\u0001\u0000\u0000\u0000HI\u0001\u0000\u0000\u0000IZ\u0001"+
		"\u0000\u0000\u0000JK\u0005\u0004\u0000\u0000KP\u0005\u000e\u0000\u0000"+
		"LM\u0005\u0014\u0000\u0000MO\u0005\u000e\u0000\u0000NL\u0001\u0000\u0000"+
		"\u0000OR\u0001\u0000\u0000\u0000PN\u0001\u0000\u0000\u0000PQ\u0001\u0000"+
		"\u0000\u0000QZ\u0001\u0000\u0000\u0000RP\u0001\u0000\u0000\u0000SW\u0005"+
		"\u000e\u0000\u0000TU\u0005\u0006\u0000\u0000UV\u0005\r\u0000\u0000VX\u0005"+
		"\u0007\u0000\u0000WT\u0001\u0000\u0000\u0000WX\u0001\u0000\u0000\u0000"+
		"XZ\u0001\u0000\u0000\u0000YC\u0001\u0000\u0000\u0000YJ\u0001\u0000\u0000"+
		"\u0000YS\u0001\u0000\u0000\u0000Z\r\u0001\u0000\u0000\u0000[\\\u0007\u0001"+
		"\u0000\u0000\\\u000f\u0001\u0000\u0000\u0000\u000b\u0013\u001c)-4;@HP"+
		"WY";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}