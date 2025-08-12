package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * AST node representing an HTML element
 */
public class ElementNode extends ChtlNode {
    private String tagName;
    private List<AttributeNode> attributes = new ArrayList<>();
    private List<ChtlNode> content = new ArrayList<>();
    private String generatedClass;
    private String generatedId;
    
    public ElementNode(String tagName, int line, int column) {
        super(line, column);
        this.tagName = tagName;
    }
    
    public void addAttribute(AttributeNode attribute) {
        attributes.add(attribute);
        addChild(attribute);
    }
    
    public void addContent(ChtlNode content) {
        this.content.add(content);
        addChild(content);
    }
    
    public String getTagName() {
        return tagName;
    }
    
    public List<AttributeNode> getAttributes() {
        return new ArrayList<>(attributes);
    }
    
    public List<ChtlNode> getContent() {
        return new ArrayList<>(content);
    }
    
    public String getGeneratedClass() {
        return generatedClass;
    }
    
    public void setGeneratedClass(String generatedClass) {
        this.generatedClass = generatedClass;
    }
    
    public String getGeneratedId() {
        return generatedId;
    }
    
    public void setGeneratedId(String generatedId) {
        this.generatedId = generatedId;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitElement(this);
    }
    
    @Override
    public String getNodeType() {
        return "Element";
    }
}