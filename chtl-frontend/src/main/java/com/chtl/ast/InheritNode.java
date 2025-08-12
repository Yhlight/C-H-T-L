package com.chtl.ast;

/**
 * AST node representing an inherit statement
 */
public class InheritNode extends ChtlNode {
    private AtReferenceNode reference;
    
    public InheritNode(AtReferenceNode reference, int line, int column) {
        super(line, column);
        this.reference = reference;
        addChild(reference);
    }
    
    public AtReferenceNode getReference() {
        return reference;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitInherit(this);
    }
    
    @Override
    public String getNodeType() {
        return "Inherit";
    }
}