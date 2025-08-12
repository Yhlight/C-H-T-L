#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <memory>

namespace CHTL {

// 代码片段类型
enum class CodeFragmentType {
    CHTL,           // CHTL主体代码
    CSS,            // 原生CSS代码
    JAVASCRIPT,     // 原生JavaScript代码
    CHTL_JAVASCRIPT,// CHTL扩展的JavaScript代码
    RAW_HTML,       // 原始HTML代码
    COMMENT         // 注释
};

// 代码片段
struct CodeFragment {
    CodeFragmentType type;
    std::string content;
    int startLine;
    int startColumn;
    int endLine;
    int endColumn;
    std::string context; // 上下文信息，如所在的元素或块
};

// 扫描器类
class Scanner {
public:
    Scanner();
    ~Scanner() = default;
    
    // 扫描文件并切割成不同类型的代码片段
    std::vector<CodeFragment> scan(const std::string& content);
    
    // 检测代码类型
    CodeFragmentType detectType(const std::string& content, const std::string& context) const;
    
private:
    // 扫描状态
    enum class ScanState {
        CHTL,
        IN_STYLE_BLOCK,
        IN_SCRIPT_BLOCK,
        IN_ORIGIN_BLOCK,
        IN_STRING,
        IN_COMMENT
    };
    
    // 扫描CHTL代码
    void scanCHTL(const std::string& content, std::vector<CodeFragment>& fragments);
    
    // 扫描style块内容
    void scanStyleBlock(const std::string& content, int startLine, int startColumn, 
                       std::vector<CodeFragment>& fragments);
    
    // 扫描script块内容
    void scanScriptBlock(const std::string& content, int startLine, int startColumn,
                        std::vector<CodeFragment>& fragments);
    
    // 检测是否包含CHTL JS扩展语法
    bool containsCHTLJSExtensions(const std::string& jsCode) const;
    
    // 提取原始嵌入块
    void extractOriginBlock(const std::string& content, int& pos, 
                           std::vector<CodeFragment>& fragments);
    
    // 工具函数
    bool isWhitespace(char c) const;
    bool isNewline(char c) const;
    void updatePosition(char c, int& line, int& column);
    std::string extractUntil(const std::string& content, int& pos, 
                            const std::string& delimiter);
    
    // 查找匹配的括号
    int findMatchingBrace(const std::string& content, int startPos) const;
    
    // 状态管理
    ScanState currentState_;
    std::vector<ScanState> stateStack_;
    
    // 位置追踪
    int currentLine_;
    int currentColumn_;
};

} // namespace CHTL

#endif // SCANNER_H