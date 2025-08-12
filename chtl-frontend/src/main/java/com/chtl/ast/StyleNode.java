package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing a style block
 */
public class StyleNode extends ChtlNode {
    private List<ChtlNode> content = new ArrayList<>();
    private boolean isGlobal;
    
    public StyleNode(int line, int column) {
        super(line, column);
        this.isGlobal = false;
    }
    
    public void addContent(ChtlNode content) {
        this.content.add(content);
        addChild(content);
    }
    
    public List<ChtlNode> getContent() {
        return new ArrayList<>(content);
    }
    
    public boolean isGlobal() {
        return isGlobal;
    }
    
    public void setGlobal(boolean global) {
        isGlobal = global;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitStyle(this);
    }
    
    @Override
    public String getNodeType() {
        return "Style";
    }
}