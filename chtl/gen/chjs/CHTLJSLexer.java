// Generated from /workspace/chtl/grammar/chjs/CHTLJS.g4 by ANTLR 4.13.1
package chtl.chjs.parser;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class CHTLJSLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		LBRACE2=1, RBRACE2=2, ARROW=3, DOT=4, HASH=5, LBRACK=6, RBRACK=7, LPAREN=8, 
		RPAREN=9, COMMA=10, SEMI=11, COLON=12, NUMBER=13, IDENT=14, LISTEN=15, 
		DELEGATE=16, ANIMATE=17, ARGCHUNK=18, OTHER=19, WS=20;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"LBRACE2", "RBRACE2", "ARROW", "DOT", "HASH", "LBRACK", "RBRACK", "LPAREN", 
			"RPAREN", "COMMA", "SEMI", "COLON", "NUMBER", "IDENT", "LISTEN", "DELEGATE", 
			"ANIMATE", "ARGCHUNK", "OTHER", "WS"
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


	public CHTLJSLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "CHTLJS.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u0014v\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002\u0001"+
		"\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004"+
		"\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007"+
		"\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b"+
		"\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002"+
		"\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002"+
		"\u0012\u0007\u0012\u0002\u0013\u0007\u0013\u0001\u0000\u0001\u0000\u0001"+
		"\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0002\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001\u0005\u0001"+
		"\u0005\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001\b\u0001\b"+
		"\u0001\t\u0001\t\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\f\u0004"+
		"\fF\b\f\u000b\f\f\fG\u0001\r\u0001\r\u0005\rL\b\r\n\r\f\rO\t\r\u0001\u000e"+
		"\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f"+
		"\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u0010\u0001\u0010\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011"+
		"\u0004\u0011j\b\u0011\u000b\u0011\f\u0011k\u0001\u0012\u0001\u0012\u0001"+
		"\u0013\u0004\u0013q\b\u0013\u000b\u0013\f\u0013r\u0001\u0013\u0001\u0013"+
		"\u0000\u0000\u0014\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004\t\u0005"+
		"\u000b\u0006\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017\f\u0019"+
		"\r\u001b\u000e\u001d\u000f\u001f\u0010!\u0011#\u0012%\u0013\'\u0014\u0001"+
		"\u0000\u0005\u0001\u000009\u0003\u0000AZ__az\u0005\u0000--09AZ__az\u0001"+
		"\u0000()\u0003\u0000\t\n\r\r  y\u0000\u0001\u0001\u0000\u0000\u0000\u0000"+
		"\u0003\u0001\u0000\u0000\u0000\u0000\u0005\u0001\u0000\u0000\u0000\u0000"+
		"\u0007\u0001\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000\u000b"+
		"\u0001\u0000\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f\u0001"+
		"\u0000\u0000\u0000\u0000\u0011\u0001\u0000\u0000\u0000\u0000\u0013\u0001"+
		"\u0000\u0000\u0000\u0000\u0015\u0001\u0000\u0000\u0000\u0000\u0017\u0001"+
		"\u0000\u0000\u0000\u0000\u0019\u0001\u0000\u0000\u0000\u0000\u001b\u0001"+
		"\u0000\u0000\u0000\u0000\u001d\u0001\u0000\u0000\u0000\u0000\u001f\u0001"+
		"\u0000\u0000\u0000\u0000!\u0001\u0000\u0000\u0000\u0000#\u0001\u0000\u0000"+
		"\u0000\u0000%\u0001\u0000\u0000\u0000\u0000\'\u0001\u0000\u0000\u0000"+
		"\u0001)\u0001\u0000\u0000\u0000\u0003,\u0001\u0000\u0000\u0000\u0005/"+
		"\u0001\u0000\u0000\u0000\u00072\u0001\u0000\u0000\u0000\t4\u0001\u0000"+
		"\u0000\u0000\u000b6\u0001\u0000\u0000\u0000\r8\u0001\u0000\u0000\u0000"+
		"\u000f:\u0001\u0000\u0000\u0000\u0011<\u0001\u0000\u0000\u0000\u0013>"+
		"\u0001\u0000\u0000\u0000\u0015@\u0001\u0000\u0000\u0000\u0017B\u0001\u0000"+
		"\u0000\u0000\u0019E\u0001\u0000\u0000\u0000\u001bI\u0001\u0000\u0000\u0000"+
		"\u001dP\u0001\u0000\u0000\u0000\u001fW\u0001\u0000\u0000\u0000!`\u0001"+
		"\u0000\u0000\u0000#i\u0001\u0000\u0000\u0000%m\u0001\u0000\u0000\u0000"+
		"\'p\u0001\u0000\u0000\u0000)*\u0005{\u0000\u0000*+\u0005{\u0000\u0000"+
		"+\u0002\u0001\u0000\u0000\u0000,-\u0005}\u0000\u0000-.\u0005}\u0000\u0000"+
		".\u0004\u0001\u0000\u0000\u0000/0\u0005-\u0000\u000001\u0005>\u0000\u0000"+
		"1\u0006\u0001\u0000\u0000\u000023\u0005.\u0000\u00003\b\u0001\u0000\u0000"+
		"\u000045\u0005#\u0000\u00005\n\u0001\u0000\u0000\u000067\u0005[\u0000"+
		"\u00007\f\u0001\u0000\u0000\u000089\u0005]\u0000\u00009\u000e\u0001\u0000"+
		"\u0000\u0000:;\u0005(\u0000\u0000;\u0010\u0001\u0000\u0000\u0000<=\u0005"+
		")\u0000\u0000=\u0012\u0001\u0000\u0000\u0000>?\u0005,\u0000\u0000?\u0014"+
		"\u0001\u0000\u0000\u0000@A\u0005;\u0000\u0000A\u0016\u0001\u0000\u0000"+
		"\u0000BC\u0005:\u0000\u0000C\u0018\u0001\u0000\u0000\u0000DF\u0007\u0000"+
		"\u0000\u0000ED\u0001\u0000\u0000\u0000FG\u0001\u0000\u0000\u0000GE\u0001"+
		"\u0000\u0000\u0000GH\u0001\u0000\u0000\u0000H\u001a\u0001\u0000\u0000"+
		"\u0000IM\u0007\u0001\u0000\u0000JL\u0007\u0002\u0000\u0000KJ\u0001\u0000"+
		"\u0000\u0000LO\u0001\u0000\u0000\u0000MK\u0001\u0000\u0000\u0000MN\u0001"+
		"\u0000\u0000\u0000N\u001c\u0001\u0000\u0000\u0000OM\u0001\u0000\u0000"+
		"\u0000PQ\u0005l\u0000\u0000QR\u0005i\u0000\u0000RS\u0005s\u0000\u0000"+
		"ST\u0005t\u0000\u0000TU\u0005e\u0000\u0000UV\u0005n\u0000\u0000V\u001e"+
		"\u0001\u0000\u0000\u0000WX\u0005d\u0000\u0000XY\u0005e\u0000\u0000YZ\u0005"+
		"l\u0000\u0000Z[\u0005e\u0000\u0000[\\\u0005g\u0000\u0000\\]\u0005a\u0000"+
		"\u0000]^\u0005t\u0000\u0000^_\u0005e\u0000\u0000_ \u0001\u0000\u0000\u0000"+
		"`a\u0005a\u0000\u0000ab\u0005n\u0000\u0000bc\u0005i\u0000\u0000cd\u0005"+
		"m\u0000\u0000de\u0005a\u0000\u0000ef\u0005t\u0000\u0000fg\u0005e\u0000"+
		"\u0000g\"\u0001\u0000\u0000\u0000hj\b\u0003\u0000\u0000ih\u0001\u0000"+
		"\u0000\u0000jk\u0001\u0000\u0000\u0000ki\u0001\u0000\u0000\u0000kl\u0001"+
		"\u0000\u0000\u0000l$\u0001\u0000\u0000\u0000mn\t\u0000\u0000\u0000n&\u0001"+
		"\u0000\u0000\u0000oq\u0007\u0004\u0000\u0000po\u0001\u0000\u0000\u0000"+
		"qr\u0001\u0000\u0000\u0000rp\u0001\u0000\u0000\u0000rs\u0001\u0000\u0000"+
		"\u0000st\u0001\u0000\u0000\u0000tu\u0006\u0013\u0000\u0000u(\u0001\u0000"+
		"\u0000\u0000\u0005\u0000GMkr\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}