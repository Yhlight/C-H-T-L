// 响应式编程 CJmod 模块示例
#include "CJmod/CJmodAPI.h"
#include <sstream>
#include <regex>

using namespace chtl::cjmod;

// 响应式赋值规则: count := 0
class ReactiveAssignmentRule : public RegexRule {
public:
    ReactiveAssignmentRule() 
        : RegexRule("reactive_assignment", 
                   R"((\w+)\s*:=\s*([^;]+);?)",
                   150,  // 高优先级
                   "reactive_assign") {}
    
    std::string generate(const CutPoint& cut, GenerateContext* ctx) override {
        // 解析切割的内容
        std::regex pattern(R"((\w+)\s*:=\s*([^;]+);?)");
        std::smatch match;
        
        if (std::regex_match(cut.content, match, pattern)) {
            std::string varName = match[1];
            std::string value = match[2];
            
            // 添加响应式运行时（只添加一次）
            ctx->addRuntimeOnce("reactive_runtime", R"(
function reactive(initialValue) {
    let value = initialValue;
    const subscribers = new Set();
    
    return {
        get value() { return value; },
        set value(newValue) {
            value = newValue;
            subscribers.forEach(fn => fn(newValue));
        },
        subscribe(fn) {
            subscribers.add(fn);
            return () => subscribers.delete(fn);
        }
    };
}
)");
            
            // 生成代码
            return "const " + varName + " = reactive(" + value + ")";
        }
        
        ctx->reportError("Invalid reactive assignment syntax", cut);
        return cut.content;
    }
};

// 计算属性规则: doubled => count.value * 2
class ComputedPropertyRule : public ComplexRule {
public:
    ComputedPropertyRule() 
        : ComplexRule("computed_property", 140) {}
    
    std::vector<CutPoint> scan(const std::string& code, ScanContext* ctx) override {
        std::vector<CutPoint> cuts;
        size_t pos = 0;
        
        while (pos < code.length()) {
            // 查找 => 模式
            size_t arrowPos = code.find("=>", pos);
            if (arrowPos == std::string::npos) break;
            
            // 检查是否在字符串或注释中
            if (ctx->isInString() || ctx->isInComment()) {
                pos = arrowPos + 2;
                continue;
            }
            
            // 向前查找变量名
            size_t varStart = arrowPos;
            while (varStart > 0 && std::isspace(code[varStart - 1])) {
                varStart--;
            }
            while (varStart > 0 && (std::isalnum(code[varStart - 1]) || code[varStart - 1] == '_')) {
                varStart--;
            }
            
            // 向后查找表达式结尾（分号或换行）
            size_t exprEnd = arrowPos + 2;
            while (exprEnd < code.length() && std::isspace(code[exprEnd])) {
                exprEnd++;
            }
            
            int parenDepth = 0;
            int braceDepth = 0;
            while (exprEnd < code.length()) {
                char ch = code[exprEnd];
                if (ch == '(') parenDepth++;
                else if (ch == ')') parenDepth--;
                else if (ch == '{') braceDepth++;
                else if (ch == '}') braceDepth--;
                else if ((ch == ';' || ch == '\n') && parenDepth == 0 && braceDepth == 0) {
                    if (ch == ';') exprEnd++;
                    break;
                }
                exprEnd++;
            }
            
            CutPoint cut;
            cut.start = varStart;
            cut.end = exprEnd;
            cut.type = "computed";
            cut.content = code.substr(varStart, exprEnd - varStart);
            
            cuts.push_back(cut);
            ctx->markProcessed(cut.start, cut.end);
            
            pos = exprEnd;
        }
        
        return cuts;
    }
    
    std::string generate(const CutPoint& cut, GenerateContext* ctx) override {
        // 解析: varName => expression
        size_t arrowPos = cut.content.find("=>");
        if (arrowPos == std::string::npos) {
            ctx->reportError("Invalid computed property syntax", cut);
            return cut.content;
        }
        
        std::string varName = cut.content.substr(0, arrowPos);
        std::string expression = cut.content.substr(arrowPos + 2);
        
        // 去除空白和分号
        varName.erase(varName.find_last_not_of(" \t\n\r") + 1);
        expression.erase(0, expression.find_first_not_of(" \t\n\r"));
        if (!expression.empty() && expression.back() == ';') {
            expression.pop_back();
        }
        
        // 添加计算属性运行时
        ctx->addRuntimeOnce("computed_runtime", R"(
function computed(fn) {
    let cache;
    let dirty = true;
    
    return {
        get value() {
            if (dirty) {
                cache = fn();
                dirty = false;
            }
            return cache;
        },
        invalidate() {
            dirty = true;
        }
    };
}
)");
        
        return "const " + varName + " = computed(() => " + expression + ")";
    }
};

// Watch 语法规则: watch count -> { ... }
class WatchRule : public ComplexRule {
public:
    WatchRule() : ComplexRule("watch", 130) {}
    
    std::vector<CutPoint> scan(const std::string& code, ScanContext* ctx) override {
        std::vector<CutPoint> cuts;
        std::regex watchPattern(R"(watch\s+(\w+)\s*->)");
        std::sregex_iterator it(code.begin(), code.end(), watchPattern);
        std::sregex_iterator end;
        
        for (; it != end; ++it) {
            size_t start = it->position();
            size_t blockStart = start + it->length();
            
            // 跳过空白找到 {
            blockStart = skipWhitespace(code, blockStart);
            if (blockStart >= code.length() || code[blockStart] != '{') {
                continue;
            }
            
            // 找到匹配的 }
            size_t blockEnd = ctx->findMatchingBrace(blockStart);
            if (blockEnd == std::string::npos) {
                continue;
            }
            
            CutPoint cut;
            cut.start = start;
            cut.end = blockEnd + 1;
            cut.type = "watch";
            cut.content = code.substr(start, cut.end - start);
            
            cuts.push_back(cut);
            ctx->markProcessed(cut.start, cut.end);
        }
        
        return cuts;
    }
    
    std::string generate(const CutPoint& cut, GenerateContext* ctx) override {
        std::regex pattern(R"(watch\s+(\w+)\s*->\s*\{(.*)\})", std::regex::singleline);
        std::smatch match;
        
        if (std::regex_match(cut.content, match, pattern)) {
            std::string varName = match[1];
            std::string body = match[2];
            
            // 添加 watch 运行时
            ctx->addRuntimeOnce("watch_runtime", R"(
function watch(target, callback) {
    if (target && typeof target.subscribe === 'function') {
        return target.subscribe(callback);
    }
    console.warn('Target is not watchable:', target);
}
)");
            
            return "watch(" + varName + ", (newValue) => {" + body + "})";
        }
        
        ctx->reportError("Invalid watch syntax", cut);
        return cut.content;
    }
};

// 双向绑定规则: bind:value="count"
class BindRule : public RegexRule {
public:
    BindRule() 
        : RegexRule("bind", 
                   R"({{&}}->bind\(["'](\w+)["']\))",
                   120,
                   "bind") {}
    
    std::string generate(const CutPoint& cut, GenerateContext* ctx) override {
        std::regex pattern(R"({{&}}->bind\(["'](\w+)["']\))");
        std::smatch match;
        
        if (std::regex_match(cut.content, match, pattern)) {
            std::string varName = match[1];
            
            ctx->addRuntimeOnce("bind_runtime", R"(
Element.prototype.bind = function(varName) {
    const element = this;
    const variable = window[varName];
    
    if (!variable || typeof variable.subscribe !== 'function') {
        console.error('Cannot bind to non-reactive variable:', varName);
        return;
    }
    
    // 输入 -> 变量
    element.addEventListener('input', (e) => {
        variable.value = e.target.value;
    });
    
    // 变量 -> 输入
    variable.subscribe((value) => {
        if (element.value !== value) {
            element.value = value;
        }
    });
    
    // 初始同步
    element.value = variable.value;
};
)");
            
            return "this.bind('" + varName + "')";
        }
        
        return cut.content;
    }
};

// 响应式模块实现
class ReactiveModule : public ICJmodModule {
public:
    std::string getName() const override {
        return "@cjmod/reactive";
    }
    
    std::string getVersion() const override {
        return "1.0.0";
    }
    
    std::string getDescription() const override {
        return "Reactive programming syntax for CHTL JS";
    }
    
    std::string getAuthor() const override {
        return "CHTL Team";
    }
    
    std::vector<std::unique_ptr<SyntaxRule>> createRules() override {
        std::vector<std::unique_ptr<SyntaxRule>> rules;
        
        rules.push_back(std::make_unique<ReactiveAssignmentRule>());
        rules.push_back(std::make_unique<ComputedPropertyRule>());
        rules.push_back(std::make_unique<WatchRule>());
        rules.push_back(std::make_unique<BindRule>());
        
        return rules;
    }
    
    void initialize() override {
        // 可以在这里做一些初始化工作
    }
};

// 导出模块
CJMOD_MODULE(ReactiveModule)