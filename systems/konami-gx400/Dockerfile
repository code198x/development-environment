# Konami GX400 - Gradius series arcade hardware
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="vasm assembler for Konami GX400 arcade development"
LABEL version="1.0.0"
LABEL system="konami-gx400"
LABEL year="1985"
LABEL cpu="MC68000"
LABEL manufacturer="Konami"
LABEL emulator="MAME"
LABEL significance="Gradius series, advanced sprite capabilities"

# vasm is included in base image

USER root

# Copy Konami GX400-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/konami-gx400 /opt/gx400-resources

# Set up environment for Konami GX400 development
ENV GX400_INCLUDES=/opt/gx400-resources/includes
ENV GX400_LIBS=/opt/gx400-resources/libs
ENV GX400_EXAMPLES=/opt/gx400-resources/examples
ENV SYSTEM_INCLUDES=/opt/gx400-resources/includes
ENV SYSTEM_LIBS=/opt/gx400-resources/libs
ENV SYSTEM_EXAMPLES=/opt/gx400-resources/examples

USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasm6800_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasm6800_mot -help > /dev/null