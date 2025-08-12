#include "CodeScanner.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <regex>

namespace chtl {

CodeScanner::CodeScanner() = default;

std::vector<CodeBlock> CodeScanner::scanCode(const std::string& sourceCode) {
    clear();
    
    // 按优先级扫描不同类型的代码块
    scanOriginBlocks(sourceCode);      // 原始嵌入块优先级最高
    scanCHTLJSBlocks(sourceCode);     // CHTL JS块
    scanJSBlocks(sourceCode);         // JavaScript块
    scanCSSBlocks(sourceCode);        // CSS块
    scanCHTLBlocks(sourceCode);       // CHTL块优先级最低
    
    // 后处理
    mergeAdjacentBlocks();
    sortCodeBlocks();
    
    return codeBlocks_;
}

CodeBlockType CodeScanner::identifyBlockType(const std::string& content) {
    std::string trimmed = content;
    
    // 去除前后空白字符
    trimmed.erase(0, trimmed.find_first_not_of(" \t\r\n"));
    trimmed.erase(trimmed.find_last_not_of(" \t\r\n") + 1);
    
    if (trimmed.empty()) {
        return CodeBlockType::UNKNOWN;
    }
    
    // 检查CHTL JS特征
    if (trimmed.find("{{") != std::string::npos || 
        trimmed.find("->") != std::string::npos ||
        trimmed.find("listen") != std::string::npos ||
        trimmed.find("delegate") != std::string::npos ||
        trimmed.find("animate") != std::string::npos) {
        return CodeBlockType::CHTL_JS;
    }
    
    // 检查JavaScript特征
    if (trimmed.find("function") != std::string::npos ||
        trimmed.find("var ") != std::string::npos ||
        trimmed.find("let ") != std::string::npos ||
        trimmed.find("const ") != std::string::npos ||
        trimmed.find("if (") != std::string::npos ||
        trimmed.find("for (") != std::string::npos ||
        trimmed.find("while (") != std::string::npos ||
        trimmed.find("=>") != std::string::npos) {
        return CodeBlockType::JS;
    }
    
    // 检查CSS特征
    if (trimmed.find(":") != std::string::npos && 
        trimmed.find(";") != std::string::npos &&
        (trimmed.find("color") != std::string::npos ||
         trimmed.find("width") != std::string::npos ||
         trimmed.find("height") != std::string::npos ||
         trimmed.find("margin") != std::string::npos ||
         trimmed.find("padding") != std::string::npos)) {
        return CodeBlockType::CSS;
    }
    
    // 检查CHTL特征
    if (trimmed.find("[Template]") != std::string::npos ||
        trimmed.find("[Custom]") != std::string::npos ||
        trimmed.find("[Origin]") != std::string::npos ||
        trimmed.find("@Style") != std::string::npos ||
        trimmed.find("@Element") != std::string::npos ||
        trimmed.find("@Var") != std::string::npos) {
        return CodeBlockType::CHTL;
    }
    
    return CodeBlockType::UNKNOWN;
}

void CodeScanner::clear() {
    codeBlocks_.clear();
}

void CodeScanner::scanOriginBlocks(const std::string& sourceCode) {
    std::regex originPattern(R"(\[Origin\]\s*@(\w+)\s*(\w+)?\s*\{)");
    std::sregex_iterator iter(sourceCode.begin(), sourceCode.end(), originPattern);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        size_t startPos = iter->position();
        std::string type = (*iter)[1].str();
        
        // 查找匹配的右大括号
        size_t endPos = findMatchingBrace(sourceCode, startPos, '{', '}');
        if (endPos == std::string::npos) continue;
        
        // 提取内容
        std::string content = sourceCode.substr(startPos, endPos - startPos + 1);
        
        // 计算行号和列号
        size_t startLine, startColumn, endLine, endColumn;
        calculateLineColumn(sourceCode, startPos, startLine, startColumn);
        calculateLineColumn(sourceCode, endPos, endLine, endColumn);
        
        // 确定类型
        CodeBlockType blockType = CodeBlockType::UNKNOWN;
        if (type == "Html") blockType = CodeBlockType::HTML;
        else if (type == "Style" || type == "CSS") blockType = CodeBlockType::CSS;
        else if (type == "JavaScript" || type == "JS") blockType = CodeBlockType::JS;
        
        if (blockType != CodeBlockType::UNKNOWN) {
            codeBlocks_.emplace_back(blockType, content, startLine, endLine, startColumn, endColumn);
        }
    }
}

void CodeScanner::scanCHTLJSBlocks(const std::string& sourceCode) {
    // 扫描script块中的CHTL JS代码
    std::regex scriptPattern(R"(script\s*\{)");
    std::sregex_iterator iter(sourceCode.begin(), sourceCode.end(), scriptPattern);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        size_t startPos = iter->position();
        
        // 查找匹配的右大括号
        size_t endPos = findMatchingBrace(sourceCode, startPos, '{', '}');
        if (endPos == std::string::npos) continue;
        
        // 提取内容
        std::string content = sourceCode.substr(startPos, endPos - startPos + 1);
        
        // 检查是否包含CHTL JS特征
        if (content.find("{{") != std::string::npos ||
            content.find("->") != std::string::npos ||
            content.find("listen") != std::string::npos ||
            content.find("delegate") != std::string::npos ||
            content.find("animate") != std::string::npos) {
            
            // 计算行号和列号
            size_t startLine, startColumn, endLine, endColumn;
            calculateLineColumn(sourceCode, startPos, startLine, startColumn);
            calculateLineColumn(sourceCode, endPos, endLine, endColumn);
            
            codeBlocks_.emplace_back(CodeBlockType::CHTL_JS, content, startLine, endLine, startColumn, endColumn);
        }
    }
}

void CodeScanner::scanJSBlocks(const std::string& sourceCode) {
    // 扫描script块中的普通JavaScript代码
    std::regex scriptPattern(R"(script\s*\{)");
    std::sregex_iterator iter(sourceCode.begin(), sourceCode.end(), scriptPattern);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        size_t startPos = iter->position();
        
        // 查找匹配的右大括号
        size_t endPos = findMatchingBrace(sourceCode, startPos, '{', '}');
        if (endPos == std::string::npos) continue;
        
        // 提取内容
        std::string content = sourceCode.substr(startPos, endPos - startPos + 1);
        
        // 检查是否不包含CHTL JS特征（即普通JS）
        if (content.find("{{") == std::string::npos &&
            content.find("->") == std::string::npos &&
            content.find("listen") == std::string::npos &&
            content.find("delegate") == std::string::npos &&
            content.find("animate") == std::string::npos) {
            
            // 计算行号和列号
            size_t startLine, startColumn, endLine, endColumn;
            calculateLineColumn(sourceCode, startPos, startLine, startColumn);
            calculateLineColumn(sourceCode, endPos, endLine, endColumn);
            
            codeBlocks_.emplace_back(CodeBlockType::JS, content, startLine, endLine, startColumn, endColumn);
        }
    }
}

void CodeScanner::scanCSSBlocks(const std::string& sourceCode) {
    // 扫描style块中的CSS代码
    std::regex stylePattern(R"(style\s*\{)");
    std::sregex_iterator iter(sourceCode.begin(), sourceCode.end(), stylePattern);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        size_t startPos = iter->position();
        
        // 查找匹配的右大括号
        size_t endPos = findMatchingBrace(sourceCode, startPos, '{', '}');
        if (endPos == std::string::npos) continue;
        
        // 提取内容
        std::string content = sourceCode.substr(startPos, endPos - startPos + 1);
        
        // 计算行号和列号
        size_t startLine, startColumn, endLine, endColumn;
        calculateLineColumn(sourceCode, startPos, startLine, startColumn);
        calculateLineColumn(sourceCode, endPos, endLine, endColumn);
        
        codeBlocks_.emplace_back(CodeBlockType::CSS, content, startLine, endLine, startColumn, endColumn);
    }
}

void CodeScanner::scanCHTLBlocks(const std::string& sourceCode) {
    // 扫描整个文件作为CHTL代码块
    // 排除已经被识别的其他类型代码块
    
    std::vector<bool> isProcessed(sourceCode.length(), false);
    
    // 标记已处理的代码块
    for (const auto& block : codeBlocks_) {
        // 这里需要根据行号和列号计算位置，简化处理
        // 实际实现中需要更精确的位置计算
    }
    
    // 将未处理的部分作为CHTL代码块
    std::string chtlContent = sourceCode;
    // 这里需要实现更复杂的逻辑来排除已处理的代码块
    
    if (!chtlContent.empty()) {
        codeBlocks_.emplace_back(CodeBlockType::CHTL, chtlContent, 1, 1, 1, 1);
    }
}

size_t CodeScanner::findMatchingBrace(const std::string& code, size_t startPos, char openBrace, char closeBrace) {
    int braceCount = 0;
    size_t pos = startPos;
    
    while (pos < code.length()) {
        char ch = code[pos];
        
        if (ch == openBrace) {
            braceCount++;
        } else if (ch == closeBrace) {
            braceCount--;
            if (braceCount == 0) {
                return pos;
            }
        } else if (ch == '"' || ch == '\'') {
            pos = skipString(code, pos);
            if (pos == std::string::npos) break;
        } else if (ch == '/' && pos + 1 < code.length()) {
            pos = skipComments(code, pos);
            if (pos == std::string::npos) break;
        }
        
        pos++;
    }
    
    return std::string::npos;
}

size_t CodeScanner::findMatchingQuote(const std::string& code, size_t startPos, char quote) {
    size_t pos = startPos + 1;
    
    while (pos < code.length()) {
        if (code[pos] == quote && code[pos - 1] != '\\') {
            return pos;
        }
        pos++;
    }
    
    return std::string::npos;
}

size_t CodeScanner::skipComments(const std::string& code, size_t pos) {
    if (pos + 1 >= code.length()) return pos;
    
    if (code[pos] == '/' && code[pos + 1] == '/') {
        // 单行注释
        size_t endPos = code.find('\n', pos);
        return endPos == std::string::npos ? code.length() - 1 : endPos;
    } else if (code[pos] == '/' && code[pos + 1] == '*') {
        // 多行注释
        size_t endPos = code.find("*/", pos);
        return endPos == std::string::npos ? code.length() - 1 : endPos + 1;
    }
    
    return pos;
}

size_t CodeScanner::skipString(const std::string& code, size_t pos) {
    char quote = code[pos];
    return findMatchingQuote(code, pos, quote);
}

void CodeScanner::calculateLineColumn(const std::string& sourceCode, size_t pos, size_t& line, size_t& column) {
    line = 1;
    column = 1;
    
    for (size_t i = 0; i < pos && i < sourceCode.length(); i++) {
        if (sourceCode[i] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
    }
}

bool CodeScanner::validateCodeBlock(const CodeBlock& block) {
    // 基本验证
    if (block.content.empty()) return false;
    if (block.startLine > block.endLine) return false;
    if (block.startColumn > block.endColumn) return false;
    
    // 类型特定验证
    switch (block.type) {
        case CodeBlockType::CHTL:
            // 检查CHTL语法完整性
            return block.content.find('{') != std::string::npos;
        case CodeBlockType::CSS:
            // 检查CSS语法完整性
            return block.content.find(':') != std::string::npos;
        case CodeBlockType::JS:
        case CodeBlockType::CHTL_JS:
            // 检查JS语法完整性
            return block.content.find('{') != std::string::npos || 
                   block.content.find(';') != std::string::npos;
        default:
            return true;
    }
}

void CodeScanner::mergeAdjacentBlocks() {
    if (codeBlocks_.size() < 2) return;
    
    std::vector<CodeBlock> merged;
    merged.reserve(codeBlocks_.size());
    
    for (size_t i = 0; i < codeBlocks_.size(); i++) {
        if (merged.empty()) {
            merged.push_back(codeBlocks_[i]);
            continue;
        }
        
        CodeBlock& last = merged.back();
        const CodeBlock& current = codeBlocks_[i];
        
        // 检查是否可以合并
        if (last.type == current.type && 
            last.endLine == current.startLine - 1) {
            // 合并代码块
            last.content += "\n" + current.content;
            last.endLine = current.endLine;
            last.endColumn = current.endColumn;
        } else {
            merged.push_back(current);
        }
    }
    
    codeBlocks_ = std::move(merged);
}

void CodeScanner::sortCodeBlocks() {
    std::sort(codeBlocks_.begin(), codeBlocks_.end(), 
        [](const CodeBlock& a, const CodeBlock& b) {
            if (a.startLine != b.startLine) {
                return a.startLine < b.startLine;
            }
            return a.startColumn < b.startColumn;
        });
}

} // namespace chtl