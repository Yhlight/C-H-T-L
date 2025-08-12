// CHTL Runtime Support
const CHTL = {
  select: function(selector) {
    if (selector.startsWith('{{') && selector.endsWith('}}')) {
      selector = selector.slice(2, -2).trim();
    }
    const elements = document.querySelectorAll(selector);
    return {
      elements: elements,
      listen: function(event, handler) {
        elements.forEach(el => el.addEventListener(event, handler));
        return this;
      },
      delegate: function(childSelector, event, handler) {
        elements.forEach(el => {
          el.addEventListener(event, function(e) {
            const target = e.target.closest(childSelector);
            if (target && el.contains(target)) {
              handler.call(target, e);
            }
          });
        });
        return this;
      },
      animate: function(options) {
        // Simple animation implementation
        elements.forEach(el => {
          if (options.begin) {
            Object.assign(el.style, options.begin);
          }
          setTimeout(() => {
            el.style.transition = `all ${options.duration || 1000}ms ${options.easing || 'ease'}`;
            if (options.end) {
              Object.assign(el.style, options.end);
            }
          }, options.delay || 0);
        });
        return this;
      }
    };
  }
};


            console.log("CHTL Script loaded");
            
            // CHTL selector and event binding
            CHTL.select('#testButton').listen({
                click: function(e) {
                    console.log("Button clicked!");
                    alert("Hello from CHTL!");
                }
            });
            
            // CHTL animation
            CHTL.select('.feature-box').animate({
                duration: 500,
                begin: { opacity: 0, transform: "translateY(20px)" },
                end: { opacity: 1, transform: "translateY(0)" },
                delay: 100
            });
        
