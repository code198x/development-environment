# Atari Lynx - First color handheld with hardware scaling/rotation
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Atari Lynx development"
LABEL version="1.0.0"
LABEL system="atari-lynx"
LABEL year="1989"
LABEL cpu="65SC02"
LABEL manufacturer="Atari"
LABEL emulator="Mednafen/MAME"
LABEL significance="Advanced handheld with hardware sprite scaling and rotation"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null