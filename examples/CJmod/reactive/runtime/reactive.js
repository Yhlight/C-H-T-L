// CHTL Reactive Module Runtime
(function(window) {
    'use strict';
    
    // 响应式系统核心
    const ReactiveSystem = {
        // 依赖收集
        currentEffect: null,
        effects: new WeakMap(),
        
        // 跟踪依赖
        track(target, key) {
            if (this.currentEffect) {
                if (!this.effects.has(target)) {
                    this.effects.set(target, new Map());
                }
                const depsMap = this.effects.get(target);
                if (!depsMap.has(key)) {
                    depsMap.set(key, new Set());
                }
                depsMap.get(key).add(this.currentEffect);
            }
        },
        
        // 触发更新
        trigger(target, key) {
            const depsMap = this.effects.get(target);
            if (!depsMap) return;
            
            const deps = depsMap.get(key);
            if (deps) {
                deps.forEach(effect => effect());
            }
        },
        
        // 创建响应式对象
        reactive(obj) {
            return new Proxy(obj, {
                get(target, key) {
                    ReactiveSystem.track(target, key);
                    return target[key];
                },
                set(target, key, value) {
                    target[key] = value;
                    ReactiveSystem.trigger(target, key);
                    return true;
                }
            });
        }
    };
    
    // 导出到全局
    window.CHTLReactive = ReactiveSystem;
    
})(window);