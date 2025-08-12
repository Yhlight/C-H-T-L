package com.chtl.parser;

import com.chtl.ast.*;
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.TerminalNode;

/**
 * Builds CHTL AST from ANTLR parse tree
 */
public class ChtlAstBuilder extends ChtlParserBaseVisitor<ChtlNode> {
    
    private String filename;
    
    public ChtlAstBuilder(String filename) {
        this.filename = filename;
    }
    
    @Override
    public ChtlNode visitChtlFile(ChtlParser.ChtlFileContext ctx) {
        ChtlFileNode fileNode = new ChtlFileNode(filename);
        
        for (ChtlParser.DeclarationContext decl : ctx.declaration()) {
            ChtlNode node = visit(decl);
            if (node != null) {
                fileNode.addDeclaration(node);
            }
        }
        
        return fileNode;
    }
    
    @Override
    public ChtlNode visitElementNode(ChtlParser.ElementNodeContext ctx) {
        if (ctx.IDENTIFIER() != null) {
            String tagName = ctx.IDENTIFIER().getText();
            ElementNode element = new ElementNode(tagName, 
                ctx.getStart().getLine(), 
                ctx.getStart().getCharPositionInLine());
            
            if (ctx.elementContent() != null) {
                for (ChtlParser.ElementContentContext content : ctx.elementContent()) {
                    ChtlNode node = visit(content);
                    if (node != null) {
                        element.addContent(node);
                    }
                }
            }
            
            return element;
        } else if (ctx.atReference() != null) {
            // Handle @Element references
            return visit(ctx.atReference());
        }
        
        return null;
    }
    
    @Override
    public ChtlNode visitTextNode(ChtlParser.TextNodeContext ctx) {
        String text = extractStringLiteral(ctx.stringLiteral());
        return new TextNode(text, 
            ctx.getStart().getLine(), 
            ctx.getStart().getCharPositionInLine());
    }
    
    @Override
    public ChtlNode visitAttribute(ChtlParser.AttributeContext ctx) {
        String name = ctx.IDENTIFIER().getText();
        String value = extractAttributeValue(ctx.attributeValue());
        
        return new AttributeNode(name, value, 
            ctx.getStart().getLine(), 
            ctx.getStart().getCharPositionInLine());
    }
    
    @Override
    public ChtlNode visitStyleBlock(ChtlParser.StyleBlockContext ctx) {
        StyleNode styleNode = new StyleNode(
            ctx.getStart().getLine(), 
            ctx.getStart().getCharPositionInLine());
        
        for (ChtlParser.StyleContentContext content : ctx.styleContent()) {
            ChtlNode node = visitStyleContent(content);
            if (node != null) {
                styleNode.addContent(node);
            }
        }
        
        return styleNode;
    }
    
    @Override
    public ChtlNode visitCssProperty(ChtlParser.CssPropertyContext ctx) {
        String property = ctx.IDENTIFIER().getText();
        String value = extractCssValue(ctx.cssValue());
        
        return new CssPropertyNode(property, value,
            ctx.getStart().getLine(),
            ctx.getStart().getCharPositionInLine());
    }
    
    @Override
    public ChtlNode visitScriptBlock(ChtlParser.ScriptBlockContext ctx) {
        StringBuilder content = new StringBuilder();
        
        for (ChtlParser.JsContentContext jsContent : ctx.jsContent()) {
            if (jsContent.enhancedSelector() != null) {
                // Process enhanced selector {{...}}
                content.append(processEnhancedSelector(jsContent.enhancedSelector()));
            } else if (jsContent.jsStatement() != null) {
                content.append(jsContent.jsStatement().getText());
            }
            content.append(" ");
        }
        
        boolean isLocal = isInsideElement(ctx);
        
        return new ScriptNode(content.toString().trim(), isLocal,
            ctx.getStart().getLine(),
            ctx.getStart().getCharPositionInLine());
    }
    
    @Override
    public ChtlNode visitTemplateDeclaration(ChtlParser.TemplateDeclarationContext ctx) {
        String type = ctx.templateType().getText();
        String name = ctx.IDENTIFIER().getText();
        
        TemplateNode template = new TemplateNode(type, name,
            ctx.getStart().getLine(),
            ctx.getStart().getCharPositionInLine());
        
        for (ChtlParser.TemplateContentContext content : ctx.templateContent()) {
            ChtlNode node = visit(content);
            if (node != null) {
                template.addContent(node);
            }
        }
        
        return template;
    }
    
    @Override
    public ChtlNode visitCustomDeclaration(ChtlParser.CustomDeclarationContext ctx) {
        String type = ctx.templateType().getText();
        String name = ctx.IDENTIFIER().getText();
        
        CustomNode custom = new CustomNode(type, name,
            ctx.getStart().getLine(),
            ctx.getStart().getCharPositionInLine());
        
        for (ChtlParser.CustomContentContext content : ctx.customContent()) {
            ChtlNode node = visit(content);
            if (node != null) {
                custom.addContent(node);
            }
        }
        
        return custom;
    }
    
    @Override
    public ChtlNode visitImportDeclaration(ChtlParser.ImportDeclarationContext ctx) {
        ImportNode importNode = new ImportNode(
            ctx.getStart().getLine(),
            ctx.getStart().getCharPositionInLine());
        
        ChtlParser.ImportTargetContext target = ctx.importTarget();
        
        if (target.AT_HTML() != null) {
            importNode.setImportType("@Html");
        } else if (target.AT_STYLE() != null) {
            importNode.setImportType("@Style");
        } else if (target.AT_JAVASCRIPT() != null) {
            importNode.setImportType("@JavaScript");
        } else if (target.AT_CHTL() != null) {
            importNode.setImportType("@Chtl");
        } else if (target.templateType() != null) {
            importNode.setImportType(target.templateType().getText());
            if (target.IDENTIFIER() != null) {
                importNode.setTargetName(target.IDENTIFIER().getText());
            }
            if (target.CUSTOM() != null) {
                importNode.setCustom(true);
            } else if (target.TEMPLATE() != null) {
                importNode.setTemplate(true);
            }
        }
        
        importNode.setSourcePath(extractStringLiteral(ctx.stringLiteral()));
        
        if (ctx.AS() != null && ctx.IDENTIFIER() != null) {
            importNode.setAlias(ctx.IDENTIFIER().getText());
        }
        
        return importNode;
    }
    
    // Helper methods
    private String extractStringLiteral(ChtlParser.StringLiteralContext ctx) {
        if (ctx.DOUBLE_QUOTE_STRING() != null) {
            String text = ctx.DOUBLE_QUOTE_STRING().getText();
            return text.substring(1, text.length() - 1); // Remove quotes
        } else if (ctx.SINGLE_QUOTE_STRING() != null) {
            String text = ctx.SINGLE_QUOTE_STRING().getText();
            return text.substring(1, text.length() - 1); // Remove quotes
        } else if (ctx.UNQUOTED_LITERAL() != null) {
            return ctx.UNQUOTED_LITERAL().getText();
        } else if (ctx.IDENTIFIER() != null) {
            return ctx.IDENTIFIER().getText();
        }
        return "";
    }
    
    private String extractAttributeValue(ChtlParser.AttributeValueContext ctx) {
        if (ctx.stringLiteral() != null) {
            return extractStringLiteral(ctx.stringLiteral());
        } else if (ctx.IDENTIFIER() != null) {
            return ctx.IDENTIFIER().getText();
        } else if (ctx.UNQUOTED_LITERAL() != null) {
            return ctx.UNQUOTED_LITERAL().getText();
        } else if (ctx.NUMBER() != null) {
            return ctx.NUMBER().getText();
        } else if (ctx.DECIMAL() != null) {
            return ctx.DECIMAL().getText();
        }
        return "";
    }
    
    private String extractCssValue(ChtlParser.CssValueContext ctx) {
        StringBuilder value = new StringBuilder();
        
        if (ctx.stringLiteral() != null) {
            value.append(extractStringLiteral(ctx.stringLiteral()));
        } else if (ctx.IDENTIFIER() != null) {
            value.append(ctx.IDENTIFIER().getText());
        } else if (ctx.UNQUOTED_LITERAL() != null) {
            value.append(ctx.UNQUOTED_LITERAL().getText());
        } else if (ctx.NUMBER() != null) {
            value.append(ctx.NUMBER().getText());
        } else if (ctx.DECIMAL() != null) {
            value.append(ctx.DECIMAL().getText());
        } else if (ctx.functionCall() != null) {
            value.append(processFunctionCall(ctx.functionCall()));
        } else if (ctx.cssValue() != null && ctx.cssValue().size() > 1) {
            // Multiple values
            for (int i = 0; i < ctx.cssValue().size(); i++) {
                if (i > 0) value.append(" ");
                value.append(extractCssValue(ctx.cssValue(i)));
            }
        }
        
        return value.toString();
    }
    
    private String processFunctionCall(ChtlParser.FunctionCallContext ctx) {
        StringBuilder result = new StringBuilder();
        result.append(ctx.IDENTIFIER().getText());
        result.append("(");
        
        if (ctx.argumentList() != null) {
            ChtlParser.ArgumentListContext args = ctx.argumentList();
            for (int i = 0; i < args.cssValue().size(); i++) {
                if (i > 0) result.append(", ");
                result.append(extractCssValue(args.cssValue(i)));
            }
        }
        
        result.append(")");
        return result.toString();
    }
    
    private String processEnhancedSelector(ChtlParser.EnhancedSelectorContext ctx) {
        ChtlParser.SelectorExpressionContext selector = ctx.selectorExpression();
        StringBuilder result = new StringBuilder("{{");
        
        if (selector.IDENTIFIER() != null) {
            result.append(selector.IDENTIFIER().getText());
            if (selector.NUMBER() != null) {
                result.append("[").append(selector.NUMBER().getText()).append("]");
            }
        } else if (selector.DOT() != null) {
            result.append(".").append(selector.IDENTIFIER().getText());
        } else if (selector.getText().startsWith("#")) {
            result.append("#").append(selector.IDENTIFIER().getText());
        } else if (selector.cssComplexSelector() != null) {
            result.append(selector.cssComplexSelector().getText());
        }
        
        result.append("}}");
        return result.toString();
    }
    
    private boolean isInsideElement(ParserRuleContext ctx) {
        ParserRuleContext parent = ctx.getParent();
        while (parent != null) {
            if (parent instanceof ChtlParser.ElementNodeContext) {
                return true;
            }
            parent = parent.getParent();
        }
        return false;
    }
}