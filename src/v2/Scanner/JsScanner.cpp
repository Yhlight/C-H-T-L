#include "v2/Scanner/Scanner.h"
#include <regex>
#include <stack>

namespace chtl::v2 {

class JsScanner::Impl {
public:
    Impl() : mode_(ScanMode::HYBRID), line_(1), column_(1), position_(0) {}
    
    std::vector<CodeSegment> scan(const std::string& source, SegmentType initialType) {
        source_ = source;
        segments_.clear();
        errors_.clear();
        resetPosition();
        
        if (mode_ == ScanMode::LOOSE) {
            // 宽判模式：快速分块，提高并行处理能力
            performLooseScan();
        } else if (mode_ == ScanMode::STRICT) {
            // 严判模式：精确提取 CHTL-JS
            performStrictScan();
        } else {
            // 混合模式：先分块，再精确处理
            performHybridScan();
        }
        
        return segments_;
    }
    
    void setScanMode(ScanMode mode) {
        mode_ = mode;
    }
    
    std::vector<std::string> getErrors() const {
        return errors_;
    }
    
    void setChtlJsValidator(std::function<bool(const std::string&)> validator) {
        chtlJsValidator_ = validator;
    }
    
private:
    // 宽判扫描：快速分块
    void performLooseScan() {
        // 策略：基于语法结构快速分割
        // 1. 函数边界
        // 2. 大括号深度
        // 3. 语句结束符
        
        size_t blockStart = 0;
        int braceDepth = 0;
        bool inString = false;
        char stringChar = 0;
        
        while (position_ < source_.length()) {
            char ch = current();
            
            // 跳过字符串内容
            if (!inString && (ch == '"' || ch == '\'' || ch == '`')) {
                inString = true;
                stringChar = ch;
            } else if (inString && ch == stringChar && previous() != '\\') {
                inString = false;
            }
            
            if (!inString) {
                if (ch == '{') {
                    braceDepth++;
                } else if (ch == '}') {
                    braceDepth--;
                    
                    // 在顶层大括号结束时分割
                    if (braceDepth == 0 && position_ - blockStart > 100) {
                        createJsSegment(blockStart, position_ + 1);
                        blockStart = position_ + 1;
                    }
                }
                
                // 在函数声明处分割
                if (braceDepth == 0 && isAtFunctionBoundary()) {
                    if (position_ > blockStart) {
                        createJsSegment(blockStart, position_);
                        blockStart = position_;
                    }
                }
            }
            
            advance();
        }
        
        // 处理剩余代码
        if (blockStart < source_.length()) {
            createJsSegment(blockStart, source_.length());
        }
    }
    
    // 严判扫描：精确提取 CHTL-JS
    void performStrictScan() {
        while (position_ < source_.length()) {
            // 查找 {{ 开始标记
            size_t chtlJsStart = source_.find("{{", position_);
            
            if (chtlJsStart == std::string::npos) {
                // 剩余部分都是普通 JS
                if (position_ < source_.length()) {
                    createJsSegment(position_, source_.length());
                }
                break;
            }
            
            // 处理 {{ 之前的普通 JS
            if (chtlJsStart > position_) {
                createJsSegment(position_, chtlJsStart);
            }
            
            // 查找对应的 }}
            size_t chtlJsEnd = findChtlJsEnd(chtlJsStart + 2);
            
            if (chtlJsEnd == std::string::npos) {
                errors_.push_back("Unclosed CHTL-JS expression at line " + 
                                std::to_string(getLineAt(chtlJsStart)));
                position_ = source_.length();
                break;
            }
            
            // 创建 CHTL-JS 段
            createChtlJsSegment(chtlJsStart, chtlJsEnd + 2);
            position_ = chtlJsEnd + 2;
        }
    }
    
    // 混合扫描：先分块，再处理每块中的 CHTL-JS
    void performHybridScan() {
        // 第一步：宽判分块
        performLooseScan();
        
        // 第二步：处理每个块中的 CHTL-JS
        std::vector<CodeSegment> processedSegments;
        
        for (const auto& segment : segments_) {
            if (segment.type == SegmentType::JS) {
                // 在每个 JS 块中查找 CHTL-JS
                auto subSegments = extractChtlJsFromBlock(segment);
                processedSegments.insert(processedSegments.end(), 
                                       subSegments.begin(), 
                                       subSegments.end());
            } else {
                processedSegments.push_back(segment);
            }
        }
        
        segments_ = std::move(processedSegments);
    }
    
    // 从 JS 块中提取 CHTL-JS
    std::vector<CodeSegment> extractChtlJsFromBlock(const CodeSegment& jsBlock) {
        std::vector<CodeSegment> result;
        size_t pos = 0;
        const std::string& content = jsBlock.content;
        
        while (pos < content.length()) {
            size_t chtlJsStart = content.find("{{", pos);
            
            if (chtlJsStart == std::string::npos) {
                // 剩余部分都是普通 JS
                if (pos < content.length()) {
                    CodeSegment seg = jsBlock;
                    seg.content = content.substr(pos);
                    seg.startColumn = jsBlock.startColumn + pos;
                    result.push_back(seg);
                }
                break;
            }
            
            // {{ 之前的普通 JS
            if (chtlJsStart > pos) {
                CodeSegment seg = jsBlock;
                seg.content = content.substr(pos, chtlJsStart - pos);
                seg.startColumn = jsBlock.startColumn + pos;
                result.push_back(seg);
            }
            
            // 查找对应的 }}
            size_t chtlJsEnd = content.find("}}", chtlJsStart + 2);
            
            if (chtlJsEnd == std::string::npos) {
                errors_.push_back("Unclosed CHTL-JS expression in block");
                break;
            }
            
            // CHTL-JS 段
            CodeSegment chtlSeg;
            chtlSeg.type = SegmentType::CHTL_JS;
            chtlSeg.content = content.substr(chtlJsStart + 2, chtlJsEnd - chtlJsStart - 2);
            chtlSeg.startLine = jsBlock.startLine;
            chtlSeg.startColumn = jsBlock.startColumn + chtlJsStart;
            chtlSeg.endLine = jsBlock.startLine;
            chtlSeg.endColumn = jsBlock.startColumn + chtlJsEnd + 2;
            
            // 记录原始位置，用于后续替换
            chtlSeg.chtlJsInfo.originalStart = chtlJsStart;
            chtlSeg.chtlJsInfo.originalEnd = chtlJsEnd + 2;
            chtlSeg.chtlJsInfo.placeholder = "__CHTL_JS_" + 
                                            std::to_string(result.size()) + "__";
            
            // 验证 CHTL-JS 表达式
            if (chtlJsValidator_ && !chtlJsValidator_(chtlSeg.content)) {
                errors_.push_back("Invalid CHTL-JS expression: " + chtlSeg.content);
            }
            
            result.push_back(chtlSeg);
            pos = chtlJsEnd + 2;
        }
        
        return result;
    }
    
    // 查找 CHTL-JS 结束位置
    size_t findChtlJsEnd(size_t start) {
        int braceCount = 2; // 已经有 {{
        size_t pos = start;
        
        while (pos < source_.length() && braceCount > 0) {
            if (source_[pos] == '{') {
                braceCount++;
            } else if (source_[pos] == '}') {
                braceCount--;
                if (braceCount == 1 && pos + 1 < source_.length() && 
                    source_[pos + 1] == '}') {
                    // 找到 }}
                    return pos;
                }
            }
            pos++;
        }
        
        return std::string::npos;
    }
    
    // 检查是否在函数边界
    bool isAtFunctionBoundary() {
        // 简单的函数边界检测
        if (position_ + 8 < source_.length()) {
            std::string ahead = source_.substr(position_, 8);
            return ahead.find("function") == 0 || 
                   ahead.find("const ") == 0 ||
                   ahead.find("let ") == 0 ||
                   ahead.find("var ") == 0 ||
                   ahead.find("class ") == 0;
        }
        return false;
    }
    
    // 创建 JS 代码段
    void createJsSegment(size_t start, size_t end) {
        if (start >= end) return;
        
        CodeSegment segment;
        segment.type = SegmentType::JS;
        segment.content = source_.substr(start, end - start);
        segment.startLine = getLineAt(start);
        segment.startColumn = getColumnAt(start);
        segment.endLine = getLineAt(end);
        segment.endColumn = getColumnAt(end);
        
        segments_.push_back(segment);
    }
    
    // 创建 CHTL-JS 代码段
    void createChtlJsSegment(size_t start, size_t end) {
        CodeSegment segment;
        segment.type = SegmentType::CHTL_JS;
        segment.content = source_.substr(start + 2, end - start - 4); // 去掉 {{ }}
        segment.startLine = getLineAt(start);
        segment.startColumn = getColumnAt(start);
        segment.endLine = getLineAt(end);
        segment.endColumn = getColumnAt(end);
        
        // 生成占位符
        segment.chtlJsInfo.originalStart = start;
        segment.chtlJsInfo.originalEnd = end;
        segment.chtlJsInfo.placeholder = "__CHTL_JS_" + 
                                        std::to_string(segments_.size()) + "__";
        
        segments_.push_back(segment);
    }
    
    // 位置相关辅助方法
    char current() const {
        return position_ < source_.length() ? source_[position_] : '\0';
    }
    
    char previous() const {
        return position_ > 0 ? source_[position_ - 1] : '\0';
    }
    
    void advance() {
        if (position_ < source_.length()) {
            if (source_[position_] == '\n') {
                line_++;
                column_ = 1;
            } else {
                column_++;
            }
            position_++;
        }
    }
    
    void resetPosition() {
        position_ = 0;
        line_ = 1;
        column_ = 1;
    }
    
    size_t getLineAt(size_t pos) const {
        size_t line = 1;
        for (size_t i = 0; i < pos && i < source_.length(); i++) {
            if (source_[i] == '\n') line++;
        }
        return line;
    }
    
    size_t getColumnAt(size_t pos) const {
        size_t column = 1;
        for (size_t i = pos; i > 0; i--) {
            if (source_[i - 1] == '\n') break;
            column++;
        }
        return column;
    }
    
private:
    std::string source_;
    ScanMode mode_;
    size_t position_;
    size_t line_;
    size_t column_;
    std::vector<CodeSegment> segments_;
    std::vector<std::string> errors_;
    std::function<bool(const std::string&)> chtlJsValidator_;
};

// JsScanner 实现
JsScanner::JsScanner() : impl_(std::make_unique<Impl>()) {}
JsScanner::~JsScanner() = default;

std::vector<CodeSegment> JsScanner::scan(const std::string& source, SegmentType initialType) {
    return impl_->scan(source, initialType);
}

void JsScanner::setScanMode(ScanMode mode) {
    impl_->setScanMode(mode);
}

std::vector<std::string> JsScanner::getErrors() const {
    return impl_->getErrors();
}

void JsScanner::setChtlJsValidator(std::function<bool(const std::string&)> validator) {
    impl_->setChtlJsValidator(validator);
}

} // namespace chtl::v2