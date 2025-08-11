#include "Utils/ConstraintEvaluator.h"
#include <algorithm>
#include <sstream>
#include <regex>

namespace chtl {

// 静态成员定义
const std::map<std::string, std::string> ConstraintEvaluator::DEVICE_MEDIA_QUERIES = {
    {"mobile", "(max-width: 767px)"},
    {"tablet", "(min-width: 768px) and (max-width: 1023px)"},
    {"desktop", "(min-width: 1024px)"},
    {"portrait", "(orientation: portrait)"},
    {"landscape", "(orientation: landscape)"},
    {"retina", "(-webkit-min-device-pixel-ratio: 2), (min-resolution: 192dpi)"},
    {"print", "print"},
    {"screen", "screen"}
};

const std::map<std::string, std::string> ConstraintEvaluator::FEATURE_DETECTIONS = {
    {"touch", "'ontouchstart' in window"},
    {"no-touch", "!('ontouchstart' in window)"},
    {"webgl", "!!window.WebGLRenderingContext"},
    {"no-webgl", "!window.WebGLRenderingContext"},
    {"geolocation", "'geolocation' in navigator"},
    {"no-geolocation", "!('geolocation' in navigator)"},
    {"localstorage", "'localStorage' in window"},
    {"no-localstorage", "!('localStorage' in window)"},
    {"webworker", "'Worker' in window"},
    {"no-webworker", "!('Worker' in window)"}
};

ConstraintEvaluator::ConstraintEvaluator() {}

ConstraintEvaluator::~ConstraintEvaluator() {}

ConstraintEvaluator::Constraint ConstraintEvaluator::parseConstraint(const std::string& constraintStr) {
    Constraint constraint;
    std::string str = constraintStr;
    
    // 去除首尾空格
    str.erase(0, str.find_first_not_of(" \t"));
    str.erase(str.find_last_not_of(" \t") + 1);
    
    // 检查是否是否定条件
    if (str.substr(0, 4) == "not ") {
        constraint.negated = true;
        str = str.substr(4);
    }
    
    // 检查是否有冒号（browser:chrome 格式）
    size_t colonPos = str.find(':');
    if (colonPos != std::string::npos) {
        constraint.name = str.substr(0, colonPos);
        constraint.value = str.substr(colonPos + 1);
    } else {
        constraint.name = str;
    }
    
    // 规范化名称
    constraint.name = normalizeConstraintName(constraint.name);
    
    // 确定约束类型
    if (DEVICE_MEDIA_QUERIES.find(constraint.name) != DEVICE_MEDIA_QUERIES.end()) {
        constraint.type = ConstraintType::DEVICE;
    } else if (constraint.name == "browser" || 
               constraint.name == "chrome" || 
               constraint.name == "firefox" || 
               constraint.name == "safari" || 
               constraint.name == "edge") {
        constraint.type = ConstraintType::BROWSER;
    } else if (FEATURE_DETECTIONS.find(constraint.name) != FEATURE_DETECTIONS.end() ||
               FEATURE_DETECTIONS.find("no-" + constraint.name) != FEATURE_DETECTIONS.end()) {
        constraint.type = ConstraintType::FEATURE;
    } else if (constraint.name == "screen" || 
               constraint.name == "print" || 
               constraint.name == "speech") {
        constraint.type = ConstraintType::MEDIA;
    } else {
        constraint.type = ConstraintType::CUSTOM;
    }
    
    return constraint;
}

bool ConstraintEvaluator::evaluateConstraint(const Constraint& constraint,
                                            const std::map<std::string, std::string>& context) {
    bool result = false;
    
    switch (constraint.type) {
        case ConstraintType::DEVICE: {
            auto it = context.find("device");
            if (it != context.end()) {
                result = (it->second == constraint.name);
            }
            break;
        }
        
        case ConstraintType::BROWSER: {
            auto it = context.find("browser");
            if (it != context.end()) {
                if (constraint.value.empty()) {
                    result = (it->second == constraint.name);
                } else {
                    result = (it->second == constraint.value);
                }
            }
            break;
        }
        
        case ConstraintType::FEATURE: {
            auto it = context.find("features");
            if (it != context.end()) {
                result = (it->second.find(constraint.name) != std::string::npos);
            }
            break;
        }
        
        case ConstraintType::MEDIA: {
            auto it = context.find("media");
            if (it != context.end()) {
                result = (it->second == constraint.name);
            }
            break;
        }
        
        case ConstraintType::CUSTOM: {
            auto it = customConstraints_.find(constraint.name);
            if (it != customConstraints_.end()) {
                result = it->second(constraint.value);
            }
            break;
        }
    }
    
    // 应用否定
    if (constraint.negated) {
        result = !result;
    }
    
    return result;
}

std::string ConstraintEvaluator::generateMediaQuery(const Constraint& constraint) {
    std::stringstream ss;
    
    if (constraint.type == ConstraintType::DEVICE || constraint.type == ConstraintType::MEDIA) {
        auto it = DEVICE_MEDIA_QUERIES.find(constraint.name);
        if (it != DEVICE_MEDIA_QUERIES.end()) {
            if (constraint.negated) {
                ss << "not " << it->second;
            } else {
                ss << it->second;
            }
            return ss.str();
        }
    }
    
    // 对于无法转换为媒体查询的约束，返回空字符串
    return "";
}

std::string ConstraintEvaluator::generateJavaScriptCondition(const Constraint& constraint) {
    std::stringstream ss;
    
    switch (constraint.type) {
        case ConstraintType::DEVICE: {
            // 使用 matchMedia 检测设备类型
            auto it = DEVICE_MEDIA_QUERIES.find(constraint.name);
            if (it != DEVICE_MEDIA_QUERIES.end()) {
                ss << "window.matchMedia('" << it->second << "').matches";
            }
            break;
        }
        
        case ConstraintType::BROWSER: {
            // 浏览器检测
            ss << "navigator.userAgent.toLowerCase().indexOf('" << constraint.name << "') > -1";
            break;
        }
        
        case ConstraintType::FEATURE: {
            // 特性检测
            auto it = FEATURE_DETECTIONS.find(constraint.name);
            if (it != FEATURE_DETECTIONS.end()) {
                ss << it->second;
            }
            break;
        }
        
        case ConstraintType::MEDIA: {
            // 媒体类型检测
            if (constraint.name == "print") {
                ss << "window.matchMedia('print').matches";
            } else {
                ss << "true"; // 默认为 screen
            }
            break;
        }
        
        case ConstraintType::CUSTOM: {
            // 自定义约束，生成函数调用
            ss << "window.CHTLConstraints && window.CHTLConstraints['" 
               << constraint.name << "'] && window.CHTLConstraints['" 
               << constraint.name << "']('" << constraint.value << "')";
            break;
        }
    }
    
    std::string condition = ss.str();
    if (constraint.negated && !condition.empty()) {
        condition = "!(" + condition + ")";
    }
    
    return condition;
}

void ConstraintEvaluator::registerCustomConstraint(const std::string& name,
                                                  std::function<bool(const std::string&)> evaluator) {
    customConstraints_[normalizeConstraintName(name)] = evaluator;
}

std::vector<ConstraintEvaluator::Constraint> 
ConstraintEvaluator::parseCompoundConstraint(const std::string& constraintStr) {
    std::vector<Constraint> constraints;
    
    // 简单实现：用逗号分隔多个约束（表示 AND 关系）
    std::istringstream iss(constraintStr);
    std::string token;
    
    while (std::getline(iss, token, ',')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        
        if (!token.empty()) {
            constraints.push_back(parseConstraint(token));
        }
    }
    
    return constraints;
}

std::string ConstraintEvaluator::normalizeConstraintName(const std::string& name) {
    std::string normalized = name;
    
    // 转换为小写
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    
    // 移除连字符和下划线
    normalized.erase(std::remove(normalized.begin(), normalized.end(), '-'), normalized.end());
    normalized.erase(std::remove(normalized.begin(), normalized.end(), '_'), normalized.end());
    
    return normalized;
}

} // namespace chtl