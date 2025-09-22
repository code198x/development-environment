# Code Like It's 198x Developer Guide

## 🚀 Quick Start

Get started with retro assembly development in seconds!

### Prerequisites
- Docker installed and running
- Basic knowledge of assembly language
- Passion for retro computing!

### Instant Development Environment

```bash
# Set up your workspace
make dev-setup

# Jump into Commodore 64 development
make c64

# Or Nintendo development
make nes

# Or any other system
make spectrum
make amiga
make genesis
```

## 📦 Project Structure

```
development-environment/
├── workspace/          # Your active development area
├── projects/           # Organized by system
│   ├── commodore-64/
│   ├── nintendo-entertainment-system/
│   ├── sinclair-zx-spectrum/
│   ├── commodore-amiga/
│   └── sega-genesis/
├── resources/          # System-specific resources
│   ├── includes/       # Header files
│   ├── libs/          # Libraries
│   └── examples/      # Example code
└── docker-compose.yml  # Multi-system orchestration
```

## 🎮 System-Specific Development

### Commodore 64 (6502)
```bash
# Start C64 development
make c64

# Inside container:
acme main.asm           # ACME assembler
ca65 main.asm          # CC65 assembler
```

### Nintendo Entertainment System (6502)
```bash
# Start NES development
make nes

# Inside container:
ca65 main.asm -o main.o
ld65 main.o -C nes.cfg -o game.nes
```

### ZX Spectrum (Z80)
```bash
# Start Spectrum development
make spectrum

# Inside container:
sjasmplus main.asm --tap=game.tap
```

### Sega Genesis (68000)
```bash
# Start Genesis development
make genesis

# Inside container:
vasmm68k_mot -Fbin main.asm -o game.bin
```

### Commodore Amiga (68000)
```bash
# Start Amiga development
make amiga

# Inside container:
vasmm68k_mot -Fhunkexe main.asm -o game
```

## 📝 Creating a New Project

```bash
# Create a new project
make new-project NAME=space-invaders SYSTEM=commodore-64

# Navigate to your project
cd projects/commodore-64/space-invaders

# Start coding!
make c64
```

## 🛠️ Available Assemblers

| System | Processor | Assemblers | Output Format |
|--------|-----------|------------|---------------|
| Commodore 64 | 6502 | ACME, CA65 | PRG, D64 |
| NES | 6502 | CA65 | NES ROM |
| ZX Spectrum | Z80 | SjASMPlus | TAP, TZX |
| Sega Genesis | 68000 | VASM | BIN, SMD |
| Amiga | 68000 | VASM | ADF, HDF |

## 🔧 Advanced Usage

### Using Docker Compose

```bash
# Start all development environments
docker-compose up -d

# Access specific system
docker-compose exec c64 /bin/bash

# Stop all containers
docker-compose down
```

### Cross-Compilation

```bash
# Assemble from outside container
make assemble FILE=main.asm SYSTEM=c64
```

### Batch Operations

```bash
# Test all systems
make test

# Build all images locally
make build-all

# Clean everything
make clean
```

## 📚 Learning Resources

Each system includes example code in `/resources/<system>/examples/`:

- **hello.asm** - Basic "Hello World"
- **sprites.asm** - Sprite manipulation
- **sound.asm** - Sound generation
- **input.asm** - Controller/keyboard input

## 🤝 Contributing

To add a new system:

1. Create system directory structure
2. Add Dockerfile with assembler
3. Create test.asm for validation
4. Update systems-config.json
5. Submit PR with examples

## 🐛 Troubleshooting

### Container won't start
```bash
docker system prune -a
make build
```

### Permission issues
```bash
# Run with your user ID
docker run --user $(id -u):$(id -g) ...
```

### Can't find assembler
```bash
# Check which assemblers are available
docker run --rm ghcr.io/code198x/commodore-64:latest which acme ca65
```

## 📊 Performance Tips

- Use volume mounts for source code (already configured)
- Keep assembled output in workspace/
- Use .dockerignore for large files
- Leverage Docker layer caching

## 🎯 Best Practices

1. **Version Control**: Keep your assembly projects in git
2. **Comments**: Document your assembly code thoroughly
3. **Modularity**: Split code into includes
4. **Testing**: Write test programs for each routine
5. **Optimization**: Profile before optimizing

## 🚢 Deployment

Built binaries can be:
- Run in emulators (VICE, FCEUX, etc.)
- Written to physical media (floppy, cartridge)
- Shared online (.prg, .nes, .tap files)

## 📖 Next Steps

1. Choose your favorite retro system
2. Start with hello world example
3. Modify and experiment
4. Build something amazing!
5. Share with the community!

Happy coding! 🎮✨