#include "CHTLCSSCompiler.h"
#include <antlr4-runtime.h>
#include <algorithm>
#include <regex>
#include <set>

#include "CHTLCSSPreprocessor.h"

namespace chtl {

// CSSRule 实现
std::string CSSRule::toString() const {
    std::stringstream ss;
    
    // 输出选择器
    for (size_t i = 0; i < selectors.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << selectors[i];
    }
    
    ss << " {\n";
    
    // 输出声明
    for (const auto& [prop, value] : declarations) {
        ss << "    " << prop << ": " << value << ";\n";
    }
    
    ss << "}\n";
    
    return ss.str();
}

// CSSAtRule 实现
std::string CSSAtRule::toString() const {
    std::stringstream ss;
    
    ss << type << " " << condition << " {\n";
    
    for (const auto& rule : rules) {
        std::string ruleStr = rule.toString();
        // 缩进嵌套规则
        std::istringstream iss(ruleStr);
        std::string line;
        while (std::getline(iss, line)) {
            ss << "    " << line << "\n";
        }
    }
    
    ss << "}\n";
    
    return ss.str();
}

// CSSCompilerListener 实现
CSSCompilerListener::CSSCompilerListener(bool minifyOutput, bool keepComments)
    : minify(minifyOutput), preserveComments(keepComments) {}

void CSSCompilerListener::enterStylesheet(CSSParser::StylesheetContext* ctx) {
    // 开始处理样式表
}

void CSSCompilerListener::exitStylesheet(CSSParser::StylesheetContext* ctx) {
    // 输出所有规则
    for (const auto& rule : rules) {
        writeRule(rule);
    }
    
    for (const auto& atRule : atRules) {
        writeAtRule(atRule);
    }
}

void CSSCompilerListener::enterRuleset(CSSParser::RulesetContext* ctx) {
    currentRule = CSSRule();
}

void CSSCompilerListener::exitRuleset(CSSParser::RulesetContext* ctx) {
    if (!inAtRule) {
        rules.push_back(currentRule);
    } else {
        currentAtRule.rules.push_back(currentRule);
    }
}

void CSSCompilerListener::enterSelectorList(CSSParser::SelectorListContext* ctx) {
    // 提取所有选择器
    for (auto* selectorCtx : ctx->selector()) {
        std::string selector = extractText(selectorCtx);
        currentRule.selectors.push_back(formatSelector(selector));
    }
}

void CSSCompilerListener::enterSelector(CSSParser::SelectorContext* ctx) {
    // 单个选择器处理
}

void CSSCompilerListener::enterDeclaration(CSSParser::DeclarationContext* ctx) {
    currentProperty.clear();
    currentValue.clear();
}

void CSSCompilerListener::exitDeclaration(CSSParser::DeclarationContext* ctx) {
    if (!currentProperty.empty() && !currentValue.empty()) {
        currentRule.declarations[currentProperty] = currentValue;
    }
}

void CSSCompilerListener::enterProperty(CSSParser::PropertyContext* ctx) {
    currentProperty = extractText(ctx);
}

void CSSCompilerListener::enterValue(CSSParser::ValueContext* ctx) {
    currentValue = extractText(ctx);
}

void CSSCompilerListener::enterAtMedia(CSSParser::AtMediaContext* ctx) {
    inAtRule = true;
    currentAtRule = CSSAtRule();
    currentAtRule.type = "@media";
    
    if (ctx->mediaQueryList()) {
        currentAtRule.condition = extractText(ctx->mediaQueryList());
    }
}

void CSSCompilerListener::exitAtMedia(CSSParser::AtMediaContext* ctx) {
    inAtRule = false;
    atRules.push_back(currentAtRule);
}

void CSSCompilerListener::enterAtKeyframes(CSSParser::AtKeyframesContext* ctx) {
    inAtRule = true;
    currentAtRule = CSSAtRule();
    currentAtRule.type = "@keyframes";
    
    if (ctx->IDENTIFIER()) {
        currentAtRule.condition = ctx->IDENTIFIER()->getText();
    }
}

void CSSCompilerListener::exitAtKeyframes(CSSParser::AtKeyframesContext* ctx) {
    inAtRule = false;
    atRules.push_back(currentAtRule);
}

void CSSCompilerListener::enterAtImport(CSSParser::AtImportContext* ctx) {
    CSSAtRule importRule;
    importRule.type = "@import";
    importRule.rawContent = extractText(ctx);
    atRules.push_back(importRule);
}

void CSSCompilerListener::enterComment(CSSParser::CommentContext* ctx) {
    if (preserveComments) {
        output << ctx->getText();
        if (!minify) output << "\n";
    }
}

std::string CSSCompilerListener::extractText(antlr4::ParserRuleContext* ctx) {
    if (!ctx) return "";
    
    antlr4::misc::Interval interval(ctx->getStart()->getStartIndex(), 
                                   ctx->getStop()->getStopIndex());
    return ctx->getStart()->getInputStream()->getText(interval);
}

std::string CSSCompilerListener::formatSelector(const std::string& selector) {
    std::string formatted = selector;
    
    // 移除多余的空格
    formatted = std::regex_replace(formatted, std::regex("\\s+"), " ");
    formatted = std::regex_replace(formatted, std::regex("^\\s+|\\s+$"), "");
    
    // 格式化组合器周围的空格
    formatted = std::regex_replace(formatted, std::regex("\\s*>\\s*"), " > ");
    formatted = std::regex_replace(formatted, std::regex("\\s*\\+\\s*"), " + ");
    formatted = std::regex_replace(formatted, std::regex("\\s*~\\s*"), " ~ ");
    
    return formatted;
}

std::string CSSCompilerListener::formatDeclaration(const std::string& property, 
                                                  const std::string& value) {
    if (minify) {
        return property + ":" + value;
    } else {
        return property + ": " + value;
    }
}

void CSSCompilerListener::writeRule(const CSSRule& rule) {
    if (rule.selectors.empty() || rule.declarations.empty()) {
        return;
    }
    
    // 输出选择器
    for (size_t i = 0; i < rule.selectors.size(); ++i) {
        if (i > 0) output << (minify ? "," : ", ");
        output << rule.selectors[i];
    }
    
    output << (minify ? "{" : " {\n");
    
    // 输出声明
    size_t count = 0;
    for (const auto& [prop, value] : rule.declarations) {
        if (!minify) output << getIndent();
        output << formatDeclaration(prop, value);
        
        if (minify) {
            output << ";";
        } else {
            output << ";\n";
        }
        count++;
    }
    
    output << (minify ? "}" : "}\n");
    if (!minify) output << "\n";
}

void CSSCompilerListener::writeAtRule(const CSSAtRule& atRule) {
    output << atRule.type;
    
    if (!atRule.condition.empty()) {
        output << " " << atRule.condition;
    }
    
    if (!atRule.rawContent.empty()) {
        output << atRule.rawContent;
        if (!minify) output << "\n";
        return;
    }
    
    output << (minify ? "{" : " {\n");
    
    for (const auto& rule : atRule.rules) {
        if (!minify) {
            // 缩进嵌套规则
            std::string ruleStr = rule.toString();
            std::istringstream iss(ruleStr);
            std::string line;
            while (std::getline(iss, line)) {
                if (!line.empty()) {
                    output << "    " << line << "\n";
                }
            }
        } else {
            // 压缩模式
            for (size_t i = 0; i < rule.selectors.size(); ++i) {
                if (i > 0) output << ",";
                output << rule.selectors[i];
            }
            output << "{";
            for (const auto& [prop, value] : rule.declarations) {
                output << prop << ":" << value << ";";
            }
            output << "}";
        }
    }
    
    output << (minify ? "}" : "}\n");
    if (!minify) output << "\n";
}

std::string CSSCompilerListener::getIndent() const {
    return "    ";
}

// CSSCompiler 实现
CSSCompiler::CSSCompiler(std::shared_ptr<CHTLContext> ctx) 
    : context(ctx), minify(false), preserveComments(false) {}

std::string CSSCompiler::compile(const std::string& css) {
    antlr4::ANTLRInputStream input(css);
    CSSLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CSSParser parser(&tokens);
    
    // 错误处理
    std::vector<std::string> errors;
    CSSErrorListener errorListener(errors);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    
    // 解析
    CSSParser::StylesheetContext* tree = parser.stylesheet();
    
    if (!errors.empty()) {
        for (const auto& error : errors) {
            context->reportError(error);
        }
        return "";
    }
    
    // 编译
    CSSCompilerListener listener(minify, preserveComments);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    
    return listener.getCompiledCSS();
}

std::pair<std::string, std::vector<CSSRule>> CSSCompiler::compileWithAnalysis(const std::string& css) {
    antlr4::ANTLRInputStream input(css);
    CSSLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CSSParser parser(&tokens);
    
    // 错误处理
    std::vector<std::string> errors;
    CSSErrorListener errorListener(errors);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    
    // 解析
    CSSParser::StylesheetContext* tree = parser.stylesheet();
    
    if (!errors.empty()) {
        for (const auto& error : errors) {
            context->reportError(error);
        }
        return {"", {}};
    }
    
    // 编译
    CSSCompilerListener listener(minify, preserveComments);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    
    return {listener.getCompiledCSS(), listener.getRules()};
}

bool CSSCompiler::validate(const std::string& css, std::vector<std::string>& errors) {
    antlr4::ANTLRInputStream input(css);
    CSSLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CSSParser parser(&tokens);
    
    // 错误处理
    CSSErrorListener errorListener(errors);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    
    // 解析
    parser.stylesheet();
    
    return errors.empty();
}

std::string CSSCompiler::processGlobalStyleBlock(const std::string& cssContent) {
    // 处理CHTL的全局样式块
    // 这里可以添加CHTL特定的预处理
    return compile(cssContent);
}

std::string CSSCompiler::mergeCSSBlocks(const std::vector<std::string>& blocks) {
    std::stringstream merged;
    
    for (const auto& block : blocks) {
        merged << block;
        if (!minify && !block.empty() && block.back() != '\n') {
            merged << "\n";
        }
    }
    
    return merged.str();
}

void CSSCompiler::CSSErrorListener::syntaxError(antlr4::Recognizer* recognizer,
                                               antlr4::Token* offendingSymbol,
                                               size_t line,
                                               size_t charPositionInLine,
                                               const std::string& msg,
                                               std::exception_ptr e) {
    std::stringstream error;
    error << "CSS Syntax Error at line " << line << ":" << charPositionInLine << " - " << msg;
    errors.push_back(error.str());
}

// CSSOptimizer 实现
std::vector<CSSRule> CSSOptimizer::optimize(const std::vector<CSSRule>& rules) {
    std::vector<CSSRule> optimized;
    
    for (const auto& rule : rules) {
        CSSRule opt = optimizeRule(rule);
        if (!opt.declarations.empty()) {
            optimized.push_back(opt);
        }
    }
    
    if (options.mergeRules) {
        optimized = mergeRules(optimized);
    }
    
    return optimized;
}

CSSRule CSSOptimizer::optimizeRule(const CSSRule& rule) {
    CSSRule optimized = rule;
    
    if (options.shorthandProperties) {
        optimized.declarations = toShorthand(optimized.declarations);
    }
    
    // 优化每个声明的值
    for (auto& [prop, value] : optimized.declarations) {
        if (options.optimizeColors) {
            value = optimizeColor(value);
        }
        if (options.optimizeUnits) {
            value = optimizeUnit(value);
        }
    }
    
    return optimized;
}

std::vector<CSSRule> CSSOptimizer::mergeRules(const std::vector<CSSRule>& rules) {
    std::unordered_map<std::string, CSSRule> merged;
    
    for (const auto& rule : rules) {
        for (const auto& selector : rule.selectors) {
            if (merged.find(selector) == merged.end()) {
                CSSRule newRule;
                newRule.selectors.push_back(selector);
                merged[selector] = newRule;
            }
            
            // 合并声明
            for (const auto& [prop, value] : rule.declarations) {
                merged[selector].declarations[prop] = value;
            }
        }
    }
    
    std::vector<CSSRule> result;
    for (const auto& [selector, rule] : merged) {
        result.push_back(rule);
    }
    
    return result;
}

std::string CSSOptimizer::optimizeColor(const std::string& color) {
    // 简单的颜色优化
    std::string opt = color;
    
    // #RRGGBB -> #RGB 如果可能
    std::regex hexColor("#([0-9a-fA-F]{6})");
    std::smatch match;
    if (std::regex_match(color, match, hexColor)) {
        std::string hex = match[1];
        if (hex[0] == hex[1] && hex[2] == hex[3] && hex[4] == hex[5]) {
            opt = "#" + std::string(1, hex[0]) + std::string(1, hex[2]) + std::string(1, hex[4]);
        }
    }
    
    // 常见颜色名称优化
    static const std::unordered_map<std::string, std::string> colorMap = {
        {"#f00", "red"},
        {"#0f0", "lime"},
        {"#00f", "blue"},
        {"#fff", "white"},
        {"#000", "black"}
    };
    
    auto it = colorMap.find(opt);
    if (it != colorMap.end() && it->second.length() < opt.length()) {
        opt = it->second;
    }
    
    return opt;
}

std::string CSSOptimizer::optimizeUnit(const std::string& value) {
    // 移除0值的单位
    std::regex zeroUnit("(^|\\s)0(px|em|rem|%|vh|vw|vmin|vmax)");
    return std::regex_replace(value, zeroUnit, "$10");
}

std::unordered_map<std::string, std::string> CSSOptimizer::toShorthand(
    const std::unordered_map<std::string, std::string>& declarations) {
    
    std::unordered_map<std::string, std::string> result = declarations;
    
    // margin简写
    auto hasMargin = [&](const std::string& side) {
        return result.find("margin-" + side) != result.end();
    };
    
    if (hasMargin("top") && hasMargin("right") && hasMargin("bottom") && hasMargin("left")) {
        std::string margin = result["margin-top"] + " " + result["margin-right"] + " " + 
                           result["margin-bottom"] + " " + result["margin-left"];
        
        // 优化margin值
        std::vector<std::string> values = {
            result["margin-top"], result["margin-right"], 
            result["margin-bottom"], result["margin-left"]
        };
        
        if (values[0] == values[2] && values[1] == values[3]) {
            if (values[0] == values[1]) {
                margin = values[0];
            } else {
                margin = values[0] + " " + values[1];
            }
        } else if (values[1] == values[3]) {
            margin = values[0] + " " + values[1] + " " + values[2];
        }
        
        result["margin"] = margin;
        result.erase("margin-top");
        result.erase("margin-right");
        result.erase("margin-bottom");
        result.erase("margin-left");
    }
    
    // padding简写（类似margin）
    auto hasPadding = [&](const std::string& side) {
        return result.find("padding-" + side) != result.end();
    };
    
    if (hasPadding("top") && hasPadding("right") && hasPadding("bottom") && hasPadding("left")) {
        std::string padding = result["padding-top"] + " " + result["padding-right"] + " " + 
                            result["padding-bottom"] + " " + result["padding-left"];
        
        std::vector<std::string> values = {
            result["padding-top"], result["padding-right"], 
            result["padding-bottom"], result["padding-left"]
        };
        
        if (values[0] == values[2] && values[1] == values[3]) {
            if (values[0] == values[1]) {
                padding = values[0];
            } else {
                padding = values[0] + " " + values[1];
            }
        } else if (values[1] == values[3]) {
            padding = values[0] + " " + values[1] + " " + values[2];
        }
        
        result["padding"] = padding;
        result.erase("padding-top");
        result.erase("padding-right");
        result.erase("padding-bottom");
        result.erase("padding-left");
    }
    
    return result;
}

// CHTLCSSProcessor 实现
CHTLCSSProcessor::CHTLCSSProcessor(std::shared_ptr<CHTLContext> ctx) 
    : context(ctx) {
    compiler = std::make_shared<CSSCompiler>(ctx);
    optimizer = std::make_shared<CSSOptimizer>();
    enhancedCompiler = std::make_shared<CHTLEnhancedCSSCompiler>(ctx);
}

void CHTLCSSProcessor::setTemplateManager(std::shared_ptr<TemplateManager> mgr) {
    templateManager = mgr;
    if (enhancedCompiler) {
        enhancedCompiler->setTemplateManager(mgr);
    }
}

void CHTLCSSProcessor::setCustomManager(std::shared_ptr<CustomManager> mgr) {
    customManager = mgr;
    if (enhancedCompiler) {
        enhancedCompiler->setCustomManager(mgr);
    }
}

void CHTLCSSProcessor::addGlobalStyleBlock(const std::string& css) {
    globalStyleBlocks.push_back(css);
}

void CHTLCSSProcessor::addLocalStyleBlock(const std::string& css, const std::string& scope) {
    std::string scopedCSS = css;
    
    // 如果提供了作用域，为所有选择器添加作用域前缀
    if (!scope.empty()) {
        // 这里简化处理，实际应该解析CSS并正确添加作用域
        scopedCSS = "/* Scoped to: " + scope + " */\n" + css;
    }
    
    localStyleBlocks.push_back(scopedCSS);
}

std::string CHTLCSSProcessor::generateFinalCSS() {
    std::vector<std::string> allBlocks;
    
    // 先处理全局样式
    for (const auto& block : globalStyleBlocks) {
        std::string compiled;
        
        if (useEnhancedMode && enhancedCompiler) {
            // 使用增强编译器（支持样式组和变量组）
            compiled = enhancedCompiler->compile(block);
        } else {
            // 使用标准编译器
            compiled = compiler->compile(block);
        }
        
        if (!compiled.empty()) {
            allBlocks.push_back(compiled);
        }
    }
    
    // 再处理局部样式
    for (const auto& block : localStyleBlocks) {
        std::string compiled = compiler->compile(block);
        if (!compiled.empty()) {
            allBlocks.push_back(compiled);
        }
    }
    
    // 合并所有CSS块
    std::string merged = compiler->mergeCSSBlocks(allBlocks);
    
    // 优化
    if (!merged.empty()) {
        auto [compiledCSS, rules] = compiler->compileWithAnalysis(merged);
        auto optimizedRules = optimizer->optimize(rules);
        
        // 重新生成CSS
        std::stringstream finalCSS;
        for (const auto& rule : optimizedRules) {
            finalCSS << rule.toString();
        }
        
        return finalCSS.str();
    }
    
    return merged;
}

std::pair<std::set<std::string>, std::set<std::string>> CHTLCSSProcessor::extractSelectorsInfo() {
    std::set<std::string> classes;
    std::set<std::string> ids;
    
    // 解析所有CSS块以提取类名和ID
    std::vector<std::string> allBlocks = globalStyleBlocks;
    allBlocks.insert(allBlocks.end(), localStyleBlocks.begin(), localStyleBlocks.end());
    
    for (const auto& block : allBlocks) {
        auto [css, rules] = compiler->compileWithAnalysis(block);
        
        for (const auto& rule : rules) {
            for (const auto& selector : rule.selectors) {
                // 提取类名
                std::regex classRegex("\\.([a-zA-Z_][a-zA-Z0-9_-]*)");
                std::sregex_iterator classIt(selector.begin(), selector.end(), classRegex);
                std::sregex_iterator classEnd;
                
                while (classIt != classEnd) {
                    classes.insert((*classIt)[1]);
                    ++classIt;
                }
                
                // 提取ID
                std::regex idRegex("#([a-zA-Z_][a-zA-Z0-9_-]*)");
                std::sregex_iterator idIt(selector.begin(), selector.end(), idRegex);
                std::sregex_iterator idEnd;
                
                while (idIt != idEnd) {
                    ids.insert((*idIt)[1]);
                    ++idIt;
                }
            }
        }
    }
    
    return {classes, ids};
}

void CHTLCSSProcessor::validateReferences(const std::set<std::string>& usedClasses,
                                        const std::set<std::string>& usedIds) {
    auto [definedClasses, definedIds] = extractSelectorsInfo();
    
    // 检查未定义的类
    for (const auto& className : usedClasses) {
        if (definedClasses.find(className) == definedClasses.end()) {
            context->reportWarning("Class '" + className + "' is used but not defined in CSS");
        }
    }
    
    // 检查未定义的ID
    for (const auto& id : usedIds) {
        if (definedIds.find(id) == definedIds.end()) {
            context->reportWarning("ID '" + id + "' is used but not defined in CSS");
        }
    }
    
    // 检查未使用的类
    for (const auto& className : definedClasses) {
        if (usedClasses.find(className) == usedClasses.end()) {
            context->reportWarning("Class '" + className + "' is defined but never used");
        }
    }
    
    // 检查未使用的ID
    for (const auto& id : definedIds) {
        if (usedIds.find(id) == usedIds.end()) {
            context->reportWarning("ID '" + id + "' is defined but never used");
        }
    }
}

} // namespace chtl