# Code Like It's 198x - Development Environment

Docker-based development environments for retro game development. Part of the [Code Like It's 198x](https://codelike198x.com) curriculum.

## Quick Start

```bash
# Pull and run the C64 environment
docker pull stevehill/code198x:commodore-64
docker run -it -v $(pwd):/workspace stevehill/code198x:commodore-64

# Pull and run the ZX Spectrum environment
docker pull stevehill/code198x:zx-spectrum
docker run -it -v $(pwd):/workspace stevehill/code198x:zx-spectrum

# Pull and run the NES environment
docker pull stevehill/code198x:nes
docker run -it -v $(pwd):/workspace stevehill/code198x:nes

# Pull and run the Amiga environment
docker pull stevehill/code198x:amiga
docker run -it -v $(pwd):/workspace stevehill/code198x:amiga
```

## What's Included

Each Docker image contains:
- The appropriate assembler for the platform
- Build scripts and helpers
- Makefile templates
- All necessary dependencies

### Commodore 64
- **Assembler**: ACME
- **Helper**: `build-c64` script
- **Output**: `.prg` files ready for emulators

### ZX Spectrum
- **Assembler**: sjasmplus
- **Helper**: `build-spectrum` script
- **Output**: `.tap` files ready for emulators

### Nintendo Entertainment System
- **Assembler**: cc65 suite (ca65/ld65)
- **Helper**: `build-nes` script
- **Output**: `.nes` ROM files

### Amiga
- **Assembler**: vasm (68000)
- **Helpers**: `build-amiga` and `makeadf` scripts
- **Output**: Bootable `.adf` disk images

## Usage Example

### Commodore 64
```bash
# Create a project directory
mkdir my-c64-game
cd my-c64-game

# Run the Docker container
docker run -it -v $(pwd):/workspace stevehill/code198x:commodore-64

# Inside the container:
# Create your assembly file
cat > game.asm << 'EOF'
    * = $0801
    !byte $0c,$08,$0a,$00,$9e
    !text "2064"
    !byte $00,$00,$00

    * = $0810
    lda #$00
    sta $d020
    sta $d021
    rts
EOF

# Build it
build-c64 game.asm

# You now have game.prg ready to run!
```

## Building Images Locally

If you want to build the images yourself:

```bash
# Clone this repository
git clone https://github.com/stevehill/code198x-development-environment.git
cd code198x-development-environment

# Build individual images
docker build -t code198x:commodore-64 commodore-64/
docker build -t code198x:zx-spectrum zx-spectrum/
docker build -t code198x:nes nes/
docker build -t code198x:amiga amiga/
```

## Directory Structure

```
development-environment/
├── commodore-64/
│   ├── Dockerfile
│   ├── scripts/
│   │   └── build.sh
│   └── templates/
│       └── Makefile.c64
├── zx-spectrum/
│   ├── Dockerfile
│   ├── scripts/
│   │   └── build.sh
│   └── templates/
│       └── Makefile.spectrum
├── nes/
│   ├── Dockerfile
│   ├── config/
│   │   └── nes.cfg
│   ├── scripts/
│   │   └── build.sh
│   └── templates/
│       └── Makefile.nes
└── amiga/
    ├── Dockerfile
    ├── scripts/
    │   ├── build.sh
    │   └── makeadf.sh
    └── templates/
        └── Makefile.amiga
```

## Requirements

- Docker Desktop (macOS/Windows) or Docker Engine (Linux)
- A local emulator for testing your builds:
  - C64: [VICE](https://vice-emu.sourceforge.io/)
  - Spectrum: [Fuse](http://fuse-emulator.sourceforge.net/)
  - NES: [FCEUX](http://fceux.com/) or [Mesen](https://mesen.ca/)
  - Amiga: [FS-UAE](https://fs-uae.net/)

## Contributing

Issues and pull requests welcome! Please ensure any new platforms follow the same pattern:
- Minimal, focused Dockerfile
- Simple build script
- Makefile template
- Clear documentation

## License

MIT License - See LICENSE file for details.

Individual tools retain their original licenses:
- ACME: Public Domain
- sjasmplus: BSD-3-Clause
- cc65: zlib License
- vasm: Free for non-commercial use