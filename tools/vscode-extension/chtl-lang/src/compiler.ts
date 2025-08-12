import * as vscode from 'vscode';
import * as path from 'path';
import * as fs from 'fs';
import { spawn, ChildProcess } from 'child_process';
import * as os from 'os';

export interface CompileResult {
    success: boolean;
    output?: string;
    error?: string;
    diagnostics?: Diagnostic[];
}

export interface Diagnostic {
    file: string;
    line: number;
    column: number;
    severity: 'error' | 'warning' | 'info';
    message: string;
    code?: string;
}

export class ChtlCompiler {
    private compilerPath: string | undefined;
    private extensionPath: string;

    constructor(context: vscode.ExtensionContext) {
        this.extensionPath = context.extensionPath;
        this.compilerPath = this.detectCompilerPath();
    }

    private detectCompilerPath(): string | undefined {
        // First check if user has specified a custom compiler path
        const config = vscode.workspace.getConfiguration('chtl');
        const customPath = config.get<string>('compiler.path');
        
        if (customPath && fs.existsSync(customPath)) {
            return customPath;
        }

        // Otherwise, use bundled compiler based on platform
        const platform = os.platform();
        const arch = os.arch();
        let binaryName = 'chtl';
        
        if (platform === 'win32') {
            binaryName = 'chtl.exe';
        }

        const compilerDir = path.join(this.extensionPath, 'compilers');
        let platformDir: string;

        switch (platform) {
            case 'darwin':
                platformDir = arch === 'arm64' ? 'darwin-arm64' : 'darwin-x64';
                break;
            case 'linux':
                platformDir = arch === 'arm64' ? 'linux-arm64' : 'linux-x64';
                break;
            case 'win32':
                platformDir = arch === 'arm' ? 'win32-arm64' : 'win32-x64';
                break;
            default:
                vscode.window.showErrorMessage(`Unsupported platform: ${platform}-${arch}`);
                return undefined;
        }

        const compilerPath = path.join(compilerDir, platformDir, binaryName);
        
        // Check if the bundled compiler exists
        if (!fs.existsSync(compilerPath)) {
            // Try fallback to common binary
            const fallbackPath = path.join(compilerDir, binaryName);
            if (fs.existsSync(fallbackPath)) {
                return fallbackPath;
            }
            
            vscode.window.showWarningMessage(
                `CHTL compiler not found for ${platform}-${arch}. Please install CHTL compiler manually and set the path in settings.`
            );
            return undefined;
        }

        // Make sure the binary is executable on Unix-like systems
        if (platform !== 'win32') {
            try {
                fs.chmodSync(compilerPath, '755');
            } catch (error) {
                console.error('Failed to make compiler executable:', error);
            }
        }

        return compilerPath;
    }

    public async compile(filePath: string, options?: {
        outputDir?: string;
        debug?: boolean;
        moduleSearchPaths?: string[];
    }): Promise<CompileResult> {
        if (!this.compilerPath) {
            return {
                success: false,
                error: 'CHTL compiler not found. Please install it manually and set the path in settings.'
            };
        }

        const config = vscode.workspace.getConfiguration('chtl.compiler');
        const outputDir = options?.outputDir || config.get<string>('outputDirectory') || 'dist';
        const debug = options?.debug || config.get<boolean>('debugMode') || false;
        const moduleSearchPaths = options?.moduleSearchPaths || config.get<string[]>('moduleSearchPaths') || [];

        const args: string[] = [filePath];
        
        // Add output directory
        if (outputDir) {
            args.push('-o', outputDir);
        }

        // Add debug flag
        if (debug) {
            args.push('--debug');
        }

        // Add module search paths
        for (const modulePath of moduleSearchPaths) {
            args.push('--module-path', modulePath);
        }

        return new Promise((resolve) => {
            const output: string[] = [];
            const errors: string[] = [];
            const diagnostics: Diagnostic[] = [];

            const process = spawn(this.compilerPath!, args, {
                cwd: vscode.workspace.rootPath || path.dirname(filePath)
            });

            process.stdout.on('data', (data) => {
                const text = data.toString();
                output.push(text);
                
                // Parse compiler output for diagnostics
                const lines = text.split('\n');
                for (const line of lines) {
                    const diagnostic = this.parseDiagnostic(line);
                    if (diagnostic) {
                        diagnostics.push(diagnostic);
                    }
                }
            });

            process.stderr.on('data', (data) => {
                const text = data.toString();
                errors.push(text);
                
                // Parse error output for diagnostics
                const lines = text.split('\n');
                for (const line of lines) {
                    const diagnostic = this.parseDiagnostic(line);
                    if (diagnostic) {
                        diagnostics.push(diagnostic);
                    }
                }
            });

            process.on('close', (code) => {
                if (code === 0) {
                    resolve({
                        success: true,
                        output: output.join(''),
                        diagnostics
                    });
                } else {
                    resolve({
                        success: false,
                        output: output.join(''),
                        error: errors.join('') || `Compiler exited with code ${code}`,
                        diagnostics
                    });
                }
            });

            process.on('error', (err) => {
                resolve({
                    success: false,
                    error: `Failed to start compiler: ${err.message}`
                });
            });
        });
    }

    private parseDiagnostic(line: string): Diagnostic | null {
        // Parse CHTL compiler error format
        // Example: "error[E001]: test.chtl:10:5: Unexpected token '{'"
        const errorPattern = /^(error|warning|info)(?:\[([^\]]+)\])?: ([^:]+):(\d+):(\d+): (.+)$/;
        const match = line.match(errorPattern);
        
        if (match) {
            return {
                severity: match[1] as 'error' | 'warning' | 'info',
                code: match[2],
                file: match[3],
                line: parseInt(match[4]),
                column: parseInt(match[5]),
                message: match[6]
            };
        }

        // Alternative format without error code
        const simplePattern = /^(error|warning|info): ([^:]+):(\d+):(\d+): (.+)$/;
        const simpleMatch = line.match(simplePattern);
        
        if (simpleMatch) {
            return {
                severity: simpleMatch[1] as 'error' | 'warning' | 'info',
                file: simpleMatch[2],
                line: parseInt(simpleMatch[3]),
                column: parseInt(simpleMatch[4]),
                message: simpleMatch[5]
            };
        }

        return null;
    }

    public async lint(filePath: string): Promise<Diagnostic[]> {
        // Use compile with --lint flag (if supported)
        const result = await this.compile(filePath, { debug: false });
        return result.diagnostics || [];
    }

    public async packCmod(moduleDir: string): Promise<CompileResult> {
        if (!this.compilerPath) {
            return {
                success: false,
                error: 'CHTL compiler not found.'
            };
        }

        const args = ['--pack-cmod', moduleDir];

        return new Promise((resolve) => {
            const output: string[] = [];
            const errors: string[] = [];

            const process = spawn(this.compilerPath!, args, {
                cwd: vscode.workspace.rootPath || path.dirname(moduleDir)
            });

            process.stdout.on('data', (data) => {
                output.push(data.toString());
            });

            process.stderr.on('data', (data) => {
                errors.push(data.toString());
            });

            process.on('close', (code) => {
                if (code === 0) {
                    resolve({
                        success: true,
                        output: output.join('')
                    });
                } else {
                    resolve({
                        success: false,
                        error: errors.join('') || `Packer exited with code ${code}`
                    });
                }
            });

            process.on('error', (err) => {
                resolve({
                    success: false,
                    error: `Failed to start packer: ${err.message}`
                });
            });
        });
    }

    public isAvailable(): boolean {
        return this.compilerPath !== undefined;
    }

    public getCompilerPath(): string | undefined {
        return this.compilerPath;
    }
}