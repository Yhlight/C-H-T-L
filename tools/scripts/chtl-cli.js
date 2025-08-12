#!/usr/bin/env node

const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');
const readline = require('readline');

const version = '1.0.0';

// 模板定义
const templates = {
    basic: {
        name: 'Basic CHTL Project',
        description: 'A simple CHTL project with minimal setup',
        files: {
            'index.chtl': `// CHTL Basic Template
html {
    head {
        title { text { "My CHTL App" } }
        meta { 
            charset: "UTF-8";
            name: "viewport";
            content: "width=device-width, initial-scale=1.0";
        }
    }
    
    body {
        div {
            id: "app";
            class: "container";
            
            h1 { text { "Hello CHTL!" } }
            p { text { "Welcome to your new CHTL project." } }
        }
    }
}`,
            '.gitignore': `dist/
node_modules/
*.log
.DS_Store`,
            'README.md': `# CHTL Project

This project was created with CHTL CLI.

## Commands

- \`chtl compile index.chtl -o dist\` - Compile CHTL files
- \`chtl watch index.chtl -o dist\` - Watch and compile on changes

## Learn More

Visit [CHTL Documentation](https://github.com/chtl/docs) to learn more.`
        }
    },
    
    webapp: {
        name: 'Web Application',
        description: 'A complete web application with routing and components',
        files: {
            'index.chtl': `[Import] @Element Header from "./components/Header.chtl";
[Import] @Element Footer from "./components/Footer.chtl";
[Import] @Style GlobalStyles from "./styles/global.chtl";

html {
    head {
        title { text { "CHTL Web App" } }
        meta { charset: "UTF-8"; }
        @Style GlobalStyles;
    }
    
    body {
        @Element Header;
        
        main {
            id: "content";
            class: "main-content";
            
            // Router outlet
            div {
                id: "router-outlet";
            }
        }
        
        @Element Footer;
        
        script {
            // Simple router implementation
            const routes = {
                '/': 'home',
                '/about': 'about',
                '/contact': 'contact'
            };
            
            function loadPage(path) {
                const page = routes[path] || 'home';
                {{#router-outlet}}.innerHTML = '<h2>' + page + '</h2>';
            }
            
            window.addEventListener('popstate', () => {
                loadPage(window.location.pathname);
            });
            
            loadPage(window.location.pathname);
        }
    }
}`,
            'components/Header.chtl': `[Template] @Element Header {
    header {
        class: "site-header";
        
        style {
            .site-header {
                background: #333;
                color: white;
                padding: 1rem;
            }
            
            .nav-link {
                color: white;
                text-decoration: none;
                margin: 0 1rem;
                
                &:hover {
                    text-decoration: underline;
                }
            }
        }
        
        nav {
            a { 
                href: "/";
                class: "nav-link";
                text { "Home" }
            }
            a { 
                href: "/about";
                class: "nav-link";
                text { "About" }
            }
            a { 
                href: "/contact";
                class: "nav-link";
                text { "Contact" }
            }
        }
    }
}

[Export] {
    @Element Header;
}`,
            'components/Footer.chtl': `[Template] @Element Footer {
    footer {
        class: "site-footer";
        
        style {
            .site-footer {
                background: #f0f0f0;
                padding: 2rem;
                text-align: center;
                margin-top: 2rem;
            }
        }
        
        p {
            text { "© 2024 CHTL Web App. All rights reserved." }
        }
    }
}

[Export] {
    @Element Footer;
}`,
            'styles/global.chtl': `[Template] @Style GlobalStyles {
    * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
    }
    
    body {
        font-family: system-ui, -apple-system, sans-serif;
        line-height: 1.6;
        color: #333;
    }
    
    .main-content {
        min-height: calc(100vh - 200px);
        padding: 2rem;
        max-width: 1200px;
        margin: 0 auto;
    }
}

[Export] {
    @Style GlobalStyles;
}`,
            '.gitignore': `dist/
node_modules/
*.log
.DS_Store
.chtl-cache/`,
            'chtl.config.json': `{
    "compiler": {
        "outputDirectory": "dist",
        "sourceMaps": true,
        "minify": false
    },
    "modules": {
        "searchPaths": ["./components", "./styles"]
    }
}`
        }
    },
    
    component: {
        name: 'Component Library',
        description: 'A reusable component library starter',
        files: {
            'index.chtl': `// Component Library Demo
[Import] * from "./src/index.chtl";

html {
    head {
        title { text { "CHTL Component Library" } }
    }
    
    body {
        div {
            class: "demo";
            
            h1 { text { "Component Library Demo" } }
            
            @Element Button {
                text { "Primary Button" }
            }
            
            @Element Card {
                h2 { text { "Card Title" } }
                p { text { "Card content goes here." } }
            }
        }
    }
}`,
            'src/index.chtl': `// Component Library Entry Point
[Import] @Element Button from "./components/Button.chtl";
[Import] @Element Card from "./components/Card.chtl";
[Import] @Element Modal from "./components/Modal.chtl";
[Import] @Style Theme from "./styles/theme.chtl";

[Export] {
    @Element Button;
    @Element Card;
    @Element Modal;
    @Style Theme;
}`,
            'src/components/Button.chtl': `[Custom] @Element Button {
    button {
        class: "chtl-button";
        
        style {
            .chtl-button {
                padding: 0.5rem 1rem;
                border: none;
                border-radius: 4px;
                background: #007bff;
                color: white;
                cursor: pointer;
                font-size: 1rem;
                transition: background 0.3s;
                
                &:hover {
                    background: #0056b3;
                }
                
                &:active {
                    transform: translateY(1px);
                }
            }
            
            .chtl-button--secondary {
                background: #6c757d;
                
                &:hover {
                    background: #545b62;
                }
            }
            
            .chtl-button--large {
                padding: 0.75rem 1.5rem;
                font-size: 1.25rem;
            }
        }
        
        slot {
            name: "content";
        }
    }
}

[Export] {
    @Element Button;
}`,
            'src/components/Card.chtl': `[Custom] @Element Card {
    div {
        class: "chtl-card";
        
        style {
            .chtl-card {
                border: 1px solid #ddd;
                border-radius: 8px;
                padding: 1.5rem;
                margin: 1rem 0;
                box-shadow: 0 2px 4px rgba(0,0,0,0.1);
                background: white;
            }
        }
        
        slot {
            name: "content";
        }
    }
}

[Export] {
    @Element Card;
}`,
            'src/components/Modal.chtl': `[Custom] @Element Modal {
    div {
        class: "chtl-modal-overlay";
        
        style {
            .chtl-modal-overlay {
                position: fixed;
                top: 0;
                left: 0;
                right: 0;
                bottom: 0;
                background: rgba(0,0,0,0.5);
                display: flex;
                align-items: center;
                justify-content: center;
                z-index: 1000;
            }
            
            .chtl-modal {
                background: white;
                border-radius: 8px;
                padding: 2rem;
                max-width: 500px;
                width: 90%;
                max-height: 90vh;
                overflow-y: auto;
            }
        }
        
        div {
            class: "chtl-modal";
            
            slot {
                name: "content";
            }
        }
    }
}

[Export] {
    @Element Modal;
}`,
            'src/styles/theme.chtl': `[Template] @Style Theme {
    :root {
        --primary-color: #007bff;
        --secondary-color: #6c757d;
        --success-color: #28a745;
        --danger-color: #dc3545;
        --warning-color: #ffc107;
        --info-color: #17a2b8;
        --light-color: #f8f9fa;
        --dark-color: #343a40;
    }
}

[Export] {
    @Style Theme;
}`,
            'package.json': `{
    "name": "chtl-component-library",
    "version": "1.0.0",
    "description": "A CHTL component library",
    "main": "dist/index.js",
    "scripts": {
        "build": "chtl compile src/index.chtl -o dist",
        "watch": "chtl watch src/index.chtl -o dist",
        "pack": "chtl pack-cmod src -o dist/library.cmod"
    },
    "keywords": ["chtl", "components", "ui"],
    "license": "MIT"
}`
        }
    }
};

// CLI 实现
class ChtlCLI {
    constructor() {
        this.rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout
        });
    }
    
    async run() {
        const args = process.argv.slice(2);
        const command = args[0];
        
        console.log('CHTL CLI v' + version);
        console.log('================\n');
        
        switch (command) {
            case 'init':
            case 'create':
                await this.createProject();
                break;
            case 'new':
                if (args[1] === 'component') {
                    await this.createComponent(args[2]);
                } else {
                    console.log('Usage: chtl new component <name>');
                }
                break;
            case '--version':
            case '-v':
                console.log(version);
                break;
            case '--help':
            case '-h':
            default:
                this.showHelp();
                break;
        }
        
        this.rl.close();
    }
    
    showHelp() {
        console.log(`Usage: chtl <command> [options]

Commands:
  init, create     Create a new CHTL project
  new component    Create a new component
  
Options:
  -v, --version    Show version
  -h, --help       Show help

Examples:
  chtl init
  chtl new component Button`);
    }
    
    async createProject() {
        // 获取项目名称
        const projectName = await this.question('Project name: ') || 'my-chtl-app';
        
        // 显示模板选项
        console.log('\nAvailable templates:');
        Object.entries(templates).forEach(([key, template], index) => {
            console.log(`  ${index + 1}. ${template.name} - ${template.description}`);
        });
        
        // 选择模板
        const templateChoice = await this.question('\nSelect template (1-3): ');
        const templateKeys = Object.keys(templates);
        const selectedTemplate = templates[templateKeys[parseInt(templateChoice) - 1] || 'basic'];
        
        // 创建项目目录
        const projectPath = path.join(process.cwd(), projectName);
        if (fs.existsSync(projectPath)) {
            console.error(`Error: Directory ${projectName} already exists`);
            return;
        }
        
        fs.mkdirSync(projectPath, { recursive: true });
        
        // 创建文件
        console.log(`\nCreating project in ${projectPath}...`);
        this.createFiles(projectPath, selectedTemplate.files);
        
        // 初始化 git
        try {
            execSync('git init', { cwd: projectPath, stdio: 'ignore' });
            console.log('✓ Initialized git repository');
        } catch (e) {
            // Git 初始化失败，继续
        }
        
        console.log(`\n✨ Project created successfully!\n`);
        console.log(`Next steps:`);
        console.log(`  cd ${projectName}`);
        console.log(`  chtl compile index.chtl -o dist`);
        console.log(`  # or use VS Code with CHTL extension`);
    }
    
    async createComponent(componentName) {
        if (!componentName) {
            componentName = await this.question('Component name: ');
        }
        
        if (!componentName) {
            console.error('Component name is required');
            return;
        }
        
        const componentPath = path.join('components', `${componentName}.chtl`);
        const componentDir = path.dirname(componentPath);
        
        // 创建目录
        if (!fs.existsSync(componentDir)) {
            fs.mkdirSync(componentDir, { recursive: true });
        }
        
        // 组件模板
        const componentContent = `[Custom] @Element ${componentName} {
    div {
        class: "${componentName.toLowerCase()}";
        
        style {
            .${componentName.toLowerCase()} {
                // Add your styles here
            }
        }
        
        // Add your component structure here
        slot {
            name: "content";
        }
    }
}

[Export] {
    @Element ${componentName};
}`;
        
        // 写入文件
        fs.writeFileSync(componentPath, componentContent);
        console.log(`✓ Created component: ${componentPath}`);
    }
    
    createFiles(basePath, files) {
        Object.entries(files).forEach(([filePath, content]) => {
            const fullPath = path.join(basePath, filePath);
            const dir = path.dirname(fullPath);
            
            // 创建目录
            if (!fs.existsSync(dir)) {
                fs.mkdirSync(dir, { recursive: true });
            }
            
            // 写入文件
            fs.writeFileSync(fullPath, content);
            console.log(`✓ Created ${filePath}`);
        });
    }
    
    question(prompt) {
        return new Promise(resolve => {
            this.rl.question(prompt, answer => {
                resolve(answer);
            });
        });
    }
}

// 运行 CLI
const cli = new ChtlCLI();
cli.run();