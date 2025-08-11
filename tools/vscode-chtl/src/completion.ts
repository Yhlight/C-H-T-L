import * as vscode from 'vscode';

export class CHTLCompletionProvider implements vscode.CompletionItemProvider {
    provideCompletionItems(
        document: vscode.TextDocument,
        position: vscode.Position,
        token: vscode.CancellationToken,
        context: vscode.CompletionContext
    ): vscode.ProviderResult<vscode.CompletionItem[] | vscode.CompletionList> {
        const linePrefix = document.lineAt(position).text.substr(0, position.character);
        
        // 标签补全
        if (context.triggerKind === vscode.CompletionTriggerKind.Invoke || !context.triggerCharacter) {
            return this.getElementCompletions();
        }

        // [块] 补全
        if (context.triggerCharacter === '[' || linePrefix.endsWith('[')) {
            return this.getBlockCompletions();
        }

        // @ 类型补全
        if (context.triggerCharacter === '@' || linePrefix.endsWith('@')) {
            return this.getTypeCompletions();
        }

        // CHTL JS 特殊语法补全
        if (context.triggerCharacter === '{' && linePrefix.endsWith('{')) {
            return this.getChtlJsCompletions();
        }

        // CJmod 语法补全
        if (this.isInScriptBlock(document, position)) {
            const cjmodCompletions = this.getCJmodCompletions(document);
            if (cjmodCompletions.length > 0) {
                return cjmodCompletions;
            }
        }

        return [];
    }

    private getElementCompletions(): vscode.CompletionItem[] {
        const elements = ['div', 'span', 'button', 'input', 'form', 'section', 'article', 'header', 'footer', 'nav', 'main', 'aside', 'h1', 'h2', 'h3', 'p', 'a', 'img', 'ul', 'ol', 'li', 'table', 'script', 'style'];
        
        return elements.map(el => {
            const item = new vscode.CompletionItem(el, vscode.CompletionItemKind.Snippet);
            item.insertText = new vscode.SnippetString(`${el} {\n\t$0\n}`);
            item.documentation = `Create a ${el} element`;
            return item;
        });
    }

    private getBlockCompletions(): vscode.CompletionItem[] {
        const blocks = [
            { label: 'Template', snippet: '[Template] @${1:Element} ${2:Name} {\n\t$0\n}', doc: 'Define a template component' },
            { label: 'Custom', snippet: '[Custom] @${1:Element} ${2:Name} {\n\t$0\n}', doc: 'Define a custom component' },
            { label: 'Style', snippet: '[Style] {\n\t$0\n}', doc: 'Global style block' },
            { label: 'Import', snippet: '[Import] @${1:Chtl} from "${2:path}";', doc: 'Import statement' },
            { label: 'Import CJmod', snippet: '[Import] @CJmod from "${1:builtin:reactive}";', doc: 'Import CJmod module' },
            { label: 'Config', snippet: '[Config] ${1:Name} {\n\t$0\n}', doc: 'Configuration block' },
            { label: 'Info', snippet: '[Info] {\n\tname: "${1:ModuleName}"\n\tversion: "${2:1.0.0}"\n\t$0\n}', doc: 'Module information' }
        ];

        return blocks.map(block => {
            const item = new vscode.CompletionItem(block.label, vscode.CompletionItemKind.Snippet);
            item.insertText = new vscode.SnippetString(block.snippet);
            item.documentation = block.doc;
            return item;
        });
    }

    private getTypeCompletions(): vscode.CompletionItem[] {
        const types = [
            { label: '@Element', doc: 'Element type' },
            { label: '@Style', doc: 'Style type' },
            { label: '@Var', doc: 'Variable type' },
            { label: '@Chtl', doc: 'CHTL module import' },
            { label: '@CJmod', doc: 'CJmod module import' },
            { label: '@Custom', doc: 'Custom component reference' },
            { label: '@Template', doc: 'Template component reference' }
        ];

        return types.map(type => {
            const item = new vscode.CompletionItem(type.label, vscode.CompletionItemKind.Keyword);
            item.documentation = type.doc;
            return item;
        });
    }

    private getChtlJsCompletions(): vscode.CompletionItem[] {
        const items: vscode.CompletionItem[] = [];

        // {{}} 语法
        const selfRef = new vscode.CompletionItem('{{&}}', vscode.CompletionItemKind.Snippet);
        selfRef.insertText = '{{&}}';
        selfRef.documentation = 'Reference to current component';
        items.push(selfRef);

        const idRef = new vscode.CompletionItem('{{#id}}', vscode.CompletionItemKind.Snippet);
        idRef.insertText = new vscode.SnippetString('{{#${1:id}}}');
        idRef.documentation = 'Reference element by ID';
        items.push(idRef);

        const classRef = new vscode.CompletionItem('{{.class}}', vscode.CompletionItemKind.Snippet);
        classRef.insertText = new vscode.SnippetString('{{.${1:class}}}');
        classRef.documentation = 'Reference elements by class';
        items.push(classRef);

        return items;
    }

    private getCJmodCompletions(document: vscode.TextDocument): vscode.CompletionItem[] {
        const items: vscode.CompletionItem[] = [];
        const imports = this.getImportedCJmods(document);

        // Reactive 模块语法
        if (imports.includes('reactive')) {
            const reactive = new vscode.CompletionItem(':=', vscode.CompletionItemKind.Operator);
            reactive.insertText = new vscode.SnippetString('${1:variable} := ${2:value};');
            reactive.documentation = 'Reactive variable declaration';
            items.push(reactive);

            const computed = new vscode.CompletionItem('=>', vscode.CompletionItemKind.Operator);
            computed.insertText = new vscode.SnippetString('${1:computed} => ${2:expression};');
            computed.documentation = 'Computed property';
            items.push(computed);

            const watch = new vscode.CompletionItem('watch', vscode.CompletionItemKind.Keyword);
            watch.insertText = new vscode.SnippetString('watch ${1:variable} {\n\t$0\n}');
            watch.documentation = 'Watch reactive variable';
            items.push(watch);
        }

        // Animation 模块语法
        if (imports.includes('animation')) {
            const animate = new vscode.CompletionItem('~>', vscode.CompletionItemKind.Operator);
            animate.insertText = new vscode.SnippetString('${1:element} ~> ${2:animation}');
            animate.documentation = 'Animation chain';
            items.push(animate);

            const delay = new vscode.CompletionItem('delay', vscode.CompletionItemKind.Function);
            delay.insertText = new vscode.SnippetString('delay(${1:1000})');
            delay.documentation = 'Delay execution';
            items.push(delay);
        }

        // Pipeline 模块语法
        if (imports.includes('pipeline')) {
            const pipe = new vscode.CompletionItem('|>', vscode.CompletionItemKind.Operator);
            pipe.insertText = ' |> ';
            pipe.documentation = 'Pipeline operator';
            items.push(pipe);
        }

        return items;
    }

    private isInScriptBlock(document: vscode.TextDocument, position: vscode.Position): boolean {
        let inScript = false;
        let braceCount = 0;

        for (let i = 0; i < position.line; i++) {
            const line = document.lineAt(i).text;
            
            if (line.includes('script') && line.includes('{')) {
                inScript = true;
                braceCount = 1;
            } else if (inScript) {
                for (const char of line) {
                    if (char === '{') braceCount++;
                    else if (char === '}') {
                        braceCount--;
                        if (braceCount === 0) inScript = false;
                    }
                }
            }
        }

        return inScript;
    }

    private getImportedCJmods(document: vscode.TextDocument): string[] {
        const imports: string[] = [];
        const text = document.getText();
        const importRegex = /\[Import\]\s+@CJmod\s+from\s+"([^"]+)"/g;
        
        let match;
        while ((match = importRegex.exec(text)) !== null) {
            const path = match[1];
            if (path.startsWith('builtin:')) {
                imports.push(path.substring(8));
            }
        }

        return imports;
    }
}