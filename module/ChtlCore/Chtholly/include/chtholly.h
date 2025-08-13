#ifndef CHTHOLLY_H
#define CHTHOLLY_H

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <map>

namespace chtholly {

// 动画缓动函数类型
enum class EasingType {
    Linear,
    EaseIn,
    EaseOut,
    EaseInOut,
    EaseInQuad,
    EaseOutQuad,
    EaseInOutQuad,
    EaseInCubic,
    EaseOutCubic,
    EaseInOutCubic,
    EaseInElastic,
    EaseOutElastic,
    EaseInOutElastic,
    EaseInBounce,
    EaseOutBounce,
    EaseInOutBounce
};

// 动画属性
struct AnimationProperty {
    std::string name;
    double from;
    double to;
    std::string unit;
};

// 动画配置
struct AnimationConfig {
    double duration = 1000;  // 毫秒
    double delay = 0;
    EasingType easing = EasingType::Linear;
    int iterations = 1;
    bool alternate = false;
    std::function<void()> onComplete;
    std::function<void(double)> onProgress;
};

// 粒子效果类型
enum class ParticleType {
    Snow,
    Rain,
    Stars,
    Bubbles,
    Confetti,
    Fire,
    Smoke,
    Custom
};

// 粒子配置
struct ParticleConfig {
    ParticleType type = ParticleType::Stars;
    int count = 100;
    double speed = 1.0;
    double size = 5.0;
    std::string color = "#ffffff";
    double lifetime = 5000;  // 毫秒
    std::map<std::string, std::string> customProperties;
};

// 手势类型
enum class GestureType {
    Tap,
    DoubleTap,
    LongPress,
    Swipe,
    Pinch,
    Rotate,
    Pan
};

// 手势配置
struct GestureConfig {
    double threshold = 10.0;  // 像素
    double timeout = 500.0;   // 毫秒
    std::function<void(const std::string&)> onGesture;
};

// 主动画类
class Animation {
public:
    Animation(const std::string& elementId);
    ~Animation();
    
    // 动画方法
    Animation& animate(const std::vector<AnimationProperty>& properties, 
                      const AnimationConfig& config = {});
    Animation& chain(const std::vector<AnimationProperty>& properties,
                    const AnimationConfig& config = {});
    Animation& parallel(const std::vector<AnimationProperty>& properties,
                       const AnimationConfig& config = {});
    
    // 控制方法
    void play();
    void pause();
    void stop();
    void reverse();
    void seek(double position);  // 0.0 - 1.0
    
    // 状态查询
    bool isPlaying() const;
    double getProgress() const;
    
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

// 粒子系统类
class ParticleSystem {
public:
    ParticleSystem(const std::string& containerId);
    ~ParticleSystem();
    
    // 创建粒子效果
    void create(const ParticleConfig& config);
    void start();
    void stop();
    void clear();
    
    // 自定义粒子
    void defineCustomParticle(const std::string& name,
                             std::function<void(double x, double y, double time)> updateFunc);
    
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

// 手势识别类
class GestureRecognizer {
public:
    GestureRecognizer(const std::string& elementId);
    ~GestureRecognizer();
    
    // 注册手势
    void registerGesture(GestureType type, const GestureConfig& config = {});
    void unregisterGesture(GestureType type);
    
    // 启用/禁用
    void enable();
    void disable();
    
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

// 视差滚动类
class ParallaxScroller {
public:
    ParallaxScroller();
    ~ParallaxScroller();
    
    // 添加图层
    void addLayer(const std::string& elementId, double speed, double offset = 0);
    void removeLayer(const std::string& elementId);
    
    // 控制
    void enable();
    void disable();
    void setBaseSpeed(double speed);
    
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

// 工具函数
namespace utils {
    // 缓动函数
    double ease(EasingType type, double t);
    
    // 颜色工具
    std::string interpolateColor(const std::string& from, 
                                const std::string& to, 
                                double t);
    std::string randomColor();
    
    // DOM工具
    void addClass(const std::string& elementId, const std::string& className);
    void removeClass(const std::string& elementId, const std::string& className);
    bool hasClass(const std::string& elementId, const std::string& className);
    
    // 性能优化
    void requestAnimationFrame(std::function<void(double)> callback);
    void cancelAnimationFrame(int id);
}

// 导出函数（供CHTL调用）
extern "C" {
    // 初始化Chtholly
    void chtholly_init();
    
    // 动画相关
    void* chtholly_create_animation(const char* elementId);
    void chtholly_animate(void* animation, const char* properties, const char* config);
    void chtholly_play_animation(void* animation);
    void chtholly_stop_animation(void* animation);
    void chtholly_destroy_animation(void* animation);
    
    // 粒子系统
    void* chtholly_create_particle_system(const char* containerId);
    void chtholly_start_particles(void* system, const char* config);
    void chtholly_stop_particles(void* system);
    void chtholly_destroy_particle_system(void* system);
    
    // 手势识别
    void* chtholly_create_gesture_recognizer(const char* elementId);
    void chtholly_register_gesture(void* recognizer, const char* type, const char* callback);
    void chtholly_destroy_gesture_recognizer(void* recognizer);
}

} // namespace chtholly

#endif // CHTHOLLY_H