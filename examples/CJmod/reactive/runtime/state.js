// CHTL Reactive State Module Runtime
(function(window) {
    'use strict';
    
    if (!window.CHTLReactive) {
        console.error('CHTLReactive.State requires CHTLReactive core module');
        return;
    }
    
    // 状态管理
    const StateManager = {
        states: new Map(),
        batchQueue: [],
        isBatching: false,
        
        // 创建状态
        createState(value) {
            const state = window.CHTLReactive.reactive({
                value: value,
                listeners: [],
                
                get() {
                    return this.value;
                },
                
                set(newValue) {
                    if (this.value !== newValue) {
                        this.value = newValue;
                        this.notify();
                    }
                },
                
                subscribe(listener) {
                    this.listeners.push(listener);
                    return () => {
                        const index = this.listeners.indexOf(listener);
                        if (index > -1) {
                            this.listeners.splice(index, 1);
                        }
                    };
                },
                
                notify() {
                    this.listeners.forEach(listener => listener(this.value));
                }
            });
            
            return state;
        },
        
        // 更新状态
        updateState(state, value) {
            if (this.isBatching) {
                this.batchQueue.push(() => state.set(value));
            } else {
                state.set(value);
            }
        },
        
        // 批量更新
        batchUpdate(fn) {
            this.isBatching = true;
            fn();
            this.isBatching = false;
            
            // 执行批量队列
            const queue = this.batchQueue.slice();
            this.batchQueue = [];
            queue.forEach(update => update());
        }
    };
    
    // 导出全局函数
    window.createState = StateManager.createState.bind(StateManager);
    window.updateState = StateManager.updateState.bind(StateManager);
    window.batchUpdate = StateManager.batchUpdate.bind(StateManager);
    
})(window);