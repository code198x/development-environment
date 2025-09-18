# Code198x Development Environment

Docker-based assembler toolchain for retro game development across classic 8-bit and 16-bit systems.

![Build Status](https://github.com/code198x/development-environment/actions/workflows/docker-build.yml/badge.svg)

## 🎮 Supported Systems

| System | Assembler | GHCR Image | Docker Hub |
|--------|-----------|------------|------------|
| Commodore 64 | ACME | `ghcr.io/code198x/commodore-64:latest` | `code198x/commodore-64:latest` |
| ZX Spectrum | SjASMPlus | `ghcr.io/code198x/sinclair-zx-spectrum:latest` | `code198x/sinclair-zx-spectrum:latest` |
| NES | cc65 | `ghcr.io/code198x/nintendo-entertainment-system:latest` | `code198x/nintendo-entertainment-system:latest` |
| Amiga | VASM | `ghcr.io/code198x/commodore-amiga:latest` | `code198x/commodore-amiga:latest` |

## 🚀 Quick Start

### Using GitHub Container Registry (Recommended)

```bash
# Commodore 64
docker pull ghcr.io/code198x/commodore-64:latest
docker run --rm -v $(pwd):/workspace ghcr.io/code198x/commodore-64:latest -o program.prg main.asm

# ZX Spectrum
docker pull ghcr.io/code198x/sinclair-zx-spectrum:latest
docker run --rm -v $(pwd):/workspace ghcr.io/code198x/sinclair-zx-spectrum:latest main.asm

# NES
docker pull ghcr.io/code198x/nintendo-entertainment-system:latest
docker run --rm -v $(pwd):/workspace ghcr.io/code198x/nintendo-entertainment-system:latest main.asm -o main.o

# Amiga
docker pull ghcr.io/code198x/commodore-amiga:latest
docker run --rm -v $(pwd):/workspace ghcr.io/code198x/commodore-amiga:latest -Fhunkexe -o program main.asm
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

- [Code198x Website](https://code198x.stevehill.xyz) - Main educational platform
- [Code Samples](https://github.com/code198x/code-samples) - Example code for lessons

---

Built with ❤️ for the retro computing community