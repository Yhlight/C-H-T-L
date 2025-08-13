/**
 * 珂朵莉CJMOD扩展
 * 提供CHTL JS的动画和交互功能
 */

#include "../../../../../src/chtl/CHTLJSExtension.h"
#include <string>
#include <sstream>
#include <cmath>

using namespace chtl::js;

CJMOD_BEGIN(Chtholly)
    // 淡入动画
    CJMOD_FUNCTION(fadeIn, {
        auto element = getArg<std::string>(args, 0);
        auto duration = getArg<double>(args, 1, 400.0);
        
        std::stringstream js;
        js << "(function(){"
           << "  var el = " << element << ";"
           << "  el.style.opacity = '0';"
           << "  el.style.transition = 'opacity " << duration << "ms ease-in';"
           << "  setTimeout(function() { el.style.opacity = '1'; }, 10);"
           << "})()";
        
        return js.str();
    })
    
    // 淡出动画
    CJMOD_FUNCTION(fadeOut, {
        auto element = getArg<std::string>(args, 0);
        auto duration = getArg<double>(args, 1, 400.0);
        
        std::stringstream js;
        js << "(function(){"
           << "  var el = " << element << ";"
           << "  el.style.transition = 'opacity " << duration << "ms ease-out';"
           << "  el.style.opacity = '0';"
           << "})()";
        
        return js.str();
    })
    
    // 滑入动画
    CJMOD_FUNCTION(slideIn, {
        auto element = getArg<std::string>(args, 0);
        auto direction = getArg<std::string>(args, 1, "left");
        auto duration = getArg<double>(args, 2, 400.0);
        
        std::stringstream js;
        js << "(function(){"
           << "  var el = " << element << ";"
           << "  var translate = '" << direction << "' === 'left' ? 'translateX(-100%)' : 'translateY(-100%)';"
           << "  el.style.transform = translate;"
           << "  el.style.transition = 'transform " << duration << "ms ease-out';"
           << "  setTimeout(function() { el.style.transform = 'translate(0)'; }, 10);"
           << "})()";
        
        return js.str();
    })
    
    // 添加类
    CJMOD_FUNCTION(addClass, {
        auto element = getArg<std::string>(args, 0);
        auto className = getArg<std::string>(args, 1);
        
        std::stringstream js;
        js << element << ".classList.add('" << className << "')";
        
        return js.str();
    })
    
    // 移除类
    CJMOD_FUNCTION(removeClass, {
        auto element = getArg<std::string>(args, 0);
        auto className = getArg<std::string>(args, 1);
        
        std::stringstream js;
        js << element << ".classList.remove('" << className << "')";
        
        return js.str();
    })
    
    // 切换类
    CJMOD_FUNCTION(toggleClass, {
        auto element = getArg<std::string>(args, 0);
        auto className = getArg<std::string>(args, 1);
        
        std::stringstream js;
        js << element << ".classList.toggle('" << className << "')";
        
        return js.str();
    })
    
    // 防抖函数
    CJMOD_FUNCTION(debounce, {
        auto func = getArg<std::string>(args, 0);
        auto delay = getArg<double>(args, 1, 300.0);
        
        std::stringstream js;
        js << "(function(){"
           << "  var timer = null;"
           << "  return function() {"
           << "    var context = this, args = arguments;"
           << "    clearTimeout(timer);"
           << "    timer = setTimeout(function() {"
           << "      " << func << ".apply(context, args);"
           << "    }, " << delay << ");"
           << "  };"
           << "})()";
        
        return js.str();
    })
    
    // 珂朵莉特效 - 闪光效果
    CJMOD_FUNCTION(chthollyGlow, {
        auto element = getArg<std::string>(args, 0);
        auto color = getArg<std::string>(args, 1, "#87CEEB");
        auto duration = getArg<double>(args, 2, 1000.0);
        
        std::stringstream js;
        js << "(function(){"
           << "  var el = " << element << ";"
           << "  el.style.boxShadow = '0 0 20px " << color << "';"
           << "  el.style.transition = 'box-shadow " << duration << "ms ease-in-out';"
           << "  setTimeout(function() {"
           << "    el.style.boxShadow = '0 0 0 transparent';"
           << "  }, " << duration << ");"
           << "})()";
        
        return js.str();
    })
    
    // 珂朵莉动画 - 幸福旋转
    CJMOD_FUNCTION(chthollyRotate, {
        auto element = getArg<std::string>(args, 0);
        auto degrees = getArg<double>(args, 1, 360.0);
        auto duration = getArg<double>(args, 2, 1000.0);
        
        std::stringstream js;
        js << "(function(){"
           << "  var el = " << element << ";"
           << "  el.style.transition = 'transform " << duration << "ms ease-in-out';"
           << "  el.style.transform = 'rotate(" << degrees << "deg)';"
           << "})()";
        
        return js.str();
    })
CJMOD_END()

CJMOD_EXPORT(Chtholly)