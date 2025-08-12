package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing a CSS rule with selector and properties
 */
public class CssRuleNode extends ChtlNode {
    private String selector;
    private String resolvedSelector; // After & resolution
    private List<CssPropertyNode> properties = new ArrayList<>();
    
    public CssRuleNode(String selector, int line, int column) {
        super(line, column);
        this.selector = selector;
    }
    
    public void addProperty(CssPropertyNode property) {
        properties.add(property);
        addChild(property);
    }
    
    public String getSelector() {
        return selector;
    }
    
    public String getResolvedSelector() {
        return resolvedSelector;
    }
    
    public void setResolvedSelector(String resolvedSelector) {
        this.resolvedSelector = resolvedSelector;
    }
    
    public List<CssPropertyNode> getProperties() {
        return new ArrayList<>(properties);
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitCssRule(this);
    }
    
    @Override
    public String getNodeType() {
        return "CssRule";
    }
}