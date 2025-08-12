package com.chtl.css;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.util.*;

/**
 * CSS原生编译器 - 用于验证和处理原生CSS代码
 */
public class CssCompiler {
    
    public static class CssCompilationResult {
        private boolean success;
        private String processedCss;
        private List<String> errors;
        private List<String> warnings;
        private CssAst ast;
        
        public CssCompilationResult() {
            this.errors = new ArrayList<>();
            this.warnings = new ArrayList<>();
            this.success = true;
        }
        
        // Getters and setters
        public boolean isSuccess() { return success; }
        public void setSuccess(boolean success) { this.success = success; }
        public String getProcessedCss() { return processedCss; }
        public void setProcessedCss(String css) { this.processedCss = css; }
        public List<String> getErrors() { return errors; }
        public List<String> getWarnings() { return warnings; }
        public CssAst getAst() { return ast; }
        public void setAst(CssAst ast) { this.ast = ast; }
        
        public void addError(String error) {
            errors.add(error);
            success = false;
        }
        
        public void addWarning(String warning) {
            warnings.add(warning);
        }
    }
    
    /**
     * 简化的CSS AST结构
     */
    public static class CssAst {
        private List<CssRule> rules = new ArrayList<>();
        
        public void addRule(CssRule rule) {
            rules.add(rule);
        }
        
        public List<CssRule> getRules() {
            return rules;
        }
    }
    
    public static class CssRule {
        private String selector;
        private Map<String, String> properties = new HashMap<>();
        
        public CssRule(String selector) {
            this.selector = selector;
        }
        
        public void addProperty(String name, String value) {
            properties.put(name, value);
        }
        
        public String getSelector() { return selector; }
        public Map<String, String> getProperties() { return properties; }
    }
    
    private boolean validateProperties = true;
    private boolean optimizeCss = false;
    
    public CssCompiler() {
    }
    
    public CssCompiler(boolean validateProperties, boolean optimizeCss) {
        this.validateProperties = validateProperties;
        this.optimizeCss = optimizeCss;
    }
    
    /**
     * 编译CSS代码
     */
    public CssCompilationResult compile(String cssCode) {
        CssCompilationResult result = new CssCompilationResult();
        
        try {
            // 创建ANTLR输入流
            ANTLRInputStream input = new ANTLRInputStream(cssCode);
            
            // 创建词法分析器
            CssLexer lexer = new CssLexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            
            // 创建语法分析器
            CssParser parser = new CssParser(tokens);
            
            // 添加错误监听器
            parser.removeErrorListeners();
            parser.addErrorListener(new BaseErrorListener() {
                @Override
                public void syntaxError(Recognizer<?, ?> recognizer, Object offendingSymbol,
                                       int line, int charPositionInLine, String msg,
                                       RecognitionException e) {
                    result.addError(String.format("CSS语法错误 [%d:%d]: %s", 
                        line, charPositionInLine, msg));
                }
            });
            
            // 解析CSS
            ParseTree tree = parser.stylesheet();
            
            // 如果有语法错误，返回
            if (!result.isSuccess()) {
                return result;
            }
            
            // 构建AST
            CssAstBuilder astBuilder = new CssAstBuilder();
            CssAst ast = astBuilder.visit(tree);
            result.setAst(ast);
            
            // 验证CSS
            if (validateProperties) {
                validateCss(ast, result);
            }
            
            // 优化CSS（如果启用）
            if (optimizeCss && result.isSuccess()) {
                optimizeCss(ast, result);
            }
            
            // 生成处理后的CSS
            String processedCss = generateCss(ast);
            result.setProcessedCss(processedCss);
            
        } catch (Exception e) {
            result.addError("CSS编译失败: " + e.getMessage());
        }
        
        return result;
    }
    
    /**
     * CSS AST构建器
     */
    private class CssAstBuilder extends CssParserBaseVisitor<CssAst> {
        private CssAst ast = new CssAst();
        
        @Override
        public CssAst visitStylesheet(CssParser.StylesheetContext ctx) {
            for (CssParser.StatementContext stmt : ctx.statement()) {
                visit(stmt);
            }
            return ast;
        }
        
        @Override
        public CssAst visitRuleset(CssParser.RulesetContext ctx) {
            String selector = ctx.selectorList().getText();
            CssRule rule = new CssRule(selector);
            
            for (CssParser.DeclarationContext decl : ctx.declaration()) {
                String property = decl.property().getText();
                String value = decl.value().getText();
                rule.addProperty(property, value);
            }
            
            ast.addRule(rule);
            return ast;
        }
        
        // 其他visit方法...
    }
    
    /**
     * 验证CSS
     */
    private void validateCss(CssAst ast, CssCompilationResult result) {
        CssValidator validator = new CssValidator();
        
        for (CssRule rule : ast.getRules()) {
            // 验证选择器
            if (!validator.isValidSelector(rule.getSelector())) {
                result.addWarning("可能无效的选择器: " + rule.getSelector());
            }
            
            // 验证属性
            for (Map.Entry<String, String> prop : rule.getProperties().entrySet()) {
                if (!validator.isValidProperty(prop.getKey())) {
                    result.addWarning("未知的CSS属性: " + prop.getKey());
                }
                
                if (!validator.isValidValue(prop.getKey(), prop.getValue())) {
                    result.addWarning(String.format("属性 '%s' 的值可能无效: %s", 
                        prop.getKey(), prop.getValue()));
                }
            }
        }
    }
    
    /**
     * 优化CSS
     */
    private void optimizeCss(CssAst ast, CssCompilationResult result) {
        // 合并相同选择器的规则
        Map<String, CssRule> mergedRules = new HashMap<>();
        
        for (CssRule rule : ast.getRules()) {
            String selector = rule.getSelector();
            if (mergedRules.containsKey(selector)) {
                // 合并属性
                CssRule existingRule = mergedRules.get(selector);
                existingRule.getProperties().putAll(rule.getProperties());
            } else {
                mergedRules.put(selector, rule);
            }
        }
        
        // 更新AST
        ast.getRules().clear();
        ast.getRules().addAll(mergedRules.values());
        
        result.addWarning("CSS已优化：合并了重复的选择器");
    }
    
    /**
     * 生成CSS代码
     */
    private String generateCss(CssAst ast) {
        StringBuilder css = new StringBuilder();
        
        for (CssRule rule : ast.getRules()) {
            css.append(rule.getSelector()).append(" {\n");
            
            for (Map.Entry<String, String> prop : rule.getProperties().entrySet()) {
                css.append("    ")
                   .append(prop.getKey())
                   .append(": ")
                   .append(prop.getValue())
                   .append(";\n");
            }
            
            css.append("}\n\n");
        }
        
        return css.toString();
    }
}

/**
 * CSS验证器
 */
class CssValidator {
    private static final Set<String> VALID_PROPERTIES = new HashSet<>(Arrays.asList(
        "color", "background-color", "background", "font-size", "font-family",
        "font-weight", "margin", "padding", "border", "width", "height",
        "display", "position", "top", "left", "right", "bottom", "z-index",
        "opacity", "visibility", "overflow", "text-align", "line-height",
        "text-decoration", "transform", "transition", "animation", "flex",
        "grid", "box-shadow", "text-shadow", "border-radius", "cursor",
        "float", "clear", "vertical-align", "white-space", "word-wrap",
        "content", "list-style", "outline", "box-sizing", "min-width",
        "max-width", "min-height", "max-height", "flex-direction", "justify-content",
        "align-items", "align-content", "flex-wrap", "order", "flex-grow",
        "flex-shrink", "flex-basis", "grid-template-columns", "grid-template-rows",
        "gap", "grid-gap", "grid-column", "grid-row", "filter", "backdrop-filter"
    ));
    
    public boolean isValidSelector(String selector) {
        // 简单的选择器验证
        return selector != null && !selector.trim().isEmpty();
    }
    
    public boolean isValidProperty(String property) {
        return VALID_PROPERTIES.contains(property.toLowerCase()) || 
               property.startsWith("-webkit-") || 
               property.startsWith("-moz-") || 
               property.startsWith("-ms-") || 
               property.startsWith("-o-") ||
               property.startsWith("--"); // CSS变量
    }
    
    public boolean isValidValue(String property, String value) {
        // 简化的值验证
        if (value == null || value.trim().isEmpty()) {
            return false;
        }
        
        // 检查一些常见的无效值
        if (value.contains("{{") || value.contains("}}")) {
            // 包含CHTL语法，对于原生CSS来说是无效的
            return false;
        }
        
        return true;
    }
}