package chtl.css;

import java.nio.file.Path;

import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import chtl.css.parser.CSS3Lexer;
import chtl.css.parser.CSS3Parser;

public class CssMain {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.err.println("Usage: java chtl.css.CssMain <file.css>");
            System.exit(1);
        }
        CharStream input = CharStreams.fromPath(Path.of(args[0]));
        CSS3Lexer lexer = new CSS3Lexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        CSS3Parser parser = new CSS3Parser(tokens);
        ParseTree tree = parser.stylesheet();
        System.out.println(tree.toStringTree(parser));
    }
}