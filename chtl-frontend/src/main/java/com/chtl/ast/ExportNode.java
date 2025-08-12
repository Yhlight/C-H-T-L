package com.chtl.ast;

import java.util.*;

/**
 * 表示[Export]导出块节点
 * 用于CMOD模块系统的导出声明
 */
public class ExportNode extends ChtlNode {
    private List<ExportItem> exports;
    
    public ExportNode(int line, int column) {
        super(line, column);
        this.exports = new ArrayList<>();
    }
    
    public void addExport(ExportItem item) {
        exports.add(item);
    }
    
    public List<ExportItem> getExports() {
        return new ArrayList<>(exports);
    }
    
    /**
     * 根据类型获取导出项
     */
    public List<ExportItem> getExportsByType(String type) {
        return exports.stream()
            .filter(item -> item.getType().equals(type))
            .toList();
    }
    
    /**
     * 获取所有导出的样式
     */
    public List<String> getExportedStyles() {
        return getExportsByType("@Style").stream()
            .flatMap(item -> item.getNames().stream())
            .toList();
    }
    
    /**
     * 获取所有导出的元素
     */
    public List<String> getExportedElements() {
        return getExportsByType("@Element").stream()
            .flatMap(item -> item.getNames().stream())
            .toList();
    }
    
    /**
     * 获取所有导出的变量组
     */
    public List<String> getExportedVars() {
        return getExportsByType("@Var").stream()
            .flatMap(item -> item.getNames().stream())
            .toList();
    }
    
    @Override
    public <T> T accept(ChtlVisitor<T> visitor) {
        return visitor.visitExport(this);
    }
    
    @Override
    public String getNodeType() {
        return "Export";
    }
    
    /**
     * 导出项
     */
    public static class ExportItem {
        private String type; // @Style, @Element, @Var
        private List<String> names;
        
        public ExportItem(String type) {
            this.type = type;
            this.names = new ArrayList<>();
        }
        
        public void addName(String name) {
            names.add(name);
        }
        
        public String getType() {
            return type;
        }
        
        public List<String> getNames() {
            return new ArrayList<>(names);
        }
    }
}