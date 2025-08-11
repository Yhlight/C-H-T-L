#ifndef CHTL_VAR_GROUP_PROCESSOR_H
#define CHTL_VAR_GROUP_PROCESSOR_H

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>
#include "Node/Custom.h"
#include "Node/Template.h"

namespace chtl {

/**
 * 变量组处理器 - 处理 @Var 的函数调用和值解析
 */
class VarGroupProcessor {
public:
    // 变量值类型
    struct VarValue {
        std::string value;
        std::string type;  // color, size, number, string 等
        bool isComputed = false;
        std::function<std::string()> computeFunc;
    };
    
    // 变量组定义
    struct VarGroup {
        std::string name;
        std::unordered_map<std::string, VarValue> variables;
        std::unordered_map<std::string, std::string> defaults;
        bool allowDynamic = false;  // 是否允许动态变量
    };
    
    VarGroupProcessor();
    ~VarGroupProcessor();
    
    /**
     * 注册变量组定义
     * @param custom Custom节点包含变量组定义
     */
    void registerVarGroup(const std::shared_ptr<Custom>& custom);
    
    /**
     * 注册模板变量组
     * @param tmpl Template节点包含变量组定义
     */
    void registerTemplateVarGroup(const std::shared_ptr<Template>& tmpl);
    
    /**
     * 处理变量组函数调用
     * @param varGroupName 变量组名称
     * @param args 函数参数 (key=value 对)
     * @return 处理后的值
     */
    std::string processVarCall(const std::string& varGroupName, 
                              const std::unordered_map<std::string, std::string>& args);
    
    /**
     * 获取变量值
     * @param varGroupName 变量组名称
     * @param varName 变量名称
     * @param fallback 默认值
     * @return 变量值
     */
    std::string getVarValue(const std::string& varGroupName, 
                           const std::string& varName,
                           const std::string& fallback = "");
    
    /**
     * 批量处理CSS中的变量引用
     * @param css 包含变量引用的CSS
     * @return 处理后的CSS
     */
    std::string processCSSVariables(const std::string& css);
    
    /**
     * 注册计算变量
     * @param varGroupName 变量组名称
     * @param varName 变量名称
     * @param computeFunc 计算函数
     */
    void registerComputedVar(const std::string& varGroupName,
                            const std::string& varName,
                            std::function<std::string()> computeFunc);
    
    /**
     * 生成CSS变量声明
     * @param varGroupName 变量组名称
     * @param prefix CSS变量前缀
     * @return CSS变量声明
     */
    std::string generateCSSVarDeclarations(const std::string& varGroupName,
                                          const std::string& prefix = "--chtl-");
    
    /**
     * 验证变量值
     * @param type 变量类型
     * @param value 变量值
     * @return 是否有效
     */
    bool validateVarValue(const std::string& type, const std::string& value);
    
    /**
     * 获取所有变量组名称
     */
    std::vector<std::string> getVarGroupNames() const;
    
    /**
     * 检查变量组是否存在
     */
    bool hasVarGroup(const std::string& name) const;
    
    /**
     * 导出变量组定义（用于模块导出）
     */
    std::string exportVarGroup(const std::string& varGroupName) const;
    
private:
    // 存储所有变量组
    std::unordered_map<std::string, VarGroup> varGroups_;
    
    // 变量组继承关系
    std::unordered_map<std::string, std::string> inheritance_;
    
    // 全局变量覆盖
    std::unordered_map<std::string, std::string> globalOverrides_;
    
    // 解析变量组节点
    VarGroup parseVarGroup(const std::shared_ptr<Node>& node);
    
    // 解析函数调用表达式
    std::pair<std::string, std::unordered_map<std::string, std::string>> 
    parseFunctionCall(const std::string& expr);
    
    // 应用变量继承
    void applyInheritance(VarGroup& group);
    
    // 计算表达式（支持简单运算）
    std::string evaluateExpression(const std::string& expr,
                                  const std::unordered_map<std::string, std::string>& context);
    
    // 类型转换
    std::string convertValue(const std::string& value, 
                            const std::string& fromType, 
                            const std::string& toType);
};

} // namespace chtl

#endif // CHTL_VAR_GROUP_PROCESSOR_H