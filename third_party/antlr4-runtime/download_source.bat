@echo off
rem Download ANTLR4 Runtime Source for Windows

setlocal enabledelayedexpansion

set ANTLR4_VERSION=4.13.1
set SCRIPT_DIR=%~dp0
cd /d "%SCRIPT_DIR%"

echo ========================================
echo Downloading ANTLR4 Runtime Source
echo ========================================
echo.

rem Download source
echo [INFO] Downloading ANTLR4 runtime v%ANTLR4_VERSION%...

set DOWNLOAD_URL=https://github.com/antlr/antlr4/archive/refs/tags/%ANTLR4_VERSION%.zip
set ARCHIVE_NAME=antlr4-%ANTLR4_VERSION%.zip

powershell -Command "Invoke-WebRequest -Uri '%DOWNLOAD_URL%' -OutFile '%ARCHIVE_NAME%'"

if not exist "%ARCHIVE_NAME%" (
    echo [ERROR] Failed to download ANTLR4 source
    exit /b 1
)

rem Extract
echo [INFO] Extracting archive...
powershell -Command "Expand-Archive -Path '%ARCHIVE_NAME%' -DestinationPath '.' -Force"

rem Copy runtime source
echo [INFO] Copying runtime source...
if exist "src" rmdir /s /q "src"
xcopy /E /I /Q "antlr4-%ANTLR4_VERSION%\runtime\Cpp\runtime\src" "src"

rem Clean up
rmdir /s /q "antlr4-%ANTLR4_VERSION%"
del "%ARCHIVE_NAME%"

echo.
echo [SUCCESS] ANTLR4 runtime source downloaded successfully!
echo [INFO] Source location: src\
echo.
echo [INFO] You can now build CHTL with the ANTLR4 runtime.
echo.

exit /b 0