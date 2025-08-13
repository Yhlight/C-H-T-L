// Generated from Scanner.g4 by ANTLR 4.13.1
package scanner;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link ScannerParser}.
 */
public interface ScannerListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link ScannerParser#document}.
	 * @param ctx the parse tree
	 */
	void enterDocument(ScannerParser.DocumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#document}.
	 * @param ctx the parse tree
	 */
	void exitDocument(ScannerParser.DocumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#codeBlock}.
	 * @param ctx the parse tree
	 */
	void enterCodeBlock(ScannerParser.CodeBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#codeBlock}.
	 * @param ctx the parse tree
	 */
	void exitCodeBlock(ScannerParser.CodeBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#chtlBlock}.
	 * @param ctx the parse tree
	 */
	void enterChtlBlock(ScannerParser.ChtlBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#chtlBlock}.
	 * @param ctx the parse tree
	 */
	void exitChtlBlock(ScannerParser.ChtlBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#chtlElement}.
	 * @param ctx the parse tree
	 */
	void enterChtlElement(ScannerParser.ChtlElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#chtlElement}.
	 * @param ctx the parse tree
	 */
	void exitChtlElement(ScannerParser.ChtlElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#elementStart}.
	 * @param ctx the parse tree
	 */
	void enterElementStart(ScannerParser.ElementStartContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#elementStart}.
	 * @param ctx the parse tree
	 */
	void exitElementStart(ScannerParser.ElementStartContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#elementEnd}.
	 * @param ctx the parse tree
	 */
	void enterElementEnd(ScannerParser.ElementEndContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#elementEnd}.
	 * @param ctx the parse tree
	 */
	void exitElementEnd(ScannerParser.ElementEndContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#elementContent}.
	 * @param ctx the parse tree
	 */
	void enterElementContent(ScannerParser.ElementContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#elementContent}.
	 * @param ctx the parse tree
	 */
	void exitElementContent(ScannerParser.ElementContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#chtlAttribute}.
	 * @param ctx the parse tree
	 */
	void enterChtlAttribute(ScannerParser.ChtlAttributeContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#chtlAttribute}.
	 * @param ctx the parse tree
	 */
	void exitChtlAttribute(ScannerParser.ChtlAttributeContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#chtlDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterChtlDeclaration(ScannerParser.ChtlDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#chtlDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitChtlDeclaration(ScannerParser.ChtlDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#chtlStatement}.
	 * @param ctx the parse tree
	 */
	void enterChtlStatement(ScannerParser.ChtlStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#chtlStatement}.
	 * @param ctx the parse tree
	 */
	void exitChtlStatement(ScannerParser.ChtlStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#textBlock}.
	 * @param ctx the parse tree
	 */
	void enterTextBlock(ScannerParser.TextBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#textBlock}.
	 * @param ctx the parse tree
	 */
	void exitTextBlock(ScannerParser.TextBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link ScannerParser#textContent}.
	 * @param ctx the parse tree
	 */
	void enterTextContent(ScannerParser.TextContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link ScannerParser#textContent}.
	 * @param ctx the parse tree
	 */
	void exitTextContent(ScannerParser.TextContentContext ctx);
}