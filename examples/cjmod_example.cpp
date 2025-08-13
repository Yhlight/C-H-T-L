/**
 * 简单的 CJMOD 示例 - MathTools
 */

#include "../src/chtl/CHTLJSExtension.h"
#include <cmath>
#include <numeric>
#include <algorithm>

namespace chtl {
namespace js {

class MathToolsExtension : public Extension {
public:
    MathToolsExtension() : Extension("MathTools") {}
    
    void initialize() override {
        // 基本数学运算
        function("add", [](const Array& args) -> Value {
            double a = getArg<double>(args, 0, 0.0);
            double b = getArg<double>(args, 1, 0.0);
            return a + b;
        });
        
        function("multiply", [](const Array& args) -> Value {
            double a = getArg<double>(args, 0, 0.0);
            double b = getArg<double>(args, 1, 0.0);
            return a * b;
        });
        
        function("power", [](const Array& args) -> Value {
            double base = getArg<double>(args, 0, 0.0);
            double exp = getArg<double>(args, 1, 0.0);
            return std::pow(base, exp);
        });
        
        // 数组操作
        function("sum", [](const Array& args) -> Value {
            if (args.empty()) return 0.0;
            
            double sum = 0.0;
            for (const auto& arg : args) {
                try {
                    sum += std::any_cast<double>(arg);
                } catch(...) {
                    // 忽略非数字参数
                }
            }
            return sum;
        });
        
        function("average", [](const Array& args) -> Value {
            if (args.empty()) return 0.0;
            
            double sum = 0.0;
            int count = 0;
            for (const auto& arg : args) {
                try {
                    sum += std::any_cast<double>(arg);
                    count++;
                } catch(...) {
                    // 忽略非数字参数
                }
            }
            return count > 0 ? sum / count : 0.0;
        });
        
        // 三角函数
        function("sin", [](const Array& args) -> Value {
            double angle = getArg<double>(args, 0, 0.0);
            return std::sin(angle);
        });
        
        function("cos", [](const Array& args) -> Value {
            double angle = getArg<double>(args, 0, 0.0);
            return std::cos(angle);
        });
        
        function("tan", [](const Array& args) -> Value {
            double angle = getArg<double>(args, 0, 0.0);
            return std::tan(angle);
        });
    }
};

// 导出设置
struct MathToolsExporter {
    MathToolsExporter() {
        CJMODExporter::setHandlers([]() {
            auto extension = std::make_shared<MathToolsExtension>();
            ExtensionManager::getInstance().registerExtension(extension);
        });
    }
};

static MathToolsExporter exporter;

} // namespace js
} // namespace chtl