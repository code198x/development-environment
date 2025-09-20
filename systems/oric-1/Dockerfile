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

USER root

# Copy Oric-1-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/oric-1 /opt/oric1-resources

# Set up environment for Oric-1 development
ENV ORIC1_INCLUDES=/opt/oric1-resources/includes
ENV ORIC1_LIBS=/opt/oric1-resources/libs
ENV ORIC1_EXAMPLES=/opt/oric1-resources/examples
ENV SYSTEM_INCLUDES=/opt/oric1-resources/includes
ENV SYSTEM_LIBS=/opt/oric1-resources/libs
ENV SYSTEM_EXAMPLES=/opt/oric1-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null