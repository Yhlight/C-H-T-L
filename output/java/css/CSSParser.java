// Generated from CSS.g4 by ANTLR 4.13.1
package css;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class CSSParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, COMMENT=31, 
		IMPORT=32, MEDIA=33, KEYFRAMES=34, FONT_FACE=35, SUPPORTS=36, PAGE=37, 
		NAMESPACE=38, CHARSET=39, VIEWPORT=40, COUNTER_STYLE=41, FONT_FEATURE_VALUES=42, 
		PROPERTY=43, ONLY=44, NOT=45, AND=46, OR=47, FROM=48, TO=49, IMPORTANT=50, 
		PX=51, EM=52, REM=53, VH=54, VW=55, VMIN=56, VMAX=57, CH=58, EX=59, CM=60, 
		MM=61, IN=62, PT=63, PC=64, DEG=65, RAD=66, GRAD=67, TURN=68, S=69, MS=70, 
		HZ=71, KHZ=72, DPI=73, DPCM=74, DPPX=75, VARIABLE=76, NUMBER=77, STRING_LITERAL=78, 
		URI=79, IDENTIFIER=80, HEX_DIGIT=81, WS=82;
	public static final int
		RULE_stylesheet = 0, RULE_statement = 1, RULE_ruleset = 2, RULE_selectorList = 3, 
		RULE_selector = 4, RULE_combinator = 5, RULE_simpleSelector = 6, RULE_typeSelector = 7, 
		RULE_universalSelector = 8, RULE_idSelector = 9, RULE_classSelector = 10, 
		RULE_attributeSelector = 11, RULE_attributeOperator = 12, RULE_pseudoSelector = 13, 
		RULE_pseudoClass = 14, RULE_pseudoClassArgument = 15, RULE_pseudoElement = 16, 
		RULE_declaration = 17, RULE_property = 18, RULE_value = 19, RULE_operator = 20, 
		RULE_term = 21, RULE_unaryOperator = 22, RULE_numeric = 23, RULE_percentage = 24, 
		RULE_length = 25, RULE_angle = 26, RULE_time = 27, RULE_frequency = 28, 
		RULE_resolution = 29, RULE_hexcolor = 30, RULE_function = 31, RULE_functionArguments = 32, 
		RULE_functionArgument = 33, RULE_calc = 34, RULE_calcExpression = 35, 
		RULE_calcTerm = 36, RULE_calcFactor = 37, RULE_atRule = 38, RULE_atImport = 39, 
		RULE_atMedia = 40, RULE_mediaQueryList = 41, RULE_mediaQuery = 42, RULE_mediaType = 43, 
		RULE_mediaFeature = 44, RULE_atKeyframes = 45, RULE_keyframeBlock = 46, 
		RULE_keyframeSelector = 47, RULE_atFontFace = 48, RULE_atSupports = 49, 
		RULE_supportsCondition = 50, RULE_supportsNegation = 51, RULE_supportsConjunction = 52, 
		RULE_supportsDisjunction = 53, RULE_supportsInParens = 54, RULE_supportsFeature = 55, 
		RULE_atPage = 56, RULE_pseudoPage = 57, RULE_atNamespace = 58, RULE_atCharset = 59, 
		RULE_atViewport = 60, RULE_atCounterStyle = 61, RULE_atFontFeatureValues = 62, 
		RULE_fontFamilyName = 63, RULE_fontFeatureValueBlock = 64, RULE_atProperty = 65, 
		RULE_expression = 66, RULE_comment = 67;
	private static String[] makeRuleNames() {
		return new String[] {
			"stylesheet", "statement", "ruleset", "selectorList", "selector", "combinator", 
			"simpleSelector", "typeSelector", "universalSelector", "idSelector", 
			"classSelector", "attributeSelector", "attributeOperator", "pseudoSelector", 
			"pseudoClass", "pseudoClassArgument", "pseudoElement", "declaration", 
			"property", "value", "operator", "term", "unaryOperator", "numeric", 
			"percentage", "length", "angle", "time", "frequency", "resolution", "hexcolor", 
			"function", "functionArguments", "functionArgument", "calc", "calcExpression", 
			"calcTerm", "calcFactor", "atRule", "atImport", "atMedia", "mediaQueryList", 
			"mediaQuery", "mediaType", "mediaFeature", "atKeyframes", "keyframeBlock", 
			"keyframeSelector", "atFontFace", "atSupports", "supportsCondition", 
			"supportsNegation", "supportsConjunction", "supportsDisjunction", "supportsInParens", 
			"supportsFeature", "atPage", "pseudoPage", "atNamespace", "atCharset", 
			"atViewport", "atCounterStyle", "atFontFeatureValues", "fontFamilyName", 
			"fontFeatureValueBlock", "atProperty", "expression", "comment"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'{'", "'}'", "','", "'>'", "'+'", "'~'", "'*'", "'#'", "'.'", 
			"'['", "']'", "'='", "'~='", "'|='", "'^='", "'$='", "'*='", "':'", "'('", 
			"')'", "'is'", "'where'", "'has'", "'::'", "';'", "'-'", "'/'", "'%'", 
			"'calc'", "'@'", null, "'@import'", "'@media'", "'@keyframes'", "'@font-face'", 
			"'@supports'", "'@page'", "'@namespace'", "'@charset'", "'@viewport'", 
			"'@counter-style'", "'@font-feature-values'", "'@property'", "'only'", 
			"'not'", "'and'", "'or'", "'from'", "'to'", "'!important'", "'px'", "'em'", 
			"'rem'", "'vh'", "'vw'", "'vmin'", "'vmax'", "'ch'", "'ex'", "'cm'", 
			"'mm'", "'in'", "'pt'", "'pc'", "'deg'", "'rad'", "'grad'", "'turn'", 
			"'s'", "'ms'", "'Hz'", "'kHz'", "'dpi'", "'dpcm'", "'dppx'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, "COMMENT", "IMPORT", "MEDIA", 
			"KEYFRAMES", "FONT_FACE", "SUPPORTS", "PAGE", "NAMESPACE", "CHARSET", 
			"VIEWPORT", "COUNTER_STYLE", "FONT_FEATURE_VALUES", "PROPERTY", "ONLY", 
			"NOT", "AND", "OR", "FROM", "TO", "IMPORTANT", "PX", "EM", "REM", "VH", 
			"VW", "VMIN", "VMAX", "CH", "EX", "CM", "MM", "IN", "PT", "PC", "DEG", 
			"RAD", "GRAD", "TURN", "S", "MS", "HZ", "KHZ", "DPI", "DPCM", "DPPX", 
			"VARIABLE", "NUMBER", "STRING_LITERAL", "URI", "IDENTIFIER", "HEX_DIGIT", 
			"WS"
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
	public String getGrammarFileName() { return "CSS.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CSSParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StylesheetContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(CSSParser.EOF, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public StylesheetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stylesheet; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterStylesheet(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitStylesheet(this);
		}
	}

	public final StylesheetContext stylesheet() throws RecognitionException {
		StylesheetContext _localctx = new StylesheetContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_stylesheet);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(139);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 17590055602170L) != 0) || _la==IDENTIFIER || _la==WS) {
				{
				{
				setState(136);
				statement();
				}
				}
				setState(141);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(142);
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
		public RulesetContext ruleset() {
			return getRuleContext(RulesetContext.class,0);
		}
		public AtRuleContext atRule() {
			return getRuleContext(AtRuleContext.class,0);
		}
		public CommentContext comment() {
			return getRuleContext(CommentContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitStatement(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_statement);
		try {
			setState(147);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__0:
			case T__2:
			case T__3:
			case T__4:
			case T__5:
			case T__6:
			case T__7:
			case T__8:
			case T__9:
			case T__17:
			case T__23:
			case IDENTIFIER:
			case WS:
				enterOuterAlt(_localctx, 1);
				{
				setState(144);
				ruleset();
				}
				break;
			case IMPORT:
			case MEDIA:
			case KEYFRAMES:
			case FONT_FACE:
			case SUPPORTS:
			case PAGE:
			case NAMESPACE:
			case CHARSET:
			case VIEWPORT:
			case COUNTER_STYLE:
			case FONT_FEATURE_VALUES:
			case PROPERTY:
				enterOuterAlt(_localctx, 2);
				{
				setState(145);
				atRule();
				}
				break;
			case COMMENT:
				enterOuterAlt(_localctx, 3);
				{
				setState(146);
				comment();
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
	public static class RulesetContext extends ParserRuleContext {
		public SelectorListContext selectorList() {
			return getRuleContext(SelectorListContext.class,0);
		}
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public RulesetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ruleset; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterRuleset(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitRuleset(this);
		}
	}

	public final RulesetContext ruleset() throws RecognitionException {
		RulesetContext _localctx = new RulesetContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_ruleset);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(149);
			selectorList();
			setState(150);
			match(T__0);
			setState(154);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE || _la==IDENTIFIER) {
				{
				{
				setState(151);
				declaration();
				}
				}
				setState(156);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(157);
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
	public static class SelectorListContext extends ParserRuleContext {
		public List<SelectorContext> selector() {
			return getRuleContexts(SelectorContext.class);
		}
		public SelectorContext selector(int i) {
			return getRuleContext(SelectorContext.class,i);
		}
		public SelectorListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_selectorList; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSelectorList(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSelectorList(this);
		}
	}

	public final SelectorListContext selectorList() throws RecognitionException {
		SelectorListContext _localctx = new SelectorListContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_selectorList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(159);
			selector();
			setState(164);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__2) {
				{
				{
				setState(160);
				match(T__2);
				setState(161);
				selector();
				}
				}
				setState(166);
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
	public static class SelectorContext extends ParserRuleContext {
		public List<SimpleSelectorContext> simpleSelector() {
			return getRuleContexts(SimpleSelectorContext.class);
		}
		public SimpleSelectorContext simpleSelector(int i) {
			return getRuleContext(SimpleSelectorContext.class,i);
		}
		public List<CombinatorContext> combinator() {
			return getRuleContexts(CombinatorContext.class);
		}
		public CombinatorContext combinator(int i) {
			return getRuleContext(CombinatorContext.class,i);
		}
		public SelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_selector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSelector(this);
		}
	}

	public final SelectorContext selector() throws RecognitionException {
		SelectorContext _localctx = new SelectorContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_selector);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(167);
			simpleSelector();
			setState(173);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 112L) != 0) || _la==WS) {
				{
				{
				setState(168);
				combinator();
				setState(169);
				simpleSelector();
				}
				}
				setState(175);
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
	public static class CombinatorContext extends ParserRuleContext {
		public TerminalNode WS() { return getToken(CSSParser.WS, 0); }
		public CombinatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_combinator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterCombinator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitCombinator(this);
		}
	}

	public final CombinatorContext combinator() throws RecognitionException {
		CombinatorContext _localctx = new CombinatorContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_combinator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(176);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 112L) != 0) || _la==WS) ) {
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
	public static class SimpleSelectorContext extends ParserRuleContext {
		public TypeSelectorContext typeSelector() {
			return getRuleContext(TypeSelectorContext.class,0);
		}
		public UniversalSelectorContext universalSelector() {
			return getRuleContext(UniversalSelectorContext.class,0);
		}
		public List<IdSelectorContext> idSelector() {
			return getRuleContexts(IdSelectorContext.class);
		}
		public IdSelectorContext idSelector(int i) {
			return getRuleContext(IdSelectorContext.class,i);
		}
		public List<ClassSelectorContext> classSelector() {
			return getRuleContexts(ClassSelectorContext.class);
		}
		public ClassSelectorContext classSelector(int i) {
			return getRuleContext(ClassSelectorContext.class,i);
		}
		public List<AttributeSelectorContext> attributeSelector() {
			return getRuleContexts(AttributeSelectorContext.class);
		}
		public AttributeSelectorContext attributeSelector(int i) {
			return getRuleContext(AttributeSelectorContext.class,i);
		}
		public List<PseudoSelectorContext> pseudoSelector() {
			return getRuleContexts(PseudoSelectorContext.class);
		}
		public PseudoSelectorContext pseudoSelector(int i) {
			return getRuleContext(PseudoSelectorContext.class,i);
		}
		public SimpleSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_simpleSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSimpleSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSimpleSelector(this);
		}
	}

	public final SimpleSelectorContext simpleSelector() throws RecognitionException {
		SimpleSelectorContext _localctx = new SimpleSelectorContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_simpleSelector);
		int _la;
		try {
			setState(199);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(180);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case IDENTIFIER:
					{
					setState(178);
					typeSelector();
					}
					break;
				case T__6:
					{
					setState(179);
					universalSelector();
					}
					break;
				case T__0:
				case T__2:
				case T__3:
				case T__4:
				case T__5:
				case T__7:
				case T__8:
				case T__9:
				case T__17:
				case T__19:
				case T__23:
				case WS:
					break;
				default:
					break;
				}
				setState(188);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 17041152L) != 0)) {
					{
					setState(186);
					_errHandler.sync(this);
					switch (_input.LA(1)) {
					case T__7:
						{
						setState(182);
						idSelector();
						}
						break;
					case T__8:
						{
						setState(183);
						classSelector();
						}
						break;
					case T__9:
						{
						setState(184);
						attributeSelector();
						}
						break;
					case T__17:
					case T__23:
						{
						setState(185);
						pseudoSelector();
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					}
					setState(190);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(195); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					setState(195);
					_errHandler.sync(this);
					switch (_input.LA(1)) {
					case T__7:
						{
						setState(191);
						idSelector();
						}
						break;
					case T__8:
						{
						setState(192);
						classSelector();
						}
						break;
					case T__9:
						{
						setState(193);
						attributeSelector();
						}
						break;
					case T__17:
					case T__23:
						{
						setState(194);
						pseudoSelector();
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					}
					setState(197); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & 17041152L) != 0) );
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
	public static class TypeSelectorContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public TypeSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterTypeSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitTypeSelector(this);
		}
	}

	public final TypeSelectorContext typeSelector() throws RecognitionException {
		TypeSelectorContext _localctx = new TypeSelectorContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_typeSelector);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(201);
			match(IDENTIFIER);
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
	public static class UniversalSelectorContext extends ParserRuleContext {
		public UniversalSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_universalSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterUniversalSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitUniversalSelector(this);
		}
	}

	public final UniversalSelectorContext universalSelector() throws RecognitionException {
		UniversalSelectorContext _localctx = new UniversalSelectorContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_universalSelector);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(203);
			match(T__6);
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
	public static class IdSelectorContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public IdSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_idSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterIdSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitIdSelector(this);
		}
	}

	public final IdSelectorContext idSelector() throws RecognitionException {
		IdSelectorContext _localctx = new IdSelectorContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_idSelector);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(205);
			match(T__7);
			setState(206);
			match(IDENTIFIER);
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
	public static class ClassSelectorContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public ClassSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterClassSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitClassSelector(this);
		}
	}

	public final ClassSelectorContext classSelector() throws RecognitionException {
		ClassSelectorContext _localctx = new ClassSelectorContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_classSelector);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(208);
			match(T__8);
			setState(209);
			match(IDENTIFIER);
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
	public static class AttributeSelectorContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(CSSParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(CSSParser.IDENTIFIER, i);
		}
		public AttributeOperatorContext attributeOperator() {
			return getRuleContext(AttributeOperatorContext.class,0);
		}
		public TerminalNode STRING_LITERAL() { return getToken(CSSParser.STRING_LITERAL, 0); }
		public AttributeSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attributeSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAttributeSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAttributeSelector(this);
		}
	}

	public final AttributeSelectorContext attributeSelector() throws RecognitionException {
		AttributeSelectorContext _localctx = new AttributeSelectorContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_attributeSelector);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(211);
			match(T__9);
			setState(212);
			match(IDENTIFIER);
			setState(216);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258048L) != 0)) {
				{
				setState(213);
				attributeOperator();
				setState(214);
				_la = _input.LA(1);
				if ( !(_la==STRING_LITERAL || _la==IDENTIFIER) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
			}

			setState(218);
			match(T__10);
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
	public static class AttributeOperatorContext extends ParserRuleContext {
		public AttributeOperatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attributeOperator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAttributeOperator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAttributeOperator(this);
		}
	}

	public final AttributeOperatorContext attributeOperator() throws RecognitionException {
		AttributeOperatorContext _localctx = new AttributeOperatorContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_attributeOperator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(220);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 258048L) != 0)) ) {
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
	public static class PseudoSelectorContext extends ParserRuleContext {
		public PseudoClassContext pseudoClass() {
			return getRuleContext(PseudoClassContext.class,0);
		}
		public PseudoElementContext pseudoElement() {
			return getRuleContext(PseudoElementContext.class,0);
		}
		public PseudoSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pseudoSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterPseudoSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitPseudoSelector(this);
		}
	}

	public final PseudoSelectorContext pseudoSelector() throws RecognitionException {
		PseudoSelectorContext _localctx = new PseudoSelectorContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_pseudoSelector);
		try {
			setState(224);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__17:
				enterOuterAlt(_localctx, 1);
				{
				setState(222);
				pseudoClass();
				}
				break;
			case T__23:
				enterOuterAlt(_localctx, 2);
				{
				setState(223);
				pseudoElement();
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
	public static class PseudoClassContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public PseudoClassArgumentContext pseudoClassArgument() {
			return getRuleContext(PseudoClassArgumentContext.class,0);
		}
		public TerminalNode NOT() { return getToken(CSSParser.NOT, 0); }
		public SelectorListContext selectorList() {
			return getRuleContext(SelectorListContext.class,0);
		}
		public PseudoClassContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pseudoClass; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterPseudoClass(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitPseudoClass(this);
		}
	}

	public final PseudoClassContext pseudoClass() throws RecognitionException {
		PseudoClassContext _localctx = new PseudoClassContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_pseudoClass);
		int _la;
		try {
			setState(246);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(226);
				match(T__17);
				setState(227);
				match(IDENTIFIER);
				setState(232);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__18) {
					{
					setState(228);
					match(T__18);
					setState(229);
					pseudoClassArgument();
					setState(230);
					match(T__19);
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(234);
				match(T__17);
				setState(235);
				match(NOT);
				setState(236);
				match(T__18);
				setState(237);
				selectorList();
				setState(238);
				match(T__19);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(240);
				match(T__17);
				setState(241);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 14680064L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(242);
				match(T__18);
				setState(243);
				selectorList();
				setState(244);
				match(T__19);
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
	public static class PseudoClassArgumentContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public TerminalNode NUMBER() { return getToken(CSSParser.NUMBER, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(CSSParser.STRING_LITERAL, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public PseudoClassArgumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pseudoClassArgument; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterPseudoClassArgument(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitPseudoClassArgument(this);
		}
	}

	public final PseudoClassArgumentContext pseudoClassArgument() throws RecognitionException {
		PseudoClassArgumentContext _localctx = new PseudoClassArgumentContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_pseudoClassArgument);
		try {
			setState(252);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(248);
				match(IDENTIFIER);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(249);
				match(NUMBER);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(250);
				match(STRING_LITERAL);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(251);
				expression();
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
	public static class PseudoElementContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public PseudoElementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pseudoElement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterPseudoElement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitPseudoElement(this);
		}
	}

	public final PseudoElementContext pseudoElement() throws RecognitionException {
		PseudoElementContext _localctx = new PseudoElementContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_pseudoElement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(254);
			match(T__23);
			setState(255);
			match(IDENTIFIER);
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
	public static class DeclarationContext extends ParserRuleContext {
		public PropertyContext property() {
			return getRuleContext(PropertyContext.class,0);
		}
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public TerminalNode IMPORTANT() { return getToken(CSSParser.IMPORTANT, 0); }
		public DeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitDeclaration(this);
		}
	}

	public final DeclarationContext declaration() throws RecognitionException {
		DeclarationContext _localctx = new DeclarationContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_declaration);
		int _la;
		try {
			setState(271);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(257);
				property();
				setState(258);
				match(T__17);
				setState(259);
				value();
				setState(261);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==IMPORTANT) {
					{
					setState(260);
					match(IMPORTANT);
					}
				}

				setState(263);
				match(T__24);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(265);
				property();
				setState(266);
				match(T__17);
				setState(267);
				value();
				setState(269);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==IMPORTANT) {
					{
					setState(268);
					match(IMPORTANT);
					}
				}

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
	public static class PropertyContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(CSSParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(CSSParser.IDENTIFIER, i);
		}
		public TerminalNode VARIABLE() { return getToken(CSSParser.VARIABLE, 0); }
		public PropertyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterProperty(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitProperty(this);
		}
	}

	public final PropertyContext property() throws RecognitionException {
		PropertyContext _localctx = new PropertyContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_property);
		int _la;
		try {
			setState(282);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(273);
				match(IDENTIFIER);
				setState(278);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__25) {
					{
					{
					setState(274);
					match(T__25);
					setState(275);
					match(IDENTIFIER);
					}
					}
					setState(280);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			case VARIABLE:
				enterOuterAlt(_localctx, 2);
				{
				setState(281);
				match(VARIABLE);
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
	public static class ValueContext extends ParserRuleContext {
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public List<OperatorContext> operator() {
			return getRuleContexts(OperatorContext.class);
		}
		public OperatorContext operator(int i) {
			return getRuleContext(OperatorContext.class,i);
		}
		public ValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterValue(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitValue(this);
		}
	}

	public final ValueContext value() throws RecognitionException {
		ValueContext _localctx = new ValueContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_value);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(284);
			term();
			setState(291);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,22,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(286);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==T__2 || _la==T__26 || _la==WS) {
						{
						setState(285);
						operator();
						}
					}

					setState(288);
					term();
					}
					} 
				}
				setState(293);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,22,_ctx);
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
	public static class OperatorContext extends ParserRuleContext {
		public TerminalNode WS() { return getToken(CSSParser.WS, 0); }
		public OperatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_operator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterOperator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitOperator(this);
		}
	}

	public final OperatorContext operator() throws RecognitionException {
		OperatorContext _localctx = new OperatorContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_operator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(294);
			_la = _input.LA(1);
			if ( !(_la==T__2 || _la==T__26 || _la==WS) ) {
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
	public static class TermContext extends ParserRuleContext {
		public NumericContext numeric() {
			return getRuleContext(NumericContext.class,0);
		}
		public PercentageContext percentage() {
			return getRuleContext(PercentageContext.class,0);
		}
		public LengthContext length() {
			return getRuleContext(LengthContext.class,0);
		}
		public AngleContext angle() {
			return getRuleContext(AngleContext.class,0);
		}
		public TimeContext time() {
			return getRuleContext(TimeContext.class,0);
		}
		public FrequencyContext frequency() {
			return getRuleContext(FrequencyContext.class,0);
		}
		public ResolutionContext resolution() {
			return getRuleContext(ResolutionContext.class,0);
		}
		public UnaryOperatorContext unaryOperator() {
			return getRuleContext(UnaryOperatorContext.class,0);
		}
		public TerminalNode STRING_LITERAL() { return getToken(CSSParser.STRING_LITERAL, 0); }
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public TerminalNode URI() { return getToken(CSSParser.URI, 0); }
		public HexcolorContext hexcolor() {
			return getRuleContext(HexcolorContext.class,0);
		}
		public FunctionContext function() {
			return getRuleContext(FunctionContext.class,0);
		}
		public TerminalNode VARIABLE() { return getToken(CSSParser.VARIABLE, 0); }
		public CalcContext calc() {
			return getRuleContext(CalcContext.class,0);
		}
		public TermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterTerm(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitTerm(this);
		}
	}

	public final TermContext term() throws RecognitionException {
		TermContext _localctx = new TermContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_term);
		int _la;
		try {
			setState(315);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,25,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(297);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__4 || _la==T__25) {
					{
					setState(296);
					unaryOperator();
					}
				}

				setState(306);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,24,_ctx) ) {
				case 1:
					{
					setState(299);
					numeric();
					}
					break;
				case 2:
					{
					setState(300);
					percentage();
					}
					break;
				case 3:
					{
					setState(301);
					length();
					}
					break;
				case 4:
					{
					setState(302);
					angle();
					}
					break;
				case 5:
					{
					setState(303);
					time();
					}
					break;
				case 6:
					{
					setState(304);
					frequency();
					}
					break;
				case 7:
					{
					setState(305);
					resolution();
					}
					break;
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(308);
				match(STRING_LITERAL);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(309);
				match(IDENTIFIER);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(310);
				match(URI);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(311);
				hexcolor();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(312);
				function();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(313);
				match(VARIABLE);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(314);
				calc();
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
	public static class UnaryOperatorContext extends ParserRuleContext {
		public UnaryOperatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unaryOperator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterUnaryOperator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitUnaryOperator(this);
		}
	}

	public final UnaryOperatorContext unaryOperator() throws RecognitionException {
		UnaryOperatorContext _localctx = new UnaryOperatorContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_unaryOperator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(317);
			_la = _input.LA(1);
			if ( !(_la==T__4 || _la==T__25) ) {
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
	public static class NumericContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(CSSParser.NUMBER, 0); }
		public NumericContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_numeric; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterNumeric(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitNumeric(this);
		}
	}

	public final NumericContext numeric() throws RecognitionException {
		NumericContext _localctx = new NumericContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_numeric);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(319);
			match(NUMBER);
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
	public static class PercentageContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(CSSParser.NUMBER, 0); }
		public PercentageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_percentage; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterPercentage(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitPercentage(this);
		}
	}

	public final PercentageContext percentage() throws RecognitionException {
		PercentageContext _localctx = new PercentageContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_percentage);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(321);
			match(NUMBER);
			setState(322);
			match(T__27);
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
	public static class LengthContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(CSSParser.NUMBER, 0); }
		public TerminalNode PX() { return getToken(CSSParser.PX, 0); }
		public TerminalNode EM() { return getToken(CSSParser.EM, 0); }
		public TerminalNode REM() { return getToken(CSSParser.REM, 0); }
		public TerminalNode VH() { return getToken(CSSParser.VH, 0); }
		public TerminalNode VW() { return getToken(CSSParser.VW, 0); }
		public TerminalNode VMIN() { return getToken(CSSParser.VMIN, 0); }
		public TerminalNode VMAX() { return getToken(CSSParser.VMAX, 0); }
		public TerminalNode CH() { return getToken(CSSParser.CH, 0); }
		public TerminalNode EX() { return getToken(CSSParser.EX, 0); }
		public TerminalNode CM() { return getToken(CSSParser.CM, 0); }
		public TerminalNode MM() { return getToken(CSSParser.MM, 0); }
		public TerminalNode IN() { return getToken(CSSParser.IN, 0); }
		public TerminalNode PT() { return getToken(CSSParser.PT, 0); }
		public TerminalNode PC() { return getToken(CSSParser.PC, 0); }
		public LengthContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_length; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterLength(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitLength(this);
		}
	}

	public final LengthContext length() throws RecognitionException {
		LengthContext _localctx = new LengthContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_length);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(324);
			match(NUMBER);
			setState(325);
			_la = _input.LA(1);
			if ( !(((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & 16383L) != 0)) ) {
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
	public static class AngleContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(CSSParser.NUMBER, 0); }
		public TerminalNode DEG() { return getToken(CSSParser.DEG, 0); }
		public TerminalNode RAD() { return getToken(CSSParser.RAD, 0); }
		public TerminalNode GRAD() { return getToken(CSSParser.GRAD, 0); }
		public TerminalNode TURN() { return getToken(CSSParser.TURN, 0); }
		public AngleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_angle; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAngle(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAngle(this);
		}
	}

	public final AngleContext angle() throws RecognitionException {
		AngleContext _localctx = new AngleContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_angle);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(327);
			match(NUMBER);
			setState(328);
			_la = _input.LA(1);
			if ( !(((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & 15L) != 0)) ) {
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
	public static class TimeContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(CSSParser.NUMBER, 0); }
		public TerminalNode S() { return getToken(CSSParser.S, 0); }
		public TerminalNode MS() { return getToken(CSSParser.MS, 0); }
		public TimeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_time; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterTime(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitTime(this);
		}
	}

	public final TimeContext time() throws RecognitionException {
		TimeContext _localctx = new TimeContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_time);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(330);
			match(NUMBER);
			setState(331);
			_la = _input.LA(1);
			if ( !(_la==S || _la==MS) ) {
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
	public static class FrequencyContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(CSSParser.NUMBER, 0); }
		public TerminalNode HZ() { return getToken(CSSParser.HZ, 0); }
		public TerminalNode KHZ() { return getToken(CSSParser.KHZ, 0); }
		public FrequencyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_frequency; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterFrequency(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitFrequency(this);
		}
	}

	public final FrequencyContext frequency() throws RecognitionException {
		FrequencyContext _localctx = new FrequencyContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_frequency);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(333);
			match(NUMBER);
			setState(334);
			_la = _input.LA(1);
			if ( !(_la==HZ || _la==KHZ) ) {
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
	public static class ResolutionContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(CSSParser.NUMBER, 0); }
		public TerminalNode DPI() { return getToken(CSSParser.DPI, 0); }
		public TerminalNode DPCM() { return getToken(CSSParser.DPCM, 0); }
		public TerminalNode DPPX() { return getToken(CSSParser.DPPX, 0); }
		public ResolutionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_resolution; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterResolution(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitResolution(this);
		}
	}

	public final ResolutionContext resolution() throws RecognitionException {
		ResolutionContext _localctx = new ResolutionContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_resolution);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(336);
			match(NUMBER);
			setState(337);
			_la = _input.LA(1);
			if ( !(((((_la - 73)) & ~0x3f) == 0 && ((1L << (_la - 73)) & 7L) != 0)) ) {
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
	public static class HexcolorContext extends ParserRuleContext {
		public List<TerminalNode> HEX_DIGIT() { return getTokens(CSSParser.HEX_DIGIT); }
		public TerminalNode HEX_DIGIT(int i) {
			return getToken(CSSParser.HEX_DIGIT, i);
		}
		public HexcolorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_hexcolor; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterHexcolor(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitHexcolor(this);
		}
	}

	public final HexcolorContext hexcolor() throws RecognitionException {
		HexcolorContext _localctx = new HexcolorContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_hexcolor);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(339);
			match(T__7);
			setState(341); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(340);
				match(HEX_DIGIT);
				}
				}
				setState(343); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==HEX_DIGIT );
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
	public static class FunctionContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public FunctionArgumentsContext functionArguments() {
			return getRuleContext(FunctionArgumentsContext.class,0);
		}
		public FunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterFunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitFunction(this);
		}
	}

	public final FunctionContext function() throws RecognitionException {
		FunctionContext _localctx = new FunctionContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_function);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(345);
			match(IDENTIFIER);
			setState(346);
			match(T__18);
			setState(348);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 603980064L) != 0) || ((((_la - 76)) & ~0x3f) == 0 && ((1L << (_la - 76)) & 31L) != 0)) {
				{
				setState(347);
				functionArguments();
				}
			}

			setState(350);
			match(T__19);
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
	public static class FunctionArgumentsContext extends ParserRuleContext {
		public List<FunctionArgumentContext> functionArgument() {
			return getRuleContexts(FunctionArgumentContext.class);
		}
		public FunctionArgumentContext functionArgument(int i) {
			return getRuleContext(FunctionArgumentContext.class,i);
		}
		public FunctionArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionArguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterFunctionArguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitFunctionArguments(this);
		}
	}

	public final FunctionArgumentsContext functionArguments() throws RecognitionException {
		FunctionArgumentsContext _localctx = new FunctionArgumentsContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_functionArguments);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(352);
			functionArgument();
			setState(357);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__2) {
				{
				{
				setState(353);
				match(T__2);
				setState(354);
				functionArgument();
				}
				}
				setState(359);
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
	public static class FunctionArgumentContext extends ParserRuleContext {
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public FunctionArgumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionArgument; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterFunctionArgument(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitFunctionArgument(this);
		}
	}

	public final FunctionArgumentContext functionArgument() throws RecognitionException {
		FunctionArgumentContext _localctx = new FunctionArgumentContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_functionArgument);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(360);
			value();
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
	public static class CalcContext extends ParserRuleContext {
		public CalcExpressionContext calcExpression() {
			return getRuleContext(CalcExpressionContext.class,0);
		}
		public CalcContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_calc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterCalc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitCalc(this);
		}
	}

	public final CalcContext calc() throws RecognitionException {
		CalcContext _localctx = new CalcContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_calc);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(362);
			match(T__28);
			setState(363);
			match(T__18);
			setState(364);
			calcExpression();
			setState(365);
			match(T__19);
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
	public static class CalcExpressionContext extends ParserRuleContext {
		public List<CalcTermContext> calcTerm() {
			return getRuleContexts(CalcTermContext.class);
		}
		public CalcTermContext calcTerm(int i) {
			return getRuleContext(CalcTermContext.class,i);
		}
		public CalcExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_calcExpression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterCalcExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitCalcExpression(this);
		}
	}

	public final CalcExpressionContext calcExpression() throws RecognitionException {
		CalcExpressionContext _localctx = new CalcExpressionContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_calcExpression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(367);
			calcTerm();
			setState(372);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__4 || _la==T__25) {
				{
				{
				setState(368);
				_la = _input.LA(1);
				if ( !(_la==T__4 || _la==T__25) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(369);
				calcTerm();
				}
				}
				setState(374);
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
	public static class CalcTermContext extends ParserRuleContext {
		public List<CalcFactorContext> calcFactor() {
			return getRuleContexts(CalcFactorContext.class);
		}
		public CalcFactorContext calcFactor(int i) {
			return getRuleContext(CalcFactorContext.class,i);
		}
		public CalcTermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_calcTerm; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterCalcTerm(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitCalcTerm(this);
		}
	}

	public final CalcTermContext calcTerm() throws RecognitionException {
		CalcTermContext _localctx = new CalcTermContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_calcTerm);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(375);
			calcFactor();
			setState(380);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__6 || _la==T__26) {
				{
				{
				setState(376);
				_la = _input.LA(1);
				if ( !(_la==T__6 || _la==T__26) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(377);
				calcFactor();
				}
				}
				setState(382);
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
	public static class CalcFactorContext extends ParserRuleContext {
		public NumericContext numeric() {
			return getRuleContext(NumericContext.class,0);
		}
		public LengthContext length() {
			return getRuleContext(LengthContext.class,0);
		}
		public PercentageContext percentage() {
			return getRuleContext(PercentageContext.class,0);
		}
		public CalcExpressionContext calcExpression() {
			return getRuleContext(CalcExpressionContext.class,0);
		}
		public CalcContext calc() {
			return getRuleContext(CalcContext.class,0);
		}
		public TerminalNode VARIABLE() { return getToken(CSSParser.VARIABLE, 0); }
		public CalcFactorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_calcFactor; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterCalcFactor(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitCalcFactor(this);
		}
	}

	public final CalcFactorContext calcFactor() throws RecognitionException {
		CalcFactorContext _localctx = new CalcFactorContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_calcFactor);
		try {
			setState(392);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,31,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(383);
				numeric();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(384);
				length();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(385);
				percentage();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(386);
				match(T__18);
				setState(387);
				calcExpression();
				setState(388);
				match(T__19);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(390);
				calc();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(391);
				match(VARIABLE);
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
	public static class AtRuleContext extends ParserRuleContext {
		public AtImportContext atImport() {
			return getRuleContext(AtImportContext.class,0);
		}
		public AtMediaContext atMedia() {
			return getRuleContext(AtMediaContext.class,0);
		}
		public AtKeyframesContext atKeyframes() {
			return getRuleContext(AtKeyframesContext.class,0);
		}
		public AtFontFaceContext atFontFace() {
			return getRuleContext(AtFontFaceContext.class,0);
		}
		public AtSupportsContext atSupports() {
			return getRuleContext(AtSupportsContext.class,0);
		}
		public AtPageContext atPage() {
			return getRuleContext(AtPageContext.class,0);
		}
		public AtNamespaceContext atNamespace() {
			return getRuleContext(AtNamespaceContext.class,0);
		}
		public AtCharsetContext atCharset() {
			return getRuleContext(AtCharsetContext.class,0);
		}
		public AtViewportContext atViewport() {
			return getRuleContext(AtViewportContext.class,0);
		}
		public AtCounterStyleContext atCounterStyle() {
			return getRuleContext(AtCounterStyleContext.class,0);
		}
		public AtFontFeatureValuesContext atFontFeatureValues() {
			return getRuleContext(AtFontFeatureValuesContext.class,0);
		}
		public AtPropertyContext atProperty() {
			return getRuleContext(AtPropertyContext.class,0);
		}
		public AtRuleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atRule; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtRule(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtRule(this);
		}
	}

	public final AtRuleContext atRule() throws RecognitionException {
		AtRuleContext _localctx = new AtRuleContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_atRule);
		try {
			setState(406);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IMPORT:
				enterOuterAlt(_localctx, 1);
				{
				setState(394);
				atImport();
				}
				break;
			case MEDIA:
				enterOuterAlt(_localctx, 2);
				{
				setState(395);
				atMedia();
				}
				break;
			case KEYFRAMES:
				enterOuterAlt(_localctx, 3);
				{
				setState(396);
				atKeyframes();
				}
				break;
			case FONT_FACE:
				enterOuterAlt(_localctx, 4);
				{
				setState(397);
				atFontFace();
				}
				break;
			case SUPPORTS:
				enterOuterAlt(_localctx, 5);
				{
				setState(398);
				atSupports();
				}
				break;
			case PAGE:
				enterOuterAlt(_localctx, 6);
				{
				setState(399);
				atPage();
				}
				break;
			case NAMESPACE:
				enterOuterAlt(_localctx, 7);
				{
				setState(400);
				atNamespace();
				}
				break;
			case CHARSET:
				enterOuterAlt(_localctx, 8);
				{
				setState(401);
				atCharset();
				}
				break;
			case VIEWPORT:
				enterOuterAlt(_localctx, 9);
				{
				setState(402);
				atViewport();
				}
				break;
			case COUNTER_STYLE:
				enterOuterAlt(_localctx, 10);
				{
				setState(403);
				atCounterStyle();
				}
				break;
			case FONT_FEATURE_VALUES:
				enterOuterAlt(_localctx, 11);
				{
				setState(404);
				atFontFeatureValues();
				}
				break;
			case PROPERTY:
				enterOuterAlt(_localctx, 12);
				{
				setState(405);
				atProperty();
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
	public static class AtImportContext extends ParserRuleContext {
		public TerminalNode IMPORT() { return getToken(CSSParser.IMPORT, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(CSSParser.STRING_LITERAL, 0); }
		public TerminalNode URI() { return getToken(CSSParser.URI, 0); }
		public MediaQueryListContext mediaQueryList() {
			return getRuleContext(MediaQueryListContext.class,0);
		}
		public AtImportContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atImport; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtImport(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtImport(this);
		}
	}

	public final AtImportContext atImport() throws RecognitionException {
		AtImportContext _localctx = new AtImportContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_atImport);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(408);
			match(IMPORT);
			setState(409);
			_la = _input.LA(1);
			if ( !(_la==STRING_LITERAL || _la==URI) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(411);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 19)) & ~0x3f) == 0 && ((1L << (_la - 19)) & 2305843009314357249L) != 0)) {
				{
				setState(410);
				mediaQueryList();
				}
			}

			setState(413);
			match(T__24);
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
	public static class AtMediaContext extends ParserRuleContext {
		public TerminalNode MEDIA() { return getToken(CSSParser.MEDIA, 0); }
		public MediaQueryListContext mediaQueryList() {
			return getRuleContext(MediaQueryListContext.class,0);
		}
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public AtMediaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atMedia; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtMedia(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtMedia(this);
		}
	}

	public final AtMediaContext atMedia() throws RecognitionException {
		AtMediaContext _localctx = new AtMediaContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_atMedia);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(415);
			match(MEDIA);
			setState(416);
			mediaQueryList();
			setState(417);
			match(T__0);
			setState(421);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 17590055602170L) != 0) || _la==IDENTIFIER || _la==WS) {
				{
				{
				setState(418);
				statement();
				}
				}
				setState(423);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(424);
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
	public static class MediaQueryListContext extends ParserRuleContext {
		public List<MediaQueryContext> mediaQuery() {
			return getRuleContexts(MediaQueryContext.class);
		}
		public MediaQueryContext mediaQuery(int i) {
			return getRuleContext(MediaQueryContext.class,i);
		}
		public MediaQueryListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mediaQueryList; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterMediaQueryList(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitMediaQueryList(this);
		}
	}

	public final MediaQueryListContext mediaQueryList() throws RecognitionException {
		MediaQueryListContext _localctx = new MediaQueryListContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_mediaQueryList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(426);
			mediaQuery();
			setState(431);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__2) {
				{
				{
				setState(427);
				match(T__2);
				setState(428);
				mediaQuery();
				}
				}
				setState(433);
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
	public static class MediaQueryContext extends ParserRuleContext {
		public MediaTypeContext mediaType() {
			return getRuleContext(MediaTypeContext.class,0);
		}
		public List<TerminalNode> AND() { return getTokens(CSSParser.AND); }
		public TerminalNode AND(int i) {
			return getToken(CSSParser.AND, i);
		}
		public List<MediaFeatureContext> mediaFeature() {
			return getRuleContexts(MediaFeatureContext.class);
		}
		public MediaFeatureContext mediaFeature(int i) {
			return getRuleContext(MediaFeatureContext.class,i);
		}
		public TerminalNode ONLY() { return getToken(CSSParser.ONLY, 0); }
		public TerminalNode NOT() { return getToken(CSSParser.NOT, 0); }
		public MediaQueryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mediaQuery; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterMediaQuery(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitMediaQuery(this);
		}
	}

	public final MediaQueryContext mediaQuery() throws RecognitionException {
		MediaQueryContext _localctx = new MediaQueryContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_mediaQuery);
		int _la;
		try {
			setState(453);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case ONLY:
			case NOT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(435);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==ONLY || _la==NOT) {
					{
					setState(434);
					_la = _input.LA(1);
					if ( !(_la==ONLY || _la==NOT) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					}
				}

				setState(437);
				mediaType();
				setState(442);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==AND) {
					{
					{
					setState(438);
					match(AND);
					setState(439);
					mediaFeature();
					}
					}
					setState(444);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			case T__18:
				enterOuterAlt(_localctx, 2);
				{
				setState(445);
				mediaFeature();
				setState(450);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==AND) {
					{
					{
					setState(446);
					match(AND);
					setState(447);
					mediaFeature();
					}
					}
					setState(452);
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
	public static class MediaTypeContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public MediaTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mediaType; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterMediaType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitMediaType(this);
		}
	}

	public final MediaTypeContext mediaType() throws RecognitionException {
		MediaTypeContext _localctx = new MediaTypeContext(_ctx, getState());
		enterRule(_localctx, 86, RULE_mediaType);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(455);
			match(IDENTIFIER);
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
	public static class MediaFeatureContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public MediaFeatureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mediaFeature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterMediaFeature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitMediaFeature(this);
		}
	}

	public final MediaFeatureContext mediaFeature() throws RecognitionException {
		MediaFeatureContext _localctx = new MediaFeatureContext(_ctx, getState());
		enterRule(_localctx, 88, RULE_mediaFeature);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(457);
			match(T__18);
			setState(458);
			match(IDENTIFIER);
			setState(461);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__17) {
				{
				setState(459);
				match(T__17);
				setState(460);
				value();
				}
			}

			setState(463);
			match(T__19);
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
	public static class AtKeyframesContext extends ParserRuleContext {
		public TerminalNode KEYFRAMES() { return getToken(CSSParser.KEYFRAMES, 0); }
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public List<KeyframeBlockContext> keyframeBlock() {
			return getRuleContexts(KeyframeBlockContext.class);
		}
		public KeyframeBlockContext keyframeBlock(int i) {
			return getRuleContext(KeyframeBlockContext.class,i);
		}
		public AtKeyframesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atKeyframes; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtKeyframes(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtKeyframes(this);
		}
	}

	public final AtKeyframesContext atKeyframes() throws RecognitionException {
		AtKeyframesContext _localctx = new AtKeyframesContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_atKeyframes);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(465);
			match(KEYFRAMES);
			setState(466);
			match(IDENTIFIER);
			setState(467);
			match(T__0);
			setState(471);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 48)) & ~0x3f) == 0 && ((1L << (_la - 48)) & 536870915L) != 0)) {
				{
				{
				setState(468);
				keyframeBlock();
				}
				}
				setState(473);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(474);
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
	public static class KeyframeBlockContext extends ParserRuleContext {
		public KeyframeSelectorContext keyframeSelector() {
			return getRuleContext(KeyframeSelectorContext.class,0);
		}
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public KeyframeBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_keyframeBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterKeyframeBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitKeyframeBlock(this);
		}
	}

	public final KeyframeBlockContext keyframeBlock() throws RecognitionException {
		KeyframeBlockContext _localctx = new KeyframeBlockContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_keyframeBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(476);
			keyframeSelector(0);
			setState(477);
			match(T__0);
			setState(481);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE || _la==IDENTIFIER) {
				{
				{
				setState(478);
				declaration();
				}
				}
				setState(483);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(484);
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
	public static class KeyframeSelectorContext extends ParserRuleContext {
		public TerminalNode FROM() { return getToken(CSSParser.FROM, 0); }
		public TerminalNode TO() { return getToken(CSSParser.TO, 0); }
		public PercentageContext percentage() {
			return getRuleContext(PercentageContext.class,0);
		}
		public List<KeyframeSelectorContext> keyframeSelector() {
			return getRuleContexts(KeyframeSelectorContext.class);
		}
		public KeyframeSelectorContext keyframeSelector(int i) {
			return getRuleContext(KeyframeSelectorContext.class,i);
		}
		public KeyframeSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_keyframeSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterKeyframeSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitKeyframeSelector(this);
		}
	}

	public final KeyframeSelectorContext keyframeSelector() throws RecognitionException {
		return keyframeSelector(0);
	}

	private KeyframeSelectorContext keyframeSelector(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		KeyframeSelectorContext _localctx = new KeyframeSelectorContext(_ctx, _parentState);
		KeyframeSelectorContext _prevctx = _localctx;
		int _startState = 94;
		enterRecursionRule(_localctx, 94, RULE_keyframeSelector, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(490);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case FROM:
				{
				setState(487);
				match(FROM);
				}
				break;
			case TO:
				{
				setState(488);
				match(TO);
				}
				break;
			case NUMBER:
				{
				setState(489);
				percentage();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			_ctx.stop = _input.LT(-1);
			setState(497);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,44,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new KeyframeSelectorContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_keyframeSelector);
					setState(492);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(493);
					match(T__2);
					setState(494);
					keyframeSelector(2);
					}
					} 
				}
				setState(499);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,44,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AtFontFaceContext extends ParserRuleContext {
		public TerminalNode FONT_FACE() { return getToken(CSSParser.FONT_FACE, 0); }
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public AtFontFaceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atFontFace; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtFontFace(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtFontFace(this);
		}
	}

	public final AtFontFaceContext atFontFace() throws RecognitionException {
		AtFontFaceContext _localctx = new AtFontFaceContext(_ctx, getState());
		enterRule(_localctx, 96, RULE_atFontFace);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(500);
			match(FONT_FACE);
			setState(501);
			match(T__0);
			setState(505);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE || _la==IDENTIFIER) {
				{
				{
				setState(502);
				declaration();
				}
				}
				setState(507);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(508);
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
	public static class AtSupportsContext extends ParserRuleContext {
		public TerminalNode SUPPORTS() { return getToken(CSSParser.SUPPORTS, 0); }
		public SupportsConditionContext supportsCondition() {
			return getRuleContext(SupportsConditionContext.class,0);
		}
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public AtSupportsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atSupports; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtSupports(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtSupports(this);
		}
	}

	public final AtSupportsContext atSupports() throws RecognitionException {
		AtSupportsContext _localctx = new AtSupportsContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_atSupports);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(510);
			match(SUPPORTS);
			setState(511);
			supportsCondition();
			setState(512);
			match(T__0);
			setState(516);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 17590055602170L) != 0) || _la==IDENTIFIER || _la==WS) {
				{
				{
				setState(513);
				statement();
				}
				}
				setState(518);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(519);
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
	public static class SupportsConditionContext extends ParserRuleContext {
		public SupportsNegationContext supportsNegation() {
			return getRuleContext(SupportsNegationContext.class,0);
		}
		public SupportsConjunctionContext supportsConjunction() {
			return getRuleContext(SupportsConjunctionContext.class,0);
		}
		public SupportsDisjunctionContext supportsDisjunction() {
			return getRuleContext(SupportsDisjunctionContext.class,0);
		}
		public SupportsInParensContext supportsInParens() {
			return getRuleContext(SupportsInParensContext.class,0);
		}
		public SupportsConditionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_supportsCondition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSupportsCondition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSupportsCondition(this);
		}
	}

	public final SupportsConditionContext supportsCondition() throws RecognitionException {
		SupportsConditionContext _localctx = new SupportsConditionContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_supportsCondition);
		try {
			setState(525);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,47,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(521);
				supportsNegation();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(522);
				supportsConjunction();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(523);
				supportsDisjunction();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(524);
				supportsInParens();
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
	public static class SupportsNegationContext extends ParserRuleContext {
		public TerminalNode NOT() { return getToken(CSSParser.NOT, 0); }
		public SupportsInParensContext supportsInParens() {
			return getRuleContext(SupportsInParensContext.class,0);
		}
		public SupportsNegationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_supportsNegation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSupportsNegation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSupportsNegation(this);
		}
	}

	public final SupportsNegationContext supportsNegation() throws RecognitionException {
		SupportsNegationContext _localctx = new SupportsNegationContext(_ctx, getState());
		enterRule(_localctx, 102, RULE_supportsNegation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(527);
			match(NOT);
			setState(528);
			supportsInParens();
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
	public static class SupportsConjunctionContext extends ParserRuleContext {
		public List<SupportsInParensContext> supportsInParens() {
			return getRuleContexts(SupportsInParensContext.class);
		}
		public SupportsInParensContext supportsInParens(int i) {
			return getRuleContext(SupportsInParensContext.class,i);
		}
		public List<TerminalNode> AND() { return getTokens(CSSParser.AND); }
		public TerminalNode AND(int i) {
			return getToken(CSSParser.AND, i);
		}
		public SupportsConjunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_supportsConjunction; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSupportsConjunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSupportsConjunction(this);
		}
	}

	public final SupportsConjunctionContext supportsConjunction() throws RecognitionException {
		SupportsConjunctionContext _localctx = new SupportsConjunctionContext(_ctx, getState());
		enterRule(_localctx, 104, RULE_supportsConjunction);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(530);
			supportsInParens();
			setState(533); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(531);
				match(AND);
				setState(532);
				supportsInParens();
				}
				}
				setState(535); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==AND );
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
	public static class SupportsDisjunctionContext extends ParserRuleContext {
		public List<SupportsInParensContext> supportsInParens() {
			return getRuleContexts(SupportsInParensContext.class);
		}
		public SupportsInParensContext supportsInParens(int i) {
			return getRuleContext(SupportsInParensContext.class,i);
		}
		public List<TerminalNode> OR() { return getTokens(CSSParser.OR); }
		public TerminalNode OR(int i) {
			return getToken(CSSParser.OR, i);
		}
		public SupportsDisjunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_supportsDisjunction; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSupportsDisjunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSupportsDisjunction(this);
		}
	}

	public final SupportsDisjunctionContext supportsDisjunction() throws RecognitionException {
		SupportsDisjunctionContext _localctx = new SupportsDisjunctionContext(_ctx, getState());
		enterRule(_localctx, 106, RULE_supportsDisjunction);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(537);
			supportsInParens();
			setState(540); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(538);
				match(OR);
				setState(539);
				supportsInParens();
				}
				}
				setState(542); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==OR );
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
	public static class SupportsInParensContext extends ParserRuleContext {
		public SupportsConditionContext supportsCondition() {
			return getRuleContext(SupportsConditionContext.class,0);
		}
		public SupportsFeatureContext supportsFeature() {
			return getRuleContext(SupportsFeatureContext.class,0);
		}
		public SupportsInParensContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_supportsInParens; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSupportsInParens(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSupportsInParens(this);
		}
	}

	public final SupportsInParensContext supportsInParens() throws RecognitionException {
		SupportsInParensContext _localctx = new SupportsInParensContext(_ctx, getState());
		enterRule(_localctx, 108, RULE_supportsInParens);
		try {
			setState(549);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,50,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(544);
				match(T__18);
				setState(545);
				supportsCondition();
				setState(546);
				match(T__19);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(548);
				supportsFeature();
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
	public static class SupportsFeatureContext extends ParserRuleContext {
		public DeclarationContext declaration() {
			return getRuleContext(DeclarationContext.class,0);
		}
		public SupportsFeatureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_supportsFeature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterSupportsFeature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitSupportsFeature(this);
		}
	}

	public final SupportsFeatureContext supportsFeature() throws RecognitionException {
		SupportsFeatureContext _localctx = new SupportsFeatureContext(_ctx, getState());
		enterRule(_localctx, 110, RULE_supportsFeature);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(551);
			match(T__18);
			setState(552);
			declaration();
			setState(553);
			match(T__19);
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
	public static class AtPageContext extends ParserRuleContext {
		public TerminalNode PAGE() { return getToken(CSSParser.PAGE, 0); }
		public PseudoPageContext pseudoPage() {
			return getRuleContext(PseudoPageContext.class,0);
		}
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public AtPageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atPage; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtPage(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtPage(this);
		}
	}

	public final AtPageContext atPage() throws RecognitionException {
		AtPageContext _localctx = new AtPageContext(_ctx, getState());
		enterRule(_localctx, 112, RULE_atPage);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(555);
			match(PAGE);
			setState(557);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__17) {
				{
				setState(556);
				pseudoPage();
				}
			}

			setState(559);
			match(T__0);
			setState(563);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE || _la==IDENTIFIER) {
				{
				{
				setState(560);
				declaration();
				}
				}
				setState(565);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(566);
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
	public static class PseudoPageContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public PseudoPageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pseudoPage; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterPseudoPage(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitPseudoPage(this);
		}
	}

	public final PseudoPageContext pseudoPage() throws RecognitionException {
		PseudoPageContext _localctx = new PseudoPageContext(_ctx, getState());
		enterRule(_localctx, 114, RULE_pseudoPage);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(568);
			match(T__17);
			setState(569);
			match(IDENTIFIER);
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
	public static class AtNamespaceContext extends ParserRuleContext {
		public TerminalNode NAMESPACE() { return getToken(CSSParser.NAMESPACE, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(CSSParser.STRING_LITERAL, 0); }
		public TerminalNode URI() { return getToken(CSSParser.URI, 0); }
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public AtNamespaceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atNamespace; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtNamespace(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtNamespace(this);
		}
	}

	public final AtNamespaceContext atNamespace() throws RecognitionException {
		AtNamespaceContext _localctx = new AtNamespaceContext(_ctx, getState());
		enterRule(_localctx, 116, RULE_atNamespace);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(571);
			match(NAMESPACE);
			setState(573);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(572);
				match(IDENTIFIER);
				}
			}

			setState(575);
			_la = _input.LA(1);
			if ( !(_la==STRING_LITERAL || _la==URI) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(576);
			match(T__24);
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
	public static class AtCharsetContext extends ParserRuleContext {
		public TerminalNode CHARSET() { return getToken(CSSParser.CHARSET, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(CSSParser.STRING_LITERAL, 0); }
		public AtCharsetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atCharset; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtCharset(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtCharset(this);
		}
	}

	public final AtCharsetContext atCharset() throws RecognitionException {
		AtCharsetContext _localctx = new AtCharsetContext(_ctx, getState());
		enterRule(_localctx, 118, RULE_atCharset);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(578);
			match(CHARSET);
			setState(579);
			match(STRING_LITERAL);
			setState(580);
			match(T__24);
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
	public static class AtViewportContext extends ParserRuleContext {
		public TerminalNode VIEWPORT() { return getToken(CSSParser.VIEWPORT, 0); }
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public AtViewportContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atViewport; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtViewport(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtViewport(this);
		}
	}

	public final AtViewportContext atViewport() throws RecognitionException {
		AtViewportContext _localctx = new AtViewportContext(_ctx, getState());
		enterRule(_localctx, 120, RULE_atViewport);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(582);
			match(VIEWPORT);
			setState(583);
			match(T__0);
			setState(587);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE || _la==IDENTIFIER) {
				{
				{
				setState(584);
				declaration();
				}
				}
				setState(589);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(590);
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
	public static class AtCounterStyleContext extends ParserRuleContext {
		public TerminalNode COUNTER_STYLE() { return getToken(CSSParser.COUNTER_STYLE, 0); }
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public AtCounterStyleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atCounterStyle; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtCounterStyle(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtCounterStyle(this);
		}
	}

	public final AtCounterStyleContext atCounterStyle() throws RecognitionException {
		AtCounterStyleContext _localctx = new AtCounterStyleContext(_ctx, getState());
		enterRule(_localctx, 122, RULE_atCounterStyle);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(592);
			match(COUNTER_STYLE);
			setState(593);
			match(IDENTIFIER);
			setState(594);
			match(T__0);
			setState(598);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE || _la==IDENTIFIER) {
				{
				{
				setState(595);
				declaration();
				}
				}
				setState(600);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(601);
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
	public static class AtFontFeatureValuesContext extends ParserRuleContext {
		public TerminalNode FONT_FEATURE_VALUES() { return getToken(CSSParser.FONT_FEATURE_VALUES, 0); }
		public List<FontFamilyNameContext> fontFamilyName() {
			return getRuleContexts(FontFamilyNameContext.class);
		}
		public FontFamilyNameContext fontFamilyName(int i) {
			return getRuleContext(FontFamilyNameContext.class,i);
		}
		public List<FontFeatureValueBlockContext> fontFeatureValueBlock() {
			return getRuleContexts(FontFeatureValueBlockContext.class);
		}
		public FontFeatureValueBlockContext fontFeatureValueBlock(int i) {
			return getRuleContext(FontFeatureValueBlockContext.class,i);
		}
		public AtFontFeatureValuesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atFontFeatureValues; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtFontFeatureValues(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtFontFeatureValues(this);
		}
	}

	public final AtFontFeatureValuesContext atFontFeatureValues() throws RecognitionException {
		AtFontFeatureValuesContext _localctx = new AtFontFeatureValuesContext(_ctx, getState());
		enterRule(_localctx, 124, RULE_atFontFeatureValues);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(603);
			match(FONT_FEATURE_VALUES);
			setState(605); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(604);
				fontFamilyName();
				}
				}
				setState(607); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==STRING_LITERAL || _la==IDENTIFIER );
			setState(609);
			match(T__0);
			setState(613);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__29) {
				{
				{
				setState(610);
				fontFeatureValueBlock();
				}
				}
				setState(615);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(616);
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
	public static class FontFamilyNameContext extends ParserRuleContext {
		public TerminalNode STRING_LITERAL() { return getToken(CSSParser.STRING_LITERAL, 0); }
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public FontFamilyNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fontFamilyName; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterFontFamilyName(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitFontFamilyName(this);
		}
	}

	public final FontFamilyNameContext fontFamilyName() throws RecognitionException {
		FontFamilyNameContext _localctx = new FontFamilyNameContext(_ctx, getState());
		enterRule(_localctx, 126, RULE_fontFamilyName);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(618);
			_la = _input.LA(1);
			if ( !(_la==STRING_LITERAL || _la==IDENTIFIER) ) {
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
	public static class FontFeatureValueBlockContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CSSParser.IDENTIFIER, 0); }
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public FontFeatureValueBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fontFeatureValueBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterFontFeatureValueBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitFontFeatureValueBlock(this);
		}
	}

	public final FontFeatureValueBlockContext fontFeatureValueBlock() throws RecognitionException {
		FontFeatureValueBlockContext _localctx = new FontFeatureValueBlockContext(_ctx, getState());
		enterRule(_localctx, 128, RULE_fontFeatureValueBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(620);
			match(T__29);
			setState(621);
			match(IDENTIFIER);
			setState(622);
			match(T__0);
			setState(626);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE || _la==IDENTIFIER) {
				{
				{
				setState(623);
				declaration();
				}
				}
				setState(628);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(629);
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
	public static class AtPropertyContext extends ParserRuleContext {
		public TerminalNode PROPERTY() { return getToken(CSSParser.PROPERTY, 0); }
		public TerminalNode VARIABLE() { return getToken(CSSParser.VARIABLE, 0); }
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public AtPropertyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atProperty; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterAtProperty(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitAtProperty(this);
		}
	}

	public final AtPropertyContext atProperty() throws RecognitionException {
		AtPropertyContext _localctx = new AtPropertyContext(_ctx, getState());
		enterRule(_localctx, 130, RULE_atProperty);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(631);
			match(PROPERTY);
			setState(632);
			match(VARIABLE);
			setState(633);
			match(T__0);
			setState(637);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE || _la==IDENTIFIER) {
				{
				{
				setState(634);
				declaration();
				}
				}
				setState(639);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(640);
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
	public static class ExpressionContext extends ParserRuleContext {
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public List<OperatorContext> operator() {
			return getRuleContexts(OperatorContext.class);
		}
		public OperatorContext operator(int i) {
			return getRuleContext(OperatorContext.class,i);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitExpression(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 132, RULE_expression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(642);
			term();
			setState(648);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__2 || _la==T__26 || _la==WS) {
				{
				{
				setState(643);
				operator();
				setState(644);
				term();
				}
				}
				setState(650);
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
	public static class CommentContext extends ParserRuleContext {
		public TerminalNode COMMENT() { return getToken(CSSParser.COMMENT, 0); }
		public CommentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_comment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).enterComment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CSSListener ) ((CSSListener)listener).exitComment(this);
		}
	}

	public final CommentContext comment() throws RecognitionException {
		CommentContext _localctx = new CommentContext(_ctx, getState());
		enterRule(_localctx, 134, RULE_comment);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(651);
			match(COMMENT);
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

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 47:
			return keyframeSelector_sempred((KeyframeSelectorContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean keyframeSelector_sempred(KeyframeSelectorContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 1);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001R\u028e\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
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
		"#\u0007#\u0002$\u0007$\u0002%\u0007%\u0002&\u0007&\u0002\'\u0007\'\u0002"+
		"(\u0007(\u0002)\u0007)\u0002*\u0007*\u0002+\u0007+\u0002,\u0007,\u0002"+
		"-\u0007-\u0002.\u0007.\u0002/\u0007/\u00020\u00070\u00021\u00071\u0002"+
		"2\u00072\u00023\u00073\u00024\u00074\u00025\u00075\u00026\u00076\u0002"+
		"7\u00077\u00028\u00078\u00029\u00079\u0002:\u0007:\u0002;\u0007;\u0002"+
		"<\u0007<\u0002=\u0007=\u0002>\u0007>\u0002?\u0007?\u0002@\u0007@\u0002"+
		"A\u0007A\u0002B\u0007B\u0002C\u0007C\u0001\u0000\u0005\u0000\u008a\b\u0000"+
		"\n\u0000\f\u0000\u008d\t\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0003\u0001\u0094\b\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0002\u0005\u0002\u0099\b\u0002\n\u0002\f\u0002\u009c\t\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0005\u0003\u00a3\b\u0003"+
		"\n\u0003\f\u0003\u00a6\t\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0005\u0004\u00ac\b\u0004\n\u0004\f\u0004\u00af\t\u0004\u0001\u0005"+
		"\u0001\u0005\u0001\u0006\u0001\u0006\u0003\u0006\u00b5\b\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0005\u0006\u00bb\b\u0006\n\u0006"+
		"\f\u0006\u00be\t\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0004\u0006\u00c4\b\u0006\u000b\u0006\f\u0006\u00c5\u0003\u0006\u00c8"+
		"\b\u0006\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001\t\u0001\t\u0001"+
		"\t\u0001\n\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0003\u000b\u00d9\b\u000b\u0001\u000b\u0001\u000b\u0001\f"+
		"\u0001\f\u0001\r\u0001\r\u0003\r\u00e1\b\r\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0003\u000e\u00e9\b\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0003"+
		"\u000e\u00f7\b\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0003"+
		"\u000f\u00fd\b\u000f\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0003\u0011\u0106\b\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0003\u0011\u010e"+
		"\b\u0011\u0003\u0011\u0110\b\u0011\u0001\u0012\u0001\u0012\u0001\u0012"+
		"\u0005\u0012\u0115\b\u0012\n\u0012\f\u0012\u0118\t\u0012\u0001\u0012\u0003"+
		"\u0012\u011b\b\u0012\u0001\u0013\u0001\u0013\u0003\u0013\u011f\b\u0013"+
		"\u0001\u0013\u0005\u0013\u0122\b\u0013\n\u0013\f\u0013\u0125\t\u0013\u0001"+
		"\u0014\u0001\u0014\u0001\u0015\u0003\u0015\u012a\b\u0015\u0001\u0015\u0001"+
		"\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0003"+
		"\u0015\u0133\b\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001"+
		"\u0015\u0001\u0015\u0001\u0015\u0003\u0015\u013c\b\u0015\u0001\u0016\u0001"+
		"\u0016\u0001\u0017\u0001\u0017\u0001\u0018\u0001\u0018\u0001\u0018\u0001"+
		"\u0019\u0001\u0019\u0001\u0019\u0001\u001a\u0001\u001a\u0001\u001a\u0001"+
		"\u001b\u0001\u001b\u0001\u001b\u0001\u001c\u0001\u001c\u0001\u001c\u0001"+
		"\u001d\u0001\u001d\u0001\u001d\u0001\u001e\u0001\u001e\u0004\u001e\u0156"+
		"\b\u001e\u000b\u001e\f\u001e\u0157\u0001\u001f\u0001\u001f\u0001\u001f"+
		"\u0003\u001f\u015d\b\u001f\u0001\u001f\u0001\u001f\u0001 \u0001 \u0001"+
		" \u0005 \u0164\b \n \f \u0167\t \u0001!\u0001!\u0001\"\u0001\"\u0001\""+
		"\u0001\"\u0001\"\u0001#\u0001#\u0001#\u0005#\u0173\b#\n#\f#\u0176\t#\u0001"+
		"$\u0001$\u0001$\u0005$\u017b\b$\n$\f$\u017e\t$\u0001%\u0001%\u0001%\u0001"+
		"%\u0001%\u0001%\u0001%\u0001%\u0001%\u0003%\u0189\b%\u0001&\u0001&\u0001"+
		"&\u0001&\u0001&\u0001&\u0001&\u0001&\u0001&\u0001&\u0001&\u0001&\u0003"+
		"&\u0197\b&\u0001\'\u0001\'\u0001\'\u0003\'\u019c\b\'\u0001\'\u0001\'\u0001"+
		"(\u0001(\u0001(\u0001(\u0005(\u01a4\b(\n(\f(\u01a7\t(\u0001(\u0001(\u0001"+
		")\u0001)\u0001)\u0005)\u01ae\b)\n)\f)\u01b1\t)\u0001*\u0003*\u01b4\b*"+
		"\u0001*\u0001*\u0001*\u0005*\u01b9\b*\n*\f*\u01bc\t*\u0001*\u0001*\u0001"+
		"*\u0005*\u01c1\b*\n*\f*\u01c4\t*\u0003*\u01c6\b*\u0001+\u0001+\u0001,"+
		"\u0001,\u0001,\u0001,\u0003,\u01ce\b,\u0001,\u0001,\u0001-\u0001-\u0001"+
		"-\u0001-\u0005-\u01d6\b-\n-\f-\u01d9\t-\u0001-\u0001-\u0001.\u0001.\u0001"+
		".\u0005.\u01e0\b.\n.\f.\u01e3\t.\u0001.\u0001.\u0001/\u0001/\u0001/\u0001"+
		"/\u0003/\u01eb\b/\u0001/\u0001/\u0001/\u0005/\u01f0\b/\n/\f/\u01f3\t/"+
		"\u00010\u00010\u00010\u00050\u01f8\b0\n0\f0\u01fb\t0\u00010\u00010\u0001"+
		"1\u00011\u00011\u00011\u00051\u0203\b1\n1\f1\u0206\t1\u00011\u00011\u0001"+
		"2\u00012\u00012\u00012\u00032\u020e\b2\u00013\u00013\u00013\u00014\u0001"+
		"4\u00014\u00044\u0216\b4\u000b4\f4\u0217\u00015\u00015\u00015\u00045\u021d"+
		"\b5\u000b5\f5\u021e\u00016\u00016\u00016\u00016\u00016\u00036\u0226\b"+
		"6\u00017\u00017\u00017\u00017\u00018\u00018\u00038\u022e\b8\u00018\u0001"+
		"8\u00058\u0232\b8\n8\f8\u0235\t8\u00018\u00018\u00019\u00019\u00019\u0001"+
		":\u0001:\u0003:\u023e\b:\u0001:\u0001:\u0001:\u0001;\u0001;\u0001;\u0001"+
		";\u0001<\u0001<\u0001<\u0005<\u024a\b<\n<\f<\u024d\t<\u0001<\u0001<\u0001"+
		"=\u0001=\u0001=\u0001=\u0005=\u0255\b=\n=\f=\u0258\t=\u0001=\u0001=\u0001"+
		">\u0001>\u0004>\u025e\b>\u000b>\f>\u025f\u0001>\u0001>\u0005>\u0264\b"+
		">\n>\f>\u0267\t>\u0001>\u0001>\u0001?\u0001?\u0001@\u0001@\u0001@\u0001"+
		"@\u0005@\u0271\b@\n@\f@\u0274\t@\u0001@\u0001@\u0001A\u0001A\u0001A\u0001"+
		"A\u0005A\u027c\bA\nA\fA\u027f\tA\u0001A\u0001A\u0001B\u0001B\u0001B\u0001"+
		"B\u0005B\u0287\bB\nB\fB\u028a\tB\u0001C\u0001C\u0001C\u0000\u0001^D\u0000"+
		"\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c"+
		"\u001e \"$&(*,.02468:<>@BDFHJLNPRTVXZ\\^`bdfhjlnprtvxz|~\u0080\u0082\u0084"+
		"\u0086\u0000\u000e\u0002\u0000\u0004\u0006RR\u0002\u0000NNPP\u0001\u0000"+
		"\f\u0011\u0001\u0000\u0015\u0017\u0003\u0000\u0003\u0003\u001b\u001bR"+
		"R\u0002\u0000\u0005\u0005\u001a\u001a\u0001\u00003@\u0001\u0000AD\u0001"+
		"\u0000EF\u0001\u0000GH\u0001\u0000IK\u0002\u0000\u0007\u0007\u001b\u001b"+
		"\u0001\u0000NO\u0001\u0000,-\u02ab\u0000\u008b\u0001\u0000\u0000\u0000"+
		"\u0002\u0093\u0001\u0000\u0000\u0000\u0004\u0095\u0001\u0000\u0000\u0000"+
		"\u0006\u009f\u0001\u0000\u0000\u0000\b\u00a7\u0001\u0000\u0000\u0000\n"+
		"\u00b0\u0001\u0000\u0000\u0000\f\u00c7\u0001\u0000\u0000\u0000\u000e\u00c9"+
		"\u0001\u0000\u0000\u0000\u0010\u00cb\u0001\u0000\u0000\u0000\u0012\u00cd"+
		"\u0001\u0000\u0000\u0000\u0014\u00d0\u0001\u0000\u0000\u0000\u0016\u00d3"+
		"\u0001\u0000\u0000\u0000\u0018\u00dc\u0001\u0000\u0000\u0000\u001a\u00e0"+
		"\u0001\u0000\u0000\u0000\u001c\u00f6\u0001\u0000\u0000\u0000\u001e\u00fc"+
		"\u0001\u0000\u0000\u0000 \u00fe\u0001\u0000\u0000\u0000\"\u010f\u0001"+
		"\u0000\u0000\u0000$\u011a\u0001\u0000\u0000\u0000&\u011c\u0001\u0000\u0000"+
		"\u0000(\u0126\u0001\u0000\u0000\u0000*\u013b\u0001\u0000\u0000\u0000,"+
		"\u013d\u0001\u0000\u0000\u0000.\u013f\u0001\u0000\u0000\u00000\u0141\u0001"+
		"\u0000\u0000\u00002\u0144\u0001\u0000\u0000\u00004\u0147\u0001\u0000\u0000"+
		"\u00006\u014a\u0001\u0000\u0000\u00008\u014d\u0001\u0000\u0000\u0000:"+
		"\u0150\u0001\u0000\u0000\u0000<\u0153\u0001\u0000\u0000\u0000>\u0159\u0001"+
		"\u0000\u0000\u0000@\u0160\u0001\u0000\u0000\u0000B\u0168\u0001\u0000\u0000"+
		"\u0000D\u016a\u0001\u0000\u0000\u0000F\u016f\u0001\u0000\u0000\u0000H"+
		"\u0177\u0001\u0000\u0000\u0000J\u0188\u0001\u0000\u0000\u0000L\u0196\u0001"+
		"\u0000\u0000\u0000N\u0198\u0001\u0000\u0000\u0000P\u019f\u0001\u0000\u0000"+
		"\u0000R\u01aa\u0001\u0000\u0000\u0000T\u01c5\u0001\u0000\u0000\u0000V"+
		"\u01c7\u0001\u0000\u0000\u0000X\u01c9\u0001\u0000\u0000\u0000Z\u01d1\u0001"+
		"\u0000\u0000\u0000\\\u01dc\u0001\u0000\u0000\u0000^\u01ea\u0001\u0000"+
		"\u0000\u0000`\u01f4\u0001\u0000\u0000\u0000b\u01fe\u0001\u0000\u0000\u0000"+
		"d\u020d\u0001\u0000\u0000\u0000f\u020f\u0001\u0000\u0000\u0000h\u0212"+
		"\u0001\u0000\u0000\u0000j\u0219\u0001\u0000\u0000\u0000l\u0225\u0001\u0000"+
		"\u0000\u0000n\u0227\u0001\u0000\u0000\u0000p\u022b\u0001\u0000\u0000\u0000"+
		"r\u0238\u0001\u0000\u0000\u0000t\u023b\u0001\u0000\u0000\u0000v\u0242"+
		"\u0001\u0000\u0000\u0000x\u0246\u0001\u0000\u0000\u0000z\u0250\u0001\u0000"+
		"\u0000\u0000|\u025b\u0001\u0000\u0000\u0000~\u026a\u0001\u0000\u0000\u0000"+
		"\u0080\u026c\u0001\u0000\u0000\u0000\u0082\u0277\u0001\u0000\u0000\u0000"+
		"\u0084\u0282\u0001\u0000\u0000\u0000\u0086\u028b\u0001\u0000\u0000\u0000"+
		"\u0088\u008a\u0003\u0002\u0001\u0000\u0089\u0088\u0001\u0000\u0000\u0000"+
		"\u008a\u008d\u0001\u0000\u0000\u0000\u008b\u0089\u0001\u0000\u0000\u0000"+
		"\u008b\u008c\u0001\u0000\u0000\u0000\u008c\u008e\u0001\u0000\u0000\u0000"+
		"\u008d\u008b\u0001\u0000\u0000\u0000\u008e\u008f\u0005\u0000\u0000\u0001"+
		"\u008f\u0001\u0001\u0000\u0000\u0000\u0090\u0094\u0003\u0004\u0002\u0000"+
		"\u0091\u0094\u0003L&\u0000\u0092\u0094\u0003\u0086C\u0000\u0093\u0090"+
		"\u0001\u0000\u0000\u0000\u0093\u0091\u0001\u0000\u0000\u0000\u0093\u0092"+
		"\u0001\u0000\u0000\u0000\u0094\u0003\u0001\u0000\u0000\u0000\u0095\u0096"+
		"\u0003\u0006\u0003\u0000\u0096\u009a\u0005\u0001\u0000\u0000\u0097\u0099"+
		"\u0003\"\u0011\u0000\u0098\u0097\u0001\u0000\u0000\u0000\u0099\u009c\u0001"+
		"\u0000\u0000\u0000\u009a\u0098\u0001\u0000\u0000\u0000\u009a\u009b\u0001"+
		"\u0000\u0000\u0000\u009b\u009d\u0001\u0000\u0000\u0000\u009c\u009a\u0001"+
		"\u0000\u0000\u0000\u009d\u009e\u0005\u0002\u0000\u0000\u009e\u0005\u0001"+
		"\u0000\u0000\u0000\u009f\u00a4\u0003\b\u0004\u0000\u00a0\u00a1\u0005\u0003"+
		"\u0000\u0000\u00a1\u00a3\u0003\b\u0004\u0000\u00a2\u00a0\u0001\u0000\u0000"+
		"\u0000\u00a3\u00a6\u0001\u0000\u0000\u0000\u00a4\u00a2\u0001\u0000\u0000"+
		"\u0000\u00a4\u00a5\u0001\u0000\u0000\u0000\u00a5\u0007\u0001\u0000\u0000"+
		"\u0000\u00a6\u00a4\u0001\u0000\u0000\u0000\u00a7\u00ad\u0003\f\u0006\u0000"+
		"\u00a8\u00a9\u0003\n\u0005\u0000\u00a9\u00aa\u0003\f\u0006\u0000\u00aa"+
		"\u00ac\u0001\u0000\u0000\u0000\u00ab\u00a8\u0001\u0000\u0000\u0000\u00ac"+
		"\u00af\u0001\u0000\u0000\u0000\u00ad\u00ab\u0001\u0000\u0000\u0000\u00ad"+
		"\u00ae\u0001\u0000\u0000\u0000\u00ae\t\u0001\u0000\u0000\u0000\u00af\u00ad"+
		"\u0001\u0000\u0000\u0000\u00b0\u00b1\u0007\u0000\u0000\u0000\u00b1\u000b"+
		"\u0001\u0000\u0000\u0000\u00b2\u00b5\u0003\u000e\u0007\u0000\u00b3\u00b5"+
		"\u0003\u0010\b\u0000\u00b4\u00b2\u0001\u0000\u0000\u0000\u00b4\u00b3\u0001"+
		"\u0000\u0000\u0000\u00b4\u00b5\u0001\u0000\u0000\u0000\u00b5\u00bc\u0001"+
		"\u0000\u0000\u0000\u00b6\u00bb\u0003\u0012\t\u0000\u00b7\u00bb\u0003\u0014"+
		"\n\u0000\u00b8\u00bb\u0003\u0016\u000b\u0000\u00b9\u00bb\u0003\u001a\r"+
		"\u0000\u00ba\u00b6\u0001\u0000\u0000\u0000\u00ba\u00b7\u0001\u0000\u0000"+
		"\u0000\u00ba\u00b8\u0001\u0000\u0000\u0000\u00ba\u00b9\u0001\u0000\u0000"+
		"\u0000\u00bb\u00be\u0001\u0000\u0000\u0000\u00bc\u00ba\u0001\u0000\u0000"+
		"\u0000\u00bc\u00bd\u0001\u0000\u0000\u0000\u00bd\u00c8\u0001\u0000\u0000"+
		"\u0000\u00be\u00bc\u0001\u0000\u0000\u0000\u00bf\u00c4\u0003\u0012\t\u0000"+
		"\u00c0\u00c4\u0003\u0014\n\u0000\u00c1\u00c4\u0003\u0016\u000b\u0000\u00c2"+
		"\u00c4\u0003\u001a\r\u0000\u00c3\u00bf\u0001\u0000\u0000\u0000\u00c3\u00c0"+
		"\u0001\u0000\u0000\u0000\u00c3\u00c1\u0001\u0000\u0000\u0000\u00c3\u00c2"+
		"\u0001\u0000\u0000\u0000\u00c4\u00c5\u0001\u0000\u0000\u0000\u00c5\u00c3"+
		"\u0001\u0000\u0000\u0000\u00c5\u00c6\u0001\u0000\u0000\u0000\u00c6\u00c8"+
		"\u0001\u0000\u0000\u0000\u00c7\u00b4\u0001\u0000\u0000\u0000\u00c7\u00c3"+
		"\u0001\u0000\u0000\u0000\u00c8\r\u0001\u0000\u0000\u0000\u00c9\u00ca\u0005"+
		"P\u0000\u0000\u00ca\u000f\u0001\u0000\u0000\u0000\u00cb\u00cc\u0005\u0007"+
		"\u0000\u0000\u00cc\u0011\u0001\u0000\u0000\u0000\u00cd\u00ce\u0005\b\u0000"+
		"\u0000\u00ce\u00cf\u0005P\u0000\u0000\u00cf\u0013\u0001\u0000\u0000\u0000"+
		"\u00d0\u00d1\u0005\t\u0000\u0000\u00d1\u00d2\u0005P\u0000\u0000\u00d2"+
		"\u0015\u0001\u0000\u0000\u0000\u00d3\u00d4\u0005\n\u0000\u0000\u00d4\u00d8"+
		"\u0005P\u0000\u0000\u00d5\u00d6\u0003\u0018\f\u0000\u00d6\u00d7\u0007"+
		"\u0001\u0000\u0000\u00d7\u00d9\u0001\u0000\u0000\u0000\u00d8\u00d5\u0001"+
		"\u0000\u0000\u0000\u00d8\u00d9\u0001\u0000\u0000\u0000\u00d9\u00da\u0001"+
		"\u0000\u0000\u0000\u00da\u00db\u0005\u000b\u0000\u0000\u00db\u0017\u0001"+
		"\u0000\u0000\u0000\u00dc\u00dd\u0007\u0002\u0000\u0000\u00dd\u0019\u0001"+
		"\u0000\u0000\u0000\u00de\u00e1\u0003\u001c\u000e\u0000\u00df\u00e1\u0003"+
		" \u0010\u0000\u00e0\u00de\u0001\u0000\u0000\u0000\u00e0\u00df\u0001\u0000"+
		"\u0000\u0000\u00e1\u001b\u0001\u0000\u0000\u0000\u00e2\u00e3\u0005\u0012"+
		"\u0000\u0000\u00e3\u00e8\u0005P\u0000\u0000\u00e4\u00e5\u0005\u0013\u0000"+
		"\u0000\u00e5\u00e6\u0003\u001e\u000f\u0000\u00e6\u00e7\u0005\u0014\u0000"+
		"\u0000\u00e7\u00e9\u0001\u0000\u0000\u0000\u00e8\u00e4\u0001\u0000\u0000"+
		"\u0000\u00e8\u00e9\u0001\u0000\u0000\u0000\u00e9\u00f7\u0001\u0000\u0000"+
		"\u0000\u00ea\u00eb\u0005\u0012\u0000\u0000\u00eb\u00ec\u0005-\u0000\u0000"+
		"\u00ec\u00ed\u0005\u0013\u0000\u0000\u00ed\u00ee\u0003\u0006\u0003\u0000"+
		"\u00ee\u00ef\u0005\u0014\u0000\u0000\u00ef\u00f7\u0001\u0000\u0000\u0000"+
		"\u00f0\u00f1\u0005\u0012\u0000\u0000\u00f1\u00f2\u0007\u0003\u0000\u0000"+
		"\u00f2\u00f3\u0005\u0013\u0000\u0000\u00f3\u00f4\u0003\u0006\u0003\u0000"+
		"\u00f4\u00f5\u0005\u0014\u0000\u0000\u00f5\u00f7\u0001\u0000\u0000\u0000"+
		"\u00f6\u00e2\u0001\u0000\u0000\u0000\u00f6\u00ea\u0001\u0000\u0000\u0000"+
		"\u00f6\u00f0\u0001\u0000\u0000\u0000\u00f7\u001d\u0001\u0000\u0000\u0000"+
		"\u00f8\u00fd\u0005P\u0000\u0000\u00f9\u00fd\u0005M\u0000\u0000\u00fa\u00fd"+
		"\u0005N\u0000\u0000\u00fb\u00fd\u0003\u0084B\u0000\u00fc\u00f8\u0001\u0000"+
		"\u0000\u0000\u00fc\u00f9\u0001\u0000\u0000\u0000\u00fc\u00fa\u0001\u0000"+
		"\u0000\u0000\u00fc\u00fb\u0001\u0000\u0000\u0000\u00fd\u001f\u0001\u0000"+
		"\u0000\u0000\u00fe\u00ff\u0005\u0018\u0000\u0000\u00ff\u0100\u0005P\u0000"+
		"\u0000\u0100!\u0001\u0000\u0000\u0000\u0101\u0102\u0003$\u0012\u0000\u0102"+
		"\u0103\u0005\u0012\u0000\u0000\u0103\u0105\u0003&\u0013\u0000\u0104\u0106"+
		"\u00052\u0000\u0000\u0105\u0104\u0001\u0000\u0000\u0000\u0105\u0106\u0001"+
		"\u0000\u0000\u0000\u0106\u0107\u0001\u0000\u0000\u0000\u0107\u0108\u0005"+
		"\u0019\u0000\u0000\u0108\u0110\u0001\u0000\u0000\u0000\u0109\u010a\u0003"+
		"$\u0012\u0000\u010a\u010b\u0005\u0012\u0000\u0000\u010b\u010d\u0003&\u0013"+
		"\u0000\u010c\u010e\u00052\u0000\u0000\u010d\u010c\u0001\u0000\u0000\u0000"+
		"\u010d\u010e\u0001\u0000\u0000\u0000\u010e\u0110\u0001\u0000\u0000\u0000"+
		"\u010f\u0101\u0001\u0000\u0000\u0000\u010f\u0109\u0001\u0000\u0000\u0000"+
		"\u0110#\u0001\u0000\u0000\u0000\u0111\u0116\u0005P\u0000\u0000\u0112\u0113"+
		"\u0005\u001a\u0000\u0000\u0113\u0115\u0005P\u0000\u0000\u0114\u0112\u0001"+
		"\u0000\u0000\u0000\u0115\u0118\u0001\u0000\u0000\u0000\u0116\u0114\u0001"+
		"\u0000\u0000\u0000\u0116\u0117\u0001\u0000\u0000\u0000\u0117\u011b\u0001"+
		"\u0000\u0000\u0000\u0118\u0116\u0001\u0000\u0000\u0000\u0119\u011b\u0005"+
		"L\u0000\u0000\u011a\u0111\u0001\u0000\u0000\u0000\u011a\u0119\u0001\u0000"+
		"\u0000\u0000\u011b%\u0001\u0000\u0000\u0000\u011c\u0123\u0003*\u0015\u0000"+
		"\u011d\u011f\u0003(\u0014\u0000\u011e\u011d\u0001\u0000\u0000\u0000\u011e"+
		"\u011f\u0001\u0000\u0000\u0000\u011f\u0120\u0001\u0000\u0000\u0000\u0120"+
		"\u0122\u0003*\u0015\u0000\u0121\u011e\u0001\u0000\u0000\u0000\u0122\u0125"+
		"\u0001\u0000\u0000\u0000\u0123\u0121\u0001\u0000\u0000\u0000\u0123\u0124"+
		"\u0001\u0000\u0000\u0000\u0124\'\u0001\u0000\u0000\u0000\u0125\u0123\u0001"+
		"\u0000\u0000\u0000\u0126\u0127\u0007\u0004\u0000\u0000\u0127)\u0001\u0000"+
		"\u0000\u0000\u0128\u012a\u0003,\u0016\u0000\u0129\u0128\u0001\u0000\u0000"+
		"\u0000\u0129\u012a\u0001\u0000\u0000\u0000\u012a\u0132\u0001\u0000\u0000"+
		"\u0000\u012b\u0133\u0003.\u0017\u0000\u012c\u0133\u00030\u0018\u0000\u012d"+
		"\u0133\u00032\u0019\u0000\u012e\u0133\u00034\u001a\u0000\u012f\u0133\u0003"+
		"6\u001b\u0000\u0130\u0133\u00038\u001c\u0000\u0131\u0133\u0003:\u001d"+
		"\u0000\u0132\u012b\u0001\u0000\u0000\u0000\u0132\u012c\u0001\u0000\u0000"+
		"\u0000\u0132\u012d\u0001\u0000\u0000\u0000\u0132\u012e\u0001\u0000\u0000"+
		"\u0000\u0132\u012f\u0001\u0000\u0000\u0000\u0132\u0130\u0001\u0000\u0000"+
		"\u0000\u0132\u0131\u0001\u0000\u0000\u0000\u0133\u013c\u0001\u0000\u0000"+
		"\u0000\u0134\u013c\u0005N\u0000\u0000\u0135\u013c\u0005P\u0000\u0000\u0136"+
		"\u013c\u0005O\u0000\u0000\u0137\u013c\u0003<\u001e\u0000\u0138\u013c\u0003"+
		">\u001f\u0000\u0139\u013c\u0005L\u0000\u0000\u013a\u013c\u0003D\"\u0000"+
		"\u013b\u0129\u0001\u0000\u0000\u0000\u013b\u0134\u0001\u0000\u0000\u0000"+
		"\u013b\u0135\u0001\u0000\u0000\u0000\u013b\u0136\u0001\u0000\u0000\u0000"+
		"\u013b\u0137\u0001\u0000\u0000\u0000\u013b\u0138\u0001\u0000\u0000\u0000"+
		"\u013b\u0139\u0001\u0000\u0000\u0000\u013b\u013a\u0001\u0000\u0000\u0000"+
		"\u013c+\u0001\u0000\u0000\u0000\u013d\u013e\u0007\u0005\u0000\u0000\u013e"+
		"-\u0001\u0000\u0000\u0000\u013f\u0140\u0005M\u0000\u0000\u0140/\u0001"+
		"\u0000\u0000\u0000\u0141\u0142\u0005M\u0000\u0000\u0142\u0143\u0005\u001c"+
		"\u0000\u0000\u01431\u0001\u0000\u0000\u0000\u0144\u0145\u0005M\u0000\u0000"+
		"\u0145\u0146\u0007\u0006\u0000\u0000\u01463\u0001\u0000\u0000\u0000\u0147"+
		"\u0148\u0005M\u0000\u0000\u0148\u0149\u0007\u0007\u0000\u0000\u01495\u0001"+
		"\u0000\u0000\u0000\u014a\u014b\u0005M\u0000\u0000\u014b\u014c\u0007\b"+
		"\u0000\u0000\u014c7\u0001\u0000\u0000\u0000\u014d\u014e\u0005M\u0000\u0000"+
		"\u014e\u014f\u0007\t\u0000\u0000\u014f9\u0001\u0000\u0000\u0000\u0150"+
		"\u0151\u0005M\u0000\u0000\u0151\u0152\u0007\n\u0000\u0000\u0152;\u0001"+
		"\u0000\u0000\u0000\u0153\u0155\u0005\b\u0000\u0000\u0154\u0156\u0005Q"+
		"\u0000\u0000\u0155\u0154\u0001\u0000\u0000\u0000\u0156\u0157\u0001\u0000"+
		"\u0000\u0000\u0157\u0155\u0001\u0000\u0000\u0000\u0157\u0158\u0001\u0000"+
		"\u0000\u0000\u0158=\u0001\u0000\u0000\u0000\u0159\u015a\u0005P\u0000\u0000"+
		"\u015a\u015c\u0005\u0013\u0000\u0000\u015b\u015d\u0003@ \u0000\u015c\u015b"+
		"\u0001\u0000\u0000\u0000\u015c\u015d\u0001\u0000\u0000\u0000\u015d\u015e"+
		"\u0001\u0000\u0000\u0000\u015e\u015f\u0005\u0014\u0000\u0000\u015f?\u0001"+
		"\u0000\u0000\u0000\u0160\u0165\u0003B!\u0000\u0161\u0162\u0005\u0003\u0000"+
		"\u0000\u0162\u0164\u0003B!\u0000\u0163\u0161\u0001\u0000\u0000\u0000\u0164"+
		"\u0167\u0001\u0000\u0000\u0000\u0165\u0163\u0001\u0000\u0000\u0000\u0165"+
		"\u0166\u0001\u0000\u0000\u0000\u0166A\u0001\u0000\u0000\u0000\u0167\u0165"+
		"\u0001\u0000\u0000\u0000\u0168\u0169\u0003&\u0013\u0000\u0169C\u0001\u0000"+
		"\u0000\u0000\u016a\u016b\u0005\u001d\u0000\u0000\u016b\u016c\u0005\u0013"+
		"\u0000\u0000\u016c\u016d\u0003F#\u0000\u016d\u016e\u0005\u0014\u0000\u0000"+
		"\u016eE\u0001\u0000\u0000\u0000\u016f\u0174\u0003H$\u0000\u0170\u0171"+
		"\u0007\u0005\u0000\u0000\u0171\u0173\u0003H$\u0000\u0172\u0170\u0001\u0000"+
		"\u0000\u0000\u0173\u0176\u0001\u0000\u0000\u0000\u0174\u0172\u0001\u0000"+
		"\u0000\u0000\u0174\u0175\u0001\u0000\u0000\u0000\u0175G\u0001\u0000\u0000"+
		"\u0000\u0176\u0174\u0001\u0000\u0000\u0000\u0177\u017c\u0003J%\u0000\u0178"+
		"\u0179\u0007\u000b\u0000\u0000\u0179\u017b\u0003J%\u0000\u017a\u0178\u0001"+
		"\u0000\u0000\u0000\u017b\u017e\u0001\u0000\u0000\u0000\u017c\u017a\u0001"+
		"\u0000\u0000\u0000\u017c\u017d\u0001\u0000\u0000\u0000\u017dI\u0001\u0000"+
		"\u0000\u0000\u017e\u017c\u0001\u0000\u0000\u0000\u017f\u0189\u0003.\u0017"+
		"\u0000\u0180\u0189\u00032\u0019\u0000\u0181\u0189\u00030\u0018\u0000\u0182"+
		"\u0183\u0005\u0013\u0000\u0000\u0183\u0184\u0003F#\u0000\u0184\u0185\u0005"+
		"\u0014\u0000\u0000\u0185\u0189\u0001\u0000\u0000\u0000\u0186\u0189\u0003"+
		"D\"\u0000\u0187\u0189\u0005L\u0000\u0000\u0188\u017f\u0001\u0000\u0000"+
		"\u0000\u0188\u0180\u0001\u0000\u0000\u0000\u0188\u0181\u0001\u0000\u0000"+
		"\u0000\u0188\u0182\u0001\u0000\u0000\u0000\u0188\u0186\u0001\u0000\u0000"+
		"\u0000\u0188\u0187\u0001\u0000\u0000\u0000\u0189K\u0001\u0000\u0000\u0000"+
		"\u018a\u0197\u0003N\'\u0000\u018b\u0197\u0003P(\u0000\u018c\u0197\u0003"+
		"Z-\u0000\u018d\u0197\u0003`0\u0000\u018e\u0197\u0003b1\u0000\u018f\u0197"+
		"\u0003p8\u0000\u0190\u0197\u0003t:\u0000\u0191\u0197\u0003v;\u0000\u0192"+
		"\u0197\u0003x<\u0000\u0193\u0197\u0003z=\u0000\u0194\u0197\u0003|>\u0000"+
		"\u0195\u0197\u0003\u0082A\u0000\u0196\u018a\u0001\u0000\u0000\u0000\u0196"+
		"\u018b\u0001\u0000\u0000\u0000\u0196\u018c\u0001\u0000\u0000\u0000\u0196"+
		"\u018d\u0001\u0000\u0000\u0000\u0196\u018e\u0001\u0000\u0000\u0000\u0196"+
		"\u018f\u0001\u0000\u0000\u0000\u0196\u0190\u0001\u0000\u0000\u0000\u0196"+
		"\u0191\u0001\u0000\u0000\u0000\u0196\u0192\u0001\u0000\u0000\u0000\u0196"+
		"\u0193\u0001\u0000\u0000\u0000\u0196\u0194\u0001\u0000\u0000\u0000\u0196"+
		"\u0195\u0001\u0000\u0000\u0000\u0197M\u0001\u0000\u0000\u0000\u0198\u0199"+
		"\u0005 \u0000\u0000\u0199\u019b\u0007\f\u0000\u0000\u019a\u019c\u0003"+
		"R)\u0000\u019b\u019a\u0001\u0000\u0000\u0000\u019b\u019c\u0001\u0000\u0000"+
		"\u0000\u019c\u019d\u0001\u0000\u0000\u0000\u019d\u019e\u0005\u0019\u0000"+
		"\u0000\u019eO\u0001\u0000\u0000\u0000\u019f\u01a0\u0005!\u0000\u0000\u01a0"+
		"\u01a1\u0003R)\u0000\u01a1\u01a5\u0005\u0001\u0000\u0000\u01a2\u01a4\u0003"+
		"\u0002\u0001\u0000\u01a3\u01a2\u0001\u0000\u0000\u0000\u01a4\u01a7\u0001"+
		"\u0000\u0000\u0000\u01a5\u01a3\u0001\u0000\u0000\u0000\u01a5\u01a6\u0001"+
		"\u0000\u0000\u0000\u01a6\u01a8\u0001\u0000\u0000\u0000\u01a7\u01a5\u0001"+
		"\u0000\u0000\u0000\u01a8\u01a9\u0005\u0002\u0000\u0000\u01a9Q\u0001\u0000"+
		"\u0000\u0000\u01aa\u01af\u0003T*\u0000\u01ab\u01ac\u0005\u0003\u0000\u0000"+
		"\u01ac\u01ae\u0003T*\u0000\u01ad\u01ab\u0001\u0000\u0000\u0000\u01ae\u01b1"+
		"\u0001\u0000\u0000\u0000\u01af\u01ad\u0001\u0000\u0000\u0000\u01af\u01b0"+
		"\u0001\u0000\u0000\u0000\u01b0S\u0001\u0000\u0000\u0000\u01b1\u01af\u0001"+
		"\u0000\u0000\u0000\u01b2\u01b4\u0007\r\u0000\u0000\u01b3\u01b2\u0001\u0000"+
		"\u0000\u0000\u01b3\u01b4\u0001\u0000\u0000\u0000\u01b4\u01b5\u0001\u0000"+
		"\u0000\u0000\u01b5\u01ba\u0003V+\u0000\u01b6\u01b7\u0005.\u0000\u0000"+
		"\u01b7\u01b9\u0003X,\u0000\u01b8\u01b6\u0001\u0000\u0000\u0000\u01b9\u01bc"+
		"\u0001\u0000\u0000\u0000\u01ba\u01b8\u0001\u0000\u0000\u0000\u01ba\u01bb"+
		"\u0001\u0000\u0000\u0000\u01bb\u01c6\u0001\u0000\u0000\u0000\u01bc\u01ba"+
		"\u0001\u0000\u0000\u0000\u01bd\u01c2\u0003X,\u0000\u01be\u01bf\u0005."+
		"\u0000\u0000\u01bf\u01c1\u0003X,\u0000\u01c0\u01be\u0001\u0000\u0000\u0000"+
		"\u01c1\u01c4\u0001\u0000\u0000\u0000\u01c2\u01c0\u0001\u0000\u0000\u0000"+
		"\u01c2\u01c3\u0001\u0000\u0000\u0000\u01c3\u01c6\u0001\u0000\u0000\u0000"+
		"\u01c4\u01c2\u0001\u0000\u0000\u0000\u01c5\u01b3\u0001\u0000\u0000\u0000"+
		"\u01c5\u01bd\u0001\u0000\u0000\u0000\u01c6U\u0001\u0000\u0000\u0000\u01c7"+
		"\u01c8\u0005P\u0000\u0000\u01c8W\u0001\u0000\u0000\u0000\u01c9\u01ca\u0005"+
		"\u0013\u0000\u0000\u01ca\u01cd\u0005P\u0000\u0000\u01cb\u01cc\u0005\u0012"+
		"\u0000\u0000\u01cc\u01ce\u0003&\u0013\u0000\u01cd\u01cb\u0001\u0000\u0000"+
		"\u0000\u01cd\u01ce\u0001\u0000\u0000\u0000\u01ce\u01cf\u0001\u0000\u0000"+
		"\u0000\u01cf\u01d0\u0005\u0014\u0000\u0000\u01d0Y\u0001\u0000\u0000\u0000"+
		"\u01d1\u01d2\u0005\"\u0000\u0000\u01d2\u01d3\u0005P\u0000\u0000\u01d3"+
		"\u01d7\u0005\u0001\u0000\u0000\u01d4\u01d6\u0003\\.\u0000\u01d5\u01d4"+
		"\u0001\u0000\u0000\u0000\u01d6\u01d9\u0001\u0000\u0000\u0000\u01d7\u01d5"+
		"\u0001\u0000\u0000\u0000\u01d7\u01d8\u0001\u0000\u0000\u0000\u01d8\u01da"+
		"\u0001\u0000\u0000\u0000\u01d9\u01d7\u0001\u0000\u0000\u0000\u01da\u01db"+
		"\u0005\u0002\u0000\u0000\u01db[\u0001\u0000\u0000\u0000\u01dc\u01dd\u0003"+
		"^/\u0000\u01dd\u01e1\u0005\u0001\u0000\u0000\u01de\u01e0\u0003\"\u0011"+
		"\u0000\u01df\u01de\u0001\u0000\u0000\u0000\u01e0\u01e3\u0001\u0000\u0000"+
		"\u0000\u01e1\u01df\u0001\u0000\u0000\u0000\u01e1\u01e2\u0001\u0000\u0000"+
		"\u0000\u01e2\u01e4\u0001\u0000\u0000\u0000\u01e3\u01e1\u0001\u0000\u0000"+
		"\u0000\u01e4\u01e5\u0005\u0002\u0000\u0000\u01e5]\u0001\u0000\u0000\u0000"+
		"\u01e6\u01e7\u0006/\uffff\uffff\u0000\u01e7\u01eb\u00050\u0000\u0000\u01e8"+
		"\u01eb\u00051\u0000\u0000\u01e9\u01eb\u00030\u0018\u0000\u01ea\u01e6\u0001"+
		"\u0000\u0000\u0000\u01ea\u01e8\u0001\u0000\u0000\u0000\u01ea\u01e9\u0001"+
		"\u0000\u0000\u0000\u01eb\u01f1\u0001\u0000\u0000\u0000\u01ec\u01ed\n\u0001"+
		"\u0000\u0000\u01ed\u01ee\u0005\u0003\u0000\u0000\u01ee\u01f0\u0003^/\u0002"+
		"\u01ef\u01ec\u0001\u0000\u0000\u0000\u01f0\u01f3\u0001\u0000\u0000\u0000"+
		"\u01f1\u01ef\u0001\u0000\u0000\u0000\u01f1\u01f2\u0001\u0000\u0000\u0000"+
		"\u01f2_\u0001\u0000\u0000\u0000\u01f3\u01f1\u0001\u0000\u0000\u0000\u01f4"+
		"\u01f5\u0005#\u0000\u0000\u01f5\u01f9\u0005\u0001\u0000\u0000\u01f6\u01f8"+
		"\u0003\"\u0011\u0000\u01f7\u01f6\u0001\u0000\u0000\u0000\u01f8\u01fb\u0001"+
		"\u0000\u0000\u0000\u01f9\u01f7\u0001\u0000\u0000\u0000\u01f9\u01fa\u0001"+
		"\u0000\u0000\u0000\u01fa\u01fc\u0001\u0000\u0000\u0000\u01fb\u01f9\u0001"+
		"\u0000\u0000\u0000\u01fc\u01fd\u0005\u0002\u0000\u0000\u01fda\u0001\u0000"+
		"\u0000\u0000\u01fe\u01ff\u0005$\u0000\u0000\u01ff\u0200\u0003d2\u0000"+
		"\u0200\u0204\u0005\u0001\u0000\u0000\u0201\u0203\u0003\u0002\u0001\u0000"+
		"\u0202\u0201\u0001\u0000\u0000\u0000\u0203\u0206\u0001\u0000\u0000\u0000"+
		"\u0204\u0202\u0001\u0000\u0000\u0000\u0204\u0205\u0001\u0000\u0000\u0000"+
		"\u0205\u0207\u0001\u0000\u0000\u0000\u0206\u0204\u0001\u0000\u0000\u0000"+
		"\u0207\u0208\u0005\u0002\u0000\u0000\u0208c\u0001\u0000\u0000\u0000\u0209"+
		"\u020e\u0003f3\u0000\u020a\u020e\u0003h4\u0000\u020b\u020e\u0003j5\u0000"+
		"\u020c\u020e\u0003l6\u0000\u020d\u0209\u0001\u0000\u0000\u0000\u020d\u020a"+
		"\u0001\u0000\u0000\u0000\u020d\u020b\u0001\u0000\u0000\u0000\u020d\u020c"+
		"\u0001\u0000\u0000\u0000\u020ee\u0001\u0000\u0000\u0000\u020f\u0210\u0005"+
		"-\u0000\u0000\u0210\u0211\u0003l6\u0000\u0211g\u0001\u0000\u0000\u0000"+
		"\u0212\u0215\u0003l6\u0000\u0213\u0214\u0005.\u0000\u0000\u0214\u0216"+
		"\u0003l6\u0000\u0215\u0213\u0001\u0000\u0000\u0000\u0216\u0217\u0001\u0000"+
		"\u0000\u0000\u0217\u0215\u0001\u0000\u0000\u0000\u0217\u0218\u0001\u0000"+
		"\u0000\u0000\u0218i\u0001\u0000\u0000\u0000\u0219\u021c\u0003l6\u0000"+
		"\u021a\u021b\u0005/\u0000\u0000\u021b\u021d\u0003l6\u0000\u021c\u021a"+
		"\u0001\u0000\u0000\u0000\u021d\u021e\u0001\u0000\u0000\u0000\u021e\u021c"+
		"\u0001\u0000\u0000\u0000\u021e\u021f\u0001\u0000\u0000\u0000\u021fk\u0001"+
		"\u0000\u0000\u0000\u0220\u0221\u0005\u0013\u0000\u0000\u0221\u0222\u0003"+
		"d2\u0000\u0222\u0223\u0005\u0014\u0000\u0000\u0223\u0226\u0001\u0000\u0000"+
		"\u0000\u0224\u0226\u0003n7\u0000\u0225\u0220\u0001\u0000\u0000\u0000\u0225"+
		"\u0224\u0001\u0000\u0000\u0000\u0226m\u0001\u0000\u0000\u0000\u0227\u0228"+
		"\u0005\u0013\u0000\u0000\u0228\u0229\u0003\"\u0011\u0000\u0229\u022a\u0005"+
		"\u0014\u0000\u0000\u022ao\u0001\u0000\u0000\u0000\u022b\u022d\u0005%\u0000"+
		"\u0000\u022c\u022e\u0003r9\u0000\u022d\u022c\u0001\u0000\u0000\u0000\u022d"+
		"\u022e\u0001\u0000\u0000\u0000\u022e\u022f\u0001\u0000\u0000\u0000\u022f"+
		"\u0233\u0005\u0001\u0000\u0000\u0230\u0232\u0003\"\u0011\u0000\u0231\u0230"+
		"\u0001\u0000\u0000\u0000\u0232\u0235\u0001\u0000\u0000\u0000\u0233\u0231"+
		"\u0001\u0000\u0000\u0000\u0233\u0234\u0001\u0000\u0000\u0000\u0234\u0236"+
		"\u0001\u0000\u0000\u0000\u0235\u0233\u0001\u0000\u0000\u0000\u0236\u0237"+
		"\u0005\u0002\u0000\u0000\u0237q\u0001\u0000\u0000\u0000\u0238\u0239\u0005"+
		"\u0012\u0000\u0000\u0239\u023a\u0005P\u0000\u0000\u023as\u0001\u0000\u0000"+
		"\u0000\u023b\u023d\u0005&\u0000\u0000\u023c\u023e\u0005P\u0000\u0000\u023d"+
		"\u023c\u0001\u0000\u0000\u0000\u023d\u023e\u0001\u0000\u0000\u0000\u023e"+
		"\u023f\u0001\u0000\u0000\u0000\u023f\u0240\u0007\f\u0000\u0000\u0240\u0241"+
		"\u0005\u0019\u0000\u0000\u0241u\u0001\u0000\u0000\u0000\u0242\u0243\u0005"+
		"\'\u0000\u0000\u0243\u0244\u0005N\u0000\u0000\u0244\u0245\u0005\u0019"+
		"\u0000\u0000\u0245w\u0001\u0000\u0000\u0000\u0246\u0247\u0005(\u0000\u0000"+
		"\u0247\u024b\u0005\u0001\u0000\u0000\u0248\u024a\u0003\"\u0011\u0000\u0249"+
		"\u0248\u0001\u0000\u0000\u0000\u024a\u024d\u0001\u0000\u0000\u0000\u024b"+
		"\u0249\u0001\u0000\u0000\u0000\u024b\u024c\u0001\u0000\u0000\u0000\u024c"+
		"\u024e\u0001\u0000\u0000\u0000\u024d\u024b\u0001\u0000\u0000\u0000\u024e"+
		"\u024f\u0005\u0002\u0000\u0000\u024fy\u0001\u0000\u0000\u0000\u0250\u0251"+
		"\u0005)\u0000\u0000\u0251\u0252\u0005P\u0000\u0000\u0252\u0256\u0005\u0001"+
		"\u0000\u0000\u0253\u0255\u0003\"\u0011\u0000\u0254\u0253\u0001\u0000\u0000"+
		"\u0000\u0255\u0258\u0001\u0000\u0000\u0000\u0256\u0254\u0001\u0000\u0000"+
		"\u0000\u0256\u0257\u0001\u0000\u0000\u0000\u0257\u0259\u0001\u0000\u0000"+
		"\u0000\u0258\u0256\u0001\u0000\u0000\u0000\u0259\u025a\u0005\u0002\u0000"+
		"\u0000\u025a{\u0001\u0000\u0000\u0000\u025b\u025d\u0005*\u0000\u0000\u025c"+
		"\u025e\u0003~?\u0000\u025d\u025c\u0001\u0000\u0000\u0000\u025e\u025f\u0001"+
		"\u0000\u0000\u0000\u025f\u025d\u0001\u0000\u0000\u0000\u025f\u0260\u0001"+
		"\u0000\u0000\u0000\u0260\u0261\u0001\u0000\u0000\u0000\u0261\u0265\u0005"+
		"\u0001\u0000\u0000\u0262\u0264\u0003\u0080@\u0000\u0263\u0262\u0001\u0000"+
		"\u0000\u0000\u0264\u0267\u0001\u0000\u0000\u0000\u0265\u0263\u0001\u0000"+
		"\u0000\u0000\u0265\u0266\u0001\u0000\u0000\u0000\u0266\u0268\u0001\u0000"+
		"\u0000\u0000\u0267\u0265\u0001\u0000\u0000\u0000\u0268\u0269\u0005\u0002"+
		"\u0000\u0000\u0269}\u0001\u0000\u0000\u0000\u026a\u026b\u0007\u0001\u0000"+
		"\u0000\u026b\u007f\u0001\u0000\u0000\u0000\u026c\u026d\u0005\u001e\u0000"+
		"\u0000\u026d\u026e\u0005P\u0000\u0000\u026e\u0272\u0005\u0001\u0000\u0000"+
		"\u026f\u0271\u0003\"\u0011\u0000\u0270\u026f\u0001\u0000\u0000\u0000\u0271"+
		"\u0274\u0001\u0000\u0000\u0000\u0272\u0270\u0001\u0000\u0000\u0000\u0272"+
		"\u0273\u0001\u0000\u0000\u0000\u0273\u0275\u0001\u0000\u0000\u0000\u0274"+
		"\u0272\u0001\u0000\u0000\u0000\u0275\u0276\u0005\u0002\u0000\u0000\u0276"+
		"\u0081\u0001\u0000\u0000\u0000\u0277\u0278\u0005+\u0000\u0000\u0278\u0279"+
		"\u0005L\u0000\u0000\u0279\u027d\u0005\u0001\u0000\u0000\u027a\u027c\u0003"+
		"\"\u0011\u0000\u027b\u027a\u0001\u0000\u0000\u0000\u027c\u027f\u0001\u0000"+
		"\u0000\u0000\u027d\u027b\u0001\u0000\u0000\u0000\u027d\u027e\u0001\u0000"+
		"\u0000\u0000\u027e\u0280\u0001\u0000\u0000\u0000\u027f\u027d\u0001\u0000"+
		"\u0000\u0000\u0280\u0281\u0005\u0002\u0000\u0000\u0281\u0083\u0001\u0000"+
		"\u0000\u0000\u0282\u0288\u0003*\u0015\u0000\u0283\u0284\u0003(\u0014\u0000"+
		"\u0284\u0285\u0003*\u0015\u0000\u0285\u0287\u0001\u0000\u0000\u0000\u0286"+
		"\u0283\u0001\u0000\u0000\u0000\u0287\u028a\u0001\u0000\u0000\u0000\u0288"+
		"\u0286\u0001\u0000\u0000\u0000\u0288\u0289\u0001\u0000\u0000\u0000\u0289"+
		"\u0085\u0001\u0000\u0000\u0000\u028a\u0288\u0001\u0000\u0000\u0000\u028b"+
		"\u028c\u0005\u001f\u0000\u0000\u028c\u0087\u0001\u0000\u0000\u0000=\u008b"+
		"\u0093\u009a\u00a4\u00ad\u00b4\u00ba\u00bc\u00c3\u00c5\u00c7\u00d8\u00e0"+
		"\u00e8\u00f6\u00fc\u0105\u010d\u010f\u0116\u011a\u011e\u0123\u0129\u0132"+
		"\u013b\u0157\u015c\u0165\u0174\u017c\u0188\u0196\u019b\u01a5\u01af\u01b3"+
		"\u01ba\u01c2\u01c5\u01cd\u01d7\u01e1\u01ea\u01f1\u01f9\u0204\u020d\u0217"+
		"\u021e\u0225\u022d\u0233\u023d\u024b\u0256\u025f\u0265\u0272\u027d\u0288";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}