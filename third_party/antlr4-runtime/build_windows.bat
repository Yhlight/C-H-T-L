@echo off
rem Build ANTLR4 Runtime for Windows

setlocal enabledelayedexpansion

set ANTLR4_VERSION=4.13.1
set SCRIPT_DIR=%~dp0
cd /d "%SCRIPT_DIR%"

echo ========================================
echo Building ANTLR4 Runtime v%ANTLR4_VERSION%
echo ========================================
echo.

rem Check dependencies
where cmake >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake not found. Please install CMake.
    exit /b 1
)

where cl >nul 2>&1
if errorlevel 1 (
    echo [ERROR] MSVC compiler not found. Please install Visual Studio.
    exit /b 1
)

rem Download ANTLR4 source
echo [INFO] Downloading ANTLR4 runtime source...

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

rem Build
echo [INFO] Building ANTLR4 runtime...
if exist "build" rmdir /s /q "build"
mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A x64 ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DANTLR4_BUILD_SHARED=ON ^
    -DANTLR4_BUILD_STATIC=ON ^
    -DCMAKE_INSTALL_PREFIX=..

if errorlevel 1 (
    echo [ERROR] CMake configuration failed
    exit /b 1
)

cmake --build . --config Release

if errorlevel 1 (
    echo [ERROR] Build failed
    exit /b 1
)

rem Install
echo [INFO] Installing to local directories...
cmake --install . --config Release

rem Clean up
cd ..
rmdir /s /q "build"
rmdir /s /q "antlr4-%ANTLR4_VERSION%"
del "%ARCHIVE_NAME%"

echo.
echo [SUCCESS] ANTLR4 runtime v%ANTLR4_VERSION% built successfully!
echo [INFO] Headers: include\
echo [INFO] Libraries: lib\
echo.

exit /b 0