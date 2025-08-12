package com.chtl.analyzer;

import com.chtl.ast.*;
import java.util.*;

/**
 * Symbol table for CHTL semantic analysis
 */
public class SymbolTable {
    private Map<String, ChtlNode> symbols;
    private Set<String> ids;
    private Map<String, List<ElementNode>> classUsages;
    private Map<String, ImportNode> importAliases;
    private List<NamespaceContext> namespaces;
    
    public SymbolTable() {
        this.symbols = new HashMap<>();
        this.ids = new HashSet<>();
        this.classUsages = new HashMap<>();
        this.importAliases = new HashMap<>();
        this.namespaces = new ArrayList<>();
    }
    
    public void clear() {
        symbols.clear();
        ids.clear();
        classUsages.clear();
        importAliases.clear();
        namespaces.clear();
    }
    
    public boolean addSymbol(String key, ChtlNode node) {
        if (symbols.containsKey(key)) {
            return false;
        }
        symbols.put(key, node);
        return true;
    }
    
    public boolean hasSymbol(String key) {
        return symbols.containsKey(key);
    }
    
    public ChtlNode getSymbol(String key) {
        return symbols.get(key);
    }
    
    public boolean addId(String id) {
        if (ids.contains(id)) {
            return false;
        }
        ids.add(id);
        return true;
    }
    
    public boolean hasId(String id) {
        return ids.contains(id);
    }
    
    public void addClassUsage(ElementNode element, String className) {
        classUsages.computeIfAbsent(className, k -> new ArrayList<>()).add(element);
    }
    
    public void addGeneratedClass(ElementNode element, String className) {
        addClassUsage(element, className);
    }
    
    public boolean hasSelector(String selector) {
        if (selector.startsWith(".")) {
            String className = selector.substring(1);
            return classUsages.containsKey(className);
        } else if (selector.startsWith("#")) {
            String id = selector.substring(1);
            return ids.contains(id);
        } else {
            // Element selector - always valid for simplicity
            return true;
        }
    }
    
    public void addImportAlias(String alias, ImportNode node) {
        importAliases.put(alias, node);
    }
    
    public ImportNode getImportByAlias(String alias) {
        return importAliases.get(alias);
    }
    
    public void addNamespace(NamespaceContext namespace) {
        namespaces.add(namespace);
    }
    
    public NamespaceContext findNamespace(String name) {
        for (NamespaceContext ns : namespaces) {
            if (ns.getName().equals(name)) {
                return ns;
            }
        }
        return null;
    }
}