#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

namespace chtl::v2 {

// 前向声明
class Node;
using NodePtr = std::shared_ptr<Node>;

/**
 * 节点类型
 */
enum class NodeType {
    DOCUMENT,       // 文档根节点
    ELEMENT,        // HTML 元素
    TEXT,           // 文本节点
    STYLE,          // 样式块
    SCRIPT,         // 脚本块
    TEMPLATE,       // 模板定义
    CUSTOM,         // 自定义组件
    REFERENCE,      // 引用（@Element 等）
    IMPORT,         // 导入声明
    CONFIG,         // 配置声明
    ORIGIN,         // 原始内容声明
    OPERATION       // 操作（inherit, delete, insert）
};

/**
 * 基础节点类
 */
class Node {
public:
    explicit Node(NodeType type) : type_(type) {}
    virtual ~Node() = default;
    
    NodeType getType() const { return type_; }
    
    // 子节点管理
    void addChild(NodePtr child);
    const std::vector<NodePtr>& getChildren() const { return children_; }
    
    // 父节点
    void setParent(Node* parent) { parent_ = parent; }
    Node* getParent() const { return parent_; }
    
    // 位置信息
    void setLocation(int line, int column) {
        line_ = line;
        column_ = column;
    }
    int getLine() const { return line_; }
    int getColumn() const { return column_; }
    
    // 访问者模式
    virtual void accept(class NodeVisitor& visitor) = 0;
    
protected:
    NodeType type_;
    std::vector<NodePtr> children_;
    Node* parent_ = nullptr;
    int line_ = 0;
    int column_ = 0;
};

/**
 * 文档节点
 */
class Document : public Node {
public:
    Document() : Node(NodeType::DOCUMENT) {}
    
    void accept(NodeVisitor& visitor) override;
};

/**
 * 元素节点
 */
class Element : public Node {
public:
    explicit Element(const std::string& tag) 
        : Node(NodeType::ELEMENT), tag_(tag) {}
    
    // 标签名
    const std::string& getTag() const { return tag_; }
    
    // ID
    void setId(const std::string& id) { id_ = id; }
    const std::string& getId() const { return id_; }
    
    // 类名
    void addClass(const std::string& className) { 
        classes_.push_back(className); 
    }
    const std::vector<std::string>& getClasses() const { return classes_; }
    
    // 属性
    void setAttribute(const std::string& name, const std::string& value) {
        attributes_[name] = value;
    }
    const std::map<std::string, std::string>& getAttributes() const { 
        return attributes_; 
    }
    
    // 局部样式
    void setLocalStyle(const std::string& style) { localStyle_ = style; }
    const std::string& getLocalStyle() const { return localStyle_; }
    
    void accept(NodeVisitor& visitor) override;
    
private:
    std::string tag_;
    std::string id_;
    std::vector<std::string> classes_;
    std::map<std::string, std::string> attributes_;
    std::string localStyle_;
};

/**
 * 文本节点
 */
class Text : public Node {
public:
    explicit Text(const std::string& content) 
        : Node(NodeType::TEXT), content_(content) {}
    
    const std::string& getContent() const { return content_; }
    void setContent(const std::string& content) { content_ = content; }
    
    void accept(NodeVisitor& visitor) override;
    
private:
    std::string content_;
};

/**
 * 样式节点
 */
class Style : public Node {
public:
    Style() : Node(NodeType::STYLE) {}
    
    void setCssContent(const std::string& css) { cssContent_ = css; }
    const std::string& getCssContent() const { return cssContent_; }
    
    void setGlobal(bool global) { isGlobal_ = global; }
    bool isGlobal() const { return isGlobal_; }
    
    void accept(NodeVisitor& visitor) override;
    
private:
    std::string cssContent_;
    bool isGlobal_ = true;
};

/**
 * 脚本节点
 */
class Script : public Node {
public:
    Script() : Node(NodeType::SCRIPT) {}
    
    void setJsContent(const std::string& js) { jsContent_ = js; }
    const std::string& getJsContent() const { return jsContent_; }
    
    void setGlobal(bool global) { isGlobal_ = global; }
    bool isGlobal() const { return isGlobal_; }
    
    // 是否包含 CHTL-JS
    void setHasChtlJs(bool has) { hasChtlJs_ = has; }
    bool hasChtlJs() const { return hasChtlJs_; }
    
    void accept(NodeVisitor& visitor) override;
    
private:
    std::string jsContent_;
    bool isGlobal_ = true;
    bool hasChtlJs_ = false;
};

/**
 * 模板节点
 */
class Template : public Node {
public:
    Template() : Node(NodeType::TEMPLATE) {}
    
    void setName(const std::string& name) { name_ = name; }
    const std::string& getName() const { return name_; }
    
    void setType(const std::string& type) { type_ = type; }
    const std::string& getTemplateType() const { return type_; }
    
    void addParameter(const std::string& param, const std::string& defaultValue = "") {
        parameters_.push_back({param, defaultValue});
    }
    const std::vector<std::pair<std::string, std::string>>& getParameters() const {
        return parameters_;
    }
    
    void accept(NodeVisitor& visitor) override;
    
private:
    std::string name_;
    std::string type_;  // @Element, @Style, @Var
    std::vector<std::pair<std::string, std::string>> parameters_;
};

/**
 * 引用节点
 */
class Reference : public Node {
public:
    Reference() : Node(NodeType::REFERENCE) {}
    
    void setReferenceType(const std::string& type) { refType_ = type; }
    const std::string& getReferenceType() const { return refType_; }
    
    void setName(const std::string& name) { name_ = name; }
    const std::string& getName() const { return name_; }
    
    void addArgument(const std::string& arg) { arguments_.push_back(arg); }
    const std::vector<std::string>& getArguments() const { return arguments_; }
    
    void accept(NodeVisitor& visitor) override;
    
private:
    std::string refType_;  // @Element, @Style, @Var
    std::string name_;
    std::vector<std::string> arguments_;
};

/**
 * 节点访问者接口
 */
class NodeVisitor {
public:
    virtual ~NodeVisitor() = default;
    
    virtual void visitDocument(Document* node) = 0;
    virtual void visitElement(Element* node) = 0;
    virtual void visitText(Text* node) = 0;
    virtual void visitStyle(Style* node) = 0;
    virtual void visitScript(Script* node) = 0;
    virtual void visitTemplate(Template* node) = 0;
    virtual void visitReference(Reference* node) = 0;
};

} // namespace chtl::v2