package com.chtl.ast;

/**
 * Visitor interface for traversing CHTL AST
 */
public interface ChtlVisitor<T> {
    T visitChtlFile(ChtlFileNode node);
    T visitElement(ElementNode node);
    T visitText(TextNode node);
    T visitAttribute(AttributeNode node);
    T visitStyle(StyleNode node);
    T visitScript(ScriptNode node);
    T visitTemplate(TemplateNode node);
    T visitCustom(CustomNode node);
    T visitImport(ImportNode node);
    T visitNamespace(NamespaceNode node);
    T visitConfiguration(ConfigurationNode node);
    T visitOrigin(OriginNode node);
    T visitCssProperty(CssPropertyNode node);
    T visitCssRule(CssRuleNode node);
    T visitEnhancedSelector(EnhancedSelectorNode node);
    T visitDelete(DeleteNode node);
    T visitInsert(InsertNode node);
    T visitExcept(ExceptNode node);
    T visitInherit(InheritNode node);
    T visitAtReference(AtReferenceNode node);
    T visitSpecialization(SpecializationNode node);
}