// 事件委托 CJmod 模块 - 展示无限可能性
#include "CJmod/CJmodCore.h"
#include <map>
#include <set>
#include <sstream>
#include <regex>

using namespace chtl::cjmod;

// 自定义头文件 - 开发者可以包含任何需要的库
#include <algorithm>
#include <chrono>
#include <thread>

// 全局状态 - 管理委托的事件
struct DelegateState {
    struct DelegateInfo {
        std::string selector;
        std::string event;
        std::string handler;
        bool once;
        bool passive;
        bool capture;
    };
    
    // 每个元素的委托事件
    std::map<std::string, std::vector<DelegateInfo>> delegates;
    
    // 性能统计
    std::map<std::string, int> eventCounts;
    std::chrono::steady_clock::time_point startTime;
    
    // 事件池 - 优化性能
    std::set<std::string> eventPool;
    
    DelegateState() : startTime(std::chrono::steady_clock::now()) {}
};

class DelegateModule : public CJmodModule {
public:
    DelegateModule() : CJmodModule("@cjmod/delegate", "2.0.0") {
        setDescription("Advanced event delegation with performance optimization")
            .setAuthor("CHTL Team");
    }
    
    void initialize() override {
        // 初始化全局状态
        state().set("delegate", DelegateState{});
        
        // 基础委托语法: on .child click -> { ... }
        syntax("basic_delegate")
            .priority(200)
            .description("Basic event delegation")
            .scan([this](ScanContext* ctx) {
                return scanDelegatePattern(ctx, 
                    R"(on\s+([\.\#\w\-\[\]]+)\s+(\w+)\s*->)",
                    false);
            })
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                return generateDelegate(result, ctx, false);
            })
            .example("on .button click -> { alert('clicked'); }", 
                    "this.delegate('.button', 'click', function(e) { alert('clicked'); })");
        
        // 一次性委托: once .child click -> { ... }
        syntax("once_delegate")
            .priority(190)
            .pattern(R"(once\s+([\.\#\w\-\[\]]+)\s+(\w+)\s*->)")
            .scan([this](ScanContext* ctx) {
                return scanDelegatePattern(ctx, 
                    R"(once\s+([\.\#\w\-\[\]]+)\s+(\w+)\s*->)",
                    true);
            })
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                return generateDelegate(result, ctx, true);
            });
        
        // 批量委托: delegate { ... }
        syntax("batch_delegate")
            .priority(180)
            .scan([this](ScanContext* ctx) {
                return scanBatchDelegate(ctx);
            })
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                return generateBatchDelegate(result, ctx);
            })
            .example(
                "delegate {\n"
                "    .btn: click, mouseenter;\n"
                "    .link: click once;\n"
                "}",
                "Batch delegation setup"
            );
        
        // 性能监控: monitor events
        syntax("monitor_events")
            .priority(170)
            .pattern(R"(monitor\s+events)")
            .replace("this.monitorEvents()")
            .example("monitor events", "this.monitorEvents()");
        
        // 设置运行时
        setupRuntime();
    }
    
private:
    // 扫描委托模式
    std::vector<ScanResult> scanDelegatePattern(ScanContext* ctx, 
                                                const std::string& pattern,
                                                bool once) {
        std::vector<ScanResult> results;
        const std::string& code = ctx->getCode();
        std::regex regex(pattern);
        
        auto it = std::sregex_iterator(code.begin(), code.end(), regex);
        auto end = std::sregex_iterator();
        
        for (; it != end; ++it) {
            size_t start = it->position();
            
            if (ctx->isProcessed(start)) continue;
            
            // 找到箭头后的代码块
            size_t arrowEnd = start + it->length();
            size_t blockStart = ctx->findNext("{", arrowEnd);
            
            if (blockStart == std::string::npos) continue;
            
            size_t blockEnd = ctx->findMatching('{', '}', blockStart);
            if (blockEnd == std::string::npos) continue;
            
            ScanResult result;
            result.start = start;
            result.end = blockEnd + 1;
            result.content = code.substr(start, result.end - start);
            result.captures["selector"] = (*it)[1];
            result.captures["event"] = (*it)[2];
            result.captures["body"] = code.substr(blockStart + 1, blockEnd - blockStart - 1);
            result.userData = once;
            
            results.push_back(result);
            ctx->markProcessed(start, result.end);
            
            // 更新全局状态
            updateDelegateState(result);
        }
        
        return results;
    }
    
    // 扫描批量委托
    std::vector<ScanResult> scanBatchDelegate(ScanContext* ctx) {
        std::vector<ScanResult> results;
        const std::string& code = ctx->getCode();
        
        size_t pos = 0;
        while ((pos = ctx->findNext("delegate", pos)) != std::string::npos) {
            if (ctx->isProcessed(pos)) {
                pos++;
                continue;
            }
            
            size_t blockStart = ctx->findNext("{", pos + 8);
            if (blockStart == std::string::npos) break;
            
            size_t blockEnd = ctx->findMatching('{', '}', blockStart);
            if (blockEnd == std::string::npos) break;
            
            ScanResult result;
            result.start = pos;
            result.end = blockEnd + 1;
            result.content = code.substr(pos, result.end - pos);
            
            // 解析批量规则
            std::string block = code.substr(blockStart + 1, blockEnd - blockStart - 1);
            result.userData = parseBatchRules(block);
            
            results.push_back(result);
            ctx->markProcessed(pos, result.end);
            
            pos = result.end;
        }
        
        return results;
    }
    
    // 生成委托代码
    std::string generateDelegate(const ScanResult& result, GenerateContext* ctx, bool once) {
        std::string selector = result.captures.at("selector");
        std::string event = result.captures.at("event");
        std::string body = result.captures.at("body");
        
        // 获取或创建唯一的处理器名称
        std::string handlerName = ctx->uniqueVar("handler");
        
        std::stringstream ss;
        ss << "this.delegate('" << selector << "', '" << event << "', ";
        ss << "function " << handlerName << "(e) {" << body << "}";
        
        if (once) {
            ss << ", { once: true }";
        }
        
        ss << ")";
        
        // 添加到事件池以优化
        auto* delegateState = ctx->getStateManager()->get<DelegateState>("delegate");
        if (delegateState) {
            delegateState->eventPool.insert(event);
        }
        
        return ss.str();
    }
    
    // 生成批量委托
    std::string generateBatchDelegate(const ScanResult& result, GenerateContext* ctx) {
        auto rules = std::any_cast<std::vector<std::map<std::string, std::string>>>(result.userData);
        
        std::stringstream ss;
        ss << "this.batchDelegate([\n";
        
        for (size_t i = 0; i < rules.size(); i++) {
            const auto& rule = rules[i];
            ss << "  { ";
            ss << "selector: '" << rule.at("selector") << "', ";
            ss << "events: '" << rule.at("events") << "'";
            
            if (rule.find("options") != rule.end()) {
                ss << ", options: " << rule.at("options");
            }
            
            ss << " }";
            
            if (i < rules.size() - 1) ss << ",";
            ss << "\n";
        }
        
        ss << "])";
        
        return ss.str();
    }
    
    // 更新委托状态
    void updateDelegateState(const ScanResult& result) {
        auto* delegateState = state().get<DelegateState>("delegate");
        if (!delegateState) return;
        
        DelegateState::DelegateInfo info;
        info.selector = result.captures.at("selector");
        info.event = result.captures.at("event");
        info.once = std::any_cast<bool>(result.userData);
        
        delegateState->delegates[info.selector].push_back(info);
        delegateState->eventCounts[info.event]++;
    }
    
    // 解析批量规则
    std::vector<std::map<std::string, std::string>> parseBatchRules(const std::string& block) {
        std::vector<std::map<std::string, std::string>> rules;
        
        std::regex ruleRegex(R"(([.\#\w\-\[\]]+)\s*:\s*([^;]+);?)");
        auto it = std::sregex_iterator(block.begin(), block.end(), ruleRegex);
        auto end = std::sregex_iterator();
        
        for (; it != end; ++it) {
            std::map<std::string, std::string> rule;
            rule["selector"] = (*it)[1];
            
            std::string eventsPart = (*it)[2];
            // 检查是否有选项
            size_t optPos = eventsPart.find(" ");
            if (optPos != std::string::npos) {
                rule["events"] = eventsPart.substr(0, optPos);
                rule["options"] = eventsPart.substr(optPos + 1);
            } else {
                rule["events"] = eventsPart;
            }
            
            rules.push_back(rule);
        }
        
        return rules;
    }
    
    // 设置运行时
    void setupRuntime() {
        runtime()
            // 核心委托系统
            .class_("DelegateSystem", R"(
class DelegateSystem {
    constructor(element) {
        this.element = element;
        this.delegates = new Map();
        this.stats = { total: 0, byEvent: {} };
    }
    
    delegate(selector, event, handler, options = {}) {
        const key = `${selector}:${event}`;
        
        if (!this.delegates.has(key)) {
            this.delegates.set(key, []);
            
            // 使用事件捕获优化性能
            this.element.addEventListener(event, (e) => {
                const handlers = this.delegates.get(key);
                if (!handlers) return;
                
                // 检查目标是否匹配选择器
                const target = e.target.closest(selector);
                if (!target || !this.element.contains(target)) return;
                
                // 执行处理器
                for (const h of handlers) {
                    if (h.once && h.executed) continue;
                    
                    h.handler.call(target, e);
                    h.executed = true;
                    
                    this.stats.total++;
                    this.stats.byEvent[event] = (this.stats.byEvent[event] || 0) + 1;
                }
                
                // 清理一次性处理器
                if (options.once) {
                    this.delegates.set(key, handlers.filter(h => !h.executed));
                }
            }, true);
        }
        
        this.delegates.get(key).push({
            handler,
            once: options.once || false,
            executed: false
        });
        
        return this;
    }
    
    batchDelegate(rules) {
        for (const rule of rules) {
            const events = rule.events.split(',').map(e => e.trim());
            for (const event of events) {
                this.delegate(rule.selector, event, () => {}, rule.options || {});
            }
        }
        return this;
    }
    
    monitorEvents() {
        console.log('Event Delegation Stats:', this.stats);
        return this;
    }
    
    clear() {
        this.delegates.clear();
        this.stats = { total: 0, byEvent: {} };
    }
}
)")
            // 扩展 Element 原型
            .prototype("Element", "delegate", R"(
function(selector, event, handler, options) {
    if (!this._delegateSystem) {
        this._delegateSystem = new DelegateSystem(this);
    }
    return this._delegateSystem.delegate(selector, event, handler, options);
}
)")
            .prototype("Element", "batchDelegate", R"(
function(rules) {
    if (!this._delegateSystem) {
        this._delegateSystem = new DelegateSystem(this);
    }
    return this._delegateSystem.batchDelegate(rules);
}
)")
            .prototype("Element", "monitorEvents", R"(
function() {
    if (this._delegateSystem) {
        return this._delegateSystem.monitorEvents();
    }
    console.log('No events delegated on this element');
    return this;
}
)")
            // 性能优化：预编译选择器
            .global("_selectorCache", "new Map()")
            .function("compileSelector", R"(
function compileSelector(selector) {
    if (_selectorCache.has(selector)) {
        return _selectorCache.get(selector);
    }
    
    // 预编译选择器以提高匹配性能
    const compiled = {
        selector,
        isClass: selector.startsWith('.'),
        isId: selector.startsWith('#'),
        tag: selector.match(/^(\w+)/)?.[1],
        attributes: [...selector.matchAll(/\[([^\]]+)\]/g)].map(m => m[1])
    };
    
    _selectorCache.set(selector, compiled);
    return compiled;
}
)")
            // 初始化代码
            .init(R"(
// 自动清理未使用的委托
setInterval(() => {
    document.querySelectorAll('[data-delegate]').forEach(el => {
        if (!document.body.contains(el) && el._delegateSystem) {
            el._delegateSystem.clear();
        }
    });
}, 60000);
)");
    }
};

// 导出模块
CJMOD_MODULE_EXPORT(DelegateModule)