# Oric Atmos - Enhanced version of the Oric-1
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Oric Atmos development"
LABEL version="1.0.0"
LABEL system="oric-atmos"
LABEL year="1984"
LABEL cpu="6502A"
LABEL manufacturer="Oric"
LABEL emulator="Oricutron"
LABEL significance="Popular in France and UK"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null