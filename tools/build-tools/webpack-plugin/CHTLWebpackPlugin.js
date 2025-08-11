const { execSync } = require('child_process');
const path = require('path');
const fs = require('fs');

class CHTLWebpackPlugin {
    constructor(options = {}) {
        this.options = {
            compilerPath: options.compilerPath || 'chtl',
            outputDir: options.outputDir || 'dist',
            sourceMap: options.sourceMap !== false,
            watch: options.watch || false,
            cjmodAutoLoad: options.cjmodAutoLoad !== false,
            ...options
        };
        
        this.compiledFiles = new Map();
    }

    apply(compiler) {
        const pluginName = 'CHTLWebpackPlugin';

        // 添加 .chtl 文件解析
        compiler.options.resolve.extensions.push('.chtl');

        // 添加 CHTL loader
        compiler.options.module.rules.push({
            test: /\.chtl$/,
            use: [
                {
                    loader: path.resolve(__dirname, 'chtl-loader.js'),
                    options: this.options
                }
            ]
        });

        // 监听文件变化
        if (this.options.watch) {
            compiler.hooks.watchRun.tap(pluginName, (compilation) => {
                this.handleFileChanges(compilation);
            });
        }

        // 编译前处理
        compiler.hooks.beforeCompile.tapAsync(pluginName, (params, callback) => {
            this.compileCHTLFiles(compiler, callback);
        });

        // 编译完成后处理
        compiler.hooks.done.tap(pluginName, (stats) => {
            if (!stats.hasErrors()) {
                console.log('[CHTL] Compilation completed successfully');
            }
        });

        // 添加 CJmod 模块解析
        compiler.hooks.normalModuleFactory.tap(pluginName, (normalModuleFactory) => {
            normalModuleFactory.hooks.resolve.tapAsync(pluginName, (data, callback) => {
                if (data.request.startsWith('@cjmod/')) {
                    this.resolveCJmod(data, callback);
                } else {
                    callback();
                }
            });
        });
    }

    compileCHTLFiles(compiler, callback) {
        const context = compiler.context;
        const chtlFiles = this.findCHTLFiles(context);

        try {
            chtlFiles.forEach(file => {
                if (!this.compiledFiles.has(file) || this.hasFileChanged(file)) {
                    this.compileFile(file);
                }
            });
            callback();
        } catch (error) {
            callback(error);
        }
    }

    compileFile(filePath) {
        console.log(`[CHTL] Compiling ${filePath}`);
        
        const outputPath = this.getOutputPath(filePath);
        const command = `${this.options.compilerPath} compile "${filePath}" -o "${outputPath}"`;
        
        if (this.options.sourceMap) {
            command += ' --source-map';
        }

        try {
            execSync(command, { stdio: 'pipe' });
            this.compiledFiles.set(filePath, {
                mtime: fs.statSync(filePath).mtime,
                output: outputPath
            });
        } catch (error) {
            throw new Error(`CHTL compilation failed: ${error.message}`);
        }
    }

    findCHTLFiles(directory) {
        const files = [];
        const items = fs.readdirSync(directory, { withFileTypes: true });

        items.forEach(item => {
            const fullPath = path.join(directory, item.name);
            
            if (item.isDirectory() && !item.name.startsWith('.') && item.name !== 'node_modules') {
                files.push(...this.findCHTLFiles(fullPath));
            } else if (item.isFile() && item.name.endsWith('.chtl')) {
                files.push(fullPath);
            }
        });

        return files;
    }

    hasFileChanged(filePath) {
        const cached = this.compiledFiles.get(filePath);
        if (!cached) return true;

        const currentMtime = fs.statSync(filePath).mtime;
        return currentMtime > cached.mtime;
    }

    getOutputPath(inputPath) {
        const relativePath = path.relative(process.cwd(), inputPath);
        const outputFile = relativePath.replace(/\.chtl$/, '.js');
        return path.join(this.options.outputDir, outputFile);
    }

    resolveCJmod(data, callback) {
        const moduleName = data.request.replace('@cjmod/', '');
        
        // 尝试解析内置模块
        if (moduleName.startsWith('builtin:')) {
            data.request = path.join(__dirname, 'cjmod-builtins', moduleName.replace('builtin:', '') + '.js');
        } else {
            // 解析本地 .cjmod 文件
            const cjmodPath = this.resolveCJmodPath(moduleName);
            if (cjmodPath) {
                data.request = cjmodPath;
            }
        }

        callback();
    }

    resolveCJmodPath(moduleName) {
        // 实现 CJmod 路径解析逻辑
        const searchPaths = [
            path.join(process.cwd(), 'node_modules', moduleName),
            path.join(process.cwd(), moduleName + '.cjmod'),
            path.join(process.cwd(), 'cjmod_modules', moduleName)
        ];

        for (const searchPath of searchPaths) {
            if (fs.existsSync(searchPath)) {
                return searchPath;
            }
        }

        return null;
    }

    handleFileChanges(compilation) {
        const changedFiles = Array.from(compilation.fileTimestamps.keys())
            .filter(file => file.endsWith('.chtl'));

        changedFiles.forEach(file => {
            this.compileFile(file);
        });
    }
}

module.exports = CHTLWebpackPlugin;