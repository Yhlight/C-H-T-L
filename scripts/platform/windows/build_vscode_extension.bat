@echo off
rem CHTL VSCode Extension Build Script for Windows

setlocal enabledelayedexpansion

rem Set directories
set SCRIPT_DIR=%~dp0
set ROOT_DIR=%SCRIPT_DIR%..\..\..
cd /d "%ROOT_DIR%"

rem Default values
set EXTENSION_DIR=vscode-ide\chtl-language-extension
set OUTPUT_DIR=build-vscode
set CLEAN=0
set PACKAGE=1
set INSTALL=0
set EMBED_COMPILER=0
set COMPILER_PATH=

rem Parse arguments
:parse_args
if "%1"=="" goto :args_done
if /i "%1"=="--help" goto :show_help
if /i "%1"=="-h" goto :show_help
if /i "%1"=="--clean" (
    set CLEAN=1
    shift
    goto :parse_args
)
if /i "%1"=="--no-package" (
    set PACKAGE=0
    shift
    goto :parse_args
)
if /i "%1"=="--install" (
    set INSTALL=1
    shift
    goto :parse_args
)
if /i "%1"=="--embed-compiler" (
    set EMBED_COMPILER=1
    shift
    goto :parse_args
)
if /i "%1"=="--compiler" (
    set COMPILER_PATH=%2
    shift
    shift
    goto :parse_args
)
shift
goto :parse_args

:args_done

rem Show configuration
echo ========================================
echo VSCode Extension Build Configuration
echo ========================================
echo Extension Directory: %EXTENSION_DIR%
echo Output Directory: %OUTPUT_DIR%
echo Embed Compiler: %EMBED_COMPILER%
echo ========================================
echo.

rem Check dependencies
echo Checking dependencies...

where npm >nul 2>&1
if errorlevel 1 (
    echo [ERROR] npm not found. Please install Node.js.
    exit /b 1
)

where code >nul 2>&1
if errorlevel 1 (
    echo [WARNING] VS Code command not found. Cannot auto-install extension.
)

rem Clean
if %CLEAN%==1 (
    echo Cleaning build directories...
    if exist "%OUTPUT_DIR%" rmdir /s /q "%OUTPUT_DIR%"
    if exist "%EXTENSION_DIR%\out" rmdir /s /q "%EXTENSION_DIR%\out"
    if exist "%EXTENSION_DIR%\node_modules" rmdir /s /q "%EXTENSION_DIR%\node_modules"
    del /q "%EXTENSION_DIR%\*.vsix" 2>nul
)

rem Create output directory
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

rem Enter extension directory
cd "%EXTENSION_DIR%"

rem Install dependencies
echo Installing npm dependencies...
call npm install

if errorlevel 1 (
    echo [ERROR] npm install failed
    exit /b 1
)

rem Compile TypeScript
echo Compiling TypeScript...
call npm run compile

if errorlevel 1 (
    echo [ERROR] TypeScript compilation failed
    exit /b 1
)

rem Embed compiler
if %EMBED_COMPILER%==1 (
    echo Embedding compiler and modules...
    
    rem Create embedded directories
    if not exist "embedded\bin" mkdir "embedded\bin"
    if not exist "embedded\modules" mkdir "embedded\modules"
    
    rem Find compiler
    set CHTLC_PATH=
    if not "%COMPILER_PATH%"=="" if exist "%COMPILER_PATH%" (
        set CHTLC_PATH=%COMPILER_PATH%
    ) else if exist "%ROOT_DIR%\build-release\chtlc.exe" (
        set CHTLC_PATH=%ROOT_DIR%\build-release\chtlc.exe
    ) else if exist "%ROOT_DIR%\build-release\Release\chtlc.exe" (
        set CHTLC_PATH=%ROOT_DIR%\build-release\Release\chtlc.exe
    ) else if exist "%ROOT_DIR%\build\chtlc.exe" (
        set CHTLC_PATH=%ROOT_DIR%\build\chtlc.exe
    ) else if exist "%ROOT_DIR%\build\Release\chtlc.exe" (
        set CHTLC_PATH=%ROOT_DIR%\build\Release\chtlc.exe
    )
    
    if "!CHTLC_PATH!"=="" (
        echo [ERROR] Compiler not found. Please build compiler first or use --compiler
        exit /b 1
    )
    
    rem Copy compiler
    copy "!CHTLC_PATH!" "embedded\bin\chtlc.exe" >nul
    echo [INFO] Embedded compiler: chtlc.exe
    
    rem Find and copy modules
    set MODULE_DIR=
    if exist "%ROOT_DIR%\build-release\modules" (
        set MODULE_DIR=%ROOT_DIR%\build-release\modules
    ) else if exist "%ROOT_DIR%\build\modules" (
        set MODULE_DIR=%ROOT_DIR%\build\modules
    )
    
    if not "!MODULE_DIR!"=="" if exist "!MODULE_DIR!" (
        copy "!MODULE_DIR!\*.cmod" "embedded\modules\" >nul 2>&1
        copy "!MODULE_DIR!\*.cjmod" "embedded\modules\" >nul 2>&1
        
        set CMOD_COUNT=0
        set CJMOD_COUNT=0
        for %%F in (embedded\modules\*.cmod) do set /a CMOD_COUNT+=1
        for %%F in (embedded\modules\*.cjmod) do set /a CJMOD_COUNT+=1
        
        echo [INFO] Embedded modules: !CMOD_COUNT! CMOD, !CJMOD_COUNT! CJMOD
    ) else (
        echo [WARNING] No packaged modules found
    )
)

rem Package VSIX
if %PACKAGE%==1 (
    echo Packaging VSIX file...
    
    rem Install vsce if not exists
    where vsce >nul 2>&1
    if errorlevel 1 (
        echo Installing vsce...
        call npm install -g vsce
    )
    
    rem Package
    call vsce package --out "%ROOT_DIR%\%OUTPUT_DIR%\"
    
    if errorlevel 1 (
        echo [ERROR] VSIX packaging failed
        exit /b 1
    )
    
    rem Find VSIX file
    for %%F in ("%ROOT_DIR%\%OUTPUT_DIR%\*.vsix") do set VSIX_FILE=%%F
    
    if exist "!VSIX_FILE!" (
        echo [SUCCESS] VSIX file created: !VSIX_FILE!
    ) else (
        echo [ERROR] VSIX file not found
        exit /b 1
    )
)

cd "%ROOT_DIR%"

rem Install to VSCode
if %INSTALL%==1 (
    where code >nul 2>&1
    if errorlevel 1 (
        echo [ERROR] VS Code command not found. Cannot auto-install.
        echo [INFO] Please install manually: Extensions -^> ... -^> Install from VSIX...
        exit /b 1
    )
    
    if exist "!VSIX_FILE!" (
        echo Installing extension to VS Code...
        code --install-extension "!VSIX_FILE!"
        
        if errorlevel 1 (
            echo [ERROR] Extension installation failed
        ) else (
            echo [SUCCESS] Extension installed successfully
            echo [INFO] Please restart VS Code to activate the extension
        )
    ) else (
        echo [ERROR] VSIX file not found
    )
)

rem Show build results
echo.
echo ========================================
echo VSCode Extension Build Completed!
echo ========================================

if %PACKAGE%==1 if exist "!VSIX_FILE!" (
    echo VSIX file: !VSIX_FILE!
    for %%F in ("!VSIX_FILE!") do echo File size: %%~zF bytes
)

if %EMBED_COMPILER%==1 (
    echo Embedded compiler: Yes
)

echo.
echo Installation instructions:
echo   1. Command line: code --install-extension "!VSIX_FILE!"
echo   2. VS Code GUI: Extensions -^> ... -^> Install from VSIX...
echo   3. Development: Open %EXTENSION_DIR% in VS Code and press F5

exit /b 0

:show_help
echo CHTL VSCode Extension Build Script
echo.
echo Usage: build_vscode_extension.bat [options]
echo.
echo Options:
echo   --help, -h          Show this help message
echo   --clean             Clean before building
echo   --no-package        Do not package VSIX file
echo   --install           Install to VS Code
echo   --embed-compiler    Embed compiler in extension
echo   --compiler PATH     Specify compiler path
echo.
echo Examples:
echo   build_vscode_extension.bat                # Build extension
echo   build_vscode_extension.bat --embed-compiler   # Build with embedded compiler
echo   build_vscode_extension.bat --install          # Build and install
echo.
exit /b 0