# Enterprise 128 - Advanced Hungarian home computer
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Enterprise 128 development"
LABEL version="1.0.0"
LABEL system="enterprise-128"
LABEL year="1985"
LABEL cpu="Z80A"
LABEL manufacturer="Enterprise Computers"
LABEL emulator="EP128EMU"
LABEL significance="Advanced graphics and sound capabilities"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null