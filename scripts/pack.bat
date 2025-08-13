@echo off
:: CHTL Windows打包脚本
:: 需要: Python 3.6+

setlocal enabledelayedexpansion

:: 检查Python
python --version >nul 2>&1
if errorlevel 1 (
    echo [ERROR] 未找到Python，请先安装Python 3.6+
    exit /b 1
)

:: 获取脚本目录
set SCRIPT_DIR=%~dp0
set ROOT_DIR=%SCRIPT_DIR%..

:: 切换到项目根目录
cd /d "%ROOT_DIR%"

:: 调用Python打包脚本
echo [INFO] 调用跨平台打包脚本...
python "%SCRIPT_DIR%pack.py" %*

:: 返回错误码
exit /b %errorlevel%