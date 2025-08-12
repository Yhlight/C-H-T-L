package com.chtl.javascript;

import java.util.*;
import java.util.regex.*;

/**
 * CHTL-JS编译器 - 处理CHTL的JavaScript扩展语法
 * 将CHTL-JS语法转换为标准JavaScript
 */
public class ChtlJsCompiler {
    
    public static class ChtlJsCompilationResult {
        private boolean success = true;
        private String transformedJs;
        private List<String> errors = new ArrayList<>();
        private List<String> warnings = new ArrayList<>();
        private Map<String, String> selectorMappings = new HashMap<>();
        
        // Getters and setters
        public boolean isSuccess() { return success; }
        public void setSuccess(boolean success) { this.success = success; }
        public String getTransformedJs() { return transformedJs; }
        public void setTransformedJs(String js) { this.transformedJs = js; }
        public List<String> getErrors() { return errors; }
        public List<String> getWarnings() { return warnings; }
        public Map<String, String> getSelectorMappings() { return selectorMappings; }
        
        public void addError(String error) {
            errors.add(error);
            success = false;
        }
        
        public void addWarning(String warning) {
            warnings.add(warning);
        }
        
        public void addSelectorMapping(String selector, String jsCode) {
            selectorMappings.put(selector, jsCode);
        }
    }
    
    private boolean validateAfterTransform = true;
    private JavaScriptCompiler jsCompiler;
    
    public ChtlJsCompiler() {
        this.jsCompiler = new JavaScriptCompiler(true, false); // 不检查CHTL特性
    }
    
    public ChtlJsCompiler(boolean validateAfterTransform) {
        this.validateAfterTransform = validateAfterTransform;
        this.jsCompiler = new JavaScriptCompiler(validateAfterTransform, false);
    }
    
    /**
     * 编译CHTL-JS代码
     */
    public ChtlJsCompilationResult compile(String chtlJsCode) {
        ChtlJsCompilationResult result = new ChtlJsCompilationResult();
        
        try {
            // 转换CHTL-JS语法到标准JavaScript
            String transformedJs = transformChtlJs(chtlJsCode, result);
            
            if (!result.isSuccess()) {
                return result;
            }
            
            result.setTransformedJs(transformedJs);
            
            // 验证转换后的JavaScript
            if (validateAfterTransform) {
                JavaScriptCompiler.JsCompilationResult jsResult = jsCompiler.compile(transformedJs);
                
                if (!jsResult.isSuccess()) {
                    for (String error : jsResult.getErrors()) {
                        result.addError("转换后的JavaScript错误: " + error);
                    }
                }
                
                for (String warning : jsResult.getWarnings()) {
                    result.addWarning("转换后的JavaScript警告: " + warning);
                }
            }
            
        } catch (Exception e) {
            result.addError("CHTL-JS编译失败: " + e.getMessage());
        }
        
        return result;
    }
    
    /**
     * 转换CHTL-JS语法到标准JavaScript
     */
    private String transformChtlJs(String code, ChtlJsCompilationResult result) {
        String transformed = code;
        
        // 1. 转换增强选择器 {{selector}}
        transformed = transformEnhancedSelectors(transformed, result);
        
        // 2. 转换箭头操作符 ->
        transformed = transformArrowOperator(transformed, result);
        
        // 3. 转换listen方法
        transformed = transformListenMethod(transformed, result);
        
        // 4. 转换delegate方法
        transformed = transformDelegateMethod(transformed, result);
        
        // 5. 转换animate函数
        transformed = transformAnimateFunction(transformed, result);
        
        return transformed;
    }
    
    /**
     * 转换增强选择器 {{selector}} -> document.querySelector(selector)
     */
    private String transformEnhancedSelectors(String code, ChtlJsCompilationResult result) {
        Pattern pattern = Pattern.compile("\\{\\{([^}]+)\\}\\}");
        Matcher matcher = pattern.matcher(code);
        StringBuffer sb = new StringBuffer();
        
        while (matcher.find()) {
            String selector = matcher.group(1).trim();
            String jsCode = generateSelectorCode(selector);
            
            result.addSelectorMapping(selector, jsCode);
            matcher.appendReplacement(sb, jsCode);
        }
        
        matcher.appendTail(sb);
        return sb.toString();
    }
    
    /**
     * 生成选择器对应的JavaScript代码
     */
    private String generateSelectorCode(String selector) {
        // 检查是否有索引访问，如 button[0]
        Pattern indexPattern = Pattern.compile("^([^\\[]+)\\[(\\d+)\\]$");
        Matcher indexMatcher = indexPattern.matcher(selector);
        
        if (indexMatcher.matches()) {
            String baseSelector = indexMatcher.group(1);
            String index = indexMatcher.group(2);
            return String.format("document.querySelectorAll('%s')[%s]", 
                normalizeSelector(baseSelector), index);
        }
        
        // 检查选择器类型
        if (selector.startsWith(".") || selector.startsWith("#") || selector.contains(" ")) {
            // CSS选择器
            return String.format("document.querySelector('%s')", selector);
        } else {
            // 可能是ID或类名的简写
            // 优先查找ID，然后是类名
            return String.format("(document.getElementById('%s') || document.querySelector('.%s'))", 
                selector, selector);
        }
    }
    
    /**
     * 规范化选择器
     */
    private String normalizeSelector(String selector) {
        if (!selector.startsWith(".") && !selector.startsWith("#")) {
            // 如果是元素名，直接返回
            if (isHtmlElement(selector)) {
                return selector;
            }
            // 否则假定是类名
            return "." + selector;
        }
        return selector;
    }
    
    /**
     * 检查是否是HTML元素名
     */
    private boolean isHtmlElement(String name) {
        String[] elements = {"div", "span", "p", "a", "button", "input", "form", 
                            "h1", "h2", "h3", "h4", "h5", "h6", "ul", "ol", "li",
                            "table", "tr", "td", "th", "img", "video", "audio"};
        
        for (String elem : elements) {
            if (elem.equalsIgnoreCase(name)) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * 转换箭头操作符 -> 为 .
     */
    private String transformArrowOperator(String code, ChtlJsCompilationResult result) {
        // 简单替换 -> 为 .
        // 注意：这里需要更复杂的解析来避免错误替换箭头函数的 =>
        Pattern pattern = Pattern.compile("(\\))\\s*->\\s*([a-zA-Z_$][a-zA-Z0-9_$]*)");
        Matcher matcher = pattern.matcher(code);
        StringBuffer sb = new StringBuffer();
        
        while (matcher.find()) {
            String replacement = matcher.group(1) + "." + matcher.group(2);
            matcher.appendReplacement(sb, replacement);
        }
        
        matcher.appendTail(sb);
        return sb.toString();
    }
    
    /**
     * 转换listen方法
     */
    private String transformListenMethod(String code, ChtlJsCompilationResult result) {
        Pattern pattern = Pattern.compile("\\.listen\\s*\\(\\s*\\{([^}]+)\\}\\s*\\)");
        Matcher matcher = pattern.matcher(code);
        StringBuffer sb = new StringBuffer();
        
        while (matcher.find()) {
            String events = matcher.group(1);
            String jsCode = generateListenCode(events);
            matcher.appendReplacement(sb, jsCode);
        }
        
        matcher.appendTail(sb);
        return sb.toString();
    }
    
    /**
     * 生成listen方法对应的JavaScript代码
     */
    private String generateListenCode(String events) {
        StringBuilder sb = new StringBuilder();
        sb.append("(function(elem) {\n");
        
        // 解析事件映射
        String[] eventPairs = events.split(",");
        for (String pair : eventPairs) {
            String[] parts = pair.trim().split(":");
            if (parts.length == 2) {
                String eventName = parts[0].trim();
                String handler = parts[1].trim();
                
                sb.append(String.format("    elem.addEventListener('%s', %s);\n", 
                    eventName, handler));
            }
        }
        
        sb.append("    return elem;\n");
        sb.append("})(this)");
        
        return sb.toString();
    }
    
    /**
     * 转换delegate方法
     */
    private String transformDelegateMethod(String code, ChtlJsCompilationResult result) {
        Pattern pattern = Pattern.compile("\\.delegate\\s*\\(\\s*\\{([^}]+)\\}\\s*\\)");
        Matcher matcher = pattern.matcher(code);
        StringBuffer sb = new StringBuffer();
        
        while (matcher.find()) {
            String config = matcher.group(1);
            String jsCode = generateDelegateCode(config);
            matcher.appendReplacement(sb, jsCode);
        }
        
        matcher.appendTail(sb);
        return sb.toString();
    }
    
    /**
     * 生成delegate方法对应的JavaScript代码
     */
    private String generateDelegateCode(String config) {
        // 解析delegate配置
        // 简化实现，实际需要更复杂的解析
        StringBuilder sb = new StringBuilder();
        sb.append("(function(parent) {\n");
        sb.append("    // 事件委托实现\n");
        sb.append("    parent.addEventListener('click', function(e) {\n");
        sb.append("        var target = e.target;\n");
        sb.append("        // 检查目标是否匹配选择器\n");
        sb.append("        // 执行相应的处理函数\n");
        sb.append("    });\n");
        sb.append("    return parent;\n");
        sb.append("})(this)");
        
        return sb.toString();
    }
    
    /**
     * 转换animate函数
     */
    private String transformAnimateFunction(String code, ChtlJsCompilationResult result) {
        Pattern pattern = Pattern.compile("animate\\s*\\(\\s*\\{([^}]+)\\}\\s*\\)");
        Matcher matcher = pattern.matcher(code);
        StringBuffer sb = new StringBuffer();
        
        while (matcher.find()) {
            String config = matcher.group(1);
            String jsCode = generateAnimateCode(config);
            matcher.appendReplacement(sb, jsCode);
        }
        
        matcher.appendTail(sb);
        return sb.toString();
    }
    
    /**
     * 生成animate函数对应的JavaScript代码
     */
    private String generateAnimateCode(String config) {
        StringBuilder sb = new StringBuilder();
        sb.append("(function() {\n");
        sb.append("    // 使用requestAnimationFrame实现动画\n");
        sb.append("    var config = {").append(config).append("};\n");
        sb.append("    var startTime = null;\n");
        sb.append("    var duration = config.duration || 1000;\n");
        sb.append("    \n");
        sb.append("    function animate(timestamp) {\n");
        sb.append("        if (!startTime) startTime = timestamp;\n");
        sb.append("        var progress = (timestamp - startTime) / duration;\n");
        sb.append("        \n");
        sb.append("        if (progress < 1) {\n");
        sb.append("            // 应用动画效果\n");
        sb.append("            requestAnimationFrame(animate);\n");
        sb.append("        } else {\n");
        sb.append("            // 动画完成\n");
        sb.append("            if (config.callback) config.callback();\n");
        sb.append("        }\n");
        sb.append("    }\n");
        sb.append("    \n");
        sb.append("    requestAnimationFrame(animate);\n");
        sb.append("})()");
        
        return sb.toString();
    }
}