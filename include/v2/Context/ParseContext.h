#pragma once

#include "v2/State/ChtlParseState.h"
#include <string>
#include <map>
#include <memory>
#include <vector>

namespace chtl::v2 {

// 前向声明
class Node;

/**
 * 元素数据
 */
struct ElementData {
    std::string tagName;
    std::string id;
    std::vector<std::string> classes;
    std::map<std::string, std::string> attributes;
};

/**
 * 声明数据（模板、自定义等）
 */
struct DeclarationData {
    std::string type;        // Template, Custom, Import 等
    std::string name;        // 声明名称
    std::vector<std::string> parameters;  // 参数列表
    bool isDefinition;       // true: 定义（全局），false: 引用（局部）
};

/**
 * 解析上下文（简化版）
 * 管理当前解析状态的相关信息
 */
class ParseContext {
public:
    ParseContext();
    ~ParseContext();
    
    // ===== 状态管理 =====
    ChtlParseState getState() const { return state_; }
    void setState(ChtlParseState state) { state_ = state; }
    
    ChtlContext getContext() const { return context_; }
    void setContext(ChtlContext ctx) { context_ = ctx; }
    
    // ===== 节点管理 =====
    std::shared_ptr<Node> getCurrentNode() const { return currentNode_; }
    void setCurrentNode(std::shared_ptr<Node> node) { currentNode_ = node; }
    
    // ===== 数据访问 =====
    ElementData& getElementData() { return elementData_; }
    const ElementData& getElementData() const { return elementData_; }
    
    DeclarationData& getDeclarationData() { return declarationData_; }
    const DeclarationData& getDeclarationData() const { return declarationData_; }
    
    // ===== CSS/JS 内容 =====
    std::string& getCssContent() { return cssContent_; }
    const std::string& getCssContent() const { return cssContent_; }
    
    std::string& getJsContent() { return jsContent_; }
    const std::string& getJsContent() const { return jsContent_; }
    
    std::string& getTextContent() { return textContent_; }
    const std::string& getTextContent() const { return textContent_; }
    
    // ===== 位置信息 =====
    void setLocation(int line, int column) {
        currentLine_ = line;
        currentColumn_ = column;
    }
    int getCurrentLine() const { return currentLine_; }
    int getCurrentColumn() const { return currentColumn_; }
    
    // ===== 工具方法 =====
    void reset();
    void resetElementData();
    void resetDeclarationData();
    void resetContent();
    
    std::string toString() const;
    
private:
    // 当前状态
    ChtlParseState state_ = ChtlParseState::INITIAL;
    ChtlContext context_ = ChtlContext::GLOBAL;
    
    // 当前节点
    std::shared_ptr<Node> currentNode_;
    
    // 位置信息
    int currentLine_ = 1;
    int currentColumn_ = 1;
    
    // 状态相关数据
    ElementData elementData_;
    DeclarationData declarationData_;
    
    // 内容缓冲
    std::string cssContent_;    // CSS 内容（整块）
    std::string jsContent_;     // JS 内容（整块）
    std::string textContent_;   // 文本内容
};

} // namespace chtl::v2