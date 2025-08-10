#include "State/ChtlJsState.h"

namespace chtl {

std::shared_ptr<BasicState> ChtlJsState::handleChar(char c) {
    static char prevChar = '\0';
    static char prevPrevChar = '\0';
    
    // 处理模板字符串
    if (c == '`' && prevChar != '\\') {
        if (inTemplateString_) {
            exitTemplateString();
        } else {
            enterTemplateString();
        }
    }
    
    // 在模板字符串中，不处理CHTL语法
    if (!inTemplateString_) {
        // 处理CHTL选择器
        if (c == '{' && prevChar == '{') {
            enterChtlSelector();
        }
        
        if (c == '}' && prevChar == '}' && inChtlSelector_) {
            exitChtlSelector();
        }
        
        // 处理CHTL方法调用
        if (c == '>' && prevChar == '-' && prevPrevChar != '=') {
            enterChtlMethod();
        }
        
        // 处理括号（用于跟踪方法调用结束）
        if (inChtlMethod_) {
            if (c == '(') {
                parenDepth_++;
            } else if (c == ')') {
                parenDepth_--;
                if (parenDepth_ <= 0) {
                    exitChtlMethod();
                    parenDepth_ = 0;
                }
            }
        }
    }
    
    // 更新历史字符
    prevPrevChar = prevChar;
    prevChar = c;
    
    // 返回nullptr表示继续使用当前状态
    return nullptr;
}

bool ChtlJsState::accepts(char c) const {
    (void)c; // CHTL-JS状态接受所有字符
    return true;
}

void ChtlJsState::reset() {
    BasicState::reset();
    inChtlSelector_ = false;
    inChtlMethod_ = false;
    inTemplateString_ = false;
    selectorDepth_ = 0;
    parenDepth_ = 0;
}

} // namespace chtl