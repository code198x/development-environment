# Commodore 128 - Dual processor computer with 6502 compatibility
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore 128 development"
LABEL version="1.0.0"
LABEL system="commodore-128"
LABEL year="1985"
LABEL cpu="8502/Z80A"
LABEL manufacturer="Commodore"
LABEL emulator="VICE (x128)"
LABEL significance="Last 8-bit Commodore with dual CPUs"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null