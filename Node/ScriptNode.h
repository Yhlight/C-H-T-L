#ifndef CHTL_NODE_SCRIPTNODE_H
#define CHTL_NODE_SCRIPTNODE_H

#include "Node.h"

namespace CHTL {

/**
 * 脚本节点 - 表示script块
 */
class ScriptNode : public Node {
public:
    ScriptNode();
    explicit ScriptNode(const std::string& code, bool isCHTLJS = false);
    ~ScriptNode() = default;
    
    // 实现visitor模式
    void accept(NodeVisitor* visitor) override;
    
    // 脚本内容
    void setCode(const std::string& code) { code_ = code; }
    const std::string& getCode() const { return code_; }
    
    // 是否是CHTL JS
    void setCHTLJS(bool isCHTLJS) { isCHTLJS_ = isCHTLJS; }
    bool isCHTLJS() const { return isCHTLJS_; }
    
    // 脚本类型
    void setType(const std::string& type) { type_ = type; }
    const std::string& getType() const { return type_; }
    
    // 脚本源（外部文件）
    void setSrc(const std::string& src) { src_ = src; }
    const std::string& getSrc() const { return src_; }
    
    // 是否异步加载
    void setAsync(bool async) { async_ = async; }
    bool isAsync() const { return async_; }
    
    // 是否延迟执行
    void setDefer(bool defer) { defer_ = defer; }
    bool isDefer() const { return defer_; }
    
    // 模块脚本
    void setModule(bool module) { module_ = module; }
    bool isModule() const { return module_; }
    
    // 克隆
    NodePtr clone() const override;
    
    // 调试信息
    std::string toString() const override;
    
private:
    std::string code_;
    bool isCHTLJS_ = false;
    std::string type_ = "text/javascript";
    std::string src_;
    bool async_ = false;
    bool defer_ = false;
    bool module_ = false;
};

} // namespace CHTL

#endif // CHTL_NODE_SCRIPTNODE_H