# Sega 32X - Genesis add-on with dual SH-2 processors
FROM ghcr.io/code198x/sh-base:latest

LABEL maintainer="code198x"
LABEL description="SuperH assembler for Sega 32X development"
LABEL version="1.0.0"
LABEL system="sega-32x"
LABEL year="1994"
LABEL cpu="SH-2 (dual)"
LABEL manufacturer="Sega"
LABEL emulator="Gens/BlastEm/MAME"
LABEL significance="Genesis add-on with 32-bit processors"

# SuperH tools are included in base image

USER root

# Copy Sega 32X-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sega-32x /opt/32x-resources

# Set up environment for Sega 32X development
ENV 32X_INCLUDES=/opt/32x-resources/includes
ENV 32X_LIBS=/opt/32x-resources/libs
ENV 32X_EXAMPLES=/opt/32x-resources/examples
ENV SYSTEM_INCLUDES=/opt/32x-resources/includes
ENV SYSTEM_LIBS=/opt/32x-resources/libs
ENV SYSTEM_EXAMPLES=/opt/32x-resources/examples

USER code198x

# Set SH assembler as the entrypoint
ENTRYPOINT ["sh-elf-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sh-elf-as --version > /dev/null