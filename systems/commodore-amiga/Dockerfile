# VASM for Commodore Amiga
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="VASM assembler for Commodore Amiga development"
LABEL version="1.0.0"
LABEL system="commodore-amiga"

# VASM is now included in the base image
# This image provides Amiga-specific configuration

USER root

# Copy Amiga-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/commodore-amiga /opt/amiga-resources

# Set up environment for Amiga development
ENV AMIGA_INCLUDES=/opt/amiga-resources/includes
ENV AMIGA_LIBS=/opt/amiga-resources/libs
ENV AMIGA_EXAMPLES=/opt/amiga-resources/examples
ENV SYSTEM_INCLUDES=/opt/amiga-resources/includes
ENV SYSTEM_LIBS=/opt/amiga-resources/libs
ENV SYSTEM_EXAMPLES=/opt/amiga-resources/examples

USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasmm68k_mot"]

# Default command shows help
CMD ["-help"]
# Health check to verify assembler is working
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasmm68k_mot -help > /dev/null
