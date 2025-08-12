package com.chtl.cmod;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.zip.*;
import com.fasterxml.jackson.databind.ObjectMapper;

/**
 * CMOD加载器 - 用于加载和管理.cmod文件
 */
public class CmodLoader {
    
    /**
     * 已加载的模块
     */
    public static class LoadedModule {
        private String name;
        private String version;
        private Path extractPath;
        private CmodPackager.CmodInfo moduleInfo;
        private long loadTime;
        
        public LoadedModule(String name, String version, Path extractPath, CmodPackager.CmodInfo moduleInfo) {
            this.name = name;
            this.version = version;
            this.extractPath = extractPath;
            this.moduleInfo = moduleInfo;
            this.loadTime = System.currentTimeMillis();
        }
        
        // Getters
        public String getName() { return name; }
        public String getVersion() { return version; }
        public Path getExtractPath() { return extractPath; }
        public CmodPackager.CmodInfo getModuleInfo() { return moduleInfo; }
        public long getLoadTime() { return loadTime; }
        
        /**
         * 获取模块中的文件路径
         */
        public Path getModuleFile(String relativePath) {
            return extractPath.resolve(relativePath);
        }
        
        /**
         * 获取主模块文件
         */
        public Path getMainModuleFile() {
            return getModuleFile("src/" + name + ".chtl");
        }
        
        /**
         * 获取子模块路径
         */
        public Path getSubmodulePath(String submoduleName) {
            return extractPath.resolve("src").resolve(submoduleName);
        }
    }
    
    private Map<String, LoadedModule> loadedModules;
    private Path tempDirectory;
    private ObjectMapper jsonMapper;
    
    public CmodLoader() {
        this.loadedModules = new HashMap<>();
        this.jsonMapper = new ObjectMapper();
        
        try {
            // 创建临时目录用于解压模块
            this.tempDirectory = Files.createTempDirectory("chtl-cmod-");
            
            // 注册关闭钩子以清理临时文件
            Runtime.getRuntime().addShutdownHook(new Thread(() -> {
                cleanupTempFiles();
            }));
            
        } catch (IOException e) {
            throw new RuntimeException("无法创建临时目录", e);
        }
    }
    
    /**
     * 加载CMOD文件
     * @param cmodFile CMOD文件路径
     * @return 加载的模块
     * @throws IOException 如果加载失败
     */
    public LoadedModule loadModule(Path cmodFile) throws IOException {
        if (!Files.exists(cmodFile)) {
            throw new IOException("CMOD文件不存在: " + cmodFile);
        }
        
        if (!cmodFile.toString().endsWith(".cmod")) {
            throw new IOException("不是有效的CMOD文件: " + cmodFile);
        }
        
        // 读取模块信息
        CmodPackager.CmodInfo moduleInfo = readModuleInfo(cmodFile);
        if (moduleInfo == null) {
            throw new IOException("无法读取模块信息");
        }
        
        // 检查是否已加载
        String moduleKey = moduleInfo.getName() + ":" + moduleInfo.getVersion();
        if (loadedModules.containsKey(moduleKey)) {
            return loadedModules.get(moduleKey);
        }
        
        // 解压模块
        Path extractPath = tempDirectory.resolve(moduleInfo.getName() + "-" + moduleInfo.getVersion());
        extractModule(cmodFile, extractPath);
        
        // 创建加载的模块
        LoadedModule module = new LoadedModule(
            moduleInfo.getName(),
            moduleInfo.getVersion(),
            extractPath,
            moduleInfo
        );
        
        // 缓存模块
        loadedModules.put(moduleKey, module);
        
        return module;
    }
    
    /**
     * 读取模块信息
     */
    private CmodPackager.CmodInfo readModuleInfo(Path cmodFile) throws IOException {
        try (ZipFile zipFile = new ZipFile(cmodFile.toFile())) {
            ZipEntry metaEntry = zipFile.getEntry("META-INF/cmod.json");
            if (metaEntry == null) {
                // 尝试从info目录读取
                return readModuleInfoFromZip(zipFile);
            }
            
            try (InputStream is = zipFile.getInputStream(metaEntry)) {
                return jsonMapper.readValue(is, CmodPackager.CmodInfo.class);
            }
        }
    }
    
    /**
     * 从ZIP文件中读取模块信息
     */
    private CmodPackager.CmodInfo readModuleInfoFromZip(ZipFile zipFile) throws IOException {
        // 查找info目录下的.chtl文件
        Enumeration<? extends ZipEntry> entries = zipFile.entries();
        while (entries.hasMoreElements()) {
            ZipEntry entry = entries.nextElement();
            String name = entry.getName();
            if (name.startsWith("info/") && name.endsWith(".chtl")) {
                // 这可能是模块信息文件
                // TODO: 解析CHTL文件以获取Info块
                // 目前返回null，实际实现需要解析CHTL
                return null;
            }
        }
        return null;
    }
    
    /**
     * 解压模块
     */
    private void extractModule(Path cmodFile, Path targetDir) throws IOException {
        Files.createDirectories(targetDir);
        
        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(cmodFile.toFile()))) {
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                Path entryPath = targetDir.resolve(entry.getName());
                
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    Files.copy(zis, entryPath, StandardCopyOption.REPLACE_EXISTING);
                }
                
                zis.closeEntry();
            }
        }
    }
    
    /**
     * 获取已加载的模块
     * @param name 模块名称
     * @param version 版本（可选）
     * @return 加载的模块，如果未找到则返回null
     */
    public LoadedModule getModule(String name, String version) {
        if (version != null) {
            return loadedModules.get(name + ":" + version);
        }
        
        // 如果没有指定版本，返回最新版本
        LoadedModule latest = null;
        for (LoadedModule module : loadedModules.values()) {
            if (module.getName().equals(name)) {
                if (latest == null || compareVersions(module.getVersion(), latest.getVersion()) > 0) {
                    latest = module;
                }
            }
        }
        
        return latest;
    }
    
    /**
     * 卸载模块
     * @param name 模块名称
     * @param version 版本
     */
    public void unloadModule(String name, String version) {
        String key = name + ":" + version;
        LoadedModule module = loadedModules.remove(key);
        
        if (module != null) {
            // 删除解压的文件
            try {
                deleteDirectory(module.getExtractPath());
            } catch (IOException e) {
                // 忽略清理错误
            }
        }
    }
    
    /**
     * 获取所有已加载的模块
     */
    public Collection<LoadedModule> getAllLoadedModules() {
        return new ArrayList<>(loadedModules.values());
    }
    
    /**
     * 清理临时文件
     */
    private void cleanupTempFiles() {
        try {
            deleteDirectory(tempDirectory);
        } catch (IOException e) {
            // 忽略清理错误
        }
    }
    
    /**
     * 递归删除目录
     */
    private void deleteDirectory(Path dir) throws IOException {
        if (Files.exists(dir)) {
            Files.walk(dir)
                .sorted(Comparator.reverseOrder())
                .forEach(path -> {
                    try {
                        Files.delete(path);
                    } catch (IOException e) {
                        // 忽略单个文件删除错误
                    }
                });
        }
    }
    
    /**
     * 比较版本号
     * @return 如果v1 > v2返回正数，如果v1 < v2返回负数，相等返回0
     */
    private int compareVersions(String v1, String v2) {
        String[] parts1 = v1.split("\\.");
        String[] parts2 = v2.split("\\.");
        
        int length = Math.max(parts1.length, parts2.length);
        for (int i = 0; i < length; i++) {
            int num1 = i < parts1.length ? parseVersionPart(parts1[i]) : 0;
            int num2 = i < parts2.length ? parseVersionPart(parts2[i]) : 0;
            
            if (num1 != num2) {
                return num1 - num2;
            }
        }
        
        return 0;
    }
    
    private int parseVersionPart(String part) {
        try {
            return Integer.parseInt(part);
        } catch (NumberFormatException e) {
            return 0;
        }
    }
}