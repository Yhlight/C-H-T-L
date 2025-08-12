package com.chtl.ast;

/**
 * AST node representing an import declaration
 */
public class ImportNode extends ChtlNode {
    private String importType; // @Html, @Style, @JavaScript, @Chtl
    private String targetName; // optional, for specific imports
    private String sourcePath;
    private String alias; // optional AS clause
    private boolean isCustom;
    private boolean isTemplate;
    
    public ImportNode(int line, int column) {
        super(line, column);
    }
    
    public String getImportType() {
        return importType;
    }
    
    public void setImportType(String importType) {
        this.importType = importType;
    }
    
    public String getTargetName() {
        return targetName;
    }
    
    public void setTargetName(String targetName) {
        this.targetName = targetName;
    }
    
    public String getSourcePath() {
        return sourcePath;
    }
    
    public void setSourcePath(String sourcePath) {
        this.sourcePath = sourcePath;
    }
    
    public String getAlias() {
        return alias;
    }
    
    public void setAlias(String alias) {
        this.alias = alias;
    }
    
    public boolean isCustom() {
        return isCustom;
    }
    
    public void setCustom(boolean custom) {
        isCustom = custom;
    }
    
    public boolean isTemplate() {
        return isTemplate;
    }
    
    public void setTemplate(boolean template) {
        isTemplate = template;
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitImport(this);
    }
    
    @Override
    public String getNodeType() {
        return "Import";
    }
}