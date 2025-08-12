package com.chtl.cmod;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.zip.*;
import com.chtl.ast.*;
import com.chtl.parser.ChtlCompiler;
import com.chtl.CompilationResult;

/**
 * CMOD打包器 - 将符合CMOD格式的文件夹打包成.cmod文件
 */
public class CmodPackager {
    
    /**
     * 打包结果
     */
    public static class PackageResult {
        private boolean success;
        private String outputPath;
        private List<String> errors;
        private List<String> warnings;
        private CmodInfo moduleInfo;
        
        public PackageResult() {
            this.errors = new ArrayList<>();
            this.warnings = new ArrayList<>();
            this.success = true;
        }
        
        // Getters
        public boolean isSuccess() { return success && errors.isEmpty(); }
        public String getOutputPath() { return outputPath; }
        public List<String> getErrors() { return errors; }
        public List<String> getWarnings() { return warnings; }
        public CmodInfo getModuleInfo() { return moduleInfo; }
        
        // Setters
        public void setOutputPath(String path) { this.outputPath = path; }
        public void setModuleInfo(CmodInfo info) { this.moduleInfo = info; }
        
        public void addError(String error) {
            errors.add(error);
            success = false;
        }
        
        public void addWarning(String warning) {
            warnings.add(warning);
        }
    }
    
    /**
     * CMOD信息
     */
    public static class CmodInfo {
        private String name;
        private String version;
        private String description;
        private String author;
        private String license;
        private String dependencies;
        private String category;
        private String minCHTLVersion;
        private String maxCHTLVersion;
        private Map<String, List<String>> exports;
        
        public CmodInfo() {
            this.exports = new HashMap<>();
        }
        
        // Getters and setters
        public String getName() { return name; }
        public void setName(String name) { this.name = name; }
        
        public String getVersion() { return version; }
        public void setVersion(String version) { this.version = version; }
        
        public String getDescription() { return description; }
        public void setDescription(String description) { this.description = description; }
        
        public String getAuthor() { return author; }
        public void setAuthor(String author) { this.author = author; }
        
        public String getLicense() { return license; }
        public void setLicense(String license) { this.license = license; }
        
        public String getDependencies() { return dependencies; }
        public void setDependencies(String dependencies) { this.dependencies = dependencies; }
        
        public String getCategory() { return category; }
        public void setCategory(String category) { this.category = category; }
        
        public String getMinCHTLVersion() { return minCHTLVersion; }
        public void setMinCHTLVersion(String minCHTLVersion) { this.minCHTLVersion = minCHTLVersion; }
        
        public String getMaxCHTLVersion() { return maxCHTLVersion; }
        public void setMaxCHTLVersion(String maxCHTLVersion) { this.maxCHTLVersion = maxCHTLVersion; }
        
        public Map<String, List<String>> getExports() { return exports; }
        public void addExport(String type, List<String> names) {
            exports.put(type, names);
        }
    }
    
    private ChtlCompiler compiler;
    
    public CmodPackager() {
        this.compiler = new ChtlCompiler();
    }
    
    /**
     * 打包CMOD模块
     * @param moduleDir 模块目录
     * @param outputDir 输出目录
     * @return 打包结果
     */
    public PackageResult packageModule(Path moduleDir, Path outputDir) {
        PackageResult result = new PackageResult();
        
        try {
            // 验证模块结构
            if (!validateModuleStructure(moduleDir, result)) {
                return result;
            }
            
            String moduleName = moduleDir.getFileName().toString();
            
            // 读取模块信息
            CmodInfo moduleInfo = readModuleInfo(moduleDir, moduleName, result);
            if (moduleInfo == null) {
                return result;
            }
            result.setModuleInfo(moduleInfo);
            
            // 验证主模块文件
            if (!validateMainModule(moduleDir, moduleName, result)) {
                return result;
            }
            
            // 自动生成导出信息
            generateExports(moduleDir, moduleInfo, result);
            
            // 创建输出文件
            Path outputPath = outputDir.resolve(moduleName + ".cmod");
            result.setOutputPath(outputPath.toString());
            
            // 打包文件
            packageFiles(moduleDir, outputPath, moduleInfo, result);
            
        } catch (Exception e) {
            result.addError("打包失败: " + e.getMessage());
        }
        
        return result;
    }
    
    /**
     * 验证模块结构
     */
    private boolean validateModuleStructure(Path moduleDir, PackageResult result) {
        if (!Files.exists(moduleDir) || !Files.isDirectory(moduleDir)) {
            result.addError("模块目录不存在: " + moduleDir);
            return false;
        }
        
        Path srcDir = moduleDir.resolve("src");
        Path infoDir = moduleDir.resolve("info");
        
        if (!Files.exists(srcDir) || !Files.isDirectory(srcDir)) {
            result.addError("缺少src目录");
            return false;
        }
        
        if (!Files.exists(infoDir) || !Files.isDirectory(infoDir)) {
            result.addError("缺少info目录");
            return false;
        }
        
        return true;
    }
    
    /**
     * 读取模块信息
     */
    private CmodInfo readModuleInfo(Path moduleDir, String moduleName, PackageResult result) {
        Path infoFile = moduleDir.resolve("info").resolve(moduleName + ".chtl");
        
        if (!Files.exists(infoFile)) {
            result.addError("缺少模块信息文件: " + infoFile);
            return null;
        }
        
        try {
            // 编译信息文件
            CompilationResult compilationResult = compiler.compile(infoFile.toString());
            
            if (!compilationResult.isSuccess()) {
                result.addError("编译模块信息文件失败");
                compilationResult.getErrors().forEach(result::addError);
                return null;
            }
            
            // 解析Info节点
            ChtlFileNode ast = (ChtlFileNode) compilationResult.getAst();
            InfoNode infoNode = findInfoNode(ast);
            
            if (infoNode == null) {
                result.addError("模块信息文件缺少[Info]块");
                return null;
            }
            
            // 转换为CmodInfo
            return convertToModInfo(infoNode);
            
        } catch (IOException e) {
            result.addError("读取模块信息文件失败: " + e.getMessage());
            return null;
        }
    }
    
    /**
     * 查找Info节点
     */
    private InfoNode findInfoNode(ChtlFileNode ast) {
        for (ChtlNode node : ast.getDeclarations()) {
            if (node instanceof InfoNode) {
                return (InfoNode) node;
            }
        }
        return null;
    }
    
    /**
     * 转换为CmodInfo
     */
    private CmodInfo convertToModInfo(InfoNode infoNode) {
        CmodInfo info = new CmodInfo();
        
        info.setName(infoNode.getName());
        info.setVersion(infoNode.getVersion());
        info.setDescription(infoNode.getDescription());
        info.setAuthor(infoNode.getAuthor());
        info.setLicense(infoNode.getLicense());
        info.setDependencies(infoNode.getDependencies());
        info.setCategory(infoNode.getCategory());
        info.setMinCHTLVersion(infoNode.getMinCHTLVersion());
        info.setMaxCHTLVersion(infoNode.getMaxCHTLVersion());
        
        return info;
    }
    
    /**
     * 验证主模块文件
     */
    private boolean validateMainModule(Path moduleDir, String moduleName, PackageResult result) {
        Path srcDir = moduleDir.resolve("src");
        Path mainModule = srcDir.resolve(moduleName + ".chtl");
        
        // 检查是否有子模块
        boolean hasSubmodules = false;
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(srcDir)) {
            for (Path entry : stream) {
                if (Files.isDirectory(entry) && isValidSubmodule(entry)) {
                    hasSubmodules = true;
                    break;
                }
            }
        } catch (IOException e) {
            result.addWarning("检查子模块时出错: " + e.getMessage());
        }
        
        // 如果没有子模块，主模块文件必须存在
        if (!hasSubmodules && !Files.exists(mainModule)) {
            result.addError("缺少主模块文件: " + mainModule);
            return false;
        }
        
        // 如果有子模块，主模块文件是可选的
        if (hasSubmodules && !Files.exists(mainModule)) {
            result.addWarning("有子模块但缺少主模块文件（这是推荐的做法）");
        }
        
        return true;
    }
    
    /**
     * 检查是否是有效的子模块
     */
    private boolean isValidSubmodule(Path submoduleDir) {
        String submoduleName = submoduleDir.getFileName().toString();
        Path srcDir = submoduleDir.resolve("src");
        Path infoDir = submoduleDir.resolve("info");
        Path mainFile = srcDir.resolve(submoduleName + ".chtl");
        Path infoFile = infoDir.resolve(submoduleName + ".chtl");
        
        return Files.exists(srcDir) && Files.exists(infoDir) && 
               Files.exists(mainFile) && Files.exists(infoFile);
    }
    
    /**
     * 自动生成导出信息
     */
    private void generateExports(Path moduleDir, CmodInfo moduleInfo, PackageResult result) {
        Map<String, Set<String>> exports = new HashMap<>();
        exports.put("@Style", new HashSet<>());
        exports.put("@Element", new HashSet<>());
        exports.put("@Var", new HashSet<>());
        
        try {
            // 扫描所有CHTL文件
            scanForExports(moduleDir.resolve("src"), exports, result);
            
            // 更新模块信息
            for (Map.Entry<String, Set<String>> entry : exports.entrySet()) {
                moduleInfo.addExport(entry.getKey(), new ArrayList<>(entry.getValue()));
            }
            
        } catch (Exception e) {
            result.addWarning("生成导出信息时出错: " + e.getMessage());
        }
    }
    
    /**
     * 扫描导出
     */
    private void scanForExports(Path dir, Map<String, Set<String>> exports, PackageResult result) throws IOException {
        Files.walk(dir)
            .filter(path -> path.toString().endsWith(".chtl"))
            .forEach(path -> {
                try {
                    CompilationResult compilationResult = compiler.compile(path.toString());
                    if (compilationResult.isSuccess()) {
                        ChtlFileNode ast = (ChtlFileNode) compilationResult.getAst();
                        collectExports(ast, exports);
                    }
                } catch (Exception e) {
                    result.addWarning("扫描文件时出错: " + path + " - " + e.getMessage());
                }
            });
    }
    
    /**
     * 收集导出
     */
    private void collectExports(ChtlFileNode ast, Map<String, Set<String>> exports) {
        for (ChtlNode node : ast.getDeclarations()) {
            if (node instanceof TemplateNode) {
                TemplateNode template = (TemplateNode) node;
                exports.get(template.getType()).add(template.getName());
            } else if (node instanceof CustomNode) {
                CustomNode custom = (CustomNode) node;
                exports.get(custom.getType()).add(custom.getName());
            }
        }
    }
    
    /**
     * 打包文件
     */
    private void packageFiles(Path moduleDir, Path outputPath, CmodInfo moduleInfo, PackageResult result) throws IOException {
        // 确保输出目录存在
        Files.createDirectories(outputPath.getParent());
        
        try (ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(outputPath.toFile()))) {
            // 添加模块信息
            addModuleMetadata(zos, moduleInfo);
            
            // 添加所有文件
            Files.walk(moduleDir)
                .filter(Files::isRegularFile)
                .forEach(path -> {
                    try {
                        Path relativePath = moduleDir.relativize(path);
                        ZipEntry entry = new ZipEntry(relativePath.toString().replace('\\', '/'));
                        zos.putNextEntry(entry);
                        Files.copy(path, zos);
                        zos.closeEntry();
                    } catch (IOException e) {
                        result.addWarning("添加文件时出错: " + path + " - " + e.getMessage());
                    }
                });
        }
        
        result.addWarning("成功打包模块: " + outputPath);
    }
    
    /**
     * 添加模块元数据
     */
    private void addModuleMetadata(ZipOutputStream zos, CmodInfo moduleInfo) throws IOException {
        // 添加CMOD元数据文件
        ZipEntry metaEntry = new ZipEntry("META-INF/cmod.json");
        zos.putNextEntry(metaEntry);
        
        // 写入JSON格式的元数据
        String json = convertToJson(moduleInfo);
        zos.write(json.getBytes("UTF-8"));
        zos.closeEntry();
    }
    
    /**
     * 转换为JSON
     */
    private String convertToJson(CmodInfo info) {
        StringBuilder json = new StringBuilder();
        json.append("{\n");
        json.append("  \"name\": \"").append(info.getName()).append("\",\n");
        json.append("  \"version\": \"").append(info.getVersion()).append("\",\n");
        json.append("  \"description\": \"").append(info.getDescription()).append("\",\n");
        json.append("  \"author\": \"").append(info.getAuthor()).append("\",\n");
        json.append("  \"license\": \"").append(info.getLicense()).append("\",\n");
        json.append("  \"dependencies\": \"").append(info.getDependencies()).append("\",\n");
        json.append("  \"category\": \"").append(info.getCategory()).append("\",\n");
        json.append("  \"minCHTLVersion\": \"").append(info.getMinCHTLVersion()).append("\",\n");
        json.append("  \"maxCHTLVersion\": \"").append(info.getMaxCHTLVersion()).append("\",\n");
        json.append("  \"exports\": {\n");
        
        boolean first = true;
        for (Map.Entry<String, List<String>> entry : info.getExports().entrySet()) {
            if (!first) json.append(",\n");
            json.append("    \"").append(entry.getKey()).append("\": [");
            
            boolean firstItem = true;
            for (String name : entry.getValue()) {
                if (!firstItem) json.append(", ");
                json.append("\"").append(name).append("\"");
                firstItem = false;
            }
            
            json.append("]");
            first = false;
        }
        
        json.append("\n  }\n");
        json.append("}\n");
        
        return json.toString();
    }
}