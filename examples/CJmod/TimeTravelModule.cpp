// 时间旅行调试器 CJmod 模块 - 展示无限创造力
#include "CJmod/CJmodCore.h"
#include <deque>
#include <chrono>
#include <json/json.h>  // 可以使用任何第三方库！

using namespace chtl::cjmod;

// 时间旅行状态
struct TimeTravelState {
    struct Snapshot {
        std::chrono::milliseconds timestamp;
        std::string domState;
        std::map<std::string, std::string> variables;
        std::string callStack;
    };
    
    std::deque<Snapshot> history;
    size_t currentIndex = 0;
    size_t maxSnapshots = 100;
    bool recording = true;
    
    // 性能分析
    std::map<std::string, double> performanceMetrics;
};

class TimeTravelModule : public CJmodModule {
public:
    TimeTravelModule() : CJmodModule("@cjmod/timetravel", "1.0.0") {
        setDescription("Time travel debugging with state snapshots")
            .setAuthor("CHTL Innovation Lab");
    }
    
    void initialize() override {
        state().set("timetravel", TimeTravelState{});
        
        // 录制状态: record { ... }
        syntax("record_block")
            .priority(300)
            .scan([this](ScanContext* ctx) {
                return scanRecordBlock(ctx);
            })
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                return generateRecordBlock(result, ctx);
            })
            .example(
                "record {\n"
                "    count++;\n"
                "    updateUI();\n"
                "}",
                "Records state changes within the block"
            );
        
        // 时间跳转: jump -5 (后退5步)
        syntax("time_jump")
            .priority(290)
            .pattern(R"(jump\s+([\-\+]?\d+))")
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                std::string steps = result.captures.at("1");
                return "this.timeTravel(" + steps + ")";
            });
        
        // 快照: snapshot "checkpoint name"
        syntax("snapshot")
            .priority(280)
            .pattern(R"(snapshot\s+["']([^"']+)["'])")
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                std::string name = result.captures.at("1");
                return "this.snapshot('" + name + "')";
            });
        
        // 回放: replay from "checkpoint"
        syntax("replay")
            .priority(270)
            .pattern(R"(replay\s+from\s+["']([^"']+)["'])")
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                std::string checkpoint = result.captures.at("1");
                return "this.replayFrom('" + checkpoint + "')";
            });
        
        // 调试断言: assert condition : "message"
        syntax("debug_assert")
            .priority(260)
            .scan([this](ScanContext* ctx) {
                return scanAssert(ctx);
            })
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                return generateAssert(result, ctx);
            });
        
        // 性能追踪: measure "operation" { ... }
        syntax("measure")
            .priority(250)
            .scan([this](ScanContext* ctx) {
                return scanMeasure(ctx);
            })
            .generate([this](const ScanResult& result, GenerateContext* ctx) {
                return generateMeasure(result, ctx);
            });
        
        setupRuntime();
    }
    
private:
    std::vector<ScanResult> scanRecordBlock(ScanContext* ctx) {
        std::vector<ScanResult> results;
        const std::string& code = ctx->getCode();
        
        size_t pos = 0;
        while ((pos = ctx->findNext("record", pos)) != std::string::npos) {
            if (ctx->isProcessed(pos)) {
                pos++;
                continue;
            }
            
            // 检查前面是否是单词边界
            if (pos > 0 && std::isalnum(code[pos - 1])) {
                pos++;
                continue;
            }
            
            size_t blockStart = ctx->findNext("{", pos + 6);
            if (blockStart == std::string::npos) {
                pos++;
                continue;
            }
            
            size_t blockEnd = ctx->findMatching('{', '}', blockStart);
            if (blockEnd == std::string::npos) {
                pos++;
                continue;
            }
            
            ScanResult result;
            result.start = pos;
            result.end = blockEnd + 1;
            result.content = code.substr(pos, result.end - pos);
            result.captures["body"] = code.substr(blockStart + 1, blockEnd - blockStart - 1);
            
            results.push_back(result);
            ctx->markProcessed(pos, result.end);
            
            pos = result.end;
        }
        
        return results;
    }
    
    std::string generateRecordBlock(const ScanResult& result, GenerateContext* ctx) {
        std::string body = result.captures.at("body");
        std::string id = ctx->uniqueVar("record");
        
        std::stringstream ss;
        ss << "(() => {\n";
        ss << "  const " << id << " = this.beginRecord();\n";
        ss << "  try {\n";
        ss << body << "\n";
        ss << "  } finally {\n";
        ss << "    this.endRecord(" << id << ");\n";
        ss << "  }\n";
        ss << "})()";
        
        return ss.str();
    }
    
    std::vector<ScanResult> scanAssert(ScanContext* ctx) {
        std::vector<ScanResult> results;
        const std::string& code = ctx->getCode();
        std::regex assertRegex(R"(assert\s+([^:]+)\s*:\s*["']([^"']+)["'])");
        
        auto it = std::sregex_iterator(code.begin(), code.end(), assertRegex);
        auto end = std::sregex_iterator();
        
        for (; it != end; ++it) {
            size_t start = it->position();
            if (ctx->isProcessed(start)) continue;
            
            ScanResult result;
            result.start = start;
            result.end = start + it->length();
            result.content = it->str();
            result.captures["condition"] = (*it)[1];
            result.captures["message"] = (*it)[2];
            
            results.push_back(result);
            ctx->markProcessed(start, result.end);
        }
        
        return results;
    }
    
    std::string generateAssert(const ScanResult& result, GenerateContext* ctx) {
        std::string condition = result.captures.at("condition");
        std::string message = result.captures.at("message");
        
        // 增强的断言，记录失败时的状态
        return "this.assert(() => " + condition + ", '" + message + "', () => ({ " + 
               "condition: '" + condition + "', " +
               "snapshot: this.getCurrentSnapshot() }))";
    }
    
    std::vector<ScanResult> scanMeasure(ScanContext* ctx) {
        std::vector<ScanResult> results;
        const std::string& code = ctx->getCode();
        std::regex measureRegex(R"(measure\s+["']([^"']+)["']\s*\{)");
        
        auto it = std::sregex_iterator(code.begin(), code.end(), measureRegex);
        auto end = std::sregex_iterator();
        
        for (; it != end; ++it) {
            size_t start = it->position();
            if (ctx->isProcessed(start)) continue;
            
            size_t blockStart = start + it->length() - 1;
            size_t blockEnd = ctx->findMatching('{', '}', blockStart);
            
            if (blockEnd == std::string::npos) continue;
            
            ScanResult result;
            result.start = start;
            result.end = blockEnd + 1;
            result.content = code.substr(start, result.end - start);
            result.captures["name"] = (*it)[1];
            result.captures["body"] = code.substr(blockStart + 1, blockEnd - blockStart - 1);
            
            results.push_back(result);
            ctx->markProcessed(start, result.end);
        }
        
        return results;
    }
    
    std::string generateMeasure(const ScanResult& result, GenerateContext* ctx) {
        std::string name = result.captures.at("name");
        std::string body = result.captures.at("body");
        std::string id = ctx->uniqueVar("perf");
        
        std::stringstream ss;
        ss << "await (async () => {\n";
        ss << "  const " << id << " = performance.now();\n";
        ss << "  try {\n";
        ss << body << "\n";
        ss << "  } finally {\n";
        ss << "    this.recordPerformance('" << name << "', performance.now() - " << id << ");\n";
        ss << "  }\n";
        ss << "})()";
        
        return ss.str();
    }
    
    void setupRuntime() {
        runtime()
            .class_("TimeTravel", R"(
class TimeTravel {
    constructor() {
        this.history = [];
        this.currentIndex = -1;
        this.recording = true;
        this.maxHistory = 100;
        this.checkpoints = new Map();
        this.observers = new Set();
        this.metrics = new Map();
    }
    
    beginRecord() {
        if (!this.recording) return null;
        
        const id = Date.now() + Math.random();
        const snapshot = this.captureSnapshot();
        
        return { id, snapshot };
    }
    
    endRecord(record) {
        if (!record || !this.recording) return;
        
        // 移除当前位置之后的历史
        this.history.splice(this.currentIndex + 1);
        
        // 添加新快照
        this.history.push({
            ...record.snapshot,
            timestamp: Date.now(),
            id: record.id
        });
        
        // 限制历史大小
        if (this.history.length > this.maxHistory) {
            this.history.shift();
        } else {
            this.currentIndex++;
        }
        
        this.notifyObservers('record', record);
    }
    
    captureSnapshot() {
        return {
            dom: document.body.innerHTML,
            variables: this.captureVariables(),
            callStack: new Error().stack,
            scrollPosition: {
                x: window.scrollX,
                y: window.scrollY
            }
        };
    }
    
    captureVariables() {
        // 捕获所有可追踪的变量
        const vars = {};
        
        // 遍历全局响应式变量
        for (const key in window) {
            if (window[key]?.constructor?.name === 'Reactive') {
                vars[key] = JSON.stringify(window[key].value);
            }
        }
        
        return vars;
    }
    
    timeTravel(steps) {
        const targetIndex = Math.max(0, 
            Math.min(this.history.length - 1, this.currentIndex + steps));
        
        if (targetIndex === this.currentIndex) return;
        
        const snapshot = this.history[targetIndex];
        this.restoreSnapshot(snapshot);
        this.currentIndex = targetIndex;
        
        this.notifyObservers('travel', { from: this.currentIndex, to: targetIndex });
    }
    
    restoreSnapshot(snapshot) {
        // 暂停录制
        const wasRecording = this.recording;
        this.recording = false;
        
        // 恢复 DOM
        document.body.innerHTML = snapshot.dom;
        
        // 恢复变量
        for (const [key, value] of Object.entries(snapshot.variables)) {
            if (window[key]?.value !== undefined) {
                window[key].value = JSON.parse(value);
            }
        }
        
        // 恢复滚动位置
        window.scrollTo(snapshot.scrollPosition.x, snapshot.scrollPosition.y);
        
        // 恢复录制状态
        this.recording = wasRecording;
    }
    
    snapshot(name) {
        const current = this.history[this.currentIndex];
        if (current) {
            this.checkpoints.set(name, {
                ...current,
                name,
                index: this.currentIndex
            });
        }
    }
    
    replayFrom(checkpointName) {
        const checkpoint = this.checkpoints.get(checkpointName);
        if (!checkpoint) {
            console.error(`Checkpoint '${checkpointName}' not found`);
            return;
        }
        
        this.currentIndex = checkpoint.index;
        this.restoreSnapshot(checkpoint);
        
        // 自动播放后续步骤
        this.autoReplay(checkpoint.index);
    }
    
    async autoReplay(fromIndex) {
        for (let i = fromIndex + 1; i < this.history.length; i++) {
            await new Promise(resolve => setTimeout(resolve, 500));
            this.timeTravel(1);
        }
    }
    
    assert(condition, message, captureExtra) {
        try {
            if (!condition()) {
                const extra = captureExtra ? captureExtra() : {};
                throw new AssertionError(message, {
                    ...extra,
                    history: this.history.slice(-10),
                    currentIndex: this.currentIndex
                });
            }
        } catch (e) {
            if (e instanceof AssertionError) throw e;
            throw new AssertionError(`Assert failed: ${e.message}`, {
                originalError: e
            });
        }
    }
    
    recordPerformance(name, duration) {
        if (!this.metrics.has(name)) {
            this.metrics.set(name, []);
        }
        
        this.metrics.get(name).push({
            duration,
            timestamp: Date.now(),
            historyIndex: this.currentIndex
        });
        
        // 计算统计
        const measurements = this.metrics.get(name);
        const avg = measurements.reduce((a, b) => a + b.duration, 0) / measurements.length;
        const min = Math.min(...measurements.map(m => m.duration));
        const max = Math.max(...measurements.map(m => m.duration));
        
        console.log(`Performance [${name}]: ${duration.toFixed(2)}ms (avg: ${avg.toFixed(2)}ms, min: ${min.toFixed(2)}ms, max: ${max.toFixed(2)}ms)`);
    }
    
    // 观察者模式
    observe(callback) {
        this.observers.add(callback);
        return () => this.observers.delete(callback);
    }
    
    notifyObservers(event, data) {
        this.observers.forEach(cb => cb(event, data));
    }
    
    // 导出/导入历史
    exportHistory() {
        return JSON.stringify({
            history: this.history,
            checkpoints: Array.from(this.checkpoints.entries()),
            currentIndex: this.currentIndex
        });
    }
    
    importHistory(data) {
        const parsed = JSON.parse(data);
        this.history = parsed.history;
        this.checkpoints = new Map(parsed.checkpoints);
        this.currentIndex = parsed.currentIndex;
        
        if (this.history[this.currentIndex]) {
            this.restoreSnapshot(this.history[this.currentIndex]);
        }
    }
}

class AssertionError extends Error {
    constructor(message, details) {
        super(message);
        this.name = 'AssertionError';
        this.details = details;
    }
}
)")
            .prototype("Element", "beginRecord", "function() { return window._timeTravel.beginRecord(); }")
            .prototype("Element", "endRecord", "function(r) { return window._timeTravel.endRecord(r); }")
            .prototype("Element", "timeTravel", "function(s) { return window._timeTravel.timeTravel(s); }")
            .prototype("Element", "snapshot", "function(n) { return window._timeTravel.snapshot(n); }")
            .prototype("Element", "replayFrom", "function(n) { return window._timeTravel.replayFrom(n); }")
            .prototype("Element", "assert", "function(c,m,e) { return window._timeTravel.assert(c,m,e); }")
            .prototype("Element", "recordPerformance", "function(n,d) { return window._timeTravel.recordPerformance(n,d); }")
            .prototype("Element", "getCurrentSnapshot", "function() { return window._timeTravel.captureSnapshot(); }")
            
            .global("_timeTravel", "new TimeTravel()")
            
            // 开发工具集成
            .init(R"(
// 集成到浏览器开发工具
if (window.__REACT_DEVTOOLS_GLOBAL_HOOK__) {
    window.__REACT_DEVTOOLS_GLOBAL_HOOK__.onCommitFiberRoot = (id, root) => {
        _timeTravel.beginRecord();
        setTimeout(() => _timeTravel.endRecord({ id: 'react-render' }), 0);
    };
}

// 键盘快捷键
document.addEventListener('keydown', (e) => {
    if (e.ctrlKey && e.shiftKey) {
        switch(e.key) {
            case 'ArrowLeft':
                e.preventDefault();
                _timeTravel.timeTravel(-1);
                break;
            case 'ArrowRight':
                e.preventDefault();
                _timeTravel.timeTravel(1);
                break;
            case 'S':
                e.preventDefault();
                const name = prompt('Snapshot name:');
                if (name) _timeTravel.snapshot(name);
                break;
        }
    }
});

// 可视化面板
const panel = document.createElement('div');
panel.id = 'timetravel-panel';
panel.innerHTML = `
    <style>
        #timetravel-panel {
            position: fixed;
            bottom: 20px;
            right: 20px;
            background: rgba(0,0,0,0.8);
            color: white;
            padding: 15px;
            border-radius: 8px;
            font-family: monospace;
            font-size: 12px;
            z-index: 99999;
        }
        #timetravel-panel button {
            margin: 0 5px;
            padding: 5px 10px;
            background: #007bff;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        #timetravel-panel button:hover {
            background: #0056b3;
        }
    </style>
    <div>Time Travel Debug Panel</div>
    <div id="tt-status">Ready</div>
    <div>
        <button onclick="_timeTravel.timeTravel(-5)">⏪ -5</button>
        <button onclick="_timeTravel.timeTravel(-1)">◀ -1</button>
        <button onclick="_timeTravel.timeTravel(1)">+1 ▶</button>
        <button onclick="_timeTravel.timeTravel(5)">+5 ⏩</button>
    </div>
    <div id="tt-history"></div>
`;
document.body.appendChild(panel);

// 更新面板
_timeTravel.observe((event, data) => {
    const status = document.getElementById('tt-status');
    const history = document.getElementById('tt-history');
    
    status.textContent = `Event: ${event} | History: ${_timeTravel.currentIndex + 1}/${_timeTravel.history.length}`;
    
    if (event === 'record') {
        history.textContent = `Last snapshot: ${new Date().toLocaleTimeString()}`;
    }
});
)")
    }
};

CJMOD_MODULE_EXPORT(TimeTravelModule)