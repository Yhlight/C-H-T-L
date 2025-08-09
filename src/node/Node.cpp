#include "node/Node.h"
#include <algorithm>
#include <sstream>
#include <cctype>

namespace chtl {

// ==================== Node 基类实现 ====================

void Node::appendChild(const std::shared_ptr<Node>& child) {
    if (!child) return;
    
    // 如果child已有父节点，先从原父节点移除
    if (auto oldParent = child->getParent()) {
        oldParent->removeChild(child);
    }
    
    children_.push_back(child);
    child->setParent(shared_from_this());
}

void Node::insertBefore(const std::shared_ptr<Node>& child, const std::shared_ptr<Node>& ref) {
    if (!child) return;
    
    // 如果ref为空，则添加到末尾
    if (!ref) {
        appendChild(child);
        return;
    }
    
    // 查找ref的位置
    auto it = std::find(children_.begin(), children_.end(), ref);
    if (it != children_.end()) {
        // 如果child已有父节点，先从原父节点移除
        if (auto oldParent = child->getParent()) {
            oldParent->removeChild(child);
        }
        
        children_.insert(it, child);
        child->setParent(shared_from_this());
    }
}

void Node::removeChild(const std::shared_ptr<Node>& child) {
    if (!child) return;
    
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        (*it)->setParent(nullptr);
        children_.erase(it);
    }
}

void Node::replaceChild(const std::shared_ptr<Node>& newChild, const std::shared_ptr<Node>& oldChild) {
    if (!newChild || !oldChild) return;
    
    auto it = std::find(children_.begin(), children_.end(), oldChild);
    if (it != children_.end()) {
        // 如果newChild已有父节点，先从原父节点移除
        if (auto oldParent = newChild->getParent()) {
            oldParent->removeChild(newChild);
        }
        
        oldChild->setParent(nullptr);
        *it = newChild;
        newChild->setParent(shared_from_this());
    }
}

std::shared_ptr<Node> Node::getFirstChild() const {
    return children_.empty() ? nullptr : children_.front();
}

std::shared_ptr<Node> Node::getLastChild() const {
    return children_.empty() ? nullptr : children_.back();
}

std::shared_ptr<Node> Node::getNextSibling() const {
    auto parent = getParent();
    if (!parent) return nullptr;
    
    const auto& siblings = parent->getChildren();
    auto it = std::find_if(siblings.begin(), siblings.end(),
        [this](const std::shared_ptr<Node>& node) {
            return node.get() == this;
        });
    
    if (it != siblings.end() && ++it != siblings.end()) {
        return *it;
    }
    return nullptr;
}

std::shared_ptr<Node> Node::getPreviousSibling() const {
    auto parent = getParent();
    if (!parent) return nullptr;
    
    const auto& siblings = parent->getChildren();
    auto it = std::find_if(siblings.begin(), siblings.end(),
        [this](const std::shared_ptr<Node>& node) {
            return node.get() == this;
        });
    
    if (it != siblings.begin() && it != siblings.end()) {
        return *(--it);
    }
    return nullptr;
}

std::vector<std::shared_ptr<Element>> Node::getElementsByTagName(const std::string& tagName) {
    std::vector<std::shared_ptr<Element>> result;
    
    NodeUtils::traverse(shared_from_this(), [&](const std::shared_ptr<Node>& node) {
        if (node->getType() == NodeType::ELEMENT) {
            auto element = std::static_pointer_cast<Element>(node);
            if (element->getTagName() == tagName || tagName == "*") {
                result.push_back(element);
            }
        }
    });
    
    return result;
}

std::vector<std::shared_ptr<Element>> Node::getElementsByClassName(const std::string& className) {
    std::vector<std::shared_ptr<Element>> result;
    
    NodeUtils::traverse(shared_from_this(), [&](const std::shared_ptr<Node>& node) {
        if (node->getType() == NodeType::ELEMENT) {
            auto element = std::static_pointer_cast<Element>(node);
            if (element->hasClass(className)) {
                result.push_back(element);
            }
        }
    });
    
    return result;
}

std::shared_ptr<Element> Node::getElementById(const std::string& id) {
    std::shared_ptr<Element> result;
    
    NodeUtils::traverse(shared_from_this(), [&](const std::shared_ptr<Node>& node) {
        if (!result && node->getType() == NodeType::ELEMENT) {
            auto element = std::static_pointer_cast<Element>(node);
            if (element->getId() == id) {
                result = element;
            }
        }
    });
    
    return result;
}

// ==================== Element 类实现 ====================

void Element::setAttribute(const std::string& name, const AttributeValue& value) {
    attributes_[name] = value;
    
    // 特殊处理id和class属性
    if (name == "id") {
        if (auto* strValue = std::get_if<std::string>(&value)) {
            setId(*strValue);
        }
    } else if (name == "class") {
        if (auto* strValue = std::get_if<std::string>(&value)) {
            setClassName(*strValue);
        }
    }
}

AttributeValue Element::getAttribute(const std::string& name) const {
    auto it = attributes_.find(name);
    if (it != attributes_.end()) {
        return it->second;
    }
    return std::string("");  // 返回空字符串作为默认值
}

bool Element::hasAttribute(const std::string& name) const {
    return attributes_.find(name) != attributes_.end();
}

void Element::removeAttribute(const std::string& name) {
    attributes_.erase(name);
    
    // 特殊处理id和class属性
    if (name == "id") {
        id_.clear();
    } else if (name == "class") {
        classList_.clear();
    }
}

void Element::setId(const std::string& id) {
    id_ = id;
    attributes_["id"] = id;
}

void Element::addClass(const std::string& className) {
    if (!className.empty() && !hasClass(className)) {
        classList_.push_back(className);
        attributes_["class"] = getClassName();
    }
}

void Element::removeClass(const std::string& className) {
    classList_.erase(
        std::remove(classList_.begin(), classList_.end(), className),
        classList_.end()
    );
    
    if (classList_.empty()) {
        attributes_.erase("class");
    } else {
        attributes_["class"] = getClassName();
    }
}

bool Element::hasClass(const std::string& className) const {
    return std::find(classList_.begin(), classList_.end(), className) != classList_.end();
}

std::string Element::getClassName() const {
    std::stringstream ss;
    for (size_t i = 0; i < classList_.size(); ++i) {
        if (i > 0) ss << " ";
        ss << classList_[i];
    }
    return ss.str();
}

void Element::setClassName(const std::string& className) {
    classList_.clear();
    
    // 解析空格分隔的类名
    std::istringstream iss(className);
    std::string cls;
    while (iss >> cls) {
        if (!cls.empty()) {
            classList_.push_back(cls);
        }
    }
    
    if (!classList_.empty()) {
        attributes_["class"] = className;
    } else {
        attributes_.erase("class");
    }
}

void Element::setStyleProperty(const std::string& property, const std::string& value) {
    styleProperties_[property] = value;
}

std::string Element::getStyleProperty(const std::string& property) const {
    auto it = styleProperties_.find(property);
    return it != styleProperties_.end() ? it->second : "";
}

bool Element::hasStyleProperty(const std::string& property) const {
    return styleProperties_.find(property) != styleProperties_.end();
}

std::shared_ptr<Node> Element::clone(bool deep) const {
    auto cloned = std::make_shared<Element>(tagName_);
    
    // 复制属性
    cloned->attributes_ = attributes_;
    cloned->classList_ = classList_;
    cloned->id_ = id_;
    cloned->isCustomElement_ = isCustomElement_;
    cloned->isTemplateInstance_ = isTemplateInstance_;
    cloned->templateName_ = templateName_;
    cloned->styleProperties_ = styleProperties_;
    
    // 深度克隆子节点
    if (deep) {
        for (const auto& child : children_) {
            cloned->appendChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Element::toString() const {
    return NodeUtils::toHTML(std::const_pointer_cast<Node>(shared_from_this()));
}

std::string Element::getInnerHTML() const {
    std::stringstream ss;
    for (const auto& child : children_) {
        ss << child->toString();
    }
    return ss.str();
}

void Element::setInnerHTML(const std::string& html) {
    // 清空现有子节点
    children_.clear();
    // TODO: 解析HTML并创建子节点
    (void)html;
}

std::string Element::getTextContent() const {
    std::stringstream ss;
    NodeUtils::traverse(std::const_pointer_cast<Node>(shared_from_this()), 
        [&](const std::shared_ptr<Node>& node) {
            if (node->getType() == NodeType::TEXT) {
                auto text = std::static_pointer_cast<Text>(node);
                ss << text->getData();
            }
        });
    return ss.str();
}

void Element::setTextContent(const std::string& text) {
    // 清空现有子节点
    children_.clear();
    // 添加文本节点
    appendChild(std::make_shared<Text>(text));
}

std::shared_ptr<Element> Element::querySelector(const std::string& selector) {
    // 简单实现：只支持标签名、ID和类选择器
    if (selector.empty()) return nullptr;
    
    if (selector[0] == '#') {
        // ID选择器
        std::string id = selector.substr(1);
        return getElementById(id);
    } else if (selector[0] == '.') {
        // 类选择器
        std::string className = selector.substr(1);
        auto elements = getElementsByClassName(className);
        return elements.empty() ? nullptr : elements[0];
    } else {
        // 标签选择器
        auto elements = getElementsByTagName(selector);
        return elements.empty() ? nullptr : elements[0];
    }
}

std::vector<std::shared_ptr<Element>> Element::querySelectorAll(const std::string& selector) {
    // 简单实现：只支持标签名、ID和类选择器
    if (selector.empty()) return {};
    
    if (selector[0] == '#') {
        // ID选择器
        std::string id = selector.substr(1);
        auto element = getElementById(id);
        return element ? std::vector<std::shared_ptr<Element>>{element} : std::vector<std::shared_ptr<Element>>{};
    } else if (selector[0] == '.') {
        // 类选择器
        std::string className = selector.substr(1);
        return getElementsByClassName(className);
    } else {
        // 标签选择器
        return getElementsByTagName(selector);
    }
}

// ==================== Text 类实现 ====================

std::string Text::substringData(size_t offset, size_t count) const {
    if (offset >= data_.length()) {
        return "";
    }
    return data_.substr(offset, count);
}

void Text::insertData(size_t offset, const std::string& data) {
    if (offset > data_.length()) {
        offset = data_.length();
    }
    data_.insert(offset, data);
}

void Text::deleteData(size_t offset, size_t count) {
    if (offset < data_.length()) {
        data_.erase(offset, count);
    }
}

void Text::replaceData(size_t offset, size_t count, const std::string& data) {
    deleteData(offset, count);
    insertData(offset, data);
}

std::shared_ptr<Text> Text::splitText(size_t offset) {
    if (offset >= data_.length()) {
        return std::make_shared<Text>("", isUnquoted_);
    }
    
    std::string newData = data_.substr(offset);
    data_ = data_.substr(0, offset);
    
    auto newText = std::make_shared<Text>(newData, isUnquoted_);
    
    // 如果有父节点，将新文本节点插入到当前节点之后
    if (auto parent = getParent()) {
        auto nextSibling = getNextSibling();
        if (nextSibling) {
            parent->insertBefore(newText, nextSibling);
        } else {
            parent->appendChild(newText);
        }
    }
    
    return newText;
}

std::shared_ptr<Node> Text::clone(bool deep) const {
    (void)deep; // Text节点没有子节点，deep参数无意义
    return std::make_shared<Text>(data_, isUnquoted_);
}

std::string Text::toString() const {
    return isUnquoted_ ? data_ : getNormalizedData();
}

bool Text::isWhitespace() const {
    return std::all_of(data_.begin(), data_.end(), [](char ch) {
        return std::isspace(static_cast<unsigned char>(ch));
    });
}

std::string Text::getNormalizedData() const {
    std::stringstream ss;
    for (char ch : data_) {
        switch (ch) {
            case '<': ss << "&lt;"; break;
            case '>': ss << "&gt;"; break;
            case '&': ss << "&amp;"; break;
            case '"': ss << "&quot;"; break;
            case '\'': ss << "&#39;"; break;
            default: ss << ch; break;
        }
    }
    return ss.str();
}

// ==================== NodeUtils 实现 ====================

std::shared_ptr<Element> NodeUtils::createElement(const std::string& tagName) {
    return std::make_shared<Element>(tagName);
}

std::shared_ptr<Text> NodeUtils::createTextNode(const std::string& data, bool unquoted) {
    return std::make_shared<Text>(data, unquoted);
}

void NodeUtils::traverse(const std::shared_ptr<Node>& node, std::function<void(const std::shared_ptr<Node>&)> callback) {
    if (!node || !callback) return;
    
    callback(node);
    
    for (const auto& child : node->getChildren()) {
        traverse(child, callback);
    }
}

std::shared_ptr<Node> NodeUtils::findCommonAncestor(const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2) {
    if (!node1 || !node2) return nullptr;
    
    auto path1 = getNodePath(node1);
    auto path2 = getNodePath(node2);
    
    std::shared_ptr<Node> commonAncestor;
    size_t minSize = std::min(path1.size(), path2.size());
    
    for (size_t i = 0; i < minSize; ++i) {
        if (path1[i] == path2[i]) {
            commonAncestor = path1[i];
        } else {
            break;
        }
    }
    
    return commonAncestor;
}

std::vector<std::shared_ptr<Node>> NodeUtils::getNodePath(const std::shared_ptr<Node>& node) {
    std::vector<std::shared_ptr<Node>> path;
    
    auto current = node;
    while (current) {
        path.insert(path.begin(), current);
        current = current->getParent();
    }
    
    return path;
}

bool NodeUtils::isAncestor(const std::shared_ptr<Node>& ancestor, const std::shared_ptr<Node>& descendant) {
    if (!ancestor || !descendant) return false;
    
    auto current = descendant->getParent();
    while (current) {
        if (current == ancestor) {
            return true;
        }
        current = current->getParent();
    }
    
    return false;
}

std::string NodeUtils::toHTML(const std::shared_ptr<Node>& node, bool pretty, int indent) {
    if (!node) return "";
    
    std::stringstream ss;
    std::string indentStr(indent * 2, ' ');
    
    switch (node->getType()) {
        case NodeType::ELEMENT: {
            auto element = std::static_pointer_cast<Element>(node);
            
            if (pretty) ss << indentStr;
            ss << "<" << element->getTagName();
            
            // 输出属性
            for (const auto& [name, value] : element->getAttributes()) {
                ss << " " << name << "=\"";
                std::visit([&ss](const auto& v) {
                    using T = std::decay_t<decltype(v)>;
                    if constexpr (std::is_same_v<T, std::string>) {
                        ss << v;
                    } else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
                        ss << v;
                    } else if constexpr (std::is_same_v<T, bool>) {
                        ss << (v ? "true" : "false");
                    }
                }, value);
                ss << "\"";
            }
            
            const auto& children = element->getChildren();
            if (children.empty()) {
                ss << " />";
                if (pretty) ss << "\n";
            } else {
                ss << ">";
                if (pretty) ss << "\n";
                
                for (const auto& child : children) {
                    ss << toHTML(child, pretty, indent + 1);
                }
                
                if (pretty) ss << indentStr;
                ss << "</" << element->getTagName() << ">";
                if (pretty) ss << "\n";
            }
            break;
        }
        
        case NodeType::TEXT: {
            auto text = std::static_pointer_cast<Text>(node);
            if (pretty && !text->isWhitespace()) {
                ss << indentStr;
            }
            ss << text->toString();
            if (pretty && !text->isWhitespace()) {
                ss << "\n";
            }
            break;
        }
        
        default:
            break;
    }
    
    return ss.str();
}

std::string NodeUtils::toCHTL(const std::shared_ptr<Node>& node, bool pretty, int indent) {
    if (!node) return "";
    
    std::stringstream ss;
    std::string indentStr(indent * 2, ' ');
    
    switch (node->getType()) {
        case NodeType::ELEMENT: {
            auto element = std::static_pointer_cast<Element>(node);
            
            if (pretty) ss << indentStr;
            
            // 检查是否是自定义元素或模板实例
            if (element->isCustomElement()) {
                ss << "@Element " << element->getTagName();
            } else if (element->isTemplateInstance()) {
                ss << "@" << element->getTemplateName();
            } else {
                ss << element->getTagName();
            }
            
            if (pretty) ss << "\n";
            if (pretty) ss << indentStr;
            ss << "{";
            if (pretty) ss << "\n";
            
            // 输出属性
            for (const auto& [name, value] : element->getAttributes()) {
                if (pretty) ss << indentStr << "  ";
                ss << name << ": ";
                std::visit([&ss](const auto& v) {
                    using T = std::decay_t<decltype(v)>;
                    if constexpr (std::is_same_v<T, std::string>) {
                        // 检查是否需要引号
                        if (v.find(' ') != std::string::npos || v.empty()) {
                            ss << "\"" << v << "\"";
                        } else {
                            ss << v;
                        }
                    } else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
                        ss << v;
                    } else if constexpr (std::is_same_v<T, bool>) {
                        ss << (v ? "true" : "false");
                    }
                }, value);
                ss << ";";
                if (pretty) ss << "\n";
            }
            
            // 输出样式属性
            if (!element->getStyleProperties().empty()) {
                if (pretty) ss << indentStr << "  ";
                ss << "style";
                if (pretty) ss << "\n";
                if (pretty) ss << indentStr << "  ";
                ss << "{";
                if (pretty) ss << "\n";
                
                for (const auto& [prop, value] : element->getStyleProperties()) {
                    if (pretty) ss << indentStr << "    ";
                    ss << prop << ": " << value << ";";
                    if (pretty) ss << "\n";
                }
                
                if (pretty) ss << indentStr << "  ";
                ss << "}";
                if (pretty) ss << "\n";
            }
            
            // 输出子节点
            bool hasTextOnly = element->getChildren().size() == 1 && 
                              element->getChildren()[0]->getType() == NodeType::TEXT;
            
            if (hasTextOnly) {
                auto text = std::static_pointer_cast<Text>(element->getChildren()[0]);
                if (pretty) ss << indentStr << "  ";
                ss << "text";
                if (pretty) ss << "\n";
                if (pretty) ss << indentStr << "  ";
                ss << "{";
                if (pretty) ss << "\n";
                if (pretty) ss << indentStr << "    ";
                
                if (text->isUnquoted()) {
                    ss << text->getData();
                } else {
                    ss << "\"" << text->getData() << "\"";
                }
                
                if (pretty) ss << "\n";
                if (pretty) ss << indentStr << "  ";
                ss << "}";
                if (pretty) ss << "\n";
            } else {
                for (const auto& child : element->getChildren()) {
                    ss << toCHTL(child, pretty, indent + 1);
                }
            }
            
            if (pretty) ss << indentStr;
            ss << "}";
            if (pretty) ss << "\n";
            break;
        }
        
        case NodeType::TEXT: {
            auto text = std::static_pointer_cast<Text>(node);
            if (!text->isWhitespace()) {
                if (pretty) ss << indentStr;
                ss << "text { ";
                if (text->isUnquoted()) {
                    ss << text->getData();
                } else {
                    ss << "\"" << text->getData() << "\"";
                }
                ss << " }";
                if (pretty) ss << "\n";
            }
            break;
        }
        
        default:
            break;
    }
    
    return ss.str();
}

} // namespace chtl