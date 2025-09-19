# Konami GX400 - Gradius series arcade hardware
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="vasm assembler for Konami GX400 arcade development"
LABEL version="1.0.0"
LABEL system="konami-gx400"
LABEL year="1985"
LABEL cpu="MC68000"
LABEL manufacturer="Konami"
LABEL emulator="MAME"
LABEL significance="Gradius series, advanced sprite capabilities"

# vasm is included in base image
USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasm6800_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasm6800_mot -help > /dev/null