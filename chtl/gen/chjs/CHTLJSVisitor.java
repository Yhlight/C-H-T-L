// Generated from /workspace/chtl/grammar/chjs/CHTLJS.g4 by ANTLR 4.13.1
package chtl.chjs.parser;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link CHTLJSParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface CHTLJSVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link CHTLJSParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(CHTLJSParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLJSParser#piece}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPiece(CHTLJSParser.PieceContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLJSParser#moustache}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMoustache(CHTLJSParser.MoustacheContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLJSParser#arrowUse}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArrowUse(CHTLJSParser.ArrowUseContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLJSParser#keywordUse}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitKeywordUse(CHTLJSParser.KeywordUseContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLJSParser#selector}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSelector(CHTLJSParser.SelectorContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLJSParser#simpleSelector}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSimpleSelector(CHTLJSParser.SimpleSelectorContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLJSParser#argChunk}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgChunk(CHTLJSParser.ArgChunkContext ctx);
}