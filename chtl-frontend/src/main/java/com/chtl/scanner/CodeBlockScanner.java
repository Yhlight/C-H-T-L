package com.chtl.scanner;

import java.util.*;
import java.util.regex.*;

/**
 * 代码块扫描器 - 负责识别和切割不同类型的代码块
 * 支持：CHTL、CSS、JavaScript、CHTL-JS
 */
public class CodeBlockScanner {
    
    public enum BlockType {
        CHTL,        // CHTL代码块
        CSS,         // 原生CSS代码块
        JAVASCRIPT,  // 原生JavaScript代码块
        CHTL_JS,     // CHTL扩展的JavaScript代码块
        RAW_HTML,    // 原始HTML代码块
        UNKNOWN
    }
    
    public static class CodeBlock {
        private BlockType type;
        private String content;
        private int startLine;
        private int startColumn;
        private int endLine;
        private int endColumn;
        private Map<String, String> metadata;
        
        public CodeBlock(BlockType type, String content, int startLine, int startColumn) {
            this.type = type;
            this.content = content;
            this.startLine = startLine;
            this.startColumn = startColumn;
            this.metadata = new HashMap<>();
        }
        
        // Getters and setters
        public BlockType getType() { return type; }
        public String getContent() { return content; }
        public int getStartLine() { return startLine; }
        public int getStartColumn() { return startColumn; }
        public int getEndLine() { return endLine; }
        public void setEndLine(int endLine) { this.endLine = endLine; }
        public int getEndColumn() { return endColumn; }
        public void setEndColumn(int endColumn) { this.endColumn = endColumn; }
        public Map<String, String> getMetadata() { return metadata; }
        
        public void addMetadata(String key, String value) {
            metadata.put(key, value);
        }
    }
    
    private String source;
    private List<CodeBlock> blocks;
    private int currentLine = 1;
    private int currentColumn = 1;
    private int currentPos = 0;
    
    public CodeBlockScanner(String source) {
        this.source = source;
        this.blocks = new ArrayList<>();
    }
    
    /**
     * 扫描源代码，返回所有代码块
     */
    public List<CodeBlock> scan() {
        blocks.clear();
        currentLine = 1;
        currentColumn = 1;
        currentPos = 0;
        
        while (currentPos < source.length()) {
            skipWhitespace();
            
            if (currentPos >= source.length()) {
                break;
            }
            
            CodeBlock block = scanNextBlock();
            if (block != null) {
                blocks.add(block);
            }
        }
        
        return blocks;
    }
    
    /**
     * 扫描下一个代码块
     */
    private CodeBlock scanNextBlock() {
        // 检查是否是特殊标记的代码块
        if (lookAhead("[Origin]")) {
            return scanOriginBlock();
        } else if (isInStyleContext()) {
            return scanCSSBlock();
        } else if (isInScriptContext()) {
            return scanJavaScriptBlock();
        } else {
            return scanCHTLBlock();
        }
    }
    
    /**
     * 扫描[Origin]原始代码块
     */
    private CodeBlock scanOriginBlock() {
        int startLine = currentLine;
        int startColumn = currentColumn;
        
        // 跳过 [Origin]
        advance(8);
        skipWhitespace();
        
        // 获取类型 (@Html, @Style, @JavaScript)
        String originType = "";
        if (lookAhead("@Html")) {
            originType = "@Html";
            advance(5);
        } else if (lookAhead("@Style")) {
            originType = "@Style";
            advance(6);
        } else if (lookAhead("@JavaScript")) {
            originType = "@JavaScript";
            advance(11);
        }
        
        skipWhitespace();
        
        // 查找代码块内容
        String content = scanBracedContent();
        
        BlockType blockType = BlockType.RAW_HTML;
        if (originType.equals("@Style")) {
            blockType = BlockType.CSS;
        } else if (originType.equals("@JavaScript")) {
            blockType = BlockType.JAVASCRIPT;
        }
        
        CodeBlock block = new CodeBlock(blockType, content, startLine, startColumn);
        block.addMetadata("origin", "true");
        block.addMetadata("originType", originType);
        block.setEndLine(currentLine);
        block.setEndColumn(currentColumn);
        
        return block;
    }
    
    /**
     * 扫描CSS代码块（在style { } 内部）
     */
    private CodeBlock scanCSSBlock() {
        int startLine = currentLine;
        int startColumn = currentColumn;
        
        // 查找style关键字
        int styleStart = findPreviousKeyword("style");
        if (styleStart == -1) {
            return null;
        }
        
        String content = scanBracedContent();
        
        // 分析内容，判断是原生CSS还是CHTL扩展的CSS
        boolean hasCHTLFeatures = detectCHTLCSSFeatures(content);
        
        CodeBlock block = new CodeBlock(
            hasCHTLFeatures ? BlockType.CHTL : BlockType.CSS,
            content,
            startLine,
            startColumn
        );
        
        block.setEndLine(currentLine);
        block.setEndColumn(currentColumn);
        
        return block;
    }
    
    /**
     * 扫描JavaScript代码块（在script { } 内部）
     */
    private CodeBlock scanJavaScriptBlock() {
        int startLine = currentLine;
        int startColumn = currentColumn;
        
        String content = scanBracedContent();
        
        // 检测是否包含CHTL-JS特性
        boolean hasCHTLJSFeatures = detectCHTLJSFeatures(content);
        
        CodeBlock block = new CodeBlock(
            hasCHTLJSFeatures ? BlockType.CHTL_JS : BlockType.JAVASCRIPT,
            content,
            startLine,
            startColumn
        );
        
        block.setEndLine(currentLine);
        block.setEndColumn(currentColumn);
        
        return block;
    }
    
    /**
     * 扫描CHTL代码块
     */
    private CodeBlock scanCHTLBlock() {
        int startLine = currentLine;
        int startColumn = currentColumn;
        
        // CHTL代码块通常以元素名、模板声明等开始
        StringBuilder content = new StringBuilder();
        int braceDepth = 0;
        boolean inBlock = false;
        
        while (currentPos < source.length()) {
            char c = source.charAt(currentPos);
            
            if (c == '{') {
                braceDepth++;
                inBlock = true;
            } else if (c == '}') {
                braceDepth--;
                if (braceDepth == 0 && inBlock) {
                    content.append(c);
                    advance(1);
                    break;
                }
            }
            
            // 检查是否进入了style或script上下文
            if (inBlock && braceDepth > 0) {
                if (lookAhead("style") && peekNextNonWhitespaceChar() == '{') {
                    // 结束当前CHTL块
                    break;
                } else if (lookAhead("script") && peekNextNonWhitespaceChar() == '{') {
                    // 结束当前CHTL块
                    break;
                }
            }
            
            content.append(c);
            advance(1);
            
            // 如果还没进入块，遇到分号可能是单行语句
            if (!inBlock && c == ';') {
                break;
            }
        }
        
        CodeBlock block = new CodeBlock(BlockType.CHTL, content.toString(), startLine, startColumn);
        block.setEndLine(currentLine);
        block.setEndColumn(currentColumn);
        
        return block;
    }
    
    /**
     * 检测CSS内容是否包含CHTL特性
     */
    private boolean detectCHTLCSSFeatures(String content) {
        // 检查CHTL CSS特性
        Pattern[] chtlPatterns = {
            Pattern.compile("@Style\\s+\\w+"),          // @Style引用
            Pattern.compile("&\\s*(::|:)?"),            // & 符号
            Pattern.compile("\\{\\{[^}]+\\}\\}"),       // {{选择器}}
            Pattern.compile("delete\\s+"),              // delete关键字
            Pattern.compile("inherit\\s+@Style")        // inherit语句
        };
        
        for (Pattern pattern : chtlPatterns) {
            if (pattern.matcher(content).find()) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * 检测JavaScript内容是否包含CHTL-JS特性
     */
    private boolean detectCHTLJSFeatures(String content) {
        // 检查CHTL-JS特性
        Pattern[] chtlJsPatterns = {
            Pattern.compile("\\{\\{[^}]+\\}\\}"),                    // {{选择器}}
            Pattern.compile("->\\s*(addEventListener|listen)"),      // -> 操作符
            Pattern.compile("->\\s*delegate\\s*\\("),                // 事件委托
            Pattern.compile("animate\\s*\\(\\s*\\{"),                // animate函数
            Pattern.compile("\\{\\{[^}]+\\}\\}\\s*->")              // 增强选择器链式调用
        };
        
        for (Pattern pattern : chtlJsPatterns) {
            if (pattern.matcher(content).find()) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * 扫描花括号包围的内容
     */
    private String scanBracedContent() {
        StringBuilder content = new StringBuilder();
        int braceDepth = 0;
        
        // 跳过前面的空白和 {
        while (currentPos < source.length() && source.charAt(currentPos) != '{') {
            advance(1);
        }
        
        if (currentPos < source.length()) {
            advance(1); // 跳过 {
            braceDepth = 1;
        }
        
        while (currentPos < source.length() && braceDepth > 0) {
            char c = source.charAt(currentPos);
            
            if (c == '{') {
                braceDepth++;
            } else if (c == '}') {
                braceDepth--;
                if (braceDepth == 0) {
                    advance(1); // 跳过最后的 }
                    break;
                }
            } else if (c == '"' || c == '\'') {
                // 处理字符串，避免字符串内的括号干扰
                content.append(c);
                advance(1);
                scanString(c, content);
                continue;
            } else if (c == '/' && currentPos + 1 < source.length()) {
                char next = source.charAt(currentPos + 1);
                if (next == '/') {
                    // 单行注释
                    content.append(c);
                    advance(1);
                    scanLineComment(content);
                    continue;
                } else if (next == '*') {
                    // 多行注释
                    content.append(c);
                    advance(1);
                    scanBlockComment(content);
                    continue;
                }
            }
            
            content.append(c);
            advance(1);
        }
        
        return content.toString();
    }
    
    /**
     * 扫描字符串
     */
    private void scanString(char quote, StringBuilder builder) {
        while (currentPos < source.length()) {
            char c = source.charAt(currentPos);
            builder.append(c);
            advance(1);
            
            if (c == quote) {
                break;
            } else if (c == '\\' && currentPos < source.length()) {
                // 转义字符
                builder.append(source.charAt(currentPos));
                advance(1);
            }
        }
    }
    
    /**
     * 扫描单行注释
     */
    private void scanLineComment(StringBuilder builder) {
        while (currentPos < source.length()) {
            char c = source.charAt(currentPos);
            if (c == '\n') {
                break;
            }
            builder.append(c);
            advance(1);
        }
    }
    
    /**
     * 扫描多行注释
     */
    private void scanBlockComment(StringBuilder builder) {
        while (currentPos < source.length()) {
            char c = source.charAt(currentPos);
            builder.append(c);
            advance(1);
            
            if (c == '*' && currentPos < source.length() && source.charAt(currentPos) == '/') {
                builder.append('/');
                advance(1);
                break;
            }
        }
    }
    
    /**
     * 辅助方法
     */
    private void advance(int count) {
        for (int i = 0; i < count && currentPos < source.length(); i++) {
            if (source.charAt(currentPos) == '\n') {
                currentLine++;
                currentColumn = 1;
            } else {
                currentColumn++;
            }
            currentPos++;
        }
    }
    
    private void skipWhitespace() {
        while (currentPos < source.length() && Character.isWhitespace(source.charAt(currentPos))) {
            advance(1);
        }
    }
    
    private boolean lookAhead(String text) {
        if (currentPos + text.length() > source.length()) {
            return false;
        }
        return source.substring(currentPos, currentPos + text.length()).equals(text);
    }
    
    private char peekNextNonWhitespaceChar() {
        int pos = currentPos;
        while (pos < source.length()) {
            char c = source.charAt(pos);
            if (!Character.isWhitespace(c)) {
                return c;
            }
            pos++;
        }
        return '\0';
    }
    
    private boolean isInStyleContext() {
        // 简化实现：检查前面是否有 style 关键字
        int searchStart = Math.max(0, currentPos - 100);
        String context = source.substring(searchStart, currentPos);
        return context.matches(".*\\bstyle\\s*$");
    }
    
    private boolean isInScriptContext() {
        // 简化实现：检查前面是否有 script 关键字
        int searchStart = Math.max(0, currentPos - 100);
        String context = source.substring(searchStart, currentPos);
        return context.matches(".*\\bscript\\s*$");
    }
    
    private int findPreviousKeyword(String keyword) {
        int searchStart = Math.max(0, currentPos - 100);
        String context = source.substring(searchStart, currentPos);
        int index = context.lastIndexOf(keyword);
        return index >= 0 ? searchStart + index : -1;
    }
}