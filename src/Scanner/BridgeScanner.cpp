#include "Scanner/BridgeScanner.h"
#include "State/StateFactory.h"
#include "Context/ContextFactory.h"
#include "Lexer/StandardLexer.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

namespace chtl {

BridgeScanner::BridgeScanner() 
    : lexer_(nullptr), chtlJsState_(nullptr), context_(nullptr) {
}

bool BridgeScanner::initialize(std::shared_ptr<BasicLexer> lexer,
                              std::shared_ptr<BasicContext> context) {
    // 如果没有提供lexer，创建一个BasicLexer
    if (!lexer) {
        lexer_ = std::make_shared<StandardLexer>();
    } else {
        lexer_ = lexer;
    }
    
    // 如果没有提供context，创建一个默认的
    if (!context) {
        context_ = ContextFactory::createContext(ContextType::CHTL);
    } else {
        context_ = context;
    }
    
    // 创建ChtlJsState用于语法识别
    auto state = StateFactory::createState(StateType::CHTL_JS, lexer_.get());
    chtlJsState_ = std::dynamic_pointer_cast<ChtlJsState>(state);
    
    if (!chtlJsState_) {
        reportError("Failed to create ChtlJsState");
        return false;
    }
    
    return true;
}

BridgeScanner::ScanResult BridgeScanner::scan(const std::string& code, 
                                              const std::string& filename) {
    ScanResult result;
    
    // 重置扫描状态
    scanState_ = ScanState();
    scanState_.currentFile = filename;
    codeBuffer_ = code;
    tokenBuffer_.clear();
    
    try {
        // 分割代码
        auto segments = splitCode(code);
        
        // 验证和分类每个段
        for (auto& segment : segments) {
            // 更新源信息
            segment->setSourceLocation(filename, 
                                     scanState_.currentLine, 
                                     scanState_.currentColumn,
                                     scanState_.currentLine, 
                                     scanState_.currentColumn);
            
            // 检测段类型
            if (segment->getType() == SegmentType::MIXED) {
                // 如果是混合段，进一步分割
                auto mixedSeg = std::dynamic_pointer_cast<MixedSegment>(segment);
                if (mixedSeg) {
                    auto subSegments = splitCode(mixedSeg->getContent());
                    for (auto& subSeg : subSegments) {
                        mixedSeg->addSubSegment(subSeg);
                    }
                }
            }
            
            // 应用验证规则
            bool isValid = false;
            if (segment->getType() == SegmentType::CHTL_JAVASCRIPT) {
                // CHTL JS使用严格模式
                isValid = validateWithStrictMode(segment->getContent());
                if (!isValid) {
                    reportError("CHTL JavaScript validation failed (strict mode)");
                }
            } else if (segment->getType() == SegmentType::JAVASCRIPT) {
                // 普通JS使用宽松模式
                isValid = validateWithLenientMode(segment->getContent());
                if (!isValid) {
                    reportWarning("JavaScript validation warning (lenient mode)");
                    isValid = true; // 宽松模式下，警告但不失败
                }
            }
            
            result.segments.push_back(segment);
        }
        
        // 分发到对应的处理器
        dispatchAll(result.segments);
        
    } catch (const std::exception& e) {
        result.success = false;
        reportError(std::string("Scan failed: ") + e.what());
    }
    
    result.errors = scanState_.chtlFeatures; // 临时使用，应该是错误列表
    return result;
}

BridgeScanner::ScanResult BridgeScanner::scanFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        ScanResult result;
        result.success = false;
        result.errors.push_back("Failed to open file: " + filename);
        return result;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return scan(buffer.str(), filename);
}

BridgeScanner::ScanResult BridgeScanner::scanStream(std::istream& stream, 
                                                    const std::string& filename) {
    std::stringstream buffer;
    buffer << stream.rdbuf();
    return scan(buffer.str(), filename);
}

void BridgeScanner::clearHandlers() {
    jsHandlers_.clear();
    chtlJsHandlers_.clear();
    errorHandler_ = nullptr;
}

void BridgeScanner::dispatch(std::shared_ptr<Segment> segment) {
    if (!segment) return;
    
    switch (segment->getType()) {
        case SegmentType::JAVASCRIPT:
            for (auto& handler : jsHandlers_) {
                handler(segment);
            }
            break;
            
        case SegmentType::CHTL_JAVASCRIPT:
            for (auto& handler : chtlJsHandlers_) {
                handler(segment);
            }
            break;
            
        case SegmentType::MIXED:
            // 混合段应该已经被分割，这里可能需要额外处理
            reportWarning("Dispatching mixed segment - consider further splitting");
            break;
            
        default:
            reportWarning("Unknown segment type for dispatch");
            break;
    }
}

void BridgeScanner::dispatchAll(const std::vector<std::shared_ptr<Segment>>& segments) {
    for (const auto& segment : segments) {
        dispatch(segment);
    }
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitCode(const std::string& code) {
    switch (config_.strategy) {
        case SplitStrategy::SYNTAX_BASED:
            return splitBySyntax(code);
        case SplitStrategy::LINE_BASED:
            return splitByLines(code);
        case SplitStrategy::BLOCK_BASED:
            return splitByBlocks(code);
        case SplitStrategy::HYBRID:
        default:
            return splitHybrid(code);
    }
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitBySyntax(const std::string& code) {
    std::vector<std::shared_ptr<Segment>> segments;
    auto boundaries = findBlockBoundaries(code);
    
    for (const auto& boundary : boundaries) {
        auto segment = createSegmentFromBoundary(code, boundary);
        if (segment) {
            segments.push_back(segment);
        }
    }
    
    return segments;
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitHybrid(const std::string& code) {
    std::vector<std::shared_ptr<Segment>> segments;
    
    // 使用混合策略：首先按语法特征分割，然后检查大小
    auto syntaxSegments = splitBySyntax(code);
    
    for (auto& segment : syntaxSegments) {
        if (static_cast<int>(segment->getContent().length()) > config_.maxSegmentSize) {
            // 如果段太大，按块再分割
            auto blockSegments = splitByBlocks(segment->getContent());
            segments.insert(segments.end(), blockSegments.begin(), blockSegments.end());
        } else {
            segments.push_back(segment);
        }
    }
    
    return segments;
}

bool BridgeScanner::isChtlSyntax(const std::string& code, size_t pos) {
    // CHTL特有语法检测
    // 检查管道操作符 |>
    if (pos + 1 < code.length() && code.substr(pos, 2) == "|>") {
        return true;
    }
    
    // 检查空安全操作符 ?.
    if (pos + 1 < code.length() && code.substr(pos, 2) == "?.") {
        return true;
    }
    
    // 检查模板函数语法 @function
    if (code[pos] == '@' && pos + 1 < code.length() && std::isalpha(code[pos + 1])) {
        return true;
    }
    
    // 检查CHTL特有的关键字
    static const std::vector<std::string> chtlKeywords = {
        "@template", "@reactive", "@async", "@pipe", "@match", "@observable"
    };
    
    for (const auto& keyword : chtlKeywords) {
        if (pos + keyword.length() <= code.length() && 
            code.substr(pos, keyword.length()) == keyword) {
            return true;
        }
    }
    
    return false;
}

SegmentType BridgeScanner::detectSegmentType(const std::string& code) {
    bool hasChtlFeatures = false;
    bool hasJsFeatures = false;
    
    // 检测CHTL特性
    auto features = detectChtlFeatures(code);
    hasChtlFeatures = !features.empty();
    
    // 简单的JS语法检测
    static const std::regex jsPattern(R"(\b(function|var|let|const|class|import|export)\b)");
    hasJsFeatures = std::regex_search(code, jsPattern);
    
    if (hasChtlFeatures && hasJsFeatures) {
        return SegmentType::MIXED;
    } else if (hasChtlFeatures) {
        return SegmentType::CHTL_JAVASCRIPT;
    } else if (hasJsFeatures) {
        return SegmentType::JAVASCRIPT;
    } else {
        return SegmentType::UNKNOWN;
    }
}

std::vector<std::string> BridgeScanner::detectChtlFeatures(const std::string& code) {
    std::vector<std::string> features;
    
    if (hasTemplateFunction(code)) features.push_back("template-function");
    if (hasOperatorExtension(code)) features.push_back("operator-extension");
    if (hasNullSafety(code)) features.push_back("null-safety");
    if (hasPipeOperator(code)) features.push_back("pipe-operator");
    if (hasPatternMatching(code)) features.push_back("pattern-matching");
    if (hasAsyncExtensions(code)) features.push_back("async-extensions");
    if (hasReactiveBindings(code)) features.push_back("reactive-bindings");
    
    return features;
}

bool BridgeScanner::validateWithStrictMode(const std::string& code) {
    // 严格模式验证 - 用于CHTL JS
    // 1. 语法必须完全符合CHTL扩展规范
    // 2. 不允许有歧义的语法
    // 3. 必须有明确的CHTL特性标记
    
    auto features = detectChtlFeatures(code);
    if (features.empty()) {
        reportError("No CHTL features detected in strict mode");
        return false;
    }
    
    // TODO: 使用ChtlJsState进行更详细的语法验证
    // 这里暂时返回true
    return true;
}

bool BridgeScanner::validateWithLenientMode(const std::string& code) {
    // 宽松模式验证 - 用于普通JS
    // 1. 允许大部分JS语法
    // 2. 不强制要求特定格式
    // 3. 主要检查基本语法错误
    
    // 基本的括号匹配检查
    int braceCount = 0;
    int parenCount = 0;
    int bracketCount = 0;
    
    for (char c : code) {
        switch (c) {
            case '{': braceCount++; break;
            case '}': braceCount--; break;
            case '(': parenCount++; break;
            case ')': parenCount--; break;
            case '[': bracketCount++; break;
            case ']': bracketCount--; break;
        }
        
        if (braceCount < 0 || parenCount < 0 || bracketCount < 0) {
            reportWarning("Unmatched brackets detected");
            return false;
        }
    }
    
    if (braceCount != 0 || parenCount != 0 || bracketCount != 0) {
        reportWarning("Unclosed brackets detected");
        return false;
    }
    
    return true;
}

std::vector<BridgeScanner::BlockBoundary> BridgeScanner::findBlockBoundaries(const std::string& code) {
    std::vector<BlockBoundary> boundaries;
    size_t pos = 0;
    size_t blockStart = 0;
    
    while (pos < code.length()) {
        // 检测CHTL块的开始
        if (isChtlSyntax(code, pos)) {
            // 如果之前有JS代码，创建JS块
            if (pos > blockStart) {
                BlockBoundary boundary;
                boundary.start = blockStart;
                boundary.end = pos;
                boundary.type = SegmentType::JAVASCRIPT;
                boundary.reason = "Before CHTL syntax";
                boundaries.push_back(boundary);
            }
            
            // 找到CHTL块的结束
            size_t chtlEnd = pos;
            while (chtlEnd < code.length() && isChtlSyntax(code, chtlEnd)) {
                chtlEnd++;
            }
            
            BlockBoundary chtlBoundary;
            chtlBoundary.start = pos;
            chtlBoundary.end = chtlEnd;
            chtlBoundary.type = SegmentType::CHTL_JAVASCRIPT;
            chtlBoundary.reason = "CHTL syntax detected";
            boundaries.push_back(chtlBoundary);
            
            blockStart = chtlEnd;
            pos = chtlEnd;
        } else {
            pos++;
        }
    }
    
    // 处理最后的块
    if (blockStart < code.length()) {
        BlockBoundary boundary;
        boundary.start = blockStart;
        boundary.end = code.length();
        boundary.type = SegmentType::JAVASCRIPT;
        boundary.reason = "End of code";
        boundaries.push_back(boundary);
    }
    
    return boundaries;
}

void BridgeScanner::reportError(const std::string& error) {
    if (errorHandler_) {
        errorHandler_(error);
    }
    // TODO: 添加到错误列表
}

void BridgeScanner::reportWarning(const std::string& warning) {
    // TODO: 添加到警告列表
    (void)warning;
}

std::shared_ptr<Segment> BridgeScanner::createSegmentFromBoundary(
    const std::string& code, 
    const BlockBoundary& boundary) {
    
    std::string content = code.substr(boundary.start, boundary.end - boundary.start);
    auto segment = SegmentFactory::createSegment(boundary.type, content);
    
    if (boundary.type == SegmentType::CHTL_JAVASCRIPT) {
        auto chtlSeg = std::dynamic_pointer_cast<ChtlJavaScriptSegment>(segment);
        if (chtlSeg) {
            // 检测并启用CHTL特性
            auto features = detectChtlFeatures(content);
            for (const auto& feature : features) {
                chtlSeg->enableFeature(feature);
            }
        }
    }
    
    return segment;
}

// CHTL特性检测实现
bool BridgeScanner::hasTemplateFunction(const std::string& code) {
    static const std::regex pattern(R"(@template\s+\w+)");
    return std::regex_search(code, pattern);
}

bool BridgeScanner::hasOperatorExtension(const std::string& code) {
    static const std::regex pattern(R"(operator\s*\+\+|operator\s*\-\-|operator\s*\[\])");
    return std::regex_search(code, pattern);
}

bool BridgeScanner::hasNullSafety(const std::string& code) {
    return code.find("?.") != std::string::npos || 
           code.find("??") != std::string::npos;
}

bool BridgeScanner::hasPipeOperator(const std::string& code) {
    return code.find("|>") != std::string::npos;
}

bool BridgeScanner::hasPatternMatching(const std::string& code) {
    static const std::regex pattern(R"(@match\s*\(|match\s*\{)");
    return std::regex_search(code, pattern);
}

bool BridgeScanner::hasAsyncExtensions(const std::string& code) {
    static const std::regex pattern(R"(@async\s+|async\*|await\*)");
    return std::regex_search(code, pattern);
}

bool BridgeScanner::hasReactiveBindings(const std::string& code) {
    static const std::regex pattern(R"(@reactive\s+|@observable\s+|\$\w+)");
    return std::regex_search(code, pattern);
}

// 占位实现
std::vector<std::shared_ptr<Segment>> BridgeScanner::splitByLines(const std::string& code) {
    // TODO: 实现按行分割
    (void)code;
    return {};
}

std::vector<std::shared_ptr<Segment>> BridgeScanner::splitByBlocks(const std::string& code) {
    // TODO: 实现按块分割
    (void)code;
    return {};
}

} // namespace chtl