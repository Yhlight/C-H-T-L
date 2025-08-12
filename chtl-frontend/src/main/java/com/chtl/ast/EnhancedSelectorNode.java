package com.chtl.ast;

/**
 * AST node representing an enhanced selector {{...}}
 */
public class EnhancedSelectorNode extends ChtlNode {
    private String selector;
    
    public EnhancedSelectorNode(String selector, int line, int column) {
        super(line, column);
        this.selector = selector;
    }
    
    public String getSelector() {
        return selector;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitEnhancedSelector(this);
    }
    
    @Override
    public String getNodeType() {
        return "EnhancedSelector";
    }
}