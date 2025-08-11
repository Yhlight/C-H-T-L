import * as vscode from 'vscode';
import * as path from 'path';
import * as fs from 'fs';
import { LanguageClient, LanguageClientOptions, ServerOptions, TransportKind } from 'vscode-languageclient/node';
import { CHTLCompletionProvider } from './completion';
import { CHTLHoverProvider } from './hover';
import { CHTLDiagnosticsProvider } from './diagnostics';
import { CHTLFormatter } from './formatter';
import { getAllBuiltinModulesCode, generateBuiltinModulesDeclaration, BUILTIN_MODULES } from './builtinModules';

let client: LanguageClient;

export function activate(context: vscode.ExtensionContext) {
    console.log('CHTL extension is now active!');

    // 初始化内置模块
    initializeBuiltinModules(context);

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

    // 导出内置模块
    context.subscriptions.push(
        vscode.commands.registerCommand('chtl.exportBuiltinModules', async () => {
            const options = await vscode.window.showQuickPick([
                { label: 'Bundle all modules', value: 'bundle' },
                { label: 'Generate type declarations', value: 'types' },
                { label: 'Export individual modules', value: 'individual' }
            ], {
                placeHolder: 'Select export option'
            });

            if (!options) return;

            switch (options.value) {
                case 'bundle':
                    await exportBundledModules(context);
                    break;
                case 'types':
                    await exportTypeDeclarations(context);
                    break;
                case 'individual':
                    await exportIndividualModules(context);
                    break;
            }
        })
    );

    // 显示模块信息
    context.subscriptions.push(
        vscode.commands.registerCommand('chtl.showModuleInfo', async () => {
            const modules = Array.from(BUILTIN_MODULES.keys());
            const selected = await vscode.window.showQuickPick(modules, {
                placeHolder: 'Select a module to view info'
            });

            if (!selected) return;

            const module = BUILTIN_MODULES.get(selected);
            if (!module) return;

            const panel = vscode.window.createWebviewPanel(
                'chtlModuleInfo',
                `CJmod: ${module.name}`,
                vscode.ViewColumn.One,
                {}
            );

            panel.webview.html = generateModuleInfoHTML(module);
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

// 初始化内置模块
function initializeBuiltinModules(context: vscode.ExtensionContext) {
    // 将内置模块存储在扩展的存储空间中
    const modulesPath = path.join(context.extensionPath, 'builtin-modules');
    
    if (!fs.existsSync(modulesPath)) {
        fs.mkdirSync(modulesPath, { recursive: true });
    }

    // 生成内置模块文件
    BUILTIN_MODULES.forEach((module, key) => {
        const moduleFile = path.join(modulesPath, `${key}.json`);
        fs.writeFileSync(moduleFile, JSON.stringify(module, null, 2));
    });

    // 生成打包的 JS 文件
    const bundleFile = path.join(modulesPath, 'chtl-builtin-modules.js');
    fs.writeFileSync(bundleFile, getAllBuiltinModulesCode());

    // 生成类型声明文件
    const typeFile = path.join(modulesPath, 'chtl-builtin-modules.d.ts');
    fs.writeFileSync(typeFile, generateBuiltinModulesDeclaration());

    console.log(`Initialized ${BUILTIN_MODULES.size} built-in CJmod modules`);
}

// 导出打包的模块
async function exportBundledModules(context: vscode.ExtensionContext) {
    const uri = await vscode.window.showSaveDialog({
        defaultUri: vscode.Uri.file('chtl-builtin-modules.js'),
        filters: {
            'JavaScript': ['js']
        }
    });

    if (!uri) return;

    const bundleCode = `
/*!
 * CHTL Built-in Modules Bundle
 * Version: 1.0.0
 * Generated: ${new Date().toISOString()}
 */

(function(window) {
    'use strict';
    
${getAllBuiltinModulesCode()}

    // Auto-initialize if CHTL runtime is present
    if (window.__CHTL_RUNTIME) {
        Object.keys(window.__CHTL_BUILTIN_MODULES).forEach(key => {
            window.__CHTL_RUNTIME.registerModule(key, window.__CHTL_BUILTIN_MODULES[key]);
        });
    }
})(typeof window !== 'undefined' ? window : this);
`;

    fs.writeFileSync(uri.fsPath, bundleCode);
    vscode.window.showInformationMessage(`Built-in modules exported to ${uri.fsPath}`);
}

// 导出类型声明
async function exportTypeDeclarations(context: vscode.ExtensionContext) {
    const uri = await vscode.window.showSaveDialog({
        defaultUri: vscode.Uri.file('chtl-builtin-modules.d.ts'),
        filters: {
            'TypeScript Declaration': ['d.ts']
        }
    });

    if (!uri) return;

    fs.writeFileSync(uri.fsPath, generateBuiltinModulesDeclaration());
    vscode.window.showInformationMessage(`Type declarations exported to ${uri.fsPath}`);
}

// 导出单个模块
async function exportIndividualModules(context: vscode.ExtensionContext) {
    const folderUri = await vscode.window.showOpenDialog({
        canSelectFolders: true,
        canSelectFiles: false,
        canSelectMany: false,
        openLabel: 'Select Export Folder'
    });

    if (!folderUri || folderUri.length === 0) return;

    const exportPath = folderUri[0].fsPath;
    
    BUILTIN_MODULES.forEach((module, key) => {
        // 导出 JSON 格式
        const jsonFile = path.join(exportPath, `${key}.cjmod.json`);
        fs.writeFileSync(jsonFile, JSON.stringify(module, null, 2));

        // 导出 JS 格式
        const jsFile = path.join(exportPath, `${key}.cjmod.js`);
        const jsContent = `
// ${module.name} v${module.version}
// ${module.description}

export const ${key}Module = ${JSON.stringify(module, null, 2)};

// Runtime code
${module.runtime.before || ''}
${module.runtime.after || ''}
`;
        fs.writeFileSync(jsFile, jsContent);
    });

    vscode.window.showInformationMessage(`Exported ${BUILTIN_MODULES.size} modules to ${exportPath}`);
}

// 生成模块信息 HTML
function generateModuleInfoHTML(module: any): string {
    const rulesHTML = module.rules.map((rule: any) => `
        <tr>
            <td><code>${escapeHtml(rule.pattern)}</code></td>
            <td><code>${escapeHtml(rule.replacement)}</code></td>
            <td>${rule.priority}</td>
        </tr>
    `).join('');

    return `
<!DOCTYPE html>
<html>
<head>
    <style>
        body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; padding: 20px; }
        h1 { color: #333; }
        h2 { color: #555; margin-top: 30px; }
        table { width: 100%; border-collapse: collapse; margin-top: 10px; }
        th, td { padding: 10px; text-align: left; border-bottom: 1px solid #ddd; }
        th { background-color: #f5f5f5; font-weight: 600; }
        code { background: #f0f0f0; padding: 2px 4px; border-radius: 3px; font-size: 0.9em; }
        pre { background: #f5f5f5; padding: 15px; border-radius: 5px; overflow-x: auto; }
        .info { background: #e8f4f8; padding: 10px; border-radius: 5px; margin: 10px 0; }
    </style>
</head>
<body>
    <h1>${module.name} Module</h1>
    <div class="info">
        <strong>Version:</strong> ${module.version}<br>
        <strong>Description:</strong> ${module.description}
    </div>

    <h2>Syntax Rules</h2>
    <table>
        <thead>
            <tr>
                <th>Pattern</th>
                <th>Replacement</th>
                <th>Priority</th>
            </tr>
        </thead>
        <tbody>
            ${rulesHTML}
        </tbody>
    </table>

    <h2>Runtime Code</h2>
    ${module.runtime.before ? `<h3>Before</h3><pre>${escapeHtml(module.runtime.before)}</pre>` : ''}
    ${module.runtime.after ? `<h3>After</h3><pre>${escapeHtml(module.runtime.after)}</pre>` : ''}

    <h2>Usage Example</h2>
    <pre>${getModuleExample(module.name)}</pre>
</body>
</html>
`;
}

function escapeHtml(text: string): string {
    const map: { [key: string]: string } = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#39;'
    };
    return text.replace(/[&<>"']/g, m => map[m]);
}

function getModuleExample(moduleName: string): string {
    const examples: { [key: string]: string } = {
        'reactive': `[Import] @CJmod from "builtin:reactive";

div {
    script {
        // Reactive variable
        count := 0;
        
        // Computed property
        doubled => count.value * 2;
        
        // Watch for changes
        watch count {
            console.log("Count changed:", count.value);
        }
    }
}`,
        'animation': `[Import] @CJmod from "builtin:animation";

div #box {
    script {
        // Animation chain
        {{&}} ~> fadeIn ~> slideDown;
        
        // With delay
        delay(1000);
        {{&}} ~> fadeOut;
    }
}`,
        'pipeline': `[Import] @CJmod from "builtin:pipeline";

div {
    script {
        // Basic pipe
        result = data |> filter |> map |> reduce;
        
        // Array operations
        filtered = array |>> double |?> isPositive;
        
        // Function composition
        process = validate >> transform >> format;
    }
}`,
        'async-flow': `[Import] @CJmod from "builtin:async-flow";

div {
    script {
        // Stream processing
        stream dataStream {
            yield* when hasData;
        }
        
        // Retry logic
        retry 3 {
            await fetchData();
        }
        
        // Concurrent execution
        concurrent 5 {
            await processItem();
        }
    }
}`
    };
    
    return examples[moduleName] || '// No example available';
}