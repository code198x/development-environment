# SAM Coupé - Enhanced Spectrum architecture
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for SAM Coupé development"
LABEL version="1.0.0"
LABEL system="sam-coupe"
LABEL year="1989"
LABEL cpu="Z80B"
LABEL manufacturer="Miles Gordon Technology"
LABEL emulator="SimCoupé"
LABEL significance="Advanced graphics capabilities, Spectrum successor"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null