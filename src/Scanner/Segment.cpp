#include "Scanner/Segment.h"
#include <sstream>

namespace chtl {

// Segment基类实现
std::string Segment::getTypeString() const {
    switch (type_) {
        case SegmentType::JAVASCRIPT:
            return "JavaScript";
        case SegmentType::CHTL_JAVASCRIPT:
            return "CHTL-JavaScript";
        case SegmentType::MIXED:
            return "Mixed";
        case SegmentType::UNKNOWN:
        default:
            return "Unknown";
    }
}

std::string Segment::toString() const {
    std::ostringstream oss;
    oss << "[" << getTypeString() << " Segment]";
    if (!sourceInfo_.filename.empty()) {
        oss << " from " << sourceInfo_.filename 
            << ":" << sourceInfo_.startLine << ":" << sourceInfo_.startColumn
            << " to " << sourceInfo_.endLine << ":" << sourceInfo_.endColumn;
    }
    if (isProcessed_) {
        oss << " (processed)";
    }
    if (!processingNote_.empty()) {
        oss << " - " << processingNote_;
    }
    oss << "\n";
    
    // 内容预览（最多显示100个字符）
    if (!content_.empty()) {
        std::string preview = content_.substr(0, 100);
        if (content_.length() > 100) {
            preview += "...";
        }
        oss << preview;
    }
    
    return oss.str();
}

// JavaScriptSegment实现
std::shared_ptr<Segment> JavaScriptSegment::clone() const {
    auto cloned = std::make_shared<JavaScriptSegment>(content_);
    cloned->sourceInfo_ = sourceInfo_;
    cloned->tokens_ = tokens_;
    cloned->isProcessed_ = isProcessed_;
    cloned->processingNote_ = processingNote_;
    cloned->isModule_ = isModule_;
    cloned->isStrict_ = isStrict_;
    return cloned;
}

std::string JavaScriptSegment::toString() const {
    std::ostringstream oss;
    oss << Segment::toString();
    
    if (isModule_) {
        oss << "\n[ES6 Module]";
    }
    if (isStrict_) {
        oss << "\n[Strict Mode]";
    }
    
    return oss.str();
}

// ChtlJavaScriptSegment实现
void ChtlJavaScriptSegment::enableFeature(const std::string& feature) {
    if (feature == "template-function") {
        features_.hasTemplateFunction = true;
    } else if (feature == "operator-extension") {
        features_.hasOperatorExtension = true;
    } else if (feature == "null-safety") {
        features_.hasNullSafety = true;
    } else if (feature == "pipe-operator") {
        features_.hasPipeOperator = true;
    } else if (feature == "pattern-matching") {
        features_.hasPatternMatching = true;
    } else if (feature == "async-extensions") {
        features_.hasAsyncExtensions = true;
    } else if (feature == "reactive-bindings") {
        features_.hasReactiveBindings = true;
    }
}

std::shared_ptr<Segment> ChtlJavaScriptSegment::clone() const {
    auto cloned = std::make_shared<ChtlJavaScriptSegment>(content_);
    cloned->sourceInfo_ = sourceInfo_;
    cloned->tokens_ = tokens_;
    cloned->isProcessed_ = isProcessed_;
    cloned->processingNote_ = processingNote_;
    cloned->features_ = features_;
    cloned->dependencies_ = dependencies_;
    return cloned;
}

std::string ChtlJavaScriptSegment::toString() const {
    std::ostringstream oss;
    oss << Segment::toString();
    
    oss << "\n[CHTL Features]";
    if (features_.hasTemplateFunction) oss << " template-function";
    if (features_.hasOperatorExtension) oss << " operator-extension";
    if (features_.hasNullSafety) oss << " null-safety";
    if (features_.hasPipeOperator) oss << " pipe-operator";
    if (features_.hasPatternMatching) oss << " pattern-matching";
    if (features_.hasAsyncExtensions) oss << " async-extensions";
    if (features_.hasReactiveBindings) oss << " reactive-bindings";
    
    if (!dependencies_.empty()) {
        oss << "\n[Dependencies]";
        for (const auto& dep : dependencies_) {
            oss << " " << dep;
        }
    }
    
    return oss.str();
}

// MixedSegment实现
std::shared_ptr<Segment> MixedSegment::clone() const {
    auto cloned = std::make_shared<MixedSegment>(content_);
    cloned->sourceInfo_ = sourceInfo_;
    cloned->tokens_ = tokens_;
    cloned->isProcessed_ = isProcessed_;
    cloned->processingNote_ = processingNote_;
    
    // 深克隆子段
    for (const auto& subSegment : subSegments_) {
        cloned->subSegments_.push_back(subSegment->clone());
    }
    
    return cloned;
}

std::string MixedSegment::toString() const {
    std::ostringstream oss;
    oss << Segment::toString();
    
    if (!subSegments_.empty()) {
        oss << "\n[SubSegments: " << subSegments_.size() << "]";
        for (size_t i = 0; i < subSegments_.size(); ++i) {
            oss << "\n  #" << (i + 1) << ": " << subSegments_[i]->getTypeString();
        }
    }
    
    return oss.str();
}

// SegmentFactory实现
std::shared_ptr<Segment> SegmentFactory::createSegment(SegmentType type, const std::string& content) {
    switch (type) {
        case SegmentType::JAVASCRIPT:
            return createJavaScriptSegment(content);
        case SegmentType::CHTL_JAVASCRIPT:
            return createChtlJavaScriptSegment(content);
        case SegmentType::MIXED:
            return createMixedSegment(content);
        default:
            return nullptr;
    }
}

std::shared_ptr<JavaScriptSegment> SegmentFactory::createJavaScriptSegment(const std::string& content) {
    return std::make_shared<JavaScriptSegment>(content);
}

std::shared_ptr<ChtlJavaScriptSegment> SegmentFactory::createChtlJavaScriptSegment(const std::string& content) {
    return std::make_shared<ChtlJavaScriptSegment>(content);
}

std::shared_ptr<MixedSegment> SegmentFactory::createMixedSegment(const std::string& content) {
    return std::make_shared<MixedSegment>(content);
}

} // namespace chtl