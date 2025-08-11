import * as vscode from 'vscode';

export class CHTLHoverProvider implements vscode.HoverProvider {
    private keywords: Map<string, string> = new Map([
        // 模板和自定义
        ['[Template]', 'Define a reusable template for @Style, @Element, or @Var'],
        ['[Custom]', 'Define a customizable component that can be specialized when used'],
        
        // 类型
        ['@Style', 'Style definition or reference'],
        ['@Element', 'Element definition or reference'],
        ['@Var', 'Variable group definition or reference'],
        ['@Html', 'HTML origin or import'],
        ['@JavaScript', 'JavaScript origin or import'],
        ['@Chtl', 'CHTL module import'],
        ['@CJmod', 'CHTL JavaScript module import'],
        
        // 特殊块
        ['[Configuration]', 'Configuration block for compiler settings'],
        ['[Import]', 'Import external resources or modules'],
        ['[Export]', 'Export definitions (CMOD only)'],
        ['[Info]', 'Module information (CMOD only)'],
        ['[Origin]', 'Embed raw HTML/CSS/JavaScript code'],
        ['[Namespace]', 'Define a namespace to prevent naming conflicts'],
        
        // 操作
        ['inherit', 'Inherit properties from another definition'],
        ['delete', 'Delete elements, attributes, or properties'],
        ['insert', 'Insert new elements at specified positions'],
        ['except', 'Define constraints to exclude certain elements or types'],
        
        // 位置
        ['before', 'Insert before the target element'],
        ['after', 'Insert after the target element'],
        ['replace', 'Replace the target element'],
        ['at top', 'Insert at the beginning'],
        ['at bottom', 'Insert at the end'],
        
        // 其他
        ['text', 'Define text content'],
        ['style', 'Define styles (inline or block)'],
        ['script', 'Define JavaScript code'],
        ['from', 'Specify import source'],
        ['as', 'Create an alias for imported item']
    ]);

    private htmlTags: Set<string> = new Set([
        'div', 'span', 'p', 'a', 'img', 'ul', 'ol', 'li', 'h1', 'h2', 'h3', 'h4', 'h5', 'h6',
        'header', 'footer', 'main', 'nav', 'section', 'article', 'aside',
        'form', 'input', 'button', 'select', 'option', 'textarea', 'label',
        'table', 'tr', 'td', 'th', 'thead', 'tbody', 'tfoot',
        'video', 'audio', 'canvas', 'svg', 'iframe'
    ]);

    provideHover(
        document: vscode.TextDocument,
        position: vscode.Position,
        token: vscode.CancellationToken
    ): vscode.ProviderResult<vscode.Hover> {
        const range = document.getWordRangeAtPosition(position, /\[?\w+\]?/);
        if (!range) {
            return null;
        }

        const word = document.getText(range);
        
        // 检查是否是关键字
        if (this.keywords.has(word)) {
            const description = this.keywords.get(word)!;
            const markdown = new vscode.MarkdownString();
            markdown.appendMarkdown(`**${word}**\n\n${description}`);
            
            // 添加示例
            markdown.appendMarkdown('\n\n### Example:\n');
            markdown.appendCodeblock(this.getExample(word), 'chtl');
            
            return new vscode.Hover(markdown, range);
        }
        
        // 检查是否是HTML标签
        if (this.htmlTags.has(word)) {
            const markdown = new vscode.MarkdownString();
            markdown.appendMarkdown(`**HTML Element: ${word}**\n\n`);
            markdown.appendMarkdown(`Standard HTML \`<${word}>\` element`);
            
            return new vscode.Hover(markdown, range);
        }
        
        // 检查变量组引用
        const varMatch = word.match(/(\w+)\(/);
        if (varMatch) {
            const varName = varMatch[1];
            const markdown = new vscode.MarkdownString();
            markdown.appendMarkdown(`**Variable Group Function: ${varName}**\n\n`);
            markdown.appendMarkdown(`Reference to @Var ${varName}\n\n`);
            markdown.appendMarkdown(`Usage: \`${varName}(property)\` or \`${varName}(property = value)\``);
            
            return new vscode.Hover(markdown, range);
        }
        
        return null;
    }

    private getExample(keyword: string): string {
        const examples: Record<string, string> = {
            '[Template]': '[Template] @Style Button {\n    background: blue;\n    color: white;\n}',
            '[Custom]': '[Custom] @Element Card {\n    div {\n        class: "card";\n    }\n}',
            '@Style': 'style {\n    @Style Button;\n}',
            '@Element': 'body {\n    @Element Card;\n}',
            '@Var': '[Template] @Var Colors {\n    primary: "#3498db";\n    secondary: "#2ecc71";\n}',
            'inherit': '[Template] @Style ExtendedButton {\n    inherit @Style Button;\n    font-size: 16px;\n}',
            'delete': '@Element Card {\n    delete span;\n    delete div[1];\n}',
            'insert': 'insert after div[0] {\n    span { text { "New" } }\n}',
            'except': 'div {\n    except span, @Html;\n}'
        };
        
        return examples[keyword] || `// Example for ${keyword}`;
    }
}