package com.chtl.ast;

/**
 * AST node representing text content
 */
public class TextNode extends ChtlNode {
    private String text;
    
    public TextNode(String text, int line, int column) {
        super(line, column);
        this.text = text;
    }
    
    public String getText() {
        return text;
    }
    
    public void setText(String text) {
        this.text = text;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitText(this);
    }
    
    @Override
    public String getNodeType() {
        return "Text";
    }
}