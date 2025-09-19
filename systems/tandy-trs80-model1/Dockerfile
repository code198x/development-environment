# TRS-80 Model I - First mass-produced home computer
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for TRS-80 Model I development"
LABEL version="1.0.0"
LABEL system="tandy-trs80-model1"
LABEL year="1977"
LABEL cpu="Z80A"
LABEL manufacturer="Tandy/RadioShack"
LABEL emulator="sdltrs"
LABEL significance="First mass-produced home computer"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null