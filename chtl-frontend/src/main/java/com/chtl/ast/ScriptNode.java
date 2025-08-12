package com.chtl.ast;

/**
 * AST node representing a script block
 */
public class ScriptNode extends ChtlNode {
    private String content;
    private boolean isLocal; // true if inside an element, false if global
    
    public ScriptNode(String content, boolean isLocal, int line, int column) {
        super(line, column);
        this.content = content;
        this.isLocal = isLocal;
    }
    
    public String getContent() {
        return content;
    }
    
    public void setContent(String content) {
        this.content = content;
    }
    
    public boolean isLocal() {
        return isLocal;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitScript(this);
    }
    
    @Override
    public String getNodeType() {
        return "Script";
    }
}