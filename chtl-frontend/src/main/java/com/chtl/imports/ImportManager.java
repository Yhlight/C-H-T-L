package com.chtl.imports;

import com.chtl.ast.*;
import com.chtl.parser.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

/**
 * 导入管理器 - 处理CHTL的导入机制
 * 包括文件搜索、循环依赖检测、重复导入检测、命名空间合并
 */
public class ImportManager {
    
    /**
     * 导入上下文
     */
    public static class ImportContext {
        private Path currentFile;
        private Path currentDirectory;
        private Path moduleDirectory;
        private Path officialModuleDirectory;
        private Set<Path> importedFiles;
        private Stack<Path> importStack;
        private Map<String, NamespaceNode> namespaces;
        private List<ImportError> errors;
        private List<ImportWarning> warnings;
        private com.chtl.cmod.CmodLoader cmodLoader;
        
        public ImportContext(Path currentFile) {
            this.currentFile = currentFile.toAbsolutePath();
            this.currentDirectory = currentFile.getParent();
            this.moduleDirectory = currentDirectory.resolve("module");
            this.officialModuleDirectory = getOfficialModuleDirectory();
            this.importedFiles = new HashSet<>();
            this.importStack = new Stack<>();
            this.namespaces = new HashMap<>();
            this.errors = new ArrayList<>();
            this.warnings = new ArrayList<>();
        }
        
        private Path getOfficialModuleDirectory() {
            // TODO: 从配置或环境变量中获取官方模块目录
            String chtlHome = System.getenv("CHTL_HOME");
            if (chtlHome != null) {
                return Paths.get(chtlHome, "module");
            }
            // 默认位置
            return Paths.get(System.getProperty("user.home"), ".chtl", "module");
        }
        
        public boolean isAlreadyImported(Path file) {
            return importedFiles.contains(file.toAbsolutePath());
        }
        
        public void markAsImported(Path file) {
            importedFiles.add(file.toAbsolutePath());
        }
        
        public boolean wouldCauseCircularDependency(Path file) {
            return importStack.contains(file.toAbsolutePath());
        }
        
        public void pushImportStack(Path file) {
            importStack.push(file.toAbsolutePath());
        }
        
        public void popImportStack() {
            if (!importStack.isEmpty()) {
                importStack.pop();
            }
        }
        
        public void addError(ImportError error) {
            errors.add(error);
        }
        
        public void addWarning(ImportWarning warning) {
            warnings.add(warning);
        }
        
        public List<ImportError> getErrors() { return errors; }
        public List<ImportWarning> getWarnings() { return warnings; }
        public Map<String, NamespaceNode> getNamespaces() { return namespaces; }
    }
    
    /**
     * 导入错误
     */
    public static class ImportError {
        private String message;
        private Path file;
        private int line;
        private int column;
        
        public ImportError(String message, Path file, int line, int column) {
            this.message = message;
            this.file = file;
            this.line = line;
            this.column = column;
        }
        
        @Override
        public String toString() {
            return String.format("[%s:%d:%d] %s", file, line, column, message);
        }
    }
    
    /**
     * 导入警告
     */
    public static class ImportWarning {
        private String message;
        private Path file;
        private int line;
        private int column;
        
        public ImportWarning(String message, Path file, int line, int column) {
            this.message = message;
            this.file = file;
            this.line = line;
            this.column = column;
        }
        
        @Override
        public String toString() {
            return String.format("[%s:%d:%d] 警告: %s", file, line, column, message);
        }
    }
    
    private ChtlCompiler compiler;
    
    public ImportManager() {
        this.compiler = new ChtlCompiler();
    }
    
    /**
     * 处理导入节点
     */
    public ImportResult processImport(ImportNode importNode, ImportContext context) {
        String importType = importNode.getImportType();
        String sourcePath = importNode.getSourcePath();
        String alias = importNode.getAlias();
        
        ImportResult result = new ImportResult();
        
        switch (importType) {
            case "@Html":
                return processHtmlImport(sourcePath, alias, context, importNode);
            case "@Style":
                return processStyleImport(sourcePath, alias, context, importNode);
            case "@JavaScript":
                return processJavaScriptImport(sourcePath, alias, context, importNode);
            case "@Chtl":
                return processChtlImport(sourcePath, context, importNode);
            case "@CJmod":
                return processCJmodImport(sourcePath, context, importNode);
            default:
                if (importNode.isCustom() || importNode.isTemplate()) {
                    return processSpecificImport(importNode, context);
                }
        }
        
        context.addError(new ImportError(
            "未知的导入类型: " + importType,
            context.currentFile,
            importNode.getLine(),
            importNode.getColumn()
        ));
        
        return result;
    }
    
    /**
     * 处理HTML导入
     */
    private ImportResult processHtmlImport(String sourcePath, String alias, 
                                          ImportContext context, ImportNode importNode) {
        ImportResult result = new ImportResult();
        
        // 如果没有as语法，直接跳过
        if (alias == null || alias.isEmpty()) {
            return result;
        }
        
        // 搜索HTML文件
        Path htmlFile = findHtmlFile(sourcePath, context);
        if (htmlFile == null) {
            context.addError(new ImportError(
                "找不到HTML文件: " + sourcePath,
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
            return result;
        }
        
        try {
            // 读取HTML内容
            String content = Files.readString(htmlFile);
            
            // 创建带名的原始嵌入节点
            OriginNode originNode = new OriginNode(
                "@Html",
                alias,
                content,
                importNode.getLine(),
                importNode.getColumn()
            );
            
            result.addNode(originNode);
            
        } catch (IOException e) {
            context.addError(new ImportError(
                "读取HTML文件失败: " + e.getMessage(),
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
        }
        
        return result;
    }
    
    /**
     * 处理CSS导入
     */
    private ImportResult processStyleImport(String sourcePath, String alias, 
                                           ImportContext context, ImportNode importNode) {
        ImportResult result = new ImportResult();
        
        // 如果没有as语法，直接跳过
        if (alias == null || alias.isEmpty()) {
            return result;
        }
        
        // 搜索CSS文件
        Path cssFile = findStyleFile(sourcePath, context);
        if (cssFile == null) {
            context.addError(new ImportError(
                "找不到CSS文件: " + sourcePath,
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
            return result;
        }
        
        try {
            // 读取CSS内容
            String content = Files.readString(cssFile);
            
            // 创建带名的原始嵌入节点
            OriginNode originNode = new OriginNode(
                "@Style",
                alias,
                content,
                importNode.getLine(),
                importNode.getColumn()
            );
            
            result.addNode(originNode);
            
        } catch (IOException e) {
            context.addError(new ImportError(
                "读取CSS文件失败: " + e.getMessage(),
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
        }
        
        return result;
    }
    
    /**
     * 处理JavaScript导入
     */
    private ImportResult processJavaScriptImport(String sourcePath, String alias, 
                                                ImportContext context, ImportNode importNode) {
        ImportResult result = new ImportResult();
        
        // 如果没有as语法，直接跳过
        if (alias == null || alias.isEmpty()) {
            return result;
        }
        
        // 搜索JavaScript文件
        Path jsFile = findJavaScriptFile(sourcePath, context);
        if (jsFile == null) {
            context.addError(new ImportError(
                "找不到JavaScript文件: " + sourcePath,
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
            return result;
        }
        
        try {
            // 读取JavaScript内容
            String content = Files.readString(jsFile);
            
            // 创建带名的原始嵌入节点
            OriginNode originNode = new OriginNode(
                "@JavaScript",
                alias,
                content,
                importNode.getLine(),
                importNode.getColumn()
            );
            
            result.addNode(originNode);
            
        } catch (IOException e) {
            context.addError(new ImportError(
                "读取JavaScript文件失败: " + e.getMessage(),
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
        }
        
        return result;
    }
    
    /**
     * 处理CHTL导入
     */
    private ImportResult processChtlImport(String sourcePath, ImportContext context, 
                                          ImportNode importNode) {
        ImportResult result = new ImportResult();
        
        // 处理通配符导入
        if (sourcePath.contains("*")) {
            return processWildcardImport(sourcePath, context, importNode);
        }
        
        // 处理子模块导入
        if (sourcePath.contains(".") && !sourcePath.endsWith(".chtl") && !sourcePath.endsWith(".cmod")) {
            return processSubmoduleImport(sourcePath, context, importNode);
        }
        
        // 搜索CHTL文件（包括.cmod文件）
        List<Path> chtlFiles = findChtlFilesWithCmod(sourcePath, context);
        if (chtlFiles.isEmpty()) {
            context.addError(new ImportError(
                "找不到CHTL文件或模块: " + sourcePath,
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
            return result;
        }
        
        // 处理每个找到的文件
        for (Path chtlFile : chtlFiles) {
            if (chtlFile.toString().endsWith(".cmod")) {
                // 处理CMOD文件
                ImportResult cmodResult = processCmodFile(chtlFile, context, importNode);
                result.merge(cmodResult);
            } else {
                // 检查循环依赖
                if (context.wouldCauseCircularDependency(chtlFile)) {
                    context.addError(new ImportError(
                        "检测到循环依赖: " + chtlFile,
                        context.currentFile,
                        importNode.getLine(),
                        importNode.getColumn()
                    ));
                    continue;
                }
                
                // 检查重复导入
                if (context.isAlreadyImported(chtlFile)) {
                    context.addWarning(new ImportWarning(
                        "文件已被导入，跳过: " + chtlFile,
                        context.currentFile,
                        importNode.getLine(),
                        importNode.getColumn()
                    ));
                    continue;
                }
                
                // 处理文件
                ImportResult fileResult = processChtlFile(chtlFile, context);
                result.merge(fileResult);
            }
        }
        
        return result;
    }
    
    /**
     * 处理CHTL文件
     */
    private ImportResult processChtlFile(Path chtlFile, ImportContext context) {
        ImportResult result = new ImportResult();
        
        try {
            // 标记为正在导入
            context.pushImportStack(chtlFile);
            context.markAsImported(chtlFile);
            
            // 编译文件
            CompilationResult compilationResult = compiler.compile(chtlFile.toString());
            
            if (!compilationResult.isSuccess()) {
                for (String error : compilationResult.getErrors()) {
                    context.addError(new ImportError(
                        "编译导入文件失败: " + error,
                        chtlFile,
                        0, 0
                    ));
                }
                return result;
            }
            
            ChtlFileNode ast = (ChtlFileNode) compilationResult.getAst();
            
            // 处理AST中的内容
            for (ChtlNode node : ast.getDeclarations()) {
                if (node instanceof NamespaceNode) {
                    // 合并命名空间
                    mergeNamespace((NamespaceNode) node, context);
                } else if (node instanceof ImportNode) {
                    // 递归处理嵌套导入
                    ImportResult nestedResult = processImport((ImportNode) node, context);
                    result.merge(nestedResult);
                } else {
                    // 其他节点直接添加
                    result.addNode(node);
                }
            }
            
        } finally {
            // 弹出导入栈
            context.popImportStack();
        }
        
        return result;
    }
    
    /**
     * 合并命名空间
     */
    private void mergeNamespace(NamespaceNode newNamespace, ImportContext context) {
        String name = newNamespace.getName();
        
        if (context.namespaces.containsKey(name)) {
            // 命名空间已存在，需要合并
            NamespaceNode existingNamespace = context.namespaces.get(name);
            
            // 检查命名冲突
            Map<String, ChtlNode> existingSymbols = collectSymbols(existingNamespace);
            Map<String, ChtlNode> newSymbols = collectSymbols(newNamespace);
            
            for (Map.Entry<String, ChtlNode> entry : newSymbols.entrySet()) {
                String symbolName = entry.getKey();
                ChtlNode newNode = entry.getValue();
                
                if (existingSymbols.containsKey(symbolName)) {
                    // 发现命名冲突
                    ChtlNode existingNode = existingSymbols.get(symbolName);
                    context.addError(new ImportError(
                        String.format("命名空间 '%s' 中的符号 '%s' 发生冲突", name, symbolName),
                        context.currentFile,
                        newNode.getLine(),
                        newNode.getColumn()
                    ));
                } else {
                    // 添加到现有命名空间
                    existingNamespace.addDeclaration(newNode);
                }
            }
        } else {
            // 新命名空间，直接添加
            context.namespaces.put(name, newNamespace);
        }
    }
    
    /**
     * 收集命名空间中的符号
     */
    private Map<String, ChtlNode> collectSymbols(NamespaceNode namespace) {
        Map<String, ChtlNode> symbols = new HashMap<>();
        
        for (ChtlNode node : namespace.getDeclarations()) {
            String symbolName = getSymbolName(node);
            if (symbolName != null) {
                symbols.put(symbolName, node);
            }
        }
        
        return symbols;
    }
    
    /**
     * 获取节点的符号名称
     */
    private String getSymbolName(ChtlNode node) {
        if (node instanceof TemplateNode) {
            return ((TemplateNode) node).getName();
        } else if (node instanceof CustomNode) {
            return ((CustomNode) node).getName();
        } else if (node instanceof OriginNode) {
            return ((OriginNode) node).getName();
        }
        // 其他类型的节点不产生符号
        return null;
    }
    
    /**
     * 文件搜索方法
     */
    private Path findHtmlFile(String sourcePath, ImportContext context) {
        List<String> extensions = Arrays.asList(".html", ".htm");
        return findFileWithExtensions(sourcePath, extensions, context.currentDirectory);
    }
    
    private Path findStyleFile(String sourcePath, ImportContext context) {
        List<String> extensions = Arrays.asList(".css");
        return findFileWithExtensions(sourcePath, extensions, context.currentDirectory);
    }
    
    private Path findJavaScriptFile(String sourcePath, ImportContext context) {
        List<String> extensions = Arrays.asList(".js", ".javascript");
        return findFileWithExtensions(sourcePath, extensions, context.currentDirectory);
    }
    
    private Path findFileWithExtensions(String sourcePath, List<String> extensions, Path searchDir) {
        Path basePath = searchDir.resolve(sourcePath);
        
        // 如果已经有扩展名，直接查找
        if (sourcePath.contains(".")) {
            if (Files.exists(basePath)) {
                return basePath;
            }
            return null;
        }
        
        // 尝试所有扩展名
        for (String ext : extensions) {
            Path candidate = searchDir.resolve(sourcePath + ext);
            if (Files.exists(candidate)) {
                return candidate;
            }
        }
        
        return null;
    }
    
    /**
     * 查找CHTL文件
     */
    private List<Path> findChtlFiles(String sourcePath, ImportContext context) {
        List<Path> files = new ArrayList<>();
        
        // 处理具体路径
        if (sourcePath.contains("/") || sourcePath.contains("\\")) {
            Path specificPath = Paths.get(sourcePath);
            if (Files.exists(specificPath) && Files.isRegularFile(specificPath)) {
                files.add(specificPath);
            }
            return files;
        }
        
        // 搜索顺序：官方模块 -> 本地module目录 -> 当前目录
        List<Path> searchDirs = Arrays.asList(
            context.officialModuleDirectory,
            context.moduleDirectory,
            context.currentDirectory
        );
        
        for (Path searchDir : searchDirs) {
            if (!Files.exists(searchDir)) {
                continue;
            }
            
            // 优先查找.cmod文件
            Path cmodFile = searchDir.resolve(sourcePath + ".cmod");
            if (Files.exists(cmodFile)) {
                files.add(cmodFile);
                return files; // 找到cmod就返回
            }
            
            // 查找.chtl文件
            Path chtlFile = searchDir.resolve(sourcePath + ".chtl");
            if (Files.exists(chtlFile)) {
                files.add(chtlFile);
                return files;
            }
        }
        
        return files;
    }
    
    /**
     * 处理通配符导入
     */
    private ImportResult processWildcardImport(String pattern, ImportContext context, 
                                              ImportNode importNode) {
        ImportResult result = new ImportResult();
        
        // 解析模式
        String directory = "";
        String filePattern = "*";
        
        int lastSlash = Math.max(pattern.lastIndexOf('/'), pattern.lastIndexOf('.'));
        if (lastSlash >= 0) {
            directory = pattern.substring(0, lastSlash);
            filePattern = pattern.substring(lastSlash + 1);
        }
        
        Path searchDir = context.currentDirectory;
        if (!directory.isEmpty()) {
            searchDir = searchDir.resolve(directory.replace('.', '/'));
        }
        
        if (!Files.exists(searchDir) || !Files.isDirectory(searchDir)) {
            context.addError(new ImportError(
                "找不到目录: " + searchDir,
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
            return result;
        }
        
        try {
            // 根据模式匹配文件
            String glob = filePattern.replace("*", "**");
            PathMatcher matcher = FileSystems.getDefault().getPathMatcher("glob:" + glob);
            
            Files.walk(searchDir, 1) // 不递归子目录
                .filter(Files::isRegularFile)
                .filter(path -> matcher.matches(path.getFileName()))
                .forEach(file -> {
                    ImportResult fileResult = processChtlFile(file, context);
                    result.merge(fileResult);
                });
                
        } catch (IOException e) {
            context.addError(new ImportError(
                "扫描目录失败: " + e.getMessage(),
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
        }
        
        return result;
    }
    
    /**
     * 处理子模块导入
     */
    private ImportResult processSubmoduleImport(String modulePath, ImportContext context, 
                                               ImportNode importNode) {
        ImportResult result = new ImportResult();
        
        // 将点号转换为路径分隔符
        String pathStr = modulePath.replace('.', '/');
        
        // 查找模块
        List<Path> searchDirs = Arrays.asList(
            context.officialModuleDirectory,
            context.moduleDirectory,
            context.currentDirectory
        );
        
        for (Path searchDir : searchDirs) {
            Path moduleDir = searchDir.resolve(pathStr);
            
            // 检查是否是CMOD结构
            Path srcDir = moduleDir.resolve("src");
            if (Files.exists(srcDir) && Files.isDirectory(srcDir)) {
                // 处理CMOD模块
                return processCmodDirectory(moduleDir, context, importNode);
            }
            
            // 检查是否是普通目录
            if (Files.exists(moduleDir) && Files.isDirectory(moduleDir)) {
                // 导入目录下的所有.chtl和.cmod文件
                return processWildcardImport(pathStr + "/*", context, importNode);
            }
        }
        
        context.addError(new ImportError(
            "找不到模块: " + modulePath,
            context.currentFile,
            importNode.getLine(),
            importNode.getColumn()
        ));
        
        return result;
    }
    
    /**
     * 处理CMOD目录
     */
    private ImportResult processCmodDirectory(Path cmodDir, ImportContext context, 
                                             ImportNode importNode) {
        ImportResult result = new ImportResult();
        
        // 处理src目录中的主模块文件
        Path srcDir = cmodDir.resolve("src");
        String moduleName = cmodDir.getFileName().toString();
        
        // 查找主模块文件
        Path mainFile = srcDir.resolve(moduleName + ".chtl");
        if (Files.exists(mainFile)) {
            ImportResult mainResult = processChtlFile(mainFile, context);
            result.merge(mainResult);
        }
        
        // 处理子模块
        try {
            Files.list(srcDir)
                .filter(Files::isDirectory)
                .forEach(submoduleDir -> {
                    ImportResult subResult = processCmodDirectory(submoduleDir, context, importNode);
                    result.merge(subResult);
                });
        } catch (IOException e) {
            context.addError(new ImportError(
                "处理CMOD模块失败: " + e.getMessage(),
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
        }
        
        return result;
    }
    
    /**
     * 查找CHTL文件（包括.cmod文件）
     */
    private List<Path> findChtlFilesWithCmod(String sourcePath, ImportContext context) {
        List<Path> files = new ArrayList<>();
        
        // 首先尝试查找.cmod文件
        files.addAll(findCmodFiles(sourcePath, context));
        
        // 如果没有找到.cmod文件，查找.chtl文件
        if (files.isEmpty()) {
            files.addAll(findChtlFiles(sourcePath, context));
        }
        
        return files;
    }
    
    /**
     * 查找CMOD文件
     */
    private List<Path> findCmodFiles(String sourcePath, ImportContext context) {
        List<Path> files = new ArrayList<>();
        
        // 搜索顺序：官方模块 -> 本地module目录 -> 当前目录
        List<Path> searchDirs = Arrays.asList(
            context.officialModuleDirectory,
            context.moduleDirectory,
            context.currentDirectory
        );
        
        for (Path searchDir : searchDirs) {
            if (!Files.exists(searchDir)) {
                continue;
            }
            
            // 查找.cmod文件
            Path cmodFile = searchDir.resolve(sourcePath + ".cmod");
            if (Files.exists(cmodFile)) {
                files.add(cmodFile);
                return files; // 找到cmod就返回
            }
        }
        
        return files;
    }
    
    /**
     * 处理CMOD文件导入
     */
    private ImportResult processCmodFile(Path cmodFile, ImportContext context, ImportNode importNode) {
        ImportResult result = new ImportResult();
        
        try {
            // 使用CmodLoader加载模块
            if (context.cmodLoader == null) {
                context.cmodLoader = new com.chtl.cmod.CmodLoader();
            }
            
            com.chtl.cmod.CmodLoader.LoadedModule module = context.cmodLoader.loadModule(cmodFile);
            
            // 处理解压后的模块目录
            ImportResult moduleResult = processCmodDirectory(module.getExtractPath(), context, importNode);
            result.merge(moduleResult);
            
        } catch (IOException e) {
            context.addError(new ImportError(
                "加载CMOD文件失败: " + e.getMessage(),
                context.currentFile,
                importNode.getLine(),
                importNode.getColumn()
            ));
        }
        
        return result;
    }
    
    /**
     * 处理CJmod导入
     */
    private ImportResult processCJmodImport(String sourcePath, ImportContext context, 
                                           ImportNode importNode) {
        // TODO: 实现CJmod导入逻辑
        ImportResult result = new ImportResult();
        context.addWarning(new ImportWarning(
            "CJmod导入暂未实现",
            context.currentFile,
            importNode.getLine(),
            importNode.getColumn()
        ));
        return result;
    }
    
    /**
     * 处理特定元素的导入
     */
    private ImportResult processSpecificImport(ImportNode importNode, ImportContext context) {
        // TODO: 实现特定元素的导入逻辑
        ImportResult result = new ImportResult();
        return result;
    }
    
    /**
     * 导入结果
     */
    public static class ImportResult {
        private List<ChtlNode> nodes = new ArrayList<>();
        
        public void addNode(ChtlNode node) {
            nodes.add(node);
        }
        
        public void merge(ImportResult other) {
            nodes.addAll(other.nodes);
        }
        
        public List<ChtlNode> getNodes() {
            return nodes;
        }
    }
}