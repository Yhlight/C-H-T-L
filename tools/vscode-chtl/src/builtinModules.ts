// 内置官方 CJmod 模块定义
export interface BuiltinModule {
    name: string;
    version: string;
    description: string;
    rules: Array<{
        pattern: string;
        replacement: string;
        priority: number;
    }>;
    runtime: {
        before?: string;
        after?: string;
    };
}

// Reactive 模块
export const ReactiveModule: BuiltinModule = {
    name: "reactive",
    version: "1.0.0",
    description: "Reactive programming support for CHTL",
    rules: [
        {
            pattern: "\\b(\\w+)\\s*:=\\s*([^;]+);",
            replacement: "let $1 = reactive($2);",
            priority: 100
        },
        {
            pattern: "\\b(\\w+)\\s*=>\\s*([^;]+);",
            replacement: "let $1 = computed(() => $2);",
            priority: 90
        },
        {
            pattern: "\\bwatch\\s+(\\w+)\\s*\\{([^}]+)\\}",
            replacement: "watch($1, () => {$2});",
            priority: 80
        }
    ],
    runtime: {
        before: `
// Reactive runtime
window.reactive = function(value) {
    const observers = [];
    const proxy = new Proxy({ value }, {
        get(target, prop) {
            if (prop === 'value') return target.value;
            if (prop === 'subscribe') {
                return (fn) => { observers.push(fn); };
            }
        },
        set(target, prop, newValue) {
            if (prop === 'value') {
                target.value = newValue;
                observers.forEach(fn => fn(newValue));
            }
            return true;
        }
    });
    return proxy;
};

window.computed = function(fn) {
    const result = reactive(fn());
    // Auto-update logic would go here
    return result;
};

window.watch = function(target, callback) {
    if (target && typeof target.subscribe === 'function') {
        target.subscribe(callback);
    }
};
`
    }
};

// Animation 模块
export const AnimationModule: BuiltinModule = {
    name: "animation",
    version: "1.0.0",
    description: "Animation chain syntax for CHTL",
    rules: [
        {
            pattern: "([^\\s]+)\\s*~>\\s*([\\w]+)",
            replacement: "$1.animate().$2",
            priority: 100
        },
        {
            pattern: "\\bdelay\\((\\d+)\\)",
            replacement: "await new Promise(r => setTimeout(r, $1))",
            priority: 90
        }
    ],
    runtime: {
        before: `
// Animation runtime
Element.prototype.animate = function() {
    const element = this;
    const animations = {
        fadeIn: () => {
            element.style.opacity = '0';
            element.style.transition = 'opacity 0.3s';
            requestAnimationFrame(() => {
                element.style.opacity = '1';
            });
            return animations;
        },
        fadeOut: () => {
            element.style.transition = 'opacity 0.3s';
            element.style.opacity = '0';
            return animations;
        },
        slideDown: () => {
            const height = element.scrollHeight;
            element.style.height = '0';
            element.style.overflow = 'hidden';
            element.style.transition = 'height 0.3s';
            requestAnimationFrame(() => {
                element.style.height = height + 'px';
            });
            return animations;
        },
        slideUp: () => {
            element.style.height = element.scrollHeight + 'px';
            element.style.overflow = 'hidden';
            element.style.transition = 'height 0.3s';
            requestAnimationFrame(() => {
                element.style.height = '0';
            });
            return animations;
        }
    };
    return animations;
};

window.delay = function(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
};
`
    }
};

// Pipeline 模块
export const PipelineModule: BuiltinModule = {
    name: "pipeline",
    version: "1.0.0",
    description: "Pipeline operators for functional programming",
    rules: [
        {
            pattern: "([^|]+)\\s*\\|>\\s*([^|;]+)",
            replacement: "pipe($1, $2)",
            priority: 100
        },
        {
            pattern: "([^|]+)\\s*\\|>>\\s*([^|;]+)",
            replacement: "mapPipe($1, $2)",
            priority: 100
        },
        {
            pattern: "([^|]+)\\s*\\|\\?>\\s*([^|;]+)",
            replacement: "filterPipe($1, $2)",
            priority: 100
        },
        {
            pattern: "(\\w+)\\s*>>\\s*(\\w+)",
            replacement: "compose($1, $2)",
            priority: 90
        },
        {
            pattern: "(\\w+)\\((\\?),\\s*([^)]+)\\)",
            replacement: "partial($1, $3)",
            priority: 80
        }
    ],
    runtime: {
        before: `
// Pipeline runtime
window.pipe = function(value, ...fns) {
    return fns.reduce((acc, fn) => fn(acc), value);
};

window.mapPipe = function(array, ...fns) {
    return array.map(item => pipe(item, ...fns));
};

window.filterPipe = function(array, predicate) {
    return array.filter(predicate);
};

window.compose = function(...fns) {
    return (value) => fns.reduceRight((acc, fn) => fn(acc), value);
};

window.partial = function(fn, ...args) {
    return (...restArgs) => {
        const allArgs = args.map(arg => arg === '?' ? restArgs.shift() : arg);
        return fn(...allArgs, ...restArgs);
    };
};
`
    }
};

// Async Flow 模块
export const AsyncFlowModule: BuiltinModule = {
    name: "async-flow",
    version: "1.0.0",
    description: "Advanced async flow control for CHTL",
    rules: [
        {
            pattern: "\\bstream\\s+(\\w+)\\s*\\{([^}]+)\\}",
            replacement: "createStream($1, async function*() {$2});",
            priority: 120
        },
        {
            pattern: "\\byield\\*\\s+when\\s+([^;]+);",
            replacement: "if ($1) yield* arguments[0];",
            priority: 110
        },
        {
            pattern: "\\bconcurrent\\s+(\\d+)\\s*\\{([^}]+)\\}",
            replacement: "await concurrent($1, async () => {$2});",
            priority: 100
        },
        {
            pattern: "\\bretry\\s+(\\d+)\\s*\\{([^}]+)\\}",
            replacement: "await retry($1, async () => {$2});",
            priority: 100
        },
        {
            pattern: "\\btimeout\\s+(\\d+)\\s*\\{([^}]+)\\}",
            replacement: "await timeout($1, async () => {$2});",
            priority: 100
        },
        {
            pattern: "\\btry\\*\\s*\\{([^}]+)\\}\\s*catch\\s*\\{([^}]+)\\}",
            replacement: "await tryAsync(async () => {$1}, async (e) => {$2});",
            priority: 90
        }
    ],
    runtime: {
        before: `
// Async Flow runtime
window.createStream = async function*(name, generator) {
    const stream = generator();
    for await (const value of stream) {
        yield value;
    }
};

window.concurrent = async function(limit, fn) {
    // Concurrent execution with limit
    const promises = [];
    for (let i = 0; i < limit; i++) {
        promises.push(fn());
    }
    return Promise.all(promises);
};

window.retry = async function(times, fn) {
    let lastError;
    for (let i = 0; i < times; i++) {
        try {
            return await fn();
        } catch (e) {
            lastError = e;
            if (i < times - 1) {
                await new Promise(r => setTimeout(r, Math.pow(2, i) * 1000));
            }
        }
    }
    throw lastError;
};

window.timeout = async function(ms, fn) {
    return Promise.race([
        fn(),
        new Promise((_, reject) => 
            setTimeout(() => reject(new Error('Timeout')), ms)
        )
    ]);
};

window.tryAsync = async function(tryFn, catchFn) {
    try {
        return await tryFn();
    } catch (e) {
        return await catchFn(e);
    }
};
`
    }
};

// 所有内置模块
export const BUILTIN_MODULES = new Map<string, BuiltinModule>([
    ['reactive', ReactiveModule],
    ['animation', AnimationModule],
    ['pipeline', PipelineModule],
    ['async-flow', AsyncFlowModule]
]);

// 获取所有内置模块代码（用于打包）
export function getAllBuiltinModulesCode(): string {
    const modules: string[] = [];
    
    BUILTIN_MODULES.forEach((module, key) => {
        modules.push(`
// ========== ${module.name} v${module.version} ==========
// ${module.description}

window.__CHTL_BUILTIN_MODULES = window.__CHTL_BUILTIN_MODULES || {};
window.__CHTL_BUILTIN_MODULES['${key}'] = ${JSON.stringify(module)};
`);
    });
    
    return modules.join('\n\n');
}

// 生成内置模块的 TypeScript 声明
export function generateBuiltinModulesDeclaration(): string {
    return `
// CHTL Built-in Modules Type Declarations

declare global {
    // Reactive Module
    function reactive<T>(value: T): { value: T; subscribe: (fn: (value: T) => void) => void };
    function computed<T>(fn: () => T): { value: T };
    function watch<T>(target: { subscribe: (fn: (value: T) => void) => void }, callback: (value: T) => void): void;
    
    // Animation Module
    interface AnimationChain {
        fadeIn(): AnimationChain;
        fadeOut(): AnimationChain;
        slideDown(): AnimationChain;
        slideUp(): AnimationChain;
    }
    
    interface Element {
        animate(): AnimationChain;
    }
    
    function delay(ms: number): Promise<void>;
    
    // Pipeline Module
    function pipe<T>(value: T, ...fns: Array<(value: any) => any>): any;
    function mapPipe<T>(array: T[], ...fns: Array<(value: T) => any>): any[];
    function filterPipe<T>(array: T[], predicate: (value: T) => boolean): T[];
    function compose(...fns: Array<(value: any) => any>): (value: any) => any;
    function partial<T extends (...args: any[]) => any>(fn: T, ...args: any[]): (...restArgs: any[]) => ReturnType<T>;
    
    // Async Flow Module
    function createStream<T>(name: string, generator: () => AsyncGenerator<T>): AsyncGenerator<T>;
    function concurrent<T>(limit: number, fn: () => Promise<T>): Promise<T[]>;
    function retry<T>(times: number, fn: () => Promise<T>): Promise<T>;
    function timeout<T>(ms: number, fn: () => Promise<T>): Promise<T>;
    function tryAsync<T, E>(tryFn: () => Promise<T>, catchFn: (error: E) => Promise<T>): Promise<T>;
}

export {};
`;
}