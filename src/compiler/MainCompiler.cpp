#include "MainCompiler.h"
#include <iostream>
#include <algorithm>
#include <sstream>

namespace chtl {

MainCompiler::MainCompiler() {
    // 初始化各个编译器
    scanner_ = std::make_unique<CodeScanner>();
    chtlCompiler_ = std::make_unique<CHTLCompiler>();
    cssCompiler_ = std::make_unique<CSSCompiler>();
    jsCompiler_ = std::make_unique<JavaScriptCompiler>();
    chtljsCompiler_ = std::make_unique<CHTLJSCompiler>();
    
    // 设置默认选项
    options_["optimize"] = "true";
    options_["minify"] = "false";
    options_["sourceMap"] = "false";
    options_["debug"] = "false";
}

bool MainCompiler::compile(const std::string& sourceCode) {
    try {
        // 重置状态
        clear();
        setSuccess(false);
        
        // 扫描并分类代码块
        auto codeBlocks = scanCodeBlocks(sourceCode);
        if (codeBlocks.empty()) {
            setError("没有找到有效的代码块");
            return false;
        }
        
        // 分发代码块到相应的编译器
        dispatchCodeBlocks(codeBlocks);
        
        // 处理编译器间的依赖关系
        resolveDependencies();
        
        // 合并编译结果
        mergeCompilationResults();
        
        // 验证编译结果
        if (!validateCompilationResults()) {
            return false;
        }
        
        // 优化输出
        if (options_["optimize"] == "true") {
            optimizeOutput();
        }
        
        // 生成最终输出
        generateFinalOutput();
        
        // 收集统计信息
        collectStatistics();
        
        setSuccess(true);
        return true;
        
    } catch (const std::exception& e) {
        setError("编译过程中发生异常: " + std::string(e.what()));
        return false;
    }
}

std::vector<CodeBlock> MainCompiler::scanCodeBlocks(const std::string& sourceCode) {
    return scanner_->scanCode(sourceCode);
}

void MainCompiler::dispatchCodeBlocks(const std::vector<CodeBlock>& codeBlocks) {
    for (const auto& block : codeBlocks) {
        bool success = false;
        
        switch (block.type) {
            case CodeBlockType::CHTL:
                success = compileCHTLBlock(block);
                break;
            case CodeBlockType::CSS:
                success = compileCSSBlock(block);
                break;
            case CodeBlockType::JS:
                success = compileJSBlock(block);
                break;
            case CodeBlockType::CHTL_JS:
                success = compileCHTLJSBlock(block);
                break;
            case CodeBlockType::HTML:
                // HTML块直接复制到输出
                htmlOutput_ += block.content + "\n";
                success = true;
                break;
            default:
                addWarning("未知的代码块类型: " + std::to_string(static_cast<int>(block.type)));
                break;
        }
        
        if (!success) {
            handleCompilationError("代码块编译失败", block);
        }
    }
}

bool MainCompiler::compileCHTLBlock(const CodeBlock& block) {
    try {
        if (!chtlCompiler_->compile(block.content)) {
            handleCompilationError("CHTL编译失败: " + chtlCompiler_->getError(), block);
            return false;
        }
        
        // 收集CHTL编译器的输出
        htmlOutput_ += chtlCompiler_->getHTML();
        cssOutput_ += chtlCompiler_->getCSS();
        jsOutput_ += chtlCompiler_->getJavaScript();
        
        return true;
        
    } catch (const std::exception& e) {
        handleCompilationError("CHTL编译异常: " + std::string(e.what()), block);
        return false;
    }
}

bool MainCompiler::compileCSSBlock(const CodeBlock& block) {
    try {
        if (!cssCompiler_->compile(block.content)) {
            handleCompilationError("CSS编译失败: " + cssCompiler_->getError(), block);
            return false;
        }
        
        // 收集CSS编译器的输出
        cssOutput_ += cssCompiler_->getCSS() + "\n";
        
        return true;
        
    } catch (const std::exception& e) {
        handleCompilationError("CSS编译异常: " + std::string(e.what()), block);
        return false;
    }
}

bool MainCompiler::compileJSBlock(const CodeBlock& block) {
    try {
        if (!jsCompiler_->compile(block.content)) {
            handleCompilationError("JavaScript编译失败: " + jsCompiler_->getError(), block);
            return false;
        }
        
        // 收集JavaScript编译器的输出
        jsOutput_ += jsCompiler_->getJavaScript() + "\n";
        
        return true;
        
    } catch (const std::exception& e) {
        handleCompilationError("JavaScript编译异常: " + std::string(e.what()), block);
        return false;
    }
}

bool MainCompiler::compileCHTLJSBlock(const CodeBlock& block) {
    try {
        if (!chtljsCompiler_->compile(block.content)) {
            handleCompilationError("CHTL JS编译失败: " + chtljsCompiler_->getError(), block);
            return false;
        }
        
        // 收集CHTL JS编译器的输出
        jsOutput_ += chtljsCompiler_->getJavaScript() + "\n";
        
        return true;
        
    } catch (const std::exception& e) {
        handleCompilationError("CHTL JS编译异常: " + std::string(e.what()), block);
        return false;
    }
}

void MainCompiler::resolveDependencies() {
    // 处理编译器间的依赖关系
    // 例如：CHTL编译器可能需要CSS和JS编译器的结果
    
    // 这里可以实现更复杂的依赖解析逻辑
    // 目前简化处理
}

void MainCompiler::mergeCompilationResults() {
    // 合并各个编译器的输出
    // 去除重复内容，确保输出的一致性
    
    // 清理空白行
    auto cleanOutput = [](std::string& output) {
        std::istringstream iss(output);
        std::string line;
        std::string cleaned;
        
        while (std::getline(iss, line)) {
            if (!line.empty() && line.find_first_not_of(" \t") != std::string::npos) {
                cleaned += line + "\n";
            }
        }
        output = cleaned;
    };
    
    cleanOutput(htmlOutput_);
    cleanOutput(cssOutput_);
    cleanOutput(jsOutput_);
}

bool MainCompiler::validateCompilationResults() {
    // 验证编译结果的完整性
    
    if (htmlOutput_.empty() && cssOutput_.empty() && jsOutput_.empty()) {
        setError("编译结果为空");
        return false;
    }
    
    // 检查HTML输出的基本结构
    if (!htmlOutput_.empty()) {
        if (htmlOutput_.find("<html") == std::string::npos) {
            addWarning("HTML输出可能不完整");
        }
    }
    
    // 检查CSS输出的基本结构
    if (!cssOutput_.empty()) {
        if (cssOutput_.find("{") == std::string::npos || 
            cssOutput_.find("}") == std::string::npos) {
            addWarning("CSS输出可能不完整");
        }
    }
    
    // 检查JavaScript输出的基本结构
    if (!jsOutput_.empty()) {
        if (jsOutput_.find(";") == std::string::npos) {
            addWarning("JavaScript输出可能不完整");
        }
    }
    
    return true;
}

void MainCompiler::generateFinalOutput() {
    // 生成最终的输出格式
    
    // 如果需要，可以在这里添加输出格式化逻辑
    // 例如：添加版权信息、版本信息等
}

void MainCompiler::optimizeOutput() {
    // 优化输出内容
    
    if (options_["minify"] == "true") {
        // 压缩输出
        // 这里可以实现压缩逻辑
    }
    
    // 其他优化操作
    // 例如：合并CSS规则、优化JavaScript代码等
}

void MainCompiler::collectStatistics() {
    // 收集编译统计信息
    
    updateStat("total_blocks", scanner_->getCodeBlocks().size());
    updateStat("html_lines", std::count(htmlOutput_.begin(), htmlOutput_.end(), '\n'));
    updateStat("css_lines", std::count(cssOutput_.begin(), cssOutput_.end(), '\n'));
    updateStat("js_lines", std::count(jsOutput_.begin(), jsOutput_.end(), '\n'));
}

void MainCompiler::handleCompilationError(const std::string& error, const CodeBlock& block) {
    std::string detailedError = "第" + std::to_string(block.startLine) + 
                               "行: " + error + "\n代码块类型: " + 
                               std::to_string(static_cast<int>(block.type));
    setError(detailedError);
}

void MainCompiler::handleCompilationWarning(const std::string& warning, const CodeBlock& block) {
    std::string detailedWarning = "第" + std::to_string(block.startLine) + 
                                 "行: " + warning + "\n代码块类型: " + 
                                 std::to_string(static_cast<int>(block.type));
    addWarning(detailedWarning);
}

std::map<std::string, int> MainCompiler::getStats() const {
    return stats_;
}

std::vector<std::string> MainCompiler::getWarnings() const {
    // 这里需要实现警告收集逻辑
    return {};
}

std::string MainCompiler::getError() const {
    return error_;
}

void MainCompiler::setOptions(const std::map<std::string, std::string>& options) {
    options_ = options;
}

} // namespace chtl