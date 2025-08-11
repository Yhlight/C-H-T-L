#!/usr/bin/env node

const { Command } = require('commander');
const { execSync } = require('child_process');
const path = require('path');
const fs = require('fs');
const chalk = require('chalk');
const chokidar = require('chokidar');

const program = new Command();

program
    .name('chtl')
    .description('CHTL Command Line Interface')
    .version('1.0.0');

// compile 命令
program
    .command('compile <file>')
    .description('Compile a CHTL file')
    .option('-o, --output <dir>', 'Output directory', './dist')
    .option('-w, --watch', 'Watch mode')
    .option('--source-map', 'Generate source maps')
    .option('--minify', 'Minify output')
    .action((file, options) => {
        if (options.watch) {
            watchAndCompile(file, options);
        } else {
            compileFile(file, options);
        }
    });

// init 命令
program
    .command('init [project-name]')
    .description('Initialize a new CHTL project')
    .option('-t, --template <template>', 'Project template', 'default')
    .action((projectName, options) => {
        initProject(projectName || 'chtl-project', options);
    });

// create 命令
program
    .command('create <type> <name>')
    .description('Create a new component, module, or page')
    .action((type, name) => {
        createComponent(type, name);
    });

// install 命令
program
    .command('install <module>')
    .alias('i')
    .description('Install a CJmod module')
    .action((module) => {
        installCJmod(module);
    });

// serve 命令
program
    .command('serve [directory]')
    .description('Start development server')
    .option('-p, --port <port>', 'Server port', '3000')
    .option('--host <host>', 'Server host', 'localhost')
    .action((directory, options) => {
        startDevServer(directory || '.', options);
    });

// build 命令
program
    .command('build [directory]')
    .description('Build project for production')
    .option('-o, --output <dir>', 'Output directory', './dist')
    .option('--analyze', 'Analyze bundle size')
    .action((directory, options) => {
        buildProject(directory || '.', options);
    });

// 功能实现

function compileFile(file, options) {
    console.log(chalk.blue(`Compiling ${file}...`));
    
    const command = buildCompileCommand(file, options);
    
    try {
        const startTime = Date.now();
        execSync(command, { stdio: 'inherit' });
        const duration = Date.now() - startTime;
        
        console.log(chalk.green(`✓ Compiled successfully in ${duration}ms`));
    } catch (error) {
        console.error(chalk.red(`✗ Compilation failed: ${error.message}`));
        process.exit(1);
    }
}

function watchAndCompile(file, options) {
    console.log(chalk.blue(`Watching ${file} for changes...`));
    
    // 初始编译
    compileFile(file, options);
    
    // 监听文件变化
    const watcher = chokidar.watch(file, {
        persistent: true,
        ignoreInitial: true
    });
    
    watcher.on('change', () => {
        console.log(chalk.yellow(`\nFile changed, recompiling...`));
        compileFile(file, options);
    });
    
    process.on('SIGINT', () => {
        watcher.close();
        process.exit(0);
    });
}

function buildCompileCommand(file, options) {
    let command = `chtl-compiler "${file}"`;
    
    if (options.output) {
        command += ` -o "${options.output}"`;
    }
    
    if (options.sourceMap) {
        command += ' --source-map';
    }
    
    if (options.minify) {
        command += ' --minify';
    }
    
    return command;
}

function initProject(projectName, options) {
    console.log(chalk.blue(`Creating new CHTL project: ${projectName}`));
    
    const projectDir = path.join(process.cwd(), projectName);
    
    // 创建项目目录
    fs.mkdirSync(projectDir, { recursive: true });
    
    // 创建项目结构
    const directories = ['src', 'src/components', 'src/styles', 'src/scripts', 'public', 'cjmod_modules'];
    directories.forEach(dir => {
        fs.mkdirSync(path.join(projectDir, dir), { recursive: true });
    });
    
    // 创建配置文件
    createPackageJson(projectDir, projectName);
    createChtlConfig(projectDir);
    createGitignore(projectDir);
    createReadme(projectDir, projectName);
    
    // 创建示例文件
    createExampleFiles(projectDir, options.template);
    
    console.log(chalk.green(`\n✓ Project created successfully!\n`));
    console.log('To get started:');
    console.log(chalk.cyan(`  cd ${projectName}`));
    console.log(chalk.cyan('  npm install'));
    console.log(chalk.cyan('  npm run dev'));
}

function createPackageJson(projectDir, projectName) {
    const packageJson = {
        name: projectName,
        version: '1.0.0',
        description: 'A CHTL project',
        scripts: {
            dev: 'chtl serve',
            build: 'chtl build',
            preview: 'chtl serve dist'
        },
        devDependencies: {
            'chtl-cli': '^1.0.0',
            'vite-plugin-chtl': '^1.0.0'
        }
    };
    
    fs.writeFileSync(
        path.join(projectDir, 'package.json'),
        JSON.stringify(packageJson, null, 2)
    );
}

function createChtlConfig(projectDir) {
    const config = `{
    "compiler": {
        "outputDir": "./dist",
        "sourceMap": true,
        "minify": false
    },
    "cjmod": {
        "autoLoad": true,
        "modules": []
    },
    "dev": {
        "port": 3000,
        "host": "localhost",
        "hot": true
    }
}`;
    
    fs.writeFileSync(path.join(projectDir, 'chtl.config.json'), config);
}

function createGitignore(projectDir) {
    const gitignore = `node_modules/
dist/
.chtl-temp/
*.log
.DS_Store
.env
.env.local`;
    
    fs.writeFileSync(path.join(projectDir, '.gitignore'), gitignore);
}

function createReadme(projectDir, projectName) {
    const readme = `# ${projectName}

A CHTL (Component HTML Template Language) project.

## Getting Started

\`\`\`bash
npm install
npm run dev
\`\`\`

## Available Scripts

- \`npm run dev\` - Start development server
- \`npm run build\` - Build for production
- \`npm run preview\` - Preview production build

## Project Structure

\`\`\`
${projectName}/
├── src/
│   ├── components/    # CHTL components
│   ├── styles/       # Global styles
│   └── scripts/      # JavaScript modules
├── public/           # Static assets
├── cjmod_modules/    # CJmod modules
└── chtl.config.json  # Configuration
\`\`\`

## Learn More

- [CHTL Documentation](https://chtl.dev)
- [CJmod Guide](https://chtl.dev/cjmod)
`;
    
    fs.writeFileSync(path.join(projectDir, 'README.md'), readme);
}

function createExampleFiles(projectDir, template) {
    // 创建主页面
    const indexChtl = `[Import] @CJmod from "builtin:reactive";

[Style] {
    body {
        font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
        margin: 0;
        padding: 0;
        background: #f5f5f5;
    }
}

div #app {
    div .container {
        max-width: 800px;
        margin: 0 auto;
        padding: 40px 20px;
        
        h1 { 
            "Welcome to CHTL" 
            style {
                color: #333;
                text-align: center;
                margin-bottom: 30px;
            }
        }
        
        @Custom Counter
        
        p .description {
            "Edit src/index.chtl to get started"
            style {
                text-align: center;
                color: #666;
                margin-top: 20px;
            }
        }
    }
}`;
    
    fs.writeFileSync(path.join(projectDir, 'src/index.chtl'), indexChtl);
    
    // 创建示例组件
    const counterComponent = `[Custom] @Element Counter {
    script {
        count := 0;
        
        function increment() {
            count.value++;
        }
        
        function decrement() {
            count.value--;
        }
    }
    
    div .counter {
        h2 { "Counter Component" }
        
        div .display {
            "Count: "
            span #count { count.value }
            
            style {
                font-size: 24px;
                text-align: center;
                margin: 20px 0;
            }
        }
        
        div .controls {
            button {
                "−"
                onclick: decrement
            }
            
            button {
                "+"
                onclick: increment
            }
            
            style {
                text-align: center;
                
                button {
                    margin: 0 10px;
                    padding: 10px 20px;
                    font-size: 18px;
                    border: none;
                    border-radius: 5px;
                    background: #007bff;
                    color: white;
                    cursor: pointer;
                    transition: background 0.2s;
                }
                
                button:hover {
                    background: #0056b3;
                }
            }
        }
    }
}`;
    
    fs.writeFileSync(
        path.join(projectDir, 'src/components/Counter.chtl'),
        counterComponent
    );
}

function createComponent(type, name) {
    const validTypes = ['component', 'page', 'module'];
    
    if (!validTypes.includes(type)) {
        console.error(chalk.red(`Invalid type: ${type}`));
        console.log(`Valid types: ${validTypes.join(', ')}`);
        return;
    }
    
    console.log(chalk.blue(`Creating ${type}: ${name}`));
    
    // 根据类型创建不同的模板
    let template = '';
    let filePath = '';
    
    switch (type) {
        case 'component':
            template = createComponentTemplate(name);
            filePath = path.join('src/components', `${name}.chtl`);
            break;
        case 'page':
            template = createPageTemplate(name);
            filePath = path.join('src/pages', `${name}.chtl`);
            break;
        case 'module':
            template = createModuleTemplate(name);
            filePath = path.join('src/modules', `${name}.js`);
            break;
    }
    
    // 确保目录存在
    const dir = path.dirname(filePath);
    if (!fs.existsSync(dir)) {
        fs.mkdirSync(dir, { recursive: true });
    }
    
    // 写入文件
    fs.writeFileSync(filePath, template);
    
    console.log(chalk.green(`✓ Created ${filePath}`));
}

function createComponentTemplate(name) {
    return `[Custom] @Element ${name} {
    -- Component properties
    props: {
        // Define props here
    }
    
    -- Component state
    script {
        // Component logic here
    }
    
    -- Component template
    div .${name.toLowerCase()}-container {
        h2 { "${name} Component" }
        
        -- Add content here
    }
    
    -- Component styles
    style {
        .${name.toLowerCase()}-container {
            padding: 20px;
            border: 1px solid #ddd;
            border-radius: 8px;
        }
    }
}`;
}

function createPageTemplate(name) {
    return `[Import] @Chtl from "./components/Layout.chtl";

div #${name.toLowerCase()}-page {
    @Custom Layout {
        title: "${name}"
        
        -- Page content
        div .content {
            h1 { "${name} Page" }
            
            -- Add page content here
        }
    }
}`;
}

function createModuleTemplate(name) {
    return `// ${name} Module

export class ${name} {
    constructor() {
        // Initialize module
    }
    
    // Add module methods here
}

export default ${name};`;
}

function installCJmod(module) {
    console.log(chalk.blue(`Installing CJmod module: ${module}`));
    
    // TODO: 实现实际的模块安装逻辑
    console.log(chalk.yellow('CJmod package manager not yet implemented'));
    console.log('For now, manually download modules to cjmod_modules/');
}

function startDevServer(directory, options) {
    console.log(chalk.blue('Starting development server...'));
    
    const viteConfig = `
import { defineConfig } from 'vite';
import chtlPlugin from 'vite-plugin-chtl';

export default defineConfig({
    plugins: [chtlPlugin()],
    server: {
        port: ${options.port},
        host: '${options.host}'
    }
});`;
    
    // 创建临时 vite 配置
    const configPath = path.join(directory, 'vite.config.temp.js');
    fs.writeFileSync(configPath, viteConfig);
    
    try {
        execSync(`npx vite --config ${configPath}`, { 
            stdio: 'inherit',
            cwd: directory 
        });
    } catch (error) {
        // 清理临时文件
        fs.unlinkSync(configPath);
    }
}

function buildProject(directory, options) {
    console.log(chalk.blue('Building project for production...'));
    
    const startTime = Date.now();
    
    try {
        // 编译所有 CHTL 文件
        const chtlFiles = findAllChtlFiles(directory);
        
        chtlFiles.forEach(file => {
            compileFile(file, {
                output: options.output,
                sourceMap: false,
                minify: true
            });
        });
        
        const duration = Date.now() - startTime;
        console.log(chalk.green(`\n✓ Build completed in ${duration}ms`));
        
        if (options.analyze) {
            analyzeBundle(options.output);
        }
    } catch (error) {
        console.error(chalk.red(`✗ Build failed: ${error.message}`));
        process.exit(1);
    }
}

function findAllChtlFiles(directory) {
    const files = [];
    
    function walk(dir) {
        const items = fs.readdirSync(dir, { withFileTypes: true });
        
        items.forEach(item => {
            const fullPath = path.join(dir, item.name);
            
            if (item.isDirectory() && !item.name.startsWith('.') && item.name !== 'node_modules') {
                walk(fullPath);
            } else if (item.isFile() && item.name.endsWith('.chtl')) {
                files.push(fullPath);
            }
        });
    }
    
    walk(directory);
    return files;
}

function analyzeBundle(outputDir) {
    console.log(chalk.blue('\nAnalyzing bundle size...'));
    
    // TODO: 实现实际的 bundle 分析
    console.log(chalk.yellow('Bundle analysis not yet implemented'));
}

// 解析命令行参数
program.parse(process.argv);