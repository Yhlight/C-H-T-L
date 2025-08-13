#!/usr/bin/env python3
"""
CHTL 跨平台构建脚本
支持: Windows, Linux, macOS
"""

import os
import sys
import subprocess
import platform
import argparse
import shutil
import multiprocessing
from pathlib import Path

# 颜色输出（跨平台）
class Colors:
    def __init__(self):
        self.enabled = sys.stdout.isatty()
        
    def red(self, text):
        return f"\033[31m{text}\033[0m" if self.enabled else text
        
    def green(self, text):
        return f"\033[32m{text}\033[0m" if self.enabled else text
        
    def yellow(self, text):
        return f"\033[33m{text}\033[0m" if self.enabled else text
        
    def blue(self, text):
        return f"\033[34m{text}\033[0m" if self.enabled else text

colors = Colors()

def print_info(msg):
    print(f"{colors.blue('[INFO]')} {msg}")

def print_success(msg):
    print(f"{colors.green('[SUCCESS]')} {msg}")

def print_warning(msg):
    print(f"{colors.yellow('[WARNING]')} {msg}")

def print_error(msg):
    print(f"{colors.red('[ERROR]')} {msg}")

class CHTLBuilder:
    def __init__(self):
        self.root_dir = Path(__file__).parent.parent.absolute()
        self.build_dir = self.root_dir / "build"
        self.platform = platform.system().lower()
        self.cpu_count = multiprocessing.cpu_count()
        
    def check_dependencies(self):
        """检查构建依赖"""
        print_info("检查构建依赖...")
        
        # 检查CMake
        if not shutil.which("cmake"):
            print_error("未找到CMake，请先安装CMake")
            return False
            
        # 检查编译器
        if self.platform == "windows":
            # 检查MSVC或MinGW
            if not (shutil.which("cl") or shutil.which("g++")):
                print_error("未找到C++编译器，请安装Visual Studio或MinGW")
                return False
        else:
            if not shutil.which("g++") and not shutil.which("clang++"):
                print_error("未找到C++编译器")
                return False
                
        # 检查Java（用于ANTLR）
        if not shutil.which("java"):
            print_warning("未找到Java，ANTLR解析器生成将被跳过")
            
        print_success("依赖检查通过")
        return True
        
    def generate_parsers(self):
        """生成ANTLR解析器"""
        print_info("生成ANTLR解析器...")
        
        antlr_jar = self.root_dir / "tools" / "antlr-4.13.1-complete.jar"
        if not antlr_jar.exists():
            print_warning("ANTLR JAR文件不存在，跳过解析器生成")
            return True
            
        grammars_dir = self.root_dir / "grammars"
        generated_dir = self.root_dir / "generated"
        
        # 创建生成目录
        generated_dir.mkdir(exist_ok=True)
        
        # 生成CSS解析器
        css_grammar = grammars_dir / "CSS3.g4"
        if css_grammar.exists():
            print_info("生成CSS解析器...")
            cmd = [
                "java", "-jar", str(antlr_jar),
                "-Dlanguage=Cpp",
                "-no-listener", "-visitor",
                "-o", str(generated_dir / "css"),
                str(css_grammar)
            ]
            result = subprocess.run(cmd, capture_output=True, text=True)
            if result.returncode != 0:
                print_error(f"CSS解析器生成失败: {result.stderr}")
                return False
                
        # 生成JS解析器
        js_lexer = grammars_dir / "JavaScriptLexer.g4"
        js_parser = grammars_dir / "JavaScriptParser.g4"
        if js_lexer.exists() and js_parser.exists():
            print_info("生成JavaScript解析器...")
            for grammar in [js_lexer, js_parser]:
                cmd = [
                    "java", "-jar", str(antlr_jar),
                    "-Dlanguage=Cpp",
                    "-no-listener", "-visitor",
                    "-o", str(generated_dir / "js"),
                    str(grammar)
                ]
                result = subprocess.run(cmd, capture_output=True, text=True)
                if result.returncode != 0:
                    print_error(f"JS解析器生成失败: {result.stderr}")
                    return False
                    
        print_success("解析器生成完成")
        return True
        
    def configure_cmake(self, build_type="Release", generator=None):
        """配置CMake"""
        print_info(f"配置CMake ({build_type})...")
        
        # 创建构建目录
        self.build_dir.mkdir(exist_ok=True)
        
        # CMake命令
        cmd = ["cmake", str(self.root_dir)]
        cmd.extend([f"-DCMAKE_BUILD_TYPE={build_type}"])
        
        # 平台特定的生成器
        if generator:
            cmd.extend(["-G", generator])
        elif self.platform == "windows":
            # Windows默认使用Visual Studio或MinGW Makefiles
            if shutil.which("cl"):
                # 自动检测Visual Studio版本
                pass  # CMake会自动选择
            elif shutil.which("mingw32-make"):
                cmd.extend(["-G", "MinGW Makefiles"])
                
        # 在构建目录中执行
        result = subprocess.run(cmd, cwd=self.build_dir, capture_output=True, text=True)
        if result.returncode != 0:
            print_error(f"CMake配置失败:\n{result.stderr}")
            return False
            
        print_success("CMake配置完成")
        return True
        
    def build(self, target=None, jobs=None):
        """构建项目"""
        print_info("开始构建...")
        
        if jobs is None:
            jobs = self.cpu_count
            
        # 构建命令
        cmd = ["cmake", "--build", str(self.build_dir)]
        
        if target:
            cmd.extend(["--target", target])
            
        # 并行构建
        if self.platform == "windows" and shutil.which("msbuild"):
            cmd.extend(["/m:" + str(jobs)])
        else:
            cmd.extend(["-j", str(jobs)])
            
        # 执行构建
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print_error(f"构建失败:\n{result.stderr}")
            return False
            
        print_success("构建完成")
        return True
        
    def install(self, prefix=None):
        """安装项目"""
        print_info("安装项目...")
        
        cmd = ["cmake", "--install", str(self.build_dir)]
        
        if prefix:
            cmd.extend(["--prefix", str(prefix)])
        elif self.platform == "windows":
            # Windows默认安装到Program Files
            if not self._is_admin():
                print_warning("需要管理员权限才能安装到默认位置")
                
        # 执行安装
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print_error(f"安装失败:\n{result.stderr}")
            return False
            
        print_success("安装完成")
        return True
        
    def clean(self):
        """清理构建"""
        print_info("清理构建目录...")
        
        if self.build_dir.exists():
            shutil.rmtree(self.build_dir)
            
        print_success("清理完成")
        return True
        
    def test(self):
        """运行测试"""
        print_info("运行测试...")
        
        # CTest命令
        cmd = ["ctest", "--test-dir", str(self.build_dir), "--output-on-failure"]
        
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print_error(f"测试失败:\n{result.stderr}")
            return False
            
        print_success("所有测试通过")
        return True
        
    def _is_admin(self):
        """检查是否有管理员权限"""
        if self.platform == "windows":
            try:
                import ctypes
                return ctypes.windll.shell32.IsUserAnAdmin() != 0
            except:
                return False
        else:
            return os.geteuid() == 0

def main():
    parser = argparse.ArgumentParser(description="CHTL跨平台构建脚本")
    parser.add_argument("--type", choices=["Debug", "Release", "RelWithDebInfo"], 
                        default="Release", help="构建类型")
    parser.add_argument("--generator", help="CMake生成器")
    parser.add_argument("--jobs", "-j", type=int, help="并行构建任务数")
    parser.add_argument("--prefix", help="安装前缀")
    parser.add_argument("--clean", action="store_true", help="清理构建")
    parser.add_argument("--test", action="store_true", help="运行测试")
    parser.add_argument("--no-parsers", action="store_true", help="跳过解析器生成")
    parser.add_argument("--install", action="store_true", help="安装项目")
    parser.add_argument("--target", help="构建特定目标")
    
    args = parser.parse_args()
    
    # 显示系统信息
    print_info(f"平台: {platform.system()} {platform.machine()}")
    print_info(f"Python: {sys.version.split()[0]}")
    print_info(f"CPU核心数: {multiprocessing.cpu_count()}")
    
    builder = CHTLBuilder()
    
    # 清理
    if args.clean:
        builder.clean()
        if not any([args.test, args.install, not args.clean]):
            return 0
            
    # 检查依赖
    if not builder.check_dependencies():
        return 1
        
    # 生成解析器
    if not args.no_parsers:
        if not builder.generate_parsers():
            print_warning("解析器生成失败，继续构建...")
            
    # 配置CMake
    if not builder.configure_cmake(args.type, args.generator):
        return 1
        
    # 构建
    if not builder.build(args.target, args.jobs):
        return 1
        
    # 测试
    if args.test:
        if not builder.test():
            return 1
            
    # 安装
    if args.install:
        if not builder.install(args.prefix):
            return 1
            
    print_success("所有操作完成！")
    return 0

if __name__ == "__main__":
    sys.exit(main())