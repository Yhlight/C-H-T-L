#ifndef CHTL_BRIDGE_SCANNER_H
#define CHTL_BRIDGE_SCANNER_H

#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <queue>
#include "Scanner/Segment.h"
#include "Lexer/BasicLexer.h"
#include "State/ChtlJsState.h"
#include "Context/BasicContext.h"

namespace chtl {

// 前向声明
class ChtlJsState;

// 桥接扫描器 - 负责扫描和分割代码，将其分发给对应的编译器
class BridgeScanner {
public:
    // 扫描模式
    enum class ScanMode {
        STRICT,      // 严格模式 - 用于CHTL JS语法
        LENIENT,     // 宽松模式 - 用于普通JS语法
        AUTO         // 自动模式 - 根据上下文自动选择
    };
    
    // 分割策略
    enum class SplitStrategy {
        SYNTAX_BASED,    // 基于语法特征分割
        LINE_BASED,      // 基于行分割
        BLOCK_BASED,     // 基于代码块分割
        HYBRID          // 混合策略
    };
    
    // 扫描结果
    struct ScanResult {
        std::vector<std::shared_ptr<Segment>> segments;
        std::vector<std::string> errors;
        std::vector<std::string> warnings;
        bool success;
        
        ScanResult() : success(true) {}
    };
    
    // 扫描配置
    struct ScanConfig {
        ScanMode defaultMode = ScanMode::AUTO;
        SplitStrategy strategy = SplitStrategy::HYBRID;
        bool preserveComments = true;
        bool preserveWhitespace = false;
        bool detectModuleType = true;
        bool enableChtlFeatures = true;
        int maxSegmentSize = 10000;  // 最大段大小（字符数）
    };
    
    // 回调函数类型
    using SegmentHandler = std::function<void(std::shared_ptr<Segment>)>;
    using ErrorHandler = std::function<void(const std::string&)>;
    
private:
    std::shared_ptr<BasicLexer> lexer_;
    std::shared_ptr<ChtlJsState> chtlJsState_;
    std::shared_ptr<BasicContext> context_;
    ScanConfig config_;
    
    // 段处理器注册
    std::vector<SegmentHandler> jsHandlers_;
    std::vector<SegmentHandler> chtlJsHandlers_;
    ErrorHandler errorHandler_;
    
    // 扫描状态
    struct ScanState {
        int currentLine;
        int currentColumn;
        std::string currentFile;
        ScanMode currentMode;
        bool inChtlBlock;
        std::vector<std::string> chtlFeatures;  // 检测到的CHTL特性
        
        ScanState() : currentLine(1), currentColumn(1), 
                     currentMode(ScanMode::AUTO), inChtlBlock(false) {}
    } scanState_;
    
    // 临时缓冲区
    std::string codeBuffer_;
    std::vector<Token> tokenBuffer_;
    
public:
    BridgeScanner();
    virtual ~BridgeScanner() = default;
    
    // 初始化
    bool initialize(std::shared_ptr<BasicLexer> lexer = nullptr,
                   std::shared_ptr<BasicContext> context = nullptr);
    
    // 扫描方法
    ScanResult scan(const std::string& code, const std::string& filename = "<script>");
    ScanResult scanFile(const std::string& filename);
    ScanResult scanStream(std::istream& stream, const std::string& filename = "<stream>");
    
    // 配置管理
    void setConfig(const ScanConfig& config) { config_ = config; }
    const ScanConfig& getConfig() const { return config_; }
    void setScanMode(ScanMode mode) { config_.defaultMode = mode; }
    void setSplitStrategy(SplitStrategy strategy) { config_.strategy = strategy; }
    
    // 处理器注册
    void registerJsHandler(SegmentHandler handler) { jsHandlers_.push_back(handler); }
    void registerChtlJsHandler(SegmentHandler handler) { chtlJsHandlers_.push_back(handler); }
    void registerErrorHandler(ErrorHandler handler) { errorHandler_ = handler; }
    void clearHandlers();
    
    // 段分发
    void dispatch(std::shared_ptr<Segment> segment);
    void dispatchAll(const std::vector<std::shared_ptr<Segment>>& segments);
    
private:
    // 核心扫描逻辑
    std::vector<std::shared_ptr<Segment>> splitCode(const std::string& code);
    std::vector<std::shared_ptr<Segment>> splitBySyntax(const std::string& code);
    std::vector<std::shared_ptr<Segment>> splitByLines(const std::string& code);
    std::vector<std::shared_ptr<Segment>> splitByBlocks(const std::string& code);
    std::vector<std::shared_ptr<Segment>> splitHybrid(const std::string& code);
    
    // 语法检测
    bool isChtlSyntax(const std::string& code, size_t pos);
    bool isJavaScriptSyntax(const std::string& code, size_t pos);
    SegmentType detectSegmentType(const std::string& code);
    std::vector<std::string> detectChtlFeatures(const std::string& code);
    
    // 宽判严判逻辑
    bool validateWithStrictMode(const std::string& code);
    bool validateWithLenientMode(const std::string& code);
    
    // 代码块边界检测
    struct BlockBoundary {
        size_t start;
        size_t end;
        SegmentType type;
        std::string reason;  // 分割原因
    };
    std::vector<BlockBoundary> findBlockBoundaries(const std::string& code);
    
    // 辅助方法
    void reportError(const std::string& error);
    void reportWarning(const std::string& warning);
    std::shared_ptr<Segment> createSegmentFromBoundary(
        const std::string& code, 
        const BlockBoundary& boundary);
    void updateSourceInfo(std::shared_ptr<Segment> segment, 
                         int startLine, int startCol, 
                         int endLine, int endCol);
    
    // CHTL特性检测器
    bool hasTemplateFunction(const std::string& code);
    bool hasOperatorExtension(const std::string& code);
    bool hasNullSafety(const std::string& code);
    bool hasPipeOperator(const std::string& code);
    bool hasPatternMatching(const std::string& code);
    bool hasAsyncExtensions(const std::string& code);
    bool hasReactiveBindings(const std::string& code);
    
    // CHTL-JS特性检测器（新增）
    bool hasChtlSelector(const std::string& code);         // {{selector}}
    bool hasChtlArrowOperator(const std::string& code);    // ->
    bool hasChtlListen(const std::string& code);           // ->listen()
    bool hasChtlDelegate(const std::string& code);         // ->delegate()
    bool hasChtlAnimate(const std::string& code);          // animate()
    
    // Token分析
    void analyzeTokens(const std::vector<Token>& tokens);
    bool isTokenSequenceChtl(const std::vector<Token>& tokens, size_t start);
};

} // namespace chtl

#endif // CHTL_BRIDGE_SCANNER_H