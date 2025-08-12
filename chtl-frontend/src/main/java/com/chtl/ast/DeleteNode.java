package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing a delete statement
 */
public class DeleteNode extends ChtlNode {
    private List<String> targets = new ArrayList<>();
    
    public DeleteNode(int line, int column) {
        super(line, column);
    }
    
    public void addTarget(String target) {
        targets.add(target);
    }
    
    public List<String> getTargets() {
        return new ArrayList<>(targets);
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitDelete(this);
    }
    
    @Override
    public String getNodeType() {
        return "Delete";
    }
}