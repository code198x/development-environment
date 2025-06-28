# Code198x Development Environment

**One-click setup for vintage computer programming!**

This repository provides a complete development environment for programming vintage computers, supporting all systems covered in the Code198x curriculum:

- **Commodore 64** (6502 assembly with ACME)
- **ZX Spectrum** (Z80 assembly with PASMO)
- **Commodore Amiga** (68000 assembly with VASM)
- **Nintendo Entertainment System** (6502 assembly with CC65)

## Quick Start

### Option 1: Automated Installation (Recommended)

```bash
# Clone this repository
git clone https://github.com/code198x/development-environment.git
cd development-environment

# Run the installer
./install.sh          # macOS/Linux
# or
install.bat           # Windows
```

### Option 2: Docker (Isolated Environments)

```bash
# Build all system containers
docker compose build

# Or build individual systems
docker build -f docker/Dockerfile.c64 -t code198x/c64 .
docker build -f docker/Dockerfile.spectrum -t code198x/spectrum .
docker build -f docker/Dockerfile.amiga -t code198x/amiga .
docker build -f docker/Dockerfile.nes -t code198x/nes .

# Run development environment
docker compose up
```

### Option 3: Manual Installation

See system-specific guides in the `docs/` folder:
- [Commodore 64 Setup](docs/c64-setup.md)
- [ZX Spectrum Setup](docs/spectrum-setup.md) 
- [Commodore Amiga Setup](docs/amiga-setup.md)
- [NES Setup](docs/nes-setup.md)

## What's Included

### 🛠️ **Complete Toolchain**
- **Assemblers**: ACME, PASMO, VASM, CC65
- **Emulators**: VICE, Fuse, FS-UAE, Mesen
- **Build tools**: Cross-platform scripts
- **Debuggers**: Built-in emulator debugging

### 📁 **Project Templates**
Ready-to-use starter projects for each system:
```bash
# Create new project from template
./scripts/new-project.sh c64 my-game
./scripts/new-project.sh spectrum my-demo
./scripts/new-project.sh amiga my-intro
./scripts/new-project.sh nes my-shooter
```

### 🔧 **IDE Integration**
- **VS Code** configuration with syntax highlighting
- **Assembly language** support for all systems
- **Build tasks** integrated into editor
- **Debugging** support where available

### 📚 **Documentation**
- Setup guides for each system
- Build process documentation
- Troubleshooting guides
- Tool reference documentation

## System Requirements

### Minimum Requirements
- **OS**: macOS 10.15+, Ubuntu 18.04+, or Windows 10
- **RAM**: 4GB (8GB recommended)
- **Storage**: 2GB free space
- **CPU**: x64 processor

### Recommended Setup
- **RAM**: 8GB+ for smooth emulation
- **Storage**: 5GB+ for ROM collections
- **Display**: 1920×1080+ for emulator windows

## Quick Test

After installation, test each system:

```bash
# Test Commodore 64
cd templates/c64-basic
./build.sh
# Should launch VICE with "Hello World"

# Test ZX Spectrum  
cd templates/spectrum-basic
./build.sh
# Should launch Fuse with color demo

# Test Amiga
cd templates/amiga-basic
./build.sh
# Should launch FS-UAE with bitplane graphics

# Test NES
cd templates/nes-basic
./build.sh
# Should launch Mesen with sprite demo
```

## Supported Platforms

### 🍎 **macOS**
- Native tools via Homebrew
- Universal binary support (Intel & Apple Silicon)
- Integrated terminal build process

### 🐧 **Linux** 
- Package manager installation
- Debian/Ubuntu packages included
- AppImage emulators for compatibility

### 🪟 **Windows**
- Chocolatey package management
- WSL2 support for Unix tools
- Native Windows emulators

## Architecture

```
development-environment/
├── install.sh              # Automated installer
├── docker/                 # Container definitions
├── tools/                  # Pre-built binaries
├── templates/              # Project starters
├── scripts/                # Build automation
├── vscode/                 # Editor integration
├── docs/                   # Documentation
└── tests/                  # Validation scripts
```

## Build Process

Each system follows a consistent pattern:

1. **Write assembly code** using system-specific syntax
2. **Run build script** (`./build.sh` or `build.bat`)
3. **Automatic assembly** with error checking
4. **Launch emulator** with compiled program
5. **Debug and iterate** using integrated tools

Example workflow:
```bash
# Edit your code
code src/main.asm

# Build and run
./build.sh

# Emulator launches automatically
# Make changes, save, and build again
```

## Getting Help

### 📖 **Documentation**
- [Installation Guide](docs/installation.md)
- [Build System Guide](docs/build-system.md)
- [Troubleshooting](docs/troubleshooting.md)
- [FAQ](docs/faq.md)

### 💬 **Community**
- [GitHub Issues](https://github.com/code198x/development-environment/issues) - Bug reports and feature requests
- [Discussions](https://github.com/code198x/development-environment/discussions) - Community help
- [Discord](https://discord.gg/code198x) - Real-time chat

### 🎓 **Learning Resources**
- [Code198x Main Site](https://code198x.com) - Complete curriculum
- [Code Samples](https://github.com/code198x/code-samples) - Working examples
- [Assembly References](docs/assembly-reference.md) - Quick syntax guides

## Contributing

We welcome contributions! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Areas for Contribution
- **Additional platforms** (Atari, MSX, etc.)
- **Tool improvements** (better build scripts)
- **Documentation** (tutorials, guides)
- **Bug fixes** and optimizations

## License

This development environment is released under the MIT License. See [LICENSE](LICENSE) for details.

Individual tools and emulators retain their original licenses:
- **ACME**: Public domain
- **PASMO**: GPL
- **VASM**: Freeware
- **CC65**: GPL
- **VICE**: GPL
- **Fuse**: GPL
- **FS-UAE**: GPL
- **Mesen**: GPL

## Changelog

### v1.0.0 (Current)
- ✅ Initial release with 4 system support
- ✅ Docker containerization
- ✅ VS Code integration
- ✅ Cross-platform installer
- ✅ Project templates
- ✅ Automated build scripts

### Planned Features
- 🔄 Additional retro systems
- 🔄 Integrated debugger UI
- 🔄 ROM management tools
- 🔄 Performance profiling
- 🔄 Graphics editors integration

---

**Ready to code like it's 198x?** 🕹️

Get started with the [Installation Guide](docs/installation.md) or jump straight to a [Project Template](templates/)!