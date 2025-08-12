# CHTL 动画 API 设计

## 核心概念

CHTL 的动画系统基于 `requestAnimationFrame`，提供了声明式的动画定义方式，让复杂动画变得简单直观。

## API 设计

### 基本用法

```chtl
script {
    // animate 返回一个动画控制器函数
    const slideIn = {{&}}->animate({
        duration: 300,              // 动画持续时间（毫秒）
        easing: 'ease-in-out',      // 缓动函数
        
        begin: {                    // 起始状态
            opacity: 0,
            transform: 'translateX(-100px)'
        },
        
        end: {                      // 结束状态
            opacity: 1,
            transform: 'translateX(0)'
        }
    });
    
    // 使用返回的函数控制动画
    slideIn.play();                 // 播放动画
    slideIn.pause();                // 暂停动画
    slideIn.reverse();              // 反向播放
    slideIn.reset();                // 重置到初始状态
    slideIn.stop();                 // 停止并重置
}
```

### 关键帧动画

```chtl
script {
    const bounce = {{&}}->animate({
        duration: 1000,
        easing: 'linear',
        
        begin: {
            transform: 'translateY(0)'
        },
        
        when: [
            {
                at: 0.2,                    // 20% 时刻
                transform: 'translateY(-30px)',
                easing: 'ease-out'          // 可以为每个关键帧指定缓动
            },
            {
                at: 0.4,                    // 40% 时刻
                transform: 'translateY(0)',
                easing: 'ease-in'
            },
            {
                at: 0.6,
                transform: 'translateY(-15px)',
                easing: 'ease-out'
            },
            {
                at: 0.8,
                transform: 'translateY(0)',
                easing: 'ease-in'
            }
        ],
        
        end: {
            transform: 'translateY(0)'
        }
    });
}
```

### 完整配置选项

```chtl
script {
    const complexAnimation = {{&}}->animate({
        // 基础配置
        duration: 1000,                     // 动画持续时间（毫秒）
        easing: 'cubic-bezier(0.4, 0, 0.2, 1)', // 缓动函数
        
        // 状态定义
        begin: {                            // 起始状态
            opacity: 0,
            transform: 'scale(0.8) rotate(0deg)',
            filter: 'blur(10px)'
        },
        
        when: [                             // 关键帧
            {
                at: 0.5,                    // 时间点（0-1）
                opacity: 0.8,
                transform: 'scale(1.1) rotate(180deg)',
                filter: 'blur(0)',
                easing: 'ease-out'          // 该段的缓动函数
            }
        ],
        
        end: {                              // 结束状态
            opacity: 1,
            transform: 'scale(1) rotate(360deg)',
            filter: 'blur(0)'
        },
        
        // 循环控制
        loop: 3,                            // 循环次数（-1 为无限循环）
        direction: 'alternate',             // 播放方向
                                           // 'normal' | 'reverse' | 'alternate' | 'alternate-reverse'
        
        // 时间控制
        delay: 200,                         // 延迟开始（毫秒）
        endDelay: 100,                      // 结束后延迟（毫秒）
        
        // 回调函数
        onStart: () => {                    // 动画开始时
            console.log('Animation started');
        },
        
        onProgress: (progress) => {         // 动画进行中
            console.log(`Progress: ${progress * 100}%`);
        },
        
        onComplete: () => {                 // 动画完成时
            console.log('Animation completed');
        },
        
        onCancel: () => {                   // 动画被取消时
            console.log('Animation cancelled');
        },
        
        // 高级选项
        composite: 'replace',               // 合成操作
                                           // 'replace' | 'add' | 'accumulate'
        fill: 'both',                      // 填充模式
                                           // 'none' | 'forwards' | 'backwards' | 'both'
        
        // 性能优化
        willChange: ['transform', 'opacity'], // 提示浏览器优化
        useGPU: true                        // 尝试使用 GPU 加速
    });
    
    // 返回的动画控制器
    const controller = complexAnimation;
    
    // 控制方法
    controller.play();                      // 播放
    controller.pause();                     // 暂停
    controller.resume();                    // 恢复
    controller.reverse();                   // 反向
    controller.reset();                     // 重置
    controller.stop();                      // 停止
    controller.seek(0.5);                   // 跳转到 50% 位置
    
    // 属性
    controller.progress;                    // 当前进度（0-1）
    controller.playState;                   // 播放状态
    controller.playbackRate = 2;            // 播放速度
    
    // 链式动画
    controller
        .play()
        .then(() => anotherAnimation.play())
        .then(() => finalAnimation.play());
}
```

### 预设缓动函数

```chtl
script {
    // CHTL 提供常用的缓动函数预设
    const easings = {
        'linear': 'cubic-bezier(0, 0, 1, 1)',
        'ease': 'cubic-bezier(0.25, 0.1, 0.25, 1)',
        'ease-in': 'cubic-bezier(0.42, 0, 1, 1)',
        'ease-out': 'cubic-bezier(0, 0, 0.58, 1)',
        'ease-in-out': 'cubic-bezier(0.42, 0, 0.58, 1)',
        
        // 材质设计缓动
        'material-standard': 'cubic-bezier(0.4, 0, 0.2, 1)',
        'material-decelerate': 'cubic-bezier(0, 0, 0.2, 1)',
        'material-accelerate': 'cubic-bezier(0.4, 0, 1, 1)',
        
        // 弹性缓动
        'elastic-in': 'cubic-bezier(0.6, -0.28, 0.735, 0.045)',
        'elastic-out': 'cubic-bezier(0.175, 0.885, 0.32, 1.275)',
        
        // 回弹缓动
        'back-in': 'cubic-bezier(0.6, -0.28, 0.735, 0.045)',
        'back-out': 'cubic-bezier(0.175, 0.885, 0.32, 1.275)'
    };
}
```

### 组合动画

```chtl
script {
    // 并行动画
    const parallel = {{&}}->animateGroup([
        {
            target: {{.box1}},
            duration: 500,
            begin: { opacity: 0 },
            end: { opacity: 1 }
        },
        {
            target: {{.box2}},
            duration: 500,
            delay: 100,
            begin: { transform: 'translateX(-100px)' },
            end: { transform: 'translateX(0)' }
        }
    ]);
    
    // 序列动画
    const sequence = {{&}}->animateSequence([
        {
            duration: 300,
            begin: { opacity: 0 },
            end: { opacity: 1 }
        },
        {
            duration: 500,
            begin: { transform: 'scale(1)' },
            end: { transform: 'scale(1.2)' }
        }
    ]);
}
```

### 动画工具函数

```chtl
script {
    // 淡入
    const fadeIn = (duration = 300) => {{&}}->animate({
        duration,
        begin: { opacity: 0 },
        end: { opacity: 1 }
    });
    
    // 滑入
    const slideIn = (direction = 'left', distance = 100) => {
        const transforms = {
            left: `translateX(-${distance}px)`,
            right: `translateX(${distance}px)`,
            top: `translateY(-${distance}px)`,
            bottom: `translateY(${distance}px)`
        };
        
        return {{&}}->animate({
            duration: 300,
            easing: 'ease-out',
            begin: {
                opacity: 0,
                transform: transforms[direction]
            },
            end: {
                opacity: 1,
                transform: 'translate(0)'
            }
        });
    };
    
    // 摇晃
    const shake = (intensity = 10) => {{&}}->animate({
        duration: 500,
        when: [
            { at: 0.1, transform: `translateX(-${intensity}px)` },
            { at: 0.2, transform: `translateX(${intensity}px)` },
            { at: 0.3, transform: `translateX(-${intensity}px)` },
            { at: 0.4, transform: `translateX(${intensity}px)` },
            { at: 0.5, transform: `translateX(-${intensity/2}px)` },
            { at: 0.6, transform: `translateX(${intensity/2}px)` },
            { at: 0.7, transform: `translateX(-${intensity/2}px)` },
            { at: 0.8, transform: `translateX(${intensity/2}px)` },
            { at: 0.9, transform: `translateX(0)` }
        ]
    });
}
```

## 实现原理

### 核心实现思路

```javascript
// 内部实现概念
class AnimationController {
    constructor(element, config) {
        this.element = element;
        this.config = config;
        this.startTime = null;
        this.pauseTime = null;
        this.animationId = null;
        this.playState = 'idle';
        this.progress = 0;
        
        // 解析并准备动画属性
        this.prepareAnimation();
    }
    
    play() {
        if (this.playState === 'running') return this;
        
        this.playState = 'running';
        this.startTime = performance.now() - (this.pauseTime || 0);
        
        const animate = (currentTime) => {
            if (this.playState !== 'running') return;
            
            const elapsed = currentTime - this.startTime - this.config.delay;
            const progress = Math.min(elapsed / this.config.duration, 1);
            
            this.progress = this.applyEasing(progress);
            this.updateStyles();
            
            if (progress < 1) {
                this.animationId = requestAnimationFrame(animate);
            } else {
                this.onComplete();
            }
        };
        
        this.animationId = requestAnimationFrame(animate);
        return this;
    }
    
    // ... 其他方法
}
```

## 优势

1. **声明式 API**：清晰直观的配置方式
2. **性能优化**：基于 requestAnimationFrame，自动优化渲染
3. **灵活控制**：完整的播放控制 API
4. **链式调用**：支持 Promise，便于组合动画
5. **类型安全**：可以轻松添加 TypeScript 支持

## 与 CSS 动画的对比

| 特性 | CHTL 动画 | CSS 动画 |
|------|-----------|----------|
| 动态性 | ✅ 完全动态 | ❌ 静态定义 |
| 控制精度 | ✅ 精确控制 | ⚠️ 有限控制 |
| 性能 | ✅ RAF 优化 | ✅ 浏览器优化 |
| 复杂动画 | ✅ 易于实现 | ⚠️ 较为困难 |
| 回调支持 | ✅ 完整支持 | ⚠️ 有限支持 |