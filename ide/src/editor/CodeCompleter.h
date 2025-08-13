#ifndef CHTL_IDE_CODE_COMPLETER_H
#define CHTL_IDE_CODE_COMPLETER_H

#include <QCompleter>
#include <QStringList>
#include <memory>
#include <unordered_map>
#include <vector>

class QTextCursor;

namespace chtl {
namespace ide {

// 补全项类型
enum class CompletionItemType {
    Keyword,        // 关键字
    Element,        // HTML元素
    Attribute,      // 属性
    Value,          // 值
    Template,       // 模板
    Custom,         // 自定义
    Variable,       // 变量
    Function,       // 函数
    Module,         // 模块
    Snippet         // 代码片段
};

// 补全项
struct CompletionItem {
    QString text;               // 显示文本
    QString insertText;         // 插入文本
    QString detail;             // 详细信息
    QString documentation;      // 文档
    CompletionItemType type;    // 类型
    int priority;               // 优先级（越小越优先）
    QString icon;               // 图标路径
};

class CodeCompleter : public QCompleter
{
    Q_OBJECT

public:
    explicit CodeCompleter(QObject* parent = nullptr);
    ~CodeCompleter();
    
    // 更新补全列表
    void updateCompletions(const QString& prefix, const QTextCursor& cursor);
    
    // 获取选中的补全项
    CompletionItem currentItem() const;
    
    // 设置上下文
    enum Context {
        Global,         // 全局
        InElement,      // 元素内
        InAttribute,    // 属性
        InStyle,        // 样式块
        InScript,       // 脚本块
        InTemplate,     // 模板
        InCustom,       // 自定义
        InImport,       // 导入
        InNamespace     // 命名空间
    };
    
    void setContext(Context context);
    Context context() const { return m_context; }
    
    // 添加自定义补全
    void addCustomCompletion(const CompletionItem& item);
    void clearCustomCompletions();
    
    // 模块支持
    void loadModuleCompletions(const QString& moduleName);
    void clearModuleCompletions();

signals:
    void itemSelected(const CompletionItem& item);

private:
    void initializeBuiltinCompletions();
    void loadKeywords();
    void loadElements();
    void loadAttributes();
    void loadTemplates();
    void loadFunctions();
    void loadSnippets();
    
    // 根据上下文过滤补全项
    std::vector<CompletionItem> filterByContext(const QString& prefix) const;
    
    // 排序补全项
    void sortCompletions(std::vector<CompletionItem>& items) const;
    
    // 创建模型
    void updateModel(const std::vector<CompletionItem>& items);
    
private:
    Context m_context;
    
    // 内置补全项
    std::vector<CompletionItem> m_keywords;
    std::vector<CompletionItem> m_elements;
    std::vector<CompletionItem> m_attributes;
    std::vector<CompletionItem> m_templates;
    std::vector<CompletionItem> m_functions;
    std::vector<CompletionItem> m_snippets;
    
    // 自定义补全项
    std::vector<CompletionItem> m_customCompletions;
    
    // 模块补全项
    std::unordered_map<QString, std::vector<CompletionItem>> m_moduleCompletions;
    
    // 当前补全项列表
    std::vector<CompletionItem> m_currentItems;
    
    // CHTL特定补全
    void initializeCHTLCompletions();
    void initializeCHTLJSCompletions();
};

// 补全项模型（用于自定义显示）
class CompletionItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CompletionItemModel(QObject* parent = nullptr);
    
    void setItems(const std::vector<CompletionItem>& items);
    CompletionItem itemAt(int index) const;
    
    // QAbstractListModel interface
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    
private:
    std::vector<CompletionItem> m_items;
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_CODE_COMPLETER_H