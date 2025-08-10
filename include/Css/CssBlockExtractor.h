#ifndef CHTL_CSS_BLOCK_EXTRACTOR_H
#define CHTL_CSS_BLOCK_EXTRACTOR_H

#include <string>
#include <vector>
#include <memory>

namespace chtl {

// CSS块提取器 - 简单实现
class CssBlockExtractor {
public:
    CssBlockExtractor() = default;
    ~CssBlockExtractor() = default;
    
    // 提取CSS块
    std::vector<std::string> extractBlocks(const std::string& css);
    
private:
    // 辅助方法
    size_t findBlockEnd(const std::string& css, size_t start);
    bool isInString(const std::string& css, size_t pos);
};

} // namespace chtl

#endif // CHTL_CSS_BLOCK_EXTRACTOR_H