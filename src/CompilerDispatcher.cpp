#include "CompilerDispatcher.h"
#include "CHTLCompiler.h"
#include "CSSCompiler.h"
#include "JSCompiler.h"
#include "CHTLJSCompiler.h"
#include "CodeGenerator.h"
#include <iostream>

namespace CHTL {

CompilerDispatcher::CompilerDispatcher() {
    scanner_ = std::make_unique<Scanner>();
    symbolTable_ = std::make_unique<SymbolTable>();
    chtlCompiler_ = std::make_unique<CHTLCompiler>(symbolTable_.get());
    cssCompiler_ = std::make_unique<CSSCompiler>();
    jsCompiler_ = std::make_unique<JSCompiler>();
    chtljsCompiler_ = std::make_unique<CHTLJSCompiler>();
}

CompilerDispatcher::~CompilerDispatcher() = default;

CompilationResult CompilerDispatcher::compile(const std::string& chtlContent) {
    CompilationResult result;
    result.success = false;
    
    try {
        // 1. 扫描代码，切割成不同类型的片段
        auto fragments = scanner_->scan(chtlContent);
        
        if (fragments.empty()) {
            addError("没有找到有效的CHTL代码");
            result.errors = errors_;
            return result;
        }
        
        // 2. 处理每个代码片段
        std::vector<std::shared_ptr<ASTNode>> asts;
        
        for (const auto& fragment : fragments) {
            auto ast = processFragment(fragment);
            if (ast) {
                asts.push_back(ast);
            }
        }
        
        // 3. 验证AST
        if (!validate(asts)) {
            result.errors = errors_;
            result.warnings = warnings_;
            return result;
        }
        
        // 4. 优化AST
        optimize(asts);
        
        // 5. 生成代码
        CodeGenerator generator(symbolTable_.get());
        
        // 设置生成器配置
        GeneratorConfig config;
        config.minify = (symbolTable_->getConfiguration("minify") == "true");
        config.prettify = (symbolTable_->getConfiguration("prettify") == "true");
        generator.setConfig(config);
        
        // 生成代码
        for (const auto& ast : asts) {
            generator.generate(ast);
        }
        
        // 6. 收集结果
        result.html = generator.getHTML();
        result.css = generator.getCSS();
        result.javascript = generator.getJavaScript();
        result.errors = errors_;
        result.warnings = warnings_;
        result.success = errors_.empty();
        
    } catch (const std::exception& e) {
        addError(std::string("编译异常: ") + e.what());
        result.errors = errors_;
    }
    
    return result;
}

std::shared_ptr<ASTNode> CompilerDispatcher::compileFile(const std::string& filePath) {
    // TODO: 实现文件编译
    return nullptr;
}

void CompilerDispatcher::setConfiguration(const std::string& key, const std::string& value) {
    symbolTable_->setConfiguration(key, value);
}

std::shared_ptr<ASTNode> CompilerDispatcher::processFragment(const CodeFragment& fragment) {
    std::shared_ptr<ASTNode> ast;
    
    switch (fragment.type) {
        case CodeFragmentType::CHTL:
            ast = chtlCompiler_->compile(fragment.content);
            errors_.insert(errors_.end(), 
                          chtlCompiler_->getErrors().begin(), 
                          chtlCompiler_->getErrors().end());
            warnings_.insert(warnings_.end(),
                            chtlCompiler_->getWarnings().begin(),
                            chtlCompiler_->getWarnings().end());
            chtlCompiler_->clearErrors();
            break;
            
        case CodeFragmentType::CSS:
            ast = cssCompiler_->compile(fragment.content);
            errors_.insert(errors_.end(),
                          cssCompiler_->getErrors().begin(),
                          cssCompiler_->getErrors().end());
            warnings_.insert(warnings_.end(),
                            cssCompiler_->getWarnings().begin(),
                            cssCompiler_->getWarnings().end());
            cssCompiler_->clearErrors();
            break;
            
        case CodeFragmentType::JAVASCRIPT:
            ast = jsCompiler_->compile(fragment.content);
            errors_.insert(errors_.end(),
                          jsCompiler_->getErrors().begin(),
                          jsCompiler_->getErrors().end());
            warnings_.insert(warnings_.end(),
                            jsCompiler_->getWarnings().begin(),
                            jsCompiler_->getWarnings().end());
            jsCompiler_->clearErrors();
            break;
            
        case CodeFragmentType::CHTL_JAVASCRIPT:
            // 首先转换CHTL JS语法
            std::string transformedCode = chtljsCompiler_->transform(fragment.content);
            // 然后使用标准JS编译器编译
            ast = jsCompiler_->compile(transformedCode);
            errors_.insert(errors_.end(),
                          chtljsCompiler_->getErrors().begin(),
                          chtljsCompiler_->getErrors().end());
            warnings_.insert(warnings_.end(),
                            chtljsCompiler_->getWarnings().begin(),
                            chtljsCompiler_->getWarnings().end());
            chtljsCompiler_->clearErrors();
            break;
    }
    
    return ast;
}

void CompilerDispatcher::mergeResults(CompilationResult& result, 
                                     const std::shared_ptr<ASTNode>& ast) {
    // TODO: 实现结果合并逻辑
}

bool CompilerDispatcher::validate(const std::vector<std::shared_ptr<ASTNode>>& asts) {
    // 验证未定义的符号
    auto undefinedSymbols = symbolTable_->getUndefinedSymbols();
    for (const auto& symbol : undefinedSymbols) {
        addError("未定义的符号: " + symbol);
    }
    
    // TODO: 实现更多验证逻辑
    
    return errors_.empty();
}

void CompilerDispatcher::optimize(std::vector<std::shared_ptr<ASTNode>>& asts) {
    // TODO: 实现AST优化逻辑
    // - 合并相同的CSS规则
    // - 优化JavaScript代码
    // - 删除未使用的模板和自定义
}

void CompilerDispatcher::addError(const std::string& error) {
    errors_.push_back(error);
}

void CompilerDispatcher::addWarning(const std::string& warning) {
    warnings_.push_back(warning);
}

} // namespace CHTL