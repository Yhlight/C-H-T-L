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

rem Download ANTLR4 runtime source if not present
if exist "third_party\antlr4-runtime\src" (
    echo [INFO] ANTLR4 runtime source already present
) else (
    echo [INFO] Downloading ANTLR4 runtime source...
    cd third_party\antlr4-runtime
    call download_source.bat
    if errorlevel 1 (
        echo [ERROR] Failed to download ANTLR4 runtime source
        exit /b 1
    )
    cd ..\..
)

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