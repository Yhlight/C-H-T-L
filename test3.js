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


            CHTL.select('"#myButton"').listen({
                click: function(e) {
                    console.log("Button clicked!");
                    this.style.backgroundColor = "#28a745";
                }
            });
            
            CHTL.select('"#myButton"').animate({
                duration: 300,
                begin: { opacity: 0.8 },
                end: { opacity: 1 },
                easing: "ease-in-out"
            });
        
