package com.chtl.ast;

/**
 * AST node representing an element attribute
 */
public class AttributeNode extends ChtlNode {
    private String name;
    private String value;
    
    public AttributeNode(String name, String value, int line, int column) {
        super(line, column);
        this.name = name;
        this.value = value;
    }
    
    public String getName() {
        return name;
    }
    
    public String getValue() {
        return value;
    }
    
    public void setValue(String value) {
        this.value = value;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitAttribute(this);
    }
    
    @Override
    public String getNodeType() {
        return "Attribute";
    }
}