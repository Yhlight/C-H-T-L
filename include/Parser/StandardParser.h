#ifndef CHTL_PARSER_STANDARD_PARSER_H
#define CHTL_PARSER_STANDARD_PARSER_H

#include "Parser/BasicParser.h"
#include <stack>

namespace chtl {

/**
 * @brief StandardParser - 标准CHTL解析器
 * 
 * 这是BasicParser的标准实现，用于解析常规的CHTL代码。
 * 实现了完整的CHTL语法解析功能。
 */
class StandardParser : public BasicParser {
public:
    StandardParser();
    virtual ~StandardParser() = default;

    // 实现纯虚函数
    virtual std::shared_ptr<Node> parse() override;

protected:
    // CHTL特定的解析方法
    std::shared_ptr<Node> parseDocument();
    std::shared_ptr<Node> parseElement();
    std::shared_ptr<Node> parseText();
    std::shared_ptr<Node> parseComment();
    std::shared_ptr<Node> parseTemplate();
    std::shared_ptr<Node> parseCustom();
    std::shared_ptr<Node> parseStyle();
    std::shared_ptr<Node> parseConfig();
    std::shared_ptr<Node> parseImport();
    std::shared_ptr<Node> parseNamespace();
    std::shared_ptr<Node> parseOperate();
    std::shared_ptr<Node> parseOrigin();
    
    // 辅助方法
    std::shared_ptr<Node> parseAttributes();
    bool isStartOfElement();
    bool isStartOfTemplate();
    bool isStartOfCustom();
    bool isStartOfSpecialNode();
    
    // 错误恢复
    void skipToNextElement();
    void skipToClosingTag(const std::string& tagName);
    
private:
    // 解析状态
    std::stack<std::string> elementStack_;  // 跟踪打开的元素
    // TODO: 实现时使用这些标志
    // bool inTemplateMode_ = false;
    // bool inConfigMode_ = false;
};

} // namespace chtl

#endif // CHTL_PARSER_STANDARD_PARSER_H