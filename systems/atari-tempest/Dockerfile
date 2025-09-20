# Atari Tempest - Color vector graphics arcade
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Tempest arcade development"
LABEL version="1.0.0"
LABEL system="atari-tempest"
LABEL year="1981"
LABEL cpu="6502"
LABEL manufacturer="Atari"
LABEL emulator="MAME"
LABEL significance="Advanced color vector graphics"

# ACME is included in base image

USER root

# Copy Atari Tempest-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/atari-tempest /opt/tempest-resources

# Set up environment for Tempest arcade development
ENV TEMPEST_INCLUDES=/opt/tempest-resources/includes
ENV TEMPEST_LIBS=/opt/tempest-resources/libs
ENV TEMPEST_EXAMPLES=/opt/tempest-resources/examples
ENV SYSTEM_INCLUDES=/opt/tempest-resources/includes
ENV SYSTEM_LIBS=/opt/tempest-resources/libs
ENV SYSTEM_EXAMPLES=/opt/tempest-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null