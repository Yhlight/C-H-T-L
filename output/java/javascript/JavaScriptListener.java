// Generated from JavaScript.g4 by ANTLR 4.13.1
package javascript;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link JavaScriptParser}.
 */
public interface JavaScriptListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(JavaScriptParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(JavaScriptParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#sourceElements}.
	 * @param ctx the parse tree
	 */
	void enterSourceElements(JavaScriptParser.SourceElementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#sourceElements}.
	 * @param ctx the parse tree
	 */
	void exitSourceElements(JavaScriptParser.SourceElementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#sourceElement}.
	 * @param ctx the parse tree
	 */
	void enterSourceElement(JavaScriptParser.SourceElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#sourceElement}.
	 * @param ctx the parse tree
	 */
	void exitSourceElement(JavaScriptParser.SourceElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(JavaScriptParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(JavaScriptParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#hoistableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterHoistableDeclaration(JavaScriptParser.HoistableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#hoistableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitHoistableDeclaration(JavaScriptParser.HoistableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDeclaration(JavaScriptParser.FunctionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDeclaration(JavaScriptParser.FunctionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#generatorDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterGeneratorDeclaration(JavaScriptParser.GeneratorDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#generatorDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitGeneratorDeclaration(JavaScriptParser.GeneratorDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#asyncFunctionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterAsyncFunctionDeclaration(JavaScriptParser.AsyncFunctionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#asyncFunctionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitAsyncFunctionDeclaration(JavaScriptParser.AsyncFunctionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#asyncGeneratorDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterAsyncGeneratorDeclaration(JavaScriptParser.AsyncGeneratorDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#asyncGeneratorDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitAsyncGeneratorDeclaration(JavaScriptParser.AsyncGeneratorDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#classDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterClassDeclaration(JavaScriptParser.ClassDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#classDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitClassDeclaration(JavaScriptParser.ClassDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#classExtends}.
	 * @param ctx the parse tree
	 */
	void enterClassExtends(JavaScriptParser.ClassExtendsContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#classExtends}.
	 * @param ctx the parse tree
	 */
	void exitClassExtends(JavaScriptParser.ClassExtendsContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#classBody}.
	 * @param ctx the parse tree
	 */
	void enterClassBody(JavaScriptParser.ClassBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#classBody}.
	 * @param ctx the parse tree
	 */
	void exitClassBody(JavaScriptParser.ClassBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#classElement}.
	 * @param ctx the parse tree
	 */
	void enterClassElement(JavaScriptParser.ClassElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#classElement}.
	 * @param ctx the parse tree
	 */
	void exitClassElement(JavaScriptParser.ClassElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#methodDefinition}.
	 * @param ctx the parse tree
	 */
	void enterMethodDefinition(JavaScriptParser.MethodDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#methodDefinition}.
	 * @param ctx the parse tree
	 */
	void exitMethodDefinition(JavaScriptParser.MethodDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#fieldDefinition}.
	 * @param ctx the parse tree
	 */
	void enterFieldDefinition(JavaScriptParser.FieldDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#fieldDefinition}.
	 * @param ctx the parse tree
	 */
	void exitFieldDefinition(JavaScriptParser.FieldDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#lexicalDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterLexicalDeclaration(JavaScriptParser.LexicalDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#lexicalDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitLexicalDeclaration(JavaScriptParser.LexicalDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#letOrConst}.
	 * @param ctx the parse tree
	 */
	void enterLetOrConst(JavaScriptParser.LetOrConstContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#letOrConst}.
	 * @param ctx the parse tree
	 */
	void exitLetOrConst(JavaScriptParser.LetOrConstContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bindingList}.
	 * @param ctx the parse tree
	 */
	void enterBindingList(JavaScriptParser.BindingListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bindingList}.
	 * @param ctx the parse tree
	 */
	void exitBindingList(JavaScriptParser.BindingListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#lexicalBinding}.
	 * @param ctx the parse tree
	 */
	void enterLexicalBinding(JavaScriptParser.LexicalBindingContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#lexicalBinding}.
	 * @param ctx the parse tree
	 */
	void exitLexicalBinding(JavaScriptParser.LexicalBindingContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(JavaScriptParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(JavaScriptParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#blockStatement}.
	 * @param ctx the parse tree
	 */
	void enterBlockStatement(JavaScriptParser.BlockStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#blockStatement}.
	 * @param ctx the parse tree
	 */
	void exitBlockStatement(JavaScriptParser.BlockStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#statementList}.
	 * @param ctx the parse tree
	 */
	void enterStatementList(JavaScriptParser.StatementListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#statementList}.
	 * @param ctx the parse tree
	 */
	void exitStatementList(JavaScriptParser.StatementListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#variableStatement}.
	 * @param ctx the parse tree
	 */
	void enterVariableStatement(JavaScriptParser.VariableStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#variableStatement}.
	 * @param ctx the parse tree
	 */
	void exitVariableStatement(JavaScriptParser.VariableStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#variableDeclarationList}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclarationList(JavaScriptParser.VariableDeclarationListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#variableDeclarationList}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclarationList(JavaScriptParser.VariableDeclarationListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclaration(JavaScriptParser.VariableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclaration(JavaScriptParser.VariableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void enterEmptyStatement(JavaScriptParser.EmptyStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void exitEmptyStatement(JavaScriptParser.EmptyStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void enterExpressionStatement(JavaScriptParser.ExpressionStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void exitExpressionStatement(JavaScriptParser.ExpressionStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(JavaScriptParser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(JavaScriptParser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#iterationStatement}.
	 * @param ctx the parse tree
	 */
	void enterIterationStatement(JavaScriptParser.IterationStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#iterationStatement}.
	 * @param ctx the parse tree
	 */
	void exitIterationStatement(JavaScriptParser.IterationStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#doWhileStatement}.
	 * @param ctx the parse tree
	 */
	void enterDoWhileStatement(JavaScriptParser.DoWhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#doWhileStatement}.
	 * @param ctx the parse tree
	 */
	void exitDoWhileStatement(JavaScriptParser.DoWhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(JavaScriptParser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(JavaScriptParser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void enterForStatement(JavaScriptParser.ForStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void exitForStatement(JavaScriptParser.ForStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#forInit}.
	 * @param ctx the parse tree
	 */
	void enterForInit(JavaScriptParser.ForInitContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#forInit}.
	 * @param ctx the parse tree
	 */
	void exitForInit(JavaScriptParser.ForInitContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#forInStatement}.
	 * @param ctx the parse tree
	 */
	void enterForInStatement(JavaScriptParser.ForInStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#forInStatement}.
	 * @param ctx the parse tree
	 */
	void exitForInStatement(JavaScriptParser.ForInStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#forOfStatement}.
	 * @param ctx the parse tree
	 */
	void enterForOfStatement(JavaScriptParser.ForOfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#forOfStatement}.
	 * @param ctx the parse tree
	 */
	void exitForOfStatement(JavaScriptParser.ForOfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#forInBinding}.
	 * @param ctx the parse tree
	 */
	void enterForInBinding(JavaScriptParser.ForInBindingContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#forInBinding}.
	 * @param ctx the parse tree
	 */
	void exitForInBinding(JavaScriptParser.ForInBindingContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#continueStatement}.
	 * @param ctx the parse tree
	 */
	void enterContinueStatement(JavaScriptParser.ContinueStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#continueStatement}.
	 * @param ctx the parse tree
	 */
	void exitContinueStatement(JavaScriptParser.ContinueStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#breakStatement}.
	 * @param ctx the parse tree
	 */
	void enterBreakStatement(JavaScriptParser.BreakStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#breakStatement}.
	 * @param ctx the parse tree
	 */
	void exitBreakStatement(JavaScriptParser.BreakStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void enterReturnStatement(JavaScriptParser.ReturnStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void exitReturnStatement(JavaScriptParser.ReturnStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#withStatement}.
	 * @param ctx the parse tree
	 */
	void enterWithStatement(JavaScriptParser.WithStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#withStatement}.
	 * @param ctx the parse tree
	 */
	void exitWithStatement(JavaScriptParser.WithStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#labelledStatement}.
	 * @param ctx the parse tree
	 */
	void enterLabelledStatement(JavaScriptParser.LabelledStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#labelledStatement}.
	 * @param ctx the parse tree
	 */
	void exitLabelledStatement(JavaScriptParser.LabelledStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#switchStatement}.
	 * @param ctx the parse tree
	 */
	void enterSwitchStatement(JavaScriptParser.SwitchStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#switchStatement}.
	 * @param ctx the parse tree
	 */
	void exitSwitchStatement(JavaScriptParser.SwitchStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#caseClause}.
	 * @param ctx the parse tree
	 */
	void enterCaseClause(JavaScriptParser.CaseClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#caseClause}.
	 * @param ctx the parse tree
	 */
	void exitCaseClause(JavaScriptParser.CaseClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#defaultClause}.
	 * @param ctx the parse tree
	 */
	void enterDefaultClause(JavaScriptParser.DefaultClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#defaultClause}.
	 * @param ctx the parse tree
	 */
	void exitDefaultClause(JavaScriptParser.DefaultClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#throwStatement}.
	 * @param ctx the parse tree
	 */
	void enterThrowStatement(JavaScriptParser.ThrowStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#throwStatement}.
	 * @param ctx the parse tree
	 */
	void exitThrowStatement(JavaScriptParser.ThrowStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#tryStatement}.
	 * @param ctx the parse tree
	 */
	void enterTryStatement(JavaScriptParser.TryStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#tryStatement}.
	 * @param ctx the parse tree
	 */
	void exitTryStatement(JavaScriptParser.TryStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#catchClause}.
	 * @param ctx the parse tree
	 */
	void enterCatchClause(JavaScriptParser.CatchClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#catchClause}.
	 * @param ctx the parse tree
	 */
	void exitCatchClause(JavaScriptParser.CatchClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#catchParameter}.
	 * @param ctx the parse tree
	 */
	void enterCatchParameter(JavaScriptParser.CatchParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#catchParameter}.
	 * @param ctx the parse tree
	 */
	void exitCatchParameter(JavaScriptParser.CatchParameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#finallyClause}.
	 * @param ctx the parse tree
	 */
	void enterFinallyClause(JavaScriptParser.FinallyClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#finallyClause}.
	 * @param ctx the parse tree
	 */
	void exitFinallyClause(JavaScriptParser.FinallyClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#debuggerStatement}.
	 * @param ctx the parse tree
	 */
	void enterDebuggerStatement(JavaScriptParser.DebuggerStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#debuggerStatement}.
	 * @param ctx the parse tree
	 */
	void exitDebuggerStatement(JavaScriptParser.DebuggerStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#importStatement}.
	 * @param ctx the parse tree
	 */
	void enterImportStatement(JavaScriptParser.ImportStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#importStatement}.
	 * @param ctx the parse tree
	 */
	void exitImportStatement(JavaScriptParser.ImportStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#importClause}.
	 * @param ctx the parse tree
	 */
	void enterImportClause(JavaScriptParser.ImportClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#importClause}.
	 * @param ctx the parse tree
	 */
	void exitImportClause(JavaScriptParser.ImportClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#importedDefaultBinding}.
	 * @param ctx the parse tree
	 */
	void enterImportedDefaultBinding(JavaScriptParser.ImportedDefaultBindingContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#importedDefaultBinding}.
	 * @param ctx the parse tree
	 */
	void exitImportedDefaultBinding(JavaScriptParser.ImportedDefaultBindingContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#namespaceImport}.
	 * @param ctx the parse tree
	 */
	void enterNamespaceImport(JavaScriptParser.NamespaceImportContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#namespaceImport}.
	 * @param ctx the parse tree
	 */
	void exitNamespaceImport(JavaScriptParser.NamespaceImportContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#namedImports}.
	 * @param ctx the parse tree
	 */
	void enterNamedImports(JavaScriptParser.NamedImportsContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#namedImports}.
	 * @param ctx the parse tree
	 */
	void exitNamedImports(JavaScriptParser.NamedImportsContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#importsList}.
	 * @param ctx the parse tree
	 */
	void enterImportsList(JavaScriptParser.ImportsListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#importsList}.
	 * @param ctx the parse tree
	 */
	void exitImportsList(JavaScriptParser.ImportsListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#importSpecifier}.
	 * @param ctx the parse tree
	 */
	void enterImportSpecifier(JavaScriptParser.ImportSpecifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#importSpecifier}.
	 * @param ctx the parse tree
	 */
	void exitImportSpecifier(JavaScriptParser.ImportSpecifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#moduleSpecifier}.
	 * @param ctx the parse tree
	 */
	void enterModuleSpecifier(JavaScriptParser.ModuleSpecifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#moduleSpecifier}.
	 * @param ctx the parse tree
	 */
	void exitModuleSpecifier(JavaScriptParser.ModuleSpecifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#exportStatement}.
	 * @param ctx the parse tree
	 */
	void enterExportStatement(JavaScriptParser.ExportStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#exportStatement}.
	 * @param ctx the parse tree
	 */
	void exitExportStatement(JavaScriptParser.ExportStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#exportClause}.
	 * @param ctx the parse tree
	 */
	void enterExportClause(JavaScriptParser.ExportClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#exportClause}.
	 * @param ctx the parse tree
	 */
	void exitExportClause(JavaScriptParser.ExportClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#exportsList}.
	 * @param ctx the parse tree
	 */
	void enterExportsList(JavaScriptParser.ExportsListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#exportsList}.
	 * @param ctx the parse tree
	 */
	void exitExportsList(JavaScriptParser.ExportsListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#exportSpecifier}.
	 * @param ctx the parse tree
	 */
	void enterExportSpecifier(JavaScriptParser.ExportSpecifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#exportSpecifier}.
	 * @param ctx the parse tree
	 */
	void exitExportSpecifier(JavaScriptParser.ExportSpecifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(JavaScriptParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(JavaScriptParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentExpression(JavaScriptParser.AssignmentExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentExpression(JavaScriptParser.AssignmentExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#assignmentOperator}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentOperator(JavaScriptParser.AssignmentOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#assignmentOperator}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentOperator(JavaScriptParser.AssignmentOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#conditionalExpression}.
	 * @param ctx the parse tree
	 */
	void enterConditionalExpression(JavaScriptParser.ConditionalExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#conditionalExpression}.
	 * @param ctx the parse tree
	 */
	void exitConditionalExpression(JavaScriptParser.ConditionalExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#coalesceExpression}.
	 * @param ctx the parse tree
	 */
	void enterCoalesceExpression(JavaScriptParser.CoalesceExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#coalesceExpression}.
	 * @param ctx the parse tree
	 */
	void exitCoalesceExpression(JavaScriptParser.CoalesceExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#logicalORExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalORExpression(JavaScriptParser.LogicalORExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#logicalORExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalORExpression(JavaScriptParser.LogicalORExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#logicalANDExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalANDExpression(JavaScriptParser.LogicalANDExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#logicalANDExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalANDExpression(JavaScriptParser.LogicalANDExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bitwiseORExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitwiseORExpression(JavaScriptParser.BitwiseORExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bitwiseORExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitwiseORExpression(JavaScriptParser.BitwiseORExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bitwiseXORExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitwiseXORExpression(JavaScriptParser.BitwiseXORExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bitwiseXORExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitwiseXORExpression(JavaScriptParser.BitwiseXORExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bitwiseANDExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitwiseANDExpression(JavaScriptParser.BitwiseANDExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bitwiseANDExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitwiseANDExpression(JavaScriptParser.BitwiseANDExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void enterEqualityExpression(JavaScriptParser.EqualityExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void exitEqualityExpression(JavaScriptParser.EqualityExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterRelationalExpression(JavaScriptParser.RelationalExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitRelationalExpression(JavaScriptParser.RelationalExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#shiftExpression}.
	 * @param ctx the parse tree
	 */
	void enterShiftExpression(JavaScriptParser.ShiftExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#shiftExpression}.
	 * @param ctx the parse tree
	 */
	void exitShiftExpression(JavaScriptParser.ShiftExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void enterAdditiveExpression(JavaScriptParser.AdditiveExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void exitAdditiveExpression(JavaScriptParser.AdditiveExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicativeExpression(JavaScriptParser.MultiplicativeExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicativeExpression(JavaScriptParser.MultiplicativeExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#exponentiationExpression}.
	 * @param ctx the parse tree
	 */
	void enterExponentiationExpression(JavaScriptParser.ExponentiationExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#exponentiationExpression}.
	 * @param ctx the parse tree
	 */
	void exitExponentiationExpression(JavaScriptParser.ExponentiationExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryExpression(JavaScriptParser.UnaryExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryExpression(JavaScriptParser.UnaryExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#updateExpression}.
	 * @param ctx the parse tree
	 */
	void enterUpdateExpression(JavaScriptParser.UpdateExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#updateExpression}.
	 * @param ctx the parse tree
	 */
	void exitUpdateExpression(JavaScriptParser.UpdateExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#leftHandSideExpression}.
	 * @param ctx the parse tree
	 */
	void enterLeftHandSideExpression(JavaScriptParser.LeftHandSideExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#leftHandSideExpression}.
	 * @param ctx the parse tree
	 */
	void exitLeftHandSideExpression(JavaScriptParser.LeftHandSideExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#newExpression}.
	 * @param ctx the parse tree
	 */
	void enterNewExpression(JavaScriptParser.NewExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#newExpression}.
	 * @param ctx the parse tree
	 */
	void exitNewExpression(JavaScriptParser.NewExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#callExpression}.
	 * @param ctx the parse tree
	 */
	void enterCallExpression(JavaScriptParser.CallExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#callExpression}.
	 * @param ctx the parse tree
	 */
	void exitCallExpression(JavaScriptParser.CallExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#superCall}.
	 * @param ctx the parse tree
	 */
	void enterSuperCall(JavaScriptParser.SuperCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#superCall}.
	 * @param ctx the parse tree
	 */
	void exitSuperCall(JavaScriptParser.SuperCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#importCall}.
	 * @param ctx the parse tree
	 */
	void enterImportCall(JavaScriptParser.ImportCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#importCall}.
	 * @param ctx the parse tree
	 */
	void exitImportCall(JavaScriptParser.ImportCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#arguments}.
	 * @param ctx the parse tree
	 */
	void enterArguments(JavaScriptParser.ArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#arguments}.
	 * @param ctx the parse tree
	 */
	void exitArguments(JavaScriptParser.ArgumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#argumentList}.
	 * @param ctx the parse tree
	 */
	void enterArgumentList(JavaScriptParser.ArgumentListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#argumentList}.
	 * @param ctx the parse tree
	 */
	void exitArgumentList(JavaScriptParser.ArgumentListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#argument}.
	 * @param ctx the parse tree
	 */
	void enterArgument(JavaScriptParser.ArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#argument}.
	 * @param ctx the parse tree
	 */
	void exitArgument(JavaScriptParser.ArgumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#memberExpression}.
	 * @param ctx the parse tree
	 */
	void enterMemberExpression(JavaScriptParser.MemberExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#memberExpression}.
	 * @param ctx the parse tree
	 */
	void exitMemberExpression(JavaScriptParser.MemberExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#metaProperty}.
	 * @param ctx the parse tree
	 */
	void enterMetaProperty(JavaScriptParser.MetaPropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#metaProperty}.
	 * @param ctx the parse tree
	 */
	void exitMetaProperty(JavaScriptParser.MetaPropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterPrimaryExpression(JavaScriptParser.PrimaryExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitPrimaryExpression(JavaScriptParser.PrimaryExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#parenthesizedExpression}.
	 * @param ctx the parse tree
	 */
	void enterParenthesizedExpression(JavaScriptParser.ParenthesizedExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#parenthesizedExpression}.
	 * @param ctx the parse tree
	 */
	void exitParenthesizedExpression(JavaScriptParser.ParenthesizedExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteral(JavaScriptParser.LiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteral(JavaScriptParser.LiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#nullLiteral}.
	 * @param ctx the parse tree
	 */
	void enterNullLiteral(JavaScriptParser.NullLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#nullLiteral}.
	 * @param ctx the parse tree
	 */
	void exitNullLiteral(JavaScriptParser.NullLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#booleanLiteral}.
	 * @param ctx the parse tree
	 */
	void enterBooleanLiteral(JavaScriptParser.BooleanLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#booleanLiteral}.
	 * @param ctx the parse tree
	 */
	void exitBooleanLiteral(JavaScriptParser.BooleanLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#numericLiteral}.
	 * @param ctx the parse tree
	 */
	void enterNumericLiteral(JavaScriptParser.NumericLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#numericLiteral}.
	 * @param ctx the parse tree
	 */
	void exitNumericLiteral(JavaScriptParser.NumericLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#stringLiteral}.
	 * @param ctx the parse tree
	 */
	void enterStringLiteral(JavaScriptParser.StringLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#stringLiteral}.
	 * @param ctx the parse tree
	 */
	void exitStringLiteral(JavaScriptParser.StringLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#arrayLiteral}.
	 * @param ctx the parse tree
	 */
	void enterArrayLiteral(JavaScriptParser.ArrayLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#arrayLiteral}.
	 * @param ctx the parse tree
	 */
	void exitArrayLiteral(JavaScriptParser.ArrayLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#elementList}.
	 * @param ctx the parse tree
	 */
	void enterElementList(JavaScriptParser.ElementListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#elementList}.
	 * @param ctx the parse tree
	 */
	void exitElementList(JavaScriptParser.ElementListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#arrayElement}.
	 * @param ctx the parse tree
	 */
	void enterArrayElement(JavaScriptParser.ArrayElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#arrayElement}.
	 * @param ctx the parse tree
	 */
	void exitArrayElement(JavaScriptParser.ArrayElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#objectLiteral}.
	 * @param ctx the parse tree
	 */
	void enterObjectLiteral(JavaScriptParser.ObjectLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#objectLiteral}.
	 * @param ctx the parse tree
	 */
	void exitObjectLiteral(JavaScriptParser.ObjectLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#propertyDefinitionList}.
	 * @param ctx the parse tree
	 */
	void enterPropertyDefinitionList(JavaScriptParser.PropertyDefinitionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#propertyDefinitionList}.
	 * @param ctx the parse tree
	 */
	void exitPropertyDefinitionList(JavaScriptParser.PropertyDefinitionListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#propertyDefinition}.
	 * @param ctx the parse tree
	 */
	void enterPropertyDefinition(JavaScriptParser.PropertyDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#propertyDefinition}.
	 * @param ctx the parse tree
	 */
	void exitPropertyDefinition(JavaScriptParser.PropertyDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#propertyName}.
	 * @param ctx the parse tree
	 */
	void enterPropertyName(JavaScriptParser.PropertyNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#propertyName}.
	 * @param ctx the parse tree
	 */
	void exitPropertyName(JavaScriptParser.PropertyNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#functionExpression}.
	 * @param ctx the parse tree
	 */
	void enterFunctionExpression(JavaScriptParser.FunctionExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#functionExpression}.
	 * @param ctx the parse tree
	 */
	void exitFunctionExpression(JavaScriptParser.FunctionExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#generatorExpression}.
	 * @param ctx the parse tree
	 */
	void enterGeneratorExpression(JavaScriptParser.GeneratorExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#generatorExpression}.
	 * @param ctx the parse tree
	 */
	void exitGeneratorExpression(JavaScriptParser.GeneratorExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#asyncFunctionExpression}.
	 * @param ctx the parse tree
	 */
	void enterAsyncFunctionExpression(JavaScriptParser.AsyncFunctionExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#asyncFunctionExpression}.
	 * @param ctx the parse tree
	 */
	void exitAsyncFunctionExpression(JavaScriptParser.AsyncFunctionExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#asyncGeneratorExpression}.
	 * @param ctx the parse tree
	 */
	void enterAsyncGeneratorExpression(JavaScriptParser.AsyncGeneratorExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#asyncGeneratorExpression}.
	 * @param ctx the parse tree
	 */
	void exitAsyncGeneratorExpression(JavaScriptParser.AsyncGeneratorExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#classExpression}.
	 * @param ctx the parse tree
	 */
	void enterClassExpression(JavaScriptParser.ClassExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#classExpression}.
	 * @param ctx the parse tree
	 */
	void exitClassExpression(JavaScriptParser.ClassExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#arrowFunction}.
	 * @param ctx the parse tree
	 */
	void enterArrowFunction(JavaScriptParser.ArrowFunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#arrowFunction}.
	 * @param ctx the parse tree
	 */
	void exitArrowFunction(JavaScriptParser.ArrowFunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#asyncArrowFunction}.
	 * @param ctx the parse tree
	 */
	void enterAsyncArrowFunction(JavaScriptParser.AsyncArrowFunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#asyncArrowFunction}.
	 * @param ctx the parse tree
	 */
	void exitAsyncArrowFunction(JavaScriptParser.AsyncArrowFunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#arrowParameters}.
	 * @param ctx the parse tree
	 */
	void enterArrowParameters(JavaScriptParser.ArrowParametersContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#arrowParameters}.
	 * @param ctx the parse tree
	 */
	void exitArrowParameters(JavaScriptParser.ArrowParametersContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#arrowBody}.
	 * @param ctx the parse tree
	 */
	void enterArrowBody(JavaScriptParser.ArrowBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#arrowBody}.
	 * @param ctx the parse tree
	 */
	void exitArrowBody(JavaScriptParser.ArrowBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#yieldExpression}.
	 * @param ctx the parse tree
	 */
	void enterYieldExpression(JavaScriptParser.YieldExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#yieldExpression}.
	 * @param ctx the parse tree
	 */
	void exitYieldExpression(JavaScriptParser.YieldExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#templateLiteral}.
	 * @param ctx the parse tree
	 */
	void enterTemplateLiteral(JavaScriptParser.TemplateLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#templateLiteral}.
	 * @param ctx the parse tree
	 */
	void exitTemplateLiteral(JavaScriptParser.TemplateLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#templateSpans}.
	 * @param ctx the parse tree
	 */
	void enterTemplateSpans(JavaScriptParser.TemplateSpansContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#templateSpans}.
	 * @param ctx the parse tree
	 */
	void exitTemplateSpans(JavaScriptParser.TemplateSpansContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#templateSpan}.
	 * @param ctx the parse tree
	 */
	void enterTemplateSpan(JavaScriptParser.TemplateSpanContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#templateSpan}.
	 * @param ctx the parse tree
	 */
	void exitTemplateSpan(JavaScriptParser.TemplateSpanContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#templateMiddle}.
	 * @param ctx the parse tree
	 */
	void enterTemplateMiddle(JavaScriptParser.TemplateMiddleContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#templateMiddle}.
	 * @param ctx the parse tree
	 */
	void exitTemplateMiddle(JavaScriptParser.TemplateMiddleContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#regularExpressionLiteral}.
	 * @param ctx the parse tree
	 */
	void enterRegularExpressionLiteral(JavaScriptParser.RegularExpressionLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#regularExpressionLiteral}.
	 * @param ctx the parse tree
	 */
	void exitRegularExpressionLiteral(JavaScriptParser.RegularExpressionLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#formalParameterList}.
	 * @param ctx the parse tree
	 */
	void enterFormalParameterList(JavaScriptParser.FormalParameterListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#formalParameterList}.
	 * @param ctx the parse tree
	 */
	void exitFormalParameterList(JavaScriptParser.FormalParameterListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#formalParameter}.
	 * @param ctx the parse tree
	 */
	void enterFormalParameter(JavaScriptParser.FormalParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#formalParameter}.
	 * @param ctx the parse tree
	 */
	void exitFormalParameter(JavaScriptParser.FormalParameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#restParameter}.
	 * @param ctx the parse tree
	 */
	void enterRestParameter(JavaScriptParser.RestParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#restParameter}.
	 * @param ctx the parse tree
	 */
	void exitRestParameter(JavaScriptParser.RestParameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bindingElement}.
	 * @param ctx the parse tree
	 */
	void enterBindingElement(JavaScriptParser.BindingElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bindingElement}.
	 * @param ctx the parse tree
	 */
	void exitBindingElement(JavaScriptParser.BindingElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bindingPattern}.
	 * @param ctx the parse tree
	 */
	void enterBindingPattern(JavaScriptParser.BindingPatternContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bindingPattern}.
	 * @param ctx the parse tree
	 */
	void exitBindingPattern(JavaScriptParser.BindingPatternContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#objectBindingPattern}.
	 * @param ctx the parse tree
	 */
	void enterObjectBindingPattern(JavaScriptParser.ObjectBindingPatternContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#objectBindingPattern}.
	 * @param ctx the parse tree
	 */
	void exitObjectBindingPattern(JavaScriptParser.ObjectBindingPatternContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bindingPropertyList}.
	 * @param ctx the parse tree
	 */
	void enterBindingPropertyList(JavaScriptParser.BindingPropertyListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bindingPropertyList}.
	 * @param ctx the parse tree
	 */
	void exitBindingPropertyList(JavaScriptParser.BindingPropertyListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bindingProperty}.
	 * @param ctx the parse tree
	 */
	void enterBindingProperty(JavaScriptParser.BindingPropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bindingProperty}.
	 * @param ctx the parse tree
	 */
	void exitBindingProperty(JavaScriptParser.BindingPropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#arrayBindingPattern}.
	 * @param ctx the parse tree
	 */
	void enterArrayBindingPattern(JavaScriptParser.ArrayBindingPatternContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#arrayBindingPattern}.
	 * @param ctx the parse tree
	 */
	void exitArrayBindingPattern(JavaScriptParser.ArrayBindingPatternContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bindingElementList}.
	 * @param ctx the parse tree
	 */
	void enterBindingElementList(JavaScriptParser.BindingElementListContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bindingElementList}.
	 * @param ctx the parse tree
	 */
	void exitBindingElementList(JavaScriptParser.BindingElementListContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bindingElision}.
	 * @param ctx the parse tree
	 */
	void enterBindingElision(JavaScriptParser.BindingElisionContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bindingElision}.
	 * @param ctx the parse tree
	 */
	void exitBindingElision(JavaScriptParser.BindingElisionContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#functionBody}.
	 * @param ctx the parse tree
	 */
	void enterFunctionBody(JavaScriptParser.FunctionBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#functionBody}.
	 * @param ctx the parse tree
	 */
	void exitFunctionBody(JavaScriptParser.FunctionBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#initializer}.
	 * @param ctx the parse tree
	 */
	void enterInitializer(JavaScriptParser.InitializerContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#initializer}.
	 * @param ctx the parse tree
	 */
	void exitInitializer(JavaScriptParser.InitializerContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#bindingIdentifier}.
	 * @param ctx the parse tree
	 */
	void enterBindingIdentifier(JavaScriptParser.BindingIdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#bindingIdentifier}.
	 * @param ctx the parse tree
	 */
	void exitBindingIdentifier(JavaScriptParser.BindingIdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#identifier}.
	 * @param ctx the parse tree
	 */
	void enterIdentifier(JavaScriptParser.IdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#identifier}.
	 * @param ctx the parse tree
	 */
	void exitIdentifier(JavaScriptParser.IdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#identifierName}.
	 * @param ctx the parse tree
	 */
	void enterIdentifierName(JavaScriptParser.IdentifierNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#identifierName}.
	 * @param ctx the parse tree
	 */
	void exitIdentifierName(JavaScriptParser.IdentifierNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#reservedWord}.
	 * @param ctx the parse tree
	 */
	void enterReservedWord(JavaScriptParser.ReservedWordContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#reservedWord}.
	 * @param ctx the parse tree
	 */
	void exitReservedWord(JavaScriptParser.ReservedWordContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#keyword}.
	 * @param ctx the parse tree
	 */
	void enterKeyword(JavaScriptParser.KeywordContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#keyword}.
	 * @param ctx the parse tree
	 */
	void exitKeyword(JavaScriptParser.KeywordContext ctx);
	/**
	 * Enter a parse tree produced by {@link JavaScriptParser#futureReservedWord}.
	 * @param ctx the parse tree
	 */
	void enterFutureReservedWord(JavaScriptParser.FutureReservedWordContext ctx);
	/**
	 * Exit a parse tree produced by {@link JavaScriptParser#futureReservedWord}.
	 * @param ctx the parse tree
	 */
	void exitFutureReservedWord(JavaScriptParser.FutureReservedWordContext ctx);
}