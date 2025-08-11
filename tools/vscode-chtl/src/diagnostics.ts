import * as vscode from 'vscode';
import * as path from 'path';
import { exec } from 'child_process';
import { promisify } from 'util';

const execAsync = promisify(exec);

export class CHTLDiagnosticsProvider {
    private diagnosticCollection: vscode.DiagnosticCollection;
    private compilerPath: string;

    constructor() {
        this.diagnosticCollection = vscode.languages.createDiagnosticCollection('chtl');
        this.compilerPath = vscode.workspace.getConfiguration('chtl').get('compiler.path', 'chtl');
    }

    async updateDiagnostics(document: vscode.TextDocument): Promise<void> {
        if (document.languageId !== 'chtl') {
            return;
        }

        const diagnostics: vscode.Diagnostic[] = [];

        // 基本语法检查
        this.checkBasicSyntax(document, diagnostics);

        // 如果配置了编译器路径，使用编译器进行检查
        if (this.compilerPath) {
            await this.checkWithCompiler(document, diagnostics);
        }

        this.diagnosticCollection.set(document.uri, diagnostics);
    }

    private checkBasicSyntax(document: vscode.TextDocument, diagnostics: vscode.Diagnostic[]) {
        const text = document.getText();
        const lines = text.split('\n');

        for (let i = 0; i < lines.length; i++) {
            const line = lines[i];
            
            // 检查未闭合的括号
            this.checkBrackets(line, i, diagnostics);
            
            // 检查属性语法
            this.checkAttributes(line, i, diagnostics);
            
            // 检查引用语法
            this.checkReferences(line, i, diagnostics);
            
            // 检查特殊块语法
            this.checkSpecialBlocks(line, i, diagnostics);
        }

        // 检查整体结构
        this.checkOverallStructure(text, diagnostics);
    }

    private checkBrackets(line: string, lineNumber: number, diagnostics: vscode.Diagnostic[]) {
        let openCount = 0;
        let closeCount = 0;
        
        for (const char of line) {
            if (char === '{') openCount++;
            if (char === '}') closeCount++;
        }
        
        if (openCount > closeCount) {
            const range = new vscode.Range(lineNumber, line.length - 1, lineNumber, line.length);
            diagnostics.push(new vscode.Diagnostic(
                range,
                'Unclosed brace',
                vscode.DiagnosticSeverity.Error
            ));
        }
    }

    private checkAttributes(line: string, lineNumber: number, diagnostics: vscode.Diagnostic[]) {
        // 检查属性赋值语法
        const attrMatch = line.match(/^\s*(\w+)\s*([^:=\s])/);
        if (attrMatch && !line.includes('{') && !line.includes('}')) {
            const range = new vscode.Range(lineNumber, attrMatch.index!, lineNumber, line.length);
            diagnostics.push(new vscode.Diagnostic(
                range,
                "Expected ':' or '=' after attribute name",
                vscode.DiagnosticSeverity.Error
            ));
        }
        
        // 检查缺失的分号
        const needsSemicolon = /^\s*\w+\s*[:=]\s*[^;{]+$/;
        if (needsSemicolon.test(line) && !line.trim().endsWith(';')) {
            const range = new vscode.Range(lineNumber, line.length - 1, lineNumber, line.length);
            diagnostics.push(new vscode.Diagnostic(
                range,
                "Missing semicolon",
                vscode.DiagnosticSeverity.Warning
            ));
        }
    }

    private checkReferences(line: string, lineNumber: number, diagnostics: vscode.Diagnostic[]) {
        // 检查@引用语法
        const refMatch = line.match(/@(\w+)\s+(\w+)/);
        if (refMatch) {
            const refType = refMatch[1];
            const validTypes = ['Style', 'Element', 'Var', 'Html', 'JavaScript', 'Chtl', 'CJmod'];
            
            if (!validTypes.includes(refType)) {
                const start = line.indexOf('@' + refType);
                const range = new vscode.Range(lineNumber, start, lineNumber, start + refType.length + 1);
                diagnostics.push(new vscode.Diagnostic(
                    range,
                    `Invalid reference type '@${refType}'`,
                    vscode.DiagnosticSeverity.Error
                ));
            }
        }
        
        // 检查变量组函数调用
        const varFuncMatch = line.match(/(\w+)\((\w+)(?:\s*=\s*([^)]+))?\)/);
        if (varFuncMatch && !line.includes('function') && !line.includes('=>')) {
            // 这可能是变量组函数调用，添加提示
            const start = line.indexOf(varFuncMatch[0]);
            const range = new vscode.Range(lineNumber, start, lineNumber, start + varFuncMatch[0].length);
            
            const hint = new vscode.Diagnostic(
                range,
                `Variable group function call: ${varFuncMatch[1]}`,
                vscode.DiagnosticSeverity.Information
            );
            hint.tags = [vscode.DiagnosticTag.Unnecessary]; // 使用淡化显示
            diagnostics.push(hint);
        }
    }

    private checkSpecialBlocks(line: string, lineNumber: number, diagnostics: vscode.Diagnostic[]) {
        // 检查特殊块语法
        const blockMatch = line.match(/\[(\w+)\]/);
        if (blockMatch) {
            const blockType = blockMatch[1];
            const validBlocks = ['Template', 'Custom', 'Configuration', 'Import', 'Export', 
                               'Info', 'Origin', 'Namespace'];
            
            if (!validBlocks.includes(blockType)) {
                const start = line.indexOf('[' + blockType + ']');
                const range = new vscode.Range(lineNumber, start, lineNumber, start + blockType.length + 2);
                diagnostics.push(new vscode.Diagnostic(
                    range,
                    `Unknown block type '[${blockType}]'`,
                    vscode.DiagnosticSeverity.Error
                ));
            }
        }
    }

    private checkOverallStructure(text: string, diagnostics: vscode.Diagnostic[]) {
        // 检查大括号配对
        let braceCount = 0;
        const lines = text.split('\n');
        
        for (let i = 0; i < lines.length; i++) {
            for (const char of lines[i]) {
                if (char === '{') braceCount++;
                if (char === '}') braceCount--;
                
                if (braceCount < 0) {
                    const range = new vscode.Range(i, 0, i, lines[i].length);
                    diagnostics.push(new vscode.Diagnostic(
                        range,
                        'Unexpected closing brace',
                        vscode.DiagnosticSeverity.Error
                    ));
                    braceCount = 0; // Reset to continue checking
                }
            }
        }
        
        if (braceCount > 0) {
            const lastLine = lines.length - 1;
            const range = new vscode.Range(lastLine, 0, lastLine, lines[lastLine].length);
            diagnostics.push(new vscode.Diagnostic(
                range,
                `${braceCount} unclosed brace(s) in file`,
                vscode.DiagnosticSeverity.Error
            ));
        }
    }

    private async checkWithCompiler(document: vscode.TextDocument, diagnostics: vscode.Diagnostic[]): Promise<void> {
        try {
            const filePath = document.fileName;
            const command = `${this.compilerPath} --check "${filePath}"`;
            
            const { stdout, stderr } = await execAsync(command);
            
            // 解析编译器输出
            if (stderr) {
                const errorLines = stderr.split('\n');
                for (const errorLine of errorLines) {
                    const errorMatch = errorLine.match(/^(.+):(\d+):(\d+):\s*(error|warning):\s*(.+)$/);
                    if (errorMatch) {
                        const line = parseInt(errorMatch[2]) - 1;
                        const column = parseInt(errorMatch[3]) - 1;
                        const severity = errorMatch[4] === 'error' 
                            ? vscode.DiagnosticSeverity.Error 
                            : vscode.DiagnosticSeverity.Warning;
                        const message = errorMatch[5];
                        
                        const range = new vscode.Range(line, column, line, column + 10);
                        diagnostics.push(new vscode.Diagnostic(range, message, severity));
                    }
                }
            }
        } catch (error) {
            // 编译器不可用或其他错误，静默失败
            console.error('Compiler check failed:', error);
        }
    }

    dispose() {
        this.diagnosticCollection.dispose();
    }
}