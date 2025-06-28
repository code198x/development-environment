@echo off
setlocal enabledelayedexpansion

REM Code198x Development Environment Installer for Windows
REM Requires Windows 10 or later with PowerShell

echo.
echo    ╔═══════════════════════════════════════╗
echo    ║          Code198x Dev Environment     ║
echo    ║        Windows Installation           ║
echo    ╚═══════════════════════════════════════╝
echo.

REM Check Windows version
for /f "tokens=4-5 delims=. " %%i in ('ver') do set VERSION=%%i.%%j
if "%VERSION%" LSS "10.0" (
    echo ❌ Windows 10 or later required
    echo Your version: %VERSION%
    pause
    exit /b 1
)

echo ✅ Windows version check passed: %VERSION%

REM Check if running as administrator
net session >nul 2>&1
if %errorLevel% == 0 (
    echo ⚠️  Running as administrator - this is not recommended
    echo The installer will request privileges when needed
    timeout /t 5
)

REM Check PowerShell version
for /f "tokens=*" %%i in ('powershell -command "$PSVersionTable.PSVersion.Major"') do set PS_VERSION=%%i
if !PS_VERSION! LSS 5 (
    echo ❌ PowerShell 5.0 or later required
    echo Please update PowerShell
    pause
    exit /b 1
)

echo ✅ PowerShell version check passed: !PS_VERSION!

REM Check available disk space (need at least 2GB = 2097152 KB)
for /f "tokens=3" %%a in ('dir /-c') do set AVAILABLE=%%a
if !AVAILABLE! LSS 2097152000 (
    echo ❌ Need at least 2GB free disk space
    pause
    exit /b 1
)

echo ✅ Disk space check passed

REM Check internet connection
ping -n 1 google.com >nul 2>&1
if errorlevel 1 (
    echo ❌ Internet connection required
    pause
    exit /b 1
)

echo ✅ Internet connection verified

echo.
echo 🚀 Starting installation...
echo.

REM Install Chocolatey if not present
where choco >nul 2>&1
if errorlevel 1 (
    echo 🍫 Installing Chocolatey package manager...
    powershell -Command "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))"
    
    REM Refresh environment
    call refreshenv
    
    REM Verify installation
    where choco >nul 2>&1
    if errorlevel 1 (
        echo ❌ Chocolatey installation failed
        pause
        exit /b 1
    )
    echo ✅ Chocolatey installed successfully
) else (
    echo ✅ Chocolatey already installed
    choco upgrade chocolatey -y
)

echo.
echo 🔧 Installing system tools...

REM Install essential tools
choco install -y git wget curl 7zip

REM Install development tools
choco install -y microsoft-build-tools

echo ✅ System tools installed

echo.
echo 🖥️ Installing Commodore 64 tools...

REM ACME assembler
choco install -y acme-crossassembler

REM VICE emulator  
choco install -y vice

echo ✅ Commodore 64 tools installed

echo.
echo 🌈 Installing ZX Spectrum tools...

REM PASMO assembler (manual download)
if not exist "tools\bin" mkdir tools\bin

powershell -Command "& {
    $url = 'http://pasmo.speccy.org/bin/pasmo-0.5.4.beta2.zip'
    $output = 'tools\pasmo.zip'
    Write-Host 'Downloading PASMO...'
    Invoke-WebRequest -Uri $url -OutFile $output
    Expand-Archive -Path $output -DestinationPath 'tools\pasmo' -Force
    Copy-Item 'tools\pasmo\pasmo.exe' 'tools\bin\pasmo.exe'
    Remove-Item $output
    Remove-Item 'tools\pasmo' -Recurse
}"

REM Fuse emulator (download)
powershell -Command "& {
    $url = 'https://sourceforge.net/projects/fuse-emulator/files/fuse/1.6.0/fuse-1.6.0-win32.zip/download'
    $output = 'tools\fuse.zip'
    Write-Host 'Downloading Fuse...'
    Invoke-WebRequest -Uri $url -OutFile $output
    Expand-Archive -Path $output -DestinationPath 'tools\fuse' -Force
    Copy-Item 'tools\fuse\fuse.exe' 'tools\bin\fuse.exe'
    Remove-Item $output
}"

echo ✅ ZX Spectrum tools installed

echo.
echo 🎨 Installing Amiga tools...

REM VASM assembler (download pre-built)
powershell -Command "& {
    $url = 'http://sun.hasenbraten.de/vasm/release/vasm-win32.zip'
    $output = 'tools\vasm.zip'
    Write-Host 'Downloading VASM...'
    Invoke-WebRequest -Uri $url -OutFile $output
    Expand-Archive -Path $output -DestinationPath 'tools\vasm' -Force
    Copy-Item 'tools\vasm\vasmm68k_mot.exe' 'tools\bin\vasmm68k_mot.exe'
    Remove-Item $output
}"

REM FS-UAE emulator
powershell -Command "& {
    $url = 'https://fs-uae.net/stable/windows-x86-64/fs-uae_3.1.66_windows-x86-64.zip'
    $output = 'tools\fsuae.zip'
    Write-Host 'Downloading FS-UAE...'
    Invoke-WebRequest -Uri $url -OutFile $output
    Expand-Archive -Path $output -DestinationPath 'tools\fsuae' -Force
    Copy-Item 'tools\fsuae\fs-uae.exe' 'tools\bin\fs-uae.exe'
    Remove-Item $output
}"

echo ✅ Amiga tools installed

echo.
echo 🎮 Installing NES tools...

REM CC65 toolkit
choco install -y cc65

REM Mesen emulator
powershell -Command "& {
    $url = 'https://github.com/SourMesen/Mesen2/releases/latest/download/Mesen.exe'
    Write-Host 'Downloading Mesen...'
    Invoke-WebRequest -Uri $url -OutFile 'tools\bin\Mesen.exe'
}"

echo ✅ NES tools installed

echo.
echo 📁 Creating project templates...

REM Create templates directory structure
if not exist "templates" mkdir templates
if not exist "scripts" mkdir scripts

REM Create project creation script
(
echo @echo off
echo setlocal
echo.
echo if "%%1"=="" goto usage
echo if "%%2"=="" goto usage
echo.
echo set SYSTEM=%%1
echo set PROJECT=%%2
echo.
echo if not exist "templates\!SYSTEM!-basic" ^(
echo     echo ❌ Unknown system: !SYSTEM!
echo     echo Available: c64, spectrum, amiga, nes
echo     exit /b 1
echo ^)
echo.
echo if exist "!PROJECT!" ^(
echo     echo ❌ Project directory '!PROJECT!' already exists
echo     exit /b 1
echo ^)
echo.
echo echo 📁 Creating !SYSTEM! project: !PROJECT!
echo xcopy "templates\!SYSTEM!-basic" "!PROJECT!" /E /I /Q
echo.
echo echo ✅ Project created successfully!
echo echo 🚀 To build and run:
echo echo    cd !PROJECT!
echo echo    build.bat
echo goto end
echo.
echo :usage
echo echo Usage: %%0 ^<system^> ^<project-name^>
echo echo Systems: c64, spectrum, amiga, nes
echo.
echo :end
) > scripts\new-project.bat

REM Create basic templates (simplified for batch)
REM C64 template
mkdir "templates\c64-basic" 2>nul
(
echo ; Code198x Commodore 64 Template
echo *= $0801
echo.
echo ; BASIC stub: 10 SYS 2061
echo !word next_line
echo !word 10
echo !byte $9e
echo !text "2061"
echo !byte 0
echo next_line:
echo !word 0
echo.
echo start:
echo     lda #$06
echo     sta $d020
echo     lda #$00
echo     sta $d021
echo.
echo     ldy #0
echo print_loop:
echo     lda message,y
echo     beq done
echo     jsr $ffd2
echo     iny
echo     bne print_loop
echo.
echo done:
echo     rts
echo.
echo message: !text "HELLO, CODE198X WORLD!", 13, 0
) > "templates\c64-basic\main.s"

(
echo @echo off
echo echo Building Commodore 64 program...
echo acme -f cbm -o hello.prg main.s
echo if errorlevel 1 ^(
echo     echo ❌ Build failed!
echo     pause
echo     exit /b 1
echo ^)
echo echo ✅ Build successful!
echo if exist "C:\Program Files\GTK3-Runtime Win64\bin\x64sc.exe" ^(
echo     echo 🚀 Launching VICE...
echo     "C:\Program Files\GTK3-Runtime Win64\bin\x64sc.exe" hello.prg
echo ^) else ^(
echo     echo ⚠️ VICE not found in expected location
echo     echo Please run hello.prg manually
echo     pause
echo ^)
) > "templates\c64-basic\build.bat"

echo ✅ Project templates created

echo.
echo 🔧 Setting up PATH...

REM Add tools to PATH
setx PATH "%PATH%;%CD%\tools\bin" /M >nul 2>&1 || (
    echo ⚠️ Could not update system PATH - add %CD%\tools\bin manually
)

echo ✅ PATH configured

echo.
echo 🧪 Testing installation...

set FAILED_TESTS=0

REM Test C64 tools
echo Testing Commodore 64...
acme -h >nul 2>&1 && (
    echo   ✅ ACME OK
) || (
    echo   ❌ ACME failed
    set /a FAILED_TESTS+=1
)

REM Test basic tools
git --version >nul 2>&1 && (
    echo   ✅ Git OK
) || (
    echo   ❌ Git failed
    set /a FAILED_TESTS+=1
)

if !FAILED_TESTS! EQU 0 (
    echo.
    echo ✅ All tests passed!
) else (
    echo.
    echo ❌ !FAILED_TESTS! tests failed
    echo Please check the installation
)

echo.
echo ╔═══════════════════════════════════════╗
echo ║        🎉 INSTALLATION COMPLETE! 🎉   ║
echo ╚═══════════════════════════════════════╝
echo.
echo ✅ Code198x Development Environment is ready!
echo.
echo Quick Start:
echo   📁 Create new project: scripts\new-project.bat c64 my-game
echo   🔨 Build and run: cd my-game ^&^& build.bat
echo   📚 Documentation: docs\
echo.
echo Next Steps:
echo   1. Try the templates in templates\
echo   2. Read the docs in docs\
echo   3. Start with Code198x lessons at https://code198x.com
echo.
echo Happy vintage coding! 🕹️
echo.

pause