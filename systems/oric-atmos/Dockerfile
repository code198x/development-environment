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

USER root

# Copy Oric Atmos-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/oric-atmos /opt/atmos-resources

# Set up environment for Oric Atmos development
ENV ATMOS_INCLUDES=/opt/atmos-resources/includes
ENV ATMOS_LIBS=/opt/atmos-resources/libs
ENV ATMOS_EXAMPLES=/opt/atmos-resources/examples
ENV SYSTEM_INCLUDES=/opt/atmos-resources/includes
ENV SYSTEM_LIBS=/opt/atmos-resources/libs
ENV SYSTEM_EXAMPLES=/opt/atmos-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null