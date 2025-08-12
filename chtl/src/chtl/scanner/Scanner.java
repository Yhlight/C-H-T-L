package chtl.scanner;

import java.util.ArrayList;
import java.util.List;

import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.Token;

import chtl.parser.CHTLParser;
import chtl.parser.CHTLLexer;

public class Scanner {
    public static List<BlockSpan> scan(CommonTokenStream tokens) {
        List<BlockSpan> spans = new ArrayList<>();
        List<? extends Token> all = tokens.getTokens();
        int i = 0;
        while (i < all.size()) {
            Token t = all.get(i);
            if (t.getType() == CHTLLexer.KEYWORD_STYLE) {
                int start = t.getStartIndex();
                int end = findMatchingBlockEnd(all, i);
                spans.add(new BlockSpan(BlockType.STYLE, start, end));
                i = skipToTokenIndex(all, end);
                continue;
            }
            if (t.getType() == CHTLLexer.KEYWORD_SCRIPT_KW) {
                int start = t.getStartIndex();
                int end = findMatchingBlockEnd(all, i);
                String text = t.getInputStream().getText(new org.antlr.v4.runtime.misc.Interval(start, end));
                BlockType type = classifyScript(text);
                spans.add(new BlockSpan(type, start, end));
                i = skipToTokenIndex(all, end);
                continue;
            }
            i++;
        }
        return spans;
    }

    private static BlockType classifyScript(String blockText) {
        if (blockText.contains("{{") || blockText.contains("->") ||
            blockText.contains("listen(") || blockText.contains("delegate(") || blockText.contains("animate(")) {
            return BlockType.SCRIPT_CHTLJS;
        }
        return BlockType.SCRIPT_JS;
    }

    private static int findMatchingBlockEnd(List<? extends Token> tokens, int keywordIndex) {
        int i = keywordIndex + 1;
        // find first LBRACE
        while (i < tokens.size() && tokens.get(i).getType() != CHTLLexer.LBRACE) i++;
        int balance = 0;
        int start = i;
        for (; i < tokens.size(); i++) {
            Token t = tokens.get(i);
            if (t.getType() == CHTLLexer.LBRACE) balance++;
            else if (t.getType() == CHTLLexer.RBRACE) {
                balance--;
                if (balance == 0) {
                    return t.getStopIndex();
                }
            }
        }
        return tokens.get(tokens.size() - 1).getStopIndex();
    }

    private static int skipToTokenIndex(List<? extends Token> tokens, int charIndex) {
        for (int i = 0; i < tokens.size(); i++) {
            Token t = tokens.get(i);
            if (t.getStartIndex() >= charIndex) return i + 1;
        }
        return tokens.size();
    }
}