package com.chtl.ast;

import java.util.HashMap;
import java.util.Map;

/**
 * AST node representing a configuration block
 */
public class ConfigurationNode extends ChtlNode {
    private Map<String, String> properties = new HashMap<>();
    private Map<String, Map<String, String>> nameGroups = new HashMap<>();
    
    public ConfigurationNode(int line, int column) {
        super(line, column);
    }
    
    public void addProperty(String name, String value) {
        properties.put(name, value);
    }
    
    public void addNameGroup(String groupName, Map<String, String> values) {
        nameGroups.put(groupName, values);
    }
    
    public Map<String, String> getProperties() {
        return new HashMap<>(properties);
    }
    
    public Map<String, Map<String, String>> getNameGroups() {
        return new HashMap<>(nameGroups);
    }
    
    public String getProperty(String name) {
        return properties.get(name);
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitConfiguration(this);
    }
    
    @Override
    public String getNodeType() {
        return "Configuration";
    }
}