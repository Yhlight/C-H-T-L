#ifndef CHTL_SOURCE_MAP_H
#define CHTL_SOURCE_MAP_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <sstream>

namespace chtl {

// 源位置信息
struct SourcePosition {
    int line;          // 0-based
    int column;        // 0-based
    int sourceIndex;   // 源文件索引
    int nameIndex;     // 名称索引（-1表示无名称）
    
    SourcePosition(int line = 0, int column = 0, int sourceIndex = 0, int nameIndex = -1)
        : line(line), column(column), sourceIndex(sourceIndex), nameIndex(nameIndex) {}
};

// 映射段
struct MappingSegment {
    int generatedColumn;     // 生成文件中的列
    int sourceIndex;         // 源文件索引
    int sourceLine;          // 源文件中的行
    int sourceColumn;        // 源文件中的列
    int nameIndex;           // 名称索引（可选）
    
    MappingSegment() : generatedColumn(0), sourceIndex(0), 
                       sourceLine(0), sourceColumn(0), nameIndex(-1) {}
};

// Source Map v3 生成器
class SourceMapGenerator {
public:
    SourceMapGenerator();
    
    // 设置文件信息
    void setFile(const std::string& file);
    void setSourceRoot(const std::string& root);
    
    // 添加源文件
    int addSource(const std::string& source, const std::string& content = "");
    
    // 添加名称
    int addName(const std::string& name);
    
    // 添加映射
    void addMapping(int generatedLine, int generatedColumn,
                   int sourceIndex, int sourceLine, int sourceColumn,
                   int nameIndex = -1);
    
    // 简化的添加映射接口
    void addMapping(int generatedLine, int generatedColumn,
                   const std::string& source, int sourceLine, int sourceColumn,
                   const std::string& name = "");
    
    // 生成Source Map
    std::string generate();
    std::string generateJSON();
    
    // 生成内联Source Map URL
    std::string generateInlineURL();
    
private:
    std::string file;
    std::string sourceRoot;
    std::vector<std::string> sources;
    std::vector<std::string> sourcesContent;
    std::vector<std::string> names;
    std::unordered_map<std::string, int> sourceIndexMap;
    std::unordered_map<std::string, int> nameIndexMap;
    
    // 按行组织的映射
    std::vector<std::vector<MappingSegment>> mappings;
    
    // VLQ编码
    static std::string encodeVLQ(int value);
    static std::string base64Encode(int value);
    
    // 生成mappings字段
    std::string generateMappings();
};

// Source Map 合并器
class SourceMapMerger {
public:
    // 合并多个Source Map
    static std::string merge(const std::vector<std::string>& sourceMaps);
    
    // 应用Source Map（用于多级转换）
    static std::string applySourceMap(const std::string& generatedSourceMap,
                                    const std::string& originalSourceMap);
};

// Source Map 消费者（用于调试）
class SourceMapConsumer {
public:
    explicit SourceMapConsumer(const std::string& sourceMapJSON);
    
    // 查找原始位置
    struct OriginalPosition {
        std::string source;
        int line;
        int column;
        std::string name;
        bool found;
    };
    
    OriginalPosition originalPositionFor(int line, int column);
    
    // 查找生成位置
    struct GeneratedPosition {
        int line;
        int column;
        bool found;
    };
    
    GeneratedPosition generatedPositionFor(const std::string& source, 
                                         int line, int column);
    
private:
    std::string file;
    std::string sourceRoot;
    std::vector<std::string> sources;
    std::vector<std::string> names;
    std::vector<std::vector<MappingSegment>> parsedMappings;
    
    void parseSourceMap(const std::string& json);
    void parseMappings(const std::string& mappings);
    static int decodeVLQ(const std::string& str, size_t& pos);
};

// 代码生成器辅助类
class SourceMapBuilder {
public:
    SourceMapBuilder();
    
    // 开始新文件
    void startFile(const std::string& filename);
    
    // 添加代码片段
    void addCode(const std::string& code, 
                const std::string& sourceFile,
                int sourceLine, int sourceColumn);
    
    // 添加生成的代码（无源映射）
    void addGeneratedCode(const std::string& code);
    
    // 添加换行
    void addNewLine();
    
    // 获取结果
    std::string getCode() const { return output.str(); }
    std::string getSourceMap();
    
private:
    std::unique_ptr<SourceMapGenerator> generator;
    std::stringstream output;
    int currentLine;
    int currentColumn;
    
    void updatePosition(const std::string& code);
};

} // namespace chtl

#endif // CHTL_SOURCE_MAP_H