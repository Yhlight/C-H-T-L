package com.chtl.generator;

import com.chtl.ast.*;
import java.util.*;
import java.io.PrintWriter;
import java.io.StringWriter;

/**
 * Generates HTML/CSS/JavaScript from CHTL AST
 */
public class HtmlGenerator implements ChtlVisitor<String> {
    
    private StringBuilder globalStyles;
    private StringBuilder globalScripts;
    private Map<String, String> templateExpansions;
    private int indentLevel;
    private static final String INDENT = "    ";
    private ElementNode currentElement;
    
    public HtmlGenerator() {
        this.globalStyles = new StringBuilder();
        this.globalScripts = new StringBuilder();
        this.templateExpansions = new HashMap<>();
        this.indentLevel = 0;
    }
    
    public GeneratedCode generate(ChtlFileNode ast) {
        // First pass: collect templates and customs
        collectTemplates(ast);
        
        // Second pass: generate HTML
        String html = visit(ast);
        
        return new GeneratedCode(html, globalStyles.toString(), globalScripts.toString());
    }
    
    @Override
    public String visitChtlFile(ChtlFileNode node) {
        StringBuilder result = new StringBuilder();
        result.append("<!DOCTYPE html>\n");
        
        boolean hasHtmlRoot = false;
        for (ChtlNode decl : node.getDeclarations()) {
            if (decl instanceof ElementNode && 
                ((ElementNode) decl).getTagName().equals("html")) {
                hasHtmlRoot = true;
                break;
            }
        }
        
        if (!hasHtmlRoot) {
            result.append("<html>\n");
            result.append("<head>\n");
            if (globalStyles.length() > 0) {
                result.append(indent()).append("<style>\n");
                result.append(globalStyles.toString());
                result.append(indent()).append("</style>\n");
            }
            result.append("</head>\n");
            result.append("<body>\n");
            indentLevel++;
        }
        
        for (ChtlNode decl : node.getDeclarations()) {
            String content = decl.accept(this);
            if (content != null && !content.isEmpty()) {
                result.append(content);
            }
        }
        
        if (!hasHtmlRoot) {
            indentLevel--;
            if (globalScripts.length() > 0) {
                result.append(indent()).append("<script>\n");
                result.append(globalScripts.toString());
                result.append(indent()).append("</script>\n");
            }
            result.append("</body>\n");
            result.append("</html>\n");
        }
        
        return result.toString();
    }
    
    @Override
    public String visitElement(ElementNode node) {
        ElementNode previousElement = currentElement;
        currentElement = node;
        
        StringBuilder result = new StringBuilder();
        String tagName = node.getTagName();
        
        // Check if this is a head or body tag that needs special handling
        if (tagName.equals("head") || tagName.equals("body")) {
            result.append(indent()).append("<").append(tagName);
            appendAttributes(result, node);
            result.append(">\n");
            
            if (tagName.equals("head") && globalStyles.length() > 0) {
                indentLevel++;
                result.append(indent()).append("<style>\n");
                result.append(globalStyles.toString());
                result.append(indent()).append("</style>\n");
                indentLevel--;
            }
            
            indentLevel++;
            for (ChtlNode content : node.getContent()) {
                String generated = content.accept(this);
                if (generated != null && !generated.isEmpty()) {
                    result.append(generated);
                }
            }
            indentLevel--;
            
            if (tagName.equals("body") && globalScripts.length() > 0) {
                indentLevel++;
                result.append(indent()).append("<script>\n");
                result.append(globalScripts.toString());
                result.append(indent()).append("</script>\n");
                indentLevel--;
            }
            
            result.append(indent()).append("</").append(tagName).append(">\n");
        } else {
            // Normal element
            result.append(indent()).append("<").append(tagName);
            appendAttributes(result, node);
            
            if (isVoidElement(tagName)) {
                result.append(" />\n");
            } else {
                result.append(">");
                
                boolean hasBlockContent = hasBlockLevelContent(node);
                if (hasBlockContent) {
                    result.append("\n");
                    indentLevel++;
                }
                
                for (ChtlNode content : node.getContent()) {
                    String generated = content.accept(this);
                    if (generated != null && !generated.isEmpty()) {
                        result.append(generated);
                    }
                }
                
                if (hasBlockContent) {
                    indentLevel--;
                    result.append(indent());
                }
                
                result.append("</").append(tagName).append(">\n");
            }
        }
        
        currentElement = previousElement;
        return result.toString();
    }
    
    @Override
    public String visitText(TextNode node) {
        String text = node.getText();
        if (text == null || text.trim().isEmpty()) {
            return "";
        }
        return indent() + text.trim() + "\n";
    }
    
    @Override
    public String visitAttribute(AttributeNode node) {
        // Attributes are handled in visitElement
        return "";
    }
    
    @Override
    public String visitStyle(StyleNode node) {
        if (node.isGlobal()) {
            // Global styles are collected
            for (ChtlNode content : node.getContent()) {
                if (content instanceof CssPropertyNode) {
                    globalStyles.append(indent()).append(content.accept(this));
                } else if (content instanceof CssRuleNode) {
                    globalStyles.append(content.accept(this));
                }
            }
        } else {
            // Local styles - generate inline style attribute
            StringBuilder inlineStyle = new StringBuilder();
            List<String> globalRules = new ArrayList<>();
            
            for (ChtlNode content : node.getContent()) {
                if (content instanceof CssPropertyNode) {
                    CssPropertyNode prop = (CssPropertyNode) content;
                    inlineStyle.append(prop.getProperty()).append(": ")
                              .append(prop.getValue()).append("; ");
                } else if (content instanceof CssRuleNode) {
                    // CSS rules go to global styles
                    globalRules.add(content.accept(this));
                }
            }
            
            // Add global rules
            for (String rule : globalRules) {
                globalStyles.append(rule);
            }
            
            // Return inline styles for the parent element
            if (inlineStyle.length() > 0) {
                return inlineStyle.toString().trim();
            }
        }
        
        return "";
    }
    
    @Override
    public String visitScript(ScriptNode node) {
        String content = processEnhancedSelectors(node.getContent());
        
        if (node.isLocal()) {
            // Local script - wrap in IIFE and add to global scripts
            globalScripts.append("(function() {\n");
            globalScripts.append(content);
            globalScripts.append("\n})();\n\n");
        } else {
            // Global script
            globalScripts.append(content).append("\n\n");
        }
        
        return "";
    }
    
    @Override
    public String visitCssProperty(CssPropertyNode node) {
        return node.getProperty() + ": " + node.getValue() + ";\n";
    }
    
    @Override
    public String visitCssRule(CssRuleNode node) {
        StringBuilder result = new StringBuilder();
        String selector = node.getResolvedSelector() != null ? 
            node.getResolvedSelector() : processSelector(node.getSelector());
        
        result.append(selector).append(" {\n");
        indentLevel++;
        for (CssPropertyNode prop : node.getProperties()) {
            result.append(indent()).append(prop.accept(this));
        }
        indentLevel--;
        result.append("}\n\n");
        
        return result.toString();
    }
    
    private String processSelector(String selector) {
        // Handle & symbol in selectors
        if (selector.contains("&") && currentElement != null) {
            String replacement = "";
            
            // Determine replacement based on element's generated class/id or tag name
            if (currentElement.getAttributes() != null) {
                for (AttributeNode attr : currentElement.getAttributes()) {
                    if ("class".equals(attr.getName()) && attr.getValue() != null) {
                        replacement = "." + attr.getValue().split("\\s+")[0]; // Use first class
                        break;
                    } else if ("id".equals(attr.getName()) && attr.getValue() != null) {
                        replacement = "#" + attr.getValue();
                        break;
                    }
                }
            }
            
            // If no class/id found, use tag name
            if (replacement.isEmpty()) {
                replacement = currentElement.getTagName();
            }
            
            // Handle special cases like &:hover, &::before
            selector = selector.replace("&::", replacement + "::");
            selector = selector.replace("&:", replacement + ":");
            selector = selector.replace("& ", replacement + " ");
            selector = selector.replace("&", replacement);
        }
        
        return selector;
    }
    
    @Override
    public String visitTemplate(TemplateNode node) {
        // Templates are expanded when referenced
        return "";
    }
    
    @Override
    public String visitCustom(CustomNode node) {
        // Customs are expanded when referenced
        return "";
    }
    
    @Override
    public String visitImport(ImportNode node) {
        // Imports are handled during semantic analysis
        return "";
    }
    
    @Override
    public String visitNamespace(NamespaceNode node) {
        // Process namespace content
        StringBuilder result = new StringBuilder();
        for (ChtlNode content : node.getContent()) {
            String generated = content.accept(this);
            if (generated != null && !generated.isEmpty()) {
                result.append(generated);
            }
        }
        return result.toString();
    }
    
    @Override
    public String visitConfiguration(ConfigurationNode node) {
        // Configuration affects parsing/generation but doesn't generate output
        return "";
    }
    
    @Override
    public String visitOrigin(OriginNode node) {
        // Origin blocks pass through raw content
        return indent() + node.getContent() + "\n";
    }
    
    @Override
    public String visitEnhancedSelector(EnhancedSelectorNode node) {
        // Enhanced selectors are processed in script content
        return "";
    }
    
    @Override
    public String visitDelete(DeleteNode node) {
        // Delete operations are handled during template expansion
        return "";
    }
    
    @Override
    public String visitInsert(InsertNode node) {
        // Insert operations are handled during template expansion
        return "";
    }
    
    @Override
    public String visitExcept(ExceptNode node) {
        // Except constraints are validated during semantic analysis
        return "";
    }
    
    @Override
    public String visitInherit(InheritNode node) {
        // Inheritance is resolved during template expansion
        return "";
    }
    
    @Override
    public String visitAtReference(AtReferenceNode node) {
        // References are expanded based on their target
        String key = node.getType() + ":" + node.getName();
        String expansion = templateExpansions.get(key);
        return expansion != null ? expansion : "";
    }
    
    @Override
    public String visitSpecialization(SpecializationNode node) {
        // Specializations are applied during template expansion
        return "";
    }
    
    // Helper methods
    private void collectTemplates(ChtlFileNode ast) {
        for (ChtlNode decl : ast.getDeclarations()) {
            if (decl instanceof TemplateNode) {
                TemplateNode template = (TemplateNode) decl;
                String key = template.getType() + ":" + template.getName();
                templateExpansions.put(key, expandTemplate(template));
            } else if (decl instanceof CustomNode) {
                CustomNode custom = (CustomNode) decl;
                String key = custom.getType() + ":" + custom.getName();
                templateExpansions.put(key, expandCustom(custom));
            }
        }
    }
    
    private String expandTemplate(TemplateNode template) {
        StringBuilder result = new StringBuilder();
        for (ChtlNode content : template.getContent()) {
            String expanded = content.accept(this);
            if (expanded != null && !expanded.isEmpty()) {
                result.append(expanded);
            }
        }
        return result.toString();
    }
    
    private String expandCustom(CustomNode custom) {
        // Similar to template expansion but with custom logic
        return expandTemplate(custom);
    }
    
    private void appendAttributes(StringBuilder result, ElementNode node) {
        // Add explicit attributes
        for (AttributeNode attr : node.getAttributes()) {
            result.append(" ").append(attr.getName())
                  .append("=\"").append(escapeHtml(attr.getValue())).append("\"");
        }
        
        // Add generated class
        if (node.getGeneratedClass() != null) {
            result.append(" class=\"").append(node.getGeneratedClass()).append("\"");
        }
        
        // Add generated ID
        if (node.getGeneratedId() != null) {
            result.append(" id=\"").append(node.getGeneratedId()).append("\"");
        }
        
        // Check for inline styles from style blocks
        for (ChtlNode content : node.getContent()) {
            if (content instanceof StyleNode && !((StyleNode) content).isGlobal()) {
                String inlineStyle = content.accept(this);
                if (inlineStyle != null && !inlineStyle.isEmpty()) {
                    result.append(" style=\"").append(inlineStyle).append("\"");
                }
            }
        }
    }
    
    private String processEnhancedSelectors(String jsCode) {
        // Convert {{selector}} to document.querySelector syntax
        return jsCode.replaceAll("\\{\\{([^}]+)\\}\\}", "document.querySelector('$1')");
    }
    
    private boolean isVoidElement(String tagName) {
        Set<String> voidElements = new HashSet<>(Arrays.asList(
            "area", "base", "br", "col", "embed", "hr", "img", "input",
            "link", "meta", "param", "source", "track", "wbr"
        ));
        return voidElements.contains(tagName.toLowerCase());
    }
    
    private boolean hasBlockLevelContent(ElementNode node) {
        for (ChtlNode content : node.getContent()) {
            if (content instanceof ElementNode || content instanceof StyleNode) {
                return true;
            }
        }
        return node.getContent().size() > 1;
    }
    
    private String indent() {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < indentLevel; i++) {
            result.append(INDENT);
        }
        return result.toString();
    }
    
    private String escapeHtml(String text) {
        return text.replace("&", "&amp;")
                  .replace("<", "&lt;")
                  .replace(">", "&gt;")
                  .replace("\"", "&quot;")
                  .replace("'", "&#39;");
    }
    
    @Override
    public String visitInfo(InfoNode node) {
        // Info节点不生成HTML，仅用于模块元信息
        return "";
    }
    
    @Override
    public String visitExport(ExportNode node) {
        // Export节点不生成HTML，仅用于模块导出声明
        return "";
    }
}