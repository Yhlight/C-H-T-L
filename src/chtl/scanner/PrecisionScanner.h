#ifndef CHTL_PRECISION_SCANNER_H
#define CHTL_PRECISION_SCANNER_H

#include "CHTLUnifiedScanner.h"
#include <deque>

namespace chtl {
namespace scanner {

// 精准扫描器 - 能够精确切割混合代码并分发给正确的编译器
class PrecisionScanner : public CHTLUnifiedScanner {
public:
    PrecisionScanner();
    
    // 重写扫描方法以实现精准切割
    std::vector<CodeFragment> scan(const std::string& input) override;
    
private:
    // 精准切割script块
    void preciseScanScriptBlock(std::vector<CodeFragment>& fragments);
    
    // 精准切割style块中的CHTL扩展
    void preciseScanStyleBlock(std::vector<CodeFragment>& fragments);
    
    // 切割混合内容
    struct MixedFragment {
        FragmentType type;
        std::string content;
        size_t startPos;
        size_t endPos;
        size_t startLine;
        size_t startColumn;
        size_t endLine;
        size_t endColumn;
    };
    
    // 分析script块并切割成多个片段
    std::vector<MixedFragment> analyzeScriptContent(
        const std::string& content,
        size_t basePos,
        size_t baseLine,
        size_t baseColumn
    );
    
    // 分析style块中的CHTL变量引用
    std::vector<MixedFragment> analyzeStyleContent(
        const std::string& content,
        size_t basePos,
        size_t baseLine,
        size_t baseColumn
    );
    
    // 检测CHTL扩展的精确位置
    struct CHTLExtension {
        enum Type {
            AT_DIRECTIVE,      // @Element, @Style, @Var
            INTERPOLATION,     // {{ }}
            VAR_DECLARATION    // var x = @...
        };
        
        Type type;
        size_t startPos;
        size_t endPos;
        std::string content;
    };
    
    std::vector<CHTLExtension> findCHTLExtensions(const std::string& content);
    
    // 将内容按CHTL扩展位置切割
    std::vector<MixedFragment> splitByExtensions(
        const std::string& content,
        const std::vector<CHTLExtension>& extensions,
        size_t basePos,
        size_t baseLine,
        size_t baseColumn
    );
    
    // 计算行列位置
    struct Position {
        size_t line;
        size_t column;
    };
    
    Position calculatePosition(const std::string& content, size_t pos,
                              size_t baseLine, size_t baseColumn);
    
    // 验证切割的完整性
    bool validateFragments(const std::vector<MixedFragment>& fragments,
                          const std::string& originalContent);
};

// 扫描器工厂 - 创建合适的扫描器实例
class ScannerFactory {
public:
    enum ScannerType {
        UNIFIED,    // 基础统一扫描器
        PRECISION   // 精准切割扫描器
    };
    
    static std::unique_ptr<CHTLUnifiedScanner> create(
        ScannerType type = PRECISION
    );
};

} // namespace scanner
} // namespace chtl

#endif // CHTL_PRECISION_SCANNER_H