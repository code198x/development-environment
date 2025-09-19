# Sega Game Gear - Color handheld console
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Sega Game Gear development"
LABEL version="1.0.0"
LABEL system="sega-game-gear"
LABEL year="1990"
LABEL cpu="Z80"
LABEL manufacturer="Sega"
LABEL emulator="MAME/Mednafen"
LABEL significance="Color handheld with Master System compatibility"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null