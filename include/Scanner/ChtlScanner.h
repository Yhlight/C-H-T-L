#ifndef CHTL_SCANNER_H
#define CHTL_SCANNER_H

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace chtl {

// 代码段类型
enum class SegmentType {
    CHTL,       // CHTL 代码
    CSS,        // CSS 代码
    JS,         // JavaScript 代码
    CHTL_JS,    // CHTL-JS 增强代码
    TEXT        // 纯文本内容
};

// 代码段
struct CodeSegment {
    SegmentType type;
    std::string content;
    size_t startLine;
    size_t startColumn;
    size_t endLine;
    size_t endColumn;
    
    // 对于 CHTL-JS，记录原始位置信息用于拼接
    struct {
        size_t originalStart;
        size_t originalEnd;
        std::string placeholder;
    } chtlJsInfo;
};

// 扫描模式
enum class ScanMode {
    LOOSE,  // 宽判 - 用于 JS 代码分块
    STRICT  // 严判 - 用于精确提取 CHTL-JS
};

class ChtlScanner {
private:
    std::string source_;
    size_t position_;
    size_t line_;
    size_t column_;
    
    // 当前扫描模式
    ScanMode mode_;
    
    // 代码段结果
    std::vector<CodeSegment> segments_;
    
    // JS 代码分析状态
    struct JsContext {
        int braceDepth = 0;
        int parenDepth = 0;
        int bracketDepth = 0;
        bool inString = false;
        char stringChar = 0;
        bool inComment = false;
        bool inRegex = false;
    } jsContext_;
    
public:
    ChtlScanner() : position_(0), line_(1), column_(1), mode_(ScanMode::LOOSE) {}
    
    // 主扫描接口
    std::vector<CodeSegment> scan(const std::string& source, SegmentType initialType);
    
    // 扫描特定类型的代码
    void scanChtl();
    void scanCss();
    void scanJs();
    
private:
    // 宽判扫描 - JS 代码分块
    void looseScanJs();
    CodeSegment extractJsBlock();
    bool shouldSplitJsHere();
    
    // 严判扫描 - CHTL-JS 提取
    void strictScanForChtlJs();
    CodeSegment extractChtlJsSegment();
    bool isValidChtlJsStart();
    size_t findChtlJsEnd();
    
    // 工具方法
    char currentChar() const;
    char peekChar(int offset = 1) const;
    void advance();
    void advanceTo(size_t pos);
    bool isAtEnd() const;
    void skipWhitespace();
    
    // JS 语法感知
    void updateJsContext(char ch);
    bool isInJsString() const { return jsContext_.inString; }
    bool isInJsComment() const { return jsContext_.inComment; }
    
    // CHTL-JS 语法验证
    bool isValidSelector(const std::string& selector);
    bool isValidChtlJsMethod(const std::string& method);
    
    // 创建代码段
    CodeSegment createSegment(SegmentType type, size_t start, size_t end);
    void addSegment(const CodeSegment& segment);
    
    // 错误处理
    void reportError(const std::string& message);
};

// 扫描器工厂
class ScannerFactory {
public:
    static std::unique_ptr<ChtlScanner> create() {
        return std::make_unique<ChtlScanner>();
    }
};

} // namespace chtl

#endif // CHTL_SCANNER_H