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
exports.deactivate = exports.activate = void 0;
const vscode = __importStar(require("vscode"));
const path = __importStar(require("path"));
const fs = __importStar(require("fs"));
const util_1 = require("util");
const compiler_1 = require("./compiler");
const fsAsync = {
    readFile: (0, util_1.promisify)(fs.readFile),
    writeFile: (0, util_1.promisify)(fs.writeFile),
    mkdir: (0, util_1.promisify)(fs.mkdir),
    access: (0, util_1.promisify)(fs.access),
    readdir: (0, util_1.promisify)(fs.readdir),
    stat: (0, util_1.promisify)(fs.stat)
};
let compiler;
let diagnosticCollection;
let outputChannel;
function activate(context) {
    console.log('CHTL extension is now active!');
    // Initialize compiler
    compiler = new compiler_1.ChtlCompiler(context);
    // Create diagnostic collection
    diagnosticCollection = vscode.languages.createDiagnosticCollection('chtl');
    context.subscriptions.push(diagnosticCollection);
    // Create output channel
    outputChannel = vscode.window.createOutputChannel('CHTL');
    context.subscriptions.push(outputChannel);
    // Check if compiler is available
    if (!compiler.isAvailable()) {
        vscode.window.showWarningMessage('CHTL compiler not found. Some features may not work. Please install the CHTL compiler or update your settings.', 'Open Settings').then(selection => {
            if (selection === 'Open Settings') {
                vscode.commands.executeCommand('workbench.action.openSettings', 'chtl.compiler.path');
            }
        });
    }
    else {
        outputChannel.appendLine(`CHTL compiler found at: ${compiler.getCompilerPath()}`);
    }
    // Register compile command
    const compileCommand = vscode.commands.registerCommand('chtl.compile', compileCurrentFile);
    context.subscriptions.push(compileCommand);
    // Register compile all command
    const compileAllCommand = vscode.commands.registerCommand('chtl.compileAll', compileAllFiles);
    context.subscriptions.push(compileAllCommand);
    // Register preview command
    const previewCommand = vscode.commands.registerCommand('chtl.preview', previewInBrowser);
    context.subscriptions.push(previewCommand);
    // Register create component command
    const createComponentCommand = vscode.commands.registerCommand('chtl.createComponent', createComponent);
    context.subscriptions.push(createComponentCommand);
    // Register pack CMOD command
    const packCmodCommand = vscode.commands.registerCommand('chtl.packCmod', packCmod);
    context.subscriptions.push(packCmodCommand);
    // Register format provider
    const formatter = vscode.languages.registerDocumentFormattingEditProvider('chtl', {
        provideDocumentFormattingEdits: formatDocument
    });
    context.subscriptions.push(formatter);
    // Register hover provider
    const hoverProvider = vscode.languages.registerHoverProvider('chtl', {
        provideHover: provideHover
    });
    context.subscriptions.push(hoverProvider);
    // Register completion provider
    const completionProvider = vscode.languages.registerCompletionItemProvider('chtl', {
        provideCompletionItems: provideCompletionItems
    }, '.', '@', '{', '<', ':', '->', '[', 'inherit', 'delete', 'insert', 'except', 'from', 'as');
    context.subscriptions.push(completionProvider);
    // Register definition provider
    const definitionProvider = vscode.languages.registerDefinitionProvider('chtl', {
        provideDefinition: provideDefinition
    });
    context.subscriptions.push(definitionProvider);
    // Register code lens provider
    const codeLensProvider = vscode.languages.registerCodeLensProvider('chtl', {
        provideCodeLenses: provideCodeLenses
    });
    context.subscriptions.push(codeLensProvider);
    // Watch for file saves to provide real-time diagnostics
    const saveWatcher = vscode.workspace.onDidSaveTextDocument(async (document) => {
        if (document.languageId === 'chtl') {
            const config = vscode.workspace.getConfiguration('chtl');
            // Run linting if enabled
            if (config.get('lint.enable')) {
                await lintDocument(document);
            }
            // Auto-compile if enabled
            if (config.get('compiler.autoCompile')) {
                await compileFile(document.uri);
            }
        }
    });
    context.subscriptions.push(saveWatcher);
    // Watch for file changes to update diagnostics
    const changeWatcher = vscode.workspace.onDidChangeTextDocument(async (event) => {
        if (event.document.languageId === 'chtl') {
            // Clear diagnostics for real-time feedback
            diagnosticCollection.delete(event.document.uri);
        }
    });
    context.subscriptions.push(changeWatcher);
    // Register a status bar item
    const statusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Right, 100);
    statusBarItem.text = '$(file-code) CHTL';
    statusBarItem.command = 'chtl.showInfo';
    statusBarItem.show();
    context.subscriptions.push(statusBarItem);
    // Register show info command
    const showInfoCommand = vscode.commands.registerCommand('chtl.showInfo', showInfo);
    context.subscriptions.push(showInfoCommand);
}
exports.activate = activate;
async function compileCurrentFile() {
    const editor = vscode.window.activeTextEditor;
    if (!editor) {
        vscode.window.showErrorMessage('No active CHTL file');
        return;
    }
    if (editor.document.languageId !== 'chtl') {
        vscode.window.showErrorMessage('Current file is not a CHTL file');
        return;
    }
    await compileFile(editor.document.uri);
}
async function compileFile(uri) {
    if (!compiler.isAvailable()) {
        vscode.window.showErrorMessage('CHTL compiler is not available');
        return;
    }
    outputChannel.clear();
    outputChannel.show();
    outputChannel.appendLine(`Compiling ${uri.fsPath}...`);
    const startTime = Date.now();
    const result = await compiler.compile(uri.fsPath);
    const duration = Date.now() - startTime;
    if (result.success) {
        outputChannel.appendLine(`✓ Compilation successful (${duration}ms)`);
        if (result.output) {
            outputChannel.appendLine(result.output);
        }
        vscode.window.showInformationMessage(`CHTL compilation successful`);
        // Clear diagnostics on success
        diagnosticCollection.delete(uri);
    }
    else {
        outputChannel.appendLine(`✗ Compilation failed (${duration}ms)`);
        if (result.error) {
            outputChannel.appendLine(result.error);
        }
        vscode.window.showErrorMessage(`CHTL compilation failed: ${result.error}`);
    }
    // Update diagnostics
    if (result.diagnostics && result.diagnostics.length > 0) {
        updateDiagnostics(uri, result.diagnostics);
    }
}
async function compileAllFiles() {
    if (!compiler.isAvailable()) {
        vscode.window.showErrorMessage('CHTL compiler is not available');
        return;
    }
    const files = await vscode.workspace.findFiles('**/*.chtl', '**/node_modules/**');
    if (files.length === 0) {
        vscode.window.showInformationMessage('No CHTL files found in workspace');
        return;
    }
    outputChannel.clear();
    outputChannel.show();
    outputChannel.appendLine(`Compiling ${files.length} CHTL files...`);
    let successCount = 0;
    let errorCount = 0;
    for (const file of files) {
        outputChannel.appendLine(`\nCompiling ${file.fsPath}...`);
        const result = await compiler.compile(file.fsPath);
        if (result.success) {
            successCount++;
            outputChannel.appendLine(`✓ Success`);
        }
        else {
            errorCount++;
            outputChannel.appendLine(`✗ Failed: ${result.error}`);
        }
        if (result.diagnostics && result.diagnostics.length > 0) {
            updateDiagnostics(file, result.diagnostics);
        }
    }
    outputChannel.appendLine(`\nCompilation complete: ${successCount} succeeded, ${errorCount} failed`);
    if (errorCount === 0) {
        vscode.window.showInformationMessage(`All ${successCount} CHTL files compiled successfully`);
    }
    else {
        vscode.window.showWarningMessage(`Compilation complete: ${successCount} succeeded, ${errorCount} failed`);
    }
}
async function lintDocument(document) {
    if (!compiler.isAvailable()) {
        return;
    }
    const diagnostics = await compiler.lint(document.uri.fsPath);
    updateDiagnostics(document.uri, diagnostics);
}
function updateDiagnostics(uri, diagnostics) {
    const vscodeDiagnostics = diagnostics.map(diag => {
        const range = new vscode.Range(Math.max(0, diag.line - 1), Math.max(0, diag.column - 1), Math.max(0, diag.line - 1), Math.max(0, diag.column));
        const severity = diag.severity === 'error' ? vscode.DiagnosticSeverity.Error :
            diag.severity === 'warning' ? vscode.DiagnosticSeverity.Warning :
                vscode.DiagnosticSeverity.Information;
        const diagnostic = new vscode.Diagnostic(range, diag.message, severity);
        if (diag.code) {
            diagnostic.code = diag.code;
        }
        diagnostic.source = 'chtl';
        return diagnostic;
    });
    diagnosticCollection.set(uri, vscodeDiagnostics);
}
async function previewInBrowser() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'chtl') {
        vscode.window.showErrorMessage('No active CHTL file');
        return;
    }
    // First compile the file
    const result = await compiler.compile(editor.document.uri.fsPath);
    if (!result.success) {
        vscode.window.showErrorMessage('Failed to compile CHTL file');
        return;
    }
    // Find the output HTML file
    const config = vscode.workspace.getConfiguration('chtl.compiler');
    const outputDir = config.get('outputDirectory') || 'dist';
    const inputPath = editor.document.uri.fsPath;
    const baseName = path.basename(inputPath, '.chtl');
    const outputPath = path.join(path.dirname(inputPath), outputDir, `${baseName}.html`);
    // Check if output file exists
    try {
        await fsAsync.access(outputPath);
    }
    catch {
        vscode.window.showErrorMessage(`Output file not found: ${outputPath}`);
        return;
    }
    // Open in default browser
    const openPath = vscode.Uri.file(outputPath);
    await vscode.env.openExternal(openPath);
}
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
    const componentType = await vscode.window.showQuickPick([
        { label: 'Custom Element', value: 'element' },
        { label: 'Template Element', value: 'template' },
        { label: 'Custom Style', value: 'style' },
        { label: 'Template Style', value: 'template-style' },
        { label: 'Custom Variable', value: 'var' },
        { label: 'Template Variable', value: 'template-var' }
    ], {
        placeHolder: 'Select component type'
    });
    if (!componentType) {
        return;
    }
    let template = '';
    switch (componentType.value) {
        case 'element':
            template = `[Custom] @Element ${componentName} {
    div {
        class: "${componentName.toLowerCase()}";
        
        style {
            // Component styles
        }
        
        script {
            {{&}}->listen({
                mounted: () => {
                    console.log('${componentName} mounted');
                }
            });
        }
        
        // Component content
    }
}`;
            break;
        case 'template':
            template = `[Template] @Element ${componentName} {
    div {
        class: "${componentName.toLowerCase()}";
        
        style {
            // Template styles
        }
        
        // Template content
    }
}`;
            break;
        case 'style':
            template = `[Custom] @Style ${componentName} {
    // Style properties (leave empty for custom values)
    color;
    background;
    padding;
}`;
            break;
        case 'template-style':
            template = `[Template] @Style ${componentName} {
    // Default style values
    color: #333;
    background: #fff;
    padding: 1rem;
}`;
            break;
        case 'var':
            template = `[Custom] @Var ${componentName} {
    // Variable definitions
    primary: "#007bff";
    secondary: "#6c757d";
}`;
            break;
        case 'template-var':
            template = `[Template] @Var ${componentName} {
    // Variable definitions
    primary: "#007bff";
    secondary: "#6c757d";
    background: "#ffffff";
}`;
            break;
    }
    // Create new document with template
    const document = await vscode.workspace.openTextDocument({
        language: 'chtl',
        content: template
    });
    await vscode.window.showTextDocument(document);
}
async function packCmod() {
    // Select module directory
    const folderUris = await vscode.window.showOpenDialog({
        canSelectFolders: true,
        canSelectFiles: false,
        canSelectMany: false,
        openLabel: 'Select CMOD Directory',
        title: 'Select the module directory to pack'
    });
    if (!folderUris || folderUris.length === 0) {
        return;
    }
    const moduleDir = folderUris[0].fsPath;
    // Check if it's a valid CMOD structure
    const infoDir = path.join(moduleDir, 'info');
    const srcDir = path.join(moduleDir, 'src');
    try {
        const infoStat = await fsAsync.stat(infoDir);
        const srcStat = await fsAsync.stat(srcDir);
        if (!infoStat.isDirectory() || !srcStat.isDirectory()) {
            vscode.window.showErrorMessage('Invalid CMOD structure: missing info/ or src/ directory');
            return;
        }
    }
    catch {
        vscode.window.showErrorMessage('Invalid CMOD structure: missing info/ or src/ directory');
        return;
    }
    outputChannel.clear();
    outputChannel.show();
    outputChannel.appendLine(`Packing CMOD: ${moduleDir}`);
    const result = await compiler.packCmod(moduleDir);
    if (result.success) {
        outputChannel.appendLine('✓ CMOD packed successfully');
        if (result.output) {
            outputChannel.appendLine(result.output);
        }
        vscode.window.showInformationMessage('CMOD packed successfully');
    }
    else {
        outputChannel.appendLine('✗ CMOD packing failed');
        if (result.error) {
            outputChannel.appendLine(result.error);
        }
        vscode.window.showErrorMessage(`CMOD packing failed: ${result.error}`);
    }
}
async function formatDocument(document) {
    const config = vscode.workspace.getConfiguration('chtl.format');
    if (!config.get('enable')) {
        return [];
    }
    const indentSize = config.get('indentSize') || 2;
    const text = document.getText();
    const lines = text.split('\n');
    const edits = [];
    let indentLevel = 0;
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        const trimmed = line.trim();
        if (trimmed === '') {
            continue;
        }
        // Decrease indent for closing braces
        if (trimmed.startsWith('}') || trimmed.startsWith(']')) {
            indentLevel = Math.max(0, indentLevel - 1);
        }
        const newIndent = ' '.repeat(indentLevel * indentSize);
        const currentIndent = line.match(/^\s*/)?.[0] || '';
        if (currentIndent !== newIndent) {
            const range = new vscode.Range(new vscode.Position(i, 0), new vscode.Position(i, currentIndent.length));
            edits.push(vscode.TextEdit.replace(range, newIndent));
        }
        // Increase indent for opening braces
        if (trimmed.endsWith('{') || trimmed.endsWith('[')) {
            indentLevel++;
        }
    }
    return edits;
}
function provideHover(document, position) {
    const wordRange = document.getWordRangeAtPosition(position);
    if (!wordRange) {
        return undefined;
    }
    const word = document.getText(wordRange);
    // Check if it's a CHTL keyword or construct
    const hoverInfo = getChtlHoverInfo(word);
    if (hoverInfo) {
        return new vscode.Hover(hoverInfo);
    }
    return undefined;
}
function getChtlHoverInfo(word) {
    const info = {
        '[Configuration]': '# Configuration Block\n\nDefines global configuration settings for the CHTL file.\n\n```chtl\n[Configuration] {\n    INDEX_INITIAL_COUNT = 0;\n    DEBUG_MODE = false;\n}\n```',
        '[Name]': '# Name Block\n\nDefines keyword aliases within a Configuration block.\n\n```chtl\n[Name] {\n    CUSTOM_STYLE = [@Style, @样式];\n}\n```',
        '[Import]': '# Import Block\n\nImports components, styles, or variables from other files or namespaces.\n\n```chtl\n[Import] {\n    @Element Button from "components/button.chtl";\n    @Style Theme from namespace UI as UITheme;\n}\n```',
        '[Export]': '# Export Block\n\nExports components for use in other files.\n\n```chtl\n[Export] {\n    @Element Button;\n    @Style Theme as DefaultTheme;\n}\n```',
        '[Namespace]': '# Namespace Block\n\nGroups related components and definitions.\n\n```chtl\n[Namespace] UI {\n    [Template] @Element Button { ... }\n}\n```',
        '[Custom]': '# Custom Block\n\nDefines customizable components with specialization support.\n\n```chtl\n[Custom] @Element MyButton {\n    inherit @Element BaseButton;\n    // Custom implementation\n}\n```',
        '[Template]': '# Template Block\n\nDefines reusable templates for elements, styles, or variables.\n\n```chtl\n[Template] @Style DefaultText {\n    color: black;\n    font-size: 16px;\n}\n```',
        '[Origin]': '# Origin Block\n\nEmbeds raw HTML, CSS, or JavaScript code.\n\n```chtl\n[Origin] @Html analytics {\n    <script>/* Analytics code */</script>\n}\n```',
        'inherit': '# inherit Keyword\n\nInherits properties from a template or custom component.\n\n```chtl\ninherit @Style BaseStyle;\ninherit [Template] @Element BaseComponent;\n```',
        'delete': '# delete Keyword\n\nRemoves inherited properties or elements.\n\n```chtl\ndelete color, background;\ndelete @Style OldStyle;\n```',
        'insert': '# insert Keyword\n\nInserts elements at specific positions.\n\n```chtl\ninsert after div[0] { ... }\ninsert at top { ... }\n```',
        'except': '# except Keyword\n\nDefines constraints on child elements.\n\n```chtl\nexcept span, [Custom] @Element Box;\n```',
        'style': '# style Block\n\nLocal style block for inline and scoped CSS.\n\n```chtl\nstyle {\n    width: 100px;\n    .auto-class { ... }\n    &:hover { ... }\n}\n```',
        'script': '# script Block\n\nLocal script block for JavaScript.\n\n```chtl\nscript {\n    {{&}}->listen({\n        click: (e) => { ... }\n    });\n}\n```',
        '{{&}}': '# Current Element Reference\n\nRefers to the current element in local script blocks.\n\n```chtl\n{{&}}->listen({ ... });\n```',
        '->': '# CHTL Arrow Operator\n\nCHTL-specific syntax for method calls.\n\n```chtl\n{{&}}->animate({ ... });\n```'
    };
    const markdown = info[word];
    if (markdown) {
        return new vscode.MarkdownString(markdown);
    }
    return undefined;
}
function provideCompletionItems(document, position, token, context) {
    const linePrefix = document.lineAt(position).text.substr(0, position.character);
    const items = [];
    // CHTL blocks
    if (linePrefix.endsWith('[')) {
        items.push(createCompletionItem('Configuration]', vscode.CompletionItemKind.Keyword, 'Global configuration'), createCompletionItem('Name]', vscode.CompletionItemKind.Keyword, 'Keyword aliases (inside Configuration)'), createCompletionItem('Import]', vscode.CompletionItemKind.Keyword, 'Import components'), createCompletionItem('Export]', vscode.CompletionItemKind.Keyword, 'Export components'), createCompletionItem('Namespace]', vscode.CompletionItemKind.Keyword, 'Namespace definition'), createCompletionItem('Custom]', vscode.CompletionItemKind.Keyword, 'Custom component'), createCompletionItem('Template]', vscode.CompletionItemKind.Keyword, 'Template component'), createCompletionItem('Origin]', vscode.CompletionItemKind.Keyword, 'Raw code embed'), createCompletionItem('Info]', vscode.CompletionItemKind.Keyword, 'Module information (CMOD only)'));
    }
    // @ prefixed types
    if (linePrefix.endsWith('@')) {
        items.push(createCompletionItem('Element', vscode.CompletionItemKind.Class, 'Element component'), createCompletionItem('Style', vscode.CompletionItemKind.Class, 'Style group'), createCompletionItem('Var', vscode.CompletionItemKind.Class, 'Variable group'), createCompletionItem('Html', vscode.CompletionItemKind.Class, 'HTML origin'), createCompletionItem('JavaScript', vscode.CompletionItemKind.Class, 'JavaScript origin'));
    }
    // Keywords
    if (linePrefix.match(/^\s*\w*$/)) {
        items.push(createCompletionItem('inherit', vscode.CompletionItemKind.Keyword, 'Inherit from template/custom'), createCompletionItem('delete', vscode.CompletionItemKind.Keyword, 'Delete properties/elements'), createCompletionItem('insert', vscode.CompletionItemKind.Keyword, 'Insert elements'), createCompletionItem('except', vscode.CompletionItemKind.Keyword, 'Exclude elements'), createCompletionItem('from', vscode.CompletionItemKind.Keyword, 'Import/export from source'), createCompletionItem('as', vscode.CompletionItemKind.Keyword, 'Rename import/export'), createCompletionItem('style', vscode.CompletionItemKind.Keyword, 'Local style block'), createCompletionItem('script', vscode.CompletionItemKind.Keyword, 'Local script block'), createCompletionItem('text', vscode.CompletionItemKind.Keyword, 'Text content block'));
    }
    // CHTL JS enhancements
    if (linePrefix.includes('{{')) {
        items.push(createCompletionItem('&}}', vscode.CompletionItemKind.Variable, 'Current element reference'), createCompletionItem('.class}}', vscode.CompletionItemKind.Variable, 'Select by class'), createCompletionItem('#id}}', vscode.CompletionItemKind.Variable, 'Select by ID'), createCompletionItem('tag}}', vscode.CompletionItemKind.Variable, 'Select by tag'));
    }
    if (linePrefix.includes('->')) {
        items.push(createCompletionItem('listen', vscode.CompletionItemKind.Method, 'Add event listeners'), createCompletionItem('delegate', vscode.CompletionItemKind.Method, 'Event delegation'), createCompletionItem('animate', vscode.CompletionItemKind.Method, 'Animate element'));
    }
    // HTML elements
    if (linePrefix.match(/^\s*\w*$/) || linePrefix.endsWith(' ')) {
        const htmlElements = ['div', 'span', 'p', 'a', 'img', 'button', 'input', 'form',
            'ul', 'ol', 'li', 'table', 'tr', 'td', 'h1', 'h2', 'h3',
            'nav', 'header', 'footer', 'section', 'article', 'aside'];
        htmlElements.forEach(el => {
            items.push(createCompletionItem(el, vscode.CompletionItemKind.Property, `HTML <${el}> element`));
        });
    }
    return items;
}
function createCompletionItem(label, kind, detail) {
    const item = new vscode.CompletionItem(label, kind);
    item.detail = detail;
    return item;
}
async function provideDefinition(document, position, token) {
    const wordRange = document.getWordRangeAtPosition(position, /[@\w]+/);
    if (!wordRange) {
        return undefined;
    }
    const word = document.getText(wordRange);
    // Look for component definitions in the current file
    const text = document.getText();
    const regex = new RegExp(`\\[(Custom|Template)\\]\\s+@\\w+\\s+${word}\\s*\\{`, 'g');
    const match = regex.exec(text);
    if (match) {
        const pos = document.positionAt(match.index);
        return new vscode.Location(document.uri, pos);
    }
    // TODO: Look in imported files
    return undefined;
}
function provideCodeLenses(document, token) {
    const codeLenses = [];
    const text = document.getText();
    // Find all component definitions
    const componentRegex = /\[(Custom|Template)\]\s+@(\w+)\s+(\w+)\s*\{/g;
    let match;
    while ((match = componentRegex.exec(text)) !== null) {
        const line = document.positionAt(match.index).line;
        const range = new vscode.Range(line, 0, line, 0);
        const componentType = match[1];
        const componentKind = match[2];
        const componentName = match[3];
        // Add "References" code lens
        const referenceLens = new vscode.CodeLens(range, {
            title: `$(references) Find References`,
            command: 'editor.action.findReferences',
            arguments: [document.uri, range.start]
        });
        codeLenses.push(referenceLens);
        // Add "Compile" code lens for Custom components
        if (componentType === 'Custom') {
            const compileLens = new vscode.CodeLens(range, {
                title: `$(run) Test Component`,
                command: 'chtl.testComponent',
                arguments: [componentName]
            });
            codeLenses.push(compileLens);
        }
    }
    return codeLenses;
}
async function showInfo() {
    const info = [
        `CHTL Extension v1.0.0`,
        ``,
        `Compiler: ${compiler.isAvailable() ? '✓ Available' : '✗ Not Found'}`,
        `Path: ${compiler.getCompilerPath() || 'Not configured'}`,
        ``,
        `Features:`,
        `• Syntax Highlighting`,
        `• IntelliSense & Snippets`,
        `• Real-time Diagnostics`,
        `• Integrated Compilation`,
        `• CMOD Packaging`,
        ``,
        `Commands:`,
        `• Compile Current File (Ctrl+Shift+C)`,
        `• Preview in Browser (Ctrl+Shift+P)`,
        `• Create Component`,
        `• Pack CMOD`,
    ].join('\n');
    vscode.window.showInformationMessage(info, { modal: true });
}
function deactivate() {
    if (outputChannel) {
        outputChannel.dispose();
    }
}
exports.deactivate = deactivate;
//# sourceMappingURL=extension.js.map