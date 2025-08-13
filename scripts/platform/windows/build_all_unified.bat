@echo off
rem CHTL Unified Build Script for Windows

setlocal enabledelayedexpansion

rem Set directories
set SCRIPT_DIR=%~dp0
set ROOT_DIR=%SCRIPT_DIR%..\..\..
cd /d "%ROOT_DIR%"

rem Default values
set BUILD_TYPE=Release
set BUILD_COMPILER=1
set BUILD_VSCODE=1
set EMBED_COMPILER=1
set CLEAN=0
set INSTALL=0
set JOBS=%NUMBER_OF_PROCESSORS%
set VERBOSE=0

rem Parse arguments
:parse_args
if "%1"=="" goto :args_done
if /i "%1"=="--help" goto :show_help
if /i "%1"=="-h" goto :show_help
if /i "%1"=="--type" (
    set BUILD_TYPE=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="--jobs" (
    set JOBS=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="-j" (
    set JOBS=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="--clean" (
    set CLEAN=1
    shift
    goto :parse_args
)
if /i "%1"=="--install" (
    set INSTALL=1
    shift
    goto :parse_args
)
if /i "%1"=="--no-compiler" (
    set BUILD_COMPILER=0
    shift
    goto :parse_args
)
if /i "%1"=="--no-vscode" (
    set BUILD_VSCODE=0
    shift
    goto :parse_args
)
if /i "%1"=="--no-embed" (
    set EMBED_COMPILER=0
    shift
    goto :parse_args
)
if /i "%1"=="--verbose" (
    set VERBOSE=1
    shift
    goto :parse_args
)
shift
goto :parse_args

:args_done

rem Calculate total steps
set TOTAL_STEPS=0
if %BUILD_COMPILER%==1 set /a TOTAL_STEPS+=1
if %BUILD_VSCODE%==1 set /a TOTAL_STEPS+=1
set CURRENT_STEP=0

rem Show configuration
echo ========================================
echo CHTL Unified Build Configuration
echo ========================================
echo Build Type: %BUILD_TYPE%
echo Build Compiler: %BUILD_COMPILER%
echo Build VSCode Extension: %BUILD_VSCODE%
echo Embed Compiler: %EMBED_COMPILER%
echo Parallel Jobs: %JOBS%
echo Total Steps: %TOTAL_STEPS%
echo ========================================
echo.

rem Record start time
set START_TIME=%TIME%

rem Clean flag
set CLEAN_FLAG=
if %CLEAN%==1 set CLEAN_FLAG=--clean

rem Build compiler
if %BUILD_COMPILER%==1 (
    set /a CURRENT_STEP+=1
    echo [STEP !CURRENT_STEP!/%TOTAL_STEPS%] Building CHTL Compiler ^(%BUILD_TYPE%^)
    echo.
    
    rem Choose build script
    if /i "%BUILD_TYPE%"=="Debug" (
        set BUILD_SCRIPT=%SCRIPT_DIR%build_debug.bat
    ) else (
        set BUILD_SCRIPT=%SCRIPT_DIR%build_release.bat
    )
    
    rem Build arguments
    set BUILD_ARGS=%CLEAN_FLAG% -j %JOBS%
    if %INSTALL%==1 set BUILD_ARGS=!BUILD_ARGS! --install
    if %VERBOSE%==1 set BUILD_ARGS=!BUILD_ARGS! --verbose
    
    rem Execute build
    if %VERBOSE%==1 (
        call "!BUILD_SCRIPT!" !BUILD_ARGS!
    ) else (
        call "!BUILD_SCRIPT!" !BUILD_ARGS! > "%TEMP%\chtl_compiler_build.log" 2>&1
    )
    
    if !errorlevel!==0 (
        echo [SUCCESS] Compiler build completed
        
        rem Show build results
        if /i "%BUILD_TYPE%"=="Debug" (
            set COMPILER_PATH=build-debug\chtlc.exe
            set MODULES_PATH=build-debug\modules
        ) else (
            set COMPILER_PATH=build-release\chtlc.exe
            set MODULES_PATH=build-release\modules
        )
        
        if exist "!COMPILER_PATH!" (
            echo [INFO] Compiler location: !COMPILER_PATH!
            for %%F in ("!COMPILER_PATH!") do echo [INFO] Compiler size: %%~zF bytes
        )
        
        if exist "!MODULES_PATH!" (
            set CMOD_COUNT=0
            set CJMOD_COUNT=0
            for %%F in ("!MODULES_PATH!\*.cmod") do set /a CMOD_COUNT+=1
            for %%F in ("!MODULES_PATH!\*.cjmod") do set /a CJMOD_COUNT+=1
            echo [INFO] Packed modules: !CMOD_COUNT! CMOD, !CJMOD_COUNT! CJMOD
        )
    ) else (
        echo [ERROR] Compiler build failed
        if %VERBOSE%==0 echo [INFO] See detailed log: %TEMP%\chtl_compiler_build.log
        exit /b 1
    )
    
    echo.
)

rem Build VSCode extension
if %BUILD_VSCODE%==1 (
    set /a CURRENT_STEP+=1
    echo [STEP !CURRENT_STEP!/%TOTAL_STEPS%] Building VSCode Extension
    echo.
    
    rem Build arguments
    set VSCODE_ARGS=%CLEAN_FLAG%
    if %EMBED_COMPILER%==1 set VSCODE_ARGS=!VSCODE_ARGS! --embed-compiler
    if %INSTALL%==1 set VSCODE_ARGS=!VSCODE_ARGS! --install
    
    rem If embedding compiler, ensure compiler is built
    if %EMBED_COMPILER%==1 if %BUILD_COMPILER%==0 (
        if not exist "build-release\chtlc.exe" if not exist "build\chtlc.exe" (
            echo [WARNING] Compiler not found, will not embed compiler in VSCode extension
            set VSCODE_ARGS=!VSCODE_ARGS:--embed-compiler=!
        )
    )
    
    rem Execute build
    if %VERBOSE%==1 (
        call "%SCRIPT_DIR%build_vscode_extension.bat" !VSCODE_ARGS!
    ) else (
        call "%SCRIPT_DIR%build_vscode_extension.bat" !VSCODE_ARGS! > "%TEMP%\chtl_vscode_build.log" 2>&1
    )
    
    if !errorlevel!==0 (
        echo [SUCCESS] VSCode extension build completed
        
        rem Find VSIX file
        set VSIX_FILE=
        for %%F in (build-vscode\*.vsix) do set VSIX_FILE=%%F
        
        if exist "!VSIX_FILE!" (
            echo [INFO] VSIX file: !VSIX_FILE!
            for %%F in ("!VSIX_FILE!") do echo [INFO] File size: %%~zF bytes
        )
    ) else (
        echo [ERROR] VSCode extension build failed
        if %VERBOSE%==0 echo [INFO] See detailed log: %TEMP%\chtl_vscode_build.log
        exit /b 1
    )
    
    echo.
)

rem Calculate duration
set END_TIME=%TIME%

rem Show final results
echo ========================================
echo Unified Build Completed!
echo ========================================
echo Start time: %START_TIME%
echo End time: %END_TIME%
echo.

rem Build artifacts summary
echo [INFO] Build Artifacts Summary:

if %BUILD_COMPILER%==1 (
    echo   Compiler:
    echo     - Executable: !COMPILER_PATH!
    if exist "!MODULES_PATH!" (
        echo     - Modules: !MODULES_PATH!
    )
)

if %BUILD_VSCODE%==1 if exist "!VSIX_FILE!" (
    echo   VSCode Extension:
    echo     - VSIX file: !VSIX_FILE!
    if %EMBED_COMPILER%==1 (
        echo     - Embedded compiler: Yes
    )
)

echo.

rem Next steps
echo [INFO] Next Steps:

if %BUILD_COMPILER%==1 if %INSTALL%==0 (
    echo   1. Install compiler: !BUILD_SCRIPT! --install
)

if %BUILD_VSCODE%==1 if %INSTALL%==0 if exist "!VSIX_FILE!" (
    echo   2. Install VSCode extension: code --install-extension "!VSIX_FILE!"
)

echo   3. Start using CHTL: Create .chtl files and start coding!

exit /b 0

:show_help
echo CHTL Unified Build Script
echo.
echo Usage: build_all_unified.bat [options]
echo.
echo Options:
echo   --help, -h          Show this help message
echo   --type TYPE         Build type (Debug/Release) [default: Release]
echo   --jobs N, -j N      Number of parallel jobs [default: %NUMBER_OF_PROCESSORS%]
echo   --clean             Clean before building
echo   --install           Install compiler and VSCode extension
echo   --no-compiler       Do not build compiler
echo   --no-vscode         Do not build VSCode extension
echo   --no-embed          Do not embed compiler in VSCode extension
echo   --verbose           Show verbose output
echo.
echo Examples:
echo   build_all_unified.bat                    # Full build (Release)
echo   build_all_unified.bat --type Debug       # Debug build
echo   build_all_unified.bat --clean --install  # Clean build and install
echo.
exit /b 0