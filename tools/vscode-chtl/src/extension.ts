import * as vscode from 'vscode';
import * as path from 'path';
import { LanguageClient, LanguageClientOptions, ServerOptions, TransportKind } from 'vscode-languageclient/node';
import { CHTLCompletionProvider } from './completion';
import { CHTLHoverProvider } from './hover';
import { CHTLDiagnosticsProvider } from './diagnostics';
import { CHTLFormatter } from './formatter';

let client: LanguageClient;

export function activate(context: vscode.ExtensionContext) {
    console.log('CHTL extension is now active!');

    // 注册命令
    registerCommands(context);

    // 注册语言特性
    registerLanguageFeatures(context);

    // 启动语言服务器
    startLanguageServer(context);

    // 注册文件监听
    registerFileWatchers(context);
}

function registerCommands(context: vscode.ExtensionContext) {
    // 编译当前文件
    context.subscriptions.push(
        vscode.commands.registerCommand('chtl.compile', async () => {
            const editor = vscode.window.activeTextEditor;
            if (!editor || editor.document.languageId !== 'chtl') {
                vscode.window.showErrorMessage('No CHTL file is currently active');
                return;
            }

            const document = editor.document;
            await document.save();

            const terminal = vscode.window.createTerminal('CHTL Compiler');
            const compilerPath = vscode.workspace.getConfiguration('chtl').get<string>('compiler.path', 'chtl');
            const outputDir = vscode.workspace.getConfiguration('chtl').get<string>('compiler.outputDirectory', './dist');
            
            terminal.sendText(`${compilerPath} compile "${document.fileName}" -o "${outputDir}"`);
            terminal.show();
        })
    );

    // 预览在浏览器中
    context.subscriptions.push(
        vscode.commands.registerCommand('chtl.preview', async () => {
            const editor = vscode.window.activeTextEditor;
            if (!editor || editor.document.languageId !== 'chtl') {
                vscode.window.showErrorMessage('No CHTL file is currently active');
                return;
            }

            // 先编译
            await vscode.commands.executeCommand('chtl.compile');
            
            // 然后在浏览器中打开
            const outputDir = vscode.workspace.getConfiguration('chtl').get<string>('compiler.outputDirectory', './dist');
            const htmlFile = path.join(outputDir, 'index.html');
            vscode.env.openExternal(vscode.Uri.file(htmlFile));
        })
    );

    // 创建新组件
    context.subscriptions.push(
        vscode.commands.registerCommand('chtl.createComponent', async () => {
            const componentName = await vscode.window.showInputBox({
                prompt: 'Enter component name',
                placeHolder: 'MyComponent'
            });

            if (!componentName) return;

            const componentType = await vscode.window.showQuickPick(['Template', 'Custom'], {
                placeHolder: 'Select component type'
            });

            if (!componentType) return;

            const content = generateComponentTemplate(componentName, componentType);
            const document = await vscode.workspace.openTextDocument({
                language: 'chtl',
                content
            });
            await vscode.window.showTextDocument(document);
        })
    );

    // 导入 CJmod 模块
    context.subscriptions.push(
        vscode.commands.registerCommand('chtl.importCJmod', async () => {
            const modules = await getCJmodModules();
            const selected = await vscode.window.showQuickPick(modules, {
                placeHolder: 'Select a CJmod module to import'
            });

            if (!selected) return;

            const editor = vscode.window.activeTextEditor;
            if (!editor) return;

            const importStatement = `[Import] @CJmod from "${selected}";\n\n`;
            await editor.edit(editBuilder => {
                editBuilder.insert(new vscode.Position(0, 0), importStatement);
            });
        })
    );
}

function registerLanguageFeatures(context: vscode.ExtensionContext) {
    // 智能提示
    const completionProvider = new CHTLCompletionProvider();
    context.subscriptions.push(
        vscode.languages.registerCompletionItemProvider('chtl', completionProvider, '.', '@', '#', ':', '[', '{')
    );

    // 悬停提示
    const hoverProvider = new CHTLHoverProvider();
    context.subscriptions.push(
        vscode.languages.registerHoverProvider('chtl', hoverProvider)
    );

    // 诊断（错误检查）
    const diagnosticsProvider = new CHTLDiagnosticsProvider();
    context.subscriptions.push(diagnosticsProvider);

    // 格式化
    const formatter = new CHTLFormatter();
    context.subscriptions.push(
        vscode.languages.registerDocumentFormattingEditProvider('chtl', formatter)
    );

    // 代码动作（快速修复）
    context.subscriptions.push(
        vscode.languages.registerCodeActionsProvider('chtl', {
            provideCodeActions(document, range, context) {
                const actions: vscode.CodeAction[] = [];

                // 添加缺失的导入
                for (const diagnostic of context.diagnostics) {
                    if (diagnostic.code === 'missing-import') {
                        const action = new vscode.CodeAction(
                            'Add missing import',
                            vscode.CodeActionKind.QuickFix
                        );
                        action.edit = new vscode.WorkspaceEdit();
                        action.edit.insert(document.uri, new vscode.Position(0, 0), 
                            `[Import] @CJmod from "${diagnostic.data.module}";\n`);
                        actions.push(action);
                    }
                }

                return actions;
            }
        })
    );
}

function startLanguageServer(context: vscode.ExtensionContext) {
    // 语言服务器路径
    const serverModule = context.asAbsolutePath(
        path.join('out', 'server', 'server.js')
    );

    const debugOptions = { execArgv: ['--nolazy', '--inspect=6009'] };

    const serverOptions: ServerOptions = {
        run: { module: serverModule, transport: TransportKind.ipc },
        debug: {
            module: serverModule,
            transport: TransportKind.ipc,
            options: debugOptions
        }
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

function registerFileWatchers(context: vscode.ExtensionContext) {
    // 监听 .cjmod 文件变化
    const cjmodWatcher = vscode.workspace.createFileSystemWatcher('**/*.cjmod');
    
    cjmodWatcher.onDidCreate(uri => {
        vscode.window.showInformationMessage(`New CJmod module detected: ${path.basename(uri.fsPath)}`);
    });

    context.subscriptions.push(cjmodWatcher);
}

function generateComponentTemplate(name: string, type: string): string {
    return `[${type}] @Element ${name} {
    -- Component properties
    props: {
        title: "string"
        onClick: "function"
    }
    
    -- Component content
    div .${name.toLowerCase()}-container {
        h2 { {{&}}.props.title }
        
        button {
            "Click me"
            onclick: {{&}}.props.onClick
        }
    }
    
    -- Component styles
    style {
        .${name.toLowerCase()}-container {
            padding: 20px;
            border: 1px solid #ddd;
            border-radius: 8px;
        }
    }
}`;
}

async function getCJmodModules(): Promise<string[]> {
    // 获取可用的 CJmod 模块
    const builtinModules = [
        'builtin:reactive',
        'builtin:animation',
        'builtin:async-flow',
        'builtin:pipeline'
    ];

    // 查找工作区中的 .cjmod 文件
    const files = await vscode.workspace.findFiles('**/*.cjmod', '**/node_modules/**');
    const localModules = files.map(file => `./${path.relative(vscode.workspace.rootPath || '', file.fsPath)}`);

    return [...builtinModules, ...localModules];
}

export function deactivate(): Thenable<void> | undefined {
    if (!client) {
        return undefined;
    }
    return client.stop();
}