#ifndef CHTL_UTILS_CONSTRAINT_EVALUATOR_H
#define CHTL_UTILS_CONSTRAINT_EVALUATOR_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace chtl {

// 前向声明
class Node;

/**
 * 约束评估器 - 处理 CHTL 的 except 条件
 */
class ConstraintEvaluator {
public:
    // 约束类型
    enum class ConstraintType {
        DEVICE,      // mobile, desktop, tablet
        BROWSER,     // chrome, firefox, safari, edge
        FEATURE,     // touch, no-touch, webgl, no-webgl
        MEDIA,       // screen, print, speech
        CUSTOM       // 自定义约束
    };
    
    // 约束条件结构
    struct Constraint {
        ConstraintType type;
        std::string name;
        std::string value;
        bool negated = false;  // 是否是否定条件（not mobile）
    };
    
    ConstraintEvaluator();
    ~ConstraintEvaluator();
    
    /**
     * 解析约束字符串
     * @param constraintStr 约束字符串，如 "mobile", "not desktop", "browser:chrome"
     * @return 解析后的约束结构
     */
    Constraint parseConstraint(const std::string& constraintStr);
    
    /**
     * 评估约束是否满足
     * @param constraint 约束条件
     * @param context 评估上下文（包含设备信息、浏览器信息等）
     * @return 是否满足约束
     */
    bool evaluateConstraint(const Constraint& constraint, 
                           const std::map<std::string, std::string>& context);
    
    /**
     * 生成约束对应的 CSS 媒体查询
     * @param constraint 约束条件
     * @return CSS 媒体查询字符串
     */
    std::string generateMediaQuery(const Constraint& constraint);
    
    /**
     * 生成约束对应的 JavaScript 条件
     * @param constraint 约束条件
     * @return JavaScript 条件表达式
     */
    std::string generateJavaScriptCondition(const Constraint& constraint);
    
    /**
     * 注册自定义约束评估器
     * @param name 约束名称
     * @param evaluator 评估函数
     */
    void registerCustomConstraint(const std::string& name,
                                 std::function<bool(const std::string&)> evaluator);
    
private:
    // 设备约束映射到媒体查询
    static const std::map<std::string, std::string> DEVICE_MEDIA_QUERIES;
    
    // 特性约束映射到 JavaScript 检测
    static const std::map<std::string, std::string> FEATURE_DETECTIONS;
    
    // 自定义约束评估器
    std::map<std::string, std::function<bool(const std::string&)>> customConstraints_;
    
    // 解析复合约束（and, or）
    std::vector<Constraint> parseCompoundConstraint(const std::string& constraintStr);
    
    // 规范化约束名称
    std::string normalizeConstraintName(const std::string& name);
};

} // namespace chtl

#endif // CHTL_UTILS_CONSTRAINT_EVALUATOR_H