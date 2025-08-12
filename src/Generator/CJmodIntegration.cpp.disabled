#include "Generator/WebGenerator.h"
#include "CJmod/CJmodProcessor.h"
#include "Scanner/ChtlScanner.h"
#include <sstream>

namespace chtl {

// 扩展 WebGenerator 以支持 CJmod
class CJmodIntegration {
public:
    // 处理带有 CJmod 的 JavaScript
    static std::string processJavaScriptWithCJmod(
        const std::string& jsCode,
        const std::vector<std::string>& activeCJmods) {
        
        if (activeCJmods.empty()) {
            // 没有 CJmod，使用标准 CHTL JS 处理
            return processStandardChtlJs(jsCode);
        }
        
        // 使用扫描器进行精准切割
        ChtlScanner scanner;
        auto segments = scanner.scanJs(jsCode);
        
        std::stringstream result;
        
        for (const auto& segment : segments) {
            if (segment.type == SegmentType::CHTL_JS) {
                // CHTL JS 片段，应用 CJmod 转换
                std::string processed = cjmod::CJmodProcessor::getInstance()
                    .processScript(segment.content, activeCJmods);
                result << processed;
            } else {
                // 普通 JS，保持原样
                result << segment.content;
            }
        }
        
        return result.str();
    }
    
    // 生成 CJmod 运行时
    static std::string generateCJmodRuntime(
        const std::vector<std::string>& activeCJmods) {
        
        if (activeCJmods.empty()) {
            return "";
        }
        
        return cjmod::CJmodProcessor::getInstance()
            .getRuntimeCode(activeCJmods);
    }
    
    // 处理 Import 声明
    static bool handleCJmodImport(
        const std::string& moduleName,
        const std::string& source) {
        
        return cjmod::integration::processImport(moduleName, source);
    }
    
private:
    // 标准 CHTL JS 处理（无 CJmod）
    static std::string processStandardChtlJs(const std::string& jsCode) {
        std::string result = jsCode;
        
        // {{&}} -> this
        size_t pos = 0;
        while ((pos = result.find("{{&}}", pos)) != std::string::npos) {
            result.replace(pos, 5, "this");
            pos += 4;
        }
        
        // {{#id}} -> document.getElementById('id')
        std::regex idRegex(R"(\{\{#([\w-]+)\}\})");
        result = std::regex_replace(result, idRegex, 
                                  "document.getElementById('$1')");
        
        // {{.class}} -> document.getElementsByClassName('class')
        std::regex classRegex(R"(\{\{\.(\w+)\}\})");
        result = std::regex_replace(result, classRegex, 
                                  "document.getElementsByClassName('$1')");
        
        // obj->method() -> obj.method()
        std::regex methodRegex(R"((\w+|this)->(\w+))");
        result = std::regex_replace(result, methodRegex, "$1.$2");
        
        return result;
    }
};

// WebGenerator 的 CJmod 扩展点
void WebGenerator::visitScriptWithCJmod(const std::shared_ptr<Script>& script) {
    // 获取当前活动的 CJmod 列表
    std::vector<std::string> activeCJmods;
    
    // 从上下文中获取已导入的 CJmod
    if (auto* enhancedCtx = dynamic_cast<EnhancedContext*>(context_)) {
        // TODO: 从上下文获取导入的模块列表
        // activeCJmods = enhancedCtx->getImportedCJmods();
    }
    
    // 处理脚本内容
    std::string processedJs = CJmodIntegration::processJavaScriptWithCJmod(
        script->getContent(), 
        activeCJmods
    );
    
    // 添加到 JS 收集器
    jsCollector_.appendLine(processedJs);
}

// 生成最终 JavaScript 文件时注入运行时
std::string WebGenerator::generateJavaScriptWithRuntime() {
    std::stringstream js;
    
    // 获取活动的 CJmod
    std::vector<std::string> activeCJmods;
    if (auto* enhancedCtx = dynamic_cast<EnhancedContext*>(context_)) {
        // TODO: 从上下文获取
    }
    
    // 生成 CJmod 运行时
    std::string runtime = CJmodIntegration::generateCJmodRuntime(activeCJmods);
    if (!runtime.empty()) {
        js << runtime << "\n\n";
    }
    
    // 添加标准 CHTL 运行时
    js << "// CHTL Standard Runtime\n";
    js << generateStandardRuntime() << "\n\n";
    
    // 添加用户代码
    js << "// User Code\n";
    js << jsCollector_.toString();
    
    return js.str();
}

// 处理 [Import] @CJmod 声明
void WebGenerator::visitCJmodImport(const std::shared_ptr<Import>& import) {
    if (import->getType() != ImportType::CJMOD) {
        return;
    }
    
    std::string moduleName = import->getModuleName();
    std::string source = import->getSource();
    
    // 处理导入
    if (CJmodIntegration::handleCJmodImport(moduleName, source)) {
        // 记录到上下文
        if (auto* enhancedCtx = dynamic_cast<EnhancedContext*>(context_)) {
            // TODO: 记录已导入的模块
            // enhancedCtx->addImportedCJmod(moduleName);
        }
    } else {
        // 导入失败
        context_->addError("Failed to import CJmod: " + moduleName);
    }
}

} // namespace chtl