package com.chtl.ast;

/**
 * AST node representing an @ reference (e.g., @Element Box)
 */
public class AtReferenceNode extends ChtlNode {
    private String type; // @Element, @Style, @Var
    private String name;
    private String namespace; // optional namespace qualifier
    
    public AtReferenceNode(String type, String name, int line, int column) {
        super(line, column);
        this.type = type;
        this.name = name;
    }
    
    public String getType() {
        return type;
    }
    
    public String getName() {
        return name;
    }
    
    public String getNamespace() {
        return namespace;
    }
    
    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitAtReference(this);
    }
    
    @Override
    public String getNodeType() {
        return "AtReference";
    }
}