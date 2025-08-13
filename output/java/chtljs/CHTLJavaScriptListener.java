// Generated from CHTLJavaScript.g4 by ANTLR 4.13.1
package chtljs;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link CHTLJavaScriptParser}.
 */
public interface CHTLJavaScriptListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterPrimaryExpression(CHTLJavaScriptParser.PrimaryExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitPrimaryExpression(CHTLJavaScriptParser.PrimaryExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#chtlSelector}.
	 * @param ctx the parse tree
	 */
	void enterChtlSelector(CHTLJavaScriptParser.ChtlSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#chtlSelector}.
	 * @param ctx the parse tree
	 */
	void exitChtlSelector(CHTLJavaScriptParser.ChtlSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#selectorExpression}.
	 * @param ctx the parse tree
	 */
	void enterSelectorExpression(CHTLJavaScriptParser.SelectorExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#selectorExpression}.
	 * @param ctx the parse tree
	 */
	void exitSelectorExpression(CHTLJavaScriptParser.SelectorExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#selectorIdentifier}.
	 * @param ctx the parse tree
	 */
	void enterSelectorIdentifier(CHTLJavaScriptParser.SelectorIdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#selectorIdentifier}.
	 * @param ctx the parse tree
	 */
	void exitSelectorIdentifier(CHTLJavaScriptParser.SelectorIdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#selectorIndex}.
	 * @param ctx the parse tree
	 */
	void enterSelectorIndex(CHTLJavaScriptParser.SelectorIndexContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#selectorIndex}.
	 * @param ctx the parse tree
	 */
	void exitSelectorIndex(CHTLJavaScriptParser.SelectorIndexContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#complexSelector}.
	 * @param ctx the parse tree
	 */
	void enterComplexSelector(CHTLJavaScriptParser.ComplexSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#complexSelector}.
	 * @param ctx the parse tree
	 */
	void exitComplexSelector(CHTLJavaScriptParser.ComplexSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#selectorPart}.
	 * @param ctx the parse tree
	 */
	void enterSelectorPart(CHTLJavaScriptParser.SelectorPartContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#selectorPart}.
	 * @param ctx the parse tree
	 */
	void exitSelectorPart(CHTLJavaScriptParser.SelectorPartContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#memberExpression}.
	 * @param ctx the parse tree
	 */
	void enterMemberExpression(CHTLJavaScriptParser.MemberExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#memberExpression}.
	 * @param ctx the parse tree
	 */
	void exitMemberExpression(CHTLJavaScriptParser.MemberExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#callExpression}.
	 * @param ctx the parse tree
	 */
	void enterCallExpression(CHTLJavaScriptParser.CallExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#callExpression}.
	 * @param ctx the parse tree
	 */
	void exitCallExpression(CHTLJavaScriptParser.CallExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#animateCall}.
	 * @param ctx the parse tree
	 */
	void enterAnimateCall(CHTLJavaScriptParser.AnimateCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#animateCall}.
	 * @param ctx the parse tree
	 */
	void exitAnimateCall(CHTLJavaScriptParser.AnimateCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#listenConfig}.
	 * @param ctx the parse tree
	 */
	void enterListenConfig(CHTLJavaScriptParser.ListenConfigContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#listenConfig}.
	 * @param ctx the parse tree
	 */
	void exitListenConfig(CHTLJavaScriptParser.ListenConfigContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#eventHandlerList}.
	 * @param ctx the parse tree
	 */
	void enterEventHandlerList(CHTLJavaScriptParser.EventHandlerListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#eventHandlerList}.
	 * @param ctx the parse tree
	 */
	void exitEventHandlerList(CHTLJavaScriptParser.EventHandlerListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#eventHandler}.
	 * @param ctx the parse tree
	 */
	void enterEventHandler(CHTLJavaScriptParser.EventHandlerContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#eventHandler}.
	 * @param ctx the parse tree
	 */
	void exitEventHandler(CHTLJavaScriptParser.EventHandlerContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#delegateConfig}.
	 * @param ctx the parse tree
	 */
	void enterDelegateConfig(CHTLJavaScriptParser.DelegateConfigContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#delegateConfig}.
	 * @param ctx the parse tree
	 */
	void exitDelegateConfig(CHTLJavaScriptParser.DelegateConfigContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#delegateProperty}.
	 * @param ctx the parse tree
	 */
	void enterDelegateProperty(CHTLJavaScriptParser.DelegatePropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#delegateProperty}.
	 * @param ctx the parse tree
	 */
	void exitDelegateProperty(CHTLJavaScriptParser.DelegatePropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#selectorArray}.
	 * @param ctx the parse tree
	 */
	void enterSelectorArray(CHTLJavaScriptParser.SelectorArrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#selectorArray}.
	 * @param ctx the parse tree
	 */
	void exitSelectorArray(CHTLJavaScriptParser.SelectorArrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#animateConfig}.
	 * @param ctx the parse tree
	 */
	void enterAnimateConfig(CHTLJavaScriptParser.AnimateConfigContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#animateConfig}.
	 * @param ctx the parse tree
	 */
	void exitAnimateConfig(CHTLJavaScriptParser.AnimateConfigContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#animateProperty}.
	 * @param ctx the parse tree
	 */
	void enterAnimateProperty(CHTLJavaScriptParser.AnimatePropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#animateProperty}.
	 * @param ctx the parse tree
	 */
	void exitAnimateProperty(CHTLJavaScriptParser.AnimatePropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#cssBlock}.
	 * @param ctx the parse tree
	 */
	void enterCssBlock(CHTLJavaScriptParser.CssBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#cssBlock}.
	 * @param ctx the parse tree
	 */
	void exitCssBlock(CHTLJavaScriptParser.CssBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#cssProperty}.
	 * @param ctx the parse tree
	 */
	void enterCssProperty(CHTLJavaScriptParser.CssPropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#cssProperty}.
	 * @param ctx the parse tree
	 */
	void exitCssProperty(CHTLJavaScriptParser.CssPropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#propertyName}.
	 * @param ctx the parse tree
	 */
	void enterPropertyName(CHTLJavaScriptParser.PropertyNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#propertyName}.
	 * @param ctx the parse tree
	 */
	void exitPropertyName(CHTLJavaScriptParser.PropertyNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#propertyValue}.
	 * @param ctx the parse tree
	 */
	void enterPropertyValue(CHTLJavaScriptParser.PropertyValueContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#propertyValue}.
	 * @param ctx the parse tree
	 */
	void exitPropertyValue(CHTLJavaScriptParser.PropertyValueContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#cssFunction}.
	 * @param ctx the parse tree
	 */
	void enterCssFunction(CHTLJavaScriptParser.CssFunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#cssFunction}.
	 * @param ctx the parse tree
	 */
	void exitCssFunction(CHTLJavaScriptParser.CssFunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#cssFunctionArguments}.
	 * @param ctx the parse tree
	 */
	void enterCssFunctionArguments(CHTLJavaScriptParser.CssFunctionArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#cssFunctionArguments}.
	 * @param ctx the parse tree
	 */
	void exitCssFunctionArguments(CHTLJavaScriptParser.CssFunctionArgumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#whenArray}.
	 * @param ctx the parse tree
	 */
	void enterWhenArray(CHTLJavaScriptParser.WhenArrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#whenArray}.
	 * @param ctx the parse tree
	 */
	void exitWhenArray(CHTLJavaScriptParser.WhenArrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#whenItem}.
	 * @param ctx the parse tree
	 */
	void enterWhenItem(CHTLJavaScriptParser.WhenItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#whenItem}.
	 * @param ctx the parse tree
	 */
	void exitWhenItem(CHTLJavaScriptParser.WhenItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#whenProperty}.
	 * @param ctx the parse tree
	 */
	void enterWhenProperty(CHTLJavaScriptParser.WhenPropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#whenProperty}.
	 * @param ctx the parse tree
	 */
	void exitWhenProperty(CHTLJavaScriptParser.WhenPropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteral(CHTLJavaScriptParser.LiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteral(CHTLJavaScriptParser.LiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(CHTLJavaScriptParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(CHTLJavaScriptParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#sourceElements}.
	 * @param ctx the parse tree
	 */
	void enterSourceElements(CHTLJavaScriptParser.SourceElementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#sourceElements}.
	 * @param ctx the parse tree
	 */
	void exitSourceElements(CHTLJavaScriptParser.SourceElementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#sourceElement}.
	 * @param ctx the parse tree
	 */
	void enterSourceElement(CHTLJavaScriptParser.SourceElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#sourceElement}.
	 * @param ctx the parse tree
	 */
	void exitSourceElement(CHTLJavaScriptParser.SourceElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(CHTLJavaScriptParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(CHTLJavaScriptParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#hoistableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterHoistableDeclaration(CHTLJavaScriptParser.HoistableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#hoistableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitHoistableDeclaration(CHTLJavaScriptParser.HoistableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDeclaration(CHTLJavaScriptParser.FunctionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDeclaration(CHTLJavaScriptParser.FunctionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#generatorDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterGeneratorDeclaration(CHTLJavaScriptParser.GeneratorDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#generatorDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitGeneratorDeclaration(CHTLJavaScriptParser.GeneratorDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#asyncFunctionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterAsyncFunctionDeclaration(CHTLJavaScriptParser.AsyncFunctionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#asyncFunctionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitAsyncFunctionDeclaration(CHTLJavaScriptParser.AsyncFunctionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#asyncGeneratorDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterAsyncGeneratorDeclaration(CHTLJavaScriptParser.AsyncGeneratorDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#asyncGeneratorDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitAsyncGeneratorDeclaration(CHTLJavaScriptParser.AsyncGeneratorDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#classDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterClassDeclaration(CHTLJavaScriptParser.ClassDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#classDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitClassDeclaration(CHTLJavaScriptParser.ClassDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#classExtends}.
	 * @param ctx the parse tree
	 */
	void enterClassExtends(CHTLJavaScriptParser.ClassExtendsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#classExtends}.
	 * @param ctx the parse tree
	 */
	void exitClassExtends(CHTLJavaScriptParser.ClassExtendsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#classBody}.
	 * @param ctx the parse tree
	 */
	void enterClassBody(CHTLJavaScriptParser.ClassBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#classBody}.
	 * @param ctx the parse tree
	 */
	void exitClassBody(CHTLJavaScriptParser.ClassBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#classElement}.
	 * @param ctx the parse tree
	 */
	void enterClassElement(CHTLJavaScriptParser.ClassElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#classElement}.
	 * @param ctx the parse tree
	 */
	void exitClassElement(CHTLJavaScriptParser.ClassElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#methodDefinition}.
	 * @param ctx the parse tree
	 */
	void enterMethodDefinition(CHTLJavaScriptParser.MethodDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#methodDefinition}.
	 * @param ctx the parse tree
	 */
	void exitMethodDefinition(CHTLJavaScriptParser.MethodDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#fieldDefinition}.
	 * @param ctx the parse tree
	 */
	void enterFieldDefinition(CHTLJavaScriptParser.FieldDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#fieldDefinition}.
	 * @param ctx the parse tree
	 */
	void exitFieldDefinition(CHTLJavaScriptParser.FieldDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#lexicalDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterLexicalDeclaration(CHTLJavaScriptParser.LexicalDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#lexicalDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitLexicalDeclaration(CHTLJavaScriptParser.LexicalDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#letOrConst}.
	 * @param ctx the parse tree
	 */
	void enterLetOrConst(CHTLJavaScriptParser.LetOrConstContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#letOrConst}.
	 * @param ctx the parse tree
	 */
	void exitLetOrConst(CHTLJavaScriptParser.LetOrConstContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bindingList}.
	 * @param ctx the parse tree
	 */
	void enterBindingList(CHTLJavaScriptParser.BindingListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bindingList}.
	 * @param ctx the parse tree
	 */
	void exitBindingList(CHTLJavaScriptParser.BindingListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#lexicalBinding}.
	 * @param ctx the parse tree
	 */
	void enterLexicalBinding(CHTLJavaScriptParser.LexicalBindingContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#lexicalBinding}.
	 * @param ctx the parse tree
	 */
	void exitLexicalBinding(CHTLJavaScriptParser.LexicalBindingContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(CHTLJavaScriptParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(CHTLJavaScriptParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#blockStatement}.
	 * @param ctx the parse tree
	 */
	void enterBlockStatement(CHTLJavaScriptParser.BlockStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#blockStatement}.
	 * @param ctx the parse tree
	 */
	void exitBlockStatement(CHTLJavaScriptParser.BlockStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#statementList}.
	 * @param ctx the parse tree
	 */
	void enterStatementList(CHTLJavaScriptParser.StatementListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#statementList}.
	 * @param ctx the parse tree
	 */
	void exitStatementList(CHTLJavaScriptParser.StatementListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#variableStatement}.
	 * @param ctx the parse tree
	 */
	void enterVariableStatement(CHTLJavaScriptParser.VariableStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#variableStatement}.
	 * @param ctx the parse tree
	 */
	void exitVariableStatement(CHTLJavaScriptParser.VariableStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#variableDeclarationList}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclarationList(CHTLJavaScriptParser.VariableDeclarationListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#variableDeclarationList}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclarationList(CHTLJavaScriptParser.VariableDeclarationListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclaration(CHTLJavaScriptParser.VariableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclaration(CHTLJavaScriptParser.VariableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void enterEmptyStatement(CHTLJavaScriptParser.EmptyStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void exitEmptyStatement(CHTLJavaScriptParser.EmptyStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void enterExpressionStatement(CHTLJavaScriptParser.ExpressionStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void exitExpressionStatement(CHTLJavaScriptParser.ExpressionStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(CHTLJavaScriptParser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(CHTLJavaScriptParser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#iterationStatement}.
	 * @param ctx the parse tree
	 */
	void enterIterationStatement(CHTLJavaScriptParser.IterationStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#iterationStatement}.
	 * @param ctx the parse tree
	 */
	void exitIterationStatement(CHTLJavaScriptParser.IterationStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#doWhileStatement}.
	 * @param ctx the parse tree
	 */
	void enterDoWhileStatement(CHTLJavaScriptParser.DoWhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#doWhileStatement}.
	 * @param ctx the parse tree
	 */
	void exitDoWhileStatement(CHTLJavaScriptParser.DoWhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(CHTLJavaScriptParser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(CHTLJavaScriptParser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void enterForStatement(CHTLJavaScriptParser.ForStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void exitForStatement(CHTLJavaScriptParser.ForStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#forInit}.
	 * @param ctx the parse tree
	 */
	void enterForInit(CHTLJavaScriptParser.ForInitContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#forInit}.
	 * @param ctx the parse tree
	 */
	void exitForInit(CHTLJavaScriptParser.ForInitContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#forInStatement}.
	 * @param ctx the parse tree
	 */
	void enterForInStatement(CHTLJavaScriptParser.ForInStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#forInStatement}.
	 * @param ctx the parse tree
	 */
	void exitForInStatement(CHTLJavaScriptParser.ForInStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#forOfStatement}.
	 * @param ctx the parse tree
	 */
	void enterForOfStatement(CHTLJavaScriptParser.ForOfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#forOfStatement}.
	 * @param ctx the parse tree
	 */
	void exitForOfStatement(CHTLJavaScriptParser.ForOfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#forInBinding}.
	 * @param ctx the parse tree
	 */
	void enterForInBinding(CHTLJavaScriptParser.ForInBindingContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#forInBinding}.
	 * @param ctx the parse tree
	 */
	void exitForInBinding(CHTLJavaScriptParser.ForInBindingContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#continueStatement}.
	 * @param ctx the parse tree
	 */
	void enterContinueStatement(CHTLJavaScriptParser.ContinueStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#continueStatement}.
	 * @param ctx the parse tree
	 */
	void exitContinueStatement(CHTLJavaScriptParser.ContinueStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#breakStatement}.
	 * @param ctx the parse tree
	 */
	void enterBreakStatement(CHTLJavaScriptParser.BreakStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#breakStatement}.
	 * @param ctx the parse tree
	 */
	void exitBreakStatement(CHTLJavaScriptParser.BreakStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void enterReturnStatement(CHTLJavaScriptParser.ReturnStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void exitReturnStatement(CHTLJavaScriptParser.ReturnStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#withStatement}.
	 * @param ctx the parse tree
	 */
	void enterWithStatement(CHTLJavaScriptParser.WithStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#withStatement}.
	 * @param ctx the parse tree
	 */
	void exitWithStatement(CHTLJavaScriptParser.WithStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#labelledStatement}.
	 * @param ctx the parse tree
	 */
	void enterLabelledStatement(CHTLJavaScriptParser.LabelledStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#labelledStatement}.
	 * @param ctx the parse tree
	 */
	void exitLabelledStatement(CHTLJavaScriptParser.LabelledStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#switchStatement}.
	 * @param ctx the parse tree
	 */
	void enterSwitchStatement(CHTLJavaScriptParser.SwitchStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#switchStatement}.
	 * @param ctx the parse tree
	 */
	void exitSwitchStatement(CHTLJavaScriptParser.SwitchStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#caseClause}.
	 * @param ctx the parse tree
	 */
	void enterCaseClause(CHTLJavaScriptParser.CaseClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#caseClause}.
	 * @param ctx the parse tree
	 */
	void exitCaseClause(CHTLJavaScriptParser.CaseClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#defaultClause}.
	 * @param ctx the parse tree
	 */
	void enterDefaultClause(CHTLJavaScriptParser.DefaultClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#defaultClause}.
	 * @param ctx the parse tree
	 */
	void exitDefaultClause(CHTLJavaScriptParser.DefaultClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#throwStatement}.
	 * @param ctx the parse tree
	 */
	void enterThrowStatement(CHTLJavaScriptParser.ThrowStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#throwStatement}.
	 * @param ctx the parse tree
	 */
	void exitThrowStatement(CHTLJavaScriptParser.ThrowStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#tryStatement}.
	 * @param ctx the parse tree
	 */
	void enterTryStatement(CHTLJavaScriptParser.TryStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#tryStatement}.
	 * @param ctx the parse tree
	 */
	void exitTryStatement(CHTLJavaScriptParser.TryStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#catchClause}.
	 * @param ctx the parse tree
	 */
	void enterCatchClause(CHTLJavaScriptParser.CatchClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#catchClause}.
	 * @param ctx the parse tree
	 */
	void exitCatchClause(CHTLJavaScriptParser.CatchClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#catchParameter}.
	 * @param ctx the parse tree
	 */
	void enterCatchParameter(CHTLJavaScriptParser.CatchParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#catchParameter}.
	 * @param ctx the parse tree
	 */
	void exitCatchParameter(CHTLJavaScriptParser.CatchParameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#finallyClause}.
	 * @param ctx the parse tree
	 */
	void enterFinallyClause(CHTLJavaScriptParser.FinallyClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#finallyClause}.
	 * @param ctx the parse tree
	 */
	void exitFinallyClause(CHTLJavaScriptParser.FinallyClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#debuggerStatement}.
	 * @param ctx the parse tree
	 */
	void enterDebuggerStatement(CHTLJavaScriptParser.DebuggerStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#debuggerStatement}.
	 * @param ctx the parse tree
	 */
	void exitDebuggerStatement(CHTLJavaScriptParser.DebuggerStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#importStatement}.
	 * @param ctx the parse tree
	 */
	void enterImportStatement(CHTLJavaScriptParser.ImportStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#importStatement}.
	 * @param ctx the parse tree
	 */
	void exitImportStatement(CHTLJavaScriptParser.ImportStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#importClause}.
	 * @param ctx the parse tree
	 */
	void enterImportClause(CHTLJavaScriptParser.ImportClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#importClause}.
	 * @param ctx the parse tree
	 */
	void exitImportClause(CHTLJavaScriptParser.ImportClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#importedDefaultBinding}.
	 * @param ctx the parse tree
	 */
	void enterImportedDefaultBinding(CHTLJavaScriptParser.ImportedDefaultBindingContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#importedDefaultBinding}.
	 * @param ctx the parse tree
	 */
	void exitImportedDefaultBinding(CHTLJavaScriptParser.ImportedDefaultBindingContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#namespaceImport}.
	 * @param ctx the parse tree
	 */
	void enterNamespaceImport(CHTLJavaScriptParser.NamespaceImportContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#namespaceImport}.
	 * @param ctx the parse tree
	 */
	void exitNamespaceImport(CHTLJavaScriptParser.NamespaceImportContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#namedImports}.
	 * @param ctx the parse tree
	 */
	void enterNamedImports(CHTLJavaScriptParser.NamedImportsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#namedImports}.
	 * @param ctx the parse tree
	 */
	void exitNamedImports(CHTLJavaScriptParser.NamedImportsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#importsList}.
	 * @param ctx the parse tree
	 */
	void enterImportsList(CHTLJavaScriptParser.ImportsListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#importsList}.
	 * @param ctx the parse tree
	 */
	void exitImportsList(CHTLJavaScriptParser.ImportsListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#importSpecifier}.
	 * @param ctx the parse tree
	 */
	void enterImportSpecifier(CHTLJavaScriptParser.ImportSpecifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#importSpecifier}.
	 * @param ctx the parse tree
	 */
	void exitImportSpecifier(CHTLJavaScriptParser.ImportSpecifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#moduleSpecifier}.
	 * @param ctx the parse tree
	 */
	void enterModuleSpecifier(CHTLJavaScriptParser.ModuleSpecifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#moduleSpecifier}.
	 * @param ctx the parse tree
	 */
	void exitModuleSpecifier(CHTLJavaScriptParser.ModuleSpecifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#exportStatement}.
	 * @param ctx the parse tree
	 */
	void enterExportStatement(CHTLJavaScriptParser.ExportStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#exportStatement}.
	 * @param ctx the parse tree
	 */
	void exitExportStatement(CHTLJavaScriptParser.ExportStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#exportClause}.
	 * @param ctx the parse tree
	 */
	void enterExportClause(CHTLJavaScriptParser.ExportClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#exportClause}.
	 * @param ctx the parse tree
	 */
	void exitExportClause(CHTLJavaScriptParser.ExportClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#exportsList}.
	 * @param ctx the parse tree
	 */
	void enterExportsList(CHTLJavaScriptParser.ExportsListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#exportsList}.
	 * @param ctx the parse tree
	 */
	void exitExportsList(CHTLJavaScriptParser.ExportsListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#exportSpecifier}.
	 * @param ctx the parse tree
	 */
	void enterExportSpecifier(CHTLJavaScriptParser.ExportSpecifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#exportSpecifier}.
	 * @param ctx the parse tree
	 */
	void exitExportSpecifier(CHTLJavaScriptParser.ExportSpecifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(CHTLJavaScriptParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(CHTLJavaScriptParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentExpression(CHTLJavaScriptParser.AssignmentExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentExpression(CHTLJavaScriptParser.AssignmentExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#assignmentOperator}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentOperator(CHTLJavaScriptParser.AssignmentOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#assignmentOperator}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentOperator(CHTLJavaScriptParser.AssignmentOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#conditionalExpression}.
	 * @param ctx the parse tree
	 */
	void enterConditionalExpression(CHTLJavaScriptParser.ConditionalExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#conditionalExpression}.
	 * @param ctx the parse tree
	 */
	void exitConditionalExpression(CHTLJavaScriptParser.ConditionalExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#coalesceExpression}.
	 * @param ctx the parse tree
	 */
	void enterCoalesceExpression(CHTLJavaScriptParser.CoalesceExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#coalesceExpression}.
	 * @param ctx the parse tree
	 */
	void exitCoalesceExpression(CHTLJavaScriptParser.CoalesceExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#logicalORExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalORExpression(CHTLJavaScriptParser.LogicalORExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#logicalORExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalORExpression(CHTLJavaScriptParser.LogicalORExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#logicalANDExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalANDExpression(CHTLJavaScriptParser.LogicalANDExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#logicalANDExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalANDExpression(CHTLJavaScriptParser.LogicalANDExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bitwiseORExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitwiseORExpression(CHTLJavaScriptParser.BitwiseORExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bitwiseORExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitwiseORExpression(CHTLJavaScriptParser.BitwiseORExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bitwiseXORExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitwiseXORExpression(CHTLJavaScriptParser.BitwiseXORExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bitwiseXORExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitwiseXORExpression(CHTLJavaScriptParser.BitwiseXORExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bitwiseANDExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitwiseANDExpression(CHTLJavaScriptParser.BitwiseANDExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bitwiseANDExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitwiseANDExpression(CHTLJavaScriptParser.BitwiseANDExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void enterEqualityExpression(CHTLJavaScriptParser.EqualityExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void exitEqualityExpression(CHTLJavaScriptParser.EqualityExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterRelationalExpression(CHTLJavaScriptParser.RelationalExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitRelationalExpression(CHTLJavaScriptParser.RelationalExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#shiftExpression}.
	 * @param ctx the parse tree
	 */
	void enterShiftExpression(CHTLJavaScriptParser.ShiftExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#shiftExpression}.
	 * @param ctx the parse tree
	 */
	void exitShiftExpression(CHTLJavaScriptParser.ShiftExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void enterAdditiveExpression(CHTLJavaScriptParser.AdditiveExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void exitAdditiveExpression(CHTLJavaScriptParser.AdditiveExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicativeExpression(CHTLJavaScriptParser.MultiplicativeExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicativeExpression(CHTLJavaScriptParser.MultiplicativeExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#exponentiationExpression}.
	 * @param ctx the parse tree
	 */
	void enterExponentiationExpression(CHTLJavaScriptParser.ExponentiationExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#exponentiationExpression}.
	 * @param ctx the parse tree
	 */
	void exitExponentiationExpression(CHTLJavaScriptParser.ExponentiationExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryExpression(CHTLJavaScriptParser.UnaryExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryExpression(CHTLJavaScriptParser.UnaryExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#updateExpression}.
	 * @param ctx the parse tree
	 */
	void enterUpdateExpression(CHTLJavaScriptParser.UpdateExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#updateExpression}.
	 * @param ctx the parse tree
	 */
	void exitUpdateExpression(CHTLJavaScriptParser.UpdateExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#leftHandSideExpression}.
	 * @param ctx the parse tree
	 */
	void enterLeftHandSideExpression(CHTLJavaScriptParser.LeftHandSideExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#leftHandSideExpression}.
	 * @param ctx the parse tree
	 */
	void exitLeftHandSideExpression(CHTLJavaScriptParser.LeftHandSideExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#newExpression}.
	 * @param ctx the parse tree
	 */
	void enterNewExpression(CHTLJavaScriptParser.NewExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#newExpression}.
	 * @param ctx the parse tree
	 */
	void exitNewExpression(CHTLJavaScriptParser.NewExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#superCall}.
	 * @param ctx the parse tree
	 */
	void enterSuperCall(CHTLJavaScriptParser.SuperCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#superCall}.
	 * @param ctx the parse tree
	 */
	void exitSuperCall(CHTLJavaScriptParser.SuperCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#importCall}.
	 * @param ctx the parse tree
	 */
	void enterImportCall(CHTLJavaScriptParser.ImportCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#importCall}.
	 * @param ctx the parse tree
	 */
	void exitImportCall(CHTLJavaScriptParser.ImportCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#arguments}.
	 * @param ctx the parse tree
	 */
	void enterArguments(CHTLJavaScriptParser.ArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#arguments}.
	 * @param ctx the parse tree
	 */
	void exitArguments(CHTLJavaScriptParser.ArgumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#argumentList}.
	 * @param ctx the parse tree
	 */
	void enterArgumentList(CHTLJavaScriptParser.ArgumentListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#argumentList}.
	 * @param ctx the parse tree
	 */
	void exitArgumentList(CHTLJavaScriptParser.ArgumentListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#argument}.
	 * @param ctx the parse tree
	 */
	void enterArgument(CHTLJavaScriptParser.ArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#argument}.
	 * @param ctx the parse tree
	 */
	void exitArgument(CHTLJavaScriptParser.ArgumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#metaProperty}.
	 * @param ctx the parse tree
	 */
	void enterMetaProperty(CHTLJavaScriptParser.MetaPropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#metaProperty}.
	 * @param ctx the parse tree
	 */
	void exitMetaProperty(CHTLJavaScriptParser.MetaPropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#parenthesizedExpression}.
	 * @param ctx the parse tree
	 */
	void enterParenthesizedExpression(CHTLJavaScriptParser.ParenthesizedExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#parenthesizedExpression}.
	 * @param ctx the parse tree
	 */
	void exitParenthesizedExpression(CHTLJavaScriptParser.ParenthesizedExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#nullLiteral}.
	 * @param ctx the parse tree
	 */
	void enterNullLiteral(CHTLJavaScriptParser.NullLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#nullLiteral}.
	 * @param ctx the parse tree
	 */
	void exitNullLiteral(CHTLJavaScriptParser.NullLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#booleanLiteral}.
	 * @param ctx the parse tree
	 */
	void enterBooleanLiteral(CHTLJavaScriptParser.BooleanLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#booleanLiteral}.
	 * @param ctx the parse tree
	 */
	void exitBooleanLiteral(CHTLJavaScriptParser.BooleanLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#numericLiteral}.
	 * @param ctx the parse tree
	 */
	void enterNumericLiteral(CHTLJavaScriptParser.NumericLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#numericLiteral}.
	 * @param ctx the parse tree
	 */
	void exitNumericLiteral(CHTLJavaScriptParser.NumericLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#stringLiteral}.
	 * @param ctx the parse tree
	 */
	void enterStringLiteral(CHTLJavaScriptParser.StringLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#stringLiteral}.
	 * @param ctx the parse tree
	 */
	void exitStringLiteral(CHTLJavaScriptParser.StringLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#arrayLiteral}.
	 * @param ctx the parse tree
	 */
	void enterArrayLiteral(CHTLJavaScriptParser.ArrayLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#arrayLiteral}.
	 * @param ctx the parse tree
	 */
	void exitArrayLiteral(CHTLJavaScriptParser.ArrayLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#elementList}.
	 * @param ctx the parse tree
	 */
	void enterElementList(CHTLJavaScriptParser.ElementListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#elementList}.
	 * @param ctx the parse tree
	 */
	void exitElementList(CHTLJavaScriptParser.ElementListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#arrayElement}.
	 * @param ctx the parse tree
	 */
	void enterArrayElement(CHTLJavaScriptParser.ArrayElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#arrayElement}.
	 * @param ctx the parse tree
	 */
	void exitArrayElement(CHTLJavaScriptParser.ArrayElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#objectLiteral}.
	 * @param ctx the parse tree
	 */
	void enterObjectLiteral(CHTLJavaScriptParser.ObjectLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#objectLiteral}.
	 * @param ctx the parse tree
	 */
	void exitObjectLiteral(CHTLJavaScriptParser.ObjectLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#propertyDefinitionList}.
	 * @param ctx the parse tree
	 */
	void enterPropertyDefinitionList(CHTLJavaScriptParser.PropertyDefinitionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#propertyDefinitionList}.
	 * @param ctx the parse tree
	 */
	void exitPropertyDefinitionList(CHTLJavaScriptParser.PropertyDefinitionListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#propertyDefinition}.
	 * @param ctx the parse tree
	 */
	void enterPropertyDefinition(CHTLJavaScriptParser.PropertyDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#propertyDefinition}.
	 * @param ctx the parse tree
	 */
	void exitPropertyDefinition(CHTLJavaScriptParser.PropertyDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#functionExpression}.
	 * @param ctx the parse tree
	 */
	void enterFunctionExpression(CHTLJavaScriptParser.FunctionExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#functionExpression}.
	 * @param ctx the parse tree
	 */
	void exitFunctionExpression(CHTLJavaScriptParser.FunctionExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#generatorExpression}.
	 * @param ctx the parse tree
	 */
	void enterGeneratorExpression(CHTLJavaScriptParser.GeneratorExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#generatorExpression}.
	 * @param ctx the parse tree
	 */
	void exitGeneratorExpression(CHTLJavaScriptParser.GeneratorExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#asyncFunctionExpression}.
	 * @param ctx the parse tree
	 */
	void enterAsyncFunctionExpression(CHTLJavaScriptParser.AsyncFunctionExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#asyncFunctionExpression}.
	 * @param ctx the parse tree
	 */
	void exitAsyncFunctionExpression(CHTLJavaScriptParser.AsyncFunctionExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#asyncGeneratorExpression}.
	 * @param ctx the parse tree
	 */
	void enterAsyncGeneratorExpression(CHTLJavaScriptParser.AsyncGeneratorExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#asyncGeneratorExpression}.
	 * @param ctx the parse tree
	 */
	void exitAsyncGeneratorExpression(CHTLJavaScriptParser.AsyncGeneratorExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#classExpression}.
	 * @param ctx the parse tree
	 */
	void enterClassExpression(CHTLJavaScriptParser.ClassExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#classExpression}.
	 * @param ctx the parse tree
	 */
	void exitClassExpression(CHTLJavaScriptParser.ClassExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#arrowFunction}.
	 * @param ctx the parse tree
	 */
	void enterArrowFunction(CHTLJavaScriptParser.ArrowFunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#arrowFunction}.
	 * @param ctx the parse tree
	 */
	void exitArrowFunction(CHTLJavaScriptParser.ArrowFunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#asyncArrowFunction}.
	 * @param ctx the parse tree
	 */
	void enterAsyncArrowFunction(CHTLJavaScriptParser.AsyncArrowFunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#asyncArrowFunction}.
	 * @param ctx the parse tree
	 */
	void exitAsyncArrowFunction(CHTLJavaScriptParser.AsyncArrowFunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#arrowParameters}.
	 * @param ctx the parse tree
	 */
	void enterArrowParameters(CHTLJavaScriptParser.ArrowParametersContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#arrowParameters}.
	 * @param ctx the parse tree
	 */
	void exitArrowParameters(CHTLJavaScriptParser.ArrowParametersContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#arrowBody}.
	 * @param ctx the parse tree
	 */
	void enterArrowBody(CHTLJavaScriptParser.ArrowBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#arrowBody}.
	 * @param ctx the parse tree
	 */
	void exitArrowBody(CHTLJavaScriptParser.ArrowBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#yieldExpression}.
	 * @param ctx the parse tree
	 */
	void enterYieldExpression(CHTLJavaScriptParser.YieldExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#yieldExpression}.
	 * @param ctx the parse tree
	 */
	void exitYieldExpression(CHTLJavaScriptParser.YieldExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#templateLiteral}.
	 * @param ctx the parse tree
	 */
	void enterTemplateLiteral(CHTLJavaScriptParser.TemplateLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#templateLiteral}.
	 * @param ctx the parse tree
	 */
	void exitTemplateLiteral(CHTLJavaScriptParser.TemplateLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#templateSpans}.
	 * @param ctx the parse tree
	 */
	void enterTemplateSpans(CHTLJavaScriptParser.TemplateSpansContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#templateSpans}.
	 * @param ctx the parse tree
	 */
	void exitTemplateSpans(CHTLJavaScriptParser.TemplateSpansContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#templateSpan}.
	 * @param ctx the parse tree
	 */
	void enterTemplateSpan(CHTLJavaScriptParser.TemplateSpanContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#templateSpan}.
	 * @param ctx the parse tree
	 */
	void exitTemplateSpan(CHTLJavaScriptParser.TemplateSpanContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#templateMiddle}.
	 * @param ctx the parse tree
	 */
	void enterTemplateMiddle(CHTLJavaScriptParser.TemplateMiddleContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#templateMiddle}.
	 * @param ctx the parse tree
	 */
	void exitTemplateMiddle(CHTLJavaScriptParser.TemplateMiddleContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#regularExpressionLiteral}.
	 * @param ctx the parse tree
	 */
	void enterRegularExpressionLiteral(CHTLJavaScriptParser.RegularExpressionLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#regularExpressionLiteral}.
	 * @param ctx the parse tree
	 */
	void exitRegularExpressionLiteral(CHTLJavaScriptParser.RegularExpressionLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#formalParameterList}.
	 * @param ctx the parse tree
	 */
	void enterFormalParameterList(CHTLJavaScriptParser.FormalParameterListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#formalParameterList}.
	 * @param ctx the parse tree
	 */
	void exitFormalParameterList(CHTLJavaScriptParser.FormalParameterListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#formalParameter}.
	 * @param ctx the parse tree
	 */
	void enterFormalParameter(CHTLJavaScriptParser.FormalParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#formalParameter}.
	 * @param ctx the parse tree
	 */
	void exitFormalParameter(CHTLJavaScriptParser.FormalParameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#restParameter}.
	 * @param ctx the parse tree
	 */
	void enterRestParameter(CHTLJavaScriptParser.RestParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#restParameter}.
	 * @param ctx the parse tree
	 */
	void exitRestParameter(CHTLJavaScriptParser.RestParameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bindingElement}.
	 * @param ctx the parse tree
	 */
	void enterBindingElement(CHTLJavaScriptParser.BindingElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bindingElement}.
	 * @param ctx the parse tree
	 */
	void exitBindingElement(CHTLJavaScriptParser.BindingElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bindingPattern}.
	 * @param ctx the parse tree
	 */
	void enterBindingPattern(CHTLJavaScriptParser.BindingPatternContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bindingPattern}.
	 * @param ctx the parse tree
	 */
	void exitBindingPattern(CHTLJavaScriptParser.BindingPatternContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#objectBindingPattern}.
	 * @param ctx the parse tree
	 */
	void enterObjectBindingPattern(CHTLJavaScriptParser.ObjectBindingPatternContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#objectBindingPattern}.
	 * @param ctx the parse tree
	 */
	void exitObjectBindingPattern(CHTLJavaScriptParser.ObjectBindingPatternContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bindingPropertyList}.
	 * @param ctx the parse tree
	 */
	void enterBindingPropertyList(CHTLJavaScriptParser.BindingPropertyListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bindingPropertyList}.
	 * @param ctx the parse tree
	 */
	void exitBindingPropertyList(CHTLJavaScriptParser.BindingPropertyListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bindingProperty}.
	 * @param ctx the parse tree
	 */
	void enterBindingProperty(CHTLJavaScriptParser.BindingPropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bindingProperty}.
	 * @param ctx the parse tree
	 */
	void exitBindingProperty(CHTLJavaScriptParser.BindingPropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#arrayBindingPattern}.
	 * @param ctx the parse tree
	 */
	void enterArrayBindingPattern(CHTLJavaScriptParser.ArrayBindingPatternContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#arrayBindingPattern}.
	 * @param ctx the parse tree
	 */
	void exitArrayBindingPattern(CHTLJavaScriptParser.ArrayBindingPatternContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bindingElementList}.
	 * @param ctx the parse tree
	 */
	void enterBindingElementList(CHTLJavaScriptParser.BindingElementListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bindingElementList}.
	 * @param ctx the parse tree
	 */
	void exitBindingElementList(CHTLJavaScriptParser.BindingElementListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bindingElision}.
	 * @param ctx the parse tree
	 */
	void enterBindingElision(CHTLJavaScriptParser.BindingElisionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bindingElision}.
	 * @param ctx the parse tree
	 */
	void exitBindingElision(CHTLJavaScriptParser.BindingElisionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#functionBody}.
	 * @param ctx the parse tree
	 */
	void enterFunctionBody(CHTLJavaScriptParser.FunctionBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#functionBody}.
	 * @param ctx the parse tree
	 */
	void exitFunctionBody(CHTLJavaScriptParser.FunctionBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#initializer}.
	 * @param ctx the parse tree
	 */
	void enterInitializer(CHTLJavaScriptParser.InitializerContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#initializer}.
	 * @param ctx the parse tree
	 */
	void exitInitializer(CHTLJavaScriptParser.InitializerContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#bindingIdentifier}.
	 * @param ctx the parse tree
	 */
	void enterBindingIdentifier(CHTLJavaScriptParser.BindingIdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#bindingIdentifier}.
	 * @param ctx the parse tree
	 */
	void exitBindingIdentifier(CHTLJavaScriptParser.BindingIdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#identifier}.
	 * @param ctx the parse tree
	 */
	void enterIdentifier(CHTLJavaScriptParser.IdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#identifier}.
	 * @param ctx the parse tree
	 */
	void exitIdentifier(CHTLJavaScriptParser.IdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#identifierName}.
	 * @param ctx the parse tree
	 */
	void enterIdentifierName(CHTLJavaScriptParser.IdentifierNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#identifierName}.
	 * @param ctx the parse tree
	 */
	void exitIdentifierName(CHTLJavaScriptParser.IdentifierNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#reservedWord}.
	 * @param ctx the parse tree
	 */
	void enterReservedWord(CHTLJavaScriptParser.ReservedWordContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#reservedWord}.
	 * @param ctx the parse tree
	 */
	void exitReservedWord(CHTLJavaScriptParser.ReservedWordContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#keyword}.
	 * @param ctx the parse tree
	 */
	void enterKeyword(CHTLJavaScriptParser.KeywordContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#keyword}.
	 * @param ctx the parse tree
	 */
	void exitKeyword(CHTLJavaScriptParser.KeywordContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLJavaScriptParser#futureReservedWord}.
	 * @param ctx the parse tree
	 */
	void enterFutureReservedWord(CHTLJavaScriptParser.FutureReservedWordContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLJavaScriptParser#futureReservedWord}.
	 * @param ctx the parse tree
	 */
	void exitFutureReservedWord(CHTLJavaScriptParser.FutureReservedWordContext ctx);
}