package com.chtl;

import com.chtl.generator.GeneratedCode;
import java.util.ArrayList;
import java.util.List;

/**
 * Result of CHTL compilation
 */
public class CompilationResult {
    private boolean success = false;
    private GeneratedCode generatedCode;
    private List<String> errors = new ArrayList<>();
    private List<String> warnings = new ArrayList<>();
    
    public boolean isSuccess() {
        return success;
    }
    
    public void setSuccess(boolean success) {
        this.success = success;
    }
    
    public GeneratedCode getGeneratedCode() {
        return generatedCode;
    }
    
    public void setGeneratedCode(GeneratedCode generatedCode) {
        this.generatedCode = generatedCode;
    }
    
    public List<String> getErrors() {
        return new ArrayList<>(errors);
    }
    
    public void addError(String error) {
        errors.add(error);
    }
    
    public List<String> getWarnings() {
        return new ArrayList<>(warnings);
    }
    
    public void addWarning(String warning) {
        warnings.add(warning);
    }
    
    public boolean hasErrors() {
        return !errors.isEmpty();
    }
    
    public boolean hasWarnings() {
        return !warnings.isEmpty();
    }
}