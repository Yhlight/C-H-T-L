package com.chtl;

import com.chtl.parser.*;
import com.chtl.ast.*;
import com.chtl.analyzer.*;
import com.chtl.generator.*;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.*;
import java.nio.file.*;
import java.util.List;

/**
 * Main CHTL compiler class
 */
public class ChtlCompiler {
    
    private boolean debug = false;
    
    public ChtlCompiler() {
    }
    
    public ChtlCompiler(boolean debug) {
        this.debug = debug;
    }
    
    /**
     * Compile a CHTL file to HTML
     */
    public CompilationResult compile(String inputFile) throws IOException {
        String content = Files.readString(Paths.get(inputFile));
        return compileString(content, inputFile);
    }
    
    /**
     * Compile CHTL content string to HTML
     */
    public CompilationResult compileString(String content, String filename) {
        CompilationResult result = new CompilationResult();
        
        try {
            // Create lexer and parser
            ANTLRInputStream input = new ANTLRInputStream(content);
            ChtlLexer lexer = new ChtlLexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            ChtlParser parser = new ChtlParser(tokens);
            
            // Parse
            ParseTree tree = parser.chtlFile();
            
            // Check for syntax errors
            if (parser.getNumberOfSyntaxErrors() > 0) {
                result.addError("Syntax errors found in " + filename);
                return result;
            }
            
            // Build AST
            ChtlAstBuilder astBuilder = new ChtlAstBuilder(filename);
            ChtlNode ast = astBuilder.visit(tree);
            
            if (!(ast instanceof ChtlFileNode)) {
                result.addError("Failed to build AST");
                return result;
            }
            
            ChtlFileNode fileNode = (ChtlFileNode) ast;
            
            // Semantic analysis
            SemanticAnalyzer analyzer = new SemanticAnalyzer();
            List<SemanticError> semanticErrors = analyzer.analyze(fileNode);
            
            // Add semantic errors to result
            for (SemanticError error : semanticErrors) {
                if (error.getSeverity() == SemanticError.Severity.ERROR) {
                    result.addError(error.toString());
                } else {
                    result.addWarning(error.toString());
                }
            }
            
            // Stop if there are errors
            if (result.hasErrors()) {
                return result;
            }
            
            // Generate HTML
            HtmlGenerator generator = new HtmlGenerator();
            GeneratedCode generatedCode = generator.generate(fileNode);
            
            result.setGeneratedCode(generatedCode);
            result.setSuccess(true);
            
            if (debug) {
                System.out.println("Compilation successful!");
                System.out.println("Generated HTML:");
                System.out.println(generatedCode.getCompleteHtml());
            }
            
        } catch (Exception e) {
            result.addError("Compilation failed: " + e.getMessage());
            if (debug) {
                e.printStackTrace();
            }
        }
        
        return result;
    }
    
    /**
     * Main method for command-line usage
     */
    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java ChtlCompiler <input.chtl> [output.html]");
            System.exit(1);
        }
        
        String inputFile = args[0];
        String outputFile = args.length > 1 ? args[1] : 
            inputFile.replaceAll("\\.chtl$", ".html");
        
        try {
            ChtlCompiler compiler = new ChtlCompiler(true);
            CompilationResult result = compiler.compile(inputFile);
            
            if (result.isSuccess()) {
                // Write output file
                Files.writeString(Paths.get(outputFile), 
                    result.getGeneratedCode().getCompleteHtml());
                System.out.println("Output written to: " + outputFile);
            } else {
                System.err.println("Compilation failed:");
                for (String error : result.getErrors()) {
                    System.err.println("  " + error);
                }
                System.exit(1);
            }
            
            // Print warnings
            if (!result.getWarnings().isEmpty()) {
                System.out.println("Warnings:");
                for (String warning : result.getWarnings()) {
                    System.out.println("  " + warning);
                }
            }
            
        } catch (IOException e) {
            System.err.println("Error reading/writing files: " + e.getMessage());
            System.exit(1);
        }
    }
}