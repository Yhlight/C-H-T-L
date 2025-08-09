#ifndef CHTL_GENERATOR_STANDARD_GENERATOR_H
#define CHTL_GENERATOR_STANDARD_GENERATOR_H

#include "Generator/HtmlGenerator.h"

namespace chtl {

/**
 * @brief StandardGenerator - 标准CHTL代码生成器
 * 
 * 这是BasicGenerator的标准实现，基于HtmlGenerator。
 * 生成标准的HTML输出。
 */
class StandardGenerator : public HtmlGenerator {
public:
    // 使用HtmlGenerator的构造函数
    using HtmlGenerator::HtmlGenerator;
    
    virtual ~StandardGenerator() = default;
};

} // namespace chtl

#endif // CHTL_GENERATOR_STANDARD_GENERATOR_H