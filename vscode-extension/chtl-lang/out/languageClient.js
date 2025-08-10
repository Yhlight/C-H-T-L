"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.getLanguageClient = exports.deactivateLanguageClient = exports.activateLanguageClient = void 0;
const vscode = __importStar(require("vscode"));
const path = __importStar(require("path"));
const node_1 = require("vscode-languageclient/node");
let client;
function activateLanguageClient(context) {
    // 服务器模块路径
    const serverModule = context.asAbsolutePath(path.join('out', 'server.js'));
    // 调试选项
    const debugOptions = { execArgv: ['--nolazy', '--inspect=6009'] };
    // 服务器选项
    const serverOptions = {
        run: { module: serverModule, transport: node_1.TransportKind.ipc },
        debug: {
            module: serverModule,
            transport: node_1.TransportKind.ipc,
            options: debugOptions
        }
    };
    // 客户端选项
    const clientOptions = {
        // 注册 CHTL 文件
        documentSelector: [{ scheme: 'file', language: 'chtl' }],
        synchronize: {
            // 监听配置更改
            configurationSection: 'chtl',
            // 监听 .chtl 文件的变化
            fileEvents: vscode.workspace.createFileSystemWatcher('**/*.chtl')
        },
        initializationOptions: {
            // 传递扩展路径给服务器
            extensionPath: context.extensionPath
        }
    };
    // 创建语言客户端
    client = new node_1.LanguageClient('chtlLanguageServer', 'CHTL Language Server', serverOptions, clientOptions);
    // 启动客户端（也会启动服务器）
    client.start();
    // 注册自定义命令
    context.subscriptions.push(vscode.commands.registerCommand('chtl.extractComponent', async () => {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            return;
        }
        const selection = editor.selection;
        if (selection.isEmpty) {
            vscode.window.showWarningMessage('Please select code to extract');
            return;
        }
        // 发送命令到语言服务器
        await client.sendRequest('workspace/executeCommand', {
            command: 'chtl.extractComponent',
            arguments: [editor.document.uri.toString(), selection]
        });
    }));
    context.subscriptions.push(vscode.commands.registerCommand('chtl.convertToTemplate', async () => {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            return;
        }
        const selection = editor.selection;
        if (selection.isEmpty) {
            // 获取当前光标所在的组件
            const position = editor.selection.active;
            const wordRange = editor.document.getWordRangeAtPosition(position);
            if (!wordRange) {
                vscode.window.showWarningMessage('Please place cursor on a Custom component');
                return;
            }
        }
        // 发送命令到语言服务器
        await client.sendRequest('workspace/executeCommand', {
            command: 'chtl.convertToTemplate',
            arguments: [editor.document.uri.toString(), selection.isEmpty ? editor.document.getWordRangeAtPosition(editor.selection.active) : selection]
        });
    }));
    // 添加状态栏项显示服务器状态
    const statusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Right, 100);
    statusBarItem.text = '$(sync~spin) CHTL LSP Starting...';
    statusBarItem.show();
    // 等待客户端准备就绪
    context.subscriptions.push(client.onDidChangeState((event) => {
        if (event.newState === 2) { // Running state
            statusBarItem.text = '$(check) CHTL LSP Ready';
            statusBarItem.tooltip = 'CHTL Language Server is running';
            // 3秒后隐藏状态栏
            setTimeout(() => {
                statusBarItem.hide();
            }, 3000);
        }
    }));
    context.subscriptions.push(statusBarItem);
}
exports.activateLanguageClient = activateLanguageClient;
function deactivateLanguageClient() {
    if (!client) {
        return undefined;
    }
    return client.stop();
}
exports.deactivateLanguageClient = deactivateLanguageClient;
function getLanguageClient() {
    return client;
}
exports.getLanguageClient = getLanguageClient;
//# sourceMappingURL=languageClient.js.map