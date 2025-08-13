#include "PrecisionScanner.h"
#include <regex>
#include <algorithm>
#include <sstream>

namespace chtl {
namespace scanner {

PrecisionScanner::PrecisionScanner() : CHTLUnifiedScanner() {}

std::vector<CodeFragment> PrecisionScanner::scan(const std::string& input) {
    input_ = input;
    pos_ = 0;
    line_ = 1;
    column_ = 1;
    errors_.clear();
    
    std::vector<CodeFragment> fragments;
    
    while (contextStack_.size() > 1) {
        contextStack_.pop();
    }
    contextStack_.push(ScannerContext::TOP_LEVEL);
    
    // 扫描顶层，但使用精准切割
    while (pos_ < input_.size()) {
        skipWhitespace();
        
        if (pos_ >= input_.size()) break;
        
        size_t startPos = pos_;
        size_t startLine = line_;
        size_t startColumn = column_;
        
        // 检查style块
        if (matchKeyword("style") && (peek() == '{' || std::isspace(peek()))) {
            // 跳过style关键字和空白
            while (pos_ < input_.size() && peek() != '{') advance();
            if (peek() == '{') advance();
            
            pushContext(ScannerContext::STYLE_BLOCK);
            preciseScanStyleBlock(fragments);
            popContext();
            
            if (peek() == '}') advance();
        }
        // 检查script块
        else if (matchKeyword("script") && (peek() == '{' || std::isspace(peek()))) {
            // 跳过script关键字和空白
            while (pos_ < input_.size() && peek() != '{') advance();
            if (peek() == '{') advance();
            
            pushContext(ScannerContext::SCRIPT_BLOCK);
            preciseScanScriptBlock(fragments);
            popContext();
            
            if (peek() == '}') advance();
        }
        // 其他CHTL内容
        else {
            std::string chtlContent;
            while (pos_ < input_.size()) {
                if (matchKeyword("style") && (peekAhead(5) == '{' || std::isspace(peekAhead(5)))) {
                    break;
                }
                if (matchKeyword("script") && (peekAhead(6) == '{' || std::isspace(peekAhead(6)))) {
                    break;
                }
                chtlContent += advance();
            }
            
            if (!chtlContent.empty()) {
                addFragment(fragments, FragmentType::CHTL, chtlContent,
                           startLine, startColumn, line_, column_);
            }
        }
    }
    
    return fragments;
}

void PrecisionScanner::preciseScanScriptBlock(std::vector<CodeFragment>& fragments) {
    size_t blockStartPos = pos_;
    size_t blockStartLine = line_;
    size_t blockStartColumn = column_;
    
    // 收集整个script块内容
    std::string scriptContent;
    int braceCount = 1;
    
    while (pos_ < input_.size() && braceCount > 0) {
        char c = peek();
        
        if (c == '{') {
            braceCount++;
        } else if (c == '}') {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        scriptContent += advance();
    }
    
    // 分析并切割内容
    auto mixedFragments = analyzeScriptContent(
        scriptContent, blockStartPos, blockStartLine, blockStartColumn
    );
    
    // 添加切割后的片段
    for (const auto& mf : mixedFragments) {
        addFragment(fragments, mf.type, mf.content,
                   mf.startLine, mf.startColumn, mf.endLine, mf.endColumn);
    }
}

void PrecisionScanner::preciseScanStyleBlock(std::vector<CodeFragment>& fragments) {
    size_t blockStartPos = pos_;
    size_t blockStartLine = line_;
    size_t blockStartColumn = column_;
    
    // 收集整个style块内容
    std::string styleContent;
    int braceCount = 1;
    
    while (pos_ < input_.size() && braceCount > 0) {
        char c = peek();
        
        if (c == '{') {
            braceCount++;
        } else if (c == '}') {
            braceCount--;
            if (braceCount == 0) break;
        }
        
        styleContent += advance();
    }
    
    // 分析style内容中的CHTL变量引用
    auto mixedFragments = analyzeStyleContent(
        styleContent, blockStartPos, blockStartLine, blockStartColumn
    );
    
    // 如果没有CHTL扩展，整个作为CSS片段
    if (mixedFragments.size() == 1 && mixedFragments[0].type == FragmentType::CSS) {
        addFragment(fragments, FragmentType::CSS, styleContent,
                   blockStartLine, blockStartColumn, line_, column_);
    } else {
        // 添加切割后的片段
        for (const auto& mf : mixedFragments) {
            addFragment(fragments, mf.type, mf.content,
                       mf.startLine, mf.startColumn, mf.endLine, mf.endColumn);
        }
    }
}

std::vector<PrecisionScanner::MixedFragment> 
PrecisionScanner::analyzeScriptContent(const std::string& content,
                                      size_t basePos,
                                      size_t baseLine,
                                      size_t baseColumn) {
    // 查找所有CHTL扩展
    auto extensions = findCHTLExtensions(content);
    
    // 如果没有扩展，整个内容是纯JS
    if (extensions.empty()) {
        MixedFragment fragment;
        fragment.type = FragmentType::JS;
        fragment.content = content;
        fragment.startPos = basePos;
        fragment.endPos = basePos + content.length();
        
        auto pos = calculatePosition(content, content.length(), baseLine, baseColumn);
        fragment.startLine = baseLine;
        fragment.startColumn = baseColumn;
        fragment.endLine = pos.line;
        fragment.endColumn = pos.column;
        
        return {fragment};
    }
    
    // 按扩展位置切割
    return splitByExtensions(content, extensions, basePos, baseLine, baseColumn);
}

std::vector<PrecisionScanner::MixedFragment> 
PrecisionScanner::analyzeStyleContent(const std::string& content,
                                     size_t basePos,
                                     size_t baseLine,
                                     size_t baseColumn) {
    // 在CSS中查找CHTL变量引用，如 var(@Var Colors.primary)
    std::vector<CHTLExtension> extensions;
    std::regex varPattern(R"(var\s*\(\s*@(Var|Style)\s+[\w\.]+\s*\))");
    
    std::sregex_iterator it(content.begin(), content.end(), varPattern);
    std::sregex_iterator end;
    
    while (it != end) {
        CHTLExtension ext;
        ext.type = CHTLExtension::AT_DIRECTIVE;
        ext.startPos = it->position();
        ext.endPos = ext.startPos + it->length();
        ext.content = it->str();
        extensions.push_back(ext);
        ++it;
    }
    
    // 如果没有CHTL扩展，返回整个CSS块
    if (extensions.empty()) {
        MixedFragment fragment;
        fragment.type = FragmentType::CSS;
        fragment.content = content;
        fragment.startPos = basePos;
        fragment.endPos = basePos + content.length();
        
        auto pos = calculatePosition(content, content.length(), baseLine, baseColumn);
        fragment.startLine = baseLine;
        fragment.startColumn = baseColumn;
        fragment.endLine = pos.line;
        fragment.endColumn = pos.column;
        
        return {fragment};
    }
    
    // 切割包含CHTL扩展的CSS
    return splitByExtensions(content, extensions, basePos, baseLine, baseColumn);
}

std::vector<PrecisionScanner::CHTLExtension> 
PrecisionScanner::findCHTLExtensions(const std::string& content) {
    std::vector<CHTLExtension> extensions;
    
    size_t pos = 0;
    while (pos < content.length()) {
        // 跳过字符串和注释
        if (content[pos] == '"' || content[pos] == '\'' || content[pos] == '`') {
            char quote = content[pos];
            pos++;
            while (pos < content.length() && content[pos] != quote) {
                if (content[pos] == '\\') pos++;
                pos++;
            }
            pos++;
            continue;
        }
        
        if (pos + 1 < content.length() && content[pos] == '/' && content[pos + 1] == '/') {
            // 单行注释
            while (pos < content.length() && content[pos] != '\n') pos++;
            continue;
        }
        
        if (pos + 1 < content.length() && content[pos] == '/' && content[pos + 1] == '*') {
            // 多行注释
            pos += 2;
            while (pos + 1 < content.length() && 
                   !(content[pos] == '*' && content[pos + 1] == '/')) {
                pos++;
            }
            pos += 2;
            continue;
        }
        
        // 检查 @Element, @Style, @Var
        if (content[pos] == '@') {
            size_t startPos = pos;
            pos++;
            
            std::string directive;
            while (pos < content.length() && std::isalpha(content[pos])) {
                directive += content[pos++];
            }
            
            if (directive == "Element" || directive == "Style" || directive == "Var") {
                CHTLExtension ext;
                ext.type = CHTLExtension::AT_DIRECTIVE;
                ext.startPos = startPos;
                
                // 读取完整的指令
                while (pos < content.length() && std::isspace(content[pos])) pos++;
                while (pos < content.length() && 
                       (std::isalnum(content[pos]) || content[pos] == '_' || content[pos] == '.')) {
                    pos++;
                }
                
                // 检查 from 子句
                size_t tempPos = pos;
                while (tempPos < content.length() && std::isspace(content[tempPos])) tempPos++;
                if (tempPos + 4 < content.length() && 
                    content.substr(tempPos, 4) == "from") {
                    pos = tempPos + 4;
                    while (pos < content.length() && std::isspace(content[pos])) pos++;
                    while (pos < content.length() && 
                           (std::isalnum(content[pos]) || content[pos] == '_' || content[pos] == '.')) {
                        pos++;
                    }
                }
                
                ext.endPos = pos;
                ext.content = content.substr(ext.startPos, ext.endPos - ext.startPos);
                extensions.push_back(ext);
                continue;
            }
        }
        
        // 检查 {{ }}
        if (pos + 1 < content.length() && content[pos] == '{' && content[pos + 1] == '{') {
            CHTLExtension ext;
            ext.type = CHTLExtension::INTERPOLATION;
            ext.startPos = pos;
            pos += 2;
            
            // 读取到 }}
            int braceCount = 0;
            while (pos + 1 < content.length()) {
                if (content[pos] == '{') braceCount++;
                else if (content[pos] == '}') {
                    if (braceCount > 0) braceCount--;
                    else if (pos + 1 < content.length() && content[pos + 1] == '}') {
                        pos += 2;
                        break;
                    }
                }
                pos++;
            }
            
            ext.endPos = pos;
            ext.content = content.substr(ext.startPos, ext.endPos - ext.startPos);
            extensions.push_back(ext);
            continue;
        }
        
        // 检查 var x = @...
        if (pos + 3 < content.length() && content.substr(pos, 3) == "var") {
            size_t tempPos = pos + 3;
            
            // 跳过空白
            while (tempPos < content.length() && std::isspace(content[tempPos])) tempPos++;
            
            // 读取变量名
            size_t varNameStart = tempPos;
            while (tempPos < content.length() && 
                   (std::isalnum(content[tempPos]) || content[tempPos] == '_')) {
                tempPos++;
            }
            
            // 跳过空白
            while (tempPos < content.length() && std::isspace(content[tempPos])) tempPos++;
            
            // 检查 =
            if (tempPos < content.length() && content[tempPos] == '=') {
                tempPos++;
                while (tempPos < content.length() && std::isspace(content[tempPos])) tempPos++;
                
                // 检查 @
                if (tempPos < content.length() && content[tempPos] == '@') {
                    CHTLExtension ext;
                    ext.type = CHTLExtension::VAR_DECLARATION;
                    ext.startPos = pos;
                    
                    // 继续读取到语句结束
                    pos = tempPos;
                    while (pos < content.length() && content[pos] != ';' && content[pos] != '\n') {
                        pos++;
                    }
                    if (content[pos] == ';') pos++;
                    
                    ext.endPos = pos;
                    ext.content = content.substr(ext.startPos, ext.endPos - ext.startPos);
                    extensions.push_back(ext);
                    continue;
                }
            }
        }
        
        pos++;
    }
    
    // 按位置排序
    std::sort(extensions.begin(), extensions.end(),
              [](const CHTLExtension& a, const CHTLExtension& b) {
                  return a.startPos < b.startPos;
              });
    
    return extensions;
}

std::vector<PrecisionScanner::MixedFragment> 
PrecisionScanner::splitByExtensions(const std::string& content,
                                   const std::vector<CHTLExtension>& extensions,
                                   size_t basePos,
                                   size_t baseLine,
                                   size_t baseColumn) {
    std::vector<MixedFragment> fragments;
    size_t lastPos = 0;
    
    for (const auto& ext : extensions) {
        // 添加扩展之前的纯JS/CSS片段
        if (ext.startPos > lastPos) {
            MixedFragment jsFragment;
            jsFragment.type = (currentContext() == ScannerContext::SCRIPT_BLOCK) 
                            ? FragmentType::JS : FragmentType::CSS;
            jsFragment.content = content.substr(lastPos, ext.startPos - lastPos);
            
            auto startPos = calculatePosition(content.substr(0, lastPos), 
                                            lastPos, baseLine, baseColumn);
            auto endPos = calculatePosition(content.substr(0, ext.startPos), 
                                          ext.startPos, baseLine, baseColumn);
            
            jsFragment.startLine = startPos.line;
            jsFragment.startColumn = startPos.column;
            jsFragment.endLine = endPos.line;
            jsFragment.endColumn = endPos.column;
            
            if (!jsFragment.content.empty()) {
                fragments.push_back(jsFragment);
            }
        }
        
        // 添加CHTL扩展片段
        MixedFragment chtlFragment;
        chtlFragment.type = FragmentType::CHTL_JS;
        chtlFragment.content = ext.content;
        
        auto startPos = calculatePosition(content.substr(0, ext.startPos), 
                                        ext.startPos, baseLine, baseColumn);
        auto endPos = calculatePosition(content.substr(0, ext.endPos), 
                                      ext.endPos, baseLine, baseColumn);
        
        chtlFragment.startLine = startPos.line;
        chtlFragment.startColumn = startPos.column;
        chtlFragment.endLine = endPos.line;
        chtlFragment.endColumn = endPos.column;
        
        fragments.push_back(chtlFragment);
        
        lastPos = ext.endPos;
    }
    
    // 添加最后的纯JS/CSS片段
    if (lastPos < content.length()) {
        MixedFragment jsFragment;
        jsFragment.type = (currentContext() == ScannerContext::SCRIPT_BLOCK) 
                        ? FragmentType::JS : FragmentType::CSS;
        jsFragment.content = content.substr(lastPos);
        
        auto startPos = calculatePosition(content.substr(0, lastPos), 
                                        lastPos, baseLine, baseColumn);
        auto endPos = calculatePosition(content, 
                                      content.length(), baseLine, baseColumn);
        
        jsFragment.startLine = startPos.line;
        jsFragment.startColumn = startPos.column;
        jsFragment.endLine = endPos.line;
        jsFragment.endColumn = endPos.column;
        
        if (!jsFragment.content.empty()) {
            fragments.push_back(jsFragment);
        }
    }
    
    return fragments;
}

PrecisionScanner::Position 
PrecisionScanner::calculatePosition(const std::string& content, size_t pos,
                                   size_t baseLine, size_t baseColumn) {
    Position result;
    result.line = baseLine;
    result.column = baseColumn;
    
    for (size_t i = 0; i < pos && i < content.length(); i++) {
        if (content[i] == '\n') {
            result.line++;
            result.column = 1;
        } else {
            result.column++;
        }
    }
    
    return result;
}

bool PrecisionScanner::validateFragments(const std::vector<MixedFragment>& fragments,
                                        const std::string& originalContent) {
    std::string reconstructed;
    
    for (const auto& fragment : fragments) {
        reconstructed += fragment.content;
    }
    
    return reconstructed == originalContent;
}

// 扫描器工厂实现
std::unique_ptr<CHTLUnifiedScanner> 
ScannerFactory::create(ScannerType type) {
    switch (type) {
        case PRECISION:
            return std::make_unique<PrecisionScanner>();
        case UNIFIED:
        default:
            return std::make_unique<CHTLUnifiedScanner>();
    }
}

} // namespace scanner
} // namespace chtl