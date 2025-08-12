#include "v2/Scanner/Scanner.h"
#include <sstream>
#include <algorithm>

namespace chtl::v2 {

std::string CodeMerger::merge(const std::vector<CodeSegment>& segments) {
    std::ostringstream result;
    
    for (const auto& segment : segments) {
        result << segment.content;
    }
    
    return result.str();
}

std::string CodeMerger::mergeJs(const std::vector<CodeSegment>& segments,
                               const std::map<std::string, std::string>& chtlJsReplacements) {
    std::ostringstream result;
    
    for (const auto& segment : segments) {
        if (segment.type == SegmentType::CHTL_JS) {
            // 查找替换内容
            auto it = chtlJsReplacements.find(segment.chtlJsInfo.placeholder);
            if (it != chtlJsReplacements.end()) {
                result << it->second;
            } else {
                // 如果没有找到替换内容，保留占位符
                result << segment.chtlJsInfo.placeholder;
            }
        } else {
            result << segment.content;
        }
    }
    
    return result.str();
}

std::string CodeMerger::generateSourceMap(const std::vector<CodeSegment>& segments) {
    // 生成源映射
    // 这是一个简化版本，实际应该生成标准的 source map 格式
    std::ostringstream sourceMap;
    sourceMap << "{\n";
    sourceMap << "  \"version\": 3,\n";
    sourceMap << "  \"sources\": [\"original.chtl\"],\n";
    sourceMap << "  \"mappings\": \"";
    
    // 简化的映射生成
    size_t currentLine = 1;
    size_t currentColumn = 1;
    
    for (const auto& segment : segments) {
        // 记录每个段的映射
        if (currentLine < segment.startLine) {
            // 添加换行
            for (size_t i = currentLine; i < segment.startLine; i++) {
                sourceMap << ";";
            }
            currentLine = segment.startLine;
            currentColumn = 1;
        }
        
        // 添加列映射
        if (currentColumn < segment.startColumn) {
            sourceMap << ",";
        }
        
        // 这里应该使用 VLQ 编码，但为了简化，我们只记录位置
        sourceMap << "A"; // 简化的映射
        
        // 更新位置
        currentLine = segment.endLine;
        currentColumn = segment.endColumn;
    }
    
    sourceMap << "\"\n";
    sourceMap << "}\n";
    
    return sourceMap.str();
}

} // namespace chtl::v2