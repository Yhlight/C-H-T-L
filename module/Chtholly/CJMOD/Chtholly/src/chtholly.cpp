#include "../../../../../src/chtl/CHTLJSExtension.h"
#include <cmath>
#include <chrono>
#include <thread>

using namespace chtl::js;

// Chtholly扩展模块
CJMOD_BEGIN(Chtholly)
    
    // ===== 动画函数 =====
    
    CJMOD_FUNCTION(fadeIn, {
        auto element = getArg<std::string>(args, 0);
        auto duration = getArg<double>(args, 1, 400.0);
        
        // 实现淡入效果
        return "fadeIn(" + element + ", " + std::to_string(duration) + ")";
    })
    
    CJMOD_FUNCTION(fadeOut, {
        auto element = getArg<std::string>(args, 0);
        auto duration = getArg<double>(args, 1, 400.0);
        
        // 实现淡出效果
        return "fadeOut(" + element + ", " + std::to_string(duration) + ")";
    })
    
    CJMOD_FUNCTION(slideIn, {
        auto element = getArg<std::string>(args, 0);
        auto direction = getArg<std::string>(args, 1, "left");
        auto duration = getArg<double>(args, 2, 400.0);
        
        return "slideIn(" + element + ", " + direction + ", " + std::to_string(duration) + ")";
    })
    
    CJMOD_FUNCTION(bounce, {
        auto element = getArg<std::string>(args, 0);
        auto times = getArg<int>(args, 1, 3);
        
        return "bounce(" + element + ", " + std::to_string(times) + ")";
    })
    
    // ===== DOM操作函数 =====
    
    CJMOD_FUNCTION(addClass, {
        auto element = getArg<std::string>(args, 0);
        auto className = getArg<std::string>(args, 1);
        
        return element + ".classList.add('" + className + "')";
    })
    
    CJMOD_FUNCTION(removeClass, {
        auto element = getArg<std::string>(args, 0);
        auto className = getArg<std::string>(args, 1);
        
        return element + ".classList.remove('" + className + "')";
    })
    
    CJMOD_FUNCTION(toggleClass, {
        auto element = getArg<std::string>(args, 0);
        auto className = getArg<std::string>(args, 1);
        
        return element + ".classList.toggle('" + className + "')";
    })
    
    // ===== 工具函数 =====
    
    CJMOD_FUNCTION(debounce, {
        auto func = getArg<std::string>(args, 0);
        auto delay = getArg<double>(args, 1, 250.0);
        
        return "debounce(" + func + ", " + std::to_string(delay) + ")";
    })
    
    CJMOD_FUNCTION(throttle, {
        auto func = getArg<std::string>(args, 0);
        auto limit = getArg<double>(args, 1, 250.0);
        
        return "throttle(" + func + ", " + std::to_string(limit) + ")";
    })
    
    // ===== 珂朵莉特效 =====
    
    CJMOD_FUNCTION(chthollyAnimate, {
        auto element = getArg<std::string>(args, 0);
        auto animation = getArg<std::string>(args, 1, "glow");
        
        // 珂朵莉特有的动画效果
        if (animation == "glow") {
            return element + ".style.animation = 'chtholly-glow 2s infinite'";
        } else if (animation == "sparkle") {
            return element + ".style.animation = 'chtholly-sparkle 3s infinite'";
        } else if (animation == "float") {
            return element + ".style.animation = 'chtholly-float 4s ease-in-out infinite'";
        }
        
        return element + ".style.animation = '" + animation + "'";
    })
    
    CJMOD_FUNCTION(chthollyParticles, {
        auto container = getArg<std::string>(args, 0);
        auto count = getArg<int>(args, 1, 50);
        auto color = getArg<std::string>(args, 2, "#ff6b6b");
        
        // 生成粒子效果代码
        std::string code = "createParticles('" + container + "', {";
        code += "count: " + std::to_string(count) + ", ";
        code += "color: '" + color + "', ";
        code += "animation: 'float'";
        code += "})";
        
        return code;
    })
    
    CJMOD_FUNCTION(chthollyMagic, {
        auto element = getArg<std::string>(args, 0);
        
        // 珂朵莉的魔法效果组合
        std::string code = "(() => {\n";
        code += "  const el = document.querySelector('" + element + "');\n";
        code += "  el.classList.add('chtholly-magic');\n";
        code += "  el.style.transform = 'scale(1.1)';\n";
        code += "  el.style.filter = 'brightness(1.2) hue-rotate(10deg)';\n";
        code += "  setTimeout(() => {\n";
        code += "    el.style.transform = 'scale(1)';\n";
        code += "    el.style.filter = 'brightness(1) hue-rotate(0deg)';\n";
        code += "  }, 500);\n";
        code += "})()";
        
        return code;
    })
    
    // ===== 事件处理 =====
    
    CJMOD_FUNCTION(on, {
        auto element = getArg<std::string>(args, 0);
        auto event = getArg<std::string>(args, 1);
        auto handler = getArg<std::string>(args, 2);
        
        return element + ".addEventListener('" + event + "', " + handler + ")";
    })
    
    CJMOD_FUNCTION(once, {
        auto element = getArg<std::string>(args, 0);
        auto event = getArg<std::string>(args, 1);
        auto handler = getArg<std::string>(args, 2);
        
        return element + ".addEventListener('" + event + "', " + handler + ", {once: true})";
    })
    
    // ===== 实用工具 =====
    
    CJMOD_FUNCTION(delay, {
        auto ms = getArg<double>(args, 0, 1000.0);
        
        // 返回Promise延迟
        return "new Promise(resolve => setTimeout(resolve, " + std::to_string(ms) + "))";
    })
    
    CJMOD_FUNCTION(random, {
        auto min = getArg<double>(args, 0, 0.0);
        auto max = getArg<double>(args, 1, 1.0);
        
        double value = min + (max - min) * (rand() / double(RAND_MAX));
        return value;
    })

CJMOD_END()

// 导出模块
CJMOD_EXPORT(Chtholly)