@echo off
:: CHTL Windows环境设置脚本
:: 自动下载和配置依赖

setlocal enabledelayedexpansion

echo ====================================
echo CHTL Windows环境设置
echo ====================================
echo.

:: 检查管理员权限
net session >nul 2>&1
if errorlevel 1 (
    echo [WARNING] 建议以管理员身份运行此脚本
    echo.
)

:: 检查Chocolatey
where choco >nul 2>&1
if errorlevel 1 (
    echo [INFO] 安装Chocolatey包管理器...
    @"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "[System.Net.ServicePointManager]::SecurityProtocol = 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"
)

:: 检查并安装依赖
echo [INFO] 检查并安装依赖...

:: Python
python --version >nul 2>&1
if errorlevel 1 (
    echo [INFO] 安装Python...
    choco install python -y
    refreshenv
)

:: CMake
cmake --version >nul 2>&1
if errorlevel 1 (
    echo [INFO] 安装CMake...
    choco install cmake -y
    refreshenv
)

:: Git
git --version >nul 2>&1
if errorlevel 1 (
    echo [INFO] 安装Git...
    choco install git -y
    refreshenv
)

:: Java (用于ANTLR)
java -version >nul 2>&1
if errorlevel 1 (
    echo [INFO] 安装Java...
    choco install openjdk -y
    refreshenv
)

:: Visual Studio Build Tools (如果没有完整VS)
cl >nul 2>&1
if errorlevel 1 (
    echo [INFO] 未检测到Visual Studio编译器
    echo 您可以选择:
    echo 1. 安装Visual Studio Build Tools (推荐)
    echo 2. 安装MinGW-w64
    echo 3. 跳过 (如果已有其他编译器)
    echo.
    set /p choice="请选择 (1/2/3): "
    
    if "!choice!"=="1" (
        echo [INFO] 安装Visual Studio Build Tools...
        choco install visualstudio2022buildtools -y
        choco install visualstudio2022-workload-vctools -y
    ) else if "!choice!"=="2" (
        echo [INFO] 安装MinGW-w64...
        choco install mingw -y
    )
)

:: 设置环境变量
echo.
echo [INFO] 设置环境变量...

:: 添加scripts目录到PATH
set SCRIPT_DIR=%~dp0
setx PATH "%PATH%;%SCRIPT_DIR%" /M >nul 2>&1

:: 下载ANTLR JAR
set TOOLS_DIR=%SCRIPT_DIR%..\tools
if not exist "%TOOLS_DIR%" mkdir "%TOOLS_DIR%"

if not exist "%TOOLS_DIR%\antlr-4.13.1-complete.jar" (
    echo [INFO] 下载ANTLR...
    powershell -Command "Invoke-WebRequest -Uri 'https://www.antlr.org/download/antlr-4.13.1-complete.jar' -OutFile '%TOOLS_DIR%\antlr-4.13.1-complete.jar'"
)

echo.
echo ====================================
echo 环境设置完成！
echo ====================================
echo.
echo 您现在可以使用以下命令:
echo   build.bat         - 构建项目
echo   pack.bat          - 打包模块
echo   build.bat --help  - 查看构建选项
echo   pack.bat --help   - 查看打包选项
echo.
echo 建议重启命令行窗口以应用环境变量更改
echo.

pause