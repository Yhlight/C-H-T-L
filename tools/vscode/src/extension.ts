import * as vscode from 'vscode';
import * as path from 'path';
import { LanguageClient, LanguageClientOptions, ServerOptions } from 'vscode-languageclient/node';

let client: LanguageClient;

export function activate(context: vscode.ExtensionContext) {
    console.log('CHTL extension is now active!');

    // 注册编译命令
    const compileCommand = vscode.commands.registerCommand('chtl.compile', () => {
        compileCHTL();
    });

    // 注册格式化命令
    const formatCommand = vscode.commands.registerCommand('chtl.format', () => {
        formatDocument();
    });

    // 注册预览命令
    const previewCommand = vscode.commands.registerCommand('chtl.showPreview', () => {
        showPreview();
    });

    // 注册项目生成命令
    const generateCommand = vscode.commands.registerCommand('chtl.generateProject', () => {
        generateProject();
    });

    // 启动语言服务器
    startLanguageServer(context);

    // 注册自动完成提供器
    const completionProvider = vscode.languages.registerCompletionItemProvider(
        'chtl',
        new CHTLCompletionProvider(),
        '[', '@', '.', ' '
    );

    // 注册悬停提供器
    const hoverProvider = vscode.languages.registerHoverProvider(
        'chtl',
        new CHTLHoverProvider()
    );

    // 注册诊断提供器
    const diagnosticCollection = vscode.languages.createDiagnosticCollection('chtl');
    
    // 注册文档符号提供器
    const symbolProvider = vscode.languages.registerDocumentSymbolProvider(
        'chtl',
        new CHTLSymbolProvider()
    );

    context.subscriptions.push(
        compileCommand,
        formatCommand,
        previewCommand,
        generateCommand,
        completionProvider,
        hoverProvider,
        diagnosticCollection,
        symbolProvider
    );

    // 监听文档变化
    vscode.workspace.onDidChangeTextDocument(event => {
        if (event.document.languageId === 'chtl') {
            updateDiagnostics(event.document, diagnosticCollection);
        }
    });
}

export function deactivate(): Thenable<void> | undefined {
    if (!client) {
        return undefined;
    }
    return client.stop();
}

// 编译CHTL文件
async function compileCHTL() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'chtl') {
        vscode.window.showErrorMessage('No CHTL file is currently open');
        return;
    }

    const document = editor.document;
    await document.save();

    const compilerPath = vscode.workspace.getConfiguration('chtl').get<string>('compiler.path', 'chtl');
    const terminal = vscode.window.createTerminal('CHTL Compiler');
    terminal.show();
    terminal.sendText(`${compilerPath} "${document.fileName}"`);
}

// 格式化文档
async function formatDocument() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'chtl') {
        return;
    }

    // TODO: 实现格式化逻辑
    vscode.window.showInformationMessage('CHTL formatting is not yet implemented');
}

// 显示预览
async function showPreview() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'chtl') {
        return;
    }

    // 创建预览面板
    const panel = vscode.window.createWebviewPanel(
        'chtlPreview',
        'CHTL Preview',
        vscode.ViewColumn.Two,
        {
            enableScripts: true,
            retainContextWhenHidden: true
        }
    );

    // TODO: 实现预览逻辑
    panel.webview.html = getPreviewHtml('Preview coming soon...');
}

// 生成项目
async function generateProject() {
    const projectName = await vscode.window.showInputBox({
        prompt: 'Enter project name',
        placeHolder: 'my-chtl-project'
    });

    if (!projectName) {
        return;
    }

    const folderUri = await vscode.window.showOpenDialog({
        canSelectFolders: true,
        canSelectFiles: false,
        openLabel: 'Select Project Location'
    });

    if (!folderUri || folderUri.length === 0) {
        return;
    }

    // TODO: 实现项目生成逻辑
    vscode.window.showInformationMessage(`Project ${projectName} will be created`);
}

// 启动语言服务器
function startLanguageServer(context: vscode.ExtensionContext) {
    const serverModule = context.asAbsolutePath(
        path.join('out', 'server', 'server.js')
    );

    const serverOptions: ServerOptions = {
        run: { module: serverModule },
        debug: { module: serverModule }
    };

    const clientOptions: LanguageClientOptions = {
        documentSelector: [{ scheme: 'file', language: 'chtl' }],
        synchronize: {
            fileEvents: vscode.workspace.createFileSystemWatcher('**/*.chtl')
        }
    };

    client = new LanguageClient(
        'chtlLanguageServer',
        'CHTL Language Server',
        serverOptions,
        clientOptions
    );

    client.start();
}

// 自动完成提供器
class CHTLCompletionProvider implements vscode.CompletionItemProvider {
    provideCompletionItems(
        document: vscode.TextDocument,
        position: vscode.Position,
        token: vscode.CancellationToken,
        context: vscode.CompletionContext
    ): vscode.ProviderResult<vscode.CompletionItem[]> {
        const completions: vscode.CompletionItem[] = [];

        // 关键字补全
        if (context.triggerCharacter === '[') {
            completions.push(
                this.createKeywordItem('Template', 'Define a template'),
                this.createKeywordItem('Custom', 'Define a custom element'),
                this.createKeywordItem('Import', 'Import a module'),
                this.createKeywordItem('Namespace', 'Define a namespace'),
                this.createKeywordItem('Origin', 'Embed raw content')
            );
        }

        // 类型补全
        if (context.triggerCharacter === '@') {
            completions.push(
                this.createTypeItem('Element', 'Element template'),
                this.createTypeItem('Style', 'Style template'),
                this.createTypeItem('Var', 'Variable group'),
                this.createTypeItem('Html', 'HTML import'),
                this.createTypeItem('JavaScript', 'JavaScript import'),
                this.createTypeItem('Module', 'Module import')
            );
        }

        return completions;
    }

    private createKeywordItem(label: string, detail: string): vscode.CompletionItem {
        const item = new vscode.CompletionItem(label, vscode.CompletionItemKind.Keyword);
        item.detail = detail;
        item.insertText = `[${label}] `;
        return item;
    }

    private createTypeItem(label: string, detail: string): vscode.CompletionItem {
        const item = new vscode.CompletionItem(label, vscode.CompletionItemKind.Class);
        item.detail = detail;
        item.insertText = `@${label} `;
        return item;
    }
}

// 悬停提供器
class CHTLHoverProvider implements vscode.HoverProvider {
    provideHover(
        document: vscode.TextDocument,
        position: vscode.Position,
        token: vscode.CancellationToken
    ): vscode.ProviderResult<vscode.Hover> {
        const range = document.getWordRangeAtPosition(position);
        const word = document.getText(range);

        // TODO: 实现智能悬停
        const hoverText = new vscode.MarkdownString();
        hoverText.appendMarkdown(`**CHTL**: ${word}`);

        return new vscode.Hover(hoverText, range);
    }
}

// 符号提供器
class CHTLSymbolProvider implements vscode.DocumentSymbolProvider {
    provideDocumentSymbols(
        document: vscode.TextDocument,
        token: vscode.CancellationToken
    ): vscode.ProviderResult<vscode.DocumentSymbol[]> {
        const symbols: vscode.DocumentSymbol[] = [];

        // TODO: 实现符号解析
        const text = document.getText();
        const templateRegex = /\[Template\]\s*@(\w+)\s+(\w+)/g;
        
        let match;
        while ((match = templateRegex.exec(text)) !== null) {
            const position = document.positionAt(match.index);
            const range = new vscode.Range(position, position);
            
            const symbol = new vscode.DocumentSymbol(
                match[2],
                match[1],
                vscode.SymbolKind.Class,
                range,
                range
            );
            
            symbols.push(symbol);
        }

        return symbols;
    }
}

// 更新诊断信息
function updateDiagnostics(
    document: vscode.TextDocument,
    diagnosticCollection: vscode.DiagnosticCollection
): void {
    if (document.languageId !== 'chtl') {
        return;
    }

    const diagnostics: vscode.Diagnostic[] = [];

    // TODO: 实现语法检查
    const text = document.getText();
    const lines = text.split('\n');

    lines.forEach((line, i) => {
        // 检查未闭合的括号
        const openBrackets = (line.match(/\[/g) || []).length;
        const closeBrackets = (line.match(/\]/g) || []).length;
        
        if (openBrackets !== closeBrackets) {
            const diagnostic = new vscode.Diagnostic(
                new vscode.Range(i, 0, i, line.length),
                'Unmatched brackets',
                vscode.DiagnosticSeverity.Error
            );
            diagnostics.push(diagnostic);
        }
    });

    diagnosticCollection.set(document.uri, diagnostics);
}

// 获取预览HTML
function getPreviewHtml(content: string): string {
    return `
        <!DOCTYPE html>
        <html>
        <head>
            <meta charset="UTF-8">
            <style>
                body {
                    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
                    padding: 20px;
                    line-height: 1.6;
                }
            </style>
        </head>
        <body>
            ${content}
        </body>
        </html>
    `;
}