# Sega Genesis/Mega Drive - 16-bit game console
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="vasm assembler for Sega Genesis/Mega Drive development"
LABEL version="1.0.0"
LABEL system="sega-genesis"
LABEL year="1988"
LABEL cpu="MC68000"
LABEL manufacturer="Sega"
LABEL emulator="Gens/BlastEm/MAME"
LABEL significance="Major 16-bit console with excellent 2D capabilities"

# vasm is included in base image
USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasm6800_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasm6800_mot -help > /dev/null