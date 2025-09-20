# Atari Jaguar - 64-bit console with complex architecture
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="vasm assembler for Atari Jaguar development"
LABEL version="1.0.0"
LABEL system="atari-jaguar"
LABEL year="1993"
LABEL cpu="MC68000 + custom chips"
LABEL manufacturer="Atari"
LABEL emulator="BigPEmu/MAME"
LABEL significance="Complex multi-chip architecture, last Atari console"

# vasm is included in base image

USER root

# Copy Atari Jaguar-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/atari-jaguar /opt/jaguar-resources

# Set up environment for Atari Jaguar development
ENV JAGUAR_INCLUDES=/opt/jaguar-resources/includes
ENV JAGUAR_LIBS=/opt/jaguar-resources/libs
ENV JAGUAR_EXAMPLES=/opt/jaguar-resources/examples
ENV SYSTEM_INCLUDES=/opt/jaguar-resources/includes
ENV SYSTEM_LIBS=/opt/jaguar-resources/libs
ENV SYSTEM_EXAMPLES=/opt/jaguar-resources/examples

USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasm6800_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasm6800_mot -help > /dev/null