# Sega Saturn - Dual SH-2 32-bit console
FROM ghcr.io/code198x/sh-base:latest

LABEL maintainer="code198x"
LABEL description="SuperH assembler for Sega Saturn development"
LABEL version="1.0.0"
LABEL system="sega-saturn"
LABEL year="1994"
LABEL cpu="SH-2 (dual)"
LABEL manufacturer="Sega"
LABEL emulator="Mednafen/SSF/Kronos"
LABEL significance="Complex dual-CPU 32-bit system"

# SuperH tools are included in base image

USER root

# Copy Sega Saturn-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sega-saturn /opt/saturn-resources

# Set up environment for Sega Saturn development
ENV SATURN_INCLUDES=/opt/saturn-resources/includes
ENV SATURN_LIBS=/opt/saturn-resources/libs
ENV SATURN_EXAMPLES=/opt/saturn-resources/examples
ENV SYSTEM_INCLUDES=/opt/saturn-resources/includes
ENV SYSTEM_LIBS=/opt/saturn-resources/libs
ENV SYSTEM_EXAMPLES=/opt/saturn-resources/examples

USER code198x

# Set SH assembler as the entrypoint
ENTRYPOINT ["sh-elf-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sh-elf-as --version > /dev/null