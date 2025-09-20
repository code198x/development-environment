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

USER root

# Copy Commodore 128-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/commodore-128 /opt/c128-resources

# Set up environment for Commodore 128 development
ENV C128_INCLUDES=/opt/c128-resources/includes
ENV C128_LIBS=/opt/c128-resources/libs
ENV C128_EXAMPLES=/opt/c128-resources/examples
ENV SYSTEM_INCLUDES=/opt/c128-resources/includes
ENV SYSTEM_LIBS=/opt/c128-resources/libs
ENV SYSTEM_EXAMPLES=/opt/c128-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null