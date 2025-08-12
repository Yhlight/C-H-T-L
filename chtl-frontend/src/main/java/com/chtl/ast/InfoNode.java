package com.chtl.ast;

import java.util.HashMap;
import java.util.Map;

/**
 * 表示[Info]信息块节点
 * 用于CMOD模块系统的信息定义
 */
public class InfoNode extends ChtlNode {
    private Map<String, String> properties;
    
    public InfoNode(int line, int column) {
        super(line, column);
        this.properties = new HashMap<>();
    }
    
    public void addProperty(String key, String value) {
        properties.put(key, value);
    }
    
    public Map<String, String> getProperties() {
        return new HashMap<>(properties);
    }
    
    public String getProperty(String key) {
        return properties.get(key);
    }
    
    // 常用属性的快捷访问方法
    public String getName() {
        return properties.get("name");
    }
    
    public String getVersion() {
        return properties.get("version");
    }
    
    public String getDescription() {
        return properties.get("description");
    }
    
    public String getAuthor() {
        return properties.get("author");
    }
    
    public String getLicense() {
        return properties.get("license");
    }
    
    public String getDependencies() {
        return properties.get("dependencies");
    }
    
    public String getCategory() {
        return properties.get("category");
    }
    
    public String getMinCHTLVersion() {
        return properties.get("minCHTLVersion");
    }
    
    public String getMaxCHTLVersion() {
        return properties.get("maxCHTLVersion");
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitInfo(this);
    }
    
    @Override
    public String getNodeType() {
        return "Info";
    }
}