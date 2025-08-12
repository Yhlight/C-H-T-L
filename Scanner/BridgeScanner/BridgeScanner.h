#ifndef CHTL_SCANNER_BRIDGESCANNER_H
#define CHTL_SCANNER_BRIDGESCANNER_H

#include <string>
#include <vector>
#include <stack>
#include <memory>
#include "Scanner/Segment/Segment.h"

namespace CHTL {

/**
 * 桥接扫描器 - 负责扫描CHTL代码并切割成不同语言的代码段
 * 主要用于JS编译器与CHTL JS编译器之间的桥接
 */
class BridgeScanner {
public:
    BridgeScanner();
    ~BridgeScanner() = default;
    
    /**
     * 扫描CHTL代码并返回代码段列表
     * @param content CHTL源代码
     * @return 代码段列表
     */
    std::vector<SegmentPtr> scan(const std::string& content);
    
    /**
     * 设置调试模式
     */
    void setDebugMode(bool debug) { debugMode_ = debug; }
    
    /**
     * 获取扫描错误
     */
    const std::vector<std::string>& getErrors() const { return errors_; }
    
private:
    // 扫描状态
    enum class ScanState {
        CHTL,               // CHTL主体
        IN_ELEMENT,         // 在元素内部
        IN_STYLE_BLOCK,     // 在style块中
        IN_SCRIPT_BLOCK,    // 在script块中
        IN_ORIGIN_BLOCK,    // 在原始嵌入块中
        IN_STRING,          // 在字符串中
        IN_COMMENT,         // 在注释中
        IN_TEMPLATE,        // 在模板声明中
        IN_CUSTOM,          // 在自定义声明中
        IN_IMPORT,          // 在导入语句中
        IN_NAMESPACE,       // 在命名空间中
        IN_CONFIG           // 在配置块中
    };
    
    // 扫描上下文
    struct ScanContext {
        ScanState state;
        std::string elementName;
        int braceCount;
        int startLine;
        int startColumn;
    };
    
    // 扫描方法
    void scanCHTL(const std::string& content, std::vector<SegmentPtr>& segments);
    void scanElement(const std::string& content, size_t& pos, std::vector<SegmentPtr>& segments);
    void scanStyleBlock(const std::string& content, size_t& pos, std::vector<SegmentPtr>& segments);
    void scanScriptBlock(const std::string& content, size_t& pos, std::vector<SegmentPtr>& segments);
    void scanOriginBlock(const std::string& content, size_t& pos, std::vector<SegmentPtr>& segments);
    
    // 检测方法
    bool isStyleBlock(const std::string& content, size_t pos) const;
    bool isScriptBlock(const std::string& content, size_t pos) const;
    bool isOriginBlock(const std::string& content, size_t pos) const;
    bool isTemplateDeclaration(const std::string& content, size_t pos) const;
    bool isCustomDeclaration(const std::string& content, size_t pos) const;
    bool containsCHTLJSExtensions(const std::string& jsCode) const;
    
    // 工具方法
    bool isWhitespace(char c) const;
    bool isNewline(char c) const;
    void updatePosition(char c, int& line, int& column);
    void skipWhitespace(const std::string& content, size_t& pos);
    std::string extractIdentifier(const std::string& content, size_t& pos);
    std::string extractUntil(const std::string& content, size_t& pos, char delimiter);
    std::string extractBlock(const std::string& content, size_t& pos);
    int findMatchingBrace(const std::string& content, size_t startPos) const;
    
    // 创建代码段
    SegmentPtr createSegment(LanguageType type, const std::string& content,
                            int startLine, int startColumn, int endLine, int endColumn);
    
    // 错误处理
    void addError(const std::string& error, int line, int column);
    
private:
    // 状态管理
    std::stack<ScanContext> contextStack_;
    ScanContext currentContext_;
    
    // 位置追踪
    int currentLine_;
    int currentColumn_;
    
    // 错误收集
    std::vector<std::string> errors_;
    
    // 调试模式
    bool debugMode_;
};

} // namespace CHTL

#endif // CHTL_SCANNER_BRIDGESCANNER_H