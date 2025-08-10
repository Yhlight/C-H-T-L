#ifndef CHTL_BRIDGE_SCANNER_H
#define CHTL_BRIDGE_SCANNER_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include "Scanner/Segment.h"
#include "State/ChtlJsState.h"
#include "Context/ChtlJsContext.h"

namespace chtl {

/**
 * BridgeScanner - 桥接扫描器
 * 负责精准切割JavaScript和CHTL-JS代码
 * 实现策略：
 * - JS代码：宽松判断，整块传递给JS分析器
 * - CHTL-JS代码：严格判断，只提取CHTL特定语法
 */
class BridgeScanner {
public:
    // 分割策略
    enum class SplitStrategy {
        SYNTAX_BASED,   // 基于语法分割（推荐）
        LINE_BASED,     // 基于行分割
        BLOCK_BASED,    // 基于块分割
        HYBRID          // 混合策略
    };
    
    // 扫描配置
    struct ScanConfig {
        SplitStrategy splitStrategy = SplitStrategy::SYNTAX_BASED;
        size_t maxSegmentSize = 1024 * 1024;  // 1MB
        bool enableOptimization = true;
        bool cacheResults = true;
    };
    
    // CHTL-JS语法类型
    enum class ChtlJsType {
        SELECTOR,          // {{selector}}
        METHOD,           // ->method()
        SPECIAL_FUNCTION  // listen(), delegate(), animate()
    };
    
    // CHTL-JS匹配结果
    struct ChtlJsMatch {
        bool found = false;
        size_t start = 0;
        size_t end = 0;
        ChtlJsType type;
    };
    
    // 段处理器类型
    using SegmentHandler = std::function<void(std::shared_ptr<Segment>)>;
    
    BridgeScanner();
    ~BridgeScanner();
    
    // 主扫描方法 - 返回精准切割的代码段
    std::vector<std::shared_ptr<Segment>> scan(const std::string& code);
    
    // 分发方法
    void dispatch(std::shared_ptr<Segment> segment);
    void dispatchAll(const std::vector<std::shared_ptr<Segment>>& segments);
    
    // 注册处理器
    void registerJavaScriptHandler(SegmentHandler handler);
    void registerChtlJavaScriptHandler(SegmentHandler handler);
    
    // 配置
    void setConfig(const ScanConfig& config) { config_ = config; }
    const ScanConfig& getConfig() const { return config_; }
    
    // 控制
    void enable(bool enabled = true);
    bool isEnabled() const { return enabled_; }
    void reset();
    void clearCache();
    
private:
    // 精准切割实现
    std::vector<std::shared_ptr<Segment>> preciseSplit(const std::string& code);
    
    // CHTL-JS语法查找
    ChtlJsMatch findNextChtlJs(const std::string& code, size_t startPos);
    size_t findChtlSelector(const std::string& code, size_t startPos);
    size_t findChtlMethod(const std::string& code, size_t startPos);
    size_t findChtlSpecialFunction(const std::string& code, size_t startPos);
    
    // 查找结束位置
    size_t findSelectorEnd(const std::string& code, size_t startPos);
    size_t findMethodEnd(const std::string& code, size_t startPos);
    size_t findSpecialFunctionEnd(const std::string& code, size_t startPos);
    
    // 辅助方法
    bool isInStringOrComment(const std::string& code, size_t pos);
    bool isOnlyWhitespace(const std::string& str);
    std::shared_ptr<Segment> createSegment(SegmentType type, const std::string& content);
    
    // 优化方法
    std::vector<std::shared_ptr<Segment>> optimizeSegments(
        const std::vector<std::shared_ptr<Segment>>& segments);
    
private:
    bool enabled_;
    ScanConfig config_;
    std::shared_ptr<ChtlJsState> chtlJsState_;
    std::shared_ptr<ChtlJsContext> chtlJsContext_;
    
    // 处理器列表
    std::vector<SegmentHandler> jsHandlers_;
    std::vector<SegmentHandler> chtlJsHandlers_;
    
    // 缓存
    std::unordered_map<std::string, std::vector<std::shared_ptr<Segment>>> cache_;
};

} // namespace chtl

#endif // CHTL_BRIDGE_SCANNER_H