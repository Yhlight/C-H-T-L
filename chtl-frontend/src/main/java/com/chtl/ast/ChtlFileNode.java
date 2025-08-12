package com.chtl.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * Root node of the CHTL AST representing the entire file
 */
public class ChtlFileNode extends ChtlNode {
    private String filename;
    private List<ChtlNode> declarations = new ArrayList<>();
    
    public ChtlFileNode(String filename) {
        super(0, 0);
        this.filename = filename;
    }
    
    public void addDeclaration(ChtlNode declaration) {
        declarations.add(declaration);
        addChild(declaration);
    }
    
    public String getFilename() {
        return filename;
    }
    
    public List<ChtlNode> getDeclarations() {
        return new ArrayList<>(declarations);
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitChtlFile(this);
    }
    
    @Override
    public String getNodeType() {
        return "ChtlFile";
    }
}