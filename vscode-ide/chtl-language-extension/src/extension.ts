import * as vscode from 'vscode';
import * as path from 'path';
import * as fs from 'fs';
import { exec } from 'child_process';
import { promisify } from 'util';

const execAsync = promisify(exec);

export function activate(context: vscode.ExtensionContext) {
    console.log('CHTL Language Extension is now active!');

    // 注册编译命令
    let compileCommand = vscode.commands.registerCommand('chtl.compile', async () => {
        const editor = vscode.window.activeTextEditor;
        if (!editor || !editor.document.fileName.endsWith('.chtl')) {
            vscode.window.showErrorMessage('请打开一个CHTL文件');
            return;
        }

        const workspaceFolder = vscode.workspace.getWorkspaceFolder(editor.document.uri);
        if (!workspaceFolder) {
            vscode.window.showErrorMessage('请在工作区中打开文件');
            return;
        }

        const fileName = editor.document.fileName;
        const compilerPath = vscode.workspace.getConfiguration('chtl').get<string>('compiler.path', 'chtlc');
        
        // 保存文件
        await editor.document.save();
        
        // 显示输出通道
        const outputChannel = vscode.window.createOutputChannel('CHTL');
        outputChannel.show();
        outputChannel.appendLine(`编译文件: ${fileName}`);
        
        try {
            const { stdout, stderr } = await execAsync(`${compilerPath} "${fileName}"`, {
                cwd: workspaceFolder.uri.fsPath
            });
            
            if (stdout) outputChannel.appendLine(stdout);
            if (stderr) outputChannel.appendLine(stderr);
            
            if (!stderr) {
                vscode.window.showInformationMessage('编译成功!');
            }
        } catch (error: any) {
            outputChannel.appendLine(`编译错误: ${error.message}`);
            vscode.window.showErrorMessage('编译失败，请查看输出面板');
        }
    });

    // 注册编译所有文件命令
    let compileAllCommand = vscode.commands.registerCommand('chtl.compileAll', async () => {
        const workspaceFolders = vscode.workspace.workspaceFolders;
        if (!workspaceFolders) {
            vscode.window.showErrorMessage('请打开一个工作区');
            return;
        }

        const compilerPath = vscode.workspace.getConfiguration('chtl').get<string>('compiler.path', 'chtlc');
        const outputChannel = vscode.window.createOutputChannel('CHTL');
        outputChannel.show();

        for (const folder of workspaceFolders) {
            const files = await vscode.workspace.findFiles(
                new vscode.RelativePattern(folder, '**/*.chtl'),
                '**/node_modules/**'
            );

            outputChannel.appendLine(`在 ${folder.name} 中找到 ${files.length} 个CHTL文件`);

            for (const file of files) {
                outputChannel.appendLine(`编译: ${file.fsPath}`);
                try {
                    const { stdout, stderr } = await execAsync(`${compilerPath} "${file.fsPath}"`, {
                        cwd: folder.uri.fsPath
                    });
                    
                    if (stdout) outputChannel.appendLine(stdout);
                    if (stderr) outputChannel.appendLine(stderr);
                } catch (error: any) {
                    outputChannel.appendLine(`错误: ${error.message}`);
                }
            }
        }

        vscode.window.showInformationMessage('所有文件编译完成');
    });

    // 注册打包模块命令
    let packModuleCommand = vscode.commands.registerCommand('chtl.packModule', async () => {
        const folders = await vscode.window.showOpenDialog({
            canSelectFolders: true,
            canSelectFiles: false,
            canSelectMany: false,
            openLabel: '选择模块文件夹',
            title: '选择要打包的模块'
        });

        if (!folders || folders.length === 0) {
            return;
        }

        const moduleFolder = folders[0].fsPath;
        const moduleName = path.basename(moduleFolder);
        
        const outputChannel = vscode.window.createOutputChannel('CHTL Module Packer');
        outputChannel.show();
        outputChannel.appendLine(`打包模块: ${moduleName}`);

        try {
            // 检测模块类型
            const hasCMOD = fs.existsSync(path.join(moduleFolder, 'CMOD')) || 
                            (fs.existsSync(path.join(moduleFolder, 'src')) && 
                             fs.readdirSync(path.join(moduleFolder, 'src')).some(f => f.endsWith('.chtl')));
            
            const hasCJMOD = fs.existsSync(path.join(moduleFolder, 'CJMOD')) ||
                             (fs.existsSync(path.join(moduleFolder, 'src')) && 
                              fs.readdirSync(path.join(moduleFolder, 'src')).some(f => f.endsWith('.cpp')));

            if (hasCMOD) {
                outputChannel.appendLine('检测到CMOD模块，开始打包...');
                const packScript = process.platform === 'win32' ? 'pack.bat' : './pack.sh';
                const { stdout, stderr } = await execAsync(`${packScript} "${moduleFolder}" --type cmod`);
                if (stdout) outputChannel.appendLine(stdout);
                if (stderr) outputChannel.appendLine(stderr);
            }

            if (hasCJMOD) {
                outputChannel.appendLine('检测到CJMOD模块，开始打包...');
                const packScript = process.platform === 'win32' ? 'pack.bat' : './pack.sh';
                const { stdout, stderr } = await execAsync(`${packScript} "${moduleFolder}" --type cjmod`);
                if (stdout) outputChannel.appendLine(stdout);
                if (stderr) outputChannel.appendLine(stderr);
            }

            vscode.window.showInformationMessage('模块打包完成');
        } catch (error: any) {
            outputChannel.appendLine(`错误: ${error.message}`);
            vscode.window.showErrorMessage('模块打包失败');
        }
    });

    // 注册创建模板命令
    let createTemplateCommand = vscode.commands.registerCommand('chtl.createTemplate', async () => {
        const templateType = await vscode.window.showQuickPick(
            ['@Style', '@Element', '@Var'],
            { placeHolder: '选择模板类型' }
        );

        if (!templateType) return;

        const templateName = await vscode.window.showInputBox({
            prompt: '输入模板名称',
            placeHolder: 'MyTemplate'
        });

        if (!templateName) return;

        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            vscode.window.showErrorMessage('请打开一个CHTL文件');
            return;
        }

        const snippet = new vscode.SnippetString(
            `[Template] ${templateType} ${templateName}\n{\n\t$0\n}\n`
        );

        editor.insertSnippet(snippet);
    });

    // 注册创建自定义组件命令
    let createCustomCommand = vscode.commands.registerCommand('chtl.createCustom', async () => {
        const customType = await vscode.window.showQuickPick(
            ['@Style', '@Element'],
            { placeHolder: '选择自定义类型' }
        );

        if (!customType) return;

        const customName = await vscode.window.showInputBox({
            prompt: '输入自定义组件名称',
            placeHolder: 'MyCustom'
        });

        if (!customName) return;

        const baseName = await vscode.window.showInputBox({
            prompt: '输入基础组件名称',
            placeHolder: 'BaseComponent'
        });

        if (!baseName) return;

        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            vscode.window.showErrorMessage('请打开一个CHTL文件');
            return;
        }

        const snippet = new vscode.SnippetString(
            `[Custom] ${customType} ${customName}\n{\n\t${customType} ${baseName};\n\t$0\n}\n`
        );

        editor.insertSnippet(snippet);
    });

    // 添加文件图标主题
    const iconTheme: any = {
        "iconDefinitions": {
            "_chtl": {
                "iconPath": "./images/chtl-icon.svg"
            },
            "_cmod": {
                "iconPath": "./images/cmod-icon.svg"
            },
            "_cjmod": {
                "iconPath": "./images/cjmod-icon.svg"
            }
        },
        "fileExtensions": {
            "chtl": "_chtl",
            "cmod": "_cmod",
            "cjmod": "_cjmod"
        }
    };

    context.subscriptions.push(
        compileCommand,
        compileAllCommand,
        packModuleCommand,
        createTemplateCommand,
        createCustomCommand
    );

    // 注册诊断集合
    const diagnosticCollection = vscode.languages.createDiagnosticCollection('chtl');
    context.subscriptions.push(diagnosticCollection);

    // 监听文件保存事件，进行语法检查
    vscode.workspace.onDidSaveTextDocument(async (document) => {
        if (document.languageId !== 'chtl') return;
        
        const config = vscode.workspace.getConfiguration('chtl');
        if (!config.get<boolean>('validation.enable', true)) return;

        const compilerPath = config.get<string>('compiler.path', 'chtlc');
        const diagnostics: vscode.Diagnostic[] = [];

        try {
            const { stderr } = await execAsync(`${compilerPath} --check "${document.fileName}"`);
            
            if (stderr) {
                // 解析错误信息
                const errorRegex = /^(.+):(\d+):(\d+):\s+(warning|error):\s+(.+)$/gm;
                let match;
                
                while ((match = errorRegex.exec(stderr)) !== null) {
                    const line = parseInt(match[2]) - 1;
                    const column = parseInt(match[3]) - 1;
                    const severity = match[4] === 'error' ? vscode.DiagnosticSeverity.Error : vscode.DiagnosticSeverity.Warning;
                    const message = match[5];
                    
                    const range = new vscode.Range(line, column, line, column + 10);
                    const diagnostic = new vscode.Diagnostic(range, message, severity);
                    diagnostics.push(diagnostic);
                }
            }
        } catch (error) {
            // 忽略错误
        }

        diagnosticCollection.set(document.uri, diagnostics);
    });
}

export function deactivate() {
    console.log('CHTL Language Extension is now deactivated');
}