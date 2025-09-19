# Oric-1 - British home computer predecessor to Atmos
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Oric-1 development"
LABEL version="1.0.0"
LABEL system="oric-1"
LABEL year="1983"
LABEL cpu="6502A"
LABEL manufacturer="Oric"
LABEL emulator="Oricutron"
LABEL significance="British 6502 computer with unique architecture"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null