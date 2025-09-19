# Code198x Development Environment - Versioning Strategy

## Overview

The Code198x development environment consists of 64 retro gaming system containers across 12 processor families. This document defines the versioning, release, and update strategy for educational stability and production readiness.

## Versioning Scheme

### Platform Versioning (Semantic Versioning)

```
MAJOR.MINOR.PATCH[-PRERELEASE]
```

- **MAJOR**: Breaking changes, new processor families, architectural changes
- **MINOR**: New systems added, significant toolchain updates, feature additions
- **PATCH**: Bug fixes, security updates, minor toolchain improvements
- **PRERELEASE**: alpha, beta, rc1, rc2, etc.

### Examples
- `v1.0.0` - Initial stable release with 64 systems
- `v1.1.0` - Added new systems or improved existing toolchains
- `v1.0.1` - Bug fix for specific system containers
- `v2.0.0-alpha.1` - Major architecture change (pre-release)

## Container Tagging Strategy

### All containers use coordinated tags:

```yaml
# Base images
ghcr.io/code198x/code198x-base:v1.0.0
ghcr.io/code198x/6502-base:v1.0.0
ghcr.io/code198x/z80-base:v1.0.0

# System images
ghcr.io/code198x/commodore-64:v1.0.0
ghcr.io/code198x/nintendo-nes:v1.0.0
ghcr.io/code198x/sega-genesis:v1.0.0
```

### Tag Categories

1. **Versioned releases**: `v1.0.0`, `v1.1.0`, etc.
2. **Latest stable**: `latest` (always points to most recent stable)
3. **Development**: `main` (current development branch)
4. **Academic year**: `2025-spring`, `2025-fall` (for educational planning)

## Release Process

### 1. Pre-Release Testing

Before any version release:
- [ ] All 64 systems build successfully
- [ ] All 12 processor families pass health checks
- [ ] Sample assembly programs compile on each platform
- [ ] Documentation is updated
- [ ] Educational content is verified

### 2. Release Creation

1. **Tag the release**: `git tag v1.0.0`
2. **Trigger release workflow**: Builds all containers with version tag
3. **Generate release notes**: Automated changelog from commits
4. **Educational documentation**: What changed for instructors

### 3. Academic Year Releases

Special releases timed for academic calendars:
- **January**: Spring semester preparation
- **August**: Fall semester preparation
- **May**: Summer session updates

## Stability Guarantees

### For Educators

- **Patch versions** (1.0.1 → 1.0.2): Safe to update mid-semester
- **Minor versions** (1.0.0 → 1.1.0): Plan for semester breaks
- **Major versions** (1.0.0 → 2.0.0): Plan for academic year transitions

### Container Compatibility

- All containers in a release are tested together
- Mixed versions are not supported (don't use v1.0.0 base with v1.1.0 systems)
- Academic year tags provide semester-long stability

## Update Strategy

### Automated Updates
- Security patches: Automatic in patch releases
- Toolchain fixes: Included in minor releases
- New systems: Only in minor/major releases

### Manual Updates Required
- Breaking changes to command-line interfaces
- Changes to educational workflows
- Removal of deprecated systems

## Base Image Stability

### Ubuntu SHA Pinning

The root base image is pinned to a specific Ubuntu manifest list SHA for maximum reproducibility:

```dockerfile
FROM ubuntu@sha256:353675e2a41babd526e2b837d7ec780c2a05bca0164f7ea5dbbd433d21d166fc
```

**Multi-Architecture Support:**
This manifest list digest contains architecture-specific images for:
- **linux/amd64**: `sha256:985be7c735afdf6f18aaa122c23f87d989c30bba4e9aa24c8278912aac339a8d`
- **linux/arm64**: `sha256:d592e55295194d2405a9bd2ce18de6ebf0e6db2fa63d2e264d602e3281bf52b6`

**Benefits:**
- Eliminates unexpected rebuilds due to upstream changes
- Ensures identical base environments across all builds and architectures
- Prevents cache invalidation from Ubuntu updates
- Guarantees reproducible educational environments
- Works seamlessly with multi-platform Docker builds

**Update Policy:**
- SHA updates only in minor or major releases
- Security updates evaluated for urgency
- Changes documented in release notes

## Documentation Requirements

Each release includes:

1. **Release notes** - What changed
2. **Migration guide** - How to update courses
3. **New features** - What's available for educators
4. **Deprecation notices** - What will change in future versions
5. **Base image updates** - Any SHA changes and rationale

## System Sunset Policy

When systems become unsupported:
1. **Deprecation warning** - Announced 1 academic year in advance
2. **Maintenance mode** - Security updates only for 1 year
3. **Archive** - Container remains available but unsupported
4. **Alternative recommendations** - Suggested replacement systems

## Emergency Updates

For critical security issues:
- Patch release within 48 hours
- All supported versions receive updates
- Clear communication to educators about necessity

---

## Current Status

- **Development Phase**: Building v1.0.0 candidate
- **Target Stable Release**: Once all 64 systems build successfully
- **Next Minor Release**: v1.1.0 planned for Q2 2025

## Contact

For questions about versioning or to request specific educational release timing, please open an issue or contact the maintainers.