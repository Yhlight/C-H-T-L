package com.chtl.ast;

/**
 * AST node representing an origin (raw) block
 */
public class OriginNode extends ChtlNode {
    private String type; // @Html, @Style, @JavaScript
    private String name; // optional name
    private String content;
    
    public OriginNode(String type, String content, int line, int column) {
        super(line, column);
        this.type = type;
        this.content = content;
    }
    
    public OriginNode(String type, String name, String content, int line, int column) {
        super(line, column);
        this.type = type;
        this.name = name;
        this.content = content;
    }
    
    public String getType() {
        return type;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public boolean hasName() {
        return name != null && !name.isEmpty();
    }
    
    public String getContent() {
        return content;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitOrigin(this);
    }
    
    @Override
    public String getNodeType() {
        return "Origin";
    }
}