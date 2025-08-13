#!/usr/bin/env python3
"""
CHTL 跨平台测试脚本
验证跨平台功能是否正常工作
"""

import os
import sys
import platform
import subprocess
import shutil
from pathlib import Path

def test_platform_info():
    """显示平台信息"""
    print("=== 平台信息 ===")
    print(f"操作系统: {platform.system()}")
    print(f"版本: {platform.version()}")
    print(f"架构: {platform.machine()}")
    print(f"Python: {sys.version}")
    print()

def test_dependencies():
    """测试依赖项"""
    print("=== 检查依赖 ===")
    
    dependencies = [
        ("Python", "python" if platform.system() == "Windows" else "python3"),
        ("CMake", "cmake"),
        ("Git", "git"),
        ("Java", "java"),
    ]
    
    for name, cmd in dependencies:
        if shutil.which(cmd):
            try:
                if cmd == "java":
                    result = subprocess.run([cmd, "-version"], 
                                          capture_output=True, text=True, stderr=subprocess.STDOUT)
                else:
                    result = subprocess.run([cmd, "--version"], 
                                          capture_output=True, text=True)
                version = result.stdout.split('\n')[0] if result.stdout else result.stderr.split('\n')[0]
                print(f"✓ {name}: {version.strip()}")
            except:
                print(f"✓ {name}: 已安装")
        else:
            print(f"✗ {name}: 未找到")
    
    # 检查C++编译器
    if platform.system() == "Windows":
        if shutil.which("cl"):
            print("✓ C++编译器: MSVC")
        elif shutil.which("g++"):
            print("✓ C++编译器: MinGW")
        else:
            print("✗ C++编译器: 未找到")
    else:
        if shutil.which("g++"):
            print("✓ C++编译器: GCC")
        elif shutil.which("clang++"):
            print("✓ C++编译器: Clang")
        else:
            print("✗ C++编译器: 未找到")
    print()

def test_scripts():
    """测试脚本可用性"""
    print("=== 测试脚本 ===")
    
    script_dir = Path(__file__).parent
    
    # Python脚本
    py_scripts = ["build.py", "pack.py"]
    for script in py_scripts:
        script_path = script_dir / script
        if script_path.exists():
            print(f"✓ {script}: 存在")
        else:
            print(f"✗ {script}: 缺失")
    
    # 平台特定脚本
    if platform.system() == "Windows":
        bat_scripts = ["build.bat", "pack.bat", "setup-windows.bat"]
        for script in bat_scripts:
            script_path = script_dir / script
            if script_path.exists():
                print(f"✓ {script}: 存在")
            else:
                print(f"✗ {script}: 缺失")
    else:
        sh_scripts = ["build_compiler.sh", "pack_cmod.sh", "pack_cjmod.sh"]
        for script in sh_scripts:
            script_path = script_dir / script
            if script_path.exists():
                print(f"✓ {script}: 存在")
            else:
                print(f"✗ {script}: 缺失")
    print()

def test_build_system():
    """测试构建系统"""
    print("=== 测试构建系统 ===")
    
    # 检查CMakeLists.txt
    root_dir = Path(__file__).parent.parent
    cmake_file = root_dir / "CMakeLists.txt"
    
    if cmake_file.exists():
        print("✓ CMakeLists.txt: 存在")
        
        # 检查是否可以配置
        build_dir = root_dir / "build_test"
        build_dir.mkdir(exist_ok=True)
        
        try:
            result = subprocess.run(
                ["cmake", str(root_dir)],
                cwd=str(build_dir),
                capture_output=True,
                text=True
            )
            
            if result.returncode == 0:
                print("✓ CMake配置: 成功")
            else:
                print("✗ CMake配置: 失败")
                print(f"  错误: {result.stderr}")
                
            # 清理测试目录
            import shutil
            shutil.rmtree(build_dir)
            
        except Exception as e:
            print(f"✗ CMake配置: 异常 - {e}")
    else:
        print("✗ CMakeLists.txt: 缺失")
    print()

def main():
    print("CHTL 跨平台测试")
    print("=" * 40)
    print()
    
    test_platform_info()
    test_dependencies()
    test_scripts()
    test_build_system()
    
    print("=" * 40)
    print("测试完成！")
    
    # 提供建议
    print("\n建议:")
    if platform.system() == "Windows":
        print("- 如果缺少依赖，请运行: scripts\\setup-windows.bat")
        print("- 构建项目: python scripts\\build.py --type Release")
    else:
        print("- 如果缺少依赖，请使用包管理器安装")
        print("- 构建项目: python3 scripts/build.py --type Release")

if __name__ == "__main__":
    main()