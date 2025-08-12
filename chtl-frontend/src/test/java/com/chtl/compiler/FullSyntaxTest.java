package com.chtl.compiler;

import com.chtl.parser.ChtlCompiler;
import com.chtl.CompilationResult;
import com.chtl.ast.*;
import com.chtl.imports.ImportManager;
import com.chtl.cmod.CmodPackager;
import com.chtl.cmod.CmodLoader;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.io.TempDir;

import java.nio.file.Path;
import java.nio.file.Files;
import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

/**
 * 完整语法测试
 */
public class FullSyntaxTest {
    
    private ChtlCompiler compiler;
    private ImportManager importManager;
    private CmodPackager packager;
    private CmodLoader loader;
    
    @TempDir
    Path tempDir;
    
    @BeforeEach
    void setUp() {
        compiler = new ChtlCompiler();
        importManager = new ImportManager();
        packager = new CmodPackager();
        loader = new CmodLoader();
    }
    
    @Test
    void testInfoAndExportBlocks() throws IOException {
        String content = """
            [Info]
            {
                name = "test-module";
                version = "1.0.0";
                description = "测试模块";
                author = "Test Author";
            }
            
            [Export]
            {
                @Style TestStyle;
                @Element TestElement;
            }
            """;
        
        Path testFile = tempDir.resolve("test-info.chtl");
        Files.writeString(testFile, content);
        
        CompilationResult result = compiler.compile(testFile.toString());
        assertTrue(result.isSuccess());
        
        ChtlFileNode ast = (ChtlFileNode) result.getAst();
        assertNotNull(ast);
        
        // 验证Info节点
        InfoNode infoNode = findNode(ast, InfoNode.class);
        assertNotNull(infoNode);
        assertEquals("test-module", infoNode.getName());
        assertEquals("1.0.0", infoNode.getVersion());
        
        // 验证Export节点
        ExportNode exportNode = findNode(ast, ExportNode.class);
        assertNotNull(exportNode);
        assertEquals(2, exportNode.getExports().size());
    }
    
    @Test
    void testNamespaceWithTemplates() throws IOException {
        String content = """
            [Namespace] TestNS
            {
                [Template] @Style MyStyle {
                    .test {
                        color: red;
                    }
                }
                
                [Template] @Element MyElement {
                    div class="test" { "Hello" }
                }
            }
            """;
        
        Path testFile = tempDir.resolve("test-namespace.chtl");
        Files.writeString(testFile, content);
        
        CompilationResult result = compiler.compile(testFile.toString());
        assertTrue(result.isSuccess());
        
        ChtlFileNode ast = (ChtlFileNode) result.getAst();
        NamespaceNode namespaceNode = findNode(ast, NamespaceNode.class);
        assertNotNull(namespaceNode);
        assertEquals("TestNS", namespaceNode.getName());
        assertEquals(2, namespaceNode.getDeclarations().size());
    }
    
    @Test
    void testConfigurationBlock() throws IOException {
        String content = """
            [Configuration]
            {
                charset = "UTF-8";
                title = "Test Page";
                
                name {
                    id {
                        prefix = "test";
                        style = "kebab-case";
                    }
                    class {
                        prefix = "test";
                    }
                }
            }
            """;
        
        Path testFile = tempDir.resolve("test-config.chtl");
        Files.writeString(testFile, content);
        
        CompilationResult result = compiler.compile(testFile.toString());
        assertTrue(result.isSuccess());
        
        ChtlFileNode ast = (ChtlFileNode) result.getAst();
        ConfigurationNode configNode = findNode(ast, ConfigurationNode.class);
        assertNotNull(configNode);
        assertEquals("UTF-8", configNode.getProperty("charset"));
        assertNotNull(configNode.getNameGroup("name"));
    }
    
    @Test
    void testOriginBlocks() throws IOException {
        String content = """
            [Origin] @Html TestHtml {
                <div>Raw HTML</div>
            }
            
            [Origin] @Style {
                .raw { color: blue; }
            }
            
            [Origin] @JavaScript {
                console.log('Raw JS');
            }
            """;
        
        Path testFile = tempDir.resolve("test-origin.chtl");
        Files.writeString(testFile, content);
        
        CompilationResult result = compiler.compile(testFile.toString());
        assertTrue(result.isSuccess());
        
        ChtlFileNode ast = (ChtlFileNode) result.getAst();
        var originNodes = findAllNodes(ast, OriginNode.class);
        assertEquals(3, originNodes.size());
        
        // 验证命名的Origin块
        OriginNode namedOrigin = originNodes.stream()
            .filter(OriginNode::hasName)
            .findFirst()
            .orElse(null);
        assertNotNull(namedOrigin);
        assertEquals("TestHtml", namedOrigin.getName());
    }
    
    @Test
    void testEnhancedCssWithAmpersand() throws IOException {
        String content = """
            div class="test" {
                @local style {
                    & {
                        color: red;
                    }
                    &:hover {
                        color: blue;
                    }
                    & .child {
                        color: green;
                    }
                }
            }
            """;
        
        Path testFile = tempDir.resolve("test-css-ampersand.chtl");
        Files.writeString(testFile, content);
        
        CompilationResult result = compiler.compile(testFile.toString());
        assertTrue(result.isSuccess());
        
        // 生成HTML验证&符号处理
        String html = result.getGeneratedCode();
        assertNotNull(html);
        assertTrue(html.contains(".test {") || html.contains("div {"));
        assertTrue(html.contains(":hover"));
    }
    
    @Test
    void testDeleteInsertSpecialize() throws IOException {
        String content = """
            [Template] @Element TestTemplate {
                div {
                    p class="old" { "Original" }
                    
                    @delete .old;
                    
                    @insert before .target {
                        span { "Inserted" }
                    }
                    
                    @specialize .existing {
                        class += " enhanced";
                    }
                }
            }
            """;
        
        Path testFile = tempDir.resolve("test-modifications.chtl");
        Files.writeString(testFile, content);
        
        CompilationResult result = compiler.compile(testFile.toString());
        assertTrue(result.isSuccess());
        
        ChtlFileNode ast = (ChtlFileNode) result.getAst();
        TemplateNode template = findNode(ast, TemplateNode.class);
        assertNotNull(template);
        
        // 验证删除、插入和特殊化节点
        ElementNode div = (ElementNode) template.getContent().get(0);
        var deleteNodes = findAllNodesInTree(div, DeleteNode.class);
        var insertNodes = findAllNodesInTree(div, InsertNode.class);
        var specializeNodes = findAllNodesInTree(div, SpecializationNode.class);
        
        assertFalse(deleteNodes.isEmpty());
        assertFalse(insertNodes.isEmpty());
        assertFalse(specializeNodes.isEmpty());
    }
    
    @Test
    void testCmodPackaging() throws IOException {
        // 创建CMOD结构
        Path moduleDir = tempDir.resolve("TestModule");
        Path srcDir = moduleDir.resolve("src");
        Path infoDir = moduleDir.resolve("info");
        
        Files.createDirectories(srcDir);
        Files.createDirectories(infoDir);
        
        // 创建info文件
        String infoContent = """
            [Info]
            {
                name = "TestModule";
                version = "1.0.0";
                description = "Test Module";
                author = "Test";
                license = "MIT";
                dependencies = "";
                category = "test";
                minCHTLVersion = "1.0.0";
                maxCHTLVersion = "2.0.0";
            }
            """;
        Files.writeString(infoDir.resolve("TestModule.chtl"), infoContent);
        
        // 创建主模块文件
        String moduleContent = """
            [Template] @Element TestElement {
                div { "Test Module Content" }
            }
            """;
        Files.writeString(srcDir.resolve("TestModule.chtl"), moduleContent);
        
        // 打包
        CmodPackager.PackageResult packageResult = packager.packageModule(moduleDir, tempDir);
        assertTrue(packageResult.isSuccess());
        assertNotNull(packageResult.getOutputPath());
        
        // 加载打包的模块
        Path cmodFile = Path.of(packageResult.getOutputPath());
        assertTrue(Files.exists(cmodFile));
        
        CmodLoader.LoadedModule loadedModule = loader.loadModule(cmodFile);
        assertNotNull(loadedModule);
        assertEquals("TestModule", loadedModule.getName());
        assertEquals("1.0.0", loadedModule.getVersion());
    }
    
    @Test
    void testImportWithCircularDependencyDetection() throws IOException {
        // 创建相互导入的文件
        String file1Content = """
            [Import] @Chtl from "./file2.chtl";
            div { "File 1" }
            """;
        
        String file2Content = """
            [Import] @Chtl from "./file1.chtl";
            div { "File 2" }
            """;
        
        Path file1 = tempDir.resolve("file1.chtl");
        Path file2 = tempDir.resolve("file2.chtl");
        
        Files.writeString(file1, file1Content);
        Files.writeString(file2, file2Content);
        
        // 处理导入
        ImportManager.ImportResult importResult = importManager.processImports(file1);
        
        // 应该检测到循环依赖
        assertFalse(importResult.getErrors().isEmpty());
        assertTrue(importResult.getErrors().stream()
            .anyMatch(error -> error.getMessage().contains("循环依赖")));
    }
    
    // 辅助方法
    @SuppressWarnings("unchecked")
    private <T extends ChtlNode> T findNode(ChtlFileNode ast, Class<T> nodeClass) {
        for (ChtlNode node : ast.getDeclarations()) {
            if (nodeClass.isInstance(node)) {
                return (T) node;
            }
        }
        return null;
    }
    
    private <T extends ChtlNode> java.util.List<T> findAllNodes(ChtlFileNode ast, Class<T> nodeClass) {
        java.util.List<T> nodes = new java.util.ArrayList<>();
        for (ChtlNode node : ast.getDeclarations()) {
            if (nodeClass.isInstance(node)) {
                nodes.add(nodeClass.cast(node));
            }
        }
        return nodes;
    }
    
    private <T extends ChtlNode> java.util.List<T> findAllNodesInTree(ChtlNode root, Class<T> nodeClass) {
        java.util.List<T> nodes = new java.util.ArrayList<>();
        findNodesRecursive(root, nodeClass, nodes);
        return nodes;
    }
    
    private <T extends ChtlNode> void findNodesRecursive(ChtlNode node, Class<T> nodeClass, java.util.List<T> result) {
        if (nodeClass.isInstance(node)) {
            result.add(nodeClass.cast(node));
        }
        
        // 递归查找子节点
        if (node instanceof ElementNode) {
            ElementNode elem = (ElementNode) node;
            for (ChtlNode child : elem.getContent()) {
                findNodesRecursive(child, nodeClass, result);
            }
        } else if (node instanceof TemplateNode) {
            TemplateNode template = (TemplateNode) node;
            for (ChtlNode child : template.getContent()) {
                findNodesRecursive(child, nodeClass, result);
            }
        }
    }
}