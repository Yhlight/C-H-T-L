package com.chtl.analyzer;

/**
 * Represents a semantic error or warning in CHTL code
 */
public class SemanticError {
    public enum Severity {
        ERROR,
        WARNING
    }
    
    private Severity severity;
    private String message;
    private int line;
    private int column;
    
    public SemanticError(Severity severity, String message, int line, int column) {
        this.severity = severity;
        this.message = message;
        this.line = line;
        this.column = column;
    }
    
    public Severity getSeverity() {
        return severity;
    }
    
    public String getMessage() {
        return message;
    }
    
    public int getLine() {
        return line;
    }
    
    public int getColumn() {
        return column;
    }
    
    @Override
    public String toString() {
        return String.format("%s at line %d, column %d: %s", 
            severity, line, column, message);
    }
}