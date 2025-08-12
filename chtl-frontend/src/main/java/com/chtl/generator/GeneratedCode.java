package com.chtl.generator;

/**
 * Container for generated HTML, CSS, and JavaScript code
 */
public class GeneratedCode {
    private String html;
    private String css;
    private String javascript;
    
    public GeneratedCode(String html, String css, String javascript) {
        this.html = html;
        this.css = css;
        this.javascript = javascript;
    }
    
    public String getHtml() {
        return html;
    }
    
    public String getCss() {
        return css;
    }
    
    public String getJavascript() {
        return javascript;
    }
    
    /**
     * Get the complete HTML document with embedded CSS and JavaScript
     */
    public String getCompleteHtml() {
        return html;
    }
    
    /**
     * Get only the body content without the HTML structure
     */
    public String getBodyContent() {
        // Extract content between <body> tags
        int bodyStart = html.indexOf("<body>");
        int bodyEnd = html.lastIndexOf("</body>");
        
        if (bodyStart != -1 && bodyEnd != -1) {
            bodyStart += "<body>".length();
            return html.substring(bodyStart, bodyEnd).trim();
        }
        
        return html;
    }
}