#include "CJmod/CJmodInterface.h"
#include "CJmod/CJmodProcessor.h"

namespace chtl {
namespace cjmod {

class AnimateModule : public ICJmod {
public:
    std::string getName() const override {
        return "animate";
    }
    
    std::string getVersion() const override {
        return "1.0.0";
    }
    
    std::string getDescription() const override {
        return "Smooth animations with chaining support";
    }
    
    std::vector<TransformRule> getTransformRules() const override {
        std::vector<TransformRule> rules;
        
        // 动画链语法: element ~> fadeIn(300) ~> slideDown(500)
        rules.push_back({
            "animation-chain",
            std::regex(R"((\w+|\{\{[^}]+\}\})\s*~>\s*(\w+)\s*\()"),
            100,
            [](const std::smatch& match) {
                return match[1].str() + ".animate()." + match[2].str() + "(";
            },
            nullptr
        });
        
        // 并行动画: element ~~ { opacity: 0, height: 0 }
        rules.push_back({
            "parallel-animation",
            std::regex(R"((\w+|\{\{[^}]+\}\})\s*~~\s*\{)"),
            95,
            [](const std::smatch& match) {
                return match[1].str() + ".animateParallel({";
            },
            nullptr
        });
        
        // 延迟语法: delay(500)
        rules.push_back({
            "delay-syntax",
            std::regex(R"(delay\s*\(\s*(\d+)\s*\))"),
            90,
            [](const std::smatch& match) {
                return "await new Promise(r => setTimeout(r, " + match[1].str() + "))";
            },
            nullptr
        });
        
        return rules;
    }
    
    std::vector<MethodInjection> getMethodInjections() const override {
        return {
            {
                "Element",
                "animate",
                R"(function() {
                    const element = this;
                    const queue = [];
                    
                    const animator = {
                        fadeIn(duration = 300) {
                            queue.push(() => new Promise(resolve => {
                                element.style.opacity = '0';
                                element.style.display = 'block';
                                element.style.transition = `opacity ${duration}ms`;
                                
                                requestAnimationFrame(() => {
                                    element.style.opacity = '1';
                                    setTimeout(resolve, duration);
                                });
                            }));
                            return this;
                        },
                        
                        fadeOut(duration = 300) {
                            queue.push(() => new Promise(resolve => {
                                element.style.transition = `opacity ${duration}ms`;
                                element.style.opacity = '0';
                                setTimeout(() => {
                                    element.style.display = 'none';
                                    resolve();
                                }, duration);
                            }));
                            return this;
                        },
                        
                        slideDown(duration = 300) {
                            queue.push(() => new Promise(resolve => {
                                const height = element.scrollHeight;
                                element.style.height = '0';
                                element.style.overflow = 'hidden';
                                element.style.display = 'block';
                                element.style.transition = `height ${duration}ms`;
                                
                                requestAnimationFrame(() => {
                                    element.style.height = height + 'px';
                                    setTimeout(() => {
                                        element.style.height = '';
                                        element.style.overflow = '';
                                        resolve();
                                    }, duration);
                                });
                            }));
                            return this;
                        },
                        
                        slideUp(duration = 300) {
                            queue.push(() => new Promise(resolve => {
                                const height = element.scrollHeight;
                                element.style.height = height + 'px';
                                element.style.overflow = 'hidden';
                                element.style.transition = `height ${duration}ms`;
                                
                                requestAnimationFrame(() => {
                                    element.style.height = '0';
                                    setTimeout(() => {
                                        element.style.display = 'none';
                                        element.style.height = '';
                                        resolve();
                                    }, duration);
                                });
                            }));
                            return this;
                        },
                        
                        async execute() {
                            for (const animation of queue) {
                                await animation();
                            }
                        }
                    };
                    
                    // 自动执行
                    setTimeout(() => animator.execute(), 0);
                    
                    return animator;
                })",
                false
            },
            {
                "Element",
                "animateParallel",
                R"(function(props, duration = 300) {
                    const element = this;
                    const transitions = [];
                    
                    for (const [prop, value] of Object.entries(props)) {
                        transitions.push(`${prop} ${duration}ms`);
                        
                        // 特殊处理
                        if (prop === 'opacity' && value === '0') {
                            setTimeout(() => {
                                element.style.display = 'none';
                            }, duration);
                        }
                    }
                    
                    element.style.transition = transitions.join(', ');
                    
                    requestAnimationFrame(() => {
                        for (const [prop, value] of Object.entries(props)) {
                            element.style[prop] = value;
                        }
                    });
                    
                    return new Promise(resolve => setTimeout(resolve, duration));
                })",
                true
            }
        };
    }
    
    std::vector<OperatorDefinition> getOperatorDefinitions() const override {
        return {};
    }
    
    std::string getRuntimeCode() const override {
        return R"(
  // Animation helpers
  window.AnimationEasing = {
    linear: 'linear',
    easeIn: 'ease-in',
    easeOut: 'ease-out',
    easeInOut: 'ease-in-out'
  };
)";
    }
};

} // namespace cjmod
} // namespace chtl