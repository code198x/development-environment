# Code198x Development Environment
## Docker-Based Cross-Development for 16 Retro Platforms

Complete development environment providing authentic cross-development tools for all supported retro computing platforms.

## 🎯 Quick Start

```bash
# Start all development containers
docker-compose up -d

# Enter main workspace
docker-compose exec workspace bash

# You're now in a complete retro development environment!
```

## 🐳 Architecture Overview

The development environment provides isolated containers for each platform with modern cross-development tools:

```
Development Environment
├── workspace/              # Main development container
│   ├── All cross-assemblers and compilers
│   ├── Build scripts for each platform
│   ├── Shared volumes for file transfer
│   └── Development utilities
├── Platform Containers/    # Specialized environments
│   ├── c64/               # VICE + ACME/ca65
│   ├── spectrum/          # Fuse + sjasmplus
│   ├── amiga/             # FS-UAE + vasm
│   ├── nes/               # Mesen + ca65
│   └── [+12 more platforms]
└── Shared Volumes/        # File transfer hub
    ├── projects/          # Your source code
    ├── builds/            # Compiled programs
    └── assets/            # Graphics, music, data
```

## 🖥️ Supported Platforms

| Platform | Container | Assembler/Compiler | Output Format | Emulator |
|----------|-----------|-------------------|---------------|-----------|
| **Commodore 64** | `c64` | ACME, ca65 | .prg files | VICE |
| **ZX Spectrum** | `spectrum` | sjasmplus | .tap, .sna files | Fuse |
| **Nintendo NES** | `nes` | ca65 | .nes files | Mesen |
| **Commodore Amiga** | `amiga` | vasm | Executables | FS-UAE |
| **Apple II** | `appleii` | ca65 | Disk images | AppleWin |
| **Game Boy** | `gameboy` | RGBDS | .gb files | BGB |
| **Atari 2600** | `atari2600` | DASM | .bin files | Stella |
| **BBC Micro** | `bbcmicro` | BeebAsm | .ssd files | BeebEm |
| **Amstrad CPC** | `amstradcpc` | rasm | .dsk files | Arnold |
| **Atari 800** | `atari800` | MADS | .xex files | Altirra |
| **Dragon 32/64** | `dragon` | lwasm | .cas files | XRoar |
| **Sega Master System** | `mastersystem` | WLA-DX | .sms files | Emulicious |
| **Atari ST** | `atarist` | vasm | .tos files | Hatari |
| **Jupiter Ace** | `jupiterace` | Native Forth | .tap files | EightyOne |
| **Vectrex** | `vectrex` | as09 | .bin files | MAME |
| **TI-99/4A** | `ti994a` | xas99 | Cartridges | MAME |

## 🚀 Getting Started

### Prerequisites

**Required:**
- Docker Desktop (Windows/Mac) or Docker Engine (Linux)
- Git for repository management
- 4GB+ RAM available for containers
- 10GB+ disk space for complete setup

**Recommended:**
- Modern emulators for testing (see Platform Guide)
- VS Code with Docker extension
- Basic understanding of command-line operations

### Initial Setup

```bash
# 1. Navigate to development environment
cd development-environment

# 2. Build all containers (first time setup)
docker-compose build

# 3. Start the environment
docker-compose up -d

# 4. Verify all containers are running
docker-compose ps
```

### First Program Test

```bash
# Enter the main workspace
docker-compose exec workspace bash

# Test C64 development
cd /workspace/projects/c64
echo 'lda #$06 / sta $d020 / rts' > hello.asm
acme -f cbm -o hello.prg hello.asm
ls -la hello.prg  # Should show compiled program

# Test Spectrum development
cd /workspace/projects/spectrum
echo 'ld a,4 / out (254),a / ret' > hello.asm
sjasmplus --raw=hello.bin hello.asm
ls -la hello.bin  # Should show compiled program

# Copy to shared directory for emulator testing
cp /workspace/projects/c64/hello.prg /workspace/shared/c64/
cp /workspace/projects/spectrum/hello.bin /workspace/shared/spectrum/
```

## 🛠️ Platform Development Workflows

### Commodore 64 Development

**Container:** `c64`  
**Primary Assembler:** ACME (modern syntax)  
**Alternative:** ca65 (cc65 suite)  
**Output:** .prg files for VICE emulator  

```bash
# Development workflow
docker-compose exec workspace bash
cd /workspace/projects/c64

# Create program
cat > demo.asm << 'EOF'
* = $0801
    .byte $0c, $08, $0a, $00, $9e, $20
    .byte $32, $30, $36, $34, $00, $00, $00

* = $0810
start:
    lda #$06        ; Blue color
    sta $d020       ; Border color register
    lda #$0e        ; Light blue
    sta $d021       ; Background color
    rts
EOF

# Assemble
acme -f cbm -o demo.prg demo.asm

# Copy to shared volume for emulator
cp demo.prg /workspace/shared/c64/

# Test in VICE: LOAD "DEMO",8,1 then SYS 2064
```

### ZX Spectrum Development

**Container:** `spectrum`  
**Assembler:** sjasmplus  
**Output:** .tap files for Fuse emulator  

```bash
# Development workflow
cd /workspace/projects/spectrum

# Create border color demo
cat > border.asm << 'EOF'
    org 32768
start:
    ld a,2          ; Red border
    out (254),a     ; ULA port
    ret
EOF

# Assemble and create TAP file
sjasmplus --raw=border.bin border.asm
python3 /usr/local/bin/bin2tap.py border.bin 32768 border.tap

# Copy for emulator testing
cp border.tap /workspace/shared/spectrum/

# Test in Fuse: LOAD "" then RANDOMIZE USR 32768
```

### Nintendo NES Development

**Container:** `nes`  
**Assembler:** ca65 (cc65 suite)  
**Output:** .nes files for Mesen emulator  

```bash
# Development workflow
cd /workspace/projects/nes

# Create simple NES program
cat > hello.asm << 'EOF'
.segment "HEADER"
    .byte "NES", $1A, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

.segment "CODE"
reset:
    lda #$3F        ; Palette address high
    sta $2006
    lda #$00        ; Palette address low
    sta $2006
    lda #$30        ; White color
    sta $2007
    
forever:
    jmp forever

.segment "VECTORS"
    .word 0, reset, 0
    
.segment "CHR"
    .res 8192       ; Empty CHR data
EOF

# Assemble and link
ca65 hello.asm
ld65 -C /usr/share/cc65/cfg/nes.cfg hello.o -o hello.nes

# Copy for testing
cp hello.nes /workspace/shared/nes/

# Test in Mesen or other NES emulator
```

### Amiga Development

**Container:** `amiga`  
**Assembler:** vasm (Motorola 68000 syntax)  
**Output:** Executable files for FS-UAE  

```bash
# Development workflow
cd /workspace/projects/amiga

# Create copper demo
cat > copper.s << 'EOF'
    section code,code
    
start:
    move.l #copperlist,$dff080    ; Copper program pointer
    move.w #$8080,$dff096         ; Enable copper
    rts

    section data,data
copperlist:
    dc.w $0180,$0f00              ; Background = red
    dc.w $ffff,$fffe              ; End copper list
EOF

# Assemble
vasmm68k_mot -Fhunkexe -o copper copper.s

# Copy for testing
cp copper /workspace/shared/amiga/

# Test in FS-UAE or WinUAE
```

## 📁 Directory Structure

### Workspace Organization

```
/workspace/
├── projects/               # Your development projects
│   ├── c64/               # C64 projects
│   │   ├── lesson-examples/    # Code from lessons
│   │   ├── experiments/        # Personal test programs
│   │   └── games/             # Complete game projects
│   ├── spectrum/          # Spectrum projects
│   ├── amiga/             # Amiga projects
│   └── [all platforms]/  
├── shared/                # Files accessible to host
│   ├── c64/               # Built programs ready for emulator
│   ├── spectrum/
│   └── [platform directories]
├── tools/                 # Development utilities
│   ├── converters/        # File format converters
│   ├── graphics/          # Sprite and graphics tools
│   └── audio/             # Sound conversion tools
└── templates/             # Project templates
    ├── c64-basic-project/
    ├── spectrum-demo/
    └── [platform templates]
```

### File Transfer Workflow

```
Docker Container → Shared Volume → Host System → Emulator
/workspace/shared/ ←→ ./shared/ ←→ Your Emulator Directory
```

## 🎮 Build System Integration

### Universal Build Commands

```bash
# Create new project from template
make create-c64-project NAME=myproject
make create-spectrum-project NAME=demo
make create-amiga-project NAME=graphics

# Build specific project
make build-prg PROJECT=myproject      # C64
make build-tap PROJECT=demo           # Spectrum  
make build-exe PROJECT=graphics       # Amiga

# Build all examples in a directory
make build-all-c64
make build-all-spectrum
```

### Platform-Specific Build Scripts

Each platform includes optimized build scripts:

```bash
# C64 build script
#!/bin/bash
PROJECT=$1
acme -f cbm -o "${PROJECT}.prg" "${PROJECT}.asm"
echo "Built ${PROJECT}.prg - Load with: LOAD \"${PROJECT}\",8,1"

# Spectrum build script  
#!/bin/bash
PROJECT=$1
sjasmplus --raw="${PROJECT}.bin" "${PROJECT}.asm"
bin2tap.py "${PROJECT}.bin" 32768 "${PROJECT}.tap"
echo "Built ${PROJECT}.tap - Load with: LOAD \"\""

# NES build script
#!/bin/bash
PROJECT=$1
ca65 "${PROJECT}.asm" -o "${PROJECT}.o"
ld65 -C nes.cfg "${PROJECT}.o" -o "${PROJECT}.nes"
echo "Built ${PROJECT}.nes"
```

## 🔧 Development Tools

### Included Cross-Assemblers

**6502 Family (C64, Apple II, NES, BBC Micro, Atari 800):**
- **ACME**: Modern macro assembler with advanced features
- **ca65**: Part of cc65 suite, excellent for larger projects
- **DASM**: Traditional assembler, popular for Atari 2600

**Z80 Family (Spectrum, Amstrad CPC, Master System):**
- **sjasmplus**: Advanced Z80 assembler with many features
- **pasmo**: Simple, portable Z80 assembler
- **WLA-DX**: Multi-platform assembler suite

**68000 Family (Amiga, Atari ST):**
- **vasm**: Portable macro assembler for many CPUs
- **PhxAss**: Amiga-specific assembler

**Specialized Assemblers:**
- **RGBDS**: Game Boy development suite
- **BeebAsm**: BBC Micro specific assembler
- **MADS**: Advanced Atari 8-bit assembler

### Graphics and Audio Tools

**Graphics Conversion:**
```bash
# Convert PNG to C64 sprite data
png2sprite input.png > sprite_data.asm

# Convert image to Spectrum format
png2spectrum input.png output.scr

# Create Amiga IFF files
png2iff input.png output.iff
```

**Audio Tools:**
```bash
# Convert MOD files for Amiga
mod2raw music.mod music.raw

# Generate C64 SID music data
sid2asm music.sid > music_data.asm
```

## 🧪 Testing and Validation

### Automated Testing

```bash
# Test all platform build systems
./scripts/test-all-platforms.sh

# Test specific platform examples
./scripts/test-c64-examples.sh
./scripts/test-spectrum-examples.sh

# Validate lesson code examples
./scripts/validate-lesson-code.sh
```

### Emulator Integration Testing

```bash
# Automated emulator testing (where supported)
./scripts/test-emulator-integration.sh

# Launch specific program in emulator
./scripts/launch-vice.sh projects/c64/demo.prg
./scripts/launch-fuse.sh projects/spectrum/demo.tap
```

## 🔄 Container Management

### Daily Workflow

```bash
# Start development session
docker-compose up -d

# Check container status
docker-compose ps

# Enter workspace for development
docker-compose exec workspace bash

# When finished (keeps containers running)
exit

# Stop containers (preserves data)
docker-compose down

# Full cleanup (removes containers and volumes)
docker-compose down -v
```

### Container Updates

```bash
# Update base images
docker-compose pull

# Rebuild with latest tools
docker-compose build --no-cache

# Update specific platform
docker-compose build c64
docker-compose up -d c64
```

### Resource Management

**Performance Tuning:**
- Allocate at least 4GB RAM to Docker
- Use SSD storage for better I/O performance
- Close unnecessary containers when not in use
- Monitor disk usage in shared volumes

**Storage Cleanup:**
```bash
# Remove unused images and containers
docker system prune

# Clean build artifacts
find ./shared -name "*.o" -delete
find ./shared -name "*.lst" -delete
```

## 🐛 Troubleshooting

### Common Issues

**Containers won't start:**
```bash
# Check Docker daemon
docker --version
docker info

# Rebuild containers
docker-compose down
docker-compose build --no-cache
docker-compose up -d
```

**File permission issues (Linux):**
```bash
# Fix shared volume permissions
sudo chown -R $USER:$USER shared/
chmod -R 755 shared/
```

**Assembly fails:**
```bash
# Verify assembler installation
docker-compose exec workspace which acme
docker-compose exec workspace acme --version

# Check file paths and syntax
docker-compose exec workspace ls -la /workspace/projects/c64/
```

**Can't access built files:**
```bash
# Verify shared volume mounting
docker-compose exec workspace ls -la /workspace/shared/
ls -la shared/  # On host system

# Check file permissions
docker-compose exec workspace stat /workspace/shared/c64/demo.prg
```

### Getting Help

**Development Environment Issues:**
- Check container logs: `docker-compose logs [service]`
- Verify volume mounts: `docker-compose config`
- Test with minimal example first

**Platform-Specific Problems:**
- Consult platform documentation in containers
- Check assembler-specific syntax requirements
- Verify target format compatibility with emulator

## 📚 Learning Resources

### Platform Documentation

Each container includes comprehensive documentation:
```bash
# Access platform-specific help
docker-compose exec c64 cat /usr/local/doc/c64-development.txt
docker-compose exec spectrum cat /usr/local/doc/spectrum-guide.txt

# View assembler documentation
docker-compose exec workspace man acme
docker-compose exec workspace sjasmplus --help
```

### Example Projects

```bash
# Explore included examples
ls -la /workspace/templates/
cat /workspace/templates/c64-basic-project/README.txt

# Copy example project
cp -r /workspace/templates/c64-demo /workspace/projects/my-c64-demo
```

### Educational Integration

The development environment integrates directly with Code198x lessons:
- All lesson code examples can be built and tested
- Screenshots can be captured automatically
- Programs can be launched in emulators for verification
- Development follows authentic period practices with modern convenience

## 🎯 Next Steps

With your development environment ready:

1. **[Start with Platform Guide](../docs/PLATFORM_GUIDE.md)** - Choose your first platform
2. **[Follow Lesson Structure](../docs/LESSON_STRUCTURE.md)** - Understand the learning progression  
3. **[Begin Phase 0 Lessons](../lessons/)** - Start programming immediately
4. **[Contribute to the Project](../CONTRIBUTING.md)** - Help expand the platform

---

**Your complete retro development environment is now ready!**

Build authentic programs for legendary computing platforms using modern tools and workflows. The same environment that created the lessons can now power your own retro programming adventures.

**Develop like it's 202x. Target like it's 198x.**