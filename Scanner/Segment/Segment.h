#ifndef CHTL_SCANNER_SEGMENT_H
#define CHTL_SCANNER_SEGMENT_H

#include <string>
#include <memory>
#include "Common/Types.h"

namespace CHTL {

/**
 * 代码段 - 表示扫描后的代码片段
 */
class Segment {
public:
    Segment(LanguageType type, const std::string& content, 
            int startLine, int startColumn, int endLine, int endColumn)
        : type_(type), content_(content), 
          startLine_(startLine), startColumn_(startColumn),
          endLine_(endLine), endColumn_(endColumn) {}
    
    // 获取语言类型
    LanguageType getType() const { return type_; }
    
    // 获取内容
    const std::string& getContent() const { return content_; }
    
    // 获取位置信息
    int getStartLine() const { return startLine_; }
    int getStartColumn() const { return startColumn_; }
    int getEndLine() const { return endLine_; }
    int getEndColumn() const { return endColumn_; }
    
    // 设置父段（用于嵌套结构）
    void setParent(Segment* parent) { parent_ = parent; }
    Segment* getParent() const { return parent_; }
    
    // 设置上下文信息
    void setContext(const std::string& context) { context_ = context; }
    const std::string& getContext() const { return context_; }
    
    // 设置所属元素（如在哪个元素的style或script块中）
    void setOwnerElement(const std::string& element) { ownerElement_ = element; }
    const std::string& getOwnerElement() const { return ownerElement_; }
    
    // 调试信息
    std::string toString() const;
    
private:
    LanguageType type_;
    std::string content_;
    int startLine_;
    int startColumn_;
    int endLine_;
    int endColumn_;
    
    Segment* parent_ = nullptr;
    std::string context_;      // 上下文信息，如 "style", "script", "origin"
    std::string ownerElement_;  // 所属元素，如 "div", "button"
};

using SegmentPtr = std::shared_ptr<Segment>;

} // namespace CHTL

#endif // CHTL_SCANNER_SEGMENT_H