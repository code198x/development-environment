# Base Images Architecture

The Code Like It's 198x development environment uses a layered base image approach to reduce duplication, improve build efficiency, and maintain consistency across related processor architectures.

## Architecture Overview

```
code198x-base (Ubuntu 24.04 + common tools)
├── 6502-base (6502 family tools)
│   └── systems/
│       ├── commodore-64 (ACME)
│       ├── nintendo-entertainment-system (cc65)
│       ├── apple-ii (ca65)
│       ├── atari-2600 (dasm)
│       ├── bbc-micro (beebasm)
│       └── atari-800 (mads)
├── z80-base (Z80 family tools)
│   └── systems/
│       ├── sinclair-zx-spectrum (SjASMPlus)
│       ├── amstrad-cpc (rasm)
│       ├── sega-master-system (wla-dx)
│       └── game-boy (rgbds)
└── 68000-base (68000 family tools)
    └── systems/
        ├── commodore-amiga (VASM)
        └── atari-st (VASM)
```

## Base Images

### code198x-base
**Purpose**: Common foundation for all retro development environments
**Contains**:
- Ubuntu 24.04 LTS
- Build essentials (gcc, make, git, etc.)
- Common utilities (wget, curl, unzip, python3)
- Standard workspace setup
- Non-privileged user account

### 6502-base
**Purpose**: Shared foundation for 6502-family processors
**Extends**: retro-base
**Contains**:
- 6502-specific dependencies
- Common 6502 development tools path (/opt/6502-tools/bin)
- Architecture environment variable (RETRO_ARCH=6502)

### z80-base
**Purpose**: Shared foundation for Z80-family processors
**Extends**: retro-base
**Contains**:
- Z80-specific dependencies
- Common Z80 development tools path (/opt/z80-tools/bin)
- Architecture environment variable (RETRO_ARCH=z80)

### 68000-base
**Purpose**: Shared foundation for 68000-family processors
**Extends**: retro-base
**Contains**:
- 68000-specific dependencies
- Common 68000 development tools path (/opt/68000-tools/bin)
- Architecture environment variable (RETRO_ARCH=68000)

## Benefits

### Build Efficiency
- **Reduced Build Time**: Common layers are built once and reused
- **Layer Caching**: Docker effectively caches shared layers
- **Parallel Builds**: Base images can be built in parallel with dependencies

### Storage Optimization
- **Reduced Image Size**: Common layers are shared across related systems
- **Registry Efficiency**: Base layers are downloaded once per architecture family

### Maintenance
- **Centralized Updates**: Update common tools in one place
- **Consistent Environment**: All systems in a family share the same base
- **Security Updates**: Base image updates propagate to all derived images

### Development
- **Faster Iteration**: System-specific changes don't require rebuilding common layers
- **Consistent Tooling**: Standard paths and utilities across all systems
- **Easy Debugging**: Consistent environment makes troubleshooting easier

## Build Order

Base images must be built in dependency order:

1. **retro-base** (foundation)
2. **Architecture bases** (6502-base, z80-base, 68000-base) - can be parallel
3. **System images** (commodore-64, zx-spectrum, etc.) - can be parallel per architecture

## Usage

### Building Base Images
```bash
# Build all base images
./scripts/build-base-images.sh

# Or build individually in order
docker build -t code198x/retro-base:latest base-images/retro-base/
docker build -t code198x/6502-base:latest base-images/6502-base/
docker build -t code198x/z80-base:latest base-images/z80-base/
docker build -t code198x/68000-base:latest base-images/68000-base/
```

### Using in System Dockerfiles
```dockerfile
# Use appropriate base for your architecture
FROM code198x/6502-base:latest

# System-specific setup
USER root
RUN git clone https://github.com/example/assembler.git /tmp/assembler && \
    cd /tmp/assembler && \
    make && \
    cp assembler /opt/6502-tools/bin/ && \
    rm -rf /tmp/assembler

USER retro
ENTRYPOINT ["assembler"]
```

### Registry Strategy
Base images are published to both:
- **GitHub Container Registry**: `ghcr.io/code198x/{base-image}:latest`
- **Docker Hub**: `code198x/{base-image}:latest` (when credentials configured)

## CI/CD Integration

The GitHub Actions workflow builds base images first, then system images:

1. **build-base-images.yml**: Builds all base images in dependency order
2. **docker-build.yml**: Depends on base images, then builds systems in parallel

This ensures base images are always available when building system images.

## Adding New Systems

When adding a new system:

1. Determine the processor architecture (6502, Z80, 68000, or new family)
2. If new family, create a new base image extending retro-base
3. Update `systems-config.json` with the appropriate `base_image` field
4. Create system Dockerfile using `FROM code198x/{base-image}:latest`

## Future Extensions

The base image architecture is designed to accommodate:
- **New Processor Families**: ARM, RISC-V, x86 systems
- **Cross-Development Tools**: Emulators, debuggers, file format converters
- **Advanced Tooling**: Static analysis, code formatting, documentation generators

## File Structure

```
development-environment/
├── base-images/
│   ├── retro-base/
│   │   └── Dockerfile
│   ├── 6502-base/
│   │   └── Dockerfile
│   ├── z80-base/
│   │   └── Dockerfile
│   └── 68000-base/
│       └── Dockerfile
├── scripts/
│   └── build-base-images.sh
├── .github/workflows/
│   ├── build-base-images.yml
│   └── docker-build.yml
├── systems-config.json
└── BASE_IMAGES.md (this file)
```