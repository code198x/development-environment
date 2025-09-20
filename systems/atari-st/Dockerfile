# Atari ST - 68000-based personal computer
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="VASM assembler for Atari ST development"
LABEL version="1.0.0"
LABEL system="atari-st"
LABEL year="1985"
LABEL cpu="68000"
LABEL manufacturer="Atari"

# VASM is included in base image

USER root

# Copy Atari ST-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/atari-st /opt/atarist-resources

# Set up environment for Atari ST development
ENV ATARIST_INCLUDES=/opt/atarist-resources/includes
ENV ATARIST_LIBS=/opt/atarist-resources/libs
ENV ATARIST_EXAMPLES=/opt/atarist-resources/examples
ENV SYSTEM_INCLUDES=/opt/atarist-resources/includes
ENV SYSTEM_LIBS=/opt/atarist-resources/libs
ENV SYSTEM_EXAMPLES=/opt/atarist-resources/examples

USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasmm68k_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasmm68k_mot -help > /dev/null