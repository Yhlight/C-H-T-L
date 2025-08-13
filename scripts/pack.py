#!/usr/bin/env python3
"""
CHTL 跨平台打包脚本
支持: Windows, Linux, macOS
"""

import os
import sys
import json
import tarfile
import zipfile
import tempfile
import shutil
import subprocess
import platform
import argparse
from pathlib import Path
from datetime import datetime

# 复用构建脚本的颜色类
sys.path.append(str(Path(__file__).parent))
try:
    from build import Colors, print_info, print_success, print_warning, print_error
except ImportError:
    # 如果导入失败，定义简单版本
    class Colors:
        def red(self, text): return text
        def green(self, text): return text
        def yellow(self, text): return text
        def blue(self, text): return text
    
    colors = Colors()
    def print_info(msg): print(f"[INFO] {msg}")
    def print_success(msg): print(f"[SUCCESS] {msg}")
    def print_warning(msg): print(f"[WARNING] {msg}")
    def print_error(msg): print(f"[ERROR] {msg}")

class ModulePackager:
    def __init__(self):
        self.root_dir = Path(__file__).parent.parent.absolute()
        self.module_dir = self.root_dir / "module"
        self.output_dir = self.root_dir / "output"
        self.platform = platform.system().lower()
        
    def detect_module_type(self, module_path):
        """检测模块类型"""
        module_path = Path(module_path)
        
        has_cmod = False
        has_cjmod = False
        
        # 检查混合模块结构
        if (module_path / "CMOD").exists():
            has_cmod = True
        if (module_path / "CJMOD").exists():
            has_cjmod = True
            
        # 检查直接模块结构
        if not (has_cmod or has_cjmod):
            if (module_path / "src").exists() and (module_path / "info").exists():
                # 检查是否有C++文件
                src_dir = module_path / "src"
                cpp_files = list(src_dir.glob("*.cpp")) + list(src_dir.glob("*.cc")) + list(src_dir.glob("*.cxx"))
                chtl_files = list(src_dir.glob("*.chtl"))
                
                if cpp_files:
                    has_cjmod = True
                elif chtl_files:
                    has_cmod = True
                    
        if has_cmod and has_cjmod:
            return "mixed"
        elif has_cmod:
            return "cmod"
        elif has_cjmod:
            return "cjmod"
        else:
            return "unknown"
            
    def get_module_name(self, module_path):
        """从info文件获取模块名"""
        module_path = Path(module_path)
        
        # 查找info文件
        info_files = []
        if (module_path / "info").exists():
            info_files.extend((module_path / "info").glob("*.chtl"))
        
        for subdir in ["CMOD", "CJMOD"]:
            subpath = module_path / subdir
            if subpath.exists():
                for item in subpath.iterdir():
                    if item.is_dir() and (item / "info").exists():
                        info_files.extend((item / "info").glob("*.chtl"))
                        
        if info_files:
            # 使用第一个info文件的名称
            return info_files[0].stem
            
        # 默认使用目录名
        return module_path.name
        
    def pack_cmod(self, module_path, output_dir=None):
        """打包CMOD模块"""
        module_path = Path(module_path)
        if output_dir is None:
            output_dir = self.output_dir
        else:
            output_dir = Path(output_dir)
            
        output_dir.mkdir(parents=True, exist_ok=True)
        
        # 获取模块名
        module_name = self.get_module_name(module_path)
        print_info(f"打包CMOD模块: {module_name}")
        
        # 查找CMOD目录
        cmod_path = None
        if (module_path / "CMOD" / module_name).exists():
            cmod_path = module_path / "CMOD" / module_name
        elif (module_path / "src").exists() and (module_path / "info").exists():
            cmod_path = module_path
        else:
            print_error(f"未找到有效的CMOD结构")
            return False
            
        # 创建临时目录
        with tempfile.TemporaryDirectory() as temp_dir:
            temp_path = Path(temp_dir)
            module_temp = temp_path / module_name
            
            # 复制模块内容
            shutil.copytree(cmod_path, module_temp)
            
            # 创建元数据
            metadata = {
                "module_name": module_name,
                "package_type": "CMOD",
                "created_at": datetime.now().isoformat(),
                "platform": "all",
                "chtl_version": "1.0.0"
            }
            
            metadata_file = module_temp / ".cmod_metadata"
            with open(metadata_file, 'w') as f:
                json.dump(metadata, f, indent=2)
                
            # 创建归档文件
            output_file = output_dir / f"{module_name}.cmod"
            
            if self.platform == "windows":
                # Windows上创建zip文件（可以用tar，但zip更常见）
                with zipfile.ZipFile(output_file, 'w', zipfile.ZIP_DEFLATED) as zf:
                    for file in module_temp.rglob('*'):
                        if file.is_file():
                            arcname = file.relative_to(temp_path)
                            zf.write(file, arcname)
            else:
                # Unix系统使用tar.gz
                with tarfile.open(output_file, 'w:gz') as tf:
                    tf.add(module_temp, arcname=module_name)
                    
        print_success(f"CMOD打包完成: {output_file}")
        return True
        
    def compile_cjmod(self, cjmod_path, build_dir, module_name):
        """编译CJMOD"""
        print_info(f"编译CJMOD: {module_name}")
        
        # 创建CMakeLists.txt
        cmake_content = f"""cmake_minimum_required(VERSION 3.16)
project({module_name} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 查找源文件
file(GLOB_RECURSE SOURCES "{cjmod_path}/src/*.cpp")

# 创建共享库
add_library({module_name} SHARED ${{SOURCES}})

# 包含目录
target_include_directories({module_name} PRIVATE
    {self.root_dir}/src
    {cjmod_path}/src
)

# 设置输出名称
set_target_properties({module_name} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "{module_name.lower()}"
)

# Windows特定设置
if(WIN32)
    target_compile_definitions({module_name} PRIVATE CJMOD_EXPORTS)
endif()
"""
        
        cmake_file = build_dir / "CMakeLists.txt"
        with open(cmake_file, 'w') as f:
            f.write(cmake_content)
            
        # 配置
        cmd = ["cmake", "-S", str(build_dir), "-B", str(build_dir)]
        if self.platform == "windows" and shutil.which("cl"):
            # 使用Visual Studio
            pass
        elif self.platform == "windows" and shutil.which("mingw32-make"):
            cmd.extend(["-G", "MinGW Makefiles"])
            
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print_error(f"CMake配置失败: {result.stderr}")
            return None
            
        # 构建
        cmd = ["cmake", "--build", str(build_dir), "--config", "Release"]
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print_error(f"编译失败: {result.stderr}")
            return None
            
        # 查找生成的库文件
        lib_extensions = {
            "windows": [".dll"],
            "darwin": [".dylib"],
            "linux": [".so"]
        }
        
        for ext in lib_extensions.get(self.platform, [".so"]):
            # 在不同可能的位置查找
            possible_paths = [
                build_dir / f"{module_name.lower()}{ext}",
                build_dir / "Release" / f"{module_name.lower()}{ext}",
                build_dir / "Debug" / f"{module_name.lower()}{ext}",
            ]
            
            for lib_path in possible_paths:
                if lib_path.exists():
                    return lib_path
                    
        print_error("未找到编译生成的库文件")
        return None
        
    def pack_cjmod(self, module_path, output_dir=None):
        """打包CJMOD模块"""
        module_path = Path(module_path)
        if output_dir is None:
            output_dir = self.output_dir
        else:
            output_dir = Path(output_dir)
            
        output_dir.mkdir(parents=True, exist_ok=True)
        
        # 获取模块名
        module_name = self.get_module_name(module_path)
        print_info(f"打包CJMOD模块: {module_name}")
        
        # 查找CJMOD目录
        cjmod_path = None
        if (module_path / "CJMOD" / module_name).exists():
            cjmod_path = module_path / "CJMOD" / module_name
        elif (module_path / "src").exists():
            # 检查是否有C++文件
            cpp_files = list((module_path / "src").glob("*.cpp"))
            if cpp_files:
                cjmod_path = module_path
                
        if not cjmod_path:
            print_error("未找到有效的CJMOD结构")
            return False
            
        # 创建临时目录
        with tempfile.TemporaryDirectory() as temp_dir:
            temp_path = Path(temp_dir)
            build_dir = temp_path / "build"
            build_dir.mkdir()
            
            # 编译CJMOD
            lib_file = self.compile_cjmod(cjmod_path, build_dir, module_name)
            if not lib_file:
                return False
                
            # 创建打包目录
            module_temp = temp_path / module_name
            module_temp.mkdir()
            
            # 复制文件
            (module_temp / "lib").mkdir()
            shutil.copy2(lib_file, module_temp / "lib" / lib_file.name)
            
            if (cjmod_path / "src").exists():
                shutil.copytree(cjmod_path / "src", module_temp / "src")
                
            if (cjmod_path / "info").exists():
                shutil.copytree(cjmod_path / "info", module_temp / "info")
                
            # 创建元数据
            metadata = {
                "module_name": module_name,
                "package_type": "CJMOD",
                "created_at": datetime.now().isoformat(),
                "platform": self.platform,
                "architecture": platform.machine(),
                "chtl_version": "1.0.0"
            }
            
            metadata_file = module_temp / ".cjmod_metadata"
            with open(metadata_file, 'w') as f:
                json.dump(metadata, f, indent=2)
                
            # 创建归档文件
            output_file = output_dir / f"{module_name}.cjmod"
            
            if self.platform == "windows":
                with zipfile.ZipFile(output_file, 'w', zipfile.ZIP_DEFLATED) as zf:
                    for file in module_temp.rglob('*'):
                        if file.is_file():
                            arcname = file.relative_to(temp_path)
                            zf.write(file, arcname)
            else:
                with tarfile.open(output_file, 'w:gz') as tf:
                    tf.add(module_temp, arcname=module_name)
                    
        print_success(f"CJMOD打包完成: {output_file}")
        return True
        
    def pack_module(self, module_path, output_dir=None):
        """自动检测并打包模块"""
        module_path = Path(module_path)
        
        if not module_path.exists():
            print_error(f"模块路径不存在: {module_path}")
            return False
            
        module_type = self.detect_module_type(module_path)
        print_info(f"检测到模块类型: {module_type}")
        
        success = True
        
        if module_type == "mixed":
            # 分别打包CMOD和CJMOD
            if not self.pack_cmod(module_path, output_dir):
                success = False
            if not self.pack_cjmod(module_path, output_dir):
                success = False
        elif module_type == "cmod":
            success = self.pack_cmod(module_path, output_dir)
        elif module_type == "cjmod":
            success = self.pack_cjmod(module_path, output_dir)
        else:
            print_error(f"无法识别的模块类型: {module_path}")
            success = False
            
        return success

def main():
    parser = argparse.ArgumentParser(description="CHTL跨平台打包脚本")
    parser.add_argument("modules", nargs="*", help="要打包的模块路径")
    parser.add_argument("-o", "--output", help="输出目录")
    parser.add_argument("-t", "--type", choices=["cmod", "cjmod", "auto"], 
                        default="auto", help="模块类型")
    parser.add_argument("--all", action="store_true", help="打包所有模块")
    
    args = parser.parse_args()
    
    packager = ModulePackager()
    
    # 确定要打包的模块
    modules_to_pack = []
    
    if args.all:
        # 打包module目录下的所有模块
        if packager.module_dir.exists():
            modules_to_pack.extend([
                p for p in packager.module_dir.iterdir() 
                if p.is_dir() and not p.name.startswith('.')
            ])
    elif args.modules:
        # 打包指定的模块
        modules_to_pack.extend([Path(m) for m in args.modules])
    else:
        print_error("请指定要打包的模块或使用 --all 打包所有模块")
        return 1
        
    # 设置输出目录
    output_dir = Path(args.output) if args.output else packager.output_dir
    
    # 打包统计
    total = len(modules_to_pack)
    success_count = 0
    failed_modules = []
    
    print_info(f"准备打包 {total} 个模块")
    print_info(f"输出目录: {output_dir}")
    
    # 执行打包
    for module_path in modules_to_pack:
        print_info(f"\n处理模块: {module_path.name}")
        
        if args.type != "auto":
            # 指定类型打包
            if args.type == "cmod":
                success = packager.pack_cmod(module_path, output_dir)
            else:
                success = packager.pack_cjmod(module_path, output_dir)
        else:
            # 自动检测打包
            success = packager.pack_module(module_path, output_dir)
            
        if success:
            success_count += 1
        else:
            failed_modules.append(module_path.name)
            
    # 打印统计
    print_info(f"\n打包完成!")
    print_success(f"成功: {success_count}/{total}")
    
    if failed_modules:
        print_error(f"失败的模块: {', '.join(failed_modules)}")
        return 1
        
    return 0

if __name__ == "__main__":
    sys.exit(main())