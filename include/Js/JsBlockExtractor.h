#ifndef CHTL_JS_BLOCK_EXTRACTOR_H
#define CHTL_JS_BLOCK_EXTRACTOR_H

#include <string>
#include <vector>
#include <memory>

namespace chtl {

// JavaScript块提取器
class JsBlockExtractor {
public:
    JsBlockExtractor() = default;
    ~JsBlockExtractor() = default;
    
    // 提取JavaScript块
    std::vector<std::string> extractBlocks(const std::string& js);
    
    // 提取函数
    std::vector<std::string> extractFunctions(const std::string& js);
    
    // 提取类
    std::vector<std::string> extractClasses(const std::string& js);
    
private:
    // 辅助方法
    size_t findBlockEnd(const std::string& js, size_t start);
    bool isInString(const std::string& js, size_t pos);
    bool isInComment(const std::string& js, size_t pos);
};

} // namespace chtl

#endif // CHTL_JS_BLOCK_EXTRACTOR_H