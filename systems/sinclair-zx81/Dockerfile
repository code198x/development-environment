# Sinclair ZX81 - Ultra-low-cost home computer
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Sinclair ZX81 development"
LABEL version="1.0.0"
LABEL system="sinclair-zx81"
LABEL year="1981"
LABEL cpu="Z80A"
LABEL manufacturer="Sinclair Research"
LABEL emulator="EightyOne"
LABEL significance="Made computing accessible to millions"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null