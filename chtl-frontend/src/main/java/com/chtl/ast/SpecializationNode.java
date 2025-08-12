package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing a specialization block
 */
public class SpecializationNode extends ChtlNode {
    private String target; // What is being specialized
    private List<ChtlNode> modifications = new ArrayList<>();
    
    public SpecializationNode(String target, int line, int column) {
        super(line, column);
        this.target = target;
    }
    
    public void addModification(ChtlNode modification) {
        modifications.add(modification);
        addChild(modification);
    }
    
    public String getTarget() {
        return target;
    }
    
    public List<ChtlNode> getModifications() {
        return new ArrayList<>(modifications);
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitSpecialization(this);
    }
    
    @Override
    public String getNodeType() {
        return "Specialization";
    }
}