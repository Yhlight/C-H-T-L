#include "CHTLCompiler.h"
#include "scanner/CHTLUnifiedScanner.h"
#include "parser/standalone/CHTLParser.h"
#include "parser/standalone/CHTLJSParser.h"
#include "config/ConfigurationSystem.h"
#include "CHTLCSSCompiler.h"
#include "CHTLJSCompiler.h"
#include <fstream>
#include <sstream>

CompilationResult CHTLCompiler::compile(const std::string& sourceCode) {
    CompilationResult result;
    
    try {
        // 初始化扫描器集成器
        scanner::ScannerIntegrator integrator;
        
        // 处理源代码
        integrator.processFile("input.chtl", sourceCode);
        
        // 检查错误
        if (integrator.hasErrors()) {
            auto errors = integrator.getAllErrors();
            for (const auto& error : errors) {
                result.errors.push_back(CompilationError{
                    0, 0, error, ErrorType::SYNTAX_ERROR
                });
            }
            result.success = false;
            return result;
        }
        
        // 获取生成的代码
        result.generatedHTML = integrator.getGeneratedHTML();
        result.generatedCSS = integrator.getGeneratedCSS();
        result.generatedJS = integrator.getGeneratedJS();
        result.success = true;
        
    } catch (const std::exception& e) {
        result.errors.push_back(CompilationError{
            0, 0, 
            std::string("Compilation failed: ") + e.what(),
            ErrorType::INTERNAL_ERROR
        });
        result.success = false;
    }
    
    return result;
}

CompilationResult CHTLCompiler::compileWithConfig(const std::string& sourceCode, 
                                                  const std::string& configFile) {
    // 加载配置
    config::ConfigurationSystem::getInstance().loadFromFile(configFile);
    
    // 使用配置编译
    return compile(sourceCode);
}