import * as vscode from 'vscode';

export class CHTLFormatter implements vscode.DocumentFormattingEditProvider {
    private indentSize: number = 4;
    private useSpaces: boolean = true;

    constructor() {
        const config = vscode.workspace.getConfiguration('editor');
        this.indentSize = config.get('tabSize', 4);
        this.useSpaces = config.get('insertSpaces', true);
    }

    provideDocumentFormattingEdits(
        document: vscode.TextDocument,
        options: vscode.FormattingOptions,
        token: vscode.CancellationToken
    ): vscode.ProviderResult<vscode.TextEdit[]> {
        const edits: vscode.TextEdit[] = [];
        const text = document.getText();
        const formatted = this.formatCHTL(text);
        
        const fullRange = new vscode.Range(
            document.positionAt(0),
            document.positionAt(text.length)
        );
        
        if (formatted !== text) {
            edits.push(vscode.TextEdit.replace(fullRange, formatted));
        }
        
        return edits;
    }

    private formatCHTL(text: string): string {
        const lines = text.split('\n');
        const formattedLines: string[] = [];
        let indentLevel = 0;
        let inComment = false;
        let inString = false;
        let stringChar = '';

        for (const line of lines) {
            const trimmed = line.trim();
            
            // 跳过空行
            if (trimmed === '') {
                formattedLines.push('');
                continue;
            }
            
            // 处理多行注释
            if (trimmed.startsWith('/*') && !trimmed.endsWith('*/')) {
                inComment = true;
            }
            if (inComment) {
                formattedLines.push(this.indent(indentLevel) + trimmed);
                if (trimmed.endsWith('*/')) {
                    inComment = false;
                }
                continue;
            }
            
            // 处理单行注释
            if (trimmed.startsWith('//') || trimmed.startsWith('--')) {
                formattedLines.push(this.indent(indentLevel) + trimmed);
                continue;
            }
            
            // 计算缩进变化
            const openBraces = this.countChar(trimmed, '{');
            const closeBraces = this.countChar(trimmed, '}');
            
            // 处理右大括号
            if (trimmed.startsWith('}')) {
                indentLevel = Math.max(0, indentLevel - 1);
            }
            
            // 格式化行
            let formattedLine = this.formatLine(trimmed, indentLevel);
            formattedLines.push(formattedLine);
            
            // 更新缩进级别
            if (!this.isInString(trimmed)) {
                indentLevel += openBraces - closeBraces;
                if (trimmed.startsWith('}')) {
                    indentLevel = Math.max(0, indentLevel + 1);
                }
            }
        }
        
        return formattedLines.join('\n');
    }

    private formatLine(line: string, indentLevel: number): string {
        const indent = this.indent(indentLevel);
        
        // 特殊块格式化
        if (line.match(/^\[(Template|Custom|Configuration|Import|Export|Info|Origin|Namespace)\]/)) {
            return indent + line;
        }
        
        // 属性格式化 - 确保冒号/等号两边有空格
        if (line.includes(':') || line.includes('=')) {
            line = line.replace(/\s*[:=]\s*/, (match) => {
                const op = match.includes(':') ? ':' : '=';
                return ` ${op} `;
            });
        }
        
        // 删除操作格式化
        if (line.startsWith('delete ')) {
            line = this.formatDeleteStatement(line);
        }
        
        // 插入操作格式化
        if (line.startsWith('insert ')) {
            line = this.formatInsertStatement(line);
        }
        
        // 引用格式化
        if (line.match(/^@(Style|Element|Var)\s+/)) {
            line = this.formatReference(line);
        }
        
        // 确保分号前没有空格
        if (line.endsWith(';')) {
            line = line.replace(/\s*;$/, ';');
        }
        
        return indent + line;
    }

    private formatDeleteStatement(line: string): string {
        // delete line-height, border; -> delete line-height, border;
        return line.replace(/,\s*/g, ', ');
    }

    private formatInsertStatement(line: string): string {
        // insert after div[0] { -> insert after div[0] {
        return line.replace(/\s+/g, ' ');
    }

    private formatReference(line: string): string {
        // @Style Button; -> @Style Button;
        return line.replace(/\s+/g, ' ');
    }

    private countChar(str: string, char: string): number {
        let count = 0;
        let inString = false;
        let stringChar = '';
        
        for (let i = 0; i < str.length; i++) {
            if ((str[i] === '"' || str[i] === "'") && (i === 0 || str[i-1] !== '\\')) {
                if (!inString) {
                    inString = true;
                    stringChar = str[i];
                } else if (str[i] === stringChar) {
                    inString = false;
                }
            }
            
            if (!inString && str[i] === char) {
                count++;
            }
        }
        
        return count;
    }

    private isInString(line: string): boolean {
        let inString = false;
        let stringChar = '';
        
        for (let i = 0; i < line.length; i++) {
            if ((line[i] === '"' || line[i] === "'") && (i === 0 || line[i-1] !== '\\')) {
                if (!inString) {
                    inString = true;
                    stringChar = line[i];
                } else if (line[i] === stringChar) {
                    inString = false;
                }
            }
        }
        
        return inString;
    }

    private indent(level: number): string {
        const char = this.useSpaces ? ' ' : '\t';
        const size = this.useSpaces ? this.indentSize : 1;
        return char.repeat(size * level);
    }
}