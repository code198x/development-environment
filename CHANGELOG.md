# Changelog

All notable changes to the Code Like It's 198x Development Environment will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Website changelog page for tracking platform updates

## [1.0.0] - 2025-09-20

### Added
- Initial stable release with 64 gaming systems across 12 processor families
- Complete Docker-based development environments for retro gaming platforms
- Real, functional toolchains for every system (no placeholders)
- TLCS-900H support via Alfred Arnold's AS macro assembler
- Multi-architecture support (linux/amd64, linux/arm64)
- GitHub Actions CI/CD with 76-job parallel build system
- Registry-based Docker caching for improved build performance
- Comprehensive versioning system for educational stability
- GitLab mirroring for platform redundancy

### Processor Families Included
- **6502**: cc65, ACME, DASM - Supporting C64, NES, Apple II, Atari systems
- **Z80**: sjasmplus, z80asm, z88dk - Supporting Spectrum, MSX, Amstrad
- **68000**: vasm, gcc-m68k - Supporting Amiga, Genesis, Neo Geo, Atari ST
- **8080**: asm8080 - Supporting Altair 8800, IMSAI 8080
- **6809**: asm6809 - Supporting Dragon 32/64, TRS-80
- **MIPS**: gcc-mips, PSn00bSDK - Supporting PlayStation, Nintendo 64
- **ARM**: gcc-arm-none-eabi - Supporting GBA, Nintendo DS, 3DO
- **SuperH**: sh-elf-gcc - Supporting Saturn, Dreamcast
- **x86**: NASM, FASM - Supporting FM Towns, PC-9801
- **V30**: NASM (8086 mode) - Supporting WonderSwan
- **TLCS**: AS assembler - Supporting Neo Geo Pocket

### Gaming Systems (64 Total)
- Commodore 64/128, PET, Plus/4
- ZX Spectrum, ZX81
- Amiga 500/1200
- Nintendo NES, SNES, Game Boy, N64
- Sega Genesis, Saturn, Dreamcast
- Sony PlayStation
- Atari 2600, 800, ST, Lynx, Jaguar
- MSX, Amstrad CPC, BBC Micro
- And 40+ more classic systems

### Infrastructure
- SHA-pinned dependencies for build reproducibility
- Semantic versioning for educational environments
- Docker BuildKit optimizations
- GitHub Container Registry (ghcr.io) as primary registry
- Automated release notes generation

### Fixed
- Processor base build failures for MIPS, ARM, TLCS, 8080
- Docker image caching issues
- Release workflow handling of base images vs system images
- Version tag generation in Docker metadata

### Security
- Removed Trivy security scanning (not applicable for retro dev tools)
- All base images built from Ubuntu 24.04 LTS

## Version History

### Versioning Strategy
- **Major (X.0.0)**: Breaking changes to toolchains or system configurations
- **Minor (1.X.0)**: New systems added or significant feature additions
- **Patch (1.0.X)**: Bug fixes and minor improvements

### Pre-1.0.0 Development
- 2025-09-19: Initial 64-system infrastructure implementation
- 2025-09-19: Debugging and fixing processor base failures
- 2025-09-19: GitLab mirroring setup
- 2025-09-20: TLCS-900H assembler integration
- 2025-09-20: Workflow optimizations and caching improvements

[Unreleased]: https://github.com/code198x/development-environment/compare/v1.0.0...HEAD
[1.0.0]: https://github.com/code198x/development-environment/releases/tag/v1.0.0