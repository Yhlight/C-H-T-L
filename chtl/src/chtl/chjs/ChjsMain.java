package chtl.chjs;

import java.nio.file.Path;

import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import chtl.chjs.parser.CHTLJSLexer;
import chtl.chjs.parser.CHTLJSParser;

public class ChjsMain {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.err.println("Usage: java chtl.chjs.ChjsMain <file>");
            System.exit(1);
        }
        CharStream input = CharStreams.fromPath(Path.of(args[0]));
        CHTLJSLexer lexer = new CHTLJSLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        CHTLJSParser parser = new CHTLJSParser(tokens);
        ParseTree tree = parser.program();
        System.out.println(tree.toStringTree(parser));
    }
}