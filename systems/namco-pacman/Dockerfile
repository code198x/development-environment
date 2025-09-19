# Namco Pac-Man - Iconic arcade game hardware
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Pac-Man arcade development"
LABEL version="1.0.0"
LABEL system="namco-pacman"
LABEL year="1980"
LABEL cpu="Z80"
LABEL manufacturer="Namco"
LABEL emulator="MAME"
LABEL significance="Most iconic arcade game of all time"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null