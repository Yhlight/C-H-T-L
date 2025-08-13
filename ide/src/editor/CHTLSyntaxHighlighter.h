#ifndef CHTL_IDE_SYNTAX_HIGHLIGHTER_H
#define CHTL_IDE_SYNTAX_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <vector>

namespace chtl {
namespace ide {

class CHTLSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit CHTLSyntaxHighlighter(QTextDocument* parent = nullptr);
    
    // 设置主题
    enum Theme {
        Light,
        Dark,
        Chtholly  // 珂朵莉主题
    };
    
    void setTheme(Theme theme);
    Theme theme() const { return m_theme; }

protected:
    void highlightBlock(const QString& text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    
    void setupFormats();
    void setupRules();
    void applyTheme();
    
    // 处理多行注释
    void highlightMultilineComment(const QString& text);
    
    // 处理嵌套块
    void highlightNestedBlocks(const QString& text);
    
    // 格式
    QTextCharFormat m_keywordFormat;
    QTextCharFormat m_elementFormat;
    QTextCharFormat m_attributeFormat;
    QTextCharFormat m_valueFormat;
    QTextCharFormat m_stringFormat;
    QTextCharFormat m_numberFormat;
    QTextCharFormat m_commentFormat;
    QTextCharFormat m_generativeCommentFormat;
    QTextCharFormat m_templateFormat;
    QTextCharFormat m_customFormat;
    QTextCharFormat m_importFormat;
    QTextCharFormat m_namespaceFormat;
    QTextCharFormat m_styleFormat;
    QTextCharFormat m_scriptFormat;
    QTextCharFormat m_selectorFormat;
    QTextCharFormat m_propertyFormat;
    QTextCharFormat m_functionFormat;
    QTextCharFormat m_variableFormat;
    QTextCharFormat m_originFormat;
    
    // 规则
    std::vector<HighlightingRule> m_highlightingRules;
    
    // 多行注释
    QRegularExpression m_commentStartExpression;
    QRegularExpression m_commentEndExpression;
    
    // 状态
    Theme m_theme;
    
    enum BlockState {
        Normal = 0,
        InComment = 1,
        InStyle = 2,
        InScript = 3,
        InOrigin = 4,
        InTemplate = 5,
        InCustom = 6
    };
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_SYNTAX_HIGHLIGHTER_H