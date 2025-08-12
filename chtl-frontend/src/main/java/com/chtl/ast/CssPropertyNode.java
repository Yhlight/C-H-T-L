package com.chtl.ast;

/**
 * AST node representing a CSS property
 */
public class CssPropertyNode extends ChtlNode {
    private String property;
    private String value;
    
    public CssPropertyNode(String property, String value, int line, int column) {
        super(line, column);
        this.property = property;
        this.value = value;
    }
    
    public String getProperty() {
        return property;
    }
    
    public String getValue() {
        return value;
    }
    
    public void setValue(String value) {
        this.value = value;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitCssProperty(this);
    }
    
    @Override
    public String getNodeType() {
        return "CssProperty";
    }
}