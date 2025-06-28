# Installation Guide

This guide will help you set up the Code198x development environment on your system.

## Quick Installation

### Option 1: Automated Installer (Recommended)

The easiest way to get started is with our automated installer:

```bash
# Clone the repository
git clone https://github.com/code198x/development-environment.git
cd development-environment

# Run the installer
./install.sh          # macOS/Linux
# or
install.bat           # Windows
```

The installer will:
- ✅ Detect your operating system
- ✅ Install package managers (Homebrew, etc.)
- ✅ Install all required assemblers and emulators
- ✅ Set up project templates
- ✅ Configure VS Code integration
- ✅ Test the installation

### Option 2: Docker (Isolated Environment)

If you prefer containerized development or have installation issues:

```bash
# Clone the repository
git clone https://github.com/code198x/development-environment.git
cd development-environment

# Build and run all systems
docker compose up

# Or run individual systems
docker compose up c64      # Commodore 64 only
docker compose up spectrum # ZX Spectrum only
docker compose up amiga    # Amiga only
docker compose up nes      # NES only
```

### Option 3: Manual Installation

For advanced users who want full control over the installation.

## System Requirements

### Minimum Requirements
- **Operating System**: macOS 10.15+, Ubuntu 18.04+, Windows 10
- **RAM**: 4GB (8GB recommended for emulation)
- **Storage**: 2GB free space (5GB+ recommended)
- **CPU**: x64 processor (ARM64 supported on macOS)

### Recommended Setup
- **RAM**: 8GB+ for smooth emulator performance
- **Storage**: 10GB+ if you plan to collect ROM images
- **Display**: 1920×1080+ for comfortable emulator windows
- **Audio**: Working audio system for sound effects

## Supported Platforms

### 🍎 macOS
- **Supported versions**: macOS 10.15 (Catalina) and later
- **Architecture**: Intel x86_64 and Apple Silicon (M1/M2)
- **Package manager**: Homebrew (installed automatically)
- **Emulators**: Native Cocoa applications

**Installation notes:**
- Homebrew will be installed automatically if not present
- On Apple Silicon Macs, some emulators run under Rosetta 2
- Xcode Command Line Tools may be required (installed automatically)

### 🐧 Linux
- **Supported distributions**: Ubuntu 18.04+, Debian 10+, Fedora 32+, Arch Linux
- **Architecture**: x86_64 (ARM64 experimental)
- **Package managers**: apt, dnf, pacman supported
- **Display**: X11 required for emulators

**Installation notes:**
- Build tools (`build-essential`) required for some assemblers
- X11 forwarding supported for remote development
- Some emulators available as AppImages for compatibility

### 🪟 Windows
- **Supported versions**: Windows 10 version 1903+, Windows 11
- **Architecture**: x86_64
- **Package manager**: Chocolatey (installed automatically)
- **Subsystem**: WSL2 supported for Unix tools

**Installation notes:**
- PowerShell 5.1+ required
- Windows Subsystem for Linux (WSL2) recommended
- Some emulators require Visual C++ Redistributables

## Installation Process

### Step 1: Prerequisites Check

The installer automatically checks for:
- Sufficient disk space (2GB minimum)
- Administrator privileges (when needed)
- Internet connection for downloading packages
- Compatible operating system version

### Step 2: Package Manager Setup

**macOS:**
- Installs Homebrew if not present
- Updates Homebrew to latest version
- Configures PATH for Apple Silicon Macs

**Linux:**
- Updates package lists (`apt update`, `dnf check-update`)
- Installs build essentials
- Configures repositories if needed

**Windows:**
- Installs Chocolatey package manager
- Configures PowerShell execution policy
- Sets up Windows PATH

### Step 3: System Tools Installation

Common tools installed on all platforms:
- **Git** - Version control
- **wget/curl** - File downloading  
- **unzip** - Archive extraction
- **Build tools** - Compilers and make

### Step 4: Vintage System Tools

For each supported system, specific tools are installed:

#### Commodore 64
- **ACME** - Cross-assembler for 6502
- **VICE** - Complete C64 emulator suite

#### ZX Spectrum  
- **PASMO** - Z80 cross-assembler
- **Fuse** - Spectrum emulator

#### Commodore Amiga
- **VASM** - 68000 macro assembler (built from source)
- **FS-UAE** - Amiga emulator

#### Nintendo Entertainment System
- **CC65** - Complete 6502 development suite
- **Mesen** - Cycle-accurate NES emulator

### Step 5: Project Templates

Creates ready-to-use project templates:
- Basic "Hello World" programs for each system
- Build scripts with error checking
- Documentation and README files
- VS Code configuration

### Step 6: Development Integration

Sets up IDE integration:
- **VS Code** settings and extensions
- **Assembly syntax highlighting**
- **Build task automation**
- **Debugging configuration** (where supported)

### Step 7: Installation Testing

Validates the installation:
- Tests each assembler
- Verifies emulator installation
- Checks project template creation
- Validates build scripts

## Troubleshooting

### Common Issues

#### "Permission denied" errors
```bash
# Make installer executable
chmod +x install.sh

# Don't run as root/administrator
# The installer will request privileges when needed
```

#### Package manager not found
```bash
# macOS: Install Homebrew manually
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Linux: Update package lists
sudo apt update        # Ubuntu/Debian
sudo dnf check-update  # Fedora
```

#### Emulator won't start
```bash
# Check X11 forwarding (Linux/WSL)
export DISPLAY=:0

# Check audio system
pulseaudio --check -v

# Try headless mode
x64sc -default
```

#### Build tools missing
```bash
# Install build essentials
sudo apt install build-essential  # Ubuntu/Debian
xcode-select --install            # macOS
```

### Platform-Specific Issues

#### macOS
- **Gatekeeper warnings**: Right-click and "Open" for unsigned apps
- **Rosetta 2**: Some tools may require `arch -x86_64` prefix
- **SIP restrictions**: Some system directories protected

#### Linux
- **Graphics drivers**: OpenGL required for some emulators
- **Audio permissions**: User may need audio group membership
- **X11 issues**: `xhost +local:` may be needed

#### Windows
- **Antivirus interference**: Exclude development folder
- **PowerShell restrictions**: May need `Set-ExecutionPolicy RemoteSigned`
- **WSL integration**: Use WSL2 for better performance

### Getting Help

If you encounter issues:

1. **Check the logs**: Installation logs are saved to `install.log`
2. **Run diagnostics**: `./scripts/test-system.sh <system>`
3. **Check documentation**: See system-specific guides in `docs/`
4. **Community support**: 
   - [GitHub Issues](https://github.com/code198x/development-environment/issues)
   - [Discord Chat](https://discord.gg/code198x)
   - [Discussion Forum](https://github.com/code198x/development-environment/discussions)

## Manual Installation

If the automated installer doesn't work for your system, see:
- [Commodore 64 Manual Setup](c64-setup.md)
- [ZX Spectrum Manual Setup](spectrum-setup.md)
- [Amiga Manual Setup](amiga-setup.md)
- [NES Manual Setup](nes-setup.md)

## Next Steps

After successful installation:

1. **Test the environment**: 
   ```bash
   ./scripts/new-project.sh c64 test-project
   cd test-project && ./build.sh
   ```

2. **Try the templates**: Explore `templates/` directory

3. **Read the documentation**: Check out `docs/` for guides

4. **Start learning**: Visit [Code198x.com](https://code198x.com) for lessons

5. **Join the community**: Connect with other vintage computing enthusiasts

Happy vintage coding! 🕹️