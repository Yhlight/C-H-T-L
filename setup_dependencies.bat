@echo off
rem Setup CHTL dependencies for Windows

setlocal enabledelayedexpansion

rem Set directories
set SCRIPT_DIR=%~dp0
cd /d "%SCRIPT_DIR%"

echo ========================================
echo CHTL Dependencies Setup
echo ========================================
echo.

rem Check if ANTLR4 JAR exists
if exist "tools\antlr-4.13.1-complete.jar" (
    echo [INFO] ANTLR4 tool JAR is already present
) else (
    echo [INFO] Downloading ANTLR4 tool JAR...
    
    if not exist "tools" mkdir "tools"
    cd tools
    
    rem Download using PowerShell
    powershell -Command "Invoke-WebRequest -Uri 'https://www.antlr.org/download/antlr-4.13.1-complete.jar' -OutFile 'antlr-4.13.1-complete.jar'"
    
    if exist "antlr-4.13.1-complete.jar" (
        echo [SUCCESS] ANTLR4 tool JAR downloaded
    ) else (
        echo [ERROR] Failed to download ANTLR4 tool JAR
        exit /b 1
    )
    
    cd ..
)

rem Note about ANTLR4 runtime
echo.
echo [INFO] ANTLR4 Runtime for Windows:
echo.
echo For Windows builds, you have two options:
echo.
echo 1. Use prebuilt binaries (recommended):
echo    - Download from: https://github.com/antlr/antlr4/releases
echo    - Extract to: third_party\antlr4-runtime\
echo.
echo 2. Build from source:
echo    - Install Visual Studio 2019 or later
echo    - Install CMake
echo    - Run: third_party\antlr4-runtime\build_windows.bat
echo.

rem Generate parsers
if exist "generated\css" if exist "generated\js" (
    echo [INFO] Parsers already generated
) else (
    echo [INFO] Generating parsers...
    
    rem Check Java
    where java >nul 2>&1
    if errorlevel 1 (
        echo [WARNING] Java not found. Parser generation skipped.
        echo [WARNING] Please install Java to generate parsers.
    ) else (
        rem Generate CSS parser
        if exist "grammars\CSS3.g4" (
            echo [INFO] Generating CSS parser...
            if not exist "generated\css" mkdir "generated\css"
            java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\css grammars\CSS3.g4
        )
        
        rem Generate JS parser
        if exist "grammars\JavaScriptLexer.g4" if exist "grammars\JavaScriptParser.g4" (
            echo [INFO] Generating JavaScript parser...
            if not exist "generated\js" mkdir "generated\js"
            java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\js grammars\JavaScriptLexer.g4
            java -jar tools\antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o generated\js grammars\JavaScriptParser.g4
        )
        
        echo [SUCCESS] Parsers generated
    )
)

echo.
echo ========================================
echo Setup completed!
echo ========================================
echo.
echo [INFO] Next steps:
echo   1. Build CHTL: build.bat
echo   2. Run tests: build.bat --test
echo   3. Install: build.bat --install
echo.

exit /b 0