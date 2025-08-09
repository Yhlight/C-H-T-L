#ifndef CHTL_SEGMENT_H
#define CHTL_SEGMENT_H

#include <string>
#include <memory>
#include <vector>
#include "Common/Token.h"

namespace chtl {

// 代码段类型
enum class SegmentType {
    JAVASCRIPT,      // 纯JavaScript代码段
    CHTL_JAVASCRIPT, // CHTL JavaScript扩展代码段
    MIXED,          // 混合代码段（需要进一步分割）
    UNKNOWN         // 未知类型
};

// 代码段基类
class Segment {
public:
    struct SourceInfo {
        std::string filename;    // 源文件名
        int startLine;          // 起始行号
        int startColumn;        // 起始列号
        int endLine;           // 结束行号
        int endColumn;         // 结束列号
        
        SourceInfo() : startLine(1), startColumn(1), endLine(1), endColumn(1) {}
        SourceInfo(const std::string& file, int sl, int sc, int el, int ec)
            : filename(file), startLine(sl), startColumn(sc), endLine(el), endColumn(ec) {}
    };
    
protected:
    SegmentType type_;
    std::string content_;
    SourceInfo sourceInfo_;
    std::vector<Token> tokens_;  // 相关的token列表
    bool isProcessed_;          // 是否已被处理
    std::string processingNote_; // 处理备注
    
public:
    Segment(SegmentType type, const std::string& content = "")
        : type_(type), content_(content), isProcessed_(false) {}
    
    virtual ~Segment() = default;
    
    // 基本访问器
    SegmentType getType() const { return type_; }
    const std::string& getContent() const { return content_; }
    void setContent(const std::string& content) { content_ = content; }
    void appendContent(const std::string& content) { content_ += content; }
    
    // 源信息管理
    const SourceInfo& getSourceInfo() const { return sourceInfo_; }
    void setSourceInfo(const SourceInfo& info) { sourceInfo_ = info; }
    void setSourceLocation(const std::string& file, int sl, int sc, int el, int ec) {
        sourceInfo_ = SourceInfo(file, sl, sc, el, ec);
    }
    
    // Token管理
    const std::vector<Token>& getTokens() const { return tokens_; }
    void setTokens(const std::vector<Token>& tokens) { tokens_ = tokens; }
    void addToken(const Token& token) { tokens_.push_back(token); }
    void clearTokens() { tokens_.clear(); }
    
    // 处理状态
    bool isProcessed() const { return isProcessed_; }
    void markProcessed(bool processed = true) { isProcessed_ = processed; }
    const std::string& getProcessingNote() const { return processingNote_; }
    void setProcessingNote(const std::string& note) { processingNote_ = note; }
    
    // 虚方法
    virtual std::string getTypeString() const;
    virtual bool validate() const { return !content_.empty(); }
    virtual std::shared_ptr<Segment> clone() const = 0;
    virtual std::string toString() const;
};

// JavaScript代码段
class JavaScriptSegment : public Segment {
private:
    bool isModule_;      // 是否是ES6模块
    bool isStrict_;      // 是否是严格模式
    
public:
    JavaScriptSegment(const std::string& content = "")
        : Segment(SegmentType::JAVASCRIPT, content), isModule_(false), isStrict_(false) {}
    
    bool isModule() const { return isModule_; }
    void setModule(bool module) { isModule_ = module; }
    bool isStrict() const { return isStrict_; }
    void setStrict(bool strict) { isStrict_ = strict; }
    
    std::shared_ptr<Segment> clone() const override;
    std::string toString() const override;
};

// CHTL JavaScript代码段
class ChtlJavaScriptSegment : public Segment {
public:
    // CHTL特有功能标记
    struct Features {
        bool hasTemplateFunction = false;    // 使用了模板函数
        bool hasOperatorExtension = false;   // 使用了操作符扩展
        bool hasNullSafety = false;         // 使用了空安全操作
        bool hasPipeOperator = false;       // 使用了管道操作符
        bool hasPatternMatching = false;    // 使用了模式匹配
        bool hasAsyncExtensions = false;    // 使用了异步扩展
        bool hasReactiveBindings = false;   // 使用了响应式绑定
    };
    
private:
    Features features_;
    std::vector<std::string> dependencies_;  // CHTL依赖
    
public:
    ChtlJavaScriptSegment(const std::string& content = "")
        : Segment(SegmentType::CHTL_JAVASCRIPT, content) {}
    
    const Features& getFeatures() const { return features_; }
    Features& getFeatures() { return features_; }
    void enableFeature(const std::string& feature);
    
    const std::vector<std::string>& getDependencies() const { return dependencies_; }
    void addDependency(const std::string& dep) { dependencies_.push_back(dep); }
    
    std::shared_ptr<Segment> clone() const override;
    std::string toString() const override;
};

// 混合代码段（需要进一步分割）
class MixedSegment : public Segment {
private:
    std::vector<std::shared_ptr<Segment>> subSegments_;
    
public:
    MixedSegment(const std::string& content = "")
        : Segment(SegmentType::MIXED, content) {}
    
    const std::vector<std::shared_ptr<Segment>>& getSubSegments() const { return subSegments_; }
    void addSubSegment(std::shared_ptr<Segment> segment) { subSegments_.push_back(segment); }
    void clearSubSegments() { subSegments_.clear(); }
    
    std::shared_ptr<Segment> clone() const override;
    std::string toString() const override;
};

// 代码段工厂
class SegmentFactory {
public:
    static std::shared_ptr<Segment> createSegment(SegmentType type, const std::string& content = "");
    static std::shared_ptr<JavaScriptSegment> createJavaScriptSegment(const std::string& content = "");
    static std::shared_ptr<ChtlJavaScriptSegment> createChtlJavaScriptSegment(const std::string& content = "");
    static std::shared_ptr<MixedSegment> createMixedSegment(const std::string& content = "");
};

} // namespace chtl

#endif // CHTL_SEGMENT_H