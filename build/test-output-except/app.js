// CHTL JS Runtime Environment
(function(window) {
  'use strict';
  
  // Initialize CHTL namespace
  window.CHTL = window.CHTL || {};
  window.CHTL.runtime = window.CHTL.runtime || {};
  
  // Event delegation function
  window.CHTL.delegate = function(parentSelector, config) {
    const parent = typeof parentSelector === 'string' ? 
      document.querySelector(parentSelector) : parentSelector;
    
    if (!parent) {
      console.warn('Parent element not found:', parentSelector);
      return;
    }
    
    // Normalize target selectors
    const targetSelectors = Array.isArray(config.target) ? 
      config.target : [config.target];
    
    // Get event handlers
    const events = Object.keys(config).filter(key => key !== 'target');
    
    // Create delegation key for deduplication
    const delegationKey = parentSelector + '::' + targetSelectors.join(',');
    
    // Check if delegation already exists
    parent.__delegations = parent.__delegations || {};
    
    events.forEach(eventType => {
      const eventKey = delegationKey + '::' + eventType;
      
      // Skip if already delegated
      if (parent.__delegations[eventKey]) return;
      
      // Create delegated handler
      const handler = function(e) {
        let target = e.target;
        
        // Walk up the DOM tree
        while (target && target !== parent) {
          // Check if target matches any selector
          for (const selector of targetSelectors) {
            if (target.matches(selector)) {
              // Call handler with correct context
              config[eventType].call(target, e);
              return;
            }
          }
          target = target.parentElement;
        }
      };
      
      // Add event listener
      parent.addEventListener(eventType, handler);
      parent.__delegations[eventKey] = handler;
    });
  };
  
  // Enhanced listen method for quick event binding
  function addListenMethod(element) {
    if (!element || typeof element !== 'object') return element;
    
    // Add listen method if not exists
    if (!element.listen) {
      element.listen = function(events) {
        for (const [eventType, handler] of Object.entries(events)) {
          if (typeof handler === 'function') {
            this.addEventListener(eventType, handler);
          }
        }
        return this;
      };
    }
    
    // Add to NodeList
    if (element instanceof NodeList) {
      element.listen = function(events) {
        this.forEach(el => addListenMethod(el).listen(events));
        return this;
      };
    }
    
    return element;
  }
  
  // Enhanced animate method
  window.CHTL.animate = function(config) {
    const {
      duration = 1000,
      easing = 'ease-in-out',
      begin = {},
      end = {},
      when = [],
      loop = 1,
      direction = 'normal',
      delay = 0,
      callback,
      target
    } = config;
    
    if (!target) {
      console.error('Animation target not specified');
      return;
    }
    
    let startTime = null;
    let currentLoop = 0;
    let animationId = null;
    
    // Easing functions
    const easings = {
      'linear': t => t,
      'ease-in': t => t * t,
      'ease-out': t => t * (2 - t),
      'ease-in-out': t => t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t
    };
    
    const easingFunc = easings[easing] || easings['linear'];
    
    // Apply styles
    function applyStyles(element, styles) {
      Object.entries(styles).forEach(([prop, value]) => {
        if (prop === 'transform') {
          element.style.transform = value;
        } else {
          element.style[prop] = value;
        }
      });
    }
    
    // Interpolate values
    function interpolate(from, to, progress) {
      if (typeof from === 'number' && typeof to === 'number') {
        return from + (to - from) * progress;
      }
      return progress < 0.5 ? from : to;
    }
    
    // Animation frame
    function animate(timestamp) {
      if (!startTime) {
        startTime = timestamp - delay;
        applyStyles(target, begin);
      }
      
      const elapsed = timestamp - startTime - delay;
      if (elapsed < 0) {
        animationId = requestAnimationFrame(animate);
        return;
      }
      
      let progress = Math.min(elapsed / duration, 1);
      if (direction === 'reverse') progress = 1 - progress;
      
      const easedProgress = easingFunc(progress);
      
      // Apply keyframes
      const currentKeyframe = when.find(kf => kf.at >= easedProgress) || { ...end, at: 1 };
      const prevKeyframe = when.filter(kf => kf.at < easedProgress).pop() || { ...begin, at: 0 };
      
      const keyframeProgress = (easedProgress - prevKeyframe.at) / (currentKeyframe.at - prevKeyframe.at);
      
      // Interpolate and apply styles
      const interpolatedStyles = {};
      Object.keys({...prevKeyframe, ...currentKeyframe}).forEach(key => {
        if (key !== 'at' && prevKeyframe[key] !== undefined && currentKeyframe[key] !== undefined) {
          interpolatedStyles[key] = interpolate(prevKeyframe[key], currentKeyframe[key], keyframeProgress);
        }
      });
      
      applyStyles(target, interpolatedStyles);
      
      // Check if animation is complete
      if (progress >= 1) {
        currentLoop++;
        if (loop === -1 || currentLoop < loop) {
          startTime = timestamp;
          if (direction === 'alternate') {
            direction = direction === 'normal' ? 'reverse' : 'normal';
          }
          animationId = requestAnimationFrame(animate);
        } else {
          applyStyles(target, end);
          if (callback) callback();
        }
      } else {
        animationId = requestAnimationFrame(animate);
      }
    }
    
    animationId = requestAnimationFrame(animate);
    
    // Return control object
    return {
      stop: () => {
        if (animationId) {
          cancelAnimationFrame(animationId);
          animationId = null;
        }
      }
    };
  };
  
  // Enhance native methods
  const originalGetElementById = document.getElementById;
  document.getElementById = function(...args) {
    const element = originalGetElementById.apply(document, args);
    return addListenMethod(element);
  };
  
  const originalGetElementsByClassName = document.getElementsByClassName;
  document.getElementsByClassName = function(...args) {
    const elements = originalGetElementsByClassName.apply(document, args);
    return addListenMethod(elements);
  };
  
  const originalGetElementsByTagName = document.getElementsByTagName;
  document.getElementsByTagName = function(...args) {
    const elements = originalGetElementsByTagName.apply(document, args);
    return addListenMethod(elements);
  };
  
  const originalQuerySelector = document.querySelector;
  document.querySelector = function(...args) {
    const element = originalQuerySelector.apply(document, args);
    return addListenMethod(element);
  };
  
  const originalQuerySelectorAll = document.querySelectorAll;
  document.querySelectorAll = function(...args) {
    const elements = originalQuerySelectorAll.apply(document, args);
    return addListenMethod(elements);
  };
  
  // Selector helper function
  window.CHTL.$ = function(selector) {
    if (typeof selector === 'string') {
      return document.querySelector(selector);
    }
    return selector;
  };
  
  window.CHTL.$$ = function(selector) {
    if (typeof selector === 'string') {
      return document.querySelectorAll(selector);
    }
    return selector;
  };
  
})(window);


