package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing an insert statement
 */
public class InsertNode extends ChtlNode {
    private String position; // after, before, replace, at top, at bottom
    private String target;
    private List<ChtlNode> content = new ArrayList<>();
    
    public InsertNode(String position, String target, int line, int column) {
        super(line, column);
        this.position = position;
        this.target = target;
    }
    
    public void addContent(ChtlNode node) {
        content.add(node);
        addChild(node);
    }
    
    public String getPosition() {
        return position;
    }
    
    public String getTarget() {
        return target;
    }
    
    public List<ChtlNode> getContent() {
        return new ArrayList<>(content);
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitInsert(this);
    }
    
    @Override
    public String getNodeType() {
        return "Insert";
    }
}