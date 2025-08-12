package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * Base class for all CHTL AST nodes
 */
public abstract class ChtlNode {
    private int line;
    private int column;
    private ChtlNode parent;
    private List<ChtlNode> children = new ArrayList<>();
    
    public ChtlNode(int line, int column) {
        this.line = line;
        this.column = column;
    }
    
    public void addChild(ChtlNode child) {
        if (child != null) {
            children.add(child);
            child.setParent(this);
        }
    }
    
    public void removeChild(ChtlNode child) {
        if (child != null) {
            children.remove(child);
            child.setParent(null);
        }
    }
    
    public int getLine() {
        return line;
    }
    
    public int getColumn() {
        return column;
    }
    
    public ChtlNode getParent() {
        return parent;
    }
    
    public void setParent(ChtlNode parent) {
        this.parent = parent;
    }
    
    public List<ChtlNode> getChildren() {
        return new ArrayList<>(children);
    }
    
    public abstract <T> T accept(ChtlVisitor<T> visitor);
    
    public abstract String getNodeType();
}