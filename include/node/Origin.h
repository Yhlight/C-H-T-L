#ifndef CHTL_ORIGIN_H
#define CHTL_ORIGIN_H

#include "node/Node.h"

namespace chtl {

// Origin节点 - 原始嵌入，用于嵌入原生HTML、CSS、JavaScript代码
class Origin : public Node {
public:
    enum class OriginType {
        HTML,       // @Html
        STYLE,      // @Style  
        JAVASCRIPT  // @JavaScript
    };
    
private:
    OriginType originType_;
    std::string originName_;    // 可选的名称
    std::string content_;       // 原始代码内容
    bool isInline_ = false;     // 是否为内联形式（带分号结尾）
    
public:
    Origin(OriginType type, const std::string& name = "")
        : Node(NodeType::ORIGIN, "[Origin]"), originType_(type), originName_(name) {}
    
    // 类型和名称管理
    OriginType getOriginType() const { return originType_; }
    const std::string& getOriginName() const { return originName_; }
    void setOriginName(const std::string& name) { originName_ = name; }
    
    // 内容管理
    const std::string& getContent() const { return content_; }
    void setContent(const std::string& content) { content_ = content; }
    void appendContent(const std::string& content) { content_ += content; }
    
    // 内联形式
    void setInline(bool inline_) { isInline_ = inline_; }
    bool isInline() const { return isInline_; }
    
    // 获取类型字符串
    std::string getTypeString() const;
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_ORIGIN_H