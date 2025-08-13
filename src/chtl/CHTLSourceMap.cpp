#include "CHTLSourceMap.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <regex>

namespace chtl {

// Base64字符表
static const char* base64Chars = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// SourceMapGenerator 实现

SourceMapGenerator::SourceMapGenerator() {}

void SourceMapGenerator::setFile(const std::string& file) {
    this->file = file;
}

void SourceMapGenerator::setSourceRoot(const std::string& root) {
    this->sourceRoot = root;
}

int SourceMapGenerator::addSource(const std::string& source, const std::string& content) {
    auto it = sourceIndexMap.find(source);
    if (it != sourceIndexMap.end()) {
        return it->second;
    }
    
    int index = sources.size();
    sources.push_back(source);
    sourcesContent.push_back(content);
    sourceIndexMap[source] = index;
    return index;
}

int SourceMapGenerator::addName(const std::string& name) {
    auto it = nameIndexMap.find(name);
    if (it != nameIndexMap.end()) {
        return it->second;
    }
    
    int index = names.size();
    names.push_back(name);
    nameIndexMap[name] = index;
    return index;
}

void SourceMapGenerator::addMapping(int generatedLine, int generatedColumn,
                                  int sourceIndex, int sourceLine, int sourceColumn,
                                  int nameIndex) {
    // 确保有足够的行
    while (mappings.size() <= generatedLine) {
        mappings.push_back(std::vector<MappingSegment>());
    }
    
    MappingSegment segment;
    segment.generatedColumn = generatedColumn;
    segment.sourceIndex = sourceIndex;
    segment.sourceLine = sourceLine;
    segment.sourceColumn = sourceColumn;
    segment.nameIndex = nameIndex;
    
    mappings[generatedLine].push_back(segment);
}

void SourceMapGenerator::addMapping(int generatedLine, int generatedColumn,
                                  const std::string& source, int sourceLine, int sourceColumn,
                                  const std::string& name) {
    int sourceIndex = addSource(source);
    int nameIndex = name.empty() ? -1 : addName(name);
    addMapping(generatedLine, generatedColumn, sourceIndex, sourceLine, sourceColumn, nameIndex);
}

std::string SourceMapGenerator::generate() {
    return generateJSON();
}

std::string SourceMapGenerator::generateJSON() {
    std::stringstream json;
    json << "{\n";
    json << "  \"version\": 3,\n";
    
    if (!file.empty()) {
        json << "  \"file\": \"" << file << "\",\n";
    }
    
    if (!sourceRoot.empty()) {
        json << "  \"sourceRoot\": \"" << sourceRoot << "\",\n";
    }
    
    // Sources数组
    json << "  \"sources\": [";
    for (size_t i = 0; i < sources.size(); i++) {
        if (i > 0) json << ", ";
        json << "\"" << sources[i] << "\"";
    }
    json << "],\n";
    
    // SourcesContent数组（可选）
    if (!sourcesContent.empty() && 
        std::any_of(sourcesContent.begin(), sourcesContent.end(), 
                   [](const std::string& s) { return !s.empty(); })) {
        json << "  \"sourcesContent\": [";
        for (size_t i = 0; i < sourcesContent.size(); i++) {
            if (i > 0) json << ", ";
            if (sourcesContent[i].empty()) {
                json << "null";
            } else {
                // 转义内容
                std::string escaped = sourcesContent[i];
                // 简化：只转义基本字符
                size_t pos = 0;
                while ((pos = escaped.find("\"", pos)) != std::string::npos) {
                    escaped.replace(pos, 1, "\\\"");
                    pos += 2;
                }
                pos = 0;
                while ((pos = escaped.find("\n", pos)) != std::string::npos) {
                    escaped.replace(pos, 1, "\\n");
                    pos += 2;
                }
                json << "\"" << escaped << "\"";
            }
        }
        json << "],\n";
    }
    
    // Names数组
    json << "  \"names\": [";
    for (size_t i = 0; i < names.size(); i++) {
        if (i > 0) json << ", ";
        json << "\"" << names[i] << "\"";
    }
    json << "],\n";
    
    // Mappings
    json << "  \"mappings\": \"" << generateMappings() << "\"\n";
    json << "}";
    
    return json.str();
}

std::string SourceMapGenerator::generateInlineURL() {
    std::string sourceMap = generateJSON();
    
    // Base64编码
    std::string encoded;
    encoded.reserve((sourceMap.size() + 2) / 3 * 4);
    
    size_t i = 0;
    while (i < sourceMap.size()) {
        uint32_t octet1 = sourceMap[i++];
        uint32_t octet2 = i < sourceMap.size() ? sourceMap[i++] : 0;
        uint32_t octet3 = i < sourceMap.size() ? sourceMap[i++] : 0;
        
        uint32_t combined = (octet1 << 16) | (octet2 << 8) | octet3;
        
        encoded += base64Chars[(combined >> 18) & 63];
        encoded += base64Chars[(combined >> 12) & 63];
        encoded += (i > sourceMap.size() + 1) ? '=' : base64Chars[(combined >> 6) & 63];
        encoded += (i > sourceMap.size()) ? '=' : base64Chars[combined & 63];
    }
    
    return "data:application/json;base64," + encoded;
}

std::string SourceMapGenerator::encodeVLQ(int value) {
    std::string encoded;
    
    // 将值转换为VLQ格式
    // 第一位表示符号
    int vlq = value < 0 ? ((-value) << 1) | 1 : value << 1;
    
    do {
        int digit = vlq & 31;  // 取低5位
        vlq >>= 5;
        
        if (vlq > 0) {
            digit |= 32;  // 设置继续位
        }
        
        encoded += base64Encode(digit);
    } while (vlq > 0);
    
    return encoded;
}

std::string SourceMapGenerator::base64Encode(int value) {
    if (value < 0 || value >= 64) {
        throw std::runtime_error("Invalid base64 value: " + std::to_string(value));
    }
    return std::string(1, base64Chars[value]);
}

std::string SourceMapGenerator::generateMappings() {
    std::stringstream result;
    
    // 跟踪前一个位置（用于相对编码）
    int previousGeneratedColumn = 0;
    int previousSourceIndex = 0;
    int previousSourceLine = 0;
    int previousSourceColumn = 0;
    int previousNameIndex = 0;
    
    for (size_t lineIdx = 0; lineIdx < mappings.size(); lineIdx++) {
        if (lineIdx > 0) {
            result << ";";
            previousGeneratedColumn = 0;  // 新行重置列
        }
        
        const auto& line = mappings[lineIdx];
        
        // 按生成列排序
        std::vector<MappingSegment> sortedLine = line;
        std::sort(sortedLine.begin(), sortedLine.end(),
                 [](const MappingSegment& a, const MappingSegment& b) {
                     return a.generatedColumn < b.generatedColumn;
                 });
        
        bool first = true;
        for (const auto& segment : sortedLine) {
            if (!first) {
                result << ",";
            }
            first = false;
            
            // 生成列（相对于上一个）
            result << encodeVLQ(segment.generatedColumn - previousGeneratedColumn);
            previousGeneratedColumn = segment.generatedColumn;
            
            // 源文件索引
            result << encodeVLQ(segment.sourceIndex - previousSourceIndex);
            previousSourceIndex = segment.sourceIndex;
            
            // 源行
            result << encodeVLQ(segment.sourceLine - previousSourceLine);
            previousSourceLine = segment.sourceLine;
            
            // 源列
            result << encodeVLQ(segment.sourceColumn - previousSourceColumn);
            previousSourceColumn = segment.sourceColumn;
            
            // 名称索引（可选）
            if (segment.nameIndex >= 0) {
                result << encodeVLQ(segment.nameIndex - previousNameIndex);
                previousNameIndex = segment.nameIndex;
            }
        }
    }
    
    return result.str();
}

// SourceMapBuilder 实现

SourceMapBuilder::SourceMapBuilder() 
    : generator(std::make_unique<SourceMapGenerator>()),
      currentLine(0), currentColumn(0) {}

void SourceMapBuilder::startFile(const std::string& filename) {
    generator->setFile(filename);
}

void SourceMapBuilder::addCode(const std::string& code, 
                              const std::string& sourceFile,
                              int sourceLine, int sourceColumn) {
    // 添加映射
    generator->addMapping(currentLine, currentColumn, 
                         sourceFile, sourceLine, sourceColumn);
    
    // 添加代码
    output << code;
    updatePosition(code);
}

void SourceMapBuilder::addGeneratedCode(const std::string& code) {
    output << code;
    updatePosition(code);
}

void SourceMapBuilder::addNewLine() {
    output << "\n";
    currentLine++;
    currentColumn = 0;
}

std::string SourceMapBuilder::getSourceMap() {
    return generator->generate();
}

void SourceMapBuilder::updatePosition(const std::string& code) {
    for (char c : code) {
        if (c == '\n') {
            currentLine++;
            currentColumn = 0;
        } else {
            currentColumn++;
        }
    }
}

// SourceMapConsumer 实现

SourceMapConsumer::SourceMapConsumer(const std::string& sourceMapJSON) {
    parseSourceMap(sourceMapJSON);
}

void SourceMapConsumer::parseSourceMap(const std::string& json) {
    // 简化的JSON解析（实际应使用JSON库）
    std::regex fileRegex("\"file\"\\s*:\\s*\"([^\"]+)\"");
    std::regex sourcesRegex("\"sources\"\\s*:\\s*\\[([^\\]]+)\\]");
    std::regex namesRegex("\"names\"\\s*:\\s*\\[([^\\]]+)\\]");
    std::regex mappingsRegex("\"mappings\"\\s*:\\s*\"([^\"]+)\"");
    
    std::smatch match;
    
    if (std::regex_search(json, match, fileRegex)) {
        file = match[1];
    }
    
    if (std::regex_search(json, match, sourcesRegex)) {
        std::string sourcesStr = match[1];
        std::regex sourceRegex("\"([^\"]+)\"");
        auto begin = std::sregex_iterator(sourcesStr.begin(), sourcesStr.end(), sourceRegex);
        auto end = std::sregex_iterator();
        
        for (auto it = begin; it != end; ++it) {
            sources.push_back((*it)[1]);
        }
    }
    
    if (std::regex_search(json, match, namesRegex)) {
        std::string namesStr = match[1];
        std::regex nameRegex("\"([^\"]+)\"");
        auto begin = std::sregex_iterator(namesStr.begin(), namesStr.end(), nameRegex);
        auto end = std::sregex_iterator();
        
        for (auto it = begin; it != end; ++it) {
            names.push_back((*it)[1]);
        }
    }
    
    if (std::regex_search(json, match, mappingsRegex)) {
        parseMappings(match[1]);
    }
}

void SourceMapConsumer::parseMappings(const std::string& mappings) {
    // 解析VLQ编码的mappings字段
    parsedMappings.clear();
    parsedMappings.push_back(std::vector<MappingSegment>());
    
    size_t pos = 0;
    int generatedColumn = 0;
    int sourceIndex = 0;
    int sourceLine = 0;
    int sourceColumn = 0;
    int nameIndex = 0;
    
    while (pos < mappings.size()) {
        if (mappings[pos] == ';') {
            // 新行
            parsedMappings.push_back(std::vector<MappingSegment>());
            generatedColumn = 0;
            pos++;
            continue;
        }
        
        if (mappings[pos] == ',') {
            // 下一个段
            pos++;
            continue;
        }
        
        MappingSegment segment;
        
        // 解码生成列
        generatedColumn += decodeVLQ(mappings, pos);
        segment.generatedColumn = generatedColumn;
        
        if (pos < mappings.size() && mappings[pos] != ',' && mappings[pos] != ';') {
            // 源文件索引
            sourceIndex += decodeVLQ(mappings, pos);
            segment.sourceIndex = sourceIndex;
            
            // 源行
            sourceLine += decodeVLQ(mappings, pos);
            segment.sourceLine = sourceLine;
            
            // 源列
            sourceColumn += decodeVLQ(mappings, pos);
            segment.sourceColumn = sourceColumn;
            
            // 名称索引（可选）
            if (pos < mappings.size() && mappings[pos] != ',' && mappings[pos] != ';') {
                nameIndex += decodeVLQ(mappings, pos);
                segment.nameIndex = nameIndex;
            }
        }
        
        parsedMappings.back().push_back(segment);
    }
}

int SourceMapConsumer::decodeVLQ(const std::string& str, size_t& pos) {
    int result = 0;
    int shift = 0;
    bool continuation;
    
    do {
        if (pos >= str.size()) {
            throw std::runtime_error("Unexpected end of VLQ string");
        }
        
        char c = str[pos++];
        int digit = -1;
        
        // 查找base64字符的值
        for (int i = 0; i < 64; i++) {
            if (base64Chars[i] == c) {
                digit = i;
                break;
            }
        }
        
        if (digit == -1) {
            throw std::runtime_error("Invalid base64 character: " + std::string(1, c));
        }
        
        continuation = (digit & 32) != 0;
        digit &= 31;
        result |= digit << shift;
        shift += 5;
    } while (continuation);
    
    // 处理符号位
    bool negative = (result & 1) != 0;
    result >>= 1;
    
    return negative ? -result : result;
}

SourceMapConsumer::OriginalPosition SourceMapConsumer::originalPositionFor(int line, int column) {
    OriginalPosition result;
    result.found = false;
    
    if (line < 0 || line >= parsedMappings.size()) {
        return result;
    }
    
    const auto& lineSegments = parsedMappings[line];
    
    // 查找最接近的段
    for (const auto& segment : lineSegments) {
        if (segment.generatedColumn <= column) {
            result.found = true;
            result.source = segment.sourceIndex < sources.size() ? 
                           sources[segment.sourceIndex] : "";
            result.line = segment.sourceLine;
            result.column = segment.sourceColumn;
            result.name = segment.nameIndex >= 0 && segment.nameIndex < names.size() ?
                         names[segment.nameIndex] : "";
        } else {
            break;  // 已经超过了目标列
        }
    }
    
    return result;
}

SourceMapConsumer::GeneratedPosition SourceMapConsumer::generatedPositionFor(
    const std::string& source, int line, int column) {
    GeneratedPosition result;
    result.found = false;
    
    // 查找源文件索引
    int sourceIndex = -1;
    for (size_t i = 0; i < sources.size(); i++) {
        if (sources[i] == source) {
            sourceIndex = i;
            break;
        }
    }
    
    if (sourceIndex == -1) {
        return result;
    }
    
    // 搜索所有映射
    for (size_t genLine = 0; genLine < parsedMappings.size(); genLine++) {
        for (const auto& segment : parsedMappings[genLine]) {
            if (segment.sourceIndex == sourceIndex &&
                segment.sourceLine == line &&
                segment.sourceColumn == column) {
                result.found = true;
                result.line = genLine;
                result.column = segment.generatedColumn;
                return result;
            }
        }
    }
    
    return result;
}

} // namespace chtl