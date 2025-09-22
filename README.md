# Code Like It's 198x Development Environment

Docker-based assembler toolchain for retro game development across classic 8-bit and 16-bit systems.

![Build Status](https://github.com/code198x/development-environment/actions/workflows/docker-build.yml/badge.svg)
![Latest Release](https://img.shields.io/github/v/release/code198x/development-environment)

**Current Version:** v2.0.0 (Released: September 22, 2025)

## 📌 Versioning

**For Educators:** Use specific version tags (e.g., `:v2.0.0`) to ensure consistency across semesters.

```bash
# Stable version (recommended for courses)
docker pull ghcr.io/code198x/commodore-64:v2.0.0

# Latest development version
docker pull ghcr.io/code198x/commodore-64:latest
```

## 🎮 Supported Systems

| System | Assembler | GHCR Image | Docker Hub |
|--------|-----------|------------|------------|
| Commodore 64 | ACME | `ghcr.io/code198x/commodore-64:v2.0.0` | `code198x/commodore-64:v2.0.0` |
| ZX Spectrum | SjASMPlus | `ghcr.io/code198x/sinclair-zx-spectrum:v2.0.0` | `code198x/sinclair-zx-spectrum:v2.0.0` |
| NES | cc65 | `ghcr.io/code198x/nintendo-entertainment-system:v2.0.0` | `code198x/nintendo-entertainment-system:v2.0.0` |
| Amiga | VASM | `ghcr.io/code198x/commodore-amiga:v2.0.0` | `code198x/commodore-amiga:v2.0.0` |

### Complete System List (64 Systems)

<details>
<summary>Click to expand full list of supported systems</summary>

#### 6502 Family
- Commodore 64, 128, PET, Plus/4
- Apple II
- Nintendo NES, Donkey Kong (Arcade)
- Atari 2600, 800
- Acorn BBC Micro

#### Z80 Family
- Sinclair ZX Spectrum, ZX81
- Amstrad CPC
- MSX
- Sam Coupé
- Enterprise 128
- Oric-1, Oric Atmos
- Thomson MO5
- Coleco Adam
- Sega Game Gear

#### 68000 Family
- Commodore Amiga
- Atari ST, Lynx, Jaguar
- Sega Genesis, 32X
- SNK Neo Geo (MVS/AES)
- Sharp X68000
- Capcom Street Fighter II (CPS1)

#### Other Processor Families
- **8080**: Altair 8800, IMSAI 8080
- **6809**: Dragon 32/64, TRS-80 Model I, Vectrex, Williams Defender
- **MIPS**: Sony PlayStation, Nintendo 64
- **ARM**: Game Boy Advance, Nintendo DS, 3DO
- **SuperH**: Sega Saturn, Dreamcast
- **x86**: FM Towns, PC-9801, PC-8801, CompuPro System 816, Sharp X1
- **V30**: Bandai WonderSwan, TurboGrafx-16, PC Engine SuperGrafx
- **TLCS-900H**: Neo Geo Pocket
- **Arcade**: Asteroids, Tempest, Pac-Man, Galaga, Konami GX400

</details>

## 🚀 Quick Start

### Using GitHub Container Registry (Recommended)

```bash
# Commodore 64
docker pull ghcr.io/code198x/commodore-64:v2.0.0
docker run --rm -v $(pwd):/workspace ghcr.io/code198x/commodore-64:v2.0.0 -o program.prg main.asm

# ZX Spectrum
docker pull ghcr.io/code198x/sinclair-zx-spectrum:v2.0.0
docker run --rm -v $(pwd):/workspace ghcr.io/code198x/sinclair-zx-spectrum:v2.0.0 main.asm

# NES
docker pull ghcr.io/code198x/nintendo-entertainment-system:v2.0.0
docker run --rm -v $(pwd):/workspace ghcr.io/code198x/nintendo-entertainment-system:v2.0.0 main.asm -o main.o

# Amiga
docker pull ghcr.io/code198x/commodore-amiga:v2.0.0
docker run --rm -v $(pwd):/workspace ghcr.io/code198x/commodore-amiga:v2.0.0 -Fhunkexe -o program main.asm
```

### Using Docker Hub (Alternative)

Replace `ghcr.io/code198x/` with `code198x/` in the commands above.

## 🏗️ Building Images Locally

```bash
# Clone the repository
git clone https://github.com/code198x/development-environment.git
cd development-environment

# Build all images
make build

# Build a specific system
make build-commodore-64

# Test an assembler
make test-commodore-64
```

## 📁 Repository Structure

```
development-environment/
├── commodore-64/
│   ├── Dockerfile          # ACME assembler
│   └── test.asm           # Test file
├── sinclair-zx-spectrum/
│   ├── Dockerfile          # SjASMPlus assembler
│   └── test.asm           # Test file
├── nintendo-entertainment-system/
│   ├── Dockerfile          # cc65 suite
│   ├── nes.cfg            # Linker configuration
│   └── test.asm           # Test file
├── commodore-amiga/
│   ├── Dockerfile          # VASM assembler
│   └── test.asm           # Test file
├── systems-config.json     # Central configuration
├── scripts/
│   ├── build-images.sh    # Build all images
│   ├── generate-matrix.mjs # Generate CI/CD matrices
│   └── add-system.mjs     # Add new systems
└── Makefile               # Convenience targets
```

## 🔧 Matrix-Based Configuration

The entire system is configured through `systems-config.json`. Adding a new platform:

1. Run the interactive script:
   ```bash
   node scripts/add-system.mjs
   ```

2. Or manually update `systems-config.json` and create the system directory

3. The CI/CD pipeline automatically adapts to include the new system

## 🏗️ Base Image Architecture

To reduce duplication and improve build efficiency, the system uses layered base images organized by processor architecture:

- **retro-base**: Common Ubuntu 24.04 foundation with build tools
- **6502-base**: For Commodore 64, NES, Apple II, Atari 2600, etc.
- **z80-base**: For ZX Spectrum, Amstrad CPC, Game Boy, etc.
- **68000-base**: For Amiga, Atari ST, etc.

See [BASE_IMAGES.md](BASE_IMAGES.md) for detailed architecture documentation.

## 🧪 Testing

Each system includes a test file:

```bash
# Test all systems
make test

# Test specific system
make test-commodore-64

# Verify in CI/CD style
node scripts/generate-matrix.mjs verify
```

## 🔄 CI/CD Integration

### GitHub Actions

The workflow automatically:
- Builds Docker images for all systems in parallel
- Publishes to GitHub Container Registry (always)
- Publishes to Docker Hub (when credentials configured)
- Tests each assembler with example code
- Creates releases with image information

### Using in Your CI/CD

```yaml
# Example GitHub Actions job
- name: Assemble C64 code
  run: |
    docker pull ghcr.io/code198x/commodore-64:latest
    docker run --rm -v $(pwd):/workspace ghcr.io/code198x/commodore-64:latest -o output.prg main.asm
```

## 📚 Documentation

- [Setup Guide](SETUP.md) - Configure Docker Hub credentials
- [Systems Config](systems-config.json) - Platform definitions
- [GitHub Actions](.github/workflows/docker-build.yml) - CI/CD pipeline

## 🤝 Contributing

1. Fork the repository
2. Add your system using `node scripts/add-system.mjs`
3. Test locally with `make test-<system>`
4. Submit a pull request

## 📜 License

MIT License - See LICENSE file for details

## 🔗 Related Projects

- [Code Like It's 198x Website](https://code198x.stevehill.xyz) - Main educational platform
- [Code Samples](https://github.com/code198x/code-samples) - Example code for lessons

---

Built with ❤️ for the retro computing community