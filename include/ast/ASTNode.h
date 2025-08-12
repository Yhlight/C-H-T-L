#ifndef AST_NODE_H
#define AST_NODE_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace CHTL {

// AST节点类型枚举
enum class ASTNodeType {
    // CHTL节点类型
    PROGRAM,
    ELEMENT,
    TEXT_NODE,
    ATTRIBUTE,
    STYLE_BLOCK,
    SCRIPT_BLOCK,
    TEMPLATE_DECLARATION,
    CUSTOM_DECLARATION,
    ORIGIN_BLOCK,
    IMPORT_STATEMENT,
    NAMESPACE_DECLARATION,
    CONFIGURATION_BLOCK,
    COMMENT,
    
    // CSS节点类型
    CSS_RULESET,
    CSS_SELECTOR,
    CSS_DECLARATION,
    CSS_MEDIA_QUERY,
    CSS_KEYFRAMES,
    
    // JavaScript节点类型
    JS_STATEMENT,
    JS_EXPRESSION,
    JS_FUNCTION,
    JS_CLASS,
    JS_VARIABLE,
    
    // CHTL JS扩展节点类型
    CHTL_SELECTOR,
    CHTL_ARROW_ACCESS,
    CHTL_LISTEN,
    CHTL_DELEGATE,
    CHTL_ANIMATE,
    
    // 其他
    UNKNOWN
};

// 前向声明
class ASTVisitor;

// AST节点基类
class ASTNode {
public:
    ASTNode(ASTNodeType type);
    virtual ~ASTNode() = default;
    
    // 访问者模式
    virtual void accept(ASTVisitor* visitor) = 0;
    
    // 获取节点类型
    ASTNodeType getType() const { return type_; }
    
    // 子节点管理
    void addChild(std::shared_ptr<ASTNode> child);
    const std::vector<std::shared_ptr<ASTNode>>& getChildren() const { return children_; }
    
    // 属性管理
    void setAttribute(const std::string& key, const std::string& value);
    std::string getAttribute(const std::string& key) const;
    bool hasAttribute(const std::string& key) const;
    
    // 源码位置信息
    void setLocation(int line, int column);
    int getLine() const { return line_; }
    int getColumn() const { return column_; }
    
protected:
    ASTNodeType type_;
    std::vector<std::shared_ptr<ASTNode>> children_;
    std::unordered_map<std::string, std::string> attributes_;
    int line_ = 0;
    int column_ = 0;
};

// CHTL特定节点类
class ElementNode : public ASTNode {
public:
    ElementNode(const std::string& tagName);
    void accept(ASTVisitor* visitor) override;
    
    const std::string& getTagName() const { return tagName_; }
    void setId(const std::string& id) { id_ = id; }
    void addClass(const std::string& className) { classes_.push_back(className); }
    
    const std::string& getId() const { return id_; }
    const std::vector<std::string>& getClasses() const { return classes_; }
    
private:
    std::string tagName_;
    std::string id_;
    std::vector<std::string> classes_;
};

class TextNode : public ASTNode {
public:
    TextNode(const std::string& text);
    void accept(ASTVisitor* visitor) override;
    
    const std::string& getText() const { return text_; }
    
private:
    std::string text_;
};

class StyleBlockNode : public ASTNode {
public:
    StyleBlockNode();
    void accept(ASTVisitor* visitor) override;
    
    void addInlineStyle(const std::string& property, const std::string& value);
    void addClassSelector(const std::string& className);
    void addIdSelector(const std::string& id);
    
    const std::unordered_map<std::string, std::string>& getInlineStyles() const { return inlineStyles_; }
    const std::vector<std::string>& getClassSelectors() const { return classSelectors_; }
    const std::vector<std::string>& getIdSelectors() const { return idSelectors_; }
    
private:
    std::unordered_map<std::string, std::string> inlineStyles_;
    std::vector<std::string> classSelectors_;
    std::vector<std::string> idSelectors_;
};

class ScriptBlockNode : public ASTNode {
public:
    ScriptBlockNode(const std::string& code, bool isCHTLJS = false);
    void accept(ASTVisitor* visitor) override;
    
    const std::string& getCode() const { return code_; }
    bool isCHTLJS() const { return isCHTLJS_; }
    
private:
    std::string code_;
    bool isCHTLJS_;
};

class TemplateNode : public ASTNode {
public:
    enum class TemplateType { STYLE, ELEMENT, VAR };
    
    TemplateNode(TemplateType templateType, const std::string& name);
    void accept(ASTVisitor* visitor) override;
    
    TemplateType getTemplateType() const { return templateType_; }
    const std::string& getName() const { return name_; }
    
private:
    TemplateType templateType_;
    std::string name_;
};

class CustomNode : public ASTNode {
public:
    enum class CustomType { STYLE, ELEMENT, VAR };
    
    CustomNode(CustomType customType, const std::string& name);
    void accept(ASTVisitor* visitor) override;
    
    CustomType getCustomType() const { return customType_; }
    const std::string& getName() const { return name_; }
    
private:
    CustomType customType_;
    std::string name_;
};

// 访问者接口
class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;
    
    virtual void visitElement(ElementNode* node) = 0;
    virtual void visitText(TextNode* node) = 0;
    virtual void visitStyleBlock(StyleBlockNode* node) = 0;
    virtual void visitScriptBlock(ScriptBlockNode* node) = 0;
    virtual void visitTemplate(TemplateNode* node) = 0;
    virtual void visitCustom(CustomNode* node) = 0;
};

// 工厂函数
std::shared_ptr<ASTNode> createASTNode(ASTNodeType type);

} // namespace CHTL

#endif // AST_NODE_H