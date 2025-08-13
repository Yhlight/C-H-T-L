/**
 * 珂朵莉CJMOD扩展
 * 提供CHTL JS的动画和交互功能
 */

#include "../../../../../src/chtl/CHTLJSExtension.h"
#include <string>
#include <sstream>
#include <cmath>

namespace chtl {
namespace js {

// 珂朵莉扩展类
class ChthollyExtension : public Extension {
public:
    ChthollyExtension() : Extension("Chtholly") {}
    
    void initialize() override {
        // 注册淡入动画
        function("fadeIn", [](const Array& args) -> Value {
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
        });
        
        // 注册淡出动画
        function("fadeOut", [](const Array& args) -> Value {
            auto element = getArg<std::string>(args, 0);
            auto duration = getArg<double>(args, 1, 400.0);
            
            std::stringstream js;
            js << "(function(){"
               << "  var el = " << element << ";"
               << "  el.style.transition = 'opacity " << duration << "ms ease-out';"
               << "  el.style.opacity = '0';"
               << "})()";
            
            return js.str();
        });
        
        // 注册滑入动画
        function("slideIn", [](const Array& args) -> Value {
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
        });
        
        // 注册类操作函数
        function("addClass", [](const Array& args) -> Value {
            auto element = getArg<std::string>(args, 0);
            auto className = getArg<std::string>(args, 1);
            
            return element + ".classList.add('" + className + "')";
        });
        
        function("removeClass", [](const Array& args) -> Value {
            auto element = getArg<std::string>(args, 0);
            auto className = getArg<std::string>(args, 1);
            
            return element + ".classList.remove('" + className + "')";
        });
        
        function("toggleClass", [](const Array& args) -> Value {
            auto element = getArg<std::string>(args, 0);
            auto className = getArg<std::string>(args, 1);
            
            return element + ".classList.toggle('" + className + "')";
        });
        
        // 注册防抖函数
        function("debounce", [](const Array& args) -> Value {
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
        });
        
        // 注册珂朵莉特效
        function("chthollyGlow", [](const Array& args) -> Value {
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
        });
        
        // 注册珂朵莉旋转动画
        function("chthollyRotate", [](const Array& args) -> Value {
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
        });
        
        // 注册珂朵莉动画序列
        function("chthollySequence", [](const Array& args) -> Value {
            auto element = getArg<std::string>(args, 0);
            
            std::stringstream js;
            js << "(function(){"
               << "  var el = " << element << ";"
               << "  var sequence = ["
               << "    function() { el.style.transform = 'scale(1.1)'; },"
               << "    function() { el.style.transform = 'scale(1.1) rotate(5deg)'; },"
               << "    function() { el.style.transform = 'scale(1.1) rotate(-5deg)'; },"
               << "    function() { el.style.transform = 'scale(1)'; }"
               << "  ];"
               << "  el.style.transition = 'transform 200ms ease-in-out';"
               << "  var index = 0;"
               << "  var interval = setInterval(function() {"
               << "    sequence[index % sequence.length]();"
               << "    index++;"
               << "    if (index >= 12) clearInterval(interval);"
               << "  }, 200);"
               << "})()";
            
            return js.str();
        });
    }
};

// CJMOD导出设置
struct ChthollyExporter {
    ChthollyExporter() {
        CJMODExporter::setHandlers(
            []() {
                // 初始化函数
                auto extension = std::make_shared<ChthollyExtension>();
                ExtensionManager::getInstance().registerExtension(extension);
            },
            []() {
                // 清理函数（可选）
            }
        );
    }
};

// 全局实例，确保在加载时设置导出函数
static ChthollyExporter exporter;

} // namespace js
} // namespace chtl