#include "v2/Css/CssParser.h"
#include "v2/Css/NativeCssAnalyzer.h"
#include <iostream>
#include <string>

using namespace chtl::v2::css;

void testCssParser() {
    std::string css = R"(
/* 测试 CSS 解析器 */
@import url("base.css");

:root {
    --primary-color: #333;
    --font-size: 16px;
}

/* 基础样式 */
body {
    margin: 0;
    padding: 0;
    font-family: Arial, sans-serif;
    color: var(--primary-color);
}

/* 复杂选择器 */
.container > .header + .content {
    background-color: #f0f0f0;
    padding: 20px 15px;
}

/* 属性选择器 */
input[type="text"]:focus,
input[type="email"]:focus {
    border-color: #007bff;
    box-shadow: 0 0 5px rgba(0, 123, 255, 0.25);
}

/* 伪类和伪元素 */
a:hover::after {
    content: " →";
    color: #666;
}

/* 媒体查询 */
@media screen and (max-width: 768px) {
    .container {
        width: 100%;
        padding: 10px;
    }
    
    .header {
        font-size: 1.2em;
    }
}

/* 动画 */
@keyframes fadeIn {
    from {
        opacity: 0;
        transform: translateY(-10px);
    }
    to {
        opacity: 1;
        transform: translateY(0);
    }
}

.fade-in {
    animation: fadeIn 0.3s ease-in-out;
}

/* ID 选择器 */
#main-content {
    min-height: 500px;
}

/* !important */
.override {
    color: red !important;
}
)";

    std::cout << "=== 测试 CSS 解析器 ===" << std::endl;
    
    try {
        // 解析 CSS
        CssParser parser(css);
        auto result = parser.parse();
        
        if (!result.errors.empty()) {
            std::cout << "\n错误:" << std::endl;
            for (const auto& error : result.errors) {
                std::cout << "  - " << error << std::endl;
            }
        }
        
        if (!result.warnings.empty()) {
            std::cout << "\n警告:" << std::endl;
            for (const auto& warning : result.warnings) {
                std::cout << "  - " << warning << std::endl;
            }
        }
        
        if (result.stylesheet) {
            std::cout << "\n解析成功！" << std::endl;
            std::cout << "规则数量: " << result.stylesheet->rules.size() << std::endl;
            
            // 输出部分规则信息
            int ruleCount = 0;
            for (const auto& rule : result.stylesheet->rules) {
                ruleCount++;
                if (rule->type == RuleType::STYLE_RULE) {
                    std::cout << "\n规则 " << ruleCount << " (样式规则):" << std::endl;
                    std::cout << "  选择器: ";
                    bool first = true;
                    for (const auto& selector : rule->selectors) {
                        if (!first) std::cout << ", ";
                        std::cout << selector->toString();
                        first = false;
                    }
                    std::cout << std::endl;
                    std::cout << "  声明数: " << rule->declarations.size() << std::endl;
                } else {
                    std::cout << "\n规则 " << ruleCount << " (@规则):" << std::endl;
                    std::cout << "  类型: @" << rule->atKeyword << std::endl;
                    if (!rule->prelude.empty()) {
                        std::cout << "  条件: " << rule->prelude << std::endl;
                    }
                    if (rule->type == RuleType::MEDIA_RULE) {
                        std::cout << "  嵌套规则数: " << rule->nestedRules.size() << std::endl;
                    }
                }
            }
            
            // 使用分析器
            std::cout << "\n=== 使用 CSS 分析器 ===" << std::endl;
            NativeCssAnalyzer analyzer;
            auto analysisResult = analyzer.analyze(css);
            
            std::cout << "分析结果:" << std::endl;
            std::cout << "  有效: " << (analysisResult.valid ? "是" : "否") << std::endl;
            std::cout << "  规则数: " << analysisResult.ruleCount << std::endl;
            std::cout << "  选择器数: " << analysisResult.selectors.size() << std::endl;
            
            std::cout << "\n属性使用统计:" << std::endl;
            for (const auto& [prop, count] : analysisResult.properties) {
                std::cout << "  " << prop << ": " << count << " 次" << std::endl;
            }
            
            std::cout << "\n特性:" << std::endl;
            std::cout << "  媒体查询: " << (analysisResult.features.hasMediaQueries ? "是" : "否") << std::endl;
            std::cout << "  动画: " << (analysisResult.features.hasAnimations ? "是" : "否") << std::endl;
            std::cout << "  @supports: " << (analysisResult.features.hasSupports ? "是" : "否") << std::endl;
            std::cout << "  @import: " << (analysisResult.features.hasImports ? "是" : "否") << std::endl;
            
            if (!analysisResult.warnings.empty()) {
                std::cout << "\n分析警告:" << std::endl;
                for (const auto& warning : analysisResult.warnings) {
                    std::cout << "  - " << warning << std::endl;
                }
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "解析失败: " << e.what() << std::endl;
    }
}

int main() {
    testCssParser();
    return 0;
}