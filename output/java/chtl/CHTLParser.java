// Generated from CHTL.g4 by ANTLR 4.13.1
package chtl;
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
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, T__30=31, 
		T__31=32, T__32=33, T__33=34, T__34=35, T__35=36, T__36=37, T__37=38, 
		T__38=39, T__39=40, T__40=41, T__41=42, T__42=43, T__43=44, SINGLE_LINE_COMMENT=45, 
		MULTI_LINE_COMMENT=46, GENERATOR_COMMENT=47, BOOLEAN=48, NUMBER=49, STRING_LITERAL=50, 
		UNQUOTED_LITERAL=51, IDENTIFIER=52, WS=53;
	public static final int
		RULE_program = 0, RULE_topLevelStatement = 1, RULE_configurationBlock = 2, 
		RULE_configurationItem = 3, RULE_configKey = 4, RULE_configValue = 5, 
		RULE_configValueArray = 6, RULE_configArrayItem = 7, RULE_nameConfigItem = 8, 
		RULE_namespaceDeclaration = 9, RULE_namespaceBody = 10, RULE_namespaceContent = 11, 
		RULE_importStatement = 12, RULE_importType = 13, RULE_importPath = 14, 
		RULE_dottedPath = 15, RULE_templateDeclaration = 16, RULE_templateType = 17, 
		RULE_templateBody = 18, RULE_templateContent = 19, RULE_templateInheritance = 20, 
		RULE_customDeclaration = 21, RULE_customType = 22, RULE_customBody = 23, 
		RULE_customContent = 24, RULE_customInheritance = 25, RULE_customSpecialization = 26, 
		RULE_specializationContent = 27, RULE_deleteStatement = 28, RULE_deleteTarget = 29, 
		RULE_insertStatement = 30, RULE_insertPosition = 31, RULE_elementSelector = 32, 
		RULE_insertContent = 33, RULE_originBlock = 34, RULE_originType = 35, 
		RULE_originContent = 36, RULE_htmlElement = 37, RULE_globalStyleElement = 38, 
		RULE_globalStyleContent = 39, RULE_elementName = 40, RULE_elementIndexAccess = 41, 
		RULE_elementBody = 42, RULE_elementContent = 43, RULE_attribute = 44, 
		RULE_attributeName = 45, RULE_attributeValue = 46, RULE_textContent = 47, 
		RULE_styleBlock = 48, RULE_styleContent = 49, RULE_styleProperty = 50, 
		RULE_propertyName = 51, RULE_propertyValue = 52, RULE_cssSelector = 53, 
		RULE_pseudoClass = 54, RULE_pseudoElement = 55, RULE_cssFunction = 56, 
		RULE_cssArguments = 57, RULE_cssArgument = 58, RULE_scriptBlock = 59, 
		RULE_scriptContent = 60, RULE_elementUsage = 61, RULE_elementSpecialization = 62, 
		RULE_elementSpecializationContent = 63, RULE_styleUsage = 64, RULE_styleSpecialization = 65, 
		RULE_variableDefinition = 66, RULE_variableUsage = 67, RULE_variableArguments = 68, 
		RULE_variableArgument = 69, RULE_variableAssignment = 70, RULE_namespacePath = 71, 
		RULE_exceptConstraint = 72, RULE_exceptTarget = 73, RULE_comment = 74;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "topLevelStatement", "configurationBlock", "configurationItem", 
			"configKey", "configValue", "configValueArray", "configArrayItem", "nameConfigItem", 
			"namespaceDeclaration", "namespaceBody", "namespaceContent", "importStatement", 
			"importType", "importPath", "dottedPath", "templateDeclaration", "templateType", 
			"templateBody", "templateContent", "templateInheritance", "customDeclaration", 
			"customType", "customBody", "customContent", "customInheritance", "customSpecialization", 
			"specializationContent", "deleteStatement", "deleteTarget", "insertStatement", 
			"insertPosition", "elementSelector", "insertContent", "originBlock", 
			"originType", "originContent", "htmlElement", "globalStyleElement", "globalStyleContent", 
			"elementName", "elementIndexAccess", "elementBody", "elementContent", 
			"attribute", "attributeName", "attributeValue", "textContent", "styleBlock", 
			"styleContent", "styleProperty", "propertyName", "propertyValue", "cssSelector", 
			"pseudoClass", "pseudoElement", "cssFunction", "cssArguments", "cssArgument", 
			"scriptBlock", "scriptContent", "elementUsage", "elementSpecialization", 
			"elementSpecializationContent", "styleUsage", "styleSpecialization", 
			"variableDefinition", "variableUsage", "variableArguments", "variableArgument", 
			"variableAssignment", "namespacePath", "exceptConstraint", "exceptTarget", 
			"comment"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'[Configuration]'", "'{'", "'}'", "'='", "';'", "'[Name]'", "'['", 
			"','", "']'", "'@'", "'[Namespace]'", "'[Import]'", "'from'", "'as'", 
			"'@Html'", "'@Style'", "'@JavaScript'", "'@Chtl'", "'[Custom]'", "'[Template]'", 
			"'.'", "'@Element'", "'@Var'", "'inherit'", "'delete'", "'insert'", "'after'", 
			"'before'", "'replace'", "'at'", "'top'", "'bottom'", "'[Origin]'", "'style'", 
			"'text'", "'script'", "':'", "'-'", "'#'", "'&'", "'::'", "'('", "')'", 
			"'except'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, "SINGLE_LINE_COMMENT", 
			"MULTI_LINE_COMMENT", "GENERATOR_COMMENT", "BOOLEAN", "NUMBER", "STRING_LITERAL", 
			"UNQUOTED_LITERAL", "IDENTIFIER", "WS"
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
		public List<TopLevelStatementContext> topLevelStatement() {
			return getRuleContexts(TopLevelStatementContext.class);
		}
		public TopLevelStatementContext topLevelStatement(int i) {
			return getRuleContext(TopLevelStatementContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitProgram(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(153);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4750019082590210L) != 0)) {
				{
				{
				setState(150);
				topLevelStatement();
				}
				}
				setState(155);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(156);
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
	public static class TopLevelStatementContext extends ParserRuleContext {
		public ConfigurationBlockContext configurationBlock() {
			return getRuleContext(ConfigurationBlockContext.class,0);
		}
		public NamespaceDeclarationContext namespaceDeclaration() {
			return getRuleContext(NamespaceDeclarationContext.class,0);
		}
		public ImportStatementContext importStatement() {
			return getRuleContext(ImportStatementContext.class,0);
		}
		public TemplateDeclarationContext templateDeclaration() {
			return getRuleContext(TemplateDeclarationContext.class,0);
		}
		public CustomDeclarationContext customDeclaration() {
			return getRuleContext(CustomDeclarationContext.class,0);
		}
		public OriginBlockContext originBlock() {
			return getRuleContext(OriginBlockContext.class,0);
		}
		public HtmlElementContext htmlElement() {
			return getRuleContext(HtmlElementContext.class,0);
		}
		public StyleBlockContext styleBlock() {
			return getRuleContext(StyleBlockContext.class,0);
		}
		public ScriptBlockContext scriptBlock() {
			return getRuleContext(ScriptBlockContext.class,0);
		}
		public CommentContext comment() {
			return getRuleContext(CommentContext.class,0);
		}
		public TopLevelStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_topLevelStatement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterTopLevelStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitTopLevelStatement(this);
		}
	}

	public final TopLevelStatementContext topLevelStatement() throws RecognitionException {
		TopLevelStatementContext _localctx = new TopLevelStatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_topLevelStatement);
		try {
			setState(168);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(158);
				configurationBlock();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(159);
				namespaceDeclaration();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(160);
				importStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(161);
				templateDeclaration();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(162);
				customDeclaration();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(163);
				originBlock();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(164);
				htmlElement();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(165);
				styleBlock();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(166);
				scriptBlock();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(167);
				comment();
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
	public static class ConfigurationBlockContext extends ParserRuleContext {
		public List<ConfigurationItemContext> configurationItem() {
			return getRuleContexts(ConfigurationItemContext.class);
		}
		public ConfigurationItemContext configurationItem(int i) {
			return getRuleContext(ConfigurationItemContext.class,i);
		}
		public ConfigurationBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_configurationBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterConfigurationBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitConfigurationBlock(this);
		}
	}

	public final ConfigurationBlockContext configurationBlock() throws RecognitionException {
		ConfigurationBlockContext _localctx = new ConfigurationBlockContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_configurationBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(170);
			match(T__0);
			setState(171);
			match(T__1);
			setState(175);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__5 || _la==IDENTIFIER) {
				{
				{
				setState(172);
				configurationItem();
				}
				}
				setState(177);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(178);
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
	public static class ConfigurationItemContext extends ParserRuleContext {
		public ConfigKeyContext configKey() {
			return getRuleContext(ConfigKeyContext.class,0);
		}
		public ConfigValueContext configValue() {
			return getRuleContext(ConfigValueContext.class,0);
		}
		public List<NameConfigItemContext> nameConfigItem() {
			return getRuleContexts(NameConfigItemContext.class);
		}
		public NameConfigItemContext nameConfigItem(int i) {
			return getRuleContext(NameConfigItemContext.class,i);
		}
		public ConfigurationItemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_configurationItem; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterConfigurationItem(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitConfigurationItem(this);
		}
	}

	public final ConfigurationItemContext configurationItem() throws RecognitionException {
		ConfigurationItemContext _localctx = new ConfigurationItemContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_configurationItem);
		int _la;
		try {
			setState(194);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(180);
				configKey();
				setState(181);
				match(T__3);
				setState(182);
				configValue();
				setState(183);
				match(T__4);
				}
				break;
			case T__5:
				enterOuterAlt(_localctx, 2);
				{
				setState(185);
				match(T__5);
				setState(186);
				match(T__1);
				setState(190);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==IDENTIFIER) {
					{
					{
					setState(187);
					nameConfigItem();
					}
					}
					setState(192);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(193);
				match(T__2);
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
	public static class ConfigKeyContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public ConfigKeyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_configKey; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterConfigKey(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitConfigKey(this);
		}
	}

	public final ConfigKeyContext configKey() throws RecognitionException {
		ConfigKeyContext _localctx = new ConfigKeyContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_configKey);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(196);
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
	public static class ConfigValueContext extends ParserRuleContext {
		public TerminalNode STRING_LITERAL() { return getToken(CHTLParser.STRING_LITERAL, 0); }
		public TerminalNode NUMBER() { return getToken(CHTLParser.NUMBER, 0); }
		public TerminalNode BOOLEAN() { return getToken(CHTLParser.BOOLEAN, 0); }
		public ConfigValueArrayContext configValueArray() {
			return getRuleContext(ConfigValueArrayContext.class,0);
		}
		public ConfigValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_configValue; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterConfigValue(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitConfigValue(this);
		}
	}

	public final ConfigValueContext configValue() throws RecognitionException {
		ConfigValueContext _localctx = new ConfigValueContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_configValue);
		try {
			setState(202);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case STRING_LITERAL:
				enterOuterAlt(_localctx, 1);
				{
				setState(198);
				match(STRING_LITERAL);
				}
				break;
			case NUMBER:
				enterOuterAlt(_localctx, 2);
				{
				setState(199);
				match(NUMBER);
				}
				break;
			case BOOLEAN:
				enterOuterAlt(_localctx, 3);
				{
				setState(200);
				match(BOOLEAN);
				}
				break;
			case T__6:
				enterOuterAlt(_localctx, 4);
				{
				setState(201);
				configValueArray();
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
	public static class ConfigValueArrayContext extends ParserRuleContext {
		public List<ConfigArrayItemContext> configArrayItem() {
			return getRuleContexts(ConfigArrayItemContext.class);
		}
		public ConfigArrayItemContext configArrayItem(int i) {
			return getRuleContext(ConfigArrayItemContext.class,i);
		}
		public ConfigValueArrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_configValueArray; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterConfigValueArray(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitConfigValueArray(this);
		}
	}

	public final ConfigValueArrayContext configValueArray() throws RecognitionException {
		ConfigValueArrayContext _localctx = new ConfigValueArrayContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_configValueArray);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(204);
			match(T__6);
			setState(205);
			configArrayItem();
			setState(210);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__7) {
				{
				{
				setState(206);
				match(T__7);
				setState(207);
				configArrayItem();
				}
				}
				setState(212);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(213);
			match(T__8);
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
	public static class ConfigArrayItemContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(CHTLParser.STRING_LITERAL, 0); }
		public ConfigArrayItemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_configArrayItem; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterConfigArrayItem(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitConfigArrayItem(this);
		}
	}

	public final ConfigArrayItemContext configArrayItem() throws RecognitionException {
		ConfigArrayItemContext _localctx = new ConfigArrayItemContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_configArrayItem);
		try {
			setState(218);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__9:
				enterOuterAlt(_localctx, 1);
				{
				setState(215);
				match(T__9);
				setState(216);
				match(IDENTIFIER);
				}
				break;
			case STRING_LITERAL:
				enterOuterAlt(_localctx, 2);
				{
				setState(217);
				match(STRING_LITERAL);
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
	public static class NameConfigItemContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public ConfigValueContext configValue() {
			return getRuleContext(ConfigValueContext.class,0);
		}
		public ConfigValueArrayContext configValueArray() {
			return getRuleContext(ConfigValueArrayContext.class,0);
		}
		public NameConfigItemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nameConfigItem; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterNameConfigItem(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitNameConfigItem(this);
		}
	}

	public final NameConfigItemContext nameConfigItem() throws RecognitionException {
		NameConfigItemContext _localctx = new NameConfigItemContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_nameConfigItem);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(220);
			match(IDENTIFIER);
			setState(221);
			match(T__3);
			setState(224);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				{
				setState(222);
				configValue();
				}
				break;
			case 2:
				{
				setState(223);
				configValueArray();
				}
				break;
			}
			setState(226);
			match(T__4);
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
	public static class NamespaceDeclarationContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public NamespaceBodyContext namespaceBody() {
			return getRuleContext(NamespaceBodyContext.class,0);
		}
		public NamespaceDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespaceDeclaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterNamespaceDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitNamespaceDeclaration(this);
		}
	}

	public final NamespaceDeclarationContext namespaceDeclaration() throws RecognitionException {
		NamespaceDeclarationContext _localctx = new NamespaceDeclarationContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_namespaceDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(228);
			match(T__10);
			setState(229);
			match(IDENTIFIER);
			setState(231);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(230);
				namespaceBody();
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
	public static class NamespaceBodyContext extends ParserRuleContext {
		public List<NamespaceContentContext> namespaceContent() {
			return getRuleContexts(NamespaceContentContext.class);
		}
		public NamespaceContentContext namespaceContent(int i) {
			return getRuleContext(NamespaceContentContext.class,i);
		}
		public NamespaceBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespaceBody; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterNamespaceBody(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitNamespaceBody(this);
		}
	}

	public final NamespaceBodyContext namespaceBody() throws RecognitionException {
		NamespaceBodyContext _localctx = new NamespaceBodyContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_namespaceBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(233);
			match(T__1);
			setState(237);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 17592187619328L) != 0)) {
				{
				{
				setState(234);
				namespaceContent();
				}
				}
				setState(239);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(240);
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
	public static class NamespaceContentContext extends ParserRuleContext {
		public NamespaceDeclarationContext namespaceDeclaration() {
			return getRuleContext(NamespaceDeclarationContext.class,0);
		}
		public TemplateDeclarationContext templateDeclaration() {
			return getRuleContext(TemplateDeclarationContext.class,0);
		}
		public CustomDeclarationContext customDeclaration() {
			return getRuleContext(CustomDeclarationContext.class,0);
		}
		public ExceptConstraintContext exceptConstraint() {
			return getRuleContext(ExceptConstraintContext.class,0);
		}
		public NamespaceContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespaceContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterNamespaceContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitNamespaceContent(this);
		}
	}

	public final NamespaceContentContext namespaceContent() throws RecognitionException {
		NamespaceContentContext _localctx = new NamespaceContentContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_namespaceContent);
		try {
			setState(246);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__10:
				enterOuterAlt(_localctx, 1);
				{
				setState(242);
				namespaceDeclaration();
				}
				break;
			case T__19:
				enterOuterAlt(_localctx, 2);
				{
				setState(243);
				templateDeclaration();
				}
				break;
			case T__18:
				enterOuterAlt(_localctx, 3);
				{
				setState(244);
				customDeclaration();
				}
				break;
			case T__43:
				enterOuterAlt(_localctx, 4);
				{
				setState(245);
				exceptConstraint();
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
	public static class ImportStatementContext extends ParserRuleContext {
		public ImportTypeContext importType() {
			return getRuleContext(ImportTypeContext.class,0);
		}
		public ImportPathContext importPath() {
			return getRuleContext(ImportPathContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public ImportStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_importStatement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterImportStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitImportStatement(this);
		}
	}

	public final ImportStatementContext importStatement() throws RecognitionException {
		ImportStatementContext _localctx = new ImportStatementContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_importStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(248);
			match(T__11);
			setState(249);
			importType();
			setState(250);
			match(T__12);
			setState(251);
			importPath();
			setState(254);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__13) {
				{
				setState(252);
				match(T__13);
				setState(253);
				match(IDENTIFIER);
				}
			}

			setState(257);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__4) {
				{
				setState(256);
				match(T__4);
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
	public static class ImportTypeContext extends ParserRuleContext {
		public CustomTypeContext customType() {
			return getRuleContext(CustomTypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public TemplateTypeContext templateType() {
			return getRuleContext(TemplateTypeContext.class,0);
		}
		public ImportTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_importType; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterImportType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitImportType(this);
		}
	}

	public final ImportTypeContext importType() throws RecognitionException {
		ImportTypeContext _localctx = new ImportTypeContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_importType);
		try {
			setState(271);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__14:
				enterOuterAlt(_localctx, 1);
				{
				setState(259);
				match(T__14);
				}
				break;
			case T__15:
				enterOuterAlt(_localctx, 2);
				{
				setState(260);
				match(T__15);
				}
				break;
			case T__16:
				enterOuterAlt(_localctx, 3);
				{
				setState(261);
				match(T__16);
				}
				break;
			case T__17:
				enterOuterAlt(_localctx, 4);
				{
				setState(262);
				match(T__17);
				}
				break;
			case T__18:
				enterOuterAlt(_localctx, 5);
				{
				setState(263);
				match(T__18);
				setState(264);
				customType();
				setState(265);
				match(IDENTIFIER);
				}
				break;
			case T__19:
				enterOuterAlt(_localctx, 6);
				{
				setState(267);
				match(T__19);
				setState(268);
				templateType();
				setState(269);
				match(IDENTIFIER);
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
		public TerminalNode STRING_LITERAL() { return getToken(CHTLParser.STRING_LITERAL, 0); }
		public DottedPathContext dottedPath() {
			return getRuleContext(DottedPathContext.class,0);
		}
		public ImportPathContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_importPath; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterImportPath(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitImportPath(this);
		}
	}

	public final ImportPathContext importPath() throws RecognitionException {
		ImportPathContext _localctx = new ImportPathContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_importPath);
		try {
			setState(275);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case STRING_LITERAL:
				enterOuterAlt(_localctx, 1);
				{
				setState(273);
				match(STRING_LITERAL);
				}
				break;
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				setState(274);
				dottedPath();
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
	public static class DottedPathContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(CHTLParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(CHTLParser.IDENTIFIER, i);
		}
		public DottedPathContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_dottedPath; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterDottedPath(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitDottedPath(this);
		}
	}

	public final DottedPathContext dottedPath() throws RecognitionException {
		DottedPathContext _localctx = new DottedPathContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_dottedPath);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(277);
			match(IDENTIFIER);
			setState(282);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__20) {
				{
				{
				setState(278);
				match(T__20);
				setState(279);
				match(IDENTIFIER);
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
	public static class TemplateDeclarationContext extends ParserRuleContext {
		public TemplateTypeContext templateType() {
			return getRuleContext(TemplateTypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public TemplateBodyContext templateBody() {
			return getRuleContext(TemplateBodyContext.class,0);
		}
		public TemplateDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateDeclaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterTemplateDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitTemplateDeclaration(this);
		}
	}

	public final TemplateDeclarationContext templateDeclaration() throws RecognitionException {
		TemplateDeclarationContext _localctx = new TemplateDeclarationContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_templateDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(285);
			match(T__19);
			setState(286);
			templateType();
			setState(287);
			match(IDENTIFIER);
			setState(288);
			templateBody();
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
	public static class TemplateTypeContext extends ParserRuleContext {
		public TemplateTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateType; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterTemplateType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitTemplateType(this);
		}
	}

	public final TemplateTypeContext templateType() throws RecognitionException {
		TemplateTypeContext _localctx = new TemplateTypeContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_templateType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(290);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 12648448L) != 0)) ) {
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
	public static class TemplateBodyContext extends ParserRuleContext {
		public List<TemplateContentContext> templateContent() {
			return getRuleContexts(TemplateContentContext.class);
		}
		public TemplateContentContext templateContent(int i) {
			return getRuleContext(TemplateContentContext.class,i);
		}
		public TemplateBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateBody; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterTemplateBody(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitTemplateBody(this);
		}
	}

	public final TemplateBodyContext templateBody() throws RecognitionException {
		TemplateBodyContext _localctx = new TemplateBodyContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_templateBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(292);
			match(T__1);
			setState(296);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4503719915880448L) != 0)) {
				{
				{
				setState(293);
				templateContent();
				}
				}
				setState(298);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(299);
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
	public static class TemplateContentContext extends ParserRuleContext {
		public StylePropertyContext styleProperty() {
			return getRuleContext(StylePropertyContext.class,0);
		}
		public HtmlElementContext htmlElement() {
			return getRuleContext(HtmlElementContext.class,0);
		}
		public TemplateInheritanceContext templateInheritance() {
			return getRuleContext(TemplateInheritanceContext.class,0);
		}
		public VariableDefinitionContext variableDefinition() {
			return getRuleContext(VariableDefinitionContext.class,0);
		}
		public TemplateContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterTemplateContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitTemplateContent(this);
		}
	}

	public final TemplateContentContext templateContent() throws RecognitionException {
		TemplateContentContext _localctx = new TemplateContentContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_templateContent);
		try {
			setState(305);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(301);
				styleProperty();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(302);
				htmlElement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(303);
				templateInheritance();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(304);
				variableDefinition();
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
	public static class TemplateInheritanceContext extends ParserRuleContext {
		public TemplateTypeContext templateType() {
			return getRuleContext(TemplateTypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public TemplateInheritanceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateInheritance; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterTemplateInheritance(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitTemplateInheritance(this);
		}
	}

	public final TemplateInheritanceContext templateInheritance() throws RecognitionException {
		TemplateInheritanceContext _localctx = new TemplateInheritanceContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_templateInheritance);
		try {
			setState(316);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__15:
			case T__21:
			case T__22:
				enterOuterAlt(_localctx, 1);
				{
				setState(307);
				templateType();
				setState(308);
				match(IDENTIFIER);
				setState(309);
				match(T__4);
				}
				break;
			case T__23:
				enterOuterAlt(_localctx, 2);
				{
				setState(311);
				match(T__23);
				setState(312);
				templateType();
				setState(313);
				match(IDENTIFIER);
				setState(314);
				match(T__4);
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
	public static class CustomDeclarationContext extends ParserRuleContext {
		public CustomTypeContext customType() {
			return getRuleContext(CustomTypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public CustomBodyContext customBody() {
			return getRuleContext(CustomBodyContext.class,0);
		}
		public CustomDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_customDeclaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCustomDeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCustomDeclaration(this);
		}
	}

	public final CustomDeclarationContext customDeclaration() throws RecognitionException {
		CustomDeclarationContext _localctx = new CustomDeclarationContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_customDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(318);
			match(T__18);
			setState(319);
			customType();
			setState(320);
			match(IDENTIFIER);
			setState(321);
			customBody();
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
	public static class CustomTypeContext extends ParserRuleContext {
		public CustomTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_customType; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCustomType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCustomType(this);
		}
	}

	public final CustomTypeContext customType() throws RecognitionException {
		CustomTypeContext _localctx = new CustomTypeContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_customType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(323);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 12648448L) != 0)) ) {
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
	public static class CustomBodyContext extends ParserRuleContext {
		public List<CustomContentContext> customContent() {
			return getRuleContexts(CustomContentContext.class);
		}
		public CustomContentContext customContent(int i) {
			return getRuleContext(CustomContentContext.class,i);
		}
		public CustomBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_customBody; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCustomBody(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCustomBody(this);
		}
	}

	public final CustomBodyContext customBody() throws RecognitionException {
		CustomBodyContext _localctx = new CustomBodyContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_customBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(325);
			match(T__1);
			setState(329);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4503719999766528L) != 0)) {
				{
				{
				setState(326);
				customContent();
				}
				}
				setState(331);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(332);
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
	public static class CustomContentContext extends ParserRuleContext {
		public StylePropertyContext styleProperty() {
			return getRuleContext(StylePropertyContext.class,0);
		}
		public HtmlElementContext htmlElement() {
			return getRuleContext(HtmlElementContext.class,0);
		}
		public CustomInheritanceContext customInheritance() {
			return getRuleContext(CustomInheritanceContext.class,0);
		}
		public VariableDefinitionContext variableDefinition() {
			return getRuleContext(VariableDefinitionContext.class,0);
		}
		public DeleteStatementContext deleteStatement() {
			return getRuleContext(DeleteStatementContext.class,0);
		}
		public InsertStatementContext insertStatement() {
			return getRuleContext(InsertStatementContext.class,0);
		}
		public CustomContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_customContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCustomContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCustomContent(this);
		}
	}

	public final CustomContentContext customContent() throws RecognitionException {
		CustomContentContext _localctx = new CustomContentContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_customContent);
		try {
			setState(340);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(334);
				styleProperty();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(335);
				htmlElement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(336);
				customInheritance();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(337);
				variableDefinition();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(338);
				deleteStatement();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(339);
				insertStatement();
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
	public static class CustomInheritanceContext extends ParserRuleContext {
		public CustomTypeContext customType() {
			return getRuleContext(CustomTypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public CustomSpecializationContext customSpecialization() {
			return getRuleContext(CustomSpecializationContext.class,0);
		}
		public TemplateTypeContext templateType() {
			return getRuleContext(TemplateTypeContext.class,0);
		}
		public CustomInheritanceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_customInheritance; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCustomInheritance(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCustomInheritance(this);
		}
	}

	public final CustomInheritanceContext customInheritance() throws RecognitionException {
		CustomInheritanceContext _localctx = new CustomInheritanceContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_customInheritance);
		int _la;
		try {
			setState(358);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,26,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(342);
				customType();
				setState(343);
				match(IDENTIFIER);
				setState(345);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(344);
					customSpecialization();
					}
				}

				setState(348);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__4) {
					{
					setState(347);
					match(T__4);
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(350);
				templateType();
				setState(351);
				match(IDENTIFIER);
				setState(353);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(352);
					customSpecialization();
					}
				}

				setState(356);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__4) {
					{
					setState(355);
					match(T__4);
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
	public static class CustomSpecializationContext extends ParserRuleContext {
		public List<SpecializationContentContext> specializationContent() {
			return getRuleContexts(SpecializationContentContext.class);
		}
		public SpecializationContentContext specializationContent(int i) {
			return getRuleContext(SpecializationContentContext.class,i);
		}
		public CustomSpecializationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_customSpecialization; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCustomSpecialization(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCustomSpecialization(this);
		}
	}

	public final CustomSpecializationContext customSpecialization() throws RecognitionException {
		CustomSpecializationContext _localctx = new CustomSpecializationContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_customSpecialization);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(360);
			match(T__1);
			setState(364);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__24 || _la==IDENTIFIER) {
				{
				{
				setState(361);
				specializationContent();
				}
				}
				setState(366);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(367);
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
	public static class SpecializationContentContext extends ParserRuleContext {
		public StylePropertyContext styleProperty() {
			return getRuleContext(StylePropertyContext.class,0);
		}
		public DeleteStatementContext deleteStatement() {
			return getRuleContext(DeleteStatementContext.class,0);
		}
		public VariableAssignmentContext variableAssignment() {
			return getRuleContext(VariableAssignmentContext.class,0);
		}
		public SpecializationContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_specializationContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterSpecializationContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitSpecializationContent(this);
		}
	}

	public final SpecializationContentContext specializationContent() throws RecognitionException {
		SpecializationContentContext _localctx = new SpecializationContentContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_specializationContent);
		try {
			setState(372);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,28,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(369);
				styleProperty();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(370);
				deleteStatement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(371);
				variableAssignment();
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
	public static class DeleteStatementContext extends ParserRuleContext {
		public List<DeleteTargetContext> deleteTarget() {
			return getRuleContexts(DeleteTargetContext.class);
		}
		public DeleteTargetContext deleteTarget(int i) {
			return getRuleContext(DeleteTargetContext.class,i);
		}
		public DeleteStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_deleteStatement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterDeleteStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitDeleteStatement(this);
		}
	}

	public final DeleteStatementContext deleteStatement() throws RecognitionException {
		DeleteStatementContext _localctx = new DeleteStatementContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_deleteStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(374);
			match(T__24);
			setState(375);
			deleteTarget();
			setState(380);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__7) {
				{
				{
				setState(376);
				match(T__7);
				setState(377);
				deleteTarget();
				}
				}
				setState(382);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(383);
			match(T__4);
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
	public static class DeleteTargetContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public TerminalNode NUMBER() { return getToken(CHTLParser.NUMBER, 0); }
		public CustomTypeContext customType() {
			return getRuleContext(CustomTypeContext.class,0);
		}
		public TemplateTypeContext templateType() {
			return getRuleContext(TemplateTypeContext.class,0);
		}
		public DeleteTargetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_deleteTarget; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterDeleteTarget(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitDeleteTarget(this);
		}
	}

	public final DeleteTargetContext deleteTarget() throws RecognitionException {
		DeleteTargetContext _localctx = new DeleteTargetContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_deleteTarget);
		try {
			setState(396);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,30,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(385);
				match(IDENTIFIER);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(386);
				match(IDENTIFIER);
				setState(387);
				match(T__6);
				setState(388);
				match(NUMBER);
				setState(389);
				match(T__8);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(390);
				customType();
				setState(391);
				match(IDENTIFIER);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(393);
				templateType();
				setState(394);
				match(IDENTIFIER);
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
	public static class InsertStatementContext extends ParserRuleContext {
		public InsertPositionContext insertPosition() {
			return getRuleContext(InsertPositionContext.class,0);
		}
		public ElementSelectorContext elementSelector() {
			return getRuleContext(ElementSelectorContext.class,0);
		}
		public List<InsertContentContext> insertContent() {
			return getRuleContexts(InsertContentContext.class);
		}
		public InsertContentContext insertContent(int i) {
			return getRuleContext(InsertContentContext.class,i);
		}
		public InsertStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_insertStatement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterInsertStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitInsertStatement(this);
		}
	}

	public final InsertStatementContext insertStatement() throws RecognitionException {
		InsertStatementContext _localctx = new InsertStatementContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_insertStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(398);
			match(T__25);
			setState(399);
			insertPosition();
			setState(400);
			elementSelector();
			setState(401);
			match(T__1);
			setState(405);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4503728490610688L) != 0)) {
				{
				{
				setState(402);
				insertContent();
				}
				}
				setState(407);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(408);
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
	public static class InsertPositionContext extends ParserRuleContext {
		public InsertPositionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_insertPosition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterInsertPosition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitInsertPosition(this);
		}
	}

	public final InsertPositionContext insertPosition() throws RecognitionException {
		InsertPositionContext _localctx = new InsertPositionContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_insertPosition);
		try {
			setState(417);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,32,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(410);
				match(T__26);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(411);
				match(T__27);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(412);
				match(T__28);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(413);
				match(T__29);
				setState(414);
				match(T__30);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(415);
				match(T__29);
				setState(416);
				match(T__31);
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
	public static class ElementSelectorContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public TerminalNode NUMBER() { return getToken(CHTLParser.NUMBER, 0); }
		public ElementSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterElementSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitElementSelector(this);
		}
	}

	public final ElementSelectorContext elementSelector() throws RecognitionException {
		ElementSelectorContext _localctx = new ElementSelectorContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_elementSelector);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(419);
			match(IDENTIFIER);
			setState(423);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__6) {
				{
				setState(420);
				match(T__6);
				setState(421);
				match(NUMBER);
				setState(422);
				match(T__8);
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
	public static class InsertContentContext extends ParserRuleContext {
		public HtmlElementContext htmlElement() {
			return getRuleContext(HtmlElementContext.class,0);
		}
		public ElementUsageContext elementUsage() {
			return getRuleContext(ElementUsageContext.class,0);
		}
		public InsertContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_insertContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterInsertContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitInsertContent(this);
		}
	}

	public final InsertContentContext insertContent() throws RecognitionException {
		InsertContentContext _localctx = new InsertContentContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_insertContent);
		try {
			setState(427);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__33:
			case T__34:
			case T__35:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(425);
				htmlElement();
				}
				break;
			case T__15:
			case T__18:
			case T__19:
			case T__21:
			case T__22:
			case T__32:
				enterOuterAlt(_localctx, 2);
				{
				setState(426);
				elementUsage();
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
	public static class OriginBlockContext extends ParserRuleContext {
		public OriginTypeContext originType() {
			return getRuleContext(OriginTypeContext.class,0);
		}
		public OriginContentContext originContent() {
			return getRuleContext(OriginContentContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public OriginBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_originBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterOriginBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitOriginBlock(this);
		}
	}

	public final OriginBlockContext originBlock() throws RecognitionException {
		OriginBlockContext _localctx = new OriginBlockContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_originBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(429);
			match(T__32);
			setState(430);
			originType();
			setState(432);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(431);
				match(IDENTIFIER);
				}
			}

			setState(434);
			match(T__1);
			setState(435);
			originContent();
			setState(436);
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
	public static class OriginTypeContext extends ParserRuleContext {
		public OriginTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_originType; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterOriginType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitOriginType(this);
		}
	}

	public final OriginTypeContext originType() throws RecognitionException {
		OriginTypeContext _localctx = new OriginTypeContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_originType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(438);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 229376L) != 0)) ) {
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
	public static class OriginContentContext extends ParserRuleContext {
		public OriginContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_originContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterOriginContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitOriginContent(this);
		}
	}

	public final OriginContentContext originContent() throws RecognitionException {
		OriginContentContext _localctx = new OriginContentContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_originContent);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(443);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 18014398509481974L) != 0)) {
				{
				{
				setState(440);
				_la = _input.LA(1);
				if ( _la <= 0 || (_la==T__2) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				}
				setState(445);
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
	public static class HtmlElementContext extends ParserRuleContext {
		public ElementNameContext elementName() {
			return getRuleContext(ElementNameContext.class,0);
		}
		public ElementBodyContext elementBody() {
			return getRuleContext(ElementBodyContext.class,0);
		}
		public ElementIndexAccessContext elementIndexAccess() {
			return getRuleContext(ElementIndexAccessContext.class,0);
		}
		public GlobalStyleElementContext globalStyleElement() {
			return getRuleContext(GlobalStyleElementContext.class,0);
		}
		public HtmlElementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_htmlElement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterHtmlElement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitHtmlElement(this);
		}
	}

	public final HtmlElementContext htmlElement() throws RecognitionException {
		HtmlElementContext _localctx = new HtmlElementContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_htmlElement);
		int _la;
		try {
			setState(453);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,38,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(446);
				elementName();
				setState(448);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__6) {
					{
					setState(447);
					elementIndexAccess();
					}
				}

				setState(450);
				elementBody();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(452);
				globalStyleElement();
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
	public static class GlobalStyleElementContext extends ParserRuleContext {
		public GlobalStyleContentContext globalStyleContent() {
			return getRuleContext(GlobalStyleContentContext.class,0);
		}
		public GlobalStyleElementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_globalStyleElement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterGlobalStyleElement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitGlobalStyleElement(this);
		}
	}

	public final GlobalStyleElementContext globalStyleElement() throws RecognitionException {
		GlobalStyleElementContext _localctx = new GlobalStyleElementContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_globalStyleElement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(455);
			match(T__33);
			setState(456);
			match(T__1);
			setState(457);
			globalStyleContent();
			setState(458);
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
	public static class GlobalStyleContentContext extends ParserRuleContext {
		public GlobalStyleContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_globalStyleContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterGlobalStyleContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitGlobalStyleContent(this);
		}
	}

	public final GlobalStyleContentContext globalStyleContent() throws RecognitionException {
		GlobalStyleContentContext _localctx = new GlobalStyleContentContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_globalStyleContent);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(463);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 18014398509481974L) != 0)) {
				{
				{
				setState(460);
				_la = _input.LA(1);
				if ( _la <= 0 || (_la==T__2) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				}
				setState(465);
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
	public static class ElementNameContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public ElementNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementName; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterElementName(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitElementName(this);
		}
	}

	public final ElementNameContext elementName() throws RecognitionException {
		ElementNameContext _localctx = new ElementNameContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_elementName);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(466);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4503719886454784L) != 0)) ) {
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
	public static class ElementIndexAccessContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(CHTLParser.NUMBER, 0); }
		public ElementIndexAccessContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementIndexAccess; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterElementIndexAccess(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitElementIndexAccess(this);
		}
	}

	public final ElementIndexAccessContext elementIndexAccess() throws RecognitionException {
		ElementIndexAccessContext _localctx = new ElementIndexAccessContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_elementIndexAccess);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(468);
			match(T__6);
			setState(469);
			match(NUMBER);
			setState(470);
			match(T__8);
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
	public static class ElementBodyContext extends ParserRuleContext {
		public List<ElementContentContext> elementContent() {
			return getRuleContexts(ElementContentContext.class);
		}
		public ElementContentContext elementContent(int i) {
			return getRuleContext(ElementContentContext.class,i);
		}
		public ElementBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementBody; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterElementBody(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitElementBody(this);
		}
	}

	public final ElementBodyContext elementBody() throws RecognitionException {
		ElementBodyContext _localctx = new ElementBodyContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_elementBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(472);
			match(T__1);
			setState(476);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 8145311001804800L) != 0)) {
				{
				{
				setState(473);
				elementContent();
				}
				}
				setState(478);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(479);
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
	public static class ElementContentContext extends ParserRuleContext {
		public AttributeContext attribute() {
			return getRuleContext(AttributeContext.class,0);
		}
		public HtmlElementContext htmlElement() {
			return getRuleContext(HtmlElementContext.class,0);
		}
		public StyleBlockContext styleBlock() {
			return getRuleContext(StyleBlockContext.class,0);
		}
		public ScriptBlockContext scriptBlock() {
			return getRuleContext(ScriptBlockContext.class,0);
		}
		public TextContentContext textContent() {
			return getRuleContext(TextContentContext.class,0);
		}
		public ElementUsageContext elementUsage() {
			return getRuleContext(ElementUsageContext.class,0);
		}
		public ExceptConstraintContext exceptConstraint() {
			return getRuleContext(ExceptConstraintContext.class,0);
		}
		public CommentContext comment() {
			return getRuleContext(CommentContext.class,0);
		}
		public ElementContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterElementContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitElementContent(this);
		}
	}

	public final ElementContentContext elementContent() throws RecognitionException {
		ElementContentContext _localctx = new ElementContentContext(_ctx, getState());
		enterRule(_localctx, 86, RULE_elementContent);
		try {
			setState(489);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,41,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(481);
				attribute();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(482);
				htmlElement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(483);
				styleBlock();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(484);
				scriptBlock();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(485);
				textContent();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(486);
				elementUsage();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(487);
				exceptConstraint();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(488);
				comment();
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
	public static class AttributeContext extends ParserRuleContext {
		public AttributeNameContext attributeName() {
			return getRuleContext(AttributeNameContext.class,0);
		}
		public AttributeValueContext attributeValue() {
			return getRuleContext(AttributeValueContext.class,0);
		}
		public AttributeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attribute; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterAttribute(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitAttribute(this);
		}
	}

	public final AttributeContext attribute() throws RecognitionException {
		AttributeContext _localctx = new AttributeContext(_ctx, getState());
		enterRule(_localctx, 88, RULE_attribute);
		try {
			setState(501);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,42,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(491);
				attributeName();
				setState(492);
				match(T__36);
				setState(493);
				attributeValue();
				setState(494);
				match(T__4);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(496);
				attributeName();
				setState(497);
				match(T__3);
				setState(498);
				attributeValue();
				setState(499);
				match(T__4);
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
	public static class AttributeNameContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public AttributeNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attributeName; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterAttributeName(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitAttributeName(this);
		}
	}

	public final AttributeNameContext attributeName() throws RecognitionException {
		AttributeNameContext _localctx = new AttributeNameContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_attributeName);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(503);
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
	public static class AttributeValueContext extends ParserRuleContext {
		public TerminalNode STRING_LITERAL() { return getToken(CHTLParser.STRING_LITERAL, 0); }
		public TerminalNode UNQUOTED_LITERAL() { return getToken(CHTLParser.UNQUOTED_LITERAL, 0); }
		public VariableUsageContext variableUsage() {
			return getRuleContext(VariableUsageContext.class,0);
		}
		public AttributeValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attributeValue; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterAttributeValue(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitAttributeValue(this);
		}
	}

	public final AttributeValueContext attributeValue() throws RecognitionException {
		AttributeValueContext _localctx = new AttributeValueContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_attributeValue);
		try {
			setState(508);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case STRING_LITERAL:
				enterOuterAlt(_localctx, 1);
				{
				setState(505);
				match(STRING_LITERAL);
				}
				break;
			case UNQUOTED_LITERAL:
				enterOuterAlt(_localctx, 2);
				{
				setState(506);
				match(UNQUOTED_LITERAL);
				}
				break;
			case IDENTIFIER:
				enterOuterAlt(_localctx, 3);
				{
				setState(507);
				variableUsage();
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
	public static class TextContentContext extends ParserRuleContext {
		public TerminalNode STRING_LITERAL() { return getToken(CHTLParser.STRING_LITERAL, 0); }
		public TerminalNode UNQUOTED_LITERAL() { return getToken(CHTLParser.UNQUOTED_LITERAL, 0); }
		public TextContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_textContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterTextContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitTextContent(this);
		}
	}

	public final TextContentContext textContent() throws RecognitionException {
		TextContentContext _localctx = new TextContentContext(_ctx, getState());
		enterRule(_localctx, 94, RULE_textContent);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(510);
			_la = _input.LA(1);
			if ( !(_la==STRING_LITERAL || _la==UNQUOTED_LITERAL) ) {
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
		public List<StyleContentContext> styleContent() {
			return getRuleContexts(StyleContentContext.class);
		}
		public StyleContentContext styleContent(int i) {
			return getRuleContext(StyleContentContext.class,i);
		}
		public StyleBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_styleBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterStyleBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitStyleBlock(this);
		}
	}

	public final StyleBlockContext styleBlock() throws RecognitionException {
		StyleBlockContext _localctx = new StyleBlockContext(_ctx, getState());
		enterRule(_localctx, 96, RULE_styleBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(512);
			match(T__33);
			setState(513);
			match(T__1);
			setState(517);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4505248909557760L) != 0)) {
				{
				{
				setState(514);
				styleContent();
				}
				}
				setState(519);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(520);
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
	public static class StyleContentContext extends ParserRuleContext {
		public StylePropertyContext styleProperty() {
			return getRuleContext(StylePropertyContext.class,0);
		}
		public CssSelectorContext cssSelector() {
			return getRuleContext(CssSelectorContext.class,0);
		}
		public List<StyleContentContext> styleContent() {
			return getRuleContexts(StyleContentContext.class);
		}
		public StyleContentContext styleContent(int i) {
			return getRuleContext(StyleContentContext.class,i);
		}
		public StyleUsageContext styleUsage() {
			return getRuleContext(StyleUsageContext.class,0);
		}
		public StyleContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_styleContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterStyleContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitStyleContent(this);
		}
	}

	public final StyleContentContext styleContent() throws RecognitionException {
		StyleContentContext _localctx = new StyleContentContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_styleContent);
		int _la;
		try {
			setState(534);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(522);
				styleProperty();
				}
				break;
			case T__20:
			case T__38:
			case T__39:
				enterOuterAlt(_localctx, 2);
				{
				setState(523);
				cssSelector();
				setState(524);
				match(T__1);
				setState(528);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4505248909557760L) != 0)) {
					{
					{
					setState(525);
					styleContent();
					}
					}
					setState(530);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(531);
				match(T__2);
				}
				break;
			case T__15:
			case T__21:
			case T__22:
				enterOuterAlt(_localctx, 3);
				{
				setState(533);
				styleUsage();
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
	public static class StylePropertyContext extends ParserRuleContext {
		public PropertyNameContext propertyName() {
			return getRuleContext(PropertyNameContext.class,0);
		}
		public PropertyValueContext propertyValue() {
			return getRuleContext(PropertyValueContext.class,0);
		}
		public StylePropertyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_styleProperty; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterStyleProperty(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitStyleProperty(this);
		}
	}

	public final StylePropertyContext styleProperty() throws RecognitionException {
		StylePropertyContext _localctx = new StylePropertyContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_styleProperty);
		try {
			setState(547);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,47,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(536);
				propertyName();
				setState(537);
				match(T__36);
				setState(538);
				propertyValue();
				setState(539);
				match(T__4);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(541);
				propertyName();
				setState(542);
				match(T__7);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(544);
				propertyName();
				setState(545);
				match(T__4);
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
	public static class PropertyNameContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(CHTLParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(CHTLParser.IDENTIFIER, i);
		}
		public PropertyNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_propertyName; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterPropertyName(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitPropertyName(this);
		}
	}

	public final PropertyNameContext propertyName() throws RecognitionException {
		PropertyNameContext _localctx = new PropertyNameContext(_ctx, getState());
		enterRule(_localctx, 102, RULE_propertyName);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(549);
			match(IDENTIFIER);
			setState(554);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__37) {
				{
				{
				setState(550);
				match(T__37);
				setState(551);
				match(IDENTIFIER);
				}
				}
				setState(556);
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
	public static class PropertyValueContext extends ParserRuleContext {
		public TerminalNode STRING_LITERAL() { return getToken(CHTLParser.STRING_LITERAL, 0); }
		public TerminalNode UNQUOTED_LITERAL() { return getToken(CHTLParser.UNQUOTED_LITERAL, 0); }
		public VariableUsageContext variableUsage() {
			return getRuleContext(VariableUsageContext.class,0);
		}
		public CssFunctionContext cssFunction() {
			return getRuleContext(CssFunctionContext.class,0);
		}
		public PropertyValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_propertyValue; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterPropertyValue(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitPropertyValue(this);
		}
	}

	public final PropertyValueContext propertyValue() throws RecognitionException {
		PropertyValueContext _localctx = new PropertyValueContext(_ctx, getState());
		enterRule(_localctx, 104, RULE_propertyValue);
		try {
			setState(561);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,49,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(557);
				match(STRING_LITERAL);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(558);
				match(UNQUOTED_LITERAL);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(559);
				variableUsage();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(560);
				cssFunction();
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
	public static class CssSelectorContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public PseudoClassContext pseudoClass() {
			return getRuleContext(PseudoClassContext.class,0);
		}
		public PseudoElementContext pseudoElement() {
			return getRuleContext(PseudoElementContext.class,0);
		}
		public CssSelectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cssSelector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCssSelector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCssSelector(this);
		}
	}

	public final CssSelectorContext cssSelector() throws RecognitionException {
		CssSelectorContext _localctx = new CssSelectorContext(_ctx, getState());
		enterRule(_localctx, 106, RULE_cssSelector);
		try {
			setState(572);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,50,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(563);
				match(T__20);
				setState(564);
				match(IDENTIFIER);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(565);
				match(T__38);
				setState(566);
				match(IDENTIFIER);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(567);
				match(T__39);
				setState(568);
				pseudoClass();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(569);
				match(T__39);
				setState(570);
				pseudoElement();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(571);
				match(T__39);
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
	public static class PseudoClassContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public PseudoClassContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pseudoClass; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterPseudoClass(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitPseudoClass(this);
		}
	}

	public final PseudoClassContext pseudoClass() throws RecognitionException {
		PseudoClassContext _localctx = new PseudoClassContext(_ctx, getState());
		enterRule(_localctx, 108, RULE_pseudoClass);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(574);
			match(T__36);
			setState(575);
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
	public static class PseudoElementContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public PseudoElementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pseudoElement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterPseudoElement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitPseudoElement(this);
		}
	}

	public final PseudoElementContext pseudoElement() throws RecognitionException {
		PseudoElementContext _localctx = new PseudoElementContext(_ctx, getState());
		enterRule(_localctx, 110, RULE_pseudoElement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(577);
			match(T__40);
			setState(578);
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
	public static class CssFunctionContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public CssArgumentsContext cssArguments() {
			return getRuleContext(CssArgumentsContext.class,0);
		}
		public CssFunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cssFunction; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCssFunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCssFunction(this);
		}
	}

	public final CssFunctionContext cssFunction() throws RecognitionException {
		CssFunctionContext _localctx = new CssFunctionContext(_ctx, getState());
		enterRule(_localctx, 112, RULE_cssFunction);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(580);
			match(IDENTIFIER);
			setState(581);
			match(T__41);
			setState(583);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 7881299347898368L) != 0)) {
				{
				setState(582);
				cssArguments();
				}
			}

			setState(585);
			match(T__42);
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
	public static class CssArgumentsContext extends ParserRuleContext {
		public List<CssArgumentContext> cssArgument() {
			return getRuleContexts(CssArgumentContext.class);
		}
		public CssArgumentContext cssArgument(int i) {
			return getRuleContext(CssArgumentContext.class,i);
		}
		public CssArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cssArguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCssArguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCssArguments(this);
		}
	}

	public final CssArgumentsContext cssArguments() throws RecognitionException {
		CssArgumentsContext _localctx = new CssArgumentsContext(_ctx, getState());
		enterRule(_localctx, 114, RULE_cssArguments);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(587);
			cssArgument();
			setState(592);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__7) {
				{
				{
				setState(588);
				match(T__7);
				setState(589);
				cssArgument();
				}
				}
				setState(594);
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
	public static class CssArgumentContext extends ParserRuleContext {
		public PropertyValueContext propertyValue() {
			return getRuleContext(PropertyValueContext.class,0);
		}
		public CssArgumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cssArgument; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterCssArgument(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitCssArgument(this);
		}
	}

	public final CssArgumentContext cssArgument() throws RecognitionException {
		CssArgumentContext _localctx = new CssArgumentContext(_ctx, getState());
		enterRule(_localctx, 116, RULE_cssArgument);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(595);
			propertyValue();
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
		public ScriptContentContext scriptContent() {
			return getRuleContext(ScriptContentContext.class,0);
		}
		public ScriptBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_scriptBlock; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterScriptBlock(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitScriptBlock(this);
		}
	}

	public final ScriptBlockContext scriptBlock() throws RecognitionException {
		ScriptBlockContext _localctx = new ScriptBlockContext(_ctx, getState());
		enterRule(_localctx, 118, RULE_scriptBlock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(597);
			match(T__35);
			setState(598);
			match(T__1);
			setState(599);
			scriptContent();
			setState(600);
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
	public static class ScriptContentContext extends ParserRuleContext {
		public ScriptContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_scriptContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterScriptContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitScriptContent(this);
		}
	}

	public final ScriptContentContext scriptContent() throws RecognitionException {
		ScriptContentContext _localctx = new ScriptContentContext(_ctx, getState());
		enterRule(_localctx, 120, RULE_scriptContent);
		int _la;
		try {
			setState(608);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__0:
			case T__1:
			case T__3:
			case T__4:
			case T__5:
			case T__6:
			case T__7:
			case T__8:
			case T__9:
			case T__10:
			case T__11:
			case T__12:
			case T__13:
			case T__14:
			case T__15:
			case T__16:
			case T__17:
			case T__18:
			case T__19:
			case T__20:
			case T__21:
			case T__22:
			case T__23:
			case T__24:
			case T__25:
			case T__26:
			case T__27:
			case T__28:
			case T__29:
			case T__30:
			case T__31:
			case T__32:
			case T__33:
			case T__34:
			case T__35:
			case T__36:
			case T__37:
			case T__38:
			case T__39:
			case T__40:
			case T__41:
			case T__42:
			case T__43:
			case SINGLE_LINE_COMMENT:
			case MULTI_LINE_COMMENT:
			case GENERATOR_COMMENT:
			case BOOLEAN:
			case NUMBER:
			case STRING_LITERAL:
			case UNQUOTED_LITERAL:
			case IDENTIFIER:
			case WS:
				enterOuterAlt(_localctx, 1);
				{
				setState(603); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(602);
					_la = _input.LA(1);
					if ( _la <= 0 || (_la==T__2) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					}
					}
					setState(605); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & 18014398509481974L) != 0) );
				}
				break;
			case T__2:
				enterOuterAlt(_localctx, 2);
				{
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
	public static class ElementUsageContext extends ParserRuleContext {
		public CustomTypeContext customType() {
			return getRuleContext(CustomTypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public ElementSpecializationContext elementSpecialization() {
			return getRuleContext(ElementSpecializationContext.class,0);
		}
		public NamespacePathContext namespacePath() {
			return getRuleContext(NamespacePathContext.class,0);
		}
		public TemplateTypeContext templateType() {
			return getRuleContext(TemplateTypeContext.class,0);
		}
		public OriginTypeContext originType() {
			return getRuleContext(OriginTypeContext.class,0);
		}
		public ElementUsageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementUsage; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterElementUsage(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitElementUsage(this);
		}
	}

	public final ElementUsageContext elementUsage() throws RecognitionException {
		ElementUsageContext _localctx = new ElementUsageContext(_ctx, getState());
		enterRule(_localctx, 122, RULE_elementUsage);
		int _la;
		try {
			setState(661);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,63,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(610);
				customType();
				setState(611);
				match(IDENTIFIER);
				setState(613);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(612);
					elementSpecialization();
					}
				}

				setState(617);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__12) {
					{
					setState(615);
					match(T__12);
					setState(616);
					namespacePath();
					}
				}

				setState(619);
				match(T__4);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(621);
				templateType();
				setState(622);
				match(IDENTIFIER);
				setState(624);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(623);
					elementSpecialization();
					}
				}

				setState(628);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__12) {
					{
					setState(626);
					match(T__12);
					setState(627);
					namespacePath();
					}
				}

				setState(630);
				match(T__4);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(632);
				match(T__18);
				setState(633);
				customType();
				setState(634);
				match(IDENTIFIER);
				setState(636);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(635);
					elementSpecialization();
					}
				}

				setState(640);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__12) {
					{
					setState(638);
					match(T__12);
					setState(639);
					namespacePath();
					}
				}

				setState(642);
				match(T__4);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(644);
				match(T__19);
				setState(645);
				templateType();
				setState(646);
				match(IDENTIFIER);
				setState(648);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(647);
					elementSpecialization();
					}
				}

				setState(652);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__12) {
					{
					setState(650);
					match(T__12);
					setState(651);
					namespacePath();
					}
				}

				setState(654);
				match(T__4);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(656);
				match(T__32);
				setState(657);
				originType();
				setState(658);
				match(IDENTIFIER);
				setState(659);
				match(T__4);
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
	public static class ElementSpecializationContext extends ParserRuleContext {
		public List<ElementSpecializationContentContext> elementSpecializationContent() {
			return getRuleContexts(ElementSpecializationContentContext.class);
		}
		public ElementSpecializationContentContext elementSpecializationContent(int i) {
			return getRuleContext(ElementSpecializationContentContext.class,i);
		}
		public ElementSpecializationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementSpecialization; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterElementSpecialization(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitElementSpecialization(this);
		}
	}

	public final ElementSpecializationContext elementSpecialization() throws RecognitionException {
		ElementSpecializationContext _localctx = new ElementSpecializationContext(_ctx, getState());
		enterRule(_localctx, 124, RULE_elementSpecialization);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(663);
			match(T__1);
			setState(667);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 4503719987118080L) != 0)) {
				{
				{
				setState(664);
				elementSpecializationContent();
				}
				}
				setState(669);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(670);
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
	public static class ElementSpecializationContentContext extends ParserRuleContext {
		public HtmlElementContext htmlElement() {
			return getRuleContext(HtmlElementContext.class,0);
		}
		public StyleBlockContext styleBlock() {
			return getRuleContext(StyleBlockContext.class,0);
		}
		public DeleteStatementContext deleteStatement() {
			return getRuleContext(DeleteStatementContext.class,0);
		}
		public InsertStatementContext insertStatement() {
			return getRuleContext(InsertStatementContext.class,0);
		}
		public ElementSpecializationContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementSpecializationContent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterElementSpecializationContent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitElementSpecializationContent(this);
		}
	}

	public final ElementSpecializationContentContext elementSpecializationContent() throws RecognitionException {
		ElementSpecializationContentContext _localctx = new ElementSpecializationContentContext(_ctx, getState());
		enterRule(_localctx, 126, RULE_elementSpecializationContent);
		try {
			setState(676);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,65,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(672);
				htmlElement();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(673);
				styleBlock();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(674);
				deleteStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(675);
				insertStatement();
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
	public static class StyleUsageContext extends ParserRuleContext {
		public CustomTypeContext customType() {
			return getRuleContext(CustomTypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public StyleSpecializationContext styleSpecialization() {
			return getRuleContext(StyleSpecializationContext.class,0);
		}
		public TemplateTypeContext templateType() {
			return getRuleContext(TemplateTypeContext.class,0);
		}
		public StyleUsageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_styleUsage; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterStyleUsage(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitStyleUsage(this);
		}
	}

	public final StyleUsageContext styleUsage() throws RecognitionException {
		StyleUsageContext _localctx = new StyleUsageContext(_ctx, getState());
		enterRule(_localctx, 128, RULE_styleUsage);
		int _la;
		try {
			setState(692);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,68,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(678);
				customType();
				setState(679);
				match(IDENTIFIER);
				setState(681);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(680);
					styleSpecialization();
					}
				}

				setState(683);
				match(T__4);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(685);
				templateType();
				setState(686);
				match(IDENTIFIER);
				setState(688);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(687);
					styleSpecialization();
					}
				}

				setState(690);
				match(T__4);
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
	public static class StyleSpecializationContext extends ParserRuleContext {
		public List<StylePropertyContext> styleProperty() {
			return getRuleContexts(StylePropertyContext.class);
		}
		public StylePropertyContext styleProperty(int i) {
			return getRuleContext(StylePropertyContext.class,i);
		}
		public StyleSpecializationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_styleSpecialization; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterStyleSpecialization(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitStyleSpecialization(this);
		}
	}

	public final StyleSpecializationContext styleSpecialization() throws RecognitionException {
		StyleSpecializationContext _localctx = new StyleSpecializationContext(_ctx, getState());
		enterRule(_localctx, 130, RULE_styleSpecialization);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(694);
			match(T__1);
			setState(698);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==IDENTIFIER) {
				{
				{
				setState(695);
				styleProperty();
				}
				}
				setState(700);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(701);
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
	public static class VariableDefinitionContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(CHTLParser.STRING_LITERAL, 0); }
		public VariableDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDefinition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterVariableDefinition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitVariableDefinition(this);
		}
	}

	public final VariableDefinitionContext variableDefinition() throws RecognitionException {
		VariableDefinitionContext _localctx = new VariableDefinitionContext(_ctx, getState());
		enterRule(_localctx, 132, RULE_variableDefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(703);
			match(IDENTIFIER);
			setState(704);
			match(T__36);
			setState(705);
			match(STRING_LITERAL);
			setState(706);
			match(T__4);
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
	public static class VariableUsageContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public VariableArgumentsContext variableArguments() {
			return getRuleContext(VariableArgumentsContext.class,0);
		}
		public VariableUsageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableUsage; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterVariableUsage(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitVariableUsage(this);
		}
	}

	public final VariableUsageContext variableUsage() throws RecognitionException {
		VariableUsageContext _localctx = new VariableUsageContext(_ctx, getState());
		enterRule(_localctx, 134, RULE_variableUsage);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(708);
			match(IDENTIFIER);
			setState(709);
			match(T__41);
			setState(711);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(710);
				variableArguments();
				}
			}

			setState(713);
			match(T__42);
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
	public static class VariableArgumentsContext extends ParserRuleContext {
		public List<VariableArgumentContext> variableArgument() {
			return getRuleContexts(VariableArgumentContext.class);
		}
		public VariableArgumentContext variableArgument(int i) {
			return getRuleContext(VariableArgumentContext.class,i);
		}
		public VariableArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableArguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterVariableArguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitVariableArguments(this);
		}
	}

	public final VariableArgumentsContext variableArguments() throws RecognitionException {
		VariableArgumentsContext _localctx = new VariableArgumentsContext(_ctx, getState());
		enterRule(_localctx, 136, RULE_variableArguments);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(715);
			variableArgument();
			setState(720);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__7) {
				{
				{
				setState(716);
				match(T__7);
				setState(717);
				variableArgument();
				}
				}
				setState(722);
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
	public static class VariableArgumentContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public PropertyValueContext propertyValue() {
			return getRuleContext(PropertyValueContext.class,0);
		}
		public VariableArgumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableArgument; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterVariableArgument(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitVariableArgument(this);
		}
	}

	public final VariableArgumentContext variableArgument() throws RecognitionException {
		VariableArgumentContext _localctx = new VariableArgumentContext(_ctx, getState());
		enterRule(_localctx, 138, RULE_variableArgument);
		try {
			setState(727);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,72,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(723);
				match(IDENTIFIER);
				setState(724);
				match(T__3);
				setState(725);
				propertyValue();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(726);
				match(IDENTIFIER);
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
	public static class VariableAssignmentContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public PropertyValueContext propertyValue() {
			return getRuleContext(PropertyValueContext.class,0);
		}
		public VariableAssignmentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableAssignment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterVariableAssignment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitVariableAssignment(this);
		}
	}

	public final VariableAssignmentContext variableAssignment() throws RecognitionException {
		VariableAssignmentContext _localctx = new VariableAssignmentContext(_ctx, getState());
		enterRule(_localctx, 140, RULE_variableAssignment);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(729);
			match(IDENTIFIER);
			setState(730);
			match(T__3);
			setState(731);
			propertyValue();
			setState(732);
			match(T__4);
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
	public static class NamespacePathContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(CHTLParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(CHTLParser.IDENTIFIER, i);
		}
		public NamespacePathContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespacePath; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterNamespacePath(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitNamespacePath(this);
		}
	}

	public final NamespacePathContext namespacePath() throws RecognitionException {
		NamespacePathContext _localctx = new NamespacePathContext(_ctx, getState());
		enterRule(_localctx, 142, RULE_namespacePath);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(734);
			match(IDENTIFIER);
			setState(739);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__20) {
				{
				{
				setState(735);
				match(T__20);
				setState(736);
				match(IDENTIFIER);
				}
				}
				setState(741);
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
	public static class ExceptConstraintContext extends ParserRuleContext {
		public List<ExceptTargetContext> exceptTarget() {
			return getRuleContexts(ExceptTargetContext.class);
		}
		public ExceptTargetContext exceptTarget(int i) {
			return getRuleContext(ExceptTargetContext.class,i);
		}
		public ExceptConstraintContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exceptConstraint; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterExceptConstraint(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitExceptConstraint(this);
		}
	}

	public final ExceptConstraintContext exceptConstraint() throws RecognitionException {
		ExceptConstraintContext _localctx = new ExceptConstraintContext(_ctx, getState());
		enterRule(_localctx, 144, RULE_exceptConstraint);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(742);
			match(T__43);
			setState(743);
			exceptTarget();
			setState(748);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__7) {
				{
				{
				setState(744);
				match(T__7);
				setState(745);
				exceptTarget();
				}
				}
				setState(750);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(751);
			match(T__4);
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
		public TerminalNode IDENTIFIER() { return getToken(CHTLParser.IDENTIFIER, 0); }
		public CustomTypeContext customType() {
			return getRuleContext(CustomTypeContext.class,0);
		}
		public TemplateTypeContext templateType() {
			return getRuleContext(TemplateTypeContext.class,0);
		}
		public ExceptTargetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exceptTarget; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterExceptTarget(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitExceptTarget(this);
		}
	}

	public final ExceptTargetContext exceptTarget() throws RecognitionException {
		ExceptTargetContext _localctx = new ExceptTargetContext(_ctx, getState());
		enterRule(_localctx, 146, RULE_exceptTarget);
		int _la;
		try {
			setState(769);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,77,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(753);
				match(IDENTIFIER);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(754);
				customType();
				setState(755);
				match(IDENTIFIER);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(757);
				templateType();
				setState(758);
				match(IDENTIFIER);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(760);
				match(T__18);
				setState(762);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 12648448L) != 0)) {
					{
					setState(761);
					customType();
					}
				}

				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(764);
				match(T__19);
				setState(766);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 12648448L) != 0)) {
					{
					setState(765);
					templateType();
					}
				}

				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(768);
				match(T__14);
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
	public static class CommentContext extends ParserRuleContext {
		public TerminalNode SINGLE_LINE_COMMENT() { return getToken(CHTLParser.SINGLE_LINE_COMMENT, 0); }
		public TerminalNode MULTI_LINE_COMMENT() { return getToken(CHTLParser.MULTI_LINE_COMMENT, 0); }
		public TerminalNode GENERATOR_COMMENT() { return getToken(CHTLParser.GENERATOR_COMMENT, 0); }
		public CommentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_comment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).enterComment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CHTLListener ) ((CHTLListener)listener).exitComment(this);
		}
	}

	public final CommentContext comment() throws RecognitionException {
		CommentContext _localctx = new CommentContext(_ctx, getState());
		enterRule(_localctx, 148, RULE_comment);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(771);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 246290604621824L) != 0)) ) {
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
		"\u0004\u00015\u0306\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
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
		"A\u0007A\u0002B\u0007B\u0002C\u0007C\u0002D\u0007D\u0002E\u0007E\u0002"+
		"F\u0007F\u0002G\u0007G\u0002H\u0007H\u0002I\u0007I\u0002J\u0007J\u0001"+
		"\u0000\u0005\u0000\u0098\b\u0000\n\u0000\f\u0000\u009b\t\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0003\u0001"+
		"\u00a9\b\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0005\u0002\u00ae\b"+
		"\u0002\n\u0002\f\u0002\u00b1\t\u0002\u0001\u0002\u0001\u0002\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0005\u0003\u00bd\b\u0003\n\u0003\f\u0003\u00c0\t\u0003\u0001"+
		"\u0003\u0003\u0003\u00c3\b\u0003\u0001\u0004\u0001\u0004\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0003\u0005\u00cb\b\u0005\u0001\u0006\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0005\u0006\u00d1\b\u0006\n\u0006\f\u0006"+
		"\u00d4\t\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0003\u0007\u00db\b\u0007\u0001\b\u0001\b\u0001\b\u0001\b\u0003\b\u00e1"+
		"\b\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0003\t\u00e8\b\t\u0001\n"+
		"\u0001\n\u0005\n\u00ec\b\n\n\n\f\n\u00ef\t\n\u0001\n\u0001\n\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u00f7\b\u000b\u0001\f"+
		"\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0003\f\u00ff\b\f\u0001\f\u0003"+
		"\f\u0102\b\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001"+
		"\r\u0001\r\u0001\r\u0001\r\u0001\r\u0003\r\u0110\b\r\u0001\u000e\u0001"+
		"\u000e\u0003\u000e\u0114\b\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0005"+
		"\u000f\u0119\b\u000f\n\u000f\f\u000f\u011c\t\u000f\u0001\u0010\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011\u0001\u0012"+
		"\u0001\u0012\u0005\u0012\u0127\b\u0012\n\u0012\f\u0012\u012a\t\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0003"+
		"\u0013\u0132\b\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001"+
		"\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0003\u0014\u013d"+
		"\b\u0014\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001"+
		"\u0016\u0001\u0016\u0001\u0017\u0001\u0017\u0005\u0017\u0148\b\u0017\n"+
		"\u0017\f\u0017\u014b\t\u0017\u0001\u0017\u0001\u0017\u0001\u0018\u0001"+
		"\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0003\u0018\u0155"+
		"\b\u0018\u0001\u0019\u0001\u0019\u0001\u0019\u0003\u0019\u015a\b\u0019"+
		"\u0001\u0019\u0003\u0019\u015d\b\u0019\u0001\u0019\u0001\u0019\u0001\u0019"+
		"\u0003\u0019\u0162\b\u0019\u0001\u0019\u0003\u0019\u0165\b\u0019\u0003"+
		"\u0019\u0167\b\u0019\u0001\u001a\u0001\u001a\u0005\u001a\u016b\b\u001a"+
		"\n\u001a\f\u001a\u016e\t\u001a\u0001\u001a\u0001\u001a\u0001\u001b\u0001"+
		"\u001b\u0001\u001b\u0003\u001b\u0175\b\u001b\u0001\u001c\u0001\u001c\u0001"+
		"\u001c\u0001\u001c\u0005\u001c\u017b\b\u001c\n\u001c\f\u001c\u017e\t\u001c"+
		"\u0001\u001c\u0001\u001c\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d"+
		"\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d"+
		"\u0001\u001d\u0003\u001d\u018d\b\u001d\u0001\u001e\u0001\u001e\u0001\u001e"+
		"\u0001\u001e\u0001\u001e\u0005\u001e\u0194\b\u001e\n\u001e\f\u001e\u0197"+
		"\t\u001e\u0001\u001e\u0001\u001e\u0001\u001f\u0001\u001f\u0001\u001f\u0001"+
		"\u001f\u0001\u001f\u0001\u001f\u0001\u001f\u0003\u001f\u01a2\b\u001f\u0001"+
		" \u0001 \u0001 \u0001 \u0003 \u01a8\b \u0001!\u0001!\u0003!\u01ac\b!\u0001"+
		"\"\u0001\"\u0001\"\u0003\"\u01b1\b\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001"+
		"#\u0001#\u0001$\u0005$\u01ba\b$\n$\f$\u01bd\t$\u0001%\u0001%\u0003%\u01c1"+
		"\b%\u0001%\u0001%\u0001%\u0003%\u01c6\b%\u0001&\u0001&\u0001&\u0001&\u0001"+
		"&\u0001\'\u0005\'\u01ce\b\'\n\'\f\'\u01d1\t\'\u0001(\u0001(\u0001)\u0001"+
		")\u0001)\u0001)\u0001*\u0001*\u0005*\u01db\b*\n*\f*\u01de\t*\u0001*\u0001"+
		"*\u0001+\u0001+\u0001+\u0001+\u0001+\u0001+\u0001+\u0001+\u0003+\u01ea"+
		"\b+\u0001,\u0001,\u0001,\u0001,\u0001,\u0001,\u0001,\u0001,\u0001,\u0001"+
		",\u0003,\u01f6\b,\u0001-\u0001-\u0001.\u0001.\u0001.\u0003.\u01fd\b.\u0001"+
		"/\u0001/\u00010\u00010\u00010\u00050\u0204\b0\n0\f0\u0207\t0\u00010\u0001"+
		"0\u00011\u00011\u00011\u00011\u00051\u020f\b1\n1\f1\u0212\t1\u00011\u0001"+
		"1\u00011\u00031\u0217\b1\u00012\u00012\u00012\u00012\u00012\u00012\u0001"+
		"2\u00012\u00012\u00012\u00012\u00032\u0224\b2\u00013\u00013\u00013\u0005"+
		"3\u0229\b3\n3\f3\u022c\t3\u00014\u00014\u00014\u00014\u00034\u0232\b4"+
		"\u00015\u00015\u00015\u00015\u00015\u00015\u00015\u00015\u00015\u0003"+
		"5\u023d\b5\u00016\u00016\u00016\u00017\u00017\u00017\u00018\u00018\u0001"+
		"8\u00038\u0248\b8\u00018\u00018\u00019\u00019\u00019\u00059\u024f\b9\n"+
		"9\f9\u0252\t9\u0001:\u0001:\u0001;\u0001;\u0001;\u0001;\u0001;\u0001<"+
		"\u0004<\u025c\b<\u000b<\f<\u025d\u0001<\u0003<\u0261\b<\u0001=\u0001="+
		"\u0001=\u0003=\u0266\b=\u0001=\u0001=\u0003=\u026a\b=\u0001=\u0001=\u0001"+
		"=\u0001=\u0001=\u0003=\u0271\b=\u0001=\u0001=\u0003=\u0275\b=\u0001=\u0001"+
		"=\u0001=\u0001=\u0001=\u0001=\u0003=\u027d\b=\u0001=\u0001=\u0003=\u0281"+
		"\b=\u0001=\u0001=\u0001=\u0001=\u0001=\u0001=\u0003=\u0289\b=\u0001=\u0001"+
		"=\u0003=\u028d\b=\u0001=\u0001=\u0001=\u0001=\u0001=\u0001=\u0001=\u0003"+
		"=\u0296\b=\u0001>\u0001>\u0005>\u029a\b>\n>\f>\u029d\t>\u0001>\u0001>"+
		"\u0001?\u0001?\u0001?\u0001?\u0003?\u02a5\b?\u0001@\u0001@\u0001@\u0003"+
		"@\u02aa\b@\u0001@\u0001@\u0001@\u0001@\u0001@\u0003@\u02b1\b@\u0001@\u0001"+
		"@\u0003@\u02b5\b@\u0001A\u0001A\u0005A\u02b9\bA\nA\fA\u02bc\tA\u0001A"+
		"\u0001A\u0001B\u0001B\u0001B\u0001B\u0001B\u0001C\u0001C\u0001C\u0003"+
		"C\u02c8\bC\u0001C\u0001C\u0001D\u0001D\u0001D\u0005D\u02cf\bD\nD\fD\u02d2"+
		"\tD\u0001E\u0001E\u0001E\u0001E\u0003E\u02d8\bE\u0001F\u0001F\u0001F\u0001"+
		"F\u0001F\u0001G\u0001G\u0001G\u0005G\u02e2\bG\nG\fG\u02e5\tG\u0001H\u0001"+
		"H\u0001H\u0001H\u0005H\u02eb\bH\nH\fH\u02ee\tH\u0001H\u0001H\u0001I\u0001"+
		"I\u0001I\u0001I\u0001I\u0001I\u0001I\u0001I\u0001I\u0003I\u02fb\bI\u0001"+
		"I\u0001I\u0003I\u02ff\bI\u0001I\u0003I\u0302\bI\u0001J\u0001J\u0001J\u0000"+
		"\u0000K\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018"+
		"\u001a\u001c\u001e \"$&(*,.02468:<>@BDFHJLNPRTVXZ\\^`bdfhjlnprtvxz|~\u0080"+
		"\u0082\u0084\u0086\u0088\u008a\u008c\u008e\u0090\u0092\u0094\u0000\u0006"+
		"\u0002\u0000\u0010\u0010\u0016\u0017\u0001\u0000\u000f\u0011\u0001\u0000"+
		"\u0003\u0003\u0002\u0000\"$44\u0001\u000023\u0001\u0000-/\u033b\u0000"+
		"\u0099\u0001\u0000\u0000\u0000\u0002\u00a8\u0001\u0000\u0000\u0000\u0004"+
		"\u00aa\u0001\u0000\u0000\u0000\u0006\u00c2\u0001\u0000\u0000\u0000\b\u00c4"+
		"\u0001\u0000\u0000\u0000\n\u00ca\u0001\u0000\u0000\u0000\f\u00cc\u0001"+
		"\u0000\u0000\u0000\u000e\u00da\u0001\u0000\u0000\u0000\u0010\u00dc\u0001"+
		"\u0000\u0000\u0000\u0012\u00e4\u0001\u0000\u0000\u0000\u0014\u00e9\u0001"+
		"\u0000\u0000\u0000\u0016\u00f6\u0001\u0000\u0000\u0000\u0018\u00f8\u0001"+
		"\u0000\u0000\u0000\u001a\u010f\u0001\u0000\u0000\u0000\u001c\u0113\u0001"+
		"\u0000\u0000\u0000\u001e\u0115\u0001\u0000\u0000\u0000 \u011d\u0001\u0000"+
		"\u0000\u0000\"\u0122\u0001\u0000\u0000\u0000$\u0124\u0001\u0000\u0000"+
		"\u0000&\u0131\u0001\u0000\u0000\u0000(\u013c\u0001\u0000\u0000\u0000*"+
		"\u013e\u0001\u0000\u0000\u0000,\u0143\u0001\u0000\u0000\u0000.\u0145\u0001"+
		"\u0000\u0000\u00000\u0154\u0001\u0000\u0000\u00002\u0166\u0001\u0000\u0000"+
		"\u00004\u0168\u0001\u0000\u0000\u00006\u0174\u0001\u0000\u0000\u00008"+
		"\u0176\u0001\u0000\u0000\u0000:\u018c\u0001\u0000\u0000\u0000<\u018e\u0001"+
		"\u0000\u0000\u0000>\u01a1\u0001\u0000\u0000\u0000@\u01a3\u0001\u0000\u0000"+
		"\u0000B\u01ab\u0001\u0000\u0000\u0000D\u01ad\u0001\u0000\u0000\u0000F"+
		"\u01b6\u0001\u0000\u0000\u0000H\u01bb\u0001\u0000\u0000\u0000J\u01c5\u0001"+
		"\u0000\u0000\u0000L\u01c7\u0001\u0000\u0000\u0000N\u01cf\u0001\u0000\u0000"+
		"\u0000P\u01d2\u0001\u0000\u0000\u0000R\u01d4\u0001\u0000\u0000\u0000T"+
		"\u01d8\u0001\u0000\u0000\u0000V\u01e9\u0001\u0000\u0000\u0000X\u01f5\u0001"+
		"\u0000\u0000\u0000Z\u01f7\u0001\u0000\u0000\u0000\\\u01fc\u0001\u0000"+
		"\u0000\u0000^\u01fe\u0001\u0000\u0000\u0000`\u0200\u0001\u0000\u0000\u0000"+
		"b\u0216\u0001\u0000\u0000\u0000d\u0223\u0001\u0000\u0000\u0000f\u0225"+
		"\u0001\u0000\u0000\u0000h\u0231\u0001\u0000\u0000\u0000j\u023c\u0001\u0000"+
		"\u0000\u0000l\u023e\u0001\u0000\u0000\u0000n\u0241\u0001\u0000\u0000\u0000"+
		"p\u0244\u0001\u0000\u0000\u0000r\u024b\u0001\u0000\u0000\u0000t\u0253"+
		"\u0001\u0000\u0000\u0000v\u0255\u0001\u0000\u0000\u0000x\u0260\u0001\u0000"+
		"\u0000\u0000z\u0295\u0001\u0000\u0000\u0000|\u0297\u0001\u0000\u0000\u0000"+
		"~\u02a4\u0001\u0000\u0000\u0000\u0080\u02b4\u0001\u0000\u0000\u0000\u0082"+
		"\u02b6\u0001\u0000\u0000\u0000\u0084\u02bf\u0001\u0000\u0000\u0000\u0086"+
		"\u02c4\u0001\u0000\u0000\u0000\u0088\u02cb\u0001\u0000\u0000\u0000\u008a"+
		"\u02d7\u0001\u0000\u0000\u0000\u008c\u02d9\u0001\u0000\u0000\u0000\u008e"+
		"\u02de\u0001\u0000\u0000\u0000\u0090\u02e6\u0001\u0000\u0000\u0000\u0092"+
		"\u0301\u0001\u0000\u0000\u0000\u0094\u0303\u0001\u0000\u0000\u0000\u0096"+
		"\u0098\u0003\u0002\u0001\u0000\u0097\u0096\u0001\u0000\u0000\u0000\u0098"+
		"\u009b\u0001\u0000\u0000\u0000\u0099\u0097\u0001\u0000\u0000\u0000\u0099"+
		"\u009a\u0001\u0000\u0000\u0000\u009a\u009c\u0001\u0000\u0000\u0000\u009b"+
		"\u0099\u0001\u0000\u0000\u0000\u009c\u009d\u0005\u0000\u0000\u0001\u009d"+
		"\u0001\u0001\u0000\u0000\u0000\u009e\u00a9\u0003\u0004\u0002\u0000\u009f"+
		"\u00a9\u0003\u0012\t\u0000\u00a0\u00a9\u0003\u0018\f\u0000\u00a1\u00a9"+
		"\u0003 \u0010\u0000\u00a2\u00a9\u0003*\u0015\u0000\u00a3\u00a9\u0003D"+
		"\"\u0000\u00a4\u00a9\u0003J%\u0000\u00a5\u00a9\u0003`0\u0000\u00a6\u00a9"+
		"\u0003v;\u0000\u00a7\u00a9\u0003\u0094J\u0000\u00a8\u009e\u0001\u0000"+
		"\u0000\u0000\u00a8\u009f\u0001\u0000\u0000\u0000\u00a8\u00a0\u0001\u0000"+
		"\u0000\u0000\u00a8\u00a1\u0001\u0000\u0000\u0000\u00a8\u00a2\u0001\u0000"+
		"\u0000\u0000\u00a8\u00a3\u0001\u0000\u0000\u0000\u00a8\u00a4\u0001\u0000"+
		"\u0000\u0000\u00a8\u00a5\u0001\u0000\u0000\u0000\u00a8\u00a6\u0001\u0000"+
		"\u0000\u0000\u00a8\u00a7\u0001\u0000\u0000\u0000\u00a9\u0003\u0001\u0000"+
		"\u0000\u0000\u00aa\u00ab\u0005\u0001\u0000\u0000\u00ab\u00af\u0005\u0002"+
		"\u0000\u0000\u00ac\u00ae\u0003\u0006\u0003\u0000\u00ad\u00ac\u0001\u0000"+
		"\u0000\u0000\u00ae\u00b1\u0001\u0000\u0000\u0000\u00af\u00ad\u0001\u0000"+
		"\u0000\u0000\u00af\u00b0\u0001\u0000\u0000\u0000\u00b0\u00b2\u0001\u0000"+
		"\u0000\u0000\u00b1\u00af\u0001\u0000\u0000\u0000\u00b2\u00b3\u0005\u0003"+
		"\u0000\u0000\u00b3\u0005\u0001\u0000\u0000\u0000\u00b4\u00b5\u0003\b\u0004"+
		"\u0000\u00b5\u00b6\u0005\u0004\u0000\u0000\u00b6\u00b7\u0003\n\u0005\u0000"+
		"\u00b7\u00b8\u0005\u0005\u0000\u0000\u00b8\u00c3\u0001\u0000\u0000\u0000"+
		"\u00b9\u00ba\u0005\u0006\u0000\u0000\u00ba\u00be\u0005\u0002\u0000\u0000"+
		"\u00bb\u00bd\u0003\u0010\b\u0000\u00bc\u00bb\u0001\u0000\u0000\u0000\u00bd"+
		"\u00c0\u0001\u0000\u0000\u0000\u00be\u00bc\u0001\u0000\u0000\u0000\u00be"+
		"\u00bf\u0001\u0000\u0000\u0000\u00bf\u00c1\u0001\u0000\u0000\u0000\u00c0"+
		"\u00be\u0001\u0000\u0000\u0000\u00c1\u00c3\u0005\u0003\u0000\u0000\u00c2"+
		"\u00b4\u0001\u0000\u0000\u0000\u00c2\u00b9\u0001\u0000\u0000\u0000\u00c3"+
		"\u0007\u0001\u0000\u0000\u0000\u00c4\u00c5\u00054\u0000\u0000\u00c5\t"+
		"\u0001\u0000\u0000\u0000\u00c6\u00cb\u00052\u0000\u0000\u00c7\u00cb\u0005"+
		"1\u0000\u0000\u00c8\u00cb\u00050\u0000\u0000\u00c9\u00cb\u0003\f\u0006"+
		"\u0000\u00ca\u00c6\u0001\u0000\u0000\u0000\u00ca\u00c7\u0001\u0000\u0000"+
		"\u0000\u00ca\u00c8\u0001\u0000\u0000\u0000\u00ca\u00c9\u0001\u0000\u0000"+
		"\u0000\u00cb\u000b\u0001\u0000\u0000\u0000\u00cc\u00cd\u0005\u0007\u0000"+
		"\u0000\u00cd\u00d2\u0003\u000e\u0007\u0000\u00ce\u00cf\u0005\b\u0000\u0000"+
		"\u00cf\u00d1\u0003\u000e\u0007\u0000\u00d0\u00ce\u0001\u0000\u0000\u0000"+
		"\u00d1\u00d4\u0001\u0000\u0000\u0000\u00d2\u00d0\u0001\u0000\u0000\u0000"+
		"\u00d2\u00d3\u0001\u0000\u0000\u0000\u00d3\u00d5\u0001\u0000\u0000\u0000"+
		"\u00d4\u00d2\u0001\u0000\u0000\u0000\u00d5\u00d6\u0005\t\u0000\u0000\u00d6"+
		"\r\u0001\u0000\u0000\u0000\u00d7\u00d8\u0005\n\u0000\u0000\u00d8\u00db"+
		"\u00054\u0000\u0000\u00d9\u00db\u00052\u0000\u0000\u00da\u00d7\u0001\u0000"+
		"\u0000\u0000\u00da\u00d9\u0001\u0000\u0000\u0000\u00db\u000f\u0001\u0000"+
		"\u0000\u0000\u00dc\u00dd\u00054\u0000\u0000\u00dd\u00e0\u0005\u0004\u0000"+
		"\u0000\u00de\u00e1\u0003\n\u0005\u0000\u00df\u00e1\u0003\f\u0006\u0000"+
		"\u00e0\u00de\u0001\u0000\u0000\u0000\u00e0\u00df\u0001\u0000\u0000\u0000"+
		"\u00e1\u00e2\u0001\u0000\u0000\u0000\u00e2\u00e3\u0005\u0005\u0000\u0000"+
		"\u00e3\u0011\u0001\u0000\u0000\u0000\u00e4\u00e5\u0005\u000b\u0000\u0000"+
		"\u00e5\u00e7\u00054\u0000\u0000\u00e6\u00e8\u0003\u0014\n\u0000\u00e7"+
		"\u00e6\u0001\u0000\u0000\u0000\u00e7\u00e8\u0001\u0000\u0000\u0000\u00e8"+
		"\u0013\u0001\u0000\u0000\u0000\u00e9\u00ed\u0005\u0002\u0000\u0000\u00ea"+
		"\u00ec\u0003\u0016\u000b\u0000\u00eb\u00ea\u0001\u0000\u0000\u0000\u00ec"+
		"\u00ef\u0001\u0000\u0000\u0000\u00ed\u00eb\u0001\u0000\u0000\u0000\u00ed"+
		"\u00ee\u0001\u0000\u0000\u0000\u00ee\u00f0\u0001\u0000\u0000\u0000\u00ef"+
		"\u00ed\u0001\u0000\u0000\u0000\u00f0\u00f1\u0005\u0003\u0000\u0000\u00f1"+
		"\u0015\u0001\u0000\u0000\u0000\u00f2\u00f7\u0003\u0012\t\u0000\u00f3\u00f7"+
		"\u0003 \u0010\u0000\u00f4\u00f7\u0003*\u0015\u0000\u00f5\u00f7\u0003\u0090"+
		"H\u0000\u00f6\u00f2\u0001\u0000\u0000\u0000\u00f6\u00f3\u0001\u0000\u0000"+
		"\u0000\u00f6\u00f4\u0001\u0000\u0000\u0000\u00f6\u00f5\u0001\u0000\u0000"+
		"\u0000\u00f7\u0017\u0001\u0000\u0000\u0000\u00f8\u00f9\u0005\f\u0000\u0000"+
		"\u00f9\u00fa\u0003\u001a\r\u0000\u00fa\u00fb\u0005\r\u0000\u0000\u00fb"+
		"\u00fe\u0003\u001c\u000e\u0000\u00fc\u00fd\u0005\u000e\u0000\u0000\u00fd"+
		"\u00ff\u00054\u0000\u0000\u00fe\u00fc\u0001\u0000\u0000\u0000\u00fe\u00ff"+
		"\u0001\u0000\u0000\u0000\u00ff\u0101\u0001\u0000\u0000\u0000\u0100\u0102"+
		"\u0005\u0005\u0000\u0000\u0101\u0100\u0001\u0000\u0000\u0000\u0101\u0102"+
		"\u0001\u0000\u0000\u0000\u0102\u0019\u0001\u0000\u0000\u0000\u0103\u0110"+
		"\u0005\u000f\u0000\u0000\u0104\u0110\u0005\u0010\u0000\u0000\u0105\u0110"+
		"\u0005\u0011\u0000\u0000\u0106\u0110\u0005\u0012\u0000\u0000\u0107\u0108"+
		"\u0005\u0013\u0000\u0000\u0108\u0109\u0003,\u0016\u0000\u0109\u010a\u0005"+
		"4\u0000\u0000\u010a\u0110\u0001\u0000\u0000\u0000\u010b\u010c\u0005\u0014"+
		"\u0000\u0000\u010c\u010d\u0003\"\u0011\u0000\u010d\u010e\u00054\u0000"+
		"\u0000\u010e\u0110\u0001\u0000\u0000\u0000\u010f\u0103\u0001\u0000\u0000"+
		"\u0000\u010f\u0104\u0001\u0000\u0000\u0000\u010f\u0105\u0001\u0000\u0000"+
		"\u0000\u010f\u0106\u0001\u0000\u0000\u0000\u010f\u0107\u0001\u0000\u0000"+
		"\u0000\u010f\u010b\u0001\u0000\u0000\u0000\u0110\u001b\u0001\u0000\u0000"+
		"\u0000\u0111\u0114\u00052\u0000\u0000\u0112\u0114\u0003\u001e\u000f\u0000"+
		"\u0113\u0111\u0001\u0000\u0000\u0000\u0113\u0112\u0001\u0000\u0000\u0000"+
		"\u0114\u001d\u0001\u0000\u0000\u0000\u0115\u011a\u00054\u0000\u0000\u0116"+
		"\u0117\u0005\u0015\u0000\u0000\u0117\u0119\u00054\u0000\u0000\u0118\u0116"+
		"\u0001\u0000\u0000\u0000\u0119\u011c\u0001\u0000\u0000\u0000\u011a\u0118"+
		"\u0001\u0000\u0000\u0000\u011a\u011b\u0001\u0000\u0000\u0000\u011b\u001f"+
		"\u0001\u0000\u0000\u0000\u011c\u011a\u0001\u0000\u0000\u0000\u011d\u011e"+
		"\u0005\u0014\u0000\u0000\u011e\u011f\u0003\"\u0011\u0000\u011f\u0120\u0005"+
		"4\u0000\u0000\u0120\u0121\u0003$\u0012\u0000\u0121!\u0001\u0000\u0000"+
		"\u0000\u0122\u0123\u0007\u0000\u0000\u0000\u0123#\u0001\u0000\u0000\u0000"+
		"\u0124\u0128\u0005\u0002\u0000\u0000\u0125\u0127\u0003&\u0013\u0000\u0126"+
		"\u0125\u0001\u0000\u0000\u0000\u0127\u012a\u0001\u0000\u0000\u0000\u0128"+
		"\u0126\u0001\u0000\u0000\u0000\u0128\u0129\u0001\u0000\u0000\u0000\u0129"+
		"\u012b\u0001\u0000\u0000\u0000\u012a\u0128\u0001\u0000\u0000\u0000\u012b"+
		"\u012c\u0005\u0003\u0000\u0000\u012c%\u0001\u0000\u0000\u0000\u012d\u0132"+
		"\u0003d2\u0000\u012e\u0132\u0003J%\u0000\u012f\u0132\u0003(\u0014\u0000"+
		"\u0130\u0132\u0003\u0084B\u0000\u0131\u012d\u0001\u0000\u0000\u0000\u0131"+
		"\u012e\u0001\u0000\u0000\u0000\u0131\u012f\u0001\u0000\u0000\u0000\u0131"+
		"\u0130\u0001\u0000\u0000\u0000\u0132\'\u0001\u0000\u0000\u0000\u0133\u0134"+
		"\u0003\"\u0011\u0000\u0134\u0135\u00054\u0000\u0000\u0135\u0136\u0005"+
		"\u0005\u0000\u0000\u0136\u013d\u0001\u0000\u0000\u0000\u0137\u0138\u0005"+
		"\u0018\u0000\u0000\u0138\u0139\u0003\"\u0011\u0000\u0139\u013a\u00054"+
		"\u0000\u0000\u013a\u013b\u0005\u0005\u0000\u0000\u013b\u013d\u0001\u0000"+
		"\u0000\u0000\u013c\u0133\u0001\u0000\u0000\u0000\u013c\u0137\u0001\u0000"+
		"\u0000\u0000\u013d)\u0001\u0000\u0000\u0000\u013e\u013f\u0005\u0013\u0000"+
		"\u0000\u013f\u0140\u0003,\u0016\u0000\u0140\u0141\u00054\u0000\u0000\u0141"+
		"\u0142\u0003.\u0017\u0000\u0142+\u0001\u0000\u0000\u0000\u0143\u0144\u0007"+
		"\u0000\u0000\u0000\u0144-\u0001\u0000\u0000\u0000\u0145\u0149\u0005\u0002"+
		"\u0000\u0000\u0146\u0148\u00030\u0018\u0000\u0147\u0146\u0001\u0000\u0000"+
		"\u0000\u0148\u014b\u0001\u0000\u0000\u0000\u0149\u0147\u0001\u0000\u0000"+
		"\u0000\u0149\u014a\u0001\u0000\u0000\u0000\u014a\u014c\u0001\u0000\u0000"+
		"\u0000\u014b\u0149\u0001\u0000\u0000\u0000\u014c\u014d\u0005\u0003\u0000"+
		"\u0000\u014d/\u0001\u0000\u0000\u0000\u014e\u0155\u0003d2\u0000\u014f"+
		"\u0155\u0003J%\u0000\u0150\u0155\u00032\u0019\u0000\u0151\u0155\u0003"+
		"\u0084B\u0000\u0152\u0155\u00038\u001c\u0000\u0153\u0155\u0003<\u001e"+
		"\u0000\u0154\u014e\u0001\u0000\u0000\u0000\u0154\u014f\u0001\u0000\u0000"+
		"\u0000\u0154\u0150\u0001\u0000\u0000\u0000\u0154\u0151\u0001\u0000\u0000"+
		"\u0000\u0154\u0152\u0001\u0000\u0000\u0000\u0154\u0153\u0001\u0000\u0000"+
		"\u0000\u01551\u0001\u0000\u0000\u0000\u0156\u0157\u0003,\u0016\u0000\u0157"+
		"\u0159\u00054\u0000\u0000\u0158\u015a\u00034\u001a\u0000\u0159\u0158\u0001"+
		"\u0000\u0000\u0000\u0159\u015a\u0001\u0000\u0000\u0000\u015a\u015c\u0001"+
		"\u0000\u0000\u0000\u015b\u015d\u0005\u0005\u0000\u0000\u015c\u015b\u0001"+
		"\u0000\u0000\u0000\u015c\u015d\u0001\u0000\u0000\u0000\u015d\u0167\u0001"+
		"\u0000\u0000\u0000\u015e\u015f\u0003\"\u0011\u0000\u015f\u0161\u00054"+
		"\u0000\u0000\u0160\u0162\u00034\u001a\u0000\u0161\u0160\u0001\u0000\u0000"+
		"\u0000\u0161\u0162\u0001\u0000\u0000\u0000\u0162\u0164\u0001\u0000\u0000"+
		"\u0000\u0163\u0165\u0005\u0005\u0000\u0000\u0164\u0163\u0001\u0000\u0000"+
		"\u0000\u0164\u0165\u0001\u0000\u0000\u0000\u0165\u0167\u0001\u0000\u0000"+
		"\u0000\u0166\u0156\u0001\u0000\u0000\u0000\u0166\u015e\u0001\u0000\u0000"+
		"\u0000\u01673\u0001\u0000\u0000\u0000\u0168\u016c\u0005\u0002\u0000\u0000"+
		"\u0169\u016b\u00036\u001b\u0000\u016a\u0169\u0001\u0000\u0000\u0000\u016b"+
		"\u016e\u0001\u0000\u0000\u0000\u016c\u016a\u0001\u0000\u0000\u0000\u016c"+
		"\u016d\u0001\u0000\u0000\u0000\u016d\u016f\u0001\u0000\u0000\u0000\u016e"+
		"\u016c\u0001\u0000\u0000\u0000\u016f\u0170\u0005\u0003\u0000\u0000\u0170"+
		"5\u0001\u0000\u0000\u0000\u0171\u0175\u0003d2\u0000\u0172\u0175\u0003"+
		"8\u001c\u0000\u0173\u0175\u0003\u008cF\u0000\u0174\u0171\u0001\u0000\u0000"+
		"\u0000\u0174\u0172\u0001\u0000\u0000\u0000\u0174\u0173\u0001\u0000\u0000"+
		"\u0000\u01757\u0001\u0000\u0000\u0000\u0176\u0177\u0005\u0019\u0000\u0000"+
		"\u0177\u017c\u0003:\u001d\u0000\u0178\u0179\u0005\b\u0000\u0000\u0179"+
		"\u017b\u0003:\u001d\u0000\u017a\u0178\u0001\u0000\u0000\u0000\u017b\u017e"+
		"\u0001\u0000\u0000\u0000\u017c\u017a\u0001\u0000\u0000\u0000\u017c\u017d"+
		"\u0001\u0000\u0000\u0000\u017d\u017f\u0001\u0000\u0000\u0000\u017e\u017c"+
		"\u0001\u0000\u0000\u0000\u017f\u0180\u0005\u0005\u0000\u0000\u01809\u0001"+
		"\u0000\u0000\u0000\u0181\u018d\u00054\u0000\u0000\u0182\u0183\u00054\u0000"+
		"\u0000\u0183\u0184\u0005\u0007\u0000\u0000\u0184\u0185\u00051\u0000\u0000"+
		"\u0185\u018d\u0005\t\u0000\u0000\u0186\u0187\u0003,\u0016\u0000\u0187"+
		"\u0188\u00054\u0000\u0000\u0188\u018d\u0001\u0000\u0000\u0000\u0189\u018a"+
		"\u0003\"\u0011\u0000\u018a\u018b\u00054\u0000\u0000\u018b\u018d\u0001"+
		"\u0000\u0000\u0000\u018c\u0181\u0001\u0000\u0000\u0000\u018c\u0182\u0001"+
		"\u0000\u0000\u0000\u018c\u0186\u0001\u0000\u0000\u0000\u018c\u0189\u0001"+
		"\u0000\u0000\u0000\u018d;\u0001\u0000\u0000\u0000\u018e\u018f\u0005\u001a"+
		"\u0000\u0000\u018f\u0190\u0003>\u001f\u0000\u0190\u0191\u0003@ \u0000"+
		"\u0191\u0195\u0005\u0002\u0000\u0000\u0192\u0194\u0003B!\u0000\u0193\u0192"+
		"\u0001\u0000\u0000\u0000\u0194\u0197\u0001\u0000\u0000\u0000\u0195\u0193"+
		"\u0001\u0000\u0000\u0000\u0195\u0196\u0001\u0000\u0000\u0000\u0196\u0198"+
		"\u0001\u0000\u0000\u0000\u0197\u0195\u0001\u0000\u0000\u0000\u0198\u0199"+
		"\u0005\u0003\u0000\u0000\u0199=\u0001\u0000\u0000\u0000\u019a\u01a2\u0005"+
		"\u001b\u0000\u0000\u019b\u01a2\u0005\u001c\u0000\u0000\u019c\u01a2\u0005"+
		"\u001d\u0000\u0000\u019d\u019e\u0005\u001e\u0000\u0000\u019e\u01a2\u0005"+
		"\u001f\u0000\u0000\u019f\u01a0\u0005\u001e\u0000\u0000\u01a0\u01a2\u0005"+
		" \u0000\u0000\u01a1\u019a\u0001\u0000\u0000\u0000\u01a1\u019b\u0001\u0000"+
		"\u0000\u0000\u01a1\u019c\u0001\u0000\u0000\u0000\u01a1\u019d\u0001\u0000"+
		"\u0000\u0000\u01a1\u019f\u0001\u0000\u0000\u0000\u01a2?\u0001\u0000\u0000"+
		"\u0000\u01a3\u01a7\u00054\u0000\u0000\u01a4\u01a5\u0005\u0007\u0000\u0000"+
		"\u01a5\u01a6\u00051\u0000\u0000\u01a6\u01a8\u0005\t\u0000\u0000\u01a7"+
		"\u01a4\u0001\u0000\u0000\u0000\u01a7\u01a8\u0001\u0000\u0000\u0000\u01a8"+
		"A\u0001\u0000\u0000\u0000\u01a9\u01ac\u0003J%\u0000\u01aa\u01ac\u0003"+
		"z=\u0000\u01ab\u01a9\u0001\u0000\u0000\u0000\u01ab\u01aa\u0001\u0000\u0000"+
		"\u0000\u01acC\u0001\u0000\u0000\u0000\u01ad\u01ae\u0005!\u0000\u0000\u01ae"+
		"\u01b0\u0003F#\u0000\u01af\u01b1\u00054\u0000\u0000\u01b0\u01af\u0001"+
		"\u0000\u0000\u0000\u01b0\u01b1\u0001\u0000\u0000\u0000\u01b1\u01b2\u0001"+
		"\u0000\u0000\u0000\u01b2\u01b3\u0005\u0002\u0000\u0000\u01b3\u01b4\u0003"+
		"H$\u0000\u01b4\u01b5\u0005\u0003\u0000\u0000\u01b5E\u0001\u0000\u0000"+
		"\u0000\u01b6\u01b7\u0007\u0001\u0000\u0000\u01b7G\u0001\u0000\u0000\u0000"+
		"\u01b8\u01ba\b\u0002\u0000\u0000\u01b9\u01b8\u0001\u0000\u0000\u0000\u01ba"+
		"\u01bd\u0001\u0000\u0000\u0000\u01bb\u01b9\u0001\u0000\u0000\u0000\u01bb"+
		"\u01bc\u0001\u0000\u0000\u0000\u01bcI\u0001\u0000\u0000\u0000\u01bd\u01bb"+
		"\u0001\u0000\u0000\u0000\u01be\u01c0\u0003P(\u0000\u01bf\u01c1\u0003R"+
		")\u0000\u01c0\u01bf\u0001\u0000\u0000\u0000\u01c0\u01c1\u0001\u0000\u0000"+
		"\u0000\u01c1\u01c2\u0001\u0000\u0000\u0000\u01c2\u01c3\u0003T*\u0000\u01c3"+
		"\u01c6\u0001\u0000\u0000\u0000\u01c4\u01c6\u0003L&\u0000\u01c5\u01be\u0001"+
		"\u0000\u0000\u0000\u01c5\u01c4\u0001\u0000\u0000\u0000\u01c6K\u0001\u0000"+
		"\u0000\u0000\u01c7\u01c8\u0005\"\u0000\u0000\u01c8\u01c9\u0005\u0002\u0000"+
		"\u0000\u01c9\u01ca\u0003N\'\u0000\u01ca\u01cb\u0005\u0003\u0000\u0000"+
		"\u01cbM\u0001\u0000\u0000\u0000\u01cc\u01ce\b\u0002\u0000\u0000\u01cd"+
		"\u01cc\u0001\u0000\u0000\u0000\u01ce\u01d1\u0001\u0000\u0000\u0000\u01cf"+
		"\u01cd\u0001\u0000\u0000\u0000\u01cf\u01d0\u0001\u0000\u0000\u0000\u01d0"+
		"O\u0001\u0000\u0000\u0000\u01d1\u01cf\u0001\u0000\u0000\u0000\u01d2\u01d3"+
		"\u0007\u0003\u0000\u0000\u01d3Q\u0001\u0000\u0000\u0000\u01d4\u01d5\u0005"+
		"\u0007\u0000\u0000\u01d5\u01d6\u00051\u0000\u0000\u01d6\u01d7\u0005\t"+
		"\u0000\u0000\u01d7S\u0001\u0000\u0000\u0000\u01d8\u01dc\u0005\u0002\u0000"+
		"\u0000\u01d9\u01db\u0003V+\u0000\u01da\u01d9\u0001\u0000\u0000\u0000\u01db"+
		"\u01de\u0001\u0000\u0000\u0000\u01dc\u01da\u0001\u0000\u0000\u0000\u01dc"+
		"\u01dd\u0001\u0000\u0000\u0000\u01dd\u01df\u0001\u0000\u0000\u0000\u01de"+
		"\u01dc\u0001\u0000\u0000\u0000\u01df\u01e0\u0005\u0003\u0000\u0000\u01e0"+
		"U\u0001\u0000\u0000\u0000\u01e1\u01ea\u0003X,\u0000\u01e2\u01ea\u0003"+
		"J%\u0000\u01e3\u01ea\u0003`0\u0000\u01e4\u01ea\u0003v;\u0000\u01e5\u01ea"+
		"\u0003^/\u0000\u01e6\u01ea\u0003z=\u0000\u01e7\u01ea\u0003\u0090H\u0000"+
		"\u01e8\u01ea\u0003\u0094J\u0000\u01e9\u01e1\u0001\u0000\u0000\u0000\u01e9"+
		"\u01e2\u0001\u0000\u0000\u0000\u01e9\u01e3\u0001\u0000\u0000\u0000\u01e9"+
		"\u01e4\u0001\u0000\u0000\u0000\u01e9\u01e5\u0001\u0000\u0000\u0000\u01e9"+
		"\u01e6\u0001\u0000\u0000\u0000\u01e9\u01e7\u0001\u0000\u0000\u0000\u01e9"+
		"\u01e8\u0001\u0000\u0000\u0000\u01eaW\u0001\u0000\u0000\u0000\u01eb\u01ec"+
		"\u0003Z-\u0000\u01ec\u01ed\u0005%\u0000\u0000\u01ed\u01ee\u0003\\.\u0000"+
		"\u01ee\u01ef\u0005\u0005\u0000\u0000\u01ef\u01f6\u0001\u0000\u0000\u0000"+
		"\u01f0\u01f1\u0003Z-\u0000\u01f1\u01f2\u0005\u0004\u0000\u0000\u01f2\u01f3"+
		"\u0003\\.\u0000\u01f3\u01f4\u0005\u0005\u0000\u0000\u01f4\u01f6\u0001"+
		"\u0000\u0000\u0000\u01f5\u01eb\u0001\u0000\u0000\u0000\u01f5\u01f0\u0001"+
		"\u0000\u0000\u0000\u01f6Y\u0001\u0000\u0000\u0000\u01f7\u01f8\u00054\u0000"+
		"\u0000\u01f8[\u0001\u0000\u0000\u0000\u01f9\u01fd\u00052\u0000\u0000\u01fa"+
		"\u01fd\u00053\u0000\u0000\u01fb\u01fd\u0003\u0086C\u0000\u01fc\u01f9\u0001"+
		"\u0000\u0000\u0000\u01fc\u01fa\u0001\u0000\u0000\u0000\u01fc\u01fb\u0001"+
		"\u0000\u0000\u0000\u01fd]\u0001\u0000\u0000\u0000\u01fe\u01ff\u0007\u0004"+
		"\u0000\u0000\u01ff_\u0001\u0000\u0000\u0000\u0200\u0201\u0005\"\u0000"+
		"\u0000\u0201\u0205\u0005\u0002\u0000\u0000\u0202\u0204\u0003b1\u0000\u0203"+
		"\u0202\u0001\u0000\u0000\u0000\u0204\u0207\u0001\u0000\u0000\u0000\u0205"+
		"\u0203\u0001\u0000\u0000\u0000\u0205\u0206\u0001\u0000\u0000\u0000\u0206"+
		"\u0208\u0001\u0000\u0000\u0000\u0207\u0205\u0001\u0000\u0000\u0000\u0208"+
		"\u0209\u0005\u0003\u0000\u0000\u0209a\u0001\u0000\u0000\u0000\u020a\u0217"+
		"\u0003d2\u0000\u020b\u020c\u0003j5\u0000\u020c\u0210\u0005\u0002\u0000"+
		"\u0000\u020d\u020f\u0003b1\u0000\u020e\u020d\u0001\u0000\u0000\u0000\u020f"+
		"\u0212\u0001\u0000\u0000\u0000\u0210\u020e\u0001\u0000\u0000\u0000\u0210"+
		"\u0211\u0001\u0000\u0000\u0000\u0211\u0213\u0001\u0000\u0000\u0000\u0212"+
		"\u0210\u0001\u0000\u0000\u0000\u0213\u0214\u0005\u0003\u0000\u0000\u0214"+
		"\u0217\u0001\u0000\u0000\u0000\u0215\u0217\u0003\u0080@\u0000\u0216\u020a"+
		"\u0001\u0000\u0000\u0000\u0216\u020b\u0001\u0000\u0000\u0000\u0216\u0215"+
		"\u0001\u0000\u0000\u0000\u0217c\u0001\u0000\u0000\u0000\u0218\u0219\u0003"+
		"f3\u0000\u0219\u021a\u0005%\u0000\u0000\u021a\u021b\u0003h4\u0000\u021b"+
		"\u021c\u0005\u0005\u0000\u0000\u021c\u0224\u0001\u0000\u0000\u0000\u021d"+
		"\u021e\u0003f3\u0000\u021e\u021f\u0005\b\u0000\u0000\u021f\u0224\u0001"+
		"\u0000\u0000\u0000\u0220\u0221\u0003f3\u0000\u0221\u0222\u0005\u0005\u0000"+
		"\u0000\u0222\u0224\u0001\u0000\u0000\u0000\u0223\u0218\u0001\u0000\u0000"+
		"\u0000\u0223\u021d\u0001\u0000\u0000\u0000\u0223\u0220\u0001\u0000\u0000"+
		"\u0000\u0224e\u0001\u0000\u0000\u0000\u0225\u022a\u00054\u0000\u0000\u0226"+
		"\u0227\u0005&\u0000\u0000\u0227\u0229\u00054\u0000\u0000\u0228\u0226\u0001"+
		"\u0000\u0000\u0000\u0229\u022c\u0001\u0000\u0000\u0000\u022a\u0228\u0001"+
		"\u0000\u0000\u0000\u022a\u022b\u0001\u0000\u0000\u0000\u022bg\u0001\u0000"+
		"\u0000\u0000\u022c\u022a\u0001\u0000\u0000\u0000\u022d\u0232\u00052\u0000"+
		"\u0000\u022e\u0232\u00053\u0000\u0000\u022f\u0232\u0003\u0086C\u0000\u0230"+
		"\u0232\u0003p8\u0000\u0231\u022d\u0001\u0000\u0000\u0000\u0231\u022e\u0001"+
		"\u0000\u0000\u0000\u0231\u022f\u0001\u0000\u0000\u0000\u0231\u0230\u0001"+
		"\u0000\u0000\u0000\u0232i\u0001\u0000\u0000\u0000\u0233\u0234\u0005\u0015"+
		"\u0000\u0000\u0234\u023d\u00054\u0000\u0000\u0235\u0236\u0005\'\u0000"+
		"\u0000\u0236\u023d\u00054\u0000\u0000\u0237\u0238\u0005(\u0000\u0000\u0238"+
		"\u023d\u0003l6\u0000\u0239\u023a\u0005(\u0000\u0000\u023a\u023d\u0003"+
		"n7\u0000\u023b\u023d\u0005(\u0000\u0000\u023c\u0233\u0001\u0000\u0000"+
		"\u0000\u023c\u0235\u0001\u0000\u0000\u0000\u023c\u0237\u0001\u0000\u0000"+
		"\u0000\u023c\u0239\u0001\u0000\u0000\u0000\u023c\u023b\u0001\u0000\u0000"+
		"\u0000\u023dk\u0001\u0000\u0000\u0000\u023e\u023f\u0005%\u0000\u0000\u023f"+
		"\u0240\u00054\u0000\u0000\u0240m\u0001\u0000\u0000\u0000\u0241\u0242\u0005"+
		")\u0000\u0000\u0242\u0243\u00054\u0000\u0000\u0243o\u0001\u0000\u0000"+
		"\u0000\u0244\u0245\u00054\u0000\u0000\u0245\u0247\u0005*\u0000\u0000\u0246"+
		"\u0248\u0003r9\u0000\u0247\u0246\u0001\u0000\u0000\u0000\u0247\u0248\u0001"+
		"\u0000\u0000\u0000\u0248\u0249\u0001\u0000\u0000\u0000\u0249\u024a\u0005"+
		"+\u0000\u0000\u024aq\u0001\u0000\u0000\u0000\u024b\u0250\u0003t:\u0000"+
		"\u024c\u024d\u0005\b\u0000\u0000\u024d\u024f\u0003t:\u0000\u024e\u024c"+
		"\u0001\u0000\u0000\u0000\u024f\u0252\u0001\u0000\u0000\u0000\u0250\u024e"+
		"\u0001\u0000\u0000\u0000\u0250\u0251\u0001\u0000\u0000\u0000\u0251s\u0001"+
		"\u0000\u0000\u0000\u0252\u0250\u0001\u0000\u0000\u0000\u0253\u0254\u0003"+
		"h4\u0000\u0254u\u0001\u0000\u0000\u0000\u0255\u0256\u0005$\u0000\u0000"+
		"\u0256\u0257\u0005\u0002\u0000\u0000\u0257\u0258\u0003x<\u0000\u0258\u0259"+
		"\u0005\u0003\u0000\u0000\u0259w\u0001\u0000\u0000\u0000\u025a\u025c\b"+
		"\u0002\u0000\u0000\u025b\u025a\u0001\u0000\u0000\u0000\u025c\u025d\u0001"+
		"\u0000\u0000\u0000\u025d\u025b\u0001\u0000\u0000\u0000\u025d\u025e\u0001"+
		"\u0000\u0000\u0000\u025e\u0261\u0001\u0000\u0000\u0000\u025f\u0261\u0001"+
		"\u0000\u0000\u0000\u0260\u025b\u0001\u0000\u0000\u0000\u0260\u025f\u0001"+
		"\u0000\u0000\u0000\u0261y\u0001\u0000\u0000\u0000\u0262\u0263\u0003,\u0016"+
		"\u0000\u0263\u0265\u00054\u0000\u0000\u0264\u0266\u0003|>\u0000\u0265"+
		"\u0264\u0001\u0000\u0000\u0000\u0265\u0266\u0001\u0000\u0000\u0000\u0266"+
		"\u0269\u0001\u0000\u0000\u0000\u0267\u0268\u0005\r\u0000\u0000\u0268\u026a"+
		"\u0003\u008eG\u0000\u0269\u0267\u0001\u0000\u0000\u0000\u0269\u026a\u0001"+
		"\u0000\u0000\u0000\u026a\u026b\u0001\u0000\u0000\u0000\u026b\u026c\u0005"+
		"\u0005\u0000\u0000\u026c\u0296\u0001\u0000\u0000\u0000\u026d\u026e\u0003"+
		"\"\u0011\u0000\u026e\u0270\u00054\u0000\u0000\u026f\u0271\u0003|>\u0000"+
		"\u0270\u026f\u0001\u0000\u0000\u0000\u0270\u0271\u0001\u0000\u0000\u0000"+
		"\u0271\u0274\u0001\u0000\u0000\u0000\u0272\u0273\u0005\r\u0000\u0000\u0273"+
		"\u0275\u0003\u008eG\u0000\u0274\u0272\u0001\u0000\u0000\u0000\u0274\u0275"+
		"\u0001\u0000\u0000\u0000\u0275\u0276\u0001\u0000\u0000\u0000\u0276\u0277"+
		"\u0005\u0005\u0000\u0000\u0277\u0296\u0001\u0000\u0000\u0000\u0278\u0279"+
		"\u0005\u0013\u0000\u0000\u0279\u027a\u0003,\u0016\u0000\u027a\u027c\u0005"+
		"4\u0000\u0000\u027b\u027d\u0003|>\u0000\u027c\u027b\u0001\u0000\u0000"+
		"\u0000\u027c\u027d\u0001\u0000\u0000\u0000\u027d\u0280\u0001\u0000\u0000"+
		"\u0000\u027e\u027f\u0005\r\u0000\u0000\u027f\u0281\u0003\u008eG\u0000"+
		"\u0280\u027e\u0001\u0000\u0000\u0000\u0280\u0281\u0001\u0000\u0000\u0000"+
		"\u0281\u0282\u0001\u0000\u0000\u0000\u0282\u0283\u0005\u0005\u0000\u0000"+
		"\u0283\u0296\u0001\u0000\u0000\u0000\u0284\u0285\u0005\u0014\u0000\u0000"+
		"\u0285\u0286\u0003\"\u0011\u0000\u0286\u0288\u00054\u0000\u0000\u0287"+
		"\u0289\u0003|>\u0000\u0288\u0287\u0001\u0000\u0000\u0000\u0288\u0289\u0001"+
		"\u0000\u0000\u0000\u0289\u028c\u0001\u0000\u0000\u0000\u028a\u028b\u0005"+
		"\r\u0000\u0000\u028b\u028d\u0003\u008eG\u0000\u028c\u028a\u0001\u0000"+
		"\u0000\u0000\u028c\u028d\u0001\u0000\u0000\u0000\u028d\u028e\u0001\u0000"+
		"\u0000\u0000\u028e\u028f\u0005\u0005\u0000\u0000\u028f\u0296\u0001\u0000"+
		"\u0000\u0000\u0290\u0291\u0005!\u0000\u0000\u0291\u0292\u0003F#\u0000"+
		"\u0292\u0293\u00054\u0000\u0000\u0293\u0294\u0005\u0005\u0000\u0000\u0294"+
		"\u0296\u0001\u0000\u0000\u0000\u0295\u0262\u0001\u0000\u0000\u0000\u0295"+
		"\u026d\u0001\u0000\u0000\u0000\u0295\u0278\u0001\u0000\u0000\u0000\u0295"+
		"\u0284\u0001\u0000\u0000\u0000\u0295\u0290\u0001\u0000\u0000\u0000\u0296"+
		"{\u0001\u0000\u0000\u0000\u0297\u029b\u0005\u0002\u0000\u0000\u0298\u029a"+
		"\u0003~?\u0000\u0299\u0298\u0001\u0000\u0000\u0000\u029a\u029d\u0001\u0000"+
		"\u0000\u0000\u029b\u0299\u0001\u0000\u0000\u0000\u029b\u029c\u0001\u0000"+
		"\u0000\u0000\u029c\u029e\u0001\u0000\u0000\u0000\u029d\u029b\u0001\u0000"+
		"\u0000\u0000\u029e\u029f\u0005\u0003\u0000\u0000\u029f}\u0001\u0000\u0000"+
		"\u0000\u02a0\u02a5\u0003J%\u0000\u02a1\u02a5\u0003`0\u0000\u02a2\u02a5"+
		"\u00038\u001c\u0000\u02a3\u02a5\u0003<\u001e\u0000\u02a4\u02a0\u0001\u0000"+
		"\u0000\u0000\u02a4\u02a1\u0001\u0000\u0000\u0000\u02a4\u02a2\u0001\u0000"+
		"\u0000\u0000\u02a4\u02a3\u0001\u0000\u0000\u0000\u02a5\u007f\u0001\u0000"+
		"\u0000\u0000\u02a6\u02a7\u0003,\u0016\u0000\u02a7\u02a9\u00054\u0000\u0000"+
		"\u02a8\u02aa\u0003\u0082A\u0000\u02a9\u02a8\u0001\u0000\u0000\u0000\u02a9"+
		"\u02aa\u0001\u0000\u0000\u0000\u02aa\u02ab\u0001\u0000\u0000\u0000\u02ab"+
		"\u02ac\u0005\u0005\u0000\u0000\u02ac\u02b5\u0001\u0000\u0000\u0000\u02ad"+
		"\u02ae\u0003\"\u0011\u0000\u02ae\u02b0\u00054\u0000\u0000\u02af\u02b1"+
		"\u0003\u0082A\u0000\u02b0\u02af\u0001\u0000\u0000\u0000\u02b0\u02b1\u0001"+
		"\u0000\u0000\u0000\u02b1\u02b2\u0001\u0000\u0000\u0000\u02b2\u02b3\u0005"+
		"\u0005\u0000\u0000\u02b3\u02b5\u0001\u0000\u0000\u0000\u02b4\u02a6\u0001"+
		"\u0000\u0000\u0000\u02b4\u02ad\u0001\u0000\u0000\u0000\u02b5\u0081\u0001"+
		"\u0000\u0000\u0000\u02b6\u02ba\u0005\u0002\u0000\u0000\u02b7\u02b9\u0003"+
		"d2\u0000\u02b8\u02b7\u0001\u0000\u0000\u0000\u02b9\u02bc\u0001\u0000\u0000"+
		"\u0000\u02ba\u02b8\u0001\u0000\u0000\u0000\u02ba\u02bb\u0001\u0000\u0000"+
		"\u0000\u02bb\u02bd\u0001\u0000\u0000\u0000\u02bc\u02ba\u0001\u0000\u0000"+
		"\u0000\u02bd\u02be\u0005\u0003\u0000\u0000\u02be\u0083\u0001\u0000\u0000"+
		"\u0000\u02bf\u02c0\u00054\u0000\u0000\u02c0\u02c1\u0005%\u0000\u0000\u02c1"+
		"\u02c2\u00052\u0000\u0000\u02c2\u02c3\u0005\u0005\u0000\u0000\u02c3\u0085"+
		"\u0001\u0000\u0000\u0000\u02c4\u02c5\u00054\u0000\u0000\u02c5\u02c7\u0005"+
		"*\u0000\u0000\u02c6\u02c8\u0003\u0088D\u0000\u02c7\u02c6\u0001\u0000\u0000"+
		"\u0000\u02c7\u02c8\u0001\u0000\u0000\u0000\u02c8\u02c9\u0001\u0000\u0000"+
		"\u0000\u02c9\u02ca\u0005+\u0000\u0000\u02ca\u0087\u0001\u0000\u0000\u0000"+
		"\u02cb\u02d0\u0003\u008aE\u0000\u02cc\u02cd\u0005\b\u0000\u0000\u02cd"+
		"\u02cf\u0003\u008aE\u0000\u02ce\u02cc\u0001\u0000\u0000\u0000\u02cf\u02d2"+
		"\u0001\u0000\u0000\u0000\u02d0\u02ce\u0001\u0000\u0000\u0000\u02d0\u02d1"+
		"\u0001\u0000\u0000\u0000\u02d1\u0089\u0001\u0000\u0000\u0000\u02d2\u02d0"+
		"\u0001\u0000\u0000\u0000\u02d3\u02d4\u00054\u0000\u0000\u02d4\u02d5\u0005"+
		"\u0004\u0000\u0000\u02d5\u02d8\u0003h4\u0000\u02d6\u02d8\u00054\u0000"+
		"\u0000\u02d7\u02d3\u0001\u0000\u0000\u0000\u02d7\u02d6\u0001\u0000\u0000"+
		"\u0000\u02d8\u008b\u0001\u0000\u0000\u0000\u02d9\u02da\u00054\u0000\u0000"+
		"\u02da\u02db\u0005\u0004\u0000\u0000\u02db\u02dc\u0003h4\u0000\u02dc\u02dd"+
		"\u0005\u0005\u0000\u0000\u02dd\u008d\u0001\u0000\u0000\u0000\u02de\u02e3"+
		"\u00054\u0000\u0000\u02df\u02e0\u0005\u0015\u0000\u0000\u02e0\u02e2\u0005"+
		"4\u0000\u0000\u02e1\u02df\u0001\u0000\u0000\u0000\u02e2\u02e5\u0001\u0000"+
		"\u0000\u0000\u02e3\u02e1\u0001\u0000\u0000\u0000\u02e3\u02e4\u0001\u0000"+
		"\u0000\u0000\u02e4\u008f\u0001\u0000\u0000\u0000\u02e5\u02e3\u0001\u0000"+
		"\u0000\u0000\u02e6\u02e7\u0005,\u0000\u0000\u02e7\u02ec\u0003\u0092I\u0000"+
		"\u02e8\u02e9\u0005\b\u0000\u0000\u02e9\u02eb\u0003\u0092I\u0000\u02ea"+
		"\u02e8\u0001\u0000\u0000\u0000\u02eb\u02ee\u0001\u0000\u0000\u0000\u02ec"+
		"\u02ea\u0001\u0000\u0000\u0000\u02ec\u02ed\u0001\u0000\u0000\u0000\u02ed"+
		"\u02ef\u0001\u0000\u0000\u0000\u02ee\u02ec\u0001\u0000\u0000\u0000\u02ef"+
		"\u02f0\u0005\u0005\u0000\u0000\u02f0\u0091\u0001\u0000\u0000\u0000\u02f1"+
		"\u0302\u00054\u0000\u0000\u02f2\u02f3\u0003,\u0016\u0000\u02f3\u02f4\u0005"+
		"4\u0000\u0000\u02f4\u0302\u0001\u0000\u0000\u0000\u02f5\u02f6\u0003\""+
		"\u0011\u0000\u02f6\u02f7\u00054\u0000\u0000\u02f7\u0302\u0001\u0000\u0000"+
		"\u0000\u02f8\u02fa\u0005\u0013\u0000\u0000\u02f9\u02fb\u0003,\u0016\u0000"+
		"\u02fa\u02f9\u0001\u0000\u0000\u0000\u02fa\u02fb\u0001\u0000\u0000\u0000"+
		"\u02fb\u0302\u0001\u0000\u0000\u0000\u02fc\u02fe\u0005\u0014\u0000\u0000"+
		"\u02fd\u02ff\u0003\"\u0011\u0000\u02fe\u02fd\u0001\u0000\u0000\u0000\u02fe"+
		"\u02ff\u0001\u0000\u0000\u0000\u02ff\u0302\u0001\u0000\u0000\u0000\u0300"+
		"\u0302\u0005\u000f\u0000\u0000\u0301\u02f1\u0001\u0000\u0000\u0000\u0301"+
		"\u02f2\u0001\u0000\u0000\u0000\u0301\u02f5\u0001\u0000\u0000\u0000\u0301"+
		"\u02f8\u0001\u0000\u0000\u0000\u0301\u02fc\u0001\u0000\u0000\u0000\u0301"+
		"\u0300\u0001\u0000\u0000\u0000\u0302\u0093\u0001\u0000\u0000\u0000\u0303"+
		"\u0304\u0007\u0005\u0000\u0000\u0304\u0095\u0001\u0000\u0000\u0000N\u0099"+
		"\u00a8\u00af\u00be\u00c2\u00ca\u00d2\u00da\u00e0\u00e7\u00ed\u00f6\u00fe"+
		"\u0101\u010f\u0113\u011a\u0128\u0131\u013c\u0149\u0154\u0159\u015c\u0161"+
		"\u0164\u0166\u016c\u0174\u017c\u018c\u0195\u01a1\u01a7\u01ab\u01b0\u01bb"+
		"\u01c0\u01c5\u01cf\u01dc\u01e9\u01f5\u01fc\u0205\u0210\u0216\u0223\u022a"+
		"\u0231\u023c\u0247\u0250\u025d\u0260\u0265\u0269\u0270\u0274\u027c\u0280"+
		"\u0288\u028c\u0295\u029b\u02a4\u02a9\u02b0\u02b4\u02ba\u02c7\u02d0\u02d7"+
		"\u02e3\u02ec\u02fa\u02fe\u0301";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}