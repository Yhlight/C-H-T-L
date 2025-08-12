#ifndef CHTL_COMPILER_CODE_SCANNER_H
#define CHTL_COMPILER_CODE_SCANNER_H

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace chtl {

// 代码块类型枚举
enum class CodeBlockType {
    CHTL,           // CHTL代码块
    CSS,            // CSS代码块
    JS,             // JavaScript代码块
    CHTL_JS,        // CHTL JS代码块
    HTML,           // HTML代码块
    UNKNOWN         // 未知类型
};

// 代码块结构
struct CodeBlock {
    CodeBlockType type;
    std::string content;
    size_t startLine;
    size_t endLine;
    size_t startColumn;
    size_t endColumn;
    
    CodeBlock(CodeBlockType t, const std::string& c, size_t sl, size_t el, size_t sc, size_t ec)
        : type(t), content(c), startLine(sl), endLine(el), startColumn(sc), endColumn(ec) {}
};

// 代码扫描器类
class CodeScanner {
public:
    CodeScanner();
    ~CodeScanner() = default;

    // 扫描并切割代码
    std::vector<CodeBlock> scanCode(const std::string& sourceCode);
    
    // 识别代码块类型
    CodeBlockType identifyBlockType(const std::string& content);
    
    // 获取扫描结果
    const std::vector<CodeBlock>& getCodeBlocks() const { return codeBlocks_; }
    
    // 清空扫描结果
    void clear();

private:
    std::vector<CodeBlock> codeBlocks_;
    
    // 扫描CHTL代码块
    void scanCHTLBlocks(const std::string& sourceCode);
    
    // 扫描CSS代码块
    void scanCSSBlocks(const std::string& sourceCode);
    
    // 扫描JavaScript代码块
    void scanJSBlocks(const std::string& sourceCode);
    
    // 扫描CHTL JS代码块
    void scanCHTLJSBlocks(const std::string& sourceCode);
    
    // 扫描原始嵌入代码块
    void scanOriginBlocks(const std::string& sourceCode);
    
    // 查找匹配的括号
    size_t findMatchingBrace(const std::string& code, size_t startPos, char openBrace, char closeBrace);
    
    // 查找匹配的引号
    size_t findMatchingQuote(const std::string& code, size_t startPos, char quote);
    
    // 跳过注释
    size_t skipComments(const std::string& code, size_t pos);
    
    // 跳过字符串
    size_t skipString(const std::string& code, size_t pos);
    
    // 计算行号和列号
    void calculateLineColumn(const std::string& sourceCode, size_t pos, size_t& line, size_t& column);
    
    // 验证代码块完整性
    bool validateCodeBlock(const CodeBlock& block);
    
    // 合并相邻的同类型代码块
    void mergeAdjacentBlocks();
    
    // 排序代码块（按起始位置）
    void sortCodeBlocks();
};

} // namespace chtl

#endif // CHTL_COMPILER_CODE_SCANNER_H