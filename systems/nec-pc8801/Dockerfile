# NEC PC-8801 - Dominant Japanese personal computer
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for PC-8801 development"
LABEL version="1.0.0"
LABEL system="nec-pc8801"
LABEL year="1981"
LABEL cpu="Z80A"
LABEL manufacturer="NEC"
LABEL emulator="M88/MAME"
LABEL significance="Massive Japanese game library, industry standard"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null