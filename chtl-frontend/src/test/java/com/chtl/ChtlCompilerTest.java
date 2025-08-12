package com.chtl;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Basic tests for CHTL compiler
 */
public class ChtlCompilerTest {
    
    private ChtlCompiler compiler;
    
    @BeforeEach
    public void setUp() {
        compiler = new ChtlCompiler();
    }
    
    @Test
    public void testSimpleHtml() {
        String chtl = "body { text { \"Hello World\" } }";
        
        CompilationResult result = compiler.compileString(chtl, "test.chtl");
        
        assertTrue(result.isSuccess());
        assertFalse(result.hasErrors());
        assertNotNull(result.getGeneratedCode());
        
        String html = result.getGeneratedCode().getCompleteHtml();
        assertTrue(html.contains("Hello World"));
        assertTrue(html.contains("<body>"));
        assertTrue(html.contains("</body>"));
    }
    
    @Test
    public void testElementWithAttributes() {
        String chtl = """
            div {
                id: test-div;
                class: container;
                
                text {
                    "Test content"
                }
            }
            """;
        
        CompilationResult result = compiler.compileString(chtl, "test.chtl");
        
        assertTrue(result.isSuccess());
        String html = result.getGeneratedCode().getCompleteHtml();
        assertTrue(html.contains("id=\"test-div\""));
        assertTrue(html.contains("class=\"container\""));
        assertTrue(html.contains("Test content"));
    }
    
    @Test
    public void testStyleGeneration() {
        String chtl = """
            div {
                style {
                    .auto-class {
                        color: red;
                        font-size: 16px;
                    }
                }
                
                text { "Styled text" }
            }
            """;
        
        CompilationResult result = compiler.compileString(chtl, "test.chtl");
        
        assertTrue(result.isSuccess());
        String html = result.getGeneratedCode().getCompleteHtml();
        assertTrue(html.contains("class=\"auto-class\""));
        assertTrue(html.contains(".auto-class"));
        assertTrue(html.contains("color: red"));
        assertTrue(html.contains("font-size: 16px"));
    }
    
    @Test
    public void testTemplate() {
        String chtl = """
            [Template] @Element Card {
                div {
                    style {
                        .card {
                            border: 1px solid black;
                        }
                    }
                    
                    text { "Card content" }
                }
            }
            
            body {
                @Element Card;
            }
            """;
        
        CompilationResult result = compiler.compileString(chtl, "test.chtl");
        
        assertTrue(result.isSuccess());
        String html = result.getGeneratedCode().getCompleteHtml();
        assertTrue(html.contains("class=\"card\""));
        assertTrue(html.contains("Card content"));
    }
    
    @Test
    public void testSyntaxError() {
        String chtl = "div { { } }"; // Invalid syntax
        
        CompilationResult result = compiler.compileString(chtl, "test.chtl");
        
        assertFalse(result.isSuccess());
        assertTrue(result.hasErrors());
    }
    
    @Test
    public void testSemanticError() {
        String chtl = """
            div {
                id: duplicate;
            }
            
            span {
                id: duplicate; // Duplicate ID
            }
            """;
        
        CompilationResult result = compiler.compileString(chtl, "test.chtl");
        
        assertFalse(result.isSuccess());
        assertTrue(result.hasErrors());
        assertTrue(result.getErrors().stream()
            .anyMatch(e -> e.contains("Duplicate ID")));
    }
}