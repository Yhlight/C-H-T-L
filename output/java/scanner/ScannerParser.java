// Generated from Scanner.g4 by ANTLR 4.13.1
package scanner;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class ScannerParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, TEXT=4, STYLE=5, SCRIPT=6, TEMPLATE_START=7, CUSTOM_START=8, 
		CONFIG_START=9, NAMESPACE_START=10, IMPORT_START=11, ORIGIN_START=12, 
		COLON_OR_EQUAL=13, IDENTIFIER=14, STRING_LITERAL=15, UNQUOTED_LITERAL=16, 
		ATTR_VALUE=17, ANY_CONTENT=18, WS=19, COMMENT=20, MULTI_COMMENT=21;
	public static final int
		RULE_document = 0, RULE_codeBlock = 1, RULE_chtlBlock = 2, RULE_chtlElement = 3, 
		RULE_elementStart = 4, RULE_elementEnd = 5, RULE_elementContent = 6, RULE_chtlAttribute = 7, 
		RULE_chtlDeclaration = 8, RULE_chtlStatement = 9, RULE_textBlock = 10, 
		RULE_textContent = 11;
	private static String[] makeRuleNames() {
		return new String[] {
			"document", "codeBlock", "chtlBlock", "chtlElement", "elementStart", 
			"elementEnd", "elementContent", "chtlAttribute", "chtlDeclaration", "chtlStatement", 
			"textBlock", "textContent"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'{'", "'}'", "';'", "'text'", "'style'", "'script'", "'[Template]'", 
			"'[Custom]'", "'[Configuration]'", "'[Namespace]'", "'[Import]'", "'[Origin]'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, "TEXT", "STYLE", "SCRIPT", "TEMPLATE_START", 
			"CUSTOM_START", "CONFIG_START", "NAMESPACE_START", "IMPORT_START", "ORIGIN_START", 
			"COLON_OR_EQUAL", "IDENTIFIER", "STRING_LITERAL", "UNQUOTED_LITERAL", 
			"ATTR_VALUE", "ANY_CONTENT", "WS", "COMMENT", "MULTI_COMMENT"
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
	public String getGrammarFileName() { return "Scanner.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ScannerParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DocumentContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(ScannerParser.EOF, 0); }
		public List<CodeBlockContext> codeBlock() {
			return getRuleContexts(CodeBlockContext.class);
		}
		public CodeBlockContext codeBlock(int i) {
			return getRuleContext(CodeBlockContext.class,i);
		}
		public DocumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_document; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterDocument(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitDocument(this);
		}
	}

	public final DocumentContext document() throws RecognitionException {
		DocumentContext _localctx = new DocumentContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_document);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(27);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 385008L) != 0)) {
				{
				{
				setState(24);
				codeBlock();
				}
				}
				setState(29);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(30);
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
	public static class CodeBlockContext extends ParserRuleContext {
		public ChtlBlockContext chtlBlock() {
			return getRuleContext(ChtlBlockContext.class,0);
		}
		public TextBlockContext textBlock() {
			return getRuleContext(TextBlockContext.class,0);
		}
		public CodeBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_codeBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterCodeBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitCodeBlock(this);
		}
	}

	public final CodeBlockContext codeBlock() throws RecognitionException {
		CodeBlockContext _localctx = new CodeBlockContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_codeBlock);
		try {
			setState(34);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TEXT:
			case STYLE:
			case SCRIPT:
			case TEMPLATE_START:
			case CUSTOM_START:
			case CONFIG_START:
			case NAMESPACE_START:
			case IMPORT_START:
			case ORIGIN_START:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(32);
				chtlBlock();
				}
				break;
			case STRING_LITERAL:
			case UNQUOTED_LITERAL:
			case ANY_CONTENT:
				enterOuterAlt(_localctx, 2);
				{
				setState(33);
				textBlock();
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
	public static class ChtlBlockContext extends ParserRuleContext {
		public ChtlElementContext chtlElement() {
			return getRuleContext(ChtlElementContext.class,0);
		}
		public ChtlDeclarationContext chtlDeclaration() {
			return getRuleContext(ChtlDeclarationContext.class,0);
		}
		public ChtlStatementContext chtlStatement() {
			return getRuleContext(ChtlStatementContext.class,0);
		}
		public ChtlBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chtlBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterChtlBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitChtlBlock(this);
		}
	}

	public final ChtlBlockContext chtlBlock() throws RecognitionException {
		ChtlBlockContext _localctx = new ChtlBlockContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_chtlBlock);
		try {
			setState(39);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TEXT:
			case STYLE:
			case SCRIPT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(36);
				chtlElement();
				}
				break;
			case TEMPLATE_START:
			case CUSTOM_START:
			case CONFIG_START:
			case NAMESPACE_START:
				enterOuterAlt(_localctx, 2);
				{
				setState(37);
				chtlDeclaration();
				}
				break;
			case IMPORT_START:
			case ORIGIN_START:
				enterOuterAlt(_localctx, 3);
				{
				setState(38);
				chtlStatement();
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
	public static class ChtlElementContext extends ParserRuleContext {
		public ElementStartContext elementStart() {
			return getRuleContext(ElementStartContext.class,0);
		}
		public ElementEndContext elementEnd() {
			return getRuleContext(ElementEndContext.class,0);
		}
		public List<ElementContentContext> elementContent() {
			return getRuleContexts(ElementContentContext.class);
		}
		public ElementContentContext elementContent(int i) {
			return getRuleContext(ElementContentContext.class,i);
		}
		public ChtlElementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chtlElement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterChtlElement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitChtlElement(this);
		}
	}

	public final ChtlElementContext chtlElement() throws RecognitionException {
		ChtlElementContext _localctx = new ChtlElementContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_chtlElement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(41);
			elementStart();
			setState(45);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 376944L) != 0)) {
				{
				{
				setState(42);
				elementContent();
				}
				}
				setState(47);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(48);
			elementEnd();
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
	public static class ElementStartContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(ScannerParser.IDENTIFIER, 0); }
		public TerminalNode TEXT() { return getToken(ScannerParser.TEXT, 0); }
		public TerminalNode STYLE() { return getToken(ScannerParser.STYLE, 0); }
		public TerminalNode SCRIPT() { return getToken(ScannerParser.SCRIPT, 0); }
		public ElementStartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementStart; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterElementStart(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitElementStart(this);
		}
	}

	public final ElementStartContext elementStart() throws RecognitionException {
		ElementStartContext _localctx = new ElementStartContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_elementStart);
		try {
			setState(58);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(50);
				match(IDENTIFIER);
				setState(51);
				match(T__0);
				}
				break;
			case TEXT:
				enterOuterAlt(_localctx, 2);
				{
				setState(52);
				match(TEXT);
				setState(53);
				match(T__0);
				}
				break;
			case STYLE:
				enterOuterAlt(_localctx, 3);
				{
				setState(54);
				match(STYLE);
				setState(55);
				match(T__0);
				}
				break;
			case SCRIPT:
				enterOuterAlt(_localctx, 4);
				{
				setState(56);
				match(SCRIPT);
				setState(57);
				match(T__0);
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
	public static class ElementEndContext extends ParserRuleContext {
		public ElementEndContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementEnd; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterElementEnd(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitElementEnd(this);
		}
	}

	public final ElementEndContext elementEnd() throws RecognitionException {
		ElementEndContext _localctx = new ElementEndContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_elementEnd);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(60);
			match(T__1);
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
	public static class ElementContentContext extends ParserRuleContext {
		public ChtlAttributeContext chtlAttribute() {
			return getRuleContext(ChtlAttributeContext.class,0);
		}
		public ChtlElementContext chtlElement() {
			return getRuleContext(ChtlElementContext.class,0);
		}
		public TextContentContext textContent() {
			return getRuleContext(TextContentContext.class,0);
		}
		public TerminalNode ANY_CONTENT() { return getToken(ScannerParser.ANY_CONTENT, 0); }
		public ElementContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterElementContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitElementContent(this);
		}
	}

	public final ElementContentContext elementContent() throws RecognitionException {
		ElementContentContext _localctx = new ElementContentContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_elementContent);
		try {
			setState(66);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(62);
				chtlAttribute();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(63);
				chtlElement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(64);
				textContent();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(65);
				match(ANY_CONTENT);
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
	public static class ChtlAttributeContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(ScannerParser.IDENTIFIER, 0); }
		public TerminalNode COLON_OR_EQUAL() { return getToken(ScannerParser.COLON_OR_EQUAL, 0); }
		public TerminalNode ATTR_VALUE() { return getToken(ScannerParser.ATTR_VALUE, 0); }
		public ChtlAttributeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chtlAttribute; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterChtlAttribute(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitChtlAttribute(this);
		}
	}

	public final ChtlAttributeContext chtlAttribute() throws RecognitionException {
		ChtlAttributeContext _localctx = new ChtlAttributeContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_chtlAttribute);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(68);
			match(IDENTIFIER);
			setState(69);
			match(COLON_OR_EQUAL);
			setState(70);
			match(ATTR_VALUE);
			setState(71);
			match(T__2);
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
	public static class ChtlDeclarationContext extends ParserRuleContext {
		public TerminalNode TEMPLATE_START() { return getToken(ScannerParser.TEMPLATE_START, 0); }
		public List<TerminalNode> ANY_CONTENT() { return getTokens(ScannerParser.ANY_CONTENT); }
		public TerminalNode ANY_CONTENT(int i) {
			return getToken(ScannerParser.ANY_CONTENT, i);
		}
		public TerminalNode CUSTOM_START() { return getToken(ScannerParser.CUSTOM_START, 0); }
		public TerminalNode CONFIG_START() { return getToken(ScannerParser.CONFIG_START, 0); }
		public TerminalNode NAMESPACE_START() { return getToken(ScannerParser.NAMESPACE_START, 0); }
		public ChtlDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chtlDeclaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterChtlDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitChtlDeclaration(this);
		}
	}

	public final ChtlDeclarationContext chtlDeclaration() throws RecognitionException {
		ChtlDeclarationContext _localctx = new ChtlDeclarationContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_chtlDeclaration);
		int _la;
		try {
			setState(105);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TEMPLATE_START:
				enterOuterAlt(_localctx, 1);
				{
				setState(73);
				match(TEMPLATE_START);
				setState(77);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==ANY_CONTENT) {
					{
					{
					setState(74);
					match(ANY_CONTENT);
					}
					}
					setState(79);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(80);
				match(T__1);
				}
				break;
			case CUSTOM_START:
				enterOuterAlt(_localctx, 2);
				{
				setState(81);
				match(CUSTOM_START);
				setState(85);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==ANY_CONTENT) {
					{
					{
					setState(82);
					match(ANY_CONTENT);
					}
					}
					setState(87);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(88);
				match(T__1);
				}
				break;
			case CONFIG_START:
				enterOuterAlt(_localctx, 3);
				{
				setState(89);
				match(CONFIG_START);
				setState(93);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==ANY_CONTENT) {
					{
					{
					setState(90);
					match(ANY_CONTENT);
					}
					}
					setState(95);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(96);
				match(T__1);
				}
				break;
			case NAMESPACE_START:
				enterOuterAlt(_localctx, 4);
				{
				setState(97);
				match(NAMESPACE_START);
				setState(101);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==ANY_CONTENT) {
					{
					{
					setState(98);
					match(ANY_CONTENT);
					}
					}
					setState(103);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(104);
				match(T__1);
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
	public static class ChtlStatementContext extends ParserRuleContext {
		public TerminalNode IMPORT_START() { return getToken(ScannerParser.IMPORT_START, 0); }
		public List<TerminalNode> ANY_CONTENT() { return getTokens(ScannerParser.ANY_CONTENT); }
		public TerminalNode ANY_CONTENT(int i) {
			return getToken(ScannerParser.ANY_CONTENT, i);
		}
		public TerminalNode ORIGIN_START() { return getToken(ScannerParser.ORIGIN_START, 0); }
		public ChtlStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chtlStatement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterChtlStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitChtlStatement(this);
		}
	}

	public final ChtlStatementContext chtlStatement() throws RecognitionException {
		ChtlStatementContext _localctx = new ChtlStatementContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_chtlStatement);
		int _la;
		try {
			int _alt;
			setState(125);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IMPORT_START:
				enterOuterAlt(_localctx, 1);
				{
				setState(107);
				match(IMPORT_START);
				setState(111);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,11,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(108);
						match(ANY_CONTENT);
						}
						} 
					}
					setState(113);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,11,_ctx);
				}
				setState(115);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__2) {
					{
					setState(114);
					match(T__2);
					}
				}

				}
				break;
			case ORIGIN_START:
				enterOuterAlt(_localctx, 2);
				{
				setState(117);
				match(ORIGIN_START);
				setState(121);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==ANY_CONTENT) {
					{
					{
					setState(118);
					match(ANY_CONTENT);
					}
					}
					setState(123);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(124);
				match(T__1);
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
	public static class TextBlockContext extends ParserRuleContext {
		public TextContentContext textContent() {
			return getRuleContext(TextContentContext.class,0);
		}
		public TextBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_textBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterTextBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitTextBlock(this);
		}
	}

	public final TextBlockContext textBlock() throws RecognitionException {
		TextBlockContext _localctx = new TextBlockContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_textBlock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(127);
			textContent();
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
	public static class TextContentContext extends ParserRuleContext {
		public TerminalNode STRING_LITERAL() { return getToken(ScannerParser.STRING_LITERAL, 0); }
		public TerminalNode UNQUOTED_LITERAL() { return getToken(ScannerParser.UNQUOTED_LITERAL, 0); }
		public TerminalNode ANY_CONTENT() { return getToken(ScannerParser.ANY_CONTENT, 0); }
		public TextContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_textContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).enterTextContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ScannerListener ) ((ScannerListener)listener).exitTextContent(this);
		}
	}

	public final TextContentContext textContent() throws RecognitionException {
		TextContentContext _localctx = new TextContentContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_textContent);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(129);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 360448L) != 0)) ) {
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
		"\u0004\u0001\u0015\u0084\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001"+
		"\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004"+
		"\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007"+
		"\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b"+
		"\u0001\u0000\u0005\u0000\u001a\b\u0000\n\u0000\f\u0000\u001d\t\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0003\u0001#\b\u0001\u0001"+
		"\u0002\u0001\u0002\u0001\u0002\u0003\u0002(\b\u0002\u0001\u0003\u0001"+
		"\u0003\u0005\u0003,\b\u0003\n\u0003\f\u0003/\t\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0004\u0001\u0004\u0003\u0004;\b\u0004\u0001\u0005\u0001"+
		"\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006C\b"+
		"\u0006\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001"+
		"\b\u0001\b\u0005\bL\b\b\n\b\f\bO\t\b\u0001\b\u0001\b\u0001\b\u0005\bT"+
		"\b\b\n\b\f\bW\t\b\u0001\b\u0001\b\u0001\b\u0005\b\\\b\b\n\b\f\b_\t\b\u0001"+
		"\b\u0001\b\u0001\b\u0005\bd\b\b\n\b\f\bg\t\b\u0001\b\u0003\bj\b\b\u0001"+
		"\t\u0001\t\u0005\tn\b\t\n\t\f\tq\t\t\u0001\t\u0003\tt\b\t\u0001\t\u0001"+
		"\t\u0005\tx\b\t\n\t\f\t{\t\t\u0001\t\u0003\t~\b\t\u0001\n\u0001\n\u0001"+
		"\u000b\u0001\u000b\u0001\u000b\u0000\u0000\f\u0000\u0002\u0004\u0006\b"+
		"\n\f\u000e\u0010\u0012\u0014\u0016\u0000\u0001\u0002\u0000\u000f\u0010"+
		"\u0012\u0012\u008d\u0000\u001b\u0001\u0000\u0000\u0000\u0002\"\u0001\u0000"+
		"\u0000\u0000\u0004\'\u0001\u0000\u0000\u0000\u0006)\u0001\u0000\u0000"+
		"\u0000\b:\u0001\u0000\u0000\u0000\n<\u0001\u0000\u0000\u0000\fB\u0001"+
		"\u0000\u0000\u0000\u000eD\u0001\u0000\u0000\u0000\u0010i\u0001\u0000\u0000"+
		"\u0000\u0012}\u0001\u0000\u0000\u0000\u0014\u007f\u0001\u0000\u0000\u0000"+
		"\u0016\u0081\u0001\u0000\u0000\u0000\u0018\u001a\u0003\u0002\u0001\u0000"+
		"\u0019\u0018\u0001\u0000\u0000\u0000\u001a\u001d\u0001\u0000\u0000\u0000"+
		"\u001b\u0019\u0001\u0000\u0000\u0000\u001b\u001c\u0001\u0000\u0000\u0000"+
		"\u001c\u001e\u0001\u0000\u0000\u0000\u001d\u001b\u0001\u0000\u0000\u0000"+
		"\u001e\u001f\u0005\u0000\u0000\u0001\u001f\u0001\u0001\u0000\u0000\u0000"+
		" #\u0003\u0004\u0002\u0000!#\u0003\u0014\n\u0000\" \u0001\u0000\u0000"+
		"\u0000\"!\u0001\u0000\u0000\u0000#\u0003\u0001\u0000\u0000\u0000$(\u0003"+
		"\u0006\u0003\u0000%(\u0003\u0010\b\u0000&(\u0003\u0012\t\u0000\'$\u0001"+
		"\u0000\u0000\u0000\'%\u0001\u0000\u0000\u0000\'&\u0001\u0000\u0000\u0000"+
		"(\u0005\u0001\u0000\u0000\u0000)-\u0003\b\u0004\u0000*,\u0003\f\u0006"+
		"\u0000+*\u0001\u0000\u0000\u0000,/\u0001\u0000\u0000\u0000-+\u0001\u0000"+
		"\u0000\u0000-.\u0001\u0000\u0000\u0000.0\u0001\u0000\u0000\u0000/-\u0001"+
		"\u0000\u0000\u000001\u0003\n\u0005\u00001\u0007\u0001\u0000\u0000\u0000"+
		"23\u0005\u000e\u0000\u00003;\u0005\u0001\u0000\u000045\u0005\u0004\u0000"+
		"\u00005;\u0005\u0001\u0000\u000067\u0005\u0005\u0000\u00007;\u0005\u0001"+
		"\u0000\u000089\u0005\u0006\u0000\u00009;\u0005\u0001\u0000\u0000:2\u0001"+
		"\u0000\u0000\u0000:4\u0001\u0000\u0000\u0000:6\u0001\u0000\u0000\u0000"+
		":8\u0001\u0000\u0000\u0000;\t\u0001\u0000\u0000\u0000<=\u0005\u0002\u0000"+
		"\u0000=\u000b\u0001\u0000\u0000\u0000>C\u0003\u000e\u0007\u0000?C\u0003"+
		"\u0006\u0003\u0000@C\u0003\u0016\u000b\u0000AC\u0005\u0012\u0000\u0000"+
		"B>\u0001\u0000\u0000\u0000B?\u0001\u0000\u0000\u0000B@\u0001\u0000\u0000"+
		"\u0000BA\u0001\u0000\u0000\u0000C\r\u0001\u0000\u0000\u0000DE\u0005\u000e"+
		"\u0000\u0000EF\u0005\r\u0000\u0000FG\u0005\u0011\u0000\u0000GH\u0005\u0003"+
		"\u0000\u0000H\u000f\u0001\u0000\u0000\u0000IM\u0005\u0007\u0000\u0000"+
		"JL\u0005\u0012\u0000\u0000KJ\u0001\u0000\u0000\u0000LO\u0001\u0000\u0000"+
		"\u0000MK\u0001\u0000\u0000\u0000MN\u0001\u0000\u0000\u0000NP\u0001\u0000"+
		"\u0000\u0000OM\u0001\u0000\u0000\u0000Pj\u0005\u0002\u0000\u0000QU\u0005"+
		"\b\u0000\u0000RT\u0005\u0012\u0000\u0000SR\u0001\u0000\u0000\u0000TW\u0001"+
		"\u0000\u0000\u0000US\u0001\u0000\u0000\u0000UV\u0001\u0000\u0000\u0000"+
		"VX\u0001\u0000\u0000\u0000WU\u0001\u0000\u0000\u0000Xj\u0005\u0002\u0000"+
		"\u0000Y]\u0005\t\u0000\u0000Z\\\u0005\u0012\u0000\u0000[Z\u0001\u0000"+
		"\u0000\u0000\\_\u0001\u0000\u0000\u0000][\u0001\u0000\u0000\u0000]^\u0001"+
		"\u0000\u0000\u0000^`\u0001\u0000\u0000\u0000_]\u0001\u0000\u0000\u0000"+
		"`j\u0005\u0002\u0000\u0000ae\u0005\n\u0000\u0000bd\u0005\u0012\u0000\u0000"+
		"cb\u0001\u0000\u0000\u0000dg\u0001\u0000\u0000\u0000ec\u0001\u0000\u0000"+
		"\u0000ef\u0001\u0000\u0000\u0000fh\u0001\u0000\u0000\u0000ge\u0001\u0000"+
		"\u0000\u0000hj\u0005\u0002\u0000\u0000iI\u0001\u0000\u0000\u0000iQ\u0001"+
		"\u0000\u0000\u0000iY\u0001\u0000\u0000\u0000ia\u0001\u0000\u0000\u0000"+
		"j\u0011\u0001\u0000\u0000\u0000ko\u0005\u000b\u0000\u0000ln\u0005\u0012"+
		"\u0000\u0000ml\u0001\u0000\u0000\u0000nq\u0001\u0000\u0000\u0000om\u0001"+
		"\u0000\u0000\u0000op\u0001\u0000\u0000\u0000ps\u0001\u0000\u0000\u0000"+
		"qo\u0001\u0000\u0000\u0000rt\u0005\u0003\u0000\u0000sr\u0001\u0000\u0000"+
		"\u0000st\u0001\u0000\u0000\u0000t~\u0001\u0000\u0000\u0000uy\u0005\f\u0000"+
		"\u0000vx\u0005\u0012\u0000\u0000wv\u0001\u0000\u0000\u0000x{\u0001\u0000"+
		"\u0000\u0000yw\u0001\u0000\u0000\u0000yz\u0001\u0000\u0000\u0000z|\u0001"+
		"\u0000\u0000\u0000{y\u0001\u0000\u0000\u0000|~\u0005\u0002\u0000\u0000"+
		"}k\u0001\u0000\u0000\u0000}u\u0001\u0000\u0000\u0000~\u0013\u0001\u0000"+
		"\u0000\u0000\u007f\u0080\u0003\u0016\u000b\u0000\u0080\u0015\u0001\u0000"+
		"\u0000\u0000\u0081\u0082\u0007\u0000\u0000\u0000\u0082\u0017\u0001\u0000"+
		"\u0000\u0000\u000f\u001b\"\'-:BMU]eiosy}";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}