@echo off
rem CHTL Module Packing Script for Windows

setlocal enabledelayedexpansion

rem Set script directory and root directory
set SCRIPT_DIR=%~dp0
set ROOT_DIR=%SCRIPT_DIR%..\..\..
cd /d "%ROOT_DIR%"

rem Default values
set OUTPUT_DIR=output
set PACK_TYPE=auto
set PACK_ALL=0
set VERBOSE=0
set MODULE_COUNT=0
set SUCCESS_COUNT=0
set FAILED_COUNT=0

rem Parse arguments
:parse_args
if "%1"=="" goto :args_done
if /i "%1"=="--help" goto :show_help
if /i "%1"=="-h" goto :show_help
if /i "%1"=="--output" (
    set OUTPUT_DIR=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="-o" (
    set OUTPUT_DIR=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="--type" (
    set PACK_TYPE=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="-t" (
    set PACK_TYPE=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="--all" (
    set PACK_ALL=1
    shift
    goto :parse_args
)
if /i "%1"=="--verbose" (
    set VERBOSE=1
    shift
    goto :parse_args
)
if /i "%1"=="-v" (
    set VERBOSE=1
    shift
    goto :parse_args
)
rem Add module to list
set /a MODULE_COUNT+=1
set MODULE_%MODULE_COUNT%=%1
shift
goto :parse_args

:args_done

rem Check if we have modules to pack
if %PACK_ALL%==0 if %MODULE_COUNT%==0 (
    echo [ERROR] No modules specified. Use --all or specify module paths.
    goto :show_help
)

rem Create output directory
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

echo ========================================
echo CHTL Module Packing
echo ========================================
echo Output Directory: %OUTPUT_DIR%
echo Pack Type: %PACK_TYPE%
echo ========================================
echo.

rem Check dependencies
where cmake >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake not found. Required for CJMOD compilation.
    exit /b 1
)

rem Pack all modules if requested
if %PACK_ALL%==1 (
    echo Packing all modules...
    for /d %%M in (src\module\*) do (
        if exist "%%M" (
            call :pack_module "%%M"
        )
    )
) else (
    rem Pack specified modules
    for /l %%i in (1,1,%MODULE_COUNT%) do (
        call :pack_module "!MODULE_%%i!"
    )
)

rem Show summary
echo.
echo ========================================
echo Packing Summary
echo ========================================
echo Total modules: %MODULE_COUNT%
echo Success: %SUCCESS_COUNT%
echo Failed: %FAILED_COUNT%
echo ========================================

if %FAILED_COUNT% gtr 0 exit /b 1
exit /b 0

:pack_module
set MODULE_PATH=%~1
set MODULE_NAME=%~nx1

echo Processing module: %MODULE_NAME%

rem Detect module type
set MODULE_TYPE=unknown
if exist "%MODULE_PATH%\CMOD" if exist "%MODULE_PATH%\CJMOD" set MODULE_TYPE=mixed
if exist "%MODULE_PATH%\CMOD" if not exist "%MODULE_PATH%\CJMOD" set MODULE_TYPE=cmod
if not exist "%MODULE_PATH%\CMOD" if exist "%MODULE_PATH%\CJMOD" set MODULE_TYPE=cjmod
if exist "%MODULE_PATH%\src" if exist "%MODULE_PATH%\info" (
    rem Check if it's a direct module
    set HAS_CPP=0
    set HAS_CHTL=0
    for %%F in ("%MODULE_PATH%\src\*.cpp" "%MODULE_PATH%\src\*.cc" "%MODULE_PATH%\src\*.cxx") do set HAS_CPP=1
    for %%F in ("%MODULE_PATH%\src\*.chtl") do set HAS_CHTL=1
    
    if !HAS_CPP!==1 set MODULE_TYPE=cjmod
    if !HAS_CHTL!==1 set MODULE_TYPE=cmod
)

if "%MODULE_TYPE%"=="unknown" (
    echo [ERROR] Unknown module type for %MODULE_NAME%
    set /a FAILED_COUNT+=1
    goto :eof
)

echo Module type: %MODULE_TYPE%

rem Pack based on type
if "%PACK_TYPE%"=="auto" (
    if "%MODULE_TYPE%"=="mixed" (
        call :pack_cmod "%MODULE_PATH%"
        call :pack_cjmod "%MODULE_PATH%"
    ) else if "%MODULE_TYPE%"=="cmod" (
        call :pack_cmod "%MODULE_PATH%"
    ) else if "%MODULE_TYPE%"=="cjmod" (
        call :pack_cjmod "%MODULE_PATH%"
    )
) else if "%PACK_TYPE%"=="cmod" (
    call :pack_cmod "%MODULE_PATH%"
) else if "%PACK_TYPE%"=="cjmod" (
    call :pack_cjmod "%MODULE_PATH%"
)

goto :eof

:pack_cmod
set CMOD_PATH=%~1
set CMOD_NAME=%~nx1

echo Packing CMOD: %CMOD_NAME%

rem Find actual CMOD directory
set ACTUAL_CMOD_PATH=
if exist "%CMOD_PATH%\CMOD\%CMOD_NAME%" (
    set ACTUAL_CMOD_PATH=%CMOD_PATH%\CMOD\%CMOD_NAME%
) else if exist "%CMOD_PATH%\src" if exist "%CMOD_PATH%\info" (
    set ACTUAL_CMOD_PATH=%CMOD_PATH%
)

if "%ACTUAL_CMOD_PATH%"=="" (
    echo [ERROR] No valid CMOD structure found
    set /a FAILED_COUNT+=1
    goto :eof
)

rem Create temporary directory
set TEMP_DIR=%TEMP%\cmod_%RANDOM%
mkdir "%TEMP_DIR%"
mkdir "%TEMP_DIR%\%CMOD_NAME%"

rem Copy module files
xcopy /E /I /Q "%ACTUAL_CMOD_PATH%\*" "%TEMP_DIR%\%CMOD_NAME%" >nul

rem Create metadata
echo { > "%TEMP_DIR%\%CMOD_NAME%\.cmod_metadata"
echo   "module_name": "%CMOD_NAME%", >> "%TEMP_DIR%\%CMOD_NAME%\.cmod_metadata"
echo   "package_type": "CMOD", >> "%TEMP_DIR%\%CMOD_NAME%\.cmod_metadata"
echo   "created_at": "%DATE% %TIME%", >> "%TEMP_DIR%\%CMOD_NAME%\.cmod_metadata"
echo   "platform": "all", >> "%TEMP_DIR%\%CMOD_NAME%\.cmod_metadata"
echo   "chtl_version": "1.0.0" >> "%TEMP_DIR%\%CMOD_NAME%\.cmod_metadata"
echo } >> "%TEMP_DIR%\%CMOD_NAME%\.cmod_metadata"

rem Create archive
set OUTPUT_FILE=%OUTPUT_DIR%\%CMOD_NAME%.cmod
if exist "%OUTPUT_FILE%" del "%OUTPUT_FILE%"

rem Use tar if available (Windows 10+)
where tar >nul 2>&1
if not errorlevel 1 (
    cd "%TEMP_DIR%"
    tar -czf "%OUTPUT_FILE%" "%CMOD_NAME%"
    cd "%ROOT_DIR%"
) else (
    rem Fallback to PowerShell compression
    powershell -Command "Compress-Archive -Path '%TEMP_DIR%\%CMOD_NAME%' -DestinationPath '%OUTPUT_FILE%.zip' -Force"
    if exist "%OUTPUT_FILE%.zip" move "%OUTPUT_FILE%.zip" "%OUTPUT_FILE%" >nul
)

rem Cleanup
rmdir /S /Q "%TEMP_DIR%"

if exist "%OUTPUT_FILE%" (
    echo [SUCCESS] Created %OUTPUT_FILE%
    set /a SUCCESS_COUNT+=1
) else (
    echo [ERROR] Failed to create %OUTPUT_FILE%
    set /a FAILED_COUNT+=1
)

goto :eof

:pack_cjmod
set CJMOD_PATH=%~1
set CJMOD_NAME=%~nx1

echo Packing CJMOD: %CJMOD_NAME%

rem Find actual CJMOD directory
set ACTUAL_CJMOD_PATH=
if exist "%CJMOD_PATH%\CJMOD\%CJMOD_NAME%" (
    set ACTUAL_CJMOD_PATH=%CJMOD_PATH%\CJMOD\%CJMOD_NAME%
) else if exist "%CJMOD_PATH%\src" (
    rem Check for C++ files
    set HAS_CPP=0
    for %%F in ("%CJMOD_PATH%\src\*.cpp" "%CJMOD_PATH%\src\*.cc" "%CJMOD_PATH%\src\*.cxx") do set HAS_CPP=1
    if !HAS_CPP!==1 set ACTUAL_CJMOD_PATH=%CJMOD_PATH%
)

if "%ACTUAL_CJMOD_PATH%"=="" (
    echo [ERROR] No valid CJMOD structure found
    set /a FAILED_COUNT+=1
    goto :eof
)

rem Create build directory
set BUILD_DIR=%TEMP%\cjmod_build_%RANDOM%
mkdir "%BUILD_DIR%"

rem Create CMakeLists.txt
echo cmake_minimum_required(VERSION 3.16) > "%BUILD_DIR%\CMakeLists.txt"
echo project(%CJMOD_NAME% LANGUAGES CXX) >> "%BUILD_DIR%\CMakeLists.txt"
echo. >> "%BUILD_DIR%\CMakeLists.txt"
echo set(CMAKE_CXX_STANDARD 17) >> "%BUILD_DIR%\CMakeLists.txt"
echo set(CMAKE_CXX_STANDARD_REQUIRED ON) >> "%BUILD_DIR%\CMakeLists.txt"
echo set(CMAKE_POSITION_INDEPENDENT_CODE ON) >> "%BUILD_DIR%\CMakeLists.txt"
echo. >> "%BUILD_DIR%\CMakeLists.txt"
echo file(GLOB_RECURSE SOURCES "%ACTUAL_CJMOD_PATH%/src/*.cpp") >> "%BUILD_DIR%\CMakeLists.txt"
echo. >> "%BUILD_DIR%\CMakeLists.txt"
echo add_library(%CJMOD_NAME% SHARED ${SOURCES}) >> "%BUILD_DIR%\CMakeLists.txt"
echo. >> "%BUILD_DIR%\CMakeLists.txt"
echo target_include_directories(%CJMOD_NAME% PRIVATE >> "%BUILD_DIR%\CMakeLists.txt"
echo     "%ROOT_DIR%/src" >> "%BUILD_DIR%\CMakeLists.txt"
echo     "%ACTUAL_CJMOD_PATH%/src" >> "%BUILD_DIR%\CMakeLists.txt"
echo ) >> "%BUILD_DIR%\CMakeLists.txt"
echo. >> "%BUILD_DIR%\CMakeLists.txt"
echo set_target_properties(%CJMOD_NAME% PROPERTIES >> "%BUILD_DIR%\CMakeLists.txt"
echo     PREFIX "" >> "%BUILD_DIR%\CMakeLists.txt"
echo     OUTPUT_NAME "%CJMOD_NAME%" >> "%BUILD_DIR%\CMakeLists.txt"
echo ) >> "%BUILD_DIR%\CMakeLists.txt"
echo. >> "%BUILD_DIR%\CMakeLists.txt"
echo if(WIN32) >> "%BUILD_DIR%\CMakeLists.txt"
echo     target_compile_definitions(%CJMOD_NAME% PRIVATE CJMOD_EXPORTS) >> "%BUILD_DIR%\CMakeLists.txt"
echo endif() >> "%BUILD_DIR%\CMakeLists.txt"

rem Configure and build
cd "%BUILD_DIR%"
cmake . -DCMAKE_BUILD_TYPE=Release >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake configuration failed
    cd "%ROOT_DIR%"
    rmdir /S /Q "%BUILD_DIR%"
    set /a FAILED_COUNT+=1
    goto :eof
)

cmake --build . --config Release >nul 2>&1
if errorlevel 1 (
    echo [ERROR] Build failed
    cd "%ROOT_DIR%"
    rmdir /S /Q "%BUILD_DIR%"
    set /a FAILED_COUNT+=1
    goto :eof
)

cd "%ROOT_DIR%"

rem Find the built library
set LIB_FILE=
if exist "%BUILD_DIR%\Release\%CJMOD_NAME%.dll" set LIB_FILE=%BUILD_DIR%\Release\%CJMOD_NAME%.dll
if exist "%BUILD_DIR%\%CJMOD_NAME%.dll" set LIB_FILE=%BUILD_DIR%\%CJMOD_NAME%.dll

if "%LIB_FILE%"=="" (
    echo [ERROR] Built library not found
    rmdir /S /Q "%BUILD_DIR%"
    set /a FAILED_COUNT+=1
    goto :eof
)

rem Create temporary directory for packaging
set TEMP_DIR=%TEMP%\cjmod_%RANDOM%
mkdir "%TEMP_DIR%"
mkdir "%TEMP_DIR%\%CJMOD_NAME%"
mkdir "%TEMP_DIR%\%CJMOD_NAME%\lib"

rem Copy files
copy "%LIB_FILE%" "%TEMP_DIR%\%CJMOD_NAME%\lib\" >nul
if exist "%ACTUAL_CJMOD_PATH%\src" xcopy /E /I /Q "%ACTUAL_CJMOD_PATH%\src" "%TEMP_DIR%\%CJMOD_NAME%\src" >nul
if exist "%ACTUAL_CJMOD_PATH%\info" xcopy /E /I /Q "%ACTUAL_CJMOD_PATH%\info" "%TEMP_DIR%\%CJMOD_NAME%\info" >nul

rem Create metadata
echo { > "%TEMP_DIR%\%CJMOD_NAME%\.cjmod_metadata"
echo   "module_name": "%CJMOD_NAME%", >> "%TEMP_DIR%\%CJMOD_NAME%\.cjmod_metadata"
echo   "package_type": "CJMOD", >> "%TEMP_DIR%\%CJMOD_NAME%\.cjmod_metadata"
echo   "created_at": "%DATE% %TIME%", >> "%TEMP_DIR%\%CJMOD_NAME%\.cjmod_metadata"
echo   "platform": "windows", >> "%TEMP_DIR%\%CJMOD_NAME%\.cjmod_metadata"
echo   "architecture": "%PROCESSOR_ARCHITECTURE%", >> "%TEMP_DIR%\%CJMOD_NAME%\.cjmod_metadata"
echo   "chtl_version": "1.0.0" >> "%TEMP_DIR%\%CJMOD_NAME%\.cjmod_metadata"
echo } >> "%TEMP_DIR%\%CJMOD_NAME%\.cjmod_metadata"

rem Create archive
set OUTPUT_FILE=%OUTPUT_DIR%\%CJMOD_NAME%.cjmod
if exist "%OUTPUT_FILE%" del "%OUTPUT_FILE%"

rem Use tar if available
where tar >nul 2>&1
if not errorlevel 1 (
    cd "%TEMP_DIR%"
    tar -czf "%OUTPUT_FILE%" "%CJMOD_NAME%"
    cd "%ROOT_DIR%"
) else (
    rem Fallback to PowerShell
    powershell -Command "Compress-Archive -Path '%TEMP_DIR%\%CJMOD_NAME%' -DestinationPath '%OUTPUT_FILE%.zip' -Force"
    if exist "%OUTPUT_FILE%.zip" move "%OUTPUT_FILE%.zip" "%OUTPUT_FILE%" >nul
)

rem Cleanup
rmdir /S /Q "%TEMP_DIR%"
rmdir /S /Q "%BUILD_DIR%"

if exist "%OUTPUT_FILE%" (
    echo [SUCCESS] Created %OUTPUT_FILE%
    set /a SUCCESS_COUNT+=1
) else (
    echo [ERROR] Failed to create %OUTPUT_FILE%
    set /a FAILED_COUNT+=1
)

goto :eof

:show_help
echo CHTL Module Packing Script for Windows
echo.
echo Usage: pack.bat [modules...] [options]
echo.
echo Options:
echo   --help, -h          Show this help message
echo   --output DIR, -o    Output directory [default: output]
echo   --type TYPE, -t     Pack type (cmod, cjmod, auto) [default: auto]
echo   --all               Pack all modules in the module directory
echo   --verbose, -v       Enable verbose output
echo.
echo Examples:
echo   pack.bat --all
echo   pack.bat module\Chtholly
echo   pack.bat module\MyModule --type cmod
echo   pack.bat --all -o dist
echo.
exit /b 0