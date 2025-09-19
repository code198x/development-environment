# Sharp X1 - Japanese home computer with excellent games
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Sharp X1 development"
LABEL version="1.0.0"
LABEL system="sharp-x1"
LABEL year="1982"
LABEL cpu="Z80A"
LABEL manufacturer="Sharp"
LABEL emulator="X1EMU"
LABEL significance="Popular Japanese computer with rich game library"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null