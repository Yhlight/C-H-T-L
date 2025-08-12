#include "CJmod/CJmodCore.h"
#include <regex>
#include <sstream>

namespace chtl {
namespace cjmod {

// ==================== SyntaxRule 实现 ====================

SyntaxRule::~SyntaxRule() = default;

// ==================== RuntimeBuilder 实现 ====================

std::string RuntimeBuilder::generate() const {
    std::stringstream ss;
    
    // 生成全局变量
    if (!globals_.empty()) {
        ss << "  // Global variables\n";
        for (const auto& [name, value] : globals_) {
            ss << "  window." << name << " = " << value << ";\n";
        }
        ss << "\n";
    }
    
    // 生成函数
    if (!functions_.empty()) {
        ss << "  // Functions\n";
        for (const auto& [name, code] : functions_) {
            ss << "  window." << name << " = " << code << ";\n";
        }
        ss << "\n";
    }
    
    // 生成类
    if (!classes_.empty()) {
        ss << "  // Classes\n";
        for (const auto& [name, code] : classes_) {
            ss << "  " << code << "\n";
            ss << "  window." << name << " = " << name << ";\n";
        }
        ss << "\n";
    }
    
    // 生成原型扩展
    if (!prototypes_.empty()) {
        ss << "  // Prototype extensions\n";
        for (const auto& [proto, extensions] : prototypes_) {
            for (const auto& [method, code] : extensions) {
                ss << "  " << proto << ".prototype." << method << " = " << code << ";\n";
            }
        }
        ss << "\n";
    }
    
    // 生成初始化代码
    if (!initCode_.empty()) {
        ss << "  // Initialization\n";
        for (const auto& code : initCode_) {
            ss << "  " << code << "\n";
        }
        ss << "\n";
    }
    
    return ss.str();
}

// ==================== SyntaxBuilder 实现 ====================

std::shared_ptr<SyntaxRule> SyntaxBuilder::build() {
    // 创建一个自定义的 SyntaxRule 实现
    class CustomSyntaxRule : public SyntaxRule {
    public:
        std::string name;
        int priority;
        std::string pattern;
        SyntaxBuilder::ScanFunc scanFunc;
        SyntaxBuilder::GenerateFunc generateFunc;
        
        std::vector<ScanResult> scan(ScanContext* ctx) override {
            if (scanFunc) {
                return scanFunc(ctx);
            }
            
            // 默认的正则匹配实现
            if (!pattern.empty()) {
                std::vector<ScanResult> results;
                std::regex re(pattern);
                std::string code = ctx->getCode();
                size_t pos = ctx->getPosition();
                
                auto begin = std::sregex_iterator(code.begin() + pos, code.end(), re);
                auto end = std::sregex_iterator();
                
                for (auto it = begin; it != end; ++it) {
                    ScanResult result;
                    result.start = it->position();
                    result.end = result.start + it->length();
                    result.content = it->str();
                    
                    // 捕获组
                    for (size_t i = 1; i < it->size(); ++i) {
                        result.captures[std::to_string(i)] = (*it)[i].str();
                    }
                    
                    results.push_back(result);
                }
                
                return results;
            }
            
            return {};
        }
        
        std::string generate(const ScanResult& result, GenerateContext* ctx) override {
            if (generateFunc) {
                return generateFunc(result, ctx);
            }
            return result.content;
        }
    };
    
    auto rule = std::make_shared<CustomSyntaxRule>();
    rule->name = name_;
    rule->priority = priority_;
    rule->pattern = pattern_;
    rule->scanFunc = scanFunc_;
    rule->generateFunc = generateFunc_;
    
    return rule;
}

} // namespace cjmod
} // namespace chtl