#include "Parser/ParserOptimizer.h"
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Node/Node.h"
#include "Common/Token.h"
#include <sstream>
#include <iomanip>
#include <thread>
#include <future>
#include <algorithm>

namespace chtl {

// MemoryPool 实现
void* ParserOptimizer::MemoryPool::allocate(size_t size) {
    // 对齐到 8 字节
    size = (size + 7) & ~7;
    
    // 如果当前块空间不足，分配新块
    if (currentOffset_ + size > BLOCK_SIZE) {
        blocks_.push_back(std::make_unique<char[]>(BLOCK_SIZE));
        currentBlock_ = blocks_.size() - 1;
        currentOffset_ = 0;
    }
    
    void* ptr = blocks_[currentBlock_].get() + currentOffset_;
    currentOffset_ += size;
    
    return ptr;
}

void ParserOptimizer::MemoryPool::reset() {
    currentBlock_ = 0;
    currentOffset_ = 0;
    // 保留第一个块，清除其他块
    if (blocks_.size() > 1) {
        blocks_.resize(1);
    }
}

size_t ParserOptimizer::MemoryPool::getTotalMemory() const {
    return blocks_.size() * BLOCK_SIZE;
}

// ParserOptimizer 实现
ParserOptimizer::ParserOptimizer() {
    precompilePatterns();
}

ParserOptimizer::~ParserOptimizer() {}

void ParserOptimizer::setOptions(const OptimizationOptions& options) {
    options_ = options;
    
    if (options_.enableCache) {
        enableCache(options_.cacheSize);
    }
}

void ParserOptimizer::optimizeParser(StandardParser* parser) {
    if (!parser) return;
    
    // TODO: 实际的解析器优化逻辑
    // 这里可以设置解析器的各种优化标志
}

void ParserOptimizer::enableCache(size_t maxSize) {
    options_.enableCache = true;
    options_.cacheSize = maxSize;
    parseCache_.reserve(maxSize);
}

void ParserOptimizer::enableStreamParsing(size_t chunkSize) {
    options_.enableStreamParsing = true;
    options_.chunkSize = chunkSize;
}

void ParserOptimizer::enableLazyParsing(size_t threshold) {
    options_.enableLazyParsing = true;
    // threshold 可以用于决定何时延迟解析
}

void ParserOptimizer::precompilePatterns() {
    // 预编译常见的CHTL模式以加速解析
    
    // 简单元素模式: tagName { ... }
    compiledPatterns_["simple_element"] = [](const std::vector<Token>& tokens) {
        // 快速解析简单元素
        return nullptr; // TODO: 实现
    };
    
    // 属性模式: key="value"
    compiledPatterns_["attribute"] = [](const std::vector<Token>& tokens) {
        // 快速解析属性
        return nullptr; // TODO: 实现
    };
    
    // 样式块模式: style { ... }
    compiledPatterns_["style_block"] = [](const std::vector<Token>& tokens) {
        // 快速解析样式块
        return nullptr; // TODO: 实现
    };
}

void ParserOptimizer::resetStats() {
    stats_ = PerformanceStats();
}

std::string ParserOptimizer::analyzePerformance() const {
    std::stringstream report;
    report << std::fixed << std::setprecision(3);
    
    report << "=== CHTL Parser Performance Analysis ===\n\n";
    
    report << "Overall Performance:\n";
    report << "  Total Time: " << stats_.totalTime << "s\n";
    report << "  Lexing Time: " << stats_.lexingTime << "s ("
           << (stats_.lexingTime / stats_.totalTime * 100) << "%)\n";
    report << "  Parsing Time: " << stats_.parsingTime << "s ("
           << (stats_.parsingTime / stats_.totalTime * 100) << "%)\n\n";
    
    report << "Throughput:\n";
    report << "  Tokens Processed: " << stats_.totalTokens << "\n";
    report << "  Nodes Created: " << stats_.totalNodes << "\n";
    report << "  Tokens/Second: " << (stats_.totalTokens / stats_.totalTime) << "\n";
    report << "  Nodes/Second: " << (stats_.totalNodes / stats_.totalTime) << "\n\n";
    
    if (options_.enableCache) {
        report << "Cache Performance:\n";
        report << "  Cache Hits: " << stats_.cacheHits << "\n";
        report << "  Cache Misses: " << stats_.cacheMisses << "\n";
        double hitRate = stats_.cacheHits + stats_.cacheMisses > 0 
            ? (double)stats_.cacheHits / (stats_.cacheHits + stats_.cacheMisses) * 100 
            : 0;
        report << "  Hit Rate: " << hitRate << "%\n\n";
    }
    
    report << "Memory Usage:\n";
    report << "  Total Memory: " << (stats_.memoryUsed / 1024.0 / 1024.0) << " MB\n";
    report << "  Memory Pool: " << (memoryPool_.getTotalMemory() / 1024.0 / 1024.0) << " MB\n";
    
    // 性能建议
    report << "\nPerformance Recommendations:\n";
    
    if (stats_.lexingTime > stats_.parsingTime * 1.5) {
        report << "  - Lexing is the bottleneck. Consider optimizing token patterns.\n";
    }
    
    if (options_.enableCache && stats_.cacheHits < stats_.cacheMisses * 0.2) {
        report << "  - Low cache hit rate. Consider increasing cache size.\n";
    }
    
    if (stats_.totalTokens > 100000 && !options_.enableStreamParsing) {
        report << "  - Large file detected. Enable stream parsing for better performance.\n";
    }
    
    if (stats_.memoryUsed > 100 * 1024 * 1024) { // 100MB
        report << "  - High memory usage. Consider enabling lazy parsing.\n";
    }
    
    return report.str();
}

void ParserOptimizer::evictOldEntries() {
    if (parseCache_.size() <= options_.cacheSize) {
        return;
    }
    
    // LRU 驱逐策略
    std::vector<std::pair<std::string, std::chrono::steady_clock::time_point>> entries;
    for (const auto& [key, entry] : parseCache_) {
        entries.push_back({key, entry.lastAccess});
    }
    
    // 按最后访问时间排序
    std::sort(entries.begin(), entries.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    
    // 移除最旧的条目
    size_t toRemove = parseCache_.size() - options_.cacheSize;
    for (size_t i = 0; i < toRemove && i < entries.size(); ++i) {
        parseCache_.erase(entries[i].first);
    }
}

std::string ParserOptimizer::generateCacheKey(const std::vector<Token>& tokens, 
                                             size_t start, size_t end) {
    std::stringstream key;
    
    // 使用token类型和值的哈希作为键
    for (size_t i = start; i < end && i < tokens.size(); ++i) {
        key << static_cast<int>(tokens[i].type) << ":" << tokens[i].value << ";";
    }
    
    return key.str();
}

bool ParserOptimizer::tryMatchPattern(const std::vector<Token>& tokens, size_t& pos,
                                     std::shared_ptr<Node>& result) {
    // 尝试匹配预编译的模式
    for (const auto& [name, matcher] : compiledPatterns_) {
        result = matcher(tokens);
        if (result) {
            return true;
        }
    }
    
    return false;
}

std::vector<ParserOptimizer::ParseTask> 
ParserOptimizer::splitIntoTasks(const std::vector<Token>& tokens) {
    std::vector<ParseTask> tasks;
    
    // 简单的任务分割策略：按顶层元素分割
    size_t taskStart = 0;
    int braceDepth = 0;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].type == TokenType::LEFT_BRACE) {
            braceDepth++;
        } else if (tokens[i].type == TokenType::RIGHT_BRACE) {
            braceDepth--;
            
            // 找到一个顶层元素的结束
            if (braceDepth == 0) {
                ParseTask task;
                task.start = taskStart;
                task.end = i + 1;
                tasks.push_back(task);
                taskStart = i + 1;
            }
        }
    }
    
    // 处理剩余的tokens
    if (taskStart < tokens.size()) {
        ParseTask task;
        task.start = taskStart;
        task.end = tokens.size();
        tasks.push_back(task);
    }
    
    return tasks;
}

void ParserOptimizer::mergeTaskResults(std::vector<ParseTask>& tasks, 
                                       std::shared_ptr<Node>& root) {
    // 合并并行解析的结果
    for (auto& task : tasks) {
        if (task.completed && task.result) {
            root->addChild(task.result);
        }
    }
}

// StreamingParser 实现
StreamingParser::StreamingParser(size_t bufferSize) 
    : bufferSize_(bufferSize), buffer_(bufferSize) {}

StreamingParser::~StreamingParser() {}

void StreamingParser::parseStream(std::istream& input,
                                 std::function<void(std::shared_ptr<Node>)> callback) {
    size_t totalBytes = 0;
    size_t processedBytes = 0;
    
    // 获取文件大小（如果可能）
    input.seekg(0, std::ios::end);
    totalBytes = input.tellg();
    input.seekg(0, std::ios::beg);
    
    StandardLexer lexer;
    StandardParser parser;
    
    std::string accumulated;
    
    while (refillBuffer(input)) {
        // 将缓冲区内容添加到累积字符串
        accumulated.append(buffer_.data(), buffer_.size());
        
        // 查找完整的顶层元素
        size_t elementEnd = 0;
        int braceDepth = 0;
        bool inString = false;
        
        for (size_t i = 0; i < accumulated.size(); ++i) {
            char c = accumulated[i];
            
            if (!inString) {
                if (c == '"') {
                    inString = true;
                } else if (c == '{') {
                    braceDepth++;
                } else if (c == '}') {
                    braceDepth--;
                    if (braceDepth == 0) {
                        elementEnd = i + 1;
                        break;
                    }
                }
            } else if (c == '"' && (i == 0 || accumulated[i-1] != '\\')) {
                inString = false;
            }
        }
        
        // 如果找到完整元素，解析它
        if (elementEnd > 0) {
            std::string element = accumulated.substr(0, elementEnd);
            accumulated = accumulated.substr(elementEnd);
            
            // 解析元素
            auto tokens = lexer.tokenize(element);
            parser.reset();
            parser.setTokens(tokens);
            auto node = parser.parse();
            
            if (node) {
                callback(node);
            }
            
            processedBytes += element.size();
            
            // 报告进度
            if (progressCallback_) {
                progressCallback_(processedBytes, totalBytes);
            }
        }
    }
    
    // 处理剩余内容
    if (!accumulated.empty()) {
        auto tokens = lexer.tokenize(accumulated);
        parser.reset();
        parser.setTokens(tokens);
        auto node = parser.parse();
        
        if (node) {
            callback(node);
        }
    }
}

void StreamingParser::setProgressCallback(std::function<void(size_t, size_t)> callback) {
    progressCallback_ = callback;
}

bool StreamingParser::refillBuffer(std::istream& input) {
    input.read(buffer_.data(), bufferSize_);
    size_t bytesRead = input.gcount();
    
    if (bytesRead > 0) {
        buffer_.resize(bytesRead);
        return true;
    }
    
    return false;
}

void StreamingParser::shiftBuffer(size_t consumed) {
    if (consumed >= buffer_.size()) {
        buffer_.clear();
    } else {
        std::memmove(buffer_.data(), buffer_.data() + consumed, buffer_.size() - consumed);
        buffer_.resize(buffer_.size() - consumed);
    }
}

} // namespace chtl