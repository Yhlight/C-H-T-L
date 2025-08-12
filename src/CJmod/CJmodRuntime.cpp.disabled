#include "CJmod/CJmodCore.h"
#include <sstream>
#include <algorithm>

namespace chtl {
namespace cjmod {

// RuntimeBuilder 实现
std::string RuntimeBuilder::generate() const {
    std::stringstream ss;
    
    // 文件头
    ss << "// CHTL CJmod Runtime - Generated Code\n";
    ss << "(function(window, document) {\n";
    ss << "  'use strict';\n\n";
    
    // 依赖检查
    if (!dependencies_.empty()) {
        ss << "  // Dependencies\n";
        for (const auto& dep : dependencies_) {
            ss << "  if (typeof " << dep << " === 'undefined') {\n";
            ss << "    console.error('CJmod: Missing dependency " << dep << "');\n";
            ss << "  }\n";
        }
        ss << "\n";
    }
    
    // 全局变量
    if (!globals_.empty()) {
        ss << "  // Global Variables\n";
        for (const auto& [name, code] : globals_) {
            ss << "  window." << name << " = " << code << ";\n";
        }
        ss << "\n";
    }
    
    // 函数定义
    if (!functions_.empty()) {
        ss << "  // Functions\n";
        for (const auto& [name, code] : functions_) {
            ss << "  window." << name << " = " << code << ";\n";
        }
        ss << "\n";
    }
    
    // 类定义
    if (!classes_.empty()) {
        ss << "  // Classes\n";
        for (const auto& [name, code] : classes_) {
            ss << code << "\n";
            ss << "  window." << name << " = " << name << ";\n\n";
        }
    }
    
    // 原型扩展
    if (!prototypes_.empty()) {
        ss << "  // Prototype Extensions\n";
        for (const auto& [key, code] : prototypes_) {
            size_t dotPos = key.find('.');
            if (dotPos != std::string::npos) {
                std::string target = key.substr(0, dotPos);
                std::string method = key.substr(dotPos + 1);
                ss << "  if (typeof " << target << " !== 'undefined') {\n";
                ss << "    " << target << ".prototype." << method << " = " << code << ";\n";
                ss << "  }\n";
            }
        }
        ss << "\n";
    }
    
    // 初始化代码
    if (!initCode_.empty()) {
        ss << "  // Initialization\n";
        ss << "  (function() {\n";
        for (const auto& code : initCode_) {
            ss << "    " << code << "\n";
        }
        ss << "  })();\n";
    }
    
    ss << "})(window, document);\n";
    
    return ss.str();
}

} // namespace cjmod
} // namespace chtl