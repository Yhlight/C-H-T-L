#ifndef CHTL_PARSER_OPTIMIZER_H
#define CHTL_PARSER_OPTIMIZER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <chrono>
#include <functional>
#include <vector>

namespace chtl {

// 前向声明
class StandardParser;
class Node;
class Token;

/**
 * 解析器优化器 - 提升大文件解析性能
 */
class ParserOptimizer {
public:
    // 性能统计
    struct PerformanceStats {
        size_t totalTokens = 0;
        size_t totalNodes = 0;
        double lexingTime = 0.0;
        double parsingTime = 0.0;
        double totalTime = 0.0;
        size_t cacheHits = 0;
        size_t cacheMisses = 0;
        size_t memoryUsed = 0;
    };
    
    // 优化选项
    struct OptimizationOptions {
        bool enableCache = true;
        bool enableParallelParsing = false;
        bool enableLazyParsing = true;
        bool enableStreamParsing = true;
        size_t cacheSize = 1000;
        size_t chunkSize = 4096;  // 用于流式解析
    };
    
    ParserOptimizer();
    ~ParserOptimizer();
    
    /**
     * 设置优化选项
     */
    void setOptions(const OptimizationOptions& options);
    
    /**
     * 优化解析器
     * @param parser 要优化的解析器
     */
    void optimizeParser(StandardParser* parser);
    
    /**
     * 启用缓存
     * @param maxSize 缓存最大大小
     */
    void enableCache(size_t maxSize = 1000);
    
    /**
     * 启用流式解析
     * @param chunkSize 块大小
     */
    void enableStreamParsing(size_t chunkSize = 4096);
    
    /**
     * 启用延迟解析
     * @param threshold 触发延迟解析的节点大小阈值
     */
    void enableLazyParsing(size_t threshold = 100);
    
    /**
     * 预编译常见模式
     */
    void precompilePatterns();
    
    /**
     * 获取性能统计
     */
    PerformanceStats getStats() const { return stats_; }
    
    /**
     * 重置统计数据
     */
    void resetStats();
    
    /**
     * 分析性能瓶颈
     * @return 性能分析报告
     */
    std::string analyzePerformance() const;
    
private:
    OptimizationOptions options_;
    PerformanceStats stats_;
    
    // 缓存系统
    struct CacheEntry {
        std::shared_ptr<Node> node;
        std::chrono::steady_clock::time_point lastAccess;
        size_t accessCount = 0;
    };
    
    std::unordered_map<std::string, CacheEntry> parseCache_;
    
    // 预编译的模式
    std::unordered_map<std::string, std::function<std::shared_ptr<Node>(const std::vector<Token>&)>> 
        compiledPatterns_;
    
    // 性能计时器
    class Timer {
        std::chrono::steady_clock::time_point start_;
        double& target_;
    public:
        Timer(double& target) : target_(target) {
            start_ = std::chrono::steady_clock::now();
        }
        ~Timer() {
            auto end = std::chrono::steady_clock::now();
            target_ += std::chrono::duration<double>(end - start_).count();
        }
    };
    
    // 缓存管理
    void evictOldEntries();
    std::string generateCacheKey(const std::vector<Token>& tokens, size_t start, size_t end);
    
    // 模式匹配优化
    bool tryMatchPattern(const std::vector<Token>& tokens, size_t& pos, 
                        std::shared_ptr<Node>& result);
    
    // 内存池
    class MemoryPool {
        std::vector<std::unique_ptr<char[]>> blocks_;
        size_t currentBlock_ = 0;
        size_t currentOffset_ = 0;
        static constexpr size_t BLOCK_SIZE = 64 * 1024; // 64KB
        
    public:
        void* allocate(size_t size);
        void reset();
        size_t getTotalMemory() const;
    };
    
    MemoryPool memoryPool_;
    
    // 并行解析支持
    struct ParseTask {
        size_t start;
        size_t end;
        std::shared_ptr<Node> result;
        bool completed = false;
    };
    
    std::vector<ParseTask> splitIntoTasks(const std::vector<Token>& tokens);
    void mergeTaskResults(std::vector<ParseTask>& tasks, std::shared_ptr<Node>& root);
};

/**
 * 流式解析器 - 处理大文件
 */
class StreamingParser {
public:
    StreamingParser(size_t bufferSize = 8192);
    ~StreamingParser();
    
    /**
     * 开始流式解析
     * @param input 输入流
     * @param callback 每解析完一个顶层节点的回调
     */
    void parseStream(std::istream& input, 
                    std::function<void(std::shared_ptr<Node>)> callback);
    
    /**
     * 设置进度回调
     * @param callback 进度回调函数(已处理字节数, 总字节数)
     */
    void setProgressCallback(std::function<void(size_t, size_t)> callback);
    
private:
    size_t bufferSize_;
    std::vector<char> buffer_;
    std::function<void(size_t, size_t)> progressCallback_;
    
    // 缓冲区管理
    bool refillBuffer(std::istream& input);
    void shiftBuffer(size_t consumed);
};

} // namespace chtl

#endif // CHTL_PARSER_OPTIMIZER_H