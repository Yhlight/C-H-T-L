#include "Js/JsBlockExtractor.h"

namespace chtl {

std::vector<std::string> JsBlockExtractor::extractBlocks(const std::string& js) {
    std::vector<std::string> blocks;
    size_t pos = 0;
    
    while (pos < js.length()) {
        // 跳过空白和注释
        while (pos < js.length() && std::isspace(js[pos])) {
            pos++;
        }
        
        if (pos >= js.length()) {
            break;
        }
        
        // 查找块的开始
        size_t blockStart = pos;
        size_t bracePos = js.find('{', pos);
        
        if (bracePos == std::string::npos) {
            // 没有更多的块
            break;
        }
        
        // 查找块的结束
        size_t blockEnd = findBlockEnd(js, bracePos);
        
        if (blockEnd != std::string::npos) {
            std::string block = js.substr(blockStart, blockEnd - blockStart + 1);
            blocks.push_back(block);
            pos = blockEnd + 1;
        } else {
            break;
        }
    }
    
    return blocks;
}

std::vector<std::string> JsBlockExtractor::extractFunctions(const std::string& js) {
    std::vector<std::string> functions;
    size_t pos = 0;
    
    while ((pos = js.find("function", pos)) != std::string::npos) {
        // 确保是独立的function关键字
        if (pos > 0 && (std::isalnum(js[pos - 1]) || js[pos - 1] == '_')) {
            pos++;
            continue;
        }
        
        size_t funcStart = pos;
        
        // 查找函数体
        size_t bracePos = js.find('{', pos);
        if (bracePos != std::string::npos) {
            size_t funcEnd = findBlockEnd(js, bracePos);
            if (funcEnd != std::string::npos) {
                std::string func = js.substr(funcStart, funcEnd - funcStart + 1);
                functions.push_back(func);
                pos = funcEnd + 1;
            } else {
                pos++;
            }
        } else {
            pos++;
        }
    }
    
    // 也提取箭头函数
    pos = 0;
    while ((pos = js.find("=>", pos)) != std::string::npos) {
        // 向前查找函数开始
        size_t funcStart = pos;
        while (funcStart > 0 && js[funcStart - 1] != '\n' && js[funcStart - 1] != ';' && js[funcStart - 1] != '{') {
            funcStart--;
        }
        
        // 向后查找函数结束
        pos += 2;
        while (pos < js.length() && std::isspace(js[pos])) {
            pos++;
        }
        
        if (pos < js.length() && js[pos] == '{') {
            size_t funcEnd = findBlockEnd(js, pos);
            if (funcEnd != std::string::npos) {
                std::string func = js.substr(funcStart, funcEnd - funcStart + 1);
                functions.push_back(func);
                pos = funcEnd + 1;
            }
        } else {
            // 单行箭头函数
            size_t funcEnd = pos;
            while (funcEnd < js.length() && js[funcEnd] != '\n' && js[funcEnd] != ';') {
                funcEnd++;
            }
            std::string func = js.substr(funcStart, funcEnd - funcStart);
            functions.push_back(func);
            pos = funcEnd;
        }
    }
    
    return functions;
}

std::vector<std::string> JsBlockExtractor::extractClasses(const std::string& js) {
    std::vector<std::string> classes;
    size_t pos = 0;
    
    while ((pos = js.find("class", pos)) != std::string::npos) {
        // 确保是独立的class关键字
        if (pos > 0 && (std::isalnum(js[pos - 1]) || js[pos - 1] == '_')) {
            pos++;
            continue;
        }
        
        size_t classStart = pos;
        
        // 查找类体
        size_t bracePos = js.find('{', pos);
        if (bracePos != std::string::npos) {
            size_t classEnd = findBlockEnd(js, bracePos);
            if (classEnd != std::string::npos) {
                std::string cls = js.substr(classStart, classEnd - classStart + 1);
                classes.push_back(cls);
                pos = classEnd + 1;
            } else {
                pos++;
            }
        } else {
            pos++;
        }
    }
    
    return classes;
}

size_t JsBlockExtractor::findBlockEnd(const std::string& js, size_t start) {
    int braceCount = 0;
    size_t pos = start;
    
    while (pos < js.length()) {
        if (!isInString(js, pos) && !isInComment(js, pos)) {
            if (js[pos] == '{') {
                braceCount++;
            } else if (js[pos] == '}') {
                braceCount--;
                if (braceCount == 0) {
                    return pos;
                }
            }
        }
        pos++;
    }
    
    return std::string::npos;
}

bool JsBlockExtractor::isInString(const std::string& js, size_t pos) {
    bool inSingle = false;
    bool inDouble = false;
    bool inTemplate = false;
    
    for (size_t i = 0; i < pos; i++) {
        if (i > 0 && js[i - 1] == '\\') {
            continue;
        }
        
        if (js[i] == '\'' && !inDouble && !inTemplate) {
            inSingle = !inSingle;
        } else if (js[i] == '"' && !inSingle && !inTemplate) {
            inDouble = !inDouble;
        } else if (js[i] == '`' && !inSingle && !inDouble) {
            inTemplate = !inTemplate;
        }
    }
    
    return inSingle || inDouble || inTemplate;
}

bool JsBlockExtractor::isInComment(const std::string& js, size_t pos) {
    // 简单实现：检查单行和多行注释
    for (size_t i = 0; i < pos; i++) {
        if (i + 1 < js.length()) {
            if (js[i] == '/' && js[i + 1] == '/') {
                // 单行注释
                size_t endLine = js.find('\n', i);
                if (endLine == std::string::npos || pos < endLine) {
                    return true;
                }
                i = endLine;
            } else if (js[i] == '/' && js[i + 1] == '*') {
                // 多行注释
                size_t endComment = js.find("*/", i + 2);
                if (endComment == std::string::npos || pos < endComment + 2) {
                    return true;
                }
                i = endComment + 1;
            }
        }
    }
    
    return false;
}

} // namespace chtl