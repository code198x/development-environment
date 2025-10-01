# Commodore 64 Development Environment

Docker-based development environment for C64 programming with BASIC and Assembly language support.

## 🎯 What's Included

- **ACME Assembler** - Cross-assembler for 6502 code
- **VICE Emulator** - Complete C64 emulator (x64sc)
- **petcat** - Convert BASIC text files to PRG format
- **Build tools** - make, git, and essential utilities

## 🚀 Quick Start

### Option 1: Docker Compose (Recommended)

```bash
# Start the environment
docker-compose up -d

# Enter the container
docker-compose exec c64-dev bash

# Stop when done
docker-compose down
```

### Option 2: VS Code Dev Container

1. Install the "Dev Containers" extension in VS Code
2. Open this folder in VS Code
3. Click "Reopen in Container" when prompted
4. VS Code will build and start the container automatically

### Option 3: Docker CLI

```bash
# Build the image
docker build -t code198x/commodore-64:latest .

# Run interactively
docker run -it --rm -v $(pwd):/workspace code198x/commodore-64:latest

# Or run a specific command
docker run --rm -v $(pwd):/workspace code198x/commodore-64:latest \
  acme -f cbm -o program.prg source.asm
```

## 📚 Examples

Three complete example projects are included:

### Assembly - Hello World
```bash
cd examples/assembly/hello
make          # Build
make run      # Run in VICE
```

### Assembly - Skyfall Game
Complete responsive player control system from the Assembly Week 1 course:
```bash
cd examples/assembly/skyfall
make          # Build
make run      # Run in VICE
```

### BASIC - Number Hunter
Number guessing game from the BASIC Week 1 course:
```bash
cd examples/basic/number-hunter
make          # Convert to PRG
make run      # Run in VICE
```

## 🛠️ Common Commands

### Assembly Development

```bash
# Assemble a program
acme -f cbm -o program.prg source.asm

# Run in emulator
x64sc program.prg

# With custom load address
acme -f cbm -o program.prg --cpu 6510 source.asm
```

### BASIC Development

```bash
# Convert BASIC text to PRG
petcat -w2 -o program.prg -- source.bas

# The -w2 flag means "BASIC V2" (C64 BASIC version)

# Run the program
x64sc program.prg
```

### Project Structure

Recommended project layout:
```
my-project/
├── src/
│   ├── main.asm      # Main source file
│   └── includes/     # Include files
├── build/            # Build output
├── Makefile          # Build automation
└── README.md         # Project documentation
```

## 🎓 Learning Resources

This environment is designed for use with the [Code Like It's 198x](https://code198x.stevehill.xyz) educational platform.

**Courses available:**
- C64 BASIC Week 1 - Number guessing game
- C64 Assembly Week 1 - Skyfall (player controls)

**Code samples:** https://github.com/code198x/code-samples

## 🔧 Troubleshooting

### VICE Display Issues

If VICE won't start with GUI, you may need X11 forwarding:

**macOS:**
```bash
# Install XQuartz
brew install --cask xquartz

# Allow X11 connections
xhost +localhost

# Set DISPLAY variable
export DISPLAY=:0
```

**Linux:**
```bash
# Allow X11 connections
xhost +local:docker
```

### Headless Mode

VICE can run without GUI for automated builds:
```bash
# Just assemble, don't run emulator
acme -f cbm -o program.prg source.asm
```

### File Permissions

If you encounter permission issues with files created in the container:

```bash
# Change ownership to your user
sudo chown -R $(whoami):$(whoami) .
```

## 📝 Makefile Template

Create a `Makefile` in your project:

```makefile
# Assembly project
TARGET = program
SRC = $(TARGET).asm

all: $(TARGET).prg

$(TARGET).prg: $(SRC)
	acme -f cbm -o $@ $<

run: $(TARGET).prg
	x64sc $<

clean:
	rm -f $(TARGET).prg

.PHONY: all run clean
```

## 🐳 Building Custom Images

To customize the environment:

1. Edit `Dockerfile` to add tools or change configuration
2. Rebuild:
   ```bash
   docker-compose build
   # or
   docker build -t code198x/commodore-64:latest .
   ```

## 📦 Publishing

To share your image on Docker Hub:

```bash
# Tag with version
docker tag code198x/commodore-64:latest code198x/commodore-64:v1.0.0

# Push to Docker Hub
docker push code198x/commodore-64:latest
docker push code198x/commodore-64:v1.0.0
```

## 🤝 Contributing

This environment is part of the Code Like It's 198x educational project.

**Repository:** https://github.com/code198x/development-environment

## 📄 License

MIT License - See LICENSE file for details

## 🎮 About

Code Like It's 198x teaches retro game development for classic 8-bit and 16-bit systems. This C64 environment provides everything needed to start coding for the legendary Commodore 64.

**Website:** https://code198x.stevehill.xyz
**Course Materials:** https://github.com/code198x/
