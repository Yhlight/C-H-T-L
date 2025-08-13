#include "../include/chtholly.h"
#include <cmath>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>

namespace chtholly {

// 动画实现类
class Animation::Impl {
public:
    Impl(const std::string& elementId) : elementId_(elementId), isPlaying_(false), progress_(0.0) {}
    
    void animate(const std::vector<AnimationProperty>& properties, const AnimationConfig& config) {
        currentProperties_ = properties;
        currentConfig_ = config;
        startTime_ = std::chrono::steady_clock::now();
        isPlaying_ = true;
    }
    
    void updateProgress() {
        if (!isPlaying_) return;
        
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime_).count();
        
        if (elapsed < currentConfig_.delay) {
            progress_ = 0.0;
            return;
        }
        
        double effectiveElapsed = elapsed - currentConfig_.delay;
        progress_ = std::min(1.0, effectiveElapsed / currentConfig_.duration);
        
        // 应用缓动函数
        double easedProgress = utils::ease(currentConfig_.easing, progress_);
        
        // 更新属性
        for (const auto& prop : currentProperties_) {
            double value = prop.from + (prop.to - prop.from) * easedProgress;
            applyProperty(prop.name, value, prop.unit);
        }
        
        // 回调
        if (currentConfig_.onProgress) {
            currentConfig_.onProgress(progress_);
        }
        
        // 完成检查
        if (progress_ >= 1.0) {
            if (currentConfig_.iterations > 1 || currentConfig_.iterations == -1) {
                // 重复或无限循环
                startTime_ = now;
                if (currentConfig_.alternate) {
                    // 反向动画
                    for (auto& prop : currentProperties_) {
                        std::swap(prop.from, prop.to);
                    }
                }
            } else {
                isPlaying_ = false;
                if (currentConfig_.onComplete) {
                    currentConfig_.onComplete();
                }
            }
        }
    }
    
    void applyProperty(const std::string& name, double value, const std::string& unit) {
        // 这里应该调用JavaScript来更新DOM
        // 简化实现，实际需要通过绑定机制
        std::stringstream js;
        js << "document.getElementById('" << elementId_ << "').style." << name 
           << " = '" << value << unit << "';";
        // executeJS(js.str());
    }
    
    std::string elementId_;
    bool isPlaying_;
    double progress_;
    std::chrono::steady_clock::time_point startTime_;
    std::vector<AnimationProperty> currentProperties_;
    AnimationConfig currentConfig_;
};

Animation::Animation(const std::string& elementId) 
    : pImpl(std::make_unique<Impl>(elementId)) {}

Animation::~Animation() = default;

Animation& Animation::animate(const std::vector<AnimationProperty>& properties, 
                            const AnimationConfig& config) {
    pImpl->animate(properties, config);
    return *this;
}

void Animation::play() {
    pImpl->isPlaying_ = true;
}

void Animation::pause() {
    pImpl->isPlaying_ = false;
}

bool Animation::isPlaying() const {
    return pImpl->isPlaying_;
}

double Animation::getProgress() const {
    return pImpl->progress_;
}

// 缓动函数实现
namespace utils {

double ease(EasingType type, double t) {
    switch (type) {
        case EasingType::Linear:
            return t;
            
        case EasingType::EaseIn:
            return t * t;
            
        case EasingType::EaseOut:
            return t * (2 - t);
            
        case EasingType::EaseInOut:
            return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
            
        case EasingType::EaseInQuad:
            return t * t;
            
        case EasingType::EaseOutQuad:
            return t * (2 - t);
            
        case EasingType::EaseInOutQuad:
            return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
            
        case EasingType::EaseInCubic:
            return t * t * t;
            
        case EasingType::EaseOutCubic:
            return (--t) * t * t + 1;
            
        case EasingType::EaseInOutCubic:
            return t < 0.5 ? 4 * t * t * t : (t - 1) * (2 * t - 2) * (2 * t - 2) + 1;
            
        case EasingType::EaseInElastic:
            if (t == 0 || t == 1) return t;
            return -std::pow(2, 10 * (t - 1)) * std::sin((t - 1.1) * 5 * M_PI);
            
        case EasingType::EaseOutElastic:
            if (t == 0 || t == 1) return t;
            return std::pow(2, -10 * t) * std::sin((t - 0.1) * 5 * M_PI) + 1;
            
        case EasingType::EaseInBounce: {
            return 1 - ease(EasingType::EaseOutBounce, 1 - t);
        }
            
        case EasingType::EaseOutBounce: {
            if (t < 1/2.75) {
                return 7.5625 * t * t;
            } else if (t < 2/2.75) {
                t -= 1.5/2.75;
                return 7.5625 * t * t + 0.75;
            } else if (t < 2.5/2.75) {
                t -= 2.25/2.75;
                return 7.5625 * t * t + 0.9375;
            } else {
                t -= 2.625/2.75;
                return 7.5625 * t * t + 0.984375;
            }
        }
            
        default:
            return t;
    }
}

std::string interpolateColor(const std::string& from, const std::string& to, double t) {
    // 简化的颜色插值实现
    // 假设输入是 #RRGGBB 格式
    if (from.length() != 7 || to.length() != 7 || from[0] != '#' || to[0] != '#') {
        return from;
    }
    
    auto hexToInt = [](const std::string& hex, size_t start) {
        return std::stoi(hex.substr(start, 2), nullptr, 16);
    };
    
    int r1 = hexToInt(from, 1), g1 = hexToInt(from, 3), b1 = hexToInt(from, 5);
    int r2 = hexToInt(to, 1), g2 = hexToInt(to, 3), b2 = hexToInt(to, 5);
    
    int r = r1 + (r2 - r1) * t;
    int g = g1 + (g2 - g1) * t;
    int b = b1 + (b2 - b1) * t;
    
    std::stringstream ss;
    ss << "#" << std::hex << std::setfill('0') 
       << std::setw(2) << r 
       << std::setw(2) << g 
       << std::setw(2) << b;
    
    return ss.str();
}

std::string randomColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 255);
    
    std::stringstream ss;
    ss << "#" << std::hex << std::setfill('0')
       << std::setw(2) << dis(gen)
       << std::setw(2) << dis(gen)
       << std::setw(2) << dis(gen);
    
    return ss.str();
}

} // namespace utils

// C接口实现
extern "C" {

void chtholly_init() {
    // 初始化代码
}

void* chtholly_create_animation(const char* elementId) {
    return new Animation(elementId);
}

void chtholly_play_animation(void* animation) {
    if (animation) {
        static_cast<Animation*>(animation)->play();
    }
}

void chtholly_stop_animation(void* animation) {
    if (animation) {
        static_cast<Animation*>(animation)->pause();
    }
}

void chtholly_destroy_animation(void* animation) {
    delete static_cast<Animation*>(animation);
}

} // extern "C"

} // namespace chtholly