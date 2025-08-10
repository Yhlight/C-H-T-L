import {
    createConnection,
    TextDocuments,
    ProposedFeatures,
    InitializeParams,
    DidChangeConfigurationNotification,
    CompletionItem,
    CompletionItemKind,
    TextDocumentPositionParams,
    TextDocumentSyncKind,
    InitializeResult,
    DocumentDiagnosticReportKind,
    type DocumentDiagnosticReport,
    DiagnosticSeverity,
    Range,
    Position,
    Hover,
    Definition,
    Location,
    SymbolInformation,
    SymbolKind,
    DocumentSymbolParams,
    WorkspaceSymbol,
    WorkspaceSymbolParams,
    CodeActionParams,
    CodeAction,
    CodeActionKind,
    TextEdit,
    Command,
    ExecuteCommandParams,
    DocumentFormattingParams,
    FormattingOptions,
} from 'vscode-languageserver/node';

import {
    TextDocument
} from 'vscode-languageserver-textdocument';

import { ChtlCompiler, CompileResult, Diagnostic as CompilerDiagnostic } from './compiler';
import * as path from 'path';
import * as fs from 'fs';

// 创建服务器连接
const connection = createConnection(ProposedFeatures.all);

// 创建文档管理器
const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

// 编译器实例
let compiler: ChtlCompiler;

// 全局设置
interface ChtlSettings {
    compiler: {
        path: string;
        outputDirectory: string;
        debugMode: boolean;
        moduleSearchPaths: string[];
    };
    format: {
        enable: boolean;
        indentSize: number;
    };
    lint: {
        enable: boolean;
    };
}

const defaultSettings: ChtlSettings = {
    compiler: {
        path: '',
        outputDirectory: 'dist',
        debugMode: false,
        moduleSearchPaths: []
    },
    format: {
        enable: true,
        indentSize: 2
    },
    lint: {
        enable: true
    }
};

let globalSettings: ChtlSettings = defaultSettings;

// 缓存每个文档的设置
const documentSettings: Map<string, Thenable<ChtlSettings>> = new Map();

// 符号缓存
interface SymbolCache {
    templates: Map<string, SymbolInformation>;
    customs: Map<string, SymbolInformation>;
    namespaces: Map<string, SymbolInformation>;
    elements: Map<string, SymbolInformation>;
}

const symbolCache: Map<string, SymbolCache> = new Map();

connection.onInitialize((params: InitializeParams) => {
    const capabilities = params.capabilities;

    // 初始化编译器
    compiler = new ChtlCompiler({
        extensionPath: params.rootPath || ''
    } as any);

    const result: InitializeResult = {
        capabilities: {
            textDocumentSync: TextDocumentSyncKind.Incremental,
            // 代码补全
            completionProvider: {
                resolveProvider: true,
                triggerCharacters: ['@', '.', '{', '[', '<', ':', '-', '#']
            },
            // 悬停信息
            hoverProvider: true,
            // 定义跳转
            definitionProvider: true,
            // 查找引用
            referencesProvider: true,
            // 文档符号
            documentSymbolProvider: true,
            // 工作区符号
            workspaceSymbolProvider: true,
            // 代码动作（快速修复）
            codeActionProvider: {
                codeActionKinds: [
                    CodeActionKind.QuickFix,
                    CodeActionKind.Refactor,
                    CodeActionKind.RefactorExtract,
                    CodeActionKind.RefactorInline
                ]
            },
            // 格式化
            documentFormattingProvider: true,
            // 重命名
            renameProvider: {
                prepareProvider: true
            },
            // 执行命令
            executeCommandProvider: {
                commands: [
                    'chtl.extractComponent',
                    'chtl.inlineComponent',
                    'chtl.convertToTemplate',
                    'chtl.convertToCustom'
                ]
            },
            // 诊断
            diagnosticProvider: {
                identifier: 'chtl',
                interFileDependencies: true,
                workspaceDiagnostics: false
            }
        }
    };

    return result;
});

connection.onInitialized(() => {
    connection.client.register(DidChangeConfigurationNotification.type, undefined);
});

connection.onDidChangeConfiguration(change => {
    if (change.settings.chtl) {
        globalSettings = <ChtlSettings>(change.settings.chtl || defaultSettings);
    }
    
    // 重新验证所有打开的文档
    documents.all().forEach(validateDocument);
});

// 文档诊断
connection.languages.diagnostics.on(async (params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
        return { kind: DocumentDiagnosticReportKind.Full, items: [] } satisfies DocumentDiagnosticReport;
    }

    return {
        kind: DocumentDiagnosticReportKind.Full,
        items: await getDiagnostics(document)
    } satisfies DocumentDiagnosticReport;
});

async function getDiagnostics(document: TextDocument) {
    const settings = await getDocumentSettings(document.uri);
    if (!settings.lint.enable) {
        return [];
    }

    const diagnostics = [];
    const text = document.getText();
    
    // 使用编译器进行语法检查
    const result = await compiler.lint(document.uri);
    
    // 转换编译器诊断为 LSP 诊断
    for (const diag of result) {
        const diagnostic = {
            severity: diag.severity === 'error' ? DiagnosticSeverity.Error :
                     diag.severity === 'warning' ? DiagnosticSeverity.Warning :
                     DiagnosticSeverity.Information,
            range: {
                start: { line: diag.line - 1, character: diag.column - 1 },
                end: { line: diag.line - 1, character: diag.column }
            },
            message: diag.message,
            source: 'chtl',
            code: diag.code
        };
        diagnostics.push(diagnostic);
    }

    // 额外的语法检查
    const lines = text.split('\n');
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        
        // 检查未闭合的括号
        const openBraces = (line.match(/{/g) || []).length;
        const closeBraces = (line.match(/}/g) || []).length;
        if (openBraces !== closeBraces) {
            diagnostics.push({
                severity: DiagnosticSeverity.Error,
                range: {
                    start: { line: i, character: 0 },
                    end: { line: i, character: line.length }
                },
                message: 'Unmatched braces',
                source: 'chtl'
            });
        }
    }

    return diagnostics;
}

// 代码补全
connection.onCompletion(
    (_textDocumentPosition: TextDocumentPositionParams): CompletionItem[] => {
        const document = documents.get(_textDocumentPosition.textDocument.uri);
        if (!document) {
            return [];
        }

        const text = document.getText();
        const offset = document.offsetAt(_textDocumentPosition.position);
        const beforeText = text.substring(0, offset);
        const afterText = text.substring(offset);

        const completions: CompletionItem[] = [];

        // 检查触发字符
        const lastChar = beforeText[beforeText.length - 1];
        const lastTwoChars = beforeText.substring(beforeText.length - 2);

        // @ 触发的补全
        if (lastChar === '@') {
            completions.push(
                {
                    label: '@Style',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Style template or reference',
                    insertText: 'Style '
                },
                {
                    label: '@Element',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Element template or reference',
                    insertText: 'Element '
                },
                {
                    label: '@Var',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Variable template or reference',
                    insertText: 'Var '
                },
                {
                    label: '@Html',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Raw HTML embed',
                    insertText: 'Html '
                },
                {
                    label: '@JavaScript',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Raw JavaScript embed',
                    insertText: 'JavaScript '
                }
            );
        }

        // [ 触发的补全
        if (lastChar === '[') {
            completions.push(
                {
                    label: '[Configuration]',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Configuration block',
                    insertText: 'Configuration] {\n\t$0\n}'
                },
                {
                    label: '[Import]',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Import statement',
                    insertText: 'Import] '
                },
                {
                    label: '[Export]',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Export statement',
                    insertText: 'Export] {\n\t$0\n}'
                },
                {
                    label: '[Template]',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Template definition',
                    insertText: 'Template] @$0'
                },
                {
                    label: '[Custom]',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Custom component definition',
                    insertText: 'Custom] @$0'
                },
                {
                    label: '[Namespace]',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Namespace definition',
                    insertText: 'Namespace] '
                },
                {
                    label: '[Origin]',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Raw content embed',
                    insertText: 'Origin] @$0'
                },
                {
                    label: '[Info]',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Module information (CMOD only)',
                    insertText: 'Info] {\n\t$0\n}'
                }
            );
        }

        // {{ 触发的补全（CHTL JS 增强语法）
        if (lastTwoChars === '{{') {
            completions.push(
                {
                    label: '{{&}}',
                    kind: CompletionItemKind.Snippet,
                    detail: 'Current element reference',
                    insertText: '&}}'
                },
                {
                    label: '{{selector}}',
                    kind: CompletionItemKind.Snippet,
                    detail: 'Enhanced selector',
                    insertText: '${1:selector}}}'
                }
            );
        }

        // -> 触发的补全
        if (lastTwoChars === '->') {
            completions.push(
                {
                    label: 'listen',
                    kind: CompletionItemKind.Method,
                    detail: 'Add event listeners',
                    insertText: 'listen({\n\t${1:event}: function(e) {\n\t\t$0\n\t}\n})'
                },
                {
                    label: 'animate',
                    kind: CompletionItemKind.Method,
                    detail: 'Animate element',
                    insertText: 'animate({\n\ttarget: "${1:property}",\n\tfrom: ${2:0},\n\tto: ${3:100},\n\tduration: ${4:1000}\n})'
                },
                {
                    label: 'delegate',
                    kind: CompletionItemKind.Method,
                    detail: 'Event delegation',
                    insertText: 'delegate("${1:selector}", {\n\t${2:event}: function(e) {\n\t\t$0\n\t}\n})'
                },
                {
                    label: 'addClass',
                    kind: CompletionItemKind.Method,
                    detail: 'Add CSS class',
                    insertText: 'addClass("${1:className}")'
                },
                {
                    label: 'removeClass',
                    kind: CompletionItemKind.Method,
                    detail: 'Remove CSS class',
                    insertText: 'removeClass("${1:className}")'
                },
                {
                    label: 'toggleClass',
                    kind: CompletionItemKind.Method,
                    detail: 'Toggle CSS class',
                    insertText: 'toggleClass("${1:className}")'
                }
            );
        }

        // 通用关键字补全
        if (!/[@\[{]/.test(lastChar)) {
            completions.push(
                {
                    label: 'inherit',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Inherit from template or custom',
                    insertText: 'inherit '
                },
                {
                    label: 'delete',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Delete inherited elements',
                    insertText: 'delete '
                },
                {
                    label: 'insert',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Insert elements',
                    insertText: 'insert ${1|after,before,replace,at top,at bottom|} '
                },
                {
                    label: 'except',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Add constraints',
                    insertText: 'except '
                },
                {
                    label: 'style',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Local style block',
                    insertText: 'style {\n\t$0\n}'
                },
                {
                    label: 'script',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Local script block',
                    insertText: 'script {\n\t$0\n}'
                },
                {
                    label: 'text',
                    kind: CompletionItemKind.Keyword,
                    detail: 'Text content',
                    insertText: 'text { "$0" }'
                }
            );
        }

        return completions;
    }
);

// 补全项解析
connection.onCompletionResolve(
    (item: CompletionItem): CompletionItem => {
        // 添加文档
        switch (item.label) {
            case '@Style':
                item.documentation = 'Creates a style template or references an existing style';
                break;
            case '@Element':
                item.documentation = 'Creates an element template or references an existing element';
                break;
            case 'inherit':
                item.documentation = 'Inherits properties from a template or custom component';
                break;
            case 'listen':
                item.documentation = 'Adds event listeners to the element. Supports multiple events in a single call.';
                break;
        }
        return item;
    }
);

// 悬停信息
connection.onHover(
    async (params: TextDocumentPositionParams): Promise<Hover | null> => {
        const document = documents.get(params.textDocument.uri);
        if (!document) {
            return null;
        }

        const text = document.getText();
        const offset = document.offsetAt(params.position);
        
        // 获取当前位置的单词
        const wordRange = getWordRangeAtPosition(document, params.position);
        if (!wordRange) {
            return null;
        }

        const word = text.substring(
            document.offsetAt(wordRange.start),
            document.offsetAt(wordRange.end)
        );

        // 提供悬停信息
        const hoverInfo = getHoverInfo(word);
        if (hoverInfo) {
            return {
                contents: hoverInfo,
                range: wordRange
            };
        }

        return null;
    }
);

// 定义跳转
connection.onDefinition(
    async (params: TextDocumentPositionParams): Promise<Definition | null> => {
        const document = documents.get(params.textDocument.uri);
        if (!document) {
            return null;
        }

        const text = document.getText();
        const wordRange = getWordRangeAtPosition(document, params.position);
        if (!wordRange) {
            return null;
        }

        const word = text.substring(
            document.offsetAt(wordRange.start),
            document.offsetAt(wordRange.end)
        );

        // 查找定义
        const cache = symbolCache.get(params.textDocument.uri);
        if (cache) {
            // 查找模板定义
            const template = cache.templates.get(word);
            if (template) {
                return Location.create(template.location.uri, template.location.range);
            }

            // 查找自定义组件定义
            const custom = cache.customs.get(word);
            if (custom) {
                return Location.create(custom.location.uri, custom.location.range);
            }
        }

        return null;
    }
);

// 查找引用
connection.onReferences(
    async (params) => {
        const document = documents.get(params.textDocument.uri);
        if (!document) {
            return null;
        }

        const wordRange = getWordRangeAtPosition(document, params.position);
        if (!wordRange) {
            return null;
        }

        const word = document.getText(wordRange);
        const references: Location[] = [];

        // 在所有文档中查找引用
        for (const doc of documents.all()) {
            const text = doc.getText();
            const regex = new RegExp(`\\b${word}\\b`, 'g');
            let match;

            while ((match = regex.exec(text)) !== null) {
                const startPos = doc.positionAt(match.index);
                const endPos = doc.positionAt(match.index + word.length);
                
                references.push({
                    uri: doc.uri,
                    range: { start: startPos, end: endPos }
                });
            }
        }

        return references;
    }
);

// 文档符号
connection.onDocumentSymbol(
    async (params: DocumentSymbolParams): Promise<SymbolInformation[]> => {
        const document = documents.get(params.textDocument.uri);
        if (!document) {
            return [];
        }

        const symbols: SymbolInformation[] = [];
        const text = document.getText();
        
        // 解析文档并提取符号
        const cache: SymbolCache = {
            templates: new Map(),
            customs: new Map(),
            namespaces: new Map(),
            elements: new Map()
        };

        // 查找模板
        const templateRegex = /\[Template\]\s*@(\w+)\s+(\w+)/g;
        let match;
        while ((match = templateRegex.exec(text)) !== null) {
            const type = match[1];
            const name = match[2];
            const position = document.positionAt(match.index);
            
            const symbol: SymbolInformation = {
                name: `${name} (${type})`,
                kind: SymbolKind.Class,
                location: {
                    uri: params.textDocument.uri,
                    range: {
                        start: position,
                        end: document.positionAt(match.index + match[0].length)
                    }
                }
            };
            
            symbols.push(symbol);
            cache.templates.set(name, symbol);
        }

        // 查找自定义组件
        const customRegex = /\[Custom\]\s*@(\w+)\s+(\w+)/g;
        while ((match = customRegex.exec(text)) !== null) {
            const type = match[1];
            const name = match[2];
            const position = document.positionAt(match.index);
            
            const symbol: SymbolInformation = {
                name: `${name} (Custom ${type})`,
                kind: SymbolKind.Class,
                location: {
                    uri: params.textDocument.uri,
                    range: {
                        start: position,
                        end: document.positionAt(match.index + match[0].length)
                    }
                }
            };
            
            symbols.push(symbol);
            cache.customs.set(name, symbol);
        }

        // 更新缓存
        symbolCache.set(params.textDocument.uri, cache);

        return symbols;
    }
);

// 工作区符号
connection.onWorkspaceSymbol(
    async (params: WorkspaceSymbolParams): Promise<WorkspaceSymbol[]> => {
        const symbols: WorkspaceSymbol[] = [];
        
        // 搜索所有缓存的符号
        for (const [uri, cache] of symbolCache) {
            // 搜索模板
            for (const [name, symbol] of cache.templates) {
                if (name.toLowerCase().includes(params.query.toLowerCase())) {
                    symbols.push(symbol);
                }
            }
            
            // 搜索自定义组件
            for (const [name, symbol] of cache.customs) {
                if (name.toLowerCase().includes(params.query.toLowerCase())) {
                    symbols.push(symbol);
                }
            }
        }
        
        return symbols;
    }
);

// 代码动作（快速修复和重构）
connection.onCodeAction(
    async (params: CodeActionParams): Promise<CodeAction[]> => {
        const document = documents.get(params.textDocument.uri);
        if (!document) {
            return [];
        }

        const codeActions: CodeAction[] = [];
        const text = document.getText();
        
        // 获取选中的文本
        const range = params.range;
        const selectedText = document.getText(range);

        // 提取组件
        if (selectedText.includes('{') && selectedText.includes('}')) {
            codeActions.push({
                title: 'Extract to Custom Component',
                kind: CodeActionKind.RefactorExtract,
                command: {
                    title: 'Extract Component',
                    command: 'chtl.extractComponent',
                    arguments: [params.textDocument.uri, range]
                }
            });
        }

        // 转换为模板
        if (selectedText.includes('[Custom]')) {
            codeActions.push({
                title: 'Convert to Template',
                kind: CodeActionKind.Refactor,
                command: {
                    title: 'Convert to Template',
                    command: 'chtl.convertToTemplate',
                    arguments: [params.textDocument.uri, range]
                }
            });
        }

        // 快速修复
        for (const diagnostic of params.context.diagnostics) {
            if (diagnostic.code === 'unmatched-brace') {
                codeActions.push({
                    title: 'Add missing closing brace',
                    kind: CodeActionKind.QuickFix,
                    diagnostics: [diagnostic],
                    edit: {
                        changes: {
                            [params.textDocument.uri]: [
                                {
                                    range: {
                                        start: diagnostic.range.end,
                                        end: diagnostic.range.end
                                    },
                                    newText: '}'
                                }
                            ]
                        }
                    }
                });
            }
        }

        return codeActions;
    }
);

// 执行命令
connection.onExecuteCommand(
    async (params: ExecuteCommandParams) => {
        switch (params.command) {
            case 'chtl.extractComponent':
                // 提取组件逻辑
                await extractComponent(params.arguments![0], params.arguments![1]);
                break;
            case 'chtl.convertToTemplate':
                // 转换为模板逻辑
                await convertToTemplate(params.arguments![0], params.arguments![1]);
                break;
        }
    }
);

// 格式化文档
connection.onDocumentFormatting(
    async (params: DocumentFormattingParams): Promise<TextEdit[]> => {
        const document = documents.get(params.textDocument.uri);
        if (!document) {
            return [];
        }

        const settings = await getDocumentSettings(params.textDocument.uri);
        if (!settings.format.enable) {
            return [];
        }

        const text = document.getText();
        const formatted = formatChtl(text, settings.format.indentSize);

        return [{
            range: {
                start: document.positionAt(0),
                end: document.positionAt(text.length)
            },
            newText: formatted
        }];
    }
);

// 文档更改时更新缓存
documents.onDidChangeContent(change => {
    validateDocument(change.document);
});

// 文档关闭时清理缓存
documents.onDidClose(e => {
    documentSettings.delete(e.document.uri);
    symbolCache.delete(e.document.uri);
});

// 辅助函数

async function getDocumentSettings(resource: string): Promise<ChtlSettings> {
    let result = documentSettings.get(resource);
    if (!result) {
        result = connection.workspace.getConfiguration({
            scopeUri: resource,
            section: 'chtl'
        });
        documentSettings.set(resource, result);
    }
    return result;
}

async function validateDocument(textDocument: TextDocument): Promise<void> {
    // 验证逻辑已移至诊断处理器
}

function getWordRangeAtPosition(document: TextDocument, position: Position): Range | null {
    const text = document.getText();
    const offset = document.offsetAt(position);
    
    // 查找单词边界
    let start = offset;
    let end = offset;
    
    const wordRegex = /[\w@#$]/;
    
    // 向前查找
    while (start > 0 && wordRegex.test(text[start - 1])) {
        start--;
    }
    
    // 向后查找
    while (end < text.length && wordRegex.test(text[end])) {
        end++;
    }
    
    if (start === end) {
        return null;
    }
    
    return {
        start: document.positionAt(start),
        end: document.positionAt(end)
    };
}

function getHoverInfo(word: string): string | null {
    const hoverData: { [key: string]: string } = {
        'Template': '**[Template]**\n\nDefines a reusable template component.\n\n```chtl\n[Template] @Style MyStyle {\n    color: red;\n}\n```',
        'Custom': '**[Custom]**\n\nDefines a customizable component.\n\n```chtl\n[Custom] @Element MyButton {\n    button {\n        text { "Click me" }\n    }\n}\n```',
        'inherit': '**inherit**\n\nInherits from another template or custom component.\n\n```chtl\ninherit @Style BaseStyle;\n```',
        'delete': '**delete**\n\nDeletes inherited elements or properties.\n\n```chtl\ndelete elementName;\ndelete @Style StyleName;\n```',
        'insert': '**insert**\n\nInserts new elements at specific positions.\n\n```chtl\ninsert after div[0] {\n    span { text { "New" } }\n}\n```',
        'listen': '**listen**\n\nCHTL JS method for adding event listeners.\n\n```javascript\n{{selector}}->listen({\n    click: function(e) { },\n    hover: function(e) { }\n});\n```',
        'animate': '**animate**\n\nCHTL JS method for animations.\n\n```javascript\n{{selector}}->animate({\n    target: "opacity",\n    from: 0,\n    to: 1,\n    duration: 1000\n});\n```'
    };

    return hoverData[word] || null;
}

function formatChtl(text: string, indentSize: number): string {
    // 简单的格式化实现
    const lines = text.split('\n');
    const formatted: string[] = [];
    let indentLevel = 0;
    const indent = ' '.repeat(indentSize);

    for (const line of lines) {
        const trimmed = line.trim();
        
        // 减少缩进
        if (trimmed.startsWith('}') || trimmed.startsWith(']')) {
            indentLevel = Math.max(0, indentLevel - 1);
        }
        
        // 添加缩进
        if (trimmed) {
            formatted.push(indent.repeat(indentLevel) + trimmed);
        } else {
            formatted.push('');
        }
        
        // 增加缩进
        if (trimmed.endsWith('{') || trimmed.endsWith('[')) {
            indentLevel++;
        }
    }

    return formatted.join('\n');
}

async function extractComponent(uri: string, range: Range): Promise<void> {
    // 提取组件的实现
    const document = documents.get(uri);
    if (!document) {
        return;
    }

    const text = document.getText(range);
    
    // 生成组件名称
    const componentName = 'ExtractedComponent';
    
    // 创建新的自定义组件
    const newComponent = `[Custom] @Element ${componentName} {\n${text}\n}\n\n`;
    
    // 替换原文本为组件引用
    const edit: TextEdit = {
        range: range,
        newText: `@Element ${componentName};`
    };

    // 应用编辑
    connection.workspace.applyEdit({
        documentChanges: [{
            textDocument: { uri, version: document.version },
            edits: [
                {
                    range: { start: { line: 0, character: 0 }, end: { line: 0, character: 0 } },
                    newText: newComponent
                },
                edit
            ]
        }]
    });
}

async function convertToTemplate(uri: string, range: Range): Promise<void> {
    // 转换为模板的实现
    const document = documents.get(uri);
    if (!document) {
        return;
    }

    const text = document.getText(range);
    
    // 将 [Custom] 替换为 [Template]
    const newText = text.replace(/\[Custom\]/g, '[Template]');
    
    const edit: TextEdit = {
        range: range,
        newText: newText
    };

    // 应用编辑
    connection.workspace.applyEdit({
        documentChanges: [{
            textDocument: { uri, version: document.version },
            edits: [edit]
        }]
    });
}

// 监听文档管理器
documents.listen(connection);

// 启动连接
connection.listen();