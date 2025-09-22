# Changelog

All notable changes to the Code Like It's 198x Development Environment will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [2.0.0] - 2025-09-22

### Changed
- **Major Performance Improvements**: Switched 5 toolchains from source builds to pre-built Ubuntu packages
  - binutils-sh: Build time reduced from 20+ minutes to ~7 seconds
  - cc65: Build time reduced from 23 seconds to 7 seconds
  - nasm: Build time reduced from 28 seconds to 5 seconds
  - acme: Build time reduced from 35 seconds to 6 seconds
  - yasm: Already using packages (no change)

### Added
- ZX Spectrum Next support via sjasmplus v1.21.0 with full Z80N instruction set
- MEGA65 support via ACME v0.97 with 45GS02 CPU extensions
- Commander X16 readiness (cc65 already supports it)
- Fail-fast disabled in GitHub Actions for independent build failures

### Fixed
- SuperH processor base now builds successfully with binutils-sh4-linux-gnu package
- NES Dockerfile corrected to use proper resource paths (nintendo-entertainment-system)
- Workflow cascade failures prevented with fail-fast: false
- Docker paths aligned with new toolchain directory structure

### Technical Details
- Timeline coverage: Systems from 1977 (Atari 2600) to 2004+ (Nintendo DS)
- 56 systems actively building in CI/CD
- 8 additional systems ready for activation (amstrad-pcw, atari-5200, atari-7800, mattel-intellivision, nintendo-snes, philips-cdi, sinclair-ql, ti-99-4a)
- All builds passing with optimized toolchains

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