#ifndef CHTL_IDE_EDITOR_WIDGET_H
#define CHTL_IDE_EDITOR_WIDGET_H

#include <QPlainTextEdit>
#include <QString>
#include <memory>

class QCompleter;
class QMenu;

namespace chtl {
namespace ide {

class CHTLSyntaxHighlighter;
class LineNumberArea;
class CodeCompleter;
class ErrorMarker;
class Document;

class EditorWidget : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit EditorWidget(QWidget* parent = nullptr);
    ~EditorWidget();
    
    // 文档管理
    void newFile();
    bool loadFile(const QString& fileName);
    bool saveFile();
    bool saveAs(const QString& fileName);
    bool isModified() const;
    QString fileName() const { return m_fileName; }
    
    // 编辑功能
    void findText(const QString& text, bool caseSensitive = false, bool wholeWord = false);
    void replaceText(const QString& findText, const QString& replaceText);
    void replaceAll(const QString& findText, const QString& replaceText);
    void goToLine(int line);
    
    // 代码功能
    void formatCode();
    void toggleComment();
    void insertTemplate(const QString& templateName);
    void showAutoComplete();
    
    // 错误标记
    void clearErrors();
    void addError(int line, int column, const QString& message, bool isWarning = false);
    
    // 配置
    void setTheme(const QString& theme);
    void setFontSize(int size);
    void setTabWidth(int width);
    void setShowLineNumbers(bool show);
    void setShowWhitespace(bool show);
    void setWordWrap(bool wrap);
    
    // 行号区域
    int lineNumberAreaWidth();
    void lineNumberAreaPaintEvent(QPaintEvent* event);

signals:
    void fileNameChanged(const QString& fileName);
    void modificationChanged(bool modified);
    void cursorPositionChanged(int line, int column);
    void requestClose();
    
protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);
    void onTextChanged();
    void onCursorPositionChanged();
    void insertCompletion(const QString& completion);
    
private:
    void setupEditor();
    void setupCompleter();
    void createContextMenu();
    void updateTitle();
    
    // 自动补全
    QString textUnderCursor() const;
    void performCompletion();
    
    // 括号匹配
    void matchParentheses();
    bool matchLeftParenthesis(QTextBlock currentBlock, int i, int numLeftParentheses);
    bool matchRightParenthesis(QTextBlock currentBlock, int i, int numRightParentheses);
    void createParenthesisSelection(int pos);
    
    // 智能缩进
    void autoIndent();
    int calculateIndentLevel(const QString& line) const;
    
private:
    QString m_fileName;
    bool m_isUntitled;
    
    // UI组件
    LineNumberArea* m_lineNumberArea;
    std::unique_ptr<CHTLSyntaxHighlighter> m_highlighter;
    std::unique_ptr<CodeCompleter> m_completer;
    std::unique_ptr<ErrorMarker> m_errorMarker;
    
    // 上下文菜单
    QMenu* m_contextMenu;
    
    // 配置
    int m_tabWidth;
    bool m_showLineNumbers;
    bool m_showWhitespace;
    bool m_autoIndent;
    
    // 括号匹配
    QList<QTextEdit::ExtraSelection> m_extraSelections;
    
    // 静态计数器（用于未命名文件）
    static int s_untitledCounter;
};

// 行号区域
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(EditorWidget* editor) : QWidget(editor), m_editor(editor) {}
    
    QSize sizeHint() const override {
        return QSize(m_editor->lineNumberAreaWidth(), 0);
    }
    
protected:
    void paintEvent(QPaintEvent* event) override {
        m_editor->lineNumberAreaPaintEvent(event);
    }
    
private:
    EditorWidget* m_editor;
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_EDITOR_WIDGET_H