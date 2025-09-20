# Sharp X68000 - 68000-based Japanese personal computer
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="VASM assembler for Sharp X68000 development"
LABEL version="1.0.0"
LABEL system="sharp-x68000"
LABEL year="1987"
LABEL cpu="68000"
LABEL manufacturer="Sharp"

# VASM is included in base image

USER root

# Copy Sharp X68000-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sharp-x68000 /opt/x68000-resources

# Set up environment for Sharp X68000 development
ENV X68000_INCLUDES=/opt/x68000-resources/includes
ENV X68000_LIBS=/opt/x68000-resources/libs
ENV X68000_EXAMPLES=/opt/x68000-resources/examples
ENV SYSTEM_INCLUDES=/opt/x68000-resources/includes
ENV SYSTEM_LIBS=/opt/x68000-resources/libs
ENV SYSTEM_EXAMPLES=/opt/x68000-resources/examples

USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasmm68k_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasmm68k_mot -help > /dev/null