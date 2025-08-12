import {
    DebugSession,
    InitializedEvent,
    TerminatedEvent,
    StoppedEvent,
    BreakpointEvent,
    OutputEvent,
    Thread,
    StackFrame,
    Scope,
    Source,
    Handles,
    Breakpoint
} from '@vscode/debugadapter';
import { DebugProtocol } from '@vscode/debugprotocol';
import * as path from 'path';
import * as fs from 'fs';
import { Subject } from 'await-notify';
import { spawn, ChildProcess } from 'child_process';

interface ChtlBreakpoint {
    id: number;
    line: number;
    source: string;
    verified: boolean;
}

interface ChtlStackFrame {
    index: number;
    name: string;
    source: string;
    line: number;
    column: number;
}

export interface LaunchRequestArguments extends DebugProtocol.LaunchRequestArguments {
    /** 要调试的 CHTL 文件 */
    program: string;
    /** 是否在入口处停止 */
    stopOnEntry?: boolean;
    /** 调试输出目录 */
    outputDirectory?: string;
    /** 是否启用源映射 */
    sourceMaps?: boolean;
    /** 浏览器路径（用于预览） */
    browserPath?: string;
}

export class ChtlDebugSession extends DebugSession {
    private static threadID = 1;
    
    private configurationDone = new Subject();
    
    private breakpoints = new Map<string, ChtlBreakpoint[]>();
    private breakpointId = 1;
    
    private runtime: ChtlRuntime;
    private variableHandles = new Handles<string>();
    
    public constructor() {
        super();
        
        this.setDebuggerLinesStartAt1(true);
        this.setDebuggerColumnsStartAt1(true);
        
        this.runtime = new ChtlRuntime();
        
        // 设置运行时事件处理
        this.runtime.on('stopOnEntry', () => {
            this.sendEvent(new StoppedEvent('entry', ChtlDebugSession.threadID));
        });
        
        this.runtime.on('stopOnBreakpoint', () => {
            this.sendEvent(new StoppedEvent('breakpoint', ChtlDebugSession.threadID));
        });
        
        this.runtime.on('stopOnException', (exception) => {
            this.sendEvent(new StoppedEvent('exception', ChtlDebugSession.threadID, exception));
        });
        
        this.runtime.on('breakpointValidated', (bp: ChtlBreakpoint) => {
            this.sendEvent(new BreakpointEvent('changed', { id: bp.id, verified: bp.verified } as DebugProtocol.Breakpoint));
        });
        
        this.runtime.on('output', (text, category) => {
            const event: DebugProtocol.OutputEvent = new OutputEvent(`${text}\n`);
            if (category) {
                event.body.category = category;
            }
            this.sendEvent(event);
        });
        
        this.runtime.on('end', () => {
            this.sendEvent(new TerminatedEvent());
        });
    }
    
    protected initializeRequest(response: DebugProtocol.InitializeResponse, args: DebugProtocol.InitializeRequestArguments): void {
        response.body = response.body || {};
        
        // 调试器功能
        response.body.supportsConfigurationDoneRequest = true;
        response.body.supportsEvaluateForHovers = true;
        response.body.supportsStepBack = false;
        response.body.supportsDataBreakpoints = false;
        response.body.supportsCompletionsRequest = true;
        response.body.completionTriggerCharacters = [".", "[", "{", "@"];
        response.body.supportsBreakpointLocationsRequest = true;
        response.body.supportsStepInTargetsRequest = false;
        response.body.supportsExceptionOptions = false;
        response.body.supportsExceptionInfoRequest = false;
        response.body.supportsSetVariable = true;
        response.body.supportsSetExpression = false;
        response.body.supportsRestartRequest = true;
        response.body.supportsGotoTargetsRequest = false;
        response.body.supportsDelayedStackTraceLoading = false;
        response.body.supportsLoadedSourcesRequest = false;
        response.body.supportsLogPoints = false;
        response.body.supportsTerminateThreadsRequest = false;
        response.body.supportsTerminateRequest = true;
        response.body.supportsConditionalBreakpoints = false;
        response.body.supportsHitConditionalBreakpoints = false;
        response.body.supportsFunctionBreakpoints = false;
        
        this.sendResponse(response);
        this.sendEvent(new InitializedEvent());
    }
    
    protected configurationDoneRequest(response: DebugProtocol.ConfigurationDoneResponse, args: DebugProtocol.ConfigurationDoneArguments): void {
        super.configurationDoneRequest(response, args);
        this.configurationDone.notify();
    }
    
    protected async launchRequest(response: DebugProtocol.LaunchResponse, args: LaunchRequestArguments) {
        // 等待配置完成
        await this.configurationDone.wait(1000);
        
        // 启动调试
        await this.runtime.start(args.program, !!args.stopOnEntry, args.outputDirectory || 'dist');
        
        this.sendResponse(response);
    }
    
    protected setBreakPointsRequest(response: DebugProtocol.SetBreakpointsResponse, args: DebugProtocol.SetBreakpointsArguments): void {
        const path = args.source.path as string;
        const clientLines = args.lines || [];
        
        // 清除旧断点
        this.runtime.clearBreakpoints(path);
        
        // 设置新断点
        const actualBreakpoints = clientLines.map(l => {
            const bp = this.runtime.setBreakpoint(path, this.convertClientLineToDebugger(l));
            return {
                id: bp.id,
                verified: bp.verified,
                line: this.convertDebuggerLineToClient(bp.line)
            } as DebugProtocol.Breakpoint;
        });
        
        response.body = {
            breakpoints: actualBreakpoints
        };
        this.sendResponse(response);
    }
    
    protected threadsRequest(response: DebugProtocol.ThreadsResponse): void {
        response.body = {
            threads: [
                new Thread(ChtlDebugSession.threadID, "thread 1")
            ]
        };
        this.sendResponse(response);
    }
    
    protected stackTraceRequest(response: DebugProtocol.StackTraceResponse, args: DebugProtocol.StackTraceArguments): void {
        const startFrame = typeof args.startFrame === 'number' ? args.startFrame : 0;
        const maxLevels = typeof args.levels === 'number' ? args.levels : 1000;
        const endFrame = startFrame + maxLevels;
        
        const stk = this.runtime.stack(startFrame, endFrame);
        
        response.body = {
            stackFrames: stk.frames.map(f => {
                const source = this.createSource(f.source);
                return new StackFrame(f.index, f.name, source, this.convertDebuggerLineToClient(f.line));
            }),
            totalFrames: stk.count
        };
        this.sendResponse(response);
    }
    
    protected scopesRequest(response: DebugProtocol.ScopesResponse, args: DebugProtocol.ScopesArguments): void {
        response.body = {
            scopes: [
                new Scope("Local", this.variableHandles.create("local"), false),
                new Scope("Global", this.variableHandles.create("global"), true)
            ]
        };
        this.sendResponse(response);
    }
    
    protected async variablesRequest(response: DebugProtocol.VariablesResponse, args: DebugProtocol.VariablesArguments, request?: DebugProtocol.Request) {
        const variables: DebugProtocol.Variable[] = [];
        
        const scope = this.variableHandles.get(args.variablesReference);
        if (scope === 'local' || scope === 'global') {
            const vars = await this.runtime.getVariables(scope);
            variables.push(...vars.map(v => ({
                name: v.name,
                value: v.value,
                type: v.type,
                variablesReference: 0
            })));
        }
        
        response.body = {
            variables: variables
        };
        this.sendResponse(response);
    }
    
    protected continueRequest(response: DebugProtocol.ContinueResponse, args: DebugProtocol.ContinueArguments): void {
        this.runtime.continue();
        this.sendResponse(response);
    }
    
    protected nextRequest(response: DebugProtocol.NextResponse, args: DebugProtocol.NextArguments): void {
        this.runtime.step();
        this.sendResponse(response);
    }
    
    protected stepInRequest(response: DebugProtocol.StepInResponse, args: DebugProtocol.StepInArguments): void {
        this.runtime.stepIn();
        this.sendResponse(response);
    }
    
    protected stepOutRequest(response: DebugProtocol.StepOutResponse, args: DebugProtocol.StepOutArguments): void {
        this.runtime.stepOut();
        this.sendResponse(response);
    }
    
    protected evaluateRequest(response: DebugProtocol.EvaluateResponse, args: DebugProtocol.EvaluateArguments): void {
        let result = '';
        
        if (args.context === 'hover' || args.context === 'watch') {
            result = this.runtime.evaluate(args.expression);
        }
        
        response.body = {
            result: result,
            variablesReference: 0
        };
        this.sendResponse(response);
    }
    
    protected restartRequest(response: DebugProtocol.RestartResponse, args: DebugProtocol.RestartArguments): void {
        this.runtime.restart();
        this.sendResponse(response);
    }
    
    protected terminateRequest(response: DebugProtocol.TerminateResponse, args: DebugProtocol.TerminateArguments): void {
        this.runtime.terminate();
        this.sendResponse(response);
    }
    
    private createSource(filePath: string): Source {
        return new Source(path.basename(filePath), this.convertDebuggerPathToClient(filePath));
    }
}

/**
 * CHTL 运行时 - 模拟调试环境
 */
class ChtlRuntime extends EventEmitter {
    private sourceFile: string = '';
    private currentLine = 0;
    private breakpoints: ChtlBreakpoint[] = [];
    private variables = new Map<string, any>();
    private process: ChildProcess | null = null;
    
    constructor() {
        super();
    }
    
    async start(program: string, stopOnEntry: boolean, outputDir: string) {
        this.sourceFile = program;
        this.currentLine = 0;
        
        // 编译 CHTL 文件
        await this.compile(program, outputDir);
        
        if (stopOnEntry) {
            this.sendEvent('stopOnEntry');
        } else {
            this.continue();
        }
    }
    
    private async compile(program: string, outputDir: string) {
        // 使用 CHTL 编译器编译文件
        const compiler = this.findCompiler();
        if (!compiler) {
            this.sendEvent('output', 'Error: CHTL compiler not found', 'stderr');
            this.sendEvent('end');
            return;
        }
        
        return new Promise<void>((resolve, reject) => {
            const args = [program, '-o', outputDir, '--source-map'];
            this.process = spawn(compiler, args);
            
            this.process.stdout?.on('data', (data) => {
                this.sendEvent('output', data.toString(), 'stdout');
            });
            
            this.process.stderr?.on('data', (data) => {
                this.sendEvent('output', data.toString(), 'stderr');
            });
            
            this.process.on('close', (code) => {
                if (code === 0) {
                    this.sendEvent('output', 'Compilation successful', 'console');
                    resolve();
                } else {
                    this.sendEvent('output', `Compilation failed with code ${code}`, 'stderr');
                    reject(new Error('Compilation failed'));
                }
            });
        });
    }
    
    private findCompiler(): string | null {
        // 查找编译器路径（简化版）
        const possiblePaths = [
            '/workspace/build/chtl',
            '/workspace/vscode-extension/chtl-lang/compilers/linux-x64/chtl'
        ];
        
        for (const path of possiblePaths) {
            if (fs.existsSync(path)) {
                return path;
            }
        }
        
        return null;
    }
    
    continue() {
        this.run();
    }
    
    step() {
        this.run(true);
    }
    
    stepIn() {
        this.run(true);
    }
    
    stepOut() {
        this.run(true);
    }
    
    private run(stepMode = false) {
        if (stepMode) {
            this.currentLine++;
            this.sendEvent('stopOnBreakpoint');
        } else {
            // 检查断点
            const breakpoint = this.breakpoints.find(bp => bp.line === this.currentLine);
            if (breakpoint) {
                this.sendEvent('stopOnBreakpoint');
            } else {
                this.currentLine++;
                if (this.currentLine > 100) { // 模拟结束
                    this.sendEvent('end');
                } else {
                    setTimeout(() => this.run(), 10);
                }
            }
        }
    }
    
    setBreakpoint(path: string, line: number): ChtlBreakpoint {
        const bp: ChtlBreakpoint = {
            id: this.breakpoints.length + 1,
            line: line,
            source: path,
            verified: true
        };
        this.breakpoints.push(bp);
        this.sendEvent('breakpointValidated', bp);
        return bp;
    }
    
    clearBreakpoints(path: string) {
        this.breakpoints = this.breakpoints.filter(bp => bp.source !== path);
    }
    
    stack(startFrame: number, endFrame: number): { frames: ChtlStackFrame[], count: number } {
        const frames: ChtlStackFrame[] = [];
        
        // 模拟调用栈
        frames.push({
            index: 0,
            name: 'main',
            source: this.sourceFile,
            line: this.currentLine,
            column: 0
        });
        
        return {
            frames: frames,
            count: frames.length
        };
    }
    
    getVariables(scope: string): Array<{name: string, value: string, type: string}> {
        const vars: Array<{name: string, value: string, type: string}> = [];
        
        if (scope === 'local') {
            vars.push({
                name: 'currentElement',
                value: '<div>',
                type: 'Element'
            });
        } else {
            vars.push({
                name: 'document',
                value: 'HTMLDocument',
                type: 'object'
            });
        }
        
        return vars;
    }
    
    evaluate(expression: string): string {
        return `evaluated: ${expression}`;
    }
    
    restart() {
        this.currentLine = 0;
        this.continue();
    }
    
    terminate() {
        if (this.process) {
            this.process.kill();
        }
        this.sendEvent('end');
    }
    
    private sendEvent(event: string, ...args: any[]) {
        setTimeout(() => {
            this.emit(event, ...args);
        }, 0);
    }
}

// 导入 EventEmitter
import { EventEmitter } from 'events';