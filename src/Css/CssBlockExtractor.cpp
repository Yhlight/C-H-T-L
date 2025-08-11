#include "Css/CssBlockExtractor.h"

namespace chtl {

std::vector<std::string> CssBlockExtractor::extractBlocks(const std::string& css) {
    std::vector<std::string> blocks;
    size_t pos = 0;
    
    while (pos < css.length()) {
        // 跳过空白和注释
        while (pos < css.length() && std::isspace(css[pos])) {
            pos++;
        }
        
        // 跳过注释
        if (pos + 1 < css.length() && css[pos] == '/' && css[pos + 1] == '*') {
            pos = css.find("*/", pos + 2);
            if (pos != std::string::npos) {
                pos += 2;
            } else {
                break;
            }
            continue;
        }
        
        // 查找块的开始
        size_t blockStart = pos;
        size_t bracePos = css.find('{', pos);
        
        if (bracePos == std::string::npos) {
            break;
        }
        
        // 查找块的结束
        size_t blockEnd = findBlockEnd(css, bracePos);
        
        if (blockEnd != std::string::npos) {
            std::string block = css.substr(blockStart, blockEnd - blockStart + 1);
            blocks.push_back(block);
            pos = blockEnd + 1;
        } else {
            break;
        }
    }
    
    return blocks;
}

size_t CssBlockExtractor::findBlockEnd(const std::string& css, size_t start) {
    int braceCount = 0;
    size_t pos = start;
    
    while (pos < css.length()) {
        if (!isInString(css, pos)) {
            if (css[pos] == '{') {
                braceCount++;
            } else if (css[pos] == '}') {
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

bool CssBlockExtractor::isInString(const std::string& css, size_t pos) {
    bool inSingle = false;
    bool inDouble = false;
    
    for (size_t i = 0; i < pos; i++) {
        if (i > 0 && css[i - 1] == '\\') {
            continue;
        }
        
        if (css[i] == '\'' && !inDouble) {
            inSingle = !inSingle;
        } else if (css[i] == '"' && !inSingle) {
            inDouble = !inDouble;
        }
    }
    
    return inSingle || inDouble;
}

} // namespace chtl