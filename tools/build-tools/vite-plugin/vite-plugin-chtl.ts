import { Plugin, ResolvedConfig } from 'vite';
import { execSync } from 'child_process';
import * as path from 'path';
import * as fs from 'fs';

interface CHTLPluginOptions {
    compilerPath?: string;
    sourceMap?: boolean;
    cjmodAutoLoad?: boolean;
    hot?: boolean;
}

export default function chtlPlugin(options: CHTLPluginOptions = {}): Plugin {
    const {
        compilerPath = 'chtl',
        sourceMap = true,
        cjmodAutoLoad = true,
        hot = true
    } = options;

    let config: ResolvedConfig;
    const compiledCache = new Map<string, { code: string; map?: string }>();

    return {
        name: 'vite-plugin-chtl',

        configResolved(resolvedConfig) {
            config = resolvedConfig;
        },

        resolveId(id) {
            // 处理 CJmod 导入
            if (id.startsWith('@cjmod/')) {
                const moduleName = id.replace('@cjmod/', '');
                return this.resolve(resolveCJmodPath(moduleName), undefined, { skipSelf: true });
            }
            return null;
        },

        async load(id) {
            if (!id.endsWith('.chtl')) {
                return null;
            }

            // 检查缓存
            if (compiledCache.has(id)) {
                return compiledCache.get(id);
            }

            // 编译 CHTL 文件
            try {
                const result = await compileCHTL(id, { compilerPath, sourceMap });
                compiledCache.set(id, result);
                return result;
            } catch (error) {
                this.error(`Failed to compile ${id}: ${error.message}`);
            }
        },

        async transform(code, id) {
            if (!id.endsWith('.chtl')) {
                return null;
            }

            // 注入 HMR 代码
            if (hot && config.command === 'serve') {
                code = injectHMR(code, id);
            }

            // 处理 CJmod imports
            if (cjmodAutoLoad) {
                code = await processCJmodImports(code);
            }

            return {
                code,
                map: null // Source map 已在 load 阶段处理
            };
        },

        handleHotUpdate({ file, server }) {
            if (file.endsWith('.chtl')) {
                // 清除缓存
                compiledCache.delete(file);

                // 通知客户端更新
                const module = server.moduleGraph.getModuleById(file);
                if (module) {
                    server.ws.send({
                        type: 'custom',
                        event: 'chtl-update',
                        data: {
                            path: file
                        }
                    });
                }

                return [];
            }
        },

        configureServer(server) {
            // 添加中间件处理 CHTL 相关请求
            server.middlewares.use((req, res, next) => {
                if (req.url?.endsWith('.chtl')) {
                    res.setHeader('Content-Type', 'application/javascript');
                }
                next();
            });
        }
    };
}

async function compileCHTL(
    filePath: string,
    options: { compilerPath: string; sourceMap: boolean }
): Promise<{ code: string; map?: string }> {
    const tempDir = path.join(process.cwd(), '.chtl-temp');
    
    // 确保临时目录存在
    if (!fs.existsSync(tempDir)) {
        fs.mkdirSync(tempDir, { recursive: true });
    }

    const outputPath = path.join(tempDir, path.basename(filePath).replace('.chtl', '.js'));
    
    let command = `${options.compilerPath} compile "${filePath}" -o "${outputPath}"`;
    if (options.sourceMap) {
        command += ' --source-map';
    }

    try {
        execSync(command, { stdio: 'pipe' });
        
        const code = fs.readFileSync(outputPath, 'utf-8');
        let map: string | undefined;
        
        if (options.sourceMap) {
            const mapPath = outputPath + '.map';
            if (fs.existsSync(mapPath)) {
                map = fs.readFileSync(mapPath, 'utf-8');
            }
        }

        // 清理临时文件
        fs.unlinkSync(outputPath);
        if (map) {
            fs.unlinkSync(outputPath + '.map');
        }

        return { code, map };
    } catch (error) {
        throw new Error(`CHTL compilation failed: ${error.message}`);
    }
}

function resolveCJmodPath(moduleName: string): string {
    // 内置模块
    if (moduleName.startsWith('builtin:')) {
        return `virtual:cjmod/${moduleName}`;
    }

    // 搜索本地模块
    const searchPaths = [
        path.join(process.cwd(), 'node_modules', '@cjmod', moduleName),
        path.join(process.cwd(), moduleName + '.cjmod'),
        path.join(process.cwd(), 'cjmod_modules', moduleName)
    ];

    for (const searchPath of searchPaths) {
        if (fs.existsSync(searchPath)) {
            return searchPath;
        }
    }

    return moduleName;
}

function injectHMR(code: string, id: string): string {
    return `
${code}

// HMR Support
if (import.meta.hot) {
    import.meta.hot.accept();
    
    import.meta.hot.on('chtl-update', (data) => {
        if (data.path === '${id}') {
            console.log('[CHTL HMR] Reloading ${id}');
            window.location.reload();
        }
    });
}
`;
}

async function processCJmodImports(code: string): Promise<string> {
    // 转换 CJmod import 语句
    const importRegex = /\[Import\]\s+@CJmod\s+from\s+"([^"]+)";/g;
    
    return code.replace(importRegex, (match, modulePath) => {
        return `import '@cjmod/${modulePath}';`;
    });
}

// 导出类型
export type { CHTLPluginOptions };