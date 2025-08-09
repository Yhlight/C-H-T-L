#ifndef CHTL_CSS_BLOCK_EXTRACTOR_H
#define CHTL_CSS_BLOCK_EXTRACTOR_H

#include "CssTypes.h"
#include "CssTokenizer.h"
#include <string>
#include <vector>
#include <memory>

namespace chtl {
namespace css {

class CssBlockExtractor {
private:
    CssTokenizer tokenizer_;
    std::vector<CssToken> tokens_;
    size_t currentTokenIndex_;
    
    const CssToken& currentToken() const;
    const CssToken& peekToken(size_t offset = 1) const;
    void advance();
    bool isAtEnd() const;
    
    // 解析方法
    std::shared_ptr<CssBlock> parseBlock();
    std::shared_ptr<CssBlock> parseRuleSet();
    std::shared_ptr<CssBlock> parseAtRule();
    std::string parseSelector();
    std::string collectBlockContent();
    
    // 工具方法
    void skipToBlockStart();
    void skipToBlockEnd();
    int countBraces(const std::string& content);
    
public:
    CssBlockExtractor();
    
    // 提取CSS块
    std::vector<std::shared_ptr<CssBlock>> extractBlocks(const std::string& css);
    
    // 提取特定信息
    std::vector<std::string> extractSelectors(const std::string& css);
    std::vector<std::string> extractClassNames(const std::string& css);
    std::vector<std::string> extractIdNames(const std::string& css);
    std::vector<std::string> extractCustomProperties(const std::string& css);
    std::vector<std::string> extractMediaQueries(const std::string& css);
    std::vector<std::string> extractImports(const std::string& css);
};

} // namespace css
} // namespace chtl

#endif // CHTL_CSS_BLOCK_EXTRACTOR_H