package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing a namespace declaration
 */
public class NamespaceNode extends ChtlNode {
    private String name;
    private List<ChtlNode> content = new ArrayList<>();
    
    public NamespaceNode(String name, int line, int column) {
        super(line, column);
        this.name = name;
    }
    
    public void addContent(ChtlNode node) {
        content.add(node);
        addChild(node);
    }
    
    public String getName() {
        return name;
    }
    
    public List<ChtlNode> getContent() {
        return new ArrayList<>(content);
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitNamespace(this);
    }
    
    @Override
    public String getNodeType() {
        return "Namespace";
    }
}