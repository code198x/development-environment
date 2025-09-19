# SNK Neo Geo MVS - Multi Video System arcade platform
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="vasm assembler for Neo Geo MVS development"
LABEL version="1.0.0"
LABEL system="snk-neogeo-mvs"
LABEL year="1990"
LABEL cpu="MC68000"
LABEL manufacturer="SNK"
LABEL emulator="MAME/FinalBurn Neo"
LABEL significance="Premium arcade system with massive sprites and animation"

# vasm is included in base image
USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasm6800_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasm6800_mot -help > /dev/null