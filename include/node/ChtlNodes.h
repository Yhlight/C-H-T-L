#ifndef CHTL_CHTL_NODES_H
#define CHTL_CHTL_NODES_H

#include "node/Node.h"
#include <set>

namespace chtl {

// ==================== Comment节点 ====================
// 支持三种注释类型：单行注释(//)、多行注释(/**/)、HTML注释(<!---->)
class Comment : public Node {
public:
    enum class CommentType {
        SINGLE_LINE,    // //
        MULTI_LINE,     // /* */
        HTML            // <!-- -->
    };
    
private:
    CommentType commentType_;
    std::string content_;
    
public:
    Comment(CommentType type, const std::string& content = "")
        : Node(NodeType::COMMENT, "#comment"), commentType_(type), content_(content) {}
    
    CommentType getCommentType() const { return commentType_; }
    const std::string& getContent() const { return content_; }
    void setContent(const std::string& content) { content_ = content; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

// ==================== Template节点 ====================
// 支持三种模板类型：@Style、@Element、@Var
class Template : public Node {
public:
    enum class TemplateType {
        STYLE,      // @Style模板
        ELEMENT,    // @Element模板
        VAR         // @Var模板
    };
    
private:
    TemplateType templateType_;
    std::string templateName_;
    std::unordered_map<std::string, std::string> parameters_;  // 模板参数
    std::vector<std::string> inheritFrom_;                     // 继承列表
    bool isExplicitInherit_ = false;                          // 是否显式inherit
    
public:
    Template(TemplateType type, const std::string& name)
        : Node(NodeType::TEMPLATE, "[Template]"), templateType_(type), templateName_(name) {}
    
    // 模板类型和名称
    TemplateType getTemplateType() const { return templateType_; }
    const std::string& getTemplateName() const { return templateName_; }
    void setTemplateName(const std::string& name) { templateName_ = name; }
    
    // 参数管理
    void setParameter(const std::string& name, const std::string& value) { parameters_[name] = value; }
    std::string getParameter(const std::string& name) const;
    bool hasParameter(const std::string& name) const { return parameters_.find(name) != parameters_.end(); }
    const std::unordered_map<std::string, std::string>& getParameters() const { return parameters_; }
    
    // 继承管理
    void addInheritance(const std::string& templateName) { inheritFrom_.push_back(templateName); }
    const std::vector<std::string>& getInheritance() const { return inheritFrom_; }
    void setExplicitInherit(bool explicit_) { isExplicitInherit_ = explicit_; }
    bool isExplicitInherit() const { return isExplicitInherit_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

// ==================== Custom节点 ====================
// 支持三种自定义类型：@Element、@Style、@Var
class Custom : public Node {
public:
    enum class CustomType {
        ELEMENT,    // 自定义元素
        STYLE,      // 自定义样式
        VAR         // 自定义变量
    };
    
private:
    CustomType customType_;
    std::string customName_;
    std::unordered_map<std::string, std::string> properties_;
    std::vector<std::string> deleteList_;  // delete语句删除的属性
    
public:
    Custom(CustomType type, const std::string& name)
        : Node(NodeType::CUSTOM, "[Custom]"), customType_(type), customName_(name) {}
    
    // 自定义类型和名称
    CustomType getCustomType() const { return customType_; }
    const std::string& getCustomName() const { return customName_; }
    void setCustomName(const std::string& name) { customName_ = name; }
    
    // 属性管理
    void setProperty(const std::string& name, const std::string& value) { properties_[name] = value; }
    std::string getProperty(const std::string& name) const;
    bool hasProperty(const std::string& name) const { return properties_.find(name) != properties_.end(); }
    const std::unordered_map<std::string, std::string>& getProperties() const { return properties_; }
    
    // 删除列表管理
    void addDelete(const std::string& property) { deleteList_.push_back(property); }
    const std::vector<std::string>& getDeleteList() const { return deleteList_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

// ==================== Style节点 ====================
// 支持局部样式（内联或元素内）和全局样式
class Style : public Node {
public:
    enum class StyleScope {
        LOCAL,      // 局部样式（元素内的style块）
        GLOBAL      // 全局样式（独立的style块）
    };
    
private:
    StyleScope scope_;
    std::string cssContent_;                                    // 原始CSS内容
    std::unordered_map<std::string, std::string> rules_;      // 解析后的CSS规则
    std::vector<std::string> selectors_;                       // CSS选择器
    bool isScoped_ = false;                                    // 是否为作用域样式
    
public:
    Style(StyleScope scope = StyleScope::LOCAL)
        : Node(NodeType::STYLE, "style"), scope_(scope) {}
    
    // 作用域管理
    StyleScope getScope() const { return scope_; }
    void setScope(StyleScope scope) { scope_ = scope; }
    bool isGlobal() const { return scope_ == StyleScope::GLOBAL; }
    bool isLocal() const { return scope_ == StyleScope::LOCAL; }
    
    // CSS内容管理
    const std::string& getCssContent() const { return cssContent_; }
    void setCssContent(const std::string& content) { cssContent_ = content; }
    void appendCssContent(const std::string& content) { cssContent_ += content; }
    
    // CSS规则管理
    void addRule(const std::string& property, const std::string& value) { rules_[property] = value; }
    std::string getRule(const std::string& property) const;
    bool hasRule(const std::string& property) const { return rules_.find(property) != rules_.end(); }
    const std::unordered_map<std::string, std::string>& getRules() const { return rules_; }
    
    // 选择器管理
    void addSelector(const std::string& selector) { selectors_.push_back(selector); }
    const std::vector<std::string>& getSelectors() const { return selectors_; }
    
    // 作用域样式
    void setScoped(bool scoped) { isScoped_ = scoped; }
    bool isScoped() const { return isScoped_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

// ==================== Config节点 ====================
// 配置节点，用于存储[Configuration]块
class Config : public Node {
private:
    std::unordered_map<std::string, std::string> configItems_;
    std::unordered_map<std::string, std::vector<std::string>> arrayItems_;
    std::string configName_;  // 可选的配置名称
    
public:
    Config(const std::string& name = "")
        : Node(NodeType::CONFIG, "[Configuration]"), configName_(name) {}
    
    // 配置名称
    const std::string& getConfigName() const { return configName_; }
    void setConfigName(const std::string& name) { configName_ = name; }
    
    // 配置项管理
    void setConfig(const std::string& key, const std::string& value) { configItems_[key] = value; }
    std::string getConfig(const std::string& key) const;
    bool hasConfig(const std::string& key) const { return configItems_.find(key) != configItems_.end(); }
    const std::unordered_map<std::string, std::string>& getConfigs() const { return configItems_; }
    
    // 数组配置项管理
    void setArrayConfig(const std::string& key, const std::vector<std::string>& values) { arrayItems_[key] = values; }
    std::vector<std::string> getArrayConfig(const std::string& key) const;
    bool hasArrayConfig(const std::string& key) const { return arrayItems_.find(key) != arrayItems_.end(); }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

// ==================== Import节点 ====================
// 导入节点，用于[Import]语句
class Import : public Node {
private:
    std::string filePath_;                      // 导入文件路径
    std::vector<std::string> importItems_;      // 具体导入项（from...as）
    std::unordered_map<std::string, std::string> aliases_;  // 别名映射
    bool isNamespaceImport_ = false;           // 是否为命名空间导入
    
public:
    Import(const std::string& path = "")
        : Node(NodeType::IMPORT, "[Import]"), filePath_(path) {}
    
    // 文件路径管理
    const std::string& getFilePath() const { return filePath_; }
    void setFilePath(const std::string& path) { filePath_ = path; }
    
    // 导入项管理
    void addImportItem(const std::string& item, const std::string& alias = "") {
        importItems_.push_back(item);
        if (!alias.empty()) {
            aliases_[item] = alias;
        }
    }
    const std::vector<std::string>& getImportItems() const { return importItems_; }
    std::string getAlias(const std::string& item) const;
    
    // 命名空间导入
    void setNamespaceImport(bool isNamespace) { isNamespaceImport_ = isNamespace; }
    bool isNamespaceImport() const { return isNamespaceImport_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

// ==================== Namespace节点 ====================
// 命名空间节点
class Namespace : public Node {
private:
    std::string namespaceName_;
    std::vector<std::string> namespacePath_;    // 嵌套命名空间路径
    bool isExport_ = false;                     // 是否导出
    
public:
    Namespace(const std::string& name)
        : Node(NodeType::NAMESPACE, "[Namespace]"), namespaceName_(name) {}
    
    // 命名空间名称
    const std::string& getNamespaceName() const { return namespaceName_; }
    void setNamespaceName(const std::string& name) { namespaceName_ = name; }
    
    // 命名空间路径（支持嵌套）
    void addToPath(const std::string& name) { namespacePath_.push_back(name); }
    const std::vector<std::string>& getNamespacePath() const { return namespacePath_; }
    std::string getFullPath() const;
    
    // 导出标记
    void setExport(bool export_) { isExport_ = export_; }
    bool isExport() const { return isExport_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

// ==================== Operate节点 ====================
// 操作节点，用于insert、delete、replace等操作
class Operate : public Node {
public:
    enum class OperationType {
        INSERT,     // insert操作
        DELETE,     // delete操作
        REPLACE,    // replace操作
        MOVE        // 移动操作（扩展）
    };
    
    enum class Position {
        BEFORE,     // before
        AFTER,      // after
        AT,         // at
        TOP,        // top
        BOTTOM,     // bottom
        DEFAULT     // 默认位置
    };
    
private:
    OperationType operationType_;
    Position position_ = Position::DEFAULT;
    std::string target_;                        // 操作目标
    std::string selector_;                      // 选择器
    std::shared_ptr<Node> content_;            // 操作内容
    std::set<std::string> constraints_;        // except约束
    
public:
    Operate(OperationType type)
        : Node(NodeType::OPERATE, "operate"), operationType_(type) {}
    
    // 操作类型
    OperationType getOperationType() const { return operationType_; }
    void setOperationType(OperationType type) { operationType_ = type; }
    
    // 位置管理
    Position getPosition() const { return position_; }
    void setPosition(Position pos) { position_ = pos; }
    
    // 目标和选择器
    const std::string& getTarget() const { return target_; }
    void setTarget(const std::string& target) { target_ = target; }
    
    const std::string& getSelector() const { return selector_; }
    void setSelector(const std::string& selector) { selector_ = selector; }
    
    // 操作内容
    std::shared_ptr<Node> getContent() const { return content_; }
    void setContent(const std::shared_ptr<Node>& content) { content_ = content; }
    
    // 约束管理
    void addConstraint(const std::string& constraint) { constraints_.insert(constraint); }
    bool hasConstraint(const std::string& constraint) const { return constraints_.find(constraint) != constraints_.end(); }
    const std::set<std::string>& getConstraints() const { return constraints_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

// 扩展Node::Visitor以支持新的节点类型
class ExtendedVisitor : public Node::Visitor {
public:
    virtual ~ExtendedVisitor() = default;
    
    // 基本访问方法（继承自Node::Visitor）
    virtual void visitElement(Element* element) override = 0;
    virtual void visitText(Text* text) override = 0;
    
    // 新增的访问方法
    virtual void visitComment(Comment* comment) = 0;
    virtual void visitTemplate(Template* template_) = 0;
    virtual void visitCustom(Custom* custom) = 0;
    virtual void visitStyle(Style* style) = 0;
    virtual void visitConfig(Config* config) = 0;
    virtual void visitImport(Import* import) = 0;
    virtual void visitNamespace(Namespace* namespace_) = 0;
    virtual void visitOperate(Operate* operate) = 0;
};

} // namespace chtl

#endif // CHTL_CHTL_NODES_H