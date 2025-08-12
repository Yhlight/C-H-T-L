package com.chtl.analyzer;

/**
 * Represents a namespace context for symbol resolution
 */
public class NamespaceContext {
    private String name;
    private NamespaceContext parent;
    
    public NamespaceContext(String name, NamespaceContext parent) {
        this.name = name;
        this.parent = parent;
    }
    
    public String getName() {
        return name;
    }
    
    public NamespaceContext getParent() {
        return parent;
    }
    
    public String getFullName() {
        if (parent == null) {
            return name;
        }
        return parent.getFullName() + "." + name;
    }
    
    @Override
    public String toString() {
        return getFullName();
    }
}