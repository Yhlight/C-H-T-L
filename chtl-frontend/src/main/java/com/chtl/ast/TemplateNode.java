package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing a template declaration
 */
public class TemplateNode extends ChtlNode {
    private String type; // @Style, @Element, @Var
    private String name;
    private List<ChtlNode> content = new ArrayList<>();
    
    public TemplateNode(String type, String name, int line, int column) {
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
        return visitor.visitTemplate(this);
    }
    
    @Override
    public String getNodeType() {
        return "Template";
    }
}