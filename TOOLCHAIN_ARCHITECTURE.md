# Proposed Toolchain Separation Architecture

## Current Problem
- 6502-base takes 35+ minutes to build (mainly due to cc65 compilation)
- Other bases take 2-12 minutes
- Any toolchain update requires rebuilding entire base images
- Cannot update individual tools without affecting others
- No parallel building of toolchains

## Proposed Solution: Separate Toolchain Images

### Architecture Overview

```
┌─────────────────────────────────────────────────────┐
│                  Tool Images (Parallel Build)        │
├─────────────┬─────────────┬────────────┬───────────┤
│ acme:latest │ cc65:latest │ vasm:latest│ sjasmplus │
│   (1 min)   │  (35 min)   │   (3 min)  │  (2 min)  │
└─────────────┴─────────────┴────────────┴───────────┘
                           ↓
        COPY --from during base image builds
                           ↓
┌─────────────────────────────────────────────────────┐
│                    Base Images                       │
├──────────────┬──────────────┬───────────────────────┤
│  6502-base   │   z80-base   │    68000-base         │
│ (acme + cc65)│  (sjasmplus) │      (vasm)           │
└──────────────┴──────────────┴───────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────┐
│                  System Images                       │
├──────────────┬──────────────┬───────────────────────┤
│ commodore-64 │ zx-spectrum  │  commodore-amiga      │
└──────────────┴──────────────┴───────────────────────┘
```

## Implementation Example

### Individual Tool Image (tools/cc65/Dockerfile)
```dockerfile
FROM ubuntu:24.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget

# Build cc65
ARG CC65_VERSION=V2.19
RUN wget https://github.com/cc65/cc65/archive/refs/tags/${CC65_VERSION}.tar.gz && \
    tar -xzf ${CC65_VERSION}.tar.gz && \
    cd cc65-* && \
    make -j$(nproc) PREFIX=/opt/cc65 && \
    make install PREFIX=/opt/cc65

# Runtime stage - just the compiled tool
FROM ubuntu:24.04
COPY --from=builder /opt/cc65 /opt/cc65
```

### Updated Base Image (base-images/6502-base/Dockerfile)
```dockerfile
FROM ghcr.io/code198x/code198x-base:latest

# Copy pre-built tools from their images
COPY --from=ghcr.io/code198x/tools/cc65:v2.19 /opt/cc65 /opt/cc65
COPY --from=ghcr.io/code198x/tools/acme:v0.97 /opt/acme /opt/acme

# Set up PATH
ENV PATH="/opt/cc65/bin:/opt/acme/bin:$PATH"
```

## Benefits

1. **Parallel Building**: All toolchains build simultaneously
2. **Better Caching**: Individual tools cached separately
3. **Faster Updates**: Update only the tool that changed
4. **Version Flexibility**: Mix and match tool versions
5. **Reduced Build Time**: 35 minutes → ~5 minutes for 6502-base
6. **Reusability**: Same tool image used by multiple bases

## Migration Strategy

### Phase 1: Create Tool Images (v1.1.0)
- Create separate images for each toolchain
- Tag with semantic versions
- Build in parallel in CI

### Phase 2: Update Base Images (v1.2.0)
- Modify base images to use COPY --from
- Remove compilation steps
- Test thoroughly

### Phase 3: Optimize CI/CD (v1.3.0)
- Cache tool images aggressively
- Only rebuild changed tools
- Use matrix strategy for parallel builds

## Tool Image List

### Assemblers
- `tools/acme` - ACME cross-assembler (6502)
- `tools/cc65` - cc65 suite (6502)
- `tools/sjasmplus` - SjASMPlus (Z80)
- `tools/vasm` - vasm multi-target (68000, etc.)
- `tools/nasm` - NASM (x86)
- `tools/armips` - armips (ARM/MIPS)
- `tools/asar` - Asar (65816)

### Emulators/Tools
- `tools/vice` - VICE emulator
- `tools/mame` - MAME (for testing)
- `tools/makefile-tools` - Common build tools

## Example GitHub Actions Workflow

```yaml
jobs:
  build-tools:
    strategy:
      matrix:
        tool: [acme, cc65, sjasmplus, vasm, nasm, armips]
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Build tool image
        uses: docker/build-push-action@v5
        with:
          context: ./tools/${{ matrix.tool }}
          push: true
          tags: ghcr.io/code198x/tools/${{ matrix.tool }}:latest
          cache-from: type=registry,ref=ghcr.io/code198x/tools/${{ matrix.tool }}:buildcache
          cache-to: type=registry,ref=ghcr.io/code198x/tools/${{ matrix.tool }}:buildcache,mode=max

  build-bases:
    needs: build-tools
    strategy:
      matrix:
        base: [6502-base, z80-base, 68000-base]
    # ... rest of base building
```

## Version Management

Each tool image would have its own versioning:
- `ghcr.io/code198x/tools/cc65:2.19`
- `ghcr.io/code198x/tools/cc65:2.19.1` (our build revision)
- `ghcr.io/code198x/tools/cc65:latest`

Base images would specify exact versions:
```dockerfile
COPY --from=ghcr.io/code198x/tools/cc65:2.19.1 /opt/cc65 /opt/cc65
```

## Estimated Time Savings

### Current Build Times
- 6502-base: 35 minutes (sequential)
- z80-base: 10 minutes
- 68000-base: 5 minutes
- Total: ~50 minutes (sequential)

### With Tool Separation
- Tool builds: 35 minutes (parallel, cached after first build)
- Base assembly: 1-2 minutes each
- Total first build: 35 minutes
- **Subsequent builds: 2-3 minutes**

## Challenges to Consider

1. **Registry Storage**: More images to store
2. **Dependency Management**: Need to track tool versions
3. **Initial Complexity**: More Dockerfiles to maintain
4. **Migration Effort**: Significant refactoring needed

## Conclusion

This architecture would dramatically improve build times, especially for incremental updates. The 6502-base build time would drop from 35 minutes to ~2 minutes after the initial tool builds are cached. This is particularly valuable for CI/CD pipelines and rapid iteration.