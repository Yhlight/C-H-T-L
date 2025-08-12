package com.chtl.cjmod;

import java.nio.file.Path;
import java.util.*;

/**
 * CJMOD接口 - 定义与C++模块交互的接口
 * CJMOD允许通过C++扩展CHTL JS语法
 */
public interface CJmodInterface {
    
    /**
     * CJMOD元数据
     */
    class CJmodMetadata {
        private String name;
        private String version;
        private String description;
        private String author;
        private List<String> exportedFunctions;
        private Map<String, String> configuration;
        
        public CJmodMetadata() {
            this.exportedFunctions = new ArrayList<>();
            this.configuration = new HashMap<>();
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
        
        public List<String> getExportedFunctions() { return exportedFunctions; }
        public void addExportedFunction(String function) { exportedFunctions.add(function); }
        
        public Map<String, String> getConfiguration() { return configuration; }
        public void addConfiguration(String key, String value) { configuration.put(key, value); }
    }
    
    /**
     * 加载CJMOD模块
     * @param modulePath 模块路径
     * @return 模块元数据
     * @throws CJmodException 如果加载失败
     */
    CJmodMetadata loadModule(Path modulePath) throws CJmodException;
    
    /**
     * 调用CJMOD函数
     * @param moduleName 模块名称
     * @param functionName 函数名称
     * @param arguments 参数列表
     * @return 函数返回值
     * @throws CJmodException 如果调用失败
     */
    String invokeFunction(String moduleName, String functionName, List<String> arguments) throws CJmodException;
    
    /**
     * 注册CJMOD语法扩展
     * @param moduleName 模块名称
     * @param syntaxDefinition 语法定义
     * @throws CJmodException 如果注册失败
     */
    void registerSyntaxExtension(String moduleName, SyntaxDefinition syntaxDefinition) throws CJmodException;
    
    /**
     * 卸载CJMOD模块
     * @param moduleName 模块名称
     * @throws CJmodException 如果卸载失败
     */
    void unloadModule(String moduleName) throws CJmodException;
    
    /**
     * 获取已加载的模块列表
     * @return 模块名称列表
     */
    List<String> getLoadedModules();
    
    /**
     * 语法定义
     */
    class SyntaxDefinition {
        private String pattern;
        private String handler;
        private Map<String, String> options;
        
        public SyntaxDefinition(String pattern, String handler) {
            this.pattern = pattern;
            this.handler = handler;
            this.options = new HashMap<>();
        }
        
        public String getPattern() { return pattern; }
        public String getHandler() { return handler; }
        public Map<String, String> getOptions() { return options; }
        public void addOption(String key, String value) { options.put(key, value); }
    }
    
    /**
     * CJMOD异常
     */
    class CJmodException extends Exception {
        public CJmodException(String message) {
            super(message);
        }
        
        public CJmodException(String message, Throwable cause) {
            super(message, cause);
        }
    }
}