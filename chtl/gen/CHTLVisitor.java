// Generated from /workspace/chtl/grammar/CHTL.g4 by ANTLR 4.13.1
package chtl.parser;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link CHTLParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface CHTLVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link CHTLParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(CHTLParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(CHTLParser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#elementNode}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitElementNode(CHTLParser.ElementNodeContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#elementName}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitElementName(CHTLParser.ElementNameContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#block}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlock(CHTLParser.BlockContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#blockItem}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlockItem(CHTLParser.BlockItemContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#textBlock}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTextBlock(CHTLParser.TextBlockContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#blockText}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlockText(CHTLParser.BlockTextContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#textLine}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTextLine(CHTLParser.TextLineContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#textPiece}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTextPiece(CHTLParser.TextPieceContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#styleBlock}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStyleBlock(CHTLParser.StyleBlockContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#blockStyle}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlockStyle(CHTLParser.BlockStyleContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#styleItem}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStyleItem(CHTLParser.StyleItemContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#scriptBlock}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitScriptBlock(CHTLParser.ScriptBlockContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#blockScript}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlockScript(CHTLParser.BlockScriptContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#scriptLine}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitScriptLine(CHTLParser.ScriptLineContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#scriptPiece}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitScriptPiece(CHTLParser.ScriptPieceContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#attribute}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAttribute(CHTLParser.AttributeContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#value}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitValue(CHTLParser.ValueContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#valuePiece}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitValuePiece(CHTLParser.ValuePieceContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#templateUsage}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTemplateUsage(CHTLParser.TemplateUsageContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#templateDecl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTemplateDecl(CHTLParser.TemplateDeclContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#customDecl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCustomDecl(CHTLParser.CustomDeclContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#originDecl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOriginDecl(CHTLParser.OriginDeclContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#configurationDecl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConfigurationDecl(CHTLParser.ConfigurationDeclContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#importStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitImportStmt(CHTLParser.ImportStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#importTarget}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitImportTarget(CHTLParser.ImportTargetContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#importPath}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitImportPath(CHTLParser.ImportPathContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#namespaceDecl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespaceDecl(CHTLParser.NamespaceDeclContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#inheritStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInheritStmt(CHTLParser.InheritStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#deleteStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDeleteStmt(CHTLParser.DeleteStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#identList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentList(CHTLParser.IdentListContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#insertStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInsertStmt(CHTLParser.InsertStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#selector}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSelector(CHTLParser.SelectorContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#exceptStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExceptStmt(CHTLParser.ExceptStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#exceptTargetList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExceptTargetList(CHTLParser.ExceptTargetListContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#exceptTarget}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExceptTarget(CHTLParser.ExceptTargetContext ctx);
	/**
	 * Visit a parse tree produced by {@link CHTLParser#atType}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAtType(CHTLParser.AtTypeContext ctx);
}