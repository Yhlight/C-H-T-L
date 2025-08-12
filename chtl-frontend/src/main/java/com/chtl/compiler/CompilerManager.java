package com.chtl.compiler;

import com.chtl.scanner.CodeBlockScanner;
import com.chtl.scanner.CodeBlockScanner.CodeBlock;
import com.chtl.css.CssCompiler;
import com.chtl.javascript.JavaScriptCompiler;
import com.chtl.javascript.ChtlJsCompiler;
import java.util.*;

/**
 * 编译器管理器 - 协调各个编译器的工作
 * 负责扫描代码块并分发给相应的编译器处理
 */
public class CompilerManager {
    
    /**
     * 统一的编译结果
     */
    public static class UnifiedCompilationResult {
        private boolean success = true;
        private Map<CodeBlockScanner.BlockType, List<BlockCompilationResult>> results = new HashMap<>();
        private List<String> globalErrors = new ArrayList<>();
        private List<String> globalWarnings = new ArrayList<>();
        
        public boolean isSuccess() { return success; }
        public void setSuccess(boolean success) { this.success = success; }
        
        public void addBlockResult(CodeBlockScanner.BlockType type, BlockCompilationResult result) {
            results.computeIfAbsent(type, k -> new ArrayList<>()).add(result);
            if (!result.isSuccess()) {
                success = false;
            }
        }
        
        public List<BlockCompilationResult> getResultsForType(CodeBlockScanner.BlockType type) {
            return results.getOrDefault(type, new ArrayList<>());
        }
        
        public Map<CodeBlockScanner.BlockType, List<BlockCompilationResult>> getAllResults() {
            return results;
        }
        
        public void addGlobalError(String error) {
            globalErrors.add(error);
            success = false;
        }
        
        public void addGlobalWarning(String warning) {
            globalWarnings.add(warning);
        }
        
        public List<String> getGlobalErrors() { return globalErrors; }
        public List<String> getGlobalWarnings() { return globalWarnings; }
        
        /**
         * 获取所有错误信息
         */
        public List<String> getAllErrors() {
            List<String> allErrors = new ArrayList<>(globalErrors);
            
            for (List<BlockCompilationResult> blockResults : results.values()) {
                for (BlockCompilationResult result : blockResults) {
                    allErrors.addAll(result.getErrors());
                }
            }
            
            return allErrors;
        }
        
        /**
         * 获取所有警告信息
         */
        public List<String> getAllWarnings() {
            List<String> allWarnings = new ArrayList<>(globalWarnings);
            
            for (List<BlockCompilationResult> blockResults : results.values()) {
                for (BlockCompilationResult result : blockResults) {
                    allWarnings.addAll(result.getWarnings());
                }
            }
            
            return allWarnings;
        }
    }
    
    /**
     * 单个代码块的编译结果
     */
    public static class BlockCompilationResult {
        private CodeBlock block;
        private boolean success = true;
        private String processedCode;
        private List<String> errors = new ArrayList<>();
        private List<String> warnings = new ArrayList<>();
        private Map<String, Object> metadata = new HashMap<>();
        
        public BlockCompilationResult(CodeBlock block) {
            this.block = block;
        }
        
        // Getters and setters
        public CodeBlock getBlock() { return block; }
        public boolean isSuccess() { return success; }
        public void setSuccess(boolean success) { this.success = success; }
        public String getProcessedCode() { return processedCode; }
        public void setProcessedCode(String code) { this.processedCode = code; }
        public List<String> getErrors() { return errors; }
        public List<String> getWarnings() { return warnings; }
        public Map<String, Object> getMetadata() { return metadata; }
        
        public void addError(String error) {
            errors.add(error);
            success = false;
        }
        
        public void addWarning(String warning) {
            warnings.add(warning);
        }
        
        public void addMetadata(String key, Object value) {
            metadata.put(key, value);
        }
    }
    
    private CssCompiler cssCompiler;
    private JavaScriptCompiler jsCompiler;
    private ChtlJsCompiler chtlJsCompiler;
    private boolean parallelProcessing = false;
    
    public CompilerManager() {
        this.cssCompiler = new CssCompiler();
        this.jsCompiler = new JavaScriptCompiler();
        this.chtlJsCompiler = new ChtlJsCompiler();
    }
    
    public CompilerManager(boolean parallelProcessing) {
        this();
        this.parallelProcessing = parallelProcessing;
    }
    
    /**
     * 编译包含多种代码块的源代码
     */
    public UnifiedCompilationResult compile(String sourceCode) {
        UnifiedCompilationResult result = new UnifiedCompilationResult();
        
        try {
            // 1. 扫描代码块
            CodeBlockScanner scanner = new CodeBlockScanner(sourceCode);
            List<CodeBlock> blocks = scanner.scan();
            
            if (blocks.isEmpty()) {
                result.addGlobalWarning("未找到任何代码块");
                return result;
            }
            
            // 2. 对代码块分类
            Map<CodeBlockScanner.BlockType, List<CodeBlock>> categorizedBlocks = categorizeBlocks(blocks);
            
            // 3. 编译各类代码块
            if (parallelProcessing) {
                compileInParallel(categorizedBlocks, result);
            } else {
                compileSequentially(categorizedBlocks, result);
            }
            
        } catch (Exception e) {
            result.addGlobalError("编译管理器错误: " + e.getMessage());
        }
        
        return result;
    }
    
    /**
     * 对代码块进行分类
     */
    private Map<CodeBlockScanner.BlockType, List<CodeBlock>> categorizeBlocks(List<CodeBlock> blocks) {
        Map<CodeBlockScanner.BlockType, List<CodeBlock>> categorized = new HashMap<>();
        
        for (CodeBlock block : blocks) {
            categorized.computeIfAbsent(block.getType(), k -> new ArrayList<>()).add(block);
        }
        
        return categorized;
    }
    
    /**
     * 顺序编译代码块
     */
    private void compileSequentially(Map<CodeBlockScanner.BlockType, List<CodeBlock>> categorizedBlocks,
                                    UnifiedCompilationResult result) {
        // 按照特定顺序处理不同类型的代码块
        // 1. 先处理CHTL代码块（可能定义模板等）
        processBlocks(categorizedBlocks.get(CodeBlockScanner.BlockType.CHTL), 
                     CodeBlockScanner.BlockType.CHTL, result);
        
        // 2. 处理CSS代码块
        processBlocks(categorizedBlocks.get(CodeBlockScanner.BlockType.CSS), 
                     CodeBlockScanner.BlockType.CSS, result);
        
        // 3. 处理JavaScript代码块
        processBlocks(categorizedBlocks.get(CodeBlockScanner.BlockType.JAVASCRIPT), 
                     CodeBlockScanner.BlockType.JAVASCRIPT, result);
        
        // 4. 处理CHTL-JS代码块
        processBlocks(categorizedBlocks.get(CodeBlockScanner.BlockType.CHTL_JS), 
                     CodeBlockScanner.BlockType.CHTL_JS, result);
        
        // 5. 处理原始HTML代码块
        processBlocks(categorizedBlocks.get(CodeBlockScanner.BlockType.RAW_HTML), 
                     CodeBlockScanner.BlockType.RAW_HTML, result);
    }
    
    /**
     * 并行编译代码块
     */
    private void compileInParallel(Map<CodeBlockScanner.BlockType, List<CodeBlock>> categorizedBlocks,
                                  UnifiedCompilationResult result) {
        // 简化实现：使用Java 8的并行流
        categorizedBlocks.entrySet().parallelStream().forEach(entry -> {
            processBlocks(entry.getValue(), entry.getKey(), result);
        });
    }
    
    /**
     * 处理特定类型的代码块
     */
    private void processBlocks(List<CodeBlock> blocks, CodeBlockScanner.BlockType type,
                              UnifiedCompilationResult result) {
        if (blocks == null || blocks.isEmpty()) {
            return;
        }
        
        for (CodeBlock block : blocks) {
            BlockCompilationResult blockResult = compileBlock(block);
            result.addBlockResult(type, blockResult);
        }
    }
    
    /**
     * 编译单个代码块
     */
    private BlockCompilationResult compileBlock(CodeBlock block) {
        BlockCompilationResult result = new BlockCompilationResult(block);
        
        try {
            switch (block.getType()) {
                case CSS:
                    compileCssBlock(block, result);
                    break;
                    
                case JAVASCRIPT:
                    compileJavaScriptBlock(block, result);
                    break;
                    
                case CHTL_JS:
                    compileChtlJsBlock(block, result);
                    break;
                    
                case CHTL:
                    // CHTL块由主编译器处理，这里只记录
                    result.setProcessedCode(block.getContent());
                    result.addMetadata("type", "chtl");
                    break;
                    
                case RAW_HTML:
                    // 原始HTML直接通过
                    result.setProcessedCode(block.getContent());
                    result.addMetadata("type", "raw_html");
                    break;
                    
                default:
                    result.addError("未知的代码块类型: " + block.getType());
            }
            
        } catch (Exception e) {
            result.addError("编译代码块失败: " + e.getMessage());
        }
        
        return result;
    }
    
    /**
     * 编译CSS代码块
     */
    private void compileCssBlock(CodeBlock block, BlockCompilationResult result) {
        CssCompiler.CssCompilationResult cssResult = cssCompiler.compile(block.getContent());
        
        result.setSuccess(cssResult.isSuccess());
        result.setProcessedCode(cssResult.getProcessedCss());
        
        for (String error : cssResult.getErrors()) {
            result.addError(formatError("CSS", block, error));
        }
        
        for (String warning : cssResult.getWarnings()) {
            result.addWarning(formatWarning("CSS", block, warning));
        }
        
        result.addMetadata("type", "css");
        result.addMetadata("ast", cssResult.getAst());
    }
    
    /**
     * 编译JavaScript代码块
     */
    private void compileJavaScriptBlock(CodeBlock block, BlockCompilationResult result) {
        JavaScriptCompiler.JsCompilationResult jsResult = jsCompiler.compile(block.getContent());
        
        result.setSuccess(jsResult.isSuccess());
        result.setProcessedCode(jsResult.getProcessedJs());
        
        for (String error : jsResult.getErrors()) {
            result.addError(formatError("JavaScript", block, error));
        }
        
        for (String warning : jsResult.getWarnings()) {
            result.addWarning(formatWarning("JavaScript", block, warning));
        }
        
        result.addMetadata("type", "javascript");
    }
    
    /**
     * 编译CHTL-JS代码块
     */
    private void compileChtlJsBlock(CodeBlock block, BlockCompilationResult result) {
        ChtlJsCompiler.ChtlJsCompilationResult chtlJsResult = chtlJsCompiler.compile(block.getContent());
        
        result.setSuccess(chtlJsResult.isSuccess());
        result.setProcessedCode(chtlJsResult.getTransformedJs());
        
        for (String error : chtlJsResult.getErrors()) {
            result.addError(formatError("CHTL-JS", block, error));
        }
        
        for (String warning : chtlJsResult.getWarnings()) {
            result.addWarning(formatWarning("CHTL-JS", block, warning));
        }
        
        result.addMetadata("type", "chtl_js");
        result.addMetadata("selectorMappings", chtlJsResult.getSelectorMappings());
    }
    
    /**
     * 格式化错误信息
     */
    private String formatError(String compilerType, CodeBlock block, String error) {
        return String.format("[%s] 行 %d-%d: %s", 
            compilerType, block.getStartLine(), block.getEndLine(), error);
    }
    
    /**
     * 格式化警告信息
     */
    private String formatWarning(String compilerType, CodeBlock block, String warning) {
        return String.format("[%s] 行 %d-%d: %s", 
            compilerType, block.getStartLine(), block.getEndLine(), warning);
    }
    
    // Getters and setters for compilers
    public void setCssCompiler(CssCompiler cssCompiler) {
        this.cssCompiler = cssCompiler;
    }
    
    public void setJsCompiler(JavaScriptCompiler jsCompiler) {
        this.jsCompiler = jsCompiler;
    }
    
    public void setChtlJsCompiler(ChtlJsCompiler chtlJsCompiler) {
        this.chtlJsCompiler = chtlJsCompiler;
    }
    
    public void setParallelProcessing(boolean parallelProcessing) {
        this.parallelProcessing = parallelProcessing;
    }
}