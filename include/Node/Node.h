#ifndef CHTL_NODE_H
#define CHTL_NODE_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <variant>
#include <functional>

namespace chtl {

// 前向声明
class Element;
class Text;
class Node;

// Node类型枚举
enum class NodeType {
    ELEMENT,
    TEXT,
    COMMENT,
    CDATA,
    DOCUMENT,
    DOCUMENT_TYPE,
    FRAGMENT,
    // CHTL特有节点类型
    TEMPLATE,
    CUSTOM,
    STYLE,
    CONFIG,
    IMPORT,
    NAMESPACE,
    OPERATE,
    ORIGIN,
    REFERENCE,  // 引用节点（@Style, @Element, @Var的使用）
    DELETE,     // 删除操作节点
    INFO,       // [Info]块节点
    EXPORT,     // [Export]块节点
    SCRIPT      // [Script]块节点
};

// 属性值类型
using AttributeValue = std::variant<std::string, int, double, bool>;

// 节点基类
class Node : public std::enable_shared_from_this<Node> {
protected:
    NodeType type_;
    std::weak_ptr<Node> parent_;
    std::vector<std::shared_ptr<Node>> children_;
    std::string nodeName_;
    
    // CHTL特有的成员
    std::string tagName_;  // 用于元素标签名或特殊节点类型名
    std::unordered_map<std::string, AttributeValue> attributes_;  // 通用属性存储
    std::vector<std::string> constraints_;  // except约束
    std::vector<std::string> inheritances_;  // 继承列表
    std::vector<std::string> exports_;  // 导出列表
    std::string text_;  // 文本内容（用于文本节点）
    std::vector<std::string> classes_;          // 类名列表
    
public:
    Node(NodeType type, const std::string& name = "")
        : type_(type), nodeName_(name) {}
    
    virtual ~Node() = default;
    
    // 获取节点类型
    NodeType getType() const { return type_; }
    
    // 获取节点名称
    const std::string& getNodeName() const { return nodeName_; }
    void setNodeName(const std::string& name) { nodeName_ = name; }
    
    // 标签名（用于元素和特殊节点）
    const std::string& getTagName() const { return tagName_; }
    void setTagName(const std::string& tagName) { tagName_ = tagName; }
    
    // 属性管理（通用接口）
    virtual void setAttribute(const std::string& name, const AttributeValue& value) {
        attributes_[name] = value;
    }
    virtual AttributeValue getAttribute(const std::string& name) const {
        auto it = attributes_.find(name);
        return it != attributes_.end() ? it->second : AttributeValue("");
    }
    virtual bool hasAttribute(const std::string& name) const {
        return attributes_.find(name) != attributes_.end();
    }
    
    // 文本内容（用于文本节点和其他需要存储文本的节点）
    const std::string& getText() const { return text_; }
    void setText(const std::string& text) { text_ = text; }
    
    // 类名管理
    void addClass(const std::string& className) {
        if (std::find(classes_.begin(), classes_.end(), className) == classes_.end()) {
            classes_.push_back(className);
        }
    }
    
    void removeClass(const std::string& className) {
        classes_.erase(
            std::remove(classes_.begin(), classes_.end(), className), 
            classes_.end()
        );
    }
    
    const std::vector<std::string>& getClasses() const {
        return classes_;
    }
    
    // 约束管理（CHTL except）
    void addConstraint(const std::string& constraint) {
        constraints_.push_back(constraint);
    }
    const std::vector<std::string>& getConstraints() const {
        return constraints_;
    }
    
    // 继承管理（CHTL inherit）
    void addInheritance(const std::string& inheritance) {
        inheritances_.push_back(inheritance);
    }
    const std::vector<std::string>& getInheritances() const {
        return inheritances_;
    }
    
    // 导出管理（CHTL export）
    void addExport(const std::string& exportItem) {
        exports_.push_back(exportItem);
    }
    const std::vector<std::string>& getExports() const {
        return exports_;
    }
    
    // 父节点管理
    std::shared_ptr<Node> getParent() const { return parent_.lock(); }
    void setParent(const std::shared_ptr<Node>& parent) { parent_ = parent; }
    
    // 子节点管理
    const std::vector<std::shared_ptr<Node>>& getChildren() const { return children_; }
    std::vector<std::shared_ptr<Node>>& getChildren() { return children_; }
    void appendChild(const std::shared_ptr<Node>& child) {
        children_.push_back(child);
        child->setParent(shared_from_this());
    }
    void addChild(const std::shared_ptr<Node>& child) {
        appendChild(child);
    }
    void insertBefore(const std::shared_ptr<Node>& child, const std::shared_ptr<Node>& ref);
    void removeChild(const std::shared_ptr<Node>& child);
    void replaceChild(const std::shared_ptr<Node>& newChild, const std::shared_ptr<Node>& oldChild);
    
    // 查找子节点
    std::shared_ptr<Node> getFirstChild() const;
    std::shared_ptr<Node> getLastChild() const;
    std::shared_ptr<Node> getNextSibling() const;
    std::shared_ptr<Node> getPreviousSibling() const;
    
    // 递归查找
    std::vector<std::shared_ptr<Element>> getElementsByTagName(const std::string& tagName);
    std::vector<std::shared_ptr<Element>> getElementsByClassName(const std::string& className);
    std::shared_ptr<Element> getElementById(const std::string& id);
    
    // 克隆节点
    virtual std::shared_ptr<Node> clone(bool deep = true) const = 0;
    
    // 转换为字符串（序列化）
    virtual std::string toString() const = 0;
    
    // 访问者模式支持
    class Visitor {
    public:
        virtual ~Visitor() = default;
        virtual void visitElement(Element* element) = 0;
        virtual void visitText(Text* text) = 0;
    };
    
    virtual void accept(Visitor* visitor) = 0;
};

// 元素节点
class Element : public Node {
private:
    std::string tagName_;
    std::unordered_map<std::string, AttributeValue> attributes_;
    std::vector<std::string> classList_;
    std::string id_;
    
    // CHTL特有属性
    bool isCustomElement_ = false;
    bool isTemplateInstance_ = false;
    std::string templateName_;
    std::unordered_map<std::string, std::string> styleProperties_;
    
public:
    Element(const std::string& tagName)
        : Node(NodeType::ELEMENT, tagName), tagName_(tagName) {}
    
    // 标签名
    const std::string& getTagName() const { return tagName_; }
    void setTagName(const std::string& tagName) { tagName_ = tagName; }
    
    // 属性管理
    void setAttribute(const std::string& name, const AttributeValue& value) override;
    AttributeValue getAttribute(const std::string& name) const override;
    bool hasAttribute(const std::string& name) const override;
    void removeAttribute(const std::string& name);
    const std::unordered_map<std::string, AttributeValue>& getAttributes() const { return attributes_; }
    
    // ID管理
    const std::string& getId() const { return id_; }
    void setId(const std::string& id);
    
    // Class管理
    void addClass(const std::string& className);
    void removeClass(const std::string& className);
    bool hasClass(const std::string& className) const;
    const std::vector<std::string>& getClassList() const { return classList_; }
    std::string getClassName() const;
    void setClassName(const std::string& className);
    
    // 样式属性（CHTL inline style）
    void setStyleProperty(const std::string& property, const std::string& value);
    std::string getStyleProperty(const std::string& property) const;
    bool hasStyleProperty(const std::string& property) const;
    const std::unordered_map<std::string, std::string>& getStyleProperties() const { return styleProperties_; }
    
    // CHTL特有方法
    bool isCustomElement() const { return isCustomElement_; }
    void setCustomElement(bool custom) { isCustomElement_ = custom; }
    
    bool isTemplateInstance() const { return isTemplateInstance_; }
    void setTemplateInstance(bool instance) { isTemplateInstance_ = instance; }
    
    const std::string& getTemplateName() const { return templateName_; }
    void setTemplateName(const std::string& name) { templateName_ = name; }
    
    // 查找元素
    std::shared_ptr<Element> querySelector(const std::string& selector);
    std::vector<std::shared_ptr<Element>> querySelectorAll(const std::string& selector);
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override { visitor->visitElement(this); }
    
    // 便捷方法
    std::string getInnerHTML() const;
    void setInnerHTML(const std::string& html);
    std::string getTextContent() const;
    void setTextContent(const std::string& text);
};

// 文本节点
class Text : public Node {
private:
    std::string data_;
    bool isUnquoted_ = false;  // CHTL特有：是否为无引号字面量
    
public:
    Text(const std::string& data = "", bool unquoted = false)
        : Node(NodeType::TEXT, "#text"), data_(data), isUnquoted_(unquoted) {}
    
    // 文本内容
    const std::string& getData() const { return data_; }
    void setData(const std::string& data) { data_ = data; }
    
    // 追加文本
    void appendData(const std::string& data) { data_ += data; }
    
    // CHTL特有
    bool isUnquoted() const { return isUnquoted_; }
    void setUnquoted(bool unquoted) { isUnquoted_ = unquoted; }
    
    // 文本操作
    size_t getLength() const { return data_.length(); }
    std::string substringData(size_t offset, size_t count) const;
    void insertData(size_t offset, const std::string& data);
    void deleteData(size_t offset, size_t count);
    void replaceData(size_t offset, size_t count, const std::string& data);
    
    // 分割文本节点
    std::shared_ptr<Text> splitText(size_t offset);
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override { visitor->visitText(this); }
    
    // 判断是否为空白文本
    bool isWhitespace() const;
    
    // 规范化文本（处理转义字符等）
    std::string getNormalizedData() const;
};

// 工具函数
namespace NodeUtils {
    // 创建元素
    std::shared_ptr<Element> createElement(const std::string& tagName);
    
    // 创建文本节点
    std::shared_ptr<Text> createTextNode(const std::string& data, bool unquoted = false);
    
    // 深度优先遍历
    void traverse(const std::shared_ptr<Node>& node, std::function<void(const std::shared_ptr<Node>&)> callback);
    
    // 查找共同祖先
    std::shared_ptr<Node> findCommonAncestor(const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2);
    
    // 节点路径
    std::vector<std::shared_ptr<Node>> getNodePath(const std::shared_ptr<Node>& node);
    
    // 判断是否为祖先
    bool isAncestor(const std::shared_ptr<Node>& ancestor, const std::shared_ptr<Node>& descendant);
    
    // 序列化为HTML
    std::string toHTML(const std::shared_ptr<Node>& node, bool pretty = false, int indent = 0);
    
    // 序列化为CHTL
    std::string toCHTL(const std::shared_ptr<Node>& node, bool pretty = false, int indent = 0);
}

} // namespace chtl

#endif // CHTL_NODE_H