#include "CJmod/CJmodCorrect.h"
#include <sstream>

namespace chtl {
namespace cjmod {

/**
 * Async Flow Control Module
 * 
 * 提供高级异步流控制语法，包括：
 * 1. async/await 流 - 类似 Rust 的异步流
 * 2. 并发控制 - 限制并发数量
 * 3. 重试机制 - 自动重试失败的操作
 * 4. 超时控制 - 自动超时
 * 5. 异步生成器 - yield* 语法
 * 6. 错误处理 - try* 语法
 */
class AsyncFlowModule : public ICJmod {
public:
    std::string getName() const override { 
        return "async-flow"; 
    }
    
    std::string getVersion() const override { 
        return "2.0.0"; 
    }
    
    std::vector<std::string> getDependencies() const override {
        return {};
    }
    
    std::vector<ScanCutRule> getScanCutRules() const override {
        return {
            // 1. 异步流语法: stream UserEvents from source { ... }
            // 转换为异步生成器
            {
                "async-stream",
                std::regex(R"(stream\s+(\w+)\s+from\s+(\w+)\s*\{)"),
                "async function* $1() { const _source = $2; try {",
                150
            },
            
            // 2. yield* 语法: yield* value when condition
            {
                "yield-when",
                std::regex(R"(yield\*\s+([^;]+)\s+when\s+([^;]+);)"),
                "if ($2) { yield $1; }",
                140
            },
            
            // 3. 并发控制: concurrent(3) { ... }
            {
                "concurrent-block",
                std::regex(R"(concurrent\s*\((\d+)\)\s*\{)"),
                "await concurrent($1, async () => {",
                130
            },
            
            // 4. 重试语法: retry(3, 1000) { ... }
            {
                "retry-block",
                std::regex(R"(retry\s*\((\d+),\s*(\d+)\)\s*\{)"),
                "await retry($1, $2, async () => {",
                120
            },
            
            // 5. 超时语法: timeout(5000) { ... } catch { ... }
            {
                "timeout-block",
                std::regex(R"(timeout\s*\((\d+)\)\s*\{)"),
                "await timeout($1, async () => {",
                110
            },
            
            // 6. try* 语法（自动捕获并记录错误）: try* { ... }
            {
                "try-star",
                std::regex(R"(try\*\s*\{)"),
                "await tryAsync(async () => {",
                100
            },
            
            // 7. 异步管道: async value |> step1 |> step2
            {
                "async-pipe",
                std::regex(R"(async\s+([^|]+)\s*\|>\s*([^|]+))"),
                "await pipe($1, $2)",
                90
            },
            
            // 8. 并行执行: parallel { task1(); task2(); }
            {
                "parallel-block",
                std::regex(R"(parallel\s*\{)"),
                "await Promise.all([",
                85
            },
            
            // 9. 竞速执行: race { task1(); task2(); }
            {
                "race-block", 
                std::regex(R"(race\s*\{)"),
                "await Promise.race([",
                85
            },
            
            // 10. 异步 for-await 增强: for await item of stream where condition { ... }
            {
                "for-await-where",
                std::regex(R"(for\s+await\s+(\w+)\s+of\s+(\w+)\s+where\s+([^{]+)\{)"),
                "for await (const $1 of $2) { if ($3) {",
                80
            },
            
            // 11. 异步断言: assert* condition, "message"
            {
                "async-assert",
                std::regex(R"(assert\*\s+([^,]+),\s*"([^"]+)")"),
                "await assertAsync(() => $1, '$2')",
                70
            },
            
            // 12. 延迟执行: defer { ... }
            {
                "defer-block",
                std::regex(R"(defer\s*\{)"),
                "_deferred.push(async () => {",
                60
            },
            
            // 13. 异步锁: lock(resource) { ... }
            {
                "lock-block",
                std::regex(R"(lock\s*\(([^)]+)\)\s*\{)"),
                "await withLock($1, async () => {",
                50
            },
            
            // 14. 结束特殊块
            {
                "special-block-end",
                std::regex(R"(\}\s*//\s*(stream|concurrent|retry|timeout|try\*|parallel|race|defer|lock)\s*end)"),
                "})",
                40
            }
        };
    }
    
    std::vector<RuntimeInjection> getRuntimeInjections() const override {
        return {
            {
                R"(
// Async Flow Control Runtime

// 并发控制器
class ConcurrencyController {
    constructor(limit) {
        this.limit = limit;
        this.running = 0;
        this.queue = [];
    }
    
    async run(fn) {
        while (this.running >= this.limit) {
            await new Promise(resolve => this.queue.push(resolve));
        }
        
        this.running++;
        try {
            return await fn();
        } finally {
            this.running--;
            const next = this.queue.shift();
            if (next) next();
        }
    }
}

// 全局并发控制
window.concurrent = async function(limit, fn) {
    const controller = new ConcurrencyController(limit);
    return controller.run(fn);
};

// 重试机制
window.retry = async function(times, delay, fn) {
    let lastError;
    for (let i = 0; i < times; i++) {
        try {
            return await fn();
        } catch (error) {
            lastError = error;
            console.warn(`Retry ${i + 1}/${times} failed:`, error);
            if (i < times - 1) {
                await new Promise(r => setTimeout(r, delay));
            }
        }
    }
    throw new Error(`Failed after ${times} retries: ${lastError?.message}`);
};

// 超时控制
window.timeout = async function(ms, fn) {
    return Promise.race([
        fn(),
        new Promise((_, reject) => 
            setTimeout(() => reject(new Error(`Timeout after ${ms}ms`)), ms)
        )
    ]);
};

// 安全的异步执行
window.tryAsync = async function(fn) {
    try {
        return await fn();
    } catch (error) {
        console.error('[AsyncFlow] Error:', error);
        return { error, success: false };
    }
};

// 异步管道
window.pipe = async function(...args) {
    let result = args[0];
    for (let i = 1; i < args.length; i++) {
        if (typeof args[i] === 'function') {
            result = await args[i](result);
        } else {
            result = args[i];
        }
    }
    return result;
};

// 异步断言
window.assertAsync = async function(condition, message) {
    const result = typeof condition === 'function' ? await condition() : condition;
    if (!result) {
        throw new Error(`Assertion failed: ${message}`);
    }
};

// 延迟执行管理
window._deferred = [];
window.runDeferred = async function() {
    const tasks = window._deferred.slice();
    window._deferred = [];
    for (const task of tasks.reverse()) {
        try {
            await task();
        } catch (error) {
            console.error('[Deferred] Error:', error);
        }
    }
};

// 在页面卸载时执行延迟任务
window.addEventListener('beforeunload', () => {
    runDeferred();
});

// 简单的异步锁实现
class AsyncLock {
    constructor() {
        this.locked = false;
        this.queue = [];
    }
    
    async acquire() {
        while (this.locked) {
            await new Promise(resolve => this.queue.push(resolve));
        }
        this.locked = true;
    }
    
    release() {
        this.locked = false;
        const next = this.queue.shift();
        if (next) next();
    }
}

// 锁管理器
window._locks = new Map();

window.withLock = async function(resource, fn) {
    if (!_locks.has(resource)) {
        _locks.set(resource, new AsyncLock());
    }
    
    const lock = _locks.get(resource);
    await lock.acquire();
    try {
        return await fn();
    } finally {
        lock.release();
    }
};

// 异步流工具
window.AsyncStream = class {
    constructor(source) {
        this.source = source;
        this.filters = [];
        this.transforms = [];
    }
    
    where(predicate) {
        this.filters.push(predicate);
        return this;
    }
    
    map(transform) {
        this.transforms.push(transform);
        return this;
    }
    
    async *[Symbol.asyncIterator]() {
        for await (const item of this.source) {
            let shouldYield = true;
            
            // 应用过滤器
            for (const filter of this.filters) {
                if (!filter(item)) {
                    shouldYield = false;
                    break;
                }
            }
            
            if (shouldYield) {
                let value = item;
                
                // 应用转换
                for (const transform of this.transforms) {
                    value = transform(value);
                }
                
                yield value;
            }
        }
    }
};

// 创建异步流
window.createStream = function(source) {
    return new AsyncStream(source);
};
)",
                "before"
            }
        };
    }
};

// 注册函数
extern "C" std::shared_ptr<ICJmod> createAsyncFlowModule() {
    return std::make_shared<AsyncFlowModule>();
}

} // namespace cjmod
} // namespace chtl