@echo off
rem CHTL Build Script for Windows
rem Supports: Visual Studio, MinGW

setlocal enabledelayedexpansion

rem Set script directory and root directory
set SCRIPT_DIR=%~dp0
set ROOT_DIR=%SCRIPT_DIR%..\..\..
cd /d "%ROOT_DIR%"

rem Default values
set BUILD_TYPE=Release
set BUILD_DIR=build
set GENERATOR=
set CLEAN=0
set TEST=0
set INSTALL=0
set NO_PARSERS=0
set JOBS=%NUMBER_OF_PROCESSORS%
set CMAKE_PREFIX_PATH=
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
if /i "%1"=="--generator" (
    set GENERATOR=%2
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
if /i "%1"=="--jobs" (
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
if /i "%1"=="--test" (
    set TEST=1
    shift
    goto :parse_args
)
if /i "%1"=="--install" (
    set INSTALL=1
    shift
    goto :parse_args
)
if /i "%1"=="--no-parsers" (
    set NO_PARSERS=1
    shift
    goto :parse_args
)
if /i "%1"=="--prefix" (
    set CMAKE_PREFIX_PATH=%2
    shift
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
echo CHTL Build Configuration
echo ========================================
echo Build Type: %BUILD_TYPE%
echo Build Directory: %BUILD_DIR%
echo Jobs: %JOBS%
echo ========================================
echo.

rem Check dependencies
echo Checking dependencies...

rem Check CMake
where cmake >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake not found. Please install CMake.
    exit /b 1
)

rem Check for C++ compiler
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

rem Generate parsers if needed
if %NO_PARSERS%==0 (
    if exist "tools\antlr-4.13.1-complete.jar" (
        echo Generating parsers...
        
        if not exist "generated" mkdir "generated"
        if not exist "generated\css" mkdir "generated\css"
        if not exist "generated\js" mkdir "generated\js"
        
        rem Generate CSS parser
        if exist "grammars\CSS3.g4" (
            echo Generating CSS parser...
            java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\css grammars\CSS3.g4
            if errorlevel 1 (
                echo [WARNING] CSS parser generation failed
            )
        )
        
        rem Generate JS parser
        if exist "grammars\JavaScriptLexer.g4" (
            echo Generating JavaScript parser...
            java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\js grammars\JavaScriptLexer.g4
            if errorlevel 1 (
                echo [WARNING] JS lexer generation failed
            )
        )
        
        if exist "grammars\JavaScriptParser.g4" (
            java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\js grammars\JavaScriptParser.g4
            if errorlevel 1 (
                echo [WARNING] JS parser generation failed
            )
        )
    ) else (
        echo [WARNING] ANTLR jar not found, skipping parser generation
    )
)

rem Configure CMake
echo Configuring CMake...
cd "%BUILD_DIR%"

set CMAKE_ARGS=-DCMAKE_BUILD_TYPE=%BUILD_TYPE%
if not "%GENERATOR%"=="" set CMAKE_ARGS=%CMAKE_ARGS% -G "%GENERATOR%"
if not "%CMAKE_PREFIX_PATH%"=="" set CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_INSTALL_PREFIX=%CMAKE_PREFIX_PATH%

cmake %CMAKE_ARGS% ..
if errorlevel 1 (
    echo [ERROR] CMake configuration failed
    exit /b 1
)

rem Build
echo Building CHTL...
cmake --build . --config %BUILD_TYPE% -j %JOBS%
if errorlevel 1 (
    echo [ERROR] Build failed
    exit /b 1
)

echo [SUCCESS] Build completed

rem Run tests if requested
if %TEST%==1 (
    echo Running tests...
    ctest -C %BUILD_TYPE% --output-on-failure
    if errorlevel 1 (
        echo [ERROR] Some tests failed
        exit /b 1
    )
    echo [SUCCESS] All tests passed
)

rem Install if requested
if %INSTALL%==1 (
    echo Installing CHTL...
    cmake --install . --config %BUILD_TYPE%
    if errorlevel 1 (
        echo [ERROR] Installation failed
        exit /b 1
    )
    echo [SUCCESS] Installation completed
)

cd ..
echo.
echo ========================================
echo Build completed successfully!
echo ========================================

exit /b 0

:show_help
echo CHTL Windows Build Script
echo.
echo Usage: build.bat [options]
echo.
echo Options:
echo   --help, -h          Show this help message
echo   --type TYPE         Build type (Debug, Release, RelWithDebInfo) [default: Release]
echo   --generator GEN     CMake generator (e.g., "Visual Studio 17 2022", "MinGW Makefiles")
echo   --jobs N, -j N      Number of parallel build jobs [default: %NUMBER_OF_PROCESSORS%]
echo   --clean             Clean build directory before building
echo   --test              Run tests after building
echo   --install           Install after building
echo   --no-parsers        Skip ANTLR parser generation
echo   --prefix PATH       Installation prefix
echo   --verbose           Enable verbose output
echo.
echo Examples:
echo   build.bat --type Debug
echo   build.bat --clean --type Release --test
echo   build.bat --generator "MinGW Makefiles" --jobs 4
echo.
exit /b 0