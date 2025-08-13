// 简单的CJMOD示例 - 数学工具扩展
#include "CHTLJSExtension.h"
#include <cmath>
#include <numeric>
#include <algorithm>

using namespace chtl::js;

CJMOD_BEGIN(MathTools)
    
    // 基础数学函数
    CJMOD_FUNCTION(sqrt, {
        double x = getArg<double>(args, 0, 0.0);
        return std::sqrt(x);
    })
    
    CJMOD_FUNCTION(abs, {
        double x = getArg<double>(args, 0, 0.0);
        return std::abs(x);
    })
    
    CJMOD_FUNCTION(max, {
        double a = getArg<double>(args, 0, 0.0);
        double b = getArg<double>(args, 1, 0.0);
        return std::max(a, b);
    })
    
    CJMOD_FUNCTION(min, {
        double a = getArg<double>(args, 0, 0.0);
        double b = getArg<double>(args, 1, 0.0);
        return std::min(a, b);
    })
    
    // 数组操作
    CJMOD_FUNCTION(sum, {
        Array arr = getArg<Array>(args, 0, Array{});
        double total = 0.0;
        for (const auto& val : arr) {
            total += value_cast<double>(val);
        }
        return total;
    })
    
    CJMOD_FUNCTION(average, {
        Array arr = getArg<Array>(args, 0, Array{});
        if (arr.empty()) return 0.0;
        
        double total = 0.0;
        for (const auto& val : arr) {
            total += value_cast<double>(val);
        }
        return total / arr.size();
    })
    
    // 实用函数
    CJMOD_FUNCTION(clamp, {
        double value = getArg<double>(args, 0, 0.0);
        double min_val = getArg<double>(args, 1, 0.0);
        double max_val = getArg<double>(args, 2, 1.0);
        return std::clamp(value, min_val, max_val);
    })
    
    CJMOD_FUNCTION(lerp, {
        double a = getArg<double>(args, 0, 0.0);
        double b = getArg<double>(args, 1, 1.0);
        double t = getArg<double>(args, 2, 0.5);
        return a + (b - a) * t;
    })

CJMOD_END()

CJMOD_EXPORT(MathTools)

// 使用示例（在CHTL中）：
/*
[Import] @CJmod MathTools

script {
    // 基础数学
    var x = sqrt(16);        // 4
    var y = abs(-5);         // 5
    var z = max(10, 20);     // 20
    
    // 数组操作
    var numbers = [1, 2, 3, 4, 5];
    var total = sum(numbers);       // 15
    var avg = average(numbers);     // 3
    
    // 实用函数
    var clamped = clamp(150, 0, 100);  // 100
    var interpolated = lerp(0, 100, 0.3); // 30
}
*/