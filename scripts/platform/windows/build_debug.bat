@echo off
rem CHTL Debug Build Script for Windows - Auto-pack modules

setlocal enabledelayedexpansion

rem Set directories
set SCRIPT_DIR=%~dp0
set ROOT_DIR=%SCRIPT_DIR%..\..\..
cd /d "%ROOT_DIR%"

rem Default values
set BUILD_DIR=build-debug
set BUILD_TYPE=Debug
set GENERATOR=
set CLEAN=0
set VERBOSE=0
set PACK_MODULES=1
set JOBS=%NUMBER_OF_PROCESSORS%

rem Parse arguments
:parse_args
if "%1"=="" goto :args_done
if /i "%1"=="--help" goto :show_help
if /i "%1"=="-h" goto :show_help
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
if /i "%1"=="--no-pack" (
    set PACK_MODULES=0
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

rem Show configuration
echo ========================================
echo CHTL Debug Build Configuration
echo ========================================
echo Build Type: Debug
echo Build Directory: %BUILD_DIR%
echo Jobs: %JOBS%
echo Auto Pack: %PACK_MODULES%
echo ========================================
echo.

rem Check dependencies
echo Checking dependencies...

where cmake >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake not found. Please install CMake.
    exit /b 1
)

rem Check compiler
set COMPILER_FOUND=0
where cl >nul 2>&1
if not errorlevel 1 (
    echo [INFO] Found MSVC compiler
    set COMPILER_FOUND=1
    if "%GENERATOR%"=="" set GENERATOR=Visual Studio 17 2022
)

if %COMPILER_FOUND%==0 (
    where g++ >nul 2>&1
    if not errorlevel 1 (
        echo [INFO] Found MinGW compiler
        set COMPILER_FOUND=1
        if "%GENERATOR%"=="" set GENERATOR=MinGW Makefiles
    )
)

if %COMPILER_FOUND%==0 (
    echo [ERROR] No C++ compiler found. Please install Visual Studio or MinGW.
    exit /b 1
)

rem Clean if requested
if %CLEAN%==1 (
    echo Cleaning build directory...
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
)

rem Create build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

rem Generate parsers
if exist "tools\antlr-4.13.1-complete.jar" (
    echo Generating parsers...
    
    if not exist "generated" mkdir "generated"
    if not exist "generated\css" mkdir "generated\css"
    if not exist "generated\js" mkdir "generated\js"
    
    if exist "grammars\CSS3.g4" (
        java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\css grammars\CSS3.g4
    )
    
    if exist "grammars\JavaScriptLexer.g4" (
        java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\js grammars\JavaScriptLexer.g4
    )
    
    if exist "grammars\JavaScriptParser.g4" (
        java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\js grammars\JavaScriptParser.g4
    )
)

rem Configure CMake
echo Configuring CMake (Debug mode)...
cd "%BUILD_DIR%"

set CMAKE_ARGS=-DCMAKE_BUILD_TYPE=Debug
if not "%GENERATOR%"=="" set CMAKE_ARGS=%CMAKE_ARGS% -G "%GENERATOR%"

cmake %CMAKE_ARGS% ..
if errorlevel 1 (
    echo [ERROR] CMake configuration failed
    exit /b 1
)

rem Build
echo Building CHTL compiler...
cmake --build . --config Debug -j %JOBS%
if errorlevel 1 (
    echo [ERROR] Build failed
    exit /b 1
)

echo [SUCCESS] Compiler build completed

cd ..

rem Auto pack modules
if %PACK_MODULES%==1 (
    echo Starting auto module packing...
    
    rem Create module output directory
    set MODULE_OUTPUT_DIR=%BUILD_DIR%\modules
    if not exist "!MODULE_OUTPUT_DIR!" mkdir "!MODULE_OUTPUT_DIR!"
    
    rem Pack all modules
    if exist "src\module" (
        for /d %%M in (src\module\*) do (
            if exist "%%M" (
                set MODULE_NAME=%%~nxM
                echo Packing module: !MODULE_NAME!
                
                rem Use packing script
                call "%SCRIPT_DIR%..\..\pack\pack_all.bat" "%%M" -o "!MODULE_OUTPUT_DIR!"
            )
        )
        
        rem Count results
        set CMOD_COUNT=0
        set CJMOD_COUNT=0
        for %%F in ("!MODULE_OUTPUT_DIR!\*.cmod") do set /a CMOD_COUNT+=1
        for %%F in ("!MODULE_OUTPUT_DIR!\*.cjmod") do set /a CJMOD_COUNT+=1
        
        echo [SUCCESS] Module packing completed: !CMOD_COUNT! CMOD, !CJMOD_COUNT! CJMOD
    ) else (
        echo [WARNING] Module directory not found
    )
)

rem Show build results
echo.
echo ========================================
echo Debug build completed!
echo ========================================
echo Compiler: %BUILD_DIR%\chtlc.exe

if %PACK_MODULES%==1 if exist "%MODULE_OUTPUT_DIR%" (
    echo Module directory: %MODULE_OUTPUT_DIR%
)

echo.
echo Debug tips:
echo   1. Use Visual Studio debugger
echo   2. Use VSCode with debug configuration
echo   3. Use gdb (MinGW): gdb %BUILD_DIR%\chtlc.exe

exit /b 0

:show_help
echo CHTL Debug Build Script
echo.
echo Usage: build_debug.bat [options]
echo.
echo Options:
echo   --help, -h          Show this help message
echo   --jobs N, -j N      Number of parallel jobs [default: %NUMBER_OF_PROCESSORS%]
echo   --clean             Clean before building
echo   --no-pack           Do not auto pack modules
echo   --verbose           Show verbose output
echo.
echo Examples:
echo   build_debug.bat            # Debug build with auto pack
echo   build_debug.bat --clean    # Clean and rebuild
echo   build_debug.bat --no-pack  # Build only
echo.
exit /b 0