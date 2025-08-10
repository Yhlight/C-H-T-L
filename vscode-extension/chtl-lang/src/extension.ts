import * as vscode from 'vscode';
import * as path from 'path';
import { exec } from 'child_process';
import { promisify } from 'util';
import * as fs from 'fs';

const execAsync = promisify(exec);
const fsAsync = {
    readFile: promisify(fs.readFile),
    writeFile: promisify(fs.writeFile),
    mkdir: promisify(fs.mkdir),
    access: promisify(fs.access)
};

// 扩展激活时调用
export function activate(context: vscode.ExtensionContext) {
    console.log('CHTL extension is now active!');

    // 注册编译命令
    const compileCommand = vscode.commands.registerCommand('chtl.compile', compileCurrentFile);
    context.subscriptions.push(compileCommand);

    // 注册预览命令
    const previewCommand = vscode.commands.registerCommand('chtl.preview', previewInBrowser);
    context.subscriptions.push(previewCommand);

    // 注册创建组件命令
    const createComponentCommand = vscode.commands.registerCommand('chtl.createComponent', createComponent);
    context.subscriptions.push(createComponentCommand);

    // 注册格式化提供程序
    const formatter = vscode.languages.registerDocumentFormattingEditProvider('chtl', {
        provideDocumentFormattingEdits: formatDocument
    });
    context.subscriptions.push(formatter);

    // 注册悬停提供程序
    const hoverProvider = vscode.languages.registerHoverProvider('chtl', {
        provideHover: provideHover
    });
    context.subscriptions.push(hoverProvider);

    // 注册补全提供程序
    const completionProvider = vscode.languages.registerCompletionItemProvider('chtl', {
        provideCompletionItems: provideCompletionItems
    }, '.', '@', '{', '<', ':', '->');
    context.subscriptions.push(completionProvider);

    // 监听文件保存事件
    const saveWatcher = vscode.workspace.onDidSaveTextDocument(async (document) => {
        if (document.languageId === 'chtl') {
            const config = vscode.workspace.getConfiguration('chtl');
            if (config.get('lint.enable')) {
                await lintDocument(document);
            }
        }
    });
    context.subscriptions.push(saveWatcher);

    // 诊断集合
    const diagnosticCollection = vscode.languages.createDiagnosticCollection('chtl');
    context.subscriptions.push(diagnosticCollection);
}

// 编译当前文件
async function compileCurrentFile() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'chtl') {
        vscode.window.showErrorMessage('No CHTL file is currently active');
        return;
    }

    const document = editor.document;
    const filePath = document.fileName;
    const workspaceFolder = vscode.workspace.getWorkspaceFolder(document.uri);
    
    if (!workspaceFolder) {
        vscode.window.showErrorMessage('File is not in a workspace');
        return;
    }

    const config = vscode.workspace.getConfiguration('chtl');
    const compilerPath = config.get<string>('compiler.path') || 'chtl';
    const outputDir = path.join(workspaceFolder.uri.fsPath, 'dist');

    // 确保输出目录存在
    try {
        await fsAsync.access(outputDir);
    } catch {
        await fsAsync.mkdir(outputDir, { recursive: true });
    }

    // 显示进度
    vscode.window.withProgress({
        location: vscode.ProgressLocation.Notification,
        title: "Compiling CHTL file...",
        cancellable: false
    }, async (progress) => {
        try {
            const { stdout, stderr } = await execAsync(
                `${compilerPath} "${filePath}" -o "${outputDir}"`,
                { cwd: workspaceFolder.uri.fsPath }
            );

            if (stderr) {
                vscode.window.showErrorMessage(`Compilation error: ${stderr}`);
            } else {
                vscode.window.showInformationMessage('Compilation successful!');
            }
        } catch (error: any) {
            vscode.window.showErrorMessage(`Compilation failed: ${error.message}`);
        }
    });
}

// 在浏览器中预览
async function previewInBrowser() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'chtl') {
        vscode.window.showErrorMessage('No CHTL file is currently active');
        return;
    }

    // 先编译
    await compileCurrentFile();

    const workspaceFolder = vscode.workspace.getWorkspaceFolder(editor.document.uri);
    if (!workspaceFolder) {
        return;
    }

    const indexPath = path.join(workspaceFolder.uri.fsPath, 'dist', 'index.html');
    
    try {
        await fsAsync.access(indexPath);
        const panel = vscode.window.createWebviewPanel(
            'chtlPreview',
            'CHTL Preview',
            vscode.ViewColumn.Two,
            {
                enableScripts: true,
                localResourceRoots: [vscode.Uri.file(path.join(workspaceFolder.uri.fsPath, 'dist'))]
            }
        );

        const htmlContent = await fsAsync.readFile(indexPath, 'utf8');
        panel.webview.html = htmlContent;
    } catch (error) {
        vscode.window.showErrorMessage('No compiled output found. Please compile first.');
    }
}

// 创建新组件
async function createComponent() {
    const componentName = await vscode.window.showInputBox({
        prompt: 'Enter component name',
        placeHolder: 'MyComponent',
        validateInput: (value) => {
            if (!value || !/^[A-Z][a-zA-Z0-9]*$/.test(value)) {
                return 'Component name must start with uppercase letter';
            }
            return null;
        }
    });

    if (!componentName) {
        return;
    }

    const workspaceFolder = vscode.workspace.workspaceFolders?.[0];
    if (!workspaceFolder) {
        vscode.window.showErrorMessage('No workspace folder found');
        return;
    }

    const componentContent = `// ${componentName} Component
Import @Core from "Chtholly.Core.*"

[Custom] @Element ${componentName} {
    props: {
        // Add your props here
    }
    
    state: {
        // Add your state here
    }
    
    render: {
        div {
            class: "chtl-${componentName.toLowerCase()}"
            
            // Component content
            
            style {
                .chtl-${componentName.toLowerCase()} {
                    // Component styles
                }
            }
        }
    }
}

[Export] {
    @Element ${componentName}
}
`;

    const fileName = `${componentName}.chtl`;
    const filePath = path.join(workspaceFolder.uri.fsPath, 'components', fileName);
    
    try {
        const componentDir = path.dirname(filePath);
        await fsAsync.mkdir(componentDir, { recursive: true });
        await fsAsync.writeFile(filePath, componentContent, 'utf8');
        
        const document = await vscode.workspace.openTextDocument(filePath);
        await vscode.window.showTextDocument(document);
        
        vscode.window.showInformationMessage(`Component ${componentName} created successfully!`);
    } catch (error: any) {
        vscode.window.showErrorMessage(`Failed to create component: ${error.message}`);
    }
}

// 格式化文档
async function formatDocument(document: vscode.TextDocument): Promise<vscode.TextEdit[]> {
    const edits: vscode.TextEdit[] = [];
    const text = document.getText();
    const lines = text.split('\n');
    
    let indentLevel = 0;
    const config = vscode.workspace.getConfiguration('chtl');
    const indentSize = config.get<number>('format.indentSize') || 2;
    const indent = ' '.repeat(indentSize);
    
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        const trimmedLine = line.trim();
        
        // 跳过空行和注释
        if (trimmedLine === '' || trimmedLine.startsWith('//')) {
            continue;
        }
        
        // 减少缩进级别
        if (trimmedLine === '}' || trimmedLine === ']' || trimmedLine.startsWith('}') || trimmedLine.startsWith(']')) {
            indentLevel = Math.max(0, indentLevel - 1);
        }
        
        // 应用缩进
        const currentIndent = indent.repeat(indentLevel);
        const formattedLine = currentIndent + trimmedLine;
        
        if (line !== formattedLine) {
            const range = new vscode.Range(i, 0, i, line.length);
            edits.push(vscode.TextEdit.replace(range, formattedLine));
        }
        
        // 增加缩进级别
        if (trimmedLine.endsWith('{') || trimmedLine.endsWith('[')) {
            indentLevel++;
        }
    }
    
    return edits;
}

// 提供悬停信息
async function provideHover(document: vscode.TextDocument, position: vscode.Position): Promise<vscode.Hover | undefined> {
    const wordRange = document.getWordRangeAtPosition(position);
    if (!wordRange) {
        return undefined;
    }
    
    const word = document.getText(wordRange);
    
    // CHTL关键字说明
    const hoverInfo: { [key: string]: string } = {
        'Import': '导入模块或组件\n\n`Import @Name from "module"`',
        'Export': '导出组件或变量\n\n`[Export] { @Element ComponentName }`',
        'Custom': '定义自定义组件\n\n`[Custom] @Element Name { ... }`',
        'Template': '定义模板函数\n\n`[Template] @Function name() { ... }`',
        'style': '局部样式块\n\n`style { .class { ... } }`',
        'script': '局部脚本块\n\n`script { {{&}}->listen({ ... }) }`',
        'Config': '配置块\n\n`[Config] { title: "Page Title" }`',
        'Info': '模块信息块\n\n`[Info] { name: "ModuleName", version: "1.0.0" }`'
    };
    
    if (hoverInfo[word]) {
        return new vscode.Hover(new vscode.MarkdownString(hoverInfo[word]));
    }
    
    // CHTL JS函数说明
    if (word === 'listen') {
        return new vscode.Hover(new vscode.MarkdownString(
            '绑定事件监听器\n\n```chtl\n{{&}}->listen({\n  click: () => { ... },\n  mouseenter: () => { ... }\n})\n```'
        ));
    }
    
    if (word === 'animate') {
        return new vscode.Hover(new vscode.MarkdownString(
            '创建动画\n\n```chtl\n{{&}}->animate({\n  duration: 300,\n  easing: "ease-out",\n  begin: { opacity: 0 },\n  end: { opacity: 1 }\n})\n```'
        ));
    }
    
    if (word === 'delegate') {
        return new vscode.Hover(new vscode.MarkdownString(
            '事件委托\n\n```chtl\n{{"#parent"}}->delegate({\n  target: ".item",\n  click: function(e) { ... }\n})\n```'
        ));
    }
    
    return undefined;
}

// 提供自动补全
async function provideCompletionItems(
    document: vscode.TextDocument,
    position: vscode.Position,
    token: vscode.CancellationToken,
    context: vscode.CompletionContext
): Promise<vscode.CompletionItem[]> {
    const items: vscode.CompletionItem[] = [];
    
    const linePrefix = document.lineAt(position).text.substr(0, position.character);
    
    // @符号后的补全
    if (linePrefix.endsWith('@')) {
        items.push(
            new vscode.CompletionItem('Element', vscode.CompletionItemKind.Keyword),
            new vscode.CompletionItem('Style', vscode.CompletionItemKind.Keyword),
            new vscode.CompletionItem('Function', vscode.CompletionItemKind.Keyword),
            new vscode.CompletionItem('Var', vscode.CompletionItemKind.Keyword)
        );
    }
    
    // {{后的补全
    if (linePrefix.endsWith('{{')) {
        items.push(
            new vscode.CompletionItem('&', vscode.CompletionItemKind.Variable),
            new vscode.CompletionItem('#id', vscode.CompletionItemKind.Variable),
            new vscode.CompletionItem('.class', vscode.CompletionItemKind.Variable)
        );
    }
    
    // ->后的补全
    if (linePrefix.endsWith('->')) {
        items.push(
            new vscode.CompletionItem('listen', vscode.CompletionItemKind.Method),
            new vscode.CompletionItem('animate', vscode.CompletionItemKind.Method),
            new vscode.CompletionItem('delegate', vscode.CompletionItemKind.Method)
        );
    }
    
    // HTML标签补全
    const htmlTags = ['div', 'span', 'p', 'a', 'button', 'input', 'form', 'ul', 'li', 'h1', 'h2', 'h3'];
    for (const tag of htmlTags) {
        const item = new vscode.CompletionItem(tag, vscode.CompletionItemKind.Property);
        item.insertText = new vscode.SnippetString(`${tag} {\n  $0\n}`);
        items.push(item);
    }
    
    // 属性补全
    if (context.triggerCharacter === ':') {
        const attributes = ['id', 'class', 'style', 'href', 'src', 'type', 'placeholder', 'value'];
        for (const attr of attributes) {
            const item = new vscode.CompletionItem(attr, vscode.CompletionItemKind.Property);
            item.insertText = new vscode.SnippetString(`${attr}: "$0"`);
            items.push(item);
        }
    }
    
    return items;
}

// 检查文档错误
async function lintDocument(document: vscode.TextDocument) {
    const diagnostics: vscode.Diagnostic[] = [];
    const text = document.getText();
    const lines = text.split('\n');
    
    let braceCount = 0;
    let bracketCount = 0;
    
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        
        // 检查大括号匹配
        for (const char of line) {
            if (char === '{') braceCount++;
            if (char === '}') braceCount--;
            if (char === '[') bracketCount++;
            if (char === ']') bracketCount--;
        }
        
        // 检查Import语法
        if (line.includes('Import') && !line.match(/Import\s+@\w+\s+from\s+"[^"]+"/)) {
            const range = new vscode.Range(i, 0, i, line.length);
            diagnostics.push(new vscode.Diagnostic(
                range,
                'Invalid import syntax. Use: Import @Name from "module"',
                vscode.DiagnosticSeverity.Error
            ));
        }
        
        // 检查未闭合的字符串
        const stringMatches = line.match(/"/g);
        if (stringMatches && stringMatches.length % 2 !== 0) {
            const range = new vscode.Range(i, 0, i, line.length);
            diagnostics.push(new vscode.Diagnostic(
                range,
                'Unclosed string literal',
                vscode.DiagnosticSeverity.Error
            ));
        }
    }
    
    // 检查括号是否匹配
    if (braceCount !== 0) {
        diagnostics.push(new vscode.Diagnostic(
            new vscode.Range(0, 0, lines.length - 1, lines[lines.length - 1].length),
            `Unmatched braces: ${braceCount > 0 ? 'missing }' : 'extra }'}`,
            vscode.DiagnosticSeverity.Error
        ));
    }
    
    if (bracketCount !== 0) {
        diagnostics.push(new vscode.Diagnostic(
            new vscode.Range(0, 0, lines.length - 1, lines[lines.length - 1].length),
            `Unmatched brackets: ${bracketCount > 0 ? 'missing ]' : 'extra ]'}`,
            vscode.DiagnosticSeverity.Error
        ));
    }
    
    // 更新诊断
    const diagnosticCollection = vscode.languages.createDiagnosticCollection('chtl');
    diagnosticCollection.set(document.uri, diagnostics);
}

// 扩展停用时调用
export function deactivate() {
    console.log('CHTL extension is now deactivated');
}