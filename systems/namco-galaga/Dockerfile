# Namco Galaga - Multi-CPU arcade shooter
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Galaga arcade development"
LABEL version="1.0.0"
LABEL system="namco-galaga"
LABEL year="1981"
LABEL cpu="Z80 (triple)"
LABEL manufacturer="Namco"
LABEL emulator="MAME"
LABEL significance="Advanced multi-CPU coordination"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null