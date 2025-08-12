package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing a custom declaration
 */
public class CustomNode extends ChtlNode {
    private String type; // @Style, @Element, @Var
    private String name;
    private List<ChtlNode> content = new ArrayList<>();
    
    public CustomNode(String type, String name, int line, int column) {
        super(line, column);
        this.type = type;
        this.name = name;
    }
    
    public void addContent(ChtlNode content) {
        this.content.add(content);
        addChild(content);
    }
    
    public String getType() {
        return type;
    }
    
    public String getName() {
        return name;
    }
    
    public List<ChtlNode> getContent() {
        return new ArrayList<>(content);
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitCustom(this);
    }
    
    @Override
    public String getNodeType() {
        return "Custom";
    }
}