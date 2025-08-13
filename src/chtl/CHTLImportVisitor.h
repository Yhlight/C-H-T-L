#pragma once

#include "generated/CHTLParserBaseVisitor.h"
#include "CHTLContext.h"
#include "CHTLTemplate.h"
#include "CHTLCustom.h"
#include "CHTLImport.h"
#include <memory>
#include <unordered_map>

namespace chtl {

/**
 * CHTL导入访问器
 * 用于从解析树中提取模板和自定义定义
 */
class CHTLImportVisitor : public CHTLParserBaseVisitor {
public:
    CHTLImportVisitor(std::shared_ptr<CHTLContext> context, 
                      const std::unordered_map<std::string, std::string>& nameMapping = {});
    
    // 访问模板定义
    antlrcpp::Any visitTemplateDefinition(CHTLParser::TemplateDefinitionContext* ctx) override;
    
    // 访问自定义定义
    antlrcpp::Any visitCustomDefinition(CHTLParser::CustomDefinitionContext* ctx) override;
    
    // 获取提取的模板
    const std::unordered_map<std::string, std::shared_ptr<Template>>& getTemplates() const {
        return templates;
    }
    
    // 获取提取的自定义
    const std::unordered_map<std::string, std::shared_ptr<Custom>>& getCustoms() const {
        return customs;
    }
    
private:
    std::shared_ptr<CHTLContext> context;
    std::unordered_map<std::string, std::string> nameMapping;  // 原名 -> 新名
    
    // 提取的定义
    std::unordered_map<std::string, std::shared_ptr<Template>> templates;
    std::unordered_map<std::string, std::shared_ptr<Custom>> customs;
    
    // 辅助方法
    std::string applyNameMapping(const std::string& originalName) const;
};

/**
 * 选择性导入访问器
 * 用于提取特定名称和类型的定义
 */
class CHTLSelectiveImportVisitor : public CHTLParserBaseVisitor {
public:
    CHTLSelectiveImportVisitor(std::shared_ptr<CHTLContext> context,
                               const std::string& targetName,
                               ImportType targetType);
    
    // 访问模板定义
    antlrcpp::Any visitTemplateDefinition(CHTLParser::TemplateDefinitionContext* ctx) override;
    
    // 访问自定义定义
    antlrcpp::Any visitCustomDefinition(CHTLParser::CustomDefinitionContext* ctx) override;
    
    // 检查是否找到目标项目
    bool hasFoundItem() const { return foundItem; }
    
    // 获取找到的模板
    std::shared_ptr<Template> getFoundTemplate() const { return foundTemplate; }
    
    // 获取找到的自定义
    std::shared_ptr<Custom> getFoundCustom() const { return foundCustom; }
    
private:
    std::shared_ptr<CHTLContext> context;
    std::string targetName;
    ImportType targetType;
    
    bool foundItem = false;
    std::shared_ptr<Template> foundTemplate;
    std::shared_ptr<Custom> foundCustom;
    
    // 辅助方法
    bool matchesTarget(const std::string& name, const std::string& type) const;
};

} // namespace chtl