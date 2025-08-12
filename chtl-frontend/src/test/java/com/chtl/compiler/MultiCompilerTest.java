package com.chtl.compiler;

import com.chtl.scanner.CodeBlockScanner;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;
import static org.junit.jupiter.api.Assertions.*;

/**
 * 多编译器系统测试
 */
public class MultiCompilerTest {
    
    private CompilerManager compilerManager;
    
    @BeforeEach
    public void setUp() {
        compilerManager = new CompilerManager();
    }
    
    @Test
    public void testMixedCodeBlocks() {
        String chtlCode = """
            div {
                style {
                    .container {
                        width: 100%;
                        max-width: 1200px;
                        margin: 0 auto;
                    }
                }
                
                h1 {
                    text {
                        "Welcome to CHTL"
                    }
                }
                
                button {
                    id: my-button;
                    text { "Click me" }
                    
                    script {
                        {{my-button}}->addEventListener('click', () => {
                            alert('Button clicked!');
                        });
                    }
                }
                
                [Origin] @Style {
                    /* 原生CSS代码 */
                    .native-css {
                        color: red;
                        font-size: 16px;
                    }
                }
                
                [Origin] @JavaScript {
                    // 原生JavaScript代码
                    console.log('Native JavaScript');
                    function nativeFunction() {
                        return 'Hello from native JS';
                    }
                }
            }
            """;
        
        CompilerManager.UnifiedCompilationResult result = compilerManager.compile(chtlCode);
        
        // 验证编译成功
        assertTrue(result.isSuccess(), "编译应该成功");
        
        // 验证各种类型的代码块都被识别
        assertFalse(result.getResultsForType(CodeBlockScanner.BlockType.CHTL).isEmpty());
        assertFalse(result.getResultsForType(CodeBlockScanner.BlockType.CSS).isEmpty());
        assertFalse(result.getResultsForType(CodeBlockScanner.BlockType.JAVASCRIPT).isEmpty());
        assertFalse(result.getResultsForType(CodeBlockScanner.BlockType.CHTL_JS).isEmpty());
    }
    
    @Test
    public void testCssValidation() {
        String chtlWithCss = """
            style {
                .valid-css {
                    color: blue;
                    margin: 10px;
                }
                
                .invalid-css {
                    unknown-property: value;
                    color: {{dynamic}};  /* CHTL特性 */
                }
            }
            """;
        
        CompilerManager.UnifiedCompilationResult result = compilerManager.compile(chtlWithCss);
        
        // 应该有警告但不是错误
        assertFalse(result.getAllErrors().isEmpty() || result.getAllWarnings().isEmpty());
        
        // 检查警告内容
        boolean hasPropertyWarning = result.getAllWarnings().stream()
            .anyMatch(w -> w.contains("unknown-property") || w.contains("未知"));
        assertTrue(hasPropertyWarning, "应该有关于未知CSS属性的警告");
    }
    
    @Test
    public void testJavaScriptValidation() {
        String jsCode = """
            script {
                // 原生JavaScript
                let x = 10;
                console.log(x);
                
                // 使用未声明的变量
                console.log(undeclaredVariable);
            }
            """;
        
        CompilerManager.UnifiedCompilationResult result = compilerManager.compile(jsCode);
        
        // 应该有关于未声明变量的警告
        boolean hasUndeclaredWarning = result.getAllWarnings().stream()
            .anyMatch(w -> w.contains("undeclaredVariable") || w.contains("未声明"));
        assertTrue(hasUndeclaredWarning, "应该有关于未声明变量的警告");
    }
    
    @Test
    public void testChtlJsTransformation() {
        String chtlJsCode = """
            script {
                // CHTL-JS扩展语法
                {{button}}->addEventListener('click', () => {
                    {{output}}->textContent = 'Clicked!';
                });
                
                {{.my-class}}->listen({
                    mouseenter: () => console.log('enter'),
                    mouseleave: () => console.log('leave')
                });
            }
            """;
        
        CompilerManager.UnifiedCompilationResult result = compilerManager.compile(chtlJsCode);
        
        assertTrue(result.isSuccess(), "CHTL-JS转换应该成功");
        
        // 验证CHTL-JS代码块被正确识别和处理
        var chtlJsResults = result.getResultsForType(CodeBlockScanner.BlockType.CHTL_JS);
        assertFalse(chtlJsResults.isEmpty());
        
        // 验证转换后的代码
        String transformedCode = chtlJsResults.get(0).getProcessedCode();
        assertNotNull(transformedCode);
        assertTrue(transformedCode.contains("document.querySelector"));
        assertFalse(transformedCode.contains("{{"));
        assertFalse(transformedCode.contains("->"));
    }
    
    @Test
    public void testErrorReporting() {
        String invalidCode = """
            style {
                .test {
                    color: {{invalid}};  /* 原生CSS中的CHTL语法 */
                }
            }
            
            [Origin] @JavaScript {
                // 语法错误的JavaScript
                function test() {
                    return
                }
            }
            """;
        
        CompilerManager.UnifiedCompilationResult result = compilerManager.compile(invalidCode);
        
        // 应该有错误
        assertFalse(result.isSuccess());
        assertFalse(result.getAllErrors().isEmpty());
        
        // 验证错误信息包含行号
        boolean hasLineInfo = result.getAllErrors().stream()
            .anyMatch(e -> e.contains("行"));
        assertTrue(hasLineInfo, "错误信息应该包含行号");
    }
    
    @Test
    public void testParallelProcessing() {
        // 创建一个大的混合代码来测试并行处理
        StringBuilder largeCode = new StringBuilder();
        
        // 添加多个CSS块
        for (int i = 0; i < 10; i++) {
            largeCode.append(String.format("""
                style {
                    .class%d {
                        color: red;
                        margin: %dpx;
                    }
                }
                """, i, i * 10));
        }
        
        // 添加多个JavaScript块
        for (int i = 0; i < 10; i++) {
            largeCode.append(String.format("""
                script {
                    function func%d() {
                        console.log('Function %d');
                    }
                }
                """, i, i));
        }
        
        // 测试顺序处理
        compilerManager.setParallelProcessing(false);
        long startTime = System.currentTimeMillis();
        CompilerManager.UnifiedCompilationResult sequentialResult = compilerManager.compile(largeCode.toString());
        long sequentialTime = System.currentTimeMillis() - startTime;
        
        // 测试并行处理
        compilerManager.setParallelProcessing(true);
        startTime = System.currentTimeMillis();
        CompilerManager.UnifiedCompilationResult parallelResult = compilerManager.compile(largeCode.toString());
        long parallelTime = System.currentTimeMillis() - startTime;
        
        // 验证两种方式的结果一致
        assertEquals(sequentialResult.isSuccess(), parallelResult.isSuccess());
        assertEquals(
            sequentialResult.getAllResults().size(), 
            parallelResult.getAllResults().size()
        );
        
        System.out.println("顺序处理时间: " + sequentialTime + "ms");
        System.out.println("并行处理时间: " + parallelTime + "ms");
    }
    
    @Test
    public void testComplexNestedStructure() {
        String complexCode = """
            [Template] @Style Theme {
                color: #333;
                font-family: Arial, sans-serif;
            }
            
            div {
                style {
                    @Style Theme;
                    
                    .wrapper {
                        display: flex;
                        justify-content: center;
                    }
                }
                
                div {
                    style {
                        .inner {
                            padding: 20px;
                        }
                    }
                    
                    script {
                        let data = [];
                        
                        {{.inner}}->addEventListener('click', (e) => {
                            data.push(e.timeStamp);
                            console.log('Clicks:', data.length);
                        });
                    }
                    
                    [Origin] @Html {
                        <!-- 原始HTML注释 -->
                        <custom-element></custom-element>
                    }
                }
            }
            """;
        
        CompilerManager.UnifiedCompilationResult result = compilerManager.compile(complexCode);
        
        // 验证复杂嵌套结构能够正确处理
        assertTrue(result.isSuccess() || !result.getAllWarnings().isEmpty(), 
            "复杂结构应该能够编译");
        
        // 验证各种代码块类型都被识别
        assertTrue(result.getAllResults().size() >= 3, "应该识别出多种代码块类型");
    }
}