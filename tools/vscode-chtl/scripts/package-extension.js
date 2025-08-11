#!/usr/bin/env node

const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

console.log('🚀 Packaging CHTL VS Code Extension...');

const extensionPath = path.join(__dirname, '..');
const distPath = path.join(extensionPath, 'dist');
const binPath = path.join(extensionPath, 'bin');
const modulesPath = path.join(extensionPath, 'modules');

// 创建必要的目录
function ensureDir(dir) {
    if (!fs.existsSync(dir)) {
        fs.mkdirSync(dir, { recursive: true });
    }
}

// 复制文件
function copyFile(src, dest) {
    ensureDir(path.dirname(dest));
    fs.copyFileSync(src, dest);
    console.log(`  ✓ Copied ${path.basename(src)}`);
}

// 递归复制目录
function copyDir(src, dest) {
    ensureDir(dest);
    
    const entries = fs.readdirSync(src, { withFileTypes: true });
    
    for (const entry of entries) {
        const srcPath = path.join(src, entry.name);
        const destPath = path.join(dest, entry.name);
        
        if (entry.isDirectory()) {
            copyDir(srcPath, destPath);
        } else {
            copyFile(srcPath, destPath);
        }
    }
}

// 1. 编译 TypeScript
console.log('\n📦 Compiling TypeScript...');
try {
    execSync('npm run compile', { cwd: extensionPath, stdio: 'inherit' });
} catch (error) {
    console.error('❌ TypeScript compilation failed');
    process.exit(1);
}

// 2. 复制 CHTL 编译器
console.log('\n📦 Copying CHTL compiler...');
ensureDir(binPath);

const compilerPath = path.join(__dirname, '../../../chtl');
const compilerFiles = ['chtl', 'chtl.exe']; // 支持 Linux/Mac 和 Windows

for (const file of compilerFiles) {
    const src = path.join(compilerPath, file);
    if (fs.existsSync(src)) {
        const dest = path.join(binPath, file);
        copyFile(src, dest);
        // 确保可执行权限
        if (!file.endsWith('.exe')) {
            fs.chmodSync(dest, '755');
        }
    }
}

// 3. 复制官方模块
console.log('\n📦 Copying official modules...');
const srcModulesPath = path.join(__dirname, '../../../modules');

if (fs.existsSync(srcModulesPath)) {
    copyDir(srcModulesPath, modulesPath);
    console.log(`  ✓ Copied modules directory`);
} else {
    console.warn('  ⚠️  Modules directory not found, creating empty directory');
    ensureDir(modulesPath);
}

// 4. 创建模块索引文件
console.log('\n📦 Creating module index...');
const moduleIndex = createModuleIndex(modulesPath);
fs.writeFileSync(
    path.join(modulesPath, 'index.json'),
    JSON.stringify(moduleIndex, null, 2)
);
console.log(`  ✓ Created module index with ${Object.keys(moduleIndex).length} modules`);

// 5. 打包扩展
console.log('\n📦 Creating VSIX package...');
try {
    execSync('vsce package', { cwd: extensionPath, stdio: 'inherit' });
    console.log('\n✅ Extension packaged successfully!');
} catch (error) {
    console.error('❌ VSIX packaging failed');
    console.log('Make sure you have vsce installed: npm install -g vsce');
    process.exit(1);
}

// 创建模块索引
function createModuleIndex(modulesDir) {
    const index = {};
    
    function scanDir(dir, basePath = '') {
        const entries = fs.readdirSync(dir, { withFileTypes: true });
        
        for (const entry of entries) {
            const fullPath = path.join(dir, entry.name);
            const relativePath = path.join(basePath, entry.name);
            
            if (entry.isDirectory()) {
                scanDir(fullPath, relativePath);
            } else if (entry.name.endsWith('.chtl') || 
                      entry.name.endsWith('.cmod') || 
                      entry.name.endsWith('.cjmod')) {
                const moduleName = path.basename(entry.name, path.extname(entry.name));
                index[moduleName] = {
                    path: relativePath,
                    type: path.extname(entry.name).slice(1),
                    size: fs.statSync(fullPath).size
                };
            }
        }
    }
    
    scanDir(modulesDir);
    return index;
}

console.log('\n🎉 Done!');