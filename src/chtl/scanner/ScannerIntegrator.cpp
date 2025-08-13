#include "CHTLUnifiedScanner.h"
#include "../parser/standalone/CHTLParser.h"
#include "../parser/standalone/CHTLJSParser.h"
#include "../CHTLCSSCompiler.h"
#include "../CHTLJSCompiler.h"
#include "../CHTLGenerator.h"
#include <sstream>

namespace chtl {
namespace scanner {

ScannerIntegrator::ScannerIntegrator() 
    : scanner_(std::make_unique<CHTLUnifiedScanner>()) {
    
    // 设置片段处理器
    scanner_->setFragmentHandler(FragmentType::CHTL, 
        [this](const CodeFragment& f) { handleCHTLFragment(f); });
    scanner_->setFragmentHandler(FragmentType::CHTL_JS, 
        [this](const CodeFragment& f) { handleCHTLJSFragment(f); });
    scanner_->setFragmentHandler(FragmentType::CSS, 
        [this](const CodeFragment& f) { handleCSSFragment(f); });
    scanner_->setFragmentHandler(FragmentType::JS, 
        [this](const CodeFragment& f) { handleJSFragment(f); });
    scanner_->setFragmentHandler(FragmentType::TEXT, 
        [this](const CodeFragment& f) { handleTextFragment(f); });
    scanner_->setFragmentHandler(FragmentType::COMMENT, 
        [this](const CodeFragment& f) { handleCommentFragment(f); });
}

ScannerIntegrator::~ScannerIntegrator() = default;

void ScannerIntegrator::processFile(const std::string& filename, const std::string& content) {
    // 清空之前的结果
    generatedHTML_.clear();
    generatedCSS_.clear();
    generatedJS_.clear();
    errors_.clear();
    
    // 扫描文件
    auto fragments = scanner_->scan(content);
    
    // 处理扫描器错误
    if (scanner_->hasErrors()) {
        errors_.insert(errors_.end(), 
                      scanner_->getErrors().begin(), 
                      scanner_->getErrors().end());
    }
    
    // 处理每个片段
    for (const auto& fragment : fragments) {
        if (handlers_.count(fragment.type)) {
            handlers_[fragment.type](fragment);
        }
    }
}

bool ScannerIntegrator::hasErrors() const {
    return !errors_.empty();
}

std::vector<std::string> ScannerIntegrator::getAllErrors() const {
    return errors_;
}

void ScannerIntegrator::handleCHTLFragment(const CodeFragment& fragment) {
    try {
        // 使用独立的CHTL解析器
        parser::CHTLLexer lexer(fragment.content);
        auto tokens = lexer.tokenize();
        auto tokenStream = std::make_shared<parser::TokenStream>(tokens);
        
        parser::CHTLParser parser(tokenStream);
        auto ast = parser.parse();
        
        // 生成HTML
        CHTLGenerator generator;
        generator.visit(ast);
        
        generatedHTML_ += generator.getGeneratedHTML();
        generatedCSS_ += generator.getGeneratedCSS();
        generatedJS_ += generator.getGeneratedJS();
        
    } catch (const std::exception& e) {
        std::ostringstream oss;
        oss << "CHTL parsing error at line " << fragment.startLine 
            << ": " << e.what();
        errors_.push_back(oss.str());
    }
}

void ScannerIntegrator::handleCHTLJSFragment(const CodeFragment& fragment) {
    try {
        // 使用独立的CHTL JS解析器
        parser::CHTLJSLexer lexer(fragment.content);
        auto tokens = lexer.tokenize();
        auto tokenStream = std::make_shared<parser::TokenStream>(tokens);
        
        parser::CHTLJSParser parser(tokenStream);
        auto ast = parser.parse();
        
        // 生成增强的JavaScript
        CHTLGenerator generator;
        generator.setGeneratingScript(true);
        generator.visit(ast);
        
        generatedJS_ += generator.getGeneratedJS();
        
    } catch (const std::exception& e) {
        std::ostringstream oss;
        oss << "CHTL JS parsing error at line " << fragment.startLine 
            << ": " << e.what();
        errors_.push_back(oss.str());
    }
}

void ScannerIntegrator::handleCSSFragment(const CodeFragment& fragment) {
    try {
        // 使用ANTLR4的CSS编译器
        CHTLCSSCompiler cssCompiler;
        auto result = cssCompiler.compile(fragment.content);
        
        if (!result.errors.empty()) {
            for (const auto& error : result.errors) {
                std::ostringstream oss;
                oss << "CSS error at line " << (fragment.startLine + error.line - 1)
                    << ": " << error.message;
                errors_.push_back(oss.str());
            }
        } else {
            generatedCSS_ += result.css;
        }
        
    } catch (const std::exception& e) {
        std::ostringstream oss;
        oss << "CSS compilation error at line " << fragment.startLine 
            << ": " << e.what();
        errors_.push_back(oss.str());
    }
}

void ScannerIntegrator::handleJSFragment(const CodeFragment& fragment) {
    try {
        // 使用ANTLR4的JS编译器
        CHTLJSCompiler jsCompiler;
        auto result = jsCompiler.compile(fragment.content);
        
        if (!result.errors.empty()) {
            for (const auto& error : result.errors) {
                std::ostringstream oss;
                oss << "JS error at line " << (fragment.startLine + error.line - 1)
                    << ": " << error.message;
                errors_.push_back(oss.str());
            }
        } else {
            generatedJS_ += result.code;
        }
        
    } catch (const std::exception& e) {
        std::ostringstream oss;
        oss << "JavaScript compilation error at line " << fragment.startLine 
            << ": " << e.what();
        errors_.push_back(oss.str());
    }
}

void ScannerIntegrator::handleTextFragment(const CodeFragment& fragment) {
    // 文本片段直接添加到HTML
    generatedHTML_ += fragment.content;
}

void ScannerIntegrator::handleCommentFragment(const CodeFragment& fragment) {
    // 注释可以选择性地保留或忽略
    // 这里我们选择保留HTML注释
    if (fragment.content.substr(0, 4) == "<!--") {
        generatedHTML_ += fragment.content;
    }
}

} // namespace scanner
} // namespace chtl