package com.chtl.javascript;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.util.*;

/**
 * JavaScript原生编译器 - 用于验证和处理原生JavaScript代码
 */
public class JavaScriptCompiler {
    
    public static class JsCompilationResult {
        private boolean success;
        private String processedJs;
        private List<String> errors;
        private List<String> warnings;
        private boolean hasErrors;
        
        public JsCompilationResult() {
            this.errors = new ArrayList<>();
            this.warnings = new ArrayList<>();
            this.success = true;
            this.hasErrors = false;
        }
        
        // Getters and setters
        public boolean isSuccess() { return success && !hasErrors; }
        public void setSuccess(boolean success) { this.success = success; }
        public String getProcessedJs() { return processedJs; }
        public void setProcessedJs(String js) { this.processedJs = js; }
        public List<String> getErrors() { return errors; }
        public List<String> getWarnings() { return warnings; }
        
        public void addError(String error) {
            errors.add(error);
            hasErrors = true;
        }
        
        public void addWarning(String warning) {
            warnings.add(warning);
        }
    }
    
    private boolean validateSyntax = true;
    private boolean checkChtlFeatures = true;
    
    public JavaScriptCompiler() {
    }
    
    public JavaScriptCompiler(boolean validateSyntax, boolean checkChtlFeatures) {
        this.validateSyntax = validateSyntax;
        this.checkChtlFeatures = checkChtlFeatures;
    }
    
    /**
     * 编译JavaScript代码
     */
    public JsCompilationResult compile(String jsCode) {
        JsCompilationResult result = new JsCompilationResult();
        
        try {
            // 检查是否包含CHTL特性
            if (checkChtlFeatures && containsChtlFeatures(jsCode)) {
                result.addError("JavaScript代码包含CHTL扩展语法，请使用CHTL-JS编译器");
                return result;
            }
            
            if (validateSyntax) {
                // 创建ANTLR输入流
                ANTLRInputStream input = new ANTLRInputStream(jsCode);
                
                // 创建词法分析器
                JavaScriptLexer lexer = new JavaScriptLexer(input);
                CommonTokenStream tokens = new CommonTokenStream(lexer);
                
                // 创建语法分析器
                JavaScriptParser parser = new JavaScriptParser(tokens);
                
                // 添加错误监听器
                parser.removeErrorListeners();
                parser.addErrorListener(new BaseErrorListener() {
                    @Override
                    public void syntaxError(Recognizer<?, ?> recognizer, Object offendingSymbol,
                                           int line, int charPositionInLine, String msg,
                                           RecognitionException e) {
                        result.addError(String.format("JavaScript语法错误 [%d:%d]: %s", 
                            line, charPositionInLine, msg));
                    }
                });
                
                // 解析JavaScript
                ParseTree tree = parser.program();
                
                // 如果有语法错误，返回
                if (!result.isSuccess()) {
                    return result;
                }
                
                // 执行语义检查
                performSemanticChecks(tree, result);
            }
            
            // 处理代码（例如：格式化、优化等）
            String processedJs = processJavaScript(jsCode, result);
            result.setProcessedJs(processedJs);
            
        } catch (Exception e) {
            result.addError("JavaScript编译失败: " + e.getMessage());
        }
        
        return result;
    }
    
    /**
     * 检查是否包含CHTL特性
     */
    private boolean containsChtlFeatures(String code) {
        // 检查CHTL-JS特有的语法
        String[] chtlPatterns = {
            "\\{\\{[^}]+\\}\\}",           // {{selector}}
            "->\\s*addEventListener",       // -> 操作符
            "->\\s*listen",                // listen方法
            "->\\s*delegate",              // delegate方法
            "\\banimate\\s*\\(",           // animate函数
            "->\\s*textContent",           // -> 链式调用
            "->\\s*style",                 // -> 样式访问
        };
        
        for (String pattern : chtlPatterns) {
            if (code.matches(".*" + pattern + ".*")) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * 执行语义检查
     */
    private void performSemanticChecks(ParseTree tree, JsCompilationResult result) {
        // 创建语义检查访问器
        JavaScriptSemanticChecker checker = new JavaScriptSemanticChecker(result);
        checker.visit(tree);
    }
    
    /**
     * 处理JavaScript代码
     */
    private String processJavaScript(String code, JsCompilationResult result) {
        // 这里可以添加代码处理逻辑，如：
        // - 代码格式化
        // - 简单的优化
        // - 代码转换
        
        // 目前直接返回原始代码
        return code;
    }
    
    /**
     * JavaScript语义检查器
     */
    private static class JavaScriptSemanticChecker extends JavaScriptParserBaseVisitor<Void> {
        private final JsCompilationResult result;
        private final Set<String> declaredVariables = new HashSet<>();
        private final Set<String> usedVariables = new HashSet<>();
        private final Stack<Set<String>> scopeStack = new Stack<>();
        
        public JavaScriptSemanticChecker(JsCompilationResult result) {
            this.result = result;
            scopeStack.push(new HashSet<>()); // 全局作用域
        }
        
        @Override
        public Void visitVariableDeclaration(JavaScriptParser.VariableDeclarationContext ctx) {
            // 检查变量声明
            if (ctx.assignable() != null) {
                String varName = ctx.assignable().getText();
                
                // 检查重复声明（简化版）
                if (getCurrentScope().contains(varName)) {
                    result.addWarning("变量 '" + varName + "' 可能被重复声明");
                }
                
                getCurrentScope().add(varName);
                declaredVariables.add(varName);
            }
            
            return super.visitVariableDeclaration(ctx);
        }
        
        @Override
        public Void visitFunctionDeclaration(JavaScriptParser.FunctionDeclarationContext ctx) {
            // 进入新的函数作用域
            scopeStack.push(new HashSet<>());
            
            // 添加函数参数到作用域
            if (ctx.formalParameterList() != null) {
                // 处理参数...
            }
            
            // 访问函数体
            super.visitFunctionDeclaration(ctx);
            
            // 离开函数作用域
            scopeStack.pop();
            
            return null;
        }
        
        @Override
        public Void visitSingleExpression(JavaScriptParser.SingleExpressionContext ctx) {
            // 检查标识符使用
            if (ctx.Identifier() != null) {
                String varName = ctx.Identifier().getText();
                usedVariables.add(varName);
                
                // 检查未声明的变量（简化版）
                if (!isVariableDeclared(varName) && !isGlobalObject(varName)) {
                    result.addWarning("可能使用了未声明的变量: " + varName);
                }
            }
            
            return super.visitSingleExpression(ctx);
        }
        
        private Set<String> getCurrentScope() {
            return scopeStack.peek();
        }
        
        private boolean isVariableDeclared(String varName) {
            // 检查所有作用域
            for (Set<String> scope : scopeStack) {
                if (scope.contains(varName)) {
                    return true;
                }
            }
            return declaredVariables.contains(varName);
        }
        
        private boolean isGlobalObject(String name) {
            // 常见的全局对象
            String[] globals = {
                "window", "document", "console", "Array", "Object", "String",
                "Number", "Boolean", "Date", "Math", "JSON", "Promise",
                "setTimeout", "setInterval", "alert", "parseInt", "parseFloat"
            };
            
            for (String global : globals) {
                if (global.equals(name)) {
                    return true;
                }
            }
            
            return false;
        }
    }
}