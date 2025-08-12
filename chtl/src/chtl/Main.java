package chtl;

import java.nio.file.Path;

import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.ConsoleErrorListener;
import org.antlr.v4.runtime.DiagnosticErrorListener;
import org.antlr.v4.runtime.tree.ParseTree;

import chtl.parser.CHTLLexer;
import chtl.parser.CHTLParser;

public class Main {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.err.println("Usage: java chtl.Main <file.chtl>");
            System.exit(1);
        }

        CharStream input = CharStreams.fromPath(Path.of(args[0]));
        CHTLLexer lexer = new CHTLLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        CHTLParser parser = new CHTLParser(tokens);

        parser.removeErrorListeners();
        parser.addErrorListener(new ConsoleErrorListener());
        parser.addErrorListener(new DiagnosticErrorListener());

        ParseTree tree = parser.program();
        System.out.println(tree.toStringTree(parser));

        if (args.length >= 2 && "--scan".equals(args[1])) {
            var spans = chtl.scanner.Scanner.scan(tokens);
            for (var s : spans) {
                System.out.println(s);
            }
        }
    }
}